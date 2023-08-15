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

static ControlMode_t controlModes [] =
{
	CtrlM_MODE_NO_CONTROL,							// GIMBAL_NO_CONTROL
	CtrlM_MODE_ANGLE,								// GIMBAL_ABSOLUTE_CONTROL
	CtrlM_MODE_SPEED,								// GIMBAL_INCREMENTAL_CONTROL
	CtrlM_MODE_RC									// GIMBAL_RC_CONTROL

};


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *												  Class Protocol Methods
 */
TxRxStatus_t SBGC32_System::Init (__UART_TYPE_DEF *uart, __TIMER_TYPE_DEF *tim)
{
	osSemaphoreCreate(xSemaphoreDebugConsole);
	osSemaphoreGive(xSemaphoreDebugConsole);

	DriverInit(&GeneralSBGC.Drv, uart, tim);

	/* SBGC32 Init */
	SBGC32_ManualInit(&GeneralSBGC, UartTransmitData, UartReceiveByte, GetAvailableBytes,
					  FillConsoleDataArr, GetTimeMs, sprintf_, SBGC_PROTOCOL_V2);

	/* Parameters load handle */
	if (GetCommunicationState())
		RecoverParameters();

	/* Getting initial adjustable variable values */
	UpdateEEPROM_AdjVars();

	/* Other */
	processStatus = PROCESS_READY;
	adjVarsSyncState = AVSS_NOT_SYNCHRONIZED;

	return GeneralSBGC._parserCurrentStatus;
}


void SBGC32_System::ResetDriver (__UART_TYPE_DEF *uart, __TIMER_TYPE_DEF *tim)
{
	DriverDeinit(&GeneralSBGC.Drv);
	DriverInit(&GeneralSBGC.Drv, uart, tim);

	/* It's need to re-init ADC, cause it is placed onto same DMA */
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
			Presets.ControlProfile[i].controlHandler[k].invert = SBGC_DEFAULT_CONTROL_INVERT;
			Presets.ControlProfile[i].controlHandler[k].attachedAxis = SBGC_CONTROL_HANDLERS_NUM - 1 - k;
			Presets.ControlProfile[i].controlHandler[k].controlMode = SBGC_DEFAULT_CONTROL_MODE;
		}
	}

	/* Adjvars load */
	for (ui8 i = 0; i < ADJ_VARS_QUANTITY; i++)
	{
		InitAdjVar(&Presets.AdjVarGeneral[i], (AdjVarID_t)i);
		TurnOffAdjVar((AdjVarID_t)i);
	}

	TurnOnAdjVar(ADJ_VAR_RC_SPEED_ROLL);
	TurnOnAdjVar(ADJ_VAR_RC_SPEED_PITCH);
	TurnOnAdjVar(ADJ_VAR_RC_SPEED_YAW);
}


TxRxStatus_t SBGC32_System::RecoverParameters (void)
{
	SetCurrentState(SBGC_NORMAL);

	ReadBoardInfo(0);
	ReadProfileParams(P_CURRENT_PROFILE);
	ReadProfileNames();
	ReadRealTimeData();

	ConfigGimbalControl();

	Gimbal.GetAddressGeneralSBGC()->_boardVersion = BoardInfo.boardVer;
	Gimbal.GetAddressGeneralSBGC()->_firmwareVersion = BoardInfo.firmwareVer;
	Gimbal.GetAddressRealTimeData()->curProfile = RealTimeData.curProfile;

	return GeneralSBGC._parserCurrentStatus;
}


TxRxStatus_t SBGC32_System::FindCommand (SerialCommand_t *cmd, SBGC_Command_t cmdID, ui32 timeout)
{
	return SBGC32_FindCommand(&GeneralSBGC, cmd, cmdID, timeout);
}


void SBGC32_System::ResetUnexpCommandBuff (void)
{
	GeneralSBGC._unexpectedCommandCurrentPointer = 0;
	GeneralSBGC._unexpectedCommandsBuffTail = 0;
	GeneralSBGC._unexpectedCommandsBuffHead = 0;
}


TxRxStatus_t SBGC32_System::CheckConfirmation (SBGC_Command_t cmdID)
{
	return SBGC32_CheckConfirmation(&GeneralSBGC, cmdID);
}


