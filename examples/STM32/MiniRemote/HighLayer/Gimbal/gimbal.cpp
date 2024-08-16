/** ____________________________________________________________________
 *
 *	@file		gimbal.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "gimbal.h"


SBGC32_System Gimbal;

static sbgcControlMode_t controlModes [] =
{
	CtrlMODE_NO_CONTROL,							// GIMBAL_NO_CONTROL
	CtrlMODE_ANGLE,									// GIMBAL_ABSOLUTE_CONTROL
	CtrlMODE_SPEED,									// GIMBAL_INCREMENTAL_CONTROL
	CtrlMODE_RC										// GIMBAL_RC_CONTROL

};


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *												  Class Protocol Methods
 */
void SBGC32_System::Init (SBGC_ADVANCED_PARAMS_)
{
	osSemaphoreCreate(xSemaphoreDebugConsole);
	osSemaphoreGive(xSemaphoreDebugConsole);

	DriverSBGC32.Init(MiniRemote.Presets.communicationWay);

	SerialAPI_LinkDriver(&GeneralSBGC, DriverSBGC32_UartTransmitData, DriverSBGC32_UartReceiveByte, DriverSBGC32_GetAvailableBytes,
						 DriverSBGC32_UartTransmitDebugData, DriverSBGC32_GetTimeMs);

	DriverSBGC32_Init(&GeneralSBGC._ll->drv, DriverSBGC32.GetAddressUART_Handle(), NULL);

	SBGC32_Init(&GeneralSBGC);

	GeneralSBGC._ll->drvTxDebug = FillConsoleDataArr;

	/* Waiting for initialization finish */
	while (GeneralSBGC._api->commandNumber);

	/* Parameters load handle */
	if (GetCommunicationState())
		RecoverParameters(SBGC_ADVANCED_ARGS_);

	/* Other */
	processStatus = PROCESS_READY;
	adjVarsSyncState = AVSS_NOT_SYNCHRONIZED;

//	return GetParserCurrentStatus();
}


void SBGC32_System::ResetDriver (SBGC_DRV_UART_TYPE_DEF__ *uart, SBGC_DRV_TIMER_TYPE_DEF__ *tim)
{
	DriverSBGC32_Deinit(&GeneralSBGC._ll->drv);
	DriverSBGC32_Init(&GeneralSBGC._ll->drv, uart, tim);

	/* It's need to re-init ADC, cause it is placed onto the same DMA */
	Potentiometer.Init();
}


void SBGC32_System::SetDefaultSettings (void)
{
	/* Control settings */
	Presets.activeControlProfile = SBGC_DEFAULT_CONTROL_PROFILE;

	for (ui8 i = 0; i < SBGC_CONTROL_PROFILES_NUM; i++)
	{
		Presets.ControlProfile[i].number = i;

		for (ui8 k = 0; k < SBGC_CONTROL_HANDLERS_NUM; k++)
		{
			Presets.ControlProfile[i].controlHandler[k].speed = SBGC_DEFAULT_CONTROL_SPEED;
			Presets.ControlProfile[i].controlHandler[k].LPF = SBGC_DEFAULT_CONTROL_LPF;
			Presets.ControlProfile[i].controlHandler[k].sensitivity = SBGC_DEFAULT_CONTROL_SENS;
			Presets.ControlProfile[i].controlHandler[k].exponent = SBGC_DEFAULT_CONTROL_EXP;
			Presets.ControlProfile[i].controlHandler[k].invert = SBGC_DEFAULT_CONTROL_INVERT;
			Presets.ControlProfile[i].controlHandler[k].attachedAxis = SBGC_CONTROL_HANDLERS_NUM - 1 - k;
			Presets.ControlProfile[i].controlHandler[k].controlMode = SBGC_DEFAULT_CONTROL_MODE;
		}
	}

	/* Adjvars load */
	for (ui8 i = 0; i < SBGC_ADJ_VARS_MAX_QUANTITY; i++)
	{
		SerialAPI_InitAdjVar(&Presets.AdjVarGeneral[i], (sbgcAdjVarID_t)i);
		TurnOffAdjVar((sbgcAdjVarID_t)i);
	}

	TurnOnAdjVar(ADJ_VAR_RC_SPEED_ROLL);
	TurnOnAdjVar(ADJ_VAR_RC_SPEED_PITCH);
	TurnOnAdjVar(ADJ_VAR_RC_SPEED_YAW);
}


