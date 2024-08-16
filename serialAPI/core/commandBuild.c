/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.0
 *
 *	@file		commandBuild.c
 *
 *	@brief		Source file of the core command building operations
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
/**	____________________________________________________________________
 *
 *	@defgroup	Command_Build Command Build
 *	@ingroup	Core
 *		@brief	Command Build library block
 *	____________________________________________________________________
 */

#include "../sbgc32.h"


/* Static Constants and Macros ----------------------------------------
 */
/* Serial command waits data receive operation. Hidden system part of SerialCommandParam_t */
#define		SCParam_RX				0x80

#define		lastCommand_			(gSBGC->_api->commandBuff[gSBGC->_api->commandNumber - 1])


#define		calculateFreeTx_()		(calcFreeSpaceFIFO(gSBGC->_api->txCommandBuffTail, gSBGC->_api->txCommandBuffHead, SBGC_TX_BUFF_TOTAL_SIZE))
#define		calculateFreeRx_()		(calcFreeSpaceFIFO(gSBGC->_api->rxCommandBuffTail, gSBGC->_api->rxCommandBuffHead, SBGC_RX_BUFF_TOTAL_SIZE))

#define		calculateEndRx_()		(((uintptr_t)gSBGC->_api->rxCommandBuff) + (SBGC_RX_BUFF_TOTAL_SIZE - 1))


#define		clearCmd_(pCmd)			memset(pCmd, 0, sizeof(serialAPI_Command_t))


/**	@addtogroup	Command_Build
 *	@{
 */
/**	@brief	Writes a byte to the serial command payload
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	byte - byte to write
 */
static void SerialAPI_WriteByte (sbgcGeneral_t *gSBGC, ui8 byte)
{
	serialAPI_Assert()

	if (calculateFreeTx_() < sizeof(ui8))
		serialAPI_Abort()

	serialAPI_CurCmd_->_payload[serialAPI_CurCmd_->_payloadSize] = byte;
	serialAPI_CurCmd_->_payloadSize += sizeof(ui8);
	gSBGC->_api->txCommandBuffHead += sizeof(ui8);
}


/**	@brief	Reads a byte from a serial command
 *			at the current read position
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *
 *	@return	Read byte
 */
static ui8 SerialAPI_ReadByte (sbgcGeneral_t *gSBGC)
{
	ui8 byte = (ui8)*serialAPI_CurCmd_->_payload;

	if (((uintptr_t)serialAPI_CurCmd_->_payload) != calculateEndRx_())
		serialAPI_CurCmd_->_payload++;

	else
		serialAPI_CurCmd_->_payload = gSBGC->_api->rxCommandBuff;

	return byte;
}


/**	@brief	Writes two bytes to the serial command's payload
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	word - two bytes to write
 */
static void SerialAPI_WriteWord (sbgcGeneral_t *gSBGC, ui16 word)
{
	serialAPI_Assert()

	if (calculateFreeTx_() < sizeof(ui16))
		serialAPI_Abort()

	gSBGC->_api->toLE(&word, &serialAPI_CurCmd_->_payload[serialAPI_CurCmd_->_payloadSize], sizeof(ui16));
	serialAPI_CurCmd_->_payloadSize += sizeof(ui16);
	gSBGC->_api->txCommandBuffHead += sizeof(ui16);
}


/**	@brief	Reads two bytes from a serial command
 *			at the current read position
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *
 *	@return	Read word
 */
