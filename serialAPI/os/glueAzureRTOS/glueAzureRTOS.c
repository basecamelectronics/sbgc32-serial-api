/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.1
 *
 *	@file		glueAzureRTOS.c
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
												SBGC_INIT_THREAD_STACK + SBGC_THREAD_STACK_SIZE + 256)
												/* May be expanded by user */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														  Static Objects
 */
/** Static SerialAPI's byte pool */
__ALIGN_BEGIN static UCHAR SBGC32_GeneralBytePoolBuffer [SBGC_AZURE_TX_MEM_POOL_SIZE] __ALIGN_END;

/** Static SerialAPI's byte pool handle object */
static TX_BYTE_POOL SBGC32_GeneralBytePool;

/** SerialAPI's initialization thread handler */
static TX_THREAD SystemSBGC32_InitThread;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
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

	PrivateSBGC32_EnterInit(gSBGC);

	#if (SBGC_NEED_ASSERTS)

		if (gSBGC->_api->serialAPI_Status != serialAPI_OK)
		{
			/*  - - - - - - User Init Error Handler - - - - - - - */
			(void)(1);
			/*  - - - - - - - - - - - - - - - - - - - - - - - - - */
		}

		else
		{
			/* Starting handler thread */
			TX_BYTE_POOL *systemSBGC32_HandlerBytePool = (TX_BYTE_POOL*)SystemSBGC32_Malloc(SBGC_THREAD_STACK_SIZE);

			if (systemSBGC32_HandlerBytePool == NULL)
				SerialAPI_FatalErrorHandler();

			if (tx_thread_create(&gSBGC->_api->threadHandle, "SBGC32 Handler", SBGC32_HandlerThread,
								 (ui32)(gSBGC), systemSBGC32_HandlerBytePool, SBGC_THREAD_STACK_SIZE,
								 SBGC_HANDLER_THREAD_PRIOR, 1, TX_NO_TIME_SLICE, TX_AUTO_START) != TX_SUCCESS)
				SerialAPI_FatalErrorHandler();
		}

	#endif

	SystemSBGC32_DestroyThreadItself();
}


/**	@brief	Initializes SerialAPI's byte pool.
 *			Creates initialization thread
 *
 *	@param	*gSBGC - pointer to sbgcGeneral_t object
 */
void SystemSBGC32_Init (void *gSBGC)
{
	if (tx_byte_pool_create(&SBGC32_GeneralBytePool, "SBGC32 Memory Pool", SBGC32_GeneralBytePoolBuffer,
							SBGC_AZURE_TX_MEM_POOL_SIZE) != TX_SUCCESS)
		SerialAPI_FatalErrorHandler();

	/* Starting init thread */
	TX_BYTE_POOL *systemSBGC32_InitBytePool = (TX_BYTE_POOL*)SystemSBGC32_Malloc(SBGC_INIT_THREAD_STACK);

	if (systemSBGC32_InitBytePool == NULL)
		SerialAPI_FatalErrorHandler();

	if (tx_thread_create(&SystemSBGC32_InitThread, "SBGC32 Init", SBGC32_InitThread,
						 (ui32)gSBGC, systemSBGC32_InitBytePool, SBGC_INIT_THREAD_STACK,
						 SBGC_THREAD_PRIOR_HIGH, 1, TX_NO_TIME_SLICE, TX_AUTO_START) != TX_SUCCESS)
		SerialAPI_FatalErrorHandler();
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


/**	@brief	Destroys current thread
 */
void SystemSBGC32_DestroyThreadItself (void)
{
	sbgcThreadDestroy(tx_thread_identify());
}


/**	@brief	Suspends thread
 *
 *	@param	*threadHandle - pointer to thread handle
 */
void SystemSBGC32_SuspendThread (sbgcThread_t *threadHandle)
{
	sbgcThreadSuspend(threadHandle);
}


/**	@brief	Resumes thread
 *
 *	@param	*threadHandle - pointer to thread handle
 */
void SystemSBGC32_ResumeThread (sbgcThread_t *threadHandle)
{
	sbgcThreadResume(threadHandle);
	sbgcYield();
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
	sbgcTakeMutex(mutex, TX_WAIT_FOREVER);
}


/**	@brief	Gives OS mutex (Exit)
 *
 *	@param	*mutex - pointer to OS mutex object
 */
void SystemSBGC32_GiveMutex (sbgcMutex_t *mutex)
{
	sbgcGiveMutex(mutex);
}


/**	@brief	Changes the priority of a thread
 *
 *	@param	*threadHandle - pointer to thread handle
 *	@param	newPrior - new thread priority
 */
void SystemSBGC32_SetThreadPriority (sbgcThread_t *threadHandle, ui32 newPrior)
{
	sbgcSetPrior(threadHandle, newPrior, &threadHandle->tx_thread_user_priority);
}
/**	@}
 */

#endif /* SBGC_USE_AZURE_RTOS */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
