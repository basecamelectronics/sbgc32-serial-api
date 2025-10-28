/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2
 *
 *	@file		driverArduino.h
 *
 *	@brief		Arduino driver header file
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
	fixed to 256 value working with Arduino boards

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

#define		SBGC_SERIAL_CONFIG		SERIAL_8N1

#if defined (ARDUINO_ARCH_ESP32)
	#define	SERIAL_TX_BUFFER_SIZE	256
	#define	SERIAL_RX_BUFFER_SIZE	256
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *											  Macros
 */
#define		sbgcDelay(ms)			delay(ms)
#define		sbgcGetTick()			millis()


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *					   Function Prototypes and Links
 */
typedef		void			(*sbgcArduinoInit_t)(void**, void*, unsigned long);
typedef		void			(*sbgcArduinoDeinit_t)(void**);


/**	@addtogroup	Arduino_Driver
 *	@{
 */
/**	@cond
 */
extern sbgcArduinoInit_t DriverSBGC32_Init;
void DriverSBGC32_Init__ (void **driver, void *serial, unsigned long serialSpeed);

extern sbgcArduinoDeinit_t DriverSBGC32_Deinit;
void DriverSBGC32_Deinit__ (void **driver);

extern sbgcGetTime_t DriverSBGC32_GetTimeMs;
sbgcTicks_t DriverSBGC32_GetTimeMs__ (void);

extern sbgcTx_t DriverSBGC32_TransmitData;
ui8 DriverSBGC32_TransmitData__ (void *driver, ui8 *data, ui16 size);

extern sbgcAvailableBytes_t DriverSBGC32_GetAvailableBytes;
ui16 DriverSBGC32_GetAvailableBytes__ (void *driver);

extern sbgcRx_t DriverSBGC32_ReceiveByte;
ui8 DriverSBGC32_ReceiveByte__ (void *driver, ui8 *data);

extern sbgcTxDebug_t DriverSBGC32_PrintDebugData;
void DriverSBGC32_PrintDebugData__ (char *data, ui16 length);
/**	@endcond
 */
/**	@}
 */

#endif /* SBGC_USE_ARDUINO_DRIVER */

#endif		/* DRIVERS_DRIVER_ARDUINO_H_ */
