/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.0
 *
 *	@file		serialAPI_ConfigTemplate.h
 *
 *	@brief 		Configuration header file of the library
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
/**	____________________________________________________________________
 *
 *	@defgroup	Configurations Serial API Configurations
 *	@ingroup	Common
 *		@brief	Serial API Configuration header file
 *	____________________________________________________________________
 */

#ifndef		SERIAL_API_CONFIG_TEMPLATE_H_
#define		SERIAL_API_CONFIG_TEMPLATE_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

/* Disable and enable parameters */
#define		sbgcOFF					(0)
#define		sbgcON					(-1)


/**	@addtogroup	Configurations
 *	@{
 */
/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								Module Configuration
 */
/* Link various library functions,
   divided into modules */
#define		SBGC_ADJVAR_MODULE		sbgcOFF			/*!<  Adjustable variables. See @ref Adjvar module									*/
#define		SBGC_CALIB_MODULE		sbgcOFF			/*!<  Calibration functions. See @ref Calib module									*/
#define		SBGC_EEPROM_MODULE		sbgcOFF			/*!<  EEPROM operations. See @ref EEPROM module										*/
#define		SBGC_CONTROL_MODULE		sbgcON			/*!<  Gimbal control. See @ref Gimbal_Control module								*/
#define		SBGC_IMU_MODULE			sbgcOFF			/*!<  IMU data functions. See @ref IMU module										*/
#define		SBGC_PROFILES_MODULE	sbgcON			/*!<  Profile configurations. See @ref Profiles module								*/
#define		SBGC_REALTIME_MODULE	sbgcON			/*!<  Realtime data processing. See @ref Realtime module							*/
#define		SBGC_SERVICE_MODULE		sbgcON			/*!<  Service functions. See @ref Service module									*/


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *					  Main Serial API Configurations
 */
#define		SBGC_SYS_BIG_ENDIAN		sbgcOFF			/*!<  Memory organization of target-control device. LITTLE ENDIAN if set off		*/
#define		SBGC_SEVERAL_DEVICES	sbgcOFF			/*!<  Using more than one controller with the library								*/
#define		SBGC_PROTOCOL_VERSION	2				/*!<  V.1 or V.2 SerialAPI protocol version											*/

#define		SBGC_NON_BLOCKING_MODE	sbgcON			/*!<  Provide the library with non-blocking communication							*/
#if (SBGC_NON_BLOCKING_MODE)
	#define	SBGC_NEED_TOKENS		sbgcON			/*!<  Add a special token to keep track current SBGC32_ request						*/
	#define	SBGC_NEED_CALLBACKS		sbgcON			/*!<  Add the callbacks from the SBGC32_ functions to the user's custom events		*/
	#define	SBGC_OPTIMIZE_COMMANDS	sbgcOFF			/*!<  Suppress the new commands if there is the same command in buffer				*/
	#define	SBGC_SEND_IMMEDIATELY	sbgcOFF			/*!<  Send serial commands right away without calling processing functions			*/
	#define	SBGC_MAX_COMMAND_NUM	10				/*!<  1 Min --> 255 Max. Maximum number of serial commands processed simultaneously	*/
#endif

#define		SBGC_TX_BUFFER_SIZE		1				/*!<  1 Min (256 bytes) --> 8 Max (32768 bytes). Buffer size for sent commands		*/
#define		SBGC_RX_BUFFER_SIZE		1				/*!<  1 Min (256 bytes) --> 8 Max (32768 bytes). Buffer size for received commands	*/
#define		SBGC_RX_CMD_OLD_PRIOR	sbgcOFF			/*!<  If set on, a buffer wouldn't save the new commands to prevent overflow.
														  In this case they should be taken manually by its corresponding functions		*/
