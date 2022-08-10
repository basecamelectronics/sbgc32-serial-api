/*  ____________________________________________________________________
 *
 *	Copyright © 2022 BaseCam Electronics™.
 *	All rights reserved.
 *
 *	Licensed under the Apache License, Version 2.0 (the "License");
 *	you may not use this file except in compliance with the License.
 *	You may obtain a copy of the License at
 *
 *	http://www.apache.org/licenses/LICENSE-2.0
 *
 *	Unless required by applicable law or agreed to in writing, software
 *	distributed under the License is distributed on an "AS IS" BASIS,
 *	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 *	implied. See the License for the specific language governing
 *	permissions and limitations under the License.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	This is an example sketch for STM32, that shows how to control
 *	SimpleBGC-driven gimbal via Serial API. API specs are available at
 *	[SerialAPI](http://www.basecamelectronics.com/serialapi/)
 *
 *	# Basic functions:
 *		## Display system status using multiple pages
 *		   (Up/Down arrow to scroll):
 *			### Battery voltage
 *			### Active profile
 *			### Average error of stabilization in 0.001 degrees
 *			### Communication errors, I2C errors, various debug info
 *			### Display a customizable set of adjustable variables
 *				(Left/Right arrow or encoder Push-button to scroll),
 *				change their values by the rotary encoder and save
 *				to EEPROM by pressing an encoder button
 *		## Trim ROLL axis with 0.1-degree precision
 *		## Use an analog joystick to control the PITCH and YAW axis
 *		   (passed to SBGC controller as regular RC channels)
 *		## Joystick push-button acts as "Menu" button
 *		## Navigation "select" button turns motors ON/OFF
 *
 *	# Hardware:
 *		## NUCLEO-F767ZI
 *		## LCD Key Shield from ELECFREAKS, that includes:
 *			### 1602 LCD display
 *			### Rotary encoder with push button
 *			### 5 navigation buttons (Left, Right, Up, Down, Select)
 *		## 2-axis joystick with push button
 *		## Wireless serial connection (optional)
 *
 *	# Gimbal settings:
 *		## Firmware version 2.61 or above
 *		## RC control in SPEED or ANGLE mode
 *		## Assign desired actions to the "Menu" button
 *		   in the "Service" tab
 *	____________________________________________________________________
 */

#ifndef		_APP_H_
#define 	_APP_H_

