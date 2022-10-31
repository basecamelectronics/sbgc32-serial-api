/** ____________________________________________________________________
 *
 * 	@file		service.h
 *
 *	@brief 		Service header file
 *
 *				<center><a href="https://www.basecamelectronics.com">
 *				www.basecamelectronics.com</a>
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
/** ____________________________________________________________________
 *
 * 	@defgroup	Service SBGC32 Service
 *	@ingroup	Sources
 *		@brief	SBGC32 Service Title Module
 *  ____________________________________________________________________
 *
 *	@defgroup	Board_Info Board Information
 *  @ingroup	Service
 *  	@brief	Board Information Module
 *
 *  			Covered Commands:
 *
 *				### CMD_BOARD_INFO
 *				### CMD_BOARD_INFO_3
 *
 *  @defgroup	Auto_PID Auto PID
 *  @ingroup	Service
 *  	@brief	Auto PID Module
 *
 *  			Covered Commands:
 *
 *				### CMD_AUTO_PID
 *				### CMD_AUTO_PID2
 *
 *  @defgroup	Motors_State Motors State
 *  @ingroup	Service
 *  	@brief	Motors State Module
 *
 *  			Covered Commands:
 *
 *				### CMD_MOTORS_ON
 *				### CMD_MOTORS_OFF
 *
 *  @defgroup	Boot_Mode Boot Mode
 *  @ingroup	Service
 *  	@brief	Boot Mode Module
 *
 *  			Covered Commands:
 *
 *				### CMD_BOOT_MODE_3
 *				### CMD_RESET
 *
 *  @defgroup	Scripts Scripts
 *  @ingroup	Service
 *  	@brief	Scripts Module
 *
 *  			Covered Commands:
 *
 *				### CMD_RUN_SCRIPT
 *				### CMD_SCRIPT_DEBUG
 *
 *  @defgroup	State_Vars State of Variables
 *  @ingroup	Service
 *  	@brief	State of Variables Module
 *
 *  			Covered Commands:
 *
 *				### CMD_WRITE_STATE_VARS
 *				### CMD_READ_STATE_VARS
 *
 *  @defgroup	Service_Other Service Other
 *  @ingroup	Service
 *  	@brief	Service Other Module
 *
 *  			Covered Commands:
 *
 *				### CMD_EVENT
 *				### CMD_TRIGGER_PIN
 *				### CMD_EXECUTE_MENU
 *				### CMD_SERVO_OUT
 *				### CMD_BEEP_SOUND
 *				### CMD_SIGN_MESSAGE
 *	____________________________________________________________________
 */

#ifndef     _SERVICE_H_
#define     _SERVICE_H_

#ifdef 		__cplusplus
extern 		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include 	"../core/core.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *										   Constants
 */
#define		SERVO_OUT_DISABLED		-1
#define 	MAX_MESSAGE_LENGTH		32
#define		MAX_NOTES_QANTITY		50


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						  			Board Info Flags
 */
/**	@addtogroup	Board_Info
 *	@{
 */
/**	@note	BoardInfo_t.stateFlags1
 */
typedef enum
{
	SF1_DEBUG_MODE 					= BIT_0_SET,	// Internal use only
	/* Starting from frw.ver. 2.66 */
	SF1_IS_FRAME_INVERTED 			= BIT_1_SET,	// System is re-configured for frame inversion over the middle motor
	SF1_INIT_STEP1_DONE 			= BIT_2_SET,
	SF1_INIT_STEP2_DONE 			= BIT_3_SET,
	SF1_STARTUP_AUTO_ROUTINE_DONE 	= BIT_4_SET

}	StateFlags1_t;


/**	@note	BoardInfo_t.boardFeatures
 */
