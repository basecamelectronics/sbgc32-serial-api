/** ____________________________________________________________________
 *
 * 	SBGC32 Serial API Library v1.1
 *
 *	@file		gimbalControl.c
 *
 *	@brief 		Gimbal control source file
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


#if (SBGC_CONTROL_MODULE)

#if (SYS_BIG_ENDIAN || SBGC_REF_INFO)

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *					Big Endian Mapping and Reference Info Structures
	 */
	/**	@addtogroup	Control
	 * 	@{
	 */
	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t controlReferenceInfoArray [] =
	{
		PARAMS_BLOCK_(	"Control Mode",				_UNSIGNED_CHAR_,		3	),  // 0
		PARAM_BLOCK_(	"Speed [ROLL]",				_SIGNED_SHORT_				),  // 1
		PARAM_BLOCK_(	"Angle [ROLL]",				_SIGNED_SHORT_				),  // 2
		PARAM_BLOCK_(	"Speed [PITCH]",			_SIGNED_SHORT_				),  // 3
		PARAM_BLOCK_(	"Angle [PITCH]",			_SIGNED_SHORT_				),  // 4
		PARAM_BLOCK_(	"Speed [YAW]",				_SIGNED_SHORT_				),  // 5
		PARAM_BLOCK_(	"Angle [YAW]",				_SIGNED_SHORT_				),  // 6

	};

	const ui8 controlReferenceInfoArrayElCnt = countof_(controlReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Control_Config
	 * 	@{
	 */
	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t controlConfigReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Timeout Ms",				_UNSIGNED_SHORT_			),  // 0
		PARAM_BLOCK_(	"Ch1 Priority",				_UNSIGNED_CHAR_				),  // 1
		PARAM_BLOCK_(	"Ch2 Priority",				_UNSIGNED_CHAR_				),  // 2
		PARAM_BLOCK_(	"Ch3 Priority",				_UNSIGNED_CHAR_				),  // 3
		PARAM_BLOCK_(	"Ch4 Priority",				_UNSIGNED_CHAR_				),  // 4
		PARAM_BLOCK_(	"This Ch Priority",			_UNSIGNED_CHAR_				),  // 5
		PARAM_BLOCK_(	"Angle LPF [ROLL]",			_UNSIGNED_CHAR_				),  // 6
		PARAM_BLOCK_(	"Speed LPF [ROLL]",			_UNSIGNED_CHAR_				),  // 7
		PARAM_BLOCK_(	"RC LPF [ROLL]",			_UNSIGNED_CHAR_				),  // 8
		PARAM_BLOCK_(	"Acc Limit [ROLL]",			_UNSIGNED_SHORT_			),  // 9
		PARAMS_BLOCK_(	"Reserved 1",				_RESERVED_CHAR_,		2	),  // 10
		PARAM_BLOCK_(	"Angle LPF [PITCH]",		_UNSIGNED_CHAR_				),  // 11
		PARAM_BLOCK_(	"Speed LPF [PITCH]",		_UNSIGNED_CHAR_				),  // 12
		PARAM_BLOCK_(	"RC LPF [PITCH]",			_UNSIGNED_CHAR_				),  // 13
		PARAM_BLOCK_(	"Acc Limit [PITCH]",		_UNSIGNED_SHORT_			),  // 14
		PARAMS_BLOCK_(	"Reserved 1",				_RESERVED_CHAR_,		2	),  // 15
		PARAM_BLOCK_(	"Angle LPF [YAW]",			_UNSIGNED_CHAR_				),  // 16
		PARAM_BLOCK_(	"Speed LPF [YAW]",			_UNSIGNED_CHAR_				),  // 17
		PARAM_BLOCK_(	"RC LPF [YAW]",				_UNSIGNED_CHAR_				),  // 18
		PARAM_BLOCK_(	"Acc Limit [YAW]",			_UNSIGNED_SHORT_			),  // 19
		PARAMS_BLOCK_(	"Reserved 1",				_RESERVED_CHAR_,		2	),  // 20

		PARAM_BLOCK_(	"RC Expo Rate",				_UNSIGNED_CHAR_				),  // 21
		PARAM_BLOCK_(	"Flags",					(_UNSIGNED_SHORT_ | _FLAG_)	),  // 22
		PARAMS_BLOCK_(	"Reserved 2",				_RESERVED_CHAR_,		10	),  // 23

	};

	const ui8 controlConfigReferenceInfoArrayElCnt = countof_(controlConfigReferenceInfoArray);
	/**	@}
	 */

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	Control
 * 	@{
 */
/**	@brief	Controls gimbal movement
 *
 *	@note	If ControlConfig_t.flags is set to
 *			RTCCF_CONTROL_CONFIG_FLAG_CONFIRM,
 *			SBGC32 will send confirmation commands
 *			after each successful transfer
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 * 	@param 	*control - structure containing gimbal control data
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_Control (GeneralSBGC_t *generalSBGC, const Control_t *control)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_CONTROL);
	WriteBuff(&cmd, control, sizeof(Control_t), PM_CONTROL);
	SBGC32_TX(generalSBGC, &cmd);
	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Control_Config
 * 	@{
 */
/** @brief	Configure the handling of CMD_CONTROL command
 *
 *	@attention	Firmware: 2.61+
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 * 	@param 	*controlConfig - structure containing gimbal
 * 			control configuration data
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ControlConfig (GeneralSBGC_t *generalSBGC, const ControlConfig_t *controlConfig)
{
	#if (SBGC_DEBUG_MODE == SET_OFF)

		if (generalSBGC->_firmwareVersion < 2610)
			return NOT_SUPPORTED_BY_FIRMWARE;

	#endif

	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_CONTROL_CONFIG);
	WriteBuff(&cmd, controlConfig, sizeof(ControlConfig_t), PM_CONTROL_CONFIG);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Virt_Channels
 * 	@{
 */
/**	@brief	Sets all virtual channels
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *	@param	*API_VirtCh - array with written virtual channel values
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_SetAPI_VirtChControl (GeneralSBGC_t *generalSBGC, const i16 API_VirtCh [VIRT_CHANNELS_QUANTITY])
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_API_VIRT_CH_CONTROL);
	for (ui8 i = 0; i < VIRT_CHANNELS_QUANTITY; i++) WriteWord(&cmd, API_VirtCh[i]);
	SBGC32_TX(generalSBGC, &cmd);
	/* no need confirmation */
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Sets certain number of virtual channels
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *	@param	*API_VirtCh - array with written virtual channel
 *			values in high resolution
 *	@param	chQuan - number of virtual channels
 *			starting with API_VIRT_CH_1
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_SetAPI_VirtChHR_Control (GeneralSBGC_t *generalSBGC, const i16 *API_VirtCh, ui8 chQuan)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_API_VIRT_CH_HIGH_RES);
	for (ui8 i = 0; i< chQuan; i++) WriteWord(&cmd, API_VirtCh[i]);
	SBGC32_TX(generalSBGC, &cmd);
	/* no need confirmation */
	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */

#endif /* SBGC_CONTROL_MODULE */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
