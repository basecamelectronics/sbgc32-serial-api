/** ____________________________________________________________________
 *
 * 	SBGC32 Serial API Library v1.0
 *
 *	@file		adjvar.c
 *
 *	@brief 		Adjustable variables source file
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


#if (SBGC_ADJVAR_MODULE)

#if (SBGC_ADJ_VARS_REF_INFO)

	/**	@addtogroup	Adjvar
	 * 	@{
	 */
	/** @brief	Global adjustable variables auxiliary array
	 */
	AdjVarReferenceInfo_t adjVarsReferenceInfoArray [] =
	/*
	||			   ENUM ID + NAME					 || MIN VALUE || MAX VALUE || 		TYPE		||
	 */
	{ {	ADJ_VAR_BLOCK_(ADJ_VAR_P_ROLL),						0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_P_PITCH),					0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_P_YAW),						0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_I_ROLL),						0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_I_PITCH),					0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_I_YAW),						0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_D_ROLL),						0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_D_PITCH),					0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_D_YAW),						0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_POWER_ROLL),					0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_POWER_PITCH),				0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_POWER_YAW),					0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_ACC_LIMITER),				0,			1275,		_UNSIGNED_SHORT_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_SPEED_ROLL),			0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_SPEED_PITCH),			0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_SPEED_YAW),			0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_LPF_ROLL),			0,			15,			_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_LPF_PITCH),			0,			15,			_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_LPF_YAW),				0,			15,			_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_SPEED_ROLL),				0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_SPEED_PITCH),				0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_SPEED_YAW),				0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_LPF_ROLL),				0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_LPF_PITCH),				0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_LPF_YAW),					0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_TRIM_ROLL),				-127,		127,		_SIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_TRIM_PITCH),				-127,		127,		_SIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_TRIM_YAW),				-127,		127,		_SIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_DEADBAND),				0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_EXPO_RATE),				0,			100,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_PITCH),				0,			1,			_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_FOLLOW_YAW_PITCH),		0,			2,			_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_DEADBAND),			0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_EXPO_RATE),			0,			100,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_ROLL_MIX_START),		0,			90,			_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_ROLL_MIX_RANGE),		0,			90,			_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_GYRO_TRUST),					0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FRAME_HEADING),				-1800,		1800,		_SIGNED_SHORT_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_GYRO_HEADING_CORR),			-20000,		20000,		_SIGNED_SHORT_
	},{	ADJ_VAR_BLOCK_(ADJ_VAL_ACC_LIMITER_ROLL),			0,			1275,		_UNSIGNED_SHORT_
	},{	ADJ_VAR_BLOCK_(ADJ_VAL_ACC_LIMITER_PITCH),			0,			1275,		_UNSIGNED_SHORT_
	},{	ADJ_VAR_BLOCK_(ADJ_VAL_ACC_LIMITER_YAW),			0,			1275,		_UNSIGNED_SHORT_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_PID_GAIN_ROLL),				0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_PID_GAIN_PITCH),				0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_PID_GAIN_YAW),				0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_LPF_FREQ_ROLL),				10,			400,		_UNSIGNED_SHORT_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_LPF_FREQ_PITCH),				10,			400,		_UNSIGNED_SHORT_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_LPF_FREQ_YAW),				10,			400,		_UNSIGNED_SHORT_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_TIMELAPSE_TIME),				1,			3600,		_UNSIGNED_SHORT_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_MAV_CTRL_MODE),				0,			2,			_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_H_CORR_FACTOR),				0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SW_LIM_MIN_ROLL),			-3600,		3600,		_SIGNED_SHORT_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SW_LIM_MAX_ROLL),			-3600,		3600,		_SIGNED_SHORT_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SW_LIM_MIN_PITCH),			-3600,		3600,		_SIGNED_SHORT_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SW_LIM_MAX_PITCH),			-3600,		3600,		_SIGNED_SHORT_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SW_LIM_MIN_YAW),				-3600,		3600,		_SIGNED_SHORT_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SW_LIM_MAX_YAW),				-3600,		3600,		_SIGNED_SHORT_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_RANGE_ROLL),			0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_RANGE_PITCH),			0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_RANGE_YAW),			0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_AUTO_PID_TARGET),			0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_MODE_ROLL),				0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_MODE_PITCH),				0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_MODE_YAW),				0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_EULER_ORDER),				0,			255,		_UNSIGNED_CHAR_
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_IN_DBAND),			0,			255,		_UNSIGNED_CHAR_

	}};
	/**	@}
	 */

