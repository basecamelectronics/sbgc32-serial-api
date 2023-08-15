/** ____________________________________________________________________
 *
 *	SBGC32 Serial API Library v1.1
 *
 *	@file		core.c
 *
 *	@brief 		Core source file
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


#if (SYS_BIG_ENDIAN || SBGC_REF_INFO)

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *					Big Endian Mapping and Reference Info Structures
	 */
	/**	@addtogroup	Other_External
	 * 	@{
	 */
	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t AHRS_DebugInfoReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Main IMU Ref Src",			_UNSIGNED_CHAR_				),  // 0
		PARAM_BLOCK_(	"Frame IMU Ref Src",		_UNSIGNED_CHAR_				),  // 1
		PARAM_BLOCK_(	"Main IMU Z Ref Err",		_UNSIGNED_CHAR_				),  // 2
		PARAM_BLOCK_(	"Main IMU H Ref Err",		_UNSIGNED_CHAR_				),  // 3
		PARAM_BLOCK_(	"Frame IMU Z Ref Err",		_UNSIGNED_CHAR_				),  // 4
		PARAM_BLOCK_(	"Frame IMU H Ref Err",		_UNSIGNED_CHAR_				),  // 5
		PARAM_BLOCK_(	"Ext IMU Status",			_UNSIGNED_CHAR_				),  // 6
		PARAM_BLOCK_(	"Ext IMU Packets Received Cnt",
													_UNSIGNED_SHORT_			),  // 7
		PARAM_BLOCK_(	"Ext IMU Parse Err Cnt",	_UNSIGNED_SHORT_			),  // 8
		PARAM_BLOCK_(	"Ext Corr H Ref",			_UNSIGNED_CHAR_				),  // 9
		PARAM_BLOCK_(	"Ext Corr Z Ref",			_UNSIGNED_CHAR_				),  // 10
		PARAMS_BLOCK_(	"Reserved",					_UNSIGNED_CHAR_,		13	),  // 11

	};

	const ui8 AHRS_DebugInfoReferenceInfoArrayElCnt = countof_(AHRS_DebugInfoReferenceInfoArray);


	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t motor4_ControlReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"FF Speed",					_SIGNED_SHORT_				),  // 0
		PARAM_BLOCK_(	"Angle Error",				_SIGNED_SHORT_				),  // 1
		PARAM_BLOCK_(	"PID Out",					_FLOAT_						),  // 2

	};

	const ui8 motor4_ControlReferenceInfoArrayElCnt = countof_(motor4_ControlReferenceInfoArray);
	/**	@}
	 */

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *											Main Communication Functions
 */
/**	@addtogroup	Communication
 * 	@{
 */
#if (UNEXP_CMD_BUFFER)

	/**	@note	Private function
	 */
	static void SaveUnexpectedCommand (GeneralSBGC_t *generalSBGC, SerialCommand_t *serialCommand)
	{
		#if (SBGC_CONFIRM_CMD == SET_OFF)

			if (serialCommand->commandID == CMD_CONFIRM)
				return;

		#endif

		/* Overflow checking */
		if (generalSBGC->_unexpectedCommandsBuffHead != generalSBGC->_unexpectedCommandsBuffTail)
		{
			ui16 headCounter = generalSBGC->_unexpectedCommandsBuffHead;
			ui16 i = 0;
			Boolean_t needShiftTailFlag = FALSE__;

			for (; i < (serialCommand->payloadSize + 2); i++)
			{
				headCounter = ((headCounter + 1) & UNEXP_CMD_BUFFER_SIZE_MASK);

				if (headCounter == generalSBGC->_unexpectedCommandsBuffTail)
				{
					needShiftTailFlag = TRUE__;
					break;
				}
			}

			if (needShiftTailFlag)
			{
				#if (UNEXP_CMD_OLD_PRIORITY)
					/* Exit if buffer will overflows */
					return;

				#else

					ui8 shiftTemp;

					while (1)
						/* Shift tail while command will fit */
					{
						shiftTemp = generalSBGC->_unexpectedCommandsBuff[generalSBGC->_unexpectedCommandsBuffTail + 1] + 2;

						if (i <= shiftTemp)
						{
							generalSBGC->_unexpectedCommandsBuffTail += shiftTemp;
							i += shiftTemp;
						}

						else
							break;
					}

				#endif
			}
		}

		generalSBGC->_unexpectedCommandsBuff[generalSBGC->_unexpectedCommandsBuffHead++] = serialCommand->commandID;

		generalSBGC->_unexpectedCommandsBuff[generalSBGC->_unexpectedCommandsBuffHead++] = serialCommand->payloadSize;

		for (ui16 i = 0; i < serialCommand->payloadSize; i++)
			generalSBGC->_unexpectedCommandsBuff[generalSBGC->_unexpectedCommandsBuffHead++] = serialCommand->payload[i];
	}


	/**	@note	Private function
	 */
	static ui8 DeleteUnexpectedCommand (GeneralSBGC_t *generalSBGC, ui16 buffPointer)
	{
		ui16 cmdPayloadSizePointer = (buffPointer + 1) & UNEXP_CMD_BUFFER_SIZE_MASK;
		ui8 cmdSize = generalSBGC->_unexpectedCommandsBuff[cmdPayloadSizePointer] + 2;

		/* Shifting */
		if (((buffPointer + cmdSize) & UNEXP_CMD_BUFFER_SIZE_MASK) != generalSBGC->_unexpectedCommandsBuffHead)
			/* If this command not latest */
			for (ui16 i = 0; i < cmdSize; i++)
				generalSBGC->_unexpectedCommandsBuff[buffPointer + i] = generalSBGC->_unexpectedCommandsBuff[buffPointer + cmdSize + i];

		generalSBGC->_unexpectedCommandsBuffHead -= cmdSize;  // Shift head pointer

		return cmdSize;
	}


	/**	@note	Private function
	 */
	static void ReadUnexpectedCommand (GeneralSBGC_t *generalSBGC, SerialCommand_t *serialCommand)
	{
		generalSBGC->_unexpectedCommandCurrentPointer = generalSBGC->_unexpectedCommandsBuffTail;

		serialCommand->commandID = generalSBGC->_unexpectedCommandsBuff[generalSBGC->_unexpectedCommandsBuffTail++];

		serialCommand->payloadSize = generalSBGC->_unexpectedCommandsBuff[generalSBGC->_unexpectedCommandsBuffTail++];

		for (ui16 i = 0; i < serialCommand->payloadSize; i++)
			serialCommand->payload[i] = generalSBGC->_unexpectedCommandsBuff[generalSBGC->_unexpectedCommandsBuffTail++];
	}


