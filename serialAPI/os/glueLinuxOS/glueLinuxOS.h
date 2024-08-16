/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.0
 *
 *	@file		glueLinuxOS.h
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
 *	@defgroup	LinuxOS_Glue Linux OS Glue
 *	@ingroup	OS
 *		@brief	Linux OS Glue Module
 *	____________________________________________________________________
 */

#ifndef		OS_GLUE_LINUX_OS_H_
#define		OS_GLUE_LINUX_OS_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../sbgc32.h"


#if (SBGC_USE_LINUX_OS)

#include	<sys/types.h>
#include	<stdlib.h>
#include	<pthread.h>
#include	<semaphore.h>
#include	<time.h>


/**	@addtogroup	LinuxOS_Glue
 *	@{
 */
/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *											   Types
 */
typedef		unsigned long			sbgcTicks_t;
typedef		pthread_t				sbgcThread_t;
typedef		void*					sbgcThreadRetval_t;
typedef		void*					sbgcThreadArg_t;
typedef		pthread_mutex_t			sbgcMutex_t;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								Macros and Constants
 */
#define		SBGC_USES_OS_SUPPORT	sbgcON

#define		sbgcMalloc(size)		malloc(size)
#define		sbgcFree(ptr)			free(ptr)

#define		sbgcDelay(tick)			usleep((tick) * 1000)
#define		sbgcGetTick()			DriverSBGC_GetTimeMs()
#define		sbgcMsToTicks(ms)		(ms)

#define		sbgcCreateMutex(m)		pthread_mutex_init(m, 0)
#define		sbgcDestroyMutex(m)		pthread_mutex_destroy(m)
#define		sbgcTakeMutex(m, t)		pthread_mutex_lock(m)
#define		sbgcGiveMutex(m)		pthread_mutex_unlock(m)

#define		SBGC_THREAD_FUNCTION(name, arg)	sbgcThreadRetval_t name(void *arg)

#define		SBGC_THREAD_PRIOR_LOW			1
#define		SBGC_THREAD_PRIOR_NORMAL		5
#define		SBGC_THREAD_PRIOR_HIGH			10

#define		SBGC_HANDLER_THREAD_PRIOR		(SBGC_THREAD_PRIOR_NORMAL + 1)
#define		SBGC_INIT_THREAD_PRIOR			(SBGC_THREAD_PRIOR_HIGH + 1)


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								 Function Prototypes
 */
sbgcThreadRetval_t SBGC32_InitThread (sbgcThreadArg_t threadArg);
void SystemSBGC32_Init (void *gSBGC);
void SystemSBGC32_CreateThread (SBGC_THREAD_FUNCTION((*fn), arg), sbgcThreadArg_t threadArg);
void SystemSBGC32_DestroyThreadItself (void);
void SystemSBGC32_Yield (void);
void SystemSBGC32_SuspendThread (const sbgcThread_t *threadHandle);
void SystemSBGC32_ResumeThread (const sbgcThread_t *threadHandle);
void SystemSBGC32_CreateMutex (sbgcMutex_t *mutex);
void SystemSBGC32_DestroyMutex (sbgcMutex_t *mutex);
void SystemSBGC32_TakeMutex (sbgcMutex_t *mutex);
void SystemSBGC32_GiveMutex (sbgcMutex_t *mutex);
/**	@}
 */

#endif		/* SBGC_USE_LINUX_OS */


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
}
#endif

#endif		/* OS_GLUE_LINUX_OS_H_ */
