#include "app.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*   					Global Software Objects  					  */
/* __________________________________________________________________ */

			GeneralSBGC_t			SBGC_1;

static 		Control_t    			Control;
static		ControlConfig_t			ControlConfig;

static		RealTimeData_t			RealTimeData;

static 		ConfirmationState_t		Confirm;

static		LCD_RemoteGeneral_t		LCD_RemoteGeneral;

			InputsInfo_t			InputsInfo;

/* LCD class for initialization */
extern 		LiquidCrystal			lcd;


/* A set of adjustable variables that can be changed by the encoder knob.
   You may add any variables listed in the AdjVarsList_t
   Be careful, this structure is placed into the RAM, which
   may be a problem with the low memory for boards */
static AdjVarsGeneral_t AdjVarsGeneral [] =
{
	  {	ADJ_VAR_BLOCK(ADJ_VAR_RC_TRIM_YAW), -127, 127 , _SIGNED_CHAR_, 5, NOT_CHANGED, SAVED
	},{	ADJ_VAR_BLOCK(ADJ_VAR_RC_SPEED_PITCH), 0, 255, _UNSIGNED_CHAR_, 5, NOT_CHANGED, SAVED
	},{	ADJ_VAR_BLOCK(ADJ_VAR_RC_SPEED_YAW), 0, 255, _UNSIGNED_CHAR_, 5, NOT_CHANGED, SAVED
	},{	ADJ_VAR_BLOCK(ADJ_VAR_FOLLOW_SPEED_PITCH), 	0, 255, _UNSIGNED_CHAR_, 5, NOT_CHANGED, SAVED
	},{	ADJ_VAR_BLOCK(ADJ_VAR_FOLLOW_SPEED_YAW), 0, 255, _UNSIGNED_CHAR_, 5, NOT_CHANGED, SAVED
	},{	ADJ_VAR_BLOCK(ADJ_VAR_FOLLOW_LPF_PITCH), 0, 15, _UNSIGNED_CHAR_, 5, NOT_CHANGED, SAVED
	},{	ADJ_VAR_BLOCK(ADJ_VAR_FOLLOW_LPF_YAW), 0, 15, _UNSIGNED_CHAR_, 5, NOT_CHANGED, SAVED
	},{	ADJ_VAR_BLOCK(ADJ_VAR_FOLLOW_DEADBAND), 0, 255, _UNSIGNED_CHAR_, 6, NOT_CHANGED, SAVED

}};


void KnobEncoderCallBackHandler (void);

/*  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */

void setup()
{
	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
	/*                         Initialization                         */
	/* ______________________________________________________________ */

	/*  - - - - - - - - - - - - Hardware Init - - - - - - - - - - - - */

	/* Serial initialization */
    SBGC_SERIAL_PORT.begin(SBGC_SERIAL_SPEED);
	DEBUG_SERIAL_PORT.begin(DEBUG_SERIAL_SPEED);
	Wire.begin();

	pinMode(SERIAL2_RX_PIN, INPUT_PULLUP);
	pinMode(MENU_BTN_PIN, INPUT);

	/* LCD initialization */
	lcd.begin(LCD_COLS, LCD_ROWS);

	/* Enable back light */
	pinMode(LCD_BACKLIGHT_PIN, OUTPUT);
	digitalWrite(LCD_BACKLIGHT_PIN, 1);

	/* Encoder setup */
	pinMode(ENCODER_A_PIN, INPUT);
	pinMode(ENCODER_B_PIN, INPUT);
	digitalWrite(ENCODER_A_PIN, 1);
	digitalWrite(ENCODER_B_PIN, 1);
	attachInterrupt(1, KnobEncoderCallBackHandler, FALLING);  // Interrupts: numbers 0 (on digital pin 2) and 1 (on digital pin 3) 

	
  	/*  - - - - - - - - SBGC Hardware-Software Init - - - - - - - - - */

  	/* High Layer Init */
  	SBGC32_DefaultInit(&SBGC_1, UartTransmitData, UartReceiveByte, GetAvailableBytes,
  			  		   UartTransmitDebugData, GetTimeMs, SBGC_PROTOCOL_V2);


	/* - - - - - - - - - High Layer Software Init - - - - - - - - - - */

	#if ((defined BLUETOOTH_DO_SETUP) && (defined BLUETOOTH_CONNECTION))

		/* The HC_05 EN pin became high level */
		BT_MasterConnect(&SBGC_1);
		/* The HC_05 EN pin became low level */
		delay(BLUETOOTH_CONNECT_WAITING * 1000);

	#endif

  	Control.controlMode[ROLL] = CtrlM_MODE_ANGLE;
  	Control.controlMode[PITCH] = CtrlM_MODE_ANGLE;
  	Control.controlMode[YAW] = CtrlM_MODE_ANGLE;

	Control.AxisC[ROLL].angle = 0;
	Control.AxisC[PITCH].angle = 0;
	Control.AxisC[YAW].angle = 0;

	Control.AxisC[ROLL].speed = 0;
	Control.AxisC[PITCH].speed = 0;
	Control.AxisC[YAW].speed = 0;

	#ifdef FLYWHEEL_CONTROL

		GetEncoderAngles(&InputsInfo);
		InputsInfo.FE_OldAngle = InputsInfo.FE_CurrentAngle;

	#endif

	ControlConfig.flags = RTCCF_CONTROL_CONFIG_FLAG_NO_CONFIRM;

	AverageInit(&LCD_RemoteGeneral.TargetErrorAverage, TARGET_LOW_PASS_FACTOR);
	AverageInit(&LCD_RemoteGeneral.JoystickAverage[0], JOY_LOW_PASS_FACTOR);
	AverageInit(&LCD_RemoteGeneral.JoystickAverage[1], JOY_LOW_PASS_FACTOR);

	LCD_RemoteGeneral.adjVarQuan = countof(AdjVarsGeneral);
	LCD_RemoteGeneral.currentAdjVarIndex = 0;

	LCD_RemoteGeneral.currentTimeMs = 0;
	LCD_RemoteGeneral.rtReqCmdTimeMs = 0;

	LCD_RemoteGeneral.connectFlag = 0;
	LCD_RemoteGeneral.currentPage = 0;

	LCD_RemoteGeneral.updateDisplayFlagEnable = DISPLAY_UPDATE_ENABLED;

	LCD_RemoteGeneral.motorsCurrentState = MOTORS_ON;


	/*  - - - - - - - - - Initializing commands - - - - - - - - - - - */

	SBGC32_ControlConfig(&SBGC_1, &ControlConfig, &Confirm);


	/*  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */
}

