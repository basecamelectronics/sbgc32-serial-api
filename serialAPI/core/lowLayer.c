/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.1
 *
 *	@file		lowLayer.c
 *
 *	@brief		Source file of the core communication with driver
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
 *	@defgroup	Low_Layer Low Layer
 *	@ingroup	Core
 *		@brief	Low Layer library block
 *	____________________________________________________________________
 */

#include "../sbgc32.h"


/* Static Constants ----------------------------------------------------
 */
#define		SBGC_P1_START_CHARACTER	0x3EU			// '>'
#define		SBGC_P2_START_CHARACTER	0x24U			// '$'

#define		SBGC_CRC16_POLYNOM		0x8005U


/**	@addtogroup	Low_Layer
 *	@{
 */
/**	@verbatim

	If you want to create your own gimbal communication driver, do it
	based on these function type templates:

	typedef	sbgcTicks_t		(*sbgcGetTime_t)(void *drv);

	typedef	ui8				(*sbgcTx_t)(void *drv, ui8 *data, ui16 size);
	typedef	ui8				(*sbgcRx_t)(void *drv, ui8 *data);
	typedef	ui16			(*sbgcAvailableBytes_t)(void *drv);

	and the secondary debug functions:

	typedef	void			(*sbgcTxDebug_t)(char *data, ui16 length);
	typedef	int				(*sbgcSprintf_t)(char *buffer, const char *format, ...);

	Additionally, user's Tx and Rx functions should return the next values:

	#define	SBGC_DRV_TX_OK_FLAG				0
	#define	SBGC_DRV_TX_BUFF_OVERFLOW_FLAG	BIT_0_SET

	#define	SBGC_DRV_RX_BUSY_FLAG			0
	#define	SBGC_DRV_RX_BUFF_EMPTY_FLAG		BIT_0_SET

	Refer to library driver functions for more

	@endverbatim
*/
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	Low_Layer
 *	@{
 */
#if ((SBGC_PROTOCOL_VERSION == 1) || SBGC_USES_DOXYGEN)

	/**	@brief	Calculates the checksum for the first version
	 *			of the SBGC32 communication protocol
	 *
	 *	@note	Private function
	 *
	 *	@param	*data - data buffer for calculate
	 *	@param	length - size of data buffer
	 *
	 *	@return	Calculated checksum
	 */
	static ui8 SerialAPI_Modulo256_Calculate (ui8 *data, ui16 length)
	{
		i32 totalSum = 0;

		while (--length)
			totalSum += *(data++);

		return totalSum % 256;
	}

#endif


#if ((SBGC_PROTOCOL_VERSION == 2) || SBGC_USES_DOXYGEN)

	/**	@brief	Calculates the checksum for the second version
	 *			of the SBGC32 communication protocol
	 *
	 *	@note	Private function
	 *
	 *	@param	*data - data buffer for calculate
	 *	@param	length - size of data buffer
	 *
	 *	@return	Calculated checksum
	 */
	static ui16 SerialAPI_CRC16_Calculate (ui8 const *data, ui16 length)
	{
		ui16 CRC_Register = 0;
		ui8 shiftRegister, dataBit, CRC_Bit;

		for (ui16 i = 0; i < length; i++)
		{
			for (shiftRegister = 1; shiftRegister > 0; shiftRegister <<= 1)
			{
				dataBit = (data[i] & shiftRegister) ? 1 : 0;
				CRC_Bit = CRC_Register >> 15;
				CRC_Register <<= 1;

				if (dataBit != CRC_Bit)
					CRC_Register ^= SBGC_CRC16_POLYNOM;
			}
		}

		return CRC_Register;
	}

#endif


/**	@brief	Forms a serial command from the buffer
 *			and sends it to the SBGC device
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void SBGC32_TX (sbgcGeneral_t *gSBGC)
{
	ui8 dataBuff [gSBGC->_api->currentSerialCommand->_payloadSize + SBGC_SERVICE_BYTES_NUM];

	/* Forming the command */
	dataBuff[0] = (SBGC_PROTOCOL_VERSION - 1) ? SBGC_P2_START_CHARACTER : SBGC_P1_START_CHARACTER;
	dataBuff[1] = gSBGC->_api->currentSerialCommand->_commandID;
	dataBuff[2] = gSBGC->_api->currentSerialCommand->_payloadSize;
	dataBuff[3] = dataBuff[1] + dataBuff[2];  // No need Modulo256 calculation

	memcpy(&dataBuff[4], gSBGC->_api->currentSerialCommand->_payload, gSBGC->_api->currentSerialCommand->_payloadSize);

	/* ui8 size = real size current gSBGC->_api->currentSerialCommand */
	ui8 size = gSBGC->_api->currentSerialCommand->_payloadSize + SBGC_SERVICE_BYTES_NUM;

	#if (SBGC_PROTOCOL_VERSION == 1)

		dataBuff[4 + gSBGC->_api->currentSerialCommand->_payloadSize] =
				SerialAPI_Modulo256_Calculate(gSBGC->_api->currentSerialCommand->_payload, gSBGC->_api->currentSerialCommand->_payloadSize);

	#else  // V.2

		ui16 CRC16_Res = SerialAPI_CRC16_Calculate(&dataBuff[1], (4 + gSBGC->_api->currentSerialCommand->_payloadSize) - 1);
		memcpy(&dataBuff[4 + gSBGC->_api->currentSerialCommand->_payloadSize], &CRC16_Res, sizeof(CRC16_Res));

	#endif

	/* Transmit now */
	ui8 txStatus = gSBGC->_ll->drvTx(gSBGC->_ll->drv, dataBuff, size);

	#if (SBGC_NON_BLOCKING_MODE)

		gSBGC->_api->currentSerialCommand->_timestamp = serialAPI_GetTick();

		if (txStatus != SBGC_DRV_TX_OK_FLAG)
		{

	#else

		/* Launch timer */
		sbgcTicks_t launchTime = serialAPI_GetTick();

		while (((serialAPI_GetTick() - launchTime) < gSBGC->_api->currentSerialCommand->timeout) && (txStatus != SBGC_DRV_TX_OK_FLAG))
		/* Try to transmit the command while its time isn't over */
		{
			txStatus = gSBGC->_ll->drvTx(gSBGC->_ll->drv, dataBuff, size);

			/* Enter to user's waiting handler */
			SerialAPI_CommandWaitingHandler(gSBGC);
		}

		if (txStatus != SBGC_DRV_TX_OK_FLAG)
		{

	#endif

			gSBGC->_lastSerialCommandStatus = serialAPI_TX_BUS_BUSY_ERROR;

			/* Enter to user's waiting handler */
			SerialAPI_CommandWaitingHandler(gSBGC);

			return;
		}

	/* Command was transmitted fine */
	gSBGC->_lastSerialCommandStatus = serialAPI_TX_RX_OK;
}


/**	@brief	Receives an incoming command
 *
 *	@note	Private function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void SBGC32_RX (sbgcGeneral_t *gSBGC)
{
	/* Parser initializing */
	static ui8 headBuff [3];  /* Header buffer:
	headBuff[0] is command ID || headBuff[1] is payload size || headBuff[2] is header checksum */

	ui8 startSymSample = (SBGC_PROTOCOL_VERSION - 1) ? SBGC_P2_START_CHARACTER : SBGC_P1_START_CHARACTER;
	ui16 availableBytes;

	static enum ParserState
	{
		STATE_IDLE = 0,
		STATE_RESYNC,
		STATE_CHECK_HEADER,
		STATE_CHECK_PAYLOAD
		// Next - a command received OK

	}	parserState = STATE_IDLE;

	/* Start parse */
	switch (parserState)
	{
		/* Waiting start byte */
		case STATE_IDLE :
		case STATE_RESYNC :
		{
			availableBytes = gSBGC->_ll->drvAvailableBytes(gSBGC->_ll->drv);

			if (availableBytes && (availableBytes != SBGC_RX_BUFFER_OVERFLOW_FLAG))
			{
				ui8 startSym = 0;

				gSBGC->_ll->drvRx(gSBGC->_ll->drv, &startSym);

				if (startSym != startSymSample)
				{
					gSBGC->_lastSerialCommandStatus = serialAPI_RX_EMPTY_BUFF_ERROR;
					break;
				}
			}

			else
			{
				gSBGC->_lastSerialCommandStatus = serialAPI_RX_EMPTY_BUFF_ERROR;
				break;
			}

			parserState = STATE_CHECK_HEADER;
			/* Passing to the next state */
		}

		/* Waiting whole header */
		case STATE_CHECK_HEADER :
		{
			availableBytes = gSBGC->_ll->drvAvailableBytes(gSBGC->_ll->drv);

			if ((availableBytes >= 3) && (availableBytes != SBGC_RX_BUFFER_OVERFLOW_FLAG))
				for (ui8 i = 0; i < 3; i++)
					gSBGC->_ll->drvRx(gSBGC->_ll->drv, &headBuff[i]);

			else
			/* The parser could not read the next 3 header bytes. Try again in the next time */
			{
				gSBGC->_lastSerialCommandStatus = serialAPI_RX_BUFFER_REALTIME_ERROR;
				break;
			}

			if (((headBuff[0] + headBuff[1]) % 256 != headBuff[2]) ||
				(headBuff[0] == 0))
			/* The header checksum is wrong. Break this command and look forward for a new command */
			{
				gSBGC->_lastSerialCommandStatus = serialAPI_RX_HEADER_CHECKSUM_ERROR;
				parserState = STATE_RESYNC;
				break;
			}

			parserState = STATE_CHECK_PAYLOAD;
			/* Passing to the next state */
		}

		/* Waiting whole payload and checksum */
		case STATE_CHECK_PAYLOAD :
		{
			ui8 checksumSize = SBGC_PROTOCOL_VERSION;
			ui8 complexBuff [sizeof(headBuff) + headBuff[1] + checksumSize];  // (Header + payloadSize + checksum) buffer

			availableBytes = gSBGC->_ll->drvAvailableBytes(gSBGC->_ll->drv);

			if ((availableBytes >= headBuff[1] + checksumSize) && (availableBytes != SBGC_RX_BUFFER_OVERFLOW_FLAG))
				for (ui8 i = 0; i < headBuff[1] + checksumSize; i++)
					gSBGC->_ll->drvRx(gSBGC->_ll->drv, &complexBuff[i + 3]);  // Offset from header space

			else
			/* The parser could not read the next payload in the full volume. Try again in the next time */
			{
				gSBGC->_lastSerialCommandStatus = serialAPI_RX_BUFFER_REALTIME_ERROR;
				break;
			}

			/* Checksum checking */
			#if (SBGC_PROTOCOL_VERSION == 1)  // V.1

				if (complexBuff[3 + headBuff[1]] != SerialAPI_Modulo256_Calculate(&complexBuff[3], headBuff[1]))
				/* The command came corrupted. Break it, look forward for a new command */
				{
					gSBGC->_lastSerialCommandStatus = serialAPI_RX_PAYLOAD_CHECKSUM_ERROR;
					parserState = STATE_RESYNC;
					break;
				}

			#else  // V.2

				memcpy(complexBuff, headBuff, 3);
				ui16 CRC_Res = SerialAPI_CRC16_Calculate(complexBuff, headBuff[1] + 3);

				if (((CRC_Res & 0x00FF) != complexBuff[3 + headBuff[1]]) &&
				   (((CRC_Res >> 8) & 0x00FF) != complexBuff[3 + headBuff[1] + 1]))
				/* The command came corrupted. Break it, look forward for a new command */
				{
					gSBGC->_lastSerialCommandStatus = serialAPI_RX_PAYLOAD_CHECKSUM_ERROR;
					parserState = STATE_RESYNC;
					break;
				}

			#endif

			#if (SBGC_NEED_CONFIRM_CMD == sbgcOFF)

				if (((serialAPI_CommandID_t)headBuff[0] == CMD_CONFIRM) || ((serialAPI_CommandID_t)headBuff[0] == CMD_ERROR))
				/* The command is CMD_CONFIRM or CMD_ERROR. Break it, look forward for a new command */
				{
					gSBGC->_lastSerialCommandStatus = serialAPI_RX_REJECTED_CONFIRM_CMD;
					parserState = STATE_IDLE;
					break;
				}

			#endif

			/* Data passed all checks. Fill the new serialCommand struct */
			gSBGC->_api->saveCmd(gSBGC, (serialAPI_CommandID_t)headBuff[0], headBuff[1], &complexBuff[3]);

			/* Prepare parser for new reading */
			parserState = STATE_IDLE;

			gSBGC->_lastSerialCommandStatus = serialAPI_TX_RX_OK;
			return;
		}
	}

	/* The command wasn't received. Exit */
}


/**	@brief	Links low-layer functions to internal
 *			software system of the library
 *
 *	@note	Quasi-private function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
void PrivateSerialAPI_LinkLowLayer (sbgcGeneral_t *gSBGC)
{
	gSBGC->_ll->tx = SBGC32_TX;
	gSBGC->_ll->rx = SBGC32_RX;
}
/**	@}
 */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
