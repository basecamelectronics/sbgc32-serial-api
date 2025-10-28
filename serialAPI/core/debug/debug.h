/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2
 *
 *	@file		debug.h
 *
 *	@brief		Header file of the core debug functions
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
/**	____________________________________________________________________
 *
 *	@defgroup	Debug Debug Functions
 *	@ingroup	Core
 *		@brief	Debug Functions Module
 *	____________________________________________________________________
 */

#ifndef		CORE_DEBUG_H_
#define		CORE_DEBUG_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../sbgc32.h"


#if (SBGC_NEED_DEBUG)

	/**	@addtogroup	Debug
	 *	@{
	 */
	void DebugSBGC32_PrintMessage (sbgcGeneral_t *gSBGC, const char *str);
	void DebugSBGC32_PrintBuffer (sbgcGeneral_t *gSBGC, char *data, ui16 length);
	void DebugSBGC32_PrintStructElement (sbgcGeneral_t *gSBGC, void *pValue, const char *str, sbgcVarType_t vType);
	#if (SBGC_NEED_REF_INFO)
		void DebugSBGC32_PrintWholeStruct (sbgcGeneral_t *gSBGC, void *structure, sbgcParserMap_t parserMap);
	#endif
	/**	@}
	 */

#endif

/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

#endif		/* CORE_DEBUG_H_ */