void SBGC32_System::RecoverParameters (SBGC_ADVANCED_PARAMS_)
{
	SetCurrentState(SBGC_NORMAL);

	ReadBoardInfo(0, SBGC_ADVANCED_ARGS_);
	ReadProfileParams(sbgcCURRENT_PROFILE, SBGC_ADVANCED_ARGS_);
	ReadProfileNames(SBGC_ADVANCED_ARGS_);
	ReadRealTimeData(SBGC_ADVANCED_ARGS_);

	ConfigGimbalControl(SBGC_ADVANCED_ARGS_);

	GeneralSBGC._api->boardVersion = BoardInfo.boardVer;
	GeneralSBGC._api->firmwareVersion = BoardInfo.firmwareVer;

	UpdateEEPROM_AdjVars(SBGC_ADVANCED_ARGS_);
}


sbgcCommandStatus_t SBGC32_System::CheckConfirmation (serialAPI_CommandID_t commandID, SBGC_ADVANCED_PARAMS_)
{
	return SBGC32_CheckConfirmation(&GeneralSBGC, &Confirm, commandID, SBGC_ADVANCED_ARGS_);
}


sbgcCommandStatus_t SBGC32_System::ExpectCommand (serialAPI_CommandID_t commandID, SBGC_ADVANCED_PARAMS_)
{
	return SBGC32_ExpectCommand(&GeneralSBGC, commandID, SBGC_ADVANCED_ARGS_);
}


sbgcBoolean_t SBGC32_System::DeleteSerialCommand (serialAPI_CommandID_t commandID)
{
	return SBGC32_DeleteCommand(&GeneralSBGC, commandID);
}


void SBGC32_System::ControlGimbal (SBGC_ADVANCED_PARAMS_)
{
	SBGC32_Control(&GeneralSBGC, &Control, SBGC_ADVANCED_ARGS_);
}


void SBGC32_System::ConfigGimbalControl (SBGC_ADVANCED_PARAMS_)
{
	ResetControlAxis(&Control);

	Control.mode[ROLL] = controlModes[Gimbal.GetHandlerOfActiveControlProfileByAxis(ROLL)->controlMode];
	Control.mode[PITCH] = controlModes[Gimbal.GetHandlerOfActiveControlProfileByAxis(PITCH)->controlMode];
	Control.mode[YAW] = controlModes[Gimbal.GetHandlerOfActiveControlProfileByAxis(YAW)->controlMode];

	for (ui8 i = 0; i < 3; i++)
		if (Gimbal.GetHandlerOfActiveControlProfileByAxis(i)->controlMode != GIMBAL_INCREMENTAL_CONTROL)
			Control.AxisC[i].speed = Gimbal.GetHandlerOfActiveControlProfileByAxis(i)->speed;

		/* else speed parameter is rests a 0 on account of ResetControlAxis() function */

	ControlConfig.AxisCCtrl[ROLL].angleLPF = Gimbal.GetHandlerOfActiveControlProfileByAxis(ROLL)->LPF;
	ControlConfig.AxisCCtrl[PITCH].angleLPF = Gimbal.GetHandlerOfActiveControlProfileByAxis(PITCH)->LPF;
	ControlConfig.AxisCCtrl[YAW].angleLPF = Gimbal.GetHandlerOfActiveControlProfileByAxis(YAW)->LPF;

	ControlConfig.flags = CtrlCONFIG_FLAG_NO_CONFIRM;

	SBGC32_ControlConfig(&GeneralSBGC, &ControlConfig, &Confirm, SBGC_ADVANCED_ARGS_);
}


