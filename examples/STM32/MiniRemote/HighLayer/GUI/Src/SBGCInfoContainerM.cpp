/** ____________________________________________________________________
 *
 *	@file		SBGCInfoContainerM.cpp
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


GimbalMenuState_t CSBGCInfoContainerM::menuCurrentState;

ui8 activeAdjVarsCount = 0;
ui8 selectedAdjVarID;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *															 Fifth Level
 */
/* Attached Axis -------------------------------------------------------
 */
sMenuItem exsControlAttachedAxisItems [] =
{
	{ ITEM_TYPE_CHECKBOX, "ROLL", FUNC_TURN_ATTACHED_AXIS, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "PITCH", FUNC_TURN_ATTACHED_AXIS, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "YAW", FUNC_TURN_ATTACHED_AXIS, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "Not Assigned", FUNC_TURN_ATTACHED_AXIS, 0, NULL, NULL, NULL },

};

sMenu exsControlAttachedAxis =
{
	"Attached Axis",
	exsControlAttachedAxisItems,
	countof_(exsControlAttachedAxisItems)

};

sPrefMenu exsPrefControlAttachedAxis =
{
	&exsControlAttachedAxis,
	1,
	0,
	SBGC_MENU_CONTROL_ATTACHED_AXIS

};


/* Control Mode --------------------------------------------------------
 */
sMenuItem exsControlModeItems [] =
{
	{ ITEM_TYPE_CHECKBOX, "Abs. Control", FUNC_TURN_CONTROL_MODE, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "Inc. Control", FUNC_TURN_CONTROL_MODE, 0, NULL, NULL, NULL },
	{ ITEM_TYPE_CHECKBOX, "RC Control", FUNC_TURN_CONTROL_MODE, 0, NULL, NULL, NULL }

};

sMenu exsControlMode =
{
	"Control Mode",
	exsControlModeItems,
	countof_(exsControlModeItems)

};

sPrefMenu exsPrefControlMode =
{
	&exsControlMode,
	1,
	0,
	SBGC_MENU_CONTROL_MODE

};


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *															Fourth Level
 */
sMenuItem exsControlHandlerItems [] =
{
	{ ITEM_TYPE_FUNCTION, "Speed", FUNC_EDIT_CONTROL_SPEED, 0, 0, 0 },
	{ ITEM_TYPE_FUNCTION, "Low Pass Filter", FUNC_EDIT_CONTROL_LPF, 0, 0, 0 },
	{ ITEM_TYPE_FUNCTION, "Sensitivity", FUNC_EDIT_CONTROL_SENS, 0, 0, 0 },
	{ ITEM_TYPE_FUNCTION, "Exponent", FUNC_EDIT_CONTROL_EXP, 0, 0, 0 },
	{ ITEM_TYPE_CHECKBOX, "Inversion", FUNC_EDIT_CONTROL_INVERSION, 0, 0, 0 },
	{ ITEM_TYPE_MENU, "Attached Axis", 0, SBGC_MENU_CONTROL_ATTACHED_AXIS, &exsPrefControlAttachedAxis },
	{ ITEM_TYPE_MENU, "Control Mode", 0, SBGC_MENU_CONTROL_MODE, &exsPrefControlMode }

};

sMenu exsControlHandler =
{
	"Settings",
	exsControlHandlerItems,
	countof_(exsControlHandlerItems)

};

sPrefMenu exsPrefControlHandler =
{
	&exsControlHandler,
	1,
	0,
	SBGC_MENU_CONTROL_HANDLER_SETTINGS

};


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *															 Third Level
 */
sMenuItem exsControlProfileItems [] =
{
	{ ITEM_TYPE_MENU, "Joystick X", 0, 0, &exsPrefControlHandler },
	{ ITEM_TYPE_MENU, "Joystick Y", 0, 0, &exsPrefControlHandler },
	{ ITEM_TYPE_MENU, "Potentiometer", 0, 0, &exsPrefControlHandler }

};

sMenu exsControlProfile =
{
	"Handlers",
	exsControlProfileItems,
	countof_(exsControlProfileItems)

};

sPrefMenu exsPrefControlProfile =
{
	&exsControlProfile,
	1,
	0,
	SBGC_MENU_CONTROL_HANDLERS

};


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *															Second Level
 */
/* Board Info ----------------------------------------------------------
 */
