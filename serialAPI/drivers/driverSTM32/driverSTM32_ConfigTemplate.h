/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2.1
 *
 *	@file		driverSTM32_ConfigTemplate.h
 *
 *	@brief		STM32 driver custom configuration header file
 *	____________________________________________________________________
 *
 *	@attention	<h3><center>
 *				Copyright © 2025 BaseCam Electronics™.<br>
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

#ifndef		DRIVERS_DRIVER_STM32_CONFIG_TEMPLATE_H_
#define		DRIVERS_DRIVER_STM32_CONFIG_TEMPLATE_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"serialAPI_Config.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *				  STM32 Custom Driver Configurations
 */
/**	@addtogroup	STM32_Driver
 *	@{
 */
#define		SBGC_GENERAL_DEVICE		SBGC32_Device	/*!<  Name of existing SBGC32 general object										*/

/* STM32 Driver Custom Includes ----------------
 */
#if (SBGC_DRV_HAL_TIMER || SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_HAL_DMA_UART)
	/* Connect the HAL files. See the stm32fxxx_hal_conf.h config file */
	#include		"stm32f7xx_hal.h"
#else
	/* Connect the core */
	#include		"stm32f7xx.h"
#endif

/* Connect the LL files */
#if (SBGC_DRV_LL_TIMER)
	#include		"stm32f7xx_ll_tim.h"
#endif

#if (SBGC_DRV_LL_TIMER || SBGC_DRV_LL_NVIC_UART || SBGC_DRV_LL_DMA_UART)
	#include		"stm32f7xx_ll_bus.h"
	#include		"stm32f7xx_ll_pwr.h"
	#include		"stm32f7xx_ll_rcc.h"
	#include		"stm32f7xx_ll_system.h"
	#include		"stm32f7xx_ll_utils.h"

	#if (SBGC_DRV_LL_NVIC_UART || SBGC_DRV_LL_DMA_UART)
		#include	"stm32f7xx_ll_usart.h"
		#include	"stm32f7xx_ll_gpio.h"

		#if (SBGC_DRV_LL_DMA_UART)
			#include		"stm32f7xx_ll_dma.h"
		#endif
	#endif
#endif

/* STM32 Driver Custom Timer Configurations ----
 */
#if (SBGC_DRV_HAL_TIMER || SBGC_DRV_LL_TIMER)
	#define	SBGC_TIMER_INSTANCE		TIM2			/*!<  SBGCs timer instance object													*/
	#define	SBGC_TIMER_IRQN			TIM2_IRQn		/*!<  SBGCs timer global interrupt. See IRQn_Type enumeration						*/
	#define	SBGC_TIMER_IRQ_HANDLER	TIM2_IRQHandler	/*!<  SBGCs timer interrupt vector. See g_pfnVectors in the STM32 startup file		*/
	#define	SBGC_TIMER_IRQ_PRIORITY	5				/*!<  SBGCs timer interrupt priority												*/

	#define	SBGC_TIMER_BUS_FREQ		108000000		/*!<  Clock frequency of SBGCs timer bus											*/

	#if (SBGC_DRV_HAL_TIMER)
		#define	SBGC_TIMER_NAME		htim2			/*!<  User sample of HAL timer object												*/

		/** SBGCs timer clock enable function */
		#define	SBGC_TIMER_CLOCK_ENABLE		__HAL_RCC_TIM2_CLK_ENABLE()

		/** SBGCs timer clock disable function */
		#define	SBGC_TIMER_CLOCK_DISABLE	__HAL_RCC_TIM2_CLK_DISABLE()

	#else /* SBGC_DRV_LL_TIMER */
		/** SBGCs timer clock enable function */
		#define	SBGC_TIMER_CLOCK_ENABLE		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2)

		/** SBGCs timer clock disable function */
		#define	SBGC_TIMER_CLOCK_DISABLE	LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM2)
	#endif
#endif

/* STM32 Driver Custom UART Configurations -----
 */
/* SBGC UART (DMA) objects settings */
#if (SBGC_DRV_HAL_DMA_UART || SBGC_DRV_HAL_NVIC_UART)
	#define	SBGC_UART_NAME			huart1			/*!<  User sample of HAL UART object												*/

	#if (SBGC_DRV_HAL_DMA_UART)
		#define	SBGC_UART_DMA_NAME	hdma2			/*!<  User sample of HAL UART DMA object											*/
	#endif
#endif

/* SBGC UART GPIO settings */
#define		SBGC_UART_TX_GPIO_PORT	GPIOB			/*!<  SBGCs UART Tx port															*/
#define		SBGC_UART_RX_GPIO_PORT	GPIOB			/*!<  SBGCs UART Rx port															*/

