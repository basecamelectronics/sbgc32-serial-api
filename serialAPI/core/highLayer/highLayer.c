/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.0
 *
 *	@file		highLayer.c
 *
 *	@brief		Source file of the core high-layer communication
 *	____________________________________________________________________
 *
 *	@attention	<h3><center>
 *				Copyright © 2024 BaseCam Electronics™.<br>
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
/* Serial command needs to call internal event anyway. Hidden system part of SerialCommandParam_t */
#define		SCParam_EVENT_ANYWAY	0x40

/* Serial command waits data receive operation. Hidden system part of SerialCommandParam_t */
#define		SCParam_RX				0x80

/* Main board information(-3) field offsets */
#define		BI_BOARD_VER_OFFSET		0
#define		BI_FRW_VER_OFFSET		1U
#define		BI_BOARD_FTR_OFFSET		4U
#define		BI_BOARD_FTR_E_OFFSET	11U
#define		BI_BASE_FRW_VER_OFFSET	16U

#define		BI3_BOARD_FTR_E2_OFFSET	52U
#define		BI3_ADJ_VAR_NUM_OFFSET	58U


/* Borrowed Functions  -------------------------------------------------
 */
extern void PrivateSerialAPI_LinkLowLayer (sbgcGeneral_t *gSBGC);
extern void PrivateSerialAPI_LinkConverter (sbgcGeneral_t *gSBGC);

#if (SBGC_USES_LOGS)
	extern void PrivateSerialAPI_LinkDebug (sbgcGeneral_t *gSBGC);
#endif

extern void PrivateSerialAPI_LinkCommandBuild (sbgcGeneral_t *gSBGC);


/**	@addtogroup	High_Layer
 *	@{
 */
#if (SBGC_USES_REF_INFO)

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *					Big Endian Mapping and Reference Info Structures
	 */
	/** @brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t AHRS_DebugInfoReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Main IMU Ref Src",			sbgcUCHAR						),  // 0
		PARAM_BLOCK_(	"Frame IMU Ref Src",		sbgcUCHAR						),  // 1
		PARAM_BLOCK_(	"Main IMU Z Ref Err",		sbgcUCHAR						),  // 2
		PARAM_BLOCK_(	"Main IMU H Ref Err",		sbgcUCHAR						),  // 3
		PARAM_BLOCK_(	"Frame IMU Z Ref Err",		sbgcUCHAR						),  // 4
		PARAM_BLOCK_(	"Frame IMU H Ref Err",		sbgcUCHAR						),  // 5
		PARAM_BLOCK_(	"Ext IMU Status",			sbgcUCHAR						),  // 6
		PARAM_BLOCK_(	"Ext IMU Packets Received Cnt",
													sbgcUSHORT						),  // 7
		PARAM_BLOCK_(	"Ext IMU Parse Err Cnt",	sbgcUSHORT						),  // 8
		PARAM_BLOCK_(	"Ext Corr H Ref",			sbgcUCHAR						),  // 9
		PARAM_BLOCK_(	"Ext Corr Z Ref",			sbgcUCHAR						),  // 10
		PARAMS_BLOCK_(	"Reserved",					sbgcRCHAR,					13	),  // 11

	};

	const ui8 AHRS_DebugInfoReferenceInfoArrayElCnt = countof_(AHRS_DebugInfoReferenceInfoArray);


	/** @brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t motor4_ControlReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"FF Speed",					sbgcSHORT						),  // 0
		PARAM_BLOCK_(	"Angle Error",				sbgcSHORT						),  // 1
		PARAM_BLOCK_(	"PID Out",					sbgcFLOAT						),  // 2

	};

	const ui8 motor4_ControlReferenceInfoArrayElCnt = countof_(motor4_ControlReferenceInfoArray);

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *											Service Executable Functions
 */
#if (SBGC_USES_TOKENS)

	/**	@brief	Returns commands' index by token
	 *
	 *	@note	Private function
	 *
	 *	@param	*gSBGC - serial connection descriptor
	 *	@param	commandToken - Tx + Rx command IDs
	 *
	 *	@return	Complex index in the next format:
	 *			0-7 bits - Tx lowest 8-bit | 8-15 bits - Rx lowest 8-bit
	 */
	static ui16 SerialAPI_FindCommandsByToken (sbgcGeneral_t *gSBGC, sbgcCommandToken_t commandToken)
	{
		if (commandToken == SBGC_EMPTY_TOKEN) return SBGC_EMPTY_TOKEN;

		ui16 complexIndex = 0;
		ui8 txCmdID = commandToken & 0x00FF;
		ui8 rxCmdID = commandToken >> 8;

		sbgcBoolean_t needTx = sbgcFALSE, needRx = sbgcFALSE;

		if (txCmdID)
			needTx = sbgcTRUE;

		if (rxCmdID)
			needRx = sbgcTRUE;

		for (ui8 i = 0; i < gSBGC->_api->commandNumber; i++)
		{
			if (((gSBGC->_api->commandBuff[i]._id & 0x000000FF) == (ui32)txCmdID) &&
				(!(gSBGC->_api->commandBuff[i].parameters & SCParam_RX)))
			{
				complexIndex |= (i & 0x00FF);
				txCmdID = 0;
			}

			else if ((gSBGC->_api->commandBuff[i]._id & 0x000000FF) == (ui32)rxCmdID &&
					 (gSBGC->_api->commandBuff[i].parameters & SCParam_RX))
			{
				complexIndex |= ((i << 8) & 0xFF00);
				rxCmdID = 0;
			}
		}

		if ((needTx && txCmdID) && (needRx && rxCmdID))
			complexIndex = SBGC_EMPTY_TOKEN;

		return complexIndex;
	}

#endif


/**	@brief	Deletes completed serial command
 *			from the Tx buffer
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*serialCommand - pointer to command
 */
static void SerialAPI_DeleteSentCommand (sbgcGeneral_t *gSBGC, serialAPI_Command_t *serialCommand)
{
	if (serialCommand->_payloadSize == 0)
		return;

	ui16 buffPointer = (ui16)(serialCommand->_payload - gSBGC->_api->txCommandBuff);
	ui16 shiftSize = calcFreeSpaceFIFO(gSBGC->_api->txCommandBuffHead, buffPointer, SBGC_TX_BUFF_TOTAL_SIZE);
	shiftSize = (shiftSize == SBGC_TX_BUFF_TOTAL_SIZE) ? 0 : shiftSize;

	if (buffPointer != gSBGC->_api->txCommandBuffTail)
	/* This command isn't first */
	{
		if (((buffPointer + serialCommand->_payloadSize) & SBGC_TX_BUFF_SIZE_MASK) == gSBGC->_api->txCommandBuffHead)
		/* This command is latest */
		{
			gSBGC->_api->txCommandBuffHead -= serialCommand->_payloadSize;
			return;
		}

		/* This command is between other commands */
		for (ui16 i = 0; i < shiftSize; i++)
		/* Shifting */
			gSBGC->_api->txCommandBuff[((buffPointer + i) & SBGC_TX_BUFF_SIZE_MASK)] =
					gSBGC->_api->txCommandBuff[((buffPointer + serialCommand->_payloadSize + i) & SBGC_TX_BUFF_SIZE_MASK)];

		/* Shift head after buffer shifting */
		gSBGC->_api->txCommandBuffHead -= serialCommand->_payloadSize;
	}

	else
	/* This command is first */
		gSBGC->_api->txCommandBuffTail += serialCommand->_payloadSize;
}


/**	@brief	Saves received serial command
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	cmdID - ID part of serial command
 *	@param	payloadSize - size part of serial command
 *	@param	*payload - pointer to payload part of serial command
 */
