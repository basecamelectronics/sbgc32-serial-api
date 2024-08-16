/** ____________________________________________________________________
 *
 *	@file		initialConfig.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_INITIAL_CONFIG_H_
#define		_INITIAL_CONFIG_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../../../../serialAPI/adjunct.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							  Initial Project Config
 */
#define		PROJ_NEED_WATCHDOG		sbgcOFF
#define		PROJ_NEED_FAULT_RESET	sbgcON


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *										Service Code
 */
/* MCU depended libraries --------------------------
 */
#include	"stm32f4xx_hal.h"


/* OS depended libraries ---------------------------
 */
/* OS includes */
#include	"FreeRTOS.h"
#include	"task.h"
#include	"croutine.h"
#include	"semphr.h"
#include	"queue.h"
#include	"timers.h"

/* OS priorities */
#define		OS_LOW_PRIORITY			(0)
#define		OS_NORMAL_PRIORITY		(configMAX_PRIORITIES - 4)
#define		OS_MEDIUM_PRIORITY		(configMAX_PRIORITIES - 3)
#define		OS_HIGH_PRIORITY		(configMAX_PRIORITIES - 2)
#define		OS_HIGHEST_PRIORITY		(configMAX_PRIORITIES - 1)

/* OS objects determination */
#define		osTaskCreate			xTaskCreate
#define		osTaskDelete(pH)		vTaskDelete(pH)

#define		osTaskStartSheduler()	vTaskStartScheduler()

#define		osSystemLock()			vPortEnterCritical()
#define		osSystemUnlock()		vPortExitCritical()

#define		osMalloc(size)			pvPortMalloc(size)
#define		osFree(p)				vPortFree(p)

#define		osTaskYIELD()			taskYIELD()

#define		osDelay(t)				vTaskDelay(t)
#define		osGetTickCount()		xTaskGetTickCount()

#define		osMaxDelay				portMAX_DELAY

#define		osSemaphoreCreate(smphr)		vSemaphoreCreateBinary(smphr)
#define		osSemaphoreTake(smphr, bTime)	xSemaphoreTake(smphr, bTime)
#define		osSemaphoreGive(smphr)			xSemaphoreGive(smphr)


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef 		__cplusplus
			}
#endif

#endif		/* _INITIAL_CONFIG_H_ */
