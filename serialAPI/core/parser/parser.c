/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2.1
 *
 *	@file		parser.c
 *
 *	@brief		Source file of the core commands data parsing
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

#include "../../sbgc32.h"


/* Static Constants ----------------------------------------------------
 */
/* Serial command waits data receive operation. Hidden system part of SerialCommandParam_t */
#define		SCParam_RX				0x80

/* RealtimeData3 command structure part elements number */
#define		COUNTOF_REALTIME_DATA_3	27

#define		SBGC_LL_STATUS_NAME_MAX_LENGTH	25
#define		SBGC_COMM_STATUS_NAME_MAX_LEN	33
#define		SBGC_CMD_ID_NAME_MAX_LEN		31
#define		SBGC_CMD_STATUS_NAME_MAX_LEN	10
#define		SBGC_ERROR_CODE_NAME_MAX_LEN	20


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								Executable Functions
 */
/**	@addtogroup	Data_Parse
 *	@{
 */
static ui8 ParserSBGC32_ConvertTypeToSize (sbgcVarType_t varType)
{
	ui8 res = 0;

	switch (varType & CLEAN_TYPE_MASK)
	{
		case sbgcUCHAR :
		case sbgcCHAR :
		case sbgcRCHAR :
			res = 1;
			break;

		case sbgcUSHORT :
		case sbgcSHORT :
			res = 2;
			break;

		case sbgcUINT :
		case sbgcINT :
		case sbgcFLOAT :
			res = 4;
			break;

		default :
			break;
	}

	return res;
}


#if (SBGC_USES_REF_INFO)

	/**	@brief	Appoints Serial API reference structure
	 *
	 *	@note	Private function
	 *
	 *	@param	*uStruct - pointer to pointer to undefined structure
	 *	@param	parserMap - structure type for assign
	 *
	 *	@return	Number of elements of an assigned structure
	 */
	static ui8 ParserSBGC32_AssignStructByParserMap (const void *uStruct, sbgcParserMap_t parserMap)
	{
		const sbgcParameterReferenceInfo_t **buffArr = (const sbgcParameterReferenceInfo_t**)uStruct;

		switch (parserMap)
		{
			#if (SBGC_ADJVAR_MODULE)

				case PM_AV_CONFIG:
					*buffArr = adjVarsCfgReferenceInfoArray;
					return adjVarsCfgReferenceInfoArrayElCnt;

				case PM_AV_STATE_OLD_TX :
					*buffArr = adjVarsStateOldTxReferenceInfoArray;
					return adjVarsStateOldTxReferenceInfoArrayElCnt;

				case PM_AV_STATE_OLD_RX :
					*buffArr = adjVarsStateOldRxReferenceInfoArray;
					return adjVarsStateOldRxReferenceInfoArrayElCnt;

				case PM_AV_STATE_TX :
					*buffArr = adjVarsStateTxReferenceInfoArray;
					return adjVarsStateTxReferenceInfoArrayElCnt;

				case PM_AV_STATE_RX :
					*buffArr = adjVarsStateRxReferenceInfoArray;
					return adjVarsStateRxReferenceInfoArrayElCnt;

			#endif

			#if (SBGC_CALIB_MODULE)

				case PM_IMU_EXT_CALIB :
					*buffArr = IMU_ExtCalibReferenceInfoArray;
					return IMU_ExtCalibReferenceInfoArrayElCnt;

				case PM_CALIB_INFO :
					*buffArr = calibInfoReferenceInfoArray;
					return calibInfoReferenceInfoArrayElCnt;

				case PM_CALIB_COGGING :
					*buffArr = calibCoggingReferenceInfoArray;
					return calibCoggingReferenceInfoArrayElCnt;

			#endif

			case PM_AHRS_DEBUG_INFO :
				*buffArr = AHRS_DebugInfoReferenceInfoArray;
				return AHRS_DebugInfoReferenceInfoArrayElCnt;

			case PM_MOTOR_4_CONTROL :
				*buffArr = motor4_ControlReferenceInfoArray;
				return motor4_ControlReferenceInfoArrayElCnt;

			#if (SBGC_CONTROL_MODULE)

				case PM_CONTROL :
					*buffArr = controlReferenceInfoArray;
					return controlReferenceInfoArrayElCnt;

				case PM_CONTROL_EXT :
					*buffArr = controlExtReferenceInfoArray;
					return controlExtReferenceInfoArrayElCnt;

				case PM_CONTROL_QUAT :
					*buffArr = controlQuatReferenceInfoArray;
					return controlQuatReferenceInfoArrayElCnt;

				case PM_CONTROL_CONFIG :
					*buffArr = controlConfigReferenceInfoArray;
					return controlConfigReferenceInfoArrayElCnt;

				case PM_CONTROL_QUAT_CONFIG :
					*buffArr = controlQuatConfigReferenceInfoArray;
					return controlQuatConfigReferenceInfoArrayElCnt;

				case PM_EXT_MOTORS_CONTROL_CONFIG :
					*buffArr = extMotorsControlConfigReferenceInfoArray;
					return extMotorsControlConfigReferenceInfoArrayElCnt;

			#endif

			#if (SBGC_IMU_MODULE)

				case PM_EXT_IMU_DEBUG_INFO :
					*buffArr = extIMU_DebugInfoReferenceInfoArray;
					return extIMU_DebugInfoReferenceInfoArrayElCnt;

				case PM_GYRO_CORRECTION :
					*buffArr = gyroCorrectionReferenceInfoArray;
					return gyroCorrectionReferenceInfoArrayElCnt;

				case PM_AHRS_HELPER :
					*buffArr = AHRS_HelperReferenceInfoArray;
					return AHRS_HelperReferenceInfoArrayElCnt;

				case PM_HELPER_DATA :
					*buffArr = helperDataReferenceInfoArray;
					return helperDataReferenceInfoArrayElCnt;

				case PM_HELPER_DATA_EXT :
					*buffArr = helperDataExtReferenceInfoArray;
					return helperDataExtReferenceInfoArrayElCnt;

			#endif

			#if (SBGC_PROFILES_MODULE)

				case PM_MAIN_PARAMS_3 :
					*buffArr = mainParams3_ReferenceInfoArray;
					return mainParams3_ReferenceInfoArrayElCnt;

				case PM_MAIN_PARAMS_EXT :
					*buffArr = mainParamsExtReferenceInfoArray;
					return mainParamsExtReferenceInfoArrayElCnt;

				case PM_MAIN_PARAMS_EXT2 :
					*buffArr = mainParamsExt2_ReferenceInfoArray;
					return mainParamsExt2_ReferenceInfoArrayElCnt;

				case PM_MAIN_PARAMS_EXT3 :
					*buffArr = mainParamsExt3_ReferenceInfoArray;
					return mainParamsExt3_ReferenceInfoArrayElCnt;

			#endif

			#if (SBGC_REALTIME_MODULE)

				case PM_DATA_STREAM_INTERVAL :
					*buffArr = dataStreamIntervalReferenceInfoArray;
					return dataStreamIntervalReferenceInfoArrayElCnt;

				case PM_SYSTEM_POWER_STATE :
					*buffArr = systemPowerStateReferenceInfoArray;
					return systemPowerStateReferenceInfoArrayElCnt;

				case PM_COMMUNICATION_ERRORS :
					*buffArr = communicationErrorsReferenceInfoArray;
					return communicationErrorsReferenceInfoArrayElCnt;

				case PM_SYSTEM_STATE :
					*buffArr = systemStateReferenceInfoArray;
					return systemStateReferenceInfoArrayElCnt;

				case PM_REALTIME_DATA_3 :
				case PM_REALTIME_DATA_4 :
				{
					*buffArr = realTimeDataReferenceInfoArray;

					if (parserMap == PM_REALTIME_DATA_3)
						return COUNTOF_REALTIME_DATA_3;

					return realTimeDataReferenceInfoArrayElCnt;
				}

				case PM_GET_ANGLES :
					*buffArr = getAnglesReferenceInfoArray;
					return getAnglesReferenceInfoArrayElCnt;

				case PM_GET_ANGLES_EXT :
					*buffArr = getAnglesExtReferenceInfoArray;
					return getAnglesExtReferenceInfoArrayElCnt;

			#endif

			#if (SBGC_SERVICE_MODULE)

				case PM_BOARD_INFO :
					*buffArr = boardInfoReferenceInfoArray;
					return boardInfoReferenceInfoArrayElCnt;

				case PM_BOARD_INFO_3 :
					*buffArr = boardInfo3_ReferenceInfoArray;
					return boardInfo3_ReferenceInfoArrayElCnt;

				case PM_AUTO_PID :
					*buffArr = autoPID_ReferenceInfoArray;
					return autoPID_ReferenceInfoArrayElCnt;

				case PM_AUTO_PID_2 :
					*buffArr = autoPID2_ReferenceInfoArray;
					return autoPID2_ReferenceInfoArrayElCnt;

				case PM_AUTO_PID_STATE :
					*buffArr = autoPID_StateReferenceInfoArray;
					return autoPID_StateReferenceInfoArrayElCnt;

				case PM_SYNC_MOTORS :
					*buffArr = syncMotorsReferenceInfoArray;
					return syncMotorsReferenceInfoArrayElCnt;

				case PM_SCRIPT_DEBUG_INFO :
					*buffArr = scriptDebugInfoReferenceInfoArray;
					return scriptDebugInfoReferenceInfoArrayElCnt;

				case PM_STATE_VARS :
					*buffArr = stateVarsReferenceInfoArray;
					return stateVarsReferenceInfoArrayElCnt;

				case PM_CAN_DEVICE_SCAN :
					*buffArr = CAN_DeviceScanReferenceInfoArray;
					return CAN_DeviceScanReferenceInfoArrayElCnt;

			#endif

			/* Prevent [-Wswitch] warning (never come here) */
			default :
				break;
		}

		*buffArr = NULL;
		return 0;
	}


	/**	@brief	Gives address of structure element by number
	 *
	 *	@param	*structure - command structure where finding is
	 *	@param	parserMap - data type required for correct parsing
	 *	@param	num - number of structure element
	 *
	 *	@return	Address of chosen element
	 */
	void *ParserSBGC32_GetElementAddress (const void* structure, sbgcParserMap_t parserMap, ui8 num)
	{
		ui8 *structureTemp = (ui8*)structure;
		ui32 currentAddrOffset = 0;

		const sbgcParameterReferenceInfo_t *parameterReferenceInfo = NULL;
		ui8 parameterReferenceInfoElCnt = ParserSBGC32_AssignStructByParserMap(&parameterReferenceInfo, parserMap);

		ui8 parameterSize;

		for (ui8 i = 0; i < parameterReferenceInfoElCnt; i++)
		{
			/* Obtain an element type for made correct structure moving */
			parameterSize = ParserSBGC32_ConvertTypeToSize(parameterReferenceInfo[i].type);

			if (i == num)
				return (void*)(structureTemp + currentAddrOffset);

			for (ui8 k = 0; k < parameterReferenceInfo[i].length; k++)
				currentAddrOffset += parameterSize;
		}

		return NULL;
	}

