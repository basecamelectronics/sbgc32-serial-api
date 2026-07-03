/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.3
 *
 *	@file		gluePThread.c
 *
 *	@brief		PThread glue source file
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

#include	"../../sbgc32.h"


#if (SBGC_USE_PTHREAD_OS)

static sbgcMutex_t handlerTaskBlockMutex;
static pthread_cond_t handlerTaskBlockCond;
static volatile sbgcBoolean_t handlerTaskBlockFlag = sbgcFALSE;
static sbgcBoolean_t handlerTaskBlockSyncCreated = sbgcFALSE;
static sbgcBoolean_t handlerThreadCreated = sbgcFALSE;
static sbgcBoolean_t serialAPIMutexCreated = sbgcFALSE;

/* Borrowed Functions  -------------------------------------------------
 */
extern sbgcCommandStatus_t PrivateSBGC32_EnterInit (sbgcGeneral_t *gSBGC);
extern NORETURN__ sbgcThreadRetval_t SBGC32_HandlerThread (sbgcThreadArg_t threadArg);


/* Static Functions  ---------------------------------------------------
 */
static void SystemSBGC32_UnlockMutexCleanup (void *mutex)
{
	pthread_mutex_unlock((sbgcMutex_t*)mutex);
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	PThread_Glue
 *	@{
 */
/**	@brief	Prepares and starts handler thread
 *
 *	@param	*sbgcGeneral - pointer to sbgcGeneral_t object
 */
void SystemSBGC32_Init (void *sbgcGeneral)
{
	retifnull_(sbgcGeneral);

	sbgcGeneral_t *gSBGC = (sbgcGeneral_t*)sbgcGeneral;

	PrivateSBGC32_EnterInit(gSBGC);

	retifnull_(gSBGC->_api);

	#if (SBGC_NEED_ASSERTS)

		if (gSBGC->_api->serialAPI_Status != serialAPI_OK)
		{
			/*  - - - - - - User Init Error Handler - - - - - - - */
			SerialAPI_FatalErrorHandler();
			/*  - - - - - - - - - - - - - - - - - - - - - - - - - */
		}

		else

	#endif

		{
			if (handlerTaskBlockSyncCreated == sbgcFALSE)
			{
				if (pthread_mutex_init(&handlerTaskBlockMutex, NULL))
					SerialAPI_FatalErrorHandler();

				if (pthread_cond_init(&handlerTaskBlockCond, NULL))
				{
					pthread_mutex_destroy(&handlerTaskBlockMutex);
					SerialAPI_FatalErrorHandler();
				}

				handlerTaskBlockFlag = sbgcFALSE;
				handlerTaskBlockSyncCreated = sbgcTRUE;
			}

			SystemSBGC32_CreateMutex(&gSBGC->_api->mutexSerialAPI);
			serialAPIMutexCreated = sbgcTRUE;

			api_->busyFlag = sbgcFALSE;
			api_->threadState = SATS_NORMAL;

			if (SystemSBGC32_CreateThread(SBGC32_HandlerThread, "SBGC32 Handler", SBGC_THREAD_STACK_SIZE,
										  gSBGC, SBGC_THREAD_PRIOR, &gSBGC->_api->threadHandle))
				SerialAPI_FatalErrorHandler();

			handlerThreadCreated = sbgcTRUE;
		}
}


/**	@brief	Removes the SBGC32 handler thread
 *
 *	@param	*sbgcGeneral - pointer to sbgcGeneral_t object
 */
void SystemSBGC32_Deinit (void *sbgcGeneral)
{
	retifnull_(sbgcGeneral);

	sbgcGeneral_t *gSBGC = (sbgcGeneral_t*)sbgcGeneral;

	retifnull_(gSBGC->_api);

	if (handlerThreadCreated)
	{
		if (pthread_cancel(gSBGC->_api->threadHandle))
			SerialAPI_FatalErrorHandler();

		if (pthread_join(gSBGC->_api->threadHandle, NULL))
			SerialAPI_FatalErrorHandler();

		handlerThreadCreated = sbgcFALSE;
	}

	if (serialAPIMutexCreated)
	{
		SystemSBGC32_DestroyMutex(&gSBGC->_api->mutexSerialAPI);
		serialAPIMutexCreated = sbgcFALSE;
	}

	if (handlerTaskBlockSyncCreated)
	{
		pthread_cond_destroy(&handlerTaskBlockCond);
		pthread_mutex_destroy(&handlerTaskBlockMutex);

		handlerTaskBlockSyncCreated = sbgcFALSE;
		handlerTaskBlockFlag = sbgcFALSE;
	}
}


/**	@brief	Creates new SBGC32 thread
 *
 *	@param	*fn - pointer to the task entry function
 *	@param	*threadName - a descriptive name for the task
 *	@param	stackSize - size of the task stack
 *	@param	threadArg - parameter for the task
 *	@param	priority - priority at which the task should run
 *	@param	*threadHandle - reference handle for created task
 *
 *	@return	Thread creation status
 */
int SystemSBGC32_CreateThread (SBGC_THREAD_FUNCTION((*fn), arg), const char * const threadName,
							   ui32 stackSize,
							   sbgcThreadArg_t threadArg,
							   ui32 priority,
							   sbgcThread_t * const threadHandle)
{
	unused_(threadName);
	unused_(stackSize);
	unused_(priority);

	if ((fn == NULL) || (threadHandle == NULL))
		return -1;

	return pthread_create(threadHandle, NULL, fn, threadArg);
}


/**	@brief	Switches current thread
 */
void SystemSBGC32_Yield (void)
{
	pthread_testcancel();
	sbgcYield();
}


/**	@brief	Suspends thread
 *
 *	@param	*threadHandle - pointer to thread handle
 */
void SystemSBGC32_SuspendThread (sbgcThread_t *threadHandle)
{
	retifnull_(threadHandle)
	unused_(threadHandle);

	if (handlerTaskBlockSyncCreated == sbgcFALSE)
		return;

	if (pthread_mutex_lock(&handlerTaskBlockMutex))
		SerialAPI_FatalErrorHandler();

	handlerTaskBlockFlag = sbgcTRUE;

	pthread_cleanup_push(SystemSBGC32_UnlockMutexCleanup, &handlerTaskBlockMutex);

	while (handlerTaskBlockFlag)
		if (pthread_cond_wait(&handlerTaskBlockCond, &handlerTaskBlockMutex))
			SerialAPI_FatalErrorHandler();

	pthread_cleanup_pop(1);
}


/**	@brief	Resumes thread
 *
 *	@param	*threadHandle - pointer to thread handle
 */
void SystemSBGC32_ResumeThread (sbgcThread_t *threadHandle)
{
	retifnull_(threadHandle)
	unused_(threadHandle);

	if (handlerTaskBlockSyncCreated == sbgcFALSE)
		return;

	if (pthread_mutex_lock(&handlerTaskBlockMutex))
		SerialAPI_FatalErrorHandler();

	handlerTaskBlockFlag = sbgcFALSE;

	if (pthread_cond_signal(&handlerTaskBlockCond))
		SerialAPI_FatalErrorHandler();

	if (pthread_mutex_unlock(&handlerTaskBlockMutex))
		SerialAPI_FatalErrorHandler();
}


/**	@brief	Creates OS mutex
 *
 *	@param	*mutex - pointer to OS mutex object
 */
void SystemSBGC32_CreateMutex (sbgcMutex_t *mutex)
{
	retifnull_(mutex)

	if (sbgcCreateMutex(mutex))
		SerialAPI_FatalErrorHandler();
}


/**	@brief	Destroys OS mutex
 *
 *	@param	*mutex - pointer to OS mutex object
 */
void SystemSBGC32_DestroyMutex (sbgcMutex_t *mutex)
{
	retifnull_(mutex)

	sbgcDestroyMutex(mutex);
}


/**	@brief	Takes OS mutex (Enter)
 *
 *	@param	*mutex - pointer to OS mutex object
 */
void SystemSBGC32_TakeMutex (sbgcMutex_t *mutex)
{
	retifnull_(mutex)

	sbgcTakeMutex(mutex, 0);
}


/**	@brief	Gives OS mutex (Exit)
 *
 *	@param	*mutex - pointer to OS mutex object
 */
void SystemSBGC32_GiveMutex (sbgcMutex_t *mutex)
{
	retifnull_(mutex)

	sbgcGiveMutex(mutex);
}


/**	@brief	Changes the priority of a thread
 *
 *	@param	*threadHandle - pointer to thread handle
 *	@param	newPrior - new thread priority
 */
void SystemSBGC32_SetThreadPriority (sbgcThread_t *threadHandle, ui32 newPrior)
{
	retifnull_(threadHandle)

	unused_(threadHandle);
	unused_(newPrior);
}
/**	@}
 */

#endif  /* SBGC_USE_PTHREAD_OS */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
