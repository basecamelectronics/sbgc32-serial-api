/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.0
 *
 *	@file		parser.h
 *
 *	@brief		Header file of the core commands data parsing
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
 *	@defgroup	Data_Parse Data Parser
 *	@ingroup	Core
 *		@brief	Data Parser Module
 *	____________________________________________________________________
 */

#ifndef		CORE_PARSER_H_
#define		CORE_PARSER_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../sbgc32.h"


/**	@addtogroup	Data_Parse
 *	@{
 */
/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								  Service Structures
 */
#if (SBGC_USES_REF_INFO)

	/**	@brief	Parser auxiliary data structure type
	 */
	typedef struct
	{
		#if (SBGC_NEED_REF_INFO)
			char			*name;					/*!<  Parameter name																*/
		#endif

		sbgcVarType_t		type;					/*!<  Parameter type as variable													*/
		ui8					length;					/*!<  Parameter length as variable													*/

	}	sbgcParameterReferenceInfo_t;

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								 Function Prototypes
 */
#if (SBGC_USES_REF_INFO)
	void *ParserSBGC32_GetElementAddress (const void* structure, sbgcParserMap_t parserMap, ui8 num);
#endif
ui8 ParserSBGC32_ConvertSerialStatusToString (serialAPI_CommandStatus_t serialStatus, char *str, ui8 size);
ui8 ParserSBGC32_ConvertCommunicationStatusToString (sbgcCommandStatus_t communicationStatus, char *str, ui8 size);
ui8 ParserSBGC32_ConvertCommandID_ToString (serialAPI_Command_t *cmd, char *str, ui8 size);
ui8 ParserSBGC32_ConvertCommandStatusToString (serialAPI_Command_t *cmd, char *str, ui8 size);
void ParserSBGC32_FormatBoardVersion (sbgcGeneral_t *gSBGC, ui8 boardVer, char *pBuff, ui8 size);
void ParserSBGC32_FormatFirmwareVersion (sbgcGeneral_t *gSBGC, ui16 firmwareVer, char *pBuff, ui8 size);
/**	@}
 */

/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

#endif		/* CORE_PARSER_H_ */