#if (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_HAL_DMA_UART)
	/** SBGCs UART Tx pin */
	#define	SBGC_UART_TX_PIN		GPIO_PIN_14

	/** SBGCs UART Tx pin alternate function. See the Alternate function mapping table in a datasheet */
	#define	SBGC_UART_TX_PIN_AF		GPIO_AF4_USART1

	/** SBGCs UART Rx pin */
	#define	SBGC_UART_RX_PIN		GPIO_PIN_15

	/** SBGCs UART Rx pin alternate function. See the Alternate function mapping table in a datasheet */
	#define	SBGC_UART_RX_PIN_AF		GPIO_AF4_USART1

	/** SBGCs UART GPIO clock enable function */
	#define	SBGC_UART_GPIO_CLOCK_ENABLE		__HAL_RCC_GPIOB_CLK_ENABLE()

#else /* SBGC_DRV_LL_NVIC_UART || SBGC_DRV_LL_NVIC_UART */
	/** SBGCs UART Tx pin */
	#define	SBGC_UART_TX_PIN		LL_GPIO_PIN_14

	/** SBGCs UART Tx pin alternate function */
	#define	SBGC_UART_TX_PIN_AF		LL_GPIO_AF_4

	/** SBGCs UART Rx pin */
	#define	SBGC_UART_RX_PIN		LL_GPIO_PIN_15

	/** SBGCs UART Rx pin alternate function */
	#define	SBGC_UART_RX_PIN_AF		LL_GPIO_AF_4

	/** SBGCs UART GPIO clock enable function */
	#define	SBGC_UART_GPIO_CLOCK_ENABLE		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB)
#endif

/* SBGC UART module settings */
#define		SBGC_UART_INSTANCE		USART1			/*!<  SBGCs UART instance object													*/
#define		SBGC_UART_IRQN			USART1_IRQn		/*!<  SBGCs UART global interrupt. See IRQn_Type enumeration						*/

/**  SBGCs UART interrupt vector. See g_pfnVectors in the STM32 startup file */
#define		SBGC_UART_IRQ_HANDLER	USART1_IRQHandler

#define		SBGC_UART_IRQ_PRIORITY	1				/*!<  SBGCs UART interrupt priority													*/

#if (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_HAL_DMA_UART)
	/** SBGCs UART clock enable function */
	#define SBGC_UART_CLOCK_ENABLE	__HAL_RCC_USART1_CLK_ENABLE()

	/** SBGCs UART clock disable function */
	#define SBGC_UART_CLOCK_DISABLE	__HAL_RCC_USART1_CLK_DISABLE()

#else /* SBGC_DRV_LL_NVIC_UART || SBGC_DRV_LL_DMA_UART */
	/** SBGCs UART clock enable function */
	#define SBGC_UART_CLOCK_ENABLE	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1)

	/** SBGCs UART clock disable function */
	#define SBGC_UART_CLOCK_DISABLE	LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART1)

	/** Peripheral UART clock source selection. See LL RCC driver file */
	#define	SBGC_UART_CLOCK_SRC		LL_RCC_USART1_CLKSOURCE_PCLK2
#endif

#if (SBGC_DRV_HAL_DMA_UART || SBGC_DRV_LL_DMA_UART)
	/* SBGC UART DMA module settings */
	/** SBGCs UART DMA Tx channel global interrupt. See IRQn_Type enumeration */
	#define	SBGC_UART_DMA_TX_CH_IRQN		DMA2_Stream7_IRQn

	/** SBGCs UART DMA Rx channel global interrupt. See IRQn_Type enumeration */
	#define	SBGC_UART_DMA_RX_CH_IRQN		DMA2_Stream2_IRQn

	/** SBGCs UART DMA Tx channel interrupt vector. See g_pfnVectors in the STM32 startup file */
	#define SBGC_UART_DMA_TX_CH_IRQ_HANDLER	DMA2_Stream7_IRQHandler

	/** SBGCs UART DMA Rx channel interrupt vector. See g_pfnVectors in the STM32 startup file */
	#define SBGC_UART_DMA_RX_CH_IRQ_HANDLER	DMA2_Stream2_IRQHandler

	#if (SBGC_DRV_HAL_DMA_UART)
		/** SBGCs UART DMA Tx channel. See HAL DMA extension module file and DMAx request mapping in a reference manual */
		#define SBGC_UART_DMA_CHANNEL		DMA_CHANNEL_4

		/** SBGCs UART DMA Tx base stream */
		#define SBGC_UART_DMA_TX_INSTANCE	DMA2_Stream7

		/** SBGCs UART DMA Rx base stream */
		#define SBGC_UART_DMA_RX_INSTANCE	DMA2_Stream2

		/** SBGCs UART DMA clock enable function */
		#define	SBGC_UART_DMA_CLOCK_ENABLE	__HAL_RCC_DMA2_CLK_ENABLE()

	#else /* SBGC_DRV_LL_DMA_UART */
		#define	SBGC_UART_DMA		DMA2			/*!<  LL User defined DMA object. Used to communicate with SBGC32 device 			*/

		/** SBGCs UART DMA Tx channel. See LL DMA extension module file and DMAx request mapping in a reference manual */
		#define SBGC_UART_DMA_CHANNEL		LL_DMA_CHANNEL_4

		/** LL User defined DMA channel for Tx */
		#define	SBGC_UART_DMA_TX			LL_DMA_STREAM_7

		/** LL User defined DMA channel for Rx */
		#define	SBGC_UART_DMA_RX			LL_DMA_STREAM_2

		/** Appointed in accordance with SBGC_UART_DMA_TX stream (TCx) */
		#define	SBGC_CLEAR_DMA_TC_TX		LL_DMA_ClearFlag_TC7

		/** Appointed in accordance with SBGC_UART_DMA_RX stream (TCx) */
		#define	SBGC_CLEAR_DMA_TC_RX		LL_DMA_ClearFlag_TC2

		/** Appointed in accordance with SBGC_UART_DMA_TX stream (TCx) */
		#define	SBGC_GET_FLAG_DMA_ISR_TC_TX	LL_DMA_IsActiveFlag_TC7

		/** Appointed in accordance with SBGC_UART_DMA_RX stream (TCx) */
		#define	SBGC_GET_FLAG_DMA_ISR_TC_RX	LL_DMA_IsActiveFlag_TC2

		/** SBGCs UART DMA clock enable function */
		#define	SBGC_UART_DMA_CLOCK_ENABLE	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2)
	#endif
