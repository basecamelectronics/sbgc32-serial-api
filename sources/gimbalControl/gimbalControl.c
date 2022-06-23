/** ____________________________________________________________________
 *
 *	@file		gimbalControl.c
 *
 *	@brief 		Gimbal control source file
 *	____________________________________________________________________
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

#include "gimbalControl.h"


#ifdef	SYS_BIG_ENDIAN

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *								Parser Big Endian Mapping Structures
	 */
	/**	@addtogroup	Control
	 * 	@{
	 */
	/** @brief	Sample for Big Endian Mapping
	 *
	 * 	@ref	UserControl_ParserStructDB
	 */
	const Control_t control_ParserStruct;

	const ParserBlock_t Control_ParserStructDB [] =
	{
		DATA_BLOCK(control_ParserStruct.controlMode),
		VAR_BLOCK(control_ParserStruct.AxisC[ROLL].speed),
		VAR_BLOCK(control_ParserStruct.AxisC[ROLL].angle),
		VAR_BLOCK(control_ParserStruct.AxisC[PITCH].speed),
		VAR_BLOCK(control_ParserStruct.AxisC[PITCH].angle),
		VAR_BLOCK(control_ParserStruct.AxisC[YAW].speed),
		VAR_BLOCK(control_ParserStruct.AxisC[YAW].angle),
	};

	const ui8 Control_ParserStructDB_Size = countof(Control_ParserStructDB);
	/**	@}
	 */


	/**	@addtogroup	Control_Config
	 * 	@{
	 */
	/** @brief	Sample for Big Endian Mapping
	 *
	 * 	@ref	controlConfig_ParserStructDB
	 */
	const ControlConfig_t controlConfig_ParserStruct;

	const ParserBlock_t ControlConfig_ParserStructDB [] =
	{
		VAR_BLOCK(controlConfig_ParserStruct.timeoutMS),
		VAR_BLOCK(controlConfig_ParserStruct.ch1_Priority),
		VAR_BLOCK(controlConfig_ParserStruct.ch2_Priority),
		VAR_BLOCK(controlConfig_ParserStruct.ch3_Priority),
		VAR_BLOCK(controlConfig_ParserStruct.ch4_Priority),
		VAR_BLOCK(controlConfig_ParserStruct.thisChPriority),
		VAR_BLOCK(controlConfig_ParserStruct.AxisCC[ROLL].angleLPF),
		VAR_BLOCK(controlConfig_ParserStruct.AxisCC[ROLL].speedLPF),
		VAR_BLOCK(controlConfig_ParserStruct.AxisCC[ROLL].RC_LPF),
		VAR_BLOCK(controlConfig_ParserStruct.AxisCC[ROLL].ACC_Limit),
		DATA_BLOCK(controlConfig_ParserStruct.AxisCC[ROLL].reserved1),
		VAR_BLOCK(controlConfig_ParserStruct.AxisCC[PITCH].angleLPF),
		VAR_BLOCK(controlConfig_ParserStruct.AxisCC[PITCH].speedLPF),
		VAR_BLOCK(controlConfig_ParserStruct.AxisCC[PITCH].RC_LPF),
		VAR_BLOCK(controlConfig_ParserStruct.AxisCC[PITCH].ACC_Limit),
		DATA_BLOCK(controlConfig_ParserStruct.AxisCC[PITCH].reserved1),
		VAR_BLOCK(controlConfig_ParserStruct.AxisCC[YAW].angleLPF),
		VAR_BLOCK(controlConfig_ParserStruct.AxisCC[YAW].speedLPF),
		VAR_BLOCK(controlConfig_ParserStruct.AxisCC[YAW].RC_LPF),
		VAR_BLOCK(controlConfig_ParserStruct.AxisCC[YAW].ACC_Limit),
		DATA_BLOCK(controlConfig_ParserStruct.AxisCC[YAW].reserved1),
		VAR_BLOCK(controlConfig_ParserStruct.RC_ExpoRate),
		VAR_BLOCK(controlConfig_ParserStruct.flags),
		DATA_BLOCK(controlConfig_ParserStruct.reserved2),
	};

	const ui8 ControlConfig_ParserStructDB_Size = countof(ControlConfig_ParserStructDB);
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
	/** When setting the ControlConfig_t.flags, may send confirmation */
	return generalSBGC->_ParserCurrentStatus;
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
 *	@param	*confirmationState - confirmation structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ControlConfig (GeneralSBGC_t *generalSBGC, const ControlConfig_t *controlConfig, ConfirmationState_t *confirmationState)
{
	if (generalSBGC->_firmwareVersion < 2610)
		return NOT_SUPPORTED_BY_FIRMWARE;

	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_CONTROL_CONFIG);
	WriteBuff(&cmd, controlConfig, sizeof(ControlConfig_t), PM_CONTROL_CONFIG);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, cmd.commandID);
	return generalSBGC->_ParserCurrentStatus;
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
	FOR_(i, VIRT_CHANNELS_QUANTITY) WriteWord(&cmd, API_VirtCh[i]);
	SBGC32_TX(generalSBGC, &cmd);
	/* no need confirmation */
	return generalSBGC->_ParserCurrentStatus;
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
	FOR_(i, chQuan) WriteWord(&cmd, API_VirtCh[i]);
	SBGC32_TX(generalSBGC, &cmd);
	/* no need confirmation */
	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