void SBGC32_System::PlayBeeper (SBGC_ADVANCED_PARAMS_)
{
	SBGC32_PlayBeeper(&GeneralSBGC, &BeeperSettings, SBGC_ADVANCED_ARGS_);
}


void SBGC32_System::ExecuteMenu (sbgcMenuCommand_t cmdID, SBGC_ADVANCED_PARAMS_)
{
	SBGC32_ExecuteMenu(&GeneralSBGC, cmdID, &Confirm, SBGC_ADVANCED_ARGS_);
}


void SBGC32_System::ReadBoardInfo (ui16 cfg, SBGC_ADVANCED_PARAMS_)
{
	SBGC32_ReadBoardInfo(&GeneralSBGC, &BoardInfo, cfg, SBGC_ADVANCED_ARGS_);
	SBGC32_ReadBoardInfo3(&GeneralSBGC, &BoardInfo3, SBGC_ADVANCED_ARGS_);
}


void SBGC32_System::ReadProfileNames (SBGC_ADVANCED_PARAMS_)
{
	SBGC32_ReadProfileNames(&GeneralSBGC, &ProfileNames, SBGC_ADVANCED_ARGS_);
}


void SBGC32_System::WriteProfileName (sbgcProfile_t profileN, const char *profileName, SBGC_ADVANCED_PARAMS_)
{
	if (profileN == sbgcCURRENT_PROFILE)
		profileN = (sbgcProfile_t)MainParams3.curProfileID;

	ui8 profNameLen = strlen(profileName);

	void *addr = ((char*)&ProfileNames + ((ui8)profileN * SBGC_MAX_PROF_NAME_LEN));

	memset(addr, 0, SBGC_MAX_PROF_NAME_LEN);
	memcpy(addr, profileName, profNameLen);

	SBGC32_WriteProfileNames(&GeneralSBGC, &ProfileNames, &Confirm, SBGC_ADVANCED_ARGS_);
}


void SBGC32_System::ReadProfileParams (sbgcProfile_t profileN, SBGC_ADVANCED_PARAMS_)
{
	SBGC32_ReadParams3(&GeneralSBGC, &MainParams3, profileN, SBGC_ADVANCED_ARGS_);
	SBGC32_ReadParamsExt(&GeneralSBGC, &MainParamsExt, profileN, SBGC_ADVANCED_ARGS_);
	SBGC32_ReadParamsExt2(&GeneralSBGC, &MainParamsExt2, profileN, SBGC_ADVANCED_ARGS_);
	SBGC32_ReadParamsExt3(&GeneralSBGC, &MainParamsExt3, profileN, SBGC_ADVANCED_ARGS_);
}


sbgcCommandStatus_t SBGC32_System::ReadRealTimeData (SBGC_ADVANCED_PARAMS_)
{
	return SBGC32_ReadRealTimeData4(&GeneralSBGC, &RealTimeData, SBGC_ADVANCED_ARGS_);
}


void SBGC32_System::ReadAngles (SBGC_ADVANCED_PARAMS_)
{
	SBGC32_GetAngles(&GeneralSBGC, &GetAngles, SBGC_ADVANCED_ARGS_);
}


void SBGC32_System::RunRealTimeDataCustomStream (ui16 intervalMs, SBGC_ADVANCED_PARAMS_)
{
	/* Data Stream Configurations */
	DataStreamInterval.cmdID = DSC_CMD_REALTIME_DATA_CUSTOM;
	DataStreamInterval.intervalMs = intervalMs;
	DataStreamInterval.syncToData = STD_SYNC_OFF;
	ui32 DataStreamIntervalConfig = RTDCF_STATOR_ROTOR_ANGLE;
	memcpy(DataStreamInterval.config, &DataStreamIntervalConfig, sizeof(DataStreamIntervalConfig));

	SBGC32_StartDataStream(&GeneralSBGC, &DataStreamInterval, &Confirm, SBGC_ADVANCED_ARGS_);
}


