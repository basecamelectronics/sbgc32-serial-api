/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2
 *
 *	@file		highLayer.h
 *
 *	@brief		Header file of the core high-layer communication
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
 *	@defgroup	High_Layer High Layer
 *	@ingroup	Core
 *		@brief	High Layer Functions Module
 *
 *				Covered Commands:
 *
 *				### CMD_CONFIRM
 *				### CMD_ERROR
 *	____________________________________________________________________
 */

#ifndef		CORE_HIGH_LAYER_H_
#define		CORE_HIGH_LAYER_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../sbgc32.h"


/**	@addtogroup	High_Layer
 *	@{
 */
/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								Macros and Constants
 */
/* System Defined Parameters -----------------------
 */
#define		SBGC_X					0
#define		SBGC_Y					1
#define		SBGC_Z					2

#define		SBGC_QW					0
#define		SBGC_QX					1
#define		SBGC_QY					2
#define		SBGC_QZ					3

#define		SBGC_RC_ROLL			0
#define		SBGC_RC_PITCH			1U
#define		SBGC_RC_YAW				2U
#define		SBGC_CMD				3U
#define		SBGC_FC_ROLL			4U
#define		SBGC_FC_PITCH			5U

#define		SBGC_RC_INPUT_NO		0
#define		SBGC_RC_INPUT_ROLL		1U
#define		SBGC_RC_INPUT_PITCH		2U
#define		SBGC_RC_INPUT_YAW		3U
#define		SBGC_RC_INPUT_FC_ROLL	4U
#define		SBGC_RC_INPUT_FC_PITCH	5U

#define		SBGC_RC_MIN_VAL			(-500)
#define		SBGC_RC_MAX_VAL			500

#define		SBGC_RC_MIN_VAL_HR		(-16384)
#define		SBGC_RC_MAX_VAL_HR		16384

#define		SBGC_RC_UNDEF			(-10000)
#define		SBGC_RC_UNDEF_HR		(-32768)

#define		SBGC_RC_CHANNELS_NUM	5U				// RC_ROLL : RC_PITCH : FC_ROLL : FC_PITCH : RC_YAW

#define		SBGC_RC_ADC_CHANNELS_NUM		3U
#define		SBGC_RC_AUX_CHANNELS_NUM		3U
#define		SBGC_VIRTUAL_CHANNELS_NUM		32U

#define		SBGC_ALL_RC_CHANNELS_NUM		(SBGC_RC_CHANNELS_NUM + SBGC_RC_ADC_CHANNELS_NUM +\
											SBGC_RC_AUX_CHANNELS_NUM + SBGC_VIRTUAL_CHANNELS_NUM)

#define		SBGC_EXTRA_MOTORS_NUM	7

/* Other Constants ---------------------------------
 */
/** A placeholder for signaling the function not to
	wait for a confirmation command as a response.
	It is also used in examples for functions for
	brevity. Replace it with an object of
	sbgcConfirm_t type if you want to receive
	confirmation command data from this function */
#define		SBGC_NO_CONFIRM			NULL

/** A value that notifies the SBGC32_ command not
	to assign a token for it */
#define		SBGC_NO_TOKEN			NULL

/** A value to finish writing the payload of the
	raw SerialAPI command */
#define		SBGC_RAW_CMD_END_SYMB	0xFFFFFFFFU

/** The maximum payload byte number for one
	SerialAPI command */
#define		SBGC_MAX_PAYLOAD_SIZE	255

/* Conversion Macros and Constants -----------------
 */
/** Maximum rotation speed for SBGC32 is 2000
 	degrees per second. This speed is limited
 	by the operational characteristics of the
 	gyroscope. All other limitations pertain
 	exclusively to the hardware components
 	of the gimbal system, particularly the
 	motor specifications */
#define		SBGC_MAX_SPEED			2000

/** SBGC32 gets the value of the encoders
	in 14-bit resolution. This is a number
	of values per encoder revolution */
#define		SBGC_ANGLE_FULL_TURN	16384

/** Number of values per encoder revolution
	in high resolution */
#define		SBGC_ANGLE_FULL_TURN_HR	1048576

/** SBGC32 speed scale value */
#define		SBGC_SPEED_SCALE		(1.0F / 0.1220740379F)

/** SBGC32 speed scale value in
	high resolution */
#define		SBGC_SPEED_SCALE_HI_RES	(1.0F / 0.001F)

/** SBGC32 angle scale value */
#define		SBGC_ANGLE_SCALE		((float)SBGC_ANGLE_FULL_TURN / 360.0F)

/** SBGC32 angle scale value in
	high resolution */
#define		SBGC_ANGLE_SCALE_HI_RES	((float)SBGC_ANGLE_FULL_TURN_HR / 360.0F)

/** SBGC32 quaternion scale
	factor value */
#define		SBGC_QUAT_SCALE_FACTOR	741453.78597590288385109097614973F


/** @brief	Converts speed value to system speed
 *			(0.1220740379 degree/sec)
 *
 *	@note	Useful for TX commands with the next fields:\n
 *			sbgcAxisC_t.speed \n
 *			sbgcAxisCE_t.speed
 *
 *	@param	s - speed in degrees per second. Should not
 *			exceed the @ref SBGC_MAX_SPEED (2000) value
 *
 *	@return	System speed value
 */
#define		sbgcSpeedToValue(s)		((s) * SBGC_SPEED_SCALE)

/** @brief	Converts system speed value
 *			(0.1220740379 degree/sec) to
 *			degrees per seconds
 *
 *	@note	Useful for RX commands with the next fields:\n
 *			sbgcAxisGA_t.targetSpeed
 *
 *	@param	v - system speed
 *
 *	@return	Speed in degrees per seconds
 */
#define		sbgcValueToSpeed(v)		(v ? ((v) / SBGC_SPEED_SCALE) : 0)

/** @brief	Converts speed value to system speed in
 *			high resolution (0.001 degree/sec)
 *
 *	@note	Useful for TX commands with the next fields:\n
 *			sbgcAxisC_t.speed \n
 *			sbgcAxisCE_t.speed
 *
 *	@param	s - speed in degrees per second
 *
 *	@return	System speed value
 */
#define		sbgcSpeedToValueHR(s)	((s) * SBGC_SPEED_SCALE_HI_RES)


/** @brief	Converts angle value to system degree
 *			value (0.02197265625 degree)
 *
 *	@note	Useful for TX commands with the next fields:\n
 *			sbgcCalibEncodersOffset_t.calibAngle \n
 *			sbgcAxisC_t.speed \n
 *			sbgcAxisCE_t.speed \n
 *			sbgcHelperData_t.frameAngleRoll \n
 *			sbgcHelperData_t.frameAnglePitch \n
 *			sbgcHelperDataExt_t.frameAngleRoll \n
 *			sbgcHelperDataExt_t.frameAnglePitch \n
 *			sbgcHelperDataExt_t.frameHeading \n
 *			sbgcMainParamsExt_t.encoderOffset \n
 *			sbgcMainParamsExt_t.encoderFldOffset \n
 *			sbgcMainParamsExt3_t.followOffsetExt
 *
 *	@param	a - angle value
 *
 *	@return	System degree value
 */
