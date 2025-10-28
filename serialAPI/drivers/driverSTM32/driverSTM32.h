/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2
 *
 *	@file		driverSTM32.h
 *
 *	@brief		STM32 driver header file
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
 *	@defgroup	STM32_Driver STM32 Driver
 *	@ingroup	Drivers
 *		@brief	STM32 Driver Module
 *	____________________________________________________________________
 */

#ifndef		DRIVERS_DRIVER_STM32_H_
#define		DRIVERS_DRIVER_STM32_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../sbgc32.h"


#if (SBGC_USE_STM32_DRIVER)

/**	@addtogroup	STM32_Driver
 *	@{
 */
/**	@verbatim

	*** Using reference timer copy this code
	into the TIMx_IRQHandler() function
	(if you are use HAL drivers - above
	the HAL_TIM_IRQHandler(&htimx))
	function in the stm32XXxx_it.c file:

		sbgcTimerIRQ_Handler(&SBGC32_Device);

	------------------------------------------------
	*** Using UART CubeMX drivers except LL DMA
	copy this code into the USARTx_IRQHandler()
	function (if you are use HAL drivers - above
	the HAL_UART_IRQHandler(&huartx)) function in
	the stm32XXxx_it.c file:

		sbgcUART_IRQ_Handler(&SBGC32_Device);

	------------------------------------------------
	*** Using UART DMA CubeMX HAL driver
	be careful with CubeMX code generator.
	It may create the MX_DMAx_Init() function under
	the MX_USARTx_Init() function and then you
	will be need to lift it above. Otherwise
	the program will not work.

	Also, keep in mind that Rx DMA channel must
	work in the Circular mode.

	------------------------------------------------
	*** Using UART DMA CubeMX LL driver copy
	this code into the DMAx_Streamx_IRQHandler()
	functions in the stm32XXxx_it.c file:

		sbgcUART_DMA_TX_IRQ_Handler(&SBGC32_Device);

	- for DMA UART Tx channel.


		sbgcUART_DMA_RX_IRQ_Handler(&SBGC32_Device);

	- for DMA UART Rx channel.

	------------------------------------------------
	The 'SBGC32_Device' is a general SBGC32
	configurations structure.

	@endverbatim
 */
/**	@}
 */

#if (SBGC_DRV_CONFIGURED)
	#if (SBGC_USE_FREE_RTOS == sbgcOFF)
		#include	"tim.h"
	#endif

	#include		"usart.h"

#elif (SBGC_SEVERAL_DEVICES == sbgcOFF)
	#include		"driverSTM32_Config.h"
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							Configuration Protection
 */
#ifndef SBGC_USE_FREE_RTOS
	#define	SBGC_USE_FREE_RTOS		sbgcOFF
#endif

#ifndef SBGC_DRV_CONFIGURED
	#define	SBGC_DRV_CONFIGURED		sbgcOFF
#endif

#if (!(SBGC_USE_FREE_RTOS || SBGC_USE_AZURE_RTOS))
	#ifndef SBGC_DRV_HAL_TIMER
		#define	SBGC_DRV_HAL_TIMER	sbgcOFF
	#endif
	#ifndef SBGC_DRV_LL_TIMER
		#define	SBGC_DRV_LL_TIMER	sbgcOFF
	#endif
#endif

#ifndef SBGC_DRV_HAL_NVIC_UART
	#define	SBGC_DRV_HAL_NVIC_UART	sbgcOFF
#endif

#ifndef SBGC_DRV_HAL_DMA_UART
	#define	SBGC_DRV_HAL_DMA_UART	sbgcOFF
#endif

#ifndef SBGC_DRV_LL_NVIC_UART
	#define	SBGC_DRV_LL_NVIC_UART	sbgcOFF
#endif

#ifndef SBGC_DRV_LL_DMA_UART
	#define	SBGC_DRV_LL_DMA_UART	sbgcOFF
#endif

#ifndef SBGC_DRV_USE_UART_DEBUG
	#define	SBGC_DRV_USE_UART_DEBUG	sbgcOFF
#endif

#ifndef SBGC_DRV_TX_BUFFER_SIZE
	#define	SBGC_DRV_TX_BUFFER_SIZE	1
