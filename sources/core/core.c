/** ____________________________________________________________________
 *
 *	@file		core.c
 *
 *	@brief 		Core source file
 *  ____________________________________________________________________
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

#include "core.h"


#ifdef	SYS_BIG_ENDIAN

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *								Parser Big Endian Mapping Structures
	 */
	/* Other external parser structures */
	extern const ParserBlock_t Control_ParserStructDB [];
	extern const ui8 Control_ParserStructDB_Size;

	extern const ParserBlock_t ControlConfig_ParserStructDB [];
	extern const ui8 ControlConfig_ParserStructDB_Size;

	extern const ParserBlock_t MainParams3_ParserStructDB [];
	extern const ui8 MainParams3_ParserStructDB_Size;

	extern const ParserBlock_t MainParamsExt_ParserStructDB [];
	extern const ui8 MainParamsExt_ParserStructDB_Size;

	extern const ParserBlock_t MainParamsExt2_ParserStructDB [];
	extern const ui8 MainParamsExt2_ParserStructDB_Size;

	extern const ParserBlock_t MainParamsExt3_ParserStructDB [];
	extern const ui8 MainParamsExt3_ParserStructDB_Size;

	extern const ParserBlock_t DataStreamInterval_ParserStructDB [];
	extern const ui8 DataStreamInterval_ParserStructDB_Size;

	extern const ParserBlock_t RealTimeData3_ParserStructDB [];
	extern const ui8 RealTimeData3_ParserStructDB_Size;

	extern const ParserBlock_t RealTimeData4_ParserStructDB [];
	extern const ui8 RealTimeData4_ParserStructDB_Size;

	extern const ParserBlock_t GetAngles_ParserStructDB [];
	extern const ui8 GetAngles_ParserStructDB_Size;

	extern const ParserBlock_t GetAnglesExt_ParserStructDB [];
	extern const ui8 GetAnglesExt_ParserStructDB_Size;

	extern const ParserBlock_t AdjVarsStateOldTx_ParserStructDB [];
	extern const ui8 AdjVarsStateOldTx_ParserStructDB_Size;

	extern const ParserBlock_t AdjVarsStateOldRx_ParserStructDB [];
	extern const ui8 AdjVarsStateOldRx_ParserStructDB_Size;

	extern const ParserBlock_t AdjVarsStateTx_ParserStructDB [];
	extern const ui8 AdjVarsStateTx_ParserStructDB_Size;

	extern const ParserBlock_t AdjVarsStateRx_ParserStructDB [];
	extern const ui8 AdjVarsStateRx_ParserStructDB_Size;

	extern const ParserBlock_t ExtIMU_DebugInfo_ParserStructDB [];
	extern const ui8 ExtIMU_DebugInfo_ParserStructDB_Size;

	extern const ParserBlock_t GyroCorrection_ParserStructDB [];
	extern const ui8 GyroCorrection_ParserStructDB_Size;

	extern const ParserBlock_t AHRS_Helper_ParserStructDB [];
	extern const ui8 AHRS_Helper_ParserStructDB_Size;

	extern const ParserBlock_t HelperData_ParserStructDB [];
	extern const ui8 HelperData_ParserStructDB_Size;

	extern const ParserBlock_t HelperDataExt_ParserStructDB [];
	extern const ui8 HelperDataExt_ParserStructDB_Size;

	extern const ParserBlock_t CalibInfo_ParserStructDB [];
	extern const ui8 CalibInfo_ParserStructDB_Size;

	extern const ParserBlock_t BoardInfo_ParserStructDB [];
	extern const ui8 BoardInfo_ParserStructDB_Size;

	extern const ParserBlock_t BoardInfo3_ParserStructDB [];
	extern const ui8 BoardInfo3_ParserStructDB_Size;

	extern const ParserBlock_t AutoPID_ParserStructDB [];
	extern const ui8 AutoPID_ParserStructDB_Size;

	extern const ParserBlock_t AutoPID_2_ParserStructDB [];
	extern const ui8 AutoPID_2_ParserStructDB_Size;

	extern const ParserBlock_t AutoPID_State_ParserStructDB [];
	extern const ui8 AutoPID_State_ParserStructDB_Size;

	extern const ParserBlock_t StateVars_ParserStructDB [];
	extern const ui8 StateVars_ParserStructDB_Size;


	/**	@addtogroup	Other_External
	 * 	@{
	 */
	/** @brief	Sample for Big Endian Mapping
	 *
	 * 	@ref	AHRS_DebugInfo_ParserStructDB
	 */
	const AHRS_DebugInfo_t AHRS_DebugInfo_ParserStruct;

	const ParserBlock_t AHRS_DebugInfo_ParserStructDB [] =
	{
		VAR_BLOCK(AHRS_DebugInfo_ParserStruct.mainIMU_RefSrc),
		VAR_BLOCK(AHRS_DebugInfo_ParserStruct.frameIMU_RefSrc),
		VAR_BLOCK(AHRS_DebugInfo_ParserStruct.mainIMU_Z_RefErr),
		VAR_BLOCK(AHRS_DebugInfo_ParserStruct.mainIMU_H_RefErr),
		VAR_BLOCK(AHRS_DebugInfo_ParserStruct.frameIMU_Z_RefErr),
		VAR_BLOCK(AHRS_DebugInfo_ParserStruct.frameIMU_H_RefErr),
		VAR_BLOCK(AHRS_DebugInfo_ParserStruct.extIMU_Status),
		VAR_BLOCK(AHRS_DebugInfo_ParserStruct.extIMU_PacketsReceivedCnt),
		VAR_BLOCK(AHRS_DebugInfo_ParserStruct.extIMU_ParseErrCnt),
		VAR_BLOCK(AHRS_DebugInfo_ParserStruct.extCorrH_Ref),
		VAR_BLOCK(AHRS_DebugInfo_ParserStruct.extCorrZ_Ref),
		DATA_BLOCK(AHRS_DebugInfo_ParserStruct.reserved),
	};

	const ui8 AHRS_DebugInfo_ParserStructDB_Size = countof(AHRS_DebugInfo_ParserStructDB);


	/** @brief	Sample for Big Endian Mapping
	 *
	 * 	@ref	Motor4_Control_ParserStructDB
	 */
	const Motor4_Control_t motor4_Control_ParserStruct;

	const ParserBlock_t Motor4_Control_ParserStructDB [] =
	{
		VAR_BLOCK(motor4_Control_ParserStruct.FF_Speed),
		VAR_BLOCK(motor4_Control_ParserStruct.angleError),
		VAR_BLOCK(motor4_Control_ParserStruct.PID_Out),
	};

	const ui8 Motor4_Control_ParserStructDB_Size = countof(Motor4_Control_ParserStructDB);
	/**	@}
	 */

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *											Main Communication Functions
 */
