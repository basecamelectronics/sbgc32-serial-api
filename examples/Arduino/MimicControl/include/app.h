/*	____________________________________________________________________
 *
 *	Copyright © 2023 BaseCam Electronics™.
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
 *	This is an example sketch for Arduino, that shows how to control
 *	SimpleBGC-driven gimbal via Serial API. API specs are available at
 *	[SerialAPI](http://www.basecamelectronics.com/serialapi/)
 *
 *	# Demo: gimbal will repeat the motion of the remote controller
 *	  build of 2 potentiometers and 2 push-buttons:
 *		## "Menu" button for the gimbal controller
 *		## "Rec" button for camera control via PWM->IR converter

 *	# Hardware:
 *      ## Arduino Mega 2560
 *		## 2 potentimeters (or encoders with analog output),
 *		   connect GND, +3.3 V to the side outputs of potentiometers
 *		## 2 Buttons (Menu, Rec)
 *		## PWM-to-IR camera control adapter, connected to FC_PITCH
 *		   of gimbal controller (optional)
 *
 *	# Gimbal settings:
 *		## RC SPEED should be set high enough to track fast
 *		   movements of a controller's handle (100..150)
 *		## Acceleration limit is set to a value that the gimbal
 *		   can process without losing sync in motors
 *	____________________________________________________________________
 */

#ifndef		_APP_H_
#define 	_APP_H_

#include	"sbgc32.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								  Hardware Constants
 */
#define		DEBUG_LED_PIN			LED_BUILTIN

#define		MENU_BTN_PIN			11

#define 	JOY_X_ANALOG_PIN 		0				// Joystick X-axis input
#define 	JOY_Y_ANALOG_PIN 		1				// Joystick Y-axis input
#define 	REC_BTN_PIN				12  			// Joystick button input

#define		DEBUG_LED_ON			digitalWrite(DEBUG_LED_PIN, HIGH)
#define		DEBUG_LED_OFF			digitalWrite(DEBUG_LED_PIN, LOW)


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								  Software Constants
 */
/*  - - - - - User Defined Parameters - - - - - - */
#define		ADC_RESOLUTION			10				// Units: bits
#define 	CMD_CONTROL_DELAY 		20				// Units: milliseconds. Delay between CMD_CONTROL commands
#define		SET_SPEED				500
#define		SOFTWARE_ANTI_BOUNCE	100				// Units: milliseconds

/* Extreme angles in degrees, that corresponds to
   0..Vcc analog input range */
#define 	PITCH_ANGLE_MIN			-60
#define 	PITCH_ANGLE_MAX			60
#define 	YAW_ANGLE_MIN			-60
#define 	YAW_ANGLE_MAX			60

#define 	LOW_PASS_FACTOR 		8				/* LPF filter applied to a signal to smooth sharp movements,
													   0..12, 0 - no filtering, 12 - max filtering */

#define 	PWM_SERVO_OUT_IDX 		1 				// PWM output port index: 0 = FC_ROLL || 1 = FC_PITCH || 2 = RC_PITCH || 3 = AUX1

/* PWM values for external infra-red
   camera control adapter */
#define 	PWM_CAM_REC_ON 			2000
#define 	PWM_CAM_REC_OFF 		1000

#define		ADC_CHANNELS_QUAN		2
#define		ADC_JOY_X				0				// JOY_X_ANALOG_PIN - first conversion
#define		ADC_JOY_Y				1				// JOY_Y_ANALOG_PIN - second conversion
/*  - - - - - - - - - - - - - - - - - - - - - - - */


typedef enum
{
	BTN_RELEASED  								= 0,
	BTN_PRESSED,
	BTN_POST_PRESSED

}	ButtonState_t;


typedef struct
{
	i32		avgBuff;
	i16		avgRes;

	ui8		_factor;

}			AverageValue_t;


typedef struct
{
	/* ADC */
	ui16	ADC_INx [ADC_CHANNELS_QUAN];			// By order: A0 - JOY_X | A1 - JOY_Y

	ui8 	_curChannel;

	ButtonState_t	recBtn,
					menuBtn;

}			InputsInfo_t;


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


void ReadADC_Inputs (InputsInfo_t *inputsInfo);
ui8 ReadButtonState (ui8 pin);

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _APP_H_ */