#endif

#ifndef SBGC_DRV_RX_BUFFER_SIZE
	#define	SBGC_DRV_RX_BUFFER_SIZE	1
#endif

/* Define configuration way */
#if ((SBGC_SEVERAL_DEVICES == sbgcOFF) && (SBGC_DRV_CONFIGURED == sbgcOFF))
	#define	SBGC_STM32_CUSTOM_DRV	sbgcON
#else
	#define	SBGC_STM32_CUSTOM_DRV	sbgcOFF
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						  Timer Macros and Constants
 */
/* Timer settings with CubeMX */
#if (SBGC_DRV_CONFIGURED)
	#if ((SBGC_DRV_HAL_TIMER == sbgcOFF) && (SBGC_DRV_LL_TIMER == sbgcOFF))
		#define	SBGC_DRV_TIMER_TYPE_DEF__	void
	#endif
#endif

/* Timer service settings */
#if (SBGC_DRV_HAL_TIMER)
	#define	SBGC_DRV_TIMER_TYPE_DEF__		TIM_HandleTypeDef

	#if (SBGC_SEVERAL_DEVICES == sbgcOFF)
		#define	sbgcTimerIRQ_Handler(gSBGC)	{ if (__HAL_TIM_GET_FLAG(SBGC_REFERENCE_TIMER, TIM_FLAG_UPDATE) &&\
												  __HAL_TIM_GET_IT_SOURCE(SBGC_REFERENCE_TIMER, TIM_FLAG_UPDATE))\
												  DriverSBGC32_TimerCallBack((gSBGC)->_ll->drv); }
	#endif

#elif (SBGC_DRV_LL_TIMER)
	#define	SBGC_DRV_TIMER_TYPE_DEF__		TIM_TypeDef

	#if (SBGC_SEVERAL_DEVICES == sbgcOFF)
		#define	sbgcTimerIRQ_Handler(gSBGC)	{ if (LL_TIM_IsActiveFlag_UPDATE(SBGC_REFERENCE_TIMER) &&\
												  LL_TIM_IsEnabledIT_UPDATE(SBGC_REFERENCE_TIMER))\
												  DriverSBGC32_TimerCallBack((gSBGC)->_ll->drv); }
	#endif

#else /* SBGC_USE_FREE_RTOS */
	#define	SBGC_DRV_TIMER_TYPE_DEF__		void
	#define	SBGC_REFERENCE_TIMER			NULL	// Dummy
#endif


/* Timer settings without CubeMX */
#if (SBGC_STM32_CUSTOM_DRV && (SBGC_DRV_HAL_TIMER || SBGC_DRV_LL_TIMER))
	#if (SBGC_DRV_HAL_TIMER)
		#define	SBGC_REFERENCE_TIMER		(&SBGC_TIMER_NAME)

		#define	SBGC_TIMER_DCLR		SBGC_DRV_TIMER_TYPE_DEF__ SBGC_TIMER_NAME

		extern SBGC_TIMER_DCLR;

	#else /* SBGC_DRV_LL_TIMER */
		#define	SBGC_REFERENCE_TIMER		(SBGC_TIMER_INSTANCE)
	#endif
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						   UART Macros and Constants
 */
/* UART service settings */
#if (SBGC_DRV_HAL_NVIC_UART)
	#define	SBGC_DRV_UART_TYPE_DEF__		UART_HandleTypeDef

	#if (SBGC_SEVERAL_DEVICES == sbgcOFF)
		#define	sbgcUART_IRQ_Handler(gSBGC)	{ if (__HAL_UART_GET_FLAG(SBGC_SERIAL_PORT, UART_FLAG_TC) &&\
												  __HAL_UART_GET_IT_SOURCE(SBGC_SERIAL_PORT, UART_IT_TC))\
												  DriverSBGC32_UART_TxCallBack((gSBGC)->_ll->drv);\
											  if (__HAL_UART_GET_FLAG(SBGC_SERIAL_PORT, UART_FLAG_RXNE) &&\
												  __HAL_UART_GET_IT_SOURCE(SBGC_SERIAL_PORT, UART_IT_RXNE))\
												  DriverSBGC32_UART_RxCallBack((gSBGC)->_ll->drv);\
											  if (__HAL_UART_GET_FLAG(SBGC_SERIAL_PORT, UART_FLAG_ORE))\
											  	  __HAL_UART_CLEAR_FLAG(SBGC_SERIAL_PORT, UART_CLEAR_OREF); }
	#endif

