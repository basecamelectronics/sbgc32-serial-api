/** ____________________________________________________________________
 *
 *	@file		incrementalEncoder.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "incrementalEncoder.h"


IncrementalEncoder LeftIncrementalEncoder(	INC_ENC2_TIM_INSTANCE,
											PRPH_LEFT_INCREMENTAL_ENCODER,
											&GPIO_ReferenceArray[INC_ENC_PRPH_OFFSET + INC_ENC_PRPH_PINS_NUM],
											INC_ENC_PRPH_PINS_NUM,
											lambafunc_(INC_ENC2_ACH_TIM_GPIO_CLOCK_ENABLE(); INC_ENC2_BCH_TIM_GPIO_CLOCK_ENABLE()),
											lambafunc_(INC_ENC2_TIM_CLOCK_ENABLE()),
											LeftIncrementalEncoderReadCount);

IncrementalEncoder RightIncrementalEncoder(	INC_ENC1_TIM_INSTANCE,
											PRPH_RIGHT_INCREMENTAL_ENCODER,
											&GPIO_ReferenceArray[INC_ENC_PRPH_OFFSET],
											INC_ENC_PRPH_PINS_NUM,
											lambafunc_(INC_ENC1_ACH_TIM_GPIO_CLOCK_ENABLE(); INC_ENC1_BCH_TIM_GPIO_CLOCK_ENABLE()),
											lambafunc_(INC_ENC1_TIM_CLOCK_ENABLE()),
											RightIncrementalEncoderReadCount);

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														   Class Methods
 */
void IncrementalEncoder::Init (void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	TIM_Encoder_InitTypeDef sConfig = {0};

	InputClockEnable();

	GPIO_InitStruct.Pin			= GPIO_Channel[0].pin;
	GPIO_InitStruct.Mode		= GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull		= GPIO_PULLUP;
	GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate	= GPIO_Channel[0].pinAF;
	HAL_GPIO_Init(GPIO_Channel[0].port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin			= GPIO_Channel[1].pin;
	GPIO_InitStruct.Mode		= GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull		= GPIO_PULLUP;
	GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate	= GPIO_Channel[1].pinAF;
	HAL_GPIO_Init(GPIO_Channel[1].port, &GPIO_InitStruct);


	ModuleClockEnable();

	htim.Instance				= instance;
	htim.Init.Prescaler			= 0;
	htim.Init.CounterMode		= TIM_COUNTERMODE_UP;
	htim.Init.Period			= 65535;
	htim.Init.ClockDivision		= TIM_CLOCKDIVISION_DIV1;
	htim.Init.RepetitionCounter	= 0;
	htim.Init.AutoReloadPreload	= TIM_AUTORELOAD_PRELOAD_DISABLE;

	sConfig.EncoderMode		= TIM_ENCODERMODE_TI12;
	sConfig.IC1Polarity		= TIM_ICPOLARITY_RISING;
	sConfig.IC1Selection	= TIM_ICSELECTION_DIRECTTI;
	sConfig.IC1Prescaler	= TIM_ICPSC_DIV1;
	sConfig.IC1Filter		= 0x0F;
	sConfig.IC2Polarity		= TIM_ICPOLARITY_RISING;
	sConfig.IC2Selection	= TIM_ICSELECTION_DIRECTTI;
	sConfig.IC2Prescaler	= TIM_ICPSC_DIV1;
	sConfig.IC2Filter		= 0x0F;

	if (HAL_TIM_Encoder_Init(&htim, &sConfig) != HAL_OK)
		HardwareErrorHandler();

	if (HAL_TIM_Encoder_Start(&htim, TIM_CHANNEL_ALL) != HAL_OK)
		HardwareErrorHandler();


	SetState(IN_ON);
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														  Free Functions
 */
void LeftIncrementalEncoderReadCount (void)
{
	LeftIncrementalEncoder.SetValue(__HAL_TIM_GET_COUNTER(LeftIncrementalEncoder.GetAddressTimHandle()) / 4);
}


void RightIncrementalEncoderReadCount (void)
{
	RightIncrementalEncoder.SetValue(__HAL_TIM_GET_COUNTER(RightIncrementalEncoder.GetAddressTimHandle()) / 4);
}