/**	@addtogroup	Communication
 *	@{
 */
/**	@brief	Forms a SerialCommand from the buffer
 *  		and sends it to the SBGC device
 *
 *  @param	*generalSBGC - pointer that takes the address
 *  		of the main structure of the target device
 *  @param	*serialCommand - pointer to a structure ready
 *  		to be transmitted
 *
 *  @return	Transmission status
 */
TxRxStatus_t SBGC32_TX (GeneralSBGC_t *generalSBGC, SerialCommand_t *serialCommand)
{
	ui8 buff [MAX_BUFF_SIZE];
	ui32 currentTime;

    buff[0] = generalSBGC->protocolVersion;
    buff[1] = serialCommand->commandID;
    buff[2] = serialCommand->payloadSize;
    buff[3] = buff[1] + buff[2];

    memcpy(&buff[4], serialCommand->payload, serialCommand->payloadSize);

    /* ui8 size = real size current serialCommand */
    ui8 size = serialCommand->payloadSize + 4 + (generalSBGC->protocolVersion == PR2_START_CHARACTER ? 2 : 1);

    if (generalSBGC->protocolVersion == PR1_START_CHARACTER)
    	buff[4 + serialCommand->payloadSize] = Modulo256_Calculate(serialCommand->payload, serialCommand->payloadSize);

    else
    {
    	ui16 CRC16_Res = CRC16_Calculate(&buff[1], (4 + serialCommand->payloadSize - 1));
    	buff[4 + serialCommand->payloadSize] = CRC16_Res & 0x00FF;
    	buff[5 + serialCommand->payloadSize] = (CRC16_Res >> 8) & 0x00FF;
    }

    currentTime = generalSBGC->GetTimeFunc(generalSBGC->Drv);
    while (generalSBGC->TxFunc(generalSBGC->Drv, buff, size))
    {
    	if (generalSBGC->GetTimeFunc(generalSBGC->Drv) - currentTime >= generalSBGC->txTimeout)
    	{
    		generalSBGC->_txErrorsCount++;
    		return TX_BUFFER_OVERFLOW_ERROR;  // aka timeout error
    	}
    }

	return TX_RX_OK;
}


/**	@brief	Receives an incoming command
 *
 *  @param	*generalSBGC - pointer that takes the address
 *  		of the main structure of the target device
 *  @param	*serialCommand - Pointer to a structure to which the
 *  		incoming serialCommand will be written
 *  @param	timeout - the value of the maximum possible waiting
 *   		time for receiving one whole SerialCommand
 *
 *  @return	TX_RX_OK or last state of lastParserError variable
 */