void SBGC32_System::ParseRealTimeDataCustomStream (SBGC_ADVANCED_PARAMS_)
{
	SBGC32_ReadDataStream(&GeneralSBGC, (sbgcDataStreamCommand_t)DataStreamInterval.cmdID,
			&DataStreamStruct, sizeof(DataStreamStruct), SBGC_ADVANCED_ARGS_);
}


void SBGC32_System::StopRealTimeDataCustomStream (SBGC_ADVANCED_PARAMS_)
{
	if (DataStreamInterval.cmdID != 0)
	{
		SBGC32_StopDataStream(&GeneralSBGC, &DataStreamInterval, &Confirm, SBGC_ADVANCED_ARGS_);
		clearbuff_(&DataStreamInterval);
	}
}


sbgcBoolean_t SBGC32_System::GetRealTimeDataCustomStreamStatus (void)
{
	return DataStreamInterval.cmdID ? sbgcTRUE : sbgcFALSE;
}


void SBGC32_System::TurnOnAdjVar (sbgcAdjVarID_t ID)
{
	Presets.AdjVarGeneral[ID].custom.activeFlag = true;
}


void SBGC32_System::TurnOffAdjVar (sbgcAdjVarID_t ID)
{
	Presets.AdjVarGeneral[ID].custom.activeFlag = false;
}


ui8 SBGC32_System::CountActiveAdjVars (void)
{
	ui8 count = 0;

	for (ui8 i = 0; i < SBGC_ADJ_VARS_MAX_QUANTITY; i++)
		if (Presets.AdjVarGeneral[i].custom.activeFlag)
			count++;

	return count;
}


/* Note: adjVarClass - means common pattern */
ui8 SBGC32_System::FindNextAdjVar (AdjVarActiveClass_t adjVarClass, ui8 originID)
{
	ui8 count;

	if (originID == (SBGC_ADJ_VARS_MAX_QUANTITY - 1))
		count = 0;

	else
		count = originID + 1;

	if (adjVarClass == AVAC_ACTIVE_ADJVARS)
		while (!Presets.AdjVarGeneral[count].custom.activeFlag)
		{
			if (count == (SBGC_ADJ_VARS_MAX_QUANTITY - 1))
				count = 0;

			++count;
		}

	else if (adjVarClass == AVAC_OTHER_ADJVARS)
		while (Presets.AdjVarGeneral[count].custom.activeFlag)
		{
			if (count == (SBGC_ADJ_VARS_MAX_QUANTITY - 1))
				count = 0;

			++count;
		}

	return count;
}


ui8 SBGC32_System::FindPreviousAdjVar (AdjVarActiveClass_t adjVarClass, ui8 originID)
{
	ui8 count;

	if (originID == 0)
		count = SBGC_ADJ_VARS_MAX_QUANTITY - 1;

	else
		count = originID - 1;

	if (adjVarClass == AVAC_ACTIVE_ADJVARS)
		while (!Presets.AdjVarGeneral[count].custom.activeFlag)
		{
			if (count == 0)
				count = SBGC_ADJ_VARS_MAX_QUANTITY;

			--count;
		}

	else if (adjVarClass == AVAC_OTHER_ADJVARS)
		while (Presets.AdjVarGeneral[count].custom.activeFlag)
		{
			if (count == 0)
				count = SBGC_ADJ_VARS_MAX_QUANTITY;

			--count;
		}

	return count;
}


void SBGC32_System::ReadAdjVarValues (sbgcAdjVarGeneral_t *adjVarGeneral, ui8 adjVarQuan, SBGC_ADVANCED_PARAMS_)
{
	if (adjVarQuan > SBGC_ADJ_VARS_MAX_NUM_PACKET)
	{
		ui8 i = 0;

		while (adjVarQuan)
		{
			SBGC32_GetAdjVarValues(&GeneralSBGC, &adjVarGeneral[i],
					(adjVarQuan > SBGC_ADJ_VARS_MAX_NUM_PACKET) ? SBGC_ADJ_VARS_MAX_NUM_PACKET : adjVarQuan, SBGC_ADVANCED_ARGS_);
			i += SBGC_ADJ_VARS_MAX_NUM_PACKET;
			adjVarQuan -= (adjVarQuan > SBGC_ADJ_VARS_MAX_NUM_PACKET) ? SBGC_ADJ_VARS_MAX_NUM_PACKET : adjVarQuan;
		}
	}

	else
		SBGC32_GetAdjVarValues(&GeneralSBGC, adjVarGeneral, adjVarQuan, SBGC_ADVANCED_ARGS_);
}


