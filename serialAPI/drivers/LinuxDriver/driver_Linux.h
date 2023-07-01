/** ____________________________________________________________________
 *
 * 	SBGC32 Serial API Library v1.0
 *
 * 	@file		driver_Linux.h
 *
 *	@brief		Linux OS driver header file
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
 * 	@defgroup	LinuxDriver Linux OS Driver
 *	@ingroup	Drivers
 *		@brief	Linux OS Driver Module
 *  ____________________________________________________________________
 */

#ifndef 	_DRIVER_LINUX_H_
#define 	_DRIVER_LINUX_H_

#ifdef 		__cplusplus
extern 		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include    "../../sbgc32.h"


#if (SBGC_USE_LINUX_DRIVER)

#include 		<sys/types.h>
#include 		<sys/stat.h>
#include 		<fcntl.h>
#include 		<sys/ioctl.h>
#include 		<unistd.h>
#include 		<termios.h>
#include 		<time.h>

/**	@addtogroup	LinuxDriver
 *	@{
 */
/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								  Hardware Constants
 */
#define     DELAY_MS_(ms)           usleep((ms) * 1000)


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 									Hardware Objects
 */
/**	@brief	General driver structure
 */
typedef struct
{
	char	*device;
	int		devFD;

}			Driver_t;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								 Function Prototypes
 */
void DriverInit (void **driver, const char *dev);

ui32 GetTimeMs (void *driver);

ui8 PortTransmitData (void *driver, ui8 *data, ui16 size);

ui16 GetAvailableBytes (void *driver);
ui8 PortReceiveByte (void *driver, ui8 *data);

void PrintDebugData (char *data, ui16 length);
/**	@}
 */

#endif		/* SBGC_USE_LINUX_DRIVER */


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef 		__cplusplus
			}
#endif

#endif 		/* _DRIVER_LINUX_H_ */
