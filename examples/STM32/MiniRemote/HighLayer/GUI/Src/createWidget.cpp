/** ____________________________________________________________________
 *
 *	@file		createWidget.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "createWidget.h"


GListener CCreateWidget::gl;

CAdjVarEditContainerM exCAdjVarEditContainerM;
CControlContainerM exCControlContainerM;
CDebugConsoleContainerM exCDebugConsoleContainerM;
CMainChoiceContainerM exCMainChoiceContainerM;
CMenuContainerM exCMenuContainerM;
CMessageWindowContainerM exCMessageWindowContainerM;
CSBGCInfoContainerM exCSBGCInfoContainerM;
CParameterEditContainerM exCParameterEditContainerM;
CPotentiometerCalibContainerM exCPotentiometerCalibContainerM;
CProfileContainerM exCProfileContainerM;
CShortcutContainerM exCShortcutContainerM;
CStickCalibContainerM exCStickCalibContainerM;

extern sPrefMenu exsPrefAdjVarsSync;
extern ShortcutParameters_t shortcutParametersReferenceArray [];


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														   Create Widget
 */
void CCreateWidget::Init (void)
{
	/* Set the widget defaults */
	gwinSetDefaultStyle(&BlackWidgetStyle, FALSE);

	GWidgetInit	wi;
	gwinWidgetClearInit(&wi);

	CXContainer *contArr [] =
	{
		&exCAdjVarEditContainerM,
		&exCControlContainerM,
		&exCDebugConsoleContainerM,
		&exCMainChoiceContainerM,
		&exCMenuContainerM,
		&exCMessageWindowContainerM,
		&exCSBGCInfoContainerM,
		&exCParameterEditContainerM,
		&exCPotentiometerCalibContainerM,
		&exCProfileContainerM,
		&exCShortcutContainerM,
		&exCStickCalibContainerM,
	};

	for (ui8 i = 0; i < countof_(contArr); ++i)
	{
		contArr[i]->Init();
		gwinHide(contArr[i]->GetContainer());
	}
}

void CCreateWidget::PreInit (void)
{
	/* Menu container */
	if (MiniRemote.Presets.adjVarsSync == AVS_GIMBAL_PRIORITY)
	{
		exsPrefAdjVarsSync.Menu->psItems[0].param = 0;
		exsPrefAdjVarsSync.Menu->psItems[1].param = 1;
	}

	for (ui8 i = 0; i < SHORTCUT_TOTAL_NUM; i++)
		shortcutParametersReferenceArray[i].currentPosition = MiniRemote.Presets.shortcutsOrderArr[i];
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														   State Manager
 */
ui8 CStateManager::stateStart;
ui8 CStateManager::stateEnd;
sDevState CStateManager::stateArr [STATE_LIFO_SIZE];
sDevState CStateManager::menuRoot;
sDevState CStateManager::currentState;

xQueueHandle CStateManager::xQueueSwitchState;


void CStateManager::Init (void)
{
	LIFO_Clear();

	menuRoot = { MAIN_CHOICE_STATE, 0 };

	xQueueSwitchState = xQueueCreate(4, sizeof(sDevState));
	osTaskCreate(vTaskSetState, "StateMachine", configMINIMAL_STACK_SIZE * 3, NULL, OS_HIGHEST_PRIORITY, NULL);
}


void CStateManager::SetState (sDevState State)
{
	xQueueSendToBack(xQueueSwitchState, &State, 0);
	taskYIELD();
}


void CStateManager::SetStateDirectly (sDevState State)
{
	LIFO_Clear();
	xQueueSendToBack(xQueueSwitchState, &State, 0);
	taskYIELD();
}


CXContainer *CStateManager::GetContainer (ui8 state)
{
	CXContainer *container = NULL;

	switch (state)
	{
		case ADJ_VAR_EDIT_STATE :
			container = &exCAdjVarEditContainerM;
			break;

		case CONTROL_STATE :
			container = &exCControlContainerM;
			break;

		case DEBUG_CONSOLE_STATE :
			container = &exCDebugConsoleContainerM;
			break;

		case MAIN_CHOICE_STATE :
			container = &exCMainChoiceContainerM;
			break;

		case REMOTE_MENU_STATE :
			container = &exCMenuContainerM;
			break;

		case MESSAGE_WINDOW_STATE :
			container = &exCMessageWindowContainerM;
			break;

		case PARAMETER_EDIT_STATE :
			container = &exCParameterEditContainerM;
			break;

		case POTENTIOMETER_CALIB_STATE:
			container = &exCPotentiometerCalibContainerM;
			break;

		case PROFILE_STATE :
			container = &exCProfileContainerM;
			break;

		case GIMBAL_MENU_STATE :
			container = &exCSBGCInfoContainerM;
			break;

		case SHORTCUT_STATE :
			container = &exCShortcutContainerM;
			break;

		case STICK_CALIB_STATE:
			container = &exCStickCalibContainerM;
			break;

		default:
			break;
	}

	return container;
}


void CStateManager::vTaskSetState (void *pvParameters)
{
	unused_(pvParameters);

	sDevState newState;
	bool prevStateFlag = 0;
	currentState = menuRoot;

	portBASE_TYPE xStatus;

	while (1)
	{
		xStatus = xQueueReceive(xQueueSwitchState, &newState, portMAX_DELAY);

		if (xStatus == pdPASS)
		{
			MiniRemote.UpdateLastResponseTime();

			if (newState.state == PREVIOUS_STATE)
			{
				LIFO_Remove(newState);
				prevStateFlag = true;
			}

			if ((currentState.state != newState.state) ||
				(currentState.Param != newState.Param))
			{
				if (prevStateFlag)
					prevStateFlag = false;

				else if (newState.state == REFRESH_THE_STATE)
					newState = currentState;

				else
					LIFO_Add(currentState);

				CXContainer *container = GetContainer(currentState.state);

				if (container)
				{
					gwinHide(container->GetContainer());

					HoldDisplayBuf();

					if (container->pxTask != NULL)
						osTaskDelete(container->pxTask);

					GiveDisplayBuf();

					container->OnHide();
				}

				container = GetContainer(newState.state);
				static ui32 *TaskParam;
				TaskParam = (ui32*)newState.Param;

				osDelay(1);

				if (container)
				{
					gwinHide(container->GetContainer());
					gwinEnable(container->GetContainer());
					container->OnShow(newState.Param);
					CCreateWidget::ClearContainerArea(container->GetContainer());

					osDelay(10);  // time to clear container area

					osTaskCreate([](void* o) { static_cast<CXContainer*>(o)->vTask((void*)TaskParam); },
								"GUI Container", configMINIMAL_STACK_SIZE * 10, container, OS_MEDIUM_PRIORITY, &container->pxTask);

					MiniRemote.SetRedrawPrimitiveObjectsFlag(sbgcTRUE);
				}

				currentState = newState;
			}
		}
	}
}

void CCreateWidget::ClearContainerArea (GHandle ghContainer)
{
	// Set the clipping region so we do not override the frame.
#if GDISP_NEED_CLIP
	gdispGSetClip(gdispGetDisplay(0), ghContainer->x, ghContainer->y, ghContainer->width, ghContainer->height);
#endif
	HoldDisplayBuf();

	// clear all
	gdispGFillArea(gdispGetDisplay(0), ghContainer->x, ghContainer->y, ghContainer->width, ghContainer->height, 0);
	GiveDisplayBuf();
}