void SBGC32_System::ClearConfirmationStruct (void)
{
	memset(&GeneralSBGC._confirmationParams, 0, sizeof(ConfirmationParams_t));
}


TxRxStatus_t SBGC32_System::ControlGimbal (void)
{
	return SBGC32_Control(&GeneralSBGC, &Control);
}


TxRxStatus_t SBGC32_System::ConfigGimbalControl (void)
{
	ResetControlAxis(&Control);

	Control.controlMode[ROLL] = controlModes[Gimbal.GetHandlerOfActiveControlProfileByAxis(ROLL)->controlMode];
	Control.controlMode[PITCH] = controlModes[Gimbal.GetHandlerOfActiveControlProfileByAxis(PITCH)->controlMode];
	Control.controlMode[YAW] = controlModes[Gimbal.GetHandlerOfActiveControlProfileByAxis(YAW)->controlMode];

	for (ui8 i = 0; i < 3; i++)
		if (Gimbal.GetHandlerOfActiveControlProfileByAxis(i)->controlMode != GIMBAL_INCREMENTAL_CONTROL)
			Control.AxisC[i].speed = Gimbal.GetHandlerOfActiveControlProfileByAxis(i)->speed;

		/* else speed parameter is rests a 0 on account of ResetControlAxis() function */

	ControlConfig.AxisCC[ROLL].angleLPF = Gimbal.GetHandlerOfActiveControlProfileByAxis(ROLL)->LPF;
	ControlConfig.AxisCC[PITCH].angleLPF = Gimbal.GetHandlerOfActiveControlProfileByAxis(PITCH)->LPF;
	ControlConfig.AxisCC[YAW].angleLPF = Gimbal.GetHandlerOfActiveControlProfileByAxis(YAW)->LPF;

	ControlConfig.flags = RTCCF_CONTROL_CONFIG_FLAG_NO_CONFIRM;

	return SBGC32_ControlConfig(&GeneralSBGC, &ControlConfig);
}


TxRxStatus_t SBGC32_System::PlayBeeper (void)
{
	return SBGC32_PlayBeeper(&GeneralSBGC, &BeeperSettings);
}


TxRxStatus_t SBGC32_System::ExecuteMenu (MenuCommand_t cmdID)
{
	return SBGC32_ExecuteMenu(&GeneralSBGC, cmdID);
}


TxRxStatus_t SBGC32_System::ReadBoardInfo (ui16 cfg)
{
	SBGC32_ReadBoardInfo(&GeneralSBGC, &BoardInfo, cfg);
	SBGC32_ReadBoardInfo3(&GeneralSBGC, &BoardInfo3);

	return GeneralSBGC._parserCurrentStatus;
}


TxRxStatus_t SBGC32_System::ReadProfileNames (void)
{
	return SBGC32_ReadProfileNames(&GeneralSBGC, &ProfileNames);
}


TxRxStatus_t SBGC32_System::WriteProfileName (Profile_t profileN, const char *profileName)
{
	if (profileN == P_CURRENT_PROFILE)
		profileN = (Profile_t)MainParams3.curProfileID;

	ui8 profNameLen = strlen(profileName);

	void *addr = ((char*)&ProfileNames + ((ui8)profileN * MAX_PROFILE_NAME_LENGTH));

	memset(addr, 0, MAX_PROFILE_NAME_LENGTH);
	memcpy(addr, profileName, profNameLen);

	return SBGC32_WriteProfileNames(&GeneralSBGC, &ProfileNames);
}


TxRxStatus_t SBGC32_System::ReadProfileParams (Profile_t profileN)
{
	SBGC32_ReadParams3(&GeneralSBGC, &MainParams3, profileN);
	SBGC32_ReadParamsExt(&GeneralSBGC, &MainParamsExt, profileN);
	SBGC32_ReadParamsExt2(&GeneralSBGC, &MainParamsExt2, profileN);
	SBGC32_ReadParamsExt3(&GeneralSBGC, &MainParamsExt3, profileN);

	return GeneralSBGC._parserCurrentStatus;
}


