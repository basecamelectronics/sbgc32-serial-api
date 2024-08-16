/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.0
 *
 *	@file		driverLinux.h
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
/**	____________________________________________________________________
 *
 *	@defgroup	Linux_Driver Linux OS Driver
 *	@ingroup	Drivers
 *		@brief	Linux OS Driver Module
 *	____________________________________________________________________
 */

#ifndef		DRIVERS_DRIVER_LINUX_H_
#define		DRIVERS_DRIVER_LINUX_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../sbgc32.h"


#if (SBGC_USE_LINUX_DRIVER)

/**	@addtogroup	Linux_Driver
 *	@{
 */
/**	@verbatim

	### ATTENTION! ###

	The serial port must have extended rights:
	sudo chmod a+rwx /dev/ttyUSB0

	@endverbatim
 */
/**	@}
 */

#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<sys/ioctl.h>
#include	<unistd.h>
#include	<termios.h>
#include	<time.h>


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							Configuration Protection
 */
#ifndef SBGC_SERIAL_PORT
	#define	SBGC_SERIAL_PORT		"/dev/ttyUSB0"
#endif

#ifndef SBGC_SERIAL_SPEED
	#define	SBGC_SERIAL_SPEED		B115200
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								Macros and Constants
 */
#ifndef	sbgcDelay
	#define	sbgcDelay(tick)			usleep((tick) * 1000)
#endif

#ifndef sbgcGetTick
	#define sbgcGetTick()			DriverSBGC32_GetTimeMs(NULL)
#endif


#define 	SBGC_DRV_TX_BUFF_TOTAL_SIZE		4096


/**	@addtogroup	Linux_Driver
 *	@{
 */
/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									Hardware Objects
 */
/**	@brief	General driver structure
 */
typedef struct
{
	char	*device;
	int		devFD;

}			sbgcDriver_t;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								 Function Prototypes
 */
void DriverSBGC32_Init (void **driver, const char *dev, ui32 serialSpeed);

sbgcTicks_t DriverSBGC32_GetTimeMs (void *driver);

ui8 DriverSBGC32_PortTransmitData (void *driver, ui8 *data, ui16 size);
ui16 DriverSBGC32_GetAvailableBytes (void *driver);
ui8 DriverSBGC32_PortReceiveByte (void *driver, ui8 *data);

void DriverSBGC32_PrintDebugData (char *data, ui16 length);
/**	@}
 */

#endif /* SBGC_USE_LINUX_DRIVER */


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

#endif		/* DRIVERS_DRIVER_LINUX_H_ */