TxRxStatus_t SBGC32_RX (GeneralSBGC_t *generalSBGC, SerialCommand_t *serialCommand, ui32 timeout)
{
	ui8 startSim;
	ui8 headBuff [3];  /* Header buffer:
	headBuff[0] is command ID || headBuff[1] is payload size || headBuff[2] is header checksum */
	ui16 availableBytes;

	TxRxStatus_t lastParserError = RX_START_PARSE;

	ParserStates_t parserState = STATE_IDLE;

	/* Launching timer */
	ui32 currentTime = generalSBGC->GetTimeFunc(generalSBGC->Drv);

	serialCommand->readPos = 0;  // Prepare for reading

	while (1)
	{
		switch (parserState)
		{
			/* Waiting start byte */
			case STATE_IDLE :
			case STATE_RESYNC :
			{
				startSim = 0;

				if (generalSBGC->RxFunc(generalSBGC->Drv, &startSim) &&
					lastParserError == RX_START_PARSE)
					lastParserError = RX_EMPTY_BUFF_ERROR;

				else if (startSim == generalSBGC->protocolVersion)
					parserState = STATE_CHECK_HEADER;

				break;  // Passing to next state
			}

			/* Waiting whole header */
			case STATE_CHECK_HEADER :
			{
				availableBytes = generalSBGC->AvailableBytesFunc(generalSBGC->Drv);

				if ((availableBytes >= 3) && (availableBytes != RX_BUFFER_OVERFLOW_FLAG))
					FOR_(i, 3) generalSBGC->RxFunc(generalSBGC->Drv, &headBuff[i]);

				else
				{
					lastParserError = RX_BUFFER_REALTIME_ERROR;
					break;
				}

				if ((headBuff[0] + headBuff[1]) % 256 != headBuff[2])  // % 256 necessary needed here
				{
					lastParserError = RX_HEADER_CHECKSUM_ERROR;
					parserState = STATE_RESYNC;
					break;
				}

				parserState = STATE_CHECK_PAYLOAD;
				break;  // Passing to next state
			}

			/* Waiting whole payload and checksum */
			case STATE_CHECK_PAYLOAD :
			{
				ui8 checksumSize = (generalSBGC->protocolVersion == PR2_START_CHARACTER ? 2 : 1);
				ui8 complexBuff [3 + headBuff[1] + checksumSize];  // (Header + payload + checksum) buffer

				availableBytes = generalSBGC->AvailableBytesFunc(generalSBGC->Drv);

				if ((availableBytes >= headBuff[1] + checksumSize) && (availableBytes != RX_BUFFER_OVERFLOW_FLAG))
					FOR_(i, headBuff[1] + checksumSize) generalSBGC->RxFunc(generalSBGC->Drv, &complexBuff[i + 3]);  // Offset from header space

				else
				{
					lastParserError = RX_BUFFER_REALTIME_ERROR;
					break;
				}

				/* Checksum checking */
				if (!(checksumSize - 1))  // If SBGC_PROTOCOL_V1
				{
					if (complexBuff[3 + headBuff[1]] != Modulo256_Calculate(&complexBuff[3], headBuff[1]))
					{
						lastParserError = RX_PAYLOAD_CHECKSUM_ERROR;
						parserState = STATE_RESYNC;
						break;
					}
				}

				else
				{
					memcpy(complexBuff, headBuff, 3);
					ui16 CRC_Res = CRC16_Calculate(complexBuff, headBuff[1] + 3);

					if (((CRC_Res & 0x00FF) != complexBuff[3 + headBuff[1]]) &&
					   (((CRC_Res >> 8) & 0x00FF) != complexBuff[3 + headBuff[1] + 1]))
					{
						lastParserError = RX_PAYLOAD_CHECKSUM_ERROR;
						parserState = STATE_RESYNC;
						break;
					}
				}

				/* Data passed all checks. Filling the serialCommand struct */
				serialCommand->commandID = (SBGC_Commands_t)headBuff[0];
				memcpy(serialCommand->payload, &complexBuff[3], headBuff[1]);
				serialCommand->payloadSize = headBuff[1];

				return TX_RX_OK;  // Incoming command was received fine
			}
		}

		if (generalSBGC->GetTimeFunc(generalSBGC->Drv) - currentTime >= timeout)
			return lastParserError;
	}
}


/**	@brief	Performs serial transmission and reception of a SerialCommand
 *
 *  @param	*generalSBGC - pointer that takes the address
 *  		of the main structure of the target device
 *  @param	*serialCommand - pointer to the formed structure, into which
 *  		the requested SerialCommand will be overwritten
 *  @param	cmdID - SBGC32 command identifier
 *
 *  @return	Request response result
 */
TxRxStatus_t SBGC32_TX_RX (GeneralSBGC_t *generalSBGC, SerialCommand_t *serialCommand, SBGC_Commands_t cmdID)
{
	if (SBGC32_TX(generalSBGC, serialCommand))
		return TX_BUFFER_OVERFLOW_ERROR;

	else
	{
		ui32 currentTime = generalSBGC->GetTimeFunc(generalSBGC->Drv);

		while (1)
		{
			TxRxStatus_t lastParserStatus = SBGC32_RX(generalSBGC, serialCommand, generalSBGC->rxTimeout);

			if (lastParserStatus == TX_RX_OK &&
			   (serialCommand->commandID == cmdID || cmdID == 0))
				return lastParserStatus;

			else if (lastParserStatus == TX_RX_OK &&
					(serialCommand->commandID != cmdID))
				generalSBGC->_missedCommandCount++;

			if (generalSBGC->GetTimeFunc(generalSBGC->Drv) - currentTime >= generalSBGC->txrxTimeout)
				return lastParserStatus;  // or return RX_TIMEOUT_ERROR;
		}
	}
}
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *											 Parser and Memory Functions
 */
/**	@addtogroup	Parser_Memory
 *	@{
 */
/**	@brief	Common data-endian convertation function
 *
 *	@param	*pDestination - where data will be written
 *	@param	*pSample - write data
 *	@param	size - data size
 *	@param	parserMap - data type required for correct parsing
 *
 *	@return	size of written data
 */
ui8 ConvertWithPM (void *pDestination, const void *pSample, ui8 size, ParserMap_t parserMap)
{
	if (size == 0)
		return 0;

	memcpy(pDestination, pSample, size);
	SwapBytesInStruct((ui8*)pDestination, size, parserMap);
	return size;
}


/**	@brief	Writes a data buffer to a SerialCommand's payload buffer
 *
 * 	@param	*cmd - writable SerialCommand
 * 	@param	*buff - write data
 * 	@param	size - write data size
 * 	@param	parserMap - data type required for correct parsing
 */
void WriteBuff (SerialCommand_t *cmd, const void *buff, ui8 size, ParserMap_t parserMap)
{
	if (cmd->payloadSize > MAX_BUFF_SIZE - size)
		return;  // data will not fit
	
	cmd->payloadSize += ConvertWithPM(&cmd->payload[cmd->payloadSize], buff, size, parserMap);
}


/**	@brief	Reads a SerialCommand's payload buffer to data buffer
 *
 *	@param	*cmd - readable SerialCommand
 *	@param	*buff - read data buffer
 *	@param	size - read data size
 *	@param	parserMap - data type required for correct parsing
 */
void ReadBuff (SerialCommand_t *cmd, void *buff, ui8 size, ParserMap_t parserMap)
{
	if (size > (MAX_BUFF_SIZE - cmd->readPos))
		return;  // data will not fit
	
	cmd->readPos += ConvertWithPM(buff, &cmd->payload[cmd->readPos], size, parserMap);
}


/**	@brief	Rearranges data depending on the
 * 			organization of system memory
 *
 *	@param 	*structure - structure buffer to bytes rearrange
 *	@param	size - structure buffer size
 *	@param	parserMap - data type required for correct parsing
 */