#endif


#if (SBGC_SYS_BIG_ENDIAN)

	/**	@brief	Swaps bytes by address
	 *
	 *	@note	Private function
	 *
	 *	@param	*p1 - pointer to first byte
	 *	@param	*p2 - pointer to second byte
	 */
	static void ParserSBGC32_SwapMemoryContent (ui8 *p1, ui8 *p2)
	{
		ui8 temp = *p1;
		*p1 = *p2;
		*p2 = temp;
	}


	/**	@brief	Rearranges data depending on the
	 *			organization of system memory
	 *
	 *	@note	Private function
	 *
	 *	@param	*structure - structure buffer to bytes rearrange
	 *	@param	size - structure buffer size
	 *	@param	parserMap - data type required for correct parsing
	 */
	static void ParserSBGC32_SwapBytesInStruct (ui8 *structure, ui8 size, sbgcParserMap_t parserMap)
	{
		if (parserMap == PM_DEFAULT_8BIT)
			return;

		else if (parserMap == PM_DEFAULT_16BIT)
		{
			for (ui8 i = 0; i < size; i += 2)
				ParserSBGC32_SwapMemoryContent(&structure[i], &structure[i + 1]);

			return;
		}

		else if (parserMap == PM_DEFAULT_32BIT)
		{
			for (ui8 i = 0; i < size; i += 4)
			{
				ParserSBGC32_SwapMemoryContent(&structure[i], &structure[i + 3]);
				ParserSBGC32_SwapMemoryContent(&structure[i + 1], &structure[i + 2]);
			}

			return;
		}

		const sbgcParameterReferenceInfo_t *parameterReferenceInfo = NULL;

		ui8 parameterReferenceInfoElCnt = ParserSBGC32_AssignStructByParserMap(&parameterReferenceInfo, parserMap);

		ui8 parameterSize;
		ui32 currentAddrOffset = 0;

		for (ui8 i = 0; i < parameterReferenceInfoElCnt; i++)
		{
			parameterSize = ParserSBGC32_ConvertTypeToSize(parameterReferenceInfo[i].type);

			for (ui8 k = 0; k < parameterReferenceInfo[i].length; k++)
			{
				switch (parameterSize)
				{
					case 1 :
						currentAddrOffset++;
						break;

					case 2 :
						ParserSBGC32_SwapMemoryContent((structure + currentAddrOffset), (structure + currentAddrOffset + 1));
						currentAddrOffset += 2;
						break;

					case 4 :
						ParserSBGC32_SwapMemoryContent((structure + currentAddrOffset), (structure + currentAddrOffset + 3));
						ParserSBGC32_SwapMemoryContent((structure + currentAddrOffset + 1), (structure + currentAddrOffset + 2));
						currentAddrOffset += 4;
						break;
				}
			}
		}
	}

