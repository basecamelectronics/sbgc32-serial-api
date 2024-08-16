/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.0
 *
 *	@file		service.h
 *
 *	@brief		Service header file
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
 *	@defgroup	Service SBGC32 Service
 *	@ingroup	Modules
 *		@brief	SBGC32 Service Title Module
 *	____________________________________________________________________
 *
 *	@defgroup	Board_Info Board Information
 *	@ingroup	Service
 *		@brief	Board Information Module
 *
 *				Covered Commands:
 *
 *				### CMD_BOARD_INFO
 *				### CMD_BOARD_INFO_3
 *
 *	@defgroup	Auto_PID Auto PID
 *	@ingroup	Service
 *		@brief	Auto PID Module
 *
 *				Covered Commands:
 *
 *				### CMD_AUTO_PID
 *				### CMD_AUTO_PID2
 *
 *	@defgroup	Motors_State Motors State
 *	@ingroup	Service
 *		@brief	Motors State Module
 *
 *				Covered Commands:
 *
 *				### CMD_MOTORS_ON
 *				### CMD_MOTORS_OFF
 *				### CMD_SYNC_MOTORS
 *				### CMD_EXT_MOTORS_STATE
 *
 *	@defgroup	Boot_Mode Boot Mode
 *	@ingroup	Service
 *		@brief	Boot Mode Module
 *
 *				Covered Commands:
 *
 *				### CMD_BOOT_MODE_3
 *				### CMD_RESET
 *
 *	@defgroup	Scripts Scripts
 *	@ingroup	Service
 *		@brief	Scripts Module
 *
 *				Covered Commands:
 *
 *				### CMD_RUN_SCRIPT
 *				### CMD_SCRIPT_DEBUG
 *
 *	@defgroup	State_Vars State of Variables
 *	@ingroup	Service
 *		@brief	State of Variables Module
 *
 *				Covered Commands:
 *
 *				### CMD_WRITE_STATE_VARS
 *				### CMD_READ_STATE_VARS
 *
 *	@defgroup	Debug_Port Debug Port
 *	@ingroup	Service
 *		@brief	Debug Port Module
 *
 *				Covered Commands:
 *
 *				### CMD_SET_DEBUG_PORT
 *
 *	@defgroup	Transparent_SerialAPI Transparent SerialAPI
 *	@ingroup	Service
 *		@brief	Transparent SerialAPI Module
 *
 *				Covered Commands:
 *
 *				###	CMD_TRANSPARENT_SAPI
 *
 *	@defgroup	Service_Other Service Other
 *	@ingroup	Service
 *		@brief	Service Other Module
 *
 *				Covered Commands:
 *
 *				### CMD_TRIGGER_PIN
 *				### CMD_EXECUTE_MENU
 *				### CMD_SERVO_OUT
 *				### CMD_BEEP_SOUND
 *				### CMD_SIGN_MESSAGE
 *				### CMD_CAN_DEVICE_SCAN
 *	____________________________________________________________________
 */

#ifndef		MODULES_SERVICE_H_
#define		MODULES_SERVICE_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../sbgc32.h"


#if (SBGC_SERVICE_MODULE)

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *										   Constants
 */
/**	@addtogroup	Service_Other
 *	@{
 */
/** Maximal quantity of servo output pins in SBGC32.
	See @ref SBGC32_SetServoOut */
#define		SBGC_SERVO_OUTS_NUM				4

/** Value to disable controller's servo signal out.
	See @ref SBGC32_SetServoOut */
#define		SBGC_SERVO_OUT_DISABLED			(-1)

/** Maximal length of message to sign.
	See @ref SBGC32_SignMessage */
#define		SBGC_MAX_MESSAGE_LENGTH			32

/** Maximal number of notes in one serial command.
	See @ref SBGC32_PlayBeeper */
#define		SBGC_MAX_NOTES_QUANTITY			50
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									Board Info Flags
 */
/**	@addtogroup	Board_Info
 *	@{
 */
/**	@note	sbgcBoardInfo_t.boardFeatures
 */
