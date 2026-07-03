/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.3
 *
 *	@file		glueAzureRTOS.c
 *
 *	@brief		AzureRTOS glue source file
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


#if (SBGC_USE_AZURE_RTOS)

/* Borrowed Functions  -------------------------------------------------
 */
extern sbgcCommandStatus_t PrivateSBGC32_EnterInit (sbgcGeneral_t *gSBGC);
extern NORETURN__ sbgcThreadRetval_t SBGC32_HandlerThread (sbgcThreadArg_t threadArg);


/**	@addtogroup	AzureRTOS_Glue
 *	@{
 */
/** Defines stack size for SerialAPI's purposes */
#define		SBGC_AZURE_TX_MEM_POOL_SIZE		(	sizeof(sbgcLowLayer_t) +\
												sizeof(sbgcDriver_t) +\
												SBGC_DRV_TX_BUFF_TOTAL_SIZE + SBGC_DRV_RX_BUFF_TOTAL_SIZE +\
												sizeof(serialAPI_General_t) +\
												(sizeof(serialAPI_Command_t) * SBGC_MAX_COMMAND_NUM) +\
												SBGC_TX_BUFF_TOTAL_SIZE + SBGC_RX_BUFF_TOTAL_SIZE +\
												SBGC_THREAD_STACK_SIZE + 256)
												/* May be expanded by user */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														  Static Objects
 */
/** Static SerialAPI's byte pool */
__ALIGN_BEGIN static UCHAR SBGC32_GeneralBytePoolBuffer [SBGC_AZURE_TX_MEM_POOL_SIZE] __ALIGN_END;

/** Static SerialAPI's byte pool handle object */
static TX_BYTE_POOL SBGC32_GeneralBytePool;

/** Shows that SerialAPI's byte pool has already been created */
static sbgcBoolean_t SBGC32_GeneralBytePoolCreated = sbgcFALSE;

/** Shows that SBGC32 handler thread is alive */
static sbgcBoolean_t SBGC32_HandlerThreadCreated = sbgcFALSE;

/** Stack memory of SBGC32 handler thread */
static void *SBGC32_HandlerThreadStack = NULL;

/** Shows that SerialAPI's mutex has already been created */
static sbgcBoolean_t SBGC32_MutexCreated = sbgcFALSE;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@brief	Prepares and starts handler thread
 *
 *	@param	*sbgcGeneral - pointer to sbgcGeneral_t object
 */
void SystemSBGC32_Init (void *sbgcGeneral)
{
	retifnull_(sbgcGeneral);

	sbgcGeneral_t *gSBGC = (sbgcGeneral_t*)sbgcGeneral;

	if (SBGC32_GeneralBytePoolCreated == sbgcFALSE)
	{
		if (tx_byte_pool_create(&SBGC32_GeneralBytePool, "SBGC32 Memory Pool", SBGC32_GeneralBytePoolBuffer,
								SBGC_AZURE_TX_MEM_POOL_SIZE) != TX_SUCCESS)
			SerialAPI_FatalErrorHandler();

		SBGC32_GeneralBytePoolCreated = sbgcTRUE;
	}

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
			SystemSBGC32_CreateMutex(&gSBGC->_api->mutexSerialAPI);

			api_->busyFlag = sbgcFALSE;
			api_->threadState = SATS_NORMAL;

			if (SystemSBGC32_CreateThread(SBGC32_HandlerThread, "SBGC32 Handler", SBGC_THREAD_STACK_SIZE,
										  (ULONG)gSBGC, SBGC_THREAD_PRIOR, &gSBGC->_api->threadHandle) != TX_SUCCESS)
				SerialAPI_FatalErrorHandler();

			SBGC32_HandlerThreadCreated = sbgcTRUE;
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

	if (SBGC32_HandlerThreadCreated)
	{
		sbgcThreadDestroy(&gSBGC->_api->threadHandle);
		SBGC32_HandlerThreadCreated = sbgcFALSE;
	}

	if (SBGC32_HandlerThreadStack)
	{
		sbgcFree(SBGC32_HandlerThreadStack);
		SBGC32_HandlerThreadStack = NULL;
	}

	if (SBGC32_MutexCreated)
	{
		sbgcDestroyMutex(&gSBGC->_api->mutexSerialAPI);
		SBGC32_MutexCreated = sbgcFALSE;
	}
}


/**	@brief	Creates new SBGC32 thread
 *
 *	@param	threadEntry - pointer to the task entry function
 *	@param	*threadName - a descriptive name for the task
 *	@param	stackSize - size of the task stack
 *	@param	threadArg - parameter for the task
 *	@param	priority - priority at which the task should run
 *	@param	*createdThread - reference handle for created task
 *
 *	@return	Thread creation status
 */
UINT SystemSBGC32_CreateThread (void (*threadEntry)(ULONG), const char * const threadName,
								ULONG stackSize,
								ULONG threadArg,
								UINT priority,
								TX_THREAD * const createdThread)
{
	if ((threadEntry == NULL) || (createdThread == NULL) || (stackSize == 0))
		return TX_PTR_ERROR;

	SBGC32_HandlerThreadStack = SystemSBGC32_Malloc(stackSize);

	if (SBGC32_HandlerThreadStack == NULL)
		return TX_PTR_ERROR;

	UINT threadCreateStatus = tx_thread_create(createdThread, (CHAR*)threadName, threadEntry,
											  threadArg, SBGC32_HandlerThreadStack, stackSize,
											  priority, priority, TX_NO_TIME_SLICE, TX_AUTO_START);

	if (threadCreateStatus != TX_SUCCESS)
	{
		sbgcFree(SBGC32_HandlerThreadStack);
		SBGC32_HandlerThreadStack = NULL;
	}

	return threadCreateStatus;
}


/**	@brief	Specialized malloc() for OS
 *
 *	@param	size - size of new memory block
 */
void *SystemSBGC32_Malloc (ui32 size)
{
	#if (SBGC_NEED_ASSERTS)
		if (!size) return NULL;
	#endif

	void *memoryPointer = NULL;

	if (tx_byte_allocate(&SBGC32_GeneralBytePool, &memoryPointer, size, TX_NO_WAIT) != TX_SUCCESS)
		SerialAPI_FatalErrorHandler();

	return memoryPointer;
}


/**	@brief	Suspends thread
 *
 *	@param	*threadHandle - pointer to thread handle
 */
void SystemSBGC32_SuspendThread (sbgcThread_t *threadHandle)
{
	retifnull_(threadHandle)

	sbgcThreadSuspend(threadHandle);
}


/**	@brief	Resumes thread
 *
 *	@param	*threadHandle - pointer to thread handle
 */
void SystemSBGC32_ResumeThread (sbgcThread_t *threadHandle)
{
	retifnull_(threadHandle)

	sbgcThreadResume(threadHandle);
}


/**	@brief	Switches current thread
 */
void SystemSBGC32_Yield (void)
{
	sbgcYield();
}


/**	@brief	Creates OS mutex
 *
 *	@param	*mutex - pointer to OS mutex object
 */
void SystemSBGC32_CreateMutex (sbgcMutex_t *mutex)
{
	retifnull_(mutex)

	if (sbgcCreateMutex(mutex) != TX_SUCCESS)
		SerialAPI_FatalErrorHandler();

	SBGC32_MutexCreated = sbgcTRUE;
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

	sbgcTakeMutex(mutex, TX_WAIT_FOREVER);
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

	UINT oldPriority;

	sbgcSetPrior(threadHandle, newPrior, &oldPriority);
}
/**	@}
 */

#endif /* SBGC_USE_AZURE_RTOS */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