#define		SBGC_NEED_DEBUG			sbgcON			/*!<  The system will print debug messages using callback function in driver		*/
#if (SBGC_NEED_DEBUG)
	#define	SBGC_LOG_COMMAND_NUMBER	sbgcON			/*!<  Add serial command number to log												*/
	#define	SBGC_LOG_COMMAND_DIR	sbgcON			/*!<  Add serial command type (Tx/Rx) to log										*/
	#define	SBGC_LOG_COMMAND_NAME	sbgcON			/*!<  Add serial command name to log												*/
	#define	SBGC_LOG_COMMAND_ID		sbgcON			/*!<  Add serial command ID to log													*/
	#define	SBGC_LOG_COMMAND_STATUS	sbgcON			/*!<  Add serial command status to log												*/
	#define	SBGC_LOG_COMMAND_PARAM	sbgcON			/*!<  Add serial command parameter to log											*/
	#define	SBGC_LOG_COMMAND_DATA	sbgcOFF			/*!<  Add serial command raw payload to log											*/
	#define	SBGC_CUSTOM_SPRINTF		sbgcOFF			/*!<  Allow to use a custom sprintf function to optimize resources usage. Use the
														  @ref SerialAPI_LinkSprintf function to link a custom sprintf to the library	*/
#endif

#define		SBGC_NEED_ASSERTS		sbgcOFF			/*!<  Allow commands assert															*/
#define		SBGC_NEED_CONFIRM_CMD	sbgcON			/*!<  Service flag that responsible for CMD_CONFIRM commands handling				*/
#define		SBGC_NEED_REF_INFO		sbgcOFF			/*!<  Debug mode flag for getting access to auxiliary info about system parameters	*/

#define		SBGC_DEFAULT_TIMEOUT	100				/*!<  Units: milliseconds. Default timeout for serial commands						*/
#define		SBGC_STARTUP_DELAY		500				/*!<  Units: milliseconds. System startup delay parameter							*/

#define		ROLL					0				/*!<  Serial number according to the Euler order. 0 - default value					*/
#define		PITCH					1				/*!<  Serial number according to the Euler order. 1 - default value					*/
#define		YAW						2				/*!<  Serial number according to the Euler order. 2 - default value					*/

#if (SBGC_ADJVAR_MODULE)
	#define	SBGC_ADJ_VARS_REF_INFO	sbgcOFF			/*!<  Debug mode flag for getting access to auxiliary adjustable variable info		*/
	#define	SBGC_ADJ_VARS_NAMES		sbgcOFF			/*!<  Add names to adjustable variable definition									*/
	#define	SBGC_ADJ_VARS_ADD_FLAG	sbgcOFF			/*!<  Extend adjustable variables structure by user-defined variables				*/
#endif

#if (defined (SBGC_ADJ_VARS_ADD_FLAG) && SBGC_ADJ_VARS_ADD_FLAG)

	/**	@brief	User-defined additional parameters
	 *			for adjustable variables.
	 *			It may be expanded
	 *
	 *	@ref	sbgcAdjVarGeneral_t structure
	 */
	typedef struct
	{
		unsigned char		parameter1;				/*!<  Customizable parameter of adjustable variable									*/

	}	sbgcAdjVarCustFld_t;

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						   OS Support Configurations
 */
#define		SBGC_USE_AZURE_RTOS		sbgcOFF			/*!<  User's applications uses Azure RTOS. Enable support of Azure RTOS				*/
#define		SBGC_USE_FREE_RTOS		sbgcOFF			/*!<  User's applications uses FreeRTOS. Enable support of FreeRTOS					*/
#if (SBGC_USE_AZURE_RTOS || SBGC_USE_FREE_RTOS)
	#define	SBGC_THREAD_STACK_SIZE	256				/*!<  SBGC32 handler thread stack usage volume										*/
	#define	SBGC_THREAD_PRIOR		3				/*!<  SBGC32 handler thread priority												*/
#endif

#define		SBGC_USE_LINUX_OS		sbgcOFF			/*!<  User's application uses Linux OS (POSIX). Enable support of POSIX Thread		*/


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							   Driver Configurations
 */
