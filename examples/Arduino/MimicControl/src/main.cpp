#include "app.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*   					Global Software Objects  					  */
/* __________________________________________________________________ */

			GeneralSBGC_t			SBGC32_Device;

static 		Control_t    			Control;
static		ControlConfig_t			ControlConfig;

			InputsInfo_t			InputsInfo;

static		i16 servoOut [8] = {	SERVO_OUT_DISABLED, SERVO_OUT_DISABLED,
									SERVO_OUT_DISABLED, SERVO_OUT_DISABLED,
									SERVO_OUT_DISABLED, SERVO_OUT_DISABLED,
									SERVO_OUT_DISABLED, SERVO_OUT_DISABLED};

static		AverageValue_t JoystickAverage [2];

static		ui32 currentTime;
static 		ui32 lastControlTime = 0;
static 		ui32 lastButtonTime;

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

	pinMode(SERIAL2_RX_PIN, INPUT_PULLUP);
	pinMode(DEBUG_LED_PIN, OUTPUT);
	pinMode(MENU_BTN_PIN, INPUT);
	pinMode(REC_BTN_PIN, INPUT);

	/*  - - - - - - - - - - Software Initialization - - - - - - - - - */

	/* SimpleBGC32 Init */
	SBGC32_Init(&SBGC32_Device);

	/* Control Configurations */
	Control.controlMode[PITCH] = CtrlM_MODE_ANGLE;
	Control.controlMode[YAW] = CtrlM_MODE_ANGLE;

	Control.AxisC[PITCH].angle = 0;
	Control.AxisC[YAW].angle = 0;

	#ifdef SET_SPEED

		Control.AxisC[PITCH].speed = SET_SPEED;
		Control.AxisC[YAW].speed = SET_SPEED;

	#endif

	ControlConfig.flags = RTCCF_CONTROL_CONFIG_FLAG_NO_CONFIRM;

	InputsInfo.recBtn = BTN_RELEASED;
	InputsInfo.menuBtn = BTN_RELEASED;

	AverageInit(&JoystickAverage[0], LOW_PASS_FACTOR);
	AverageInit(&JoystickAverage[1], LOW_PASS_FACTOR);

	servoOut[PWM_SERVO_OUT_IDX] = PWM_CAM_REC_OFF;


	/*  - - - - - - - - - Initializing commands - - - - - - - - - - - */

	SBGC32_ControlConfig(&SBGC32_Device, &ControlConfig);

	SBGC32_SetServoOut(&SBGC32_Device, servoOut);

	/*  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */
}

void loop()
{
	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
	/* 						  Start Worker Cycle					  */
	/* ______________________________________________________________ */

	/* Getting current time */
	currentTime = SBGC32_Device.GetTimeFunc(SBGC32_Device.Drv);


	/*  - - - - - - - - - - - Joystick Handling - - - - - - - - - - - */

	ReadADC_Inputs(&InputsInfo);

	AverageValue(&JoystickAverage[0], (i16)DEGREE_TO_ANGLE_INT(YAW_ANGLE_MIN) +
		(i16)((i32)InputsInfo.ADC_INx[ADC_JOY_Y] * DEGREE_TO_ANGLE_INT(YAW_ANGLE_MAX - YAW_ANGLE_MIN) / (1 << ADC_RESOLUTION)));

	AverageValue(&JoystickAverage[1], (i16)DEGREE_TO_ANGLE_INT(PITCH_ANGLE_MIN) +
		(i16)((i32)InputsInfo.ADC_INx[ADC_JOY_X] * DEGREE_TO_ANGLE_INT(PITCH_ANGLE_MAX - PITCH_ANGLE_MIN) / (1 << ADC_RESOLUTION)));


	if ((currentTime - lastControlTime ) > CMD_CONTROL_DELAY)
	{
		lastControlTime = currentTime;

		Control.AxisC[PITCH].angle = JoystickAverage[1].avgRes;
		Control.AxisC[YAW].angle = JoystickAverage[0].avgRes;

		SBGC32_Control(&SBGC32_Device, &Control);
		/* SBGC32_CheckConfirmation(&SBGC32_Device, CMD_CONTROL); */
	}


	/* - - - - - - - - - - - - Buttons Handling - - - - - - - - - - - */

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
			SBGC32_ExecuteMenu(&SBGC32_Device, MENU_BUTTON_IS_PRESSED);
			InputsInfo.menuBtn = BTN_POST_PRESSED;
		}
	}

	else if ((currentTime - lastButtonTime > SOFTWARE_ANTI_BOUNCE) &&
				(InputsInfo.menuBtn != BTN_RELEASED))
		InputsInfo.menuBtn = BTN_RELEASED;


	/* Make a constant sampling time by inserting a delay of 1 ms */
	while ((SBGC32_Device.GetTimeFunc(SBGC32_Device.Drv) - currentTime) < 1);

	/*  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */
}
