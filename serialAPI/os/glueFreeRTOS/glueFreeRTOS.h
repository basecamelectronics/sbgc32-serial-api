/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2.1
 *
 *	@file		glueFreeRTOS.h
 *
 *	@brief		FreeRTOS glue header file
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
/**	____________________________________________________________________
 *
 *	@defgroup	FreeRTOS_Glue FreeRTOS Glue
 *	@ingroup	OS
 *		@brief	FreeRTOS Glue Module
 *	____________________________________________________________________
 */

#ifndef		OS_GLUE_FREE_RTOS_H_
#define		OS_GLUE_FREE_RTOS_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../sbgc32.h"


#if (SBGC_USE_FREE_RTOS)

#if (SBGC_USE_ESPIDF_DRIVER)
	#include	"freertos/FreeRTOS.h"
	#include	"freertos/semphr.h"
#else
	#include	"FreeRTOS.h"
	#include	"semphr.h"
#endif


/**	@addtogroup	FreeRTOS_Glue
 *	@{
 */
/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *											   Types
 */
typedef		portTickType			sbgcTicks_t;
typedef		xTaskHandle				sbgcThread_t;
typedef		void					sbgcThreadRetval_t;
typedef		void*					sbgcThreadArg_t;
typedef		xSemaphoreHandle		sbgcMutex_t;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								Macros and Constants
 */
#define		SBGC_USES_OS_SUPPORT	sbgcON

#define		sbgcThreadDestroy(pH)	vTaskDelete(pH)
#define		sbgcThreadSuspend(pH)	vTaskSuspend(pH)
#define		sbgcThreadResume(pH)	vTaskResume(pH)

#define		sbgcMalloc(size)		pvPortMalloc(size)
#define		sbgcFree(ptr)			vPortFree(ptr)

#define		sbgcDelay(tick)			vTaskDelay(tick / portTICK_PERIOD_MS)
#define		sbgcGetTick()			xTaskGetTickCount()
#define		sbgcTickToMs(tick)		((tick) * (1000.0 / configTICK_RATE_HZ))
#define		sbgcMsToTick(ms)		((ms) / portTICK_PERIOD_MS)

#define		sbgcYield()				taskYIELD()

#define		sbgcLockSystem()		taskENTER_CRITICAL()
#define		sbgcUnlockSystem()		taskEXIT_CRITICAL()

#define		sbgcCreateMutex(m)		vSemaphoreCreateBinary(m)
#define		sbgcDestroyMutex(m)		vSemaphoreDelete(m)
#define		sbgcTakeMutex(m, t)		xSemaphoreTake(m, t)
#define		sbgcGiveMutex(m)		xSemaphoreGive(m)

#define		sbgcSetPrior(pH, pr)	vTaskPrioritySet(pH, pr)

#define		SBGC_THREAD_PRIOR_LOW			0
#define		SBGC_THREAD_PRIOR_NORMAL		(configMAX_PRIORITIES / 2)
#define		SBGC_THREAD_PRIOR_HIGH			(configMAX_PRIORITIES - 1)


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *											Warnings
 */
#if (SBGC_USE_FREE_RTOS && (SBGC_THREAD_PRIOR < SBGC_THREAD_QUIET_PRIOR))
	#error "Error! The lowered priority must not be higher than the normal"
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								 Function Prototypes
 */
void SystemSBGC32_Init (void *gSBGC);
void SystemSBGC32_Deinit (void *gSBGC);
BaseType_t SystemSBGC32_CreateThread (TaskFunction_t pxTaskCode, const char * const pcName,
									  const configSTACK_DEPTH_TYPE usStackDepth,
									  void * const pvParameters,
									  UBaseType_t uxPriority,
									  TaskHandle_t * const pxCreatedTask);
void SystemSBGC32_DestroyThreadItself (void);
void SystemSBGC32_Yield (void);
void SystemSBGC32_SuspendThread (sbgcThread_t *threadHandle);
void SystemSBGC32_ResumeThread (sbgcThread_t *threadHandle);
void SystemSBGC32_CreateMutex (sbgcMutex_t *mutex);
void SystemSBGC32_DestroyMutex (sbgcMutex_t *mutex);
void SystemSBGC32_TakeMutex (sbgcMutex_t *mutex);
void SystemSBGC32_GiveMutex (sbgcMutex_t *mutex);
void SystemSBGC32_SetThreadPriority (sbgcThread_t *threadHandle, ui32 newPrior);
/**	@}
 */

#endif /* SBGC_USE_FREE_RTOS */


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

#endif		/* OS_GLUE_FREE_RTOS_H_ */