#define		SBGC_USE_ARDUINO_DRIVER	sbgcON			/*!<  Using an Arduino board as a master device										*/
#define		SBGC_USE_LINUX_DRIVER	sbgcOFF			/*!<  Using a Linux machine as a master device										*/
#define		SBGC_USE_STM32_DRIVER	sbgcOFF			/*!<  Using a STM32 controller as a master device									*/


#if (SBGC_USE_ARDUINO_DRIVER && (SBGC_SEVERAL_DEVICES == sbgcOFF))
	/**	@addtogroup	Arduino_Driver
	 *	@{
	 */
	/* Arduino Driver Common Configurations --------
	 */
	/*	Attention!
		SERIAL_TX_BUFFER_SIZE and SERIAL_RX_BUFFER_SIZE
		in the "HardwareSerial.h" library must be
		fixed to 256 value
	 */
	/**	@cond
	 */
	#define	SBGC_SERIAL_PORT		Serial1			/*!<  SBGCs UART serial port														*/

	#if (SBGC_NEED_DEBUG)
		#define	SBGC_DEBUG_SERIAL_PORT		Serial	/*!<  Debug UART serial port														*/
	#endif

	#define	SBGC_SERIAL_SPEED		115200			/*!<  SBGCs UART serial speed														*/

	#if (SBGC_NEED_DEBUG)
		#define	SBGC_DEBUG_SERIAL_SPEED		115200	/*!<  Debug UART serial speed														*/
	#endif
	/**	@endcond
	 */
	/**	@}
	 */
#endif /* SBGC_USE_ARDUINO_DRIVER */


#if (SBGC_USE_LINUX_DRIVER && (SBGC_SEVERAL_DEVICES == sbgcOFF))
	/**	@addtogroup	Linux_Driver
	 *	@{
	 */
	/* Linux Driver Common Configurations ----------
	 */
	/*	Attention!
		The serial port must have extended rights:
		sudo chmod a+rwx /dev/ttyUSB0
	 */
	/**	@cond
	 */
	#define SBGC_SERIAL_PORT		"/dev/ttyUSB0"	/*!<  Path to a connected SBGC32 device												*/

	#define SBGC_SERIAL_SPEED		B115200			/*!<  SBGCs COM-port serial speed													*/
	/**	@endcond
	 */
	/**	@}
	 */
#endif /* SBGC_USE_LINUX_DRIVER */