void SBGC32_System::ReadAllAdjVarValues (SBGC_ADVANCED_PARAMS_)
{
	ReadAdjVarValues(Presets.AdjVarGeneral, GetAdjVarsNumber(), SBGC_ADVANCED_ARGS_);
}


void SBGC32_System::SetAdjVarValue (sbgcAdjVarGeneral_t *adjVarGeneral, SBGC_ADVANCED_PARAMS_)
{
	SBGC32_SetAdjVarValue(&GeneralSBGC, adjVarGeneral, &Confirm, SBGC_ADVANCED_ARGS_);
}


void SBGC32_System::SetAllAdjVarValues (sbgcAdjVarGeneral_t *adjVarGeneral, SBGC_ADVANCED_PARAMS_)
{
	ui8 adjVarQuan = GetAdjVarsNumber();
	ui8 i = 0;

	while (adjVarQuan)
	{
		SBGC32_SetAdjVarValues(&GeneralSBGC, &adjVarGeneral[i],
				(adjVarQuan > SBGC_ADJ_VARS_MAX_NUM_PACKET) ? SBGC_ADJ_VARS_MAX_NUM_PACKET : adjVarQuan, &Confirm, SBGC_ADVANCED_ARGS_);
		i += SBGC_ADJ_VARS_MAX_NUM_PACKET;
		adjVarQuan -= (adjVarQuan > SBGC_ADJ_VARS_MAX_NUM_PACKET) ? SBGC_ADJ_VARS_MAX_NUM_PACKET : adjVarQuan;
	}
}


sbgcCommandStatus_t SBGC32_System::SaveAllAdjVarsToEEPROM (SBGC_ADVANCED_PARAMS_)
{
	return SBGC32_SaveAllActiveAdjVarsToEEPROM(&GeneralSBGC, &Confirm, SBGC_ADVANCED_ARGS_);
}


void SBGC32_System::ReadEEPROM_AdjVarsSafety (sbgcAdjVarGeneral_t *adjVarGeneral, SBGC_ADVANCED_PARAMS_)
{
	sbgcAdjVarGeneral_t *adjVarGeneralTemp = (sbgcAdjVarGeneral_t*)osMalloc(sizeof(sbgcAdjVarGeneral_t) * GeneralSBGC._api->adjVarsNumber);

	/* Init */
	for (ui8 i = 0; i < GeneralSBGC._api->adjVarsNumber; i++)
		adjVarGeneralTemp[i].ID = (sbgcAdjVarID_t)i;

	/* Firstly read actual values */
	ReadAdjVarValues(adjVarGeneralTemp, GeneralSBGC._api->adjVarsNumber, SBGC_ADVANCED_ARGS_);

	/* Reset to EEPROM values on the gimbal side */
	SBGC32_ReadParams3(&GeneralSBGC, &MainParams3, sbgcCURRENT_PROFILE, SBGC_ADVANCED_ARGS_);

	/* Read EEPROM values */
	ReadAdjVarValues(adjVarGeneral, GeneralSBGC._api->adjVarsNumber, SBGC_ADVANCED_ARGS_);

	/* Return current values to the gimbal session */
	SetAllAdjVarValues(adjVarGeneralTemp, SBGC_ADVANCED_ARGS_);

	osFree(adjVarGeneralTemp);

//	return GetParserCurrentStatus();
}