static void SerialAPI_SaveReceivedCommand (sbgcGeneral_t *gSBGC, serialAPI_CommandID_t cmdID, ui8 payloadSize, ui8 const *payload)
{
	if ((calcFreeSpaceFIFO(gSBGC->_api->rxCommandBuffTail, gSBGC->_api->rxCommandBuffHead, SBGC_RX_BUFF_TOTAL_SIZE) < (payloadSize + 2)) &&
		(gSBGC->_api->rxCommandBuffHead != gSBGC->_api->rxCommandBuffTail))
	{
		#if (SBGC_RX_CMD_OLD_PRIOR)
			/* Exit to save old serial commands */
			gSBGC->_lastSerialCommandStatus = serialAPI_RX_BUFFER_OVERFLOW_ERROR;
			return;

		#else

			/* It's necessary to clean the space for a new serial command */
			while ((calcFreeSpaceFIFO(gSBGC->_api->rxCommandBuffTail, gSBGC->_api->rxCommandBuffHead, SBGC_RX_BUFF_TOTAL_SIZE) < (payloadSize + 2)))
				gSBGC->_api->rxCommandBuffTail += gSBGC->_api->rxCommandBuff[(gSBGC->_api->rxCommandBuffTail + 1) & SBGC_RX_BUFF_SIZE_MASK] + 2;

			gSBGC->_api->rxCommandBuffCurP = gSBGC->_api->rxCommandBuffTail;

		#endif
	}

	gSBGC->_api->rxCommandBuff[gSBGC->_api->rxCommandBuffHead++] = cmdID;
	gSBGC->_api->rxCommandBuff[gSBGC->_api->rxCommandBuffHead++] = payloadSize;

	for (ui16 i = 0; i < payloadSize; i++)
		gSBGC->_api->rxCommandBuff[gSBGC->_api->rxCommandBuffHead++] = payload[i];
}


/**	@brief	Reads handled serial command
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*serialCommand - pointer to command
 */
static ui8 SerialAPI_ReadReceivedCommand (sbgcGeneral_t *gSBGC, serialAPI_Command_t *serialCommand)
{
	serialCommand->_commandID = gSBGC->_api->rxCommandBuff[gSBGC->_api->rxCommandBuffCurP++];

	ui8 payloadSize = gSBGC->_api->rxCommandBuff[gSBGC->_api->rxCommandBuffCurP++];

	serialCommand->_payload = &gSBGC->_api->rxCommandBuff[gSBGC->_api->rxCommandBuffCurP];
	gSBGC->_api->rxCommandBuffCurP += payloadSize;

	return payloadSize;
}


/**	@brief	Deletes completed serial command
 *			from the Rx buffer
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*payload - pointer to command's payload
 */
static void SerialAPI_DeleteReceivedCommand (sbgcGeneral_t *gSBGC, ui8 const *payload)
{
	if (payload == NULL)
		return;

	/* Note: gSBGC->_api->rxCommandBuffCurP aren't available to read here */

	ui16 buffPointer = (((((uintptr_t)payload) - 2) & SBGC_RX_BUFF_SIZE_MASK) - (uintptr_t)gSBGC->_api->rxCommandBuff) & SBGC_RX_BUFF_SIZE_MASK;
	ui8 cmdSize = gSBGC->_api->rxCommandBuff[((buffPointer + 1) & SBGC_RX_BUFF_SIZE_MASK)] + 2;
	ui16 shiftSize = calcFreeSpaceFIFO(gSBGC->_api->rxCommandBuffHead, (buffPointer + cmdSize) & SBGC_RX_BUFF_SIZE_MASK,
									   SBGC_RX_BUFF_TOTAL_SIZE);
	shiftSize = (shiftSize == SBGC_RX_BUFF_TOTAL_SIZE) ? 0 : shiftSize;

	if (buffPointer != gSBGC->_api->rxCommandBuffTail)
	/* This command isn't first */
	{
		if (((buffPointer + cmdSize) & SBGC_RX_BUFF_SIZE_MASK) == gSBGC->_api->rxCommandBuffHead)
		/* This command is latest */
		{
			gSBGC->_api->rxCommandBuffHead -= cmdSize;

			/* Prepare the parser for next reading */
			gSBGC->_api->rxCommandBuffCurP = gSBGC->_api->rxCommandBuffTail;
			return;
		}

		/* This command is between other commands */
		for (ui16 i = 0; i < shiftSize; i++)
		/* Shifting */
			gSBGC->_api->rxCommandBuff[((buffPointer + i) & SBGC_RX_BUFF_SIZE_MASK)] =
					gSBGC->_api->rxCommandBuff[((buffPointer + cmdSize + i) & SBGC_RX_BUFF_SIZE_MASK)];

		/* Shift head after buffer shifting */
		gSBGC->_api->rxCommandBuffHead -= cmdSize;
	}

	else
	/* This command is first */
		gSBGC->_api->rxCommandBuffTail += cmdSize;  // Shift head pointer

	/* Prepare the parser for next reading */
	gSBGC->_api->rxCommandBuffCurP = gSBGC->_api->rxCommandBuffTail;
}


/**	@brief	Deletes completed serial command
 *			from the main commands buffer
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	index - command sequence number
 */
static void SerialAPI_DeleteCommand (sbgcGeneral_t *gSBGC, ui8 index)
{
	if ((index >= gSBGC->_api->commandNumber) || (gSBGC->_api->commandNumber == 0))
		return;

	if (gSBGC->_api->commandBuff[index]._state != SCState_FORMING)
	/* A command was in runtime */
	{
		for (int i = 0; i < (gSBGC->_api->commandNumber - index - 1); i++)
			memcpy(&gSBGC->_api->commandBuff[index + i], &gSBGC->_api->commandBuff[index + i + 1], sizeof(serialAPI_Command_t));

		gSBGC->_api->commandNumber--;
		gSBGC->_api->commandNumber = constrain_(gSBGC->_api->commandNumber, 0, SBGC_MAX_COMMAND_NUM);
	}

	else
	/* A command cannot continue to exist cause a daughter command doesn't fit to the command buffer */
	{
		for (int i = 0; i < (gSBGC->_api->commandNumber - index - 1); i++)
			memcpy(&gSBGC->_api->commandBuff[index + i], &gSBGC->_api->commandBuff[index + i + 1], sizeof(serialAPI_Command_t));
	}

	serialAPI_CurCmd_ = NULL;
}


/**	@brief	Finds serial command from general queue by its number
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	ID - serialAPI_Command_t.ID
 *
 *	@return Pointer to found serial command
 */
static serialAPI_Command_t *SerialAPI_FindCommandByID (sbgcGeneral_t *gSBGC, ui32 ID)
{
	for (ui8 i = 0; i < gSBGC->_api->commandNumber; i++)
		if (gSBGC->_api->commandBuff[i]._id == ID)
			return &gSBGC->_api->commandBuff[i];

	return NULL;
}


/**	@brief	Finds serial command from general queue by its
 *			API identifier
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	commandID - SBGC32 command identifier
 *
 *	@return Pointer to found serial command
 */
static serialAPI_Command_t *SerialAPI_FindCommandByCommandID (sbgcGeneral_t *gSBGC, serialAPI_CommandID_t commandID)
{
	for (ui8 i = 0; i < gSBGC->_api->commandNumber; i++)
		if (gSBGC->_api->commandBuff[i]._commandID == commandID)
			return &gSBGC->_api->commandBuff[i];

	return NULL;
}


/**	@brief	Gives the location of a serial command in the
 *			main command buffer
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*serialCommand - pointer to serial command
 *
 *	@return Serial command's index
 */
static ui8 SerialAPI_GetSerialCommandIndex (sbgcGeneral_t *gSBGC, serialAPI_Command_t *serialCommand)
{
	return (((uintptr_t)serialCommand / sizeof(serialAPI_Command_t)) - ((uintptr_t)gSBGC->_api->commandBuff) / sizeof(serialAPI_Command_t));
}