typedef enum
{
	BF_3_AXIS 						= BIT_0_SET,
	BF_BAT_MONITORING 				= BIT_1_SET,
	BF_ENCODERS 					= BIT_2_SET,
	BF_BODE_TEST					= BIT_3_SET,
	BF_SCRIPTING 					= BIT_4_SET,
	BF_CURRENT_SENSOR 				= BIT_5_SET,
	BF_MAG_SENSOR 					= BIT_6_SET,
	BF_ORDER_OF_AXES_LETUS 			= BIT_7_SET,
	BF_IMU_EEPROM 					= BIT_8_SET,
	BF_FRAME_IMU_EEPROM 			= BIT_9_SET,
	BF_CAN_PORT						= BIT_10_SET,
	BF_MOMENTUM 					= BIT_11_SET,
	BF_COGGING_CORRECTION 			= BIT_12_SET,
	BF_MOTOR4_CONTROL 				= BIT_13_SET,
	BF_ACC_AUTO_CALIB 				= BIT_14_SET,
	BF_BIG_FLASH	 				= BIT_15_SET 	// Firmware needs 256Kb of FLASH

}	BoardFeatures_t;


/**	@note	BoardInfo_t.connectionFlag
 */
typedef enum
{
	ConnF_DISCONNECTED_USB			= 0,
	ConnF_CONNECTION_USB			= 1

}	ConnectionFlag_t;


/**	@note	BoardInfo_t.boardFeaturesExt
 */
typedef enum
{
	BFE_EXT_IMU 					= BIT_0_SET,
	BFE_STATE_VARS 					= BIT_2_SET,
	BFE_POWER_MANAGEMENT 			= BIT_3_SET,
	BFE_GYRO_ADVANCED_CALIB 		= BIT_4_SET,
	BFE_LIMITED_VERSION 			= BIT_5_SET,
	BFE_REACTION 					= BIT_6_SET,
	BFE_ENCODER_LUT 				= BIT_7_SET

}	BoardFeaturesExt_t;


/**	@note	BoardInfo3_t.profileSetSlots
 */
typedef enum
{
	PSS_PROFILE_SET_1 				= BIT_0_SET,
	PSS_PROFILE_SET_2 				= BIT_1_SET,
	PSS_PROFILE_SET_3 				= BIT_2_SET,
	PSS_PROFILE_SET_4 				= BIT_3_SET,
	PSS_PROFILE_SET_5 				= BIT_4_SET,
	PSS_PROFILE_SET_BACKUP 			= BIT_5_SET

}	ProfileSetSlots_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									  Auto PID Flags
 */
/**	@addtogroup	Auto_PID
 *	@{
 */
/**	@note	AutoPID_t.profileID
 */
typedef enum
{
	APIDP_PROFILE_1					= 0,
	APIDP_PROFILE_2					= 1,
	APIDP_PROFILE_3					= 2,
	APIDP_PROFILE_4					= 3,
	APIDP_PROFILE_5					= 4

}	AutoPID_Profile_t;


/**	@note	AutoPID_t.cfgFlags
 */
typedef enum
{
	APIDCF_AUTO_PID_STOP 			= 0,
	APIDCF_AUTO_PID_CFG_ROLL 		= BIT_0_SET,
	APIDCF_AUTO_PID_CFG_PITCH		= BIT_1_SET,
	APIDCF_AUTO_PID_CFG_YAW 		= BIT_2_SET,
	APIDCF_AUTO_PID_CFG_SEND_GUI 	= BIT_3_SET,
	APIDCF_AUTO_PID_CFG_KEEP_CURRENT
									= BIT_4_SET,
	APIDCF_AUTO_PID_CFG_TUNE_LPF_FREQ
									= BIT_5_SET,
	APIDCF_AUTO_PID_CFG_ALL_PROFILES
									= BIT_6_SET

}	AutoPID_CfgFlags_t;


/**	@note	AutoPID_2_t.action
 */
