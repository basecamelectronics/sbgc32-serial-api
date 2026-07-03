/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.3
 *
 *	@file		gluePThread.h
 *
 *	@brief		PThread glue header file
 *	____________________________________________________________________
 *
 *	@attention	<h3><center>
 *				Copyright © 2026 BaseCam Electronics™.<br>
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
 *	@defgroup	PThread_Glue POSIX Thread Glue
 *	@ingroup	OS
 *		@brief	POSIX Thread Glue Module
 *	____________________________________________________________________
 */

#ifndef		OS_GLUE_PTHREAD_H_
#define		OS_GLUE_PTHREAD_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../sbgc32.h"


#if (SBGC_USE_PTHREAD_OS)

#include	<sys/types.h>
#include	<stdlib.h>
#include	<pthread.h>
#include	<semaphore.h>
#include	<time.h>
#include	<unistd.h>
#include	<sched.h>


/**	@addtogroup	PThread_Glue
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
#define		sbgcGetTick()			DriverSBGC32_GetTimeMs()
#define		sbgcTickToMs(tick)		(tick)
#define		sbgcMsToTick(ms)		(ms)

#define		sbgcYield()				sched_yield()

#define		sbgcCreateMutex(m)		pthread_mutex_init(m, 0)
#define		sbgcDestroyMutex(m)		pthread_mutex_destroy(m)
#define		sbgcTakeMutex(m, t)		pthread_mutex_lock(m)
#define		sbgcGiveMutex(m)		pthread_mutex_unlock(m)

#define		SBGC_THREAD_FUNCTION(name, arg)	sbgcThreadRetval_t name(void *arg)

#define		SBGC_THREAD_PRIOR_LOW			1
#define		SBGC_THREAD_PRIOR_NORMAL		5
#define		SBGC_THREAD_PRIOR_HIGH			10

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								 Function Prototypes
 */
void SystemSBGC32_Init (void *sbgcGeneral);
void SystemSBGC32_Deinit (void *sbgcGeneral);
int SystemSBGC32_CreateThread (SBGC_THREAD_FUNCTION((*fn), arg), const char * const threadName,
							   ui32 stackSize,
							   sbgcThreadArg_t threadArg,
							   ui32 priority,
							   sbgcThread_t * const threadHandle);
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

#endif		/* SBGC_USE_PTHREAD_OS */


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
}
#endif

#endif		/* OS_GLUE_PTHREAD_H_ */
