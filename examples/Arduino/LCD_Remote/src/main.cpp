#include "app.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                       Global Software Objects                      */
/* __________________________________________________________________ */

			sbgcGeneral_t			SBGC32_Device;

static 		sbgcControl_t    		Control = { 0 };
static		sbgcControlConfig_t		ControlConfig = { 0 };

static		sbgcRealTimeData_t		RealTimeData;
static		sbgcGetAnglesExt_t		GetAnglesExt;

static		sbgcConfirm_t			Confirm;

static		LCD_RemoteGeneral_t		LCD_RemoteGeneral;

			InputsInfo_t			InputsInfo;

/* LCD class for initialization */
extern 		LiquidCrystal			lcd;


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


/* Function prototypes */
void KnobEncoderCallBackHandler (void);


void setup()
{
	Wire.begin();

	/* Pull-up Serial 1 Rx pin */
	pinMode(19, INPUT_PULLUP);

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

	/* SimpleBGC32 Init */
	SBGC32_Init(&SBGC32_Device);

	#if ((defined BLUETOOTH_DO_SETUP) && (defined BLUETOOTH_CONNECTION))

		/* Bluetooth initialization */
		/* The HC_05 EN pin became high level */
		BT_MasterConnect(&SBGC32_Device);
		/* The HC_05 EN pin became low level */
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
}

void loop()
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
}


void KnobEncoderCallBackHandler (void)
{
	if (digitalRead(ENCODER_B_PIN))  // Increment
		InputsInfo.KE_CurrentValue++;

	else  // Decrement
		InputsInfo.KE_CurrentValue--;
}
