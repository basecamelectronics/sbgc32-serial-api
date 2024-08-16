/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.0
 *
 *	@file		driverSTM32.c
 *
 *	@brief		STM32 driver source file
 *	____________________________________________________________________
 *
 *	@attention	<h3><center>
 *				Copyright © 2024 BaseCam Electronics™.<br>
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

/**	@addtogroup	STM32_Driver
 *	@{
 */
/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						 Static Macros and Constants
 */
/* Timer */
#if (SBGC_DRV_HAL_TIMER)
	#define	START_TIMER(TIM)		HAL_TIM_Base_Start_IT(TIM)
	#define	STOP_TIMER(TIM)			HAL_TIM_Base_Stop_IT(TIM)

#elif (SBGC_DRV_LL_TIMER)
	#define	START_TIMER(TIM)		LL_TIM_EnableIT_UPDATE(TIM);\
									LL_TIM_EnableCounter(TIM)
	#define	STOP_TIMER(TIM)			LL_TIM_DisableIT_UPDATE(TIM);\
									LL_TIM_DisableCounter(TIM)
#endif

/* UART */
#if (SBGC_DRV_HAL_NVIC_UART)
	#if defined (STM32F0) || defined (STM32F3) || defined (STM32F7) ||\
		defined (STM32L0) || defined (STM32L4) || defined (STM32L5) ||\
		defined (STM32G0) || defined (STM32G4) || defined (STM32H7)
		#define	TDR__				TDR
		#define	RDR__				RDR
		#define	USART_RDR_RDR__		USART_RDR_RDR

		#define	CLEAR_UART_ORE(UART)		__HAL_UART_CLEAR_FLAG(UART, UART_CLEAR_OREF)
	#else
		#define	TDR__				DR
		#define	RDR__				DR
		#define	USART_RDR_RDR__		USART_DR_DR

		#define	CLEAR_UART_ORE(UART)
	#endif

	#define	WRITE_UART_BYTE(UART, BYTE)		((UART)->Instance->TDR__ = BYTE)
	#define READ_UART_BYTE(UART)			(ui8)(READ_BIT((UART)->Instance->RDR__, USART_RDR_RDR__) & 0xFFU)

	#define	ENABLE_UART_CR1_TCIE(UART)		__HAL_UART_ENABLE_IT(UART, UART_IT_TC)
	#define	DISABLE_UART_CR1_TCIE(UART)		__HAL_UART_DISABLE_IT(UART, UART_IT_TC)
	#define	ENABLE_UART_CR1_RXNEIE(UART)	__HAL_UART_ENABLE_IT(UART, UART_IT_RXNE)
	#define	DISABLE_UART_CR1_RXNEIE(UART)	__HAL_UART_DISABLE_IT(UART, UART_IT_RXNE)
	#define	ENABLE_UART_CR1_IDLEIE(UART)	__HAL_UART_ENABLE_IT(UART, UART_IT_IDLE)
	#define	DISABLE_UART_CR1_IDLEIE(UART)	__HAL_UART_DISABLE_IT(UART, UART_IT_IDLE)

	#define	GET_FLAG_UART_ISR_TC(UART)		__HAL_UART_GET_FLAG(UART, UART_FLAG_TC)
	#define	GET_FLAG_UART_CR1_TCIE(UART)	__HAL_UART_GET_IT_SOURCE(UART, UART_IT_TC)
	#define	GET_FLAG_UART_ISR_RXNE(UART)	__HAL_UART_GET_FLAG(UART, UART_FLAG_RXNE)
	#define	GET_FLAG_UART_CR1_RXNEIE(UART)	__HAL_UART_GET_IT_SOURCE(UART, UART_IT_RXNE)

#elif (SBGC_DRV_HAL_DMA_UART)
	#define	GET_DMA_RX_COUNTER(DMAX)		__HAL_DMA_GET_COUNTER(DMAX)

#elif (SBGC_DRV_LL_NVIC_UART)
	#define	WRITE_UART_BYTE(UART, BYTE)		LL_USART_TransmitData8(UART, BYTE)
	#define READ_UART_BYTE(UART)			LL_USART_ReceiveData8(UART)
	#define	CLEAR_UART_ORE(UART)			LL_USART_ClearFlag_ORE(UART)

	#define	ENABLE_UART_CR1_TCIE(UART)		LL_USART_EnableIT_TC(UART)
	#define	DISABLE_UART_CR1_TCIE(UART)		LL_USART_DisableIT_TC(UART)
	#define	ENABLE_UART_CR1_RXNEIE(UART)	LL_USART_EnableIT_RXNE(UART)
	#define	DISABLE_UART_CR1_RXNEIE(UART)	LL_USART_DisableIT_RXNE(UART)
	#define	ENABLE_UART_CR1_IDLEIE(UART)	LL_USART_EnableIT_IDLE(UART)
	#define	DISABLE_UART_CR1_IDLEIE(UART)	LL_USART_DisableIT_IDLE(UART)

	#define	GET_FLAG_UART_ISR_TC(UART)		LL_USART_IsActiveFlag_TC(UART)
	#define	GET_FLAG_UART_CR1_TCIE(UART)	LL_USART_IsEnabledIT_TC(UART)
	#define	GET_FLAG_UART_ISR_RXNE(UART)	LL_USART_IsActiveFlag_RXNE(UART)
	#define	GET_FLAG_UART_CR1_RXNEIE(UART)	LL_USART_IsEnabledIT_RXNE(UART)
	#define	GET_FLAG_UART_ISR_ORE(UART)		LL_USART_IsActiveFlag_ORE(UART)

