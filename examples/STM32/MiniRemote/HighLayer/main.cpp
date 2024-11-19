/** ____________________________________________________________________
 *
 *	@file		main.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

/* System HL includes */
#include "parameters.h"
#include "system.h"
#include "gimbal.h"


extern sPrefMenu exsPrefSBGC32_AdjvarsData;
static ui8 communicationOneTimeFlag = 0;  // needed if gimbal haven't found at startup


void SerialAPI_LinkSprintf (sbgcGeneral_t *gSBGC)
{
	gSBGC->_ll->debugSprintf = sprintf_;
}


static void SBGC32_PingCallback (void *tick)
{
	*(TickType_t*)tick = osGetTickCount();
}


void SystemClock_Config (void);
void TaskStartup (void *pvParameters);
void TaskBackground (void *pvParameters);


int main (void)
{
	HAL_Init();

	SystemClock_Config();

	/* PendSV_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(PendSV_IRQn, 3, 0);

	osTaskCreate(TaskStartup, "Initialization", configMINIMAL_STACK_SIZE * 5, NULL, OS_MEDIUM_PRIORITY, NULL);

	/* Start the scheduler */
	osTaskStartSheduler();

	while (1);
}


void TaskStartup (void *pvParameters)
{
	unused_(pvParameters);

	char miniRemoteVersionBuff [30] = { 0 };

	sbgcBoolean_t needRefreshGUI_Flag = sbgcFALSE;

	/* System startup delay */
	osDelay(10);

	/* Graphics init */
	gfxInit();

	Utils::showLogo();
	gdispSetBacklight(DEFAULT_INITIAL_BRIGHTNESS);

	/* Presets restore */
	CRC32_Module.Init();
	EEPROM.Init();

	osDelay(10);

	#if (LOADER_NEED_CHANGE_SETTINGS == SET_OFF)

		if (SettingsLoader.Boot())
			needRefreshGUI_Flag = sbgcTRUE;

		if (SettingsLoader.GetCurrentState() == LS_READ_ERROR)

	#endif

		{
			MiniRemote.SetDefaultSettings();
			Gimbal.SetDefaultSettings();

			/* Create new settings file */
			SettingsLoader.Save();
		}

	/* Current version */
	FormatMiniRemoteFirmwareVersion(MiniRemote.GetFirmwareVersion(), miniRemoteVersionBuff);
	gdispFillStringBoxSimple(4, DISPLAY_HEIGHT - SMALL_FONT_HEIGHT - 2, DISPLAY_WIDTH - 1, SMALL_FONT_HEIGHT,
							 miniRemoteVersionBuff, MiniRemote.GetSmallFont(),
							 GFX_DARK_GRAY, GFX_BLACK, justifyLeft);

	/* System init */
	MiniRemote.Init();

	if (needRefreshGUI_Flag == sbgcTRUE)
		CCreateWidget::PreInit();

	CStateManager::Init();
	CCreateWidget::Init();

	/* SimpleBGC32 Init */
	Gimbal.Init(SCParam_FREEZE, SCPrior_HIGH, 200, SBGC_NO_CALLBACK_);

	/* Pre-launch */
	CStateManager::SetState({ MAIN_CHOICE_STATE, 0 });

	if (Gimbal.GetCommunicationState())
	{
		communicationOneTimeFlag = 1;
		exCMessageWindowContainerM.SetMessage(TEXT_LENGTH_("Dummy"), MW_GIMBAL_INIT_OK_STATE, MW_MEDIUM_FONT, SHOW_MESSAGE_TIME);
	}

	else  // No-communication handle
	{
		exCMessageWindowContainerM.SetMessage(TEXT_LENGTH_("Connection is lost"), MW_NOTE_STATE, MW_MEDIUM_FONT, SHOW_MESSAGE_TIME);
		MiniRemote.SetDisconnectionMessageState(DM_SHOWED);
	}

	CStateManager::SetState({ MESSAGE_WINDOW_STATE, 0 });

	/* Background cycle start */
	osTaskCreate(TaskBackground, "Background", configMINIMAL_STACK_SIZE * 6, NULL, OS_NORMAL_PRIORITY, NULL);

	#if (PROJ_NEED_WATCHDOG)

		/* Watch Dog launch */
		WatchDog.Init();

	#endif

	osTaskDelete(NULL);

	while (1);
}