static ui16 SerialAPI_ReadWord (sbgcGeneral_t *gSBGC)
{
	ui16 word;

	if (calculateEndRx_() < (((uintptr_t)serialAPI_CurCmd_->_payload) + (sizeof(ui16) - 1)))
	{
		ui8 wordBuff [2];

		wordBuff[0] = *serialAPI_CurCmd_->_payload;
		serialAPI_CurCmd_->_payload = gSBGC->_api->rxCommandBuff;
		wordBuff[1] = *serialAPI_CurCmd_->_payload;
		serialAPI_CurCmd_->_payload += sizeof(ui8);
		gSBGC->_api->fromLE(&word, wordBuff, sizeof(ui16));
	}

	else
	{
		gSBGC->_api->fromLE(&word, serialAPI_CurCmd_->_payload, sizeof(ui16));
		serialAPI_CurCmd_->_payload += sizeof(ui16);
	}

	if (((uintptr_t)serialAPI_CurCmd_->_payload) > calculateEndRx_())
		serialAPI_CurCmd_->_payload = gSBGC->_api->rxCommandBuff;

	return word;
}


/**	@brief	Writes four bytes to the serial command's payload
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	dword - four bytes to write
 */
static void SerialAPI_WriteLong (sbgcGeneral_t *gSBGC, ui32 dword)
{
	serialAPI_Assert()

	if (calculateFreeTx_() < sizeof(ui32))
		serialAPI_Abort()

	gSBGC->_api->toLE(&dword, &serialAPI_CurCmd_->_payload[serialAPI_CurCmd_->_payloadSize], 4);
	serialAPI_CurCmd_->_payloadSize += sizeof(ui32);
	gSBGC->_api->txCommandBuffHead += sizeof(ui32);
}


/**	@brief	Reads four bytes from a serial command
 *			at the current read position
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *
 *	@return	Read long
 */
static ui32 SerialAPI_ReadLong (sbgcGeneral_t *gSBGC)
{
	ui32 dword;

	if (calculateEndRx_() < (((uintptr_t)serialAPI_CurCmd_->_payload) + (sizeof(ui32) - 1)))
	{
		ui8 longBuff [4];
		ui8 cutSize = (calculateEndRx_() - ((uintptr_t)serialAPI_CurCmd_->_payload)) + 1;

		memcpy(longBuff, serialAPI_CurCmd_->_payload, cutSize);
		serialAPI_CurCmd_->_payload = gSBGC->_api->rxCommandBuff;
		memcpy(&longBuff[cutSize], serialAPI_CurCmd_->_payload, sizeof(ui32) - cutSize);
		serialAPI_CurCmd_->_payload += sizeof(ui32) - cutSize;
		gSBGC->_api->fromLE(&dword, longBuff, sizeof(ui32));
	}

	else
	{
		gSBGC->_api->fromLE(&dword, serialAPI_CurCmd_->_payload, sizeof(ui32));
		serialAPI_CurCmd_->_payload += 4;
	}

	if (((uintptr_t)serialAPI_CurCmd_->_payload) > calculateEndRx_())
		serialAPI_CurCmd_->_payload = gSBGC->_api->rxCommandBuff;

	return dword;
}


/**	@brief	Writes a data buffer to the serial command payload buffer
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*buff - written data
 *	@param	size - written data size
 */
static void SerialAPI_WriteBuff (sbgcGeneral_t *gSBGC, const void *buff, ui8 size)
{
	serialAPI_Assert()

	if (!size) return;

	if (calculateFreeTx_() < size)
		serialAPI_Abort()

	#if (SBGC_SYS_BIG_ENDIAN)
		sbgcParserMap_t parserMap = gSBGC->_api->getCmdPM(serialAPI_CurCmd_);
	#else
		sbgcParserMap_t parserMap = PM_DEFAULT_8BIT;
	#endif

	serialAPI_CurCmd_->_payloadSize +=
			gSBGC->_api->convWithPM(&serialAPI_CurCmd_->_payload[serialAPI_CurCmd_->_payloadSize], buff, size, parserMap);

	gSBGC->_api->txCommandBuffHead += size;
}


/**	@brief	Reads a serial command payload buffer to a data buffer
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*buff - where data will be written
 *	@param	size - read data size
 */
