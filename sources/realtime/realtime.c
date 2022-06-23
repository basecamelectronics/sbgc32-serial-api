/** ____________________________________________________________________
 *
 *	@file		realtime.c
 *
 *	@brief 		Realtime source file
 *	____________________________________________________________________
 *
 *	@attention	<center><h3>
 *	Copyright © 2022 BaseCam Electronics™.</h3></center>
 *	<center>All rights reserved.</center>
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

#include "realtime.h"


#ifdef	SYS_BIG_ENDIAN

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *								Parser Big Endian Mapping Structures
	 */
	/**	@addtogroup	Data_Stream_Interval Data Stream Interval
	 * 	@{
	 */
	/** @brief	Sample for Big Endian Mapping
	 *
	 * 	@ref	DataStreamInterval_ParserStructDB
	 */
	const DataStreamInterval_t dataStreamInterval_ParserStruct;

	const ParserBlock_t DataStreamInterval_ParserStructDB [] =
	{
		VAR_BLOCK(dataStreamInterval_ParserStruct.cmdID),
		VAR_BLOCK(dataStreamInterval_ParserStruct.intervalMs),
		DATA_BLOCK(dataStreamInterval_ParserStruct.config),
		VAR_BLOCK(dataStreamInterval_ParserStruct.syncToData),
		DATA_BLOCK(dataStreamInterval_ParserStruct.reserved),
	};

	const ui8 DataStreamInterval_ParserStructDB_Size = countof(DataStreamInterval_ParserStructDB);
	/**	@}
	 */


	/**	@addtogroup	Realtime_Data_3_4
	 * 	@{
	 */
	/** @brief	Sample for Big Endian Mapping
	 *
	 * 	@ref	RealTimeData3_ParserStructDB \n
	 * 	@ref	RealTimeData4_ParserStructDB
	 */
	const RealTimeData_t realTimeData_ParserStruct;

	const ParserBlock_t RealTimeData3_ParserStructDB [] =
	{
		VAR_BLOCK(realTimeData_ParserStruct.AxisRTD[AXIS_X].ACC_Data),
		VAR_BLOCK(realTimeData_ParserStruct.AxisRTD[AXIS_X].gyroData),
		VAR_BLOCK(realTimeData_ParserStruct.AxisRTD[AXIS_Y].ACC_Data),
		VAR_BLOCK(realTimeData_ParserStruct.AxisRTD[AXIS_Y].gyroData),
		VAR_BLOCK(realTimeData_ParserStruct.AxisRTD[AXIS_Z].ACC_Data),
		VAR_BLOCK(realTimeData_ParserStruct.AxisRTD[AXIS_Z].gyroData),
		VAR_BLOCK(realTimeData_ParserStruct.serialErrCnt),
		VAR_BLOCK(realTimeData_ParserStruct.systemError),
		VAR_BLOCK(realTimeData_ParserStruct.systemSubError),
		DATA_BLOCK(realTimeData_ParserStruct.reserved),
		VAR_BLOCK(realTimeData_ParserStruct.RC_ROLL),
		VAR_BLOCK(realTimeData_ParserStruct.RC_PITCH),
		VAR_BLOCK(realTimeData_ParserStruct.RC_YAW),
		VAR_BLOCK(realTimeData_ParserStruct.RC_Cmd),
		VAR_BLOCK(realTimeData_ParserStruct.ExtFC_ROLL),
		VAR_BLOCK(realTimeData_ParserStruct.ExtFC_PITCH),
		DATA_BLOCK(realTimeData_ParserStruct.IMU_Angle),
		DATA_BLOCK(realTimeData_ParserStruct.frameIMU_Angle),
		DATA_BLOCK(realTimeData_ParserStruct.targetAngle),
		VAR_BLOCK(realTimeData_ParserStruct.cycleTime),
		VAR_BLOCK(realTimeData_ParserStruct.I2C_ErrorCount),
		VAR_BLOCK(realTimeData_ParserStruct.errorCode),
		VAR_BLOCK(realTimeData_ParserStruct.batLevel),
		VAR_BLOCK(realTimeData_ParserStruct.RT_DataFlags),
		VAR_BLOCK(realTimeData_ParserStruct.curIMU),
		VAR_BLOCK(realTimeData_ParserStruct.curProfile),
		DATA_BLOCK(realTimeData_ParserStruct.motorPower),
	};

	const ui8 RealTimeData3_ParserStructDB_Size = countof(RealTimeData3_ParserStructDB);


	const ParserBlock_t RealTimeData4_ParserStructDB [] =
	{
		VAR_BLOCK(realTimeData_ParserStruct.AxisRTD[AXIS_X].ACC_Data),
		VAR_BLOCK(realTimeData_ParserStruct.AxisRTD[AXIS_X].gyroData),
		VAR_BLOCK(realTimeData_ParserStruct.AxisRTD[AXIS_Y].ACC_Data),
		VAR_BLOCK(realTimeData_ParserStruct.AxisRTD[AXIS_Y].gyroData),
		VAR_BLOCK(realTimeData_ParserStruct.AxisRTD[AXIS_Z].ACC_Data),
		VAR_BLOCK(realTimeData_ParserStruct.AxisRTD[AXIS_Z].gyroData),
		VAR_BLOCK(realTimeData_ParserStruct.serialErrCnt),
		VAR_BLOCK(realTimeData_ParserStruct.systemError),
		VAR_BLOCK(realTimeData_ParserStruct.systemSubError),
		DATA_BLOCK(realTimeData_ParserStruct.reserved),
		VAR_BLOCK(realTimeData_ParserStruct.RC_ROLL),
		VAR_BLOCK(realTimeData_ParserStruct.RC_PITCH),
		VAR_BLOCK(realTimeData_ParserStruct.RC_YAW),
		VAR_BLOCK(realTimeData_ParserStruct.RC_Cmd),
		VAR_BLOCK(realTimeData_ParserStruct.ExtFC_ROLL),
		VAR_BLOCK(realTimeData_ParserStruct.ExtFC_PITCH),
		DATA_BLOCK(realTimeData_ParserStruct.IMU_Angle),
		DATA_BLOCK(realTimeData_ParserStruct.frameIMU_Angle),
		DATA_BLOCK(realTimeData_ParserStruct.targetAngle),
		VAR_BLOCK(realTimeData_ParserStruct.cycleTime),
		VAR_BLOCK(realTimeData_ParserStruct.I2C_ErrorCount),
		VAR_BLOCK(realTimeData_ParserStruct.errorCode),
		VAR_BLOCK(realTimeData_ParserStruct.batLevel),
		VAR_BLOCK(realTimeData_ParserStruct.RT_DataFlags),
		VAR_BLOCK(realTimeData_ParserStruct.curIMU),
		VAR_BLOCK(realTimeData_ParserStruct.curProfile),
		DATA_BLOCK(realTimeData_ParserStruct.motorPower),
		DATA_BLOCK(realTimeData_ParserStruct.frameCamAngle),
		VAR_BLOCK(realTimeData_ParserStruct.reserved1),
		DATA_BLOCK(realTimeData_ParserStruct.balanceError),
		VAR_BLOCK(realTimeData_ParserStruct.current),
		DATA_BLOCK(realTimeData_ParserStruct.magData),
		VAR_BLOCK(realTimeData_ParserStruct.IMU_Temperature),
		VAR_BLOCK(realTimeData_ParserStruct.frameIMU_Temperature),
		VAR_BLOCK(realTimeData_ParserStruct.IMU_G_Err),
		VAR_BLOCK(realTimeData_ParserStruct.IMU_H_Err),
		DATA_BLOCK(realTimeData_ParserStruct.motorOut),
		VAR_BLOCK(realTimeData_ParserStruct.calibMode),
		VAR_BLOCK(realTimeData_ParserStruct.CAN_IMU_ExtSensErr),
		DATA_BLOCK(realTimeData_ParserStruct.reserved2),
	};

	const ui8 RealTimeData4_ParserStructDB_Size = countof(RealTimeData4_ParserStructDB);
	/**	@}
	 */


	/**	@addtogroup	Get_Angles
	 * 	@{
	 */
	/** @brief	Sample for Big Endian Mapping
	 *
	 * 	@ref	GetAngles_ParserStructDB
	 */
	const GetAngles_t getAngles_ParserStruct;

	const ParserBlock_t GetAngles_ParserStructDB [] =
	{
		VAR_BLOCK(getAngles_ParserStruct.AxisGA[ROLL].IMU_Angle),
		VAR_BLOCK(getAngles_ParserStruct.AxisGA[ROLL].targetAngle),
		VAR_BLOCK(getAngles_ParserStruct.AxisGA[ROLL].targetSpeed),
		VAR_BLOCK(getAngles_ParserStruct.AxisGA[PITCH].IMU_Angle),
		VAR_BLOCK(getAngles_ParserStruct.AxisGA[PITCH].targetAngle),
		VAR_BLOCK(getAngles_ParserStruct.AxisGA[PITCH].targetSpeed),
		VAR_BLOCK(getAngles_ParserStruct.AxisGA[YAW].IMU_Angle),
		VAR_BLOCK(getAngles_ParserStruct.AxisGA[YAW].targetAngle),
		VAR_BLOCK(getAngles_ParserStruct.AxisGA[YAW].targetSpeed),
	};

	const ui8 GetAngles_ParserStructDB_Size = countof(GetAngles_ParserStructDB);


	/** @brief	Sample for Big Endian Mapping
	 *
	 * 	@ref	GetAnglesExt_ParserStructDB
	 */
	const GetAnglesExt_t getAnglesExt_ParserStruct;

	const ParserBlock_t GetAnglesExt_ParserStructDB [] =
	{
		VAR_BLOCK(getAnglesExt_ParserStruct.AxisGAE[ROLL].IMU_Angle),
		VAR_BLOCK(getAnglesExt_ParserStruct.AxisGAE[ROLL].targetAngle),
		VAR_BLOCK(getAnglesExt_ParserStruct.AxisGAE[ROLL].frameCamAngle),
		DATA_BLOCK(getAnglesExt_ParserStruct.AxisGAE[ROLL].reserved),
		VAR_BLOCK(getAnglesExt_ParserStruct.AxisGAE[PITCH].IMU_Angle),
		VAR_BLOCK(getAnglesExt_ParserStruct.AxisGAE[PITCH].targetAngle),
		VAR_BLOCK(getAnglesExt_ParserStruct.AxisGAE[PITCH].frameCamAngle),
		DATA_BLOCK(getAnglesExt_ParserStruct.AxisGAE[PITCH].reserved),
		VAR_BLOCK(getAnglesExt_ParserStruct.AxisGAE[YAW].IMU_Angle),
		VAR_BLOCK(getAnglesExt_ParserStruct.AxisGAE[YAW].targetAngle),
		VAR_BLOCK(getAnglesExt_ParserStruct.AxisGAE[YAW].frameCamAngle),
		DATA_BLOCK(getAnglesExt_ParserStruct.AxisGAE[YAW].reserved),
	};

	const ui8 GetAnglesExt_ParserStructDB_Size = countof(GetAnglesExt_ParserStructDB);
	/**	@}
	 */

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	Data_Stream_Interval
 * 	@{
 */
/**	@brief	Register or update data stream
 *
 *	@note	Firmware: 2.60+\n
 *			A commands sent by the controller with
 *			the fixed rate without request
 *
 *	@note	Firmware: 2.65+\n
 *			...or based on events
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *	@param	*dataStreamInterval - structure with prepared
 *			command parameters
 *	@param	*confirmationState - confirmation structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_RequestDataStream (GeneralSBGC_t *generalSBGC, DataStreamInterval_t *dataStreamInterval, ConfirmationState_t *confirmationState)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_DATA_STREAM_INTERVAL);
	WriteBuff(&cmd, dataStreamInterval, sizeof(DataStreamInterval_t), PM_DATA_STREAM_INTERVAL);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, cmd.commandID);
	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Realtime_Data_Custom
 * 	@{
 */
/**	@brief	Request configurable realtime data
 *
 *	@attention	Firmware: 2.60+
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 * 	@param 	*realTimeDataCustom - structure for storing
 * 			any pieces of real-time data
 * 	@param 	flags - variable containing the required flags:\n
 *				bit0: 	IMU_Angles [3]\n
 *				bit1: 	targetAngles [3]\n
 *				bit2: 	targetSpeed [3]\n
 *				bit3: 	frameCamAngle [3]\n
 *				bit4: 	gyroData [3]\n
 *				bit5: 	RC_Data [6]\n
 *				bit6:	Z_Vector [3], H_Vector [3]\n
 *				bit7: 	RC_Channels [18]\n
 *				bit8: 	ACC_Data [3]\n
 *				bit9: 	motor4_Control data structure\n
 *				bit10: 	AHRS_DebugInfo data structure\n
 *				bit11: 	encoderRaw24 [3][3]\n
 *				bit12: 	IMU_AnglesRad [3]
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_RequestRealTimeDataCustom (GeneralSBGC_t *generalSBGC, RealTimeDataCustom_t *realTimeDataCustom, RealTimeDataCustomFlags_t flags)
{
	if (generalSBGC->_firmwareVersion < 2600)
		return NOT_SUPPORTED_BY_FIRMWARE;

	ui32 checkFlag = 0;
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_REALTIME_DATA_CUSTOM);
	WriteLong(&cmd, flags);
	WriteEmptyBuff(&cmd, 6);  // reserved[6]

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_REALTIME_DATA_CUSTOM), "RealTime Data Custom:") == TX_RX_OK)
	{
		SkipBytes(&cmd, 2);  // ui16 timestampMs offset

		/* Data Parsing */
		FOR_(i, 32)
		{
			checkFlag = flags & (1 << i);
			switch (checkFlag)
			{
				case RTDCF_IMU_ANGLES :
					realTimeDataCustom->IMU_Angles[AXIS_X] = ReadWord(&cmd);
					realTimeDataCustom->IMU_Angles[AXIS_Y] = ReadWord(&cmd);
					realTimeDataCustom->IMU_Angles[AXIS_Z] = ReadWord(&cmd);
					break;

							case RTDCF_TARGET_ANGLES :
								realTimeDataCustom->targetAngles[AXIS_X] = ReadWord(&cmd);
								realTimeDataCustom->targetAngles[AXIS_Y] = ReadWord(&cmd);
								realTimeDataCustom->targetAngles[AXIS_Z] = ReadWord(&cmd);
								break;

				case RTDCF_TARGET_SPEED :
					realTimeDataCustom->targetSpeed[AXIS_X] = ReadWord(&cmd);
					realTimeDataCustom->targetSpeed[AXIS_Y] = ReadWord(&cmd);
					realTimeDataCustom->targetSpeed[AXIS_Z] = ReadWord(&cmd);
					break;

							case RTDCF_STATOR_ROTOR_ANGLE :
								realTimeDataCustom->frameCamAngle[AXIS_X] = ReadWord(&cmd);
								realTimeDataCustom->frameCamAngle[AXIS_Y] = ReadWord(&cmd);
								realTimeDataCustom->frameCamAngle[AXIS_Z] = ReadWord(&cmd);
								break;

				case RTDCF_GYRO_DATA :
					realTimeDataCustom->gyroData[AXIS_X] = ReadWord(&cmd);
					realTimeDataCustom->gyroData[AXIS_Y] = ReadWord(&cmd);
					realTimeDataCustom->gyroData[AXIS_Z] = ReadWord(&cmd);
					break;

							case RTDCF_RC_DATA :
								realTimeDataCustom->RC_Data[ROLL] = ReadWord(&cmd);
								realTimeDataCustom->RC_Data[PITCH] = ReadWord(&cmd);
								realTimeDataCustom->RC_Data[YAW] = ReadWord(&cmd);
								realTimeDataCustom->RC_Data[CMD_] = ReadWord(&cmd);
								realTimeDataCustom->RC_Data[FC_ROLL] = ReadWord(&cmd);
								realTimeDataCustom->RC_Data[FC_PITCH] = ReadWord(&cmd);
								break;

				case RTDCF_Z_VECTOR_H_VECTOR :
					realTimeDataCustom->Z_Vector[AXIS_X] = ReadLong(&cmd);
					realTimeDataCustom->Z_Vector[AXIS_Y] = ReadLong(&cmd);
					realTimeDataCustom->Z_Vector[AXIS_Z] = ReadLong(&cmd);
					realTimeDataCustom->H_Vector[AXIS_X] = ReadLong(&cmd);
					realTimeDataCustom->H_Vector[AXIS_Y] = ReadLong(&cmd);
					realTimeDataCustom->H_Vector[AXIS_Z] = ReadLong(&cmd);
					break;

							case RTDCF_RC_CHANNELS :
								FOR_(k, 18)
								realTimeDataCustom->RC_Channels[i] = ReadWord(&cmd);
								break;

				case RTDCF_ACC_DATA :
					realTimeDataCustom->ACC_Data[AXIS_X] = ReadWord(&cmd);
					realTimeDataCustom->ACC_Data[AXIS_Y] = ReadWord(&cmd);
					realTimeDataCustom->ACC_Data[AXIS_Z] = ReadWord(&cmd);
					break;

							case RTDCF_AHRS_DEBUG_INFO :
								ReadBuff(&cmd, &realTimeDataCustom->AHRS_DebugInfo, sizeof(AHRS_DebugInfo_t), PM_AHRS_DEBUG_INFO);
								break;

				case RTDCF_MOTOR4_CONTROL :
					ReadBuff(&cmd, &realTimeDataCustom->motor4_Control, sizeof(Motor4_Control_t), PM_MOTOR_4_CONTROL);
					break;

							case RTDCF_ENCODER_RAW24 :
							{
								ReadBuff(&cmd, &realTimeDataCustom->encoderRaw24[AXIS_X], 3, PM_DEFAULT_8BIT);
								ReadBuff(&cmd, &realTimeDataCustom->encoderRaw24[AXIS_Y * 3], 3, PM_DEFAULT_8BIT);
								ReadBuff(&cmd, &realTimeDataCustom->encoderRaw24[AXIS_Z * 3], 3, PM_DEFAULT_8BIT);
								break;
							}

				case RTDCF_IMU_ANGLES_RAD :
					realTimeDataCustom->IMU_AnglesRad[AXIS_X] = ReadLong(&cmd);
					realTimeDataCustom->IMU_AnglesRad[AXIS_Y] = ReadLong(&cmd);
					realTimeDataCustom->IMU_AnglesRad[AXIS_Z] = ReadLong(&cmd);
					break;
			}
		}
	}

	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Realtime_Data_3_4
 * 	@{
 */
/** @brief	Receive real-time data
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 * 	@param 	*realTimeData - structure for storing real-time data
 *
 * 	@return Communication status
 */
TxRxStatus_t SBGC32_ReadRealTimeData3 (GeneralSBGC_t *generalSBGC, RealTimeData_t *realTimeData)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_REALTIME_DATA_3);
	ui8 realTime3_Size = offsetof_(realTimeData->frameCamAngle[0], *realTimeData);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_REALTIME_DATA_3), "Real-Time Data 3:") == TX_RX_OK)
		ReadBuff(&cmd, realTimeData, realTime3_Size, PM_REALTIME_DATA_3);

	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Receive extended version of real-time data
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 * 	@param 	*realTimeData - structure for storing real-time data
 *
 * 	@return Communication status
 */