typedef enum
{
	APID2A_ACTION_START				= 1,
	APID2A_ACTION_START_SAVE		= 2,
	APID2A_ACTION_SAVE				= 3,
	APID2A_ACTION_STOP				= 5,
	APID2A_ACTION_READ				= 6

}	AutoPID_2_Action_t;


/**	@note	AxisAPID2_t.axisFlag
 *
 *	Can be combined with @ref AutoPID_2_AxisNotchFilters_t
 */
typedef enum
{
	APID2AF_AXIS_IS_ENABLED			= BIT_0_SET,
	APID2AF_TUNE_LPF				= BIT_1_SET

}	AutoPID_2_AxisFlags_t;

/**	@note	AxisAPID2_t.axisFlag
 *
 *	Can be combined with @ref AutoPID_2_AxisFlags_t
 */
typedef enum
{
	APID2AF_NOTCH_FILTER_TUNE_0		= 0,
	APID2AF_NOTCH_FILTER_TUNE_1		= 1,
	APID2AF_NOTCH_FILTER_TUNE_2		= 2,
	APID2AF_NOTCH_FILTER_TUNE_3		= 3

}	AutoPID_2_AxisNotchFilters_t;

/**	@brief	Used as a function of joining
 * 			AutoPID_2 axis flags and AutoPID_2 axis
 * 			notch filter flags
 *
 *	@param	flag - clean value of AutoPID_2 axis flags
 *	@param	filter - clean value of AutoPID_2 axis notch filter
 *
 *	@return	Packed value to AxisAPID2_t.axisFlag
 */
static inline ui8 PackAPID_AxisFlag (AutoPID_2_AxisFlags_t flag, AutoPID_2_AxisNotchFilters_t filter)
{
	return (flag & 0b00000011) | ((filter << 2) & 0b00001100);
}


/**	@note	AutoPID_2_t.generalFlags
 */
typedef enum
{
	APID2GF_START_FROM_CURRENT_VALUES
									= BIT_0_SET,
	APID2GF_SAVE_RESULT_TO_ALL_PROFILES
									= BIT_1_SET,
	APID2GF_TUNE_GAIN_ONLY  		= BIT_2_SET,
	/* bit 3 - reserved */
	APID2GF_AUTOSAVE				= BIT_4_SET

}	AutoPID_2_GeneralFlags_t;


/**	@note	AutoPID_2_t.startupCfg
 */
typedef enum
{
	APID2SC_DISABLE					= 0,
	APID2SC_TUNE_GAIN_ONLY			= 1,
	APID2SC_TUNE_ALL_PARAMETERS		= 2

}	AutoPID_2_StartupCfg;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								  Motors State Flags
 */
/**	@addtogroup	Motors_State
 * 	@{
 */
/**	@note @ref	SBGC32_SetMotorsOFF, 2 arg
 */
typedef enum
{
	MM_NORMAL						= 0,
	MM_BREAK						= 1,
	MM_SAFE_STOP					= 2

}	MotorsMode_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *										 Reset Flags
 */
/**	@addtogroup	Boot_Mode
 * 	@{
 */
/**	@note @ref	SBGC32_Reset, 2 arg
 */
typedef enum
{
	RF_FULL_RESET_NO_CONFIRMATION	= 0,
	RF_FULL_RESET_CONFIRMATION		= 1,
	RF_RESTART_NO_CONFIRMATION		= 2,
	RF_RESTART_CONFIRMATION			= 3

}	ResetFlag_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									   Scripts Flags
 */
/**	@addtogroup	Scripts
 * 	@{
 */
/**	@note @ref	SBGC32_RunScript, 2 arg
 */
typedef enum
{
	SM_STOP							= 0,
	SM_START						= 1,
	SM_START_WITH_DEBUG				= 2

}	ScriptMode_t;


/**	@note @ref	SBGC32_RunScript, 3 arg
 */