static void SerialAPI_ReadBuff (sbgcGeneral_t *gSBGC, void *buff, ui8 size)
{
	sbgcParserMap_t parserMap = gSBGC->_api->getCmdPM(serialAPI_CurCmd_);

	if (calculateEndRx_() < (((uintptr_t)serialAPI_CurCmd_->_payload) + (size - 1)))
	{
		ui8 buffTemp [size];
		ui8 cutSize = (calculateEndRx_() - ((uintptr_t)serialAPI_CurCmd_->_payload)) + 1;

		memcpy(buffTemp, serialAPI_CurCmd_->_payload, cutSize);
		serialAPI_CurCmd_->_payload = gSBGC->_api->rxCommandBuff;
		memcpy(&buffTemp[cutSize], serialAPI_CurCmd_->_payload, size - cutSize);
		serialAPI_CurCmd_->_payload += size - cutSize;
		gSBGC->_api->convWithPM(buff, buffTemp, size, parserMap);
	}

	else
		serialAPI_CurCmd_->_payload += gSBGC->_api->convWithPM(buff, serialAPI_CurCmd_->_payload, size, parserMap);
}


/**	@brief	Fills with zeros the serial command's payload
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	size - size of filled with zeros data
 */
static void SerialAPI_WriteEmptyBuff (sbgcGeneral_t *gSBGC, ui8 size)
{
	serialAPI_Assert()

	if (calculateFreeTx_() < size)
		serialAPI_Abort()

	memset(&serialAPI_CurCmd_->_payload[serialAPI_CurCmd_->_payloadSize], 0, size);
	serialAPI_CurCmd_->_payloadSize += size;
	gSBGC->_api->txCommandBuffHead += size;
}


/**	@brief	Moves current reading position
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	size - size of skipped data
 */
static void SerialAPI_SkipBytes (sbgcGeneral_t *gSBGC, ui8 size)
{
	if (calculateEndRx_() < (((uintptr_t)serialAPI_CurCmd_->_payload) + size))
	{
		ui8 restSize = size - ((calculateEndRx_() - ((uintptr_t)serialAPI_CurCmd_->_payload)) + 1);

		serialAPI_CurCmd_->_payload = gSBGC->_api->rxCommandBuff + restSize;
	}

	else
		serialAPI_CurCmd_->_payload += size;
}


/**	@brief	Initializes the write a serial command
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	cmdID - SBGC32 command identifier
 */
static void SerialAPI_StartWrite (sbgcGeneral_t *gSBGC, serialAPI_CommandID_t cmdID
								  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	/* Lock all SerialAPI operations to add a new command */
	serialAPI_Lock()

	#if (SBGC_NON_BLOCKING_MODE)

		for (ui8 i = 0; i < gSBGC->_api->commandNumber; i++)
			if ((gSBGC->_api->commandBuff[i]._commandID == cmdID) && (!(gSBGC->_api->commandBuff[i].parameters & SCParam_RX)) &&
				(gSBGC->_api->commandBuff[i].parameters & SCParam_RETAIN) && (!(parameters & SCParam_RETAIN)))
			/* The serial command must be freed */
			{
				serialAPI_CurCmd_ = &gSBGC->_api->commandBuff[i];

				serialAPI_CurCmd_->parameters = (serialAPI_CommandParam_t)parameters;
				serialAPI_CurCmd_->priority = priority;
				serialAPI_CurCmd_->timeout = timeout;

				#if (SBGC_USES_CALLBACKS)

					serialAPI_CurCmd_->callback = callback;
					serialAPI_CurCmd_->callbackArg = callbackArg;

				#endif

				serialAPI_CurCmd_->_state = SCState_FORMING;

				/* Continue to register the command */
				return;
			}

	#endif

	if (gSBGC->_api->commandNumber >= SBGC_MAX_COMMAND_NUM)
	{
		gSBGC->_lastCommandStatus = sbgcCOMMAND_BUFFER_OVERFLOW_ERROR;
		serialAPI_Error()
	}

	#if (SBGC_OPTIMIZE_COMMANDS)

		/* Looking for a command with the same commandID. Exit if found */
		for (ui8 i = 0; i < gSBGC->_api->commandNumber; i++)
			if ((gSBGC->_api->commandBuff[i]._commandID == cmdID) && (!(gSBGC->_api->commandBuff[i].parameters & SCParam_RX)))
			{
				gSBGC->_lastCommandStatus = sbgcCOMMAND_BUFFER_OPTIMIZED;
				serialAPI_Error()
			}

	#endif

	/* Begin to registration for a new command */
	serialAPI_CurCmd_ = &gSBGC->_api->commandBuff[gSBGC->_api->commandNumber];
	gSBGC->_api->commandNumber++;

	clearCmd_(serialAPI_CurCmd_);

	serialAPI_CurCmd_->_payload = &gSBGC->_api->txCommandBuff[gSBGC->_api->txCommandBuffHead];

	serialAPI_CurCmd_->_id = ++gSBGC->_api->commandTotalCount;
	serialAPI_CurCmd_->_state = SCState_FORMING;
	serialAPI_CurCmd_->_commandID = cmdID;

	#if (SBGC_NON_BLOCKING_MODE)

		serialAPI_CurCmd_->parameters = (serialAPI_CommandParam_t)(serialAPI_CurCmd_->parameters | parameters);
		serialAPI_CurCmd_->priority = priority;
		serialAPI_CurCmd_->timeout = timeout;

		#if (SBGC_USES_CALLBACKS)

			serialAPI_CurCmd_->callback = callback;
			serialAPI_CurCmd_->callbackArg = callbackArg;

		#endif

		gSBGC->_api->commandSortFlag = sbgcFALSE;

	#endif
}