#elif (SBGC_DRV_HAL_DMA_UART)
	#define	sbgcUART_IRQ_Handler(gSBGC)		{ if (__HAL_UART_GET_FLAG(SBGC_SERIAL_PORT, UART_FLAG_TC) &&\
												  __HAL_UART_GET_IT_SOURCE(SBGC_SERIAL_PORT, UART_IT_TC))\
												  DriverSBGC32_UART_TxCallBack((gSBGC)->_ll->drv); }

	#define	SBGC_DRV_UART_TYPE_DEF__		UART_HandleTypeDef
	#define	SBGC_DRV_DMA_TYPE_DEF__			DMA_HandleTypeDef

#elif (SBGC_DRV_LL_NVIC_UART)
	#define	SBGC_DRV_UART_TYPE_DEF__		USART_TypeDef

	#define	sbgcUART_IRQ_Handler(gSBGC)		{ if (LL_USART_IsActiveFlag_TC(SBGC_SERIAL_PORT) &&\
												  LL_USART_IsEnabledIT_TC(SBGC_SERIAL_PORT))\
												  DriverSBGC32_UART_TxCallBack((gSBGC)->_ll->drv);\
											  if (LL_USART_IsActiveFlag_RXNE(SBGC_SERIAL_PORT) &&\
												  LL_USART_IsEnabledIT_RXNE(SBGC_SERIAL_PORT))\
												  DriverSBGC32_UART_RxCallBack((gSBGC)->_ll->drv);\
											  if (LL_USART_IsActiveFlag_ORE(SBGC_SERIAL_PORT))\
												  LL_USART_ClearFlag_ORE(SBGC_SERIAL_PORT); }

#elif (SBGC_DRV_LL_DMA_UART)
	#define	SBGC_DRV_UART_TYPE_DEF__		USART_TypeDef
	#define	SBGC_DRV_DMA_TYPE_DEF__			DMA_TypeDef

	#define	sbgcUART_DMA_TX_IRQ_Handler(gSBGC)	{ DriverSBGC32_UART_DMA_TxClearTC();\
												  DriverSBGC32_UART_TxCallBack((gSBGC)->_ll->drv); }
	#define	sbgcUART_DMA_RX_IRQ_Handler(gSBGC)	{ DriverSBGC32_UART_DMA_RxClearTC(); }
#endif

/* UART settings without CubeMX */
#if (SBGC_STM32_CUSTOM_DRV)
	#if (SBGC_DRV_HAL_DMA_UART || SBGC_DRV_HAL_NVIC_UART)
		#define	SBGC_SERIAL_PORT	(&(SBGC_UART_NAME))
		#define	SBGC_UART_DCLR		SBGC_DRV_UART_TYPE_DEF__ SBGC_UART_NAME

		extern SBGC_UART_DCLR;

		#if (SBGC_DRV_HAL_DMA_UART)
			#define	SBGC_UART_DMA_DCLR		SBGC_DRV_DMA_TYPE_DEF__ SBGC_UART_DMA_NAME

			extern SBGC_UART_DMA_DCLR;
		#endif

	#else /* SBGC_DRV_LL_DMA_UART || SBGC_DRV_LL_NVIC_UART */
		#define	SBGC_UART_NAME		SBGC_UART_INSTANCE

		#define	SBGC_SERIAL_PORT	(SBGC_UART_NAME)
	#endif

	/* Debug UART service settings */
	#if (SBGC_DRV_USE_UART_DEBUG)
		#if (SBGC_DRV_HAL_DMA_UART || SBGC_DRV_HAL_NVIC_UART)
			#define SBGC_DEBUG_SERIAL_PORT	(&SBGC_DEBUG_UART_NAME)

			#define	SBGC_DEBUG_UART_DCLR	SBGC_DRV_UART_TYPE_DEF__ SBGC_DEBUG_UART_NAME

			extern SBGC_DEBUG_UART_DCLR;

		#else /* SBGC_DRV_LL_DMA_UART || SBGC_DRV_LL_NVIC_UART */
			#define	SBGC_DEBUG_UART_NAME	SBGC_DEBUG_UART_INSTANCE

			#define SBGC_DEBUG_SERIAL_PORT	(SBGC_DEBUG_UART_NAME)
		#endif
	#endif
