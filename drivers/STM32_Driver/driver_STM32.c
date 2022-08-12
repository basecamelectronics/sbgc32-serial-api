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

	ClearTxBuff(drv);
	ClearRxBuff(drv);

	DISABLE_UART_CR1_TCIE(drv->uart);
	ENABLE_UART_CR1_RXNEIE(drv->uart);
	DISABLE_UART_CR1_IDLEIE(drv->uart);


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
}


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

		/*  - - - - User Complete Transmit Handler - - - - */

		/* - - - - - - - - - - - - - - - - - - - - - - - - */
	}
}


/**	@brief	Service Tx buffer cleaner
 *
 *	@param	*Driver - main hardware driver object
 */
void ClearTxBuff (void *Driver)
{
	Driver_t *drv = (Driver_t*)Driver;

	memset(drv->TxBuffer, 0, TX_BUFFER_SIZE);
	drv->TxTail = 0;
	drv->TxHead = 0;
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

	if (drv->RxTail == drv->RxHead)
	{
		/* - - - - User Complete Receive Handler - - - - - */

		/* - - - - - - - - - - - - - - - - - - - - - - - - */
		return 1;
	}

	*data = drv->RxBuffer[drv->RxTail++];

	if (drv->RxTail >= RX_BUFFER_SIZE)
	   drv->RxTail = 0;

	if (drv->RxOverflowFlag == 1)  // Reset the overflow flag
		drv->RxOverflowFlag = 0;

	return 0;	// Rx ring buffer isn't empty
}


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

		(void)READ_UART_BYTE(drv->uart);  // Prevents overflow error (USART_ISR_ORE)

		if (drv->RxOverflowFlag == 0)  // Set the overflow flag
			drv->RxOverflowFlag = 1;

		return;
	}

	drv->RxBuffer[drv->RxHead++] = READ_UART_BYTE(drv->uart);

	if (drv->RxHead >= RX_BUFFER_SIZE)
		drv->RxHead = 0;
}


/**	@brief	Service Rx buffer cleaner
 *
 *	@param	*Driver - main hardware driver object
 */
void ClearRxBuff (void *Driver)
{
	Driver_t *drv = (Driver_t*)Driver;

	memset(drv->RxBuffer, 0, RX_BUFFER_SIZE);
	drv->RxTail = 0;
	drv->RxHead = 0;
	drv->RxOverflowFlag = 0;
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														 Debug Functions
 */
#ifdef HAL_UART_MODULE_ENABLED

	/**	@brief	Sends debug data
	 *
	 *	@param	*data - debug data
	 *	@param	length - size of debug data
	 */
	void UartTransmitDebugData (char *data, ui16 length)
	{
		HAL_UART_Transmit(DEBUG_SERIAL_PORT, (ui8*)data, length, 100);
	}

#else

	/**	@brief	Sends debug data
	 *
	 *	@param	*data - debug data
	 *	@param	length - size of debug data
	 */
	void UartTransmitDebugData (char *data, ui16 length)
	{
		ui16 count = 0;
		while (count < length)
		{
			while (!LL_USART_IsActiveFlag_TXE(DEBUG_SERIAL_PORT))
				;

			LL_USART_TransmitData8(DEBUG_SERIAL_PORT, data[count++]);
		}
	}

#endif
/**	@}
 */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
