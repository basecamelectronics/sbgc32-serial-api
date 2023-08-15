/** ____________________________________________________________________
 *
 *	@file		MenuContainerM.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "createWidget.h"
#include "gwinMenuPref.h"
#include "gimbal.h"


RemoteMenuState_t CMenuContainerM::menuCurrentState;

static volatile ui8 chosenMixChannel = 0;

ParameterHandle_t *mixMinHandle, *mixMaxHandle, *mixOffsetHandle, *mixMultiplierHandle, *mixAverageHandle;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *															Fourth Level
 */
/* Mixer Inputs --------------------------------------------------------
 */
sMenuItem exsMixInputsItems [] =
{
	{ ITEM_TYPE_CHECKBOX, "Digital Joy. X", PRPH_DIGITAL_JOYSTICK_CHANNEL_X, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "Digital Joy. Y", PRPH_DIGITAL_JOYSTICK_CHANNEL_Y, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "Abs. Encoder", PRPH_ABSOLUTE_ENCODER, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "Left Inc. Encoder", PRPH_LEFT_INCREMENTAL_ENCODER, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "Right Inc. Encoder", PRPH_RIGHT_INCREMENTAL_ENCODER, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "Potentiometer", PRPH_POTENTIOMETER, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "Left Encoder But.", PRPH_ENCODER1_BUTTON, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "Right Encoder But.", PRPH_ENCODER2_BUTTON, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "Button 1", PRPH_BUTTON1, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "Button 2", PRPH_BUTTON2, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "Toggle Switch 1", PRPH_TOGGLE_SWITCH1, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "Toggle Switch 2", PRPH_TOGGLE_SWITCH2, 0, NULL, NULL, NULL },

	{ ITEM_TYPE_CHECKBOX, "No Input", PRPH_NO_INPUT, 0, 0, 0 }

};


sMenu exsMixInputs =
{
	"Mix Inputs",
	exsMixInputsItems,
	countof_(exsMixInputsItems)

};


sPrefMenu exsPrefMixInputs =
{
	&exsMixInputs,
	1,
	0,
	REMOTE_MENU_MIX_CHANNEL_SETTINGS_INPUT

};


/* Mixer Outputs -------------------------------------------------------
 */
sMenuItem exsMixOutputsItems [] =
{
	{ ITEM_TYPE_CHECKBOX, "Navigation Enter", CSF_NAVIGATION_ENTER, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "Navigation Exit", CSF_NAVIGATION_EXIT, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "Navigation X", CSF_NAVIGATION_X, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "Navigation Y", CSF_NAVIGATION_Y, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "Parameter Edit", CSF_PARAMETER_CHANGE, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "SC Save Adjvars", VSF_SC_SAVE_ADJ_VARS, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "SC Menu Adjvars", VSF_SC_MENU_ADJ_VARS, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "SC Reset Adjvars", VSF_SC_RESET_ADJ_VARS, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "SC Control Toggle", VSF_NAVIGATION_CONTROL_TOGGLE, 0, NULL, NULL, NULL },

	{ ITEM_TYPE_CHECKBOX, "No Output", SF_NO, 0, 0, 0 }

};


sMenu exsMixOutputs =
{
	"Mix Outputs",
	exsMixOutputsItems,
	countof_(exsMixOutputsItems)

};


sPrefMenu exsPrefMixOutputs =
{
	&exsMixOutputs,
	1,
	0,
	REMOTE_MENU_MIX_CHANNEL_SETTINGS_OUTPUT

};


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *															 Third Level
 */
/* Mixer Settings ------------------------------------------------------
 */
sMenuItem exsMixSettingsItems [] =
{
	{ ITEM_TYPE_MENU, "Input", FUNC_EDIT_PARAMETER, 0, &exsPrefMixInputs, NULL, NULL },
	{ ITEM_TYPE_MENU, "Output", FUNC_EDIT_PARAMETER, 0, &exsPrefMixOutputs, NULL, NULL },
	{ ITEM_TYPE_FUNCTION, "Min", FUNC_EDIT_PARAMETER, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_FUNCTION, "Max", FUNC_EDIT_PARAMETER, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_FUNCTION, "Offset", FUNC_EDIT_PARAMETER, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_FUNCTION, "Multiplier", FUNC_EDIT_PARAMETER, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "Inversion", FUNC_EDIT_PARAMETER, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_FUNCTION, "Average", FUNC_EDIT_PARAMETER, 0, NULL, NULL, NULL }

};