typedef enum
{
	BF_3_AXIS						= BIT_0_SET,
	BF_BAT_MONITORING				= BIT_1_SET,
	BF_ENCODERS						= BIT_2_SET,
	BF_BODE_TEST					= BIT_3_SET,
	BF_SCRIPTING					= BIT_4_SET,
	BF_CURRENT_SENSOR				= BIT_5_SET,
	BF_MAG_SENSOR					= BIT_6_SET,
	BF_ORDER_OF_AXES_LETUS			= BIT_7_SET,
	BF_IMU_EEPROM					= BIT_8_SET,
	BF_FRAME_IMU_EEPROM				= BIT_9_SET,
	BF_CAN_PORT						= BIT_10_SET,
	BF_MOMENTUM						= BIT_11_SET,
	BF_COGGING_CORRECTION			= BIT_12_SET,
	BF_MOTOR4_CONTROL				= BIT_13_SET,
	BF_ACC_AUTO_CALIB				= BIT_14_SET,
	BF_BIG_FLASH					= BIT_15_SET,	// Firmware needs 256Kb of FLASH

	/* Artificial expanding for
	   serialAPI_General_t.boardFeatures only */
	BF_EXT_IMU						= BIT_16_SET,
	BF_STATE_VARS					= BIT_18_SET,
	BF_POWER_MANAGEMENT				= BIT_19_SET,
	BF_GYRO_ADVANCED_CALIB			= BIT_20_SET,
	BF_LIMITED_VERSION				= BIT_21_SET,
	BF_REACTION						= BIT_22_SET,
	BF_ENCODER_LUT					= BIT_23_SET

}	sbgcBoardFeature_t;


/**	@note	sbgcBoardInfo_t.connectionFlag
 */
typedef enum
{
	ConnF_DISCONNECTED_USB			= 0,
	ConnF_CONNECTION_USB			= 1

}	sbgcConnectionFlag_t;


/**	@note	sbgcBoardInfo_t.boardFeaturesExt
 */
typedef enum
{
	BFE_EXT_IMU						= BIT_0_SET,
	BFE_STATE_VARS					= BIT_2_SET,
	BFE_POWER_MANAGEMENT			= BIT_3_SET,
	BFE_GYRO_ADVANCED_CALIB			= BIT_4_SET,
	BFE_LIMITED_VERSION				= BIT_5_SET,
	BFE_REACTION					= BIT_6_SET,
	BFE_ENCODER_LUT					= BIT_7_SET

}	sbgcBoardFeatureExt_t;


/**	@note	sbgcBoardInfo3_t.profileSetSlots
 */
typedef enum
{
	PSS_PROFILE_SET_1				= BIT_0_SET,
	PSS_PROFILE_SET_2				= BIT_1_SET,
	PSS_PROFILE_SET_3				= BIT_2_SET,
	PSS_PROFILE_SET_4				= BIT_3_SET,
	PSS_PROFILE_SET_5				= BIT_4_SET,
	PSS_PROFILE_SET_BACKUP			= BIT_5_SET

}	sbgcProfileSetSlots_t;


/**	@note	sbgcBoardInfo3_t.boardFeaturesExt2
 */
typedef enum
{
	BFE2_PLUS_VER					= BIT_0_SET,
	BFE2_SHAKE_GENERATOR			= BIT_1_SET,
	BFE2_EXT_MOTORS					= BIT_2_SET,
	BFE2_QUAT_CONTROL				= BIT_3_SET,
	BFE2_ADC4						= BIT_4_SET

}	sbgcBoardFeatureExt2_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									  Auto PID Flags
 */
/**	@addtogroup	Auto_PID
 *	@{
 */
/**	@note	sbgcAutoPID_t.cfgFlags
 */
typedef enum
{
	APIDC_FLAG_STOP					= 0,
	APIDC_FLAG_ROLL					= BIT_0_SET,
	APIDC_FLAG_PITCH				= BIT_1_SET,
	APIDC_FLAG_YAW					= BIT_2_SET,
	APIDC_FLAG_SEND_GUI				= BIT_3_SET,
	APIDC_FLAG_KEEP_CURRENT			= BIT_4_SET,
	APIDC_FLAG_TUNE_LPF_FREQ		= BIT_5_SET,
	APIDC_FLAG_ALL_PROFILES			= BIT_6_SET

}	sbgcAutoPID_CfgFlag_t;


/**	@note	sbgcAutoPID2_t.action
 */
typedef enum
{
	APID2A_ACTION_START				= 1,
	APID2A_ACTION_START_SAVE		= 2,
	APID2A_ACTION_SAVE				= 3,
	APID2A_ACTION_STOP				= 5,
	APID2A_ACTION_READ				= 6

}	sbgcAutoPID2_Action_t;


/**	@note	sbgcAxisAPID2_t.axisFlag \n
 *			Part of sbgcAutoPID2_t \n
 *
 *	Can be combined with @ref sbgcAutoPID2_AxisNotchFilter_t
 */
typedef enum
{
	APID2AF_AXIS_IS_ENABLED			= BIT_0_SET,
	APID2AF_TUNE_LPF				= BIT_1_SET

}	sbgcAutoPID2_AxisFlag_t;

/**	@note	sbgcAxisAPID2_t.axisFlag \n
 *			Part of sbgcAutoPID2_t \n
 *
 *	Can be combined with @ref sbgcAutoPID2_AxisFlag_t
 */
