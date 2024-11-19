/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.1
 *
 *	@file		adjvar.h
 *
 *	@brief		Adjustable variables header file
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
 *	@defgroup	Adjvar SBGC32 Adjustable Variables
 *	@ingroup	Modules
 *		@brief	SBGC32 Adjustable Variables Title Module
 *	____________________________________________________________________
 *
 *	@defgroup	Adjvar_Values Adjustable Variable Values
 *	@ingroup	Adjvar
 *		@brief	Adjustable Variable Values Module
 *
 *				Covered Commands:
 *
 *				### CMD_SET_ADJ_VARS_VAL
 *				### CMD_GET_ADJ_VARS_VAL
 *				### CMD_SAVE_PARAMS_3
 *
 *	@defgroup	Adjvar_Configs Adjustable Variable Configurations
 *	@ingroup	Adjvar
 *		@brief	Adjustable Variable Configurations Module
 *
 *				Covered Commands:
 *
 *				### CMD_WRITE_ADJ_VARS_CFG
 *				### CMD_READ_ADJ_VARS_CFG
 *
 *	@defgroup	Adjvar_State Adjustable Variable States
 *	@ingroup	Adjvar
 *		@brief	Adjustable Variable States Module
 *
 *				Covered Commands:
 *
 *				### CMD_ADJ_VARS_STATE
 *
 *	@defgroup	Adjvar_Info Adjustable Variable Info
 *	@ingroup	Adjvar
 *		@brief	Adjustable Variable Info Module
 *
 *				Covered Commands:
 *
 *				### CMD_ADJ_VARS_INFO
 *	____________________________________________________________________
 */

#ifndef		MODULES_ADJVAR_H_
#define		MODULES_ADJVAR_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../sbgc32.h"


#if (SBGC_ADJVAR_MODULE)

/**	@addtogroup	Adjvar
 *	@{
 */
/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *										   Constants
 */
/**	@cond
 */
#ifndef	SBGC_ADJ_VARS_REF_INFO
	#define	SBGC_ADJ_VARS_REF_INFO	sbgcOFF
#endif

#ifndef	SBGC_ADJ_VARS_NAMES
	#define	SBGC_ADJ_VARS_NAMES		sbgcOFF
#endif

#ifndef	SBGC_ADJ_VARS_ADD_FLAG
	#define	SBGC_ADJ_VARS_ADD_FLAG	sbgcOFF
#endif
/**	@endcond
 */

/** Maximal number of adjustable variables
	for current library version */
#define		SBGC_ADJ_VARS_MAX_QUANTITY		91

/** Minimal number of adjustable variables
	compatible with all firmwares */
#define		SBGC_ADJ_VARS_MIN_QUANTITY		50

/** Maximum number of adjustable variables
	in the one serial command using the
	@ref SBGC32_SetAdjVarValues and
	@ref SBGC32_GetAdjVarValues functions */
#define		SBGC_ADJ_VARS_MAX_NUM_PACKET	40

/** Maximal length of adjustable variable received
	in the @ref SBGC32_RequestAdjVarsInfo
	function */
#define		SBGC_ADJ_VAR_INFO_MAX_NAME		16

/** Can be used for cutting "ADJ_VAR_" prefix
	from adjustable variable name */
#define		SBGC_ADJ_VAR_NAME_CUT	8


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *				Adjustable Variables General Objects
 */
/**	@brief	Adjustable variables general enumeration
 *
 *	@note	sbgcAdjVarsCfg_t.AnalogSlot
 *	@note	sbgcAdjVarsState_t.analogVarID
 *	@note	sbgcAdjVarsState_t.lutVarID
 */