sMenu exsMixSettings =
{
	"",
	exsMixSettingsItems,
	countof_(exsMixSettingsItems)

};


sPrefMenu exsPrefMixSettings =
{
	&exsMixSettings,
	1,
	0,
	REMOTE_MENU_MIX_CHANNEL_SETTINGS

};


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *															Second Level
 */
/* Communication Way ---------------------------------------------------
 */
sMenuItem exsCommunicationWayItems [] =
{
	{ ITEM_TYPE_CHECKBOX, "UART", FUNC_SWITCH_COMMUNICATION_WAY, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "RS-422", FUNC_SWITCH_COMMUNICATION_WAY, 0, NULL, NULL, NULL },

};


sMenu exsCommunicationWay =
{
	"Communic. Way",
	exsCommunicationWayItems,
	countof_(exsCommunicationWayItems)

};


sPrefMenu exsPrefCommunicationWay =
{
	&exsCommunicationWay,
	1,
	0,
	REMOTE_MENU_COMMUNICATION_WAY

};


/* Mix channels --------------------------------------------------------
 */
sPrefMenu exsPrefMixChannels;


/* AdjVars synchronization priorities ----------------------------------
 */
sMenuItem exsAdjVarsSyncItems [] =
{
	{ ITEM_TYPE_CHECKBOX, "Remote Priority", FUNC_SWITCH_AV_SYNC_PRIORITY, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "Gimbal Priority", FUNC_SWITCH_AV_SYNC_PRIORITY, 0, NULL, NULL, NULL },

};


sMenu exsAdjVarsSync =
{
	"Adj. Vars. Sync.",
	exsAdjVarsSyncItems,
	countof_(exsAdjVarsSyncItems)

};


sPrefMenu exsPrefAdjVarsSync =
{
	&exsAdjVarsSync,
	1,
	0,
	REMOTE_MENU_ADJ_VARS_SYNC_PRIORITY

};


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *															 First Level
 */
/* Remote menu root ----------------------------------------------------
 */
sMenuItem exsRemoteMenuItems [] =
{
	{ ITEM_TYPE_MENU, "Communic. Way", 0, 0, &exsPrefCommunicationWay, NULL, NULL },
	{ ITEM_TYPE_MENU, "Mixer Settings", 0, 0, &exsPrefMixChannels, NULL, NULL },
	{ ITEM_TYPE_FUNCTION, "Joystick Calib.", FUNC_SET_STATE, STICK_CALIB_STATE, NULL, NULL, NULL },
	{ ITEM_TYPE_FUNCTION, "Potentiometer Calib.", FUNC_SET_STATE, POTENTIOMETER_CALIB_STATE, NULL, NULL, NULL },
	{ ITEM_TYPE_FUNCTION, "Backlight", FUNC_EDIT_SYSTEM_BRIGHTNESS, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_FUNCTION, "Backlight Dimming", FUNC_EDIT_SYSTEM_EE_RATIO, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_FUNCTION, "Backlight Dim. Time", FUNC_EDIT_SYSTEM_EE_TIMER, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_MENU, "Adj. Vars. Sync.", 0, 0, &exsPrefAdjVarsSync, NULL, NULL },
	{ ITEM_TYPE_FUNCTION, "Restart", FUNC_RESTART, 0, NULL, NULL, NULL }

};


sMenu exsRemoteMenu =
{
	"Remote",
	exsRemoteMenuItems,
	countof_(exsRemoteMenuItems)

};


sPrefMenu exsPrefRemoteMenu =
{
	&exsRemoteMenu,
	1,
	0,
	REMOTE_MENU_ROOT

};


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													 Glue-Data Functions
 */