#endif


/**	@brief	Forms a SerialCommand from the buffer
 *			and sends it to the SBGC device
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*serialCommand - pointer to a structure ready
 *			to be transmitted
 *
 *	@return	Transmission status
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
	ui8 size = serialCommand->payloadSize + 4 + ((generalSBGC->protocolVersion == PR2_START_CHARACTER) ? 2 : 1);

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
 *	@note	Be careful, this function absorbs Rx driver buffer
 *			permanently at this layer
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*serialCommand - Pointer to a structure to which the
 *			incoming serialCommand will be written
 *	@param	timeout - the value of the maximum possible waiting
 *			time for receiving one whole SerialCommand
 *
 *	@return	TX_RX_OK or last state of lastParserStatus variable
 */
TxRxStatus_t SBGC32_RX (GeneralSBGC_t *generalSBGC, SerialCommand_t *serialCommand, ui32 timeout)
{
	serialCommand->readPos = 0;  // Prepare for reading

	#if (UNEXP_CMD_BUFFER)

		if (generalSBGC->_unexpectedCommandsBuffTail != generalSBGC->_unexpectedCommandsBuffHead)
		/* Read next keeping in _unexpectedCommandsBuff serial command */
		{
			ReadUnexpectedCommand(generalSBGC, serialCommand);
			return RX_BUFFERED_COMMAND;
		}

		else
		/* Try to get a new serial command from hardware driver buffer */

	#endif

	{
		/* Parser initializing */
		ui8 startSim;
		ui8 headBuff [3];  /* Header buffer:
		headBuff[0] is command ID || headBuff[1] is payload size || headBuff[2] is header checksum */
		ui16 availableBytes;

		TxRxStatus_t lastParserStatus = RX_START_PARSE;
		ParserState_t parserState = STATE_IDLE;

		/* Launch timer */
		ui32 currentTime = generalSBGC->GetTimeFunc(generalSBGC->Drv);

		while (1)
		{
			switch (parserState)
			{
				/* Waiting start byte */
				case STATE_IDLE :
				case STATE_RESYNC :
				{
					if (generalSBGC->AvailableBytesFunc(generalSBGC->Drv))
					{
						startSim = 0;

						generalSBGC->RxFunc(generalSBGC->Drv, &startSim);

						if (startSim == generalSBGC->protocolVersion)
							parserState = STATE_CHECK_HEADER;

						else
							lastParserStatus = RX_START_PARSE;
					}

					else
						lastParserStatus = RX_EMPTY_BUFF_ERROR;

					break;  // Passing to next state
				}

				/* Waiting whole header */
				case STATE_CHECK_HEADER :
				{
					availableBytes = generalSBGC->AvailableBytesFunc(generalSBGC->Drv);

					if ((availableBytes >= 3) && (availableBytes != RX_BUFFER_OVERFLOW_FLAG))
						for (ui8 i = 0; i < 3; i++)
							generalSBGC->RxFunc(generalSBGC->Drv, &headBuff[i]);

					else
					{
						lastParserStatus = RX_BUFFER_REALTIME_ERROR;
						break;
					}

					if (((headBuff[0] + headBuff[1]) % 256 != headBuff[2]) ||
						(headBuff[0] == 0))
					{
						lastParserStatus = RX_HEADER_CHECKSUM_ERROR;
						parserState = STATE_RESYNC;
						break;
					}

					parserState = STATE_CHECK_PAYLOAD;
					break;  // Passing to next state
				}

				/* Waiting whole payload and checksum */
				case STATE_CHECK_PAYLOAD :
				{
					ui8 checksumSize = ((generalSBGC->protocolVersion == PR2_START_CHARACTER) ? 2 : 1);
					ui8 complexBuff [3 + headBuff[1] + checksumSize];  // (Header + payload + checksum) buffer

					availableBytes = generalSBGC->AvailableBytesFunc(generalSBGC->Drv);

					if ((availableBytes >= headBuff[1] + checksumSize) && (availableBytes != RX_BUFFER_OVERFLOW_FLAG))
						for (ui8 i = 0; i < headBuff[1] + checksumSize; i++)
							generalSBGC->RxFunc(generalSBGC->Drv, &complexBuff[i + 3]);  // Offset from header space

					else
					{
						lastParserStatus = RX_BUFFER_REALTIME_ERROR;
						break;
					}

					/* Checksum checking */
					if (!(checksumSize - 1))  // If SBGC_PROTOCOL_V1
					{
						if (complexBuff[3 + headBuff[1]] != Modulo256_Calculate(&complexBuff[3], headBuff[1]))
						{
							lastParserStatus = RX_PAYLOAD_CHECKSUM_ERROR;
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
							lastParserStatus = RX_PAYLOAD_CHECKSUM_ERROR;
							parserState = STATE_RESYNC;
							break;
						}
					}

					/* Data passed all checks. Filling the serialCommand struct */
					serialCommand->commandID = (SBGC_Command_t)headBuff[0];
					memcpy(serialCommand->payload, &complexBuff[3], headBuff[1]);
					serialCommand->payloadSize = headBuff[1];

					return TX_RX_OK;  // Incoming command was received fine
				}
			}

			/* Timeout checking */
			if ((generalSBGC->GetTimeFunc(generalSBGC->Drv) - currentTime) >= timeout)
				return lastParserStatus;
		}
	}
}


