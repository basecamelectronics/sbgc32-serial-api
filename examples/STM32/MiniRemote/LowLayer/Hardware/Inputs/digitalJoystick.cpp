/** ____________________________________________________________________
 *
 *	@file		digitalJoystick.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "digitalJoystick.h"


DigitalJoystickChannel DigitalJoystickChannelX(	DJOY_XCH_TIM_INSTANCE,
												DJOY_XCH_TIM_IRQN,
												DJOY_XCH_TIM_IC_CHANNEL,
												PRPH_DIGITAL_JOYSTICK_CHANNEL_X,
												&GPIO_ReferenceArray[DJOY_XCH_PRPH_OFFSET],
												DJOY_CH_PRPH_PINS_NUM,
												lambdafunc_(DJOY_XCH_TIM_GPIO_CLOCK_ENABLE()),
												lambdafunc_(DJOY_XCH_TIM_CLOCK_ENABLE()),
												NO_PROCESS_FUNC);

DigitalJoystickChannel DigitalJoystickChannelY(	DJOY_YCH_TIM_INSTANCE,
												DJOY_YCH_TIM_IRQN,
												DJOY_YCH_TIM_IC_CHANNEL,
												PRPH_DIGITAL_JOYSTICK_CHANNEL_Y,
												&GPIO_ReferenceArray[DJOY_YCH_PRPH_OFFSET],
												DJOY_CH_PRPH_PINS_NUM,
												lambdafunc_(DJOY_YCH_TIM_GPIO_CLOCK_ENABLE()),
												lambdafunc_(DJOY_YCH_TIM_CLOCK_ENABLE()),
												NO_PROCESS_FUNC);


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														   Class Methods
 */
void DigitalJoystickChannel::Init (void)
{
	TIM_SlaveConfigTypeDef sSlaveConfig = {0};
	TIM_IC_InitTypeDef sConfigIC = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	InputClockEnable();

	GPIO_InitStruct.Pin			= GPIO_Channel->pin;
	GPIO_InitStruct.Mode		= GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull		= GPIO_PULLUP;
	GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate	= GPIO_Channel->pinAF;
	HAL_GPIO_Init(GPIO_Channel->port, &GPIO_InitStruct);

	ModuleClockEnable();

	htim.Instance = instance;
	htim.Init.Prescaler			= 9;
	htim.Init.CounterMode		= TIM_COUNTERMODE_UP;
	htim.Init.Period			= 0xFFFF;
	htim.Init.ClockDivision		= TIM_CLOCKDIVISION_DIV1;
	htim.Init.AutoReloadPreload	= TIM_AUTORELOAD_PRELOAD_DISABLE;

	if (HAL_TIM_IC_Init(&htim) != HAL_OK)
		HardwareErrorHandler();

	sSlaveConfig.SlaveMode			= TIM_SLAVEMODE_RESET;
	sSlaveConfig.InputTrigger		= (IC_Channel == TIM_CHANNEL_1) ? TIM_TS_TI1FP1 : TIM_TS_TI2FP2;
	sSlaveConfig.TriggerPolarity	= (IC_Channel == TIM_CHANNEL_1) ? TIM_INPUTCHANNELPOLARITY_RISING : TIM_INPUTCHANNELPOLARITY_FALLING;
	sSlaveConfig.TriggerPrescaler	= TIM_ICPSC_DIV1;
	sSlaveConfig.TriggerFilter		= 0xF;

	if (HAL_TIM_SlaveConfigSynchro(&htim, &sSlaveConfig) != HAL_OK)
		HardwareErrorHandler();

	sConfigIC.ICPolarity	= TIM_INPUTCHANNELPOLARITY_RISING;
	sConfigIC.ICSelection	= (IC_Channel == TIM_CHANNEL_1) ? TIM_ICSELECTION_DIRECTTI : TIM_ICSELECTION_INDIRECTTI;
	sConfigIC.ICPrescaler	= TIM_ICPSC_DIV1;
	sConfigIC.ICFilter		= 0xF;

	if (HAL_TIM_IC_ConfigChannel(&htim, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
		HardwareErrorHandler();

	sConfigIC.ICPolarity	= TIM_INPUTCHANNELPOLARITY_FALLING;
	sConfigIC.ICSelection	= (IC_Channel == TIM_CHANNEL_1) ? TIM_ICSELECTION_INDIRECTTI : TIM_ICSELECTION_DIRECTTI;

	if (HAL_TIM_IC_ConfigChannel(&htim, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
		HardwareErrorHandler();

	if (
		#if defined (TIM1)
			instance == TIM1
		#endif

		#if defined (TIM2)
			|| instance == TIM2
		#endif

		#if defined (TIM3)
			|| instance == TIM3
		#endif

		#if defined (TIM4)
			|| instance == TIM4
		#endif

		#if defined (TIM5)
			|| instance == TIM5
		#endif

		#if defined (TIM8)
			|| instance == TIM8
		#endif
		)
	{
		sMasterConfig.MasterOutputTrigger	= TIM_TRGO_RESET;
		sMasterConfig.MasterSlaveMode		= TIM_MASTERSLAVEMODE_DISABLE;

		if (HAL_TIMEx_MasterConfigSynchronization(&htim, &sMasterConfig) != HAL_OK)
			HardwareErrorHandler();
	}

	/* Peripheral interrupt init */
	HAL_NVIC_SetPriority(IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(IRQn);

	if (HAL_TIM_IC_Start_IT(&htim, TIM_CHANNEL_1) != HAL_OK)
		HardwareErrorHandler();

	if (HAL_TIM_IC_Start_IT(&htim, TIM_CHANNEL_2) != HAL_OK)
		HardwareErrorHandler();


	SetState(IN_ON);
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													  Interrupt Handlers
 */
volatile static ui16 uwDutyCycle, uwIC_Value;

/*	Note:	Works as input process function in passive mode
 */
void HAL_TIM_IC_CaptureCallback (TIM_HandleTypeDef *htim)
{
	/* Channel X */
	if ((DigitalJoystickChannelX.GetAddressTimHandle()->Instance == htim->Instance) &&
		(htim->Channel == ((DigitalJoystickChannelX.GetIC_Channel() == TIM_CHANNEL_1) ?
							HAL_TIM_ACTIVE_CHANNEL_1 : HAL_TIM_ACTIVE_CHANNEL_2)))
	{
		uwIC_Value = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

		if (uwIC_Value != 0)
		{
			uwDutyCycle = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2) * htim->Init.Period / uwIC_Value;
			DigitalJoystickChannelX.SetValue(uwDutyCycle);
		}
	}

	/* Channel Y */
	else if ((DigitalJoystickChannelY.GetAddressTimHandle()->Instance == htim->Instance) &&
			 (htim->Channel == ((DigitalJoystickChannelY.GetIC_Channel() == TIM_CHANNEL_1) ?
					 	 	 	 HAL_TIM_ACTIVE_CHANNEL_1 : HAL_TIM_ACTIVE_CHANNEL_2)))
	{
		uwIC_Value = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);

		if (uwIC_Value != 0)
		{
			uwDutyCycle = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1) * htim->Init.Period / uwIC_Value;
			DigitalJoystickChannelY.SetValue(uwDutyCycle);  // Note: permanent value inversion
		}
	}
}
