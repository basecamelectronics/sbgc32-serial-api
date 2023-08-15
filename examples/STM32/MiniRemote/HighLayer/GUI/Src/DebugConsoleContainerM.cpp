/** ____________________________________________________________________
 *
 *	@file		DebugConsoleContainerM.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "createWidget.h"
#include "gimbal.h"


ConsoleData_t ConsoleData;


void CDebugConsoleContainerM::ClearConsoleBuffer (void)
{
	gwinClear(ghContainer);

	memset(ConsoleData.CD_Buffer, 0, DEBUG_CONSOLE_BUFFER_SIZE);
	ConsoleData.CD_BufferHead = 0;
	ConsoleData.CD_BufferTail = 0;
	ConsoleData.CD_BufferPointer = 0;
	ConsoleData.updateFlag = 0;
}

void CDebugConsoleContainerM::Init (void)
{
	static GWindowInit wi;

	wi.show = FALSE;
	wi.x = 0;
	wi.y = 5;
	wi.width = gdispGetWidth();
	wi.height = gdispGetHeight() - 10;
	ghContainer = gwinConsoleCreate(0, &wi);
	wi.show = TRUE;
	wi.parent = ghContainer;

	gwinSetFont(ghContainer, MiniRemote.GetMediumFont());

	/* Set the fore- and background colors for each console */
	gwinSetColor(ghContainer, GFX_LIGHT_GRAY);
	gwinSetBgColor(ghContainer, GFX_BLACK);

	/* Clear all console windows - to set background */
	ClearConsoleBuffer();
}


void CDebugConsoleContainerM::OnHide (void)
{
	if (ghContainer)
		gwinHide(ghContainer);
}


void CDebugConsoleContainerM::vTask (void *pvParameters)
{
	unused_(pvParameters);

	gdispClear(gwinGetDefaultBgColor());
	gwinShow(ghContainer);

	gwinSetFont(ghContainer, MiniRemote.GetSmallFont());

	ButtonState_t exitButton = BS_INIT;

	while (1)
	{
		MiniRemote.ProcessNavigationDirection();
		MiniRemote.ProcessFunction(CSF_NAVIGATION_EXIT, &exitButton);

		if ((MiniRemote.GetNavigationDirection() == ND_LEFT) || (exitButton == BS_PRESSED))
		{
			CStateManager::SetState({ PREVIOUS_STATE, 0 });
			while (1);
		}

		/* System awaking */
		MiniRemote.UpdateLastResponseTime();

		vTaskDelay(CONTAINER_PROCESS_DELAY);

		if (osSemaphoreTake(Gimbal.xSemaphoreDebugConsole, 0) != pdTRUE)
			osSemaphoreTake(Gimbal.xSemaphoreDebugConsole, osMaxDelay);

		if (ConsoleData.updateFlag != 0)  // Printing...
		{
			gwinPrintf(ghContainer, (const char*)&ConsoleData.CD_Buffer[ConsoleData.CD_BufferPointer]);

			memset(ConsoleData.CD_Buffer, 0, ConsoleData.CD_BufferHead);
			ConsoleData.CD_BufferHead = 0;
			ConsoleData.CD_BufferPointer = 0;
			ConsoleData.updateFlag = 0;
		}

		else if (ConsoleData.emptyFlag != 0)
		{
			gwinClear(ghContainer);
			gwinPrintf(ghContainer, "Buffer is empty\n");
		}

		osSemaphoreGive(Gimbal.xSemaphoreDebugConsole);
	}
}