#endif

/* Other */
#ifndef SBGC_SERIAL_PORT
	#define	SBGC_SERIAL_PORT	NULL
#endif

#ifndef SBGC_SERIAL_SPEED
	#define	SBGC_SERIAL_SPEED	0
#endif

#ifndef SBGC_REFERENCE_TIMER
	#define	SBGC_REFERENCE_TIMER	NULL
#endif

#ifndef sbgcTimerIRQ_Handler
	#define	sbgcTimerIRQ_Handler(gSBGC)
#endif

#ifndef sbgcUART_IRQ_Handler
	#define	sbgcUART_IRQ_Handler(gSBGC)
#endif

#ifndef sbgcUART_DMA_TX_IRQ_Handler
	#define	sbgcUART_DMA_TX_IRQ_Handler(gSBGC)
#endif

#ifndef sbgcUART_DMA_RX_IRQ_Handler
	#define	sbgcUART_DMA_RX_IRQ_Handler(gSBGC)
#endif

#ifndef sbgcDelay
	#define	sbgcDelay(ms)			DriverSBGC32_DelayMs(ms)
#endif

#ifndef sbgcGetTick
	#define	sbgcGetTick()			DriverSBGC32_GetTimeMs()
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *											   Other
 */
/* General UART buffer size values */
#define		SBGC_DRV_TX_BUFF_POWER			(SBGC_DRV_TX_BUFFER_SIZE + 7)
#define		SBGC_DRV_RX_BUFF_POWER			(SBGC_DRV_RX_BUFFER_SIZE + 7)

#define		SBGC_DRV_TX_BUFF_TOTAL_SIZE		(1 << SBGC_DRV_TX_BUFF_POWER)
#define		SBGC_DRV_RX_BUFF_TOTAL_SIZE		(1 << SBGC_DRV_RX_BUFF_POWER)

#define		SBGC_DRV_TX_BUFF_SIZE_MASK		(SBGC_DRV_TX_BUFF_TOTAL_SIZE - 1)
#define		SBGC_DRV_RX_BUFF_SIZE_MASK		(SBGC_DRV_TX_BUFF_TOTAL_SIZE - 1)

/* Warnings */
#if ((!(SBGC_USE_FREE_RTOS || SBGC_USE_AZURE_RTOS)) && ((SBGC_DRV_HAL_TIMER) + (SBGC_DRV_LL_TIMER)) != -1)
	#error "Error! Please, select the one time-control method!"
#endif

#if (((SBGC_DRV_HAL_NVIC_UART) + (SBGC_DRV_HAL_DMA_UART) + (SBGC_DRV_LL_NVIC_UART) + (SBGC_DRV_LL_DMA_UART)) != -1)
	#error "Error! Please, select the one UART-communication method!"
#endif


/**	@addtogroup	STM32_Driver
 *	@{
 */
/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									Hardware Objects
 */
/**	@brief	GPIO auxiliary structure
 */
typedef struct
{
	ui16			txPin;							/*!<  GPIO pin																		*/
	GPIO_TypeDef	*txPort;						/*!<  GPIO port																		*/
	ui8				txPinAF;						/*!<  Alternate function															*/

	ui16			rxPin;							/*!<  GPIO pin																		*/
	GPIO_TypeDef	*rxPort;						/*!<  GPIO port																		*/
	ui8				rxPinAF;						/*!<  Alternate function															*/

}	sbgcDriver_GPIO_t;


/**	@brief	General driver structure
 */
