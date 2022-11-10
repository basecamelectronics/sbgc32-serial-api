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
/*  - - - - - User Defined Parameters - - - - - - */
#define		STM32_HAL_NVIC_UART						/*!<  UART driver works with NVIC through HAL										*/
//#define		STM32_LL_NVIC_UART						/*!<  UART driver works with NVIC through LL										*/
//#define		STM32_HAL_DMA_UART						/*!<  UART driver works with DMA through HAL										*/
//#define		STM32_LL_DMA_UART						/*!<  UART driver works with DMA through LL											*/

#define		STM32_HAL_TIMER							/*!<  Timer driver works with NVIC through HAL										*/
//#define		STM32_LL_TIMER							/*!<  Timer driver works with NVIC through LL										*/
/*  - - - - - - - - - - - - - - - - - - - - - - - */


/*				   ### Timer ###				  */
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

#if defined (STM32_HAL_TIMER)
	/*  - - - - User Defined Parameters - - - - - */
	#define INTERNAL_MAIN_TIMER	&htim2				/*!<  HAL User defined timer object. Each SBGC32 device has its own self timer		*/
	/*  - - - - - - - - - - - - - - - - - - - - - */

	#define	__TIMER_STRUCT		TIM_HandleTypeDef *tim

	#define	START_TIMER(TIM)	HAL_TIM_Base_Start_IT(TIM);

	#define	GET_FLAG_TIM_SR_UIF(TIM)		__HAL_TIM_GET_FLAG(TIM, TIM_FLAG_UPDATE)
	#define	GET_FLAG_TIM_DIER_UIE(TIM)		__HAL_TIM_GET_IT_SOURCE(TIM, TIM_FLAG_UPDATE)

#elif defined (STM32_LL_TIMER)
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
/**	@verbatim

	*** UART by means of NVIC: ***
	==============================

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


	*** UART by means of DMA with LL: ***
	=====================================

	Copy this code into the DMAx_Streamx_IRQHandler()
	functions in the stm32XXxx_it.c file:

	if (GET_FLAG_DMA_HISR_TC_TX)
		CLEAR_DMA_TC_TX;

	- for DMA UART Tx channel.

	if (GET_FLAG_DMA_HISR_TC_RX)
		CLEAR_DMA_TC_RX;

	- for DMA UART Rx channel.

	Note: Be careful with CubeMX code generator.
	It may to create the MX_DMA_Init() function under
	the MX_USARTx_Init() function and then you will be
	need to lift it above. Otherwise this program
	will not work

	@endverbatim
 */

#if defined (STM32_HAL_NVIC_UART)
	/*  - - - - User Defined Parameters - - - - - */
	#define SBGC_SERIAL_PORT	&huart1				/*!<  HAL User defined UART object. Used to communicate with SBGC32 device 			*/
	#define DEBUG_SERIAL_PORT	&huart2				/*!<  HAL User defined UART object. Used to print debug data						*/
	/*  - - - - - - - - - - - - - - - - - - - - - */

	#define	__UART_STRUCT		UART_HandleTypeDef *uart

	/*			   ### ATTENTION! ###			  */
	/* If your STM32 device doesn't have TDR and
	   RDR, please change them to DR */
	#define	WRITE_UART_BYTE(UART, BYTE)		((UART)->Instance->TDR = BYTE)
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

#elif defined (STM32_LL_NVIC_UART)
	/*  - - - - User Defined Parameters - - - - - */
	#define SBGC_SERIAL_PORT    USART1				/*!<  LL User defined UART object. Used to communicate with SBGC32 device 			*/
	#define DEBUG_SERIAL_PORT   USART2				/*!<  LL User defined UART object. Used to print debug data							*/
	/*  - - - - - - - - - - - - - - - - - - - - - */

	#define __UART_STRUCT		USART_TypeDef *uart

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

#elif defined (STM32_HAL_DMA_UART)
	/*  - - - - User Defined Parameters - - - - - */
	#define SBGC_SERIAL_PORT	&huart1				/*!<  HAL User defined UART object. Used to communicate with SBGC32 device 			*/
	#define DEBUG_SERIAL_PORT	&huart2				/*!<  HAL User defined UART object. Used to print debug data						*/

	/** LL User defined DMA object. Used to communicate with SBGC32 device */
	#define	DMA_UART_RX			(SBGC_SERIAL_PORT)->hdmarx
	/*  - - - - - - - - - - - - - - - - - - - - - */

	#define	__UART_STRUCT		UART_HandleTypeDef *uart

	#define	GET_DMA_RX_COUNTER(DMAX)		__HAL_DMA_GET_COUNTER(DMAX)