/**	@brief	Initializes the read a serial command
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	cmdID - SBGC32 command identifier
 */
static void SerialAPI_StartRead (sbgcGeneral_t *gSBGC, serialAPI_CommandID_t cmdID
								 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	/* The SerialAPI is always locked at here */

	serialAPI_Assert()

	#if (SBGC_NON_BLOCKING_MODE)

		for (ui8 i = 0; i < gSBGC->_api->commandNumber; i++)
			if ((gSBGC->_api->commandBuff[i]._commandID == cmdID) && (gSBGC->_api->commandBuff[i].parameters & SCParam_RX) &&
				(gSBGC->_api->commandBuff[i].parameters & SCParam_RETAIN) && (!(parameters & SCParam_RETAIN)))
			/* The serial command must be freed */
			{
				serialAPI_CurCmd_ = &gSBGC->_api->commandBuff[i];

				serialAPI_CurCmd_->parameters = (serialAPI_CommandParam_t)(parameters | SCParam_RX);
				serialAPI_CurCmd_->priority = priority;
				serialAPI_CurCmd_->timeout = timeout;

				#if (SBGC_USES_CALLBACKS)

					serialAPI_CurCmd_->callback = callback;
					serialAPI_CurCmd_->callbackArg = callbackArg;

				#endif

				serialAPI_CurCmd_->_state = SCState_FORMING;

				/* Continue to register the command */
				return;
			}

	#endif

	if (gSBGC->_api->commandNumber >= SBGC_MAX_COMMAND_NUM)
	{
		gSBGC->_lastCommandStatus = sbgcCOMMAND_BUFFER_OVERFLOW_ERROR;
		serialAPI_Error()
	}

	#if (SBGC_OPTIMIZE_COMMANDS)

		/* Looking for a command with the same commandID. Exit if found */
		for (ui8 i = 0; i < gSBGC->_api->commandNumber; i++)
			if ((gSBGC->_api->commandBuff[i].parameters & SCParam_RX) && (gSBGC->_api->commandBuff[i]._commandID == cmdID))
			{
				gSBGC->_lastCommandStatus = sbgcCOMMAND_BUFFER_OPTIMIZED;
				serialAPI_Error()
			}

	#endif

	/* Begin to registration for a new command */
	serialAPI_CurCmd_ = &gSBGC->_api->commandBuff[gSBGC->_api->commandNumber];
	gSBGC->_api->commandNumber++;

	clearCmd_(serialAPI_CurCmd_);

	serialAPI_CurCmd_->_id = ++gSBGC->_api->commandTotalCount;
	serialAPI_CurCmd_->_state = SCState_FORMING;
	serialAPI_CurCmd_->_commandID = cmdID;
	serialAPI_CurCmd_->parameters = SCParam_RX;

	#if (SBGC_NON_BLOCKING_MODE)

		serialAPI_CurCmd_->parameters = (serialAPI_CommandParam_t)(serialAPI_CurCmd_->parameters | parameters);
		serialAPI_CurCmd_->priority = priority;
		serialAPI_CurCmd_->timeout = timeout;

		#if (SBGC_USES_CALLBACKS)

			serialAPI_CurCmd_->callback = callback;
			serialAPI_CurCmd_->callbackArg = callbackArg;

		#endif

		gSBGC->_api->commandSortFlag = sbgcFALSE;

	#endif
}