void SwapBytesInStruct (ui8 *structure, ui8 size, ParserMap_t parserMap)
{
	#ifdef SYS_BIG_ENDIAN

		if (parserMap == PM_DEFAULT_8BIT)
			return;

		else if (parserMap == PM_DEFAULT_16BIT)
		{
			for (ui8 i = 0; i < size; i += 2)
				SwapMemoryContent(&structure[i], &structure[i + 1]);

			return;
		}

		else if (parserMap == PM_DEFAULT_32BIT)
		{
			for (ui8 i = 0; i < size; i += 4)
			{
				SwapMemoryContent(&structure[i], &structure[i + 3]);
				SwapMemoryContent(&structure[i + 1], &structure[i + 2]);
			}

			return;
		}

		const ParserBlock_t *arrDB;
		ui8 arrDB_ElementsCount;

		switch (parserMap)
		{
			case PM_CONTROL :
				arrDB = Control_ParserStructDB;
				arrDB_ElementsCount = Control_ParserStructDB_Size;
				break;

						case PM_CONTROL_CONFIG :
							arrDB = ControlConfig_ParserStructDB;
							arrDB_ElementsCount = ControlConfig_ParserStructDB_Size;
							break;

			case PM_MAIN_PARAMS_3 :
				arrDB = MainParams3_ParserStructDB;
				arrDB_ElementsCount = MainParams3_ParserStructDB_Size;
				break;

						case PM_MAIN_PARAMS_EXT :
							arrDB = MainParamsExt_ParserStructDB;
							arrDB_ElementsCount = MainParamsExt_ParserStructDB_Size;
							break;

			case PM_MAIN_PARAMS_EXT_2 :
				arrDB = MainParamsExt2_ParserStructDB;
				arrDB_ElementsCount = MainParamsExt2_ParserStructDB_Size;
				break;

						case PM_MAIN_PARAMS_EXT_3 :
							arrDB = MainParamsExt3_ParserStructDB;
							arrDB_ElementsCount = MainParamsExt3_ParserStructDB_Size;
							break;

			case PM_DATA_STREAM_INTERVAL :
				arrDB = DataStreamInterval_ParserStructDB;
				arrDB_ElementsCount = DataStreamInterval_ParserStructDB_Size;
				break;

						case PM_REALTIME_DATA_3 :
							arrDB = RealTimeData3_ParserStructDB;
							arrDB_ElementsCount = RealTimeData3_ParserStructDB_Size;
							break;

			case PM_REALTIME_DATA_4 :
				arrDB = RealTimeData4_ParserStructDB;
				arrDB_ElementsCount = RealTimeData4_ParserStructDB_Size;
				break;

						case PM_GET_ANGLES :
							arrDB = GetAngles_ParserStructDB;
							arrDB_ElementsCount = GetAngles_ParserStructDB_Size;
							break;

			case PM_GET_ANGLES_EXT :
				arrDB = GetAnglesExt_ParserStructDB;
				arrDB_ElementsCount = GetAnglesExt_ParserStructDB_Size;
				break;

						case PM_AV_STATE_OLD_TX :
							arrDB = AdjVarsStateOldTx_ParserStructDB;
							arrDB_ElementsCount = AdjVarsStateOldTx_ParserStructDB_Size;
							break;

			case PM_AV_STATE_OLD_RX :
				arrDB = AdjVarsStateOldRx_ParserStructDB;
				arrDB_ElementsCount = AdjVarsStateOldRx_ParserStructDB_Size;
				break;

						case PM_AV_STATE_TX :
							arrDB = AdjVarsStateTx_ParserStructDB;
							arrDB_ElementsCount = AdjVarsStateTx_ParserStructDB_Size;
							break;

			case PM_AV_STATE_RX :
				arrDB = AdjVarsStateRx_ParserStructDB;
				arrDB_ElementsCount = AdjVarsStateRx_ParserStructDB_Size;
				break;

						case PM_EXT_IMU_DEBUG_INFO :
							arrDB = ExtIMU_DebugInfo_ParserStructDB;
							arrDB_ElementsCount = ExtIMU_DebugInfo_ParserStructDB_Size;
							break;

			case PM_GYRO_CORRECTION :
				arrDB = GyroCorrection_ParserStructDB;
				arrDB_ElementsCount = GyroCorrection_ParserStructDB_Size;
				break;

						case PM_AHRS_HELPER :
							arrDB = AHRS_Helper_ParserStructDB;
							arrDB_ElementsCount = AHRS_Helper_ParserStructDB_Size;
							break;

			case PM_HELPER_DATA :
				arrDB = HelperData_ParserStructDB;
				arrDB_ElementsCount = HelperData_ParserStructDB_Size;
				break;

						case PM_HELPER_DATA_EXT :
							arrDB = HelperDataExt_ParserStructDB;
							arrDB_ElementsCount = HelperDataExt_ParserStructDB_Size;
							break;

			case PM_CALIB_INFO :
				arrDB = CalibInfo_ParserStructDB;
				arrDB_ElementsCount = CalibInfo_ParserStructDB_Size;
				break;

						case PM_BOARD_INFO :
							arrDB = BoardInfo_ParserStructDB;
							arrDB_ElementsCount = BoardInfo_ParserStructDB_Size;
							break;

			case PM_BOARD_INFO_3 :
				arrDB = BoardInfo3_ParserStructDB;
				arrDB_ElementsCount = BoardInfo3_ParserStructDB_Size;
				break;

						case PM_AUTO_PID :
							arrDB = AutoPID_ParserStructDB;
							arrDB_ElementsCount = AutoPID_ParserStructDB_Size;
							break;

			case PM_AUTO_PID_2 :
				arrDB = AutoPID_2_ParserStructDB;
				arrDB_ElementsCount = AutoPID_2_ParserStructDB_Size;
				break;

						case PM_AUTO_PID_STATE :
							arrDB = AutoPID_State_ParserStructDB;
							arrDB_ElementsCount = AutoPID_State_ParserStructDB_Size;
							break;

			case PM_STATE_VARS :
				arrDB = StateVars_ParserStructDB;
				arrDB_ElementsCount = StateVars_ParserStructDB_Size;
				break;

						case PM_AHRS_DEBUG_INFO :
							arrDB = AHRS_DebugInfo_ParserStructDB;
							arrDB_ElementsCount = AHRS_DebugInfo_ParserStructDB_Size;
							break;

			case PM_MOTOR_4_CONTROL :
				arrDB = Motor4_Control_ParserStructDB;
				arrDB_ElementsCount = Motor4_Control_ParserStructDB_Size;
				break;

										case PM_DEFAULT_8BIT :  // Prevents [-Wswitch] warning
											return;
		}

		ui8 arrVarSize;
		ui8 currentOffsetAddr = 0;

		FOR_(i, arrDB_ElementsCount)
		{
			arrVarSize = arrDB[i].size / arrDB[i].length;

			FOR_(k, arrDB[i].length)
			{
				switch (arrVarSize)
				{
					case 1 :
						currentOffsetAddr++;
						break;

					case 2 :
						SwapMemoryContent((structure + currentOffsetAddr), (structure + currentOffsetAddr + 1));
						/* or (void)__builtin_bswap16(structure[currentOffsetAddr]); */

						currentOffsetAddr += 2;
						break;

					case 4 :
						SwapMemoryContent((structure + currentOffsetAddr), (structure + currentOffsetAddr + 3));
						SwapMemoryContent((structure + currentOffsetAddr + 1), (structure + currentOffsetAddr + 2));
						/* or (void)__builtin_bswap32(structure[currentOffsetAddr]); */

						currentOffsetAddr += 4;
						break;
				}
			}
		}

	#endif
}