TxRxStatus_t SBGC32_System::ReadRealTimeData (void)
{
	return SBGC32_ReadRealTimeData4(&GeneralSBGC, &RealTimeData);
}


TxRxStatus_t SBGC32_System::ReadAngles (void)
{
	return SBGC32_GetAngles(&GeneralSBGC, &GetAngles);
}


TxRxStatus_t SBGC32_System::RunRealTimeDataCustomStream (ui16 intervalMs)
{
	/* Data Stream Configurations */
	DataStreamInterval.cmdID = CMD_REALTIME_DATA_CUSTOM;
	DataStreamInterval.intervalMs = intervalMs;
	DataStreamInterval.syncToData = STD_SYNC_OFF;
	ui32 DataStreamIntervalConfig = RTDCF_STATOR_ROTOR_ANGLE;
	memcpy(DataStreamInterval.config, &DataStreamIntervalConfig, sizeof(DataStreamIntervalConfig));
	return SBGC32_RequestDataStream(&GeneralSBGC, &DataStreamInterval);
}


TxRxStatus_t SBGC32_System::ParseRealTimeDataCustomStream (void)
{
	ui8 buffTemp [10];
	ui8 BuffRPx = 2;  // ui16 timestampMs offset

	SBGC32_ParseDataStream(&GeneralSBGC, buffTemp, (SBGC_Command_t)DataStreamInterval.cmdID);

	if (GetCommunicationState())
		BuffRPx += ConvertWithPM(frameCamAngle, &buffTemp[BuffRPx], sizeof(frameCamAngle), PM_DEFAULT_16BIT);

	return GeneralSBGC._parserCurrentStatus;
}


TxRxStatus_t SBGC32_System::StopDataStream (void)
{
	return SBGC32_StopDataStream(&GeneralSBGC, &DataStreamInterval);
}


void SBGC32_System::TurnOnAdjVar (AdjVarID_t ID)
{
	Presets.AdjVarGeneral[ID].custom.activeFlag = true;
}


void SBGC32_System::TurnOffAdjVar (AdjVarID_t ID)
{
	Presets.AdjVarGeneral[ID].custom.activeFlag = false;
}


ui8 SBGC32_System::CountActiveAdjVars (void)
{
	ui8 count = 0;

	for (ui8 i = 0; i < ADJ_VARS_QUANTITY; i++)
		if (Presets.AdjVarGeneral[i].custom.activeFlag)
			count++;

	return count;
}


/* Note: adjVarClass - means common pattern */
ui8 SBGC32_System::FindNextAdjVar (AdjVarActiveClass_t adjVarClass, ui8 originID)
{
	ui8 count;

	if (originID == (ADJ_VARS_QUANTITY - 1))
		count = 0;

	else
		count = originID + 1;

	if (adjVarClass == AVAC_ACTIVE_ADJVARS)
		while (!Presets.AdjVarGeneral[count].custom.activeFlag)
		{
			if (count == (ADJ_VARS_QUANTITY - 1))
				count = 0;

			++count;
		}

	else if (adjVarClass == AVAC_OTHER_ADJVARS)
		while (Presets.AdjVarGeneral[count].custom.activeFlag)
		{
			if (count == (ADJ_VARS_QUANTITY - 1))
				count = 0;

			++count;
		}

	return count;
}


ui8 SBGC32_System::FindPreviousAdjVar (AdjVarActiveClass_t adjVarClass, ui8 originID)
{
	ui8 count;

	if (originID == 0)
		count = ADJ_VARS_QUANTITY - 1;

	else
		count = originID - 1;

	if (adjVarClass == AVAC_ACTIVE_ADJVARS)
		while (!Presets.AdjVarGeneral[count].custom.activeFlag)
		{
			if (count == 0)
				count = ADJ_VARS_QUANTITY;

			--count;
		}

	else if (adjVarClass == AVAC_OTHER_ADJVARS)
		while (Presets.AdjVarGeneral[count].custom.activeFlag)
		{
			if (count == 0)
				count = ADJ_VARS_QUANTITY;

			--count;
		}

	return count;
}


TxRxStatus_t SBGC32_System::ReadAdjVarValues (AdjVarGeneral_t *adjVarGeneral, ui8 adjVarQuan)
{
	return SBGC32_GetAdjVarValues(&GeneralSBGC, adjVarGeneral, adjVarQuan);
}


