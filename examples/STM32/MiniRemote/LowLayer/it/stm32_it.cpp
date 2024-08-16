/** ____________________________________________________________________
 *
 *	@file		stm32_it.c
 *
 *	@brief 		STM32 interrupts source file
 *	____________________________________________________________________
 *
 *	@attention	<center><h3>
 *	Copyright © 2023 BaseCam Electronics™.</h3></center>
 *	<center>All rights reserved.</center>
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
 *	____________________________________________________________________
 */

#include "stm32_it.h"


/*  - - - - User SBGC32_General Object - - - - - */
extern SBGC32_System Gimbal;
/* - - - - - - - - - - - - - - - - - - - - - - - */


void NMI_Handler (void)
{
	while (1);
}


void HardFault_Handler (void)
{
	#if (PROJ_NEED_FAULT_RESET)
		NVIC_SystemReset();
	#endif

	while (1);
}


void MemManage_Handler (void)
{
	while (1);
}


void BusFault_Handler (void)
{
	while (1);
}


void UsageFault_Handler (void)
{
	while (1);
}


void DebugMon_Handler (void)
{
	;
}


#if (SBGC_SEVERAL_DEVICES == sbgcOFF)

	void SBGC_UART_IRQ_HANDLER (void)
	{
		sbgcDriver_t *drv = (sbgcDriver_t*)Gimbal.GetAddressGeneralSBGC_Driver();

		sbgcUART_IRQ_Handler(Gimbal.GetAddressGeneralSBGC());

		HAL_UART_IRQHandler(drv->uart);
	}


	void SBGC_UART_DMA_TX_CH_IRQ_HANDLER (void)
	{
		sbgcDriver_t *drv = (sbgcDriver_t*)Gimbal.GetAddressGeneralSBGC_Driver();

		HAL_DMA_IRQHandler(drv->uart->hdmatx);
	}


	void SBGC_UART_DMA_RX_CH_IRQ_HANDLER (void)
	{
		sbgcDriver_t *drv = (sbgcDriver_t*)Gimbal.GetAddressGeneralSBGC_Driver();

		HAL_DMA_IRQHandler(drv->uart->hdmarx);
	}

#else

	/* The USRTs work by one and don't interfere each other */
	void SBGC_UART1_IRQ_HANDLER (void)
	{
		sbgcDriver_t *drv = (sbgcDriver_t*)Gimbal.GetAddressGeneralSBGC_Driver();

		if (__HAL_UART_GET_FLAG(drv->uart, UART_FLAG_TC) &&
			__HAL_UART_GET_IT_SOURCE(drv->uart, UART_IT_TC))
			DriverSBGC32_UART_TxCallBack((Gimbal.GetAddressGeneralSBGC())->_ll->drv);

		HAL_UART_IRQHandler(drv->uart);
	}


	void SBGC_UART1_DMA_TX_CH_IRQ_HANDLER (void)
	{
		sbgcDriver_t *drv = (sbgcDriver_t*)Gimbal.GetAddressGeneralSBGC_Driver();

		HAL_DMA_IRQHandler(drv->uart->hdmatx);
	}


	void SBGC_UART1_DMA_RX_CH_IRQ_HANDLER (void)
	{
		sbgcDriver_t *drv = (sbgcDriver_t*)Gimbal.GetAddressGeneralSBGC_Driver();

		HAL_DMA_IRQHandler(drv->uart->hdmarx);
	}


	void SBGC_UART2_IRQ_HANDLER (void)
	{
		sbgcDriver_t *drv = (sbgcDriver_t*)Gimbal.GetAddressGeneralSBGC_Driver();

		if (__HAL_UART_GET_FLAG(drv->uart, UART_FLAG_TC) &&
			__HAL_UART_GET_IT_SOURCE(drv->uart, UART_IT_TC))
			DriverSBGC32_UART_TxCallBack((Gimbal.GetAddressGeneralSBGC())->_ll->drv);

		HAL_UART_IRQHandler(drv->uart);
	}


	void SBGC_UART2_DMA_TX_CH_IRQ_HANDLER (void)
	{
		sbgcDriver_t *drv = (sbgcDriver_t*)Gimbal.GetAddressGeneralSBGC_Driver();

		HAL_DMA_IRQHandler(drv->uart->hdmatx);
	}


	void SBGC_UART2_DMA_RX_CH_IRQ_HANDLER (void)
	{
		sbgcDriver_t *drv = (sbgcDriver_t*)Gimbal.GetAddressGeneralSBGC_Driver();

		HAL_DMA_IRQHandler(drv->uart->hdmarx);
	}

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *												Other Interrupt Handlers
 */
void DJOY_XCH_TIM_IRQ_HANDLER (void)
{
	HAL_TIM_IRQHandler(DigitalJoystickChannelX.GetAddressTimHandle());
}


void DJOY_YCH_TIM_IRQ_HANDLER (void)
{
	HAL_TIM_IRQHandler(DigitalJoystickChannelY.GetAddressTimHandle());
}


void GENERAL_ADC_DMA_IRQ_HANDLER (void)
{
	HAL_DMA_IRQHandler(&AnalogInput::hdma);
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