typedef enum
{
	SSN_SLOT_1						= 0,
	SSN_SLOT_2						= 1,
	SSN_SLOT_3						= 2,
	SSN_SLOT_4						= 3,
	SSN_SLOT_5						= 4

}	ScriptSlotNum_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								 Service Other Flags
 */
/**	@addtogroup	Service_Other
 * 	@{
 */
/**	@note	Event_t.eventID
 */
typedef enum
{
	EID_EVENT_ID_MENU_BUTTON 		= 1,
	EID_EVENT_ID_MOTOR_STATE 		= 2,
	EID_EVENT_ID_EMERGENCY_STOP 	= 3,
	EID_EVENT_ID_CAMERA 			= 4,
	/** frw. ver. 2.68b8+ */
	EID_EVENT_ID_SCRIPT 			= 5

}	EventID_t;


/**	@note	Event_t.eventType
 */
typedef enum
{
	/* Applicable for EID_EVENT_ID_MENU_BUTTON,
	   EID_EVENT_ID_MOTOR_STATE, EID_EVENT_ID_EMERGENCY_STOP,
	   EID_EVENT_ID_SCRIPT */
	EVENT_TYPE_OFF 					= 1,
	EVENT_TYPE_ON 					= 2,
	EVENT_TYPE_HOLD 				= 4,

	/* Applicable for EID_EVENT_ID_CAMERA */
	EVENT_TYPE_REC_PHOTO 			= 1,
	EVENT_TYPE_PHOTO		 		= 2

}	EventType_t;
/**	@}
 */


/**	@note @ref	SBGC32_SetTriggerPin, 3 arg
 */
typedef enum
{
 	PS_PIN_LOW						= 0,
	PS_PIN_HIGH						= 1,
	/** frw. ver 2.66+ */
	PS_PIN_FLOATING					= 2

}	PinState_t;

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 							   Board Info Structures
 */
/**	@addtogroup	Board_Info
 * 	@{
 */
/**	@brief	Structure type for work with
 *  		BoardInfo parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			CMD_BOARD_INFO
 *
 *			RX 18 bytes
 *
 *	@ref	SBGC32_ReadBoardInfo function
 */
typedef struct __PACKED__
{
	ui8		boardVer;								/*!<  Multiplied by 10																*/
	ui16	firmwareVer;							/*!<  Split into decimal digits X.XX.X												*/
	ui8		stateFlags1;							/*!<  See @ref StateFlags1_t enumeration											*/
	ui16	boardFeatures;							/*!<  See @ref BoardFeatures_t enumeration											*/
	ui8		connectionFlag;							/*!<  See @ref ConnectionFlag_t enumeration											*/
	ui32	FRW_ExtraID;							/*!<  Used for specific builds only													*/
	ui16	boardFeaturesExt;						/*!<  Continues boardFeatures. See @ref BoardFeaturesExt_t enumeration				*/
	ui8		reserved [3];
	ui16	baseFRW_Ver;							/*!<  For “experimental” versions encodes the main version which they are based on	*/

}           BoardInfo_t;


/**	@brief	Structure type for work with
 *  		BoardInfo3 parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			CMD_BOARD_INFO_3
 *
 *			RX 69 bytes
 *
 *			Additional board information.
 *
 *	@ref	SBGC32_ReadBoardInfo3 function
 */
typedef struct __PACKED__
{
	ui8		deviceID [9];							/*!<  Unique ID used to identify each controller in licensing system 				*/
	ui8		MCU_ID [12];							/*!<  MCU ID, unique																*/
	ui32	EEPROM_Size;							/*!<  Size of available EEPROM in current device. Generally 32K bytes				*/

	ui16	scriptSlot1_Size,						/*!<  ...																			*/
			scriptSlot2_Size,						/*!<  ...																			*/
			scriptSlot3_Size,						/*!<  ...																			*/
			scriptSlot4_Size,						/*!<  ...																			*/
			scriptSlot5_Size;						/*!<  Size of user-written stored in each slot, 0 if slot is empty					*/

	ui8		profileSetSlots;						/*!<  See @ref ProfileSetSlots_t enumeration	 				 					*/
	ui8		profileSetCur;							/*!<  1 --> 6. A number of currently selected profile set 							*/
	ui8		flashSize;								/*!<  Actual FLASH memory size (a number of 32 Kb pages) 							*/
	ui8		reserved [31];

}			BoardInfo3_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								 Auto PID Structures
 */
