/** ____________________________________________________________________
 *
 * 	SBGC32 Serial API Library v1.1
 *
 *	@file		driver_STM32.c
 *
 *	@brief 		STM32 driver source file
 *	____________________________________________________________________
 *
 *	@attention	<h3><center>
 *				Copyright © 2023 BaseCam Electronics™.<br>
 *				All rights reserved.
 *				</center></h3>
 *
 *				<center><a href="https://www.basecamelectronics.com">
 *				www.basecamelectronics.com</a></center>
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

#include "../../sbgc32.h"


#if (SBGC_USE_STM32_DRIVER)

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *												Initialization Functions
 */
/**	@addtogroup	STM32_Driver
 *	@{
 */
#if (DRV_USE_CUBEMX == SET_OFF)

	/* Creating global driver variables */
	#if (DRV_HAL_NVIC_UART || DRV_HAL_DMA_UART)
		SBGC_UART_DCLR;

		#if (DRV_USE_UART_DEBUG)
			DEBUG_UART_DCLR;
		#endif

		#if (DRV_HAL_DMA_UART)
			SBGC_UART_DMA_DCLR;
		#endif
	#endif

	#if (DRV_HAL_TIMER)
		SBGC_TIMER_DCLR;
	#endif

	#if (DRV_HAL_NVIC_UART || DRV_HAL_DMA_UART || DRV_HAL_TIMER)

		/** @brief	User driver errors handler
		 */
		static void DrvErrorHandler (void)
		{
			__disable_irq();

			while (1)
			{
				/* - - - - - User Driver Errors Handler - - - - - */
				;
				/*  - - - - - - - - - - - - - - - - - - - - - - - */
			}
		}

	#endif


	/**	@note	Private function
	 */
	static void DrvSetPeripheryClock (void)
	{
		#if (DRV_HAL_TIMER || DRV_LL_TIMER)
			SBGC_TIMER_CLOCK_ENABLE;
		#endif

		SBGC_UART_GPIO_CLOCK_ENABLE;
		SBGC_UART_CLOCK_ENABLE;

		#if (DRV_HAL_DMA_UART || DRV_LL_DMA_UART)
			SBGC_UART_DMA_CLOCK_ENABLE;
		#endif

		#if (DRV_USE_UART_DEBUG)
			DEBUG_UART_GPIO_CLOCK_ENABLE;
			DEBUG_UART_CLOCK_ENABLE;
		#endif
	}


	/**	@note	Private function
	 */
	static void DrvResetPeripheryClock (void)
	{
		#if (DRV_HAL_TIMER || DRV_LL_TIMER)
			SBGC_TIMER_CLOCK_DISABLE;
		#endif

		SBGC_UART_GPIO_CLOCK_DISABLE;
		SBGC_UART_CLOCK_DISABLE;

		#if (DRV_HAL_DMA_UART || DRV_LL_DMA_UART)
			SBGC_UART_DMA_CLOCK_DISABLE;
		#endif

		#if (DRV_USE_UART_DEBUG)
			DEBUG_UART_GPIO_CLOCK_DISABLE;
			DEBUG_UART_CLOCK_DISABLE;
		#endif
	}


	/**	@note	Private function
	 */
	static void UART_DrvPinDetermination (Driver_t *driver)
	{
		driver->SBGC_UART_GPIO.txPin	= SBGC_UART_TX_PIN;
		driver->SBGC_UART_GPIO.txPort	= SBGC_UART_TX_GPIO_PORT;
		driver->SBGC_UART_GPIO.txAF		= SBGC_UART_TX_PIN_AF;

		driver->SBGC_UART_GPIO.rxPin	= SBGC_UART_RX_PIN;
		driver->SBGC_UART_GPIO.rxPort	= SBGC_UART_RX_GPIO_PORT;
		driver->SBGC_UART_GPIO.rxAF		= SBGC_UART_RX_PIN_AF;

		#if (DRV_USE_UART_DEBUG)

			driver->DebugUART_GPIO.txPin	= DEBUG_UART_TX_PIN;
			driver->DebugUART_GPIO.txPort	= DEBUG_UART_TX_GPIO_PORT;
			driver->DebugUART_GPIO.txAF		= DEBUG_UART_TX_PIN_AF;

			driver->DebugUART_GPIO.rxPin	= DEBUG_UART_RX_PIN;
			driver->DebugUART_GPIO.rxPort	= DEBUG_UART_RX_GPIO_PORT;
			driver->DebugUART_GPIO.rxAF		= DEBUG_UART_RX_PIN_AF;

		#endif
	}


	/**	@note	Private function
	 */
	static void UART_DrvPeriphDetermination (Driver_t *driver)
	{
		#if (DRV_HAL_TIMER)

			driver->tim->Instance	= SBGC_TIMER_INSTANCE;
			driver->TIM_IRQn		= SBGC_TIMER_IRQN;

		#endif

		#if (DRV_LL_TIMER)

			driver->tim			= SBGC_TIMER_INSTANCE;
			driver->TIM_IRQn	= SBGC_TIMER_IRQN;

		#endif

		#if (DRV_HAL_NVIC_UART) || (DRV_HAL_DMA_UART)
			driver->uart->Instance	= SBGC_UART_INSTANCE;
		#else /* DRV_LL_NVIC_UART || DRV_LL_DMA_UART */
			driver->uart = SBGC_UART_INSTANCE;
		#endif

		driver->SBGC_SerialSpeed = SBGC_UART_SERIAL_SPEED;

		driver->UART_IRQn = SBGC_UART_IRQN;

		#if (DRV_HAL_DMA_UART) || (DRV_LL_DMA_UART)

			driver->DMA_TxIRQn	= SBGC_UART_DMA_TX_CH_IRQN;
			driver->DMA_RxIRQn	= SBGC_UART_DMA_RX_CH_IRQN;

			#if (DRV_HAL_DMA_UART)

				driver->hdmaTx	= SBGC_UART_DMA_NAME;
				driver->hdmaRx	= SBGC_UART_DMA_NAME;

			#endif

		#endif

		#if (DRV_USE_UART_DEBUG)

			#if (DRV_HAL_NVIC_UART) || (DRV_HAL_DMA_UART)
				driver->debugUart->Instance	= DEBUG_UART_INSTANCE;
			#else /* DRV_LL_NVIC_UART || DRV_LL_DMA_UART */
				driver->debugUart = DEBUG_UART_INSTANCE;
			#endif

			driver->debugSerialSpeed = DEBUG_UART_SERIAL_SPEED;

		#endif
	}


	/**	@note	Private function\n
	 *			Changes to the function body are allowed
	 */
	static void UART_DrvInit (Driver_t *driver)
	{
		/* Timer Init */
		#if (DRV_HAL_TIMER)

			TIM_ClockConfigTypeDef sClockSourceConfig = {0};
			TIM_MasterConfigTypeDef sMasterConfig = {0};

			driver->tim->Init.Prescaler			= (SBGC_TIMER_BUS_FREQ / 1000000) - 1;
			driver->tim->Init.CounterMode		= TIM_COUNTERMODE_UP;
			driver->tim->Init.Period			= 999;
			driver->tim->Init.ClockDivision 	= TIM_CLOCKDIVISION_DIV1;
			driver->tim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

			if (HAL_TIM_Base_Init(driver->tim) != HAL_OK)
				DrvErrorHandler();

			sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;

			if (HAL_TIM_ConfigClockSource(driver->tim, &sClockSourceConfig) != HAL_OK)
				DrvErrorHandler();

			sMasterConfig.MasterOutputTrigger	= TIM_TRGO_UPDATE;
			sMasterConfig.MasterSlaveMode		= TIM_MASTERSLAVEMODE_DISABLE;

			if (HAL_TIMEx_MasterConfigSynchronization(driver->tim, &sMasterConfig) != HAL_OK)
				DrvErrorHandler();

			/* TIMx Interrupt Init */
			HAL_NVIC_SetPriority(driver->TIM_IRQn, SBGC_TIMER_IRQ_PRIORITY, 0);
			HAL_NVIC_EnableIRQ(driver->TIM_IRQn);

		#elif (DRV_LL_TIMER)

			LL_TIM_InitTypeDef TIM_InitStruct = {0};

			TIM_InitStruct.Prescaler		= (SBGC_TIMER_BUS_FREQ / 1000000) - 1;
			TIM_InitStruct.CounterMode		= LL_TIM_COUNTERMODE_UP;
			TIM_InitStruct.Autoreload		= 999;
			TIM_InitStruct.ClockDivision	= LL_TIM_CLOCKDIVISION_DIV1;

			LL_TIM_Init(driver->tim, &TIM_InitStruct);
			LL_TIM_DisableARRPreload(driver->tim);
			LL_TIM_SetClockSource(driver->tim, LL_TIM_CLOCKSOURCE_INTERNAL);
			LL_TIM_SetTriggerOutput(driver->tim, LL_TIM_TRGO_UPDATE);
			LL_TIM_DisableMasterSlaveMode(driver->tim);

			/* TIMx Interrupt Init */
			NVIC_SetPriority(driver->TIM_IRQn, SBGC_TIMER_IRQ_PRIORITY);
			NVIC_EnableIRQ(driver->TIM_IRQn);

		#endif


		/* UART Init */
		#if (DRV_HAL_NVIC_UART) || (DRV_HAL_DMA_UART)

			/* Configure the UART peripheral */
			GPIO_InitTypeDef SBGC_GPIO_InitStruct;

			/* UART Tx GPIO pin configuration */
			SBGC_GPIO_InitStruct.Pin		= driver->SBGC_UART_GPIO.txPin;
			SBGC_GPIO_InitStruct.Mode		= GPIO_MODE_AF_PP;
			SBGC_GPIO_InitStruct.Pull		= GPIO_PULLUP;
			SBGC_GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_HIGH;
			SBGC_GPIO_InitStruct.Alternate	= driver->SBGC_UART_GPIO.txAF;

			HAL_GPIO_Init(driver->SBGC_UART_GPIO.txPort, &SBGC_GPIO_InitStruct);

			/* UART Rx GPIO pin configuration */
			SBGC_GPIO_InitStruct.Pin		= driver->SBGC_UART_GPIO.rxPin;
			SBGC_GPIO_InitStruct.Alternate	= driver->SBGC_UART_GPIO.rxAF;

			HAL_GPIO_Init(driver->SBGC_UART_GPIO.rxPort, &SBGC_GPIO_InitStruct);

			#if (DRV_HAL_DMA_UART)

				/* Configure the DMA handler for reception process */
				driver->hdmaRx.Instance					= SBGC_UART_DMA_RX_INSTANCE;
				driver->hdmaRx.Init.Channel				= SBGC_UART_DMA_RX_CHANNEL;
				driver->hdmaRx.Init.Direction			= DMA_PERIPH_TO_MEMORY;
				driver->hdmaRx.Init.PeriphInc			= DMA_PINC_DISABLE;
				driver->hdmaRx.Init.MemInc				= DMA_MINC_ENABLE;
				driver->hdmaRx.Init.PeriphDataAlignment	= DMA_PDATAALIGN_BYTE;
				driver->hdmaRx.Init.MemDataAlignment	= DMA_MDATAALIGN_BYTE;
				driver->hdmaRx.Init.Mode				= DMA_CIRCULAR;
				driver->hdmaRx.Init.Priority			= DMA_PRIORITY_HIGH;
				driver->hdmaRx.Init.FIFOMode			= DMA_FIFOMODE_DISABLE;

				if (HAL_DMA_Init(&driver->hdmaRx) != HAL_OK)
					DrvErrorHandler();

				/* Associate the initialized DMA handle to the UART handle */
				__HAL_LINKDMA(driver->uart, hdmarx, driver->hdmaRx);


				/* Configure the DMA handler for transmission process */
				driver->hdmaTx.Instance					= SBGC_UART_DMA_TX_INSTANCE;
				driver->hdmaTx.Init.Channel				= SBGC_UART_DMA_TX_CHANNEL;
				driver->hdmaTx.Init.Direction			= DMA_MEMORY_TO_PERIPH;
				driver->hdmaTx.Init.PeriphInc			= DMA_PINC_DISABLE;
				driver->hdmaTx.Init.MemInc				= DMA_MINC_ENABLE;
				driver->hdmaTx.Init.PeriphDataAlignment	= DMA_PDATAALIGN_BYTE;
				driver->hdmaTx.Init.MemDataAlignment	= DMA_MDATAALIGN_BYTE;
				driver->hdmaTx.Init.Mode				= DMA_NORMAL;
				driver->hdmaTx.Init.Priority			= DMA_PRIORITY_HIGH;
				driver->hdmaTx.Init.FIFOMode			= DMA_FIFOMODE_DISABLE;

				if (HAL_DMA_Init(&driver->hdmaTx) != HAL_OK)
					DrvErrorHandler();

				/* Associate the initialized DMA handle to the UART handle */
				__HAL_LINKDMA(driver->uart, hdmatx, driver->hdmaTx);

			#endif

			HAL_NVIC_DisableIRQ(driver->UART_IRQn);

			/* Configure the UART peripheral */
			driver->uart->Init.BaudRate			= driver->SBGC_SerialSpeed;
			driver->uart->Init.WordLength		= UART_WORDLENGTH_8B;
			driver->uart->Init.StopBits			= UART_STOPBITS_1;
			driver->uart->Init.Parity			= UART_PARITY_NONE;
			driver->uart->Init.HwFlowCtl		= UART_HWCONTROL_NONE;
			driver->uart->Init.Mode				= UART_MODE_TX_RX;

			if (HAL_UART_DeInit(driver->uart) != HAL_OK)
				DrvErrorHandler();

			if (HAL_UART_Init(driver->uart) != HAL_OK)
				DrvErrorHandler();

			/* UARTx Interrupt Init */
			HAL_NVIC_SetPriority(driver->UART_IRQn, SBGC_UART_IRQ_PRIORITY, 0);
			HAL_NVIC_EnableIRQ(driver->UART_IRQn);

			#if (DRV_HAL_DMA_UART)

				HAL_NVIC_SetPriority(driver->DMA_TxIRQn, constrain_((SBGC_UART_IRQ_PRIORITY + 2), 2, 15), 0);
				HAL_NVIC_EnableIRQ(driver->DMA_TxIRQn);

				HAL_NVIC_SetPriority(driver->DMA_RxIRQn, constrain_((SBGC_UART_IRQ_PRIORITY + 2), 1, 14), 0);
				HAL_NVIC_EnableIRQ(driver->DMA_RxIRQn);

			#endif

			#if (DRV_USE_UART_DEBUG)

				/* Debug UART Init */
				GPIO_InitTypeDef DebugGPIO_InitStruct;

				/* UART Tx GPIO pin configuration */
				DebugGPIO_InitStruct.Pin		= driver->DebugUART_GPIO.txPin;
				DebugGPIO_InitStruct.Mode		= GPIO_MODE_AF_PP;
				DebugGPIO_InitStruct.Pull		= GPIO_PULLUP;
				DebugGPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_HIGH;
				DebugGPIO_InitStruct.Alternate	= driver->DebugUART_GPIO.txAF;

				HAL_GPIO_Init(driver->DebugUART_GPIO.txPort, &DebugGPIO_InitStruct);

				/* Configure the UART peripheral */
				driver->debugUart->Init.BaudRate	= driver->debugSerialSpeed;
				driver->debugUart->Init.WordLength	= UART_WORDLENGTH_8B;
				driver->debugUart->Init.StopBits	= UART_STOPBITS_1;
				driver->debugUart->Init.Parity		= UART_PARITY_NONE;
				driver->debugUart->Init.HwFlowCtl	= UART_HWCONTROL_NONE;
				driver->debugUart->Init.Mode		= UART_MODE_TX;

				if (HAL_UART_DeInit(driver->debugUart) != HAL_OK)
					while (1);

				if (HAL_UART_Init(driver->debugUart) != HAL_OK)
					while (1);

			#endif

		#elif (DRV_LL_NVIC_UART) || (DRV_LL_DMA_UART)

			#if (DRV_LL_DMA_UART)

				/* USARTx_RX DMA Init */
				LL_DMA_SetChannelSelection		(DMA_UART_RX, DMA_UART_RX_STREAM, SBGC_UART_DMA_RX_CHANNEL);
				LL_DMA_SetDataTransferDirection	(DMA_UART_RX, DMA_UART_RX_STREAM, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
				LL_DMA_SetStreamPriorityLevel	(DMA_UART_RX, DMA_UART_RX_STREAM, LL_DMA_PRIORITY_HIGH);
				LL_DMA_SetMode					(DMA_UART_RX, DMA_UART_RX_STREAM, LL_DMA_MODE_CIRCULAR);
				LL_DMA_SetPeriphIncMode			(DMA_UART_RX, DMA_UART_RX_STREAM, LL_DMA_PERIPH_NOINCREMENT);
				LL_DMA_SetMemoryIncMode			(DMA_UART_RX, DMA_UART_RX_STREAM, LL_DMA_MEMORY_INCREMENT);
				LL_DMA_SetPeriphSize			(DMA_UART_RX, DMA_UART_RX_STREAM, LL_DMA_PDATAALIGN_BYTE);
				LL_DMA_SetMemorySize			(DMA_UART_RX, DMA_UART_RX_STREAM, LL_DMA_MDATAALIGN_BYTE);
				LL_DMA_DisableFifoMode			(DMA_UART_RX, DMA_UART_RX_STREAM);

				/* USARTx_TX DMA Init */
				LL_DMA_SetChannelSelection		(DMA_UART_TX, DMA_UART_TX_STREAM, SBGC_UART_DMA_TX_CHANNEL);
				LL_DMA_SetDataTransferDirection	(DMA_UART_TX, DMA_UART_TX_STREAM, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
				LL_DMA_SetStreamPriorityLevel	(DMA_UART_TX, DMA_UART_TX_STREAM, LL_DMA_PRIORITY_HIGH);
				LL_DMA_SetMode					(DMA_UART_TX, DMA_UART_TX_STREAM, LL_DMA_MODE_NORMAL);
				LL_DMA_SetPeriphIncMode			(DMA_UART_TX, DMA_UART_TX_STREAM, LL_DMA_PERIPH_NOINCREMENT);
				LL_DMA_SetMemoryIncMode			(DMA_UART_TX, DMA_UART_TX_STREAM, LL_DMA_MEMORY_INCREMENT);
				LL_DMA_SetPeriphSize			(DMA_UART_TX, DMA_UART_TX_STREAM, LL_DMA_PDATAALIGN_BYTE);
				LL_DMA_SetMemorySize			(DMA_UART_TX, DMA_UART_TX_STREAM, LL_DMA_MDATAALIGN_BYTE);
				LL_DMA_DisableFifoMode			(DMA_UART_TX, DMA_UART_TX_STREAM);

				/* DMAx_Streamx_IRQn interrupt configuration */
				NVIC_SetPriority(driver->DMA_RxIRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
				NVIC_EnableIRQ(driver->DMA_RxIRQn);

				/* DMAx_Streamx_IRQn interrupt configuration */
				NVIC_SetPriority(driver->DMA_TxIRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
				NVIC_EnableIRQ(driver->DMA_TxIRQn);

			#endif

			/* Configure the UART peripheral */
			LL_GPIO_InitTypeDef SBGC_GPIO_InitStruct = {0};
			LL_USART_InitTypeDef SBGC_USART_InitStruct = {0};

			LL_RCC_SetUSARTClockSource(SBGC_UART_CLOCK_SRC);

			/* UART Tx GPIO pin configuration */
			SBGC_GPIO_InitStruct.Pin		= driver->SBGC_UART_GPIO.txPin;
			SBGC_GPIO_InitStruct.Mode		= LL_GPIO_MODE_ALTERNATE;
			SBGC_GPIO_InitStruct.Speed		= LL_GPIO_SPEED_FREQ_HIGH;
			SBGC_GPIO_InitStruct.OutputType	= LL_GPIO_OUTPUT_PUSHPULL;
			SBGC_GPIO_InitStruct.Pull		= LL_GPIO_PULL_NO;
			SBGC_GPIO_InitStruct.Alternate	= driver->SBGC_UART_GPIO.txAF;

			LL_GPIO_Init(driver->SBGC_UART_GPIO.txPort, &SBGC_GPIO_InitStruct);

			/* UART Rx GPIO pin configuration */
			SBGC_GPIO_InitStruct.Pin		= driver->SBGC_UART_GPIO.rxPin;
			SBGC_GPIO_InitStruct.Mode		= LL_GPIO_MODE_ALTERNATE;
			SBGC_GPIO_InitStruct.Speed		= LL_GPIO_SPEED_FREQ_HIGH;
			SBGC_GPIO_InitStruct.OutputType	= LL_GPIO_OUTPUT_PUSHPULL;
			SBGC_GPIO_InitStruct.Pull		= LL_GPIO_PULL_UP;
			SBGC_GPIO_InitStruct.Alternate	= driver->SBGC_UART_GPIO.rxAF;

			LL_GPIO_Init(driver->SBGC_UART_GPIO.rxPort, &SBGC_GPIO_InitStruct);

			/* Configure the UART peripheral */
			SBGC_USART_InitStruct.BaudRate				= driver->SBGC_SerialSpeed;
			SBGC_USART_InitStruct.DataWidth				= LL_USART_DATAWIDTH_8B;
			SBGC_USART_InitStruct.StopBits				= LL_USART_STOPBITS_1;
			SBGC_USART_InitStruct.Parity				= LL_USART_PARITY_NONE;
			SBGC_USART_InitStruct.TransferDirection		= LL_USART_DIRECTION_TX_RX;
			SBGC_USART_InitStruct.HardwareFlowControl	= LL_USART_HWCONTROL_NONE;
			SBGC_USART_InitStruct.OverSampling			= LL_USART_OVERSAMPLING_16;

			LL_USART_Init(driver->uart, &SBGC_USART_InitStruct);
			LL_USART_ConfigAsyncMode(driver->uart);
			LL_USART_Enable(driver->uart);

			/* UARTx Interrupt Init */
			NVIC_SetPriority(driver->UART_IRQn, SBGC_UART_IRQ_PRIORITY);
			NVIC_EnableIRQ(driver->UART_IRQn);

			#if (DRV_USE_UART_DEBUG)

				/* Configure the UART peripheral */
				LL_GPIO_InitTypeDef DebugGPIO_InitStruct = {0};
				LL_USART_InitTypeDef DebugUSART_InitStruct = {0};

				LL_RCC_SetUSARTClockSource(DEBUG_UART_CLOCK_SRC);

				/* UART Tx GPIO pin configuration */
				DebugGPIO_InitStruct.Pin		= driver->DebugUART_GPIO.txPin;
				DebugGPIO_InitStruct.Mode		= LL_GPIO_MODE_ALTERNATE;
				DebugGPIO_InitStruct.Speed		= LL_GPIO_SPEED_FREQ_HIGH;
				DebugGPIO_InitStruct.OutputType	= LL_GPIO_OUTPUT_PUSHPULL;
				DebugGPIO_InitStruct.Pull		= LL_GPIO_PULL_NO;
				DebugGPIO_InitStruct.Alternate	= driver->DebugUART_GPIO.txAF;

				LL_GPIO_Init(driver->DebugUART_GPIO.txPort, &DebugGPIO_InitStruct);

				/* Configure the UART peripheral */
				DebugUSART_InitStruct.BaudRate				= driver->debugSerialSpeed;
				DebugUSART_InitStruct.DataWidth				= LL_USART_DATAWIDTH_8B;
				DebugUSART_InitStruct.StopBits				= LL_USART_STOPBITS_1;
				DebugUSART_InitStruct.Parity				= LL_USART_PARITY_NONE;
				DebugUSART_InitStruct.TransferDirection		= LL_USART_DIRECTION_TX;
				DebugUSART_InitStruct.HardwareFlowControl	= LL_USART_HWCONTROL_NONE;
				DebugUSART_InitStruct.OverSampling			= LL_USART_OVERSAMPLING_16;

				LL_USART_Init(driver->debugUart, &DebugUSART_InitStruct);
				LL_USART_ConfigAsyncMode(driver->debugUart);
				LL_USART_Enable(driver->debugUart);

			#endif

		#endif
	}


	/**	@note	Private function\n
	 *			Changes to the function body are allowed
	 */
	static void UART_DrvDeinit (Driver_t *driver)
	{
		/* Timer Deinit */
		#if (DRV_HAL_TIMER)

			if (HAL_TIM_Base_DeInit(driver->tim) != HAL_OK)
				DrvErrorHandler();

			/* TIMx Interrupt Init */
			HAL_NVIC_SetPriority(driver->TIM_IRQn, 0, 0);
			HAL_NVIC_DisableIRQ(driver->TIM_IRQn);

		#elif (DRV_LL_TIMER)

			LL_TIM_DisableCounter(driver->tim);
			LL_TIM_DisableIT_UPDATE(driver->tim);
			LL_TIM_DeInit(driver->tim);

			NVIC_SetPriority(driver->TIM_IRQn, 0);
			NVIC_DisableIRQ(driver->TIM_IRQn);

		#endif


		/* UART Deinit */
		#if (DRV_HAL_NVIC_UART) || (DRV_HAL_DMA_UART)

			HAL_GPIO_DeInit(driver->SBGC_UART_GPIO.txPort, driver->SBGC_UART_GPIO.txPin);
			HAL_GPIO_DeInit(driver->SBGC_UART_GPIO.rxPort, driver->SBGC_UART_GPIO.rxPin);

			#if (DRV_HAL_DMA_UART)

				/* Deinitialize the DMA Rx handler */
				if (driver->hdmaRx.State != HAL_DMA_STATE_READY)
					if (HAL_DMA_Abort(&driver->hdmaRx) != HAL_OK)
						DrvErrorHandler();

				__HAL_DMA_DISABLE_IT(&driver->hdmaRx, DMA_IT_TC | DMA_IT_HT | DMA_IT_TE | DMA_IT_DME);

				if (HAL_DMA_DeInit(&driver->hdmaRx) != HAL_OK)
					DrvErrorHandler();

				/* Deinitialize the DMA Tx handler */
				if (driver->hdmaTx.State != HAL_DMA_STATE_READY)
					if (HAL_DMA_Abort(&driver->hdmaTx) != HAL_OK)
						DrvErrorHandler();

				__HAL_DMA_DISABLE_IT(&driver->hdmaTx, DMA_IT_TC | DMA_IT_HT | DMA_IT_TE | DMA_IT_DME);

				if (HAL_DMA_DeInit(&driver->hdmaTx) != HAL_OK)
					DrvErrorHandler();

			#endif

			/* Deinitialize the UART peripheral */
			if (HAL_UART_DeInit(driver->uart) != HAL_OK)
				DrvErrorHandler();

			HAL_NVIC_DisableIRQ(driver->UART_IRQn);

			#if (DRV_USE_UART_DEBUG)

				/* Debug UART Deinit */
				HAL_GPIO_DeInit(driver->DebugUART_GPIO.txPort, driver->DebugUART_GPIO.txPin);

				if (HAL_UART_DeInit(driver->debugUart) != HAL_OK)
					while (1);

				if (HAL_UART_Init(driver->debugUart) != HAL_OK)
					while (1);

			#endif

		#elif (DRV_LL_NVIC_UART) || (DRV_LL_DMA_UART)

			LL_GPIO_DeInit(driver->SBGC_UART_GPIO.txPort);
			LL_GPIO_DeInit(driver->SBGC_UART_GPIO.rxPort);

			LL_USART_Disable(driver->uart);

			/* UARTx Interrupt Init */
			NVIC_SetPriority(driver->UART_IRQn, 0);
			NVIC_DisableIRQ(driver->UART_IRQn);

			#if (DRV_LL_DMA_UART)

				LL_DMA_DisableStream(&driver->hdmaTx, DMA_UART_TX_STREAM);
				LL_DMA_DisableStream(&driver->hdmaRx, DMA_UART_RX_STREAM);

				LL_USART_DisableDMAReq_TX(driver->uart);
				LL_USART_DisableDMAReq_RX(driver->uart);

				LL_DMA_DeInit(&driver->hdmaTx, DMA_UART_TX_STREAM);
				LL_DMA_DeInit(&driver->hdmaRx, DMA_UART_RX_STREAM);

				NVIC_DisableIRQ(driver->DMA_RxIRQn);
				NVIC_DisableIRQ(driver->DMA_TxIRQn);

			#endif

			LL_USART_DeInit(driver->uart);

			#if (DRV_USE_UART_DEBUG)

				LL_GPIO_DeInit(driver->DebugUART_GPIO.txPort);

				LL_USART_DeInit(driver->debugUart);

			#endif
		#endif
	}

#endif


/**	@brief	Initializes the driver object from GeneralSBGC_t
 *
 *	@param	**driver - main hardware driver object
 *	@param	*uart - user defined UART object
 *	@param	*tim - user defined timer object
 */
void DriverInit (void **driver, __UART_TYPE_DEF *uart, __TIMER_TYPE_DEF *tim)
{
	#if (DRV_USE_FREERTOS)
		*driver = pvPortMalloc(sizeof(Driver_t));
	#else
		*driver = malloc(sizeof(Driver_t));
	#endif

	Driver_t *drv = (Driver_t*)(*driver);

	#if (DRV_HAL_TIMER || DRV_LL_TIMER)
		/* Timer */
		drv->tim = tim;
		drv->timCount = 0;

	#else
		unused_(tim);
	#endif

	#if (DRV_USE_FREERTOS)
		/* FreeRTOS */
		vSemaphoreCreateBinary(drv->xSemaphoreTxBusy);
		xSemaphoreGive(drv->xSemaphoreTxBusy);

	#endif

    /* UART */
	drv->uart = uart;

	#if (DRV_USE_UART_DEBUG && (DRV_USE_CUBEMX == SET_OFF))
		drv->debugUart = DEBUG_SERIAL_PORT;
	#endif

	#if (DRV_USE_CUBEMX == SET_OFF)

		DrvSetPeripheryClock();

		UART_DrvPinDetermination(drv);
		UART_DrvPeriphDetermination(drv);

		UART_DrvInit(drv);

	#endif

	ClearTxBuff(drv);
	ClearRxBuff(drv);

	#if (DRV_HAL_NVIC_UART || DRV_LL_NVIC_UART)
		/* UART Interrupts executable code */
		DISABLE_UART_CR1_TCIE(drv->uart);
		ENABLE_UART_CR1_RXNEIE(drv->uart);
		DISABLE_UART_CR1_IDLEIE(drv->uart);

	#elif (DRV_HAL_DMA_UART)
		/* UART HAL DMA executable code */
		HAL_UART_Receive_DMA(drv->uart, drv->RxBuffer, RX_FIFO_TOTAL_SIZE);

	#elif (DRV_LL_DMA_UART)
		/* UART LL DMA executable code */
		/* Tx Init */
		LL_USART_EnableDMAReq_TX(SBGC_SERIAL_PORT);
		LL_DMA_EnableIT_TC(DMA_UART_TX, DMA_UART_TX_STREAM);

		LL_DMA_ConfigAddresses(DMA_UART_TX, DMA_UART_TX_STREAM,
							   (ui32)drv->TxBuffer,
							   LL_USART_DMA_GetRegAddr(SBGC_SERIAL_PORT, LL_USART_DMA_REG_DATA_TRANSMIT),
							   LL_DMA_GetDataTransferDirection(DMA_UART_TX, DMA_UART_TX_STREAM));

		/* Rx Init */
		LL_USART_EnableDMAReq_RX(SBGC_SERIAL_PORT);
		LL_DMA_EnableIT_TC(DMA_UART_RX, DMA_UART_RX_STREAM);

		LL_DMA_ConfigAddresses(DMA_UART_RX, DMA_UART_RX_STREAM,
							   LL_USART_DMA_GetRegAddr(SBGC_SERIAL_PORT, LL_USART_DMA_REG_DATA_RECEIVE),
							   (ui32)drv->RxBuffer,
							   LL_DMA_GetDataTransferDirection(DMA_UART_RX, DMA_UART_RX_STREAM));

		LL_DMA_DisableStream(DMA_UART_RX, DMA_UART_RX_STREAM);
		LL_DMA_SetDataLength(DMA_UART_RX, DMA_UART_RX_STREAM, RX_FIFO_TOTAL_SIZE);
		LL_DMA_EnableStream(DMA_UART_RX, DMA_UART_RX_STREAM);

	#endif

	#if (DRV_HAL_TIMER || DRV_LL_TIMER)
		START_TIMER(drv->tim);
	#endif
}


/**	@brief	Initializes the driver object from GeneralSBGC_t
 *
 *	@param	**driver - main hardware driver object
 */
void DriverDeinit (void **driver)
{
	Driver_t *drv = (Driver_t*)(*driver);

	#if (DRV_USE_FREERTOS)

		/* FreeRTOS */
		vSemaphoreDelete(drv->xSemaphoreTxBusy);

	#endif

	#if (DRV_USE_CUBEMX == SET_OFF)

		UART_DrvDeinit(drv);
		DrvResetPeripheryClock();

	#endif

	ClearTxBuff(drv);
	ClearRxBuff(drv);

	#if (DRV_HAL_NVIC_UART || DRV_LL_NVIC_UART)

		/* UART Interrupts executable code */
		DISABLE_UART_CR1_TCIE(drv->uart);
		DISABLE_UART_CR1_RXNEIE(drv->uart);
		DISABLE_UART_CR1_IDLEIE(drv->uart);

	#endif

	#if (DRV_HAL_TIMER || DRV_LL_TIMER)
		STOP_TIMER(drv->tim);
	#endif

	memset(*driver, 0, sizeof(Driver_t));

	#if (DRV_USE_FREERTOS)
		vPortFree(*driver);
	#else
		free(*driver);
	#endif
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														 Timer Functions
 */
/**	@brief	Gets current system time in milliseconds
 *
 *	@param	*driver - main hardware driver object
 *
 *	@return	Current time
 */
ui32 GetTimeMs (void *driver)
{
	Driver_t *drv = (Driver_t*)driver;

	#if (DRV_USE_FREERTOS)
		drv->timCount = xTaskGetTickCount();
	#endif

	return drv->timCount;
}


/**	@brief	Timer interrupts handler
 *
 *	@param	*driver - main hardware driver object
 */
void TimerDRV_CallBack (void *driver)
{
	Driver_t *drv = (Driver_t*)driver;

	drv->timCount++;

	#if (DRV_LL_TIMER)
		LL_TIM_ClearFlag_UPDATE(drv->tim);
	#endif
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *															Tx Functions
 */
/**	@brief	Sends an amount of data to the Tx ring buffer
 *
 *	@param	*driver - main hardware driver object
 *	@param	*data - transferred data
 *	@param	size - size of transferred data
 *
 *	@return	Tx overflow status (1 - ERROR | 0 - OK)
 */
ui8 UartTransmitData (void *driver, ui8 *data, ui16 size)
{
	Driver_t *drv = (Driver_t*)driver;

	#if (DRV_HAL_NVIC_UART || DRV_LL_NVIC_UART)
	/* UART Interrupts executable code */

		/* Free space check */
		if (TX_FIFO_TOTAL_SIZE - ((drv->TxHead - drv->TxTail) & (TX_FIFO_TOTAL_SIZE - 1)) < size)
		{
			/* - - - - User TxBuffer Overflow Handler - - - - */

			/*  - - - - - - - - - - - - - - - - - - - - - - - */
			return 1;
		}

		ui16 count = 0;
		while (count < size)
		{
			drv->TxBuffer[drv->TxHead++] = data[count++];

			if (drv->TxHead >= TX_FIFO_TOTAL_SIZE)
				drv->TxHead = 0;
		}

		ENABLE_UART_CR1_TCIE(drv->uart);  // Enable transfer completion interrupts

		return 0;

	#elif (DRV_HAL_DMA_UART)
	/* UART DMA executable code */

		#if (DRV_USE_FREERTOS)

			if (xSemaphoreTake(drv->xSemaphoreTxBusy, 0) != pdTRUE)
				xSemaphoreTake(drv->xSemaphoreTxBusy, portMAX_DELAY);

		#endif

		memcpy(drv->TxBuffer, data, size);

		HAL_UART_Transmit_DMA(drv->uart, drv->TxBuffer, size);

		return 0;

	#elif (DRV_LL_DMA_UART)

		memcpy(drv->TxBuffer, data, size);

		LL_DMA_DisableStream(DMA_UART_TX, DMA_UART_TX_STREAM);
		LL_DMA_SetDataLength(DMA_UART_TX, DMA_UART_TX_STREAM, size);
		LL_DMA_EnableStream(DMA_UART_TX, DMA_UART_TX_STREAM);

		return 0;

	#endif
}


#if (DRV_HAL_NVIC_UART || DRV_LL_NVIC_UART || DRV_USE_FREERTOS)
/* UART Interrupts executable code */

	/**	@brief	UART transfer completion interrupts handler
	 *
	 *	@param	*driver - main hardware driver object
	 */
	void UART_DRV_TxCallBack (void *driver)
	{
		Driver_t *drv = (Driver_t*)driver;

		#if (DRV_USE_FREERTOS)

			static BaseType_t xHigherPriorityTaskWoken;
			xHigherPriorityTaskWoken = pdTRUE;
			xSemaphoreGiveFromISR(drv->xSemaphoreTxBusy, &xHigherPriorityTaskWoken);
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

		#endif

		#if (DRV_HAL_NVIC_UART || DRV_LL_NVIC_UART)

			WRITE_UART_BYTE(drv->uart, drv->TxBuffer[drv->TxTail++] & (ui32)0xFF);

			if (drv->TxTail == TX_FIFO_TOTAL_SIZE)
				drv->TxTail = 0;

			if (drv->TxTail == drv->TxHead)
			{
				DISABLE_UART_CR1_TCIE(drv->uart);  // Disable transmission complete interrupts

				/* - - - - User Transmit-Complete Handler - - - - */

				/*  - - - - - - - - - - - - - - - - - - - - - - - */
			}

		#endif
	}

#endif


/**	@brief	Service Tx buffer cleaner
 *
 *	@param	*driver - main hardware driver object
 */
void ClearTxBuff (void *driver)
{
	#if (DRV_HAL_NVIC_UART || DRV_LL_NVIC_UART || DRV_LL_DMA_UART)

		Driver_t *drv = (Driver_t*)driver;

		memset(drv->TxBuffer, 0, TX_FIFO_TOTAL_SIZE);
		drv->TxTail = 0;
		drv->TxHead = 0;

	#else
		unused_(driver);
	#endif
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *															Rx Functions
 */
/**	@brief	Returns the number of available bytes
 *
 *	@param	*driver - main hardware driver object
 *
 *	@return	Number of available bytes (0xFFFF - overflow error)
 */
ui16 GetAvailableBytes (void *driver)
{
	Driver_t *drv = (Driver_t*)driver;

	#if (DRV_HAL_NVIC_UART || DRV_LL_NVIC_UART)
	/* UART Interrupts executable code */

		if (drv->RxOverflowFlag)
			return 0xFFFF;

		ui16 rxHead = drv->RxHead;
		ui16 rxTail = drv->RxTail;

		ui16 count = 0;
		while (rxHead != rxTail)
		{
			if (!rxHead)
				rxHead = RX_FIFO_TOTAL_SIZE;

			rxHead--;
			count++;
		}

		return count;

	#elif (DRV_HAL_DMA_UART) || (DRV_LL_DMA_UART)

		/* UART DMA executable code */
		drv->RxHead = RX_FIFO_TOTAL_SIZE - GET_DMA_RX_COUNTER(DMA_UART_RX);
		return (drv->RxHead - drv->RxTail) & (RX_FIFO_TOTAL_SIZE - 1);

	#endif
}


/**	@brief	Receives byte from the Rx ring buffer
 *
 *	@param	*driver - main hardware driver object
 *	@param	*data - data buffer
 *
 *	@return	Receipt status (0 - receiving in progress | 1 - receive completed)
 */
ui8 UartReceiveByte (void *driver, ui8 *data)
{
	Driver_t *drv = (Driver_t*)driver;

	#if (DRV_HAL_NVIC_UART || DRV_LL_NVIC_UART)
	/* UART Interrupts executable code */

		if (drv->RxTail == drv->RxHead)
		{
			/*  - - - - User Receive-Complete Handler - - - - */

			/*  - - - - - - - - - - - - - - - - - - - - - - - */
			return 1;
		}

		*data = drv->RxBuffer[drv->RxTail++];

		if (drv->RxTail >= RX_FIFO_TOTAL_SIZE)
		   drv->RxTail = 0;

		if (drv->RxOverflowFlag == 1)  // Reset the overflow flag
			drv->RxOverflowFlag = 0;

		return 0;  // Rx ring buffer isn't empty

	#elif (DRV_HAL_DMA_UART) || (DRV_LL_DMA_UART)
	/* UART DMA executable code */

		if (GetAvailableBytes(drv) == 0)
			return 1;

		*data = drv->RxBuffer[drv->RxTail];

		if (drv->RxTail != drv->RxHead)
		{
			drv->RxTail++;
			drv->RxTail &= (RX_FIFO_TOTAL_SIZE - 1);
		}

		return 0;

	#endif
}


#if (DRV_HAL_NVIC_UART || DRV_LL_NVIC_UART)
/* UART Interrupts executable code */

	/**	@brief	UART receive completion interrupts handler
	 *
	 *	@param	*driver - main hardware driver object
	 */
	void UART_DRV_RxCallBack (void *driver)
	{
		Driver_t *drv = (Driver_t*)driver;

		if ((drv->RxHead - drv->RxTail == RX_FIFO_TOTAL_SIZE - 1) ||
			(drv->RxTail - drv->RxHead == 1))
		{
			/* - - - - User RxBuffer Overflow Handler - - - - */

			/*  - - - - - - - - - - - - - - - - - - - - - - - */

			(void)READ_UART_BYTE(drv->uart);  // Prevent hardware overflow error (USART_ISR_ORE)

			if (drv->RxOverflowFlag == 0)  // Set the overflow flag
				drv->RxOverflowFlag = 1;

			return;
		}

		drv->RxBuffer[drv->RxHead++] = READ_UART_BYTE(drv->uart);

		if (drv->RxHead >= RX_FIFO_TOTAL_SIZE)
			drv->RxHead = 0;
	}

#endif


/**	@brief	Service Rx buffer cleaner
 *
 *	@param	*driver - main hardware driver object
 */
void ClearRxBuff (void *driver)
{
	Driver_t *drv = (Driver_t*)driver;

	memset(drv->RxBuffer, 0, RX_FIFO_TOTAL_SIZE);
	drv->RxTail = 0;
	drv->RxHead = 0;
	drv->RxOverflowFlag = 0;
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														 Debug Functions
 */

/**	@brief	Sends debug data
 *
 *	@param	*data - debug data
 *	@param	length - size of debug data
 */
void UartTransmitDebugData (char *data, ui16 length)
{
	#if (DRV_USE_UART_DEBUG)
		#if (DRV_HAL_NVIC_UART || DRV_HAL_DMA_UART)

			/* UART HAL executable code */
			HAL_UART_Transmit(DEBUG_SERIAL_PORT, (ui8*)data, length, 100);

		#elif (DRV_LL_NVIC_UART) || (DRV_LL_DMA_UART)

			/* UART LL executable code */
			ui16 count = 0;

			while (count < length)
			{
				while (!LL_USART_IsActiveFlag_TXE(DEBUG_SERIAL_PORT));

				LL_USART_TransmitData8(DEBUG_SERIAL_PORT, data[count++]);
			}

		#endif
	#endif
}
/**	@}
 */

#endif /* SBGC_USE_STM32_DRIVER */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