#endif

#if (SYS_BIG_ENDIAN || SBGC_REF_INFO)

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *					Big Endian Mapping and Reference Info Structures
	 */
	/**	@addtogroup	Adjvar_Cfg
	 * 	@{
	 */
	/** @brief	Sample reference info
	 */
	const ParameterReferenceInfo_t adjVarsCfgReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Trigger Src Ch [SLOT0]",	_UNSIGNED_CHAR_				),  // 0
		PARAM_BLOCK_(	"Analog Slot [SLOT0]",		_UNSIGNED_CHAR_				),  // 1
		PARAM_BLOCK_(	"Trigger Src Ch [SLOT1]",	_UNSIGNED_CHAR_				),  // 2
		PARAM_BLOCK_(	"Analog Slot [SLOT1]",		_UNSIGNED_CHAR_				),  // 3
		PARAM_BLOCK_(	"Trigger Src Ch [SLOT2]",	_UNSIGNED_CHAR_				),  // 4
		PARAM_BLOCK_(	"Analog Slot [SLOT2]",		_UNSIGNED_CHAR_				),  // 5
		PARAM_BLOCK_(	"Trigger Src Ch [SLOT3]",	_UNSIGNED_CHAR_				),  // 6
		PARAM_BLOCK_(	"Analog Slot [SLOT3]",		_UNSIGNED_CHAR_				),  // 7
		PARAM_BLOCK_(	"Trigger Src Ch [SLOT4]",	_UNSIGNED_CHAR_				),  // 8
		PARAM_BLOCK_(	"Analog Slot [SLOT4]",		_UNSIGNED_CHAR_				),  // 9
		PARAM_BLOCK_(	"Trigger Src Ch [SLOT5]",	_UNSIGNED_CHAR_				),  // 10
		PARAM_BLOCK_(	"Analog Slot [SLOT5]",		_UNSIGNED_CHAR_				),  // 11
		PARAM_BLOCK_(	"Trigger Src Ch [SLOT6]",	_UNSIGNED_CHAR_				),  // 12
		PARAM_BLOCK_(	"Analog Slot [SLOT6]",		_UNSIGNED_CHAR_				),  // 13
		PARAM_BLOCK_(	"Trigger Src Ch [SLOT7]",	_UNSIGNED_CHAR_				),  // 14
		PARAM_BLOCK_(	"Analog Slot [SLOT7]",		_UNSIGNED_CHAR_				),  // 15
		PARAM_BLOCK_(	"Trigger Src Ch [SLOT8]",	_UNSIGNED_CHAR_				),  // 16
		PARAM_BLOCK_(	"Analog Slot [SLOT8]",		_UNSIGNED_CHAR_				),  // 17
		PARAM_BLOCK_(	"Trigger Src Ch [SLOT9]",	_UNSIGNED_CHAR_				),  // 18
		PARAM_BLOCK_(	"Analog Slot [SLOT9]",		_UNSIGNED_CHAR_				),  // 19
		PARAM_BLOCK_(	"Analog Src [SLOT0]",		_UNSIGNED_CHAR_				),  // 20
		PARAM_BLOCK_(	"Var ID [SLOT0]",			_UNSIGNED_CHAR_				),  // 21
		PARAM_BLOCK_(	"Min Val [SLOT0]",			_UNSIGNED_CHAR_				),  // 22
		PARAM_BLOCK_(	"Max Val [SLOT0]",			_UNSIGNED_CHAR_				),  // 23
		PARAM_BLOCK_(	"Analog Src [SLOT1]",		_UNSIGNED_CHAR_				),  // 24
		PARAM_BLOCK_(	"Var ID [SLOT1]",			_UNSIGNED_CHAR_				),  // 25
		PARAM_BLOCK_(	"Min Val [SLOT1]",			_UNSIGNED_CHAR_				),  // 26
		PARAM_BLOCK_(	"Max Val [SLOT1]",			_UNSIGNED_CHAR_				),  // 27
		PARAM_BLOCK_(	"Analog Src [SLOT2]",		_UNSIGNED_CHAR_				),  // 28
		PARAM_BLOCK_(	"Var ID [SLOT2]",			_UNSIGNED_CHAR_				),  // 29
		PARAM_BLOCK_(	"Min Val [SLOT2]",			_UNSIGNED_CHAR_				),  // 30
		PARAM_BLOCK_(	"Max Val [SLOT2]",			_UNSIGNED_CHAR_				),  // 31
		PARAM_BLOCK_(	"Analog Src [SLOT3]",		_UNSIGNED_CHAR_				),  // 32
		PARAM_BLOCK_(	"Var ID [SLOT3]",			_UNSIGNED_CHAR_				),  // 33
		PARAM_BLOCK_(	"Min Val [SLOT3]",			_UNSIGNED_CHAR_				),  // 34
		PARAM_BLOCK_(	"Max Val [SLOT3]",			_UNSIGNED_CHAR_				),  // 35
		PARAM_BLOCK_(	"Analog Src [SLOT4]",		_UNSIGNED_CHAR_				),  // 36
		PARAM_BLOCK_(	"Var ID [SLOT4]",			_UNSIGNED_CHAR_				),  // 37
		PARAM_BLOCK_(	"Min Val [SLOT4]",			_UNSIGNED_CHAR_				),  // 38
		PARAM_BLOCK_(	"Max Val [SLOT4]",			_UNSIGNED_CHAR_				),  // 39
		PARAM_BLOCK_(	"Analog Src [SLOT5]",		_UNSIGNED_CHAR_				),  // 40
		PARAM_BLOCK_(	"Var ID [SLOT5]",			_UNSIGNED_CHAR_				),  // 41
		PARAM_BLOCK_(	"Min Val [SLOT5]",			_UNSIGNED_CHAR_				),  // 42
		PARAM_BLOCK_(	"Max Val [SLOT5]",			_UNSIGNED_CHAR_				),  // 43
		PARAM_BLOCK_(	"Analog Src [SLOT6]",		_UNSIGNED_CHAR_				),  // 44
		PARAM_BLOCK_(	"Var ID [SLOT6]",			_UNSIGNED_CHAR_				),  // 45
		PARAM_BLOCK_(	"Min Val [SLOT6]",			_UNSIGNED_CHAR_				),  // 46
		PARAM_BLOCK_(	"Max Val [SLOT6]",			_UNSIGNED_CHAR_				),  // 47
		PARAM_BLOCK_(	"Analog Src [SLOT7]",		_UNSIGNED_CHAR_				),  // 48
		PARAM_BLOCK_(	"Var ID [SLOT7]",			_UNSIGNED_CHAR_				),  // 49
		PARAM_BLOCK_(	"Min Val [SLOT7]",			_UNSIGNED_CHAR_				),  // 50
		PARAM_BLOCK_(	"Max Val [SLOT7]",			_UNSIGNED_CHAR_				),  // 51
		PARAM_BLOCK_(	"Analog Src [SLOT8]",		_UNSIGNED_CHAR_				),  // 52
		PARAM_BLOCK_(	"Var ID [SLOT8]",			_UNSIGNED_CHAR_				),  // 53
		PARAM_BLOCK_(	"Min Val [SLOT8]",			_UNSIGNED_CHAR_				),  // 54
		PARAM_BLOCK_(	"Max Val [SLOT8]",			_UNSIGNED_CHAR_				),  // 55
		PARAM_BLOCK_(	"Analog Src [SLOT9]",		_UNSIGNED_CHAR_				),  // 56
		PARAM_BLOCK_(	"Var ID [SLOT9]",			_UNSIGNED_CHAR_				),  // 57
		PARAM_BLOCK_(	"Min Val [SLOT9]",			_UNSIGNED_CHAR_				),  // 58
		PARAM_BLOCK_(	"Max Val [SLOT9]",			_UNSIGNED_CHAR_				),  // 59
		PARAM_BLOCK_(	"Analog Src [SLOT10]",		_UNSIGNED_CHAR_				),  // 60
		PARAM_BLOCK_(	"Var ID [SLOT10]",			_UNSIGNED_CHAR_				),  // 61
		PARAM_BLOCK_(	"Min Val [SLOT10]",			_UNSIGNED_CHAR_				),  // 62
		PARAM_BLOCK_(	"Max Val [SLOT10]",			_UNSIGNED_CHAR_				),  // 63
		PARAM_BLOCK_(	"Analog Src [SLOT11]",		_UNSIGNED_CHAR_				),  // 64
		PARAM_BLOCK_(	"Var ID [SLOT11]",			_UNSIGNED_CHAR_				),  // 65
		PARAM_BLOCK_(	"Min Val [SLOT11]",			_UNSIGNED_CHAR_				),  // 66
		PARAM_BLOCK_(	"Max Val [SLOT11]",			_UNSIGNED_CHAR_				),  // 67
		PARAM_BLOCK_(	"Analog Src [SLOT12]",		_UNSIGNED_CHAR_				),  // 68
		PARAM_BLOCK_(	"Var ID [SLOT12]",			_UNSIGNED_CHAR_				),  // 69
		PARAM_BLOCK_(	"Min Val [SLOT12]",			_UNSIGNED_CHAR_				),  // 70
		PARAM_BLOCK_(	"Max Val [SLOT12]",			_UNSIGNED_CHAR_				),  // 71
		PARAM_BLOCK_(	"Analog Src [SLOT13]",		_UNSIGNED_CHAR_				),  // 72
		PARAM_BLOCK_(	"Var ID [SLOT13]",			_UNSIGNED_CHAR_				),  // 73
		PARAM_BLOCK_(	"Min Val [SLOT13]",			_UNSIGNED_CHAR_				),  // 74
		PARAM_BLOCK_(	"Max Val [SLOT13]",			_UNSIGNED_CHAR_				),  // 75
		PARAM_BLOCK_(	"Analog Src [SLOT14]",		_UNSIGNED_CHAR_				),  // 76
		PARAM_BLOCK_(	"Var ID [SLOT14]",			_UNSIGNED_CHAR_				),  // 77
		PARAM_BLOCK_(	"Min Val [SLOT14]",			_UNSIGNED_CHAR_				),  // 78
		PARAM_BLOCK_(	"Max Val [SLOT14]",			_UNSIGNED_CHAR_				),  // 79

	};

	const ui8 adjVarsCfgReferenceInfoArrayElCnt = countof_(adjVarsCfgReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Adjvar_State
	 * 	@{
	 */
	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t adjVarsStateOldTxReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Trigger Slot (old)",		_UNSIGNED_CHAR_				),  // 0
		PARAM_BLOCK_(	"Analog Slot",				_UNSIGNED_CHAR_				),  // 1

	};

	const ui8 adjVarsStateOldTxReferenceInfoArrayElCnt = countof_(adjVarsStateOldTxReferenceInfoArray);


	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t adjVarsStateOldRxReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Trigger RC Data (old)",	_SIGNED_SHORT_				),  // 0
		PARAM_BLOCK_(	"Trigger Action (old)",		_UNSIGNED_CHAR_				),  // 1
		PARAM_BLOCK_(	"Analog RC Data",			_SIGNED_SHORT_				),  // 2
		PARAM_BLOCK_(	"Analog Value",				_SIGNED_INT_				),  // 3
		PARAMS_BLOCK_(	"Reserved",					_RESERVED_CHAR_,		6	),  // 4

	};

	const ui8 adjVarsStateOldRxReferenceInfoArrayElCnt = countof_(adjVarsStateOldRxReferenceInfoArray);


	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t adjVarsStateTxReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Trigger Slot",				_UNSIGNED_CHAR_				),  // 0
		PARAM_BLOCK_(	"Analog Src ID",			_UNSIGNED_SHORT_			),  // 1
		PARAM_BLOCK_(	"Analog Var ID",			_UNSIGNED_CHAR_				),  // 2
		PARAM_BLOCK_(	"Lut Src ID",				_UNSIGNED_SHORT_			),  // 3
		PARAM_BLOCK_(	"Lut Var ID",				_UNSIGNED_CHAR_				),  // 4

	};

	const ui8 adjVarsStateTxReferenceInfoArrayElCnt = countof_(adjVarsStateTxReferenceInfoArray);


	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t adjVarsStateRxReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Trigger RC Data",			_SIGNED_SHORT_				),  // 0
		PARAM_BLOCK_(	"Trigger Action",			_UNSIGNED_CHAR_				),  // 1
		PARAM_BLOCK_(	"Analog Src Value",			_SIGNED_SHORT_				),  // 2
		PARAM_BLOCK_(	"Analog Var Value",			_FLOAT_						),  // 3
		PARAM_BLOCK_(	"Lut Src Value",			_SIGNED_SHORT_				),  // 4
		PARAM_BLOCK_(	"Lut Var Value",			_FLOAT_						),  // 5

	};

	const ui8 adjVarsStateRxReferenceInfoArrayElCnt = countof_(adjVarsStateRxReferenceInfoArray);
	/**	@}
	 */

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	Adjvar_Values
 * 	@{
 */

#if (SBGC_ADJ_VARS_REF_INFO)

	/**	@brief	Needs to automatically initializing adjustable variable
	 *
	 *	@param 	*adjVarGeneral - general adjustable variables structure
	 *	@param	ID - adjustable variable ID
	 */
	void InitAdjVar (AdjVarGeneral_t *adjVarGeneral, AdjVarID_t ID)
	{
		memset(adjVarGeneral, 0, sizeof(AdjVarGeneral_t));

		adjVarGeneral->ID = ID;

		#if (SBGC_ADJ_VARS_NAMES)
			memcpy(adjVarGeneral->name, adjVarsReferenceInfoArray[ID].name, ADJ_VAR_MAX_NAME_LENGTH);
		#endif

		adjVarGeneral->minValue = adjVarsReferenceInfoArray[ID].minValue;
		adjVarGeneral->maxValue = adjVarsReferenceInfoArray[ID].maxValue;
		adjVarGeneral->varType = adjVarsReferenceInfoArray[ID].varType;
	}

#endif


/**	@brief	Needs to change the values of adjustable variables
 *
 *	@attention	Please only use this function to change
 *				the adjustable variable values.
 *
 *	@param 	*adjVarGeneral - general adjustable variables structure
 *	@param	value - new value of adjustable variable
 */
void EditAdjVarValue (AdjVarGeneral_t *adjVarGeneral, i32 value)
{
	/* Values border checking */
	value = constrain_(value, adjVarGeneral->minValue, adjVarGeneral->maxValue);

	if (adjVarGeneral->value == value)
		return;

	adjVarGeneral->value = value;
	adjVarGeneral->changeFlag = CHANGED;
	adjVarGeneral->saveFlag = NOT_SAVED;
}


/**	@brief	Updates the value of changed variables
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param 	*adjVarGeneral - general adjustable variables structure
 *	@param	adjVarQuan - number of adjustable variables
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_SetAdjVarValues (GeneralSBGC_t *generalSBGC, AdjVarGeneral_t *adjVarGeneral, ui8 adjVarQuan)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_SET_ADJ_VARS_VAL);

	ui8 numParams = 0;
	WriteByte(&cmd, numParams);  // temporary offset

	for (ui8 i = 0; i < adjVarQuan; i++)
		if (adjVarGeneral[i].changeFlag == CHANGED)
		{
			WriteByte(&cmd, adjVarGeneral[i].ID);
			WriteLong(&cmd, adjVarGeneral[i].value);

			adjVarGeneral[i].changeFlag = NOT_CHANGED;
			adjVarGeneral[i].saveFlag = NOT_SAVED;
			numParams++;
		}

	if (numParams == 0)  // No variables changed
		return generalSBGC->_parserCurrentStatus;

	cmd.payload[0] = numParams;  // re-writing numParams
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Query the actual value of selected variables
 *
 *	@note	AdjVarGeneral_t.ID must be filled
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param 	*adjVarGeneral - general adjustable variables structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_GetAdjVarValue (GeneralSBGC_t *generalSBGC, AdjVarGeneral_t *adjVarGeneral)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_GET_ADJ_VARS_VAL);
	WriteByte(&cmd, 1);
	WriteByte(&cmd, adjVarGeneral->ID);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_SET_ADJ_VARS_VAL), "Adj Var Value:") == TX_RX_OK)
	{
		SkipBytes(&cmd, 2);  // skip ui8 numParams and ui8 ID
		adjVarGeneral->value = ReadLong(&cmd);
	}

	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Query the all actual parameter values
 *
 *	@note	AdjVarGeneral_t.ID must be filled
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param 	*adjVarGeneral - general adjustable variables structure
 *	@param	adjVarQuan - number of adjustable variables
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_GetAdjVarValues (GeneralSBGC_t *generalSBGC, AdjVarGeneral_t *adjVarGeneral, ui8 adjVarQuan)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_GET_ADJ_VARS_VAL);

	ui8 firstGroupQuan = (adjVarQuan > 40) ? 40 : adjVarQuan;

	WriteByte(&cmd, firstGroupQuan);  // numParams

	ui8 count = 0;
	while (count < firstGroupQuan)
		WriteByte(&cmd, adjVarGeneral[count++].ID);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_SET_ADJ_VARS_VAL), "Adj Var Values vol. 1:") == TX_RX_OK)
	{
		SkipBytes(&cmd, 1);  // skip ui8 numParams

		for (ui8 i = 0; i < firstGroupQuan; i++)
		{
			SkipBytes(&cmd, 1);  // skip ui8 ID
			adjVarGeneral[i].value = ReadLong(&cmd);
		}

		if (adjVarQuan > 40)
		{
			InitCmdWrite(&cmd, CMD_GET_ADJ_VARS_VAL);  // command re-init
			WriteByte(&cmd, adjVarQuan - 40);

			while (count < adjVarQuan)
				WriteByte(&cmd, adjVarGeneral[count++].ID);

			if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_SET_ADJ_VARS_VAL), "Adj Var Values vol. 2:") == TX_RX_OK)
			{
				SkipBytes(&cmd, 1);  // skip ui8 numParams

				for (ui8 i = 0; i < adjVarQuan - 40; i++)
				{
					SkipBytes(&cmd, 1);  // skip ui8 ID
					adjVarGeneral[i + 40].value = ReadLong(&cmd);
				}
			}
		}
	}

	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Saves current value of adjustable variable to EEPROM
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param 	*adjVarGeneral - general adjustable variables structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_SaveAdjVarToEEPROM (GeneralSBGC_t *generalSBGC, AdjVarGeneral_t *adjVarGeneral)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_SAVE_PARAMS_3);
	WriteByte(&cmd, adjVarGeneral->ID);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);

	if (adjVarGeneral->saveFlag != SAVED)
		adjVarGeneral->saveFlag = SAVED;

	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Saves current adjustable variable values to EEPROM
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param 	*adjVarGeneral - general adjustable variables structure
 *	@param	adjVarQuan - number of adjustable variables
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_SaveAdjVarsToEEPROM (GeneralSBGC_t *generalSBGC, AdjVarGeneral_t *adjVarGeneral, ui8 adjVarQuan)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_SAVE_PARAMS_3);

	for (ui8 i = 0; i < adjVarQuan; i++)
		if (adjVarGeneral[i].saveFlag == NOT_SAVED)
			WriteByte(&cmd, adjVarGeneral[i].ID);

	if (cmd.payloadSize == 0)  // nothing to save
		return generalSBGC->_parserCurrentStatus;

	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);

	#if (SBGC_CONFIRM_CMD)
		if (generalSBGC->_confirmationStatus == CONFIRMATION_OK)
	#else
		if (generalSBGC->_parserCurrentStatus == TX_RX_OK)
	#endif
			for (ui8 i = 0; i < adjVarQuan; i++)
				if (adjVarGeneral[i].saveFlag != SAVED)
					adjVarGeneral[i].saveFlag = SAVED;

	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Saves all not saved active variables
 *
 *	@note	Recommended manual setting of the SAVED flag
 *			on all saved variables
 *
 *	@param	*generalSBGC - serial connection descriptor
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_SaveAllActiveAdjVarsToEEPROM (GeneralSBGC_t *generalSBGC)
{
	SBGC32_SendEmptyCommand(generalSBGC, CMD_SAVE_PARAMS_3);
	SBGC32_CheckConfirmation(generalSBGC, CMD_SAVE_PARAMS_3);

	return generalSBGC->_parserCurrentStatus;
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
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_WriteAdjVarsCfg (GeneralSBGC_t *generalSBGC, const AdjVarsCfg_t *adjVarsCfg)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_WRITE_ADJ_VARS_CFG);
	WriteBuff(&cmd, adjVarsCfg, sizeof(AdjVarsCfg_t), PM_DEFAULT_8BIT);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
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

	return generalSBGC->_parserCurrentStatus;
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

	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */

#endif /* SBGC_ADJVAR_MODULE */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