/**	@addtogroup	Auto_PID
 * 	@{
 */
/**	@brief	Structure type for work with
 *  		AutoPID parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			CMD_AUTO_PID
 *
 *			TX 19 bytes
 *
 *			Starts automatic PID calibration
 *
 *	@ref	SBGC32_TuneAutoPID function
 */
typedef struct __PACKED__
{
	ui8		profileID,								/*!<  See @ref AutoPID_Profile_t enumeration										*/
			cfgFlags,								/*!<  See @ref AutoPID_CfgFlags_t enumeration										*/
			Gain_VS_Stability,						/*!<  0 --> 255																		*/
			momentum,								/*!<  0 --> 255																		*/
			action,									/*!<  0 - start tuning																*/
			reserved [14];

}			AutoPID_t;


/**	@brief	Part of AutoPID_2_t structure
 *
 * 	@note	AutoPID_2_t.AxisAPID2_t
 */
typedef struct __PACKED__
{
	ui8		axisFlag,								/*!<  See @ref AutoPID_2_AxisFlags_t and @ref AutoPID_2_AxisNotchFilters_t
														  enumerations																	*/
			gain,									/*!<  0 --> 255. Stability vs performance ratio										*/
			stimulus,								/*!<  0 --> 255. Stimulus signal strength											*/
			effectiveFreq,							/*!<  0 --> 255. Units: Hz. Effective frequency										*/
			problemFreq,							/*!<  0 --> 255. Units: Hz. Problematic frequency									*/
			problemMargin,							/*!<  0 --> 255. Units: dB*10. Problematic margin									*/
			reserved2 [6];

}			AxisAPID2_t;

/**	@brief	Structure type for work with
 *  		AutoPID_2 parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			CMD_AUTO_PID2
 *
 *			Firmware: 2.70+
 *
 *			TX ??? bytes
 *
 *	@ref	SBGC32_TuneAutoPID_2 function
 */
typedef struct __PACKED__
{
	ui8		action;									/*!<  See @ref AutoPID_2_Action_t enumeration										*/
	ui8		reserved1 [10];
	/* The following data is required only for
	   APID2A_ACTION_START, APID2A_ACTION_START_SAVE */
	ui8		cfgVersion;

	AxisAPID2_t	AxisAPID2 [3];						/*!<  ROLL : PITCH : YAW															*/

	ui16	generalFlags;							/*!<  See @ref AutoPID_2_GeneralFlags_t enumeration									*/
	ui8		startupCfg;								/*!<  See @ref AutoPID_2_StartupCfg enumeration										*/
	ui8		reserved3 [22];

}			AutoPID_2_t;


/**	@brief	Part of AutoPID_State_t structure
 *
 * 	@note	AutoPID_State_t.AxisAPIDS
 */
typedef struct __PACKED__
{
	float	trackingError;							/*!< Current error between the target and actual system response					*/
	ui8		reserved1 [6];

}			AxisAPIDS_t;

/**	@brief	Structure type for work with
 *  		AutoPID_Continuous parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			RX 57 bytes
 *
 *			Realtime information about progress
 *			of PID auto tuning
 *
 *	@ref	SBGC32_ParseAutoPID_StateCmd function
 */
typedef struct __PACKED__
{
	ui8		p [3],
			i [3],
			d [3];

	ui16	LPF_Freq [3];
	ui16	iterationCnt;

	AxisAPIDS_t	AxisAPIDS [3];						/*!<  ROLL : PITCH : YAW															*/

	ui8		reserved2 [10];

}			AutoPID_State_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								   Scripts Structure
 */
