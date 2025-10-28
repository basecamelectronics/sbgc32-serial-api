/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2
 *
 *	@file		debug.c
 *
 *	@brief		Source file of the core debug functions
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


#if (SBGC_NEED_DEBUG)

/* Static Constants and Macros ----------------------------------------
 */
/* Serial command waits data receive operation. Hidden system part of SerialCommandParam_t */
#define		SCParam_RX				0x80

#define		SBGC_DEBUG_BUFF_SIZE	64

#define		SBGC_LOG_BUFF_SIZE		((SBGC_LOG_COMMAND_TIME * -12) +\
									(SBGC_LOG_COMMAND_NUMBER * -12) +\
									(SBGC_LOG_COMMAND_DIR * -4) +\
									(SBGC_LOG_COMMAND_NAME * -32) +\
									(SBGC_LOG_COMMAND_ID * -7) +\
									(SBGC_LOG_COMMAND_STATUS * -11) +\
									((SBGC_LOG_COMMAND_PARAM * -5) * 4) +\
									(SBGC_LOG_COMMAND_DATA * -6) +\
									3)


#define		calculateEndRx_()		(((uintptr_t)gSBGC->_api->rxCommandBuff) + (SBGC_RX_BUFF_TOTAL_SIZE - 1))


/**	@addtogroup	Debug
 *	@{
 */
/**	@brief	Displays debug information
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*str - printable string
 */
void DebugSBGC32_PrintMessage (sbgcGeneral_t *gSBGC, const char *str)
{
	#if (SBGC_NEED_ASSERTS)
		if (gSBGC->_ll->drvTxDebug == NULL) return;
	#endif

	gSBGC->_ll->drvTxDebug((char*)str, strlen(str));
}


/**	@brief	Displays the contents of buffer
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*data - printable data
 *	@param	length - length of printable data
 */
void DebugSBGC32_PrintBuffer (sbgcGeneral_t *gSBGC, char *data, ui16 length)
{
	#if (SBGC_NEED_ASSERTS)
		if (gSBGC->_ll->drvTxDebug == NULL) return;
	#endif

	gSBGC->_ll->drvTxDebug(data, length);
}


/**	@brief	Displays any variable by its address
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*pValue - printable variable
 *	@param	*str - debug info string
 *	@param	vType - type of variable
 */
void DebugSBGC32_PrintStructElement (sbgcGeneral_t *gSBGC, void *pValue, const char *str, sbgcVarType_t vType)
{
	char debugStr [SBGC_DEBUG_BUFF_SIZE] = { 0 };

	if (!(vType & sbgcFLAG))
	/* Simple values */
	{
		char valueStr [16] = { 0 };

		switch (vType)
		{
			case sbgcUCHAR :
				gSBGC->_ll->debugSprintf(valueStr, "%u", *(ui8*)pValue);
				break;

			case sbgcUSHORT :
				gSBGC->_ll->debugSprintf(valueStr, "%u", *(ui16*)pValue);
				break;

			case sbgcUINT :
				#ifdef _L32__
					gSBGC->_ll->debugSprintf(valueStr, "%u", *(ui32*)pValue);
				#else
					gSBGC->_ll->debugSprintf(valueStr, "%lu", *(ui32*)pValue);
				#endif

				break;

			case sbgcCHAR :
				gSBGC->_ll->debugSprintf(valueStr, "%i", *(i8*)pValue);
				break;

			case sbgcSHORT :
				gSBGC->_ll->debugSprintf(valueStr, "%i", *(i16*)pValue);
				break;

			case sbgcINT :
				#ifdef _L32__
					gSBGC->_ll->debugSprintf(valueStr, "%i", *(i32*)pValue);
				#else
					gSBGC->_ll->debugSprintf(valueStr, "%li", *(i32*)pValue);
				#endif

				break;

			case sbgcFLOAT :
				gSBGC->_ll->debugSprintf(valueStr, "%14.6f", *(float*)pValue);  // 14(8).6f is default. May be changed
				break;

			default :  // Prevents [-Wswitch warning]
				break;
		}

		if (strlen(str) > (SBGC_DEBUG_BUFF_SIZE - sizeof(valueStr)))
			strncat(debugStr, str, SBGC_DEBUG_BUFF_SIZE - sizeof(valueStr));

		gSBGC->_ll->debugSprintf(debugStr, "%s %s\n", str, valueStr);
	}

	else
	/* Flags */
	{
		char flagStr [33] = { 0 };

		switch (vType & CLEAN_TYPE_MASK)
		{
			case sbgcUCHAR :
			{
				ui8 valueTemp = *(ui8*)pValue;

				for (ui8 i = 0; i < 8; i++)
				{
					if (valueTemp & (1 << i))
						flagStr[7 - i] = '1';

					else
						flagStr[7 - i] = '0';
				}

				flagStr[8] = '\0';

				gSBGC->_ll->debugSprintf(debugStr, "%s %s\n", str, flagStr);
				break;
			}

			case sbgcUSHORT :
			{
				ui16 valueTemp = *(ui16*)pValue;

				for (ui16 i = 0; i < 16; i++)
				{
					if (valueTemp & (1 << i))
						flagStr[15 - i] = '1';

					else
						flagStr[15 - i] = '0';
				}

				flagStr[16] = '\0';

				break;
			}

			case sbgcUINT :
			{
				ui32 valueTemp = *(ui32*)pValue;

				for (ui32 i = 0; i < 32; i++)
				{
					if (valueTemp & (1 << i))
						flagStr[31 - i] = '1';

					else
						flagStr[31 - i] = '0';
				}

				flagStr[32] = '\0';

				break;
			}
		}

		if (strlen(str) > (SBGC_DEBUG_BUFF_SIZE - sizeof(flagStr)))
			strncat(debugStr, str, SBGC_DEBUG_BUFF_SIZE - sizeof(flagStr));

		gSBGC->_ll->debugSprintf(debugStr, "%s %s\n", str, flagStr);
	}

	DebugSBGC32_PrintMessage(gSBGC, debugStr);
}