#endif


/**	@brief	Converts the serial status to string
 *
 *	@param	serialStatus - status of Tx/Rx operation
 *	@param	*str - writable buffer
 *	@param	size - buffer size
 *
 *	@return	Length of written string
 */
ui8 ParserSBGC32_ConvertSerialStatusToString (serialAPI_CommandStatus_t serialStatus, char *str, ui8 size)
{
	if (size < SBGC_LL_STATUS_NAME_MAX_LENGTH) return 0;

	switch (serialStatus)
	{
		case serialAPI_TX_RX_OK :					memcpy(str, TEXT_LENGTH_("TX_RX_OK")); break;

		#if (SBGC_NEED_CONFIRM_CMD == sbgcOFF)
			case serialAPI_RX_REJECTED_CONFIRM_CMD :memcpy(str, TEXT_LENGTH_("RX_REJECTED_CONFIRM_CMD")); break;
		#endif

		case serialAPI_TX_BUS_BUSY_ERROR :			memcpy(str, TEXT_LENGTH_("TX_BUS_BUSY_ERROR")); break;
		case serialAPI_RX_EMPTY_BUFF_ERROR :		memcpy(str, TEXT_LENGTH_("RX_EMPTY_BUFF_ERROR")); break;
		case serialAPI_RX_BUFFER_REALTIME_ERROR :	memcpy(str, TEXT_LENGTH_("RX_BUFFER_REALTIME_ERROR")); break;
		case serialAPI_RX_HEADER_CHECKSUM_ERROR :	memcpy(str, TEXT_LENGTH_("RX_HEADER_CHECKSUM_ERROR")); break;
		case serialAPI_RX_PAYLOAD_CHECKSUM_ERROR :	memcpy(str, TEXT_LENGTH_("RX_PAYLOAD_CHECKSUM_ERROR")); break;
		case serialAPI_RX_NOT_FOUND_ERROR :			memcpy(str, TEXT_LENGTH_("RX_NOT_FOUND_ERROR")); break;
		case serialAPI_RX_BUFFER_OVERFLOW_ERROR :	memcpy(str, TEXT_LENGTH_("RX_BUFFER_OVERFLOW_ERROR")); break;
	}

	return strlen(str);
}


/**	@brief	Converts the communication status to string
 *
 *	@param	communicationStatus - status of communication operation
 *	@param	*str - writable buffer
 *	@param	size - buffer size
 *
 *	@return	Length of written string
 */
ui8 ParserSBGC32_ConvertCommunicationStatusToString (sbgcCommandStatus_t communicationStatus, char *str, ui8 size)
{
	if (size < SBGC_COMM_STATUS_NAME_MAX_LEN) return 0;

	switch (communicationStatus)
	{
		case sbgcCOMMAND_OK :						memcpy(str, TEXT_LENGTH_("COMMAND_OK")); break;
		case sbgcCOMMAND_PROCESSING :				memcpy(str, TEXT_LENGTH_("COMMAND_PROCESSING")); break;
		case sbgcCOMMAND_QUEUE_IS_EMPTY :			memcpy(str, TEXT_LENGTH_("COMMAND_QUEUE_IS_EMPTY")); break;
		case sbgcCOMMAND_TX_ERROR :					memcpy(str, TEXT_LENGTH_("COMMAND_TX_ERROR")); break;
		case sbgcCOMMAND_RX_ERROR :					memcpy(str, TEXT_LENGTH_("COMMAND_RX_ERROR")); break;
		case sbgcCOMMAND_NOT_SUPPORTED_BY_FIRMWARE :memcpy(str, TEXT_LENGTH_("COMMAND_NOT_SUPPORTED_BY_FIRMWARE")); break;
		case sbgcCOMMAND_NOT_SUPPORTED_BY_HARDWARE :memcpy(str, TEXT_LENGTH_("COMMAND_NOT_SUPPORTED_BY_HARDWARE")); break;
		case sbgcCOMMAND_NOT_SUPPORTED_FEATURE :	memcpy(str, TEXT_LENGTH_("COMMAND_NOT_SUPPORTED_FEATURE")); break;
		case sbgcCOMMAND_PARAM_ASSERT_ERROR :		memcpy(str, TEXT_LENGTH_("COMMAND_PARAM_ASSERT_ERROR")); break;
		case sbgcCOMMAND_NOTHING_TO_CHANGE :		memcpy(str, TEXT_LENGTH_("COMMAND_NOTHING_TO_CHANGE")); break;
		case sbgcCOMMAND_DESTINATION_IS_NULL :		memcpy(str, TEXT_LENGTH_("COMMAND_DESTINATION_IS_NULL")); break;
		case sbgcCOMMAND_BUFFER_OVERFLOW_ERROR :	memcpy(str, TEXT_LENGTH_("COMMAND_BUFFER_OVERFLOW_ERROR")); break;
		case sbgcCOMMAND_SERIAL_API_BUSY_ERROR :	memcpy(str, TEXT_LENGTH_("COMMAND_SERIAL_API_BUSY_ERROR")); break;

		#if (SBGC_USES_TOKENS)
			case sbgcCOMMAND_TOKEN_NOT_FOUND :		memcpy(str, TEXT_LENGTH_("COMMAND_TOKEN_NOT_FOUND")); break;
		#endif

		#if (SBGC_OPTIMIZE_COMMANDS)
			case sbgcCOMMAND_BUFFER_OPTIMIZED :		memcpy(str, TEXT_LENGTH_("COMMAND_BUFFER_OPTIMIZED")); break;
		#endif
	}

	return strlen(str);
}