typedef enum
{
	ADJ_VAR_UNDEFINED				= -1,
	ADJ_VAR_P_ROLL					= 0,
	ADJ_VAR_P_PITCH,
	ADJ_VAR_P_YAW,
	ADJ_VAR_I_ROLL,
	ADJ_VAR_I_PITCH,
	ADJ_VAR_I_YAW,
	ADJ_VAR_D_ROLL,
	ADJ_VAR_D_PITCH,
	ADJ_VAR_D_YAW,
	ADJ_VAR_POWER_ROLL,
	ADJ_VAR_POWER_PITCH,
	ADJ_VAR_POWER_YAW,
	ADJ_VAR_ACC_LIMITER,
	ADJ_VAR_FOLLOW_SPEED_ROLL,
	ADJ_VAR_FOLLOW_SPEED_PITCH,
	ADJ_VAR_FOLLOW_SPEED_YAW,
	ADJ_VAR_FOLLOW_LPF_ROLL,
	ADJ_VAR_FOLLOW_LPF_PITCH,
	ADJ_VAR_FOLLOW_LPF_YAW,
	ADJ_VAR_RC_SPEED_ROLL,
	ADJ_VAR_RC_SPEED_PITCH,
	ADJ_VAR_RC_SPEED_YAW,
	ADJ_VAR_RC_LPF_ROLL,
	ADJ_VAR_RC_LPF_PITCH,
	ADJ_VAR_RC_LPF_YAW,
	ADJ_VAR_RC_TRIM_ROLL,
	ADJ_VAR_RC_TRIM_PITCH,
	ADJ_VAR_RC_TRIM_YAW,
	ADJ_VAR_RC_DEADBAND,
	ADJ_VAR_RC_EXPO_RATE,
	ADJ_VAR_FOLLOW_PITCH,
	ADJ_VAR_RC_FOLLOW_YAW_PITCH,
	ADJ_VAR_FOLLOW_DEADBAND,
	ADJ_VAR_FOLLOW_EXPO_RATE,
	ADJ_VAR_FOLLOW_ROLL_MIX_START,
	ADJ_VAR_FOLLOW_ROLL_MIX_RANGE,
	ADJ_VAR_GYRO_TRUST,
	ADJ_VAR_FRAME_HEADING_ANGLE,
	ADJ_VAR_GYRO_HEADING_CORR,
	ADJ_VAR_ACC_LIMITER_ROLL,
	ADJ_VAR_ACC_LIMITER_PITCH,
	ADJ_VAR_ACC_LIMITER_YAW,
	ADJ_VAR_PID_GAIN_ROLL,
	ADJ_VAR_PID_GAIN_PITCH,
	ADJ_VAR_PID_GAIN_YAW,
	ADJ_VAR_LPF_FREQ_ROLL,
	ADJ_VAR_LPF_FREQ_PITCH,
	ADJ_VAR_LPF_FREQ_YAW,
	ADJ_VAR_TIMELAPSE_TIME,
	ADJ_VAR_MAV_CTRL_MODE,
	ADJ_VAR_H_CORR_FACTOR,
	ADJ_VAR_SW_LIM_MIN_ROLL,
	ADJ_VAR_SW_LIM_MAX_ROLL,
	ADJ_VAR_SW_LIM_MIN_PITCH,
	ADJ_VAR_SW_LIM_MAX_PITCH,
	ADJ_VAR_SW_LIM_MIN_YAW,
	ADJ_VAR_SW_LIM_MAX_YAW,
	ADJ_VAR_FOLLOW_RANGE_ROLL,
	ADJ_VAR_FOLLOW_RANGE_PITCH,
	ADJ_VAR_FOLLOW_RANGE_YAW,
	ADJ_VAR_AUTO_PID_TARGET,
	ADJ_VAR_RC_MODE_ROLL,
	ADJ_VAR_RC_MODE_PITCH,
	ADJ_VAR_RC_MODE_YAW,
	ADJ_VAR_EULER_ORDER,
	ADJ_VAR_FOLLOW_IN_DBAND,
	ADJ_VAR_RC_LIMIT_MIN_ROLL,
	ADJ_VAR_RC_LIMIT_MAX_ROLL,
	ADJ_VAR_RC_LIMIT_MIN_PITCH,
	ADJ_VAR_RC_LIMIT_MAX_PITCH,
	ADJ_VAR_RC_LIMIT_MIN_YAW,
	ADJ_VAR_RC_LIMIT_MAX_YAW,
	ADJ_VAR_RC_DEADBAND_PITCH,
	ADJ_VAR_RC_DEADBAND_YAW,
	ADJ_VAR_RC_EXPO_RATE_PITCH,
	ADJ_VAR_RC_EXPO_RATE_YAW,
	ADJ_VAR_SHAKE_AMP_ROLL,
	ADJ_VAR_SHAKE_AMP_TILT,
	ADJ_VAR_SHAKE_AMP_PAN,
	ADJ_VAR_SHAKE_FREQ,
	ADJ_VAR_SHAKE_FREQ_RANGE,
	ADJ_VAR_SHAKE_PAUSE_PERIOD,
	ADJ_VAR_SHAKE_PAUSE_BALANCE,
	ADJ_VAR_SHAKE_PAUSE_RANDOMNESS,
	ADJ_VAR_SHAKE_RESONANCE_GAIN_ROLL,
	ADJ_VAR_SHAKE_RESONANCE_GAIN_TILT,
	ADJ_VAR_SHAKE_RESONANCE_GAIN_PAN,
	ADJ_VAR_SHAKE_FREQ_SHIFT_ROLL,
	ADJ_VAR_SHAKE_FREQ_SHIFT_TILT,
	ADJ_VAR_SHAKE_FREQ_SHIFT_PAN,
	ADJ_VAR_SHAKE_MASTER_GAIN

}	sbgcAdjVarID_t;