/**	@brief	Performs serial transmission and reception of a SerialCommand
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*serialCommand - pointer to a formed structure, into which
 *			the requested SerialCommand will be overwritten
 *	@param	cmdID - SBGC32 command identifier
 *
 *	@return	Request response result
 */
TxRxStatus_t SBGC32_TX_RX (GeneralSBGC_t *generalSBGC, SerialCommand_t *serialCommand, SBGC_Command_t cmdID)
{
	TxRxStatus_t lastParserStatus;

	/* Send request */
	lastParserStatus = SBGC32_TX(generalSBGC, serialCommand);

	if (lastParserStatus != TX_RX_OK)
		return lastParserStatus;

	lastParserStatus = SBGC32_FindCommand(generalSBGC, serialCommand, cmdID, generalSBGC->txrxTimeout);

	if (getcommstatus_(lastParserStatus) == FALSE__)
		generalSBGC->_missedCommandCount++;

	return lastParserStatus;
}


/**	@brief	Finds a SerialCommand in a buffer
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*serialCommand - pointer to an empty structure, into which
 *			the found SerialCommand will be overwritten
 *	@param	cmdID - SBGC32 command identifier
 *	@param	timeout - the value of the maximum possible waiting
 *			time for receiving desired SerialCommand
 *
 *	@return	Found result
 */
