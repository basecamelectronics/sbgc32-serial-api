/** ____________________________________________________________________
 *
 *	@file		adjvar.c
 *
 *	@brief 		Adjustable variables source file
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

#include "adjvar.h"


#ifdef SBGC_DEBUG_MODE

	/**	@addtogroup	Adjvar
	 * 	@{
	 */
	/** @brief	Global Adjustable Variables Auxiliary Array
	 */
	const AdjVarsDebugInfo_t AdjVarsDebugInfoArray [] =
	/*
	||			   ENUM ID + NAME					 || MIN VALUE || MAX VALUE || 		TYPE		||
	 */
	{ { ADJ_VAR_BLOCK(ADJ_VAR_P_ROLL), 						0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_P_PITCH), 					0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_P_YAW), 						0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_I_ROLL), 						0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_I_PITCH), 					0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_I_YAW), 						0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_D_ROLL), 						0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_D_PITCH), 					0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_D_YAW), 						0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_POWER_ROLL), 					0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_POWER_PITCH), 				0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_POWER_YAW), 					0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_ACC_LIMITER), 				0, 			1275, 		_UNSIGNED_SHORT_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_FOLLOW_SPEED_ROLL),	 		0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_FOLLOW_SPEED_PITCH), 			0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_FOLLOW_SPEED_YAW), 			0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_FOLLOW_LPF_ROLL), 			0, 			15, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_FOLLOW_LPF_PITCH), 			0, 			15, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_FOLLOW_LPF_YAW), 				0, 			15, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_RC_SPEED_ROLL), 				0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_RC_SPEED_PITCH), 				0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_RC_SPEED_YAW), 				0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_RC_LPF_ROLL), 				0, 			255,	 	_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_RC_LPF_PITCH), 				0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_RC_LPF_YAW), 					0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_RC_TRIM_ROLL), 				-127, 		127, 		_SIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_RC_TRIM_PITCH), 				-127, 		127, 		_SIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_RC_TRIM_YAW), 				-127, 		127, 		_SIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_RC_DEADBAND), 				0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_RC_EXPO_RATE), 				0, 			100, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_FOLLOW_PITCH), 				0, 			1, 			_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_RC_FOLLOW_YAW_PITCH), 		0, 			2, 			_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_FOLLOW_DEADBAND), 			0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_FOLLOW_EXPO_RATE), 			0, 			100, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_FOLLOW_ROLL_MIX_START), 		0, 			90, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_FOLLOW_ROLL_MIX_RANGE), 		0, 			90, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_GYRO_TRUST), 					0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_FRAME_HEADING), 				-1800, 		1800, 		_SIGNED_SHORT_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_GYRO_HEADING_CORR), 			-20000, 	20000, 		_SIGNED_SHORT_
	},{	ADJ_VAR_BLOCK(ADJ_VAL_ACC_LIMITER_ROLL),			0, 			1275, 		_UNSIGNED_SHORT_
	},{ ADJ_VAR_BLOCK(ADJ_VAL_ACC_LIMITER_PITCH), 			0, 			1275, 		_UNSIGNED_SHORT_
	},{	ADJ_VAR_BLOCK(ADJ_VAL_ACC_LIMITER_YAW), 			0, 			1275, 		_UNSIGNED_SHORT_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_PID_GAIN_ROLL), 				0, 			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_PID_GAIN_PITCH), 				0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_PID_GAIN_YAW), 				0,		 	255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_LPF_FREQ_ROLL), 				10, 		400, 		_UNSIGNED_SHORT_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_LPF_FREQ_PITCH),				10, 		400, 		_UNSIGNED_SHORT_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_LPF_FREQ_YAW), 				10, 		400, 		_UNSIGNED_SHORT_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_TIMELAPSE_TIME), 				1, 			3600, 		_UNSIGNED_SHORT_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_MAV_CTRL_MODE), 				0, 			2, 			_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_H_CORR_FACTOR), 				0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_SW_LIM_MIN_ROLL), 			-3600, 		3600, 		_SIGNED_SHORT_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_SW_LIM_MAX_ROLL), 			-3600, 		3600, 		_SIGNED_SHORT_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_SW_LIM_MIN_PITCH), 			-3600, 		3600, 		_SIGNED_SHORT_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_SW_LIM_MAX_PITCH), 			-3600, 		3600, 		_SIGNED_SHORT_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_SW_LIM_MIN_YAW), 				-3600, 		3600,	 	_SIGNED_SHORT_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_SW_LIM_MAX_YAW), 				-3600, 		3600, 		_SIGNED_SHORT_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_FOLLOW_RANGE_ROLL), 			0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_FOLLOW_RANGE_PITCH), 			0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_FOLLOW_RANGE_YAW), 			0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_AUTO_PID_TARGET), 			0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_RC_MODE_ROLL), 				0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_RC_MODE_PITCH), 				0, 			255, 		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK(ADJ_VAR_RC_MODE_YAW), 				0, 			255, 		_UNSIGNED_CHAR_
	},{ ADJ_VAR_BLOCK(ADJ_VAR_EULER_ORDER), 				0, 			255,		_UNSIGNED_CHAR_

	}};
	/**	@}
	 */

