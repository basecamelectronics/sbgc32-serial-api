/** ____________________________________________________________________
 *
 * 	SBGC32 Serial API Library v1.0
 *
 * 	@file		driver_STM32.h
 *
 *	@brief 		STM32 driver header file
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
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../sbgc32.h"


#if (SBGC_USE_STM32_DRIVER)

#if (DRV_USE_CUBEMX)
	#include		"tim.h"
	#include		"usart.h"
#endif


/**	@addtogroup	STM32_Driver
 *	@{
 */
/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						  Timer Macros and Constants
 */
/* Timer settings with CubeMX */
#if (DRV_USE_CUBEMX)
	#if ((DRV_HAL_TIMER == SET_OFF) && (DRV_LL_TIMER == SET_OFF))
		#define	__TIMER_TYPE_DEF	void
	#endif
#endif

/* Timer service settings */
#if (DRV_HAL_TIMER)
	#define	__TIMER_TYPE_DEF		TIM_HandleTypeDef

	#define	START_TIMER(TIM)		HAL_TIM_Base_Start_IT(TIM);
	#define	STOP_TIMER(TIM)			HAL_TIM_Base_Stop_IT(TIM);

	#define	GET_FLAG_TIM_SR_UIF(TIM)		__HAL_TIM_GET_FLAG(TIM, TIM_FLAG_UPDATE)
	#define	GET_FLAG_TIM_DIER_UIE(TIM)		__HAL_TIM_GET_IT_SOURCE(TIM, TIM_FLAG_UPDATE)

#elif (DRV_LL_TIMER)
	#define	__TIMER_TYPE_DEF		TIM_TypeDef

	#define	START_TIMER(TIM)		LL_TIM_EnableIT_UPDATE(TIM);\
									LL_TIM_EnableCounter(TIM)
	#define	STOP_TIMER(TIM)			LL_TIM_DisableIT_UPDATE(TIM);\
									LL_TIM_DisableCounter(TIM)

	#define	GET_FLAG_TIM_SR_UIF(TIM)		LL_TIM_IsActiveFlag_UPDATE(TIM)
	#define	GET_FLAG_TIM_DIER_UIE(TIM)		LL_TIM_IsEnabledIT_UPDATE(TIM)

#else /* DRV_USE_FREERTOS */
	#define	__TIMER_TYPE_DEF		void
	#define	SBGC_REFERENCE_TIMER	NULL			// Dummy
#endif


/* Timer settings without CubeMX */
#if ((DRV_USE_CUBEMX == SET_OFF) && (DRV_HAL_TIMER || DRV_LL_TIMER))
	#if (DRV_HAL_TIMER)
		#define	SBGC_REFERENCE_TIMER		(&(SBGC_TIMER_NAME))

		#define	SBGC_TIMER_DCLR		__TIMER_TYPE_DEF SBGC_TIMER_NAME

		extern SBGC_TIMER_DCLR;

	#else /* DRV_LL_TIMER */
		#define	SBGC_REFERENCE_TIMER		(SBGC_TIMER_INSTANCE)
	#endif
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						   UART Macros and Constants
 */
/* UART service settings */
#if (DRV_HAL_NVIC_UART)
	#if defined (STM32F0) || defined (STM32F3) || defined (STM32F7) ||\
		defined (STM32L0) || defined (STM32L4) || defined (STM32L5) ||\
		defined (STM32G0) || defined (STM32G4) || defined (STM32H7)
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
#if (DRV_USE_CUBEMX == SET_OFF)
	#if (DRV_HAL_DMA_UART) || (DRV_HAL_NVIC_UART)
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

	/* Debug UART service settings */
	#if (DRV_USE_UART_DEBUG)
		#if (DRV_HAL_DMA_UART) || (DRV_HAL_NVIC_UART)
			#define DEBUG_SERIAL_PORT		(&(DEBUG_UART_NAME))

			#define	DEBUG_UART_DCLR			__UART_TYPE_DEF DEBUG_UART_NAME

			extern DEBUG_UART_DCLR;

		#else /* DRV_LL_DMA_UART || DRV_LL_NVIC_UART */
			#define	DEBUG_UART_NAME	DEBUG_UART_INSTANCE

			#define DEBUG_SERIAL_PORT		(DEBUG_UART_NAME)
		#endif
	#endif
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *											   Other
 */
