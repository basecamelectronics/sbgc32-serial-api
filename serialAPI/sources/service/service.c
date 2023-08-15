/** ____________________________________________________________________
 *
 * 	SBGC32 Serial API Library v1.1
 *
 *	@file		service.c
 *
 *	@brief 		Service source file
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


#if (SBGC_SERVICE_MODULE)

#if (SYS_BIG_ENDIAN || SBGC_REF_INFO)

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *					Big Endian Mapping and Reference Info Structures
	 */
	/**	@addtogroup	Board_Info
	 * 	@{
	 */
	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t boardInfoReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Board Ver",				_UNSIGNED_CHAR_				),  // 0
		PARAM_BLOCK_(	"Firmware Ver",				_UNSIGNED_SHORT_			),  // 1
		PARAM_BLOCK_(	"State Flags 1",			(_UNSIGNED_CHAR_ | _FLAG_)	),  // 2
		PARAM_BLOCK_(	"Board Features",			(_UNSIGNED_SHORT_ | _FLAG_)	),  // 3
		PARAM_BLOCK_(	"Connection Flag",			(_UNSIGNED_CHAR_ | _FLAG_)	),  // 4
		PARAM_BLOCK_(	"Frw Extra ID",				_UNSIGNED_INT_				),  // 5
		PARAM_BLOCK_(	"Board Features Ext",		_UNSIGNED_SHORT_			),  // 6
		PARAMS_BLOCK_(	"Reserved",					_RESERVED_CHAR_,		3	),  // 7
		PARAM_BLOCK_(	"Base Frw Ver",				_UNSIGNED_SHORT_			),  // 8

	};

	const ui8 boardInfoReferenceInfoArrayElCnt = countof_(boardInfoReferenceInfoArray);


	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t boardInfo3_ReferenceInfoArray [] =
	{
		PARAMS_BLOCK_(	"Device ID",				_UNSIGNED_CHAR_,		9	),  // 0
		PARAMS_BLOCK_(	"MCU ID",					_UNSIGNED_CHAR_,		12	),  // 1
		PARAM_BLOCK_(	"EEPROM Size",				_UNSIGNED_INT_				),  // 2
		PARAM_BLOCK_(	"Script Slot 1 Size",		_UNSIGNED_SHORT_			),  // 3
		PARAM_BLOCK_(	"Script Slot 2 Size",		_UNSIGNED_SHORT_			),  // 4
		PARAM_BLOCK_(	"Script Slot 3 Size",		_UNSIGNED_SHORT_			),  // 5
		PARAM_BLOCK_(	"Script Slot 4 Size",		_UNSIGNED_SHORT_			),  // 6
		PARAM_BLOCK_(	"Script Slot 5 Size",		_UNSIGNED_SHORT_			),  // 7
		PARAM_BLOCK_(	"Profile Set Slots",		_UNSIGNED_CHAR_				),  // 8
		PARAM_BLOCK_(	"Profile Set Cur",			_UNSIGNED_CHAR_				),  // 9
		PARAM_BLOCK_(	"Flash Size",				_UNSIGNED_CHAR_				),  // 10
		PARAMS_BLOCK_(	"Reserved",					_RESERVED_CHAR_,		31	),  // 11

	};

	const ui8 boardInfo3_ReferenceInfoArrayElCnt = countof_(boardInfo3_ReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Auto_PID
	 * 	@{
	 */
	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t autoPID_ReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Profile ID",				_UNSIGNED_CHAR_				),  // 0
		PARAM_BLOCK_(	"Cfg Flags",				_UNSIGNED_CHAR_				),  // 1
		PARAM_BLOCK_(	"Gain VS Stability",		_UNSIGNED_CHAR_				),  // 2
		PARAM_BLOCK_(	"Momentum",					_UNSIGNED_CHAR_				),  // 3
		PARAM_BLOCK_(	"Action",					_UNSIGNED_CHAR_				),  // 4
		PARAMS_BLOCK_(	"Reserved",					_RESERVED_CHAR_,		14	),  // 5

	};

	const ui8 autoPID_ReferenceInfoArrayElCnt = countof_(autoPID_ReferenceInfoArray);


	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t autoPID2_ReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Action",					_UNSIGNED_CHAR_				),  // 0
		PARAMS_BLOCK_(	"Reserved 1",				_RESERVED_CHAR_,		10	),  // 1
		PARAM_BLOCK_(	"Cfg Version",				_UNSIGNED_CHAR_				),  // 2
		PARAM_BLOCK_(	"Axis Flag [ROLL]",			(_UNSIGNED_CHAR_ | _FLAG_)	),  // 3
		PARAM_BLOCK_(	"Gain [ROLL]",				_UNSIGNED_CHAR_				),  // 4
		PARAM_BLOCK_(	"Stimulus [ROLL]",			_UNSIGNED_CHAR_				),  // 5
		PARAM_BLOCK_(	"Effective Freq [ROLL]",	_UNSIGNED_CHAR_				),  // 6
		PARAM_BLOCK_(	"Problem Freq [ROLL]",		_UNSIGNED_CHAR_				),  // 7
		PARAM_BLOCK_(	"Problem Margin [ROLL]",	_UNSIGNED_CHAR_				),  // 8
		PARAMS_BLOCK_(	"Reserved 2",				_UNSIGNED_CHAR_,		6	),  // 9
		PARAM_BLOCK_(	"Axis Flag [PITCH]",		(_UNSIGNED_CHAR_ | _FLAG_)	),  // 10
		PARAM_BLOCK_(	"Gain [PITCH]",				_UNSIGNED_CHAR_				),  // 11
		PARAM_BLOCK_(	"Stimulus [PITCH]",			_UNSIGNED_CHAR_				),  // 12
		PARAM_BLOCK_(	"Effective Freq [PITCH]",	_UNSIGNED_CHAR_				),  // 13
		PARAM_BLOCK_(	"Problem Freq [PITCH]",		_UNSIGNED_CHAR_				),  // 14
		PARAM_BLOCK_(	"Problem Margin [PITCH]",	_UNSIGNED_CHAR_				),  // 15
		PARAMS_BLOCK_(	"Reserved 2",				_UNSIGNED_CHAR_,		6	),  // 16
		PARAM_BLOCK_(	"Axis Flag [YAW]",			(_UNSIGNED_CHAR_ | _FLAG_)	),  // 17
		PARAM_BLOCK_(	"Gain [YAW]",				_UNSIGNED_CHAR_				),  // 18
		PARAM_BLOCK_(	"Stimulus [YAW]",			_UNSIGNED_CHAR_				),  // 19
		PARAM_BLOCK_(	"Effective Freq [YAW]",		_UNSIGNED_CHAR_				),  // 20
		PARAM_BLOCK_(	"Problem Freq [YAW]",		_UNSIGNED_CHAR_				),  // 21
		PARAM_BLOCK_(	"Problem Margin [YAW]",		_UNSIGNED_CHAR_				),  // 22
		PARAMS_BLOCK_(	"Reserved 2",				_UNSIGNED_CHAR_,		6	),  // 23
		PARAM_BLOCK_(	"General Flags",			(_UNSIGNED_SHORT_ | _FLAG_)	),  // 24
		PARAM_BLOCK_(	"Startup Cfg",				(_UNSIGNED_CHAR_ | _FLAG_)	),  // 25
		PARAMS_BLOCK_(	"Reserved 3",				_RESERVED_CHAR_,		22	),  // 26

	};

	const ui8 autoPID2_ReferenceInfoArrayElCnt = countof_(autoPID2_ReferenceInfoArray);


	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t autoPID_StateReferenceInfoArray [] =
	{
		PARAMS_BLOCK_(	"P",						_UNSIGNED_CHAR_,		3	),  // 0
		PARAMS_BLOCK_(	"I",						_UNSIGNED_CHAR_,		3	),  // 1
		PARAMS_BLOCK_(	"D",						_UNSIGNED_CHAR_,		3	),  // 2
		PARAMS_BLOCK_(	"LPF Freq",					_UNSIGNED_SHORT_,		3	),  // 3
		PARAM_BLOCK_(	"Iteration Cnt",			_UNSIGNED_SHORT_			),  // 4
		PARAM_BLOCK_(	"Tracking Error [ROLL]",	_FLOAT_						),  // 5
		PARAMS_BLOCK_(	"Reserved 1",				_RESERVED_CHAR_,		6	),  // 6
		PARAM_BLOCK_(	"Tracking Error [PITCH]",	_FLOAT_						),  // 7
		PARAMS_BLOCK_(	"Reserved 1",				_RESERVED_CHAR_,		6	),  // 8
		PARAM_BLOCK_(	"Tracking Error [YAW]",		_FLOAT_						),  // 9
		PARAMS_BLOCK_(	"Reserved 1",				_RESERVED_CHAR_,		6	),  // 10
		PARAMS_BLOCK_(	"Reserved 2",				_RESERVED_CHAR_,		10	),  // 11

	};

	const ui8 autoPID_StateReferenceInfoArrayElCnt = countof_(autoPID_StateReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Scripts
	 * 	@{
	 */
	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t scriptDebugInfoReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Cur Com Counter",			_UNSIGNED_SHORT_			),  // 0
		PARAM_BLOCK_(	"Err Core",					_UNSIGNED_CHAR_				),  // 1

	};

	const ui8 scriptDebugInfoReferenceInfoArrayElCnt = countof_(scriptDebugInfoReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	State_Vars
	 * 	@{
	 */
	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t stateVarsReferenceInfoArray [] =
	{
		PARAMS_BLOCK_(	"Step Signal Vars",			_UNSIGNED_CHAR_,		6	),  // 0
		PARAM_BLOCK_(	"Sub Error",				_UNSIGNED_CHAR_				),  // 1
		PARAM_BLOCK_(	"Max Acc",					_UNSIGNED_CHAR_				),  // 2
		PARAM_BLOCK_(	"Work Time",				_UNSIGNED_INT_				),  // 3
		PARAM_BLOCK_(	"Startup Cnt",				_UNSIGNED_SHORT_			),  // 4
		PARAM_BLOCK_(	"Max Current",				_UNSIGNED_SHORT_			),  // 5
		PARAM_BLOCK_(	"IMU Temp Main",			_UNSIGNED_CHAR_				),  // 6
		PARAM_BLOCK_(	"IMU Temp Max",				_UNSIGNED_CHAR_				),  // 7
		PARAM_BLOCK_(	"MCU Temp Min",				_UNSIGNED_CHAR_				),  // 8
		PARAM_BLOCK_(	"MCU Temp Max",				_UNSIGNED_CHAR_				),  // 9
		PARAMS_BLOCK_(	"Shock Cnt",				_UNSIGNED_CHAR_,		4	),  // 10
		PARAM_BLOCK_(	"Energy Time",				_UNSIGNED_INT_				),  // 11
		PARAM_BLOCK_(	"Energy",					_FLOAT_						),  // 12
		PARAM_BLOCK_(	"Avg Current Time",			_UNSIGNED_INT_				),  // 13
		PARAM_BLOCK_(	"Avg Current",				_FLOAT_						),  // 14
		PARAMS_BLOCK_(	"Reserved",					_RESERVED_CHAR_,		152	),  // 15

	};

	const ui8 stateVarsReferenceInfoArrayElCnt = countof_(stateVarsReferenceInfoArray);
	/**	@}
	 */

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	Board_Info
 * 	@{
 */
/**	@brief	Reads version and board information
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*boardInfo - structure storing board information
 *	@param	cfg - configuration for this serial driver
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ReadBoardInfo (GeneralSBGC_t *generalSBGC, BoardInfo_t *boardInfo, ui16 cfg)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_BOARD_INFO);
	WriteWord(&cmd, cfg);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_BOARD_INFO), "Board Info:") == TX_RX_OK)
		ReadBuff(&cmd, boardInfo, sizeof(BoardInfo_t), PM_BOARD_INFO);

	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Reads additional board information
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*boardInfo3 - structure storing additional board information
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ReadBoardInfo3 (GeneralSBGC_t *generalSBGC, BoardInfo3_t *boardInfo3)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_BOARD_INFO_3);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_BOARD_INFO_3), "Board Info 3:") == TX_RX_OK)
		ReadBuff(&cmd, boardInfo3, sizeof(BoardInfo3_t), PM_BOARD_INFO_3);

	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Auto_PID
 * 	@{
 */
/**	@brief	Starts automatic PID calibration
 *
 *	@note	When finished, the controller sends
 *			a full set of tuned parameters:\n
 *			See @ref Profile_Params_Ext,\n
 *			@ref Profile_Params_Ext_2 and\n
 *			@ref Profile_Params_Ext_3 modules.\n
 *			To interrupt currently running auto-tuning process
 *			send this command with zero values in autoPID structure
 *			or use @ref SBGC32_BreakAutoPID_Tuning function
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*autoPID - structure with written auto-PID configurations
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_TuneAutoPID (GeneralSBGC_t *generalSBGC, const AutoPID_t *autoPID)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_AUTO_PID);
	WriteBuff(&cmd, autoPID, sizeof(AutoPID_t), PM_AUTO_PID);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Interrupts PID tuning
 *
 *	@note	Applies to @ref SBGC32_TuneAutoPID function
 *
 *	@param	*generalSBGC - serial connection descriptor
 *
 *	@return	Communication status
 */
TxRxStatus_t SBGC32_BreakAutoPID_Tuning (GeneralSBGC_t *generalSBGC)
{
	AutoPID_t AutoPID = {0};
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_AUTO_PID);
	WriteBuff(&cmd, &AutoPID, sizeof(AutoPID_t), PM_AUTO_PID);
	SBGC32_TX(generalSBGC, &cmd);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Starts automatic PID calibration ver. 2
 *
 *	@attention	Firmware: 2.70+
 *
 *	@note	When finished, the controller sends
 *			a full set of tuned parameters:\n
 *			See @ref Profile_Params_Ext,\n
 *			@ref Profile_Params_Ext_2 and\n
 *			@ref Profile_Params_Ext_3 modules
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*autoPID2 - structure with written auto-PID configurations
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_TuneAutoPID2 (GeneralSBGC_t *generalSBGC, const AutoPID2_t *autoPID2)
{
	#if (SBGC_DEBUG_MODE == SET_OFF)

		if (generalSBGC->_firmwareVersion < 2700)
			return NOT_SUPPORTED_BY_FIRMWARE;

	#endif

	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_AUTO_PID2);
	WriteBuff(&cmd, autoPID2, sizeof(AutoPID2_t), PM_AUTO_PID_2);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Parses progress of PID auto tuning data
 *
 *	@param	*cmd - SerialCommand structure, receiving
 *			progress of PID auto tuning realtime data
 *	@param	*autoPID_State - structure storing progress of PID
 */
void SBGC32_ParseAutoPID_StateCmd (SerialCommand_t *cmd, AutoPID_State_t *autoPID_State)
{
	cmd->readPos = 0;
	ReadBuff(cmd, autoPID_State, sizeof(AutoPID_State_t), PM_AUTO_PID_STATE);
}
/**	@}
 */


/**	@addtogroup	Motors_State
 * 	@{
 */
/**	@brief	Switches motors ON
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_SetMotorsON (GeneralSBGC_t *generalSBGC)
{
	SBGC32_SendEmptyCommand(generalSBGC, CMD_MOTORS_ON);
	SBGC32_CheckConfirmation(generalSBGC, CMD_MOTORS_ON);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Switches motors OFF
 *
 *	@attention	Firmware: 2.68b7+ for parameter "mode"
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 * 	@param	mode - possible way for turn off motors
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_SetMotorsOFF (GeneralSBGC_t *generalSBGC, MotorsMode_t mode)
{
	#if (SBGC_DEBUG_MODE == SET_OFF)

		if (generalSBGC->_firmwareVersion < 2687)
			return NOT_SUPPORTED_BY_FIRMWARE;

	#endif

	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_MOTORS_OFF);
	WriteByte(&cmd, mode);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Boot_Mode
 * 	@{
 */
/**	@brief	Enters bootloader mode to upload firmware
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_SetBootMode (GeneralSBGC_t *generalSBGC)
{
	SBGC32_SendEmptyCommand(generalSBGC, CMD_BOOT_MODE_3);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Enters bootloader mode to upload firmware
 * 			in extended format
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *	@param	confirm - yes/no confirmation after reset
 *	@param	delayMs - waiting for a given time before reset
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_SetBootModeExt (GeneralSBGC_t *generalSBGC, Boolean_t confirm, ui16 delayMs)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_BOOT_MODE_3);
	WriteByte(&cmd, confirm);
	WriteWord(&cmd, delayMs);
	SBGC32_TX(generalSBGC, &cmd);
	if (confirm == TRUE__)
		SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Resets device
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *	@param	flag - reset action
 *	@param	delayMs - waiting for a given time before reset
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_Reset (GeneralSBGC_t *generalSBGC, ResetFlag_t flag, ui16 delayMs)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_RESET);
	WriteByte(&cmd, flag);
	WriteWord(&cmd, delayMs);
	SBGC32_TX(generalSBGC, &cmd);
	/* Confirmation is processed manually */
	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Scripts
 * 	@{
 */
/**	@brief	Start or stop user-written script
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *	@param	mode - script's action
 *	@param	slot - script's slot
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_RunScript (GeneralSBGC_t *generalSBGC, ScriptMode_t mode, ScriptSlotNum_t slot)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_RUN_SCRIPT);
	WriteByte(&cmd, mode);
	WriteByte(&cmd, slot);
	WriteEmptyBuff(&cmd, 32);  // reserved[32]
	SBGC32_TX(generalSBGC, &cmd);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Parses script debug information data
 *
 *	@param	*cmd - SerialCommand structure, receiving
 *			script debug information realtime data
 *	@param	*scriptDebugInfo - structure storing
 *			script debug information
 */
void SBGC32_ParseScriptDebugInfoCmd (SerialCommand_t *cmd, ScriptDebugInfo_t *scriptDebugInfo)
{
	cmd->readPos = 0;
	scriptDebugInfo->curComCounter = ReadWord(cmd);
	scriptDebugInfo->errCode = ReadByte(cmd);
}
/**	@}
 */


/**	@addtogroup	State_Vars
 * 	@{
 */
/**	@brief	Writes system persistent state variables, cumulative
 * 			statistics and maintenance data
 *
 * 	@attention	Firmware: 2.68b7+ ("Extended" family only)
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *	@param	*stateVars - structure with written var state parameters
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_WriteStateVars (GeneralSBGC_t *generalSBGC, const StateVars_t *stateVars)
{
	#if (SBGC_DEBUG_MODE == SET_OFF)

		if (generalSBGC->_firmwareVersion < 2687)
			return NOT_SUPPORTED_BY_FIRMWARE;

	#endif

	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_WRITE_STATE_VARS);
	WriteBuff(&cmd, stateVars, sizeof(StateVars_t), PM_STATE_VARS);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Request reading system persistent state variables, cumulative
 * 			statistics and maintenance data
 *
 * 	@attention	Firmware: 2.68b7+ ("Extended" family only)
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *	@param	*stateVars - structure for storing var state parameters
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ReadStateVars (GeneralSBGC_t *generalSBGC, StateVars_t *stateVars)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_READ_STATE_VARS);
	SBGC32_TX_RX(generalSBGC, &cmd, CMD_READ_STATE_VARS);
	ReadBuff(&cmd, stateVars, sizeof(StateVars_t), PM_STATE_VARS);
	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Service_Other
 * 	@{
 */
/**	@brief	Parse event message
 *
 *	@attention	Firmware: 2.65+
 *
 *	@param	*cmd - SerialCommand structure,
*			receiving event data
 *	@param	*event - structure storing event data
 */
void SBGC32_ParseEventCmd (SerialCommand_t *cmd, Event_t *event)
{
	if (cmd->readPos != 0)
		cmd->readPos = 0;

	ReadBuff(cmd, event, sizeof(Event_t), PM_DEFAULT_8BIT);
}


/**	@brief	Trigger output pin
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	pinID - trigger pin identifier
 *	@param	state - the physical state of the pin
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_SetTriggerPin (GeneralSBGC_t *generalSBGC, TriggerPinID_t pinID, PinState_t state)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_TRIGGER_PIN);
	WriteByte(&cmd, pinID);
	WriteByte(&cmd, state);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	/* Pin doesn't must be occupied for other functions and was really triggered */
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Execute menu command
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	cmdID - menu command identifier
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ExecuteMenu (GeneralSBGC_t *generalSBGC, MenuCommand_t cmdID)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_EXECUTE_MENU);
	WriteByte(&cmd, cmdID);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Set output PWM signal on the specified pins
 *
 *	@attention	Although command takes 8 values, the real
 *				number of hardware outputs depends on
 *				board version and may be less
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*servoTime - array with PWM duty cycle
 *			values for each output
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_SetServoOut (GeneralSBGC_t *generalSBGC, const i16 servoTime [8])
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_SERVO_OUT);
	for (ui8 i = 0; i < 8; i++) WriteWord(&cmd, servoTime[i]);
	SBGC32_TX(generalSBGC, &cmd);
	/* no need confirmation */
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Play melody by motors or emit standard beep sound
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*beeperSettings - structure with prescribed
 *			beeper playback settings
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_PlayBeeper (GeneralSBGC_t *generalSBGC, const BeeperSettings_t *beeperSettings)
{
    SerialCommand_t cmd;
    InitCmdWrite(&cmd, CMD_BEEP_SOUND);
    WriteWord(&cmd, beeperSettings->mode);
    WriteByte(&cmd, beeperSettings->noteLength);
    WriteByte(&cmd, beeperSettings->decayFactor);
	WriteEmptyBuff(&cmd, 8);  // reserved[8]

    if (beeperSettings->mode == BM_BEEPER_MODE_CUSTOM_MELODY)
    	for (ui8 i = 0; i < beeperSettings->notesQuan; i++)
    		WriteWord(&cmd, beeperSettings->notesFreqHz[i]);

    SBGC32_TX(generalSBGC, &cmd);
    /* no need confirmation */
    return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Signs the user's message
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	signType - set of keys to be used
 *	@param	*txMessage - the user's input message
 *	@param	*rxMessage - signed message
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_SignMessage (GeneralSBGC_t *generalSBGC, ui8 signType, const char txMessage [MAX_MESSAGE_LENGTH], char rxMessage [MAX_MESSAGE_LENGTH])
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_SIGN_MESSAGE);
	WriteByte(&cmd, signType);
	WriteBuff(&cmd, txMessage, MAX_MESSAGE_LENGTH, PM_DEFAULT_8BIT);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_SIGN_MESSAGE), "Sign Message:") == TX_RX_OK)
		ReadBuff(&cmd, rxMessage, MAX_MESSAGE_LENGTH, PM_DEFAULT_8BIT);

	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */

#endif /* SBGC_SERVICE_MODULE */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
