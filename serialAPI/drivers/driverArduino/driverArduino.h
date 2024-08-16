/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.0
 *
 *	@file		driverArduino.h
 *
 *	@brief		Arduino driver header file
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
/**	____________________________________________________________________
 *
 *	@defgroup	Arduino_Driver Arduino Driver
 *	@ingroup	Drivers
 *		@brief	Arduino Driver Module
 *  ____________________________________________________________________
 */

#ifndef		DRIVERS_DRIVER_ARDUINO_H_
#define		DRIVERS_DRIVER_ARDUINO_H_

#include	"../../sbgc32.h"


#if (SBGC_USE_ARDUINO_DRIVER)

/**	@addtogroup	Arduino_Driver
 *	@{
 */
/**	@verbatim

	### ATTENTION! ###

	SERIAL_TX_BUFFER_SIZE and SERIAL_RX_BUFFER_SIZE
	in the "HardwareSerial.h" library must be
	fixed to 256 value

	@endverbatim
 */
/**	@}
 */

#include	<Arduino.h>


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							Configuration Protection
 */
#ifndef SBGC_SERIAL_PORT
	#define	SBGC_SERIAL_PORT		Serial1
#endif

#ifndef SBGC_DEBUG_SERIAL_PORT
	#define	SBGC_DEBUG_SERIAL_PORT	Serial
#endif

#ifndef SBGC_SERIAL_SPEED
	#define	SBGC_SERIAL_SPEED		115200
#endif

#ifndef SBGC_DEBUG_SERIAL_SPEED
	#define	SBGC_DEBUG_SERIAL_SPEED	115200
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *											  Macros
 */
#define		sbgcDelay(ms)			delay(ms)
#define		sbgcGetTick()			millis()


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *					   Function Prototypes and Links
 */
typedef		void		(*sbgcArduinoInit_t)(void);


/**	@addtogroup	Arduino_Driver
 *	@{
 */
/**	@cond
 */
extern sbgcArduinoInit_t DriverSBGC32_InitFuncTemp;
void DriverSBGC32_Init (void);

extern sbgcGetTime_t DriverSBGC32_GetTimeFuncTemp;
ui32 DriverSBGC32_GetTimeMs (void *driver);

extern sbgcTx_t DriverSBGC32_TxFuncTemp;
ui8 DriverSBGC32_UartTransmitData (void *driver, ui8 *data, ui16 size);

extern sbgcAvailableBytes_t DriverSBGC32_AvailableBytesFuncTemp;
ui16 DriverSBGC32_GetAvailableBytes (void *driver);

extern sbgcRx_t DriverSBGC32_RxFuncTemp;
ui8 DriverSBGC32_UartReceiveByte (void *driver, ui8 *data);

extern sbgcTxDebug_t DriverSBGC32_TxDebugFuncTemp;
void DriverSBGC32_UartTransmitDebugData (char *data, ui16 length);
/**	@endcond
 */
/**	@}
 */

#endif /* SBGC_USE_ARDUINO_DRIVER */

#endif		/* DRIVERS_DRIVER_ARDUINO_H_ */