/**	@brief	Finishes forming the command to write
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void SerialAPI_FinishWrite (sbgcGeneral_t *gSBGC)
{
	serialAPI_Assert()

	#if (SBGC_USES_BLOCKING_MODE)

		gSBGC->_api->process(gSBGC, 0);

		if (gSBGC->_lastSerialCommandStatus != serialAPI_TX_RX_OK)
		{
			gSBGC->_lastCommandStatus = sbgcCOMMAND_TX_ERROR;

			/* Close SerialAPI to prevent superfluous RX command registration */
			serialAPI_Error()
		}

		else
		{
			gSBGC->_lastCommandStatus = sbgcCOMMAND_OK;
			return;
		}

	#endif

	#if (SBGC_USES_TOKENS)
		gSBGC->_api->lastCommandToken = ((sbgcCommandToken_t)serialAPI_CurCmd_->_id) & 0x000000FF;
	#endif

	serialAPI_CurCmd_->_state = SCState_PREPARED;
}


/**	@brief	Finishes forming the command to read
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void SerialAPI_FinishRead (sbgcGeneral_t *gSBGC)
{
	serialAPI_Assert()

	#if (SBGC_USES_BLOCKING_MODE)

		gSBGC->_api->process(gSBGC, 0);

		if (gSBGC->_lastSerialCommandStatus != serialAPI_TX_RX_OK)
			gSBGC->_lastCommandStatus = sbgcCOMMAND_RX_ERROR;

		else
			gSBGC->_lastCommandStatus = sbgcCOMMAND_OK;

		gSBGC->_api->serialAPI_Status = serialAPI_OK;
		return;

	#endif

	#if (SBGC_USES_TOKENS)

		gSBGC->_api->lastCommandToken &= 0x00FF;
		gSBGC->_api->lastCommandToken |= (((sbgcCommandToken_t)serialAPI_CurCmd_->_id) << 8) & 0x0000FF00;

	#endif

	serialAPI_CurCmd_->_state = SCState_PREPARED;
}


/**	@brief	Aborts the last serial command
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void SerialAPI_AbortLastCmd (sbgcGeneral_t *gSBGC)
{
	#if (SBGC_USES_LOGS)
		gSBGC->_api->writeLog(gSBGC, &lastCommand_);
	#endif

	clearCmd_(&lastCommand_);
	gSBGC->_api->commandNumber--;
}


#if (SBGC_NEED_CONFIRM_CMD)

	/**	@brief	SerialAPI event
	 *
	 *	@note	Private function.
	 *			See @ref SerialAPI_AddConfirmationCommand function
	 *
	 *	@param	*gSBGC - serial connection descriptor
	 */
	static void PostCheckConfirmation (sbgcGeneral_t *gSBGC)
	{
		sbgcConfirm_t *confirm = (sbgcConfirm_t*)serialAPI_CurCmdDest_;

		SerialAPI_SkipBytes(gSBGC, 1);  // Skip commandID

		if (serialAPI_CurCmd_->_commandID == CMD_CONFIRM)
		{
			if (serialAPI_CurCmd_->_payloadSize == 2)
				confirm->cmdData = SerialAPI_ReadByte(gSBGC);

			else if (serialAPI_CurCmd_->_payloadSize == 3)
				confirm->cmdData = SerialAPI_ReadWord(gSBGC);

			confirm->status = sbgcCONFIRM_RECEIVED;
		}

		else if (serialAPI_CurCmd_->_commandID == CMD_ERROR)
		{
			confirm->errorCode = SerialAPI_ReadByte(gSBGC);

			if (serialAPI_CurCmd_->_payloadSize > 1)
				SerialAPI_ReadBuff(gSBGC, confirm->errorData, 4);

			confirm->status = sbgcCONFIRM_ERROR;
		}
	}

