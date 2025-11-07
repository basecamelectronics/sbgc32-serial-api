/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2.1
 *
 *	@file		driverESP32.c
 *
 *	@brief		ESP32 driver source file
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


#if (SBGC_USE_ESPIDF_DRIVER)


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	ESP32_Driver
 *	@{
 */
/**	@brief	Initializes the driver object of sbgcGeneral_t
 *
 *	@param	**driver - main hardware driver object
 *	@param	serial - user defined serial object
 *	@param	*serialSpeed - user defined serial speed
 */
void DriverSBGC32_Init (void **driver, uart_port_t serial, unsigned long serialSpeed)
{
	unused_(serial);
	
	*driver = sbgcMalloc(sizeof(sbgcDriver_t));
	
	sbgcDriver_t *drv = (sbgcDriver_t*)(*driver);
	
	drv->uart = serial;
	
    uart_config_t cfg =
    {
        .baud_rate	= serialSpeed,
        .data_bits	= UART_DATA_8_BITS,
        .parity		= UART_PARITY_DISABLE,
        .stop_bits	= UART_STOP_BITS_1,
        .flow_ctrl	= UART_HW_FLOWCTRL_DISABLE,
        
		#if ESP_IDF_VERSION_MAJOR >= 5
        	.source_clk = UART_SCLK_APB,
		#endif
    };

    /* Configure parameters */
    unused_(uart_param_config(drv->uart, &cfg));
    unused_(uart_set_pin(drv->uart, SBGC_SERIAL_TX_PIN, SBGC_SERIAL_RX_PIN, -1, -1));
    unused_(uart_driver_install(drv->uart, SBGC_DRV_RX_BUFF_TOTAL_SIZE, SBGC_DRV_TX_BUFF_TOTAL_SIZE, 0, NULL, 0));
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
    return (ui32)(esp_timer_get_time() / 1000ULL);
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
	sbgcDriver_t *drv = (sbgcDriver_t*)(driver);
	
    unused_(uart_write_bytes(drv->uart, (const char*)data, (size_t)size));

    return 0;
}


/**	@brief	Returns the number of available bytes
 *
 *	@param	*driver - main hardware driver object
 *
 *	@return	Number of available bytes
 */
ui16 DriverSBGC32_GetAvailableBytes (void *driver)
{
	sbgcDriver_t *drv = (sbgcDriver_t*)(driver);
	
	size_t buffered = 0;
	
	if (uart_get_buffered_data_len(drv->uart, &buffered) != ESP_OK)
	    return 0;
	
	if (buffered > 0xFFFFU)
		buffered = 0xFFFFU;
		
	return (ui16)buffered;
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
	sbgcDriver_t *drv = (sbgcDriver_t*)(driver);
	
    if (!data)
    	return SBGC_DRV_RX_BUFF_EMPTY_FLAG;

    return (uart_read_bytes(drv->uart, data, 1, 0) == 1) ? SBGC_DRV_RX_BUSY_FLAG : SBGC_DRV_RX_BUFF_EMPTY_FLAG;
}


/**	@brief	Sends debug data
 *
 *	@param	*data - debug data
 *	@param	length - size of debug data
 */
void DriverSBGC32_PrintDebugData (char *data, ui16 length)
{
	fwrite(data, 1, length, stdout);
	
	fflush(stdout);
}
/**	@}
 */


#endif /* SBGC_USE_ESPIDF_DRIVER */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
