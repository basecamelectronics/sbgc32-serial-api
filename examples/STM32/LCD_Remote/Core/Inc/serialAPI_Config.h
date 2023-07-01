/** ____________________________________________________________________
 *
 * 	SBGC32 Serial API Library v1.0
 *
 * 	@file		serialAPI_Config.h
 *
 *	@brief 		Configuration header file of the Library
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
/** ____________________________________________________________________
 *
 * 	@defgroup	Configurations Serial API Configurations
 *	@ingroup	Common
 *		@brief	Serial API Configuration header file
 *  ____________________________________________________________________
 */

#ifndef		_SERIAL_API_CONFIG_H_
#define		_SERIAL_API_CONFIG_H_

#ifdef 		__cplusplus
extern 		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

/* Primitive defines for configuration */
#define		SET_OFF					(0)
#define		SET_ON					(-1)


/**	@addtogroup	Configurations
 *	@{
 */
/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									 Library General
 */
#define		SBGC_ADJVAR_MODULE		SET_ON			/*!<  Allow work with adjustable variables											*/
#define		SBGC_CALIB_MODULE		SET_OFF			/*!<  Allow work with calibration functions											*/
#define		SBGC_EEPROM_MODULE		SET_OFF			/*!<  Allow work with EEPROM operations												*/
#define		SBGC_CONTROL_MODULE		SET_ON			/*!<  Allow gimbal control															*/
#define		SBGC_IMU_MODULE			SET_OFF			/*!<  Allow work with IMU functions													*/
#define		SBGC_PROFILES_MODULE	SET_OFF			/*!<  Allow profile configurations													*/
#define		SBGC_REALTIME_MODULE	SET_ON			/*!<  Allow realtime data processing												*/
#define		SBGC_SERVICE_MODULE		SET_ON			/*!<  Allow work with service functions												*/


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *					  Main Serial API Configurations
 */
#define		SYS_BIG_ENDIAN			SET_OFF			/*!<  Memory organization of target-control device.
	 	 	 	 	 	 	 	 	 	 	 	 	 	  LITTLE ENDIAN if this macro is set off										*/

#define		SBGC_DEBUG_MODE			SET_ON			/*!<  Debug mode flag for handling detailed system information out					*/
#define		SBGC_CONFIRM_CMD		SET_ON			/*!<  Service flag that responsible for CMD_CONFIRM commands handling
														  (wait for confirmation and set the corresponding flag)						*/
#define		SBGC_REF_INFO			SET_OFF			/*!<  Debug mode flag for getting access to auxiliary info about system parameters	*/
#define		SBGC_ADJ_VARS_REF_INFO	SET_ON			/*!<  Debug mode flag for getting access to auxiliary adjustable variable info		*/
#define		SBGC_ADJ_VARS_NAMES		SET_ON			/*!<  Add names to adjustable variable definition									*/
#define		SBGC_ADJ_VARS_ADD_FLAG	SET_OFF			/*!<  Extend adjustable variables structure by user-defined variables				*/

#define     MAX_BUFF_SIZE           256				/*!<  256 is recommended value. Maximum buffer size for communication with SBGC32.
 	 	 	 	 	 	 	 	 	 	 	 	 	 	  Can be reduced in order to minimize a RAM load in the control system			*/

#define		UNEXP_CMD_BUFFER		SET_ON			/*!<  Disable or enable command buffering											*/
	#define	UNEXP_CMD_BUFFER_SIZE	10				/*!<  1 Min --> 16 Max. Buffer size for received unexpected serial commands.
														  Various powers of 2															*/
	#define	UNEXP_CMD_ALWAYS_SAVE	SET_ON			/*!<  Keep unexpected command in the buffer while standard parsing.
	 	 	 	 	 	 	 	 	 	 	 	 	 	  See @ref SBGC32_TX_RX function												*/

#define		SBGC_TX_WAITING			100				/*!<  Units: milliseconds. Data transfer wait parameter on SBGC32
														  for the Serial API initialization												*/
#define		SBGC_RX_WAITING			300				/*!<  Units: milliseconds. Data receiving wait parameter on SBGC32
														  for the Serial API initialization												*/
#define		SBGC_REQ_WAITING		300				/*!<  Units: milliseconds. Data requesting wait parameter on SBGC32
														  for the Serial API initialization												*/