/**	@brief	Converts the serial command ID to string
 *
 *	@param	*serialCommand - pointer to serial command
 *	@param	*str - writable buffer
 *	@param	size - buffer size
 *
 *	@return	Length of a writable string
 */
ui8 ParserSBGC32_ConvertCommandID_ToString (serialAPI_Command_t *serialCommand, char *str, ui8 size)
{
	if (size < SBGC_CMD_ID_NAME_MAX_LEN) return 0;

	switch (serialCommand->_commandID)
	{
		case sbgcANY_SERIAL_COMMAND :				break;

		case CMD_BOARD_INFO_3 :						memcpy(str, TEXT_LENGTH_("CMD_BOARD_INFO_3")); break;
		case CMD_READ_PARAMS_3 :					memcpy(str, TEXT_LENGTH_("CMD_READ_PARAMS_3")); break;
		case CMD_WRITE_PARAMS_3 :					memcpy(str, TEXT_LENGTH_("CMD_WRITE_PARAMS_3")); break;
		case CMD_REALTIME_DATA_3 :					memcpy(str, TEXT_LENGTH_("CMD_REALTIME_DATA_3")); break;
		case CMD_SELECT_IMU_3 :						memcpy(str, TEXT_LENGTH_("CMD_SELECT_IMU_3")); break;
		case CMD_REALTIME_DATA_4 :					memcpy(str, TEXT_LENGTH_("CMD_REALTIME_DATA_4")); break;
		case CMD_ENCODERS_CALIB_OFFSET_4 :			memcpy(str, TEXT_LENGTH_("CMD_ENCODERS_CALIB_OFFSET_4")); break;
		case CMD_ENCODERS_CALIB_FLD_OFFSET_4 :		memcpy(str, TEXT_LENGTH_("CMD_ENCODERS_CALIB_FLD_OFFSET_4")); break;
		case CMD_READ_PROFILE_NAMES :				memcpy(str, TEXT_LENGTH_("CMD_READ_PROFILE_NAMES")); break;
		case CMD_WRITE_PROFILE_NAMES :				memcpy(str, TEXT_LENGTH_("CMD_WRITE_PROFILE_NAMES")); break;
		case CMD_QUEUE_PARAMS_INFO_3 :				memcpy(str, TEXT_LENGTH_("CMD_QUEUE_PARAMS_INFO_3")); break;
		case CMD_SET_ADJ_VARS_VAL :					memcpy(str, TEXT_LENGTH_("CMD_SET_ADJ_VARS_VAL")); break;
		case CMD_SAVE_PARAMS_3 :					memcpy(str, TEXT_LENGTH_("CMD_SAVE_PARAMS_3")); break;
		case CMD_READ_PARAMS_EXT :					memcpy(str, TEXT_LENGTH_("CMD_READ_PARAMS_EXT")); break;
		case CMD_WRITE_PARAMS_EXT :					memcpy(str, TEXT_LENGTH_("CMD_WRITE_PARAMS_EXT")); break;
		case CMD_AUTO_PID :							memcpy(str, TEXT_LENGTH_("CMD_AUTO_PID")); break;
		case CMD_SERVO_OUT :						memcpy(str, TEXT_LENGTH_("CMD_SERVO_OUT")); break;
		case CMD_BODE_TEST_START_STOP :				memcpy(str, TEXT_LENGTH_("CMD_BODE_TEST_START_STOP")); break;
		case CMD_I2C_WRITE_REG_BUF :				memcpy(str, TEXT_LENGTH_("CMD_I2C_WRITE_REG_BUF")); break;
		case CMD_I2C_READ_REG_BUF :					memcpy(str, TEXT_LENGTH_("CMD_I2C_READ_REG_BUF")); break;
		case CMD_WRITE_EXTERNAL_DATA :				memcpy(str, TEXT_LENGTH_("CMD_WRITE_EXTERNAL_DATA")); break;
		case CMD_READ_EXTERNAL_DATA :				memcpy(str, TEXT_LENGTH_("CMD_READ_EXTERNAL_DATA")); break;
		case CMD_READ_ADJ_VARS_CFG :				memcpy(str, TEXT_LENGTH_("CMD_READ_ADJ_VARS_CFG")); break;
		case CMD_WRITE_ADJ_VARS_CFG :				memcpy(str, TEXT_LENGTH_("CMD_WRITE_ADJ_VARS_CFG")); break;
		case CMD_API_VIRT_CH_CONTROL :				memcpy(str, TEXT_LENGTH_("CMD_API_VIRT_CH_CONTROL")); break;
		case CMD_ADJ_VARS_STATE :					memcpy(str, TEXT_LENGTH_("CMD_ADJ_VARS_STATE")); break;
		case CMD_EEPROM_WRITE :						memcpy(str, TEXT_LENGTH_("CMD_EEPROM_WRITE")); break;
		case CMD_EEPROM_READ :						memcpy(str, TEXT_LENGTH_("CMD_EEPROM_READ")); break;
		case CMD_CALIB_INFO :						memcpy(str, TEXT_LENGTH_("CMD_CALIB_INFO")); break;
		case CMD_SIGN_MESSAGE :						memcpy(str, TEXT_LENGTH_("CMD_SIGN_MESSAGE")); break;
		case CMD_BOOT_MODE_3 :						memcpy(str, TEXT_LENGTH_("CMD_BOOT_MODE_3")); break;
		case CMD_SYSTEM_STATE :						memcpy(str, TEXT_LENGTH_("CMD_SYSTEM_STATE")); break;
		case CMD_READ_FILE :						memcpy(str, TEXT_LENGTH_("CMD_READ_FILE")); break;
		case CMD_WRITE_FILE :						memcpy(str, TEXT_LENGTH_("CMD_WRITE_FILE")); break;
		case CMD_FS_CLEAR_ALL :						memcpy(str, TEXT_LENGTH_("CMD_FS_CLEAR_ALL")); break;
		case CMD_AHRS_HELPER :						memcpy(str, TEXT_LENGTH_("CMD_AHRS_HELPER")); break;
		case CMD_RUN_SCRIPT :						memcpy(str, TEXT_LENGTH_("CMD_RUN_SCRIPT")); break;
		case CMD_SCRIPT_DEBUG :						memcpy(str, TEXT_LENGTH_("CMD_SCRIPT_DEBUG")); break;
		case CMD_CALIB_MAG :						memcpy(str, TEXT_LENGTH_("CMD_CALIB_MAG")); break;
		case CMD_GET_ANGLES_EXT :					memcpy(str, TEXT_LENGTH_("CMD_GET_ANGLES_EXT")); break;
		case CMD_READ_PARAMS_EXT2 :					memcpy(str, TEXT_LENGTH_("CMD_READ_PARAMS_EXT2")); break;
		case CMD_WRITE_PARAMS_EXT2 :				memcpy(str, TEXT_LENGTH_("CMD_WRITE_PARAMS_EXT2")); break;
		case CMD_GET_ADJ_VARS_VAL :					memcpy(str, TEXT_LENGTH_("CMD_GET_ADJ_VARS_VAL")); break;
		case CMD_CALIB_ACC :						memcpy(str, TEXT_LENGTH_("CMD_CALIB_ACC")); break;
		case CMD_CALIB_BAT :						memcpy(str, TEXT_LENGTH_("CMD_CALIB_BAT")); break;
		case /* CMD_CONFIRM or CMD_CONTROL */ 67 :
			if (serialCommand->parameters &
				SCParam_RX)							memcpy(str, TEXT_LENGTH_("CMD_CONFIRM"));
			else									memcpy(str, TEXT_LENGTH_("CMD_CONTROL"));
			break;
		case CMD_REALTIME_DATA :					memcpy(str, TEXT_LENGTH_("CMD_REALTIME_DATA")); break;
		case CMD_EXECUTE_MENU :						memcpy(str, TEXT_LENGTH_("CMD_EXECUTE_MENU")); break;
		case CMD_USE_DEFAULTS :						memcpy(str, TEXT_LENGTH_("CMD_USE_DEFAULTS")); break;
		case CMD_CALIB_EXT_GAIN :					memcpy(str, TEXT_LENGTH_("CMD_CALIB_EXT_GAIN")); break;
		case CMD_HELPER_DATA :						memcpy(str, TEXT_LENGTH_("CMD_HELPER_DATA")); break;
		case CMD_GET_ANGLES :						memcpy(str, TEXT_LENGTH_("CMD_GET_ANGLES")); break;
		case CMD_CALIB_MOTOR_MAG_LINK :				memcpy(str, TEXT_LENGTH_("CMD_CALIB_MOTOR_MAG_LINK")); break;
		case CMD_GYRO_CORRECTION :					memcpy(str, TEXT_LENGTH_("CMD_GYRO_CORRECTION")); break;
		case CMD_MODULE_LIST :						memcpy(str, TEXT_LENGTH_("CMD_MODULE_LIST")); break;
		case CMD_MOTORS_ON :						memcpy(str, TEXT_LENGTH_("CMD_MOTORS_ON")); break;
		case CMD_CALIB_OFFSET :						memcpy(str, TEXT_LENGTH_("CMD_CALIB_OFFSET")); break;
		case CMD_CALIB_POLES :						memcpy(str, TEXT_LENGTH_("CMD_CALIB_POLES")); break;
		case CMD_READ_PARAMS :						memcpy(str, TEXT_LENGTH_("CMD_READ_PARAMS")); break;
		case CMD_TRIGGER_PIN :						memcpy(str, TEXT_LENGTH_("CMD_TRIGGER_PIN")); break;
		case CMD_DATA_STREAM_INTERVAL :				memcpy(str, TEXT_LENGTH_("CMD_DATA_STREAM_INTERVAL")); break;
		case CMD_BOARD_INFO :						memcpy(str, TEXT_LENGTH_("CMD_BOARD_INFO")); break;
		case CMD_WRITE_PARAMS :						memcpy(str, TEXT_LENGTH_("CMD_WRITE_PARAMS")); break;
		case CMD_REALTIME_DATA_CUSTOM :				memcpy(str, TEXT_LENGTH_("CMD_REALTIME_DATA_CUSTOM")); break;
		case CMD_BEEP_SOUND :						memcpy(str, TEXT_LENGTH_("CMD_BEEP_SOUND")); break;
		case CMD_CONTROL_CONFIG :					memcpy(str, TEXT_LENGTH_("CMD_CONTROL_CONFIG")); break;
		case CMD_CALIB_ORIENT_CORR :				memcpy(str, TEXT_LENGTH_("CMD_CALIB_ORIENT_CORR")); break;
		case CMD_COGGING_CALIB_INFO :				memcpy(str, TEXT_LENGTH_("CMD_COGGING_CALIB_INFO")); break;
		case CMD_CALIB_COGGING :					memcpy(str, TEXT_LENGTH_("CMD_CALIB_COGGING")); break;
		case CMD_CALIB_ACC_EXT_REF :				memcpy(str, TEXT_LENGTH_("CMD_CALIB_ACC_EXT_REF")); break;
		case CMD_PROFILE_SET :						memcpy(str, TEXT_LENGTH_("CMD_PROFILE_SET")); break;
		case CMD_CAN_DEVICE_SCAN :					memcpy(str, TEXT_LENGTH_("CMD_CAN_DEVICE_SCAN")); break;
		case CMD_CAN_DRV_HARD_PARAMS :				memcpy(str, TEXT_LENGTH_("CMD_CAN_DRV_HARD_PARAMS")); break;
		case CMD_CAN_DRV_STATE :					memcpy(str, TEXT_LENGTH_("CMD_CAN_DRV_STATE")); break;
		case CMD_CAN_DRV_CALIBRATE :				memcpy(str, TEXT_LENGTH_("CMD_CAN_DRV_CALIBRATE")); break;
		case CMD_READ_RC_INPUTS :					memcpy(str, TEXT_LENGTH_("CMD_READ_RC_INPUTS")); break;
		case CMD_REALTIME_DATA_CAN_DRV :			memcpy(str, TEXT_LENGTH_("CMD_REALTIME_DATA_CAN_DRV")); break;
		case CMD_EVENT :							memcpy(str, TEXT_LENGTH_("CMD_EVENT")); break;
		case CMD_CALIB_GYRO :						memcpy(str, TEXT_LENGTH_("CMD_CALIB_GYRO")); break;
		case CMD_READ_PARAMS_EXT3 :					memcpy(str, TEXT_LENGTH_("CMD_READ_PARAMS_EXT3")); break;
		case CMD_WRITE_PARAMS_EXT3 :				memcpy(str, TEXT_LENGTH_("CMD_WRITE_PARAMS_EXT3")); break;
		case CMD_EXT_IMU_DEBUG_INFO :				memcpy(str, TEXT_LENGTH_("CMD_EXT_IMU_DEBUG_INFO")); break;
		case CMD_SET_DEVICE_ADDR :					memcpy(str, TEXT_LENGTH_("CMD_SET_DEVICE_ADDR")); break;
		case CMD_AUTO_PID2 :						memcpy(str, TEXT_LENGTH_("CMD_AUTO_PID2")); break;
		case CMD_MOTORS_OFF :						memcpy(str, TEXT_LENGTH_("CMD_MOTORS_OFF")); break;
		case CMD_EXT_IMU_CMD :						memcpy(str, TEXT_LENGTH_("CMD_EXT_IMU_CMD")); break;
		case CMD_READ_STATE_VARS :					memcpy(str, TEXT_LENGTH_("CMD_READ_STATE_VARS")); break;
		case CMD_WRITE_STATE_VARS :					memcpy(str, TEXT_LENGTH_("CMD_WRITE_STATE_VARS")); break;
		case CMD_SERIAL_PROXY :						memcpy(str, TEXT_LENGTH_("CMD_SERIAL_PROXY")); break;
		case CMD_RESET :							memcpy(str, TEXT_LENGTH_("CMD_RESET")); break;
		case CMD_IMU_ADVANCED_CALIB :				memcpy(str, TEXT_LENGTH_("CMD_IMU_ADVANCED_CALIB")); break;
		case CMD_API_VIRT_CH_HIGH_RES :				memcpy(str, TEXT_LENGTH_("CMD_API_VIRT_CH_HIGH_RES")); break;
		case CMD_CALIB_ENCODER_LUT :				memcpy(str, TEXT_LENGTH_("CMD_CALIB_ENCODER_LUT")); break;
		case CMD_CALIB_ENCODER_LUT_RES :			memcpy(str, TEXT_LENGTH_("CMD_CALIB_ENCODER_LUT_RES")); break;
		case CMD_WRITE_PARAMS_SET :					memcpy(str, TEXT_LENGTH_("CMD_WRITE_PARAMS_SET")); break;
		case CMD_CALIB_CUR_SENS :					memcpy(str, TEXT_LENGTH_("CMD_CALIB_CUR_SENS")); break;
		case CMD_CONTROL_EXT :						memcpy(str, TEXT_LENGTH_("CMD_CONTROL_EXT")); break;
		case CMD_SYNC_MOTORS :						memcpy(str, TEXT_LENGTH_("CMD_SYNC_MOTORS")); break;
		case CMD_CAN_DRV_TELEMETRY :				memcpy(str, TEXT_LENGTH_("CMD_CAN_DRV_TELEMETRY")); break;
		case CMD_EXT_MOTORS_ACTION :				memcpy(str, TEXT_LENGTH_("CMD_EXT_MOTORS_ACTION")); break;
		case CMD_EXT_MOTORS_CONTROL :				memcpy(str, TEXT_LENGTH_("CMD_EXT_MOTORS_CONTROL")); break;
		case CMD_EXT_MOTORS_CONTROL_CONFIG :		memcpy(str, TEXT_LENGTH_("CMD_EXT_MOTORS_CONTROL_CONFIG")); break;
		case CMD_EXT_MOTORS_STATE :					memcpy(str, TEXT_LENGTH_("CMD_EXT_MOTORS_STATE")); break;
		case CMD_ADJ_VARS_INFO :					memcpy(str, TEXT_LENGTH_("CMD_ADJ_VARS_INFO")); break;
		case CMD_SERVO_OUT_EXT :					memcpy(str, TEXT_LENGTH_("CMD_SERVO_OUT_EXT")); break;
		case CMD_SET_ADJ_VARS_VAL_F :				memcpy(str, TEXT_LENGTH_("CMD_SET_ADJ_VARS_VAL_F")); break;
		case CMD_GET_ADJ_VARS_VAL_F :				memcpy(str, TEXT_LENGTH_("CMD_GET_ADJ_VARS_VAL_F")); break;
		case CMD_CONTROL_QUAT :						memcpy(str, TEXT_LENGTH_("CMD_CONTROL_QUAT")); break;
		case CMD_CONTROL_QUAT_STATUS :				memcpy(str, TEXT_LENGTH_("CMD_CONTROL_QUAT_STATUS")); break;
		case CMD_CONTROL_QUAT_CONFIG :				memcpy(str, TEXT_LENGTH_("CMD_CONTROL_QUAT_CONFIG")); break;
		case CMD_EXT_SENS_CMD :						memcpy(str, TEXT_LENGTH_("CMD_EXT_SENS_CMD")); break;
		case CMD_TRANSPARENT_SAPI :					memcpy(str, TEXT_LENGTH_("CMD_TRANSPARENT_SAPI")); break;
		case CMD_SET_DEBUG_PORT :					memcpy(str, TEXT_LENGTH_("CMD_SET_DEBUG_PORT")); break;
		case CMD_MAVLINK_INFO :						memcpy(str, TEXT_LENGTH_("CMD_MAVLINK_INFO")); break;
		case CMD_MAVLINK_DEBUG :					memcpy(str, TEXT_LENGTH_("CMD_MAVLINK_DEBUG")); break;
		case CMD_DEBUG_VARS_INFO_3 :				memcpy(str, TEXT_LENGTH_("CMD_DEBUG_VARS_INFO_3")); break;
		case CMD_DEBUG_VARS_3 :						memcpy(str, TEXT_LENGTH_("CMD_DEBUG_VARS_3")); break;
		case CMD_ERROR :							memcpy(str, TEXT_LENGTH_("CMD_ERROR")); break;
	}

	return strlen(str);
}