#if (SBGC_NEED_REF_INFO)

	/**	@brief	Prints the Serial API structures entirely
	 *
	 *	@param	*gSBGC - serial connection descriptor
	 *	@param	*structure - Serial API command data
	 *	@param	parserMap - data type required for correct parsing
	 */
	void DebugSBGC32_PrintWholeStruct (sbgcGeneral_t *gSBGC, void *structure, sbgcParserMap_t parserMap)
	{
		ui8 *structureTemp = (ui8*)structure;
		ui32 currentAddrOffset = 0;

		const sbgcParameterReferenceInfo_t *parameterReferenceInfo = NULL;
		ui8 parameterReferenceInfoElCnt = gSBGC->_api->assignByPM(&parameterReferenceInfo, parserMap);

		ui8 parameterSize;

		char debugStr [50];

		for (ui8 i = 0; i < parameterReferenceInfoElCnt; i++)
		{
			/* Obtain an element type for made correct structure moving */
			parameterSize = gSBGC->_api->typeToSize(parameterReferenceInfo[i].type);

			for (ui8 k = 0; k < parameterReferenceInfo[i].length; k++)
			{
				if (parameterReferenceInfo[i].type != sbgcRCHAR)
				{
					if (parameterReferenceInfo[i].length == 1)
						 memcpy(debugStr, parameterReferenceInfo[i].name, strlen(parameterReferenceInfo[i].name) + 1);

					else
						gSBGC->_ll->debugSprintf(debugStr, "%s [%d]", parameterReferenceInfo[i].name, k);

					memcpy(&debugStr[strlen(debugStr)], " =", 3);

					DebugSBGC32_PrintStructElement(gSBGC, &structureTemp[currentAddrOffset], debugStr, parameterReferenceInfo[i].type);
				}

				currentAddrOffset += parameterSize;
			}
		}

		DebugSBGC32_PrintMessage(gSBGC, " \n");
	}

#endif


