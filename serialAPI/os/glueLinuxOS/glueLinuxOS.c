/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.0
 *
 *	@file		glueLinuxOS.c
 *
 *	@brief		Source OS glue file
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

#include	"../../sbgc32.h"


#if (SBGC_USE_LINUX_OS)

static sbgcMutex_t handlerTaskBlockMutex;
static volatile sbgcBoolean_t handlerTaskBlockFlag = sbgcFALSE;

/* Borrowed Functions  -------------------------------------------------
 */
extern sbgcCommandStatus_t PrivateSBGC32_EnterInit (sbgcGeneral_t *gSBGC);
extern NORETURN__ sbgcThreadRetval_t SBGC32_HandlerThread (sbgcThreadArg_t threadArg);


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	LinuxOS_Glue
 *	@{
 */
/**	@brief	SerialAPI initialization thread
 *
 *	@note	Private function
 *
 *	@param	threadArg - pointer to sbgcGeneral_t object
 *
 *  @return Initialization finish status
 */
static sbgcThreadRetval_t SBGC32_InitThread (sbgcThreadArg_t threadArg)
{
	sbgcGeneral_t *gSBGC = (sbgcGeneral_t*)threadArg;

	gSBGC->_api->busyFlag = sbgcFALSE;

	SBGC32_EnterInit(gSBGC);

	#if (SBGC_NEED_ASSERTS)

		if (gSBGC->_api->serialAPI_Status != serialAPI_TX_RX_OK)
		{
			/*  - - - - - - User Init Error Handler - - - - - - - */
			(void)(1);
			/*  - - - - - - - - - - - - - - - - - - - - - - - - - */
		}

		else
			SystemSBGC32_CreateThread(SBGC32_HandlerThread, gSBGC);

	#endif

	SystemSBGC32_DestroyThreadItself();

	return (void*)(1);
}


/**	@brief	Creates initialization thread.
 *			Starts the scheduler if necessary
 *
 *	@param	*gSBGC - pointer to sbgcGeneral_t object
 */
void SystemSBGC32_Init (void *gSBGC)
{
	SystemSBGC32_CreateThread(SBGC32_InitThread, gSBGC);
}


/**	@brief	Creates new SBGC32 thread
 *
 *	@param	*fn - pointer to the task entry function
 *	@param	threadArg - parameter for the task
 */
void SystemSBGC32_CreateThread (SBGC_THREAD_FUNCTION((*fn), arg), sbgcThreadArg_t threadArg)
{
	sbgcThread_t Thread;

	if (pthread_create(&Thread, NULL, fn ,threadArg))
		SerialAPI_FatalErrorHandler();
}


/**	@brief	Destroys current thread
 */
void SystemSBGC32_DestroyThreadItself (void)
{
	sbgcThread_t Thread = pthread_self();

	if (pthread_cancel(Thread))
		SerialAPI_FatalErrorHandler();

	if (pthread_join(Thread, NULL))
		SerialAPI_FatalErrorHandler();
}


/**	@brief	Switches current thread
 */
void SystemSBGC32_Yield (void)
{
	(void)(1);
}


/**	@brief	Suspends thread
 *
 *	@param	*threadHandle - pointer to thread handle
 */
void SystemSBGC32_SuspendThread (const sbgcThread_t *threadHandle)
{
	unused_(threadHandle);

	SystemSBGC32_TakeMutex(&handlerTaskBlockMutex);
	handlerTaskBlockFlag = sbgcTRUE;
	SystemSBGC32_GiveMutex(&handlerTaskBlockMutex);

	while (handlerTaskBlockFlag);
}


/**	@brief	Resumes thread
 *
 *	@param	*threadHandle - pointer to thread handle
 */
void SystemSBGC32_ResumeThread (const sbgcThread_t *threadHandle)
{
	unused_(threadHandle);

	SystemSBGC32_TakeMutex(&handlerTaskBlockMutex);
	handlerTaskBlockFlag = sbgcFALSE;
	SystemSBGC32_GiveMutex(&handlerTaskBlockMutex);
}


/**	@brief	Creates OS mutex
 *
 *	@param	*mutex - pointer to OS mutex object
 */
void SystemSBGC32_CreateMutex (sbgcMutex_t *mutex)
{
	sbgcCreateMutex(mutex);
}


/**	@brief	Destroys OS mutex
 *
 *	@param	*mutex - pointer to OS mutex object
 */
void SystemSBGC32_DestroyMutex (sbgcMutex_t *mutex)
{
	sbgcDestroyMutex(mutex);
}


/**	@brief	Takes OS mutex (Enter)
 *
 *	@param	*mutex - pointer to OS mutex object
 */
void SystemSBGC32_TakeMutex (sbgcMutex_t *mutex)
{
	sbgcTakeMutex(mutex, 0);
}


/**	@brief	Gives OS mutex (Exit)
 *
 *	@param	*mutex - pointer to OS mutex object
 */
void SystemSBGC32_GiveMutex (sbgcMutex_t *mutex)
{
	sbgcGiveMutex(mutex);
}
/**	@}
 */

#endif  /* SBGC_USE_LINUX_OS */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