/**	@brief	Converts the serial command status to string
 *
 *	@param	*serialCommand - pointer to serial command
 *	@param	*str - writable buffer
 *	@param	size - buffer size
 *
 *	@return	Length of a writable string
 */
ui8 ParserSBGC32_ConvertCommandStatusToString (serialAPI_Command_t *serialCommand, char *str, ui8 size)
{
	if (size < SBGC_CMD_STATUS_NAME_MAX_LEN) return 0;

	switch (serialCommand->_state)
	{
		case SCState_FORMING :						memcpy(str, TEXT_LENGTH_("FORMING")); break;
		case SCState_ABORTED :						memcpy(str, TEXT_LENGTH_("ABORTED")); break;
		case SCState_PREPARED :						memcpy(str, TEXT_LENGTH_("PREPARED")); break;
		case SCState_PROCESSING :					memcpy(str, TEXT_LENGTH_("PROCESSING")); break;
		case SCState_RELOAD :						memcpy(str, TEXT_LENGTH_("RELOAD")); break;
		case SCState_ERROR :						memcpy(str, TEXT_LENGTH_("ERROR")); break;
		case SCState_PROCESSED :					memcpy(str, TEXT_LENGTH_("PROCESSED")); break;
	}

	return strlen(str);
}


#if (SBGC_DETAILED_CONFIRM)

	/**	@brief	Converts the error code to string
	 *
	 *	@param	*confirm - pointer to confirm structure
	 *	@param	*str - writable buffer
	 *	@param	size - buffer size
	 *
	 *	@return	Length of a writable string
	 */
	ui8 ParserSBGC32_ConvertErrorCodeToString (sbgcConfirm_t *confirm, char *str, ui8 size)
	{
		if (size < SBGC_ERROR_CODE_NAME_MAX_LEN) return 0;

		switch (confirm->errorCode)
		{
			case sbgcERR_CMD_SIZE :					memcpy(str, TEXT_LENGTH_("ERR_CMD_SIZE")); break;
			case sbgcERR_WRONG_PARAMS :				memcpy(str, TEXT_LENGTH_("ERR_WRONG_PARAMS")); break;
			case sbgcERR_CRYPTO :					memcpy(str, TEXT_LENGTH_("ERR_CRYPTO")); break;
			case sbgcERR_UNKNOWN_COMMAND :			memcpy(str, TEXT_LENGTH_("ERR_UNKNOWN_COMMAND")); break;
			case sbgcERR_WRONG_STATE :				memcpy(str, TEXT_LENGTH_("ERR_WRONG_STATE")); break;
			case sbgcERR_NOT_SUPPORTED :			memcpy(str, TEXT_LENGTH_("ERR_NOT_SUPPORTED")); break;
			case sbgcERR_OPERATION_FAILED :			memcpy(str, TEXT_LENGTH_("ERR_OPERATION_FAILED")); break;
			case sbgcERR_TEMPORARY :				memcpy(str, TEXT_LENGTH_("ERR_TEMPORARY")); break;

			default :								return 0;
		}

		return strlen(str);
	}