#define		sbgcAngleToDegree(a)	((a) * SBGC_ANGLE_SCALE)

/** @brief	Converts system degree value
 *			(0.02197265625 degree) to angle
 *
 *	@note	Useful for RX commands with the next fields:\n
 *			sbgcMainParamsExt_t.encoderOffset \n
 *			sbgcMainParamsExt_t.encoderFldOffset \n
 *			sbgcMainParamsExt3_t.followOffsetExt \n
 *			sbgcRealTimeDataCustomReference_t.IMU_Angles \n
 *			sbgcRealTimeDataCustomReference_t.targetAngles \n
 *			sbgcRealTimeDataCustomReference_t.frameCamAngle \n
 *			sbgcRealTimeData_t.targetAngle \n
 *			sbgcRealTimeData_t.frameCamAngle \n
 *			sbgcAxisGA_t.targetAngle \n
 *			sbgcAxisGAE_t.frameCamAngle
 *
 *	@param	d - system degree value
 *
 *	@return	Angle value
 */
#define		sbgcDegreeToAngle(d)	((d) ? ((d) / SBGC_ANGLE_SCALE) : 0)


/** @brief	Converts radians to degree
 *
 *	@param	r - radians value
 *
 *	@return	Degrees value
 */
#define		sbgcRadiansToDegree(r)	((r) ? (((r) * 180.0) / M_PI) : 0)

/** @brief	Converts degree to radians
 *
 *	@param	d - degrees value
 *
 *	@return	Radians value
 */
#define		sbgcDegreeToRadians(d)	((d) ? (((d) * M_PI) / 180.0) : 0)


/** @brief	Compresses quaternion
 *
 *	@param	v - absolute value
 *
 *	@return	Compressed quaternion value
 */
#define		sbgcCompressQuat(v)		((v) * SBGC_QUAT_SCALE_FACTOR)

/** @brief	Restores original value
 *
 *	@param	q - quaternion value
 *
 *	@return	Original value
 */
#define		sbgcRestoreQuat(q)		((q) * (1 / SBGC_QUAT_SCALE_FACTOR))

/** @brief	Restores the 4th component
 *
 *	@param	a - 1st quaternion component
 *	@param	b - 2nd quaternion component
 *	@param	c - 3rd quaternion component
 *
 *	@return	Restored 4th component
 */
#define		sbgcRestoreQuatLargest(a, b, c)	(sqrt(1 - (((a) * (a)) + ((b) * (b)) + ((c) * (c)))))

/* Other Macros ------------------------------------
 */
#if (SBGC_NON_BLOCKING_MODE)

	/** @brief	Blocks further execution of the code until
	 *			the serial command queue is empty
	 *
	 *	@pre	The serial command(-s) must be registered first
	 *
	 *	@note	Should be used with:\n
	 *			@ref SBGC32_TransmitAllCommands \n
	 *			@ref SBGC32_ReceiveAllCommands \n
	 *			@ref SBGC32_ProcessAllCommands
	 *
	 *	@code

	 			// ...
	 	 	 	// Previously registered serial commands

				sbgcBlockQueue(SBGC32_ProcessAllCommands(&SBGC32_Device))
				{
					// User code
				}

	 *	@endcode
	 *
	 *	@param	s - @ref SBGC32_TransmitAllCommands,
	 *			@ref SBGC32_ReceiveAllCommands or
	 *			@ref SBGC32_ProcessAllCommands
	 */
	#define	sbgcBlockQueue(s)		while ((s) != sbgcCOMMAND_QUEUE_IS_EMPTY)

#endif

#if (SBGC_USES_TOKENS || SBGC_USES_DOXYGEN)

	/** @brief	Blocks further execution of the code
	 *			until the serial command completes
	 *
	 *	@pre	The serial command(-s) must be registered first
	 *
	 *	@note	Should be used with:\n
	 *			@ref SBGC32_Transmit \n
	 *			@ref SBGC32_Receive
	 *
	 *	@code

				// ...
	 	 	 	// Previously registered serial commands

				sbgcBlockCommand(SBGC32_Transmit(&SBGC32_Device, txCmdToken))
				{
					// User Tx waiting code

					// *Keep in mind that Tx serial commands do not wait for the complete transmission.
					// They just copy the payload data to the driver buffer and return OK if there is enough space for writing.
					// This waiting loop is necessary to either wait for space to become available
					// in the buffer or to remove a serial command if it times out.
				}

				sbgcBlockCommand(SBGC32_Receive(&SBGC32_Device, rxCmdToken))
				{
					// User Rx waiting code

					// *The loop will wait until the expected serial command is either successfully received
					// or removed due to its timeout.
				}

	 *	@endcode
	 *
	 *	@param	s - @ref SBGC32_Transmit or @ref SBGC32_Receive
	 */
	#define	sbgcBlockCommand(s)		while ((s) == sbgcCOMMAND_PROCESSING)

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								 Common System Flags
 */
/**	@note	serialAPI_General_t.boardFeatures
 *			sbgcBoardInfo_t.boardFeatures
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


/**	@note	serialAPI_General_t.boardFeatures2
 *			sbgcBoardInfo3_t.boardFeaturesExt2
 */
typedef enum
{
	BFE2_PLUS_VER					= BIT_0_SET,
	BFE2_SHAKE_GENERATOR			= BIT_1_SET,
	BFE2_EXT_MOTORS					= BIT_2_SET,
	BFE2_QUAT_CONTROL				= BIT_3_SET,
	BFE2_ADC4						= BIT_4_SET

}	sbgcBoardFeatureExt2_t;


/**	@brief	Special codes for menu commands
 *
 *	@note	@ref SBGC32_ExecuteMenu, 2 arg\n
 *			sbgcMainParams3_t.RC_Cmd_Low \n
 *			sbgcMainParams3_t.RC_Cmd_Mid \n
 *			sbgcMainParams3_t.RC_Cmd_High \n
 *			sbgcMainParams3_t.MenuBtnCmd1 \n
 *			sbgcMainParams3_t.MenuBtnCmd2 \n
 *			sbgcMainParams3_t.MenuBtnCmd3 \n
 *			sbgcMainParams3_t.MenuBtnCmd4 \n
 *			sbgcMainParams3_t.MenuBtnCmd5 \n
 *			sbgcMainParams3_t.MenuBtnCmdLong \n
 *			sbgcMainParamsExt2_t.startupAction \n
 *			sbgcTriggerSlot_t.triggerAction \n
 *			sbgcAdjVarsState_t.triggerAction__old
 */