#if (SBGC_USE_STM32_DRIVER)
	/**	@addtogroup	STM32_Driver
	 *	@{
	 */
	/* STM32 Driver Common Configurations ----------
	 */
	#define	SBGC_DRV_USE_CUBEMX		sbgcOFF			/*!<  If set off whole SBGC32 driver configured manually
														  through HAL or LL without CubeMX												*/

	#if (!(SBGC_USE_FREE_RTOS || SBGC_USE_AZURE_RTOS))
		#define	SBGC_DRV_HAL_TIMER	sbgcOFF			/*!<  Timer driver works with NVIC through HAL										*/
		#define	SBGC_DRV_LL_TIMER	sbgcOFF			/*!<  Timer driver works with NVIC through LL										*/

		/*	Attention!
			*** Using reference timer copy this code
			into the TIMx_IRQHandler() function
			(if you are use HAL drivers - above
			the HAL_TIM_IRQHandler(&htimx))
			function in the stm32XXxx_it.c file:

			sbgcTimerIRQ_Handler(&SBGC32_Device);

			where the 'SBGC32_Device' is a general
			SBGC32 configurations structure
		 */
	#endif

	#define	SBGC_DRV_HAL_NVIC_UART	sbgcOFF			/*!<  UART driver works with NVIC through HAL										*/
	#define	SBGC_DRV_HAL_DMA_UART	sbgcOFF			/*!<  UART driver works with DMA through HAL										*/
	#define	SBGC_DRV_LL_NVIC_UART	sbgcOFF			/*!<  UART driver works with NVIC through LL										*/
	#define	SBGC_DRV_LL_DMA_UART	sbgcOFF			/*!<  UART driver works with DMA through LL											*/

	/*	Attention!
		*** Using UART CubeMX drivers except LL DMA
		copy this code into the USARTx_IRQHandler()
		function (if you are use HAL drivers - above
		the HAL_UART_IRQHandler(&huartx)) function
		in the stm32XXxx_it.c file:

		sbgcUART_IRQ_Handler(&SBGC32_Device);

		*** Using UART DMA CubeMX HAL driver
		be careful with CubeMX code generator.
		It may create the MX_DMAx_Init() function
		under the MX_USARTx_Init() function and then
		you will be need to lift it above. Otherwise
		the program will not work.

		Also, keep in mind that Rx DMA channel must
		work in the Circular mode.

		*** Using UART DMA CubeMX LL driver copy
		this code into the DMAx_Streamx_IRQHandler()
		functions in the stm32XXxx_it.c file:

		sbgcUART_DMA_TX_IRQ_Handler(&SBGC32_Device);

		- for DMA UART Tx channel.

		sbgcUART_DMA_RX_IRQ_Handler(&SBGC32_Device);

		- for DMA UART Rx channel.

		The 'SBGC32_Device' is a general SBGC32
		configurations structure.
	 */

	#define	SBGC_DRV_TX_BUFFER_SIZE	1				/*!<  1 Min (256 bytes) --> 7 Max (16384 bytes). Driver sent data buffer size		*/
	#define	SBGC_DRV_RX_BUFFER_SIZE	1				/*!<  1 Min (256 bytes) --> 7 Max (16384 bytes). Driver received data buffer size	*/

	#if (SBGC_NEED_DEBUG)
		#define	SBGC_DRV_USE_UART_DEBUG		sbgcOFF	/*!<  UART debug flag																*/
	#endif

	#if (SBGC_DRV_USE_CUBEMX == sbgcOFF)
		#if (SBGC_DRV_HAL_TIMER || SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_HAL_DMA_UART)
			#include		"stm32f7xx_hal.h"
		#else
			#include		"stm32f7xx.h"
		#endif

		#if (SBGC_DRV_LL_TIMER)
			#include				"stm32f7xx_ll_tim.h"
		#endif

		#if (SBGC_DRV_LL_TIMER || SBGC_DRV_LL_NVIC_UART || SBGC_DRV_LL_DMA_UART)
			#include				"stm32f7xx_ll_bus.h"
			#include				"stm32f7xx_ll_pwr.h"
			#include				"stm32f7xx_ll_rcc.h"
			#include				"stm32f7xx_ll_system.h"
			#include				"stm32f7xx_ll_utils.h"

			#if (SBGC_DRV_LL_NVIC_UART || SBGC_DRV_LL_DMA_UART)
				#include			"stm32f7xx_ll_usart.h"
				#include			"stm32f7xx_ll_gpio.h"

				#if (SBGC_DRV_LL_DMA_UART)
					#include		"stm32f7xx_ll_dma.h"
				#endif
			#endif
		#endif
	#endif
#endif

