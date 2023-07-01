/** ____________________________________________________________________
 *
 * 	SBGC32 Serial API Library v1.0
 *
 * 	@file		driver_Arduino.h
 *
 *	@brief 		Arduino driver header file
 *	____________________________________________________________________
 *
 *	@attention	<h3><center>
 *				Copyright © 2023 BaseCam Electronics™.<br>
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
/** ____________________________________________________________________
 *
 * 	@defgroup	ArduinoDriver Arduino Driver
 *	@ingroup	Drivers
 *		@brief	Arduino Driver Module
 *  ____________________________________________________________________
 */

#ifndef		_DRIVER_ARDUINO_H_
#define		_DRIVER_ARDUINO_H_

#include	"../../sbgc32.h"


#if (SBGC_USE_ARDUINO_DRIVER)

#include	<Arduino.h>

/**	@addtogroup	ArduinoDriver
 *	@{
 */
#define		SERIAL0_RX_PIN			0
#define		SERIAL0_TX_PIN			1

/* Arduino mega pins */
#define		SERIAL1_TX_PIN			18
#define		SERIAL1_RX_PIN			19

#define		SERIAL2_TX_PIN			16
#define		SERIAL2_RX_PIN			17

#define		SERIAL3_TX_PIN			14
#define		SERIAL3_RX_PIN			15

#define		DELAY_MS_(ms)			delay(ms)


extern TxFunc_t TxFuncTemp;
extern RxFunc_t RxFuncTemp;
extern TxDebugFunc_t TxDebugFuncTemp;
extern AvailableBytesFunc_t AvailableBytesFuncTemp;
extern GetTimeFunc_t GetTimeFuncTemp;


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

#endif		/* SBGC_USE_ARDUINO_DRIVER */

#endif      /* _DRIVER_ARDUINO_H_ */