/* General UART buffer sizes values */
#define		TX_FIFO_TOTAL_SIZE		(1 << (DRV_TX_BUFFER_SIZE + 7))
#define		RX_FIFO_TOTAL_SIZE		(1 << (DRV_RX_BUFFER_SIZE + 7))

/* Delay common function */
#if (DRV_USE_FREERTOS)
	#define	DELAY_MS_(ms)			vTaskDelay(ms)

#else
	#if defined (HAL_MODULE_ENABLED)
		#define	DELAY_MS_(ms)		HAL_Delay(ms)
	#elif defined (USE_FULL_LL_DRIVER)
		#define	DELAY_MS_(ms)		LL_mDelay(ms)
	#endif
#endif

/* Warnings */
#if ((DRV_USE_FREERTOS == SET_OFF) && ((DRV_HAL_TIMER) + (DRV_LL_TIMER)) != -1)
	#error "Error! Please, select a one time-control method!"
#endif

#if (((DRV_HAL_NVIC_UART) + (DRV_HAL_DMA_UART) + (DRV_LL_NVIC_UART) + (DRV_LL_DMA_UART)) != -1)
	#error "Error! Please, select a one UART-communication method!"
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
	#if defined (DRV_HAL_TIMER) || defined (DRV_LL_TIMER)

		/* Timer */
		__TIMER_TYPE_DEF	*tim;					/*!<  Timer object																	*/

		#if (DRV_USE_CUBEMX == SET_OFF)

			IRQn_Type		TIM_IRQn;				/*!<  Timer IRQ number																*/

		#endif

	#endif

	ui32	timCount;								/*!<  Current system time variable. Units: milliseconds								*/


	/* UART */
	__UART_TYPE_DEF			*uart;					/*!<  SBGC UART communication object												*/

	ui8		TxBuffer [TX_FIFO_TOTAL_SIZE];			/*!<  SBGC UART Tx ring buffer														*/
	ui16	TxTail;									/*!<  SBGC UART Tx ring buffer tail point. Not used in DMA LL mode					*/
	ui16	TxHead;									/*!<  SBGC UART Tx ring buffer head point. Not used in DMA LL mode					*/

	ui8		RxBuffer [RX_FIFO_TOTAL_SIZE];			/*!<  SBGC UART Rx ring buffer														*/
	ui16	RxTail;									/*!<  SBGC UART Rx ring buffer tail point											*/
	ui16	RxHead;									/*!<  SBGC UART Rx ring buffer head point											*/

	ui8		RxOverflowFlag;							/*!<  SBGC UART Rx ring buffer overflow flag										*/

	#if (DRV_USE_CUBEMX == SET_OFF)

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
void DriverInit (void **driver, __UART_TYPE_DEF *uart, __TIMER_TYPE_DEF *tim);
void DriverDeinit (void **driver);

ui32 GetTimeMs (void *driver);
void TimerDRV_CallBack (void *driver);

ui8 UartTransmitData (void *driver, ui8 *data, ui16 size);

#if (DRV_HAL_NVIC_UART || DRV_LL_NVIC_UART || DRV_USE_FREERTOS)
	void UART_DRV_TxCallBack (void *driver);
#endif

void ClearTxBuff (void *driver);

ui16 GetAvailableBytes (void *Driver);
ui8 UartReceiveByte (void *driver, ui8 *data);

#if (DRV_HAL_NVIC_UART) || (DRV_LL_NVIC_UART)
	void UART_DRV_RxCallBack (void *driver);
#endif

void ClearRxBuff (void *driver);

void UartTransmitDebugData (char *data, ui16 length);
/**	@}
 */

#endif		/* SBGC_USE_STM32_DRIVER */


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

#endif		/* _DRIVER_STM32_H_ */