typedef enum
{
	MENU_CMD_NO						= 0,
	MENU_CMD_PROFILE1				= 1,
	MENU_CMD_PROFILE2				= 2,
	MENU_CMD_PROFILE3				= 3,
	MENU_CMD_SWAP_PITCH_ROLL		= 4,
	MENU_CMD_SWAP_YAW_ROLL			= 5,
	MENU_CMD_CALIB_ACC				= 6,
	MENU_CMD_RESET					= 7,
	MENU_CMD_SET_ANGLE				= 8,
	MENU_CMD_CALIB_GYRO				= 9,
	MENU_CMD_MOTOR_TOGGLE			= 10,
	MENU_CMD_MOTOR_ON				= 11,
	MENU_CMD_MOTOR_OFF				= 12,
	MENU_CMD_FRAME_UPSIDE_DOWN		= 13,
	MENU_CMD_PROFILE4				= 14,
	MENU_CMD_PROFILE5				= 15,
	MENU_CMD_AUTO_PID				= 16,
	MENU_CMD_LOOK_DOWN				= 17,
	MENU_CMD_HOME_POSITION			= 18,
	MENU_CMD_RC_BIND				= 19,
	MENU_CMD_CALIB_GYRO_TEMP		= 20,
	MENU_CMD_CALIB_ACC_TEMP			= 21,
	MENU_CMD_BUTTON_PRESS			= 22,
	MENU_CMD_RUN_SCRIPT1			= 23,
	MENU_CMD_RUN_SCRIPT2			= 24,
	MENU_CMD_RUN_SCRIPT3			= 25,
	MENU_CMD_RUN_SCRIPT4			= 26,
	MENU_CMD_RUN_SCRIPT5			= 27,
	MENU_CMD_CALIB_MAG				= 33,
	MENU_CMD_LEVEL_ROLL_PITCH		= 34,
	MENU_CMD_CENTER_YAW				= 35,
	MENU_CMD_UNTWIST_CABLES			= 36,
	MENU_CMD_SET_ANGLE_NO_SAVE		= 37,
	MENU_CMD_HOME_POSITION_SHORTEST	= 38,
	MENU_CMD_CENTER_YAW_SHORTEST	= 39,
	MENU_CMD_ROTATE_YAW_180			= 40,
	MENU_CMD_ROTATE_YAW_180_FRAME_REL
									= 41,
	MENU_CMD_SWITCH_YAW_180_FRAME_REL
									= 42,
	MENU_CMD_SWITCH_POS_ROLL_90		= 43,
	MENU_CMD_START_TIMELAPSE		= 44,
	MENU_CMD_CALIB_MOMENTUM			= 45,
	MENU_CMD_LEVEL_ROLL				= 46,
	MENU_CMD_REPEAT_TIMELAPSE		= 47,
	MENU_CMD_LOAD_PROFILE_SET1		= 48,
	MENU_CMD_LOAD_PROFILE_SET2		= 49,
	MENU_CMD_LOAD_PROFILE_SET3		= 50,
	MENU_CMD_LOAD_PROFILE_SET4		= 51,
	MENU_CMD_LOAD_PROFILE_SET5		= 52,
	MENU_CMD_LOAD_PROFILE_SET_BACKUP
									= 53,
	MENU_CMD_INVERT_RC_ROLL			= 54,
	MENU_CMD_INVERT_RC_PITCH		= 55,
	MENU_CMD_INVERT_RC_YAW			= 56,
	MENU_CMD_SNAP_TO_FIXED_POSITION	= 57,
	MENU_CMD_CAMERA_REC_PHOTO_EVENT	= 58,
	MENU_CMD_CAMERA_PHOTO_EVENT		= 59,
	MENU_CMD_MOTORS_SAFE_STOP		= 60,
	MENU_CMD_CALIB_ACC_AUTO			= 61,
	MENU_CMD_RESET_IMU				= 62,
	MENU_CMD_FORCED_FOLLOW_TOGGLE	= 63,
	MENU_CMD_AUTO_PID_GAIN_ONLY		= 64,
	MENU_CMD_LEVEL_PITCH			= 65,
	MENU_CMD_MOTORS_SAFE_TOGGLE		= 66,
	MENU_CMD_TIMELAPSE_STEP1		= 67,
	MENU_CMD_EXT_GYRO_ONLINE_CALIB	= 68,
	MENU_CMD_DISABLE_FOLLOW_TOGGLE	= 69,
	MENU_CMD_SET_CUR_POS_AS_HOME	= 70,
	MENU_CMD_STOP_SCRIPT			= 71,
	MENU_CMD_TRIPOD_MODE_OFF		= 72,
	MENU_CMD_TRIPOD_MODE_ON			= 73,
	MENU_CMD_SET_RC_TRIM			= 74,
	MENU_CMD_HOME_POSITION_MOTORS	= 75,
	MENU_CMD_RETRACTED_POSITION		= 76,
	MENU_CMD_SHAKE_GENERATOR_OFF	= 77,
	MENU_CMD_SHAKE_GENERATOR_ON		= 78,
	MENU_CMD_SERVO_MODE_ON			= 79,
	MENU_CMD_SERVO_MODE_OFF			= 80,
	MENU_CMD_SERVO_MODE_TOGGLE		= 81,

	/* only for sbgcMainParamsExt2_t.startupAction */
	sbgcMENU_BUTTON_IS_PRESSED		= BIT_7_SET

}	sbgcMenuCommand_t;


/**	@brief	Details of any error that occurs instead
 *			of the CMD_CONFIRM command or due to
 *			another reasons
 *
 *	@note	sbgcConfirmParams_t.errorCode \n
 *			sbgcScriptDebugInfo_t.errorCode
 */
typedef enum
{
	sbgcERR_NO						= 0,

	sbgcERR_CMD_SIZE				= 1,
	sbgcERR_WRONG_PARAMS			= 2,
	sbgcERR_CRYPTO					= 4,
	sbgcERR_UNKNOWN_COMMAND			= 6,
	sbgcERR_WRONG_STATE				= 8,
	sbgcERR_NOT_SUPPORTED			= 9,
	sbgcERR_OPERATION_FAILED		= 10,
	sbgcERR_TEMPORARY				= 11

	/*	Codes related to file operations:

		sbgcERR_EEPROM_FAULT		= 1,
		sbgcERR_FILE_NOT_FOUND		= 2,
		sbgcERR_FAT					= 3,
		sbgcERR_NO_FREE_SPACE		= 4,
		sbgcERR_FAT_IS_FULL			= 5,
		sbgcERR_FILE_SIZE			= 6,
		sbgcERR_CRC					= 7,
		sbgcERR_LIMIT_REACHED		= 8,
		sbgcERR_FILE_CORRUPTED		= 9,
		sbgcERR_WRONG_PARAMS		= 10

	*/

}	sbgcErrorCode_t;


/**	@brief	Type of IMU sensor
 *
 *	@note	@ref SBGC32_SelectIMU_3, 2 arg\n
 *			sbgcMainParams3_t.curIMU \n
 *			sbgcRealTimeData_t.curIMU \n
 *			sbgcIMU_ExtCalib_t.IMU_IDx \n
 *			sbgcCalibInfo_t.IMU_Type \n
 *			@ref ParserSBGC32_AHRSH_IMU_TypeToStream, 2 arg\n
 *			Available value for the sbgcDataStreamInterval_t.config
 */
typedef enum
{
	sbgcIMU_TYPE_CURRENTLY_ACTIVE	= 0,			// Only for CMD_SELECT_IMU_3 in extended format. See SBGC32_SelectIMU_3 function

	sbgcIMU_TYPE_MAIN				= 1,
	sbgcIMU_TYPE_FRAME				= 2

}	sbgcIMU_Type_t;