static void MixChannelsMenuInit (void)
{
	ui8 mixChannelNumBuffLength = 20;
	char mixChannelNumBuff [mixChannelNumBuffLength];

	exsPrefMixChannels.Menu = (sMenu*)osMalloc(sizeof(sMenu));

	exsPrefMixChannels.Menu->psItems = (sMenuItem*)osMalloc(sizeof(sMenuItem) * MIX_CHANNELS_TOTAL_NUMBER);
	memset(exsPrefMixChannels.Menu->psItems, 0, sizeof(sMenuItem) * MIX_CHANNELS_TOTAL_NUMBER);

	exsPrefMixChannels.Menu->nItems = MIX_CHANNELS_TOTAL_NUMBER;
	exsPrefMixChannels.Menu->pszTitle = "Mixer Settings";
	exsPrefMixChannels.nItems = 1;
	exsPrefMixChannels.menuType = REMOTE_MENU_MIX_CHANNELS;

	for (ui8 i = 0; i < MIX_CHANNELS_TOTAL_NUMBER; i++)
	{
		char mixerFunctionsState [3] = {0};

		exsPrefMixChannels.Menu->psItems[i].ItemType = ITEM_TYPE_MENU;

		if (MiniRemote.Presets.mixChannel[i].source != MIX_HAVENO_INPUT)
			mixerFunctionsState[0] = '*';

		if (MiniRemote.Presets.mixChannel[i].target != MIX_HAVENO_OUTPUT)
		{
			if (mixerFunctionsState[0] == '*')
				mixerFunctionsState[1] = '#';

			else
				mixerFunctionsState[0] = '#';
		}

		sprintf_(mixChannelNumBuff, "Mix Channel %d %s", (ui8)MiniRemote.Presets.mixChannel[i].number, mixerFunctionsState);

		exsPrefMixChannels.Menu->psItems[i].pTitle = (const char*)osMalloc(mixChannelNumBuffLength);
		memcpy((void*)exsPrefMixChannels.Menu->psItems[i].pTitle, mixChannelNumBuff, mixChannelNumBuffLength);

		exsPrefMixChannels.Menu->psItems[i].pSubMenu = &exsPrefMixSettings;

		exsPrefMixChannels.Menu->psItems[i].param = (ui32)&MiniRemote.Presets.mixChannel[i];
	}
}