/**	@brief	Writes the variable at the address to the buffer considering
 * 			the organization of the system's memory
 *
 *	@param	*value - writable variable address
 *	@param	*payload - place of data writing
 *	@param	size - variable size
 */
void ToLittleEndian (const void *value, ui8 *payload, ui8 size)
{
	if (size > 4) return;
	if (size == 3) size = 4;

	memcpy(payload, value, size);

	#ifdef SYS_BIG_ENDIAN

		FOR_(i, size / 2)
			SwapMemoryContent((ui8*)payload + i, (ui8*)payload + size - 1 - i);

	#endif
}


/**	@brief	Reads a buffer into the address of a variable considering
 * 			the organization of the system's memory
 *
 *	@param	*value - variable write address
 *	@param	*payload - place of data reading
 *	@param	size - variable size
 */
void FromLittleEndian (void *value, ui8 *payload, ui8 size)
{
	if (size > 4) return;
	if (size == 3) size = 4;

	memcpy(value, payload, size);

	#ifdef SYS_BIG_ENDIAN

		FOR_(i, size / 2)
			SwapMemoryContent((ui8*)value + i, (ui8*)value + size - 1 - i);

	#endif
}


/**	@brief	Swaps bytes by address
 *
 *	@param	*p1 - pointer to first byte
 *	@param	*p2 - pointer to second byte
 */
void SwapMemoryContent (ui8 *p1, ui8 *p2)
{
    ui8 temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}


/**	@brief	Writes a byte to SerialCommand's payload
 *
 *	@param	*cmd - SerialCommand
 *	@param	byte - byte to write
 */
void WriteByte (SerialCommand_t *cmd, const ui8 byte)
{
	if (cmd->payloadSize < MAX_BUFF_SIZE)
		cmd->payload[cmd->payloadSize++] = byte;
}


/**	@brief	Reads a byte from the SerialCommand
 * 			at the current read position
 *
 *	@param	*cmd - SerialCommand
 *
 *	@return	Byte read
 */
ui8 ReadByte (SerialCommand_t *cmd)
{
	return cmd->payload[cmd->readPos++];
}


/**	@brief	Writes two bytes to SerialCommand's payload
 *
 *	@param	*cmd - SerialCommand
 *	@param	word - two bytes to write
 */
void WriteWord (SerialCommand_t *cmd, const ui16 word)
{
	if (cmd->payloadSize <= MAX_BUFF_SIZE - 2)
	{
		ToLittleEndian(&word, &cmd->payload[cmd->payloadSize], 2);
		cmd->payloadSize += 2;
	}
}


/**	@brief	Reads two bytes from the SerialCommand
 * 			at the current read position
 *
 *	@param 	*cmd - SerialCommand
 *
 *	@return	Word read
 */
ui16 ReadWord (SerialCommand_t *cmd)
{
	ui16 word;
	FromLittleEndian(&word, &cmd->payload[cmd->readPos], 2);
	cmd->readPos += 2;
	return word;
}


/**	@brief	Writes four bytes to SerialCommand's payload
 *
 *	@param	*cmd - SerialCommand
 *	@param	dword - four bytes to write
 */
void WriteLong (SerialCommand_t *cmd, const ui32 dword)
{
	if (cmd->payloadSize <= MAX_BUFF_SIZE - 4)
	{
		ToLittleEndian(&dword, &cmd->payload[cmd->payloadSize], 4);
		cmd->payloadSize += 4;
	}
}


/**	@brief	Reads four bytes from the SerialCommand
 * 			at the current read position
 *
 *	@param	*cmd - SerialCommand
 *
 *	@return	Long read
 */