#endif

#ifdef	SYS_BIG_ENDIAN

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *								Parser Big Endian Mapping Structures
	 */
	/**	@addtogroup	Adjvar_State
	 * 	@{
	 */
	/** @brief	Sample for Big Endian Mapping
	 *
	 * 	@ref	AdjVarsStateOldTx_ParserStructDB \n
	 * 	@ref	AdjVarsStateOldRx_ParserStructDB \n
	 * 	@ref	AdjVarsStateTx_ParserStructDB \n
	 * 	@ref	AdjVarsStateRx_ParserStructDB
	 */
	const AdjVarsState_t adjVarsState_ParserStruct;

	const ParserBlock_t AdjVarsStateOldTx_ParserStructDB [] =
	{
		VAR_BLOCK(adjVarsState_ParserStruct.triggerSlot__old),
		VAR_BLOCK(adjVarsState_ParserStruct.analogSlot),
	};

	const ui8 AdjVarsStateOldTx_ParserStructDB_Size = countof(AdjVarsStateOldTx_ParserStructDB);


	const ParserBlock_t AdjVarsStateOldRx_ParserStructDB [] =
	{
		VAR_BLOCK(adjVarsState_ParserStruct.triggerRC_Data__old),
		VAR_BLOCK(adjVarsState_ParserStruct.triggerAction__old),
		VAR_BLOCK(adjVarsState_ParserStruct.analogRC_Data),
		VAR_BLOCK(adjVarsState_ParserStruct.analogValue),
		VAR_BLOCK(adjVarsState_ParserStruct.reserved),
	};

	const ui8 AdjVarsStateOldRx_ParserStructDB_Size = countof(AdjVarsStateOldRx_ParserStructDB);


	const ParserBlock_t AdjVarsStateTx_ParserStructDB [] =
	{
		VAR_BLOCK(adjVarsState_ParserStruct.triggerSlot),
		VAR_BLOCK(adjVarsState_ParserStruct.analogSrcID),
		VAR_BLOCK(adjVarsState_ParserStruct.analogVarID),
		VAR_BLOCK(adjVarsState_ParserStruct.lutSrcID),
		VAR_BLOCK(adjVarsState_ParserStruct.lutVarID),
	};

	const ui8 AdjVarsStateTx_ParserStructDB_Size = countof(AdjVarsStateTx_ParserStructDB);


	const ParserBlock_t AdjVarsStateRx_ParserStructDB [] =
	{
		VAR_BLOCK(adjVarsState_ParserStruct.triggerRC_Data),
		VAR_BLOCK(adjVarsState_ParserStruct.triggerAction),
		VAR_BLOCK(adjVarsState_ParserStruct.analogSrcValue),
		VAR_BLOCK(adjVarsState_ParserStruct.analogVarValue),
		VAR_BLOCK(adjVarsState_ParserStruct.lutSrcValue),
		VAR_BLOCK(adjVarsState_ParserStruct.lutVarValue),
	};

	const ui8 AdjVarsStateRx_ParserStructDB_Size = countof(AdjVarsStateRx_ParserStructDB);
	/**	@}
	 */

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	Adjvar_Values
 * 	@{
 */
/**	@brief	Needed to change the values of adjustable variables
 *
 *	@attention	Please only use this function to change
 *				the adjustable variable values.
 *
 *	@param 	*adjVarsGeneral - general adjustable variables structure
 *	@param	value - new value of adjustable variable
 */
void EditAdjVarValue (AdjVarsGeneral_t *adjVarsGeneral, i32 value)
{
	/* Values border checking */
	value = CONSTRAINT(value, adjVarsGeneral->minValue, adjVarsGeneral->maxValue);

	if (adjVarsGeneral->value == value)
		return;

	adjVarsGeneral->value = value;
	adjVarsGeneral->changeFlag = CHANGED;
	adjVarsGeneral->saveFlag = NOT_SAVED;
}


/**	@brief	Updates the value of changed variables
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param 	*adjVarsGeneral - general adjustable variables structure
 *	@param	adjVarQuan - number of adjustable variables
 *	@param	*confirmationState - confirmation structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_SetAdjVarValues (GeneralSBGC_t *generalSBGC, AdjVarsGeneral_t *adjVarsGeneral, ui8 adjVarQuan, ConfirmationState_t *confirmationState)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_SET_ADJ_VARS_VAL);

	ui8 numParams = 0;
	WriteByte(&cmd, numParams);  // temporary offset

	FOR_(i, adjVarQuan)
		if (adjVarsGeneral[i].changeFlag == CHANGED)
		{
			WriteByte(&cmd, adjVarsGeneral[i].ID);
			WriteLong(&cmd, adjVarsGeneral[i].value);

			adjVarsGeneral[i].changeFlag = NOT_CHANGED;
			adjVarsGeneral[i].saveFlag = NOT_SAVED;
			numParams++;
		}

	if (numParams == 0)  // No variables changed
		return generalSBGC->_ParserCurrentStatus;

	cmd.payload[0] = numParams;  // re-writing numParams
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, cmd.commandID);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Query the actual value of selected variables
 *
 *	@note	AdjVarsGeneral_t.ID must be filled
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param 	*adjVarsGeneral - general adjustable variables structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_GetAdjVarValue (GeneralSBGC_t *generalSBGC, AdjVarsGeneral_t *adjVarsGeneral)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_GET_ADJ_VARS_VAL);
	WriteByte(&cmd, 1);
	WriteByte(&cmd, adjVarsGeneral->ID);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_SET_ADJ_VARS_VAL), "Adj Var Value:") == TX_RX_OK)
	{
		SkipBytes(&cmd, 2);  // skip ui8 numParams and ui8 ID
		adjVarsGeneral->value = ReadLong(&cmd);
	}

	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Query the all actual parameter values
 *
 *	@note	AdjVarsGeneral_t.ID must be filled
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param 	*adjVarsGeneral - general adjustable variables structure
 *	@param	adjVarQuan - number of adjustable variables
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_GetAdjVarValues (GeneralSBGC_t *generalSBGC, AdjVarsGeneral_t *adjVarsGeneral, ui8 adjVarQuan)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_GET_ADJ_VARS_VAL);

	ui8 firstGroupQuan = (adjVarQuan > 40) ? 40 : adjVarQuan;

	WriteByte(&cmd, firstGroupQuan);  // numParams

	ui8 count = 0;
	while (count < firstGroupQuan)
		WriteByte(&cmd, adjVarsGeneral[count++].ID);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_SET_ADJ_VARS_VAL), "Adj Var Values vol. 1:") == TX_RX_OK)
	{
		SkipBytes(&cmd, 1);  // skip ui8 numParams

		FOR_(i, firstGroupQuan)
		{
			SkipBytes(&cmd, 1);  // skip ui8 ID
			adjVarsGeneral[i].value = ReadLong(&cmd);
		}

		if (adjVarQuan > 40)
		{
			InitCmdWrite(&cmd, CMD_GET_ADJ_VARS_VAL);  // command re-init
			WriteByte(&cmd, adjVarQuan - 40);

			while (count < (adjVarQuan - 40))
				WriteByte(&cmd, count++);

			if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_SET_ADJ_VARS_VAL), "Adj Var Values vol. 2:") == TX_RX_OK)
				FOR_(i, adjVarQuan - 40)
				{
					SkipBytes(&cmd, 1);  // skip ui8 ID
					adjVarsGeneral[i + 40].value = ReadLong(&cmd);
				}
		}
	}

	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Saves current value of adjustable variable to EEPROM
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param 	*adjVarsGeneral - general adjustable variables structure
 *	@param	*confirmationState - confirmation structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_SaveAdjVarToEEPROM (GeneralSBGC_t *generalSBGC, AdjVarsGeneral_t *adjVarsGeneral, ConfirmationState_t *confirmationState)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_SAVE_PARAMS_3);
	WriteByte(&cmd, adjVarsGeneral->ID);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, cmd.commandID);

	adjVarsGeneral->saveFlag = SAVED;
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Saves current adjustable variable values to EEPROM
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param 	*adjVarsGeneral - general adjustable variables structure
 *	@param	adjVarQuan - number of adjustable variables
 *	@param	*confirmationState - confirmation structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_SaveAdjVarsToEEPROM (GeneralSBGC_t *generalSBGC, AdjVarsGeneral_t *adjVarsGeneral, ui8 adjVarQuan, ConfirmationState_t *confirmationState)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_SAVE_PARAMS_3);

	FOR_(i, adjVarQuan)
		if (adjVarsGeneral[i].saveFlag == NOT_SAVED)
			WriteByte(&cmd, adjVarsGeneral[i].ID);

	if (cmd.payloadSize == 0)  // nothing to save
		return generalSBGC->_ParserCurrentStatus;

	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, cmd.commandID);

	if (confirmationState->cmdID == CMD_SAVE_PARAMS_3)
		FOR_(i, adjVarQuan)
			adjVarsGeneral[i].saveFlag = SAVED;

	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Saves all not saved active variables
 *
 *	@note	Recommended manual setting of the SAVED flag
 *			on all saved variables
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*confirmationState - confirmation structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_SaveAllActiveAdjVarsToEEPROM (GeneralSBGC_t *generalSBGC, ConfirmationState_t *confirmationState)
{
	SBGC32_SendEmptyCommand(generalSBGC, CMD_SAVE_PARAMS_3);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, CMD_SAVE_PARAMS_3);
	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Adjvar_Cfg
 * 	@{
 */
/**	@brief	Writes configuration of mapping of control
 * 			inputs to adjustable variables
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*adjVarsCfg - structure with written adjustable
 *			variable configuration parameters
 *	@param	*confirmationState - confirmation structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_WriteAdjVarsCfg (GeneralSBGC_t *generalSBGC, const AdjVarsCfg_t *adjVarsCfg, ConfirmationState_t *confirmationState)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_WRITE_ADJ_VARS_CFG);
	WriteBuff(&cmd, adjVarsCfg, sizeof(AdjVarsCfg_t), PM_DEFAULT_8BIT);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, cmd.commandID);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Request configuration of mapping of control
 * 			inputs to adjustable variables
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*adjVarsCfg - structure for storing adjustable
 *			variable configuration parameters
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ReadAdjVarsCfg (GeneralSBGC_t *generalSBGC, AdjVarsCfg_t *adjVarsCfg)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_READ_ADJ_VARS_CFG);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_READ_ADJ_VARS_CFG), "Adj Var Config:") == TX_RX_OK)
		ReadBuff(&cmd, adjVarsCfg, sizeof(AdjVarsCfg_t), PM_DEFAULT_8BIT);

	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Adjvar_State
 * 	@{
 */
/**	@brief	Request the state of adjustable variable
 * 			in the given trigger and analog slots
 *
 * 	@note	This function can work in two ways. It will depend
 * 			on the current firmware version of the device
 *
 * 	@note	Firmware: prior to 2.62b5:\n
 * 			Must be set:\n
 *			AdjVarsState_t.triggerSlot__old \n
 *			AdjVarsState_t.analogSlot
 *
 *	@note	Firmware: 2.62b5+:\n
 * 			Must be set:\n
 *			AdjVarsState_t.triggerSlot \n
 *			AdjVarsState_t.analogSrcID \n
 *			AdjVarsState_t.analogVarID \n
 *			AdjVarsState_t.lutSrcID \n
 *			AdjVarsState_t.lutVarID
 *
 *			See @ref AdjVarsState_t structure
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*adjVarsState - structure for writing and storing adjustable
 *			variable configuration parameters
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_RequestAdjVarsState (GeneralSBGC_t *generalSBGC, AdjVarsState_t *adjVarsState)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_ADJ_VARS_STATE);

	if (generalSBGC->_firmwareVersion < 2625)  // Firmware ver. prior to 2.62b5
	{
		WriteBuff(&cmd, adjVarsState, 2, PM_AV_STATE_OLD_TX);
		if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_ADJ_VARS_STATE), "Adj Var State (old):") == TX_RX_OK)
			ReadBuff(&cmd, &adjVarsState->triggerRC_Data__old, cmd.payloadSize, PM_AV_STATE_OLD_RX);
	}

	else  // Firmware ver. 2.62b5+
	{
		WriteBuff(&cmd, &adjVarsState->triggerSlot, 7, PM_AV_STATE_TX);
		if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_ADJ_VARS_STATE), "Adj Var State:") == TX_RX_OK)
			ReadBuff(&cmd, &adjVarsState->triggerRC_Data, cmd.payloadSize, PM_AV_STATE_RX);
	}

	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
