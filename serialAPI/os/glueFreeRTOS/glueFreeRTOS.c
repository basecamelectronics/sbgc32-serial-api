/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2
 *
 *	@file		glueFreeRTOS.c
 *
 *	@brief		Source OS glue file
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

#include	"../../sbgc32.h"


#if (SBGC_USE_FREE_RTOS)

/* Borrowed Functions  -------------------------------------------------
 */
extern sbgcCommandStatus_t PrivateSBGC32_EnterInit (sbgcGeneral_t *sbgcGeneral);
extern NORETURN__ sbgcThreadRetval_t SBGC32_HandlerThread (sbgcThreadArg_t threadArg);


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	FreeRTOS_Glue
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
	sbgcGeneral_t *sbgcGeneral = (sbgcGeneral_t*)threadArg;
	
	PrivateSBGC32_EnterInit(sbgcGeneral);
	
	#if (SBGC_NEED_ASSERTS)

		if (sbgcGeneral->_api->serialAPI_Status != serialAPI_OK)
		{
			/*  - - - - - - User Init Error Handler - - - - - - - */
			SerialAPI_FatalErrorHandler();
			/*  - - - - - - - - - - - - - - - - - - - - - - - - - */
		}

		else

	#endif

		{
			SystemSBGC32_CreateThread(SBGC32_HandlerThread, "SBGC32 Handler", SBGC_THREAD_STACK_SIZE,
									  sbgcGeneral, SBGC_THREAD_PRIOR, &sbgcGeneral->_api->threadHandle);
		}

	SystemSBGC32_DestroyThreadItself();
}


/**	@brief	Creates initialization thread
 *
 *	@param	*gSBGC - pointer to sbgcGeneral_t object
 */
void SystemSBGC32_Init (void *gSBGC)
{
	configSTACK_DEPTH_TYPE usStackDepth = configMINIMAL_STACK_SIZE;
	usStackDepth = (usStackDepth > 64) ? usStackDepth : 64;

	if (SystemSBGC32_CreateThread(SBGC32_InitThread, "SBGC32 Init", usStackDepth,
								  gSBGC, SBGC_THREAD_PRIOR, NULL) != pdPASS)
		SerialAPI_FatalErrorHandler();
}


/**	@brief	Removes the SBGC32 handler thread
 *
 *	@param	*gSBGC - pointer to sbgcGeneral_t object
 */
void SystemSBGC32_Deinit (void *gSBGC)
{
	sbgcGeneral_t *sbgcGeneral = (sbgcGeneral_t*)gSBGC;

	sbgcThreadDestroy(sbgcGeneral->_api->threadHandle);
}


/**	@brief	Creates new SBGC32 thread
 *
 *	@param	pxTaskCode - pointer to the task entry function
 *	@param	*pcName - a descriptive name for the task
 *	@param	usStackDepth - size of the task stack
 *	@param	*pvParameters - pointer to parameter for the task
 *	@param	uxPriority - priority at which the task should run
 *	@param	*pxCreatedTask - reference handle for created task
 *
 *	@return	Thread creation status
 */
BaseType_t SystemSBGC32_CreateThread (TaskFunction_t pxTaskCode, const char * const pcName,
									  const configSTACK_DEPTH_TYPE usStackDepth,
									  void * const pvParameters,
									  UBaseType_t uxPriority,
									  TaskHandle_t * const pxCreatedTask)
{
	return xTaskCreate(pxTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask);
}


/**	@brief	Destroys current thread
 */
void SystemSBGC32_DestroyThreadItself (void)
{
	sbgcThreadDestroy(NULL);

	while (1);
}


/**	@brief	Switches current thread
 */
void SystemSBGC32_Yield (void)
{
	sbgcYield();

	#if (SBGC_USE_ESPIDF_DRIVER)
		sbgcDelay(1);
	#endif
}


/**	@brief	Suspends thread
 *
 *	@param	*threadHandle - pointer to thread handle
 */
void SystemSBGC32_SuspendThread (sbgcThread_t *threadHandle)
{
	sbgcThreadSuspend(*threadHandle);
}


/**	@brief	Resumes thread
 *
 *	@param	*threadHandle - pointer to thread handle
 */
void SystemSBGC32_ResumeThread (sbgcThread_t *threadHandle)
{
	sbgcThreadResume(*threadHandle);
}


/**	@brief	Creates OS mutex
 *
 *	@param	*mutex - pointer to OS mutex object
 */
void SystemSBGC32_CreateMutex (sbgcMutex_t *mutex)
{
	sbgcCreateMutex(*mutex);
}


/**	@brief	Destroys OS mutex
 *
 *	@param	*mutex - pointer to OS mutex object
 */
void SystemSBGC32_DestroyMutex (sbgcMutex_t *mutex)
{
	sbgcDestroyMutex(*mutex);
}


/**	@brief	Takes OS mutex (Enter)
 *
 *	@param	*mutex - pointer to OS mutex object
 */
void SystemSBGC32_TakeMutex (sbgcMutex_t *mutex)
{
	sbgcTakeMutex(*mutex, portMAX_DELAY);
}


/**	@brief	Gives OS mutex (Exit)
 *
 *	@param	*mutex - pointer to OS mutex object
 */
void SystemSBGC32_GiveMutex (sbgcMutex_t *mutex)
{
	sbgcGiveMutex(*mutex);
}


/**	@brief	Changes the priority of a thread
 *
 *	@param	*threadHandle - pointer to thread handle
 *	@param	newPrior - new thread priority
 */
void SystemSBGC32_SetThreadPriority (sbgcThread_t *threadHandle, ui32 newPrior)
{
	sbgcSetPrior(*threadHandle, newPrior);
}
/**	@}
 */

#endif /* SBGC_USE_FREE_RTOS */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