/**	@brief	Structure type for work with
 *  		ScriptDebugInfo parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			RX 3 bytes
 *
 *			Realtime script debug information
 *
 *	@ref	SBGC32_ParseScriptDebugInfoCmd function
 */
typedef struct
{
	ui16 	curComCounter;							/*!<  Current command counter														*/
	ui8		errCode;								/*!<  See @ref ErrorCode_t enumeration												*/

}			ScriptDebugInfo_t;



/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								State Vars Structure
 */
/**	@addtogroup	State_Vars
 * 	@{
 */
/**	@brief	Structure type for work with
 *  		StateVars parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			CMD_WRITE_STATE_VARS
 *			CMD_READ_STATE_VARS
 *
 *			Firmware: 2.68b7+ (“Extended” family only)
 *
 *			TX/RX 192 bytes
 *
 *	@ref	SBGC32_WriteStateVars function\n
 *	@ref	SBGC32_ReadStateVars function
 */
typedef struct __PACKED__
{
	ui8 	stepSignalVars [6];						/*!<  Step signal current value														*/
	ui8		subError;								/*!<  Last code of EMERGENCY_STOP error												*/
	ui8		maxAcc;									/*!<  Units: 1/16 G  																*/
	ui32	workTime;								/*!<  Units: seconds																*/
	ui16	startupCnt;
	ui16	maxCurrent;								/*!<  Units: mA																		*/

	ui8		IMU_TempMin,							/*!<  Units: °C																		*/
			IMU_TempMax,							/*!<  Units: °C																		*/
			MCU_TempMin,							/*!<  Units: °C																		*/
			MCU_TempMax;							/*!<  Units: °C																		*/

	ui8		shockCnt [4];
	ui32	energyTime;								/*!<  Units: seconds																*/
	float	energy;									/*!<  Units: Watt*hour  															*/
	ui32	AVG_CurrentTime;						/*!<  Units: seconds																*/
	float	AVG_Current;							/*!<  Units: A		  																*/
	ui8 	reserved [152];

}			StateVars_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							Service Other Structures
 */
/**	@addtogroup	Service_Other
 * 	@{
 */
/**	@brief	Structure type for work with
 *  		Event parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			Firmware: 2.65+
 *
 *			RX 4 bytes
 *
 *	@ref	SBGC32_GetEvent function
 */
typedef struct __PACKED__
{
	ui8		eventID,								/*!<  See @ref EventID_t enumeration												*/
			eventType;								/*!<  See @ref EventType_t enumeration												*/

	ui8		param [2];								/*!<  Possible value and its meaning depends on the eventID and eventType parameters*/
	/* This command may be expanded by extra
	   parameters in future versions... */
}			Event_t;


/**	@brief	Structure type for work with
 *  		BeeperSettings parameters.
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			TX ? bytes
 *
 *	@ref	SBGC32_PlayBeeper function
 */
typedef struct __PACKED__
{
	ui16	mode;									/*!<  See @ref BeeperModes_t enumeration											*/

	ui8		noteLength,								/*!<  Units: 8ms samples. The duration of each note in custom melody mode			*/
			decayFactor,							/*!<  Set the envelope "attack-decay" after each pause, that makes sound
														  more natural. The bigger value, the longer decay. 0 - no decay				*/
			reserved [8];

	ui16	notesFreqHz [MAX_NOTES_QANTITY];		/*!<  Units: Hz																		*/
	ui8		notesQuan;								/*!<  Number of notes in one message. The parameter is only used in the function	*/

}			BeeperSettings_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								 Function Prototypes
 */
/**	@addtogroup	Board_Info
 * 	@{
 */