#if (SBGC_ADJVAR_MODULE)

	/**	@brief	Checks the presence of an adjustable variable
	 *			in the current firmware version
	 *
	 *	@note	Private function
	 *
	 *	@param	*gSBGC - serial connection descriptor
	 */
	static void SerialAPI_DetermineAdjVarsNumber (sbgcGeneral_t *gSBGC)
	{
		if (gSBGC->_api->baseFirmwareVersion < 2687) gSBGC->_api->adjVarsNumber = 50;
		if (gSBGC->_api->baseFirmwareVersion < 2688) gSBGC->_api->adjVarsNumber = 51;
		if (gSBGC->_api->baseFirmwareVersion < 2689) gSBGC->_api->adjVarsNumber = 57;
		if (gSBGC->_api->baseFirmwareVersion < 2693) gSBGC->_api->adjVarsNumber = 61;
		if (gSBGC->_api->baseFirmwareVersion < 2704) gSBGC->_api->adjVarsNumber = 65;
		if (gSBGC->_api->baseFirmwareVersion < 2720) gSBGC->_api->adjVarsNumber = 66;
		if (gSBGC->_api->baseFirmwareVersion < 2730) gSBGC->_api->adjVarsNumber = 76;
	}

#endif


/**	@brief	Sends a serial command without payload
 *
 *	@note	Quasi-private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	cmdID - SBGC32 command identifier
 *
 *	@return	Communication status
 */