/**	@note	sbgcControlQuat_t.mode
 *			sbgcControlQuatStatusReference_t.mode
 */
typedef enum
{
	CtrlQ_MODE_DISABLED				= 0,			/*!<  Stops this type of control and return to a regular operation mode				*/
	CtrlQ_MODE_SPEED				= 1,			/*!<  Gimbal rotates with the TARGET_SPEED. The TARGET_ATTITUDE is ignored and
														  should be omitted. No motion profile is applied in this mode, excepting
														  the low-pass filtering, if enabled in CMD_CONTROL_QUAT_CONFIG					*/
	CtrlQ_MODE_ATTITUDE				= 2,			/*!<  Gimbal moves to the TARGET_ATTITUDE with the configured speed profile.
														  TARGET_SPEED is ignored and should be omitted									*/
	CtrlQ_MODE_SPEED_ATTITUDE		= 5,			/*!<  Gimbal rotates with the TARGET_SPEED and if the actual position differs from
														  the provided TARGET_ATTITUDE, it’s corrected in order to match				*/
	CtrlQ_MODE_SPEED_LIMITED		= 9				/*!<  The same as MODE_SPEED but the motion profile (acceleration limit) is applied	*/

}	sbgcControlQuatMode_t;


/**	@note	sbgcControlQuat_t.flags
 *			sbgcControlQuatStatusReference_t.flags
 */
typedef enum
{
	CtrlQ_FLAG_NEED_CONFIRM			= BIT_0_SET,	/*!<  If set, CMD_CONFIRM is sent in response										*/
	CtrlQ_FLAG_ATTITUDE_PACKED		= BIT_1_SET,	/*!<  If set, TARGET_ATTITUDE is packed to 8 bytes. For more see
														  Appendix F: Compressed quaternion format command in the
														  <a href=https://www.basecamelectronics.com/serialapi/>
														  SimpleBGC32 Serial API protocol specification</a>								*/
	CtrlQ_FLAG_ATTITUDE_LIMITED_180	= BIT_2_SET,	/*!<  If set, TARGET_ATTITUDE is considered to be limited by ±180° and a
														  'phase unwrap' filter is applied by comparing the new value to the
														  previous value and choosing the shortest path. See Quaternions section in
														  Appendix D in the <a href=https://www.basecamelectronics.com/serialapi/>
														  SimpleBGC32 Serial API protocol specification</a>	for more details			*/
	CtrlQ_FLAG_AUTO_TASK			= BIT_6_SET		/*!<  Applicable for: CtrlQ_MODE_ATTITUDE. The task is processed with the speed and
														  acceleration configured for automated tasks. When the target attitude is
														  reached with the 1-degree tolerance, confirmation is sent: CMD_CONFIRM
														  (CMD_CONTROL_QUAT, 1), then gimbal switches to a normal operation mode.
														  Use this flag to move gimbal to a certain position as fast as possible,
														  and receive confirmation when the target is reached. If system can't
														  process the planned trajectory for some reasons, motion will be
														  interrupted after 10-second timeout											*/

}	sbgcControlQuatFlag_t;


/**	@note	sbgcMainParams3_t.profileID \n
 *			sbgcMainParams3_t.curProfileID \n
 *			sbgcMainParamsExt_t.profileID \n
 *			sbgcMainParamsExt2_t.profileID \n
 *			sbgcMainParamsExt3_t.profileID \n
 *			sbgcRealTimeData_t.curProfile \n
 *			sbgcAutoPID_t.profileID
 */
typedef enum
{
	sbgcPROFILE_1					= 0,
	sbgcPROFILE_2					= 1,
	sbgcPROFILE_3					= 2,
	sbgcPROFILE_4					= 3,
	sbgcPROFILE_5					= 4,

	/* only for SBGC32_UseDefaults function */
	sbgcERASE_EEPROM				= 253,
	sbgcRESET_CURRENTLY_SELECTED	= 254,

	/* Don't use for sbgcAutoPID_t.profileID */
	sbgcCURRENT_PROFILE				= 255

}	sbgcProfile_t;


/**	@brief	RC-mapping source types
 *
 *	@note	sbgcMainParams3_t.RC_MapROLL \n
 *			sbgcMainParams3_t.RC_MapPITCH \n
 *			sbgcMainParams3_t.RC_MapYAW \n
 *			sbgcMainParams3_t.RC_MapCmd \n
 *			sbgcMainParams3_t.RC_MapFC_ROLL \n
 *			sbgcMainParams3_t.RC_MapFC_PITCH \n
 *			sbgcMainParamsExt2_t.startupActionSrc \n
 *			sbgcStepSignalN_t.stepSignalSrc \n
 *			sbgcRC_CalibN_t.RC_CalibSrc \n
 *			sbgcMainParamsExt3_t.ADC_ReplaceSrc \n
 *			sbgcTriggerSlot_t.triggerSrcCh \n
 *			sbgcAnalogSlot_t.analogSrc \n
 *			sbgcRC_Inputs_t.RC_Src
 */
typedef enum
{
	sbgcRCMap_ANALOG_TYPE			= BIT_5_SET,
	sbgcRCMap_RC_SERIAL_TYPE		= BIT_6_SET,
	sbgcRCMap_API_VIRT_CH_TYPE		= BIT_7_SET,
	sbgcRCMap_STEP_SIGNAL_TYPE		= (BIT_5_SET | BIT_7_SET)

}	sbgcRC_MapSourceType_t;

/**	@brief	RC-mapping sources (directly)
 *
 *	@note	sbgcMainParams3_t.RC_MapRoll \n
 *			sbgcMainParams3_t.RC_MapPitch \n
 *			sbgcMainParams3_t.RC_MapYaw \n
 *			sbgcMainParams3_t.RC_MapCmd \n
 *			sbgcMainParams3_t.RC_MapFC_Roll \n
 *			sbgcMainParams3_t.RC_MapFC_Pitch \n
 *			sbgcMainParamsExt2_t.startupActionSrc \n
 *			sbgcStepSignalN_t.stepSignalSrc \n
 *			sbgcRC_CalibN_t.RC_CalibSrc \n
 *			sbgcMainParamsExt3_t.ADC_ReplaceSrc \n
 *			sbgcTriggerSlot_t.triggerSrcCh \n
 *			sbgcAnalogSlot_t.analogSrc \n
 *			sbgcRC_Inputs_t.RC_Src
 */