#endif


/**	@brief	Transforms SBGC32 device type to string
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	boardVer - sbgcBoardInfo_t.boardVer
 *	@param	*pBuff - buffer to write
 *	@param	size - buffer size
 */
void ParserSBGC32_FormatDeviceType (sbgcGeneral_t *gSBGC, ui8 boardVer, char *pBuff, ui8 size)
{
	if ((!pBuff) || (size < SBGC_DEVICE_TYPE_MAX_LEN)) return;

	switch (boardVer)
	{
		case 25 :	gSBGC->_ll->debugSprintf(pBuff, "Tiny rev. C GD32");	break;
		case 27 :	gSBGC->_ll->debugSprintf(pBuff, "Extended Long GD32");	break;
		case 30 :	gSBGC->_ll->debugSprintf(pBuff, "Regular");				break;
		case 31 :	gSBGC->_ll->debugSprintf(pBuff, "Tiny");				break;
		case 34 :	gSBGC->_ll->debugSprintf(pBuff, "OEM");					break;
		case 36 :	gSBGC->_ll->debugSprintf(pBuff, "Extended");			break;
		case 41 :	gSBGC->_ll->debugSprintf(pBuff, "Pro");					break;
		case 50 :	gSBGC->_ll->debugSprintf(pBuff, "CAN MCU");				break;

		default:	break;
	}
}