#ifdef 		__cplusplus
extern 		"C" {
#endif

#include	"driver_STM32.h"
#include	"adc.h"
#include	"i2c.h"

#include 	"LiquidCrystal.h"

#include 	"gimbalControl/gimbalControl.h"
#include 	"realtime/realtime.h"
#include 	"adjvar/adjvar.h"
#include 	"service/service.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 						 Hardware Macros & Constants
 */
/*					### ADC ###					  */
#ifdef 		HAL_ADC_MODULE_ENABLED
	/*  - - - - User Defined Parameters - - - - - */
	#define	JOYSTICK_ADC		&hadc1
	/*  - - - - - - - - - - - - - - - - - - - - - */

	#define	__ADC_STRUCT		ADC_HandleTypeDef *adc

	#define	START_ADC(ADC)		HAL_ADC_Start_IT(ADC)
	#define	STOP_ADC(ADC)		HAL_ADC_Stop_IT(ADC)

	#define	DISABLE_ADC_CR1_EOCIE(ADC)	__HAL_ADC_DISABLE_IT(ADC, ADC_CR1_EOCIE)

	#define	GET_ADC_CONV_DATA(ADC)		(ui16)(READ_BIT((ADC)->Instance->DR, ADC_DR_DATA))

	#define	GET_FLAG_ADC_SR_EOC(ADC)	__HAL_ADC_GET_FLAG(ADC, ADC_SR_EOC)
	#define	GET_FLAG_ADC_CR1_EOCIE(ADC)	__HAL_ADC_GET_IT_SOURCE(ADC, ADC_CR1_EOCIE)
#else		/* LL_ADC */
	/*  - - - - User Defined Parameters - - - - - */
	#define	JOYSTICK_ADC		ADC1
	/*  - - - - - - - - - - - - - - - - - - - - - */

	#define	__ADC_STRUCT		ADC_TypeDef *adc

	#define	START_ADC(ADC)		LL_ADC_Enable(ADC);\
								LL_ADC_EnableIT_EOCS(ADC);\
								LL_ADC_REG_StartConversionSWStart(ADC)
	#define	STOP_ADC(ADC)		LL_ADC_Disable(ADC);\
								LL_ADC_DisableIT_EOCS(ADC)

	#define	DISABLE_ADC_CR1_EOCIE(ADC)	LL_ADC_DisableIT_EOCS(ADC)

	#define	GET_ADC_CONV_DATA(ADC)		LL_ADC_REG_ReadConversionData12(inputsInfo->adc)  // (READ_BIT(ADCx->DR, ADC_DR_DATA));

	#define	GET_FLAG_ADC_SR_EOC(ADC)	LL_ADC_IsActiveFlag_EOCS(ADC)
	#define	GET_FLAG_ADC_CR1_EOCIE(ADC)	LL_ADC_IsEnabledIT_EOCS(ADC)
#endif

/*				    ### I2C ###					  */
#ifdef 		HAL_I2C_MODULE_ENABLED
	/*  - - - - User Defined Parameters - - - - - */
	#define	ENCODER_I2C			&hi2c4
	/*  - - - - - - - - - - - - - - - - - - - - - */

	#define	__I2C_STRUCT		I2C_HandleTypeDef *i2c
#else		/* LL_I2C */
	/*  - - - - User Defined Parameters - - - - - */
	#define	ENCODER_I2C			I2C4
	/*  - - - - - - - - - - - - - - - - - - - - - */

	#define	__I2C_STRUCT		I2C_TypeDef *i2c
#endif

/*				    ### GPIO ###				  */
/*  - - - - - User Defined Parameters - - - - - - */
#define		MENU_BTN_PORT		MENU_BTN_GPIO_Port
#define		MENU_BTN_PIN		MENU_BTN_Pin
#define		DEBUG_LED_PORT		LED_GPIO_Port
#define		DEBUG_LED_PIN		LED_Pin
/*  - - - - - - - - - - - - - - - - - - - - - - - */

#define		__GPIO_STRUCT		GPIO_TypeDef *gpio

#ifdef 		HAL_GPIO_MODULE_ENABLED
	#define	READ_PIN(PORT, PIN)	HAL_GPIO_ReadPin(PORT, PIN)

	#define	DEBUG_LED_ON		HAL_GPIO_WritePin(DEBUG_LED_PORT, DEBUG_LED_PIN, GPIO_PIN_SET);
	#define	DEBUG_LED_OFF		HAL_GPIO_WritePin(DEBUG_LED_PORT, DEBUG_LED_PIN, GPIO_PIN_RESET);

	#define	GET_FLAG_EXTI_ENC(PIN)		__HAL_GPIO_EXTI_GET_IT(PIN)
#else		/* LL_GPIO */
	#define	READ_PIN(PORT, PIN)	LL_GPIO_IsInputPinSet(PORT, PIN)

	#define	DEBUG_LED_ON		LL_GPIO_SetOutputPin(DEBUG_LED_PORT, DEBUG_LED_PIN);
	#define	DEBUG_LED_OFF		LL_GPIO_ResetOutputPin(DEBUG_LED_PORT, DEBUG_LED_PIN);

	#define	GET_FLAG_EXTI_ENC(PIN)		LL_EXTI_IsActiveFlag_0_31(PIN)
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								  Software Constants
 */
/*  - - - - - User Defined Parameters - - - - - - */
/* BLUETOOTH_HC05. Be sure to use the HC-05 module with a KEY pin. This pin should be pulled to 3.3V
 * If you are using the Bluetooth module, set the SBGC_RX_WAITING to at least 500
 */
#define		BLUETOOTH_CONNECTION

/* 12 hex digits: "XXXX,XX,XXXXXX" */
#define		BLUETOOTH_CLIENT_MAC_ADDR	"0020,10,08CF59"

/* If defined, will search for a device containing this pattern in its name */
#define		BLUETOOTH_CLIENT_NAME_PTRN	"SBGC"

#define		BLUETOOTH_CLIENT_PIN		"1234"		// PIN code set for connection

#define		BLUETOOTH_BAUD				115200

//#define		BLUETOOTH_DO_SETUP						// Configure BT module as master role and set PIN. May be done only once.
#define		BLUETOOTH_BUF_SIZE			16			// Size of buffer for service answers from module

#define		BLUETOOTH_CONNECT_WAITING	10			// Units: seconds

#define		FLYWHEEL_CONTROL
//#define		JOYSTICK_CONTROL

#define		MOTORS_ON_CONTROL_PAUSE		3000		// Units: milliseconds

#define		CMD_CONTROL_DELAY			50			// Units: milliseconds

#define		FLYWHEEL_SENSITIVITY		0.05		// Rotation sensitivity coefficient. Recommended borders: 0.01 --> 0.2
#define		FLYWHEEL_ERROR				2			// (error from 12-bit message)

#define		JOY_X_NEUTRAL				2048
#define		JOY_Y_NEUTRAL				2048

#define		JOYSTICK_ERROR				200			// Joystick center error (from 12-bit message)

#define		SOFTWARE_ANTI_BOUNCE		100			// Units: milliseconds

#define 	REALTIME_DATA_REQUEST_INTERAL_MS	500	// Interval between realtime data requests
#define 	JOYSTICK_CMD_SEND_INTERVAL_MS		50	// Interval of sending joystick control commands

#define	 	MAX_WAIT_TIME_MS 			2000  		// Time to wait for incoming commands to be in CONNECTED state
#define 	LOW_RATE_TASK_INTERVAL 		500  		// Interval between low-priority tasks (display update, etc)

#define	 	ADJ_VAR_NAME_MAX_LENGTH 	10
#define		ADJ_VAR_STEP				1.0

#define 	TARGET_LOW_PASS_FACTOR 		6			// 0 --> 16. LPF filter applied to a signal to smooth sharp movements
#define 	JOY_LOW_PASS_FACTOR			11			// 0 --> 12. LPF filter applied to a signal to smooth sharp movements

#define 	LCD_ROWS 					2
#define 	LCD_COLS 					16

#define		ENCODER_I2C_ADDRES			(64	<< 1)	// Without hardware changes. "64" is manual address of AS5048 encoder
#define		ENCODER_ANGLE_REG_MB		0xFE
#define		ENCODER_ANGLE_REG_LB		0xFF

#define		ADC_NAV						0			// ADC_IN3 - first conversion

#ifdef		JOYSTICK_CONTROL
	#define	ADC_CHANNELS_QUAN			3
	#define	ADC_JOY_X					1			// ADC_IN5 - second conversion
	#define	ADC_JOY_Y					2			// ADC_IN6 - third conversion
#else
	#define	ADC_CHANNELS_QUAN			1
#endif
/*  - - - - - - - - - - - - - - - - - - - - - - - */


typedef enum
{
	BTN_RELEASED  								= 0,
	BTN_PRESSED,
	BTN_POST_PRESSED

}	ButtonState_t;


typedef enum
{
	NAV_BTN_RELEASED							= 0,

	NAV_BTN_RIGHT,
	NAV_BTN_UP,
	NAV_BTN_DOWN,
	NAV_BTN_LEFT,
	NAV_BTN_SELECT,
	NAV_BTN_ENCODER_SELECT

}	ButtonDirection_t;


typedef enum
{
	DISPLAY_UPDATED								= 0,
	DISPLAY_NOT_UPDATED

}	DisplayUpdateFlag_t;


typedef enum
{
	DISPLAY_UPDATE_ENABLED						= 0,
	DISPLAY_UPDATE_DISABLED

}	DisplayUpdateEnableFlag_t;


typedef enum
{
	MOTORS_ON									= 0,
	MOTORS_OFF

}	MotorsState_t;


typedef struct
{
	ui16	lastTimeMs;

	ButtonDirection_t	state; 						// Current state
	ButtonDirection_t	triggerState; 				// De-bounced const state

} 			ButtonInfo_t;


typedef struct
{
	i32		avgBuff;
	i16		avgRes;

	ui8		_factor;

}			AverageValue_t;


typedef struct
{
	/* ADC */
	ui16	ADC_INx [ADC_CHANNELS_QUAN];			// By order: IN3 - NAV | IN5 - JOY_X | IN6 - JOY_Y

	ui8 	_curChannel;

	__ADC_STRUCT;

	/* Flywheel Encoder */
	ui8 	I2C_Buff [2];							// Size of encoder's message

	ui16	FE_CurrentAngle,
			FE_OldAngle;

	i16		deltaFW;

	__I2C_STRUCT;

	/* Knob Encoder */
	i8		KE_CurrentValue;

	/* Buttons */
	ButtonState_t	menuBtn;

}			InputsInfo_t;


typedef struct
{
	AverageValue_t	JoystickAverage [2],
					TargetErrorAverage;

	ButtonInfo_t	NavButton;

	ui8		currentAdjVarIndex;
	ui8 	adjVarQuan;

	ui32 	currentTimeMs,

			lowRateTimeMs,
 			rtReqCmdTimeMs,
			gimbalCtrlTimeMs,
			btnTimeMs;

 	ui8 	connectFlag;
 	i8 		currentPage;

 	i16 	debug1,
	 		debug2,
			debug3,
			debug4;

 	DisplayUpdateEnableFlag_t	updateDisplayFlagEnable;
 	DisplayUpdateFlag_t			updateDisplayFlag;

 	MotorsState_t	motorsCurrentState;
 	ui32	controlPause;

}			LCD_RemoteGeneral_t;


static inline void AverageInit (AverageValue_t *averageValue, ui8 factor)
{
	averageValue->_factor = factor;
	averageValue->avgBuff = 0;
	averageValue->avgRes = 0;
}


static inline void AverageValue (AverageValue_t *averageValue, i16 value)
{
	averageValue->avgBuff += (i32)value - (i32)averageValue->avgRes;
	averageValue->avgRes = (i16)(averageValue->avgBuff >> averageValue->_factor);
}


static inline void LCD_PrintProgress (LCD_RemoteGeneral_t *LCD_RemoteGeneral, ui8 cursor_pos)
{
	for (ui8 i = 0; i < 3; i++)
		cursor_pos += print_char(((ui8)(LCD_RemoteGeneral->currentTimeMs / 1000)) % 4 > i ? '.' : ' ');
}


static inline void LCD_FillSpace (ui8 *cursor_pos, ui8 to_pos)
{
	while (*cursor_pos < to_pos)
	{
		print_char(' ');
		(*cursor_pos)++;
	}
}


void ProcessHandler (GeneralSBGC_t *generalSBGC, LCD_RemoteGeneral_t *LCD_RemoteGeneral,
					 RealTimeData_t *realTimeData, AdjVarsGeneral_t *adjVarGeneral);
ui8 DebounceNavigationButton (LCD_RemoteGeneral_t *LCD_RemoteGeneral, ButtonDirection_t newState);

ButtonDirection_t ReadNavigationButtonState (InputsInfo_t *inputsInfo);
void UpdateDisplay (GeneralSBGC_t *generalSBGC, LCD_RemoteGeneral_t *LCD_RemoteGeneral,
					RealTimeData_t *realTimeData, AdjVarsGeneral_t *adjVarGeneral);
void LCD_DebugMessage (ui8 raw, char *str, ui8 length);
ui8 BT_ReadAnswer (GeneralSBGC_t *generalSBGC, ui8 *buf, ui16 timeout, Boolean_t debug);
void BT_MasterConnect (GeneralSBGC_t *generalSBGC);

void InitADC (InputsInfo_t *inputsInfo, __ADC_STRUCT);
void ReadADC_Inputs (InputsInfo_t *inputsInfo);
void ADC_DRV_EndConvCallBack (InputsInfo_t *inputsInfo);
ui8 ReadButtonState (__GPIO_STRUCT, ui16 pin);
void EXTI_DRV_FallingCallBack (InputsInfo_t *inputsInfo, ui16 pin);
void InitI2C (InputsInfo_t *inputsInfo, __I2C_STRUCT);
void GetEncoderAngles (InputsInfo_t *inputsInfo);

/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef 		__cplusplus
			}
#endif

#endif		/* _APP_H_ */