typedef enum
{
	sbgcRCMap_NO_SIGNAL				= 0,

	sbgcRCMap_RC_INPUT_ROLL			= 1,
	sbgcRCMap_RC_INPUT_PITCH		= 2,
	sbgcRCMap_EXT_FC_INPUT_ROLL		= 3,
	sbgcRCMap_EXT_FC_INPUT_PITCH	= 4,
	sbgcRCMap_RC_INPUT_YAW			= 5,

	sbgcRCMap_ADC_1					= (sbgcRCMap_ANALOG_TYPE + 1),
	sbgcRCMap_ADC_2					= (sbgcRCMap_ANALOG_TYPE + 2),
	sbgcRCMap_ADC_3					= (sbgcRCMap_ANALOG_TYPE + 3),

	/* ADC_4 is available on some boards */
	sbgcRCMap_ADC_4					= (sbgcRCMap_ANALOG_TYPE + 4),

	sbgcRCMap_SERIAL_VIRT_CH_1		= (sbgcRCMap_RC_SERIAL_TYPE + 1),
	/* ... */
	sbgcRCMap_SERIAL_VIRT_CH_32		= (sbgcRCMap_RC_SERIAL_TYPE + 32),

	sbgcRCMap_API_VIRT_CH_1			= (sbgcRCMap_API_VIRT_CH_TYPE + 1),
	/* ... */
	sbgcRCMap_API_VIRT_CH_32		= (sbgcRCMap_API_VIRT_CH_TYPE + 32),

	sbgcRCMap_STEP_SIGNAL_CH_1		= (sbgcRCMap_STEP_SIGNAL_TYPE + 1),
	/* ... */
	sbgcRCMap_STEP_SIGNAL_CH_6		= (sbgcRCMap_STEP_SIGNAL_TYPE + 6)

}	sbgcRC_MapSource_t;

/**	@brief	Used as a mask to extract the
 *			RC source type
 *
 *	@param	RC_Src - Map channel source
 *
 *	@return	RC map source type
 */
static inline sbgcRC_MapSourceType_t ParserSBGC32_GetRC_SourceType (sbgcRC_MapSource_t RC_Src)
{
	return (sbgcRC_MapSourceType_t)(RC_Src & 0b11100000);
}


/**	@brief	Identifiers of RC trigger pin
 *
 *	@note	sbgcMainParamsExt2_t.extLED_PinID \n
 *			sbgcMainParamsExt2_t.interruptCfg \n
 *			SBGC32_SetTriggerPin, 2 arg
 */
typedef enum
{
	/* Triggers pin only if it isn't used for input */
	sbgcPIN_RC_ROLL					= 1,
	sbgcPIN_RC_PITCH				= 2,
	sbgcPIN_EXT_FC_ROLL				= 3,
	sbgcPIN_EXT_FC_PITCH			= 4,
	sbgcPIN_RC_INPUT_YAW			= 5,
	sbgcPIN_AUX_1					= 16,
	sbgcPIN_AUX_2					= 17,
	sbgcPIN_AUX_3					= 18,
	sbgcPIN_BUZZER					= 32,
	sbgcPIN_SSAT_POWER				= 33

}	sbgcTriggerPinID_t;


/**	@brief	AHRS reference sources
 *
 *	@note	sbgcAHRS_DebugInfo_t.mainIMU_RefSrc \n
 *			sbgcAHRS_DebugInfo_t.frameIMU_RefSrc
 */
typedef enum
{
	sbgcAHRSRS_NO_REF				= 0,
	sbgcAHRSRS_INTERNAL				= 1,
	sbgcAHRSRS_EXTERNAL				= 2,
	sbgcAHRSRS_TRANSLATE			= 3

}	sbgcAHRS_RefSrc_t;

/**	@brief	Additional flags for AHRS reference
 *
 *	@note	sbgcAHRS_DebugInfo_t.mainIMU_RefSrc \n
 *			sbgcAHRS_DebugInfo_t.frameIMU_RefSrc
 */
typedef enum
{
	sbgcFRS_INTERNAL_SENSOR_CONNECTED_USED
									= BIT_6_SET,
	sbgcFRS_PROCESSING_IMU_ENABLED	= BIT_7_SET

}	sbgcFlagsRefSrc_t;

/**@brief	Used as a mask to extract the
 *			attitude reference source value from
 *			AHRS_DebugInfo_t.mainIMU_RefSrc or
 *			AHRS_DebugInfo_t.frameIMU_RefSrc
 *
 *	@param	value (sbgcAHRS_DebugInfo_t.mainIMU_RefSrc or
 *			sbgcAHRS_DebugInfo_t.frameIMU_RefSrc)
 *
 *	@return	Attitude reference source
 */
static inline sbgcAHRS_RefSrc_t ParserSBGC32_GetAttitudeRefSrc (ui8 value)
{
	return (sbgcAHRS_RefSrc_t)(value & 0b00000111);
}

/**@brief	Used as a mask to extract the
 *			header reference source value from
 *			sbgcAHRS_DebugInfo_t.mainIMU_RefSrc or
 *			sbgcAHRS_DebugInfo_t.frameIMU_RefSrc
 *
 *	@param	value (sbgcAHRS_DebugInfo_t.mainIMU_RefSrc or
 *			sbgcAHRS_DebugInfo_t.frameIMU_RefSrc)
 *
 *	@return	Header reference source
 */
static inline sbgcAHRS_RefSrc_t ParserSBGC32_GetHeaderRefSrc (ui8 value)
{
	return (sbgcAHRS_RefSrc_t)((value & 0b00111000) >> 3);
}


/**	@brief	Statuses of external IMU sensors
 *
 *	@note	sbgcAHRS_DebugInfo_t.extIMU_Status
 */
typedef enum
{
	sbgcEIMUS_DISABLED				= 0,
	sbgcEIMUS_NOT_CONNECTED			= 1,
	sbgcEIMUS_UNKNOWN				= 2,
	sbgcEIMUS_ERROR					= 3,
	sbgcEIMUS_BAD					= 4,
	sbgcEIMUS_COARSE				= 5,
	sbgcEIMUS_GOOD					= 6,
	sbgcEIMUS_FINE					= 7

}	sbgcExtIMU_Status_t;

/**	@brief	Additional flags for external IMU status
 *
 *	@note	sbgcAHRS_DebugInfo_t.extIMU_Status
 */
typedef enum
{
	sbgcEIMUSF_BAD_MAG				= BIT_6_SET,
	sbgcEIMUSF_NO_GPS_SIGNAL		= BIT_7_SET

}	sbgcExtIMU_StatusFlag_t;

/**	@brief	Used as a mask to extract the
 *			external IMU status value from
 *			sbgcAHRS_DebugInfo_t.extIMU_Status
 *
 *	@param	value (sbgcAHRS_DebugInfo_t.extIMU_Status)
 *
 *	@return	external IMU status
 */
static inline sbgcExtIMU_Status_t ParserSBGC32_GetExtIMU_Status (ui8 value)
{
	return (sbgcExtIMU_Status_t)(value & 0b00000111);
}


/**	@note	sbgcBoardInfo_t.stateFlags \n
 *			sbgcRealTimeDataCustomReference_t.systemStateFlags \n
 *			sbgcRealTimeData_t.systemStateFlags
 */