typedef enum
{
	APID2AF_NOTCH_FILTER_TUNE_0		= 0,
	APID2AF_NOTCH_FILTER_TUNE_1		= 1,
	APID2AF_NOTCH_FILTER_TUNE_2		= 2,
	APID2AF_NOTCH_FILTER_TUNE_3		= 3

}	sbgcAutoPID2_AxisNotchFilter_t;

/**	@brief	Used as a function of joining
 *			AutoPID2 axis flags and AutoPID2 axis
 *			notch filter flags
 *
 *	@param	flag - clean value of AutoPID2 axis flags
 *	@param	filter - clean value of AutoPID2 axis notch filter
 *
 *	@return	Packed value to sbgcAxisAPID2_t.axisFlag
 */
static inline ui8 ParserSBGC32_PackAPID_AxisFlag (sbgcAutoPID2_AxisFlag_t flag, sbgcAutoPID2_AxisNotchFilter_t filter)
{
	return (flag & 0b00000011) | ((filter << 2) & 0b00001100);
}


/**	@note	sbgcAutoPID2_t.generalFlags
 */
typedef enum
{
	APID2GF_START_FROM_CURRENT_VALUES
									= BIT_0_SET,
	APID2GF_SAVE_RESULT_TO_ALL_PROFILES
									= BIT_1_SET,
	APID2GF_TUNE_GAIN_ONLY			= BIT_2_SET,
	/* bit 3 - reserved */
	APID2GF_AUTOSAVE				= BIT_4_SET

}	sbgcAutoPID2_GeneralFlag_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								  Motors State Flags
 */
/**	@addtogroup	Motors_State
 *	@{
 */
/**	@note	@ref SBGC32_SetMotorsOFF, 2 arg
 */
typedef enum
{
	MOTOR_MODE_NORMAL				= 0,
	MOTOR_MODE_BREAK				= 1,
	MOTOR_MODE_SAFE_STOP			= 2

}	sbgcMotorsMode_t;


/**	@note sbgcSyncMotors_t.axis
 */
typedef enum
{
	SYNC_MOTOR_AXIS_ROLL			= 0,
	SYNC_MOTOR_AXIS_PITCH			= 1,
	SYNC_MOTOR_AXIS_YAW				= 2

}	sbgcSyncMotorsAxis_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *										 Reset Flags
 */
/**	@addtogroup	Boot_Mode
 *	@{
 */
/**	@note	@ref SBGC32_Reset, 2 arg
 */
typedef enum
{
	RESET_FLAG_NEED_CONFIRMATION	= BIT_0_SET,
	RESET_FLAG_RESTORE_STATE		= BIT_1_SET

}	sbgcResetFlag_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									   Scripts Flags
 */
/**	@addtogroup	Scripts
 *	@{
 */
/**	@note	@ref SBGC32_RunScript, 2 arg
 */
typedef enum
{
	ScrtM_STOP						= 0,
	ScrtM_START						= 1,
	ScrtM_START_WITH_DEBUG			= 2

}	sbgcScriptMode_t;


/**	@note	@ref SBGC32_RunScript, 3 arg
 */
typedef enum
{
	ScrtSN_SLOT_1					= 0,
	ScrtSN_SLOT_2					= 1,
	ScrtSN_SLOT_3					= 2,
	ScrtSN_SLOT_4					= 3,
	ScrtSN_SLOT_5					= 4

}	sbgcScriptSlotNum_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									Debug Port Flags
 */
/**	@addtogroup	Debug_Port
 *	@{
 */
/**	@note	@ref SBGC32_SetDebugPort, 3 arg
 */
typedef enum
{
	DPA_STOP_USING_DEBUG_PORT		= 0,
	DPA_START_USING_DEBUG_PORT		= 1

}	sbgcDebugPortAction_t;


/**	@note	@ref SBGC32_SetDebugPort, 4 arg
 */
typedef enum
{
	DPF_CMD_REALTIME_DATA_3			= BIT_0_SET,
	DPF_CMD_REALTIME_DATA_4			= BIT_1_SET,
	DPF_CMD_REALTIME_DATA_CUSTOM	= BIT_2_SET,
	DPF_CMD_DEBUG_VARS_3			= BIT_3_SET,
	DPF_CMD_MAVLINK_DEBUG			= BIT_4_SET,
	DPF_CMD_GET_ANGLES				= BIT_5_SET,
	DPF_CMD_GET_ANGLES_EXT			= BIT_6_SET,
	DPF_CMD_BODE_TEST_DATA			= BIT_7_SET,
	DPF_CMD_HELPER_DATA				= BIT_8_SET,
	DPF_CMD_AHRS_HELPER				= BIT_9_SET,
	DPF_CMD_GYRO_CORRECTION			= BIT_10_SET,
	DPF_CMD_CONTROL					= BIT_11_SET,
	DPF_CMD_SET_ADJ_VARS_VAL		= BIT_12_SET,
	DPF_CMD_API_VIRT_CH_CONTROL		= BIT_13_SET,
	DPF_CMD_API_VIRT_CH_HIGH_RES	= BIT_14_SET

}	sbgcDebugPortFilter_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						 Transparent SerialAPI Flags
 */