TxRxStatus_t SBGC32_System::ReadAllAdjVarValues (void)
{
	return SBGC32_GetAdjVarValues(&GeneralSBGC, Presets.AdjVarGeneral, ADJ_VARS_QUANTITY);
}


TxRxStatus_t SBGC32_System::SetAdjVarValue (AdjVarGeneral_t *adjVarGeneral)
{
	return SBGC32_SetAdjVarValues(&GeneralSBGC, adjVarGeneral, 1);
}


TxRxStatus_t SBGC32_System::SetAllAdjVarValues (AdjVarGeneral_t *adjVarGeneral)
{
	return SBGC32_SetAdjVarValues(&GeneralSBGC, adjVarGeneral, ADJ_VARS_QUANTITY);
}


TxRxStatus_t SBGC32_System::SaveAllAdjVarsToEEPROM (void)
{
	return SBGC32_SaveAdjVarsToEEPROM(&GeneralSBGC, Presets.AdjVarGeneral, ADJ_VARS_QUANTITY);
}


TxRxStatus_t SBGC32_System::ReadEEPROM_AdjVarsSafety (AdjVarGeneral_t *adjVarGeneral)
{
	/* Reset to EEPROM values on the gimbal side */
	SBGC32_ReadParams3(&GeneralSBGC, &MainParams3, P_CURRENT_PROFILE);

	/* Reading the stock values to the target buffer */
	for (ui8 i = 0; i < ADJ_VARS_QUANTITY; i++)
		adjVarGeneral[i].ID = (AdjVarID_t)i;

	ReadAdjVarValues(adjVarGeneral, ADJ_VARS_QUANTITY);

	/* Return current values to the gimbal session */
	SetAllAdjVarValues(Presets.AdjVarGeneral);

	return GeneralSBGC._parserCurrentStatus;
}


TxRxStatus_t SBGC32_System::UpdateEEPROM_AdjVars (void)
{
	AdjVarGeneral_t *adjVarGeneralTemp = (AdjVarGeneral_t*)osMalloc(sizeof(AdjVarGeneral_t) * ADJ_VARS_QUANTITY);

	ReadEEPROM_AdjVarsSafety(adjVarGeneralTemp);

	for (ui8 i = 0; i < ADJ_VARS_QUANTITY; i++)
		EEPROM_AdjVarsValue[i] = adjVarGeneralTemp[i].value;

	osFree(adjVarGeneralTemp);

	return GeneralSBGC._parserCurrentStatus;
}


/* Needed after PID Auto Tune */
void SBGC32_System::UpdatePID_EEPROM_AdjVars (MainParams3_t *mainParams3)
{
	EEPROM_AdjVarsValue[ADJ_VAR_P_ROLL] = mainParams3->AxisCMP3[ROLL].p;
	EEPROM_AdjVarsValue[ADJ_VAR_I_ROLL] = mainParams3->AxisCMP3[ROLL].i;
	EEPROM_AdjVarsValue[ADJ_VAR_D_ROLL] = mainParams3->AxisCMP3[ROLL].d;

	EEPROM_AdjVarsValue[ADJ_VAR_P_PITCH] = mainParams3->AxisCMP3[PITCH].p;
	EEPROM_AdjVarsValue[ADJ_VAR_I_PITCH] = mainParams3->AxisCMP3[PITCH].i;
	EEPROM_AdjVarsValue[ADJ_VAR_D_PITCH] = mainParams3->AxisCMP3[PITCH].d;

	EEPROM_AdjVarsValue[ADJ_VAR_P_YAW] = mainParams3->AxisCMP3[YAW].p;
	EEPROM_AdjVarsValue[ADJ_VAR_I_YAW] = mainParams3->AxisCMP3[YAW].i;
	EEPROM_AdjVarsValue[ADJ_VAR_D_YAW] = mainParams3->AxisCMP3[YAW].d;
}


void SBGC32_System::AppoinRC_InputSource (ui8 num, ui8 source)
{
	RC_Inputs[num].RC_Src = source;
}