typedef enum
{
	SF_DEBUG_MODE					= BIT_0_SET,	// Internal use only
	SF_IS_FRAME_INVERTED			= BIT_1_SET,	// System is re-configured for frame inversion over the middle motor

	/* The following flags are updated
	   at the system initialization */
	SF_INIT_STEP1_DONE				= BIT_2_SET,
	SF_INIT_STEP2_DONE				= BIT_3_SET,
	SF_STARTUP_AUTO_ROUTINE_DONE	= BIT_4_SET,
	SF_POWER_MANAGER_ENABLED		= BIT_5_SET,	// For CAN_MCU board only
	/* For real-time data custom only */
	SF_SHAKE_GENERATOR_ENABLED		= BIT_8_SET,	// Shake Generator is active
	SF_SERVO_MODE_IS_ACTIVE			= BIT_9_SET,	// "Servo mode" is active (gimbal is controlled in motor coordinates)
	SF_FOLLOW_MODE_ROLL_IS_ACTIVE	= BIT_10_SET,
	SF_FOLLOW_MODE_PITCH_IS_ACTIVE	= BIT_11_SET,
	SF_FOLLOW_MODE_YAW_IS_ACTIVE	= BIT_12_SET,
	/* frw. ver. 2.73.9+ */
	SF_TRIPOD_MODE_ENABLED			= BIT_13_SET,	// "Tripod mode" is active
	/* frw. ver. 2.74+ */
	SF_RETRACTED_POSITION			= BIT_14_SET,	// "Retracted position" is active

}	sbgcStateFlag_t;


/**	@note	@ref SBGC32_RequestMotorState, 3 arg\n
 *			@ref ParserSBGC32_EMS_ID_AndSetToStream, 3 arg\n
 *			Available value for the sbgcDataStreamInterval_t.config \n
 */
typedef enum
{
	MSDS_CONTROL_MODE				= BIT_0_SET,
	MSDS_TORQUE						= BIT_1_SET,
	MSDS_TORQUE_SETPOINT			= BIT_2_SET,
	MSDS_SPEED16					= BIT_3_SET,
	MSDS_SPEED16_SETPOINT			= BIT_4_SET,
	MSDS_SPEED32					= BIT_5_SET,
	MSDS_SPEED32_SETPOINT			= BIT_6_SET,
	MSDS_ANGLE16					= BIT_7_SET,
	MSDS_ANGLE16_SETPOINT			= BIT_8_SET,
	MSDS_ANGLE32					= BIT_9_SET,
	MSDS_ANGLE32_SETPOINT			= BIT_10_SET,
	MSDS_STATE_FLAGS				= BIT_11_SET,
	MSDS_MAX_SPEED					= BIT_12_SET,
	MSDS_MAX_ACCELERATION			= BIT_13_SET,
	MSDS_JERK_SLOPE					= BIT_14_SET,
	MSDS_MAX_TORQUE					= BIT_15_SET,
	MSDS_CURRENT					= BIT_16_SET,
	MSDS_BATTERY_VOLTAGE			= BIT_17_SET,
	MSDS_MOTOR_TEMPERATURE			= BIT_18_SET,
	MSDS_DRIVER_TEMPERATURE			= BIT_19_SET

}	sbgcMotorsStateDataSet_t;


/**	@note	sbgcControlExtMotors_t.forMotors
 *			@ref SBGC32_ExtMotorsAction, 2 arg
 *			@ref ParserSBGC32_CAN_DT_FlagsAndID_ToStream, 3 arg
 */
typedef enum
{
	EXT_MOTOR_ID_1					= BIT_0_SET,
	EXT_MOTOR_ID_2					= BIT_1_SET,
	EXT_MOTOR_ID_3					= BIT_2_SET,
	EXT_MOTOR_ID_4					= BIT_3_SET,
	EXT_MOTOR_ID_5					= BIT_4_SET,
	EXT_MOTOR_ID_6					= BIT_5_SET,
	EXT_MOTOR_ID_7					= BIT_6_SET,
	/* Only for SBGC32_ExtMotorsAction function */
	EXT_MOTOR_NEED_CONFIRM			= BIT_7_SET

}	sbgcExtMotorID_t;


/**	@note	sbgcExtMotorsStateReference_t.controlMode
 */
typedef enum
{
	EMS_CONTROL_MODE_POSITION		= 0,
	EMS_CONTROL_MODE_SPEED			= 1,
	EMS_CONTROL_MODE_TORQUE			= 2

}	sbgcExtMotorsStateControlMode_t;


/**	@note	sbgcExtMotorsStateReference_t.stateFlags
 */
typedef enum
{
	EMS_FLAG_OFF_BRAKE				= 0,
	EMS_FLAG_ON						= 1,
	EMS_FLAG_OFF_FLOATING			= 2,
	EMS_FLAG_OFF_STATE_STOP			= 3

}	sbgcExtMotorsStateFlag_t;


/**	@note	sbgcControlConfig_t.EulerOrder
 *			sbgcMainParams3_t.EulerOrder
 *
 *			Important! EO_DONT_CHANGE and
 *			EO_SCREEN_RELATED parameters are
 *			absented for sbgcMainParams3_t.EulerOrder
 *			field. Also, the remaining parameters
 *			should be reduced by 1
 */
typedef enum
{
	/* For sbgcControlConfig_t.EulerOrder only */
	EO_DONT_CHANGE					= 0,

	EO_PITCH_ROLL_YAW				= 0,
	EO_ROLL_PITCH_YAW				= 1,

	/* PITCH and YAW are motor-related axes,
	   ROLL is global Euler axis */
	EO_PITCHm_ROLL_YAWm				= 2,
	EO_ROLL_PITCHm_YAWm				= 3,

	EO_YAW_ROLL_PITCH				= 4,

	/* Next modes are not compatible
	   with orders 2 and 3 */
	EO_CTRL_IN_LOCAL_XYZ			= BIT_4_SET,

	/* Frw.ver. 2.74+ */
	EO_STAB_CTRL_IN_LOCAL_XYZ		= BIT_5_SET

}	sbgcEulerOrder_t;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							Common System Structures
 */
/**	@brief	Attitude and heading reference system
 *			structure type. Information about
 *			the AHRS state
 */
typedef struct PACKED__
{
	ui8		mainIMU_RefSrc,							/*!<  Encodes the source of the reference information for the main/frame IMU...		*/
			frameIMU_RefSrc,						/*!<  ...See @ref sbgcAHRS_RefSrc_t and @ref sbgcFlagsRefSrc_t enumerations			*/

			mainIMU_Z_RefErr,						/*!<  Units: 0.1°. Error between the reference defined by the mainIMU_RefSrc,
														  and the estimated attitude													*/
			mainIMU_H_RefErr,						/*!<  Units: 0.1°. Error between the reference defined by the mainIMU_RefSrc,
														  and the estimated attitude													*/
			frameIMU_Z_RefErr,						/*!<  Units: 0.1°. Error between the reference defined by the frameIMU_RefSrc,
														  and the estimated attitude													*/
			frameIMU_H_RefErr,						/*!<  Units: 0.1°. Error between the reference defined by the frameIMU_RefSrc,
														  and the estimated attitude													*/
			extIMU_Status;							/*!<  See @ref sbgcExtIMU_Status_t and @ref sbgcExtIMU_StatusFlag_t enumerations	*/

	ui16	extIMU_PacketsReceivedCnt,				/*!<  0 --> 65535																	*/
			extIMU_ParseErrCnt;						/*!<  0 --> 65535																	*/

	ui8		extCorrH_Ref,							/*!<  Units: 0.1°. Difference between the externally referenced heading
														  and the current heading														*/
			extCorrZ_Ref;							/*!<  Units: 0.1°. Difference between the externally referenced attitude
														  and the current heading														*/

	ui8		reserved [13];

}	sbgcAHRS_DebugInfo_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t AHRS_DebugInfoReferenceInfoArray [];
	extern const ui8 AHRS_DebugInfoReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif


/**	@brief	Type of structure provides data
 *			for the external controller
 *			of the 4th axis motor
 */
typedef struct PACKED__
{
	i16		FF_Speed;								/*!<  Units: 0.06103701895 degree/sec. Feed-forward control							*/
	i16		angleError;								/*!<  Units: 0.02197265625 degree. Distance to reach the target angle of 4th axis	*/
	float	PID_Out;								/*!<  The output of the internal PID loop running over the ANGLE_ERROR
														  with the FF_SPEED mixed, scaled by the 'scale factor' parameter				*/

}	sbgcMotor4_Control_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t motor4_ControlReferenceInfoArray [];
	extern const ui8 motor4_ControlReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif


/**	@brief	Structure reference for work with
 *			ExtMotorsState parameters
 *
 *	@note	Use this structure type as a reference
 *			for filling a custom external
 *			motors state structure
 *
 *	@ref	SBGC32_RequestMotorState function\n
 *	@ref	SBGC32_ReadMotorState function
 */
typedef struct
{
	/* Sent parameters */
	ui32	dataSet;								/*!<  See @ref sbgcMotorsStateDataSet_t enumeration									*/

	/* The followed data is regulated
	   by the 'dataSet' field */
	ui8		controlMode;							/*!<  See @ref sbgcExtMotorsStateControlMode_t enumeration							*/

	i16		torque,									/*!<  ...																			*/
			torqueSetpoint,							/*!<  ...-32767 --> 32767. For the maximum torque the driver can provide			*/

			speed16,								/*!<  ...																			*/
			speed16_Setpoint;						/*!<  ...Units: 0.1220740379 degree/sec. Use the @ref sbgcValueToSpeed macro
														  to obtain this data conveniently												*/

	i32		speed32,								/*!<  ...																			*/
			speed32_Setpoint;						/*!<  ...Units: µrad/sec.															*/

	i16		angle16,								/*!<  ...																			*/
			angle16_Setpoint;						/*!<  ...Units: 0.02197265625 degree. Use the @ref sbgcDegreeToAngle macro
														  to obtain this data conveniently												*/

	i32		angle32,								/*!<  ...																			*/
			angle32_Setpoint;						/*!<  ...Units: 0.00034332275390625 degree											*/

	ui16	stateFlags;								/*!<  See @ref sbgcExtMotorsStateFlag_t enumeration									*/

	ui16	maxSpeed,
			maxAcceleration,
			jerkSlope,
			maxTorque,
			current,								/*!<  Units: mA																		*/
			batteryVoltage;							/*!<  Units: mV																		*/

	i8		motorTemperature,						/*!<  Units: °C																		*/
			driverTemperature;						/*!<  Units: °C																		*/

}	sbgcExtMotorsStateReference_t;


/**	@brief	Structure reference for work with
 *			quaternions
 *
 *	@note	Compressing to packed format:\n
 *			1. Find the largest component and store
 *			its index (0..3) in the 'largest' field.
 *			If the value is negative, set
 *			the 'largestSign' bit to 1;\n
 *			2. Take an absolute value of other 3
 *			components, multiply them by
 *			@ref SBGC_QUAT_SCALE_FACTOR and store
 *			to a, b, c fields (preserving the
 *			original order). If any value is
 *			negative, set the corresponding sign
 *			bit to 1
 *
 *	@note	Restoring from packed format:\n
 *			1. Restore 3 components a, b, c to
 *			floats using the @ref sbgcRestoreQuat
 *			and taking into account the 'sign' bit;\n
 *			2. Restore the 4th component referenced
 *			by the 'largest' index, using the
 *			@ref sbgcRestoreQuatLargest taking into
 *			account the 'largestSign' bit
 */
typedef struct
{
	ui32	a				: 19;					/*!<  Component 'a'																	*/
	ui16	aSign			: 1;					/*!<  Component 'a' sign (1 - negative)												*/

	ui32	b				: 19;					/*!<  Component 'b'																	*/
	ui16	bSign			: 1;					/*!<  Component 'b' sign (1 - negative)												*/

	ui32	c				: 19;					/*!<  Component 'c'																	*/
	ui16	cSign			: 1;					/*!<  Component 'c' sign (1 - negative)												*/

	ui16	largest			: 2;					/*!<  Index of the largest component in quaternion, 0..3							*/
	ui16	largestSign		: 1;					/*!<  Sign of the largest component (1 - negative)									*/

	ui16	reserved		: 1;					/*!<  Not used, padding to 64-bits													*/

}	sbgcQuatPackedReference_t;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *					  Function Prototypes and Inline
 */
/** @brief	Returns last SBGC32 command status
 *
 *	@param	gSBGC - pointer to serial connection descriptor
 *
 *	@return	sbgcGeneral_t._lastCommandStatus
 */
static inline sbgcCommandStatus_t SerialAPI_GetStatus (sbgcGeneral_t *gSBGC)
{
	return gSBGC->_lastCommandStatus;
}

/** @brief	Returns last SBGC32 serial command
 *			low-layer status
 *
 *	@param	gSBGC - pointer to serial connection descriptor
 *
 *	@return	sbgcGeneral_t._lastSerialCommandStatus
 */
static inline serialAPI_CommandStatus_t SerialAPI_GetSerialStatus (sbgcGeneral_t *gSBGC)
{
	return gSBGC->_lastSerialCommandStatus;
}


#if (SBGC_NEED_CONFIRM_CMD)

	/** @brief	Returns the status of confirmation
	 *
	 *	@param	*confirm - pointer to confirmation structure
	 *
	 *	@return	sbgcConfirm_t.status
	 */
	static inline sbgcConfirmStatus_t SerialAPI_GetConfirmStatus (sbgcConfirm_t *confirm)
	{
		return confirm->status;
	}

#endif

#if (SBGC_USES_OS_SUPPORT)

	/** @brief	Returns a pointer to the @ref SBGC32_HandlerThread
	 *			thread object
	 *
	 *	@param	gSBGC - pointer to serial connection descriptor
	 *
	 *	@return	&serialAPI_General_t.threadHandle
	 */
	static inline sbgcThread_t *SerialAPI_GetHandlerThread (sbgcGeneral_t *gSBGC)
	{
		return &gSBGC->_api->threadHandle;
	}

#endif


/** @brief	Returns the current board version
 *
 *	@param	gSBGC - pointer to serial connection descriptor
 *
 *	@return	serialAPI_General_t.boardVersion
 */
static inline ui8 SerialAPI_GetBoardVersion (sbgcGeneral_t *gSBGC)
{
	return gSBGC->_api->boardVersion;
}

/** @brief	Returns the current firmware version
 *
 *	@param	gSBGC - pointer to serial connection descriptor
 *
 *	@return	serialAPI_General_t.firmwareVersion
 */