void loop()
{

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
	/*                     Start Worker Cycle                     */
	/* __________________________________________________________ */

	/* Getting current time */
	LCD_RemoteGeneral.currentTimeMs = SBGC_1.GetTimeFunc(SBGC_1.Drv);


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
				SBGC32_Control(&SBGC_1, &Control);
				/* SBGC32_CheckConfirmation(&SBGC_1, &Confirm, CMD_CONTROL); */

				if (LCD_RemoteGeneral.updateDisplayFlagEnable == DISPLAY_UPDATE_ENABLED)
					LCD_RemoteGeneral.updateDisplayFlagEnable = DISPLAY_UPDATE_DISABLED;
			}

			else if (LCD_RemoteGeneral.updateDisplayFlagEnable == DISPLAY_UPDATE_DISABLED)
			{
				LCD_RemoteGeneral.updateDisplayFlagEnable = DISPLAY_UPDATE_ENABLED;
				LCD_RemoteGeneral.lowRateTimeMs = LCD_RemoteGeneral.currentTimeMs;
				LCD_RemoteGeneral.updateDisplayFlag = DISPLAY_UPDATED;
			}

		#endif

		#ifdef JOYSTICK_CONTROL

			ReadADC_Inputs(&InputsInfo);

			if ((abs(InputsInfo.ADC_INx[ADC_JOY_X] - JOY_X_NEUTRAL) > JOYSTICK_ERROR ||
				(abs(InputsInfo.ADC_INx[ADC_JOY_Y] - JOY_Y_NEUTRAL) > JOYSTICK_ERROR)) &&
				(LCD_RemoteGeneral.currentTimeMs - LCD_RemoteGeneral.gimbalCtrlTimeMs) > CMD_CONTROL_DELAY)
			{

				Control.AxisC[PITCH].angle = InputsInfo.ADC_INx[ADC_JOY_X] - JOY_X_NEUTRAL;
				Control.AxisC[YAW].angle = InputsInfo.ADC_INx[ADC_JOY_Y] - JOY_Y_NEUTRAL;
				SBGC32_Control(&SBGC_1, &Control);
				/* SBGC32_CheckConfirmation(&SBGC_1, &Confirm, CMD_CONTROL); */

				LCD_RemoteGeneral.gimbalCtrlTimeMs = LCD_RemoteGeneral.currentTimeMs;

				if (LCD_RemoteGeneral.updateDisplayFlagEnable == DISPLAY_UPDATE_ENABLED)
					LCD_RemoteGeneral.updateDisplayFlagEnable = DISPLAY_UPDATE_DISABLED;
			}

			if ((abs(InputsInfo.ADC_INx[ADC_JOY_X] - JOY_X_NEUTRAL) <= JOYSTICK_ERROR) &&
				(abs(InputsInfo.ADC_INx[ADC_JOY_Y] - JOY_Y_NEUTRAL) <= JOYSTICK_ERROR) &&
				((LCD_RemoteGeneral.currentTimeMs - LCD_RemoteGeneral.gimbalCtrlTimeMs) > CMD_CONTROL_DELAY) &&
				(LCD_RemoteGeneral.updateDisplayFlagEnable == DISPLAY_UPDATE_DISABLED))
			{
				LCD_RemoteGeneral.updateDisplayFlagEnable = DISPLAY_UPDATE_ENABLED;
				LCD_RemoteGeneral.lowRateTimeMs = LCD_RemoteGeneral.currentTimeMs;
				LCD_RemoteGeneral.updateDisplayFlag = DISPLAY_UPDATED;

				Control.AxisC[PITCH].angle = 0;
				Control.AxisC[YAW].angle = 0;
				SBGC32_Control(&SBGC_1, &Control);
				/* SBGC32_CheckConfirmation(&SBGC_1, &Confirm, CMD_CONTROL); */
			}

		#endif
	}

	/* - - - - - - - - - - Knob Encoder Handler - - - - - - - - - */

	if (InputsInfo.KE_CurrentValue != 0)
	{
		EditAdjVarValue(&AdjVarsGeneral[LCD_RemoteGeneral.currentAdjVarIndex],
						(AdjVarsGeneral[LCD_RemoteGeneral.currentAdjVarIndex].value + (InputsInfo.KE_CurrentValue * ADJ_VAR_STEP)));

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
				if (SBGC32_ExecuteMenu(&SBGC_1, MENU_CMD_MOTOR_TOGGLE, &Confirm) == TX_RX_OK)
				{
					LCD_RemoteGeneral.motorsCurrentState = (LCD_RemoteGeneral.motorsCurrentState == MOTORS_ON) ? MOTORS_OFF : MOTORS_ON;
					if (LCD_RemoteGeneral.motorsCurrentState == MOTORS_ON)
						LCD_RemoteGeneral.controlPause = LCD_RemoteGeneral.currentTimeMs;
				}
				break;

			case NAV_BTN_ENCODER_SELECT:
				SBGC32_SaveAdjVarsToEEPROM(&SBGC_1, AdjVarsGeneral, LCD_RemoteGeneral.adjVarQuan, &Confirm);
				break;

			default:
				break;
		}

		/* Update display immediately to reduce lag */
		LCD_RemoteGeneral.updateDisplayFlag = DISPLAY_NOT_UPDATED;
	}

	/*  - - - - - - - - - - Buttons Handling - - - - - - - - - - */

	/* Menu Button */
	if (ReadButtonState(MENU_BTN_PIN))
	{
		if (InputsInfo.menuBtn == BTN_RELEASED)
		{
			LCD_RemoteGeneral.btnTimeMs = LCD_RemoteGeneral.currentTimeMs;
			InputsInfo.menuBtn = BTN_PRESSED;
		}

		if ((LCD_RemoteGeneral.currentTimeMs - LCD_RemoteGeneral.btnTimeMs > SOFTWARE_ANTI_BOUNCE) &&
			(InputsInfo.menuBtn != BTN_POST_PRESSED))
		{
			SBGC32_ExecuteMenu(&SBGC_1, MENU_BUTTON_IS_PRESSED, &Confirm);
			InputsInfo.menuBtn = BTN_POST_PRESSED;
		}
	}

	else if ((LCD_RemoteGeneral.currentTimeMs - LCD_RemoteGeneral.btnTimeMs > SOFTWARE_ANTI_BOUNCE) &&
				(InputsInfo.menuBtn != BTN_RELEASED))
		InputsInfo.menuBtn = BTN_RELEASED;


	/* - - - - - - - - - AdjVarsGeneral Handler - - - - - - - - - */

	/* Send the value of updated adjvars to the board */
	SBGC32_SetAdjVarValues(&SBGC_1, AdjVarsGeneral, LCD_RemoteGeneral.adjVarQuan, &Confirm);


	/* - - - - - - - - - - - SBGC Handler - - - - - - - - - - - - */

	ProcessHandler(&SBGC_1, &LCD_RemoteGeneral, &RealTimeData, AdjVarsGeneral);

	/* Request realtime data with the fixed rate */
	if ((LCD_RemoteGeneral.currentTimeMs - LCD_RemoteGeneral.rtReqCmdTimeMs) > REALTIME_DATA_REQUEST_INTERAL_MS)
	{
		if (SBGC32_ReadRealTimeData4(&SBGC_1, &RealTimeData) == TX_RX_OK)
			LCD_RemoteGeneral.rtReqCmdTimeMs = LCD_RemoteGeneral.currentTimeMs;
	}


	/* - - - - - - - - - - Display Updating - - - - - - - - - - - */

	/* Low-rate tasks */
	if (((LCD_RemoteGeneral.currentTimeMs - LCD_RemoteGeneral.lowRateTimeMs) > LOW_RATE_TASK_INTERVAL ||
			LCD_RemoteGeneral.updateDisplayFlag) && !LCD_RemoteGeneral.updateDisplayFlagEnable)
		UpdateDisplay(&SBGC_1, &LCD_RemoteGeneral, &RealTimeData, AdjVarsGeneral);  // Update LCD to display animation and state

	/*  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */
}


void KnobEncoderCallBackHandler (void)
{
	if (digitalRead(ENCODER_B_PIN))  // Increment
		InputsInfo.KE_CurrentValue++;

	else  // Decrement
		InputsInfo.KE_CurrentValue--;
}
