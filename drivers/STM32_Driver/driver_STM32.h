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
 *	Copyright © 2022 BaseCam Electronics™.</h3></center>
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

#include	"usart.h"
#include	"tim.h"
#include	"string.h"
#include	"stdlib.h"

#ifndef		SHORT_TYPE_NAMES
#define		SHORT_TYPE_NAMES
	#if defined	__x86_64__
		#define	_long__
		#define	_L32__
	#else
		#define	_long__				long
	#endif

	typedef	unsigned char			ui8;
	typedef	unsigned short			ui16;
	typedef	_long__ unsigned int	ui32;

	typedef	signed char				i8;
	typedef	short signed int		i16;
	typedef	_long__ signed int		i32;
#endif


/**	@addtogroup	STM32_Driver
 *	@{
 */
/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 						 Hardware Macros & Constants
 */
/*				   ### Timer ###				  */
#ifdef 		HAL_TIM_MODULE_ENABLED
	/*  - - - - User Defined Parameters - - - - - */
	#define INTERNAL_MAIN_TIMER	&htim2				/*!<  HAL User defined timer object. Each SBGC32 device has its own self timer		*/
	/*  - - - - - - - - - - - - - - - - - - - - - */

	#define	__TIMER_STRUCT		TIM_HandleTypeDef *tim

	#define	START_TIMER(TIM)	HAL_TIM_Base_Start_IT(TIM);

	#define	GET_FLAG_TIM_SR_UIF(TIM)		__HAL_TIM_GET_FLAG(TIM, TIM_FLAG_UPDATE)
	#define	GET_FLAG_TIM_DIER_UIE(TIM)		__HAL_TIM_GET_IT_SOURCE(TIM, TIM_FLAG_UPDATE)
#else		/* LL_TIM */
	/*  - - - - User Defined Parameters - - - - - */
	#define INTERNAL_MAIN_TIMER TIM2				/*!<  LL User defined timer object. Each SBGC32 device has its own self timer		*/
	/*  - - - - - - - - - - - - - - - - - - - - - */

	#define	__TIMER_STRUCT		TIM_TypeDef *tim

	#define	START_TIMER(TIM)	LL_TIM_EnableIT_UPDATE(TIM);\
								LL_TIM_EnableCounter(TIM)

	#define	GET_FLAG_TIM_SR_UIF(TIM)		LL_TIM_IsActiveFlag_UPDATE(TIM)
	#define	GET_FLAG_TIM_DIER_UIE(TIM)		LL_TIM_IsEnabledIT_UPDATE(TIM)
#endif

/*				   ### UART ###					  */
#ifdef 		HAL_UART_MODULE_ENABLED
	/*  - - - - User Defined Parameters - - - - - */
	#define SBGC_SERIAL_PORT	&huart1				/*!<  HAL User defined UART object. Used to communicate with SBGC32 device 			*/
	#define DEBUG_SERIAL_PORT	&huart2				/*!<  HAL User defined UART object. Used to print debug data						*/
	/*  - - - - - - - - - - - - - - - - - - - - - */

	#define	__UART_STRUCT		UART_HandleTypeDef *uart

	/*			   ### ATTENTION! ###			  */
	/* If your STM32 device doesn't have TDR and
	   RDR, please change them to DR */
	#define	WRITE_UART_BYTE(UART, DATA)		((UART)->Instance->TDR = DATA)
	#define READ_UART_BYTE(UART)			(ui8)(READ_BIT((UART)->Instance->RDR, USART_RDR_RDR) & 0xFFU)
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
#else		/* LL_UART */
	/*  - - - - User Defined Parameters - - - - - */
	#define SBGC_SERIAL_PORT    USART1				/*!<  LL User defined UART object. Used to communicate with SBGC32 device 			*/
	#define DEBUG_SERIAL_PORT   USART2				/*!<  LL User defined UART object. Used to print debug data							*/
	/*  - - - - - - - - - - - - - - - - - - - - - */

	#define __UART_STRUCT		USART_TypeDef *uart

	#define	WRITE_UART_DATA(UART, DATA)		LL_USART_TransmitData8(UART, DATA)
	#define READ_UART_DATA(UART)			LL_USART_ReceiveData8(UART)
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
#endif

/*				   ### Other ###				  */
/*  - - - - - User Defined Parameters - - - - - - */
#define		TX_BUFFER_SIZE			256				/*!<  256 Min --> 65534 Max															*/
#define		RX_BUFFER_SIZE			256				/*!<  256 Min --> 65534 Max															*/
/*  - - - - - - - - - - - - - - - - - - - - - - - */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									Hardware Objects
 */
/**	@brief	General driver structure
 */
typedef struct
{
	/* Timer */
	ui32			timCount;						/*!<  Current system time variable. Units: ms										*/

	__TIMER_STRUCT;									/*!<  Timer object																	*/

	/* UART */
	ui8		TxBuffer [TX_BUFFER_SIZE];				/*!<  UART Tx ring buffer															*/
	ui16	TxTail;									/*!<  UART Tx ring buffer tail point												*/
	ui16	TxHead;									/*!<  UART Tx ring buffer head point												*/

	ui8		RxBuffer [RX_BUFFER_SIZE];				/*!<  UART Rx ring buffer															*/
	ui16	RxTail;									/*!<  UART Rx ring buffer tail point												*/
	ui16	RxHead;									/*!<  UART Rx ring buffer head point												*/
	ui8		RxOverflowFlag;							/*!<  UART Rx ring buffer overflow flag												*/

	__UART_STRUCT;									/*!<  UART communication object														*/

}			Driver_t;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								 Function Prototypes
 */
void DriverInit (void *Driver, __UART_STRUCT, __TIMER_STRUCT);

ui32 GetTimeMs (void *Driver);
void TimerDRV_CallBack (void *Driver);

ui8 UartTransmitData (void *Driver, ui8 *data, ui16 size);
void UART_DRV_TxCallBack (void *Driver);
void ClearTxBuff (void *Driver);

ui16 GetAvailableBytes (void *Driver);
ui8 UartReceiveByte (void *Driver, ui8 *data);
void UART_DRV_RxCallBack (void *Driver);
void ClearRxBuff (void *Driver);

void UartTransmitDebugData (char *data, ui16 length);
/**	@}
 */

/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

#endif		/* _DRIVER_STM32_H_ */