/**	@note	sbgcAdjVarGeneral_t.syncFlag
 */
typedef enum
{
	AV_NOT_SYNCHRONIZED				= 0,
	AV_SYNCHRONIZED

}	sbgcAdjVarSyncFlag_t;


/**	@note	sbgcAdjVarGeneral_t.saveFlag
 */
typedef enum
{
	AV_SAVED						= 0,
	AV_NOT_SAVED

}	sbgcAdjVarSaveFlag_t;


/**	@brief	Adjustable variables general structure
 */
typedef struct
{
	sbgcAdjVarID_t	ID;								/*!<  Adjustable variable ID														*/

	#if	(SBGC_ADJ_VARS_NAMES)
		char		*name;							/*!<  Adjustable variable name														*/
	#endif

	i16				minValue,						/*!<  Adjustable variable minimal value												*/
					maxValue;						/*!<  Adjustable variable maximal value												*/

	i32				value;							/*!<  Adjustable variable value														*/

	sbgcAdjVarSyncFlag_t
					syncFlag;						/*!<  Set when the value of adjustable variable synchronized with gimbal			*/
	sbgcAdjVarSaveFlag_t
					saveFlag;						/*!<  Set when saving the changed adjustable variable value							*/

	#if	(SBGC_ADJ_VARS_ADD_FLAG)
		sbgcAdjVarCustFld_t
					custom;							/*!<  Customizable parameters of adjustable variable								*/
	#endif

}	sbgcAdjVarGeneral_t;


#if (SBGC_ADJ_VARS_REF_INFO)

	/**	@brief	Adjustable variables
	 *			debug info structure
	 */
	typedef struct
	{
		sbgcAdjVarID_t		ID;						/*!<  Adjustable variable ID														*/

		#if	(SBGC_ADJ_VARS_NAMES)
			char			*name;					/*!<  Adjustable variable name														*/
		#endif

		i32					minValue,				/*!<  Adjustable variable minimal value												*/
							maxValue;				/*!<  Adjustable variable maximal value												*/

	}	sbgcAdjVarReferenceInfo_t;

	/**	@cond
	 */
	extern sbgcAdjVarReferenceInfo_t adjVarsReferenceInfoArray [];
	/**	@endcond
	 */
#endif
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *		Adjustable Variable Configuration Structures
 */
/**	@addtogroup	Adjvar_Configs
 *	@{
 */
/**	@brief	Part of sbgcAdjVarsCfg_t structure
 *
 *	@note	sbgcAdjVarsCfg_t.TriggerSlot
 */
typedef struct PACKED__
{
	ui8		triggerSrcCh,							/*!<  See @ref sbgcRC_MapSourceType_t and @ref sbgcRC_MapSource_t enumerations		*/
			triggerAction [5];						/*!<  See @ref sbgcMenuCommand_t enumeration										*/

}	sbgcTriggerSlot_t;

/**	@brief	Part of sbgcAdjVarsCfg_t structure
 *
 *	@note	sbgcAdjVarsCfg_t.AnalogSlot
 */
typedef struct PACKED__
{
	ui8		analogSrc,								/*!<  See @ref sbgcRC_MapSourceType_t and @ref sbgcRC_MapSource_t enumerations		*/
			varID,									/*!<  See @ref sbgcAdjVarID_t enumeration											*/

			minVal,									/*!<  ...																			*/
			maxVal;									/*!<  ...Is specify a working range, that is mapped to a native range
														  of particular parameter														*/

}	sbgcAnalogSlot_t;

/**	@brief	Structure type for work with
 *			sbgcAdjVarsCfg parameters
 *
 *	@ref	SBGC32_WriteAdjVarsCfg function\n
 *	@ref	SBGC32_ReadAdjVarsCfg function
 */
typedef struct PACKED__
{
	sbgcTriggerSlot_t		TriggerSlot [10];

	sbgcAnalogSlot_t		AnalogSlot [15];

	ui8		reserved [8];

}	sbgcAdjVarsCfg_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t adjVarsCfgReferenceInfoArray [];
	extern const ui8 adjVarsCfgReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif
/**	@}
 */


/**	@addtogroup	Adjvar_State
 *	@{
 */
/**	@brief	Structure type for work with
 *			sbgcAdjVarsState parameters
 *
 *	@ref	SBGC32_RequestAdjVarsState function
 */
