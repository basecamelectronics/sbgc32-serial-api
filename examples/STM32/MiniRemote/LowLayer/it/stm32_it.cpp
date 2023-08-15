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


#if (DRV_USE_CUBEMX == SET_OFF)

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


	#if (DRV_USE_FREERTOS == 0)

		void SVC_Handler (void)
		{
			;
		}


		void PendSV_Handler (void)
		{
			;
		}


		void SysTick_Handler (void)
		{
			#if (DRV_HAL_TIMER)
				HAL_IncTick();
			#else
				;
			#endif
		}

	#endif

	#if (DRV_HAL_TIMER || DRV_LL_TIMER)

		void SBGC_TIMER_IRQ_HANDLER (void)
		{
			/* - Main Timer Interrupt Flags Check - - */

			if (GET_FLAG_TIM_SR_UIF(SBGC_REFERENCE_TIMER) &&
				GET_FLAG_TIM_DIER_UIE(SBGC_REFERENCE_TIMER))
				TimerDRV_CallBack(SBGC32_Handy.Drv);

			/*  - - - - - - - - - - - - - - - - - - - */

			#if (DRV_HAL_TIMER)
				HAL_TIM_IRQHandler(SBGC_REFERENCE_TIMER);
			#endif
		}

	#endif


	void SBGC_UART_IRQ_HANDLER (void)
	{
		#if (DRV_USE_FREERTOS)
			UART_DRV_TxCallBack(Gimbal.GetAddressGeneralSBGC_Driver());
		#endif

		#if (DRV_HAL_NVIC_UART) || (DRV_LL_NVIC_UART)
			/*  - UART1 Interrupt Flags Check - - */

			if (GET_FLAG_UART_ISR_TC(SBGC_SERIAL_PORT) &&
				GET_FLAG_UART_CR1_TCIE(SBGC_SERIAL_PORT))
				UART_DRV_TxCallBack(SBGC32_Handy.Drv);

			if (GET_FLAG_UART_ISR_RXNE(SBGC_SERIAL_PORT) &&
				GET_FLAG_UART_CR1_RXNEIE(SBGC_SERIAL_PORT))
				UART_DRV_RxCallBack(SBGC32_Handy.Drv);

			if (GET_FLAG_UART_ISR_ORE(SBGC_SERIAL_PORT))
				CLEAR_UART_ORE(SBGC_SERIAL_PORT);

			/*  - - - - - - - - - - - - - - - - - */
		#endif

		#if (DRV_HAL_DMA_UART) || (DRV_HAL_NVIC_UART)
			HAL_UART_IRQHandler(SBGC_SERIAL_PORT);
		#endif
	}


	#if (DRV_HAL_DMA_UART) || (DRV_LL_DMA_UART)

		void SBGC_UART_DMA_TX_CH_IRQ_HANDLER (void)
		{
			#if (DRV_HAL_DMA_UART)

				Driver_t *drv = (Driver_t*)Gimbal.GetAddressGeneralSBGC_Driver();

				HAL_DMA_IRQHandler(drv->uart->hdmatx);

			#else /* DRV_LL_DMA_UART */

				if (GET_FLAG_DMA_HISR_TC_TX)
					CLEAR_DMA_TC_TX;

			#endif
		}


		void SBGC_UART_DMA_RX_CH_IRQ_HANDLER (void)
		{
			#if (DRV_HAL_DMA_UART)

				Driver_t *drv = (Driver_t*)Gimbal.GetAddressGeneralSBGC_Driver();

				HAL_DMA_IRQHandler(drv->uart->hdmarx);

			#else /* DRV_LL_DMA_UART */

				if (GET_FLAG_DMA_HISR_TC_RX)
					CLEAR_DMA_TC_RX;

			#endif
		}

	#endif
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
