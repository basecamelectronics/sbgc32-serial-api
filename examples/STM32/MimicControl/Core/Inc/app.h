/** ____________________________________________________________________
 *
 *	@file		app.h
 *
 *				BaseCamElectronics Team
 *
 *				Mimic Control project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	This is an example sketch for STM32, that shows how to control
 *	SimpleBGC-driven gimbal via Serial API. API specs are available at
 *	[SerialAPI](http://www.basecamelectronics.com/serialapi/)
 *
 *	# Demo: gimbal will repeat the motion of the remote controller
 *	  build of 2 potentiometers and 2 push-buttons:
 *		## "Menu" button for the gimbal controller
 *		## "Rec" button for camera control via PWM->IR converter

 *	# Hardware:
 *		## NUCLEO-F767ZI
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
 *		   can process without losing sync in the motors
 *	____________________________________________________________________
 */

#ifndef		_APP_H_
#define 	_APP_H_

#ifdef 		__cplusplus
extern 		"C" {
#endif

#include	"adc.h"
#include	"sbgc32.h"


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

	#define	GET_ADC_CONV_DATA(ADC)		LL_ADC_REG_ReadConversionData12(inputsInfo->adc)

	#define	GET_FLAG_ADC_SR_EOC(ADC)	LL_ADC_IsActiveFlag_EOCS(ADC)
	#define	GET_FLAG_ADC_CR1_EOCIE(ADC)	LL_ADC_IsEnabledIT_EOCS(ADC)
#endif

/*				    ### GPIO ###				  */
/*  - - - - - User Defined Parameters - - - - - - */
#define		REC_BTN_PORT		REC_BTN_GPIO_Port
#define		REC_BTN_PIN			REC_BTN_Pin
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
#else		/* LL_GPIO */
	#define	READ_PIN(PORT, PIN)	LL_GPIO_IsInputPinSet(PORT, PIN)

	#define	DEBUG_LED_ON		LL_GPIO_SetOutputPin(LED_GPIO_Port, LED_Pin);
	#define	DEBUG_LED_OFF		LL_GPIO_ResetOutputPin(LED_GPIO_Port, LED_Pin);
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								  Software Constants
 */
/*  - - - - - User Defined Parameters - - - - - - */
#define		ADC_RESOLUTION			12				// Units: bits
#define 	CMD_CONTROL_DELAY 		20				// Units: milliseconds. Delay between CMD_CONTROL commands
#define		SET_SPEED				500
#define		SOFTWARE_ANTI_BOUNCE	100				// Units: milliseconds

/* Extreme angles in degrees, that corresponds to
   0..VCC analog input range */
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
#define		ADC_JOY_X				0				// ADC_IN0 - first conversion
#define		ADC_JOY_Y				1				// ADC_IN4 - second conversion
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
	ui16	ADC_INx [ADC_CHANNELS_QUAN];			// By order: IN0 - JOY_X | IN4 - JOY_Y

	ui8 	_curChannel;

	__ADC_STRUCT;

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


void InitADC (InputsInfo_t *inputsInfo, __ADC_STRUCT);
void ReadADC_Inputs (InputsInfo_t *inputsInfo);
void ADC_DRV_EndConvCallBack (InputsInfo_t *inputsInfo);
ui8 ReadButtonState (__GPIO_STRUCT, ui16 pin);


#ifdef 		__cplusplus
			}
#endif

#endif		/* _APP_H_ */