static inline ui16 SerialAPI_GetFirmwareVersion (sbgcGeneral_t *gSBGC)
{
	return gSBGC->_api->firmwareVersion;
}


/** @brief	Returns the board features part 1
 *
 *	@param	gSBGC - pointer to serial connection descriptor
 *
 *	@return	serialAPI_General_t.boardFeatures
 */
static inline ui32 SerialAPI_GetBoardFeatures (sbgcGeneral_t *gSBGC)
{
	return gSBGC->_api->boardFeatures;
}

/** @brief	Returns the board features part 2
 *
 *	@param	gSBGC - pointer to serial connection descriptor
 *
 *	@return	serialAPI_General_t.boardFeatures2
 */
static inline ui32 SerialAPI_GetBoardFeatures2 (sbgcGeneral_t *gSBGC)
{
	return gSBGC->_api->boardFeatures2;
}


#if (SBGC_ADJVAR_MODULE)

	/** @brief	Returns the number of available adjustable variables
	 *
	 *	@param	gSBGC - pointer to serial connection descriptor
	 *
	 *	@return	serialAPI_General_t.adjVarsNumber
	 */
	static inline ui8 SerialAPI_GetAdjVarNumber (sbgcGeneral_t *gSBGC)
	{
		return gSBGC->_api->adjVarsNumber;
	}

#endif


/** @brief	Returns the number of command transmission errors
 *
 *	@param	gSBGC - pointer to serial connection descriptor
 *
 *	@return	serialAPI_General_t.txErrorsCount
 */
static inline ui16 SerialAPI_GetTxErrorsNumber (sbgcGeneral_t *gSBGC)
{
	return gSBGC->_api->txErrorsCount;
}

/** @brief	Returns the number of command read errors
 *
 *	@param	gSBGC - pointer to serial connection descriptor
 *
 *	@return	serialAPI_General_t.rxErrorsCount
 */
static inline ui16 SerialAPI_GetRxErrorsNumber (sbgcGeneral_t *gSBGC)
{
	return gSBGC->_api->rxErrorsCount;
}


/** @brief	Returns the number of active commands in the queue
 *
 *	@param	gSBGC - pointer to serial connection descriptor
 *
 *	@return	serialAPI_General_t.commandNumber
 */
static inline ui8 SerialAPI_GetQueueCommandNumber (sbgcGeneral_t *gSBGC)
{
	return gSBGC->_api->commandNumber;
}

/** @brief	Returns the total number of processed commands
 *
 *	@param	gSBGC - pointer to serial connection descriptor
 *
 *	@return	serialAPI_General_t.commandTotalCount
 */
static inline ui8 SerialAPI_GetTotalCommandNumber (sbgcGeneral_t *gSBGC)
{
	return gSBGC->_api->commandTotalCount;
}


/** @brief	Gets the number of available bytes for reading
 *
 *	@note	Appeal to low-layer similar driver function
 *
 *	@param	gSBGC - pointer to serial connection descriptor
 *
 *	@return Number of available bytes for reading
 */
static inline ui16 SerialAPI_GetBytesAvailable (sbgcGeneral_t *gSBGC)
{
	return gSBGC->_ll->drvAvailableBytes(gSBGC->_ll->drv);
}


/** @brief	Indicates whether the Tx command buffer is empty
 *
 *	@param	gSBGC - pointer to serial connection descriptor
 *
 *	@return	True if empty, false otherwise
 */
static inline sbgcBoolean_t SerialAPI_IsTxEmpty (sbgcGeneral_t *gSBGC)
{
	return (gSBGC->_api->txCommandBuffTail == gSBGC->_api->txCommandBuffHead) ? sbgcTRUE : sbgcFALSE;
}

/** @brief	Indicates whether the Rx command buffer is empty
 *
 *	@param	gSBGC - pointer to serial connection descriptor
 *
 *	@return	True if empty, false otherwise
 */
static inline sbgcBoolean_t SerialAPI_IsRxEmpty (sbgcGeneral_t *gSBGC)
{
	return (gSBGC->_api->rxCommandBuffTail == gSBGC->_api->rxCommandBuffHead) ? sbgcTRUE : sbgcFALSE;
}


#if (SBGC_USES_TOKENS)
	sbgcCommandStatus_t SBGC32_Transmit (sbgcGeneral_t *gSBGC, sbgcCommandToken_t *commandToken);
	sbgcCommandStatus_t SBGC32_Receive (sbgcGeneral_t *gSBGC, sbgcCommandToken_t *commandToken);
#endif
#if (SBGC_NON_BLOCKING_MODE && (SBGC_USES_OS_SUPPORT == sbgcOFF))
	sbgcCommandStatus_t SBGC32_TransmitAllCommands (sbgcGeneral_t *gSBGC);
	sbgcCommandStatus_t SBGC32_ReceiveAllCommands (sbgcGeneral_t *gSBGC);
	sbgcCommandStatus_t SBGC32_ProcessAllCommands (sbgcGeneral_t *gSBGC);
#endif
#if (SBGC_USES_OS_SUPPORT && SBGC_AUTO_PING_CALLBACK)
	void SBGC32_AutoPingCallback (void *gSBGC);
#endif
sbgcCommandStatus_t SBGC32_SetupLibrary (sbgcGeneral_t *gSBGC);
void SerialAPI_ResetLibrary (sbgcGeneral_t *gSBGC);
#if (SBGC_NEED_CONFIRM_CMD)
	sbgcCommandStatus_t SBGC32_CheckConfirmation (sbgcGeneral_t *gSBGC, sbgcConfirm_t *confirm, serialAPI_CommandID_t cmdID SBGC_ADVANCED_PARAMS__);
#endif
sbgcCommandStatus_t SBGC32_SendRawCommand (sbgcGeneral_t *gSBGC, ui32 cmdID, ...);
sbgcCommandStatus_t SBGC32_ExpectCommand (sbgcGeneral_t *gSBGC, serialAPI_CommandID_t cmdID, void *pDestination, ui8 size SBGC_ADVANCED_PARAMS__);
sbgcBoolean_t SBGC32_DeleteCommand (sbgcGeneral_t *gSBGC, serialAPI_CommandID_t cmdID);
void SerialAPI_LinkDriver (sbgcGeneral_t *gSBGC, sbgcTx_t tx, sbgcRx_t rx,
						   sbgcAvailableBytes_t availableBytes, sbgcTxDebug_t txDebug,
						   sbgcGetTime_t getTime);
#if (SBGC_USES_CUSTOM_SPRINTF)
	void SerialAPI_LinkSprintf (sbgcGeneral_t *gSBGC);
#endif
void SerialAPI_ResetTxBuffer (sbgcGeneral_t *gSBGC);
void SerialAPI_ResetRxBuffer (sbgcGeneral_t *gSBGC);
#if ((SBGC_USES_LOGS & SBGC_NON_BLOCKING_MODE) || SBGC_USES_DOXYGEN)
	void SerialAPI_LogCommandQueue (sbgcGeneral_t *gSBGC);
#endif
/**	@}
 */

/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

#endif		/* CORE_HIGH_LAYER_H_ */