#endif


/**	@brief	Assigns a serialAPI event to a serial command
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*serialAPI_Event - pointer to a system event function.
 *			If this parameter is NULL, payload will be written
 *			directly to pDestination
 *	@param	*pDestination - where the data will be written or changed
 *	@param	size - destination buffer size
 */
static void SerialAPI_AssignSystemEvent (sbgcGeneral_t *gSBGC, serialAPI_Event_t serialAPI_Event, void *pDestination, ui16 size)
{
	serialAPI_Assert()

	#if (SBGC_NEED_ASSERTS)

		if (pDestination == NULL)
			serialAPI_Abort()

	#endif

	serialAPI_CurCmd_->_serialAPI_Event = serialAPI_Event;
	serialAPI_CurCmd_->_pDestination = pDestination;
	serialAPI_CurCmd_->_destinationSize = size;
}


/**	@brief	Adds confirmation to the last serial command
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*confirm - confirmation result storage structure
 *	@param	cmdID - identifier of the command
 *			that needs to be confirmed
 */
static void SerialAPI_AddConfirmationCommand (sbgcGeneral_t *gSBGC, sbgcConfirm_t *confirm, serialAPI_CommandID_t cmdID
											  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	serialAPI_Assert()

	if (confirm == SBGC_NO_CONFIRM) return;

	#if (SBGC_NEED_CONFIRM_CMD)

		#if (SBGC_NON_BLOCKING_MODE)

			if (serialAPI_CurCmd_ == NULL)
			/* Break, if depended Tx command doesn't exist */
				return;

			else if (serialAPI_CurCmd_->_state != SCState_PREPARED)
			/* Break, if depended Tx command is faulted */
				return;

		#endif

		/* Clear confirmation command */
		memset(confirm, 0, sizeof(sbgcConfirm_t));

		/* Assign command ID to confirm */
		confirm->commandID = cmdID;

		/* Start read */
		SerialAPI_StartRead(gSBGC, CMD_CONFIRM SBGC_ADVANCED_ARGS__);
		SerialAPI_AssignSystemEvent(gSBGC, PostCheckConfirmation, confirm, sizeof(sbgcConfirm_t));
		SerialAPI_FinishRead(gSBGC);

	#else
		unused_(gSBGC);
	#endif
}


/**	@brief	Defines payload size to command must wait
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	payloadSize - how many bytes command waits
 */
static void SerialAPI_DefinePayloadSize (sbgcGeneral_t *gSBGC, ui8 payloadSize)
{
	serialAPI_Assert()

	serialAPI_CurCmd_->_payloadSize = payloadSize;
}


