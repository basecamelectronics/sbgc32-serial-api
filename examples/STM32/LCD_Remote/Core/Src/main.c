/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "app.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                       Global Software Objects                      */
/* __________________________________________________________________ */

			sbgcGeneral_t			SBGC32_Device;

static 		sbgcControl_t			Control = { 0 };
static		sbgcControlConfig_t		ControlConfig = { 0 };

static		sbgcRealTimeData_t		RealTimeData;
static		sbgcGetAnglesExt_t		GetAnglesExt;

static		sbgcConfirm_t			Confirm;

static		LCD_RemoteGeneral_t		LCD_RemoteGeneral;

			InputsInfo_t			InputsInfo;


/* A set of adjustable variables that can be changed by the encoder knob.
   You may add any variables listed in the sbgcAdjVarID_t
   Be careful, this structure is placed into the RAM, which
   may be a problem with the low memory of boards */
static sbgcAdjVarGeneral_t AdjVarGeneral [] =
{
	  {	ADJ_VAR_RC_TRIM_YAW, (char*)"RC Trim YAW", -127, 127, 0, AV_NOT_SYNCHRONIZED, AV_SAVED
	},{	ADJ_VAR_RC_SPEED_PITCH, (char*)"RC Speed PITCH", 0, 255, 100, AV_NOT_SYNCHRONIZED, AV_SAVED
	},{	ADJ_VAR_RC_SPEED_YAW, (char*)"RC Speed YAW", 0, 255, 100, AV_NOT_SYNCHRONIZED, AV_SAVED
	},{	ADJ_VAR_FOLLOW_SPEED_PITCH, (char*)"Follow Speed PITCH", 0, 255, 50, AV_NOT_SYNCHRONIZED, AV_SAVED
	},{	ADJ_VAR_FOLLOW_SPEED_YAW, (char*)"Follow Speed YAW", 0, 255, 50, AV_NOT_SYNCHRONIZED, AV_SAVED
	},{	ADJ_VAR_FOLLOW_LPF_PITCH, (char*)"Follow LPF PITCH", 0, 15, 5, AV_NOT_SYNCHRONIZED, AV_SAVED
	},{	ADJ_VAR_FOLLOW_LPF_YAW, (char*)"Follow LPF YAW", 0, 15, 5, AV_NOT_SYNCHRONIZED, AV_SAVED
	},{	ADJ_VAR_FOLLOW_DEADBAND, (char*)"Follow Deadband", 0, 255, 0, AV_NOT_SYNCHRONIZED, AV_SAVED

}};

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_I2C4_Init();
  /* USER CODE BEGIN 2 */

	begin(16, 2);  // LCD Init
	WRITE_PIN(LCD_BL_GPIO_Port, LCD_BL_Pin, 1);  // LCD Backlight ON

	InitADC(&InputsInfo, JOYSTICK_ADC);
	InitI2C(&InputsInfo, ENCODER_I2C);

	/* SimpleBGC32 Init */
	SBGC32_Init(&SBGC32_Device);

	#if ((defined BLUETOOTH_DO_SETUP) && (defined BLUETOOTH_CONNECTION))

		/* Bluetooth initialization */
		WRITE_PIN(BT_EN_GPIO_Port, BT_EN_Pin, 1);  // The HC_05 EN pin became high level
		sbgcDelay(200);
		BT_MasterConnect(&SBGC32_Device);
		WRITE_PIN(BT_EN_GPIO_Port, BT_EN_Pin, 0);  // The HC_05 EN pin became low level
		sbgcDelay(BLUETOOTH_CONNECT_WAITING * 1000);

	#endif

	/* Control Configurations */
	Control.mode[PITCH] = CtrlMODE_ANGLE;
	Control.mode[YAW] = CtrlMODE_ANGLE;

	Control.AxisC[ROLL].angle = 0;
	Control.AxisC[PITCH].angle = 0;

	Control.AxisC[PITCH].speed = 0;
	Control.AxisC[YAW].speed = 0;

	#ifdef FLYWHEEL_CONTROL

		GetEncoderAngles(&InputsInfo);
		InputsInfo.FE_OldAngle = InputsInfo.FE_CurrentAngle;

	#endif

	ControlConfig.flags = CtrlCONFIG_FLAG_NO_CONFIRM;

	AverageInit(&LCD_RemoteGeneral.TargetErrorAverage, TARGET_LOW_PASS_FACTOR);
	AverageInit(&LCD_RemoteGeneral.JoystickAverage[0], JOY_LOW_PASS_FACTOR);
	AverageInit(&LCD_RemoteGeneral.JoystickAverage[1], JOY_LOW_PASS_FACTOR);

	LCD_RemoteGeneral.adjVarQuan = countof_(AdjVarGeneral);
	LCD_RemoteGeneral.currentAdjVarIndex = 0;

	LCD_RemoteGeneral.currentTimeMs = 0;
	LCD_RemoteGeneral.rtReqCmdTimeMs = 0;

	LCD_RemoteGeneral.connectFlag = 0;
	LCD_RemoteGeneral.currentPage = 0;

	LCD_RemoteGeneral.updateDisplayFlagEnable = DISPLAY_UPDATE_ENABLED;

	LCD_RemoteGeneral.motorsCurrentState = MOTORS_ON;


	SBGC32_ControlConfig(&SBGC32_Device, &ControlConfig, SBGC_NO_CONFIRM);

	SBGC32_GetAnglesExt(&SBGC32_Device, &GetAnglesExt);
	Control.AxisC[YAW].angle = (i16)GetAnglesExt.AxisGAE[YAW].frameCamAngle;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		/* Getting current time */
		LCD_RemoteGeneral.currentTimeMs = sbgcGetTick();

		/*  - - - - - - - - - Controllers Handler - - - - - - - - - - */

		if ((LCD_RemoteGeneral.currentTimeMs - LCD_RemoteGeneral.controlPause > MOTORS_ON_CONTROL_PAUSE) &&
			(LCD_RemoteGeneral.motorsCurrentState == MOTORS_ON))
		{
			#ifdef FLYWHEEL_CONTROL

				GetEncoderAngles(&InputsInfo);

				InputsInfo.deltaFW = InputsInfo.FE_CurrentAngle - InputsInfo.FE_OldAngle;

				if (abs(InputsInfo.deltaFW) > FLYWHEEL_ERROR)
				{
					if (abs(InputsInfo.deltaFW) < 2048)
						Control.AxisC[YAW].angle += InputsInfo.deltaFW * FLYWHEEL_SENSITIVITY;

					InputsInfo.FE_OldAngle = InputsInfo.FE_CurrentAngle;
					SBGC32_Control(&SBGC32_Device, &Control);
					/* SBGC32_CheckConfirmation(&SBGC32_Device, CMD_CONTROL); */

					/* if (LCD_RemoteGeneral.updateDisplayFlagEnable == DISPLAY_UPDATE_ENABLED)
						LCD_RemoteGeneral.updateDisplayFlagEnable = DISPLAY_UPDATE_DISABLED; */
				}

				/* else if (LCD_RemoteGeneral.updateDisplayFlagEnable == DISPLAY_UPDATE_DISABLED)
				{
					LCD_RemoteGeneral.updateDisplayFlagEnable = DISPLAY_UPDATE_ENABLED;
					LCD_RemoteGeneral.lowRateTimeMs = LCD_RemoteGeneral.currentTimeMs;
					LCD_RemoteGeneral.updateDisplayFlag = DISPLAY_UPDATED;
				} */

			#endif

			#ifdef JOYSTICK_CONTROL

				ReadADC_Inputs(&InputsInfo);

				if ((abs(InputsInfo.ADC_INx[ADC_JOY_X] - JOY_X_NEUTRAL) > JOYSTICK_ERROR ||
					(abs(InputsInfo.ADC_INx[ADC_JOY_Y] - JOY_Y_NEUTRAL) > JOYSTICK_ERROR)) &&
					(LCD_RemoteGeneral.currentTimeMs - LCD_RemoteGeneral.gimbalCtrlTimeMs) > CMD_CONTROL_DELAY)
				{

					Control.AxisC[PITCH].angle = InputsInfo.ADC_INx[ADC_JOY_X] - JOY_X_NEUTRAL;
					Control.AxisC[YAW].angle = InputsInfo.ADC_INx[ADC_JOY_Y] - JOY_Y_NEUTRAL;
					SBGC32_Control(&SBGC32_Device, &Control);
					/* SBGC32_CheckConfirmation(&SBGC32_Device, CMD_CONTROL); */

					LCD_RemoteGeneral.gimbalCtrlTimeMs = LCD_RemoteGeneral.currentTimeMs;

					/* if (LCD_RemoteGeneral.updateDisplayFlagEnable == DISPLAY_UPDATE_ENABLED)
						LCD_RemoteGeneral.updateDisplayFlagEnable = DISPLAY_UPDATE_DISABLED; */
				}

				if ((abs(InputsInfo.ADC_INx[ADC_JOY_X] - JOY_X_NEUTRAL) <= JOYSTICK_ERROR) &&
					(abs(InputsInfo.ADC_INx[ADC_JOY_Y] - JOY_Y_NEUTRAL) <= JOYSTICK_ERROR) &&
					((LCD_RemoteGeneral.currentTimeMs - LCD_RemoteGeneral.gimbalCtrlTimeMs) > CMD_CONTROL_DELAY) &&
					(LCD_RemoteGeneral.updateDisplayFlagEnable == DISPLAY_UPDATE_DISABLED))
				{
					/* LCD_RemoteGeneral.updateDisplayFlagEnable = DISPLAY_UPDATE_ENABLED;
					LCD_RemoteGeneral.lowRateTimeMs = LCD_RemoteGeneral.currentTimeMs;
					LCD_RemoteGeneral.updateDisplayFlag = DISPLAY_UPDATED; */

					Control.AxisC[PITCH].angle = 0;
					Control.AxisC[YAW].angle = 0;
					SBGC32_Control(&SBGC32_Device, &Control);
					/* SBGC32_CheckConfirmation(&SBGC32_Device, CMD_CONTROL); */
				}

			#endif
		}

		/* - - - - - - - - - - Knob Encoder Handler - - - - - - - - - */

		if (InputsInfo.KE_CurrentValue != 0)
		{
			SerialAPI_EditAdjVarValue(&AdjVarGeneral[LCD_RemoteGeneral.currentAdjVarIndex],
					(AdjVarGeneral[LCD_RemoteGeneral.currentAdjVarIndex].value + (InputsInfo.KE_CurrentValue * ADJ_VAR_STEP)));

			InputsInfo.KE_CurrentValue = 0;

			LCD_RemoteGeneral.updateDisplayFlag = DISPLAY_NOT_UPDATED;
		}


		/* - - - - - - - - - - - Menu Handler - - - - - - - - - - - - */

		/* Process navigation */
		if (DebounceNavigationButton(&LCD_RemoteGeneral, ReadNavigationButtonState(&InputsInfo)))
		{
			switch (LCD_RemoteGeneral.NavButton.triggerState)
			{
				case NAV_BTN_RIGHT :
					LCD_RemoteGeneral.currentAdjVarIndex =
							(LCD_RemoteGeneral.currentAdjVarIndex + 1) % LCD_RemoteGeneral.adjVarQuan;
					break;

				case NAV_BTN_LEFT :  /* Select prev adj. var */
					LCD_RemoteGeneral.currentAdjVarIndex =
							(LCD_RemoteGeneral.currentAdjVarIndex + (LCD_RemoteGeneral.adjVarQuan - 1)) % LCD_RemoteGeneral.adjVarQuan;
					break;

				case NAV_BTN_UP :  /* Select next page */
					LCD_RemoteGeneral.currentPage++;
					break;

				case NAV_BTN_DOWN :  /* Select prev page */
					LCD_RemoteGeneral.currentPage--;
					break;

				case NAV_BTN_SELECT:  /* Turn motors ON/OFF */
					SBGC32_ExecuteMenu(&SBGC32_Device, MENU_CMD_MOTOR_TOGGLE, &Confirm);

					if (SerialAPI_GetConfirmStatus(&Confirm) == sbgcCONFIRM_RECEIVED)
					{
						LCD_RemoteGeneral.motorsCurrentState = (LCD_RemoteGeneral.motorsCurrentState == MOTORS_ON) ? MOTORS_OFF : MOTORS_ON;
						if (LCD_RemoteGeneral.motorsCurrentState == MOTORS_ON)
							LCD_RemoteGeneral.controlPause = LCD_RemoteGeneral.currentTimeMs;
					}
					break;

				case NAV_BTN_ENCODER_SELECT:
					SBGC32_SaveAdjVarsToEEPROM(&SBGC32_Device, AdjVarGeneral, LCD_RemoteGeneral.adjVarQuan, SBGC_NO_CONFIRM);
					break;

				default:
					break;
			}

			/* Update display immediately to reduce lag */
			LCD_RemoteGeneral.updateDisplayFlag = DISPLAY_NOT_UPDATED;
		}

		/*  - - - - - - - - - - Buttons Handling - - - - - - - - - - */
		/* Menu Button */
		if (ReadButtonState(MENU_BTN_PORT, MENU_BTN_PIN))
		{
			if (InputsInfo.menuBtn == BTN_RELEASED)
			{
				LCD_RemoteGeneral.btnTimeMs = LCD_RemoteGeneral.currentTimeMs;
				InputsInfo.menuBtn = BTN_PRESSED;
			}

			if ((LCD_RemoteGeneral.currentTimeMs - LCD_RemoteGeneral.btnTimeMs > SOFTWARE_ANTI_BOUNCE) &&
				(InputsInfo.menuBtn != BTN_POST_PRESSED))
			{
				SBGC32_ExecuteMenu(&SBGC32_Device, MENU_CMD_BUTTON_PRESS, &Confirm);

				if (SerialAPI_GetConfirmStatus(&Confirm) == sbgcCONFIRM_RECEIVED)
					InputsInfo.menuBtn = BTN_POST_PRESSED;
			}
		}

		else if ((LCD_RemoteGeneral.currentTimeMs - LCD_RemoteGeneral.btnTimeMs > SOFTWARE_ANTI_BOUNCE) &&
				 (InputsInfo.menuBtn != BTN_RELEASED))
			InputsInfo.menuBtn = BTN_RELEASED;


		/* - - - - - - - - - AdjVarGeneral Handler - - - - - - - - - */

		/* Send the value of updated adjvars to the board */
		SBGC32_SetAdjVarValues(&SBGC32_Device, AdjVarGeneral, LCD_RemoteGeneral.adjVarQuan, SBGC_NO_CONFIRM);


		/* - - - - - - - - - - - SBGC Handler - - - - - - - - - - - - */

		ProcessHandler(&SBGC32_Device, &LCD_RemoteGeneral, &RealTimeData, AdjVarGeneral);

		/* Request realtime data with the fixed rate */
		if ((LCD_RemoteGeneral.currentTimeMs - LCD_RemoteGeneral.rtReqCmdTimeMs) > REALTIME_DATA_REQUEST_INTERAL_MS)
		{
			if (SBGC32_ReadRealTimeData4(&SBGC32_Device, &RealTimeData) == sbgcCOMMAND_OK)
				LCD_RemoteGeneral.rtReqCmdTimeMs = LCD_RemoteGeneral.currentTimeMs;
		}


		/* - - - - - - - - - - Display Updating - - - - - - - - - - - */

		/* Low-rate tasks */
		if (((LCD_RemoteGeneral.currentTimeMs - LCD_RemoteGeneral.lowRateTimeMs) > LOW_RATE_TASK_INTERVAL ||
			  LCD_RemoteGeneral.updateDisplayFlag) && !LCD_RemoteGeneral.updateDisplayFlagEnable)
			UpdateDisplay(&SBGC32_Device, &LCD_RemoteGeneral, &RealTimeData, AdjVarGeneral);  // Update LCD to display animation and state

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void SerialAPI_FatalErrorHandler (void)
{
	/* User common error handler */
	__disable_irq();

	while (1);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