sMenuItem exsSBGC32_BoardInfoItems [] =
{
	/* BoardInfo_t */
	{ ITEM_TYPE_VALUE, "Board Version", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Firmware Version", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "State Flags 1", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Board Features", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Connection Flag", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "FRW Extra ID", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Board Features Ext", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Main IMU Sens Model", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Frame IMU Sens Model", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Build Number", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Base FRW Version", 0, 0, NULL, NULL },

	/* BoardInfo3_t */
	{ ITEM_TYPE_VALUE, "Device ID", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "MCU ID", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "EEPROM Size", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Script Slot 1 Size", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Script Slot 2 Size", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Script Slot 3 Size", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Script Slot 4 Size", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Script Slot 5 Size", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Profile Set Slots", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Profile Set Cur", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "IMU Calib Info", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Script Slot 6 Size", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Script Slot 7 Size", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Script Slot 8 Size", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Script Slot 9 Size", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Script Slot 10 Size", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Hardware Flags", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Board Features Ext 2", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "CAN Drv Main Limit", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "CAN Drv Aux. Limit", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Adj Vars Total Num", 0, 0, NULL, NULL }

	/* reserved [10] */

};

sMenu exsSBGC32_BoardInfo =
{
	"Board Info",
	exsSBGC32_BoardInfoItems,
	countof_(exsSBGC32_BoardInfoItems)

};

sPrefMenu exsPrefSBGC32_BoardInfo =
{
	&exsSBGC32_BoardInfo,
	1,
	0,
	SBGC_MENU_BOARD_INFO

};


/* RealTime Data -------------------------------------------------------
 */
sMenuItem exsSBGC32_RealTimeDataItems [] =
{
	/* Realtime Data 3 */
	{ ITEM_TYPE_VALUE, "Acc Data [ROLL]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Gyro Data [ROLL]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Acc Data [PITCH]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Gyro Data [PITCH]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Acc Data [YAW]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Gyro Data [YAW]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Serial Error Count", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "System Error", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "System Sub Error", 0, 0, NULL, NULL },
	/* reserved [3] */
	{ ITEM_TYPE_VALUE, "RC Roll", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "RC Pitch", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "RC Yaw", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "RC Cmd", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Ext FC Roll", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Ext FC Pitch", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "IMU Angle [ROLL]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "IMU Angle [PITCH]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "IMU Angle [YAW]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Frame IMU Angle [ROLL]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Frame IMU Angle [PITCH]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Frame IMU Angle [YAW]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Target Angle [ROLL]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Target Angle [PITCH]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Target Angle [YAW]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Cycle Time", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "I2C Error Count", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Error Code", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Battery level", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "RT Data Flags", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Cur IMU", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Cur Profile", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Motor Power [ROLL]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Motor Power [PITCH]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Motor Power [YAW]", 0, 0, NULL, NULL },

	/* Realtime Data 4 */
	{ ITEM_TYPE_VALUE, "Frame Camera Angle [ROLL]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Frame Camera Angle [PITCH]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Frame Camera Angle [YAW]", 0, 0, NULL, NULL },
	/* reserved [1] */
	{ ITEM_TYPE_VALUE, "Balance Error [ROLL]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Balance Error [PITCH]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Balance Error [YAW]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Current", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Mag Data [ROLL]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Mag Data [PITCH]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Mag Data [YAW]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "IMU Temperature", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Frame IMU Temperature", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "IMU G Error", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "IMU H Error", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Motor Out [ROLL]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Motor Out [PITCH]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Motor Out [YAW]", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "Calib Mode", 0, 0, NULL, NULL },
	{ ITEM_TYPE_VALUE, "CAN IMU Ext Sens Err", 0, 0, NULL, NULL }
	/* reserved [28] */

};

sMenu exsSBGC32_RealTimeData =
{
	"Realtime Data",
	exsSBGC32_RealTimeDataItems,
	countof_(exsSBGC32_RealTimeDataItems)

};

sPrefMenu exsPrefSBGC32_RealTimeData =
{
	&exsSBGC32_RealTimeData,
	1,
	0,
	SBGC_MENU_REALTIME_DATA

};


/* RC Inputs -----------------------------------------------------------
 */
sPrefMenu exsPrefSBGC32_RC_Inputs;


/* AdjVars Data --------------------------------------------------------
 */
sPrefMenu exsPrefSBGC32_AdjvarsData;


/* Other AdjVars Data --------------------------------------------------
 */
sPrefMenu exsPrefSBGC32_AdjvarsDataOther;


/* Control Config ------------------------------------------------------
 */
sMenuItem exsSBGC32_ControlProfilesItems [] =
{
	{ ITEM_TYPE_MENU, "Profile 1", 0, 0, &exsPrefControlProfile },
	{ ITEM_TYPE_MENU, "Profile 2", 0, 0, &exsPrefControlProfile },
	{ ITEM_TYPE_MENU, "Profile 3", 0, 0, &exsPrefControlProfile }

};

sMenu exsSBGC32_ControlProfiles =
{
	"Control Profiles",
	exsSBGC32_ControlProfilesItems,
	countof_(exsSBGC32_ControlProfilesItems)

};

sPrefMenu exsPrefSBGC32_ControlProfiles =
{
	&exsSBGC32_ControlProfiles,
	1,
	0,
	SBGC_MENU_CONTROL_PROFILES

};


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *															 First Level
 */
/* Gimbal Info ---------------------------------------------------------
 */
sMenuItem exsSBGCInfoItems[] =
{
	{ ITEM_TYPE_MENU, "Board Info", 0, 0, &exsPrefSBGC32_BoardInfo },
	{ ITEM_TYPE_MENU, "Realtime Data", 0, 0, &exsPrefSBGC32_RealTimeData },
	{ ITEM_TYPE_MENU, "RC Inputs", 0, 0, &exsPrefSBGC32_RC_Inputs },
	{ ITEM_TYPE_MENU, "Adj. Vars. Data", 0, 0, &exsPrefSBGC32_AdjvarsData },
	{ ITEM_TYPE_MENU, "Control Profiles", 0, 0, &exsPrefSBGC32_ControlProfiles },
	{ ITEM_TYPE_FUNCTION, "Debug Console", FUNC_SET_STATE, DEBUG_CONSOLE_STATE, 0, 0 }

};

sMenu exsSBGCInfo =
{
	"Gimbal",
	exsSBGCInfoItems,
	countof_(exsSBGCInfoItems)
};

sPrefMenu exsPrefSBGCInfo =
{
	&exsSBGCInfo,
	1,
	0,
	SBGC_MENU_ROOT

};


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													 Glue-Data Functions
 */
static void ConvertDataToMenuElement (sMenuItem *arr, ui8 elementNumber, void* data, sbgcVarType_t dataType)
{
	char dataStrTemp [12];
	ui8 dataStrCount;

	switch (dataType)
	{
		case sbgcUCHAR :
		{
			ui8 dataTemp = *(ui8*)data;
			dataStrCount = sprintf_(dataStrTemp, "%u", dataTemp);

			break;
		}

		case sbgcUSHORT :
		{
			ui16 dataTemp = *(ui16*)data;
			dataStrCount = sprintf_(dataStrTemp, "%u", dataTemp);

			break;
		}

		case sbgcUINT :
		{
			ui32 dataTemp = *(ui32*)data;

			#ifdef _L32__
				dataStrCount = sprintf_(dataStrTemp, "%u", dataTemp);
			#else
				dataStrCount = sprintf_(dataStrTemp, "%lu", dataTemp);
			#endif

			break;
		}

		case sbgcCHAR :
		{
			i8 dataTemp = *(i8*)data;
			dataStrCount = sprintf_(dataStrTemp, "%i", dataTemp);

			break;
		}

		case sbgcSHORT :
		{
			i16 dataTemp = *(i16*)data;
			dataStrCount = sprintf_(dataStrTemp, "%i", dataTemp);

			break;
		}

		case sbgcINT :
		{
			i32 dataTemp = *(i32*)data;

			#ifdef _L32__
				dataStrCount = sprintf_(dataStrTemp, "%i", dataTemp);
			#else
				dataStrCount = sprintf_(dataStrTemp, "%li", dataTemp);
			#endif

			break;
		}

		case sbgcFLOAT :
		{
			float dataTemp = *(float*)data;
			dataStrCount = sprintf_(dataStrTemp, "%.3f", dataTemp);  // .3f is default. May be changed

			break;
		}

		default :
		/* Flag case */
		{
			if (dataType & sbgcFLAG)
				dataStrCount = sprintf_(dataStrTemp, "F.O.");  // Flag optimization

			break;
		}
	}

	arr[elementNumber].value = (char*)osMalloc(dataStrCount + 1);
	arr[elementNumber].value[dataStrCount] = '\0';  // Filling for strlen()
	memcpy((void*)arr[elementNumber].value, dataStrTemp, dataStrCount);
}


static void BoardInfoMenuInit (void)
{
	/* Reading board info */
	Gimbal.ReadBoardInfo(0, SCParam_FREEZE, SCPrior_NORMAL, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);

	if ((!Gimbal.GetCommunicationState()) &&
		(MiniRemote.GetDisconnectionMessageState() != DM_SHOWED))
		MiniRemote.SetDisconnectionMessageState(DM_NEED_TO_SHOW);

	/* Printing */
	ui8 i = 0;

	for (; i < boardInfoReferenceInfoArrayElCnt; i++)
	{
		ConvertDataToMenuElement(exsSBGC32_BoardInfoItems, i,
								 Gimbal.GetStructureElement(Gimbal.GetAddressBoardInfo(), PM_BOARD_INFO, i),
								 boardInfoReferenceInfoArray[i].type);
	}

	/* Device ID*/
	exsSBGC32_BoardInfoItems[i].value = (char*)osMalloc(sizeof("A.O."));
	memcpy(exsSBGC32_BoardInfoItems[i].value, BUFF_SIZE_("A.O."));
	i++;

	/* MCU ID */
	exsSBGC32_BoardInfoItems[i].value = (char*)osMalloc(sizeof("A.O."));
	memcpy(exsSBGC32_BoardInfoItems[i].value, BUFF_SIZE_("A.O."));

	i = 2;

	for (; i < boardInfo3_ReferenceInfoArrayElCnt; i++)
	{
		ConvertDataToMenuElement(exsSBGC32_BoardInfoItems, boardInfoReferenceInfoArrayElCnt + i,
								 Gimbal.GetStructureElement(Gimbal.GetAddressBoardInfo3(), PM_BOARD_INFO_3, i),
								 boardInfo3_ReferenceInfoArray[i].type);
	}
}


static void RealTimeMenuRewrite (void)
{
	ui8 elementsCount = 0;
	ui8 valuesCount = 0;  // Involving buffer's variables

	for (; elementsCount < realTimeDataReferenceInfoArrayElCnt; elementsCount++)
	{
		if (realTimeDataReferenceInfoArray[elementsCount].type != sbgcRCHAR)
		{
			if (realTimeDataReferenceInfoArray[elementsCount].length == 1)
			{
				ConvertDataToMenuElement(exsSBGC32_RealTimeDataItems, valuesCount,
										 Gimbal.GetStructureElement(Gimbal.GetAddressRealTimeData(), PM_REALTIME_DATA_4, elementsCount),
										 realTimeDataReferenceInfoArray[elementsCount].type);

				valuesCount++;
			}

			else
			{
				ui8 valueSize = Gimbal.GetAddressGeneralSBGC()->_api->typeToSize(realTimeDataReferenceInfoArray[elementsCount].type);

				for (ui8 i = 0; i < realTimeDataReferenceInfoArray[elementsCount].length; i++)
				{
					ConvertDataToMenuElement(exsSBGC32_RealTimeDataItems, valuesCount,
											 ((ui8*)(Gimbal.GetStructureElement(Gimbal.GetAddressRealTimeData(),
													 PM_REALTIME_DATA_4, elementsCount)) + (valueSize * i)),
											 realTimeDataReferenceInfoArray[elementsCount].type);
					valuesCount++;
				}
			}
		}
	}
}


static void ActiveAdjVarsMenuInit (void)
{
	activeAdjVarsCount = Gimbal.CountActiveAdjVars();

	exsPrefSBGC32_AdjvarsData.Menu = (sMenu*)osMalloc(sizeof(sMenu));

	exsPrefSBGC32_AdjvarsData.Menu->psItems = (sMenuItem*)osMalloc(sizeof(sMenuItem) * (activeAdjVarsCount + SBGC_MENU_ADJVARS_ADD_FUNC_NUM));
	memset(exsPrefSBGC32_AdjvarsData.Menu->psItems, 0, (sizeof(sMenuItem) * (activeAdjVarsCount + SBGC_MENU_ADJVARS_ADD_FUNC_NUM)));

	exsPrefSBGC32_AdjvarsData.Menu->nItems = activeAdjVarsCount + SBGC_MENU_ADJVARS_ADD_FUNC_NUM;
	exsPrefSBGC32_AdjvarsData.Menu->pszTitle = "Adj.Vars. Data";
	exsPrefSBGC32_AdjvarsData.nItems = 1;

	/* Reading active adjvars */
	if ((MiniRemote.Presets.adjVarsSync == AVS_GIMBAL_PRIORITY) &&
		(!SBGC_NoConnectionStateMask(Gimbal.GetCurrentState())))
	{
		Gimbal.ReadAllAdjVarValues(SCParam_FREEZE, SCPrior_NORMAL, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);

		if ((!Gimbal.GetCommunicationState()) && (MiniRemote.GetDisconnectionMessageState() != DM_SHOWED))
			MiniRemote.SetDisconnectionMessageState(DM_NEED_TO_SHOW);
	}

	/* Set adjvars preset */
	else if ((MiniRemote.Presets.adjVarsSync == AVS_REMOTE_PRIORITY) &&
			 (!SBGC_NoConnectionStateMask(Gimbal.GetCurrentState())))
	{
		Gimbal.SetAllAdjVarValues(Gimbal.Presets.AdjVarGeneral, SCParam_FREEZE, SCPrior_NORMAL, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);

		if ((!Gimbal.GetCommunicationState()) && (MiniRemote.GetDisconnectionMessageState() != DM_SHOWED))
			MiniRemote.SetDisconnectionMessageState(DM_NEED_TO_SHOW);
	}

	volatile ui8 elementsCount = 0;

	for (ui8 i = 0; i < SBGC_ADJ_VARS_MAX_QUANTITY; i++)
	{
		if (Gimbal.Presets.AdjVarGeneral[i].custom.activeFlag)
		{
			exsPrefSBGC32_AdjvarsData.Menu->psItems[elementsCount].ItemType = ITEM_TYPE_ADJVAR;
			exsPrefSBGC32_AdjvarsData.Menu->psItems[elementsCount].param = (ui32)&Gimbal.Presets.AdjVarGeneral[i].ID;
			ConvertDataToMenuElement(exsPrefSBGC32_AdjvarsData.Menu->psItems, elementsCount,
									 &Gimbal.Presets.AdjVarGeneral[i].value, sbgcSHORT);
			exsPrefSBGC32_AdjvarsData.Menu->psItems[elementsCount].pTitle = &adjVarsReferenceInfoArray[i].name[SBGC_ADJ_VAR_NAME_CUT];
			elementsCount++;
		}
	}

	/* Additional functions init */
	exsPrefSBGC32_AdjvarsData.Menu->psItems[elementsCount].ItemType = ITEM_TYPE_MENU;
	exsPrefSBGC32_AdjvarsData.Menu->psItems[elementsCount].pTitle = "Other Adj. Vars.";
	exsPrefSBGC32_AdjvarsData.Menu->psItems[elementsCount].pSubMenu = &exsPrefSBGC32_AdjvarsDataOther;
	elementsCount++;

	exsPrefSBGC32_AdjvarsData.Menu->psItems[elementsCount].ItemType = ITEM_TYPE_FUNCTION;
	exsPrefSBGC32_AdjvarsData.Menu->psItems[elementsCount].pTitle = "Save to Gimbal";
	exsPrefSBGC32_AdjvarsData.Menu->psItems[elementsCount].FuncID = FUNC_SAVE_ADJVARS_TO_GIMBAL;
	elementsCount++;

	exsPrefSBGC32_AdjvarsData.Menu->psItems[elementsCount].ItemType = ITEM_TYPE_FUNCTION;
	exsPrefSBGC32_AdjvarsData.Menu->psItems[elementsCount].pTitle = "Save to Remote";
	exsPrefSBGC32_AdjvarsData.Menu->psItems[elementsCount].FuncID = FUNC_SAVE_ADJVARS_TO_REMOTE;
	elementsCount++;

	exsPrefSBGC32_AdjvarsData.Menu->psItems[elementsCount].ItemType = ITEM_TYPE_FUNCTION;
	exsPrefSBGC32_AdjvarsData.Menu->psItems[elementsCount].pTitle = "Reset Adjvars";
	exsPrefSBGC32_AdjvarsData.Menu->psItems[elementsCount].FuncID = FUNC_RESET_ADJVARS;
	elementsCount++;

	exsPrefSBGC32_AdjvarsData.Menu->nItems = elementsCount;

	/* Comparing EEPROM and current adjvar values */
	for (ui8 i = 0; i < Gimbal.GetAdjVarsNumber(); i++)
	{
		if (Gimbal.EEPROM_AdjVarValues[i] != Gimbal.Presets.AdjVarGeneral[i].value)
		{
			Gimbal.adjVarsSyncState = AVSS_NOT_SYNCHRONIZED;
			return;
		}
	}

	Gimbal.adjVarsSyncState = AVSS_SYNCHRONIZED;
}


static void OtherAdjVarsMenuInit (void)
{
	ui8 otherAdjvarCount = SBGC_ADJ_VARS_MAX_QUANTITY - Gimbal.CountActiveAdjVars();

	exsPrefSBGC32_AdjvarsDataOther.Menu = (sMenu*)osMalloc(sizeof(sMenu));

	exsPrefSBGC32_AdjvarsDataOther.Menu->psItems = (sMenuItem*)osMalloc(sizeof(sMenuItem) * otherAdjvarCount);
	memset(exsPrefSBGC32_AdjvarsDataOther.Menu->psItems, 0, (sizeof(sMenuItem) * otherAdjvarCount));

	exsPrefSBGC32_AdjvarsDataOther.Menu->nItems = otherAdjvarCount;
	exsPrefSBGC32_AdjvarsDataOther.Menu->pszTitle = "Other Adj.Vars.";
	exsPrefSBGC32_AdjvarsDataOther.nItems = 1;

	/* Reading active adjvars */
	if ((MiniRemote.Presets.adjVarsSync == AVS_GIMBAL_PRIORITY) &&
		(!SBGC_NoConnectionStateMask(Gimbal.GetCurrentState())))
	{
		Gimbal.ReadAllAdjVarValues(SCParam_FREEZE, SCPrior_NORMAL, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);

		if ((!Gimbal.GetCommunicationState()) && (MiniRemote.GetDisconnectionMessageState() != DM_SHOWED))
			MiniRemote.SetDisconnectionMessageState(DM_NEED_TO_SHOW);
	}

	/* Set adjvars preset */
	else if ((MiniRemote.Presets.adjVarsSync == AVS_REMOTE_PRIORITY) &&
			 (!SBGC_NoConnectionStateMask(Gimbal.GetCurrentState())))
	{
		Gimbal.SetAllAdjVarValues(Gimbal.Presets.AdjVarGeneral, SCParam_FREEZE, SCPrior_NORMAL, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);

		if ((!Gimbal.GetCommunicationState()) && (MiniRemote.GetDisconnectionMessageState() != DM_SHOWED))
			MiniRemote.SetDisconnectionMessageState(DM_NEED_TO_SHOW);
	}


	volatile ui8 elementsCount = 0;

	for (ui8 i = 0; i < SBGC_ADJ_VARS_MAX_QUANTITY ; i++)
	{
		if (!Gimbal.Presets.AdjVarGeneral[i].custom.activeFlag)
		{
			exsPrefSBGC32_AdjvarsDataOther.Menu->psItems[elementsCount].ItemType = ITEM_TYPE_ADJVAR;
			exsPrefSBGC32_AdjvarsDataOther.Menu->psItems[elementsCount].param = (ui32)&Gimbal.Presets.AdjVarGeneral[i].ID;
			ConvertDataToMenuElement(exsPrefSBGC32_AdjvarsDataOther.Menu->psItems, elementsCount,
									 &Gimbal.Presets.AdjVarGeneral[i].value, sbgcSHORT);
			exsPrefSBGC32_AdjvarsDataOther.Menu->psItems[elementsCount].pTitle = &adjVarsReferenceInfoArray[i].name[SBGC_ADJ_VAR_NAME_CUT];
			elementsCount++;
		}
	}

	exsPrefSBGC32_AdjvarsDataOther.Menu->nItems = elementsCount;

	/* Comparing EEPROM and current adjvar values */
	for (ui8 i = 0; i < SBGC_ADJ_VARS_MAX_QUANTITY; i++)
	{
		if (Gimbal.EEPROM_AdjVarValues[i] != Gimbal.Presets.AdjVarGeneral[i].value)
		{
			Gimbal.adjVarsSyncState = AVSS_NOT_SYNCHRONIZED;
			return;
		}
	}

	Gimbal.adjVarsSyncState = AVSS_SYNCHRONIZED;
}


static void RC_InputValuesRewrite (void)
{
	ui8 activeChannelsCounter = 0;
	i16 percentValue;

	for (ui8 i = 0; i < MENU_RC_NUM_CHANNELS; i++)
	{
		if (Gimbal.GetAddressRC_Inputs()[i].RC_Src != sbgcRCMap_NO_SIGNAL)
		{
			percentValue = (Gimbal.GetAddressRC_Inputs()[i].RC_Val * 100) / 16384;

			ConvertDataToMenuElement(exsPrefSBGC32_RC_Inputs.Menu->psItems, activeChannelsCounter,
									 &percentValue, sbgcSHORT);

			activeChannelsCounter++;
		}
	}
}


static void RC_InputsMenuInit (void)
{
	ui8 RC_InputsNum = MENU_RC_NUM_CHANNELS;
	char RC_InputsNumBuff [12];

	Gimbal.AppoinRC_InputSource(0, sbgcRCMap_RC_INPUT_ROLL);
	Gimbal.AppoinRC_InputSource(1, sbgcRCMap_RC_INPUT_PITCH);
	Gimbal.AppoinRC_InputSource(2, sbgcRCMap_EXT_FC_INPUT_ROLL);
	Gimbal.AppoinRC_InputSource(3, sbgcRCMap_EXT_FC_INPUT_PITCH);
	Gimbal.AppoinRC_InputSource(4, sbgcRCMap_RC_INPUT_YAW);

	Gimbal.AppoinRC_InputSource(5, sbgcRCMap_ADC_1);
	Gimbal.AppoinRC_InputSource(6, sbgcRCMap_ADC_2);
	Gimbal.AppoinRC_InputSource(7, sbgcRCMap_ADC_3);

	Gimbal.ReadRC_Inputs(ICF_TRY_TO_INIT_INPUT, RC_InputsNum, SCParam_FREEZE, SCPrior_NORMAL, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);

	if (!Gimbal.GetCommunicationState())
	/* Connection is lost */
	{
		for (ui8 i = 0; i < MENU_RC_NUM_CHANNELS; i++)
			Gimbal.GetAddressRC_Inputs()[i].RC_Src = sbgcRCMap_NO_SIGNAL;

		RC_InputsNum = 0;
	}

	else
		for (ui8 i = 0; i < MENU_RC_NUM_CHANNELS; i++)
			if ((Gimbal.GetAddressRC_Inputs()[i].RC_Val == SBGC_RC_UNDEF_HR) ||
				(Gimbal.GetAddressRC_Inputs()[i].RC_Val == SBGC_RC_UNDEF))
			{
				Gimbal.GetAddressRC_Inputs()[i].RC_Src = sbgcRCMap_NO_SIGNAL;
				RC_InputsNum--;
			}

	Gimbal.SetRC_InputsActiveNum(RC_InputsNum);

	exsPrefSBGC32_RC_Inputs.Menu = (sMenu*)osMalloc(sizeof(sMenu));

	exsPrefSBGC32_RC_Inputs.Menu->psItems = (sMenuItem*)osMalloc(sizeof(sMenuItem) * RC_InputsNum);
	memset(exsPrefSBGC32_RC_Inputs.Menu->psItems, 0, sizeof(sMenuItem) * RC_InputsNum);

	exsPrefSBGC32_RC_Inputs.Menu->nItems = RC_InputsNum;
	exsPrefSBGC32_RC_Inputs.Menu->pszTitle = "RC Inputs";
	exsPrefSBGC32_RC_Inputs.nItems = 1;

	for (ui8 i = 0; i < RC_InputsNum; i++)
	{
		exsPrefSBGC32_RC_Inputs.Menu->psItems[i].ItemType = ITEM_TYPE_VALUE;

		sprintf_(RC_InputsNumBuff, "RC Input %d", i);
		exsPrefSBGC32_RC_Inputs.Menu->psItems[i].pTitle = (const char*)osMalloc(12);
		memcpy((void*)exsPrefSBGC32_RC_Inputs.Menu->psItems[i].pTitle, RC_InputsNumBuff, 12);

		exsPrefSBGC32_RC_Inputs.Menu->psItems[i].pSubMenu = &exsPrefSBGCInfo;

		RC_InputValuesRewrite();
	}
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													 	   Class Methods
 */
void CSBGCInfoContainerM::Init (void)
{
	static GWidgetInit wi;
	gwinWidgetClearInit(&wi);

	wi.g.show = FALSE;
	wi.g.x = 0;
	wi.g.y = 0;
	wi.g.width = gdispGetWidth();
	wi.g.height = gdispGetHeight();
	ghContainer = gwinContainerCreate(0, &wi, 0);
	wi.g.show = TRUE;
	wi.g.parent = ghContainer;

	ghMenu = 0;

	/* Title label */
	wi.g.width = DISPLAY_WIDTH - ((WIDGET_IMAGE_SIZE + WIDGET_IMAGE_CLEARANCE) * 2);
	wi.g.height = LARGE_FONT_HEIGHT + 2;
	wi.g.x = WIDGET_HOR_MARGIN + WIDGET_IMAGE_SIZE + WIDGET_IMAGE_CLEARANCE;
	wi.g.y = CONTAINER_TITLE_Y_MARGIN;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleLabelDimmed;
	wi.customParam = (void*)(justifyCenter | justifyMiddle);
	wi.customDraw = gwinLabelDrawJustifiedCustomMono;
	ghLabelTitle = gwinLabelCreate(0, &wi);
	gwinSetFont(ghLabelTitle, MiniRemote.GetLargeFont());

	/* Return arrow */
	static gdispImage *gdispImageBuff;
	Utils::imageOpenFile(gdispImageBuff, imagePathsReferenceArray[IPR_EXIT]);
	wi.g.x = WIDGET_HOR_MARGIN;
	wi.g.y = WIDGET_VERT_MARGIN;
	wi.g.height = gdispImageBuff->height;
	wi.g.width = gdispImageBuff->width;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
	wi.customDraw = gwinImageWOpenAndDrawCustom_Mono;
	wi.customParam = (void*)imagePathsReferenceArray[IPR_EXIT];
	ghImageReturn = gwinImageWCreate(0, &wi);
	Utils::imageCloseFile(gdispImageBuff);

	/* Adjvar synchronization arrow */
	Utils::imageOpenFile(gdispImageBuff, imagePathsReferenceArray[IPR_ADJ_VARS_SYNC]);
	wi.g.x = DISPLAY_WIDTH - WIDGET_IMAGE_SIZE - WIDGET_HOR_MARGIN;
	wi.g.y = WIDGET_VERT_MARGIN;
	wi.g.height = gdispImageBuff->height;
	wi.g.width = gdispImageBuff->width;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
	wi.customDraw = gwinImageWOpenAndDrawCustom_Mono;
	wi.customParam = (void*)imagePathsReferenceArray[IPR_ADJ_VARS_SYNC];
	ghImageSync = gwinImageWCreate(0, &wi);
	Utils::imageCloseFile(gdispImageBuff);
	gwinHide(ghImageSync);

	/* Dynamic structures pre-init */
	exsPrefSBGC32_RC_Inputs.menuType = SBGC_MENU_RC_INPUTS;
	exsPrefSBGC32_AdjvarsData.menuType = SBGC_MENU_ADJVARS_DATA;
	exsPrefSBGC32_AdjvarsDataOther.menuType = SBGC_MENU_OTHER_ADJVARS_DATA;

	/* Post-Init */
	CSBGCInfoContainerM::SwitchState(SBGC_MENU_ROOT);

	exsPrefSBGC32_AdjvarsData.nSelect = 0;
	exsPrefSBGC32_AdjvarsDataOther.nSelect = 0;
}


void CSBGCInfoContainerM::vTask (void *pvParameters)
{
	if (!EnterPrefMenu((sPrefMenu*)pvParameters))
	{
		CStateManager::SetState({ PREVIOUS_STATE, 0 });
		while (1);
	}

	gwinShow(ghContainer);

	NavigationDirection_t nav;
	ButtonState_t enterButton = BS_INIT;
	ButtonState_t exitButton = BS_INIT;

	TickType_t xRealTimeDataUpdateTime = osGetTickCount();

	TickType_t xNavigationBlockTime = osGetTickCount();
	while (osGetTickCount() < (xNavigationBlockTime + NAVIGATION_INIT_BLOCK_TIME));

	while (1)
	{
		MiniRemote.ProcessNavigationDirection();
		nav = MiniRemote.GetNavigationDirection();
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
				case SBGC_MENU_CONTROL_PROFILES :
					Gimbal.chosenProfile = ((GMenuObject*)ghMenu)->class_obj->SelectedItemIdx;
					break;

				case SBGC_MENU_CONTROL_HANDLERS :
					Gimbal.chosenHandler = ((GMenuObject*)ghMenu)->class_obj->SelectedItemIdx;
					break;

				case SBGC_MENU_CONTROL_ATTACHED_AXIS :
					for (ui8 i = 0; i < countof_(exsControlAttachedAxisItems); i++)
						exsPrefControlAttachedAxis.Menu->psItems[i].param = 0;

					break;

				case SBGC_MENU_CONTROL_MODE :
					for (ui8 i = 0; i < countof_(exsControlModeItems); i++)
						exsPrefControlMode.Menu->psItems[i].param = 0;

					break;

				default :
					break;
			}

			((GMenuObject*)ghMenu)->class_obj->ButtonEnter((GWidgetObject*)ghMenu);
		}

		if ((nav == ND_LEFT) || (exitButton == BS_PRESSED))
		{
			CStateManager::SetState({ PREVIOUS_STATE, 0 });
			while (1);
		}


		/* Realtime operations handling */
		if (GetState() == SBGC_MENU_ADJVARS_DATA || GetState() == SBGC_MENU_OTHER_ADJVARS_DATA)
		{
			if ((Gimbal.adjVarsSyncState == AVSS_SYNCHRONIZED) &&
				!SBGC_NoConnectionStateMask(Gimbal.GetCurrentState()))
				gwinShow(ghImageSync);

			else
				gwinHide(ghImageSync);
		}

		else if ((GetState() == SBGC_MENU_REALTIME_DATA) && (!SBGC_NoConnectionStateMask(Gimbal.GetCurrentState())))
		{
			if ((osGetTickCount() - xRealTimeDataUpdateTime) > REALTIME_DATA_UPDATE_TIME)
			{
				Gimbal.ReadRealTimeData(SCParam_NO, SCPrior_LOW, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);
				RealTimeMenuRewrite();

				for (ui8 i = 0; i < countof_(exsSBGC32_RealTimeDataItems); i++)
					osFree(exsSBGC32_RealTimeDataItems[i].value);

				xRealTimeDataUpdateTime = osGetTickCount();

				MiniRemote.SetRedrawMenuFlag(sbgcTRUE);
				MiniRemote.UpdateLastResponseTime();
			}
		}

		else if ((GetState() == SBGC_MENU_RC_INPUTS) && (!SBGC_NoConnectionStateMask(Gimbal.GetCurrentState())))
		{
			if ((osGetTickCount() - xRealTimeDataUpdateTime) > REALTIME_DATA_UPDATE_TIME)
			{
				Gimbal.ReadRC_Inputs(ICF_DONT_TRY_TO_INIT_INPUT, MENU_RC_NUM_CHANNELS,
						SCParam_NO, SCPrior_LOW, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);

				for (ui8 i = 0; i < Gimbal.GetRC_InputsActiveNum(); i++)
					RC_InputValuesRewrite();

				for (ui8 i = 0; i < Gimbal.GetRC_InputsActiveNum(); i++)
					osFree(exsPrefSBGC32_RC_Inputs.Menu->psItems[i].value);

				xRealTimeDataUpdateTime = osGetTickCount();

				MiniRemote.SetRedrawMenuFlag(sbgcTRUE);
				MiniRemote.UpdateLastResponseTime();
			}
		}

		((GMenuObject*)ghMenu)->class_obj->UpdateMenu((GWidgetObject*)ghMenu);

		osDelay(CONTAINER_PROCESS_DELAY);
	}
}


void CSBGCInfoContainerM::OnHide (void)
{
	/* Destroy dynamic objects */
	switch (CSBGCInfoContainerM::menuCurrentState)
	{
		case SBGC_MENU_BOARD_INFO :
			for (ui8 i = 0; i < countof_(exsSBGC32_BoardInfoItems); i++)
				osFree(exsSBGC32_BoardInfoItems[i].value);

			break;

		case SBGC_MENU_ADJVARS_DATA :
			for (ui8 i = 0; i < activeAdjVarsCount; i++)
				osFree(exsPrefSBGC32_AdjvarsData.Menu->psItems[i].value);

			osFree(exsPrefSBGC32_AdjvarsData.Menu->psItems);
			osFree(exsPrefSBGC32_AdjvarsData.Menu);

			gwinHide(ghImageSync);

			break;

		case SBGC_MENU_OTHER_ADJVARS_DATA :
			for (ui8 i = 0; i < (SBGC_ADJ_VARS_MAX_QUANTITY - activeAdjVarsCount); i++)
				osFree(exsPrefSBGC32_AdjvarsDataOther.Menu->psItems[i].value);

			osFree(exsPrefSBGC32_AdjvarsDataOther.Menu->psItems);
			osFree(exsPrefSBGC32_AdjvarsDataOther.Menu);

			exsPrefSBGC32_AdjvarsData.nSelect = activeAdjVarsCount;  // Other menu select return

			break;

		case SBGC_MENU_RC_INPUTS :
			for (ui8 i = 0; i < Gimbal.GetRC_InputsActiveNum(); i++)
				osFree((void*)exsPrefSBGC32_RC_Inputs.Menu->psItems[i].pTitle);

			osFree(exsPrefSBGC32_RC_Inputs.Menu->psItems);
			osFree(exsPrefSBGC32_RC_Inputs.Menu);

			break;

		default:
			break;
	}

	if (PrefMenu)
		PrefMenu->nSelect = ((GMenuObject *)ghMenu)->class_obj->SelectedItemIdx;

	if (ghMenu)
		gwinDestroy(ghMenu);
}


bool CSBGCInfoContainerM::EnterPrefMenu (sPrefMenu *menuPath)
{
	GWidgetInit wi;
	gwinWidgetClearInit(&wi);

	/* Menu */
	wi.g.show = TRUE;
	wi.g.parent = ghContainer;
	wi.g.width = ghContainer->width;
	wi.g.height = ghContainer->height - LARGE_FONT_HEIGHT - MENU_TITLE_INDENT;
	wi.g.y = LARGE_FONT_HEIGHT + MENU_TITLE_INDENT;
	wi.g.x = 0;
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;

	PrefMenu = menuPath;

	CSBGCInfoContainerM::SwitchState((GimbalMenuState_t)PrefMenu->menuType);

	Process(menuCurrentState);

	gwinSetText(ghLabelTitle, (const char*)PrefMenu->Menu->pszTitle, FALSE);
	ghMenu = CGWIN_Menu::Create(GDISP, 0, &wi, MENU_SBGC_INFO, (void*)PrefMenu->Menu, PrefMenu->nItems, PrefMenu->nSelect);

	return true;
}


void CSBGCInfoContainerM::Process (GimbalMenuState_t currentState)
{
	switch (currentState)
	{
		case SBGC_MENU_BOARD_INFO :
			Gimbal.ReadBoardInfo(0, SCParam_FREEZE, SCPrior_NORMAL, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);
			BoardInfoMenuInit();

			break;

		case SBGC_MENU_REALTIME_DATA :
			RealTimeMenuRewrite();
			break;

		case SBGC_MENU_ADJVARS_DATA :
			ActiveAdjVarsMenuInit();
			break;

		case SBGC_MENU_OTHER_ADJVARS_DATA :
			OtherAdjVarsMenuInit();
			break;

		case SBGC_MENU_RC_INPUTS :
			RC_InputsMenuInit();
			break;

		case SBGC_MENU_CONTROL_HANDLER_SETTINGS :
			exsPrefControlHandler.Menu->psItems[4].param = Gimbal.GetChosenControlHandler()->invert;
			break;

		case SBGC_MENU_CONTROL_ATTACHED_AXIS :
			for (ui8 i = 0; i < countof_(exsControlAttachedAxisItems); i++)
				exsPrefControlAttachedAxis.Menu->psItems[i].param = 0;

			exsPrefControlAttachedAxis.Menu->psItems[Gimbal.GetChosenControlHandler()->attachedAxis].param = 1;

			break;

		case SBGC_MENU_CONTROL_MODE :
			for (ui8 i = 0; i < countof_(exsControlModeItems); i++)
				exsPrefControlMode.Menu->psItems[i].param = 0;

			if (Gimbal.GetChosenControlHandler()->controlMode != GIMBAL_NO_CONTROL)
				exsPrefControlMode.Menu->psItems[Gimbal.GetChosenControlHandler()->controlMode - 1].param = 1;

			break;

		default :
			break;
	}
}
