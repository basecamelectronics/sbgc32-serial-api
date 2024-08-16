/** ____________________________________________________________________
 *
 *	@file		peripheral.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "peripheral.h"


/*	This array provide hardware driver with low layer inputs mapping
 *	to peripheral layer for correct GPIO initialization
 */
const GPIO_Channel_t GPIO_ReferenceArray [] =
	/*
	||			GPIO PIN		  ||		   GPIO PORT		  ||		 GPIO PIN AF		 ||
	 */
	{ {	DJOY_XCH_TIM_IC_PIN,		DJOY_XCH_TIM_IC_GPIO_PORT,		DJOY_XCH_TIM_IC_PIN_AF
	},{	DJOY_YCH_TIM_IC_PIN,		DJOY_YCH_TIM_IC_GPIO_PORT,		DJOY_YCH_TIM_IC_PIN_AF
	},{	ABS_ENC_I2C_SDA_PIN,		ABS_ENC_I2C_SDA_GPIO_PORT,		ABS_ENC_I2C_SDA_PIN_AF
	},{	ABS_ENC_I2C_SCL_PIN,		ABS_ENC_I2C_SCL_GPIO_PORT,		ABS_ENC_I2C_SCL_PIN_AF
	},{	INC_ENC1_ACH_TIM_EM_PIN,	INC_ENC1_ACH_TIM_EM_GPIO_PORT,	INC_ENC1_ACH_TIM_EM_PIN_AF
	},{	INC_ENC1_BCH_TIM_EM_PIN,	INC_ENC1_BCH_TIM_EM_GPIO_PORT,	INC_ENC1_BCH_TIM_EM_PIN_AF
	},{	INC_ENC2_ACH_TIM_EM_PIN,	INC_ENC2_ACH_TIM_EM_GPIO_PORT,	INC_ENC2_ACH_TIM_EM_PIN_AF
	},{	INC_ENC2_BCH_TIM_EM_PIN,	INC_ENC2_BCH_TIM_EM_GPIO_PORT,	INC_ENC2_BCH_TIM_EM_PIN_AF
	},{	AJOY_XCH_ADC_PIN,			AJOY_XCH_ADC_GPIO_PORT,			0
	},{	AJOY_YCH_ADC_PIN,			AJOY_YCH_ADC_GPIO_PORT,			0
	},{	POT_ADC_PIN,				POT_ADC_GPIO_PORT,				0
	},{	ENC1_BUT_PIN,				ENC1_BUT_GPIO_PORT,				0
	},{	ENC2_BUT_PIN,				ENC2_BUT_GPIO_PORT,				0
	},{	BUT1_PIN,					BUT1_GPIO_PORT,					0
	},{	BUT2_PIN,					BUT2_GPIO_PORT,					0
	},{	TSW1_PIN,					TSW1_GPIO_PORT,					0
	},{	TSW2_PIN,					TSW2_GPIO_PORT,					0

	}};


Input *inputClassesArray [] =
{
	&DigitalJoystickChannelX,
	&DigitalJoystickChannelY,
	&AbsoluteEncoder,
	&LeftIncrementalEncoder,
	&RightIncrementalEncoder,
	&AnalogJoystickChannelX,
	&AnalogJoystickChannelY,
	&Potentiometer,
	&Encoder1_Button,
	&Encoder2_Button,
	&Button1,
	&Button2,
	&ToggleSwitch1,
	&ToggleSwitch2

	/* Total members quantity must be equal HW_NUM_INPUTS */
};


void TaskStartPeripheral (void *params)
{
	/* Inputs peripheral init */
	osTaskCreate(	TaskInputsManage,
					"PeripheralManage",
					configMINIMAL_STACK_SIZE * 2,
					NULL,
					OS_HIGHEST_PRIORITY,
					NULL);

	osTaskDelete(NULL);

	while (1);
}


void TaskInputsManage (void *params)
{
	for (ui8 i = 0; i < countof_(inputClassesArray); i++)
	{
		if (inputClassesArray[i]->GetState() == IN_NEED_INIT)
			inputClassesArray[i]->Init();

		else if (inputClassesArray[i]->GetState() == IN_NEED_DEINIT)
			inputClassesArray[i]->Deinit();
	}

	osTaskDelete(NULL);

	while (1);
}