TxRxStatus_t SBGC32_ReadRealTimeData4 (GeneralSBGC_t *generalSBGC, RealTimeData_t *realTimeData)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_REALTIME_DATA_4);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_REALTIME_DATA_4), "Real-Time Data 4:") == TX_RX_OK)
		ReadBuff(&cmd, realTimeData, sizeof(RealTimeData_t), PM_REALTIME_DATA_4);

	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Get_Angles
 * 	@{
 */
/** @brief	Get information about actual gimbal control state
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 * 	@param 	*getAngles - structure for storing angles state
 *
 * 	@return Communication status
 */
TxRxStatus_t SBGC32_GetAngles (GeneralSBGC_t *generalSBGC, GetAngles_t *getAngles)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_GET_ANGLES);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_GET_ANGLES), "Angles:") == TX_RX_OK)
		ReadBuff(&cmd, getAngles, sizeof(GetAngles_t), PM_GET_ANGLES);

	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Get information about angles in different format
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 * 	@param 	*getAnglesExt - structure for storing
 * 			angles state in different format
 *
 * 	@return Communication status
 */
TxRxStatus_t SBGC32_GetAnglesExt (GeneralSBGC_t *generalSBGC, GetAnglesExt_t *getAnglesExt)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_GET_ANGLES_EXT);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_GET_ANGLES_EXT), "Angles Ext:") == TX_RX_OK)
		ReadBuff(&cmd, getAnglesExt, sizeof(GetAnglesExt_t), PM_GET_ANGLES_EXT);

	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	RC_Inputs
 * 	@{
 */
/**	@brief	Read values for the selected RC inputs
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *	@param	*RC_Inputs - structure to send and store RC Inputs info
 *	@param	cfgFlags - RC configuration flags
 *	@param	srcQuan - quantity of RC sources
 *
 *	@note	Must be set:\n
 *			RC_Info_t.RC_Src
 *
 * 	@return Communication status
 */
TxRxStatus_t SBGC32_ReadRC_Inputs (GeneralSBGC_t *generalSBGC, RC_Inputs_t *RC_Inputs, InitCfgFlags_t cfgFlags, ui8 srcQuan)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_READ_RC_INPUTS);
	WriteWord(&cmd, cfgFlags);
	FOR_(i, srcQuan) WriteByte(&cmd, RC_Inputs[i].RC_Src);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_READ_RC_INPUTS), "RC Inputs:") == TX_RX_OK)
		FOR_(i, srcQuan) RC_Inputs[i].RC_Val = ReadWord(&cmd);

	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Debug_Var_3
 * 	@{
 */
/**	@brief	Request information about debug variables
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *	@param	*debugVars3 - structure to storing debug variables info
 *
 * 	@return Communication status
 */
TxRxStatus_t SBGC32_RequestDebugVarInfo3 (GeneralSBGC_t *generalSBGC, DebugVars3_t *debugVars3)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_DEBUG_VARS_INFO_3);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_DEBUG_VARS_INFO_3), "Debug Var Info:") == TX_RX_OK)
	{
		debugVars3->varNum = ReadByte(&cmd);
		FOR_(i, debugVars3->varNum)
		{
			debugVars3->DebugVar[i].varNameLength = ReadByte(&cmd);
			ReadBuff(&cmd, &debugVars3->DebugVar[i].varName, debugVars3->DebugVar[i].varNameLength, PM_DEFAULT_8BIT);
			debugVars3->DebugVar[i].varName[debugVars3->DebugVar[i].varNameLength] = 0;
			debugVars3->DebugVar[i].varType = ReadByte(&cmd);
			SkipBytes(&cmd, 2);
		}
	}

	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Request values of debug variables
 *
 *	@attention	Before using need get information about debug variables
 *				through SBGC32_RequestDebugVarInfo3 function
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *	@param	*debugVars3 - structure to storing debug variable values
 *
 * 	@return Communication status
 */