/**	@brief	Transforms the board version variable to string
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	boardVer - sbgcBoardInfo_t.boardVer
 *	@param	*pBuff - buffer to write
 *	@param	size - buffer size
 */
void ParserSBGC32_FormatBoardVersion (sbgcGeneral_t *gSBGC, ui8 boardVer, char *pBuff, ui8 size)
{
	if ((!pBuff) || (size < SBGC_BOARD_VERSION_MAX_LEN)) return;

	ui8 majorVer = boardVer / 10;
	ui8 minorVer = boardVer % 10;

	gSBGC->_ll->debugSprintf(pBuff, "%u.%u", majorVer, minorVer);
}


/**	@brief	Transforms the firmware version variable to string
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	firmwareVer - sbgcBoardInfo_t.firmwareVer
 *	@param	*pBuff - buffer to write
 *	@param	size - buffer size
 */
void ParserSBGC32_FormatFirmwareVersion (sbgcGeneral_t *gSBGC, ui16 firmwareVer, char *pBuff, ui8 size)
{
	if ((!pBuff) || (size < SBGC_FIRMWARE_VERSION_MAX_LEN)) return;

	ui8 majorVer = firmwareVer / 1000;
	ui8 minorVer = (firmwareVer % 1000) / 10;
	ui8 betaVer = firmwareVer % 10;

	if (betaVer && (firmwareVer < 2730))
		gSBGC->_ll->debugSprintf(pBuff, "%u.%ub%u", majorVer, minorVer, betaVer);

	else if (betaVer && (firmwareVer >= 2730))
		gSBGC->_ll->debugSprintf(pBuff, "%u.%u.%u", majorVer, minorVer, betaVer);

	else
		gSBGC->_ll->debugSprintf(pBuff, "%u.%u", majorVer, minorVer);
}


/**	@brief	Writes variable at the address to the buffer considering
 *			the organization of the system's memory
 *
 *	@note	Private function
 *
 *	@param	*value - writable variable address
 *	@param	*payload - place of data writing
 *	@param	size - variable size
 */
static void ParserSBGC32_ToLittleEndian (const void *value, ui8 *payload, ui8 size)
{
	if (size > 4) return;
	if (size == 3) size = 4;

	memcpy(payload, value, size);

	#if (SBGC_SYS_BIG_ENDIAN)

		for (ui8 i = 0; i < size / 2; i++)
			ParserSBGC32_SwapMemoryContent((ui8*)payload + i, (ui8*)payload + size - 1 - i);

	#endif
}