#endif

#if (SBGC_DRV_USE_UART_DEBUG)
	/* Debug UART settings */
	#if (SBGC_DRV_HAL_DMA_UART || SBGC_DRV_HAL_NVIC_UART)
		/** User sample of HAL UART object */
		#define	SBGC_DEBUG_UART_NAME		huart2
	#endif

	/* Debug UART module settings */
	/** Debug UART serial speed */
	#define	SBGC_DEBUG_UART_SERIAL_SPEED	115200

	/** Debug UART instance object */
	#define	SBGC_DEBUG_UART_INSTANCE		USART2

	/* Debug UART GPIO settings */
	/** Debug UART Tx port */
	#define	SBGC_DEBUG_UART_TX_GPIO_PORT	GPIOA

	/** Debug UART Rx port */
	#define	SBGC_DEBUG_UART_RX_GPIO_PORT	GPIOA

	#if (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_HAL_DMA_UART)
		/** Debug UART Tx pin */
		#define	SBGC_DEBUG_UART_TX_PIN		GPIO_PIN_2

		/** Debug UART Tx pin alternate function. See the Alternate function mapping table in a datasheet */
		#define	SBGC_DEBUG_UART_TX_PIN_AF	GPIO_AF7_USART2

		/** Debug UART Rx pin */
		#define	SBGC_DEBUG_UART_RX_PIN		GPIO_PIN_3

		/** Debug UART Rx pin alternate function. See the Alternate function mapping table in a datasheet */
		#define	SBGC_DEBUG_UART_RX_PIN_AF	GPIO_AF7_USART2

		/** Debug UART GPIO clock enable function */
		#define	SBGC_DEBUG_UART_GPIO_CLOCK_ENABLE	__HAL_RCC_GPIOA_CLK_ENABLE()

	#else /* SBGC_DRV_LL_NVIC_UART || SBGC_DRV_LL_NVIC_UART */
		/** Debug UART Tx pin */
		#define	SBGC_DEBUG_UART_TX_PIN		LL_GPIO_PIN_2

		/** Debug UART Tx pin alternate function */
		#define	SBGC_DEBUG_UART_TX_PIN_AF	LL_GPIO_AF_7

		/** Debug UART Rx pin */
		#define	SBGC_DEBUG_UART_RX_PIN		LL_GPIO_PIN_3

		/** Debug UART Rx pin alternate function */
		#define	SBGC_DEBUG_UART_RX_PIN_AF	LL_GPIO_AF_7

		/** Debug UART GPIO clock enable function */
		#define	SBGC_DEBUG_UART_GPIO_CLOCK_ENABLE	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA)
	#endif

	#if (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_HAL_DMA_UART)
		/** Debug UART clock enable function */
		#define SBGC_DEBUG_UART_CLOCK_ENABLE		__HAL_RCC_USART2_CLK_ENABLE()

		/** Debug UART clock disable function */
		#define SBGC_DEBUG_UART_CLOCK_DISABLE		__HAL_RCC_USART2_CLK_DISABLE()

	#else /* SBGC_DRV_LL_NVIC_UART || SBGC_DRV_LL_DMA_UART */
		/** Debug UART clock enable function */
		#define SBGC_DEBUG_UART_CLOCK_ENABLE		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2)

		/** Debug UART clock disable function */
		#define SBGC_DEBUG_UART_CLOCK_DISABLE		LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART2)

		/** Peripheral UART clock source selection. See LL RCC driver file */
		#define	SBGC_DEBUG_UART_CLOCK_SRC	LL_RCC_USART1_CLKSOURCE_PCLK2
	#endif
#endif
/**	@}
 */

/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

#endif		/* DRIVERS_DRIVER_STM32_CONFIG_TEMPLATE_H_ */