sbgcCommandStatus_t SBGC32_System::UpdateEEPROM_AdjVars (SBGC_ADVANCED_PARAMS_)
{
	sbgcAdjVarGeneral_t *adjVarGeneralTemp = (sbgcAdjVarGeneral_t*)osMalloc(sizeof(sbgcAdjVarGeneral_t) * GeneralSBGC._api->adjVarsNumber);

	for (ui8 i = 0; i < GeneralSBGC._api->adjVarsNumber; i++)
		adjVarGeneralTemp[i].ID = (sbgcAdjVarID_t)i;

	ReadEEPROM_AdjVarsSafety(adjVarGeneralTemp, SBGC_ADVANCED_ARGS_);

	for (ui8 i = 0; i < GeneralSBGC._api->adjVarsNumber; i++)
		EEPROM_AdjVarValues[i] = adjVarGeneralTemp[i].value;

	osFree(adjVarGeneralTemp);

	return GetParserCurrentStatus();
}


/* Needed after PID Auto Tune */
void SBGC32_System::UpdatePID_EEPROM_AdjVars (sbgcMainParams3_t *mainParams3)
{
	EEPROM_AdjVarValues[ADJ_VAR_P_ROLL] = mainParams3->AxisCMP3[ROLL].p;
	EEPROM_AdjVarValues[ADJ_VAR_I_ROLL] = mainParams3->AxisCMP3[ROLL].i;
	EEPROM_AdjVarValues[ADJ_VAR_D_ROLL] = mainParams3->AxisCMP3[ROLL].d;

	EEPROM_AdjVarValues[ADJ_VAR_P_PITCH] = mainParams3->AxisCMP3[PITCH].p;
	EEPROM_AdjVarValues[ADJ_VAR_I_PITCH] = mainParams3->AxisCMP3[PITCH].i;
	EEPROM_AdjVarValues[ADJ_VAR_D_PITCH] = mainParams3->AxisCMP3[PITCH].d;

	EEPROM_AdjVarValues[ADJ_VAR_P_YAW] = mainParams3->AxisCMP3[YAW].p;
	EEPROM_AdjVarValues[ADJ_VAR_I_YAW] = mainParams3->AxisCMP3[YAW].i;
	EEPROM_AdjVarValues[ADJ_VAR_D_YAW] = mainParams3->AxisCMP3[YAW].d;
}


void SBGC32_System::AppoinRC_InputSource (ui8 num, ui8 source)
{
	RC_Inputs[num].RC_Src = source;
}


void SBGC32_System::ReadRC_Inputs (sbgcInitCfgFlag_t cfgFlags, ui8 srcQuan, SBGC_ADVANCED_PARAMS_)
{
	SBGC32_ReadRC_Inputs(&GeneralSBGC, RC_Inputs, cfgFlags, srcQuan, SBGC_ADVANCED_ARGS_);
}


sbgcCommandStatus_t SBGC32_System::RequestCalibInfo (sbgcIMU_Type_t IMU_Type, SBGC_ADVANCED_PARAMS_)
{
	return SBGC32_RequestCalibInfo(&GeneralSBGC, &CalibInfo, IMU_Type, SBGC_ADVANCED_ARGS_);
}


sbgcCommandStatus_t SBGC32_System::CalibAcc (SBGC_ADVANCED_PARAMS_)
{
	if (!SBGC_CalibrationStateMask(GetCurrentState()))
	{
		IMU_ExtCalib.IMU_IDx = SBGC_TARGET_IMU;
		IMU_ExtCalib.action = IMUECA_DO_REGULAR_CALIBRATION;

		return SBGC32_CalibAccExt(&GeneralSBGC, &IMU_ExtCalib, &Confirm, SBGC_ADVANCED_ARGS_);
	}

	return sbgcCOMMAND_NOTHING_TO_CHANGE;
}


sbgcCommandStatus_t SBGC32_System::CalibGyro (SBGC_ADVANCED_PARAMS_)
{
	if (!SBGC_CalibrationStateMask(GetCurrentState()))
	{
		IMU_ExtCalib.IMU_IDx = SBGC_TARGET_IMU;
		IMU_ExtCalib.action = IMUECA_DO_REGULAR_CALIBRATION;
		IMU_ExtCalib.timeMs = 0;

		return SBGC32_CalibGyroExt(&GeneralSBGC, &IMU_ExtCalib, &Confirm, SBGC_ADVANCED_ARGS_);
	}

	return sbgcCOMMAND_NOTHING_TO_CHANGE;
}