ui32 ReadLong (SerialCommand_t *cmd)
{
	ui32 dword;
	FromLittleEndian(&dword, &cmd->payload[cmd->readPos], 4);
	cmd->readPos += 4;
	return dword;
}


/**	@brief	Fills with zeros the SerialCommand's payload
 *
 *	@param	*cmd - SerialCommand
 *	@param	size - size of filled with zeros data
 */
void WriteEmptyBuff (SerialCommand_t *cmd, ui8 size)
{
	memset(&cmd->payload[cmd->payloadSize], 0, size);
	cmd->payloadSize += size;
}


/**	@brief	Rearranges current reading position
 *
 *	@param	*cmd - SerialCommand
 *	@param	size - size of skipped data
 */
void SkipBytes (SerialCommand_t *cmd, ui8 size)
{
	cmd->readPos += size;
}

/**	@brief	Initializes the write SerialCommand
 *
 *	@param	*cmd - SerialCommand
 *	@param	cmdID - SBGC32 command identifier
 */
void InitCmdWrite (SerialCommand_t *cmd, SBGC_Commands_t cmdID)
{
	cmd->commandID = cmdID;
	cmd->payloadSize = 0;
}
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *												  SBGC Service Functions
 */
/**	@addtogroup	Common
 *	@{
 */
/**	@brief	Sends SerialCommand without data
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	cmdID - SBGC32 command identifier
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_SendEmptyCommand (GeneralSBGC_t *generalSBGC, SBGC_Commands_t cmdID)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, cmdID);
	SBGC32_TX(generalSBGC, &cmd);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Sets default values of library variables for communication
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*TxFunc - driver function to transmit data buffers
 *	@param	*RxFunc - driver function to receive a data byte
 *	@param	*AvailableBytesFunc - driver function to get
 *			count of available bytes for reading
 *	@param	*TxDebugFunc - driver function to
 *			transmit debug data buffers
 *	@param	*GetTimeFunc - driver function getting
 *			current time in milliseconds
 *	@param	protocolVersion - SBGC32 communication protocol version
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_DefaultInit (GeneralSBGC_t *generalSBGC, TxFunc_t TxFunc, RxFunc_t RxFunc,
								 AvailableBytesFunc_t AvailableBytesFunc, TxDebugFunc_t TxDebugFunc,
								 GetTimeFunc_t GetTimeFunc, SBGC_ProtocolVersion_t protocolVersion)
{
	generalSBGC->TxFunc = TxFunc;
	generalSBGC->RxFunc = RxFunc;
	generalSBGC->AvailableBytesFunc = AvailableBytesFunc;
	generalSBGC->TxDebugFunc = TxDebugFunc;
	generalSBGC->GetTimeFunc = GetTimeFunc;

	generalSBGC->protocolVersion = protocolVersion;
	generalSBGC->txTimeout = SBGC_TX_WAITING;
	generalSBGC->rxTimeout = SBGC_RX_WAITING;
	generalSBGC->txrxTimeout = SBGC_RX_WAITING;

	generalSBGC->_txErrorsCount = 0;
	generalSBGC->_rxErrorsCount = 0;

	/* Startup Delay */
	ui32 currentTime = generalSBGC->GetTimeFunc(generalSBGC->Drv);
	while ((generalSBGC->GetTimeFunc(generalSBGC->Drv) - currentTime) < SBGC_STARTUP_DELAY);

	/* Getting board information */
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_BOARD_INFO);
	WriteWord(&cmd, 0);  // cfg = 0

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_BOARD_INFO), "Board Info:") == TX_RX_OK)
	{
		generalSBGC->_boardVersion = cmd.payload[0];
		FromLittleEndian(&generalSBGC->_firmwareVersion, &cmd.payload[1], 2);
	}

	#ifdef SBGC_DEBUG_MODE

	    char boardVersionStr [4];
  		char firmwareVersionStr [7];

		FormatBoardVersion(generalSBGC->_boardVersion, boardVersionStr);
   		FormatFirmwareVersion(generalSBGC->_firmwareVersion, firmwareVersionStr);

		PrintMessage(generalSBGC, TEXT_SIZE_(" \n"));
		PrintMessage(generalSBGC, TEXT_SIZE_("******************************\n"));

		if (generalSBGC->_ParserCurrentStatus == TX_RX_OK)
		{
			PrintMessage(generalSBGC, TEXT_SIZE_("The system is ready to go!\n"));
			PrintMessage(generalSBGC, TEXT_SIZE_((char*)"Board Version: "));
			PrintMessage(generalSBGC, TEXT_SIZE_(boardVersionStr));
			PrintMessage(generalSBGC, TEXT_SIZE_((char*)" \n"));
			PrintMessage(generalSBGC, TEXT_SIZE_((char*)"Firmware Version: "));
			PrintMessage(generalSBGC, TEXT_SIZE_(firmwareVersionStr));
			PrintMessage(generalSBGC, TEXT_SIZE_((char*)" \n"));
			PrintMessage(generalSBGC, TEXT_SIZE_("******************************\n\r"));
		}

		else
		{
			PrintMessage(generalSBGC, TEXT_SIZE_("Communication Error!\n"));
			PrintMessage(generalSBGC, TEXT_SIZE_("******************************\n\r"));
		}

	#endif

	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *												  Verification Functions
 */
/**	@addtogroup	Verification
 *	@{
 */