/**	@addtogroup	Transparent_SerialAPI
 *	@{
 */
/**	@note	@ref ParserSBGC32_PackTC_Target, 1 arg\n
 *
 *	Can be combined with @ref sbgcTransparentCommandDevice_t
 *	and @ref sbgcTransparentCommandFlag_t
 */
typedef enum
{
	TC_PORT_DEVICE_1				= 0,
	TC_PORT_DEVICE_2				= 1,
	TC_PORT_DEVICE_3				= 2,
	TC_PORT_DEVICE_4				= 3

}	sbgcTransparentCommandPort_t;

/**	@note	@ref ParserSBGC32_PackTC_Target, 2 arg\n
 *
 *	Can be combined with @ref sbgcTransparentCommandPort_t
 *	and @ref sbgcTransparentCommandFlag_t
 */
typedef enum
{
	TC_DEVICE_SBGC32				= 4,
	TC_DEVICE_GPS_IMU				= 5,
	TC_DEVICE_CAN_IMU_MAIN			= 6,
	TC_DEVICE_CAN_IMU_FRAME			= 7,
	TC_DEVICE_GPS_SPLIT_RCVR		= 8,
	TC_DEVICE_CAN_SERIAL_HUB_1		= 9,
	TC_DEVICE_CAN_SERIAL_HUB_2		= 10,

	TC_DEVICE_CAN_DRV_1				= 11,
	TC_DEVICE_CAN_DRV_2				= 12,
	TC_DEVICE_CAN_DRV_3				= 13,
	TC_DEVICE_CAN_DRV_4				= 14

}	sbgcTransparentCommandDevice_t;

/**	@note	@ref ParserSBGC32_PackTC_Target, 3 arg\n
 *
 *	Can be combined with @ref sbgcTransparentCommandPort_t
 *	and @ref sbgcTransparentCommandDevice_t
 */
typedef enum
{
	TC_FLAG_SKIP_DATA_PACKET		= 0,
	TC_FLAG_BLOCK_AND_WAIT			= BIT_6_SET

}	sbgcTransparentCommandFlag_t;

/**	@brief	Used as a function of joining
 *			the port, device kind and flag parameters
 *			of the SerialAPI transparent command
 *
 *	@param	port - port on the target device
 *	@param	device - target device kind
 *	@param	flag -  wait flag
 *
 *	@return	Packed value for sbgcTransparentCommand_t.target field
 */
static inline ui8 ParserSBGC32_PackTC_Target (sbgcTransparentCommandPort_t port, sbgcTransparentCommandDevice_t device,
											  sbgcTransparentCommandFlag_t flag)
{
	return (port | device | flag);
}
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								 Service Other Flags
 */
/**	@addtogroup	Service_Other
 *	@{
 */
/**	@note	@ref SBGC32_SetTriggerPin, 3 arg
 */
typedef enum
{
	sbgcPIN_STATE_LOW				= 0,
	sbgcPIN_STATE_HIGH				= 1,
	/* frw. ver 2.66+ */
	sbgcPIN_STATE_FLOATING			= 2

}	sbgcPinState_t;


/**	@brief	Various beep modes
 *
 *	@note	sbgcMainParams3_t.beeperModes \n
 *			sbgcBeeperSettings_t.mode
 */
typedef enum
{
	BEEP_MODE_CALIBRATE				= BIT_0_SET,
	BEEP_MODE_CONFIRM				= BIT_1_SET,
	BEEP_MODE_ERROR					= BIT_2_SET,
	BEEP_MODE_CLICK					= BIT_4_SET,
	BEEP_MODE_COMPLETE				= BIT_5_SET,
	BEEP_MODE_INTRO					= BIT_6_SET,

	BEEP_MODE_CUSTOM_MELODY			= BIT_15_SET

}	sbgcBeeperMode_t;


/**	@note sbgcCAN_DeviceScan_t.ID
 */
typedef enum
{
	CDI_CAN_IMU_MAIN				= 5,
	CDI_CAN_IMU_FRAME				= 6,
	CDI_GPS_IMU_MAIN				= 7,
	CDI_CAN_DRV_1					= 17,
	CDI_CAN_DRV_2					= 18,
	CDI_CAN_DRV_3					= 19,
	CDI_CAN_DRV_4					= 20,
	CDI_CAN_DRV_5					= 21,
	CDI_CAN_DRV_6					= 22,
	CDI_CAN_DRV_7					= 23,
	CDI_CAN_IMU_MAIN_OLD			= 28,
	CDI_CAN_IMU_FRAME_OLD			= 29

}	sbgcCAN_DeviceID_t;