#if (SBGC_USE_STM32_DRIVER && (SBGC_SEVERAL_DEVICES == sbgcOFF))
	/* STM32 Driver Timer Configurations -----------
	 */
	/* Timer settings with CubeMX */
	#if (SBGC_DRV_USE_CUBEMX)
		#if (SBGC_DRV_HAL_TIMER)
			#define SBGC_REFERENCE_TIMER	&htim2	/*!<  HAL User defined timer object. Each SBGC32 device has its own self timer		*/

		#elif (SBGC_DRV_LL_TIMER)
			#define SBGC_REFERENCE_TIMER	TIM2	/*!<  LL User defined timer object. Each SBGC32 device has its own self timer		*/
		#endif
	#endif

	/* Timer settings without CubeMX */
	#if ((SBGC_DRV_USE_CUBEMX == sbgcOFF) && (SBGC_DRV_HAL_TIMER || SBGC_DRV_LL_TIMER))
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

		#if (SBGC_DRV_HAL_TIMER)
			#define	SBGC_TIMER_NAME			htim2	/*!<  User sample of HAL timer object												*/

			/** SBGCs timer clock enable function */
			#define	SBGC_TIMER_CLOCK_ENABLE			__HAL_RCC_TIM2_CLK_ENABLE()

			/** SBGCs timer clock disable function */
			#define	SBGC_TIMER_CLOCK_DISABLE		__HAL_RCC_TIM2_CLK_DISABLE()

		#else /* SBGC_DRV_LL_TIMER */
			/** SBGCs timer clock enable function */
			#define	SBGC_TIMER_CLOCK_ENABLE			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2)

			/** SBGCs timer clock disable function */
			#define	SBGC_TIMER_CLOCK_DISABLE		LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM2)
		#endif
	#endif

	/* STM32 Driver UART Configurations ------------
	 */
	/**	@cond
	 */
	/* UART settings with CubeMX */
	#if (SBGC_DRV_USE_CUBEMX)
		#if (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_HAL_DMA_UART)
			#define SBGC_SERIAL_PORT		&huart1	/*!<  HAL User defined UART object. Used to communicate with SBGC32 device 			*/

			#if (SBGC_DRV_USE_UART_DEBUG)
				/** HAL User defined UART object. Used to print debug data */
				#define	SBGC_DEBUG_SERIAL_PORT		&huart2
			#endif

		#elif (SBGC_DRV_LL_NVIC_UART || SBGC_DRV_LL_DMA_UART)
			#define SBGC_SERIAL_PORT		USART1	/*!<  LL User defined UART object. Used to communicate with SBGC32 device 			*/

			#if (SBGC_DRV_USE_UART_DEBUG)
				/** LL User defined UART object. Used to print debug data */
				#define SBGC_DEBUG_SERIAL_PORT		USART2
			#endif
		#endif
	#endif
	/**	@endcond
	 */

	#if (SBGC_DRV_LL_DMA_UART)
		#define	SBGC_DMA_UART_TX	DMA2			/*!<  LL User defined DMA object. Used to communicate with SBGC32 device 			*/
		#define	SBGC_DMA_UART_RX	DMA2			/*!<  LL User defined DMA object. Used to communicate with SBGC32 device 			*/

		/** LL User defined DMA channel object. Used to communicate with SBGC32 device */
		#define	SBGC_DMA_UART_TX_STREAM		LL_DMA_STREAM_7

		/** LL User defined DMA channel object. Used to communicate with SBGC32 device */
		#define	SBGC_DMA_UART_RX_STREAM		LL_DMA_STREAM_2

		/** Appointed in accordance with DMA_UART_TX_STREAM channel (TCx) */
		#define	SBGC_CLEAR_DMA_TC_TX		LL_DMA_ClearFlag_TC7(SBGC_DMA_UART_TX)

		/** Appointed in accordance with DMA_UART_RX_STREAM channel (TCx) */
		#define	SBGC_CLEAR_DMA_TC_RX		LL_DMA_ClearFlag_TC2(SBGC_DMA_UART_RX)

		/** Appointed in accordance with DMA_UART_TX_STREAM channel (TCx) */
		#define	SBGC_GET_FLAG_DMA_ISR_TC_TX	LL_DMA_IsActiveFlag_TC7(SBGC_DMA_UART_TX)

		/** Appointed in accordance with DMA_UART_RX_STREAM channel (TCx) */
		#define	SBGC_GET_FLAG_DMA_ISR_TC_RX	LL_DMA_IsActiveFlag_TC2(SBGC_DMA_UART_RX)
	#endif

	/* UART settings without CubeMX */
	#if (SBGC_DRV_USE_CUBEMX == sbgcOFF)
		/* SBGC UART (DMA) objects settings */
		#if (SBGC_DRV_HAL_DMA_UART || SBGC_DRV_HAL_NVIC_UART)
			#define	SBGC_UART_NAME	huart1			/*!<  User sample of HAL UART object												*/

			#if (SBGC_DRV_HAL_DMA_UART)
				#define	SBGC_UART_DMA_NAME	hdma2	/*!<  User sample of HAL UART DMA object											*/
			#endif
		#endif

		/* SBGC UART GPIO settings */
		#define	SBGC_UART_TX_GPIO_PORT		GPIOA	/*!<  SBGCs UART Tx port															*/
		#define	SBGC_UART_RX_GPIO_PORT		GPIOA	/*!<  SBGCs UART Rx port															*/

		#if (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_HAL_DMA_UART)
			/** SBGCs UART Tx pin */
			#define	SBGC_UART_TX_PIN		GPIO_PIN_9

			/** SBGCs UART Tx pin alternate function */
			#define	SBGC_UART_TX_PIN_AF		GPIO_AF7_USART1

			/** SBGCs UART Rx pin */
			#define	SBGC_UART_RX_PIN		GPIO_PIN_10

			/** SBGCs UART Rx pin alternate function */
			#define	SBGC_UART_RX_PIN_AF		GPIO_AF7_USART1

			/** SBGCs UART GPIO clock enable function */
			#define	SBGC_UART_GPIO_CLOCK_ENABLE		__HAL_RCC_GPIOA_CLK_ENABLE()

			/** SBGCs UART GPIO clock disable function */
			#define	SBGC_UART_GPIO_CLOCK_DISABLE	__HAL_RCC_GPIOA_CLK_DISABLE()

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

			/** SBGCs UART GPIO clock disable function */
			#define	SBGC_UART_GPIO_CLOCK_DISABLE	LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOB)
		#endif

		/* SBGC UART module settings */
		#define	SBGC_UART_SERIAL_SPEED		115200	/*!<  SBGCs UART serial speed														*/

		#define	SBGC_UART_INSTANCE	USART1			/*!<  SBGCs UART instance object													*/
		#define SBGC_UART_IRQN		USART1_IRQn		/*!<  SBGCs UART global interrupt. See IRQn_Type enumeration						*/

		/**  SBGCs UART interrupt vector. See g_pfnVectors in the STM32 startup file */
		#define SBGC_UART_IRQ_HANDLER		USART1_IRQHandler

		#define	SBGC_UART_IRQ_PRIORITY		5		/*!<  SBGCs UART interrupt priority													*/

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
				#define SBGC_UART_DMA_TX_CHANNEL	DMA_CHANNEL_4

				/** SBGCs UART DMA Rx channel. See HAL DMA extension module file and DMAx request mapping in a reference manual */
				#define SBGC_UART_DMA_RX_CHANNEL	DMA_CHANNEL_4

				/** SBGCs UART DMA Tx base stream */
				#define SBGC_UART_DMA_TX_INSTANCE	DMA2_Stream7

				/** SBGCs UART DMA Rx base stream */
				#define SBGC_UART_DMA_RX_INSTANCE	DMA2_Stream2

				/** SBGCs UART DMA clock enable function */
				#define	SBGC_UART_DMA_CLOCK_ENABLE	__HAL_RCC_DMA2_CLK_ENABLE()

				/** SBGCs UART DMA clock disable function */
				#define	SBGC_UART_DMA_CLOCK_DISABLE	__HAL_RCC_DMA2_CLK_DISABLE()

			#else
				/** SBGCs UART DMA Tx channel. See LL DMA extension module file and DMAx request mapping in a reference manual */
				#define SBGC_UART_DMA_TX_CHANNEL	LL_DMA_CHANNEL_4

				/** SBGCs UART DMA Rx channel. See LL DMA extension module file and DMAx request mapping in a reference manual */
				#define SBGC_UART_DMA_RX_CHANNEL	LL_DMA_CHANNEL_4

				/** SBGCs UART DMA clock enable function */
				#define	SBGC_UART_DMA_CLOCK_ENABLE	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2)

				/** SBGCs UART DMA clock disable function */
				#define	SBGC_UART_DMA_CLOCK_DISABLE	LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_DMA2)
			#endif
		#endif
	#endif

	#if ((SBGC_DRV_USE_CUBEMX == sbgcOFF) && SBGC_DRV_USE_UART_DEBUG)
		/* Debug UART settings */
		#if (SBGC_DRV_HAL_DMA_UART || SBGC_DRV_HAL_NVIC_UART)
			/** User sample of HAL UART object */
			#define	SBGC_DEBUG_UART_NAME	huart2
		#endif

		/* Debug UART module settings */
		/** Debug UART serial speed */
		#define	SBGC_DEBUG_UART_SERIAL_SPEED		115200

		/** Debug UART instance object */
		#define	SBGC_DEBUG_UART_INSTANCE			USART2

		/* Debug UART GPIO settings */
		/** Debug UART Tx port */
		#define	SBGC_DEBUG_UART_TX_GPIO_PORT		GPIOA

		/** Debug UART Rx port */
		#define	SBGC_DEBUG_UART_RX_GPIO_PORT		GPIOA

		#if (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_HAL_DMA_UART)
			/** Debug UART Tx pin */
			#define	SBGC_DEBUG_UART_TX_PIN			GPIO_PIN_2

			/** Debug UART Tx pin alternate function */
			#define	SBGC_DEBUG_UART_TX_PIN_AF		GPIO_AF7_USART2

			/** Debug UART Rx pin */
			#define	SBGC_DEBUG_UART_RX_PIN			GPIO_PIN_3

			/** Debug UART Rx pin alternate function */
			#define	SBGC_DEBUG_UART_RX_PIN_AF		GPIO_AF7_USART2

			/** Debug UART GPIO clock enable function */
			#define	SBGC_DEBUG_UART_GPIO_CLOCK_ENABLE\
													__HAL_RCC_GPIOA_CLK_ENABLE()

			/** Debug UART GPIO clock disable function */
			#define	SBGC_DEBUG_UART_GPIO_CLOCK_DISABLE\
													__HAL_RCC_GPIOA_CLK_DISABLE()

		#else /* SBGC_DRV_LL_NVIC_UART || SBGC_DRV_LL_NVIC_UART */
			/** Debug UART Tx pin */
			#define	SBGC_DEBUG_UART_TX_PIN			LL_GPIO_PIN_2

			/** Debug UART Tx pin alternate function */
			#define	SBGC_DEBUG_UART_TX_PIN_AF		LL_GPIO_AF_7

			/** Debug UART Rx pin */
			#define	SBGC_DEBUG_UART_RX_PIN			LL_GPIO_PIN_3

			/** Debug UART Rx pin alternate function */
			#define	SBGC_DEBUG_UART_RX_PIN_AF		LL_GPIO_AF_7

			/** Debug UART GPIO clock enable function */
			#define	SBGC_DEBUG_UART_GPIO_CLOCK_ENABLE\
													LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA)

			/** Debug UART GPIO clock disable function */
			#define	SBGC_DEBUG_UART_GPIO_CLOCK_DISABLE\
													LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOA)
		#endif

		#if (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_HAL_DMA_UART)
			/** Debug UART clock enable function */
			#define SBGC_DEBUG_UART_CLOCK_ENABLE	__HAL_RCC_USART2_CLK_ENABLE()

			/** Debug UART clock disable function */
			#define SBGC_DEBUG_UART_CLOCK_DISABLE	__HAL_RCC_USART2_CLK_DISABLE()

		#else /* SBGC_DRV_LL_NVIC_UART || SBGC_DRV_LL_DMA_UART */
			/** Debug UART clock enable function */
			#define SBGC_DEBUG_UART_CLOCK_ENABLE	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2)

			/** Debug UART clock disable function */
			#define SBGC_DEBUG_UART_CLOCK_DISABLE	LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART2)

			/** Peripheral UART clock source selection. See LL RCC driver file */
			#define	SBGC_DEBUG_UART_CLOCK_SRC		LL_RCC_USART1_CLKSOURCE_PCLK2
		#endif
	#endif
	/**	@}
	 */
#endif /* SBGC_USE_STM32_DRIVER */
/**	@}
 */

/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef 		__cplusplus
			}
#endif

#endif		/* SERIAL_API_CONFIG_TEMPLATE_H_ */
