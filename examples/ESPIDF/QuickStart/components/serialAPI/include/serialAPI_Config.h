/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2.1
 *
 *	@file		serialAPI_ConfigTemplate.h
 *
 *	@brief 		Configuration header file of the library
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
 *									   Build Options
 */
#define		SBGC_NEED_SOURCES_MAKE	sbgcOFF			/*!<  Collects all nested source files into the library's top level. Uses the
														  serialAPI_MakeCpp.cpp file to collect and compile C++ sources					*/


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
#define		SBGC_SEVERAL_DEVICES	sbgcOFF			/*!<  @ref Note1. Using more than one controller with the library					*/
#define		SBGC_PROTOCOL_VERSION	2				/*!<  V.1 or V.2 SerialAPI protocol version											*/

#define		SBGC_NON_BLOCKING_MODE	sbgcON			/*!<  Provide the library with non-blocking communication							*/
#if (SBGC_NON_BLOCKING_MODE)
	#define	SBGC_NEED_TOKENS		sbgcON			/*!<  Add a special token to keep track current SBGC32_ request						*/
	#define	SBGC_NEED_CALLBACKS		sbgcON			/*!<  Add the callbacks from the SBGC32_ functions to the user's custom events		*/
	#define	SBGC_OPTIMIZE_COMMANDS	sbgcOFF			/*!<  @ref Note2. Suppress the new commands if there is the same command in buffer 	*/
	#define	SBGC_SEND_IMMEDIATELY	sbgcOFF			/*!<  @ref Note3. Send Tx commands directly without invoking processing functions	*/
	#define	SBGC_CHAINED_TIMEOUT	sbgcOFF			/*!<  In this case, the assigned timeout for the commands is shared between them.
														  If Tx command consumes the entire time limit, Rx command will be removed		*/
	#define	SBGC_MAX_COMMAND_NUM	10				/*!<  1 Min --> 255 Max. @ref Note4. Maximum simultaneous serial commands processed	*/
#endif

#define		SBGC_TX_BUFFER_SIZE		1				/*!<  1 Min (256 bytes) --> 8 Max (32768 bytes). Buffer size for sent commands		*/
#define		SBGC_RX_BUFFER_SIZE		1				/*!<  1 Min (256 bytes) --> 8 Max (32768 bytes). Buffer size for received commands	*/
#define		SBGC_RX_CMD_OLD_PRIOR	sbgcOFF			/*!<  If set on, a buffer wouldn't save the new commands to prevent overflow.
														  In this case they should be taken manually by its corresponding functions		*/
#define		SBGC_NEED_DEBUG			sbgcON			/*!<  The system will print debug messages using callback function in driver		*/
#if (SBGC_NEED_DEBUG)
	#define	SBGC_LOG_COMMAND_TIME	sbgcON			/*!<  Add serial command completion time to log										*/
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

#if (SBGC_ADJ_VARS_ADD_FLAG)

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

#if (SBGC_NEED_DEBUG && SBGC_NEED_CONFIRM_CMD)
	#define	SBGC_DETAILED_CONFIRM	sbgcOFF			/*!<  Print additional codes upon completion of confirmation command processing		*/
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						   OS Support Configurations
 */
#define		SBGC_USE_AZURE_RTOS		sbgcOFF			/*!<  User's application uses Azure RTOS. Enable support of Azure RTOS				*/
#define		SBGC_USE_FREE_RTOS		sbgcOFF			/*!<  User's application uses FreeRTOS. Enable support of FreeRTOS					*/
#define		SBGC_USE_PTHREAD_OS		sbgcOFF			/*!<  User's application uses POSIX Thread. Enable support of POSIX Thread			*/