sbgcCommandStatus_t SBGC32_SendEmptyCommand (sbgcGeneral_t *gSBGC, serialAPI_CommandID_t cmdID
											 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertParam(cmdID, CMD_BOARD_INFO_3, CMD_ERROR)

	gSBGC->_api->startWrite(gSBGC, cmdID SBGC_ADVANCED_ARGS__);
	gSBGC->_api->finishWrite(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Sends a serial command from the buffer
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*serialCommand - pointer to completed structure
 *			ready to be transmitted
 */
static void SBGC32_SendCommand (sbgcGeneral_t *gSBGC, serialAPI_Command_t *serialCommand)
{
	#if (SBGC_USES_BLOCKING_MODE)

		serialCommand->_state = SCState_PROCESSING;
		serialCommand->timeout = SBGC_DEFAULT_TIMEOUT;

		/* Transmit */
		gSBGC->_ll->tx(gSBGC);

		if (gSBGC->_lastSerialCommandStatus == serialAPI_TX_RX_OK)
			serialCommand->_state = SCState_PROCESSED;

		else
		{
			serialCommand->_state = SCState_ERROR;
			gSBGC->_api->txErrorsCount++;
		}

	#else

		if (serialCommand->_state == SCState_PREPARED)
		/* Launch the command */
		{
			serialCommand->_state = SCState_PROCESSING;
			serialCommand->_timestamp = serialAPI_GetTick();
		}

		/* Transmit */
		gSBGC->_ll->tx(gSBGC);

		if (gSBGC->_lastSerialCommandStatus == serialAPI_TX_RX_OK)
			serialCommand->_state = SCState_PROCESSED;

		else if ((serialAPI_GetTick() - serialCommand->_timestamp) > serialCommand->timeout)
		/* Command's time is over */
		{
			if (serialCommand->_state & SCParam_RETAIN)
				serialCommand->_state = SCState_RELOAD;

			else
			{
				serialCommand->_state = SCState_ERROR;
				gSBGC->_api->txErrorsCount++;
			}
		}

	#endif
}


/**	@brief	Filters received serial commands
 *
 *	@note	Private function
 *
 *	@param	*serialCommand - pointer to command
 *	@param	payloadSize - size of received command
 *
 *	@return	Whether the command will be accepted or not
 */
static sbgcBoolean_t SerialAPI_FilterSerialCommand (serialAPI_Command_t *serialCommand, ui8 payloadSize)
{
	/* Check the expected payload size */
	if ((serialCommand->_payloadSize != 0) && (serialCommand->_payloadSize != payloadSize))
		return sbgcFALSE;

	serialCommand->_payloadSize = payloadSize;

	switch (serialCommand->_commandID)
	{
		case CMD_CONFIRM :
		case CMD_ERROR :
		{
			#if (SBGC_NEED_CONFIRM_CMD)

				if (serialCommand->_pDestination)
				{
					sbgcConfirm_t *confirm = (sbgcConfirm_t*)serialCommand->_pDestination;

					if (confirm->commandID != serialCommand->_payload[0])
						return sbgcFALSE;
				}

				/* else this is a confirmation from the SBGC32_ExpectCommand function */

				break;

			#else
				break;
			#endif
		}

		default :
			break;
	}

	return sbgcTRUE;
}


/**	@brief	Finds a serial command in the buffer
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*serialCommand - pointer to a structure, into which
 *			the found serial command will be overwritten
 *	@param	cmdID - SBGC32 command identifier
 */
static void SBGC32_FindCommand (sbgcGeneral_t *gSBGC, serialAPI_Command_t *serialCommand, serialAPI_CommandID_t cmdID)
{
	serialAPI_CommandID_t cmdID_Temp;

	gSBGC->_lastSerialCommandStatus = serialAPI_TX_RX_OK;
	/* It's always sbgcCOMMAND_OK until in the rxCommandBuff isn't empty */

	#if (SBGC_USES_BLOCKING_MODE)

		sbgcTicks_t launchTime = serialAPI_GetTick();

		serialCommand->_state = SCState_PROCESSING;
		serialCommand->timeout = SBGC_DEFAULT_TIMEOUT;

	#else

		if (serialCommand->_state == SCState_PREPARED)
		{
			serialCommand->_timestamp = serialAPI_GetTick();
			serialCommand->_state = SCState_PROCESSING;
		}

	#endif

	gSBGC->_api->rxCommandBuffCurP = gSBGC->_api->rxCommandBuffTail;

	/* Start high-layer parsing */
	while (1)
	{
		if (gSBGC->_api->rxCommandBuffCurP == gSBGC->_api->rxCommandBuffHead)
		/* Read a new data if the Rx buffer is empty or there wasn't a needed command there */
			gSBGC->_ll->rx(gSBGC);

		cmdID_Temp = gSBGC->_api->rxCommandBuff[gSBGC->_api->rxCommandBuffCurP];

		/* Handling */
		if (gSBGC->_lastSerialCommandStatus == serialAPI_TX_RX_OK)
		/* We have some serial command */
		{
			if ((cmdID == sbgcANY_SERIAL_COMMAND) ||
				(cmdID_Temp == cmdID) ||
				(((cmdID == CMD_CONFIRM) || (cmdID == CMD_CAN_DEVICE_SCAN)) && (cmdID_Temp == CMD_ERROR)))
			/* A correct command has parsed (or a CMD_ERROR have come while we wait a CMD_CONFIRM or a CMD_CAN_DEVICE_SCAN) */
			{
				ui8 payloadSize = SerialAPI_ReadReceivedCommand(gSBGC, serialCommand);

				if ((cmdID == sbgcANY_SERIAL_COMMAND) ||
					SerialAPI_FilterSerialCommand(serialCommand, payloadSize))
				/* Search command has required advanced searching patterns, or they aren't requested.
				   Or pass next if receiving any command */
				{
					serialCommand->_payloadSize = payloadSize;
					serialCommand->_state = SCState_PROCESSED;

					/* Command was received fine, exit */
					return;
				}

				/* Else search command doesn't correspond advanced searching patterns. Go next */
			}

			else if (cmdID_Temp != cmdID)
			/* Has wrong command parsed or  */
				gSBGC->_api->rxCommandBuffCurP += gSBGC->_api->rxCommandBuff[(gSBGC->_api->rxCommandBuffCurP + 1) & SBGC_RX_BUFF_SIZE_MASK] + 2;
		}

		/* Timeout and buffer ending checking */
		#if (SBGC_NON_BLOCKING_MODE)

			if ((gSBGC->_api->rxCommandBuffCurP == gSBGC->_api->rxCommandBuffHead) &&
				(gSBGC->_lastSerialCommandStatus != serialAPI_TX_RX_OK))
			/* There wasn't a needed command anywhere */

		#else

			if (((gSBGC->_api->rxCommandBuffCurP == gSBGC->_api->rxCommandBuffHead) &&
				(gSBGC->_lastSerialCommandStatus != serialAPI_TX_RX_OK)) &&
				((serialAPI_GetTick() - launchTime) >= serialCommand->timeout))
			/* There wasn't a needed command anywhere and command processing time is over */

		#endif

			{
				/* Return rxCommandBuffCurP to the buffer start */
				gSBGC->_api->rxCommandBuffCurP = gSBGC->_api->rxCommandBuffTail;

				#if (SBGC_USES_OS_SUPPORT == sbgcOFF)

					#if (SBGC_NON_BLOCKING_MODE)

						if ((serialAPI_GetTick() - serialCommand->_timestamp) > serialCommand->timeout)
						{
							if (serialCommand->parameters & SCParam_RETAIN)
								serialCommand->_state = SCState_RELOAD;

							else
							{
								serialCommand->_state = SCState_ERROR;
								gSBGC->_api->rxErrorsCount++;
							}
						}

					#else

						serialCommand->_state = SCState_ERROR;
						gSBGC->_api->rxErrorsCount++;

					#endif

					if (gSBGC->_lastSerialCommandStatus == serialAPI_TX_RX_OK)
					/* For example a case when a stream clogs serialAPI */
						gSBGC->_lastSerialCommandStatus = serialAPI_RX_NOT_FOUND_ERROR;

				#endif

				return;
			}
	}
}


#if (SBGC_NON_BLOCKING_MODE)

	/**	@brief	Sorts subscribers by priority and timings
	 *
	 *	@note	Private function
	 *
	 *	@param	*gSBGC - serial connection descriptor
	 */
	static void SerialAPI_SortCommands (sbgcGeneral_t *gSBGC)
	{
		if (gSBGC->_api->commandSortFlag) return;

		serialAPI_Command_t cmdTemp;
		ui16 commandIndexTemp;
		ui8 commandPriorityTemp;
		ui32 commandID_Temp;

		for (ui8 i = 0; i < gSBGC->_api->commandNumber; i++)
		{
			commandIndexTemp = 0;
			commandPriorityTemp = 0;
			commandID_Temp = 0xFFFFFFFFU;

			for (ui8 k = i; k < gSBGC->_api->commandNumber; k++)
			{
				/* Sorting by priority, direction and index */
				if ((gSBGC->_api->commandBuff[k].priority > commandPriorityTemp) ||
					/* or there are two same-priority command, but it's necessary to up TX command under RX command */
					((gSBGC->_api->commandBuff[k].priority == commandPriorityTemp) &&
					((gSBGC->_api->commandBuff[commandIndexTemp].parameters & SCParam_RX) &&
					(!(gSBGC->_api->commandBuff[k].parameters & SCParam_RX)))) ||
					/* or two commands with similar priority and direction but they have different id (number) */
					((gSBGC->_api->commandBuff[k].priority == commandPriorityTemp) &&
					((gSBGC->_api->commandBuff[commandIndexTemp].parameters & SCParam_RX) == (gSBGC->_api->commandBuff[k].parameters & SCParam_RX)) &&
					(gSBGC->_api->commandBuff[k]._id < commandID_Temp)))
				{
					commandPriorityTemp = gSBGC->_api->commandBuff[k].priority;
					commandID_Temp = gSBGC->_api->commandBuff[k]._id;

					commandIndexTemp = k;
				}
			}

			if ((commandIndexTemp != i) && (commandPriorityTemp > 0))
			{
				memcpy(&cmdTemp, &gSBGC->_api->commandBuff[i], sizeof(serialAPI_Command_t));
				memcpy(&gSBGC->_api->commandBuff[i], &gSBGC->_api->commandBuff[commandIndexTemp], sizeof(serialAPI_Command_t));
				memcpy(&gSBGC->_api->commandBuff[commandIndexTemp], &cmdTemp, sizeof(serialAPI_Command_t));
			}
		}

		gSBGC->_api->commandSortFlag = sbgcTRUE;
	}

#endif


/**	@brief	Process serial command on high level
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	index - command sequence number
 *
 *	@return	True if command wasn't deleted, false otherwise
 */
static sbgcBoolean_t SerialAPI_ProcessCommand (sbgcGeneral_t *gSBGC, ui8 index)
{
	sbgcBoolean_t commandExist = sbgcTRUE;

	serialAPI_CurCmd_ = &gSBGC->_api->commandBuff[index];

	sbgcBoolean_t thisCommandRx = (serialAPI_CurCmd_->parameters & SCParam_RX) ? sbgcTRUE : sbgcFALSE;

	if (thisCommandRx)
	{
		/* Don't find command yet if the library uses OS functional */
		#if (SBGC_USES_OS_SUPPORT == sbgcOFF)
			SBGC32_FindCommand(gSBGC, serialAPI_CurCmd_, serialAPI_CurCmd_->_commandID);
		#endif
	}

	else
		SBGC32_SendCommand(gSBGC, serialAPI_CurCmd_);

	/* After physical operations... */
	switch (serialAPI_CurCmd_->_state)
	{
		case SCState_PROCESSED :
		case SCState_ERROR :
		{
			/* Finish the command */
			#if (SBGC_USES_LOGS)

				/* Print log */
				gSBGC->_api->writeLog(gSBGC, serialAPI_CurCmd_);

			#endif

			/* It's necessary to save payload pointer cause the next actions may shift it */
			void *payloadTemp = serialAPI_CurCmd_->_payload;

			if ((serialAPI_CurCmd_->_state == SCState_PROCESSED) || (serialAPI_CurCmd_->parameters & SCParam_EVENT_ANYWAY))
			/* Execute SerialAPI event */
			{
				if (serialAPI_CurCmd_->_serialAPI_Event)
					((serialAPI_Event_t)serialAPI_CurCmd_->_serialAPI_Event)(gSBGC);

				else if (thisCommandRx && (serialAPI_CurCmd_->_pDestination != NULL))  // and it don't have an event
				{
					if (serialAPI_CurCmd_->_destinationSize < serialAPI_CurCmd_->_payloadSize)
						SerialAPI_FatalErrorHandler();

					else
						gSBGC->_api->readBuff(gSBGC, serialAPI_CurCmd_->_pDestination, serialAPI_CurCmd_->_payloadSize);
				}

				/* Return payload pointer to the start */
				serialAPI_CurCmd_->_payload = payloadTemp;
			}

			#if (SBGC_USES_CALLBACKS)

				if (((serialAPI_CurCmd_->_state == SCState_PROCESSED) || (serialAPI_CurCmd_->parameters & SCParam_FORCE_CALLBACK)) &&
					serialAPI_CurCmd_->callback)
				/* Pass to user's callback */
				{
					if (serialAPI_CurCmd_->callbackArg == NULL)
					/* If callbackArg is NULL, assign the general object to this */
						serialAPI_CurCmd_->callbackArg = gSBGC;

					((serialAPI_Callback_t)serialAPI_CurCmd_->callback)(serialAPI_CurCmd_->callbackArg);
				}

			#endif

			#if (SBGC_NON_BLOCKING_MODE)

				if (serialAPI_CurCmd_->parameters & SCParam_RETAIN)
				/* Command processed fine. Reload it */
					serialAPI_CurCmd_->_state = SCState_RELOAD;

			#endif

			if (thisCommandRx)
			/* Delete command ID, size and payload from Rx buffer in any case */
				SerialAPI_DeleteReceivedCommand(gSBGC, payloadTemp);

			else
			/* Delete command payload from Tx buffer and command object from main command buffer */
				SerialAPI_DeleteSentCommand(gSBGC, serialAPI_CurCmd_);

			#if (SBGC_USES_OS_SUPPORT)

				/* Don't delete this command if another thread is waiting it */
				if (serialAPI_CurCmd_->parameters & SCParam_FREEZE)
				{
					serialAPI_Suspend()

					/* ... */
					/* Return here from another thread and finish */
				}

			#endif

			if (serialAPI_CurCmd_->_state != SCState_RELOAD)
			{
				commandExist = sbgcFALSE;
				SerialAPI_DeleteCommand(gSBGC, index);
			}

			else
			/* Reload serial command */
				serialAPI_CurCmd_->_state = SCState_PREPARED;

			break;
		}

		case SCState_RELOAD :

			#if (SBGC_USES_LOGS)

				/* Print log */
				gSBGC->_api->writeLog(gSBGC, serialAPI_CurCmd_);

			#endif

			/* Reload serial command */
			serialAPI_CurCmd_->_state = SCState_PREPARED;

			break;

		default :
			break;
	}

	return commandExist;
}


#if (SBGC_USES_OS_SUPPORT || SBGC_USES_DOXYGEN)

	/**	@brief	SerialAPI commands handler function
	 *
	 *	@note	Private function
	 *
	 *	@param	*gSBGC - serial connection descriptor
	 *
	 *	@return	Communication status
	 */
	static sbgcCommandStatus_t SBGC32_ProcessAllCommandsOS (sbgcGeneral_t *gSBGC)
	{
		serialAPI_LockBus()

		serialAPI_Command_t serialCommand = {0};

		SerialAPI_SortCommands(gSBGC);

		/* Transmit */
		for (ui8 i = 0; i < gSBGC->_api->commandNumber;)
		{
			if (!(gSBGC->_api->commandBuff[i].parameters & SCParam_RX))
			{
				SerialAPI_ProcessCommand(gSBGC, i);

				if (gSBGC->_lastSerialCommandStatus != serialAPI_TX_RX_OK)
					gSBGC->_lastCommandStatus = sbgcCOMMAND_TX_ERROR;

				else
					gSBGC->_lastCommandStatus = sbgcCOMMAND_OK;
			}

			else
				i++;
		}

		/* Handle Rx commands */
		for (ui8 i = 0; i < gSBGC->_api->commandNumber;)
		/* Check all commands' lifetime */
		{
			if (gSBGC->_api->commandBuff[i].parameters & SCParam_RX)
			{
				/* Launch a new commands */
				if (gSBGC->_api->commandBuff[i]._state == SCState_PREPARED)
				{
					gSBGC->_api->commandBuff[i]._timestamp = serialAPI_GetTick();
					gSBGC->_api->commandBuff[i]._state = SCState_PROCESSING;
				}

				/* Timeout check for existing commands */
				if (gSBGC->_api->commandBuff[i].timeout < serialAPI_GetTick() - gSBGC->_api->commandBuff[i]._timestamp)
				/* This serial command must be deleted or reloaded */
				{
					if (gSBGC->_api->commandBuff[i].parameters & SCParam_RETAIN)
						gSBGC->_api->commandBuff[i]._state = SCState_RELOAD;

					else
					{
						gSBGC->_api->commandBuff[i]._state = SCState_ERROR;
						gSBGC->_api->rxErrorsCount++;
					}

					/* Logs, events, delete or reload */
					SerialAPI_ProcessCommand(gSBGC, i);

					continue;
				}
			}

			i++;
		}

		/* Count the Rx commands */
		ui8 rxCommandsCount = 0;

		for (ui8 i = 0; i < gSBGC->_api->commandNumber; i++)
			if (gSBGC->_api->commandBuff[i].parameters & SCParam_RX)
				rxCommandsCount++;

		/* Reading */
		while (rxCommandsCount--)
		{
			/* Try to receive any serial command */
			SBGC32_FindCommand(gSBGC, &serialCommand, sbgcANY_SERIAL_COMMAND);

			if (gSBGC->_lastSerialCommandStatus == serialAPI_TX_RX_OK)
			{
				gSBGC->_lastCommandStatus = sbgcCOMMAND_OK;

				/* It's okay, we have some serial command now. Try to find a subscriber to this command */
				for (ui8 i = 0; i < gSBGC->_api->commandNumber;)
				{
					if (gSBGC->_api->commandBuff[i].parameters & SCParam_RX)
					/* This command is Rx */
					{
						if (gSBGC->_api->commandBuff[i]._commandID == serialCommand._commandID)
						/* We got necessary command */
						{
							#if (SBGC_NEED_CONFIRM_CMD)

								if (gSBGC->_api->commandBuff[i]._commandID == CMD_CONFIRM)
								{
									/* Assign destination for the next filter if this command is CMD_CONFIRM */
									serialCommand._pDestination = gSBGC->_api->commandBuff[i]._pDestination;

									/* Add command ID to confirm */
									gSBGC->_api->commandBuff[i]._payload = serialCommand._payload;
								}

							#endif

							if (SerialAPI_FilterSerialCommand(&gSBGC->_api->commandBuff[i], serialCommand._payloadSize))
							/* The command is passed all checks */
							{
								/* Write new serial command */
								gSBGC->_api->commandBuff[i]._payload = serialCommand._payload;
								gSBGC->_api->commandBuff[i]._state = serialCommand._state;

								/* Logs, events and then delete or reload */
								SerialAPI_ProcessCommand(gSBGC, i);

								continue;
							}
						}
					}

					i++;
				}
			}

			else
				gSBGC->_lastCommandStatus = sbgcCOMMAND_RX_ERROR;
		}

		gSBGC->_api->rxCommandBuffTail = gSBGC->_api->rxCommandBuffHead;

		serialAPI_Unlock()

		return gSBGC->_lastCommandStatus;
	}

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														  User Functions
 */
#if (SBGC_USES_TOKENS || SBGC_USES_DOXYGEN)

	/**	@brief	Transmits one serial command by its token
	 *
	 *	@param	*gSBGC - serial connection descriptor
	 *	@param	*commandToken - special object to identify fully
	 *			SerialAPI request from SBGC32_ functions
	 *
	 *	@return	Communication status
	 */
	sbgcCommandStatus_t SBGC32_Transmit (sbgcGeneral_t *gSBGC, sbgcCommandToken_t *commandToken)
	{
		#if (SBGC_NEED_ASSERTS)
			if (commandToken == NULL) return sbgcCOMMAND_PARAM_ASSERT_ERROR;
		#endif

		serialAPI_LockBus()

		sbgcCommandToken_t token = SerialAPI_FindCommandsByToken(gSBGC, *commandToken);
		ui8 txIndex = token;

		if ((token == SBGC_EMPTY_TOKEN) || (txIndex >= gSBGC->_api->commandNumber) ||
			(gSBGC->_api->commandBuff[txIndex].parameters & SCParam_RX))
		{
			serialAPI_Unlock()

			return sbgcCOMMAND_TOKEN_NOT_FOUND;
		}

		/* Send found command */
		if (SerialAPI_ProcessCommand(gSBGC, txIndex) && (gSBGC->_lastSerialCommandStatus != serialAPI_TX_RX_OK))
		/* Serial command still exists */
			gSBGC->_lastCommandStatus = sbgcCOMMAND_PROCESSING;

		else if (gSBGC->_lastSerialCommandStatus == serialAPI_TX_RX_OK)
			gSBGC->_lastCommandStatus = sbgcCOMMAND_OK;

		else
			gSBGC->_lastCommandStatus = sbgcCOMMAND_TX_ERROR;

		serialAPI_Unlock()

		return gSBGC->_lastCommandStatus;
	}


	/**	@brief	Receives one serial command by its token
	 *
	 *	@param	*gSBGC - serial connection descriptor
	 *	@param	*commandToken - special object to identify fully
	 *			SerialAPI request from SBGC32_ functions
	 *
	 *	@return	Communication status
	 */
	sbgcCommandStatus_t SBGC32_Receive (sbgcGeneral_t *gSBGC, sbgcCommandToken_t *commandToken)
	{
		#if (SBGC_NEED_ASSERTS)
			if (commandToken == NULL) return sbgcCOMMAND_PARAM_ASSERT_ERROR;
		#endif

		serialAPI_LockBus()

		sbgcCommandToken_t token = SerialAPI_FindCommandsByToken(gSBGC, *commandToken);
		ui8 rxIndex = (token >> 8) & 0x00FF;

		if ((token == SBGC_EMPTY_TOKEN) || (rxIndex >= gSBGC->_api->commandNumber) ||
			(!(gSBGC->_api->commandBuff[rxIndex].parameters & SCParam_RX)))
		{
			serialAPI_Unlock()

			return sbgcCOMMAND_TOKEN_NOT_FOUND;
		}

		/* Try to read required command */
		if (SerialAPI_ProcessCommand(gSBGC, rxIndex) && (gSBGC->_lastSerialCommandStatus != serialAPI_TX_RX_OK))
		/* Serial command still exists */
			gSBGC->_lastCommandStatus = sbgcCOMMAND_PROCESSING;

		else if (gSBGC->_lastSerialCommandStatus == serialAPI_TX_RX_OK)
			gSBGC->_lastCommandStatus = sbgcCOMMAND_OK;

		else
			gSBGC->_lastSerialCommandStatus = sbgcCOMMAND_RX_ERROR;

		serialAPI_Unlock()

		return gSBGC->_lastCommandStatus;
	}

#endif


#if ((SBGC_NON_BLOCKING_MODE && (SBGC_USES_OS_SUPPORT == sbgcOFF)) || SBGC_USES_DOXYGEN)

	/**	@brief	Transmits all ready serial commands
	 *
	 *	@param	*gSBGC - serial connection descriptor
	 *
	 *	@return	Communication status
	 */
	sbgcCommandStatus_t SBGC32_TransmitAllCommands (sbgcGeneral_t *gSBGC)
	{
		sbgcBoolean_t queueIsEmptyFlag = sbgcTRUE;
		ui8 commandNumber;

		serialAPI_LockBus()

		SerialAPI_SortCommands(gSBGC);

		for (ui8 i = 0; i < gSBGC->_api->commandNumber;)
		{
			if (!(gSBGC->_api->commandBuff[i].parameters & SCParam_RX))
			{
				queueIsEmptyFlag = sbgcFALSE;

				commandNumber = gSBGC->_api->commandNumber;

				SerialAPI_ProcessCommand(gSBGC, i);

				if (gSBGC->_lastSerialCommandStatus != serialAPI_TX_RX_OK)
				{
					gSBGC->_lastCommandStatus = sbgcCOMMAND_TX_ERROR;
					i++;
				}

				else
				{
					gSBGC->_lastCommandStatus = sbgcCOMMAND_OK;

					if (commandNumber == gSBGC->_api->commandNumber)
					/* There was a retained command */
						i++;
				}
			}

			else
				i++;
		}

		serialAPI_Unlock()

		if (queueIsEmptyFlag)
			return sbgcCOMMAND_QUEUE_IS_EMPTY;

		return gSBGC->_lastCommandStatus;
	}


	/**	@brief	Receives all expected serial commands
	 *
	 *	@param	*gSBGC - serial connection descriptor
	 *
	 *	@return	Communication status
	 */
	sbgcCommandStatus_t SBGC32_ReceiveAllCommands (sbgcGeneral_t *gSBGC)
	{
		sbgcBoolean_t queueIsEmptyFlag = sbgcTRUE;
		ui8 commandNumber;

		serialAPI_LockBus()

		SerialAPI_SortCommands(gSBGC);

		for (ui8 i = 0; i < gSBGC->_api->commandNumber;)
		{
			if (gSBGC->_api->commandBuff[i].parameters & SCParam_RX)
			{
				queueIsEmptyFlag = sbgcFALSE;

				commandNumber = gSBGC->_api->commandNumber;

				SerialAPI_ProcessCommand(gSBGC, i);

				if (gSBGC->_lastSerialCommandStatus != serialAPI_TX_RX_OK)
				{
					gSBGC->_lastCommandStatus = sbgcCOMMAND_RX_ERROR;
					i++;
				}

				else
				{
					gSBGC->_lastCommandStatus = sbgcCOMMAND_OK;

					if (commandNumber == gSBGC->_api->commandNumber)
					/* There was a retained command */
						i++;
				}
			}

			else
				i++;
		}

		serialAPI_Unlock()

		if (queueIsEmptyFlag)
			return sbgcCOMMAND_QUEUE_IS_EMPTY;

		return gSBGC->_lastCommandStatus;
	}


	/**	@brief	Transmits and receives all prepared serial commands
	 *
	 *	@param	*gSBGC - serial connection descriptor
	 *
	 *	@return	Communication status
	 */
	sbgcCommandStatus_t SBGC32_ProcessAllCommands (sbgcGeneral_t *gSBGC)
	{
		sbgcBoolean_t queueIsEmptyFlag = sbgcFALSE;

		if (SBGC32_TransmitAllCommands(gSBGC) == sbgcCOMMAND_QUEUE_IS_EMPTY)
			queueIsEmptyFlag = sbgcTRUE;

		if ((SBGC32_ReceiveAllCommands(gSBGC) == sbgcCOMMAND_QUEUE_IS_EMPTY) && queueIsEmptyFlag)
			return sbgcCOMMAND_QUEUE_IS_EMPTY;

		return gSBGC->_lastCommandStatus;
	}

#endif

#if (SBGC_USES_OS_SUPPORT || SBGC_USES_DOXYGEN)

	/**	@brief	SerialAPI commands handler thread
	 *
	 *	@note	Quasi-private function. Don't use it
	 *
	 *	@param	threadArg - pointer to GeneralSBGC_t object
	 *
	 *	@return	No-return function
	 */
	NORETURN__ sbgcThreadRetval_t SBGC32_HandlerThread (sbgcThreadArg_t threadArg)
	{
		sbgcGeneral_t *gSBGC = (sbgcGeneral_t*)threadArg;

		gSBGC->_api->busyFlag = sbgcTRUE;

		while (1)
		{
			/* Handle whole serial buffer */
			SBGC32_ProcessAllCommandsOS(gSBGC);

			if (gSBGC->_api->commandNumber == 0)
			/* Stop SerialAPI handler if there are no commands left */
				serialAPI_Suspend()

			serialAPI_Yield()
		}
	}

#endif


/**	@brief	SerialAPI event
 *
 *	@note	Private function
 *			See @ref SBGC32_SetupLibrary function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostSetupLibrary (sbgcGeneral_t *gSBGC)
{
	/* Read all data manually only */

	if (serialAPI_CurCmd_->_commandID == CMD_BOARD_INFO)
	/* Getting board information */
	{
		if (gSBGC->_lastSerialCommandStatus == serialAPI_TX_RX_OK)
		{
			ui32 boardFeatures;

			/* Don't care about _payload pointer verge cause there is a first command */
			gSBGC->_api->boardVersion = *(serialAPI_CurCmd_->_payload + BI_BOARD_VER_OFFSET);
			gSBGC->_api->fromLE(&gSBGC->_api->firmwareVersion, serialAPI_CurCmd_->_payload + BI_FRW_VER_OFFSET,
								sizeof(gSBGC->_api->firmwareVersion));

			boardFeatures = (((ui32)(*(ui16*)(serialAPI_CurCmd_->_payload + BI_BOARD_FTR_OFFSET))) & 0x0000FFFF) |
					((((ui32)(*(ui16*)(serialAPI_CurCmd_->_payload + BI_BOARD_FTR_E_OFFSET))) << 16) & 0xFFFF0000);

			gSBGC->_api->fromLE(&gSBGC->_api->boardFeatures, (ui8*)(&boardFeatures), sizeof(gSBGC->_api->boardFeatures));

			gSBGC->_api->fromLE(&gSBGC->_api->baseFirmwareVersion, serialAPI_CurCmd_->_payload + BI_BASE_FRW_VER_OFFSET,
								sizeof(gSBGC->_api->baseFirmwareVersion));

			if (gSBGC->_api->baseFirmwareVersion == 0)
			/* Some SBGC32 boards have no this data field */
				gSBGC->_api->baseFirmwareVersion = gSBGC->_api->firmwareVersion;

			return;
		}
	}

	else if (serialAPI_CurCmd_->_commandID == CMD_BOARD_INFO_3)
	/* Getting total adjustable variables number */
	{
		if (gSBGC->_api->firmwareVersion && (gSBGC->_lastSerialCommandStatus == serialAPI_TX_RX_OK))
		{
			gSBGC->_api->fromLE(&gSBGC->_api->boardFeatures2, serialAPI_CurCmd_->_payload + BI3_BOARD_FTR_E2_OFFSET,
								sizeof(gSBGC->_api->boardFeatures2));

			#if (SBGC_ADJVAR_MODULE)

				if (gSBGC->_api->baseFirmwareVersion < 2730)
					SerialAPI_DetermineAdjVarsNumber(gSBGC);

				else
					gSBGC->_api->adjVarsNumber = *(serialAPI_CurCmd_->_payload + BI3_ADJ_VAR_NUM_OFFSET);

			#endif

			#if (SBGC_NEED_DEBUG)

				char boardVersionStr [5],
					 firmwareVersionStr [8];

				ParserSBGC32_FormatBoardVersion(gSBGC, gSBGC->_api->boardVersion, BUFF_SIZE_(boardVersionStr));
				ParserSBGC32_FormatFirmwareVersion(gSBGC, gSBGC->_api->firmwareVersion, BUFF_SIZE_(firmwareVersionStr));

				DebugSBGC32_PrintMessage(gSBGC, "\n********************************\n");
				DebugSBGC32_PrintMessage(gSBGC, "The system is ready to go!\n");
				DebugSBGC32_PrintMessage(gSBGC, "Board Version: ");
				DebugSBGC32_PrintMessage(gSBGC, boardVersionStr);
				DebugSBGC32_PrintMessage(gSBGC, "\nFirmware Version: ");
				DebugSBGC32_PrintMessage(gSBGC, firmwareVersionStr);
				DebugSBGC32_PrintMessage(gSBGC, "\n********************************\n\n");

			#endif

			return;
		}
	}

	#if (SBGC_NEED_DEBUG)

		DebugSBGC32_PrintMessage(gSBGC, "\n********************************\n");
		DebugSBGC32_PrintMessage(gSBGC, "Communication Error!\n");
		DebugSBGC32_PrintMessage(gSBGC, "********************************\n\n");

	#endif
}


/**	@brief	Sets custom values of library variables for communication
 *
 *	@param	*gSBGC - serial connection descriptor
 *
 *	@return	Communication status
 */
sbgcCommandStatus_t SBGC32_SetupLibrary (sbgcGeneral_t *gSBGC)
{
	gSBGC->_api = (serialAPI_General_t*)sbgcMalloc(sizeof(serialAPI_General_t));

	PrivateSerialAPI_LinkLowLayer(gSBGC);
	PrivateSerialAPI_LinkConverter(gSBGC);

	#if (SBGC_USES_LOGS)
		PrivateSerialAPI_LinkDebug(gSBGC);
	#endif

	PrivateSerialAPI_LinkCommandBuild(gSBGC);

	/* Link high-layer service functions */
	gSBGC->_api->saveCmd = SerialAPI_SaveReceivedCommand;
	gSBGC->_api->findCmd = SerialAPI_FindCommandByID;

	#if (SBGC_USES_BLOCKING_MODE || SBGC_SEND_IMMEDIATELY)
		gSBGC->_api->process = SerialAPI_ProcessCommand;
	#endif

	#if (SBGC_USES_OS_SUPPORT)

		SystemSBGC32_CreateMutex(&gSBGC->_api->mutexSerialAPI);
		SystemSBGC32_GiveMutex(&gSBGC->_api->mutexSerialAPI);

	#endif

	gSBGC->_api->serialAPI_Status = serialAPI_OK;

	gSBGC->_api->boardVersion = 0;
	gSBGC->_api->firmwareVersion = 0;
	gSBGC->_api->baseFirmwareVersion = 0;

	#if (SBGC_ADJVAR_MODULE)
		gSBGC->_api->adjVarsNumber = SBGC_ADJ_VARS_MIN_QUANTITY;
	#endif

	gSBGC->_api->txErrorsCount = 0;
	gSBGC->_api->rxErrorsCount = 0;

	gSBGC->_api->commandBuff = (serialAPI_Command_t*)sbgcMalloc(sizeof(serialAPI_Command_t) * SBGC_MAX_COMMAND_NUM);
	gSBGC->_api->commandNumber = 0;
	gSBGC->_api->commandTotalCount = 0;

	gSBGC->_api->currentSerialCommand = NULL;

	#if (SBGC_NON_BLOCKING_MODE)
		gSBGC->_api->commandSortFlag = sbgcTRUE;
	#endif

	#if (SBGC_USES_TOKENS)
		gSBGC->_api->lastCommandToken = 0;
	#endif

	gSBGC->_api->txCommandBuff = (ui8*)sbgcMalloc(SBGC_TX_BUFF_TOTAL_SIZE);
	gSBGC->_api->txCommandBuffTail = 0;
	gSBGC->_api->txCommandBuffHead = 0;

	gSBGC->_api->rxCommandBuff = (ui8*)sbgcMalloc(SBGC_RX_BUFF_TOTAL_SIZE);
	gSBGC->_api->rxCommandBuffTail = 0;
	gSBGC->_api->rxCommandBuffHead = 0;
	gSBGC->_api->rxCommandBuffCurP = 0;

	gSBGC->_lastSerialCommandStatus = serialAPI_TX_RX_OK;
	gSBGC->_lastCommandStatus = sbgcCOMMAND_OK;

	/* Startup delay */
	sbgcTicks_t launchTime = serialAPI_GetTick();

	while ((serialAPI_GetTick() - launchTime) < SBGC_STARTUP_DELAY);

	/* Getting board information */
	gSBGC->_api->startWrite(gSBGC, CMD_BOARD_INFO SBGC_DEFAULT_ARGS__);
	gSBGC->_api->writeWord(gSBGC, 0);
	serialAPI_CurCmd_->parameters |= SCParam_EVENT_ANYWAY;

	#if (SBGC_USES_OS_SUPPORT)
		serialAPI_CurCmd_->priority = SCPrior_SUPREME;
	#endif

	gSBGC->_api->finishWrite(gSBGC);

	serialAPI_Unlock()

	#if (SBGC_NON_BLOCKING_MODE && (SBGC_USES_OS_SUPPORT == sbgcOFF))
		sbgcBlockQueue(SBGC32_TransmitAllCommands(gSBGC));
	#endif

	serialAPI_LockRead();

	gSBGC->_api->startRead(gSBGC, CMD_BOARD_INFO SBGC_DEFAULT_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, PostSetupLibrary, gSBGC, SBGC_MAX_PAYLOAD_SIZE);
	serialAPI_CurCmd_->parameters |= SCParam_EVENT_ANYWAY;

	#if (SBGC_USES_OS_SUPPORT)
		serialAPI_CurCmd_->priority = SCPrior_SUPREME;
	#endif

	gSBGC->_api->finishRead(gSBGC);

	serialAPI_Unlock()

	#if (SBGC_NON_BLOCKING_MODE && (SBGC_USES_OS_SUPPORT == sbgcOFF))
		sbgcBlockQueue(SBGC32_ReceiveAllCommands(gSBGC));
	#endif

	if (gSBGC->_lastCommandStatus == sbgcCOMMAND_OK)
	/* Getting the second features part and total adjustable variables number */
	{
		gSBGC->_api->startWrite(gSBGC, CMD_BOARD_INFO_3 SBGC_DEFAULT_ARGS__);
		serialAPI_CurCmd_->parameters |= SCParam_EVENT_ANYWAY;

		#if (SBGC_USES_OS_SUPPORT)
			serialAPI_CurCmd_->priority = SCPrior_SUPREME;
		#endif

		gSBGC->_api->finishWrite(gSBGC);

		serialAPI_Unlock()

		#if (SBGC_NON_BLOCKING_MODE && (SBGC_USES_OS_SUPPORT == sbgcOFF))
			sbgcBlockQueue(SBGC32_TransmitAllCommands(gSBGC));
		#endif

		serialAPI_LockRead();

		gSBGC->_api->startRead(gSBGC, CMD_BOARD_INFO_3 SBGC_DEFAULT_ARGS__);
		gSBGC->_api->assignEvent(gSBGC, PostSetupLibrary, gSBGC, SBGC_MAX_PAYLOAD_SIZE);
		serialAPI_CurCmd_->parameters |= SCParam_EVENT_ANYWAY;

		#if (SBGC_USES_OS_SUPPORT)
			serialAPI_CurCmd_->priority = SCPrior_SUPREME;
		#endif

		gSBGC->_api->finishRead(gSBGC);

		serialAPI_Unlock()

		#if (SBGC_NON_BLOCKING_MODE && (SBGC_USES_OS_SUPPORT == sbgcOFF))
			sbgcBlockQueue(SBGC32_ReceiveAllCommands(gSBGC));
		#endif
	}

	return gSBGC->_lastCommandStatus;
}


#if (SBGC_NEED_CONFIRM_CMD)

	/**	@brief	Manually expects the CMD_CONFIRM or CMD_ERROR
	 *			serial commands from the controller
	 *
	 *	####	RX <— CMD_CONFIRM :	1-6 bytes
	 *
	 *	@note	Use the @ref SerialAPI_DeleteCommand function
	 *			with CMD_CONFIRM argument to delete
	 *			this command manually
	 *
	 *	@param	*gSBGC - serial connection descriptor
	 *	@param	*confirm - confirmation result storage structure
	 *	@param	cmdID - SBGC32 command identifier to confirm
	 *
	 *	@return	Communication status
	 */
	sbgcCommandStatus_t SBGC32_CheckConfirmation (sbgcGeneral_t *gSBGC, sbgcConfirm_t *confirm, serialAPI_CommandID_t cmdID
												  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
	{
		/* It's necessary to lock SerialAPI before Rx operation */
		serialAPI_LockRead()

		gSBGC->_api->addConfirm(gSBGC, confirm, cmdID SBGC_ADVANCED_ARGS__);

		serialAPI_GiveToken()

		return gSBGC->_api->exit(gSBGC);
	}

#endif


/**	@brief	Sends a serial command with manually full data
 *
 *	@attention	It is necessary to insert @ref SBGC_RAW_CMD_END_SYMB
 *				as the last argument of the function
 *
 *	@note	Doesn't support the advanced parameters
 *
 *	@note	Other arguments are ui8 payload formatted
 *
 *	@code

			// For example, let's tilt a camera down 30 degrees
			SBGC32_SendRawCommand(&SBGC32_Device, CMD_CONTROL,
			0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7A, 0x00, 0x55,
			0x05, 0x00, 0x00, 0x00, 0x00, SBGC_RAW_CMD_END_SYMB);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	cmdID - SBGC32 command identifier
 *
 *	@return	Communication status
 */
sbgcCommandStatus_t SBGC32_SendRawCommand (sbgcGeneral_t *gSBGC, ui32 cmdID, ...)
{
	sbgcAssertParam(cmdID, CMD_BOARD_INFO_3, CMD_ERROR)

	va_list args;
	va_start(args, cmdID);

	ui32 byte = va_arg(args, ui32);

	gSBGC->_api->startWrite(gSBGC, cmdID SBGC_DEFAULT_ARGS__);

	while (byte != SBGC_RAW_CMD_END_SYMB)
	{
		#if (SBGC_NEED_ASSERTS)
			if (byte > 255U) return sbgcCOMMAND_PARAM_ASSERT_ERROR;
		#endif

		gSBGC->_api->writeByte(gSBGC, (ui8)byte);
		byte = va_arg(args, ui32);
	}

	va_end(args);

	gSBGC->_api->finishWrite(gSBGC);

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Expect a serial command from the controller
 *
 *	@note	Use the @ref SerialAPI_DeleteCommand function
 *			to delete the command manually
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	cmdID - SBGC32 command identifier
 *
 *	@return	Communication status
 */
sbgcCommandStatus_t SBGC32_ExpectCommand (sbgcGeneral_t *gSBGC, serialAPI_CommandID_t cmdID
										  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	/* It's necessary to lock SerialAPI before Rx operation */
	serialAPI_LockRead()

	gSBGC->_api->startRead(gSBGC, cmdID SBGC_ADVANCED_ARGS__);
	gSBGC->_api->finishRead(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Deletes a serial command from the main command buffer
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	cmdID - SBGC32 command identifier
 *
 *	@return	Result of delete
 */
sbgcBoolean_t SBGC32_DeleteCommand (sbgcGeneral_t *gSBGC, serialAPI_CommandID_t cmdID)
{
	serialAPI_Command_t *serialCommand = SerialAPI_FindCommandByCommandID(gSBGC, cmdID);

	if (serialCommand == NULL)
		return sbgcFALSE;

	SerialAPI_DeleteCommand(gSBGC, SerialAPI_GetSerialCommandIndex(gSBGC, serialCommand));

	return sbgcTRUE;
}


/**	@brief	Links driver functions to the lower level of the library
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*tx - driver function to transmit data buffers
 *	@param	*rx - driver function to receive a data byte
 *	@param	*availableBytes - driver function to get
 *			count of available bytes for reading
 *	@param	*txDebug - driver function to
 *			transmit debug data buffers
 *	@param	*getTime - driver function getting
 *			current time in milliseconds
 */
void SerialAPI_LinkDriver (sbgcGeneral_t *gSBGC, sbgcTx_t tx, sbgcRx_t rx,
						   sbgcAvailableBytes_t availableBytes, sbgcTxDebug_t txDebug,
						   sbgcGetTime_t getTime)
{
	gSBGC->_ll = (sbgcLowLayer_t*)sbgcMalloc(sizeof(sbgcLowLayer_t));

	gSBGC->_ll->drvTx = tx;
	gSBGC->_ll->drvRx = rx;
	gSBGC->_ll->drvAvailableBytes = availableBytes;

	#if (SBGC_NEED_DEBUG)
		gSBGC->_ll->drvTxDebug = txDebug;
	#else
		gSBGC->_ll->drvTxDebug = NULL;
	#endif

	gSBGC->_ll->drvGetTime = getTime;

	#if (SBGC_USES_CUSTOM_SPRINTF)
		SerialAPI_LinkSprintf(gSBGC);
	#else
		gSBGC->_ll->debugSprintf = sprintf;
	#endif
}


#if (SBGC_USES_CUSTOM_SPRINTF)

	/**	@brief	Links custom sprintf function to
	 *			the lower level of the library
	 *
	 *	@note	Weak function. It's necessary to copy
	 *			it completely and assign the custom
	 *			sprintf function inside
	 *
	 *	@code

				void SerialAPI_LinkSprintf (sbgcGeneral_t *gSBGC)
				{
					gSBGC->_ll->debugSprintf = userSprintf;
				}

	 *	@endcode
	 *
	 *	@param	*gSBGC - serial connection descriptor
	 */
	WEAK__ void SerialAPI_LinkSprintf (sbgcGeneral_t *gSBGC)
	{
		/* gSBGC->_ll->debugSprintf = userSprintf; */

		gSBGC->_ll->debugSprintf = NULL;
	}

#endif


/** @brief	Resets Tx data serial buffer
 *
 *	@param	gSBGC - pointer to serial connection descriptor
 */
void SerialAPI_ResetTxBuffer (sbgcGeneral_t *gSBGC)
{
	serialAPI_TakeMutex();

	gSBGC->_api->txCommandBuffTail = 0;
	gSBGC->_api->txCommandBuffHead = 0;

	gSBGC->_api->serialAPI_Status = serialAPI_OK;

	serialAPI_GiveMutex();
}


/** @brief	Resets Rx data serial buffer
 *
 *	@param	gSBGC - pointer to serial connection descriptor
 */
void SerialAPI_ResetRxBuffer (sbgcGeneral_t *gSBGC)
{
	serialAPI_TakeMutex();

	(gSBGC)->_api->rxCommandBuffTail = 0;
	(gSBGC)->_api->rxCommandBuffHead = 0;
	(gSBGC)->_api->rxCommandBuffCurP = 0;

	(gSBGC)->_api->serialAPI_Status = serialAPI_OK;

	serialAPI_GiveMutex();
}
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
