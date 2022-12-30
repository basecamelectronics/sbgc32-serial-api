/** ____________________________________________________________________
 *
 * 	@file		driver_STM32.h
 *
 *	@brief 		STM32 driver header file
 *
 *				<center><a href="https://www.basecamelectronics.com">
 *				www.basecamelectronics.com</a>
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
/** ____________________________________________________________________
 *
 * 	@defgroup	STM32_Driver STM32 Driver
 *	@ingroup	Drivers
 *		@brief	STM32 Driver Module
 *  ____________________________________________________________________
 */

#ifndef		_DRIVER_STM32_H_
#define		_DRIVER_STM32_H_

#ifdef		__cplusplus
extern		"C" {
#endif

#include	"MCU_Config.h"


/**	@addtogroup	STM32_Driver
 *	@{
 */
/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								Macros and Constants
 */
/*  = = = = = = = = = = = = = = = = = = = = = = = */
/*				   ### Timer ###				  */
/*  = = = = = = = = = = = = = = = = = = = = = = = */
/**	@verbatim

	Copy this code into the TIMx_IRQHandler()
	function (if you are use HAL drivers - above
	the HAL_TIM_IRQHandler(&htimx)) function in
	the stm32XXxx_it.c file:

	if (GET_FLAG_TIM_SR_UIF(INTERNAL_MAIN_TIMER) &&
		GET_FLAG_TIM_DIER_UIE(INTERNAL_MAIN_TIMER))
		TimerDRV_CallBack(SBGC32_Device.Drv);

	where the 'SBGC32_Device' is a general SBGC32
	configurations structure.

	@endverbatim
 */

/* Timer settings with CubeMX */
#if (DRV_CUSTOM_SETTING == SET_OFF)
	/*  - - - - User Defined Parameters - - - - - */
	#if (DRV_HAL_TIMER)
		#define SBGC_REFERENCE_TIMER		&htim2	/*!<  HAL User defined timer object. Each SBGC32 device has its own self timer		*/

	#elif (DRV_LL_TIMER)
		#define SBGC_REFERENCE_TIMER		TIM2	/*!<  LL User defined timer object. Each SBGC32 device has its own self timer		*/
	/*  - - - - - - - - - - - - - - - - - - - - - */

	#else
		#define	__TIMER_TYPE_DEF	void
	#endif
#endif

/* Timer service settings */
#if (DRV_HAL_TIMER)
	#define	__TIMER_TYPE_DEF		TIM_HandleTypeDef

	#define	START_TIMER(TIM)		HAL_TIM_Base_Start_IT(TIM);

	#define	GET_FLAG_TIM_SR_UIF(TIM)		__HAL_TIM_GET_FLAG(TIM, TIM_FLAG_UPDATE)
	#define	GET_FLAG_TIM_DIER_UIE(TIM)		__HAL_TIM_GET_IT_SOURCE(TIM, TIM_FLAG_UPDATE)

#else /* DRV_LL_TIMER */
	#define	__TIMER_TYPE_DEF		TIM_TypeDef

	#define	START_TIMER(TIM)		LL_TIM_EnableIT_UPDATE(TIM);\
									LL_TIM_EnableCounter(TIM)

	#define	GET_FLAG_TIM_SR_UIF(TIM)		LL_TIM_IsActiveFlag_UPDATE(TIM)
	#define	GET_FLAG_TIM_DIER_UIE(TIM)		LL_TIM_IsEnabledIT_UPDATE(TIM)
#endif


/* Timer settings without CubeMX */
#if ((DRV_CUSTOM_SETTING) && ((DRV_HAL_TIMER) || (DRV_LL_TIMER)))
	/*  - - - - User Defined Parameters - - - - - */
	#define	SBGC_TIMER_INSTANCE		TIM2			/*!<  SBGCs timer instance object													*/
	#define	SBGC_TIMER_IRQN			TIM2_IRQn		/*!<  SBGCs timer global interrupt. See IRQn_Type enumeration						*/
	#define	SBGC_TIMER_IRQ_HANDLER	TIM2_IRQHandler	/*!<  SBGCs timer interrupt vector. See g_pfnVectors in the STM32 startup file		*/
	#define	SBGC_TIMER_IRQ_PRIORITY	5				/*!<  SBGCs timer interrupt priority												*/

	#define	SBGC_TIMER_BUS_FREQ		108000000		/*!<  Clock frequency of SBGCs timer bus											*/

	#if (DRV_HAL_TIMER)
		#define	SBGC_TIMER_NAME		qtim2			/*!<  User sample of HAL timer object												*/

		/** SBGCs timer clock enable function */
		#define	SBGC_TIMER_CLOCK_ENABLE		__HAL_RCC_TIM2_CLK_ENABLE()

	#else /* DRV_LL_TIMER */
		/** SBGCs timer clock enable function */
		#define	SBGC_TIMER_CLOCK_ENABLE		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2)
	#endif
	/*  - - - - - - - - - - - - - - - - - - - - - */

	#if (DRV_HAL_TIMER)
		#define	SBGC_REFERENCE_TIMER		(&(SBGC_TIMER_NAME))

		#define	SBGC_TIMER_DCLR		__TIMER_TYPE_DEF SBGC_TIMER_NAME

		extern SBGC_TIMER_DCLR;

	#else /* DRV_LL_TIMER */
		#define	SBGC_REFERENCE_TIMER		(SBGC_TIMER_INSTANCE)
	#endif
#endif


/*  = = = = = = = = = = = = = = = = = = = = = = = */
/*				   ### UART ###					  */
/*  = = = = = = = = = = = = = = = = = = = = = = = */
/**	@verbatim

	*** UART by means of CubeMX NVIC: ***
	=====================================

	Copy this code into the USARTx_IRQHandler()
	function (if you are use HAL drivers - above
	the HAL_UART_IRQHandler(&huartx)) function in
	the stm32XXxx_it.c file:

	if (GET_FLAG_UART_ISR_TC(SBGC_SERIAL_PORT) &&
		GET_FLAG_UART_CR1_TCIE(SBGC_SERIAL_PORT))
		UART_DRV_TxCallBack(SBGC32_Device.Drv);

	if (GET_FLAG_UART_ISR_RXNE(SBGC_SERIAL_PORT) &&
		GET_FLAG_UART_CR1_RXNEIE(SBGC_SERIAL_PORT))
		UART_DRV_RxCallBack(SBGC32_Device.Drv);

	if (GET_FLAG_UART_ISR_ORE(SBGC_SERIAL_PORT))
		CLEAR_UART_ORE(SBGC_SERIAL_PORT);

	where the 'SBGC32_Device' is a general SBGC32
	configurations structure.


	*** UART by means of CubeMX DMA with LL: ***
	============================================

	Copy this code into the DMAx_Streamx_IRQHandler()
	functions in the stm32XXxx_it.c file:

	if (GET_FLAG_DMA_HISR_TC_TX)
		CLEAR_DMA_TC_TX;

	- for DMA UART Tx channel.

	if (GET_FLAG_DMA_HISR_TC_RX)
		CLEAR_DMA_TC_RX;

	- for DMA UART Rx channel.

	Note: Be careful with CubeMX code generator.
	It may to create the MX_DMAx_Init() function
	under the MX_USARTx_Init() function and then
	you will be need to lift it above. Otherwise
	this program will not work.

	@endverbatim
 */

/* UART settings with CubeMX */
#if (DRV_CUSTOM_SETTING == SET_OFF)
	#if (DRV_HAL_NVIC_UART) || (DRV_HAL_DMA_UART)
		/*  - - - User Defined Parameters - - - - */
		#define SBGC_SERIAL_PORT	&huart1			/*!<  HAL User defined UART object. Used to communicate with SBGC32 device 			*/

		#if (DRV_USE_UART_DEBUG)
			#define	DEBUG_SERIAL_PORT		&huart2	/*!<  HAL User defined UART object. Used to print debug data						*/
		#endif
		/*  - - - - - - - - - - - - - - - - - - - */

	#elif (DRV_LL_NVIC_UART) || (DRV_LL_DMA_UART)
		/*  - - - User Defined Parameters - - - - */
		#define SBGC_SERIAL_PORT	USART1			/*!<  LL User defined UART object. Used to communicate with SBGC32 device 			*/

		#if (DRV_USE_UART_DEBUG)
			#define DEBUG_SERIAL_PORT		USART2	/*!<  LL User defined UART object. Used to print debug data							*/
		#endif
		/*  - - - - - - - - - - - - - - - - - - - */
	#endif
#endif

#if (DRV_LL_DMA_UART)
	/*  - - - - User Defined Parameters - - - - - */
	#define	DMA_UART_TX				DMA2			/*!<  LL User defined DMA object. Used to communicate with SBGC32 device 			*/
	#define	DMA_UART_RX				DMA2			/*!<  LL User defined DMA object. Used to communicate with SBGC32 device 			*/

	#define	DMA_UART_TX_STREAM		LL_DMA_STREAM_7	/*!<  LL User defined DMA channel object. Used to communicate with SBGC32 device	*/
	#define	DMA_UART_RX_STREAM		LL_DMA_STREAM_2	/*!<  LL User defined DMA channel object. Used to communicate with SBGC32 device	*/

	/** Appointed in accordance with DMA_UART_TX_STREAM channel (TCx) */
	#define	CLEAR_DMA_TC_TX			LL_DMA_ClearFlag_TC7(DMA_UART_TX)

	/** Appointed in accordance with DMA_UART_RX_STREAM channel (TCx) */
	#define	CLEAR_DMA_TC_RX			LL_DMA_ClearFlag_TC2(DMA_UART_RX)

	/** Appointed in accordance with DMA_UART_TX_STREAM channel (TCx) */
	#define	GET_FLAG_DMA_HISR_TC_TX	LL_DMA_IsActiveFlag_TC7(DMA_UART_TX)

	/** Appointed in accordance with DMA_UART_RX_STREAM channel (TCx) */
	#define	GET_FLAG_DMA_HISR_TC_RX	LL_DMA_IsActiveFlag_TC2(DMA_UART_RX)
	/*  - - - - - - - - - - - - - - - - - - - - - */
#endif


/* UART service settings */
#if (DRV_HAL_NVIC_UART)
	#if defined (STM32F0__) || defined (STM32F3__) || defined (STM32F7__) ||\
		defined (STM32L0__) || defined (STM32L4__) || defined (STM32L5__) ||\
		defined (STM32G0__) || defined (STM32G4__) || defined (STM32H7__)
		#define	TDR__				TDR
		#define	RDR__				RDR
	#else
		#define	TDR__				DR
		#define	RDR__				DR
	#endif

	#define	WRITE_UART_BYTE(UART, BYTE)		((UART)->Instance->TDR__ = BYTE)
	#define READ_UART_BYTE(UART)			(ui8)(READ_BIT((UART)->Instance->RDR__, USART_RDR_RDR) & 0xFFU)

	#define	CLEAR_UART_ORE(UART)			__HAL_UART_CLEAR_FLAG(UART, UART_CLEAR_OREF)

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
	#define	GET_FLAG_UART_ISR_ORE(UART)		__HAL_UART_GET_FLAG(UART, UART_FLAG_ORE)

	#define	__UART_TYPE_DEF					UART_HandleTypeDef

#elif (DRV_HAL_DMA_UART)
	#define	DMA_UART_RX				(SBGC_SERIAL_PORT)->hdmarx

	#define	GET_DMA_RX_COUNTER(DMAX)		__HAL_DMA_GET_COUNTER(DMAX)

	#define	__UART_TYPE_DEF					UART_HandleTypeDef
	#define	__DMA_TYPE_DEF					DMA_HandleTypeDef

#elif (DRV_LL_NVIC_UART)
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

	#define	__UART_TYPE_DEF					USART_TypeDef

#elif (DRV_LL_DMA_UART)
	#define	GET_DMA_RX_COUNTER(DMAX)		LL_DMA_GetDataLength(DMAX, DMA_UART_RX_STREAM)

	#define	__UART_TYPE_DEF					USART_TypeDef
	#define	__DMA_TYPE_DEF					DMA_TypeDef
#endif


/* UART settings without CubeMX */
#if (DRV_CUSTOM_SETTING)
	/*  - - - - User Defined Parameters - - - - - */
	/* SBGC UART GPIO settings */
	#define	SBGC_UART_TX_GPIO_PORT	GPIOB			/*!<  SBGCs UART Tx port															*/
	#define	SBGC_UART_RX_GPIO_PORT	GPIOB			/*!<  SBGCs UART Rx port															*/

	#if (DRV_HAL_NVIC_UART) || (DRV_HAL_DMA_UART)
		#define	SBGC_UART_TX_PIN	GPIO_PIN_14		/*!<  SBGCs UART Tx pin																*/
		#define	SBGC_UART_TX_PIN_AF	GPIO_AF4_USART1	/*!<  SBGCs UART Tx pin alternate function											*/

		#define	SBGC_UART_RX_PIN	GPIO_PIN_15		/*!<  SBGCs UART Rx pin																*/
		#define	SBGC_UART_RX_PIN_AF	GPIO_AF4_USART1	/*!<  SBGCs UART Rx pin alternate function											*/

		/** SBGCs UART GPIO clock enable function */
		#define	SBGC_UART_GPIO_CLOCK_ENABLE	__HAL_RCC_GPIOB_CLK_ENABLE()

	#else /* DRV_LL_NVIC_UART || DRV_LL_NVIC_UART */
		#define	SBGC_UART_TX_PIN	LL_GPIO_PIN_14	/*!<  SBGCs UART Tx pin																*/
		#define	SBGC_UART_TX_PIN_AF	LL_GPIO_AF_4	/*!<  SBGCs UART Tx pin alternate function											*/

		#define	SBGC_UART_RX_PIN	LL_GPIO_PIN_15	/*!<  SBGCs UART Rx pin																*/
		#define	SBGC_UART_RX_PIN_AF	LL_GPIO_AF_4	/*!<  SBGCs UART Rx pin alternate function											*/

		/** SBGCs UART GPIO clock enable function */
		#define	SBGC_UART_GPIO_CLOCK_ENABLE	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB)
	#endif

	/* SBGC UART module settings */
	#define	SBGC_UART_SERIAL_SPEED	115200			/*!<  SBGCs UART serial speed														*/

	#define	SBGC_UART_INSTANCE		USART1			/*!<  SBGCs UART instance object													*/
	#define SBGC_UART_IRQN			USART1_IRQn		/*!<  SBGCs UART global interrupt. See IRQn_Type enumeration						*/

	/**  SBGCs UART interrupt vector. See g_pfnVectors in the STM32 startup file */
	#define SBGC_UART_IRQ_HANDLER	USART1_IRQHandler

	#define	SBGC_UART_IRQ_PRIORITY	1				/*!<  SBGCs UART interrupt priority													*/

	#if (DRV_HAL_NVIC_UART) || (DRV_HAL_DMA_UART)
		/** SBGCs UART clock enable function */
		#define SBGC_UART_CLOCK_ENABLE		__HAL_RCC_USART1_CLK_ENABLE()

	#else /* DRV_LL_NVIC_UART || DRV_LL_DMA_UART */
		/** SBGCs UART clock enable function */
		#define SBGC_UART_CLOCK_ENABLE		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1)

		/** Peripheral UART clock source selection. See LL RCC driver file */
		#define	SBGC_UART_CLOCK_SRC			LL_RCC_USART1_CLKSOURCE_PCLK2
	#endif

	#if (DRV_HAL_DMA_UART) || (DRV_LL_DMA_UART)
		/* SBGC UART DMA module settings */
		/** SBGCs UART DMA Tx channel global interrupt. See IRQn_Type enumeration */
		#define	SBGC_UART_DMA_TX_CH_IRQN	DMA2_Stream7_IRQn

		/** SBGCs UART DMA Rx channel global interrupt. See IRQn_Type enumeration */
		#define	SBGC_UART_DMA_RX_CH_IRQN	DMA2_Stream2_IRQn

		/** SBGCs UART DMA Tx channel interrupt vector. See g_pfnVectors in the STM32 startup file */
		#define SBGC_UART_DMA_TX_CH_IRQ_HANDLER		DMA2_Stream7_IRQHandler

		/** SBGCs UART DMA Rx channel interrupt vector. See g_pfnVectors in the STM32 startup file */
		#define SBGC_UART_DMA_RX_CH_IRQ_HANDLER		DMA2_Stream2_IRQHandler

		#if (DRV_HAL_DMA_UART)
			/** SBGCs UART DMA Tx channel. See HAL DMA extension module file */
			#define SBGC_UART_DMA_TX_CHANNEL		DMA_CHANNEL_4

			/** SBGCs UART DMA Rx channel. See HAL DMA extension module file */
			#define SBGC_UART_DMA_RX_CHANNEL		DMA_CHANNEL_4

			/** SBGCs UART DMA Tx base stream */
			#define SBGC_UART_DMA_TX_INSTANCE		DMA2_Stream7

			/** SBGCs UART DMA Rx base stream */
			#define SBGC_UART_DMA_RX_INSTANCE		DMA2_Stream2

			/** SBGCs UART DMA clock enable function */
			#define	SBGC_UART_DMA_CLOCK_ENABLE		__HAL_RCC_DMA2_CLK_ENABLE()
		#else
			/** SBGCs UART DMA Tx channel. See LL DMA extension module file */
			#define SBGC_UART_DMA_TX_CHANNEL		LL_DMA_CHANNEL_4

			/** SBGCs UART DMA Rx channel. See LL DMA extension module file */
			#define SBGC_UART_DMA_RX_CHANNEL		LL_DMA_CHANNEL_4

			/** SBGCs UART DMA clock enable function */
			#define	SBGC_UART_DMA_CLOCK_ENABLE		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2)
		#endif
	#endif

	/* SBGC UART (DMA) objects settings */
	#if (DRV_HAL_DMA_UART) || (DRV_HAL_NVIC_UART)
		#define	SBGC_UART_NAME		quart1			/*!<  User sample of HAL UART object												*/

		#if (DRV_HAL_DMA_UART)
			#define	SBGC_UART_DMA_NAME		qdma2	/*!<  User sample of HAL UART DMA object											*/
		#endif
	/*  - - - - - - - - - - - - - - - - - - - - - */

		#define	SBGC_SERIAL_PORT	(&(SBGC_UART_NAME))
		#define	SBGC_UART_DCLR		__UART_TYPE_DEF SBGC_UART_NAME

		extern SBGC_UART_DCLR;

		#if (DRV_HAL_DMA_UART)
			#define	SBGC_UART_DMA_DCLR		__DMA_TYPE_DEF SBGC_UART_DMA_NAME

			extern SBGC_UART_DMA_DCLR;
		#endif

	#else /* DRV_LL_DMA_UART || DRV_LL_NVIC_UART */
		#define	SBGC_UART_NAME		SBGC_UART_INSTANCE

		#define	SBGC_SERIAL_PORT	(SBGC_UART_NAME)
	#endif

	/* Debug UART settings */
	#if (DRV_USE_UART_DEBUG)
		/*  - - - User Defined Parameters - - - - */
		/* Debug UART GPIO settings */
		#define	DEBUG_UART_TX_GPIO_PORT		GPIOA	/*!<  Debug UART Tx port															*/
		#define	DEBUG_UART_RX_GPIO_PORT		GPIOA	/*!<  Debug UART Rx port															*/

		#if (DRV_HAL_NVIC_UART) || (DRV_HAL_DMA_UART)
			/** Debug UART Tx pin */
			#define	DEBUG_UART_TX_PIN		GPIO_PIN_2

			/** Debug UART Tx pin alternate function */
			#define	DEBUG_UART_TX_PIN_AF	GPIO_AF7_USART2

			/** Debug UART Rx pin */
			#define	DEBUG_UART_RX_PIN		GPIO_PIN_3

			/** Debug UART Rx pin alternate function */
			#define	DEBUG_UART_RX_PIN_AF	GPIO_AF7_USART2

			/** Debug UART GPIO clock enable function */
			#define	DEBUG_UART_GPIO_CLOCK_ENABLE	__HAL_RCC_GPIOA_CLK_ENABLE()

		#else /* DRV_LL_NVIC_UART || DRV_LL_NVIC_UART */
			/** Debug UART Tx pin */
			#define	DEBUG_UART_TX_PIN		LL_GPIO_PIN_2

			/** Debug UART Tx pin alternate function */
			#define	DEBUG_UART_TX_PIN_AF	LL_GPIO_AF_7

			/** Debug UART Rx pin */
			#define	DEBUG_UART_RX_PIN		LL_GPIO_PIN_3

			/** Debug UART Rx pin alternate function */
			#define	DEBUG_UART_RX_PIN_AF	LL_GPIO_AF_7

			/** Debug UART GPIO clock enable function */
			#define	DEBUG_UART_GPIO_CLOCK_ENABLE	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA)
		#endif

		/* Debug UART module settings */
		#define	DEBUG_UART_SERIAL_SPEED		115200	/*!<  Debug UART serial speed														*/

		#define	DEBUG_UART_INSTANCE			USART2	/*!<  Debug UART instance object													*/

		#if (DRV_HAL_NVIC_UART) || (DRV_HAL_DMA_UART)
			/** Debug UART clock enable function */
			#define DEBUG_UART_CLOCK_ENABLE	__HAL_RCC_USART2_CLK_ENABLE()
		#else /* DRV_LL_NVIC_UART || DRV_LL_DMA_UART */
			/** Debug UART clock enable function */
			#define DEBUG_UART_CLOCK_ENABLE	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2)

			/** Peripheral UART clock source selection. See LL RCC driver file */
			#define	DEBUG_UART_CLOCK_SRC	LL_RCC_USART1_CLKSOURCE_PCLK2
		#endif

		/* Debug UART objects settings */
		#if (DRV_HAL_DMA_UART) || (DRV_HAL_NVIC_UART)
			#define	DEBUG_UART_NAME	quart2			/*!<  User sample of HAL UART object												*/
		/*  - - - - - - - - - - - - - - - - - - - */

			#define DEBUG_SERIAL_PORT		(&(DEBUG_UART_NAME))

			#define	DEBUG_UART_DCLR		__UART_TYPE_DEF DEBUG_UART_NAME

			extern DEBUG_UART_DCLR;

		#else /* DRV_LL_DMA_UART || DRV_LL_NVIC_UART */
			#define	DEBUG_UART_NAME	DEBUG_UART_INSTANCE

			#define DEBUG_SERIAL_PORT		(DEBUG_UART_NAME)
		#endif
	#endif
#endif

/* Free driver software */
/*  - - - - - User Defined Parameters - - - - - - */
#define		TX_BUFFER_SIZE			1				/*!<  Various powers of 2, starting from 8 (256). 1 Min --> 7 Max					*/
#define		RX_BUFFER_SIZE			1				/*!<  Various powers of 2, starting from 8 (256). 1 Min --> 7 Max					*/
/*  - - - - - - - - - - - - - - - - - - - - - - - */

#define		TX_FIFO_TOTAL_SIZE		(1 << (TX_BUFFER_SIZE + 7))
#define		RX_FIFO_TOTAL_SIZE		(1 << (RX_BUFFER_SIZE + 7))


#if defined (HAL_MODULE_ENABLED)
	#define	DELAY_MS_(ms)			HAL_Delay(ms)
#elif defined (USE_FULL_LL_DRIVER)
	#define	DELAY_MS_(ms)			LL_mDelay(ms)
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									Hardware Objects
 */
typedef struct
{
	ui16			txPin;  						/*!<  GPIO pin																		*/
	GPIO_TypeDef	*txPort;						/*!<  GPIO port																		*/
	ui8				txAF; 							/*!<  Alternate function															*/

	ui16			rxPin;							/*!<  GPIO pin																		*/
	GPIO_TypeDef	*rxPort;						/*!<  GPIO port																		*/
	ui8				rxAF;							/*!<  Alternate function															*/

}	UART_GPIO_t;


/**	@brief	General driver structure
 */
typedef struct
{
	#if (DRV_HAL_TIMER) || (DRV_LL_TIMER)

		/* Timer */
		__TIMER_TYPE_DEF	*tim;					/*!<  Timer object																	*/

		ui32	timCount;							/*!<  Current system time variable. Units: milliseconds								*/

		#if (DRV_CUSTOM_SETTING)

			IRQn_Type		TIM_IRQn;				/*!<  Timer IRQ number																*/

		#endif

	#endif

	/* UART */
	__UART_TYPE_DEF			*uart;					/*!<  SBGC UART communication object												*/

	ui8		TxBuffer [TX_FIFO_TOTAL_SIZE];			/*!<  SBGC UART Tx ring buffer														*/
	ui16	TxTail;									/*!<  SBGC UART Tx ring buffer tail point. Not used in DMA LL mode					*/
	ui16	TxHead;									/*!<  SBGC UART Tx ring buffer head point. Not used in DMA LL mode					*/

	ui8		RxBuffer [RX_FIFO_TOTAL_SIZE];			/*!<  SBGC UART Rx ring buffer														*/
	ui16	RxTail;									/*!<  SBGC UART Rx ring buffer tail point											*/
	ui16	RxHead;									/*!<  SBGC UART Rx ring buffer head point											*/

	ui8		RxOverflowFlag;							/*!<  SBGC UART Rx ring buffer overflow flag										*/

	#if (DRV_CUSTOM_SETTING)

		ui32				SBGC_SerialSpeed;		/*!<  SBGC UART port serial speed													*/

		UART_GPIO_t			SBGC_UART_GPIO;			/*!<  SBGC UART GPIO object															*/

		IRQn_Type			UART_IRQn;				/*!<  UART IRQ number																*/

		#if (DRV_HAL_DMA_UART) || (DRV_LL_DMA_UART)

			IRQn_Type		DMA_TxIRQn,				/*!<  DMA Tx IRQ number																*/
							DMA_RxIRQn;				/*!<  DMA Rx IRQ number																*/

			__DMA_TYPE_DEF	hdmaTx,					/*!<  UART DMA Tx channel object													*/
							hdmaRx;					/*!<  UART DMA Rx channel object													*/

		#endif

		#if (DRV_USE_UART_DEBUG)

			ui32			debugSerialSpeed;		/*!<  Debug UART port serial speed													*/

			UART_GPIO_t		DebugUART_GPIO;			/*!<  Debug UART GPIO object														*/

			__UART_TYPE_DEF	*debugUart;				/*!<  Debug UART communication object												*/

		#endif

	#endif

	#if (DRV_USE_FREERTOS)

		xSemaphoreHandle	xSemaphoreTxBusy;		/*!<  FreeRTOS UART Tx semaphore													*/

	#endif

}		Driver_t;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								 Function Prototypes
 */
void DriverInit (void *Driver, __UART_TYPE_DEF *uart, __TIMER_TYPE_DEF *tim);

ui32 GetTimeMs (void *Driver);
void TimerDRV_CallBack (void *Driver);

ui8 UartTransmitData (void *Driver, ui8 *data, ui16 size);

#if (DRV_HAL_NVIC_UART) || (DRV_LL_NVIC_UART) || (DRV_USE_FREERTOS)
	void UART_DRV_TxCallBack (void *Driver);
#endif

void ClearTxBuff (void *Driver);

ui16 GetAvailableBytes (void *Driver);
ui8 UartReceiveByte (void *Driver, ui8 *data);

#if (DRV_HAL_NVIC_UART) || (DRV_LL_NVIC_UART)
	void UART_DRV_RxCallBack (void *Driver);
#endif

void ClearRxBuff (void *Driver);

void UartTransmitDebugData (char *data, ui16 length);
/**	@}
 */

/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

#endif		/* _DRIVER_STM32_H_ */
