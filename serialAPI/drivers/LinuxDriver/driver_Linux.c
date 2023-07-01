/** ____________________________________________________________________
 *
 * 	SBGC32 Serial API Library v1.0
 *
 *	@file		driver_Linux.c
 *
 *	@brief 		Linux OS driver source file
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

#include "../../sbgc32.h"


#if (SBGC_USE_LINUX_DRIVER)

/**	@addtogroup	LinuxDriver
 *	@{
 */
/**	@brief	Initializes the driver object from GeneralSBGC_t
 *
 *	@param	**driver - main hardware driver object
 *	@param	*dev - path to a connected SBGC32 device
 */
void DriverInit (void **driver, const char *dev)
{
	*driver = malloc(sizeof(Driver_t));

	Driver_t *drv = (Driver_t*)(*driver);

	ui8 devNameLength = strlen(dev) + 1;
	drv->device = (char*)malloc(devNameLength);
	memcpy(drv->device, dev, devNameLength);

	drv->devFD = open(drv->device, O_RDWR | O_NOCTTY | O_NDELAY);

	if (drv->devFD == -1)
	{
		char errorStr [] = "Device not found!\n";
		PrintDebugData(errorStr, strlen(errorStr));
		return;
	}

	struct termios portConfigurations;

	tcgetattr(drv->devFD, &portConfigurations);

	cfsetispeed(&portConfigurations, B115200);
	cfsetospeed(&portConfigurations, B115200);

	portConfigurations.c_cflag &= ~(PARENB | PARODD | CSTOPB | CRTSCTS);
	portConfigurations.c_cflag |= CS8 | CREAD | CLOCAL;

	portConfigurations.c_iflag &= ~(IXON | IXOFF | IXANY | ICRNL);

	portConfigurations.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	portConfigurations.c_oflag &= ~OPOST;

	tcsetattr(drv->devFD, TCSANOW, &portConfigurations);
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														 Timer Functions
 */
/**	@brief	Gets current system time in milliseconds
 *
 *	@param	*driver - main hardware driver object
 *
 *	@return	Current time
 */
ui32 GetTimeMs (void *driver)
{
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);

	return ((spec.tv_sec & 0x000FFFFF) * 1000) + (spec.tv_nsec / 1.0e6);
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *															Tx Functions
 */
/**	@brief	Sends an amount of data to serial port
 *
 *	@param	*driver - main hardware driver object
 *	@param	*data - transferred data
 *	@param	size - size of transferred data
 *
 *	@return	0
 */
ui8 PortTransmitData (void *driver, ui8 *data, ui16 size)
{
	Driver_t *drv = (Driver_t*)driver;

	ui16 count = 0;
    while (count < size)
    {
		write(drv->devFD, &data[count], 1);
        count++;
    }

	return 0;
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *															Rx Functions
 */
/**	@brief	Returns the number of available bytes
 *
 *	@param	*driver - main hardware driver object
 *
 *	@return	Number of available bytes
 */
ui16 GetAvailableBytes (void *driver)
{
	Driver_t *drv = (Driver_t*)driver;

	ui16 bytes;
	ioctl(drv->devFD, FIONREAD, &bytes);
	return bytes;
}


/**	@brief	Receives byte from serial port
 *
 *	@param	*driver - main hardware driver object
 *	@param	*data - data buffer
 *
 *	@return	Receipt status (0 - receiving in progress | 1 - received)
 */
ui8 PortReceiveByte (void *driver, ui8 *data)
{
	Driver_t *drv = (Driver_t*)driver;

	if (!GetAvailableBytes(drv))
		return 1;

	read(drv->devFD, data, 1);

	return 0;
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														 Debug Functions
 */
/**	@brief	Prints debug data
 *
 *	@param	*data - debug data
 *	@param	length - size of debug data
 */
void PrintDebugData (char *data, ui16 length)
{
	ui16 count = 0;
	while (count < length)
		printf("%c", data[count++]);
}
/**	@}
 */

#endif /* SBGC_USE_LINUX_DRIVER */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
