/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.0
 *
 *	@file		driverArduino.cpp
 *
 *	@brief		Arduino driver source file
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

#include "../../sbgc32.h"


#if (SBGC_USE_ARDUINO_DRIVER)

/**	@addtogroup	Arduino_Driver
 *	@{
 */
/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														 Special Objects
 */
/**	@cond
 */
sbgcArduinoInit_t DriverSBGC32_InitFuncTemp = &DriverSBGC32_Init;
sbgcTx_t DriverSBGC32_TxFuncTemp = &DriverSBGC32_UartTransmitData;
sbgcRx_t DriverSBGC32_RxFuncTemp = &DriverSBGC32_UartReceiveByte;
sbgcTxDebug_t DriverSBGC32_TxDebugFuncTemp = &DriverSBGC32_UartTransmitDebugData;
sbgcAvailableBytes_t DriverSBGC32_AvailableBytesFuncTemp = &DriverSBGC32_GetAvailableBytes;
sbgcGetTime_t DriverSBGC32_GetTimeFuncTemp = &DriverSBGC32_GetTimeMs;
/**	@endcond
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@brief	Initialize the periphery
 */
void DriverSBGC32_Init (void)
{
	SBGC_SERIAL_PORT.begin(SBGC_SERIAL_SPEED);
	SBGC_DEBUG_SERIAL_PORT.begin(SBGC_DEBUG_SERIAL_SPEED);
}

/**	@brief	Gets current system time in milliseconds
 *
 *	@param	*driver - main hardware driver object (here is just a stub)
 *
 *	@return	Current time
 */
ui32 DriverSBGC32_GetTimeMs (void *driver)
{
	unused_(driver);

	return millis();
}


/**	@brief	Sends an amount of data to Arduino Tx ring buffer
 *
 *	@param	*driver - main hardware driver object (here is just a stub)
 *	@param	*data - transferred data
 *	@param	size - size of transferred data
 *
 *	@return Tx status
 */
ui8 DriverSBGC32_UartTransmitData (void *driver, ui8 *data, ui16 size)
{
	unused_(driver);

	if ((ui16)SBGC_SERIAL_PORT.availableForWrite() < size)
		return SBGC_DRV_TX_BUFF_OVERFLOW_FLAG;

    SBGC_SERIAL_PORT.write(data, size);

	return SBGC_DRV_TX_OK_FLAG;
}


/**	@brief	Returns the number of available bytes
 *
 *	@param	*driver - main hardware driver object (here is just a stub)
 *
 *	@return	Number of available bytes (0xFFFF - overflow error)
 */
ui16 DriverSBGC32_GetAvailableBytes (void *driver)
{
	unused_(driver);

	return SBGC_SERIAL_PORT.available();
}


/**	@brief	Receives byte from Arduino Rx ring buffer
 *
 *	@param	*driver - main hardware driver object (here is just a stub)
 *	@param	*data - data buffer
 *
 *	@return	Rx status
 */
ui8 DriverSBGC32_UartReceiveByte (void *driver, ui8 *data)
{
	unused_(driver);

	if (SBGC_SERIAL_PORT.available() < 1)
		return SBGC_DRV_RX_BUFF_EMPTY_FLAG;

	*data = SBGC_SERIAL_PORT.read();

	return SBGC_DRV_RX_BUSY_FLAG;
}


/**	@brief	Sends debug data
 *
 *	@param	*data - debug data
 *	@param	length - size of debug data
 */
void DriverSBGC32_UartTransmitDebugData (char *data, ui16 length)
{
	SBGC_DEBUG_SERIAL_PORT.write(data, length);

	SBGC_DEBUG_SERIAL_PORT.flush();
}
/**	@}
 */

#endif /* SBGC_USE_ARDUINO_DRIVER */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