/**	@note sbgcCAN_DeviceScan_t.type
 */
typedef enum
{
	CDT_MOTOR_DRIVER				= 1,
	CDT_IMU							= 2,

	CDT_HARDWARE_ASSIGNED			= BIT_7_SET

}	sbgcCAN_DeviceType_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							   Board Info Structures
 */
/**	@addtogroup	Board_Info
 *	@{
 */
/**	@brief	Structure type for work with
 *			BoardInfo parameters
 *
 *	@ref	SBGC32_ReadBoardInfo function
 */
typedef struct PACKED__
{
	ui8		boardVer;								/*!<  Multiplied by 10																*/
	ui16	firmwareVer;							/*!<  Split into decimal digits X.XX.X												*/
	ui8		stateFlags;								/*!<  See @ref sbgcStateFlag_t enumeration											*/
	ui16	boardFeatures;							/*!<  See @ref sbgcBoardFeature_t enumeration										*/
	ui8		connectionFlag;							/*!<  See @ref sbgcConnectionFlag_t enumeration										*/
	ui32	frwExtraID;								/*!<  Used for specific builds only													*/
	ui16	boardFeaturesExt;						/*!<  Continues boardFeatures. See @ref sbgcBoardFeatureExt_t enumeration			*/

	ui8		mainIMU_SensModel,						/*!<  ...																			*/
			frameIMU_SensModel;						/*!<  ...For the CAN_IMU used as a main or a frame IMU, reports the assigned
														  external sensor model. Frw. ver. 2.73+										*/

	ui8		buildNumber;							/*!<  Firmware version build number. Frw. ver. 2.73+								*/
	ui16	baseFrwVer;								/*!<  For "experimental" versions encodes the main version which they are based on	*/

}           sbgcBoardInfo_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t boardInfoReferenceInfoArray [];
	extern const ui8 boardInfoReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif


/**	@brief	Structure type for work with
 *			BoardInfo3 parameters
 *
 *	@ref	SBGC32_ReadBoardInfo3 function
 */
typedef struct PACKED__
{
	ui8		deviceID [9];							/*!<  Unique ID used to identify each controller in licensing system				*/
	ui8		MCU_ID [12];							/*!<  MCU ID, unique																*/
	ui32	EEPROM_Size;							/*!<  Size of available EEPROM in current device. Generally 32K bytes				*/

	ui16	scriptSlot1_Size,						/*!<  ...																			*/
			scriptSlot2_Size,						/*!<  ...																			*/
			scriptSlot3_Size,						/*!<  ...																			*/
			scriptSlot4_Size,						/*!<  ...																			*/
			scriptSlot5_Size;						/*!<  ...Size of user-written scripts stored in five slots, 0 if slot is empty		*/

	ui8		profileSetSlots;						/*!<  See @ref sbgcProfileSetSlots_t enumeration									*/
	ui8		profileSetCur;							/*!<  1 --> 6. A number of currently selected profile set							*/
	ui8		flashSize;								/*!<  Actual FLASH memory size (a number of 32 Kb pages)							*/
	ui8		IMU_CalibInfo [2];

	ui16	scriptSlot6_Size,						/*!<  ...																			*/
			scriptSlot7_Size,						/*!<  ...																			*/
			scriptSlot8_Size,						/*!<  ...																			*/
			scriptSlot9_Size,						/*!<  ...																			*/
			scriptSlot10_Size;						/*!<  ...Size of user-written scripts stored in five add. slots, 0 if slot is empty	*/

	ui16	hwFlags;								/*!<  Board hardware configuration. Bit0: one-wire crypto IC is installed			*/
	ui32	boardFeaturesExt2;						/*!<  See @ref sbgcBoardFeatureExt2_t enumeration. Frw. ver. 2.73+					*/

	ui8		CAN_DrvMainLimit,						/*!<  ...																			*/
			CAN_DrvAuxLimit;						/*!<  ...The number of licensed external motor drivers "CAN Driver" for the main
														  stabilization axes and auxiliary motors. Frw. ver. 2.73+						*/

	ui8		adjVarsTotalNum;						/*!<  A total number of adjustable variables in the system. Frw. ver. 2.73+			*/
	ui8		reserved [10];

}			sbgcBoardInfo3_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t boardInfo3_ReferenceInfoArray [];
	extern const ui8 boardInfo3_ReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								 Auto PID Structures
 */
/**	@addtogroup	Auto_PID
 *	@{
 */
/**	@brief	Structure type for work with
 *			AutoPID parameters
 *
 *	@ref	SBGC32_TuneAutoPID function
 */