/**	@brief	Bounds Tx and Rx serial commands
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void SerialAPI_BoundCommands (sbgcGeneral_t *gSBGC)
{
	#if (SBGC_USES_BLOCKING_MODE)
		return;
	#endif

	if (gSBGC->_api->serialAPI_Status == serialAPI_ERROR)
	{
		if (serialAPI_CurCmd_->parameters & SCParam_RX)
		/* It means that Rx command was corrupted but still exist. Abort previous Tx command */
			gSBGC->_api->commandBuff[gSBGC->_api->commandNumber - 2]._state = SCState_ABORTED;

		else
			serialAPI_CurCmd_->_state = SCState_ABORTED;

		return;
	}

	if (gSBGC->_api->commandNumber == 0) return;
	if (!(serialAPI_CurCmd_->parameters & SCParam_RX)) return;

	serialAPI_Assert()

	/* Bound commands if everything is OK */
	serialAPI_Command_t *TxCmd = &gSBGC->_api->commandBuff[gSBGC->_api->commandNumber - 2];
	serialAPI_Command_t *RxCmd = serialAPI_CurCmd_;

	/* ID exchange */
	TxCmd->_relatedCommandID = RxCmd->_id;
	RxCmd->_relatedCommandID = TxCmd->_id;

	#if (SBGC_USES_CALLBACKS)

		if (TxCmd->parameters & SCParam_TX_CALLBACK)
		{
			RxCmd->callback = NULL;
			RxCmd->callbackArg = NULL;
		}

		else
		{
			TxCmd->callback = NULL;
			TxCmd->callbackArg = NULL;
		}

	#endif
}


/**	@brief	Finish SBGC32 command processing and
 * 			exits from the function
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 *
 *	@return	Communication status
 */
static sbgcCommandStatus_t SerialAPI_Exit (sbgcGeneral_t *gSBGC)
{
	if (gSBGC->_api->serialAPI_Status == serialAPI_ERROR)
	/* Check what's wrong */
	{
		while ((lastCommand_._state == SCState_ABORTED) && gSBGC->_api->commandNumber)
		/* Delete all corrupted commands */
			SerialAPI_AbortLastCmd(gSBGC);

        serialAPI_Unlock()

		/* Return error code */
		return gSBGC->_lastCommandStatus;
	}

	#if (SBGC_SEND_IMMEDIATELY)

		ui16 txCommandIndex = 0xFFFF;

		for (ui8 i = 0; i < gSBGC->_api->commandNumber; i++)
			if (!(gSBGC->_api->commandBuff[i].parameters & SCParam_RX))
			{
				txCommandIndex = i;
				break;
			}

		if (txCommandIndex != 0xFFFF)
		{
			gSBGC->_api->process(gSBGC, txCommandIndex);

			if (gSBGC->_lastSerialCommandStatus != serialAPI_TX_RX_OK)
				gSBGC->_lastCommandStatus = sbgcCOMMAND_TX_ERROR;

			else
				gSBGC->_lastCommandStatus = sbgcCOMMAND_OK;
		}

	#endif

	#if (SBGC_USES_OS_SUPPORT)

		sbgcCommandStatus_t lastCommandStatus = gSBGC->_lastCommandStatus;

		if (lastCommand_.parameters & SCParam_FREEZE)
		{
			/* If Tx or Rx only using Last. If Tx-Rx: Tx - Prev, Rx - Last */
			serialAPI_Command_t *freezeCommandPrev, *freezeCommandLast;

			freezeCommandLast = &lastCommand_;
			freezeCommandPrev = gSBGC->_api->findCmd(gSBGC, lastCommand_._relatedCommandID);

			ui32 freezeCommandLastID = lastCommand_._id;
			ui32 freezeCommandPrevID;

			serialAPI_CommandParam_t freezeCommandLastParam = lastCommand_.parameters;
			serialAPI_CommandParam_t freezeCommandPrevParam;

			if (freezeCommandPrev)
			/* Freeze also Tx command that may bounds with Rx command */
			{
				freezeCommandPrevID = freezeCommandPrev->_id;
				freezeCommandPrevParam = freezeCommandPrev->parameters;
			}

			serialAPI_Unlock()

			/* Launch SerialAPI handler */
			serialAPI_Resume()

			if (freezeCommandPrev)
			{
				while (1)
				{
					freezeCommandPrev = gSBGC->_api->findCmd(gSBGC, freezeCommandPrevID);

					if ((freezeCommandPrev == NULL) || (freezeCommandPrev->_state == SCState_ERROR))
					/* Something goes wrong and this command doesn't exist now or finished with communication error */
					{
						lastCommandStatus = (freezeCommandPrevParam & SCParam_RX) ? sbgcCOMMAND_RX_ERROR : sbgcCOMMAND_TX_ERROR;
						break;
					}

					else if (freezeCommandPrev->_state == SCState_PROCESSED)
					/* This command is closed now, but we don't know anything about results. Unlock this thread now */
					{
						lastCommandStatus = sbgcCOMMAND_OK;
						break;
					}
				}
			}

			/* Launch SerialAPI handler */
			serialAPI_Resume()

			/* Pass to Rx command finish waiting */
			while (1)
			{
				freezeCommandLast = gSBGC->_api->findCmd(gSBGC, freezeCommandLastID);

				if ((freezeCommandLast == NULL) || (freezeCommandLast->_state == SCState_ERROR))
				/* Something goes wrong and this command doesn't exist now or finished with communication error */
				{
					lastCommandStatus = (freezeCommandLastParam & SCParam_RX) ? sbgcCOMMAND_RX_ERROR : sbgcCOMMAND_TX_ERROR;
					break;
				}

				else if (freezeCommandLast->_state == SCState_PROCESSED)
				/* This command is closed now, but we don't know anything about results. Unlock this thread now */
				{
					lastCommandStatus = sbgcCOMMAND_OK;
					break;
				}
			}
		}

		serialAPI_Unlock()

		/* Launch SerialAPI handler */
		serialAPI_Resume()

		return lastCommandStatus;

	#endif

	#if (SBGC_NON_BLOCKING_MODE)

		if (gSBGC->_api->serialAPI_Status == serialAPI_FORMING)
			serialAPI_Unlock()

		else
		/* An unprotected entry into the function occurred */
		{
			gSBGC->_lastCommandStatus = sbgcCOMMAND_SERIAL_API_BUSY_ERROR;
			return gSBGC->_lastCommandStatus;
		}

		#if (SBGC_SEND_IMMEDIATELY == sbgcOFF)
			gSBGC->_lastCommandStatus = sbgcCOMMAND_OK;
		#endif

	#endif

	serialAPI_Unlock()

	return gSBGC->_lastCommandStatus;
}