TxRxStatus_t SBGC32_RequestDebugVarValue3 (GeneralSBGC_t *generalSBGC, DebugVars3_t *debugVars3)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_DEBUG_VARS_3);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_DEBUG_VARS_3), "Debug Var Value:") == TX_RX_OK)
	{
		FOR_(i, debugVars3->varNum)
		{
			switch (debugVars3->DebugVar[i].varType & 0b00001111)
			{
				case _UNSIGNED_CHAR_ :
				case _SIGNED_CHAR_ :
					debugVars3->DebugVar[i].varValue = ReadByte(&cmd);
					break;

				case _UNSIGNED_SHORT_ :
				case _SIGNED_SHORT_ :
					debugVars3->DebugVar[i].varValue = ReadWord(&cmd);
					break;

				case _UNSIGNED_INT_ :
				case _SIGNED_INT_ :
				case _FLOAT_ :
					debugVars3->DebugVar[i].varValue = ReadLong(&cmd);
					break;

				default :
					break;
			}
		}
	}

	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	IMU_Select_3
 * 	@{
 */
/**	@brief	Select which IMU to configure
 *
 * 	@note	For select in simple format action parameter
 * 			must be set to SIMUA_SIMPLE_SELECT (0)
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	IMU_Type - main or frame IMU sensor
 *	@param	action - action with IMU sensor
 *	@param	timeMs - Time for gyroscope calibration, in milliseconds.
 *			If set to 0, default time is used (~4 seconds), which
 *			is good balance between precision and speed
 *	@param	*confirmationState - confirmation structure
 *
 * 	@return Communication status
 */
TxRxStatus_t SBGC32_SelectIMU_3 (GeneralSBGC_t *generalSBGC, IMU_Type_t IMU_Type, SelectIMU_Actions_t action,
								 ui16 timeMs, ConfirmationState_t *confirmationState)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_SELECT_IMU_3);
	WriteByte(&cmd, IMU_Type);
	if (action)  // != SIMUA_SIMPLE_SELECT
	{
		WriteByte(&cmd, action);
		WriteWord(&cmd, timeMs);
		WriteEmptyBuff(&cmd, 8);  // reserved[8]
	}

	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, cmd.commandID);
	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