typedef struct PACKED__
{
	ui8		profileID,								/*!<  See @ref sbgcProfile_t enumeration											*/
			cfgFlags,								/*!<  See @ref sbgcAutoPID_CfgFlag_t enumeration									*/
			Gain_VS_Stability,						/*!<  0 --> 255																		*/
			momentum,								/*!<  0 --> 255																		*/
			action,									/*!<  0 - start tuning																*/
			reserved [14];

}			sbgcAutoPID_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t autoPID_ReferenceInfoArray [];
	extern const ui8 autoPID_ReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif


/**	@brief	Part of AutoPID2_t structure
 *
 *	@note	sbgcAutoPID2_t.AxisAPID2
 */
typedef struct PACKED__
{
	ui8		axisFlag;								/*!<  See @ref sbgcAutoPID2_AxisFlag_t and @ref sbgcAutoPID2_AxisNotchFilter_t
														  enumerations																	*/
	ui8		gain;									/*!<  0 --> 255. Stability vs performance ratio										*/
	ui16	stimulusGain;							/*!<  0 --> 65535. Stimulus signal strength											*/

	ui8		effectiveFreq,							/*!<  0 --> 255. Units: Hz. Effective frequency										*/
			problemFreq,							/*!<  0 --> 255. Units: Hz. Problematic frequency									*/
			problemMargin,							/*!<  0 --> 255. Units: dB/10. Problematic margin									*/
			reserved2 [6];

}			sbgcAxisAPID2_t;

/**	@brief	Structure type for work with
 *			AutoPID2 parameters
 *
 *	@ref	SBGC32_TuneAutoPID2 function
 */
typedef struct PACKED__
{
	ui8		action;									/*!<  See @ref sbgcAutoPID2_Action_t enumeration									*/
	ui8		reserved1 [10];

	/* The following data is required only for
	   APID2A_ACTION_START, APID2A_ACTION_START_SAVE */
	ui8		cfgVersion;

	sbgcAxisAPID2_t	AxisAPID2 [3];					/*!<  ROLL : PITCH : YAW															*/

	ui16	generalFlags;							/*!<  See @ref sbgcAutoPID2_GeneralFlag_t enumeration								*/
	ui8		reserved3;

	ui8		testFreqFrom,							/*!<  Units: 0.1 Hz. Test signal start frequency 									*/
			testFreqTo;								/*!<  Units: 1 Hz. Test signal start frequency 										*/

	ui8		reserved4 [17];

}			sbgcAutoPID2_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t autoPID2_ReferenceInfoArray [];
	extern const ui8 autoPID2_ReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif


/**	@brief	Part of sbgcAutoPID_State_t structure
 *
 *	@note	sbgcAutoPID_State_t.AxisAPIDS
 */
typedef struct PACKED__
{
	float	trackingError;							/*!< Current error between the target and actual system response					*/
	ui8		reserved1 [6];

}			sbgcAxisAPIDS_t;

/**	@brief	Structure type for work with
 *			AutoPID_Continuous parameters
 *
 *	@ref	SBGC32_ReadAutoPID_StateCmd function
 */
typedef struct PACKED__
{
	ui8		p [3],
			i [3],
			d [3];

	ui16	LPF_Freq [3];
	ui16	iterationCnt;

	sbgcAxisAPIDS_t	AxisAPIDS [3];					/*!<  ROLL : PITCH : YAW															*/

	ui8		reserved2 [10];

}			sbgcAutoPID_State_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t autoPID_StateReferenceInfoArray [];
	extern const ui8 autoPID_StateReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									Motors Structure
 */
/**	@addtogroup	Motors_State
 *	@{
 */
/**	@brief	Structure type for work with
 *			motors synchronization parameters
 *
 *	@ref	SBGC32_SynchronizeMotors function
 */
typedef struct
{
	ui8		axis;									/*!<  See @ref sbgcSyncMotorsAxis_t enumeration										*/
	ui8		power;									/*!<  0 --> 255. Amount of power to apply to motor's winding in synchronous mode	*/
	ui16	timeMs;									/*!<  0 --> 65535. Power is applied for the given time, then motors are turned OFF	*/
	ui16	angle;									/*!<  Angle to rotate. 0 to hold the current position								*/

}			sbgcSyncMotors_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t syncMotorsReferenceInfoArray [];
	extern const ui8 syncMotorsReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								   Scripts Structure
 */
/**	@addtogroup	Scripts
 *	@{
 */
/**	@brief	Structure type for work with
 *			ScriptDebugInfo parameters
 *
 *	@ref	SBGC32_ReadScriptDebugInfo function
 */
