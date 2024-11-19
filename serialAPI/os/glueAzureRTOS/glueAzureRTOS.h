/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.1
 *
 *	@file		glueAzureRTOS.h
 *
 *	@brief		Header OS glue file
 *	____________________________________________________________________
 *
 *	@attention	<h3><center>
 *				Copyright © 2024 BaseCam Electronics™.<br>
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
 *	@defgroup	AzureRTOS_Glue AzureRTOS Glue
 *	@ingroup	OS
 *		@brief	AzureRTOS Glue Module
 *	____________________________________________________________________
 */

#ifndef		OS_GLUE_AZURE_RTOS_H_
#define		OS_GLUE_AZURE_RTOS_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../sbgc32.h"


#if (SBGC_USE_AZURE_RTOS)

#include	"tx_api.h"

/**	@addtogroup	AzureRTOS_Glue
 *	@{
 */
/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *											   Types
 */
typedef		ULONG					sbgcTicks_t;
typedef		TX_THREAD				sbgcThread_t;
typedef		void					sbgcThreadRetval_t;
typedef		ULONG					sbgcThreadArg_t;
typedef		TX_MUTEX				sbgcMutex_t;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								Macros and Constants
 */
#define		SBGC_USES_OS_SUPPORT	sbgcON

#define		sbgcThreadDestroy(pH)	tx_thread_delete(pH)
#define		sbgcThreadSuspend(pH)	tx_thread_suspend(pH)
#define		sbgcThreadResume(pH)	tx_thread_resume(pH)

#define		sbgcStartSheduler()		tx_kernel_enter()

#define		sbgcMalloc(size)		SystemSBGC32_Malloc(size)
#define		sbgcFree(ptr)			tx_byte_release(ptr)

#define		sbgcDelay(tick)			tx_thread_sleep(tick)
#define		sbgcGetTick()			tx_time_get()

#define		sbgcYield()				tx_thread_relinquish()

#define		sbgcLockSystem()		INTERRUPTS_OFF()
#define		sbgcUnlockSystem()		INTERRUPTS_ON()

#define		sbgcCreateMutex(m)		tx_mutex_create(m, NULL, 0)
#define		sbgcDestroyMutex(m)		tx_mutex_delete(m)
#define		sbgcTakeMutex(m, t)		tx_mutex_get(m, t)
#define		sbgcGiveMutex(m)		tx_mutex_put(m)

#define		sbgcSetPrior(pH, newPr, oldPr)	tx_thread_priority_change(pH, newPr, oldPr)

#define		SBGC_THREAD_PRIOR_LOW			(TX_MAX_PRIORITIES - 1)
#define		SBGC_THREAD_PRIOR_NORMAL		((int)(TX_MAX_PRIORITIES / 2))
#define		SBGC_THREAD_PRIOR_HIGH			((int)(TX_MAX_PRIORITIES / 4))

#if (TX_MINIMUM_STACK > 512)
	#define	SBGC_INIT_THREAD_STACK	TX_MINIMUM_STACK
#else
	#define	SBGC_INIT_THREAD_STACK	512
#endif

#define		SBGC_HANDLER_THREAD_PRIOR		(SBGC_THREAD_PRIOR_NORMAL + 1)


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *											Warnings
 */
#if (SBGC_THREAD_STACK_SIZE < TX_MINIMUM_STACK)
	#error "Error! SBGC_THREAD_STACK_SIZE must be greater than TX_MINIMUM_STACK"
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								 Function Prototypes
 */
void SystemSBGC32_Init (void *gSBGC);
void *SystemSBGC32_Malloc (ui32 size);
void SystemSBGC32_DestroyThreadItself (void);
void SystemSBGC32_SuspendThread (sbgcThread_t *threadHandle);
void SystemSBGC32_ResumeThread (sbgcThread_t *threadHandle);
void SystemSBGC32_Yield (void);
void SystemSBGC32_CreateMutex (sbgcMutex_t *mutex);
void SystemSBGC32_DestroyMutex (sbgcMutex_t *mutex);
void SystemSBGC32_TakeMutex (sbgcMutex_t *mutex);
void SystemSBGC32_GiveMutex (sbgcMutex_t *mutex);
void SystemSBGC32_SetThreadPriority (sbgcThread_t *threadHandle, ui32 newPrior);
/**	@}
 */

#endif /* SBGC_USE_AZURE_RTOS */


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

#endif		/* OS_GLUE_AZURE_RTOS_H_ */