typedef struct PACKED__
{
	/* Firmware ver. prior to 2.62b5 */
	/* Sent data */
	ui8		triggerSlot__old;						/*!<  0 --> 9																		*/
	ui8		analogSlot;								/*!<  0 --> 14																		*/
	/* Received data */
	i16		triggerRC_Data__old;					/*!<  -500 --> 500. RC signal for the "trigger" variable slot						*/
	ui8		triggerAction__old;						/*!<  See @ref sbgcMenuCommand_t enumeration										*/
	i16		analogRC_Data;							/*!<  -500 --> 500. RC signal for the "analog" variable slot						*/
	i32		analogValue;							/*!<  Current value of the variable after all calculations							*/
	ui8		reserved [6];

	/* Firmware ver. 2.62b5+ */
	/* Sent data */
	ui8		triggerSlot;							/*!<  0 --> 9																		*/
	ui16	analogSrcID;							/*!<  "Trigger" slot number to show its state										*/
	ui8		analogVarID;							/*!<  See @ref sbgcAdjVarID_t enumeration. Variable ID to show its value			*/
	ui16	lutSrcID;								/*!<  Signal source to show its value												*/
	ui8		lutVarID;								/*!<  See @ref sbgcAdjVarID_t enumeration. Variable ID to show its value			*/
	/* Received data */
	i16		triggerRC_Data;							/*!<  -16384 --> 16384. RC signal for the "trigger" variable slot					*/
	ui8		triggerAction;							/*!<  See @ref sbgcMenuCommand_t enumeration										*/
	i16		analogSrcValue;							/*!<  -16384 --> 16384. Signal value requested in the analogSrcID					*/
	float	analogVarValue;							/*!<  Value of variable requested in the analogVarID								*/
	i16		lutSrcValue;							/*!<  -16384 --> 16384. Signal value requested in the lutSrcID						*/
	float	lutVarValue;							/*!<  Current value of variable requested in the lutVarID							*/

}	sbgcAdjVarsState_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t adjVarsStateOldTxReferenceInfoArray [];
	extern const ui8 adjVarsStateOldTxReferenceInfoArrayElCnt;
	extern const sbgcParameterReferenceInfo_t adjVarsStateOldRxReferenceInfoArray [];
	extern const ui8 adjVarsStateOldRxReferenceInfoArrayElCnt;
	extern const sbgcParameterReferenceInfo_t adjVarsStateTxReferenceInfoArray [];
	extern const ui8 adjVarsStateTxReferenceInfoArrayElCnt;
	extern const sbgcParameterReferenceInfo_t adjVarsStateRxReferenceInfoArray [];
	extern const ui8 adjVarsStateRxReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif
/**	@}
 */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								 Function Prototypes
 */
/**	@cond
 */
/**	@addtogroup	Adjvar
 *	@{
 */
#if (SBGC_ADJ_VARS_REF_INFO)
	void SerialAPI_InitAdjVar (sbgcAdjVarGeneral_t *adjVarGeneral, sbgcAdjVarID_t ID);
	void SerialAPI_InitAllAdjVars (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral);
#endif
sbgcAdjVarGeneral_t *SerialAPI_FindAdjVarByID (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral, sbgcAdjVarID_t ID);
/**	@}
 */


/**	@addtogroup	Adjvar_Values
 *	@{
 */
void SerialAPI_EditAdjVarValue (sbgcAdjVarGeneral_t *adjVarGeneral, i32 value);
sbgcCommandStatus_t SBGC32_SetAdjVarValue (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral, sbgcConfirm_t *confirm
										   SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_SetAdjVarValues (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral, ui8 adjVarQuan, sbgcConfirm_t *confirm
											SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_GetAdjVarValue (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_GetAdjVarValues (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral, ui8 adjVarQuan SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_SaveAdjVarToEEPROM (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral, sbgcConfirm_t *confirm
											   SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_SaveAdjVarsToEEPROM (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral, ui8 adjVarQuan, sbgcConfirm_t *confirm
												SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_SaveAllActiveAdjVarsToEEPROM (sbgcGeneral_t *gSBGC, sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Adjvar_Configs
 *	@{
 */
sbgcCommandStatus_t SBGC32_WriteAdjVarsCfg (sbgcGeneral_t *gSBGC, const sbgcAdjVarsCfg_t *adjVarsCfg, sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ReadAdjVarsCfg (sbgcGeneral_t *gSBGC, sbgcAdjVarsCfg_t *adjVarsCfg SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Adjvar_State
 *	@{
 */
sbgcCommandStatus_t SBGC32_RequestAdjVarsState (sbgcGeneral_t *gSBGC, sbgcAdjVarsState_t *adjVarsState SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Adjvar_Info
 *	@{
 */
sbgcCommandStatus_t SBGC32_RequestAdjVarsInfo (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral, sbgcAdjVarID_t ID
											   SBGC_ADVANCED_PARAMS__);
/**	@}
 */
/**	@endcond
 */

#endif /* SBGC_ADJVAR_MODULE */


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

#endif		/* MODULES_ADJVAR_H_ */