/**	@brief	Reads a buffer into the address of variable considering
 *			the organization of the system's memory
 *
 *	@note	Private function
 *
 *	@param	*value - variable write address
 *	@param	*payload - place of data reading
 *	@param	size - variable size
 */
static void ParserSBGC32_FromLittleEndian (void *value, ui8 *payload, ui8 size)
{
	if (size > 4) return;
	if (size == 3) size = 4;

	memcpy(value, payload, size);

	#if (SBGC_SYS_BIG_ENDIAN)

		for (ui8 i = 0; i < size / 2; i++)
			ParserSBGC32_SwapMemoryContent((ui8*)value + i, (ui8*)value + size - 1 - i);

	#endif
}


/**	@brief	Extracts parser map from serial command
 *
 *	@note	Private function
 *
 *	@param	*serialCommand - pointer to command
 *
 *	@return	Parser mapping pattern
 */
static sbgcParserMap_t ParserSBGC32_GetCommandParserMap (serialAPI_Command_t *serialCommand)
{
	#if (SBGC_SYS_BIG_ENDIAN == sbgcOFF)

		unused_(serialCommand);

		return PM_DEFAULT_8BIT;

	#else

		switch (serialCommand->_commandID)
		{
			case CMD_WRITE_ADJ_VARS_CFG : case CMD_READ_ADJ_VARS_CFG :				return PM_AV_CONFIG;
			case CMD_ADJ_VARS_STATE : if (serialCommand->parameters & SCParam_RX)	return PM_AV_STATE_RX;
									  else											return PM_AV_STATE_TX;
			case CMD_CALIB_ACC : case CMD_CALIB_GYRO : case CMD_CALIB_MAG :			return PM_IMU_EXT_CALIB;
			case CMD_CALIB_INFO :													return PM_CALIB_INFO;
			case CMD_CALIB_COGGING :												return PM_CALIB_COGGING;
			case CMD_CONTROL :														return PM_CONTROL;

			case CMD_CONTROL_EXT :													return PM_CONTROL_EXT;
			case CMD_CONTROL_QUAT :													return PM_CONTROL_QUAT;
			case CMD_CONTROL_CONFIG :												return PM_CONTROL_CONFIG;
			case CMD_CONTROL_QUAT_CONFIG :											return PM_CONTROL_QUAT_CONFIG;
			case CMD_EXT_MOTORS_CONTROL_CONFIG :									return PM_EXT_MOTORS_CONTROL_CONFIG;
			case CMD_EXT_IMU_DEBUG_INFO :											return PM_EXT_IMU_DEBUG_INFO;
			case CMD_GYRO_CORRECTION :												return PM_GYRO_CORRECTION;
			case CMD_AHRS_HELPER :													return PM_AHRS_HELPER;
			case CMD_HELPER_DATA :													return PM_HELPER_DATA_EXT;
			case CMD_WRITE_PARAMS_3 : case CMD_READ_PARAMS_3 :						return PM_MAIN_PARAMS_3;
			case CMD_WRITE_PARAMS_EXT : case CMD_READ_PARAMS_EXT :					return PM_MAIN_PARAMS_EXT;
			case CMD_WRITE_PARAMS_EXT2 : case CMD_READ_PARAMS_EXT2 :				return PM_MAIN_PARAMS_EXT2;
			case CMD_WRITE_PARAMS_EXT3 : case CMD_READ_PARAMS_EXT3 :				return PM_MAIN_PARAMS_EXT3;
			case CMD_DATA_STREAM_INTERVAL :											return PM_DATA_STREAM_INTERVAL;
			case CMD_REALTIME_DATA_3 :												return PM_REALTIME_DATA_3;
			case CMD_REALTIME_DATA_4 :												return PM_REALTIME_DATA_4;
			case CMD_GET_ANGLES :													return PM_GET_ANGLES;
			case CMD_GET_ANGLES_EXT :												return PM_GET_ANGLES_EXT;
			case CMD_BOARD_INFO :													return PM_BOARD_INFO;
			case CMD_BOARD_INFO_3 :													return PM_BOARD_INFO_3;
			case CMD_AUTO_PID : if (serialCommand->parameters & SCParam_RX)			return PM_AUTO_PID_STATE;
								else												return PM_AUTO_PID;
			case CMD_AUTO_PID2 :													return PM_AUTO_PID_2;
			case CMD_SYNC_MOTORS :													return PM_SYNC_MOTORS;
			case CMD_SCRIPT_DEBUG :													return PM_SCRIPT_DEBUG_INFO;
			case CMD_WRITE_STATE_VARS : case CMD_READ_STATE_VARS :					return PM_STATE_VARS;
			case CMD_CAN_DEVICE_SCAN :												return PM_CAN_DEVICE_SCAN;

			default :																return PM_DEFAULT_8BIT;
		}

	#endif
}


/**	@brief	Common data-endian converting function
 *
 *	@note	Private function
 *
 *	@param	*pDestination - where data will be written
 *	@param	*pSource - data origin
 *	@param	size - data size
 *	@param	parserMap - data type required for correct parsing
 *
 *	@return	Size of written data
 */
static ui8 ParserSBGC32_ConvertWithPM (void *pDestination, const void *pSource, ui8 size, sbgcParserMap_t parserMap)
{
	#if (SBGC_NEED_ASSERTS)
		if ((pDestination == NULL) || (size == 0)) return 0;
	#endif

	memcpy(pDestination, pSource, size);

	#if (SBGC_SYS_BIG_ENDIAN)
		ParserSBGC32_SwapBytesInStruct((ui8*)pDestination, size, parserMap);
	#else
		unused_(parserMap);
	#endif

	return size;
}


/**	@brief	Links parser functions to internal
 *			software system of the library
 *
 *	@note	Quasi-private function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
void PrivateSerialAPI_LinkConverter (sbgcGeneral_t *gSBGC)
{
	gSBGC->_api->typeToSize	= ParserSBGC32_ConvertTypeToSize;

	#if (SBGC_USES_REF_INFO)
		gSBGC->_api->assignByPM	= ParserSBGC32_AssignStructByParserMap;
	#endif

	gSBGC->_api->toLE		= ParserSBGC32_ToLittleEndian;
	gSBGC->_api->fromLE		= ParserSBGC32_FromLittleEndian;
	gSBGC->_api->getCmdPM	= ParserSBGC32_GetCommandParserMap;
	gSBGC->_api->convWithPM	= ParserSBGC32_ConvertWithPM;
}
/**	@}
 */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
