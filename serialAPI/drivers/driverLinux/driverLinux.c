/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2.1
 *
 *	@file		driverLinux.c
 *
 *	@brief		Linux OS driver source file
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

#include "../../sbgc32.h"


#if (SBGC_USE_LINUX_DRIVER)

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

/**	@addtogroup	Linux_Driver
 *	@{
 */
/**	@brief	Initializes the driver object of sbgcGeneral_t
 *
 *	@param	**driver - main hardware driver object
 *	@param	*dev - path to a connected SBGC32 device
 *	@param	serialSpeed - speed of the COM port
 */
void DriverSBGC32_Init (void **driver, const char *dev, unsigned long serialSpeed)
{
	*driver = sbgcMalloc(sizeof(sbgcDriver_t));

	sbgcDriver_t *drv = (sbgcDriver_t*)(*driver);

	ui8 devNameLength = strlen(dev) + 1;
	drv->device = (char*)sbgcMalloc(devNameLength);
	memcpy(drv->device, dev, devNameLength);

	drv->devFD = open(drv->device, O_RDWR | O_NOCTTY | O_NDELAY);

	if (drv->devFD == -1)
	{
		char errorStr [] = "Device not found!\n";
		DriverSBGC32_PrintDebugData(errorStr, strlen(errorStr));
		SerialAPI_FatalErrorHandler();
	}

	struct termios portConfigurations;

	tcgetattr(drv->devFD, &portConfigurations);

	cfsetispeed(&portConfigurations, serialSpeed);
	cfsetospeed(&portConfigurations, serialSpeed);

	portConfigurations.c_cflag &= ~(PARENB | PARODD | CSTOPB | CRTSCTS);
	portConfigurations.c_cflag |= CS8 | CREAD | CLOCAL;

	portConfigurations.c_iflag &= ~(IXON | IXOFF | IXANY | ICRNL);

	portConfigurations.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	portConfigurations.c_oflag &= ~OPOST;

	tcsetattr(drv->devFD, TCSANOW, &portConfigurations);
}


/**	@brief	Deinitializes the periphery
 *
 *	@param	**driver - main hardware driver object
 */
void DriverSBGC32_Deinit (void **driver)
{
	unused_(driver);
}


/**	@brief	Gets current system time in milliseconds
 *
 *	@return	Current time
 */
sbgcTicks_t DriverSBGC32_GetTimeMs (void)
{
	struct timespec spec;

	clock_gettime(CLOCK_REALTIME, &spec);

	return ((spec.tv_sec & 0x000FFFFF) * 1000) + (sbgcTicks_t)((double)spec.tv_nsec / 1.0e6);
}


/**	@brief	Sends an amount of data to serial port
 *
 *	@param	*driver - main hardware driver object
 *	@param	*data - transferred data
 *	@param	size - size of transferred data
 *
 *	@return	Tx status
 */
ui8 DriverSBGC32_TransmitData (void *driver, ui8 *data, ui16 size)
{
	sbgcDriver_t *drv = (sbgcDriver_t*)driver;

	int bytes;

	ioctl(drv->devFD, TIOCOUTQ, &bytes);

	if (((SBGC_DRV_TX_BUFF_TOTAL_SIZE - bytes) < size) || (bytes == -1))
		return SBGC_DRV_TX_BUFF_OVERFLOW_FLAG;

	write(drv->devFD, data, size);

	return SBGC_DRV_TX_OK_FLAG;
}


/**	@brief	Returns the number of available bytes
 *
 *	@param	*driver - main hardware driver object
 *
 *	@return	Number of available bytes
 */
ui16 DriverSBGC32_GetAvailableBytes (void *driver)
{
	sbgcDriver_t *drv = (sbgcDriver_t*)driver;

	int bytes;

	ioctl(drv->devFD, FIONREAD, &bytes);

	return bytes;
}


/**	@brief	Receives byte from serial port
 *
 *	@param	*driver - main hardware driver object
 *	@param	*data - data buffer
 *
 *	@return	Rx status
 */
ui8 DriverSBGC32_ReceiveByte (void *driver, ui8 *data)
{
	sbgcDriver_t *drv = (sbgcDriver_t*)driver;

	if (!DriverSBGC32_GetAvailableBytes(drv))
		return SBGC_DRV_RX_BUFF_EMPTY_FLAG;

	read(drv->devFD, data, 1);

	return SBGC_DRV_RX_BUSY_FLAG;
}


/**	@brief	Prints debug data
 *
 *	@param	*data - debug data
 *	@param	length - size of debug data
 */
void DriverSBGC32_PrintDebugData (char *data, ui16 length)
{
	while (length)
	{
		printf("%c", *(data++));
		length--;
	}
}
/**	@}
 */

#pragma GCC diagnostic pop


#endif /* SBGC_USE_LINUX_DRIVER */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