void TaskBackground (void *pvParameters)
{
	unused_(pvParameters);

	#if (SBGC_NEED_PING)
		TickType_t	xLastPingTime = osGetTickCount();
	#endif


	TickType_t		xLastButtonTime = osGetTickCount();

	ButtonState_t	controlToggleButton = BS_INIT,
					adjVarsMenuSC_Button = BS_INIT;

	TogglerState_t	controlProfileToggler = TS_INIT;


	TickType_t xNavigationBlockTime = osGetTickCount();
	while (osGetTickCount() < (xNavigationBlockTime + DEBUG_CONSOLE_MESSAGE_DELAY));

	while (1)
	{
		#if (SBGC_NEED_PING)

			/* Ping */
			if (((osGetTickCount() - xLastPingTime) > SBGC_PING_UPDATE_TIME) &&
				!SBGC_RebootStateMask(Gimbal.GetCurrentState()))
				Gimbal.ReadAngles(SCParam_NO, SCPrior_LOW, 50, SBGC32_PingCallback, &xLastPingTime);

			/* Disconnection handler */
			if (((osGetTickCount() - xLastPingTime) > DISCONNECTION_UPDATE_TIME) &&
				!SBGC_NoConnectionStateMask(Gimbal.GetCurrentState()) &&
				!SBGC_RebootStateMask(Gimbal.GetCurrentState()))
			{
				Gimbal.SetCurrentState(SBGC_LOST_CONNECTION);

				/* Waiting until other window will be hidden */
				while (CStateManager::GetCurrentState() == MESSAGE_WINDOW_STATE);

				if (MiniRemote.GetDisconnectionMessageState() == DM_NEED_TO_SHOW)
				{
					exCMessageWindowContainerM.SetMessage(TEXT_LENGTH_("Connection is lost"), MW_NOTE_STATE, MW_MEDIUM_FONT, SHOW_MESSAGE_TIME);
					CStateManager::SetState({ MESSAGE_WINDOW_STATE, 0 });
					MiniRemote.SetDisconnectionMessageState(DM_SHOWED);
					osDelay(10);
				}
			}

			if (SBGC_NoConnectionStateMask(Gimbal.GetCurrentState()) &&
			    Gimbal.GetCommunicationState())
			{
				if (Gimbal.GetPreviousState() != SBGC_LOST_CONNECTION)
					Gimbal.SetCurrentState(Gimbal.GetPreviousState());  // Return old state

				else
					Gimbal.SetCurrentState(SBGC_NORMAL);

				/* Waiting until other window will be hidden */
				while (CStateManager::GetCurrentState() == MESSAGE_WINDOW_STATE);

				MiniRemote.SetDisconnectionMessageState(DM_NEED_TO_SHOW);

				if (communicationOneTimeFlag == 0)
				{
					Gimbal.RecoverParameters(SCParam_FREEZE, SCPrior_HIGH, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);
					exCMessageWindowContainerM.SetMessage(TEXT_LENGTH_("Dummy"), MW_GIMBAL_INIT_OK_STATE, MW_MEDIUM_FONT, SHOW_MESSAGE_TIME);
					communicationOneTimeFlag = 1;
				}

				else
					exCMessageWindowContainerM.SetMessage(TEXT_LENGTH_("Connection restored"), MW_NOTE_STATE, MW_MEDIUM_FONT, SHOW_MESSAGE_TIME);

				CStateManager::SetState({ MESSAGE_WINDOW_STATE, 0 });

				Gimbal.ReadRealTimeData(SCParam_NO, SCPrior_NORMAL, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);
				Gimbal.ReadBoardInfo(0, SCParam_NO, SCPrior_LOW, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);
			}

		#endif

		/* Main button handler */
		if ((osGetTickCount() - xLastButtonTime) > TOGGLE_BUTTON_UPDATE_TIME)
		{
	    	xLastButtonTime = osGetTickCount();

	    	MiniRemote.ProcessFunction(VSF_NAVIGATION_CONTROL_TOGGLE, &controlToggleButton);

	    	if (controlToggleButton == BS_PRESSED)
	    	{
	    		if (MiniRemote.GetCurrentState() == MR_GIMBAL_CONROL)
	    		{
	    			MiniRemote.SetCurrentState(MR_MENU_CONTROL);
	    			Gimbal.ClearCurrentState(SBGC_CONTROL);

	    			/* Stop data streaming */
	    			Gimbal.StopRealTimeDataCustomStream(SCParam_FREEZE, SCPrior_NORMAL, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);

	    			/* Save control modes */
	    			ui8 modesTemp [3];

	    			for (ui8 i = 0; i < 3; i++)
	    			{
	    				modesTemp[i] = Gimbal.Control.mode[i];
	    				Gimbal.Control.mode[i] = CtrlMODE_NO_CONTROL;
	    			}

	    			/* Free control */
	    			Gimbal.ControlGimbal(SCParam_FREEZE, SCPrior_NORMAL, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);

	    			for (ui8 i = 0; i < 3; i++)
	    				Gimbal.Control.mode[i] = modesTemp[i];

	    			CStateManager::SetState({ PREVIOUS_STATE, 0 });
	    			osDelay(10);
	    		}

	    		else
	    		{
	    			MiniRemote.SetCurrentState(MR_GIMBAL_CONROL);
	    			Gimbal.AddCurrentState(SBGC_CONTROL);
	    			CStateManager::SetState({ CONTROL_STATE, 0 });
	    			osDelay(10);
	    		}
			}
		}

		/* Control mode and axes order handler */
		MiniRemote.ProcessFunction(VSF_CONTROL_PROFILE_TOGGLE, &controlProfileToggler);

		if (controlProfileToggler & TS_TRIGGER_FLAG)
		{
			controlProfileToggler = (TogglerState_t)(controlProfileToggler & ~TS_TRIGGER_FLAG);

			switch (controlProfileToggler)
			{
				case TS_UP :
					Gimbal.Presets.activeControlProfile = CTRLP_1;
					break;

				case TS_CENTER :
					Gimbal.Presets.activeControlProfile = CTRLP_2;
					break;

				case TS_DOWN :
					Gimbal.Presets.activeControlProfile = CTRLP_3;
					break;

				default :
					break;
			}

			Gimbal.ConfigGimbalControl(SCParam_FREEZE, SCPrior_HIGH, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);

			if (MiniRemote.GetCurrentState() == MR_GIMBAL_CONROL)
				CStateManager::SetState({ REFRESH_THE_STATE, 0 });
		}

		/* Shortcuts handler */
		MiniRemote.ProcessFunction(VSF_SC_MENU_ADJ_VARS, &adjVarsMenuSC_Button);

		if ((MiniRemote.GetCurrentState() != MR_GIMBAL_CONROL) &&
			(adjVarsMenuSC_Button == BS_PRESSED))
		{
			CStateManager::SetState((sDevState){ GIMBAL_MENU_STATE, ((uint32_t)&exsPrefSBGC32_AdjvarsData) });
			osDelay(10);
		}

		/* Energy mode handler */
		if (((osGetTickCount() - MiniRemote.GetLastResponseTime()) > (MiniRemote.GetBrightnessTimer() * 1000)) &&
			(!(MiniRemote.GetCurrentState() & MR_ENERGY_ECONOMIC)))
			MiniRemote.SwitchDisplayToEnergyEconomicState();

		else if (((osGetTickCount() - MiniRemote.GetLastResponseTime()) < (MiniRemote.GetBrightnessTimer() * 1000)) &&
				 (MiniRemote.GetCurrentState() & MR_ENERGY_ECONOMIC))
			MiniRemote.SwitchDisplayToNormalState();


		#if (PROJ_NEED_WATCHDOG)

			/* Watch Dog refreshing */
			WatchDog.Refresh();

		#endif

		/* Background task rate */
		osDelay(BACKGROUND_TASK_DELAY);
	}
}

/**
  * @brief System Clock Configuration
  * @retval None
  *
  */
void SystemClock_Config (void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Configure the main internal regulator output voltage
	*/
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/** Initializes the RCC Oscillators according to the specified parameters
	* in the RCC_OscInitTypeDef structure.
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 100;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;

	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
		HardwareErrorHandler();

	/** Initializes the CPU, AHB and APB buses clocks
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
							  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
		HardwareErrorHandler();
}


HAL_StatusTypeDef HAL_InitTick (uint32_t TickPriority)
{
	unused_(TickPriority);

	/* Return function status */
	return HAL_OK;
}


uint32_t HAL_GetTick (void)
{
	return osGetTickCount();
}


void HAL_Delay (__IO uint32_t Delay)
{
	osDelay(Delay);
}


void SerialAPI_FatalErrorHandler (void)
{
	/* User common error handler */
	__disable_irq();

	while (1);
}