#elif (SBGC_DRV_LL_DMA_UART)
	#define	GET_DMA_RX_COUNTER(DMAX)		LL_DMA_GetDataLength(DMAX, SBGC_DMA_UART_RX_STREAM)
	#define	GET_FLAG_UART_ISR_TC(UART)		LL_USART_IsActiveFlag_TC(UART)
#endif

#if (SBGC_STM32_CUSTOM_DRV)

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *													 Private Objects
	 */
	/* Creating global driver variables */
	#if (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_HAL_DMA_UART)
		SBGC_UART_DCLR;

		#if (SBGC_DRV_USE_UART_DEBUG)
			SBGC_DEBUG_UART_DCLR;
		#endif

		#if (SBGC_DRV_HAL_DMA_UART)
			SBGC_UART_DMA_DCLR;
		#endif
	#endif

	#if (SBGC_DRV_HAL_TIMER)
		SBGC_TIMER_DCLR;
	#endif

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *												   Private Functions
	 */
	/**	@note	Private function
	 */
	static void DriverSBGC32_SetPeripheryClock (void)
	{
		#if (SBGC_DRV_HAL_TIMER || SBGC_DRV_LL_TIMER)
			SBGC_TIMER_CLOCK_ENABLE;
		#endif

		SBGC_UART_GPIO_CLOCK_ENABLE;
		SBGC_UART_CLOCK_ENABLE;

		#if (SBGC_DRV_HAL_DMA_UART || SBGC_DRV_LL_DMA_UART)
			SBGC_UART_DMA_CLOCK_ENABLE;
		#endif

		#if (SBGC_DRV_USE_UART_DEBUG)
			SBGC_DEBUG_UART_GPIO_CLOCK_ENABLE;
			SBGC_DEBUG_UART_CLOCK_ENABLE;
		#endif
	}


	/**	@note	Private function
	 */
	static void DriverSBGC32_ResetPeripheryClock (void)
	{
		#if (SBGC_DRV_HAL_TIMER || SBGC_DRV_LL_TIMER)
			SBGC_TIMER_CLOCK_DISABLE;
		#endif

		SBGC_UART_GPIO_CLOCK_DISABLE;
		SBGC_UART_CLOCK_DISABLE;

		#if (SBGC_DRV_HAL_DMA_UART || SBGC_DRV_LL_DMA_UART)
			SBGC_UART_DMA_CLOCK_DISABLE;
		#endif

		#if (SBGC_DRV_USE_UART_DEBUG)
			SBGC_DEBUG_UART_GPIO_CLOCK_DISABLE;
			SBGC_DEBUG_UART_CLOCK_DISABLE;
		#endif
	}


	/**	@note	Private function
	 */
	static void DriverSBGC32_UART_PinDeterminate (sbgcDriver_t *driver)
	{
		driver->SBGC_UART_GPIO.txPin	= SBGC_UART_TX_PIN;
		driver->SBGC_UART_GPIO.txPort	= SBGC_UART_TX_GPIO_PORT;
		driver->SBGC_UART_GPIO.txPinAF	= SBGC_UART_TX_PIN_AF;

		driver->SBGC_UART_GPIO.rxPin	= SBGC_UART_RX_PIN;
		driver->SBGC_UART_GPIO.rxPort	= SBGC_UART_RX_GPIO_PORT;
		driver->SBGC_UART_GPIO.rxPinAF	= SBGC_UART_RX_PIN_AF;

		#if (SBGC_DRV_USE_UART_DEBUG)

			driver->DebugUART_GPIO.txPin	= SBGC_DEBUG_UART_TX_PIN;
			driver->DebugUART_GPIO.txPort	= SBGC_DEBUG_UART_TX_GPIO_PORT;
			driver->DebugUART_GPIO.txPinAF	= SBGC_DEBUG_UART_TX_PIN_AF;

			driver->DebugUART_GPIO.rxPin	= SBGC_DEBUG_UART_RX_PIN;
			driver->DebugUART_GPIO.rxPort	= SBGC_DEBUG_UART_RX_GPIO_PORT;
			driver->DebugUART_GPIO.rxPinAF	= SBGC_DEBUG_UART_RX_PIN_AF;

		#endif
	}


	/**	@note	Private function
	 */
	static void DriverSBGC32_UART_PeriphDeterminate (sbgcDriver_t *driver)
	{
		#if (SBGC_DRV_HAL_TIMER)

			driver->tim->Instance	= SBGC_TIMER_INSTANCE;
			driver->TIM_IRQn		= SBGC_TIMER_IRQN;

		#endif

		#if (SBGC_DRV_LL_TIMER)

			driver->tim			= SBGC_TIMER_INSTANCE;
			driver->TIM_IRQn	= SBGC_TIMER_IRQN;

		#endif

		#if (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_HAL_DMA_UART)
			driver->uart->Instance = SBGC_UART_INSTANCE;
		#else /* SBGC_DRV_LL_NVIC_UART || SBGC_DRV_LL_DMA_UART */
			driver->uart = SBGC_UART_INSTANCE;
		#endif

		driver->SBGC_SerialSpeed = SBGC_UART_SERIAL_SPEED;

		driver->UART_IRQn = SBGC_UART_IRQN;

		#if (SBGC_DRV_HAL_DMA_UART || SBGC_DRV_LL_DMA_UART)

			driver->DMA_TxIRQn	= SBGC_UART_DMA_TX_CH_IRQN;
			driver->DMA_RxIRQn	= SBGC_UART_DMA_RX_CH_IRQN;

			#if (SBGC_DRV_HAL_DMA_UART)

				driver->hdmaTx	= SBGC_UART_DMA_NAME;
				driver->hdmaRx	= SBGC_UART_DMA_NAME;

			#endif

		#endif

		#if (SBGC_DRV_USE_UART_DEBUG)

			#if (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_HAL_DMA_UART)
				driver->debugUart->Instance	= SBGC_DEBUG_UART_INSTANCE;
			#else /* SBGC_DRV_LL_NVIC_UART || SBGC_DRV_LL_DMA_UART */
				driver->debugUart = SBGC_DEBUG_UART_INSTANCE;
			#endif

			driver->debugSerialSpeed = SBGC_DEBUG_UART_SERIAL_SPEED;

		#endif
	}


	/**	@note	Private function
	 */
	static void DriverSBGC32_UART_Init (sbgcDriver_t *driver)
	{
		/* Timer Init */
		#if (SBGC_DRV_HAL_TIMER)

			TIM_ClockConfigTypeDef sClockSourceConfig = {0};
			TIM_MasterConfigTypeDef sMasterConfig = {0};

			driver->tim->Init.Prescaler			= (SBGC_TIMER_BUS_FREQ / 1000000) - 1;
			driver->tim->Init.CounterMode		= TIM_COUNTERMODE_UP;
			driver->tim->Init.Period			= 999;
			driver->tim->Init.ClockDivision		= TIM_CLOCKDIVISION_DIV1;
			driver->tim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

			if (HAL_TIM_Base_Init(driver->tim) != HAL_OK)
				SerialAPI_FatalErrorHandler();

			sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;

			if (HAL_TIM_ConfigClockSource(driver->tim, &sClockSourceConfig) != HAL_OK)
				SerialAPI_FatalErrorHandler();

			sMasterConfig.MasterOutputTrigger	= TIM_TRGO_UPDATE;
			sMasterConfig.MasterSlaveMode		= TIM_MASTERSLAVEMODE_DISABLE;

			if (HAL_TIMEx_MasterConfigSynchronization(driver->tim, &sMasterConfig) != HAL_OK)
				SerialAPI_FatalErrorHandler();

			/* TIMx Interrupt Init */
			HAL_NVIC_SetPriority(driver->TIM_IRQn, SBGC_TIMER_IRQ_PRIORITY, 0);
			HAL_NVIC_EnableIRQ(driver->TIM_IRQn);

		#elif (SBGC_DRV_LL_TIMER)

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
		#if (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_HAL_DMA_UART)

			/* Configure the UART peripheral */
			GPIO_InitTypeDef SBGC_GPIO_InitStruct;

			/* UART Tx GPIO pin configuration */
			SBGC_GPIO_InitStruct.Pin		= driver->SBGC_UART_GPIO.txPin;
			SBGC_GPIO_InitStruct.Mode		= GPIO_MODE_AF_PP;
			SBGC_GPIO_InitStruct.Pull		= GPIO_PULLUP;
			SBGC_GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_HIGH;
			SBGC_GPIO_InitStruct.Alternate	= driver->SBGC_UART_GPIO.txPinAF;

			HAL_GPIO_Init(driver->SBGC_UART_GPIO.txPort, &SBGC_GPIO_InitStruct);

			/* UART Rx GPIO pin configuration */
			SBGC_GPIO_InitStruct.Pin		= driver->SBGC_UART_GPIO.rxPin;
			SBGC_GPIO_InitStruct.Alternate	= driver->SBGC_UART_GPIO.rxPinAF;

			HAL_GPIO_Init(driver->SBGC_UART_GPIO.rxPort, &SBGC_GPIO_InitStruct);

			#if (SBGC_DRV_HAL_DMA_UART)

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
					SerialAPI_FatalErrorHandler();

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
					SerialAPI_FatalErrorHandler();

				/* Associate the initialized DMA handle to the UART handle */
				__HAL_LINKDMA(driver->uart, hdmatx, driver->hdmaTx);

				/* DMAx Interrupts Init */
				HAL_NVIC_SetPriority(driver->DMA_RxIRQn, constrain_((SBGC_UART_IRQ_PRIORITY + 2), 2, 15), 0);
				HAL_NVIC_EnableIRQ(driver->DMA_RxIRQn);

				HAL_NVIC_SetPriority(driver->DMA_TxIRQn, constrain_((SBGC_UART_IRQ_PRIORITY + 2), 2, 15), 0);
				HAL_NVIC_EnableIRQ(driver->DMA_TxIRQn);

			#endif

			HAL_NVIC_DisableIRQ(driver->UART_IRQn);

			/* Configure the UART peripheral */
			driver->uart->Init.BaudRate			= driver->SBGC_SerialSpeed;
			driver->uart->Init.WordLength		= UART_WORDLENGTH_8B;
			driver->uart->Init.StopBits			= UART_STOPBITS_1;
			driver->uart->Init.Parity			= UART_PARITY_NONE;
			driver->uart->Init.HwFlowCtl		= UART_HWCONTROL_NONE;
			driver->uart->Init.Mode				= UART_MODE_TX_RX;
			driver->uart->Init.OverSampling		= UART_OVERSAMPLING_16;

			if (HAL_UART_Init(driver->uart) != HAL_OK)
				SerialAPI_FatalErrorHandler();

			/* UARTx Interrupt Init */
			HAL_NVIC_SetPriority(driver->UART_IRQn, SBGC_UART_IRQ_PRIORITY, 0);
			HAL_NVIC_EnableIRQ(driver->UART_IRQn);

			#if (SBGC_DRV_USE_UART_DEBUG)

				/* Debug UART Init */
				GPIO_InitTypeDef DebugGPIO_InitStruct;

				/* UART Tx GPIO pin configuration */
				DebugGPIO_InitStruct.Pin		= driver->DebugUART_GPIO.txPin;
				DebugGPIO_InitStruct.Mode		= GPIO_MODE_AF_PP;
				DebugGPIO_InitStruct.Pull		= GPIO_PULLUP;
				DebugGPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_HIGH;
				DebugGPIO_InitStruct.Alternate	= driver->DebugUART_GPIO.txPinAF;

				HAL_GPIO_Init(driver->DebugUART_GPIO.txPort, &DebugGPIO_InitStruct);

				/* Configure the UART peripheral */
				driver->debugUart->Init.BaudRate	= driver->debugSerialSpeed;
				driver->debugUart->Init.WordLength	= UART_WORDLENGTH_8B;
				driver->debugUart->Init.StopBits	= UART_STOPBITS_1;
				driver->debugUart->Init.Parity		= UART_PARITY_NONE;
				driver->debugUart->Init.HwFlowCtl	= UART_HWCONTROL_NONE;
				driver->debugUart->Init.Mode		= UART_MODE_TX;

				if (HAL_UART_Init(driver->debugUart) != HAL_OK)
					SerialAPI_FatalErrorHandler();

			#endif

		#elif (SBGC_DRV_LL_NVIC_UART || SBGC_DRV_LL_DMA_UART)

			#if (SBGC_DRV_LL_DMA_UART)

				/* USARTx_RX DMA Init */
				LL_DMA_SetChannelSelection		(SBGC_DMA_UART_RX, SBGC_DMA_UART_RX_STREAM, SBGC_UART_DMA_RX_CHANNEL);
				LL_DMA_SetDataTransferDirection	(SBGC_DMA_UART_RX, SBGC_DMA_UART_RX_STREAM, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
				LL_DMA_SetStreamPriorityLevel	(SBGC_DMA_UART_RX, SBGC_DMA_UART_RX_STREAM, LL_DMA_PRIORITY_HIGH);
				LL_DMA_SetMode					(SBGC_DMA_UART_RX, SBGC_DMA_UART_RX_STREAM, LL_DMA_MODE_CIRCULAR);
				LL_DMA_SetPeriphIncMode			(SBGC_DMA_UART_RX, SBGC_DMA_UART_RX_STREAM, LL_DMA_PERIPH_NOINCREMENT);
				LL_DMA_SetMemoryIncMode			(SBGC_DMA_UART_RX, SBGC_DMA_UART_RX_STREAM, LL_DMA_MEMORY_INCREMENT);
				LL_DMA_SetPeriphSize			(SBGC_DMA_UART_RX, SBGC_DMA_UART_RX_STREAM, LL_DMA_PDATAALIGN_BYTE);
				LL_DMA_SetMemorySize			(SBGC_DMA_UART_RX, SBGC_DMA_UART_RX_STREAM, LL_DMA_MDATAALIGN_BYTE);
				LL_DMA_DisableFifoMode			(SBGC_DMA_UART_RX, SBGC_DMA_UART_RX_STREAM);

				/* USARTx_TX DMA Init */
				LL_DMA_SetChannelSelection		(SBGC_DMA_UART_TX, SBGC_DMA_UART_TX_STREAM, SBGC_UART_DMA_TX_CHANNEL);
				LL_DMA_SetDataTransferDirection	(SBGC_DMA_UART_TX, SBGC_DMA_UART_TX_STREAM, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
				LL_DMA_SetStreamPriorityLevel	(SBGC_DMA_UART_TX, SBGC_DMA_UART_TX_STREAM, LL_DMA_PRIORITY_HIGH);
				LL_DMA_SetMode					(SBGC_DMA_UART_TX, SBGC_DMA_UART_TX_STREAM, LL_DMA_MODE_NORMAL);
				LL_DMA_SetPeriphIncMode			(SBGC_DMA_UART_TX, SBGC_DMA_UART_TX_STREAM, LL_DMA_PERIPH_NOINCREMENT);
				LL_DMA_SetMemoryIncMode			(SBGC_DMA_UART_TX, SBGC_DMA_UART_TX_STREAM, LL_DMA_MEMORY_INCREMENT);
				LL_DMA_SetPeriphSize			(SBGC_DMA_UART_TX, SBGC_DMA_UART_TX_STREAM, LL_DMA_PDATAALIGN_BYTE);
				LL_DMA_SetMemorySize			(SBGC_DMA_UART_TX, SBGC_DMA_UART_TX_STREAM, LL_DMA_MDATAALIGN_BYTE);
				LL_DMA_DisableFifoMode			(SBGC_DMA_UART_TX, SBGC_DMA_UART_TX_STREAM);

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
			SBGC_GPIO_InitStruct.Alternate	= driver->SBGC_UART_GPIO.txPinAF;

			LL_GPIO_Init(driver->SBGC_UART_GPIO.txPort, &SBGC_GPIO_InitStruct);

			/* UART Rx GPIO pin configuration */
			SBGC_GPIO_InitStruct.Pin		= driver->SBGC_UART_GPIO.rxPin;
			SBGC_GPIO_InitStruct.Mode		= LL_GPIO_MODE_ALTERNATE;
			SBGC_GPIO_InitStruct.Speed		= LL_GPIO_SPEED_FREQ_HIGH;
			SBGC_GPIO_InitStruct.OutputType	= LL_GPIO_OUTPUT_PUSHPULL;
			SBGC_GPIO_InitStruct.Pull		= LL_GPIO_PULL_UP;
			SBGC_GPIO_InitStruct.Alternate	= driver->SBGC_UART_GPIO.rxPinAF;

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

			#if (SBGC_DRV_USE_UART_DEBUG)

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
				DebugGPIO_InitStruct.Alternate	= driver->DebugUART_GPIO.txPinAF;

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


	/**	@note	Private function
	 */
	static void DriverSBGC32_UART_Deinit (sbgcDriver_t *driver)
	{
		/* Timer Deinit */
		#if (SBGC_DRV_HAL_TIMER)

			if (HAL_TIM_Base_DeInit(driver->tim) != HAL_OK)
				SerialAPI_FatalErrorHandler();

			/* TIMx Interrupt Init */
			HAL_NVIC_SetPriority(driver->TIM_IRQn, 0, 0);
			HAL_NVIC_DisableIRQ(driver->TIM_IRQn);

		#elif (SBGC_DRV_LL_TIMER)

			LL_TIM_DisableCounter(driver->tim);
			LL_TIM_DisableIT_UPDATE(driver->tim);
			LL_TIM_DeInit(driver->tim);

			NVIC_SetPriority(driver->TIM_IRQn, 0);
			NVIC_DisableIRQ(driver->TIM_IRQn);

		#endif


		/* UART Deinit */
		#if (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_HAL_DMA_UART)

			HAL_GPIO_DeInit(driver->SBGC_UART_GPIO.txPort, driver->SBGC_UART_GPIO.txPin);
			HAL_GPIO_DeInit(driver->SBGC_UART_GPIO.rxPort, driver->SBGC_UART_GPIO.rxPin);

			#if (SBGC_DRV_HAL_DMA_UART)

				/* Deinitialize the DMA Rx handler */
				if (driver->hdmaRx.State != HAL_DMA_STATE_READY)
					if (HAL_DMA_Abort(&driver->hdmaRx) != HAL_OK)
						SerialAPI_FatalErrorHandler();

				__HAL_DMA_DISABLE_IT(&driver->hdmaRx, DMA_IT_TC | DMA_IT_HT | DMA_IT_TE | DMA_IT_DME);

				if (HAL_DMA_DeInit(&driver->hdmaRx) != HAL_OK)
					SerialAPI_FatalErrorHandler();

				/* Deinitialize the DMA Tx handler */
				if (driver->hdmaTx.State != HAL_DMA_STATE_READY)
					if (HAL_DMA_Abort(&driver->hdmaTx) != HAL_OK)
						SerialAPI_FatalErrorHandler();

				__HAL_DMA_DISABLE_IT(&driver->hdmaTx, DMA_IT_TC | DMA_IT_HT | DMA_IT_TE | DMA_IT_DME);

				if (HAL_DMA_DeInit(&driver->hdmaTx) != HAL_OK)
					SerialAPI_FatalErrorHandler();

			#endif

			/* Deinitialize the UART peripheral */
			if (HAL_UART_DeInit(driver->uart) != HAL_OK)
				SerialAPI_FatalErrorHandler();

			HAL_NVIC_DisableIRQ(driver->UART_IRQn);

			#if (SBGC_DRV_USE_UART_DEBUG)

				/* Debug UART Deinit */
				HAL_GPIO_DeInit(driver->DebugUART_GPIO.txPort, driver->DebugUART_GPIO.txPin);

				if (HAL_UART_DeInit(driver->debugUart) != HAL_OK)
					SerialAPI_FatalErrorHandler();

				if (HAL_UART_Init(driver->debugUart) != HAL_OK)
					SerialAPI_FatalErrorHandler();

			#endif

		#elif (SBGC_DRV_LL_NVIC_UART || SBGC_DRV_LL_DMA_UART)

			LL_GPIO_DeInit(driver->SBGC_UART_GPIO.txPort);
			LL_GPIO_DeInit(driver->SBGC_UART_GPIO.rxPort);

			LL_USART_Disable(driver->uart);

			/* UARTx Interrupt Init */
			NVIC_SetPriority(driver->UART_IRQn, 0);
			NVIC_DisableIRQ(driver->UART_IRQn);

			#if (SBGC_DRV_LL_DMA_UART)

				LL_DMA_DisableStream(&driver->hdmaTx, SBGC_DMA_UART_TX_STREAM);
				LL_DMA_DisableStream(&driver->hdmaRx, SBGC_DMA_UART_RX_STREAM);

				LL_USART_DisableDMAReq_TX(driver->uart);
				LL_USART_DisableDMAReq_RX(driver->uart);

				LL_DMA_DeInit(&driver->hdmaTx, SBGC_DMA_UART_TX_STREAM);
				LL_DMA_DeInit(&driver->hdmaRx, SBGC_DMA_UART_RX_STREAM);

				NVIC_DisableIRQ(driver->DMA_RxIRQn);
				NVIC_DisableIRQ(driver->DMA_TxIRQn);

			#endif

			LL_USART_DeInit(driver->uart);

			#if (SBGC_DRV_USE_UART_DEBUG)

				LL_GPIO_DeInit(driver->DebugUART_GPIO.txPort);

				LL_USART_DeInit(driver->debugUart);

			#endif

		#endif
	}

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@brief	Initializes the driver object of sbgcGeneral_t
 *
 *	@param	**driver - main hardware driver object
 *	@param	*uart - user defined UART object
 *	@param	*tim - user defined timer object
 */
void DriverSBGC32_Init (void **driver, SBGC_DRV_UART_TYPE_DEF__ *uart, SBGC_DRV_TIMER_TYPE_DEF__ *tim)
{
	*driver = sbgcMalloc(sizeof(sbgcDriver_t));

	sbgcDriver_t *drv = (sbgcDriver_t*)(*driver);

	#if (SBGC_DRV_HAL_TIMER || SBGC_DRV_LL_TIMER)
		/* Timer */
		drv->tim = tim;
		drv->timCount = 0;

	#else
		unused_(tim);
	#endif

    /* UART */
	drv->uart = uart;

	#if (SBGC_DRV_USE_UART_DEBUG && (SBGC_STM32_CUSTOM_DRV))
		drv->debugUart = &SBGC_DEBUG_SERIAL_PORT;
	#endif

	#if (SBGC_STM32_CUSTOM_DRV)

		DriverSBGC32_SetPeripheryClock();

		DriverSBGC32_UART_PinDeterminate(drv);
		DriverSBGC32_UART_PeriphDeterminate(drv);

		DriverSBGC32_UART_Init(drv);

	#endif

	drv->txBuffer = (ui8*)sbgcMalloc(SBGC_DRV_TX_BUFF_TOTAL_SIZE);
	drv->rxBuffer = (ui8*)sbgcMalloc(SBGC_DRV_RX_BUFF_TOTAL_SIZE);

	DriverSBGC32_ClearTxBuff(drv);
	DriverSBGC32_ClearRxBuff(drv);

	#if (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_LL_NVIC_UART)
		/* UART Interrupts executable code */
		DISABLE_UART_CR1_TCIE(drv->uart);
		ENABLE_UART_CR1_RXNEIE(drv->uart);
		DISABLE_UART_CR1_IDLEIE(drv->uart);

		(void)READ_UART_BYTE(drv->uart);
		CLEAR_UART_ORE(drv->uart);

	#elif (SBGC_DRV_HAL_DMA_UART)
		/* UART HAL DMA executable code */
		HAL_UART_Receive_DMA(drv->uart, drv->rxBuffer, SBGC_DRV_RX_BUFF_TOTAL_SIZE);

	#elif (SBGC_DRV_LL_DMA_UART)
		/* UART LL DMA executable code */
		/* Tx Init */
		LL_USART_EnableDMAReq_TX(SBGC_SERIAL_PORT);
		LL_DMA_EnableIT_TC(SBGC_DMA_UART_TX, SBGC_DMA_UART_TX_STREAM);

		LL_DMA_ConfigAddresses(SBGC_DMA_UART_TX, SBGC_DMA_UART_TX_STREAM,
							   (ui32)drv->txBuffer,
							   LL_USART_DMA_GetRegAddr(SBGC_SERIAL_PORT, LL_USART_DMA_REG_DATA_TRANSMIT),
							   LL_DMA_GetDataTransferDirection(SBGC_DMA_UART_TX, SBGC_DMA_UART_TX_STREAM));

		SBGC_CLEAR_DMA_TC_TX;

		/* Rx Init */
		LL_USART_EnableDMAReq_RX(SBGC_SERIAL_PORT);
		LL_DMA_EnableIT_TC(SBGC_DMA_UART_RX, SBGC_DMA_UART_RX_STREAM);

		LL_DMA_ConfigAddresses(SBGC_DMA_UART_RX, SBGC_DMA_UART_RX_STREAM,
							   LL_USART_DMA_GetRegAddr(SBGC_SERIAL_PORT, LL_USART_DMA_REG_DATA_RECEIVE),
							   (ui32)drv->rxBuffer,
							   LL_DMA_GetDataTransferDirection(SBGC_DMA_UART_RX, SBGC_DMA_UART_RX_STREAM));

		LL_DMA_DisableStream(SBGC_DMA_UART_RX, SBGC_DMA_UART_RX_STREAM);
		LL_DMA_SetDataLength(SBGC_DMA_UART_RX, SBGC_DMA_UART_RX_STREAM, SBGC_DRV_RX_BUFF_TOTAL_SIZE);
		LL_DMA_EnableStream(SBGC_DMA_UART_RX, SBGC_DMA_UART_RX_STREAM);

	#endif

	#if (SBGC_DRV_HAL_TIMER || SBGC_DRV_LL_TIMER)
		START_TIMER(drv->tim);
	#endif
}


/**	@brief	Deinitializes the driver object from sbgcGeneral_t
 *
 *	@param	**driver - main hardware driver object
 */
void DriverSBGC32_Deinit (void **driver)
{
	sbgcDriver_t *drv = (sbgcDriver_t*)(*driver);

	#if (SBGC_STM32_CUSTOM_DRV)

		DriverSBGC32_UART_Deinit(drv);
		DriverSBGC32_ResetPeripheryClock();

	#endif

	DriverSBGC32_ClearTxBuff(drv);
	DriverSBGC32_ClearRxBuff(drv);

	sbgcFree(drv->txBuffer);
	sbgcFree(drv->rxBuffer);

	#if (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_LL_NVIC_UART)

		/* UART Interrupts executable code */
		DISABLE_UART_CR1_TCIE(drv->uart);
		DISABLE_UART_CR1_RXNEIE(drv->uart);
		DISABLE_UART_CR1_IDLEIE(drv->uart);

	#endif

	#if (SBGC_DRV_HAL_TIMER || SBGC_DRV_LL_TIMER)
		STOP_TIMER(drv->tim);
	#endif

	memset(*driver, 0, sizeof(sbgcDriver_t));

	sbgcFree(*driver);
}


/**	@brief	Gets current system time in milliseconds
 *
 *	@param	*driver - main hardware driver object
 *
 *	@return	Current time
 */
sbgcTicks_t DriverSBGC32_GetTimeMs (void *driver)
{
	sbgcDriver_t *drv = (sbgcDriver_t*)driver;

	#if (SBGC_USES_OS_SUPPORT)
		drv->timCount = sbgcGetTick();
	#endif

	return drv->timCount;
}


/**	@brief	Timer interrupts handler
 *
 *	@param	*driver - main hardware driver object
 */
void DriverSBGC32_TimerCallBack (void *driver)
{
	sbgcDriver_t *drv = (sbgcDriver_t*)driver;

	drv->timCount++;

	#if (SBGC_DRV_LL_TIMER)
		LL_TIM_ClearFlag_UPDATE(drv->tim);
	#endif
}


/**	@brief	Sends an amount of data to the Tx ring buffer
 *
 *	@param	*driver - main hardware driver object
 *	@param	*data - transferred data
 *	@param	size - size of transferred data
 *
 *	@return	Tx status
 */
ui8 DriverSBGC32_UartTransmitData (void *driver, ui8 *data, ui16 size)
{
	sbgcDriver_t *drv = (sbgcDriver_t*)driver;

	#if (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_LL_NVIC_UART)
	/* UART Interrupts executable code */

		if (drv->txTail != drv->txHead)
			ENABLE_UART_CR1_TCIE(drv->uart);  // Enable transfer completion interrupts

		/* Free space check */
		if (calcFreeSpaceFIFO(drv->txTail, drv->txHead, SBGC_DRV_TX_BUFF_TOTAL_SIZE) <= size)
		{
			/*  - - - User Tx Buffer Overflow Handler - - - - */

			/*  - - - - - - - - - - - - - - - - - - - - - - - */
			return SBGC_DRV_TX_BUFF_OVERFLOW_FLAG;
		}

		while (size--)
			drv->txBuffer[drv->txHead++] = *(data++);

		if (!GET_FLAG_UART_CR1_TCIE(drv->uart))
			ENABLE_UART_CR1_TCIE(drv->uart);  // Enable transfer completion interrupts

	#elif (SBGC_DRV_HAL_DMA_UART)
	/* UART DMA executable code */

		if ((SBGC_DRV_TX_BUFF_TOTAL_SIZE - drv->txHead) < size)
		{
			/*  - - - User Tx Buffer Overflow Handler - - - - */

			/*  - - - - - - - - - - - - - - - - - - - - - - - */
			return SBGC_DRV_TX_BUFF_OVERFLOW_FLAG;
		}

		if ((drv->uart->gState != HAL_UART_STATE_READY) || (drv->txHead != 0))
		{
			memcpy(&drv->txBuffer[drv->txHead], data, size);
			drv->txHead += size;
		}

		else
		{
			memcpy(drv->txBuffer, data, size);
			drv->txHead += size;
			drv->txTail = drv->txHead;

			HAL_UART_Transmit_DMA(drv->uart, drv->txBuffer, size);
		}

	#elif (SBGC_DRV_LL_DMA_UART)

		if ((SBGC_DRV_TX_BUFF_TOTAL_SIZE - drv->txHead) < size)
		{
			/*  - - - User Tx Buffer Overflow Handler - - - - */

			/*  - - - - - - - - - - - - - - - - - - - - - - - */
			return SBGC_DRV_TX_BUFF_OVERFLOW_FLAG;
		}

		if ((!GET_FLAG_UART_ISR_TC(drv->uart)) || (drv->txHead != 0))
		{
			memcpy(&drv->txBuffer[drv->txHead], data, size);
			drv->txHead += size;
		}

		else
		{
			memcpy(drv->txBuffer, data, size);
			drv->txHead += size;
			drv->txTail = drv->txHead;

			LL_DMA_DisableStream(SBGC_DMA_UART_TX, SBGC_DMA_UART_TX_STREAM);
			LL_DMA_SetDataLength(SBGC_DMA_UART_TX, SBGC_DMA_UART_TX_STREAM, size);
			LL_DMA_EnableStream(SBGC_DMA_UART_TX, SBGC_DMA_UART_TX_STREAM);
		}

	#endif

	return SBGC_DRV_TX_OK_FLAG;
}


/**	@brief	UART transfer completion interrupts handler
 *
 *	@param	*driver - main hardware driver object
 */
void DriverSBGC32_UART_TxCallBack (void *driver)
{
	sbgcDriver_t *drv = (sbgcDriver_t*)driver;

	#if (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_LL_NVIC_UART)

		WRITE_UART_BYTE(drv->uart, drv->txBuffer[drv->txTail++] & (ui32)0xFF);

		if (drv->txTail == drv->txHead)
		{
			DISABLE_UART_CR1_TCIE(drv->uart);  // Disable transmission complete interrupts

			/* - - - - User Transmit-Complete Handler - - - - */

			/*  - - - - - - - - - - - - - - - - - - - - - - - */
		}

	#else

		if (drv->txTail != drv->txHead)
		/* Start a new transmit */
		{
			ui16 dataSize = drv->txHead - drv->txTail;

			memmove(drv->txBuffer, &drv->txBuffer[drv->txTail], dataSize);

			#if (SBGC_DRV_HAL_DMA_UART)

				drv->uart->gState = HAL_UART_STATE_READY;
				HAL_UART_Transmit_DMA(drv->uart, drv->txBuffer, dataSize);

			#else

				LL_DMA_DisableStream(SBGC_DMA_UART_TX, SBGC_DMA_UART_TX_STREAM);
				LL_DMA_SetDataLength(SBGC_DMA_UART_TX, SBGC_DMA_UART_TX_STREAM, dataSize);
				LL_DMA_EnableStream(SBGC_DMA_UART_TX, SBGC_DMA_UART_TX_STREAM);

			#endif

			drv->txHead -= drv->txTail;
		}

		else
			drv->txHead = 0;

		drv->txTail = drv->txHead;

	#endif
}


/**	@brief	Service Tx buffer cleaner
 *
 *	@param	*driver - main hardware driver object
 */
void DriverSBGC32_ClearTxBuff (void *driver)
{
	sbgcDriver_t *drv = (sbgcDriver_t*)driver;

	memset(drv->txBuffer, 0, SBGC_DRV_TX_BUFF_TOTAL_SIZE);
	drv->txTail = 0;
	drv->txHead = 0;
}


/**	@brief	Returns the number of available bytes
 *
 *	@param	*driver - main hardware driver object
 *
 *	@return	Number of available bytes (0xFFFF - overflow error)
 */
ui16 DriverSBGC32_GetAvailableBytes (void *driver)
{
	sbgcDriver_t *drv = (sbgcDriver_t*)driver;

	#if (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_LL_NVIC_UART)
	/* UART Interrupts executable code */

		if (drv->rxOverflowFlag)
			return SBGC_RX_BUFFER_OVERFLOW_FLAG;

		ui16 availableBytes = calcFreeSpaceFIFO(drv->rxHead, drv->rxTail, SBGC_DRV_RX_BUFF_TOTAL_SIZE);
		availableBytes = (availableBytes == SBGC_DRV_RX_BUFF_TOTAL_SIZE) ? 0 : availableBytes;

		return availableBytes;

	#elif (SBGC_DRV_HAL_DMA_UART)

		/* UART DMA executable code */
		drv->rxHead = SBGC_DRV_RX_BUFF_TOTAL_SIZE - GET_DMA_RX_COUNTER(drv->uart->hdmarx);
		return (drv->rxHead - drv->rxTail) & SBGC_DRV_RX_BUFF_SIZE_MASK;

	#elif (SBGC_DRV_LL_DMA_UART)

		drv->rxHead = SBGC_DRV_RX_BUFF_TOTAL_SIZE - GET_DMA_RX_COUNTER(SBGC_DMA_UART_RX);
		return (drv->rxHead - drv->rxTail) & SBGC_DRV_RX_BUFF_SIZE_MASK;

	#endif
}


/**	@brief	Receives byte from the Rx ring buffer
 *
 *	@param	*driver - main hardware driver object
 *	@param	*data - data buffer
 *
 *	@return	Rx status
 */
ui8 DriverSBGC32_UartReceiveByte (void *driver, ui8 *data)
{
	sbgcDriver_t *drv = (sbgcDriver_t*)driver;

	#if (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_LL_NVIC_UART)
	/* UART Interrupts executable code */

		if (drv->rxTail == drv->rxHead)
		{
			/*  - - - - User Receive-Complete Handler - - - - */

			/*  - - - - - - - - - - - - - - - - - - - - - - - */
			return SBGC_DRV_RX_BUFF_EMPTY_FLAG;
		}

		*data = drv->rxBuffer[drv->rxTail++];

		if (drv->rxOverflowFlag == 1)  // Reset the overflow flag
			drv->rxOverflowFlag = 0;

	#elif (SBGC_DRV_HAL_DMA_UART || SBGC_DRV_LL_DMA_UART)
	/* UART DMA executable code */

		if (DriverSBGC32_GetAvailableBytes(drv) == 0)
			return SBGC_DRV_RX_BUFF_EMPTY_FLAG;

		*data = drv->rxBuffer[drv->rxTail];

		if (drv->rxTail != drv->rxHead)
			drv->rxTail++;

	#endif

	return SBGC_DRV_RX_BUSY_FLAG;  // Rx ring buffer isn't empty
}


#if (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_LL_NVIC_UART)

	/**	@brief	UART receive completion interrupts handler
	 *
	 *	@param	*driver - main hardware driver object
	 */
	void DriverSBGC32_UART_RxCallBack (void *driver)
	{
		sbgcDriver_t *drv = (sbgcDriver_t*)driver;

		if (!calcFreeSpaceFIFO(drv->rxTail, drv->rxHead, SBGC_DRV_RX_BUFF_TOTAL_SIZE))
		{
			/* - - - - User rxBuffer Overflow Handler - - - - */

			/*  - - - - - - - - - - - - - - - - - - - - - - - */

			(void)READ_UART_BYTE(drv->uart);  // Prevent hardware overflow error (USART_ISR_ORE)

			drv->rxOverflowFlag = 1;

			return;
		}

		drv->rxBuffer[drv->rxHead++] = READ_UART_BYTE(drv->uart);
	}

#endif


/**	@brief	Service Rx buffer cleaner
 *
 *	@param	*driver - main hardware driver object
 */
void DriverSBGC32_ClearRxBuff (void *driver)
{
	sbgcDriver_t *drv = (sbgcDriver_t*)driver;

	memset(drv->rxBuffer, 0, SBGC_DRV_RX_BUFF_TOTAL_SIZE);
	drv->rxTail = 0;
	drv->rxHead = 0;
	drv->rxOverflowFlag = 0;
}


/**	@brief	Sends debug data
 *
 *	@param	*data - debug data
 *	@param	length - size of debug data
 */
void DriverSBGC32_UartTransmitDebugData (char *data, ui16 length)
{
	#if (SBGC_DRV_USE_UART_DEBUG && (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_HAL_DMA_UART))

		/* UART HAL executable code */
		HAL_UART_Transmit(SBGC_DEBUG_SERIAL_PORT, (ui8*)data, length, 100);

	#elif (SBGC_DRV_USE_UART_DEBUG && (SBGC_DRV_LL_NVIC_UART || SBGC_DRV_LL_DMA_UART))

		/* UART LL executable code */
		while (length--)
		{
			while (!LL_USART_IsActiveFlag_TXE(SBGC_DEBUG_SERIAL_PORT));

			LL_USART_TransmitData8(SBGC_DEBUG_SERIAL_PORT, *(data++));
		}

	#endif
}
/**	@}
 */

#endif /* SBGC_USE_STM32_DRIVER */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