TxRxStatus_t SBGC32_FindCommand (GeneralSBGC_t *generalSBGC, SerialCommand_t *serialCommand, SBGC_Command_t cmdID, ui32 timeout)
{
	#if (UNEXP_CMD_BUFFER)
		ui16 unexpectedCommandsBuffTailTemp = generalSBGC->_unexpectedCommandsBuffTail;
	#endif

	TxRxStatus_t lastParserStatus;
	ui32 currentTime = generalSBGC->GetTimeFunc(generalSBGC->Drv);

	while (1)
	{
		lastParserStatus = SBGC32_RX(generalSBGC, serialCommand, generalSBGC->rxTimeout);

		if (getcommstatus_(lastParserStatus) &&
			(serialCommand->commandID == cmdID))
			/* Has correct command parsed */
		{
			#if (UNEXP_CMD_BUFFER)

				if (lastParserStatus == RX_BUFFERED_COMMAND)
				{
					ui8 deletedCmdSize = 0;

					deletedCmdSize = DeleteUnexpectedCommand(generalSBGC, generalSBGC->_unexpectedCommandCurrentPointer);

					if (generalSBGC->_unexpectedCommandCurrentPointer ==
						((generalSBGC->_unexpectedCommandsBuffTail - deletedCmdSize) & UNEXP_CMD_BUFFER_SIZE_MASK))
						/* If this command was latest it is need to shift tail by deletedCmdSize backward */
						generalSBGC->_unexpectedCommandsBuffTail -= deletedCmdSize;

					unexpectedCommandsBuffTailTemp = generalSBGC->_unexpectedCommandsBuffTail;
				}

				generalSBGC->_unexpectedCommandsBuffTail = unexpectedCommandsBuffTailTemp;

			#endif

			return lastParserStatus;
		}

		#if (UNEXP_CMD_BUFFER)

			if (serialCommand->commandID != cmdID)
				/* Has wrong command parsed */
			{
				if (lastParserStatus == TX_RX_OK)
				{
					/* Remember old tail temp pointer before new command saving */
					generalSBGC->_unexpectedCommandsBuffTail = unexpectedCommandsBuffTailTemp;

					SaveUnexpectedCommand(generalSBGC, serialCommand);

					/* Rewrite to new tail pointer */
					unexpectedCommandsBuffTailTemp = generalSBGC->_unexpectedCommandsBuffTail;
				}
			}

		#endif

		/* Timeout checking */
		if ((generalSBGC->GetTimeFunc(generalSBGC->Drv) - currentTime) >= timeout)
		{
			#if (UNEXP_CMD_BUFFER)
				generalSBGC->_unexpectedCommandsBuffTail = unexpectedCommandsBuffTailTemp;
			#endif

			return RX_TIMEOUT_ERROR;
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
#if (SYS_BIG_ENDIAN || SBGC_REF_INFO)

	/**	@brief	Appoints Serial API reference structure
	 *
	 *	@param	**buffArr - pointer to undefined structure
	 *	@param	parserMap - structure type for assign
	 *
	 *	@return	Number of elements of an assigned structure
	 */
	ui8 AssignStructFromParserMap (const ParameterReferenceInfo_t **buffArr, ParserMap_t parserMap)
	{
			switch (parserMap)
			{
				#if (SBGC_ADJVAR_MODULE)

					case PM_AV_STATE_OLD_TX :
						*buffArr = adjVarsStateOldTxReferenceInfoArray;
						return adjVarsStateOldTxReferenceInfoArrayElCnt;
						break;

					case PM_AV_STATE_OLD_RX :
						*buffArr = adjVarsStateOldRxReferenceInfoArray;
						return adjVarsStateOldRxReferenceInfoArrayElCnt;
						break;

					case PM_AV_STATE_TX :
						*buffArr = adjVarsStateTxReferenceInfoArray;
						return adjVarsStateTxReferenceInfoArrayElCnt;
						break;

					case PM_AV_STATE_RX :
						*buffArr = adjVarsStateRxReferenceInfoArray;
						return adjVarsStateRxReferenceInfoArrayElCnt;
						break;

				#endif

				#if (SBGC_CALIB_MODULE)

					case PM_IMU_EXT_CALIB :
						*buffArr = IMU_ExtCalibReferenceInfoArray;
						return IMU_ExtCalibReferenceInfoArrayElCnt;
						break;

					case PM_CALIB_INFO :
						*buffArr = calibInfoReferenceInfoArray;
						return calibInfoReferenceInfoArrayElCnt;
						break;

				#endif

				case PM_AHRS_DEBUG_INFO :
					*buffArr = AHRS_DebugInfoReferenceInfoArray;
					return AHRS_DebugInfoReferenceInfoArrayElCnt;
					break;

				case PM_MOTOR_4_CONTROL :
					*buffArr = motor4_ControlReferenceInfoArray;
					return motor4_ControlReferenceInfoArrayElCnt;
					break;

				#if (SBGC_CONTROL_MODULE)

					case PM_CONTROL :
						*buffArr = controlReferenceInfoArray;
						return controlReferenceInfoArrayElCnt;
						break;

					case PM_CONTROL_CONFIG :
						*buffArr = controlConfigReferenceInfoArray;
						return controlConfigReferenceInfoArrayElCnt;
						break;

				#endif

				#if (SBGC_IMU_MODULE)

					case PM_EXT_IMU_DEBUG_INFO :
						*buffArr = extIMU_DebugInfoReferenceInfoArray;
						return extIMU_DebugInfoReferenceInfoArrayElCnt;
						break;

					case PM_GYRO_CORRECTION :
						*buffArr = gyroCorrectionReferenceInfoArray;
						return gyroCorrectionReferenceInfoArrayElCnt;
						break;

					case PM_AHRS_HELPER :
						*buffArr = AHRS_HelperReferenceInfoArray;
						return AHRS_HelperReferenceInfoArrayElCnt;
						break;

					case PM_HELPER_DATA :
						*buffArr = helperDataReferenceInfoArray;
						return helperDataReferenceInfoArrayElCnt;
						break;

					case PM_HELPER_DATA_EXT :
						*buffArr = helperDataExtReferenceInfoArray;
						return helperDataExtReferenceInfoArrayElCnt;
						break;

				#endif

				#if (SBGC_PROFILES_MODULE)

					case PM_MAIN_PARAMS_3 :
						*buffArr = mainParams3_ReferenceInfoArray;
						return mainParams3_ReferenceInfoArrayElCnt;
						break;

					case PM_MAIN_PARAMS_EXT :
						*buffArr = mainParamsExtReferenceInfoArray;
						return mainParamsExtReferenceInfoArrayElCnt;
						break;

					case PM_MAIN_PARAMS_EXT_2 :
						*buffArr = mainParamsExt2_ReferenceInfoArray;
						return mainParamsExt2_ReferenceInfoArrayElCnt;
						break;

					case PM_MAIN_PARAMS_EXT_3 :
						*buffArr = mainParamsExt3_ReferenceInfoArray;
						return mainParamsExt3_ReferenceInfoArrayElCnt;
						break;

				#endif

				#if (SBGC_REALTIME_MODULE)

					case PM_DATA_STREAM_INTERVAL :
						*buffArr = dataStreamIntervalReferenceInfoArray;
						return dataStreamIntervalReferenceInfoArrayElCnt;
						break;

					case PM_REALTIME_DATA_3 :
					case PM_REALTIME_DATA_4 :
					{
						*buffArr = realTimeDataReferenceInfoArray;

						if (parserMap == PM_REALTIME_DATA_3)
							return COUNTOF_REALTIME_DATA_3;

						else
							return realTimeDataReferenceInfoArrayElCnt;

						break;
					}

					case PM_GET_ANGLES :
						*buffArr = getAnglesReferenceInfoArray;
						return getAnglesReferenceInfoArrayElCnt;
						break;

					case PM_GET_ANGLES_EXT :
						*buffArr = getAnglesExtReferenceInfoArray;
						return getAnglesExtReferenceInfoArrayElCnt;
						break;

				#endif

				#if (SBGC_SERVICE_MODULE)

					case PM_BOARD_INFO :
						*buffArr = boardInfoReferenceInfoArray;
						return boardInfoReferenceInfoArrayElCnt;
						break;

					case PM_BOARD_INFO_3 :
						*buffArr = boardInfo3_ReferenceInfoArray;
						return boardInfo3_ReferenceInfoArrayElCnt;
						break;

					case PM_AUTO_PID :
						*buffArr = autoPID_ReferenceInfoArray;
						return autoPID_ReferenceInfoArrayElCnt;
						break;

					case PM_AUTO_PID_2 :
						*buffArr = autoPID2_ReferenceInfoArray;
						return autoPID2_ReferenceInfoArrayElCnt;
						break;

					case PM_AUTO_PID_STATE :
						*buffArr = autoPID_StateReferenceInfoArray;
						return autoPID_StateReferenceInfoArrayElCnt;
						break;

					case PM_STATE_VARS :
						*buffArr = stateVarsReferenceInfoArray;
						return stateVarsReferenceInfoArrayElCnt;
						break;

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
	 *	@param	*generalSBGC - serial connection descriptor
	 *	@param 	*structure - command structure where finding is
	  *	@param	parserMap - data type required for correct parsing
	 *	@param	num - number of structure element
	 *
	 *	@return	Address of chosen element
	 */
	void *GetStructureElementAddress (GeneralSBGC_t *generalSBGC, const void* structure, ParserMap_t parserMap, ui8 num)
	{
		ui8 *structureTemp = (ui8*)structure;
		ui32 currentAddrOffset = 0;

		const ParameterReferenceInfo_t *parameterReferenceInfo = NULL;
		ui8 parameterReferenceInfoElCnt = AssignStructFromParserMap(&parameterReferenceInfo, parserMap);

		ui8 parameterSize;

		for (ui8 i = 0; i < parameterReferenceInfoElCnt; i++)
		{
			/* Obtain an element type for made correct structure moving */
			parameterSize = ConvertTypeToByteNum(parameterReferenceInfo[i].type);

			if (i == num)
				return (void*)(structureTemp + currentAddrOffset);

			for (ui8 k = 0; k < parameterReferenceInfo[i].length; k++)
				currentAddrOffset += parameterSize;
		}

		return NULL;
	}

#endif


/**	@brief	Common data-endian converting function
 *
 *	@param	*pDestination - where data will be written
 *	@param	*pSource - data origin
 *	@param	size - data size
 *	@param	parserMap - data type required for correct parsing
 *
 *	@return	size of written data
 */
ui8 ConvertWithPM (void *pDestination, const void *pSource, ui8 size, ParserMap_t parserMap)
{
	if (size == 0)
		return 0;

	memcpy(pDestination, pSource, size);
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
	#if (SYS_BIG_ENDIAN)

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

		const ParameterReferenceInfo_t *parameterReferenceInfo = NULL;

		ui8 parameterReferenceInfoElCnt = AssignStructFromParserMap(&parameterReferenceInfo, parserMap);

		ui8 parameterSize;
		ui32 currentAddrOffset = 0;

		for (ui8 i = 0; i < parameterReferenceInfoElCnt; i++)
		{
			parameterSize = ConvertTypeToByteNum(parameterReferenceInfo[i].type)

			for (ui8 k = 0; k < parameterReferenceInfo[i].length; k++)
			{
				switch (parameterSize)
				{
					case 1 :
						currentAddrOffset++;
						break;

					case 2 :
						SwapMemoryContent((structure + currentAddrOffset), (structure + currentAddrOffset + 1));
						currentAddrOffset += 2;
						break;

					case 4 :
						SwapMemoryContent((structure + currentAddrOffset), (structure + currentAddrOffset + 3));
						SwapMemoryContent((structure + currentAddrOffset + 1), (structure + currentAddrOffset + 2));
						currentAddrOffset += 4;
						break;
				}
			}
		}

	#else

		unused_(structure);
		unused_(size);
		unused_(parserMap);

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

	#if (SYS_BIG_ENDIAN)

		for (ui8 i = 0; i < size / 2; i++)
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

	#if (SYS_BIG_ENDIAN)

		for (ui8 i = 0; i < size / 2; i++)
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
void InitCmdWrite (SerialCommand_t *cmd, SBGC_Command_t cmdID)
{
	cmd->commandID = cmdID;
	cmd->payloadSize = 0;
}


/**	@brief	Clear the SerialCommand
 *
 *	@param	*cmd - SerialCommand
 */
void ClearCmd (SerialCommand_t *cmd)
{
	memset(cmd, 0, sizeof(SerialCommand_t));
}
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *												  SBGC Service Functions
 */
/**	@addtogroup	Common_Core
 *	@{
 */
/**	@brief	Sets custom values of library variables for communication
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
 *	@param	*SprintfFunc - driver function to format debug strings
 *	@param	protocolVersion - SBGC32 communication protocol version
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ManualInit (GeneralSBGC_t *generalSBGC, TxFunc_t TxFunc, RxFunc_t RxFunc,
								AvailableBytesFunc_t AvailableBytesFunc, TxDebugFunc_t TxDebugFunc,
								GetTimeFunc_t GetTimeFunc, SprintfFunc_t SprintfFunc,
								SBGC_ProtocolVersion_t protocolVersion)
{
	generalSBGC->TxFunc = TxFunc;
	generalSBGC->RxFunc = RxFunc;
	generalSBGC->AvailableBytesFunc = AvailableBytesFunc;
	generalSBGC->TxDebugFunc = TxDebugFunc;
	generalSBGC->GetTimeFunc = GetTimeFunc;
	generalSBGC->SprintfFunc = SprintfFunc;
	generalSBGC->protocolVersion = protocolVersion;

	generalSBGC->txTimeout = SBGC_TX_WAITING;
	generalSBGC->rxTimeout = SBGC_RX_WAITING;
	generalSBGC->txrxTimeout = SBGC_REQ_WAITING;

	generalSBGC->_txErrorsCount = 0;
	generalSBGC->_rxErrorsCount = 0;

	#if (UNEXP_CMD_BUFFER)

		generalSBGC->_unexpectedCommandsBuffTail = 0;
		generalSBGC->_unexpectedCommandsBuffHead = 0;

	#endif

	generalSBGC->_missedCommandCount = 0;

	/* Startup delay */
	ui32 currentTime = generalSBGC->GetTimeFunc(generalSBGC->Drv);
	while ((generalSBGC->GetTimeFunc(generalSBGC->Drv) - currentTime) < SBGC_STARTUP_DELAY);

	/* Getting board information */
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_BOARD_INFO);
	WriteWord(&cmd, 0);  // cfg = 0

	if (getcommstatus_(CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_BOARD_INFO), "Board Info:")))
	{
		generalSBGC->_boardVersion = cmd.payload[0];
		FromLittleEndian(&generalSBGC->_firmwareVersion, &cmd.payload[1], 2);
	}

	else
	{
		generalSBGC->_boardVersion = 0;
		generalSBGC->_firmwareVersion = 0;
	}

	#if (SBGC_DEBUG_MODE)

		char boardVersionStr [5],
			 firmwareVersionStr [8];

		FormatBoardVersion(generalSBGC, generalSBGC->_boardVersion, boardVersionStr);
		FormatFirmwareVersion(generalSBGC, generalSBGC->_firmwareVersion, firmwareVersionStr);

		PrintMessage(generalSBGC, TEXT_SIZE_(" \n"));
		PrintMessage(generalSBGC, TEXT_SIZE_("******************************\n"));

		if (getcommstatus_(generalSBGC->_parserCurrentStatus))
		{
			PrintMessage(generalSBGC, TEXT_SIZE_("The system is ready to go!\n"));
			PrintMessage(generalSBGC, TEXT_SIZE_((char*)"Board Version: "));
			PrintMessage(generalSBGC, TEXT_SIZE_(boardVersionStr));
			PrintMessage(generalSBGC, TEXT_SIZE_((char*)" \n"));
			PrintMessage(generalSBGC, TEXT_SIZE_((char*)"Firmware Version: "));
			PrintMessage(generalSBGC, TEXT_SIZE_(firmwareVersionStr));
			PrintMessage(generalSBGC, TEXT_SIZE_((char*)" \n"));
			PrintMessage(generalSBGC, TEXT_SIZE_("******************************\n\n"));
		}

		else
		{
			PrintMessage(generalSBGC, TEXT_SIZE_("Communication Error!\n"));
			PrintMessage(generalSBGC, TEXT_SIZE_("******************************\n\n"));
		}

	#endif

	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Sends SerialCommand without data
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	cmdID - SBGC32 command identifier
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_SendEmptyCommand (GeneralSBGC_t *generalSBGC, SBGC_Command_t cmdID)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, cmdID);
	SBGC32_TX(generalSBGC, &cmd);
	return generalSBGC->_parserCurrentStatus;
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
 *	@param	cmdID - identifier of the SerialCommand being confirmed
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CheckConfirmation (GeneralSBGC_t *generalSBGC, SBGC_Command_t cmdID)
{
	#if (SBGC_CONFIRM_CMD)

		SerialCommand_t cmd;
		TxRxStatus_t lastParserStatus;
		ui32 currentTime = generalSBGC->GetTimeFunc(generalSBGC->Drv);

		#if (SBGC_DEBUG_MODE)
			char debugStr [30];
		#endif

		while (1)
		{
			lastParserStatus = SBGC32_FindCommand(generalSBGC, &cmd, CMD_CONFIRM, generalSBGC->rxTimeout);

			if (getcommstatus_(lastParserStatus) &&
				((cmd.commandID == CMD_CONFIRM) && (cmdID == cmd.payload[0])))
			{
				generalSBGC->_confirmationParams.cmdID = ReadByte(&cmd);

				if (cmd.payloadSize == 2)
					generalSBGC->_confirmationParams.cmdData = ReadByte(&cmd);
				else if (cmd.payloadSize == 3)
					generalSBGC->_confirmationParams.cmdData = ReadWord(&cmd);

				#if (SBGC_DEBUG_MODE)

					if (cmd.payloadSize <= 1)
						generalSBGC->SprintfFunc(debugStr, "CMD_CONFIRM #%d\n", generalSBGC->_confirmationParams.cmdID);
					else
						generalSBGC->SprintfFunc(debugStr, "CMD_CONFIRM #%d (%u)\n", generalSBGC->_confirmationParams.cmdID,
																					 generalSBGC->_confirmationParams.cmdData);

					PrintMessage(generalSBGC, debugStr, strlen(debugStr));

				#endif

				generalSBGC->_parserCurrentStatus = lastParserStatus;
				generalSBGC->_confirmationStatus = CONFIRMATION_OK;
				break;
			}

			else if (getcommstatus_(lastParserStatus) && (cmd.commandID == CMD_ERROR))
			{
				generalSBGC->_confirmationParams.errCode = ReadByte(&cmd);

				if (cmd.payloadSize > 1)
					ReadBuff(&cmd, &generalSBGC->_confirmationParams.errData, 4, PM_DEFAULT_8BIT);

				#if (SBGC_DEBUG_MODE)

					generalSBGC->SprintfFunc(debugStr, "CMD_ERROR: #%d (%d)\n", generalSBGC->_confirmationParams.errCode,
																				generalSBGC->_confirmationParams.errData[0]);

					PrintMessage(generalSBGC, debugStr, strlen(debugStr));

				#endif

				generalSBGC->_parserCurrentStatus = lastParserStatus;
				generalSBGC->_confirmationStatus = CONFIRMATION_ERROR;
				break;
			}

			if (generalSBGC->GetTimeFunc(generalSBGC->Drv) - currentTime >= generalSBGC->txrxTimeout)
			{
				#if (SBGC_DEBUG_MODE)
					PrintMessage(generalSBGC, TEXT_SIZE_("CONFIRM_TIMEOUT_ERROR!\n"));
				#endif

				generalSBGC->_parserCurrentStatus = RX_TIMEOUT_ERROR;
				generalSBGC->_confirmationStatus = CONFIRMATION_TIMEOUT;
				break;
			}
		}

	#endif

	return generalSBGC->_parserCurrentStatus;
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
	generalSBGC->_parserCurrentStatus = receiveStatus;

	if (getcommstatus_(generalSBGC->_parserCurrentStatus) == FALSE__)
		generalSBGC->_rxErrorsCount++;

	#if (SBGC_DEBUG_MODE)

		char totalStr [60];
		ui8 pos = 0;

		if (getcommstatus_(generalSBGC->_parserCurrentStatus))
		{
			memcpy(totalStr, TEXT_SIZE_(message));
			pos += strlen(message);
			memcpy(&totalStr[pos], TEXT_SIZE_(" Receive OK!"));
			pos += strlen(" Receive OK!");
			totalStr[pos] = '\n';
			totalStr[pos + 1] = '\0';
		}

		else
		{
			memcpy(totalStr, TEXT_SIZE_(message));
			pos += strlen(message);
			memcpy(&totalStr[pos], TEXT_SIZE_(" Receive Error: "));
			pos += strlen(" Receive Error: ");
			pos += ConvertErrorToString(generalSBGC->_parserCurrentStatus, &totalStr[pos]);
			totalStr[pos] = '\n';
			totalStr[pos + 1] = '\0';
		}

		PrintMessage(generalSBGC, TEXT_SIZE_(totalStr));

	#endif

	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Calculates the checksum for the first version
 *			of the SBGC32 communication protocol
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
	ui8 shiftRegister,
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
				CRC_Register ^= PR2_CRC16_POLYNOM;
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
	if (generalSBGC->TxDebugFunc == NULL)  // Prevent HardFault errors
		return;

	generalSBGC->TxDebugFunc(data, length);
}


/**	@brief	Displays variable
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*pValue - printable variable
 *	@param	*str - debug info string
 *	@param	vType - type of variable
 */
void PrintStructElement (GeneralSBGC_t *generalSBGC, void *pValue, const char *str, VarType_t vType)
{
	char debugStr [50];

	if (!(vType & _FLAG_))
	/* Simple values */
	{
		switch (vType)
		{
			case _UNSIGNED_CHAR_ :
			{
				ui8 dataTemp = *(ui8*)pValue;
				generalSBGC->SprintfFunc(debugStr, "%s %u\n", str, dataTemp);
				break;
			}

			case _UNSIGNED_SHORT_ :
			{
				ui16 dataTemp = *(ui16*)pValue;
				generalSBGC->SprintfFunc(debugStr, "%s %u\n", str, dataTemp);
				break;
			}

			case _UNSIGNED_INT_ :
			{
				ui32 dataTemp = *(ui32*)pValue;

				#ifdef _L32__
					generalSBGC->SprintfFunc(debugStr, "%s %u\n", str, dataTemp);
				#else
					generalSBGC->SprintfFunc(debugStr, "%s %lu\n", str, dataTemp);
				#endif

				break;
			}

			case _SIGNED_CHAR_ :
			{
				i8 dataTemp = *(i8*)pValue;
				generalSBGC->SprintfFunc(debugStr, "%s %i\n", str, dataTemp);
				break;
			}

			case _SIGNED_SHORT_ :
			{
				i16 dataTemp = *(i16*)pValue;
				generalSBGC->SprintfFunc(debugStr, "%s %i\n", str, dataTemp);
				break;
			}

			case _SIGNED_INT_ :
			{
				i32 dataTemp = *(i32*)pValue;

				#ifdef _L32__
					generalSBGC->SprintfFunc(debugStr, "%s %i\n", str, dataTemp);
				#else
					generalSBGC->SprintfFunc(debugStr, "%s %li\n", str, dataTemp);
				#endif

				break;
			}

			case _FLOAT_ :
			{
				float dataTemp = *(float*)pValue;
				generalSBGC->SprintfFunc(debugStr, "%s %.3f\n", str, dataTemp);  // .3f is default. May be changed
				break;
			}

			default :  // Prevents [-Wswitch warning]
				break;
		}
	}

	else
	/* Flags */
    {
		const char zero = '0';
		const char one = '1';

		switch (vType & CLEAN_TYPE_MASK)
		{
			case _UNSIGNED_CHAR_ :
			{
				char flagStr [9];
				ui8 valueTemp = *(ui8*)pValue;

				for (ui8 i = 0; i < 8; i++)
				{
					if (valueTemp & (1 << i))
						memcpy(&flagStr[7 - i], &one, 1);

					else
						memcpy(&flagStr[7 - i], &zero, 1);
				}

				flagStr[8] = '\0';
				generalSBGC->SprintfFunc(debugStr, "%s %s\n", str, flagStr);
				break;
			}

			case _UNSIGNED_SHORT_ :
			{
				char flagStr [17];
				ui16 valueTemp = *(ui16*)pValue;

				for (ui16 i = 0; i < 16; i++)
				{
					if (valueTemp & (1 << i))
						memcpy(&flagStr[15 - i], &one, 1);

					else
						memcpy(&flagStr[15 - i], &zero, 1);
				}

				flagStr[16] = '\0';
				generalSBGC->SprintfFunc(debugStr, "%s %s\n", str, flagStr);
				break;
			}

			case _UNSIGNED_INT_ :
			{
				char flagStr [33];
				ui32 valueTemp = *(ui32*)pValue;

				for (ui32 i = 0; i < 32; i++)
				{
					if (valueTemp & (1 << i))
						memcpy(&flagStr[31 - i], &one, 1);

					else
						memcpy(&flagStr[31 - i], &zero, 1);
				}

				flagStr[32] = '\0';
				generalSBGC->SprintfFunc(debugStr, "%s %s\n", str, flagStr);
				break;
			}
		}
    }

	PrintMessage(generalSBGC, TEXT_SIZE_(debugStr));
}


#if (SBGC_REF_INFO)

	/**	@brief	Prints the Serial API structures entirely
	 *
	 *	@param	*generalSBGC - serial connection descriptor
	 *	@param 	*structure - Serial API command data
	 *	@param	parserMap - data type required for correct parsing
	 */
	void PrintWholeStruct (GeneralSBGC_t *generalSBGC, void *structure, ParserMap_t parserMap)
	{
		ui8 *structureTemp = (ui8*)structure;
		ui32 currentAddrOffset = 0;

		const ParameterReferenceInfo_t *parameterReferenceInfo = NULL;
		ui8 parameterReferenceInfoElCnt = AssignStructFromParserMap(&parameterReferenceInfo, parserMap);

		ui8 parameterSize;

		char debugStr [50];

		for (ui8 i = 0; i < parameterReferenceInfoElCnt; i++)
		{
			/* Obtain an element type for made correct structure moving */
			parameterSize = ConvertTypeToByteNum(parameterReferenceInfo[i].type);

			for (ui8 k = 0; k < parameterReferenceInfo[i].length; k++)
			{
				if (parameterReferenceInfo[i].type != _RESERVED_CHAR_)
				{
					if (parameterReferenceInfo[i].length == 1)
						 memcpy(debugStr, parameterReferenceInfo[i].name, strlen(parameterReferenceInfo[i].name) + 1);

					else  // if (parameterReferenceInfo[i].length > 1)
						generalSBGC->SprintfFunc(debugStr, "%s [%d]", parameterReferenceInfo[i].name, k);

					memcpy(&debugStr[strlen(debugStr)], " =", 3);

					PrintStructElement(generalSBGC, &structureTemp[currentAddrOffset], debugStr, parameterReferenceInfo[i].type);
				}

				currentAddrOffset += parameterSize;
			}
		}
	}

#endif


/**	@brief	Converts the parser status to a string
 *
 *	@param	txRxStatus - last status from communication operation
 *	@param	*str - writable buffer
 *
 *	@return	Length of a writable string
 */
ui8 ConvertErrorToString (TxRxStatus_t txRxStatus, char *str)
{
	switch (txRxStatus)
	{
		case TX_RX_OK :
			memcpy(str, TEXT_SIZE_(nameof_(TX_RX_OK)));
			return strlen(nameof_(TX_RX_OK));

					case RX_BUFFERED_COMMAND :
						memcpy(str, TEXT_SIZE_(nameof_(RX_BUFFERED_COMMAND)));
						return strlen(nameof_(RX_BUFFERED_COMMAND));

		case RX_START_PARSE :
			memcpy(str, TEXT_SIZE_(nameof_(RX_START_PARSE)));
			return strlen(nameof_(RX_START_PARSE));

					case RX_EMPTY_BUFF_ERROR :
						memcpy(str, TEXT_SIZE_(nameof_(RX_EMPTY_BUFF_ERROR)));
						return strlen(nameof_(RX_EMPTY_BUFF_ERROR));

		case RX_BUFFER_REALTIME_ERROR :
			memcpy(str, TEXT_SIZE_(nameof_(RX_BUFFER_REALTIME_ERROR)));
			return strlen(nameof_(RX_BUFFER_REALTIME_ERROR));

					case RX_HEADER_CHECKSUM_ERROR :
						memcpy(str, TEXT_SIZE_(nameof_(RX_HEADER_CHECKSUM_ERROR)));
						return strlen(nameof_(RX_HEADER_CHECKSUM_ERROR));

		case RX_PAYLOAD_CHECKSUM_ERROR :
			memcpy(str, TEXT_SIZE_(nameof_(RX_PAYLOAD_CHECKSUM_ERROR)));
			return strlen(nameof_(RX_PAYLOAD_CHECKSUM_ERROR));

					case RX_BUFFER_OVERFLOW_ERROR :
						memcpy(str, TEXT_SIZE_(nameof_(RX_BUFFER_OVERFLOW_ERROR)));
						return strlen(nameof_(RX_BUFFER_OVERFLOW_ERROR));

		case RX_TIMEOUT_ERROR :
			memcpy(str, TEXT_SIZE_(nameof_(RX_TIMEOUT_ERROR)));
			return strlen(nameof_(RX_TIMEOUT_ERROR));

					case TX_BUFFER_OVERFLOW_ERROR :
						memcpy(str, TEXT_SIZE_(nameof_(TX_BUFFER_OVERFLOW_ERROR)));
						return strlen(nameof_(TX_BUFFER_OVERFLOW_ERROR));

		case NOT_SUPPORTED_BY_FIRMWARE :
			memcpy(str, TEXT_SIZE_(nameof_(NOT_SUPPORTED_BY_FIRMWARE)));
			return strlen(nameof_(NOT_SUPPORTED_BY_FIRMWARE));
	}

	return 0;
}
/**	@}
 */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