#if (SBGC_USE_AZURE_RTOS || SBGC_USE_FREE_RTOS || SBGC_USE_PTHREAD_OS)
	#if ((SBGC_USE_PTHREAD_OS == sbgcOFF) || SBGC_USES_DOXYGEN)
		#define	SBGC_THREAD_STACK_SIZE		256		/*!<  @ref Note5. @ref SBGC32_HandlerThread stack usage volume 						*/
		#define	SBGC_THREAD_PRIOR			3		/*!<  @ref SBGC32_HandlerThread priority											*/
		#define	SBGC_THREAD_QUIET_PRIOR		1		/*!<  @ref SBGC32_HandlerThread priority for handling retained serial commands		*/
	#endif

	#define	SBGC_NEED_AUTO_PING		sbgcOFF			/*!<  Add an automatic ping command to check the connection status of SBGC32		*/

	#if (SBGC_NEED_AUTO_PING)
		#define	SBGC_AUTO_PING_PERIOD		1000	/*!<  Units: milliseconds. The periodicity of the ping command retry request		*/

		#if (SBGC_NEED_DEBUG)
			#define	SBGC_LOG_AUTO_PING		sbgcOFF	/*!<  Enable logging for the ping command											*/
		#endif

		#if (SBGC_NEED_CALLBACKS)
			#define	SBGC_AUTO_PING_CALLBACK	sbgcOFF	/*!<  A customizable callback function triggered every @ref SBGC_AUTO_PING_PERIOD
														  milliseconds. See @ref SBGC32_AutoPingCallback function						*/
		#endif
	#endif
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							   Driver Configurations
 */
#define		SBGC_USE_ARDUINO_DRIVER	sbgcOFF			/*!<  Using an Arduino board (framework) as a master device							*/
#define		SBGC_USE_ESPIDF_DRIVER	sbgcON			/*!<  Using an ESP32 controller with ESP-IDF framework as a master device			*/
#define		SBGC_USE_LINUX_DRIVER	sbgcOFF			/*!<  Using a Linux machine as a master device										*/
#define		SBGC_USE_STM32_DRIVER	sbgcOFF			/*!<  Using an STM32 controller as a master device									*/


#if (SBGC_USE_ARDUINO_DRIVER && (SBGC_SEVERAL_DEVICES == sbgcOFF))
	/**	@addtogroup	Arduino_Driver
	 *	@{
	 */
	/* Arduino Driver Common Configurations --------
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

	/* Not used on Arduino boards */
	#define	SBGC_SERIAL_TX_PIN		21				/*!<  ESP32 UART serial Tx pin for communication with SBGC32						*/
	#define	SBGC_SERIAL_RX_PIN		20				/*!<  ESP32 UART serial Rx pin for communication with SBGC32						*/
	/**	@endcond
	 */
	/**	@}
	 */
#endif /* SBGC_USE_ARDUINO_DRIVER */


#if (SBGC_USE_ESPIDF_DRIVER && (SBGC_SEVERAL_DEVICES == sbgcOFF))
	/**	@addtogroup	ESP32_Driver
	 *	@{
	 */
	/* ESP32 Driver Common Configurations ----------
	 */
	/**	@cond
	 */
	#define	SBGC_DRV_TX_BUFFER_SIZE	1				/*!<  1 Min (256 bytes) --> 7 Max (16384 bytes). Driver sent data buffer size		*/
	#define	SBGC_DRV_RX_BUFFER_SIZE	1				/*!<  1 Min (256 bytes) --> 7 Max (16384 bytes). Driver received data buffer size	*/

	#define	SBGC_SERIAL_PORT		UART_NUM_1		/*!<  SBGCs UART serial number														*/

	#if (SBGC_NEED_DEBUG)
		/** Debug UART serial number */
		#define	SBGC_DEBUG_SERIAL_PORT		UART_NUM_0
	#endif

	#define	SBGC_SERIAL_SPEED		115200			/*!<  SBGCs UART serial speed														*/

	#if (SBGC_NEED_DEBUG)
		#define	SBGC_DEBUG_SERIAL_SPEED		115200	/*!<  Debug UART serial speed														*/
	#endif

	#define	SBGC_SERIAL_TX_PIN		21				/*!<  ESP32 UART serial Tx pin for communication with SBGC32						*/
	#define	SBGC_SERIAL_RX_PIN		20				/*!<  ESP32 UART serial Rx pin for communication with SBGC32						*/
	/**	@endcond
	 */
	/**	@}
	 */
