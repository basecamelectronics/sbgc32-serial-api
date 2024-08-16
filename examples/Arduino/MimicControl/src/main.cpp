#include "app.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                       Global Software Objects                      */
/* __________________________________________________________________ */

			sbgcGeneral_t			SBGC32_Device;

static		sbgcControl_t			Control;
static		sbgcControlConfig_t		ControlConfig;

static		sbgcConfirm_t			Confirm;

			InputsInfo_t			InputsInfo;

static		i16 servoOut [SBGC_SERVO_OUTS_NUM] = {	SBGC_SERVO_OUT_DISABLED, SBGC_SERVO_OUT_DISABLED,
													SBGC_SERVO_OUT_DISABLED, SBGC_SERVO_OUT_DISABLED};

static		AverageValue_t JoystickAverage [2];

static		ui32 currentTime;
static		ui32 lastControlTime = 0;
static		ui32 lastButtonTime;


void setup()
{
	/* Pull-up Serial 1 Rx pin */
	pinMode(19, INPUT_PULLUP);

	pinMode(DEBUG_LED_PIN, OUTPUT);
	pinMode(MENU_BTN_PIN, INPUT);
	pinMode(REC_BTN_PIN, INPUT);

	/* SimpleBGC32 Init */
	SBGC32_Init(&SBGC32_Device);

	/* Control Configurations */
	Control.mode[PITCH] = CtrlMODE_ANGLE;
	Control.mode[YAW] = CtrlMODE_ANGLE;

	Control.AxisC[PITCH].angle = 0;
	Control.AxisC[YAW].angle = 0;

	#ifdef SET_SPEED

		Control.AxisC[PITCH].speed = SET_SPEED;
		Control.AxisC[YAW].speed = SET_SPEED;

	#endif

	ControlConfig.flags = CtrlCONFIG_FLAG_NO_CONFIRM;

	InputsInfo.recBtn = BTN_RELEASED;
	InputsInfo.menuBtn = BTN_RELEASED;

	AverageInit(&JoystickAverage[0], LOW_PASS_FACTOR);
	AverageInit(&JoystickAverage[1], LOW_PASS_FACTOR);

	servoOut[PWM_SERVO_OUT_IDX] = PWM_CAM_REC_OFF;


	SBGC32_ControlConfig(&SBGC32_Device, &ControlConfig, SBGC_NO_CONFIRM);

	SBGC32_SetServoOut(&SBGC32_Device, servoOut);
}

void loop()
{
	/* Getting current time */
	currentTime = sbgcGetTick();


	/* - - - - - - - - - - Joystick Handling - - - - - - - - - - */

	ReadADC_Inputs(&InputsInfo);

	AverageValue(&JoystickAverage[0], (i16)sbgcDegreeToAngle(YAW_ANGLE_MIN) +
		(i16)((i32)InputsInfo.ADC_INx[ADC_JOY_Y] * sbgcDegreeToAngle(YAW_ANGLE_MAX - YAW_ANGLE_MIN) / (1 << ADC_RESOLUTION)));

	AverageValue(&JoystickAverage[1], (i16)sbgcDegreeToAngle(PITCH_ANGLE_MIN) +
		(i16)((i32)InputsInfo.ADC_INx[ADC_JOY_X] * sbgcDegreeToAngle(PITCH_ANGLE_MAX - PITCH_ANGLE_MIN) / (1 << ADC_RESOLUTION)));


	if ((currentTime - lastControlTime ) > CMD_CONTROL_DELAY)
	{
		lastControlTime = currentTime;

		Control.AxisC[PITCH].angle = JoystickAverage[1].avgRes;
		Control.AxisC[YAW].angle = JoystickAverage[0].avgRes;

		SBGC32_Control(&SBGC32_Device, &Control);
		/* SBGC32_CheckConfirmation(&SBGC32_Device, CMD_CONTROL, &Confirm); */
	}


	/*  - - - - - - - - - - Buttons Handling - - - - - - - - - - */
	/* Rec Button - for long press */
	if (ReadButtonState(REC_BTN_PIN))
	{
		if (InputsInfo.recBtn != BTN_PRESSED)
		{
			lastButtonTime = currentTime;
			InputsInfo.recBtn = BTN_PRESSED;
		}

		if ((currentTime - lastButtonTime > SOFTWARE_ANTI_BOUNCE))
		{
			servoOut[PWM_SERVO_OUT_IDX] = PWM_CAM_REC_ON;
			SBGC32_SetServoOut(&SBGC32_Device, servoOut);
			DEBUG_LED_ON;
		}
	}

	else if ((currentTime - lastButtonTime > SOFTWARE_ANTI_BOUNCE) &&
				(InputsInfo.recBtn == BTN_PRESSED))
	{
		servoOut[PWM_SERVO_OUT_IDX] = PWM_CAM_REC_OFF;
		SBGC32_SetServoOut(&SBGC32_Device, servoOut);
		DEBUG_LED_OFF;
		InputsInfo.recBtn = BTN_RELEASED;
	}

	/* Menu Button */
	if (ReadButtonState(MENU_BTN_PIN))
	{
		if (InputsInfo.menuBtn == BTN_RELEASED)
		{
			lastButtonTime = currentTime;
			InputsInfo.menuBtn = BTN_PRESSED;
		}

		if ((currentTime - lastButtonTime > SOFTWARE_ANTI_BOUNCE) &&
			(InputsInfo.menuBtn != BTN_POST_PRESSED))
		{
			SBGC32_ExecuteMenu(&SBGC32_Device, MENU_CMD_BUTTON_PRESS, &Confirm);

			if (SerialAPI_GetConfirmStatus(&Confirm) == sbgcCONFIRM_RECEIVED)
				InputsInfo.menuBtn = BTN_POST_PRESSED;
		}
	}

	else if ((currentTime - lastButtonTime > SOFTWARE_ANTI_BOUNCE) &&
				(InputsInfo.menuBtn != BTN_RELEASED))
		InputsInfo.menuBtn = BTN_RELEASED;


	/* Make a constant sampling time by inserting a delay of 1 ms */
	while ((sbgcGetTick() - currentTime) < 1);
}
