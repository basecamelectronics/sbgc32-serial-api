/** ____________________________________________________________________
 *
 * 	SBGC32 Serial API Library v1.1
 *
 *	@file		realtime.c
 *
 *	@brief 		Realtime source file
 *	____________________________________________________________________
 *
 *	@attention	<h3><center>
 *				Copyright © 2023 BaseCam Electronics™.<br>
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

#include "../../sbgc32.h"


#if (SBGC_REALTIME_MODULE)

#if (SYS_BIG_ENDIAN || SBGC_REF_INFO)

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *					Big Endian Mapping and Reference Info Structures
	 */
	/**	@addtogroup	Data_Stream_Interval Data Stream Interval
	 * 	@{
	 */
	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t dataStreamIntervalReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Cmd ID",					_UNSIGNED_CHAR_				),  // 0
		PARAM_BLOCK_(	"Interval Ms",				_UNSIGNED_SHORT_			),  // 1
		PARAMS_BLOCK_(	"Cmd ID",					_UNSIGNED_CHAR_,		8	),  // 2
		PARAM_BLOCK_(	"Sync to Data",				_UNSIGNED_CHAR_				),  // 3
		PARAMS_BLOCK_(	"Reserved",					_RESERVED_CHAR_,		9	),  // 4

	};

	const ui8 dataStreamIntervalReferenceInfoArrayElCnt = countof_(dataStreamIntervalReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Realtime_Data_3_4
	 * 	@{
	 */
	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t realTimeDataReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Acc Data [ROLL]",			_SIGNED_SHORT_				),  // 0
		PARAM_BLOCK_(	"Gyro Data [ROLL]",			_SIGNED_SHORT_				),  // 1
		PARAM_BLOCK_(	"Acc Data [PITCH]",			_SIGNED_SHORT_				),  // 2
		PARAM_BLOCK_(	"Gyro Data [PITCH]",		_SIGNED_SHORT_				),  // 3
		PARAM_BLOCK_(	"Acc Data [YAW]",			_SIGNED_SHORT_				),  // 4
		PARAM_BLOCK_(	"Gyro Data [YAW]",			_SIGNED_SHORT_				),  // 5
		PARAM_BLOCK_(	"Serial Err Cnt",			_UNSIGNED_SHORT_			),  // 6
		PARAM_BLOCK_(	"System Error",				_UNSIGNED_SHORT_			),  // 7
		PARAM_BLOCK_(	"System Sub Error",			_UNSIGNED_CHAR_				),  // 8
		PARAMS_BLOCK_(	"Reserved",					_RESERVED_CHAR_,		3	),  // 9
		PARAM_BLOCK_(	"RC ROLL",					_SIGNED_SHORT_				),  // 10
		PARAM_BLOCK_(	"RC PITCH",					_SIGNED_SHORT_				),  // 11
		PARAM_BLOCK_(	"RC YAW",					_SIGNED_SHORT_				),  // 12
		PARAM_BLOCK_(	"RC Cmd",					_SIGNED_SHORT_				),  // 13
		PARAM_BLOCK_(	"Ext FC ROLL",				_SIGNED_SHORT_				),  // 14
		PARAM_BLOCK_(	"Ext FC PITCH",				_SIGNED_SHORT_				),  // 15
		PARAMS_BLOCK_(	"IMU Angle",				_SIGNED_SHORT_,			3	),  // 16
		PARAMS_BLOCK_(	"Frame IMU Angle",			_SIGNED_SHORT_,			3	),  // 17
		PARAMS_BLOCK_(	"Target Angle",				_SIGNED_SHORT_,			3	),  // 18
		PARAM_BLOCK_(	"Cycle Time",				_UNSIGNED_SHORT_			),  // 19
		PARAM_BLOCK_(	"I2C Error Count",			_UNSIGNED_SHORT_			),  // 20
		PARAM_BLOCK_(	"Error Code",				_UNSIGNED_CHAR_				),  // 21
		PARAM_BLOCK_(	"Bat Level",				_UNSIGNED_SHORT_			),  // 22
		PARAM_BLOCK_(	"RT Data Flags",			(_UNSIGNED_CHAR_ | _FLAG_)	),  // 23
		PARAM_BLOCK_(	"Cur IMU",					_UNSIGNED_CHAR_				),  // 24
		PARAM_BLOCK_(	"Cur Profile",				_UNSIGNED_CHAR_				),  // 25
		PARAMS_BLOCK_(	"Motor Power",				_UNSIGNED_CHAR_,		3	),  // 26
		/* Realtime Data 4 */
		PARAMS_BLOCK_(	"Frame Cam Angle",			_SIGNED_SHORT_,			3	),  // 27
		PARAM_BLOCK_(	"Reserved 1",				_RESERVED_CHAR_				),  // 28
		PARAMS_BLOCK_(	"Balance Error",			_SIGNED_SHORT_,			3	),  // 29
		PARAM_BLOCK_(	"Current",					_UNSIGNED_SHORT_			),  // 30
		PARAMS_BLOCK_(	"Mag Data",					_SIGNED_SHORT_,			3	),  // 31
		PARAM_BLOCK_(	"IMU Temperature",			_SIGNED_CHAR_				),  // 32
		PARAM_BLOCK_(	"Frame IMU Temperature",	_SIGNED_CHAR_				),  // 33
		PARAM_BLOCK_(	"IMU G Err",				_UNSIGNED_CHAR_				),  // 34
		PARAM_BLOCK_(	"IMU H Err",				_UNSIGNED_CHAR_				),  // 35
		PARAMS_BLOCK_(	"Motor Out",				_SIGNED_SHORT_,			3	),  // 36
		PARAM_BLOCK_(	"Calib Mode",				_UNSIGNED_CHAR_				),  // 37
		PARAM_BLOCK_(	"CAN IMU Ext Sens Err",		_UNSIGNED_CHAR_				),  // 38
		PARAMS_BLOCK_(	"Reserved 2",				_RESERVED_CHAR_,		28	),  // 39

	};

	const ui8 realTimeDataReferenceInfoArrayElCnt = countof_(realTimeDataReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Get_Angles
	 * 	@{
	 */
	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t getAnglesReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"IMU Angle [ROLL]",			_SIGNED_SHORT_				),  // 0
		PARAM_BLOCK_(	"Target Angle [ROLL]",		_SIGNED_SHORT_				),  // 1
		PARAM_BLOCK_(	"Target Speed [ROLL]",		_SIGNED_SHORT_				),  // 2
		PARAM_BLOCK_(	"IMU Angle [PITCH]",		_SIGNED_SHORT_				),  // 3
		PARAM_BLOCK_(	"Target Angle [PITCH]",		_SIGNED_SHORT_				),  // 4
		PARAM_BLOCK_(	"Target Speed [PITCH]",		_SIGNED_SHORT_				),  // 5
		PARAM_BLOCK_(	"IMU Angle [YAW]",			_SIGNED_SHORT_				),  // 6
		PARAM_BLOCK_(	"Target Angle [YAW]",		_SIGNED_SHORT_				),  // 7
		PARAM_BLOCK_(	"Target Speed [YAW]",		_SIGNED_SHORT_				),  // 8

	};

	const ui8 getAnglesReferenceInfoArrayElCnt = countof_(getAnglesReferenceInfoArray);


	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t getAnglesExtReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"IMU Angle [ROLL]",			_SIGNED_SHORT_				),  // 0
		PARAM_BLOCK_(	"Target Angle [ROLL]",		_SIGNED_SHORT_				),  // 1
		PARAM_BLOCK_(	"Frame Cam Angle [ROLL]",	_SIGNED_INT_				),  // 2
		PARAMS_BLOCK_(	"Reserved",					_RESERVED_CHAR_,		10	),  // 3
		PARAM_BLOCK_(	"IMU Angle [PITCH]",		_SIGNED_SHORT_				),  // 4
		PARAM_BLOCK_(	"Target Angle [PITCH]",		_SIGNED_SHORT_				),  // 5
		PARAM_BLOCK_(	"Frame Cam Angle [PITCH]",	_SIGNED_INT_				),  // 6
		PARAMS_BLOCK_(	"Reserved",					_RESERVED_CHAR_,		10	),  // 7
		PARAM_BLOCK_(	"IMU Angle [YAW]",			_SIGNED_SHORT_				),  // 8
		PARAM_BLOCK_(	"Target Angle [YAW]",		_SIGNED_SHORT_				),  // 9
		PARAM_BLOCK_(	"Frame Cam Angle [YAW]",	_SIGNED_INT_				),  // 10
		PARAMS_BLOCK_(	"Reserved",					_RESERVED_CHAR_,		10	),  // 11

	};

	const ui8 getAnglesExtReferenceInfoArrayElCnt = countof_(getAnglesExtReferenceInfoArray);
	/**	@}
	 */

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	Data_Stream_Interval
 * 	@{
 */
/**	@brief	Registers or updates a data stream
 *
 *	@attention	Firmware: 2.60+\n
 *				Commands sent by the controller with
 *				the fixed rate without request
 *
 *	@note	Firmware: 2.65+\n
 *			...or based on events
 *
 *			After use @ref SBGC32_StopDataStream function is required
 *			update DataStreamInterval_t.intervalMs field
 *
 *	@ref	SBGC32_ParseDataStream function
 *			for parse the requested data
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *	@param	*dataStreamInterval - structure with prepared
 *			command parameters
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_RequestDataStream (GeneralSBGC_t *generalSBGC, DataStreamInterval_t *dataStreamInterval)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_DATA_STREAM_INTERVAL);
	WriteBuff(&cmd, dataStreamInterval, sizeof(DataStreamInterval_t), PM_DATA_STREAM_INTERVAL);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Stops a data stream
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *	@param	*dataStreamInterval - working DataStream descriptor
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_StopDataStream (GeneralSBGC_t *generalSBGC, DataStreamInterval_t *dataStreamInterval)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_DATA_STREAM_INTERVAL);
	dataStreamInterval->intervalMs = 0;
	WriteBuff(&cmd, dataStreamInterval, sizeof(DataStreamInterval_t), PM_DATA_STREAM_INTERVAL);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Parses the requested data stream
 *
 *  @ref	SBGC32_RequestDataStream function
 *			for request a data stream
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *	@param	*dataStreamStruct - one of the relevant
 *			structs to the cmdID parameter
 *	@param	cmdID - sent in the DataStreamInterval_t.cmdID
 *			parameter, for which a response is expected
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ParseDataStream (GeneralSBGC_t *generalSBGC, void *dataStreamStruct, SBGC_Command_t cmdID)
{
	SerialCommand_t cmd;

	if (getcommstatus_(CheckReceipt(generalSBGC, SBGC32_FindCommand(generalSBGC, &cmd, cmdID, generalSBGC->rxTimeout), "Data Stream:")))
	{
		switch (cmdID)
		{
			case CMD_REALTIME_DATA_3 :
			{
				/* dataStreamStruct = &RealTimeData_t struct for reading */
				ReadBuff(&cmd, dataStreamStruct, SIZEOF_REALTIME_DATA_3, PM_REALTIME_DATA_3);
				break;
			}

						case CMD_REALTIME_DATA_4 :
						{
							/* dataStreamStruct = &RealTimeData_t struct for reading */
							ReadBuff(&cmd, dataStreamStruct, sizeof(RealTimeData_t), PM_REALTIME_DATA_4);
							break;
						}

			case CMD_REALTIME_DATA_CUSTOM :
			{
				/* This case will not work correctly in the big endian systems.
				   You must repair <PM_DEFAULT_8BIT> value to custom, corresponding to the requested data.

				   Also, you can get the parsed data to custom data structure and then transfer it to the
				   RealTimeDataCustom_t struct. This method can be used, when you need to get
				   separated data arrays.

				   Anyway it will began with ui16 timestampMs value.
				   dataStreamStruct = &RealTimeDataCustom_t struct for reading */
				ReadBuff(&cmd, dataStreamStruct, cmd.payloadSize, PM_DEFAULT_8BIT);
				break;
			}

						case CMD_AHRS_HELPER :
						{
							/* dataStreamStruct = &RealTimeData_t->Z_Vect[0] field for reading */
							ReadBuff(&cmd, dataStreamStruct, cmd.payloadSize, PM_DEFAULT_8BIT);
							for (ui8 i = 0; i < 6; i++) ReadLong(&cmd);
							break;
						}

			case CMD_EVENT :
			{
				if (cmd.readPos != 0)
					cmd.readPos = 0;

				ReadBuff(&cmd, dataStreamStruct, SIZEOF_EVENT, PM_DEFAULT_8BIT);
				break;
			}

						default :
							break;
		}
	}

	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Realtime_Data_Custom
 * 	@{
 */
/**	@brief	Requests configurable realtime data
 *
 *	@attention	Firmware: 2.60+
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 * 	@param 	*realTimeDataCustom - structure for storing
 * 			any pieces of real-time data
 * 	@param 	flags - variable containing the required flags:\n
 *				bit0: 		IMU_Angles [3]				RTDCF_IMU_ANGLES\n
 *				bit1: 		targetAngles [3]			RTDCF_TARGET_ANGLES\n
 *				bit2: 		targetSpeed [3]				RTDCF_TARGET_SPEED\n
 *				bit3: 		frameCamAngle [3]			RTDCF_STATOR_ROTOR_ANGLE\n
 *				bit4: 		gyroData [3]				RTDCF_GYRO_DATA\n
 *				bit5: 		RC_Data [6]					RTDCF_RC_DATA\n
 *				bit6:		Z_Vector [3], H_Vector [3]	RTDCF_Z_VECTOR_H_VECTOR\n
 *				bit7: 		RC_Channels [18]			RTDCF_RC_CHANNELS\n
 *				bit8: 		ACC_Data [3]				RTDCF_ACC_DATA\n
 *				bit9: 		motor4_Control struct		RTDCF_MOTOR4_CONTROL\n
 *				bit10: 		AHRS_DebugInfo struct		RTDCF_AHRS_DEBUG_INFO\n
 *				bit11: 		encoderRaw24 [3][3]			RTDCF_ENCODER_RAW24\n
 *				bit12: 		IMU_AnglesRad [3]			RTDCF_IMU_ANGLES_RAD
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_RequestRealTimeDataCustom (GeneralSBGC_t *generalSBGC, RealTimeDataCustom_t *realTimeDataCustom, RealTimeDataCustomFlag_t flags)
{
	#if (SBGC_DEBUG_MODE == SET_OFF)

		if (generalSBGC->_firmwareVersion < 2600)
			return NOT_SUPPORTED_BY_FIRMWARE;

	#endif

	ui32 checkFlag = 0;
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_REALTIME_DATA_CUSTOM);
	WriteLong(&cmd, flags);
	WriteEmptyBuff(&cmd, 6);  // reserved[6]

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_REALTIME_DATA_CUSTOM), "RealTime Data Custom:") == TX_RX_OK)
	{
		realTimeDataCustom->timestampMs = ReadWord(&cmd);

		/* Data Parsing */
		for (ui8 i = 0; i < 32; i++)
		{
			checkFlag = flags & (1 << i);
			switch (checkFlag)
			{
				case RTDCF_IMU_ANGLES :
					realTimeDataCustom->IMU_Angles[ROLL] = ReadWord(&cmd);
					realTimeDataCustom->IMU_Angles[PITCH] = ReadWord(&cmd);
					realTimeDataCustom->IMU_Angles[YAW] = ReadWord(&cmd);
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
								realTimeDataCustom->frameCamAngle[ROLL] = ReadWord(&cmd);
								realTimeDataCustom->frameCamAngle[PITCH] = ReadWord(&cmd);
								realTimeDataCustom->frameCamAngle[YAW] = ReadWord(&cmd);
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
								for (ui8 k = 0; k < 18; k++)
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
								ReadBuff(&cmd, &realTimeDataCustom->encoderRaw24[AXIS_X][0], 3, PM_DEFAULT_8BIT);
								ReadBuff(&cmd, &realTimeDataCustom->encoderRaw24[AXIS_Y][1], 3, PM_DEFAULT_8BIT);
								ReadBuff(&cmd, &realTimeDataCustom->encoderRaw24[AXIS_Z][2], 3, PM_DEFAULT_8BIT);
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

	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Realtime_Data_3_4
 * 	@{
 */
/** @brief	Receives real-time data
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

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_REALTIME_DATA_3), "Real-Time Data 3:") == TX_RX_OK)
		ReadBuff(&cmd, realTimeData, SIZEOF_REALTIME_DATA_3, PM_REALTIME_DATA_3);
		/* or offsetof_(realTimeData->frameCamAngle, realTimeData); */

	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Receives extended version of real-time data
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

	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Get_Angles
 * 	@{
 */
/** @brief	Get information about the actual gimbal control state
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

	return generalSBGC->_parserCurrentStatus;
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

	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	RC_Inputs
 * 	@{
 */
/**	@brief	Read values for the selected RC inputs
 *
 *	@note	Must be set:\n
 *			RC_Inputs_t.RC_Src
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *	@param	*RC_Inputs - structure to send and store RC Inputs info
 *	@param	cfgFlags - RC configuration flags
 *	@param	srcQuan - quantity of RC sources
 *
 * 	@return Communication status
 */
TxRxStatus_t SBGC32_ReadRC_Inputs (GeneralSBGC_t *generalSBGC, RC_Inputs_t *RC_Inputs, InitCfgFlag_t cfgFlags, ui8 srcQuan)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_READ_RC_INPUTS);
	WriteWord(&cmd, cfgFlags);
	for (ui8 i = 0; i < srcQuan; i++) WriteByte(&cmd, RC_Inputs[i].RC_Src);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_READ_RC_INPUTS), "RC Inputs:") == TX_RX_OK)
		for (ui8 i = 0; i < srcQuan; i++)
			RC_Inputs[i].RC_Val = ReadWord(&cmd);

	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Debug_Var_3
 * 	@{
 */
/**	@brief	Requests information about debug variables
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

		for (ui8 i = 0; i < debugVars3->varNum; i++)
		{
			debugVars3->DebugVar[i].varNameLength = ReadByte(&cmd);
			ReadBuff(&cmd, &debugVars3->DebugVar[i].varName, debugVars3->DebugVar[i].varNameLength, PM_DEFAULT_8BIT);
			debugVars3->DebugVar[i].varName[debugVars3->DebugVar[i].varNameLength] = 0;
			debugVars3->DebugVar[i].varType = ReadByte(&cmd);
			SkipBytes(&cmd, 2);
		}
	}

	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Requests values of debug variables
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
		for (ui8 i = 0; i < debugVars3->varNum; i++)
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

	return generalSBGC->_parserCurrentStatus;
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
 *
 * 	@return Communication status
 */
TxRxStatus_t SBGC32_SelectIMU_3 (GeneralSBGC_t *generalSBGC, IMU_Type_t IMU_Type, SelectIMU_Action_t action,
								 ui16 timeMs)
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
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */

#endif /* SBGC_REALTIME_MODULE */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
