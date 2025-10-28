/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2
 *
 *	@file		driverArduino.cpp
 *
 *	@brief		Arduino driver source file
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
/* Coating C++ driver functions into variables to use them in C */
sbgcArduinoInit_t DriverSBGC32_Init = &DriverSBGC32_Init__;
sbgcArduinoDeinit_t DriverSBGC32_Deinit = &DriverSBGC32_Deinit__;
sbgcGetTime_t DriverSBGC32_GetTimeMs = &DriverSBGC32_GetTimeMs__;
sbgcTx_t DriverSBGC32_TransmitData = &DriverSBGC32_TransmitData__;
sbgcAvailableBytes_t DriverSBGC32_GetAvailableBytes = &DriverSBGC32_GetAvailableBytes__;
sbgcRx_t DriverSBGC32_ReceiveByte = &DriverSBGC32_ReceiveByte__;
sbgcTxDebug_t DriverSBGC32_PrintDebugData = &DriverSBGC32_PrintDebugData__;
/**	@endcond
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@brief	Initializes the periphery
 */
void DriverSBGC32_Init__ (void **driver, void *serial, unsigned long serialSpeed)
{
	unused_(driver);
	unused_(serial);

	#if defined (ARDUINO_ARCH_ESP32)
		/* Configure buffers first */
		SBGC_SERIAL_PORT.setRxBufferSize(SBGC_ESP32_RX_BUFFER);
		SBGC_SERIAL_PORT.setTxBufferSize(SBGC_ESP32_TX_BUFFER);
	#endif

	/* Begin hardware serial; allow explicit pins or defaults (-1) */
	SBGC_SERIAL_PORT.begin(
		serialSpeed,
		SBGC_SERIAL_CONFIG
	);

	/* Start debug port if available */
	#if (SBGC_NEED_DEBUG)
		SBGC_DEBUG_SERIAL_PORT.begin(SBGC_DEBUG_SERIAL_SPEED);
	#endif
}


/**	@brief	Deinitializes the periphery
 *
 *	@param	**driver - main hardware driver object
 */
void DriverSBGC32_Deinit__ (void **driver)
{
	unused_(driver);

	SBGC_SERIAL_PORT.end();

	#if (SBGC_NEED_DEBUG)
		SBGC_DEBUG_SERIAL_PORT.end();
	#endif
}


/**	@brief	Gets current system time in milliseconds
 *
 *	@return	Current time
 */
sbgcTicks_t DriverSBGC32_GetTimeMs__ (void)
{
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
ui8 DriverSBGC32_TransmitData__ (void *driver, ui8 *data, ui16 size)
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
ui16 DriverSBGC32_GetAvailableBytes__ (void *driver)
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
ui8 DriverSBGC32_ReceiveByte__ (void *driver, ui8 *data)
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
void DriverSBGC32_PrintDebugData__ (char *data, ui16 length)
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