typedef struct
{
	ui16	curComCounter;							/*!<  Current command counter														*/
	ui8		errorCode;								/*!<  See @ref sbgcErrorCode_t enumeration											*/

}			sbgcScriptDebugInfo_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t scriptDebugInfoReferenceInfoArray [];
	extern const ui8 scriptDebugInfoReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								State Vars Structure
 */
/**	@addtogroup	State_Vars
 *	@{
 */
/**	@brief	Structure type for work with
 *			StateVars parameters
 *
 *	@ref	SBGC32_WriteStateVars function\n
 *	@ref	SBGC32_ReadStateVars function
 */
typedef struct PACKED__
{
	ui8		stepSignalVars [6];						/*!<  Step signal current value														*/
	ui8		subError;								/*!<  Last code of EMERGENCY_STOP error												*/
	ui8		maxAcc;									/*!<  Units: 1/16 G																	*/
	ui32	workTime;								/*!<  Units: seconds																*/
	ui16	startupCnt;
	ui16	maxCurrent;								/*!<  Units: mA																		*/

	ui8		IMU_TempMin,							/*!<  Units: °C																		*/
			IMU_TempMax,							/*!<  Units: °C																		*/
			MCU_TempMin,							/*!<  Units: °C																		*/
			MCU_TempMax;							/*!<  Units: °C																		*/

	ui8		shockCnt [4];
	ui32	energyTime;								/*!<  Units: seconds																*/
	float	energy;									/*!<  Units: Watt*hour																*/
	ui32	avgCurrentTime;							/*!<  Units: seconds																*/
	float	avgCurrent;								/*!<  Units: A																		*/
	ui8		reserved [152];

}			sbgcStateVars_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t stateVarsReferenceInfoArray [];
	extern const ui8 stateVarsReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								Debug Port Structure
 */
/**	@addtogroup	Debug_Port
 *	@{
 */
/**	@brief	Structure type for work with
 *			debug port data parameters
 *
 *	@ref	SBGC32_ReadDebugPort function
 */
typedef struct PACKED__
{
	ui16	timeMs;									/*!<  Units: milliseconds. Time since system start									*/
	ui8		portAndDir;								/*!<  Bits0..6: port index, bit7: direction											*/
	ui8		cmdID;									/*!<  Command ID. See @ref serialAPI_CommandID_t enumeration						*/
	ui8		*payload;								/*!<  Payload, variable length. Initialized manually by user. It's
														  recommended to allocate @ref SBGC_MAX_PAYLOAD_SIZE (255) bytes
														  of space for this buffer														*/

}			sbgcDebugPortData_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *					 Transparent SerialAPI Structure
 */
/**	@addtogroup	Transparent_SerialAPI
 *	@{
 */
/**	@brief	Structure type for work with
 *			transparent serial commands
 *
 *	@ref	SBGC32_SendTransparentCommand function\n
 *	@ref	SBGC32_ReadTransparentCommand function
 */
typedef struct
{
	ui8		target;									/*!<  Target device parameters. See @ref sbgcTransparentCommandPort_t,
														  @ref sbgcTransparentCommandDevice_t, @ref sbgcTransparentCommandFlag_t
														  enumerations and @ref ParserSBGC32_PackTC_Target function						*/
	ui8		payloadSize;							/*!<  Size of user payload															*/
	ui8		*payload;								/*!<  Pointer to the data for sending or the location for storing the command
														  data. Initialized manually by user. It's recommended to allocate
														  @ref SBGC_MAX_PAYLOAD_SIZE (255) bytes of space for this buffer				*/

}			sbgcTransparentCommand_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							Service Other Structures
 */
/**	@addtogroup	Service_Other
 *	@{
 */
/**	@brief	Structure type for work with
 *			beeper setting parameters
 *
 *	@ref	SBGC32_PlayBeeper function
 */
typedef struct PACKED__
{
	ui16	mode;									/*!<  See @ref sbgcBeeperMode_t enumeration											*/

	ui8		noteLength,								/*!<  Units: 8ms samples. The duration of each note in custom melody mode			*/
			decayFactor,							/*!<  Set the envelope "attack-decay" after each pause, that makes sound
														  more natural. The bigger value, the longer decay. 0 - no decay				*/
			reserved [8];

	ui16	*notesFreqHz;							/*!<  Units: Hz. Initializes manually by user										*/
	ui8		notesQuan;								/*!<  Number of notes in one message. The parameter is only used in the function	*/

}			sbgcBeeperSettings_t;


/**	@brief	Structure type for work with
 *			CAN device parameters
 *
 *	@ref	SBGC32_CAN_DeviceScan function
 */
