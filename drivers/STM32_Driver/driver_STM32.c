/** ____________________________________________________________________
 *
 *	@file		driver_STM32.c
 *
 *	@brief 		STM32 driver source file
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

#include "driver_STM32.h"


/**	@addtogroup	STM32_Driver
 *	@{
 */
/**	@brief	Initializes the driver object from GeneralSBGC_t
 *
 *	@param	*Driver - main hardware driver object
 *	@param	__UART_STRUCT - (aka *uart) user defined UART object
 *	@param	__TIMER_STRUCT - (aka *tim) user defined timer object
 */
void DriverInit (void *Driver, __UART_STRUCT, __TIMER_STRUCT)
{
	Driver_t *drv = (Driver_t*)Driver;

	drv->tim = tim;
	drv->timCount = 0;


	drv->uart = uart;

	#ifndef STM32_HAL_DMA_UART
		ClearTxBuff(drv);
	#endif

	ClearRxBuff(drv);

	#if defined (STM32_HAL_NVIC_UART) || defined (STM32_LL_NVIC_UART)
	/* UART Interrupts executable code */

		DISABLE_UART_CR1_TCIE(drv->uart);
		ENABLE_UART_CR1_RXNEIE(drv->uart);
		DISABLE_UART_CR1_IDLEIE(drv->uart);

	#elif defined (STM32_HAL_DMA_UART)
	/* UART HAL DMA executable code */

		HAL_UART_Receive_DMA(drv->uart, drv->RxBuffer, RX_BUFFER_SIZE);

	#elif defined (STM32_LL_DMA_UART)
	/* UART LL DMA executable code */

		/* Tx Init */
		LL_USART_EnableDMAReq_TX(SBGC_SERIAL_PORT);
		LL_DMA_EnableIT_TC(DMA_UART_TX, DMA_UART_TX_STREAM);

		LL_DMA_ConfigAddresses(DMA_UART_TX, DMA_UART_TX_STREAM,
							   (ui32)drv->TxBuffer,
							   LL_USART_DMA_GetRegAddr(SBGC_SERIAL_PORT, LL_USART_DMA_REG_DATA_TRANSMIT),
							   LL_DMA_GetDataTransferDirection(DMA_UART_TX, DMA_UART_TX_STREAM));

		/* Rx Init */
		LL_USART_EnableDMAReq_RX(SBGC_SERIAL_PORT);
		LL_DMA_EnableIT_TC(DMA_UART_RX, DMA_UART_RX_STREAM);

		LL_DMA_ConfigAddresses(DMA_UART_RX, DMA_UART_RX_STREAM,
							   LL_USART_DMA_GetRegAddr(SBGC_SERIAL_PORT, LL_USART_DMA_REG_DATA_RECEIVE),
							   (ui32)drv->RxBuffer,
							   LL_DMA_GetDataTransferDirection(DMA_UART_RX, DMA_UART_RX_STREAM));

		LL_DMA_DisableStream(DMA_UART_RX, DMA_UART_RX_STREAM);
		LL_DMA_SetDataLength(DMA_UART_RX, DMA_UART_RX_STREAM, RX_BUFFER_SIZE);
		LL_DMA_EnableStream(DMA_UART_RX, DMA_UART_RX_STREAM);

	#endif


	START_TIMER(drv->tim);
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														 Timer Functions
 */
/**	@brief	Gets current system time in milliseconds
 *
 *	@param	*Driver - main hardware driver object
 *
 *	@return	Current time
 */
ui32 GetTimeMs (void *Driver)
{
	Driver_t *drv = (Driver_t*)Driver;

	return drv->timCount;
}


/**	@brief	Timer interrupts handler
 *
 *	@param	*Driver - main hardware driver object
 */
void TimerDRV_CallBack (void *Driver)
{
	Driver_t *drv = (Driver_t*)Driver;

	drv->timCount++;

	#ifndef HAL_TIM_MODULE_ENABLED
		LL_TIM_ClearFlag_UPDATE(drv->tim);
	#endif
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *															Tx Functions
 */
/**	@brief	Sends an amount of data to the Tx ring buffer
 *
 *	@param	*Driver - main hardware driver object
 *	@param	*data - transferred data
 *	@param	size - size of transferred data
 *
 *	@return	Tx overflow status (1 - ERROR | 0 - OK)
 */
ui8 UartTransmitData (void *Driver, ui8 *data, ui16 size)
{
	Driver_t *drv = (Driver_t*)Driver;

	#if defined (STM32_HAL_NVIC_UART) || defined (STM32_LL_NVIC_UART)
	/* UART Interrupts executable code */

		/* Free space check */
		ui16 txHead = drv->TxHead;
		ui16 txTail = drv->TxTail;

		ui16 count = 0;
		while (txHead != txTail)
		{
			if (!txHead)
				txHead = TX_BUFFER_SIZE;

			txHead--;
			count++;
		}

		if (TX_BUFFER_SIZE - count < size)
		{
			/* - - - - User TxBuffer Overflow Handler - - - - -*/

			/* - - - - - - - - - - - - - - - - - - - - - - - - */
			return 1;
		}

		count = 0;
		while (count < size)
		{
			drv->TxBuffer[drv->TxHead++] = data[count++];

			if (drv->TxHead >= TX_BUFFER_SIZE)
				drv->TxHead = 0;
		}

		ENABLE_UART_CR1_TCIE(drv->uart);  // Enable transfer completion interrupts

		return 0;

	#elif defined (STM32_HAL_DMA_UART)
	/* UART DMA executable code */

		HAL_UART_Transmit_DMA(drv->uart, data, size);

		return 0;

	#elif defined (STM32_LL_DMA_UART)

		memcpy(drv->TxBuffer, data, size);

		LL_DMA_DisableStream(DMA_UART_TX, DMA_UART_TX_STREAM);
		LL_DMA_SetDataLength(DMA_UART_TX, DMA_UART_TX_STREAM, size);
		LL_DMA_EnableStream(DMA_UART_TX, DMA_UART_TX_STREAM);

		return 0;

	#endif
}


#if defined (STM32_HAL_NVIC_UART) || defined (STM32_LL_NVIC_UART)
/* UART Interrupts executable code */

	/**	@brief	UART transfer completion interrupts handler
	 *
	 *	@param	*Driver - main hardware driver object
	 */
	void UART_DRV_TxCallBack (void *Driver)
	{
		Driver_t *drv = (Driver_t*)Driver;

		WRITE_UART_BYTE(drv->uart, drv->TxBuffer[drv->TxTail++] & (ui32)0xFF);

		if (drv->TxTail == TX_BUFFER_SIZE)
			drv->TxTail = 0;

		if (drv->TxTail == drv->TxHead)
		{
			DISABLE_UART_CR1_TCIE(drv->uart);  // Disable transmission complete interrupts

			/*  - - - - User Transmit-Complete Handler - - - - */

			/* - - - - - - - - - - - - - - - - - - - - - - - - */
		}
	}

#endif


/**	@brief	Service Tx buffer cleaner
 *
 *	@param	*Driver - main hardware driver object
 */
void ClearTxBuff (void *Driver)
{
	#if defined (STM32_HAL_NVIC_UART) || defined (STM32_LL_NVIC_UART)
	/* UART Interrupts executable code */

		Driver_t *drv = (Driver_t*)Driver;

		memset(drv->TxBuffer, 0, TX_BUFFER_SIZE);
		drv->TxTail = 0;
		drv->TxHead = 0;

	#elif defined (STM32_LL_DMA_UART)
	/* UART LL DMA executable code */

		Driver_t *drv = (Driver_t*)Driver;

		memset(drv->TxBuffer, 0, TX_BUFFER_SIZE);
		drv->TxTail = 0;
		drv->TxHead = 0;

	#endif
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *															Rx Functions
 */
/**	@brief	Returns the number of available bytes
 *
 *	@param	*Driver - main hardware driver object
 *
 *	@return	Number of available bytes (0xFFFF - overflow error)
 */
ui16 GetAvailableBytes (void *Driver)
{
	Driver_t *drv = (Driver_t*)Driver;

	#if defined (STM32_HAL_NVIC_UART) || defined (STM32_LL_NVIC_UART)
	/* UART Interrupts executable code */

		if (drv->RxOverflowFlag)
			return 0xFFFF;

		ui16 rxHead = drv->RxHead;
		ui16 rxTail = drv->RxTail;

		ui16 count = 0;
		while (rxHead != rxTail)
		{
			if (!rxHead)
				rxHead = RX_BUFFER_SIZE;

			rxHead--;
			count++;
		}

		return count;

	#elif defined (STM32_HAL_DMA_UART) || defined (STM32_LL_DMA_UART)
	/* UART DMA executable code */

		drv->RxHead = RX_BUFFER_SIZE - GET_DMA_RX_COUNTER(DMA_UART_RX);
		return (drv->RxHead - drv->RxTail) & (RX_BUFFER_SIZE - 1);

	#endif
}


/**	@brief	Receives byte from the Rx ring buffer
 *
 *	@param	*Driver - main hardware driver object
 *	@param	*data - data buffer
 *
 *	@return	Receipt status (0 - receiving in progress | 1 - receive completed)
 */
ui8 UartReceiveByte (void *Driver, ui8 *data)
{
	Driver_t *drv = (Driver_t*)Driver;

	#if defined (STM32_HAL_NVIC_UART) || defined (STM32_LL_NVIC_UART)
	/* UART Interrupts executable code */

		if (drv->RxTail == drv->RxHead)
		{
			/* - - - - User Receive-Complete Handler - - - - - */

			/* - - - - - - - - - - - - - - - - - - - - - - - - */
			return 1;
		}

		*data = drv->RxBuffer[drv->RxTail++];

		if (drv->RxTail >= RX_BUFFER_SIZE)
		   drv->RxTail = 0;

		if (drv->RxOverflowFlag == 1)  // Reset the overflow flag
			drv->RxOverflowFlag = 0;

		return 0;  // Rx ring buffer isn't empty

	#elif defined (STM32_HAL_DMA_UART) || defined (STM32_LL_DMA_UART)
	/* UART DMA executable code */

		if (GetAvailableBytes(drv) == 0)
			return 1;

		*data = drv->RxBuffer[drv->RxTail];

		if (drv->RxTail != drv->RxHead)
		{
			drv->RxTail++;
			drv->RxTail &= (RX_BUFFER_SIZE - 1);
		}

		return 0;

	#endif
}


#if defined (STM32_HAL_NVIC_UART) || defined (STM32_LL_NVIC_UART)
/* UART Interrupts executable code */

	/**	@brief	UART receive completion interrupts handler
	 *
	 *	@param	*Driver - main hardware driver object
	 */
	void UART_DRV_RxCallBack (void *Driver)
	{
		Driver_t *drv = (Driver_t*)Driver;

		if ((drv->RxHead - drv->RxTail == RX_BUFFER_SIZE - 1) ||
			(drv->RxTail - drv->RxHead == 1))
		{
			/*  - - - - User RxBuffer Overflow Handler - - - - */

			/* - - - - - - - - - - - - - - - - - - - - - - - - */

			(void)READ_UART_BYTE(drv->uart);  // Prevent overflow error (USART_ISR_ORE)

			if (drv->RxOverflowFlag == 0)  // Set the overflow flag
				drv->RxOverflowFlag = 1;

			return;
		}

		drv->RxBuffer[drv->RxHead++] = READ_UART_BYTE(drv->uart);

		if (drv->RxHead >= RX_BUFFER_SIZE)
			drv->RxHead = 0;
	}

#endif


/**	@brief	Service Rx buffer cleaner
 *
 *	@param	*Driver - main hardware driver object
 */
void ClearRxBuff (void *Driver)
{
	Driver_t *drv = (Driver_t*)Driver;

	#if defined (STM32_HAL_NVIC_UART) || defined (STM32_LL_NVIC_UART)
	/* UART Interrupts executable code */

		memset(drv->RxBuffer, 0, RX_BUFFER_SIZE);
		drv->RxTail = 0;
		drv->RxHead = 0;
		drv->RxOverflowFlag = 0;

	#elif defined (STM32_HAL_DMA_UART) || defined (STM32_LL_DMA_UART)
	/* UART DMA executable code */

		memset(drv->RxBuffer, 0, RX_BUFFER_SIZE);
		drv->RxTail = 0;
		drv->RxHead = 0;
		drv->RxOverflowFlag = 0;

	#endif
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														 Debug Functions
 */
/**	@brief	Sends debug data
 *
 *	@param	*data - debug data
 *	@param	length - size of debug data
 */
void UartTransmitDebugData (char *data, ui16 length)
{
	#if defined (STM32_HAL_NVIC_UART) || defined (STM32_HAL_DMA_UART)
	/* UART HAL executable code */

		HAL_UART_Transmit(DEBUG_SERIAL_PORT, (ui8*)data, length, 100);

	#elif defined (STM32_LL_NVIC_UART) || defined (STM32_LL_DMA_UART)
	/* UART LL executable code */

		ui16 count = 0;
		while (count < length)
		{
			while (!LL_USART_IsActiveFlag_TXE(DEBUG_SERIAL_PORT))
				;

			LL_USART_TransmitData8(DEBUG_SERIAL_PORT, data[count++]);
		}

	#endif
}
/**	@}
 */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
