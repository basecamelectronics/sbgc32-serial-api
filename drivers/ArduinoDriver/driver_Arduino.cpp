/** ____________________________________________________________________
 *
 * 	@file		driver_Arduino.c
 *
 *	@brief 		Arduino driver source file
 *	____________________________________________________________________
 *
 *	@attention	<center><h3>
 *	Copyright © 2023 BaseCam Electronics™.</h3></center>
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

#include "driver_Arduino.h"


/**	@addtogroup	ArduinoDriver
 *	@{
 */
/**	@brief	Gets current system time in milliseconds
 *
 *	@param	*Driver - main hardware driver object (here is just a stub)
 *
 *	@return	Current time
 */
ui32 GetTimeMs (void *Driver)
{
	return millis();
}


/**	@brief	Sends an amount of data to Arduino Tx ring buffer
 *
 *	@param	*Driver - main hardware driver object (here is just a stub)
 *	@param	*data - transferred data
 *	@param	size - size of transferred data
 *
 *	@return 0
 */
ui8 UartTransmitData (void *Driver, ui8 *data, ui16 size)
{
    SBGC_SERIAL_PORT.write(data, size);

    SBGC_SERIAL_PORT.flush();

	return 0;
}


/**	@brief	Returns the number of available bytes
 *
 *	@param	*Driver - main hardware driver object
 *
 *	@return	Number of available bytes (0xFFFF - overflow error)
 */
ui16 GetAvailableBytes (void *Driver)
{
	return SBGC_SERIAL_PORT.available();
}


/**	@brief	Receives byte from Arduino Rx ring buffer
 *
 *	@param	*Driver - main hardware driver object (here is just a stub)
 *	@param	*data - data buffer
 *
 *	@return	Receipt status (0 - receiving in progress | 1 - receive completed)
 */
ui8 UartReceiveByte (void *Driver, ui8 *data)
{ 
	if (SBGC_SERIAL_PORT.available() < 1)
		return 1;

	*data = SBGC_SERIAL_PORT.read();

	return 0;
}


/**	@brief	Sends debug data
 *
 *	@param	*data - debug data
 *	@param	length - size of debug data
 */
void UartTransmitDebugData (char *data, ui16 length)
{
    DEBUG_SERIAL_PORT.write(data, length);

    DEBUG_SERIAL_PORT.flush();
}
/**	@}
 */