sbgcCommandStatus_t SBGC32_System::TurnOffMotors (SBGC_ADVANCED_PARAMS_)
{
	return SBGC32_ExecuteMenu(&GeneralSBGC, MENU_CMD_MOTOR_OFF, &Confirm, SBGC_ADVANCED_ARGS_);
}


sbgcCommandStatus_t SBGC32_System::TurnOnMotors (SBGC_ADVANCED_PARAMS_)
{
	return SBGC32_ExecuteMenu(&GeneralSBGC, MENU_CMD_MOTOR_ON, &Confirm, SBGC_ADVANCED_ARGS_);
}


sbgcCommandStatus_t SBGC32_System::ToggleMotors (SBGC_ADVANCED_PARAMS_)
{
	if (RealTimeData.RT_DataFlags & RTDF_MOTORS_ON)
		return TurnOffMotors(SBGC_ADVANCED_ARGS_);

	else
		return TurnOnMotors(SBGC_ADVANCED_ARGS_);

	/* or MENU_CMD_MOTOR_TOGGLE only */
}


sbgcCommandStatus_t SBGC32_System::TuneAutoPID (SBGC_ADVANCED_PARAMS_)
{
	if (GetAddressGeneralSBGC()->_api->baseFirmwareVersion < 2731)
	{
		/* Update the 'currentProfile' variable */
		SBGC32_ReadRealTimeData3(&GeneralSBGC, &RealTimeData, SCParam_FREEZE, SCPrior_NORMAL, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);

		sbgcAutoPID_t AutoPID = { 0 };

		// Tune PIDs in first profile and request debug information
		AutoPID.profileID = RealTimeData.curProfile;
		AutoPID.cfgFlags = APIDC_FLAG_SEND_GUI | APIDC_FLAG_TUNE_LPF_FREQ;
		AutoPID.Gain_VS_Stability = 127;

		return SBGC32_TuneAutoPID(&GeneralSBGC, &AutoPID, &Confirm, SBGC_ADVANCED_ARGS_);
	}

	else
	{
		sbgcAutoPID2_t AutoPID2 = { 0 };

		AutoPID2.action = APID2A_ACTION_START_SAVE;
		AutoPID2.cfgVersion = 1;

		for (ui8 i = 0; i < 3; i++)
		{
			AutoPID2.AxisAPID2[i].axisFlag = APID2AF_AXIS_IS_ENABLED | APID2AF_TUNE_LPF;

			AutoPID2.AxisAPID2[i].gain = 127;
			AutoPID2.AxisAPID2[i].stimulusGain = 650;
			AutoPID2.AxisAPID2[i].effectiveFreq = 20;
			AutoPID2.AxisAPID2[i].problemFreq = 50;
			AutoPID2.AxisAPID2[i].problemMargin = 50;
		}

		AutoPID2.generalFlags = APID2GF_START_FROM_CURRENT_VALUES | APID2GF_SAVE_RESULT_TO_ALL_PROFILES;

		AutoPID2.testFreqFrom = 10;
		AutoPID2.testFreqTo = 150;

		return SBGC32_TuneAutoPID2(&GeneralSBGC, &AutoPID2, &Confirm, SBGC_ADVANCED_ARGS_);
	}
}


sbgcCommandStatus_t SBGC32_System::Reset (SBGC_ADVANCED_PARAMS_)
{
	SBGC32_Reset(&GeneralSBGC, RESET_FLAG_NEED_CONFIRMATION | RESET_FLAG_RESTORE_STATE, 0, SBGC_ADVANCED_ARGS_);

	return SBGC32_ExpectCommand(&GeneralSBGC, CMD_RESET, SBGC_ADVANCED_ARGS_);
}


