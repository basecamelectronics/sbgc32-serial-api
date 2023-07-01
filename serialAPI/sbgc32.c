/** ____________________________________________________________________
 *
 *	SBGC32 Serial API Library v1.0
 *
 * 	@file		sbgc32.c
 *
 *	@brief 		Assembly source file of the Library
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

#include "sbgc32.h"


/**	@addtogroup	Common
 *	@{
 */
/**	@brief	General initialization function.
 * 			Sets library variables from configurations
 *
 * 	@param	*generalSBGC - serial connection descriptor
 *
 *	@return	Communication status
 */
TxRxStatus_t SBGC32_Init (GeneralSBGC_t *generalSBGC)
{
	#if (SBGC_USE_ARDUINO_DRIVER)

		return SBGC32_ManualInit(generalSBGC, TxFuncTemp, RxFuncTemp, AvailableBytesFuncTemp,
								 TxDebugFuncTemp, GetTimeFuncTemp, sprintf, SBGC_PROTOCOL_V2);

	#elif (SBGC_USE_LINUX_DRIVER)

		DriverInit(&generalSBGC->Drv, SBGC_SERIAL_PORT);

		return SBGC32_ManualInit(generalSBGC, PortTransmitData, PortReceiveByte, GetAvailableBytes,
								 PrintDebugData, GetTimeMs, sprintf, SBGC_PROTOCOL_V2);

	#elif (SBGC_USE_STM32_DRIVER)

		DriverInit(&generalSBGC->Drv, SBGC_SERIAL_PORT, SBGC_REFERENCE_TIMER);

		return SBGC32_ManualInit(generalSBGC, UartTransmitData, UartReceiveByte, GetAvailableBytes,
								 UartTransmitDebugData, GetTimeMs, sprintf, SBGC_PROTOCOL_V2);

	#else
		#error "When using a custom driver, use the SBGC32_ManualInit() function!"
	#endif
}
/**	@}
 */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
