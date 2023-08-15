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

#ifdef 		__cplusplus
extern 		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../../../../serialAPI/adjunct.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							  Initial Project Config
 */
#define		PROJ_USE_HAL			SET_ON
#define		PROJ_USE_LL				SET_OFF

#define		PROJ_USE_FREERTOS		SET_ON

#define		PROJ_NEED_WATCHDOG		SET_OFF
#define		PROJ_NEED_FAULT_RESET	SET_OFF


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *										Service Code
 */
/* MCU depended libraries --------------------------
 */
#if (PROJ_USE_HAL)
	#include		"stm32f4xx_hal.h"

#elif (PROJ_USE_LL)
	/* User LL libraries includes */
#endif

#if (PROJ_USE_FREERTOS == SET_OFF)
	#define	__GetTick()				HAL_GetTick()
	#define	__DelayMs(ms)			HAL_Delay(ms)

	#define	__Malloc(size)			malloc(size)
	#define	__Free(addr)			free(addr)
#endif

/* OS depended libraries ---------------------------
 */
#if (PROJ_USE_FREERTOS)
	/* OS includes */
	#include "FreeRTOS.h"
	#include "task.h"
	#include "croutine.h"
	#include "semphr.h"
	#include "queue.h"
	#include "timers.h"

	/* OS priorities */
	#define	OS_LOW_PRIORITY			(0)
	#define	OS_NORMAL_PRIORITY		(configMAX_PRIORITIES - 4)
	#define	OS_MEDIUM_PRIORITY		(configMAX_PRIORITIES - 3)
	#define	OS_HIGH_PRIORITY		(configMAX_PRIORITIES - 2)
	#define	OS_HIGHEST_PRIORITY		(configMAX_PRIORITIES - 1)

	/* OS objects determination */
	#define	osTaskCreate			xTaskCreate
	#define	osTaskDelete(pH)		vTaskDelete(pH)

	#define	osTaskStartSheduler()	vTaskStartScheduler()

	#define	osSystemLock()			vPortEnterCritical()
	#define	osSystemUnlock()		vPortExitCritical()

	#define	osMalloc(size)			pvPortMalloc(size)
	#define	osFree(p)				vPortFree(p)

	#define	osTaskYIELD()			taskYIELD()

	#define	osDelay(t)				vTaskDelay(t)
	#define	osGetTickCount()		xTaskGetTickCount()

	#define	osMaxDelay				portMAX_DELAY

	#define	osSemaphoreCreate(smphr)		vSemaphoreCreateBinary(smphr)
	#define osSemaphoreTake(smphr, bTime)	xSemaphoreTake(smphr, bTime)
	#define osSemaphoreGive(smphr)			xSemaphoreGive(smphr)

	/* Gluing with main shell */
	#define	__GetTick()				osGetTickCount()
	#define	__DelayMs(ms)			osDelay(ms)

	#define	__Malloc(size)			osMalloc(size)
	#define	__Free(addr)			osFree(addr)
#endif

#define		__ProcessorDelay(x)		for (ui32 i = 0; i < x; i++) __NOP();

/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef 		__cplusplus
			}
#endif

#endif		/* _INITIAL_CONFIG_H_ */