static void MixChannelSettingsMenuInit (void)
{
	mixMinHandle = (ParameterHandle_t*)osMalloc(sizeof(ParameterHandle_t));
	mixMaxHandle = (ParameterHandle_t*)osMalloc(sizeof(ParameterHandle_t));
	mixOffsetHandle = (ParameterHandle_t*)osMalloc(sizeof(ParameterHandle_t));
	mixMultiplierHandle = (ParameterHandle_t*)osMalloc(sizeof(ParameterHandle_t));
	mixAverageHandle = (ParameterHandle_t*)osMalloc(sizeof(ParameterHandle_t));

	*mixMinHandle = { FUNC_EDIT_PARAMETER, NULL, 1.0F, 0, 0, IN_MIN_VALUE, IN_MAX_VALUE, _SIGNED_INT_, "Min", 0, 0, 0, 0, 0, 0};
	*mixMaxHandle = { FUNC_EDIT_PARAMETER, NULL, 1.0F, 0, 0, IN_MIN_VALUE, IN_MAX_VALUE, _SIGNED_INT_, "Max", 0, 0, 0, 0, 0, 0};
	*mixOffsetHandle = { FUNC_EDIT_PARAMETER, NULL, 1.0F, 0, 0, MIN_MIX_OFFSET, MAX_MIX_OFFSET, _SIGNED_INT_, "Offset", 0, 0, 0, 0, 0, 0};
	*mixMultiplierHandle = { FUNC_EDIT_PARAMETER, NULL, 1.0F, 0, 0, MIN_MIX_MPL, MAX_MIX_MPL, _SIGNED_INT_, "Multiplier", 0, 0, 0, 0, 0, 0};
	*mixAverageHandle = { FUNC_EDIT_PARAMETER, NULL, 1.0F, 0, 0, MIN_MIX_AVERAGE, MAX_MIX_AVERAGE, _SIGNED_INT_, "Average", 0, 0, 0, 0, 0, 0};

	mixMinHandle->initValue = MiniRemote.Presets.mixChannel[chosenMixChannel].min;
	mixMaxHandle->initValue = MiniRemote.Presets.mixChannel[chosenMixChannel].max;
	mixOffsetHandle->initValue = MiniRemote.Presets.mixChannel[chosenMixChannel].offset;
	mixMultiplierHandle->initValue = MiniRemote.Presets.mixChannel[chosenMixChannel].multiplier;
	mixAverageHandle->initValue = MiniRemote.Presets.mixChannel[chosenMixChannel].average;

	mixMinHandle->operatingValue = &MiniRemote.Presets.mixChannel[chosenMixChannel].min;
	mixMaxHandle->operatingValue = &MiniRemote.Presets.mixChannel[chosenMixChannel].max;
	mixOffsetHandle->operatingValue = &MiniRemote.Presets.mixChannel[chosenMixChannel].offset;
	mixMultiplierHandle->operatingValue = &MiniRemote.Presets.mixChannel[chosenMixChannel].multiplier;
	mixAverageHandle->operatingValue = &MiniRemote.Presets.mixChannel[chosenMixChannel].average;

	mixAverageHandle->typeValue = _UNSIGNED_SHORT_;
	mixMaxHandle->typeValue = _UNSIGNED_SHORT_;
	mixOffsetHandle->typeValue = _SIGNED_INT_;
	mixMultiplierHandle->typeValue = _FLOAT_;
	mixAverageHandle->typeValue = _UNSIGNED_CHAR_;

	/* Title */
	char mixChannelTitle [15] = {0};
	sprintf(mixChannelTitle, "Mix Channel %d", chosenMixChannel);

	exsPrefMixSettings.Menu->pszTitle = (const char*)osMalloc(strlen(mixChannelTitle));
	memcpy((void*)exsPrefMixSettings.Menu->pszTitle, mixChannelTitle, sizeof(mixChannelTitle));

	/* Coefficients */
	exsPrefMixSettings.Menu->psItems[2].param = (ui32)mixMinHandle;
	exsPrefMixSettings.Menu->psItems[3].param = (ui32)mixMaxHandle;
	exsPrefMixSettings.Menu->psItems[4].param = (ui32)mixOffsetHandle;
	exsPrefMixSettings.Menu->psItems[5].param = (ui32)mixMultiplierHandle;
	exsPrefMixSettings.Menu->psItems[7].param = (ui32)mixAverageHandle;

	/* Inversion */
	exsPrefMixSettings.Menu->psItems[6].param = (ui32)&MiniRemote.Presets.mixChannel[chosenMixChannel].inversion;

	/* Input */
	for (ui8 i = 0; i < countof_(exsMixInputsItems); i++)
		exsPrefMixInputs.Menu->psItems[i].param = 0;

	if (MiniRemote.Presets.mixChannel[chosenMixChannel].source == MIX_HAVENO_INPUT)
		exsPrefMixInputs.Menu->psItems[countof_(exsMixInputsItems) - 1].param = 1;

	else
		for (ui8 i = 0; i < countof_(exsMixInputsItems); i++)
			if (MiniRemote.Presets.mixChannel[chosenMixChannel].source->GetID() == exsPrefMixInputs.Menu->psItems[i].FuncID)
				exsPrefMixInputs.Menu->psItems[i].param = 1;

	/* Output */
	for (ui8 i = 0; i < countof_(exsMixOutputsItems); i++)
		exsPrefMixOutputs.Menu->psItems[i].param = 0;

	if (MiniRemote.Presets.mixChannel[chosenMixChannel].target == MIX_HAVENO_OUTPUT)
		exsPrefMixOutputs.Menu->psItems[countof_(exsMixOutputsItems) - 1].param = 1;

	else
		for (ui8 i = 0; i < countof_(exsMixOutputsItems); i++)
			if (MiniRemote.Presets.mixChannel[chosenMixChannel].target->ID == exsPrefMixOutputs.Menu->psItems[i].FuncID)
				exsPrefMixOutputs.Menu->psItems[i].param = 1;
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													 	   Class Methods
 */
void CMenuContainerM::Init (void)
{
	static GWidgetInit wi;
	gwinWidgetClearInit(&wi);

	/* Container */
	wi.g.show = FALSE;
	wi.g.x = 0;
	wi.g.y = 0;
	wi.g.width = gdispGetWidth();
	wi.g.height = gdispGetHeight();
	ghContainer = gwinContainerCreate(0, &wi, 0);
	wi.g.show = TRUE;
	wi.g.parent = ghContainer;

	ghMenu = 0;

	static gdispImage *gdispImageReturn;
	Utils::imageOpenFile(gdispImageReturn, imagePathsReferenceArray[IPR_ARROW_RETURN_LEFT]);
	wi.g.x = 0;
	wi.g.y = 0;
	wi.g.height = gdispImageReturn->height;
	wi.g.width = gdispImageReturn->width;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
	wi.customDraw = gwinImageWOpenAndDrawCustom_Mono;
	wi.customParam = (void*)imagePathsReferenceArray[IPR_ARROW_RETURN_LEFT];
	ghImageReturn = gwinImageWCreate(0, &wi);
	Utils::imageCloseFile(gdispImageReturn);

	/* Title label */
	wi.g.x = wi.g.height;
	wi.g.width = ghContainer->width - (WIDGET_IMAGE_SIZE * 2);
	wi.g.height = LARGE_FONT_HEIGHT + 2;
	wi.g.y = 1;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleLabelDimmed;
	wi.customParam = (void*)(justifyCenter | justifyMiddle);
	wi.customDraw = gwinLabelDrawJustifiedCustomMono;
	ghLabelTitle = gwinLabelCreate(0, &wi);
	gwinSetFont(ghLabelTitle, MiniRemote.GetLargeFont());

	/* Dynamic structures pre-init */
	exsPrefMixChannels.menuType = REMOTE_MENU_MIX_CHANNELS;
}


void CMenuContainerM::vTask (void *pvParameters)
{
	if (!EnterPrefMenu((sPrefMenu*)pvParameters))
		CStateManager::SetState({ PREVIOUS_STATE, 0 });

	gwinShow(ghContainer);
	gwinSetText(ghLabelTitle, (const char*)PrefMenu->Menu->pszTitle, FALSE);

	NavigationDirection_t nav;
	ButtonState_t enterButton = BS_INIT;
	ButtonState_t exitButton = BS_INIT;

	TickType_t xNavigationBlockTime = osGetTickCount();
	while (osGetTickCount() < (xNavigationBlockTime + NAVIGATION_INIT_BLOCK_TIME));

	while (1)
	{
		MiniRemote.ProcessNavigationDirection();
		nav =  MiniRemote.GetNavigationDirection();
		MiniRemote.ProcessFunction(CSF_NAVIGATION_ENTER, &enterButton);
		MiniRemote.ProcessFunction(CSF_NAVIGATION_EXIT, &exitButton);

		/* Navigation handle */
		if ((nav == ND_UP) || (nav == (ND_UP | ND_CONTINUOUS)))
			((GMenuObject*)ghMenu)->class_obj->ButtonUp((GWidgetObject*)ghMenu);

		if ((nav == ND_DOWN) || (nav == (ND_DOWN | ND_CONTINUOUS)))
			((GMenuObject*)ghMenu)->class_obj->ButtonDown((GWidgetObject*)ghMenu);

		if ((nav == ND_RIGHT) || (enterButton == BS_PRESSED))
		{
			switch (GetState())
			{
				case REMOTE_MENU_COMMUNICATION_WAY :
					for (ui8 i = 0; i < countof_(exsCommunicationWayItems); i++)
						exsPrefCommunicationWay.Menu->psItems[i].param = 0;

					break;

				case REMOTE_MENU_ADJ_VARS_SYNC_PRIORITY :
					for (ui8 i = 0; i < countof_(exsAdjVarsSyncItems); i++)
						exsPrefAdjVarsSync.Menu->psItems[i].param = 0;

					break;

				case REMOTE_MENU_MIX_CHANNELS :
					chosenMixChannel = (ui8)MiniRemote.Presets.mixChannel[((GMenuObject*)ghMenu)->class_obj->SelectedItemIdx].number;
					break;

				case REMOTE_MENU_MIX_CHANNEL_SETTINGS_INPUT :
					MiniRemote.SetMixInput(&MiniRemote.Presets.mixChannel[chosenMixChannel],
										   (InputID_t)((GMenuObject*)ghMenu)->class_obj->GetSelectedItem()->FuncID);

					for (ui8 i = 0; i < countof_(exsMixInputsItems); i++)
						exsPrefMixInputs.Menu->psItems[i].param = 0;

					break;


				case  REMOTE_MENU_MIX_CHANNEL_SETTINGS_OUTPUT :
					MiniRemote.SetMixOutput(&MiniRemote.Presets.mixChannel[chosenMixChannel],
											(SystemFunctionID_t)((GMenuObject*)ghMenu)->class_obj->GetSelectedItem()->FuncID);

					for (ui8 i = 0; i < countof_(exsMixOutputsItems); i++)
						exsPrefMixOutputs.Menu->psItems[i].param = 0;

					break;

				default :
					break;
			}

			((GMenuObject*)ghMenu)->class_obj->ButtonEnter((GWidgetObject*)ghMenu);
		}

		if ((nav == ND_LEFT) || (exitButton == BS_PRESSED))
			CStateManager::SetState({ PREVIOUS_STATE, 0 });

		/* One-time drawing objects handle */
		if (oneTimeDrawObjectsFlag)
		{
			gdispFillStringBoxSimple(MENU_ITEM_HOR_PAD, ADJ_VARS_SYNC_NOTE_Y_COORD,
									 ghContainer->width - (MESSAGE_WINDOW_MARGINS * 2), ADJ_VARS_SYNC_NOTE_HEIGHT,
									 (char*)"Where to save values between sessions ", MiniRemote.GetSmallFont(),
									 GFX_DARK_GRAY, GFX_BLACK, (gJustify)(gJustifyCenter | gJustifyMiddle));

			oneTimeDrawObjectsFlag = FALSE__;
		}


		osDelay(CONTAINER_PROCESS_DELAY);
	}
}


void CMenuContainerM::OnHide (void)
{
	/* Destroy dynamic objects */
	switch (CMenuContainerM::menuCurrentState)
	{
		case REMOTE_MENU_MIX_CHANNELS :
			for (ui8 i = 0; i < exsPrefMixChannels.Menu->nItems; i++)
				osFree((void*)exsPrefMixChannels.Menu->psItems[i].pTitle);

			osFree(exsPrefMixChannels.Menu->psItems);
			osFree(exsPrefMixChannels.Menu);
			break;

		case REMOTE_MENU_MIX_CHANNEL_SETTINGS :
			osFree((void*)exsPrefMixSettings.Menu->psItems[2].param);
			osFree((void*)exsPrefMixSettings.Menu->psItems[3].param);
			osFree((void*)exsPrefMixSettings.Menu->psItems[4].param);
			osFree((void*)exsPrefMixSettings.Menu->psItems[5].param);
			osFree((void*)exsPrefMixSettings.Menu->psItems[7].param);
			break;

		default:
			break;
	}

	if (PrefMenu)
		PrefMenu->nSelect = ((GMenuObject*)ghMenu)->class_obj->SelectedItemIdx;

	if (ghMenu)
		gwinDestroy(ghMenu);
}


bool CMenuContainerM::EnterPrefMenu (sPrefMenu *menuPath)
{
	GWidgetInit wi;
	gwinWidgetClearInit(&wi);

	/* Menu */
	wi.g.show = TRUE;
	wi.g.parent = ghContainer;
	wi.g.width = ghContainer->width;
	wi.g.height = ghContainer->height - 20;
	wi.g.y = 20;
	wi.g.x = 0;
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;

	PrefMenu = menuPath;

	CMenuContainerM::SwitchState((RemoteMenuState_t)PrefMenu->menuType);

	if (PrefMenu->menuType == REMOTE_MENU_ADJ_VARS_SYNC_PRIORITY)
		oneTimeDrawObjectsFlag = TRUE__;

	Process(menuCurrentState);

	gwinSetText(ghLabelTitle, (const char*)PrefMenu->Menu->pszTitle, FALSE);
	ghMenu = CGWIN_Menu::Create(GDISP, 0, &wi, MENU_REMOTE, (void*)PrefMenu->Menu, PrefMenu->nItems, PrefMenu->nSelect);
	return true;
}


void CMenuContainerM::Process (RemoteMenuState_t currentState)
{
	switch (currentState)
	{
		case REMOTE_MENU_MIX_CHANNELS :
			MixChannelsMenuInit();
			break;

		case REMOTE_MENU_MIX_CHANNEL_SETTINGS :
			MixChannelSettingsMenuInit();
			break;

		default :
			break;
	}
}