typedef struct
{
	#if (SBGC_DRV_HAL_TIMER || SBGC_DRV_LL_TIMER)

		/* Timer */
		SBGC_DRV_TIMER_TYPE_DEF__
							*tim;					/*!<  Timer object																	*/

		#if (SBGC_STM32_CUSTOM_DRV)
			IRQn_Type		TIM_IRQn;				/*!<  Timer IRQ number																*/
		#endif

	#endif

	/* UART */
	SBGC_DRV_UART_TYPE_DEF__
							*uart;					/*!<  SBGC UART communication object												*/

	ui8		*txBuffer;								/*!<  SBGC UART Tx ring buffer														*/
	ui16	txTail : SBGC_DRV_TX_BUFF_POWER;		/*!<  SBGC UART Tx ring buffer tail point. Not used in DMA LL mode					*/
	ui16	txHead : SBGC_DRV_TX_BUFF_POWER;		/*!<  SBGC UART Tx ring buffer head point. Not used in DMA LL mode					*/

	ui8		*rxBuffer;								/*!<  SBGC UART Rx ring buffer														*/
	ui16	rxTail : SBGC_DRV_RX_BUFF_POWER;		/*!<  SBGC UART Rx ring buffer tail point											*/
	ui16	rxHead : SBGC_DRV_RX_BUFF_POWER;		/*!<  SBGC UART Rx ring buffer head point											*/

	ui8		rxOverflowFlag;							/*!<  SBGC UART Rx ring buffer overflow flag										*/

	#if (SBGC_STM32_CUSTOM_DRV)

		ui32				SBGC_SerialSpeed;		/*!<  SBGC UART port serial speed													*/

		sbgcDriver_GPIO_t	SBGC_UART_GPIO;			/*!<  SBGC UART GPIO object															*/

		IRQn_Type			UART_IRQn;				/*!<  UART IRQ number																*/

		#if (SBGC_DRV_HAL_DMA_UART || SBGC_DRV_LL_DMA_UART)

			IRQn_Type		DMA_TxIRQn,				/*!<  DMA Tx IRQ number																*/
							DMA_RxIRQn;				/*!<  DMA Rx IRQ number																*/

			SBGC_DRV_DMA_TYPE_DEF__
							hdmaTx,					/*!<  UART DMA Tx channel object													*/
							hdmaRx;					/*!<  UART DMA Rx channel object													*/

		#endif

		#if (SBGC_DRV_USE_UART_DEBUG)

			ui32			debugSerialSpeed;		/*!<  Debug UART port serial speed													*/

			sbgcDriver_GPIO_t
							DebugUART_GPIO;			/*!<  Debug UART GPIO object														*/

			SBGC_DRV_UART_TYPE_DEF__
							*debugUart;				/*!<  Debug UART communication object												*/

		#endif
	#endif

}	sbgcDriver_t;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								 Function Prototypes
 */
#if (SBGC_STM32_CUSTOM_DRV == sbgcOFF)
	void DriverSBGC32_MX_Init (void);
#endif
void DriverSBGC32_Init (void **driver, void *serial, unsigned long serialSpeed);
void DriverSBGC32_Deinit (void **driver);

sbgcTicks_t DriverSBGC32_GetTimeMs (void);
void DriverSBGC32_DelayMs (sbgcTicks_t delay);
void DriverSBGC32_TimerCallBack (void *driver);

ui8 DriverSBGC32_TransmitData (void *driver, ui8 *data, ui16 size);
void DriverSBGC32_UART_DMA_TxClearTC (void);
void DriverSBGC32_UART_DMA_RxClearTC (void);
void DriverSBGC32_UART_TxCallBack (void *driver);
void DriverSBGC32_ClearTxBuff (void *driver);

ui16 DriverSBGC32_GetAvailableBytes (void *Driver);
ui8 DriverSBGC32_ReceiveByte (void *driver, ui8 *data);
#if (SBGC_DRV_HAL_NVIC_UART || SBGC_DRV_LL_NVIC_UART)
	void DriverSBGC32_UART_RxCallBack (void *driver);
#endif
void DriverSBGC32_ClearRxBuff (void *driver);

void DriverSBGC32_PrintDebugData (char *data, ui16 length);
/**	@}
 */

#endif /* SBGC_USE_STM32_DRIVER */


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

#endif		/* DRIVERS_DRIVER_STM32_H_ */