#endif /* SBGC_USE_ESPIDF_DRIVER */


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
	#define	SBGC_SERIAL_SPEED		115200			/*!<  SBGCs UART serial speed														*/

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

	#define	SBGC_DRV_CONFIGURED		sbgcOFF			/*!<  Enable if the UART and timer have already been initialized via CubeMX or by
														  other means. Otherwise copy the driverSTM32_ConfigTemplate.h file as
														  driverSTM32_Config.h and continue the configuration there						*/
	/**	@}
	 */
#endif

#if (SBGC_USE_STM32_DRIVER && SBGC_DRV_CONFIGURED && (SBGC_SEVERAL_DEVICES == sbgcOFF))
	/**	@addtogroup	STM32_Driver
	 *	@{
	 */
	/* STM32 Driver Timer Configurations -----------
	 */
	/* Timer settings with CubeMX */
	#if (SBGC_DRV_HAL_TIMER)
		#define	SBGC_REFERENCE_TIMER		&htim2	/*!<  HAL User defined timer object. Each SBGC32 device has its own self timer		*/

	#elif (SBGC_DRV_LL_TIMER)
		#define	SBGC_REFERENCE_TIMER		TIM2	/*!<  LL User defined timer object. Each SBGC32 device has its own self timer		*/
	#endif

	/* STM32 Driver UART Configurations ------------
	 */
	/**	@cond
	 */
	/* UART settings with CubeMX */
	#if (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_HAL_DMA_UART)
		#define SBGC_SERIAL_PORT	&huart1			/*!<  HAL User defined UART object. Used to communicate with SBGC32 device			*/

		#if (SBGC_DRV_USE_UART_DEBUG)
			#define	SBGC_DEBUG_SERIAL_PORT	&huart2	/*!<  HAL User defined UART object. Used to print debug data						*/
		#endif

	#elif (SBGC_DRV_LL_NVIC_UART || SBGC_DRV_LL_DMA_UART)
		#define SBGC_SERIAL_PORT	USART1			/*!<  LL User defined UART object. Used to communicate with SBGC32 device 			*/

		#if (SBGC_DRV_USE_UART_DEBUG)
			#define SBGC_DEBUG_SERIAL_PORT	USART2	/*!<  LL User defined UART object. Used to print debug data							*/
		#endif
	#endif
	/**	@endcond
	 */

	#if (SBGC_DRV_LL_DMA_UART)
		#define	SBGC_UART_DMA		DMA2			/*!<  LL User defined DMA object. Used to communicate with SBGC32 device 			*/

		#define	SBGC_UART_DMA_TX	LL_DMA_STREAM_7	/*!<  LL User defined DMA channel for Tx											*/
		#define	SBGC_UART_DMA_RX	LL_DMA_STREAM_2	/*!<  LL User defined DMA channel for Rx											*/

		/** Appointed in accordance with SBGC_UART_DMA_TX stream (TCx) */
		#define	SBGC_CLEAR_DMA_TC_TX		LL_DMA_ClearFlag_TC7

		/** Appointed in accordance with SBGC_UART_DMA_RX stream (TCx) */
		#define	SBGC_CLEAR_DMA_TC_RX		LL_DMA_ClearFlag_TC2

		/** Appointed in accordance with SBGC_UART_DMA_TX stream (TCx) */
		#define	SBGC_GET_FLAG_DMA_ISR_TC_TX	LL_DMA_IsActiveFlag_TC7

		/** Appointed in accordance with SBGC_UART_DMA_RX stream (TCx) */
		#define	SBGC_GET_FLAG_DMA_ISR_TC_RX	LL_DMA_IsActiveFlag_TC2
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
