/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.1
 *
 *	@file		sbgc32.c
 *
 *	@brief		Assembly source file of the Library
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

#include "sbgc32.h"


/**	@addtogroup	Common
 *	@{
 */
/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@brief	Conducts to general initialization
 *
 *	@note	Quasi-private function. Don't use it
 *
 *	@param	*gSBGC - serial connection descriptor
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t PrivateSBGC32_EnterInit (sbgcGeneral_t *gSBGC)
{
	#if (SBGC_SEVERAL_DEVICES == sbgcOFF)

		#if (SBGC_USE_ARDUINO_DRIVER)

			SerialAPI_LinkDriver(gSBGC, DriverSBGC32_TxFuncTemp, DriverSBGC32_RxFuncTemp, DriverSBGC32_AvailableBytesFuncTemp,
								 DriverSBGC32_TxDebugFuncTemp, DriverSBGC32_GetTimeFuncTemp);

			DriverSBGC32_InitFuncTemp();

		#elif (SBGC_USE_LINUX_DRIVER)

			SerialAPI_LinkDriver(gSBGC, DriverSBGC32_PortTransmitData, DriverSBGC32_PortReceiveByte, DriverSBGC32_GetAvailableBytes,
								 DriverSBGC32_PrintDebugData, DriverSBGC32_GetTimeMs);

			DriverSBGC32_Init(&gSBGC->_ll->drv, SBGC_SERIAL_PORT, SBGC_SERIAL_SPEED);

		#elif (SBGC_USE_STM32_DRIVER)

			SerialAPI_LinkDriver(gSBGC, DriverSBGC32_UartTransmitData, DriverSBGC32_UartReceiveByte, DriverSBGC32_GetAvailableBytes,
								 DriverSBGC32_UartTransmitDebugData, DriverSBGC32_GetTimeMs);

			DriverSBGC32_Init(&gSBGC->_ll->drv, SBGC_SERIAL_PORT, SBGC_REFERENCE_TIMER);

		#endif
	#endif

	return SBGC32_SetupLibrary(gSBGC);
}


/**	@brief	General initialization function.
 *			Launches SBGC32 thread if OS support is on.
 *			Links embedded driver functions to the low-layer,
 *			sets library variables from configurations, gets
 *			firmware and hardware versions of the board
 *
 *	@pre	Connected SBGC32 device
 *
 *	@code

			// Link the library files
			#include "sbgc32.h"

			// Declare a general SBGC32 object
			sbgcGeneral_t SBGC32_Device;

			// Initialize the library
			SBGC32_Init(&SBGC32_Device);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_Init (sbgcGeneral_t *gSBGC)
{
	#if (!(SBGC_USE_ARDUINO_DRIVER || SBGC_USE_LINUX_DRIVER || SBGC_USE_STM32_DRIVER))

		/* Attention! When using a custom driver, use the SerialAPI_LinkDriver() and SBGC32_SetupLibrary function! */
		return sbgcCOMMAND_PARAM_ASSERT_ERROR;

	#endif

	#if (SBGC_USES_OS_SUPPORT)
		SystemSBGC32_Init(gSBGC);
	#else
		return PrivateSBGC32_EnterInit(gSBGC);
	#endif

	return sbgcCOMMAND_OK;
}


/**	@brief	Will be executed upon any error occurrence
 *
 *	@note	Weak function
 */
WEAK__ void SerialAPI_FatalErrorHandler (void)
{
	/* User common error handler */

	while (1);
}


/**	@brief	Called every time while waiting for
 *			sending/receiving a command
 *
 *	@note	Weak function
 *
 *	@note	Avoid spending much time in this function, as it's called
 *			on every serial data processing. Include only fast and
 *			non-blocking operations. Otherwise, overloading it
 *			may impact serial port performance
 *
 *	@param	*gSBGC - serial connection descriptor
 */
WEAK__ void SerialAPI_CommandWaitingHandler (sbgcGeneral_t *gSBGC)
{
	/* Any user actions while waiting */

	unused_(gSBGC);
}
/**	@}
 */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
