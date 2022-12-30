/** ____________________________________________________________________
 *
 * 	@file		driver_Arduino.h
 *
 *	@brief 		Arduino driver header file
 *
 *				<center><a href="https://www.basecamelectronics.com">
 *				www.basecamelectronics.com</a>
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
/** ____________________________________________________________________
 *
 * 	@defgroup	ArduinoDriver Arduino Driver
 *	@ingroup	Drivers
 *		@brief	Arduino Driver Module
 *  ____________________________________________________________________
 */

#ifndef     _DRIVER_ARDUINO_H_
#define     _DRIVER_ARDUINO_H_

#include    <Arduino.h>

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
	typedef _long__ unsigned int	ui32;

	typedef	signed char				i8;
	typedef	short signed int		i16;
	typedef	_long__ signed int		i32;
#endif


/**	@addtogroup	ArduinoDriver
 *	@{
 */
/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 				                  Hardware Constants
 */
/*				### ATTENTION! ###				*/
/* SERIAL_TX_BUFFER_SIZE and SERIAL_RX_BUFFER_SIZE
   in the "HardwareSerial.h" library must be fixed
   to 256 value */
#define 	SERIAL0_RX_PIN			0
#define 	SERIAL0_TX_PIN			1

#define 	SERIAL1_TX_PIN			18
#define 	SERIAL1_RX_PIN			19

#define 	SERIAL2_TX_PIN			16
#define 	SERIAL2_RX_PIN			17

#define 	SERIAL3_TX_PIN			14
#define 	SERIAL3_RX_PIN			15

#define     SBGC_SERIAL_PORT        Serial2
#define     DEBUG_SERIAL_PORT       Serial

#define     SBGC_SERIAL_SPEED       115200
#define     DEBUG_SERIAL_SPEED      9600


#define		DELAY_MS_(ms)			delay(ms)				

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								 Function Prototypes
 */
ui32 GetTimeMs (void *Driver);

ui8 UartTransmitData (void *Driver, ui8 *data, ui16 size);
ui16 GetAvailableBytes (void *Driver);
ui8 UartReceiveByte (void *Driver, ui8 *data);

void UartTransmitDebugData (char *data, ui16 length);
/**	@}
 */

#endif      /* _DRIVER_ARDUINO_H_ */