#define		SBGC_STARTUP_DELAY		1000			/*!<  Units: milliseconds. System startup delay parameter							*/

#if (SBGC_ADJ_VARS_ADD_FLAG)

	/**	@brief	User-defined additional parameters
	 *			for adjustable variables
	 */
	typedef struct
	{
		unsigned char		parameter1;				/*!<  Customizable parameter of adjustable variable									*/

	}	AdjVarCustFld_t;

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							   Driver Configurations
 */
#define		SBGC_USE_ARDUINO_DRIVER	SET_OFF			/*!<  Using an Arduino board as a master device			 							*/
#define		SBGC_USE_LINUX_DRIVER	SET_OFF			/*!<  Using a Linux machine as a master device										*/
#define		SBGC_USE_STM32_DRIVER	SET_ON			/*!<  Using a STM32 controller as a master device									*/
/**	@}
 */

#if (SBGC_USE_ARDUINO_DRIVER)
	/**	@addtogroup	ArduinoDriver
	 *	@{
	 */
	/* Arduino Driver Common Configurations --------
	 */
	/**	@verbatim

		### ATTENTION! ###

		SERIAL_TX_BUFFER_SIZE and SERIAL_RX_BUFFER_SIZE
		in the "HardwareSerial.h" library must be
		fixed to 256 value

		@endverbatim
	 */
	/**	@cond
	 */
	#define	SBGC_SERIAL_PORT		Serial1			/*!<  SBGCs UART serial port														*/
	#define	DEBUG_SERIAL_PORT		Serial			/*!<  Debug UART serial port														*/
	/**	@endcond
	 */

	#define	SBGC_SERIAL_SPEED		115200			/*!<  SBGCs UART serial speed														*/
	#define	DEBUG_SERIAL_SPEED		9600			/*!<  Debug UART serial speed														*/
	/**	@}
	 */
#endif /* SBGC_USE_ARDUINO_DRIVER */


#if (SBGC_USE_LINUX_DRIVER)
	/**	@addtogroup	LinuxDriver
	 *	@{
	 */
	/* Linux Driver Common Configurations ----------
	 */
	/**	@verbatim

		### ATTENTION! ###

		The serial port must have extended rights:
		sudo chmod a+rwx /dev/ttyUSB0

		@endverbatim
	 */
	/**	@}
	 */
	#define SBGC_SERIAL_PORT		"/dev/ttyUSB0"	/*!<  Path to a connected SBGC32 device												*/
#endif /* SBGC_USE_LINUX_DRIVER */