/**	@brief	Receives a confirmation command from SBGC32
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*confirmationState - confirmation structure
 *	@param	cmdID - identifier of the SerialCommand being confirmed
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CheckConfirmation (GeneralSBGC_t *generalSBGC, ConfirmationState_t *confirmationState, SBGC_Commands_t cmdID)
{
	SerialCommand_t cmd;
	ui32 currentTime = generalSBGC->GetTimeFunc(generalSBGC->Drv);

	#ifdef SBGC_DEBUG_MODE
		char debugStr [30];
	#endif

	while (1)
	{
		TxRxStatus_t lastParserStatus = SBGC32_RX(generalSBGC, &cmd, generalSBGC->txrxTimeout);

		if (lastParserStatus == TX_RX_OK &&
			((cmd.commandID == CMD_CONFIRM && cmdID == cmd.payload[0]) ||
			(cmd.commandID == CMD_RESET)))
		{
			confirmationState->cmdID = ReadByte(&cmd);

			if (cmd.payloadSize == 2)
				confirmationState->cmdData = ReadByte(&cmd);
			else if (cmd.payloadSize == 3)
				confirmationState->cmdData = ReadWord(&cmd);

			#ifdef SBGC_DEBUG_MODE
				/* - - - - - - - User Confirm Handler - - - - - - - - */
				if (cmd.payloadSize <= 1)
					sprintf(debugStr, "CMD_CONFIRM #%d\n", confirmationState->cmdID);
				else
					sprintf(debugStr, "CMD_CONFIRM #%d (%u)\n", confirmationState->cmdID, confirmationState->cmdData);

				generalSBGC->TxDebugFunc(debugStr, strlen(debugStr));
				/*  - - - - - - - - - - - - - - - - - - - - - - - - - */
			#endif

			generalSBGC->_ParserCurrentStatus = lastParserStatus;
			return generalSBGC->_ParserCurrentStatus;
		}

		else if (lastParserStatus == TX_RX_OK && (cmd.commandID == CMD_ERROR))
		{
			confirmationState->errCode = ReadByte(&cmd);

			if (cmd.payloadSize > 1)
				ReadBuff(&cmd, &confirmationState->errData, 4, PM_DEFAULT_8BIT);

			#ifdef SBGC_DEBUG_MODE
				/* - - - - - - - - User Error Handler - - - - - - - - */
				sprintf(debugStr, "CMD_ERROR: #%d (%s)\n", confirmationState->errCode, confirmationState->errData);
				generalSBGC->TxDebugFunc(debugStr, strlen(debugStr));
				/*  - - - - - - - - - - - - - - - - - - - - - - - - - */
			#endif

			generalSBGC->_ParserCurrentStatus = lastParserStatus;
			return generalSBGC->_ParserCurrentStatus;
		}

		if (generalSBGC->GetTimeFunc(generalSBGC->Drv) - currentTime >= generalSBGC->txrxTimeout)
		{
			#ifdef SBGC_DEBUG_MODE
				/*  - - - - - - User Wait-Error Handler - - - - - - - */
				PrintMessage(generalSBGC, TEXT_SIZE_("CONFIRM_TIMEOUT_ERROR!\n"));
				/*  - - - - - - - - - - - - - - - - - - - - - - - - - */
			#endif

			generalSBGC->_ParserCurrentStatus = RX_TIMEOUT_ERROR;
			return generalSBGC->_ParserCurrentStatus;
		}
	}
}


/**	@brief	Works with read parser errors
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	receiveStatus - status from RX or TX_RX operation
 *	@param 	*message - debug info string
 *
 *	@return Communication status
 */