typedef struct PACKED__
{
	ui8		UID [12];								/*!<  Unique identifier of the device												*/

	ui8		ID;										/*!<  Assigned ID to this device, 0 if not assigned.
														  See @ref sbgcCAN_DeviceID_t enumeration										*/

	ui8		type;									/*!<  See @ref sbgcCAN_DeviceType_t enumeration										*/

}			sbgcCAN_DeviceScan_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t CAN_DeviceScanReferenceInfoArray [];
	extern const ui8 CAN_DeviceScanReferenceInfoArrayElCnt;
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
/**	@addtogroup	Board_Info
 *	@{
 */
sbgcCommandStatus_t SBGC32_ReadBoardInfo (sbgcGeneral_t *gSBGC, sbgcBoardInfo_t *boardInfo, ui16 cfg SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ReadBoardInfo3 (sbgcGeneral_t *gSBGC, sbgcBoardInfo3_t *boardInfo3 SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Auto_PID
 *	@{
 */
sbgcCommandStatus_t SBGC32_TuneAutoPID (sbgcGeneral_t *gSBGC, const sbgcAutoPID_t *autoPID, sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_BreakAutoPID_Tuning (sbgcGeneral_t *gSBGC, sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_TuneAutoPID2 (sbgcGeneral_t *gSBGC, const sbgcAutoPID2_t *autoPID2, sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ReadAutoPID_StateCmd  (sbgcGeneral_t *gSBGC, sbgcAutoPID_State_t *autoPID_State SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Motors_State
 *	@{
 */
sbgcCommandStatus_t SBGC32_SetMotorsON (sbgcGeneral_t *gSBGC, sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_SetMotorsOFF (sbgcGeneral_t *gSBGC, sbgcMotorsMode_t mode, sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_SynchronizeMotors (sbgcGeneral_t *gSBGC, sbgcSyncMotors_t *syncMotors, sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_RequestMotorState (sbgcGeneral_t *gSBGC, sbgcExtMotorID_t motorID, void *extMotorsState, ui16 size
											  SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ReadMotorState (sbgcGeneral_t *gSBGC, void *data, ui16 size SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Boot_Mode
 *	@{
 */
sbgcCommandStatus_t SBGC32_SetBootMode (sbgcGeneral_t *gSBGC SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_SetBootModeExt (sbgcGeneral_t *gSBGC, sbgcBoolean_t needConfirm, ui16 delayMs SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Scripts
 *	@{
 */
sbgcCommandStatus_t SBGC32_RunScript (sbgcGeneral_t *gSBGC, sbgcScriptMode_t mode, sbgcScriptSlotNum_t slot SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ReadScriptDebugInfo (sbgcGeneral_t *gSBGC, sbgcScriptDebugInfo_t *scriptDebugInfo SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	State_Vars
 *	@{
 */
sbgcCommandStatus_t SBGC32_WriteStateVars (sbgcGeneral_t *gSBGC, const sbgcStateVars_t *stateVars, sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ReadStateVars (sbgcGeneral_t *gSBGC, sbgcStateVars_t *stateVars SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Debug_Port
 *	@{
 */
sbgcCommandStatus_t SBGC32_SetDebugPort (sbgcGeneral_t *gSBGC, sbgcDebugPortData_t *debugPortSettings, sbgcDebugPortAction_t action,
										 ui32 filter, sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ReadDebugPort (sbgcGeneral_t *gSBGC, sbgcDebugPortData_t *debugPortSettings SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Transparent_SerialAPI
 *	@{
 */
sbgcCommandStatus_t SBGC32_SendTransparentCommand (sbgcGeneral_t *gSBGC, const sbgcTransparentCommand_t *cmd SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ReadTransparentCommand (sbgcGeneral_t *gSBGC, sbgcTransparentCommand_t *cmd SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Service_Other
 *	@{
 */
sbgcCommandStatus_t SBGC32_Reset (sbgcGeneral_t *gSBGC, ui8 flag, ui16 delayMs SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_SetTriggerPin (sbgcGeneral_t *gSBGC, sbgcTriggerPinID_t pinID, sbgcPinState_t state, sbgcConfirm_t *confirm
										  SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ExecuteMenu (sbgcGeneral_t *gSBGC, sbgcMenuCommand_t menuCommandID, sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_SetServoOut (sbgcGeneral_t *gSBGC, const i16 *servoTime SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_PlayBeeper (sbgcGeneral_t *gSBGC, const sbgcBeeperSettings_t *beeperSettings SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_SignMessage (sbgcGeneral_t *gSBGC, ui8 signType, const char *txMessage, char *rxMessage SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_CAN_DeviceScan (sbgcGeneral_t *gSBGC, sbgcCAN_DeviceScan_t *CAN_DeviceScan SBGC_ADVANCED_PARAMS__);
/**	@endcond
 */

#endif		/* SBGC_SERVICE_MODULE */


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

#endif		/* MODULES_SERVICE_H_ */