#if (SBGC_USE_STM32_DRIVER)
	/**	@addtogroup	STM32_Driver
	 *	@{
	 */
	/* STM32 Driver Common Configurations ----------
	 */
	#define	DRV_USE_FREERTOS		SET_OFF			/*!<  UART driver required FreeRTOS support											*/

	#define	DRV_USE_CUBEMX			SET_ON			/*!<  If set off: whole SBGC32 driver configured manually
														  through HAL or LL without CubeMX												*/

	#if (DRV_USE_FREERTOS == SET_OFF)
		#define	DRV_HAL_TIMER		SET_ON			/*!<  Timer driver works with NVIC through HAL										*/
		#define	DRV_LL_TIMER		SET_OFF			/*!<  Timer driver works with NVIC through LL										*/
	#endif

	#define	DRV_HAL_NVIC_UART		SET_ON			/*!<  UART driver works with NVIC through HAL										*/
	#define	DRV_HAL_DMA_UART		SET_OFF			/*!<  UART driver works with DMA through HAL										*/
	#define	DRV_LL_NVIC_UART		SET_OFF			/*!<  UART driver works with NVIC through LL										*/
	#define	DRV_LL_DMA_UART			SET_OFF			/*!<  UART driver works with DMA through LL											*/

	#define	DRV_USE_UART_DEBUG		SET_ON			/*!<  UART debug flag																*/

	#define	DRV_TX_BUFFER_SIZE		3				/*!<  1 Min --> 7 Max. Various powers of 2, starting from 8 (256). 					*/
	#define	DRV_RX_BUFFER_SIZE		3				/*!<  1 Min --> 7 Max. Various powers of 2, starting from 8 (256). 					*/


	/* Include driver files */
	#if (DRV_USE_FREERTOS)
		#include	"FreeRTOS.h"
		#include	"semphr.h"
	#endif

	#if (DRV_USE_CUBEMX == SET_OFF)
		#if (DRV_HAL_TIMER) || (DRV_HAL_NVIC_UART) || (DRV_HAL_DMA_UART)
			#include		"stm32f7xx_hal.h"
		#else
			#include		"stm32f7xx.h"
		#endif

		#if (DRV_LL_TIMER)
			#include		"stm32f7xx_ll_tim.h"
		#endif

		#if (DRV_LL_TIMER) || (DRV_LL_NVIC_UART) || (DRV_LL_DMA_UART)
			#include				"stm32f7xx_ll_bus.h"
			#include				"stm32f7xx_ll_pwr.h"
			#include				"stm32f7xx_ll_rcc.h"
			#include				"stm32f7xx_ll_system.h"
			#include				"stm32f7xx_ll_utils.h"

			#if (DRV_LL_NVIC_UART) || (DRV_LL_DMA_UART)
				#include			"stm32f7xx_ll_usart.h"
				#include			"stm32f7xx_ll_gpio.h"

				#if (DRV_LL_DMA_UART)
					#include		"stm32f7xx_ll_dma.h"
				#endif
			#endif
		#endif
	#endif

	/* STM32 Driver Timer Configurations -----------
	 */
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
	#if (DRV_USE_CUBEMX)
		#if (DRV_HAL_TIMER)
			#define SBGC_REFERENCE_TIMER	&htim2	/*!<  HAL User defined timer object. Each SBGC32 device has its own self timer		*/

		#elif (DRV_LL_TIMER)
			#define SBGC_REFERENCE_TIMER	TIM2	/*!<  LL User defined timer object. Each SBGC32 device has its own self timer		*/
		#endif
	#endif

	/* Timer settings without CubeMX */
	#if ((DRV_USE_CUBEMX == SET_OFF) && (DRV_HAL_TIMER || DRV_LL_TIMER))
		/** SBGCs timer instance object	*/
		#define	SBGC_TIMER_INSTANCE			TIM2

		/** SBGCs timer global interrupt. See IRQn_Type enumeration */
		#define	SBGC_TIMER_IRQN				TIM2_IRQn

		/** SBGCs timer interrupt vector. See g_pfnVectors in the STM32 startup file */
		#define	SBGC_TIMER_IRQ_HANDLER		TIM2_IRQHandler

		/** SBGCs timer interrupt priority */
		#define	SBGC_TIMER_IRQ_PRIORITY		5

		/** Clock frequency of SBGCs timer bus */
		#define	SBGC_TIMER_BUS_FREQ			108000000

		#if (DRV_HAL_TIMER)
			#define	SBGC_TIMER_NAME			qtim2	/*!<  User sample of HAL timer object												*/

			/** SBGCs timer clock functions */
			#define	SBGC_TIMER_CLOCK_ENABLE			__HAL_RCC_TIM2_CLK_ENABLE()
			#define	SBGC_TIMER_CLOCK_DISABLE		__HAL_RCC_TIM2_CLK_DISABLE()

		#else /* DRV_LL_TIMER */
			/** SBGCs timer clock functions */
			#define	SBGC_TIMER_CLOCK_ENABLE			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2)
			#define	SBGC_TIMER_CLOCK_DISABLE		LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM2)
		#endif
	#endif

	/* STM32 Driver UART Configurations ------------
	 */
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


	 	*** UART by means of CubeMX DMA: ***
		====================================

		Note: Be careful with CubeMX code generator.
		It may to create the MX_DMAx_Init() function
		under the MX_USARTx_Init() function and then
		you will be need to lift it above. Otherwise
		this program will not work.

		Also, keep in mind, that Rx channel must be
		works in the Circular mode


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

		@endverbatim
	 */
	/**	@cond
	 */
	/* UART settings with CubeMX */
	#if (DRV_USE_CUBEMX)
		#if (DRV_HAL_NVIC_UART) || (DRV_HAL_DMA_UART)
			#define SBGC_SERIAL_PORT		&huart1	/*!<  HAL User defined UART object. Used to communicate with SBGC32 device 			*/

			#if (DRV_USE_UART_DEBUG)
				#define	DEBUG_SERIAL_PORT	&huart2	/*!<  HAL User defined UART object. Used to print debug data						*/
			#endif

		#elif (DRV_LL_NVIC_UART) || (DRV_LL_DMA_UART)
			#define SBGC_SERIAL_PORT		USART1	/*!<  LL User defined UART object. Used to communicate with SBGC32 device 			*/

			#if (DRV_USE_UART_DEBUG)
				#define DEBUG_SERIAL_PORT	USART2	/*!<  LL User defined UART object. Used to print debug data							*/
			#endif
		#endif
	#endif
	/**	@endcond
	 */

	#if (DRV_LL_DMA_UART)
		#define	DMA_UART_TX			DMA2			/*!<  LL User defined DMA object. Used to communicate with SBGC32 device 			*/
		#define	DMA_UART_RX			DMA2			/*!<  LL User defined DMA object. Used to communicate with SBGC32 device 			*/

		#define	DMA_UART_TX_STREAM	LL_DMA_STREAM_7	/*!<  LL User defined DMA channel object. Used to communicate with SBGC32 device	*/
		#define	DMA_UART_RX_STREAM	LL_DMA_STREAM_2	/*!<  LL User defined DMA channel object. Used to communicate with SBGC32 device	*/

		/** Appointed in accordance with DMA_UART_TX_STREAM channel (TCx) */
		#define	CLEAR_DMA_TC_TX		LL_DMA_ClearFlag_TC7(DMA_UART_TX)

		/** Appointed in accordance with DMA_UART_RX_STREAM channel (TCx) */
		#define	CLEAR_DMA_TC_RX		LL_DMA_ClearFlag_TC2(DMA_UART_RX)

		/** Appointed in accordance with DMA_UART_TX_STREAM channel (TCx) */
		#define	GET_FLAG_DMA_HISR_TC_TX		LL_DMA_IsActiveFlag_TC7(DMA_UART_TX)

		/** Appointed in accordance with DMA_UART_RX_STREAM channel (TCx) */
		#define	GET_FLAG_DMA_HISR_TC_RX		LL_DMA_IsActiveFlag_TC2(DMA_UART_RX)
	#endif

	/* UART settings without CubeMX */
	#if (DRV_USE_CUBEMX == SET_OFF)
		/* SBGC UART (DMA) objects settings */
		#if (DRV_HAL_DMA_UART) || (DRV_HAL_NVIC_UART)
			#define	SBGC_UART_NAME	quart1			/*!<  User sample of HAL UART object												*/

			#if (DRV_HAL_DMA_UART)
				#define	SBGC_UART_DMA_NAME	qdma2	/*!<  User sample of HAL UART DMA object											*/
			#endif
		#endif

		/* SBGC UART GPIO settings */
		#define	SBGC_UART_TX_GPIO_PORT		GPIOA	/*!<  SBGCs UART Tx port															*/
		#define	SBGC_UART_RX_GPIO_PORT		GPIOA	/*!<  SBGCs UART Rx port															*/

		#if (DRV_HAL_NVIC_UART) || (DRV_HAL_DMA_UART)
			/** SBGCs UART Tx pin */
			#define	SBGC_UART_TX_PIN		GPIO_PIN_9

			/** SBGCs UART Tx pin alternate function */
			#define	SBGC_UART_TX_PIN_AF		GPIO_AF7_USART1

			/** SBGCs UART Rx pin */
			#define	SBGC_UART_RX_PIN		GPIO_PIN_10

			/** SBGCs UART Rx pin alternate function */
			#define	SBGC_UART_RX_PIN_AF		GPIO_AF7_USART1

			/** SBGCs UART GPIO clock functions */
			#define	SBGC_UART_GPIO_CLOCK_ENABLE		__HAL_RCC_GPIOA_CLK_ENABLE()
			#define	SBGC_UART_GPIO_CLOCK_DISABLE	__HAL_RCC_GPIOA_CLK_DISABLE()

		#else /* DRV_LL_NVIC_UART || DRV_LL_NVIC_UART */
			/** SBGCs UART Tx pin */
			#define	SBGC_UART_TX_PIN		LL_GPIO_PIN_14

			/** SBGCs UART Tx pin alternate function */
			#define	SBGC_UART_TX_PIN_AF		LL_GPIO_AF_4

			/** SBGCs UART Rx pin */
			#define	SBGC_UART_RX_PIN		LL_GPIO_PIN_15

			/** SBGCs UART Rx pin alternate function */
			#define	SBGC_UART_RX_PIN_AF		LL_GPIO_AF_4

			/** SBGCs UART GPIO clock functions */
			#define	SBGC_UART_GPIO_CLOCK_ENABLE		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB)
			#define	SBGC_UART_GPIO_CLOCK_DISABLE	LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOB)
		#endif

		/* SBGC UART module settings */
		#define	SBGC_UART_SERIAL_SPEED		115200	/*!<  SBGCs UART serial speed														*/

		#define	SBGC_UART_INSTANCE	USART1			/*!<  SBGCs UART instance object													*/
		#define SBGC_UART_IRQN		USART1_IRQn		/*!<  SBGCs UART global interrupt. See IRQn_Type enumeration						*/

		/**  SBGCs UART interrupt vector. See g_pfnVectors in the STM32 startup file */
		#define SBGC_UART_IRQ_HANDLER		USART1_IRQHandler

		#define	SBGC_UART_IRQ_PRIORITY		5		/*!<  SBGCs UART interrupt priority													*/

		#if (DRV_HAL_NVIC_UART || DRV_HAL_DMA_UART)
			/** SBGCs UART clock functions */
			#define SBGC_UART_CLOCK_ENABLE	__HAL_RCC_USART1_CLK_ENABLE()
			#define SBGC_UART_CLOCK_DISABLE	__HAL_RCC_USART1_CLK_DISABLE()

		#else /* DRV_LL_NVIC_UART || DRV_LL_DMA_UART */
			/** SBGCs UART clock functions */
			#define SBGC_UART_CLOCK_ENABLE	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1)
			#define SBGC_UART_CLOCK_DISABLE	LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART1)

			/** Peripheral UART clock source selection. See LL RCC driver file */
			#define	SBGC_UART_CLOCK_SRC		LL_RCC_USART1_CLKSOURCE_PCLK2
		#endif

		#if (DRV_HAL_DMA_UART || DRV_LL_DMA_UART)
			/* SBGC UART DMA module settings */
			/** SBGCs UART DMA Tx channel global interrupt. See IRQn_Type enumeration */
			#define	SBGC_UART_DMA_TX_CH_IRQN		DMA2_Stream7_IRQn

			/** SBGCs UART DMA Rx channel global interrupt. See IRQn_Type enumeration */
			#define	SBGC_UART_DMA_RX_CH_IRQN		DMA2_Stream2_IRQn

			/** SBGCs UART DMA Tx channel interrupt vector. See g_pfnVectors in the STM32 startup file */
			#define SBGC_UART_DMA_TX_CH_IRQ_HANDLER	DMA2_Stream7_IRQHandler

			/** SBGCs UART DMA Rx channel interrupt vector. See g_pfnVectors in the STM32 startup file */
			#define SBGC_UART_DMA_RX_CH_IRQ_HANDLER	DMA2_Stream2_IRQHandler

			#if (DRV_HAL_DMA_UART)
				/** SBGCs UART DMA Tx channel. See HAL DMA extension module file and DMAx request mapping in a reference manual */
				#define SBGC_UART_DMA_TX_CHANNEL	DMA_CHANNEL_4

				/** SBGCs UART DMA Rx channel. See HAL DMA extension module file and DMAx request mapping in a reference manual */
				#define SBGC_UART_DMA_RX_CHANNEL	DMA_CHANNEL_4

				/** SBGCs UART DMA Tx base stream */
				#define SBGC_UART_DMA_TX_INSTANCE	DMA2_Stream7

				/** SBGCs UART DMA Rx base stream */
				#define SBGC_UART_DMA_RX_INSTANCE	DMA2_Stream2

				/** SBGCs UART DMA clock functions */
				#define	SBGC_UART_DMA_CLOCK_ENABLE	__HAL_RCC_DMA2_CLK_ENABLE()
				#define	SBGC_UART_DMA_CLOCK_DISABLE	__HAL_RCC_DMA2_CLK_DISABLE()
			#else
				/** SBGCs UART DMA Tx channel. See LL DMA extension module file and DMAx request mapping in a reference manual */
				#define SBGC_UART_DMA_TX_CHANNEL	LL_DMA_CHANNEL_4

				/** SBGCs UART DMA Rx channel. See LL DMA extension module file and DMAx request mapping in a reference manual */
				#define SBGC_UART_DMA_RX_CHANNEL	LL_DMA_CHANNEL_4

				/** SBGCs UART DMA clock functions */
				#define	SBGC_UART_DMA_CLOCK_ENABLE	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2)
				#define	SBGC_UART_DMA_CLOCK_DISABLE	LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_DMA2)
			#endif
		#endif

		/* Debug UART settings */
		#if (DRV_USE_UART_DEBUG)
			#if (DRV_HAL_DMA_UART) || (DRV_HAL_NVIC_UART)
				#define	DEBUG_UART_NAME		quart2	/*!<  User sample of HAL UART object												*/
			#endif

			/* Debug UART module settings */
			#define	DEBUG_UART_SERIAL_SPEED	115200	/*!<  Debug UART serial speed														*/

			#define	DEBUG_UART_INSTANCE		USART2	/*!<  Debug UART instance object													*/

			/* Debug UART GPIO settings */
			#define	DEBUG_UART_TX_GPIO_PORT	GPIOA	/*!<  Debug UART Tx port															*/
			#define	DEBUG_UART_RX_GPIO_PORT	GPIOA	/*!<  Debug UART Rx port															*/

			#if (DRV_HAL_NVIC_UART || DRV_HAL_DMA_UART)
				/** Debug UART Tx pin */
				#define	DEBUG_UART_TX_PIN			GPIO_PIN_2

				/** Debug UART Tx pin alternate function */
				#define	DEBUG_UART_TX_PIN_AF		GPIO_AF7_USART2

				/** Debug UART Rx pin */
				#define	DEBUG_UART_RX_PIN			GPIO_PIN_3

				/** Debug UART Rx pin alternate function */
				#define	DEBUG_UART_RX_PIN_AF		GPIO_AF7_USART2

				/** Debug UART GPIO clock functions */
				#define	DEBUG_UART_GPIO_CLOCK_ENABLE\
													__HAL_RCC_GPIOA_CLK_ENABLE()
				#define	DEBUG_UART_GPIO_CLOCK_DISABLE\
													__HAL_RCC_GPIOA_CLK_DISABLE()

			#else /* DRV_LL_NVIC_UART || DRV_LL_NVIC_UART */
				/** Debug UART Tx pin */
				#define	DEBUG_UART_TX_PIN			LL_GPIO_PIN_2

				/** Debug UART Tx pin alternate function */
				#define	DEBUG_UART_TX_PIN_AF		LL_GPIO_AF_7

				/** Debug UART Rx pin */
				#define	DEBUG_UART_RX_PIN			LL_GPIO_PIN_3

				/** Debug UART Rx pin alternate function */
				#define	DEBUG_UART_RX_PIN_AF		LL_GPIO_AF_7

				/** Debug UART GPIO clock functions */
				#define	DEBUG_UART_GPIO_CLOCK_ENABLE\
													LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA)
				#define	DEBUG_UART_GPIO_CLOCK_DISABLE\
													LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOA)
			#endif

			#if (DRV_HAL_NVIC_UART) || (DRV_HAL_DMA_UART)
				/** Debug UART clock functions */
				#define DEBUG_UART_CLOCK_ENABLE		__HAL_RCC_USART2_CLK_ENABLE()
				#define DEBUG_UART_CLOCK_DISABLE	__HAL_RCC_USART2_CLK_DISABLE()
			#else /* DRV_LL_NVIC_UART || DRV_LL_DMA_UART */
				/** Debug UART clock functions */
				#define DEBUG_UART_CLOCK_ENABLE		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2)
				#define DEBUG_UART_CLOCK_DISABLE	LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART2)

				/** Peripheral UART clock source selection. See LL RCC driver file */
				#define	DEBUG_UART_CLOCK_SRC		LL_RCC_USART1_CLKSOURCE_PCLK2
			#endif
		#endif
	#endif
	/**	@}
	 */
#endif /* SBGC_USE_STM32_DRIVER */


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef 		__cplusplus
			}
#endif

#endif		/* _SERIAL_API_CONFIG_TEMPLATE_H_ */