TxRxStatus_t SBGC32_System::ReadRC_Inputs (InitCfgFlag_t cfgFlags, ui8 srcQuan)
{
	return SBGC32_ReadRC_Inputs(&GeneralSBGC, RC_Inputs, cfgFlags, srcQuan);
}


TxRxStatus_t SBGC32_System::RequestCalibInfo (IMU_Type_t IMU_Type)
{
	return SBGC32_RequestCalibInfo(&GeneralSBGC, &CalibInfo, IMU_Type);
}


TxRxStatus_t SBGC32_System::CalibAcc (void)
{
	if (!SBGC_CalibrationStateMask(GetCurrentState()))
	{
		IMU_ExtCalib.IMU_IDx = SBGC_TARGET_IMU;
		IMU_ExtCalib.action = IMUECA_DO_REGULAR_CALIBRATION;
		return SBGC32_CalibAccExt(&GeneralSBGC, &IMU_ExtCalib);
	}

	return RX_TIMEOUT_ERROR;
}


TxRxStatus_t SBGC32_System::CalibGyro (void)
{
	if (!SBGC_CalibrationStateMask(GetCurrentState()))
	{
		IMU_ExtCalib.IMU_IDx = SBGC_TARGET_IMU;
		IMU_ExtCalib.action = IMUECA_DO_REGULAR_CALIBRATION;
		IMU_ExtCalib.timeMs = 0;
		return SBGC32_CalibGyroExt(&GeneralSBGC, &IMU_ExtCalib);
	}

	return RX_TIMEOUT_ERROR;
}


TxRxStatus_t SBGC32_System::TurnOffMotors (void)
{
	return SBGC32_ExecuteMenu(&GeneralSBGC, MENU_CMD_MOTOR_OFF);
}


TxRxStatus_t SBGC32_System::TurnOnMotors (void)
{
	return SBGC32_ExecuteMenu(&GeneralSBGC, MENU_CMD_MOTOR_ON);
}


TxRxStatus_t SBGC32_System::ToggleMotors (void)
{
	if (RealTimeData.RT_DataFlags & RTDF_MOTORS_ON)
		return TurnOffMotors();

	else
		return TurnOnMotors();

	/* or MENU_CMD_MOTOR_TOGGLE only */
}


TxRxStatus_t SBGC32_System::TuneAutoPID (void)
{
	SBGC32_ReadRealTimeData3(&GeneralSBGC, &RealTimeData);  // Update a <currentProfile> variable
	AutoPID.profileID = (AutoPID_Profile_t)RealTimeData.curProfile;

	AutoPID.cfgFlags = APIDCF_AUTO_PID_CFG_ROLL | APIDCF_AUTO_PID_CFG_PITCH | APIDCF_AUTO_PID_CFG_YAW;

	AutoPID.Gain_VS_Stability = 128;
	AutoPID.momentum = 128;
	AutoPID.action = 0;

	return SBGC32_TuneAutoPID(&GeneralSBGC, &AutoPID);
}


TxRxStatus_t SBGC32_System::Reset (void)
{
	SerialCommand_t cmd;

	SBGC32_ExecuteMenu(&GeneralSBGC, MENU_CMD_RESET);
	SetParserCurrentStatus(SBGC32_FindCommand(&GeneralSBGC, &cmd, CMD_RESET, SBGC_REQ_WAITING));

	return GeneralSBGC._parserCurrentStatus;
}


TxRxStatus_t SBGC32_System::RunScript (ScriptSlotNum_t slot)
{
	return SBGC32_RunScript(&GeneralSBGC, ScrtM_START_WITH_DEBUG, slot);
}


TxRxStatus_t SBGC32_System::StopScript (ScriptSlotNum_t slot)
{
	return SBGC32_RunScript(&GeneralSBGC, ScrtM_STOP, slot);
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													 Class Other Methods
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


void SBGC32_System::PrintMessageConsole (char *str, ui16 length)
{
	PrintMessage(&GeneralSBGC, str, length);
}


void SBGC32_System::PrintStructElementConsole (void *data, const char *str, VarType_t vType)
{
	PrintStructElement(&GeneralSBGC, data, str, vType);
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														  Free Functions
 */
void ResetControlAxis (Control_t *control)
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

