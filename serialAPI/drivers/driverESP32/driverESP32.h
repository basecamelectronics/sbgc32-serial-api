/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2.1
 *
 *	@file		driverESP32.h
 *
 *	@brief		ESP32 driver header file
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

#ifndef		DRIVERS_DRIVER_ESP32_H_
#define		DRIVERS_DRIVER_ESP32_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../sbgc32.h"


#if (SBGC_USE_ESPIDF_DRIVER)

#include	"esp_timer.h"
#include	"driver/uart.h"
#include	"driver/gpio.h"
#include	"esp_log.h"
#include	"esp_err.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							Configuration Protection
 */
#ifndef SBGC_SERIAL_PORT
	#define	SBGC_SERIAL_PORT		1
#endif

#ifndef SBGC_DEBUG_SERIAL_PORT
	#define	SBGC_DEBUG_SERIAL_PORT	0
#endif

#ifndef SBGC_SERIAL_SPEED
	#define	SBGC_SERIAL_SPEED		115200
#endif

#ifndef SBGC_DEBUG_SERIAL_SPEED
	#define	SBGC_DEBUG_SERIAL_SPEED	115200
#endif

#ifndef SBGC_SERIAL_TX_PIN
    #define SBGC_SERIAL_TX_PIN		-1
#endif

#ifndef SBGC_SERIAL_RX_PIN
    #define SBGC_SERIAL_RX_PIN		-1
#endif

#ifndef SBGC_DRV_TX_BUFFER_SIZE
    #define SBGC_DRV_TX_BUFFER_SIZE	3
#endif

#ifndef SBGC_DRV_RX_BUFFER_SIZE
    #define SBGC_DRV_RX_BUFFER_SIZE	3
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *											  Macros
 */
#ifndef	sbgcDelay
	#define	sbgcDelay(ms)			vTaskDelay(pdMS_TO_TICKS(ms))
#endif

#ifndef	sbgcGetTick
	#define	sbgcGetTick()			((ui32)(esp_timer_get_time() / 1000ULL))
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *											   Other
 */
/* General UART buffer size values */
#define		SBGC_DRV_TX_BUFF_POWER			(SBGC_DRV_TX_BUFFER_SIZE + 7)
#define		SBGC_DRV_RX_BUFF_POWER			(SBGC_DRV_RX_BUFFER_SIZE + 7)

#define		SBGC_DRV_TX_BUFF_TOTAL_SIZE		(1 << SBGC_DRV_TX_BUFF_POWER)
#define		SBGC_DRV_RX_BUFF_TOTAL_SIZE		(1 << SBGC_DRV_RX_BUFF_POWER)


/**	@addtogroup	ESP32_Driver
 *	@{
 */
/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									Hardware Objects
 */
/**	@brief	General driver structure
 */
typedef struct
{
	uart_port_t		uart;
	
}	sbgcDriver_t;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								 Function Prototypes
 */
void DriverSBGC32_Init (void **driver, uart_port_t serial, unsigned long serialSpeed);
void DriverSBGC32_Deinit (void **driver);

sbgcTicks_t DriverSBGC32_GetTimeMs (void);

ui8  DriverSBGC32_TransmitData (void *driver, ui8 *data, ui16 size);
ui16 DriverSBGC32_GetAvailableBytes (void *driver);
ui8  DriverSBGC32_ReceiveByte (void *driver, ui8 *data);

void DriverSBGC32_PrintDebugData (char *data, ui16 length);
/**	@}
 */
 
#endif /* SBGC_USE_ESP32_DRIVER */


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

#endif		/* DRIVERS_DRIVER_ESP32_H_ */