#elif defined (STM32_LL_DMA_UART)
	/*  - - - - User Defined Parameters - - - - - */
	#define SBGC_SERIAL_PORT    USART1				/*!<  LL User defined UART object. Used to communicate with SBGC32 device 			*/
	#define DEBUG_SERIAL_PORT   USART2				/*!<  LL User defined UART object. Used to print debug data							*/

	#define	DMA_UART_TX			DMA2				/*!<  LL User defined DMA object. Used to communicate with SBGC32 device 			*/
	#define	DMA_UART_RX			DMA2				/*!<  LL User defined DMA object. Used to communicate with SBGC32 device 			*/
	#define	DMA_UART_TX_STREAM	LL_DMA_STREAM_7		/*!<  LL User defined DMA channel object. Used to communicate with SBGC32 device 	*/
	#define	DMA_UART_RX_STREAM	LL_DMA_STREAM_2		/*!<  LL User defined DMA channel object. Used to communicate with SBGC32 device 	*/

	/** Appointed in accordance with DMA_UART_TX_STREAM channel (TCx) */
	#define	CLEAR_DMA_TC_TX		LL_DMA_ClearFlag_TC7(DMA_UART_TX)

	/** Appointed in accordance with DMA_UART_RX_STREAM channel (TCx) */
	#define	CLEAR_DMA_TC_RX		LL_DMA_ClearFlag_TC2(DMA_UART_RX)

	/** Appointed in accordance with DMA_UART_TX_STREAM channel (TCx) */
	#define	GET_FLAG_DMA_HISR_TC_TX			LL_DMA_IsActiveFlag_TC7(DMA_UART_TX)

	/** Appointed in accordance with DMA_UART_RX_STREAM channel (TCx) */
	#define	GET_FLAG_DMA_HISR_TC_RX			LL_DMA_IsActiveFlag_TC2(DMA_UART_RX)
	/*  - - - - - - - - - - - - - - - - - - - - - */

	#define __UART_STRUCT		USART_TypeDef *uart

	#define	GET_DMA_RX_COUNTER(DMAX)		LL_DMA_GetDataLength(DMAX, DMA_UART_RX_STREAM)
#endif

#if defined (STM32_HAL_NVIC_UART) || defined (STM32_LL_NVIC_UART) || defined (STM32_LL_DMA_UART)
	/*				 ### Other ###				  */
	/*  - - - - User Defined Parameters - - - - - */
	#define		TX_BUFFER_SIZE			256			/*!<  256 Min --> 65534 Max															*/
#endif

	#define		RX_BUFFER_SIZE			256			/*!<  256 Min --> 65534 Max															*/
	/*  - - - - - - - - - - - - - - - - - - - - - */


#if defined (USE_HAL_DRIVER)
	#define	DELAY_MS(ms)			HAL_Delay(ms)
#elif defined (USE_FULL_LL_DRIVER)
	#define	DELAY_MS(ms)			LL_mDelay(ms)
#endif


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
	#if defined(STM32_HAL_NVIC_UART) || defined (STM32_LL_NVIC_UART) || defined (STM32_LL_DMA_UART)

		ui8		TxBuffer [TX_BUFFER_SIZE];			/*!<  UART Tx ring buffer															*/
		ui16	TxTail;								/*!<  UART Tx ring buffer tail point. Not used in DMA LL mode						*/
		ui16	TxHead;								/*!<  UART Tx ring buffer head point. Not used in DMA LL mode						*/

	#endif

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

#if defined(STM32_HAL_NVIC_UART) || defined (STM32_LL_NVIC_UART)
	void UART_DRV_TxCallBack (void *Driver);
#endif

void ClearTxBuff (void *Driver);

ui16 GetAvailableBytes (void *Driver);
ui8 UartReceiveByte (void *Driver, ui8 *data);

#if defined(STM32_HAL_NVIC_UART) || defined (STM32_LL_NVIC_UART)
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