#if (SBGC_USES_LOGS)

	/**	@brief	Writes system's logs
	 *
	 *	@note	Private function
	 *
	 *	@param	*gSBGC - serial connection descriptor
	 *	@param	*serialCommand - pointer to a serial command
	 */
	static void DebugSBGC32_WriteLog (sbgcGeneral_t *gSBGC, serialAPI_Command_t *serialCommand)
	{
		if (serialCommand->parameters & SCParam_NO_NEED_LOG) return;

		char logBuffer [SBGC_LOG_BUFF_SIZE] = { 0 };
		ui8 pointer = 0;

		#if (SBGC_LOG_COMMAND_TIME)

			ui8 minutes, seconds;
			ui16 milliseconds;
			sbgcTicks_t timestamp = sbgcGetTick();

			milliseconds = timestamp % 1000;
			seconds = ((timestamp - milliseconds) / 1000) % 60;
			minutes = (((timestamp - milliseconds) / 1000) / 60) % 100;

			pointer += gSBGC->_ll->debugSprintf(logBuffer, "[%02u:%02u:%03u] ", minutes, seconds, milliseconds);

		#endif

		#if (SBGC_LOG_COMMAND_NUMBER)

			#ifdef _L32__
				pointer += gSBGC->_ll->debugSprintf(&logBuffer[pointer], "%u. ", serialCommand->_CID);
			#else
				pointer += gSBGC->_ll->debugSprintf(&logBuffer[pointer], "%lu. ", serialCommand->_CID);
			#endif

		#endif

		#if (SBGC_LOG_COMMAND_DIR)

			pointer += (serialCommand->parameters & SCParam_RX) ?
					gSBGC->_ll->debugSprintf(&logBuffer[pointer], "<-- ") : gSBGC->_ll->debugSprintf(&logBuffer[pointer], "--> ");

		#endif

		#if (SBGC_LOG_COMMAND_NAME)

			pointer += ParserSBGC32_ConvertCommandID_ToString(serialCommand, &logBuffer[pointer], SBGC_LOG_BUFF_SIZE - pointer);
			logBuffer[pointer] = ' ';
			pointer++;

		#endif

		#if (SBGC_LOG_COMMAND_ID)
			pointer += gSBGC->_ll->debugSprintf(&logBuffer[pointer], "(#%d) ", serialCommand->_commandID);
		#endif

		#if ((SBGC_LOG_COMMAND_STATUS | SBGC_LOG_COMMAND_PARAM | SBGC_LOG_COMMAND_DATA) && (SBGC_LOG_COMMAND_NAME | SBGC_LOG_COMMAND_ID))
			pointer += gSBGC->_ll->debugSprintf(&logBuffer[pointer - 1], ": ") - 1;
		#endif

		#if (SBGC_LOG_COMMAND_STATUS)

			pointer += ParserSBGC32_ConvertCommandStatusToString(serialCommand, &logBuffer[pointer], SBGC_LOG_BUFF_SIZE - pointer);
			logBuffer[pointer] = ' ';
			pointer++;

		#endif

		#if (SBGC_LOG_COMMAND_PARAM && SBGC_NON_BLOCKING_MODE)

			if (serialCommand->parameters & SCParam_TX_CALLBACK) pointer += gSBGC->_ll->debugSprintf(&logBuffer[pointer], "(TC) ");
			if (serialCommand->parameters & SCParam_FORCE_CALLBACK) pointer += gSBGC->_ll->debugSprintf(&logBuffer[pointer], "(FC) ");
			if (serialCommand->parameters & SCParam_RETAIN) pointer += gSBGC->_ll->debugSprintf(&logBuffer[pointer], "(RT) ");

			#if (SBGC_USES_OS_SUPPORT)
				if (serialCommand->parameters & SCParam_FREEZE) pointer += gSBGC->_ll->debugSprintf(&logBuffer[pointer], "(FT) ");
			#endif

		#endif

		#if (SBGC_LOG_COMMAND_DATA)
			if ((serialCommand->_state == SCState_PROCESSED) && serialCommand->_payloadSize)
				pointer += gSBGC->_ll->debugSprintf(&logBuffer[pointer], "[%d]:", serialCommand->_payloadSize);

			else
		#endif

				logBuffer[pointer] = '\n';

		if (pointer >= SBGC_LOG_BUFF_SIZE)
			SerialAPI_FatalErrorHandler();

		DebugSBGC32_PrintMessage(gSBGC, logBuffer);

		#if (SBGC_LOG_COMMAND_DATA)

			if ((serialCommand->_state != SCState_PROCESSED) || (serialCommand->_payloadSize == 0))
				return;

			ui8 payloadSize = serialCommand->_payloadSize;
			ui8 payloadPacketSize = ((payloadSize * 4) > SBGC_LOG_BUFF_SIZE) ? SBGC_LOG_BUFF_SIZE : (payloadSize * 4);
			ui8 payloadOffset = 0;
			ui8 *payloadPointer = serialCommand->_payload;

			while (1)
			{
				memset(logBuffer, 0, sizeof(logBuffer));

				if (serialCommand->parameters & SCParam_RX)
				{
					for (pointer = 0; pointer < (payloadPacketSize / 4); pointer++)
					{
						if (((uintptr_t)payloadPointer) > calculateEndRx_())
							payloadPointer = gSBGC->_api->rxCommandBuff;

						gSBGC->_ll->debugSprintf(&logBuffer[pointer * 4], " x%02X", *payloadPointer);

						payloadPointer++;
					}
				}

				else
					for (pointer = 0; pointer < (payloadPacketSize / 4); pointer++)
						gSBGC->_ll->debugSprintf(&logBuffer[pointer * 4], " x%02X", *(serialCommand->_payload + payloadOffset + pointer));

				payloadSize -= (payloadPacketSize / 4);

				if (payloadSize)
				{
					payloadPacketSize = ((payloadSize * 4) > SBGC_LOG_BUFF_SIZE) ? SBGC_LOG_BUFF_SIZE : (payloadSize * 4);
					DebugSBGC32_PrintBuffer(gSBGC, logBuffer, SBGC_LOG_BUFF_SIZE - (SBGC_LOG_BUFF_SIZE % 4));
				}

				else
				/* Finish */
				{
					if (pointer < ((SBGC_LOG_BUFF_SIZE - (SBGC_LOG_BUFF_SIZE % 4)) / 4))
					{
						logBuffer[pointer * 4] = '\n';
						DebugSBGC32_PrintMessage(gSBGC, logBuffer);
					}

					else
					{
						DebugSBGC32_PrintBuffer(gSBGC, logBuffer, SBGC_LOG_BUFF_SIZE - (SBGC_LOG_BUFF_SIZE % 4));
						DebugSBGC32_PrintMessage(gSBGC, " \n");
					}

					break;
				}

				payloadOffset += (SBGC_LOG_BUFF_SIZE / 4);
			}

		#endif
	}


	/**	@brief	Links debug functions to internal
	 *			software system of the library
	 *
	 *	@note	Quasi-private function
	 *
	 *	@param	*gSBGC - serial connection descriptor
	 */
	void PrivateSerialAPI_LinkDebug (sbgcGeneral_t *gSBGC)
	{
		gSBGC->_api->log = DebugSBGC32_WriteLog;
	}

#endif
/**	@}
 */

#endif /* SBGC_NEED_DEBUG */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