/**	@brief	Links command-build functions to internal
 *			software system of the library
 *
 *	@note	Quasi-private function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
void PrivateSerialAPI_LinkCommandBuild (sbgcGeneral_t *gSBGC)
{
	gSBGC->_api->writeByte	= SerialAPI_WriteByte;
	gSBGC->_api->readByte	= SerialAPI_ReadByte;
	gSBGC->_api->writeWord	= SerialAPI_WriteWord;
	gSBGC->_api->readWord	= SerialAPI_ReadWord;
	gSBGC->_api->writeLong	= SerialAPI_WriteLong;
	gSBGC->_api->readLong	= SerialAPI_ReadLong;
	gSBGC->_api->writeBuff	= SerialAPI_WriteBuff;
	gSBGC->_api->readBuff	= SerialAPI_ReadBuff;
	gSBGC->_api->writeEmptyBuff
							= SerialAPI_WriteEmptyBuff;
	gSBGC->_api->skipBytes	= SerialAPI_SkipBytes;
	gSBGC->_api->startWrite	= SerialAPI_StartWrite;
	gSBGC->_api->startRead	= SerialAPI_StartRead;
	gSBGC->_api->finishWrite
							= SerialAPI_FinishWrite;
	gSBGC->_api->finishRead	= SerialAPI_FinishRead;
	gSBGC->_api->abortLast	= SerialAPI_AbortLastCmd;
	gSBGC->_api->addConfirm	= SerialAPI_AddConfirmationCommand;
	gSBGC->_api->assignEvent
							= SerialAPI_AssignSystemEvent;
	gSBGC->_api->definePayload
							= SerialAPI_DefinePayloadSize;
	gSBGC->_api->bound		= SerialAPI_BoundCommands;
	gSBGC->_api->exit		= SerialAPI_Exit;
}
/**	@}
 */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