TxRxStatus_t SBGC32_ReadBoardInfo (GeneralSBGC_t *generalSBGC, BoardInfo_t *boardInfo, ui16 cfg);
TxRxStatus_t SBGC32_ReadBoardInfo3 (GeneralSBGC_t *generalSBGC, BoardInfo3_t *boardInfo3);
/**	@}
 */


/**	@addtogroup	Auto_PID
 * 	@{
 */
TxRxStatus_t SBGC32_TuneAutoPID (GeneralSBGC_t *generalSBGC, const AutoPID_t *autoPID, ConfirmationState_t *confirmationState);
TxRxStatus_t SBGC32_TuneAutoPID_2 (GeneralSBGC_t *generalSBGC, const AutoPID_2_t *autoPID_2, ConfirmationState_t *confirmationState);
void SBGC32_ParseAutoPID_StateCmd (SerialCommand_t *cmd, AutoPID_State_t *autoPID_State);
/**	@}
 */


/**	@addtogroup	Motors_State
 * 	@{
 */
TxRxStatus_t SBGC32_SetMotorsON (GeneralSBGC_t *generalSBGC, ConfirmationState_t *confirmationState);
TxRxStatus_t SBGC32_SetMotorsOFF (GeneralSBGC_t *generalSBGC, MotorsMode_t mode, ConfirmationState_t *confirmationState);
/**	@}
 */


/**	@addtogroup	Boot_Mode
 * 	@{
 */
TxRxStatus_t SBGC32_SetBootMode (GeneralSBGC_t *generalSBGC);
TxRxStatus_t SBGC32_SetBootModeExt (GeneralSBGC_t *generalSBGC, Boolean_t confirm, ui16 delayMs, ConfirmationState_t *confirmationState);
TxRxStatus_t SBGC32_Reset (GeneralSBGC_t *generalSBGC, ResetFlag_t flag, ui16 delayMs);
/**	@}
 */


/**	@addtogroup	Scripts
 * 	@{
 */
TxRxStatus_t SBGC32_RunScript (GeneralSBGC_t *generalSBGC, ScriptMode_t mode, ScriptSlotNum_t slot, ConfirmationState_t *confirmationState);
void SBGC32_ParseScriptDebugInfoCmd (SerialCommand_t *cmd, ScriptDebugInfo_t *scriptDebugInfo);
/**	@}
 */


/**	@addtogroup	State_Vars
 * 	@{
 */
/* EFO */	TxRxStatus_t SBGC32_WriteStateVars (GeneralSBGC_t *generalSBGC, const StateVars_t *stateVars, ConfirmationState_t *confirmationState);
/* EFO */	TxRxStatus_t SBGC32_ReadStateVars (GeneralSBGC_t *generalSBGC, StateVars_t *stateVars);
/**	@}
 */


/**	@addtogroup	Service_Other
 * 	@{
 */
void SBGC32_ParseEventCmd (SerialCommand_t *cmd, Event_t *event);
TxRxStatus_t SBGC32_SetTriggerPin (GeneralSBGC_t *generalSBGC, TriggerPinID_t pinID, PinState_t state, ConfirmationState_t *confirmationState);
TxRxStatus_t SBGC32_ExecuteMenu (GeneralSBGC_t *generalSBGC, MenuCommands_t cmdID, ConfirmationState_t *confirmationState);
TxRxStatus_t SBGC32_SetServoOut (GeneralSBGC_t *generalSBGC, const i16 servoTime [8]);
TxRxStatus_t SBGC32_PlayBeeper (GeneralSBGC_t *generalSBGC, const BeeperSettings_t *beeperSettings);
TxRxStatus_t SBGC32_SignMessage (GeneralSBGC_t *generalSBGC, ui8 signType, const char txMessage [MAX_MESSAGE_LENGTH], char rxMessage [MAX_MESSAGE_LENGTH]);
/**	@}
 */


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef 		__cplusplus
			}
#endif

#endif      /* _SEVICE_H_ */