TxRxStatus_t CheckReceipt (GeneralSBGC_t *generalSBGC, TxRxStatus_t receiveStatus, char *message)
{
	generalSBGC->_ParserCurrentStatus = receiveStatus;

	if (generalSBGC->_ParserCurrentStatus != TX_RX_OK)
		generalSBGC->_rxErrorsCount++;

	#ifdef SBGC_DEBUG_MODE

		char totalStr [60];
		ui8 pos = 0;

		if (generalSBGC->_ParserCurrentStatus != TX_RX_OK)
		{
			/* - - - - - - - - User RX Errors Handler - - - - - - - - */
			memcpy(totalStr, TEXT_SIZE_(message));
			pos += strlen(message);
			memcpy(&totalStr[pos], TEXT_SIZE_(" Receive Error: "));
			pos += strlen(" Receive Error: ");
			pos += ConvertErrorToString(generalSBGC->_ParserCurrentStatus, &totalStr[pos]);
			totalStr[pos] = '\n';
			totalStr[pos + 1] = '\0';
			/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - */
		}

		else
		{
			/*  - - - - - - - User RX Success Handler - - - - - - - - */
			memcpy(totalStr, TEXT_SIZE_(message));
			pos += strlen(message);
			memcpy(&totalStr[pos], TEXT_SIZE_(" Receive OK!"));
			pos += strlen(" Receive OK!");
			totalStr[pos] = '\n';
			totalStr[pos + 1] = '\0';
			/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - */
		}

		generalSBGC->TxDebugFunc(TEXT_SIZE_(totalStr));

	#endif

	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Calculates the checksum for the first version
 * 			of the SBGC32 communication protocol
 *
 *	@param	*data - data buffer for calculate
 *	@param	length - size of data buffer
 *
 *	@return	Calculated checksum
 */
ui8 Modulo256_Calculate (ui8 *data, ui16 length)
{
    i32 totalSum = 0;

    ui16 count = 0;
    while (count < length)
        totalSum += data[count++];

    return totalSum % 256;
}


/**	@brief	Calculates the checksum for the second version
 * 			of the SBGC32 communication protocol
 *
 *	@param	*data - data buffer for calculate
 *	@param	length - size of data buffer
 *
 *	@return	Calculated checksum
 */
ui16 CRC16_Calculate (ui8 *data, ui16 length)
{
    ui16 CRC_Register = 0;
    ui16 polynom = 0x8005;
    ui8  shiftRegister,
    	 dataBit,
		 CRC_Bit;

    for (ui16 i = 0; i < length; i++)
    {
        for (shiftRegister = 1; shiftRegister > 0; shiftRegister <<= 1)
        {
        	dataBit = (data[i] & shiftRegister) ? 1 : 0;
            CRC_Bit = CRC_Register >> 15;
            CRC_Register <<= 1;

            if (dataBit != CRC_Bit)
            	CRC_Register ^= polynom;
        }
    }

    return CRC_Register;
}
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														 Debug Functions
 */
/**	@addtogroup	Debug
 *	@{
 */
/**	@brief	Displays debug information
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*data - printable data
 *	@param	length - printable data size
 */
void PrintMessage (GeneralSBGC_t *generalSBGC, char *data, ui16 length)
{
	generalSBGC->TxDebugFunc(data, length);
}


/**	@brief	Displays variable
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*data - printable variable
 *	@param	*str - debug info string
 *	@param	vType - type of variable
 */
void PrintStructElement (GeneralSBGC_t *generalSBGC, void *data, const char *str, VarTypes_t vType)
{
	char debugStr [50];

	switch (vType)
	{
		case _UNSIGNED_CHAR_ :
		{
			ui8 dataTemp = *(ui8*)data;
			sprintf(debugStr, "%s %u\n", str, dataTemp);

			break;
		}

		case _UNSIGNED_SHORT_ :
		{
			ui16 dataTemp = *(ui16*)data;
			sprintf(debugStr, "%s %u\n", str, dataTemp);

			break;
		}

		case _UNSIGNED_INT_ :
		{
			ui32 dataTemp = *(ui32*)data;

			#ifdef _L32__
				sprintf(debugStr, "%s %u\n", str, dataTemp);
			#else
				sprintf(debugStr, "%s %lu\n", str, dataTemp);
			#endif

			break;
		}

		case _SIGNED_CHAR_ :
		{
			i8 dataTemp = *(i8*)data;
			sprintf(debugStr, "%s %i\n", str, dataTemp);

			break;
		}

		case _SIGNED_SHORT_ :
		{
			i16 dataTemp = *(i16*)data;
			sprintf(debugStr, "%s %i\n", str, dataTemp);

			break;
		}

		case _SIGNED_INT_ :
		{
			i32 dataTemp = *(i32*)data;

			#ifdef _L32__
				sprintf(debugStr, "%s %i\n", str, dataTemp);
			#else
				sprintf(debugStr, "%s %li\n", str, dataTemp);
			#endif

			break;
		}

		case _FLOAT_ :
		{
			float dataTemp = *(float*)data;
			sprintf(debugStr, "%s %.3f\n", str, dataTemp);  // .3f is default. May be changed

			break;
		}

		default :
		{
			i32 dataTemp = *(i32*)data;

			#ifdef _L32__
				sprintf(debugStr, "%s %i\n", str, dataTemp);
			#else
				sprintf(debugStr, "%s %li\n", str, dataTemp);
			#endif

			break;
		}
	}

	PrintMessage(generalSBGC, TEXT_SIZE_(debugStr));
}


/**	@brief	Converts the parser status to a string
 *
 *	@param	txRxStatus - status from TX/RX operation
 *	@param	*str - writable buffer
 *
 *	@return	Length of a writable string
 */
ui8 ConvertErrorToString (TxRxStatus_t txRxStatus, char *str)
{
	switch (txRxStatus)
	{
		case TX_RX_OK :
			memcpy(str, TEXT_SIZE_(nameof(TX_RX_OK)));
			return strlen(nameof(TX_RX_OK));

					case TX_BUFFER_OVERFLOW_ERROR :
						memcpy(str, TEXT_SIZE_(nameof(TX_BUFFER_OVERFLOW_ERROR)));
						return strlen(nameof(TX_BUFFER_OVERFLOW_ERROR));

		case RX_START_PARSE :
			memcpy(str, TEXT_SIZE_(nameof(RX_START_PARSE)));
			return strlen(nameof(RX_START_PARSE));

					case RX_EMPTY_BUFF_ERROR :
						memcpy(str, TEXT_SIZE_(nameof(RX_EMPTY_BUFF_ERROR)));
						return strlen(nameof(RX_EMPTY_BUFF_ERROR));

		case RX_BUFFER_REALTIME_ERROR :
			memcpy(str, TEXT_SIZE_(nameof(RX_BUFFER_REALTIME_ERROR)));
			return strlen(nameof(RX_BUFFER_REALTIME_ERROR));

					case RX_HEADER_CHECKSUM_ERROR :
						memcpy(str, TEXT_SIZE_(nameof(RX_HEADER_CHECKSUM_ERROR)));
						return strlen(nameof(RX_HEADER_CHECKSUM_ERROR));

		case RX_PAYLOAD_CHECKSUM_ERROR :
			memcpy(str, TEXT_SIZE_(nameof(RX_PAYLOAD_CHECKSUM_ERROR)));
			return strlen(nameof(RX_PAYLOAD_CHECKSUM_ERROR));

					case RX_BUFFER_OVERFLOW_ERROR :
						memcpy(str, TEXT_SIZE_(nameof(RX_BUFFER_OVERFLOW_ERROR)));
						return strlen(nameof(RX_BUFFER_OVERFLOW_ERROR));

		case RX_TIMEOUT_ERROR :
			memcpy(str, TEXT_SIZE_(nameof(RX_TIMEOUT_ERROR)));
			return strlen(nameof(RX_TIMEOUT_ERROR));

					case NOT_SUPPORTED_BY_FIRMWARE :
						memcpy(str, TEXT_SIZE_(nameof(NOT_SUPPORTED_BY_FIRMWARE)));
						return strlen(nameof(NOT_SUPPORTED_BY_FIRMWARE));
	}

	return 0;
}
/**	@}
 */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
