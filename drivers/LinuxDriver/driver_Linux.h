/** ____________________________________________________________________
 *
 * 	@file		driver_Linux.h
 *
 *	@brief 		Linux OS driver header file
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

#include 	<stdio.h>

#include 	<sys/types.h>
#include 	<sys/stat.h>
#include 	<fcntl.h>
#include 	<sys/ioctl.h>
#include 	<unistd.h>

#include 	<termios.h>
#include 	<time.h>

#include 	"string.h"
#include 	"stdlib.h"

#ifndef		SHORT_TYPE_NAMES
#define		SHORT_TYPE_NAMES
	#if defined __x86_64__
		#define	_long__
		#define	_L32__
	#else
		#define	_long__				long
	#endif

	typedef unsigned char			ui8;
	typedef unsigned short			ui16;
	typedef _long__ unsigned int	ui32;

	typedef signed char				i8;
	typedef short signed int		i16;
	typedef _long__ signed int		i32;
#endif


/**	@addtogroup	LinuxDriver
 *	@{
 */
/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								  Hardware Constants
 */
#define		__USB_ADDR				char dev [20]

/*  - - - - - User Defined Parameters - - - - - - */
/*		   ### !!! ATTENTION !!! ###		  */
/* 		 sudo chmod a+rwx /dev/ttyUSB0 		  */
#define 	SBGC_SERIAL_PORT    	"/dev/ttyUSB0"	/*!<  Path to a connected SBGC32 device												*/
/*  - - - - - - - - - - - - - - - - - - - - - - - */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 									Hardware Objects
 */
/**	@brief	General driver structure
 */
typedef struct
{
	char	device [20];
	int		devFD;

}			Driver_t;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								 Function Prototypes
 */
void DriverInit (void *Driver, __USB_ADDR);

ui32 GetTimeMs (void *Driver);

ui8 PortTransmitData (void *Driver, ui8 *data, ui16 size);

ui16 GetAvailableBytes (void *Driver);
ui8 PortReceiveByte (void *Driver, ui8 *data);

void PrintDebugData (char *data, ui16 length);
/**	@}
 */

/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef 		__cplusplus
			}
#endif

#endif 		/* _DRIVER_LINUX_H_ */