sbgcCommandStatus_t SBGC32_System::RunScript (sbgcScriptSlotNum_t slot, SBGC_ADVANCED_PARAMS_)
{
	return SBGC32_RunScript(&GeneralSBGC, ScrtM_START_WITH_DEBUG, slot, SBGC_ADVANCED_ARGS_);
}


sbgcCommandStatus_t SBGC32_System::StopScript (sbgcScriptSlotNum_t slot, SBGC_ADVANCED_PARAMS_)
{
	return SBGC32_RunScript(&GeneralSBGC, ScrtM_STOP, slot, SBGC_ADVANCED_ARGS_);
}


sbgcCommandStatus_t SBGC32_System::ReadScriptDebugInfo (sbgcScriptDebugInfo_t *scriptDebugInfo, SBGC_ADVANCED_PARAMS_)
{
	return SBGC32_ReadScriptDebugInfo(&GeneralSBGC, scriptDebugInfo, SBGC_ADVANCED_ARGS_);
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														   Other Methods
 */
void SBGC32_System::SetCurrentState (SBGC_CurrentState_t newState)
{
	previousState = currentState;
	currentState = newState;
}


SBGC_CurrentState_t SBGC32_System::GetPreviousState (void)
{
	return previousState;
}


SBGC_CurrentState_t SBGC32_System::GetCurrentState (void)
{
	return currentState;
}


void SBGC32_System::AddCurrentState (SBGC_CurrentState_t newState)
{
	if (currentState != SBGC_LOST_CONNECTION)
	{
		ui8 temp = (currentState | newState);

		previousState = currentState;
		currentState = (SBGC_CurrentState_t)temp;
	}
}


void SBGC32_System::ClearCurrentState (SBGC_CurrentState_t clearedState)
{
	ui8 temp = currentState & ~clearedState;

	previousState = currentState;
	currentState = (SBGC_CurrentState_t)temp;
}


void SBGC32_System::PrintStructElementConsole (void *data, const char *str, sbgcVarType_t vType)
{
	DebugSBGC32_PrintStructElement(&GeneralSBGC, data, str, vType);
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														  Free Functions
 */
void ResetControlAxis (sbgcControl_t *control)
{
	memset(control->AxisC, 0, sizeof(control->AxisC));
}


void FillConsoleDataArr (char *data, ui16 length)
{
	if (osSemaphoreTake(Gimbal.xSemaphoreDebugConsole, 0) != pdTRUE)
		osSemaphoreTake(Gimbal.xSemaphoreDebugConsole, osMaxDelay);

	if (ConsoleData.emptyFlag != 0)  // Until the console wouldn't be cleared
		ConsoleData.emptyFlag = 0;

	if (ConsoleData.updateFlag != 1)  // Until the console wouldn't change itself state
		ConsoleData.updateFlag = 1;

	/* Note: Block the console, while it don't take data from buffer */
	if (DEBUG_CONSOLE_BUFFER_SIZE - (ConsoleData.CD_BufferHead - ConsoleData.CD_BufferTail) >= length)
	{
		memcpy(&ConsoleData.CD_Buffer[ConsoleData.CD_BufferHead], data, length);
		ConsoleData.CD_BufferHead += length;
	}

	#if (DEBUG_CONSOLE_EXLUDING_BEHAVIOR)
		/* Note: or excluding behavior - delete old data and enter new */
		else
		{
			while (ConsoleData.CD_Buffer[ConsoleData.CD_BufferTail] != '\n')
				ConsoleData.CD_BufferTail++;

			ConsoleData.CD_BufferTail += 1;

			memcpy(&ConsoleData.CD_Buffer[0], &ConsoleData.CD_Buffer[ConsoleData.CD_BufferTail],
					ConsoleData.CD_BufferHead - ConsoleData.CD_BufferTail);

			ConsoleData.CD_BufferHead -= ConsoleData.CD_BufferTail;
			ConsoleData.CD_BufferTail = 0;
			ConsoleData.CD_BufferPointer = ConsoleData.CD_BufferHead;
		}

	#endif

	osSemaphoreGive(Gimbal.xSemaphoreDebugConsole);
}

