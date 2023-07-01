/** ____________________________________________________________________
 *
 * 	SBGC32 Serial API Library v1.0
 *
 * 	@file		realtime.h
 *
 *	@brief 		Realtime header file
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
/** ____________________________________________________________________
 *
 * 	@defgroup	Realtime SBGC32 Realtime
 *	@ingroup	Sources
 *		@brief	SBGC32 Realtime Title Module
 *  ____________________________________________________________________
 *
 *	@defgroup	Data_Stream_Interval Data Stream Interval
 *  @ingroup	Realtime
 *  	@brief	Data Stream Interval Module
 *
 *  			Covered Commands:
 *
 *				### CMD_DATA_STREAM_INTERVAL
 *
 *  @defgroup	Realtime_Data_Custom Realtime Data Custom
 *  @ingroup	Realtime
 *  	@brief	Realtime Data Custom Module
 *
 *  			Covered Commands:
 *
 *				### CMD_REALTIME_DATA_CUSTOM
 *
 *  @defgroup	Realtime_Data_3_4 Realtime Data 3(-4)
 *  @ingroup	Realtime
 *  	@brief	Realtime Data 3(-4) Module
 *
 *  			Covered Commands:
 *
 *				### CMD_REALTIME_DATA_3
 *				### CMD_REALTIME_DATA_4
 *
 *  @defgroup	Get_Angles Get Angles
 *  @ingroup	Realtime
 *  	@brief	Get Angles Module
 *
 *  			Covered Commands:
 *
 *				### CMD_GET_ANGLES
 *				### CMD_GET_ANGLES_EXT
 *
 *	@defgroup	RC_Inputs RC Inputs
 *	@ingroup	Realtime
 *		@brief	RC Inputs Module
 *
 *				Covered Commands:
 *
 *				### CMD_READ_RC_INPUTS
 *
 *	@defgroup	Debug_Var_3 Debug Variables 3
 *	@ingroup	Realtime
 *		@brief	Debug Variables 3 Module
 *
 *				Covered Commands:
 *
 *				### CMD_DEBUG_VARS_INFO_3
 *				### CMD_DEBUG_VARS_3
 *
 *	@defgroup	IMU_Select_3 IMU Select 3
 *	@ingroup	Realtime
 *		@brief	IMU Select 3 Module
 *
 *				Covered Commands:
 *
 *				### CMD_SELECT_IMU_3
 *	____________________________________________________________________
 */

#ifndef     _REALTIME_H_
#define     _REALTIME_H_

#ifdef 		__cplusplus
extern 		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../sbgc32.h"


#if (SBGC_REALTIME_MODULE)

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *										   Constants
 */
/**	@addtogroup	Data_Stream_Interval
 * 	@{
 */
#define		SIZEOF_EVENT			4				/*!<  May be expanded by extra parameters in future versions. sizeof(Event_t)		*/
/**	@}
 */


/**	@addtogroup	Realtime_Data_3_4
 * 	@{
 */
#define		SIZEOF_REALTIME_DATA_3	63				/*!<  or offsetof_(&realTimeData->frameCamAngle[0], &realTimeData)					*/
#define		COUNTOF_REALTIME_DATA_3	27				/*!<  RealtimeData3 command structure part elements number							*/
/**	@}
 */


/**	@addtogroup	Debug_Var_3
 * 	@{
 */
#define		MAX_DEBUG_VARS_QUAN		10				/*!<  1 --> 255																		*/
/**	@}
 */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 					  Data Stream Interval Structure
 */
/**	@addtogroup	Data_Stream_Interval Data Stream Interval
 * 	@{
 */
/**	@note	DataStreamInterval_t.cmdID
 */
typedef enum
{
	DSC_CMD_REALTIME_DATA_3			= 0,
	DSC_CMD_REALTIME_DATA_4			= 1,
	DSC_CMD_REALTIME_DATA_CUSTOM	= 2,
	DSC_CMD_AHRS_HELPER				= 3,
	/* frw.ver. 2.65b7+ */
	DSC_CMD_EVENT					= 4

}	DataStreamCommand_t;


/**	@note	DataStreamInterval_t.syncToData
 */
typedef enum
{
	STD_SYNC_OFF					= 0,
	STD_SYNC_ON						= 1

}	SyncToData_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						  Realtime Data Custom Flags
 */
/**	@addtogroup	Realtime_Data_Custom
 *	@{
 */
/**	@note @ref 	SBGC32_RequestRealTimeDataCustom, 3 arg\n
 * 				Can be combined with each other
 */
typedef enum
{
	RTDCF_IMU_ANGLES				= BIT_0_SET,
	RTDCF_TARGET_ANGLES				= BIT_1_SET,
	RTDCF_TARGET_SPEED				= BIT_2_SET,
	RTDCF_STATOR_ROTOR_ANGLE		= BIT_3_SET,
	RTDCF_GYRO_DATA					= BIT_4_SET,
	RTDCF_RC_DATA					= BIT_5_SET,
	RTDCF_Z_VECTOR_H_VECTOR			= BIT_6_SET,
	RTDCF_RC_CHANNELS				= BIT_7_SET,
	RTDCF_ACC_DATA					= BIT_8_SET,
	RTDCF_MOTOR4_CONTROL			= BIT_9_SET,
	RTDCF_AHRS_DEBUG_INFO			= BIT_10_SET,
	RTDCF_ENCODER_RAW24				= BIT_11_SET,
	RTDCF_IMU_ANGLES_RAD			= BIT_12_SET

}	RealTimeDataCustomFlag_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						  Realtime Data 3 (-4) Flags
 */
/**	@addtogroup	Realtime_Data_3_4
 *	@{
 */
/**	@note	RealTimeData_t.systemError
 */
typedef enum
{
	SE_NO_ERROR						= 0,
	SE_ERR_NO_SENSOR 				= BIT_0_SET,
	SE_ERR_CALIB_ACC 				= BIT_1_SET,
	SE_ERR_SET_POWER				= BIT_2_SET,
	SE_ERR_CALIB_POLES				= BIT_3_SET,
	SE_ERR_PROTECTION 				= BIT_4_SET,
	SE_ERR_SERIAL 					= BIT_5_SET,
	/* Beside that, extended error contains bits: */
	SE_ERR_LOW_BAT1					= BIT_6_SET,
	SE_ERR_LOW_BAT2 				= BIT_7_SET,
	SE_ERR_GUI_VERSION 				= BIT_8_SET,
	SE_ERR_MISS_STEPS 				= BIT_9_SET,
	SE_ERR_SYSTEM 					= BIT_10_SET,
	SE_ERR_EMERGENCY_STOP 			= BIT_11_SET

}	SystemError_t;


/**	@note	RealTimeData_t.systemSubError
 */
typedef enum
{
	/* Specifies the reason of emergency stop: */
	SSE_SUB_ERR_I2C_ERRORS 			= 1, 			// High rate of I2C errors
	SSE_SUB_ERR_DRV_OTW 			= 2, 			// Driver over-temperature protection
	SSE_SUB_ERR_DRV_FAULT 			= 3, 			// Driver fault (under-voltage, over-current, short circuit)
	SSE_SUB_ERR_ENCODER_IMU_ANGLE 	= 4, 			// Encoder/IMU angles mismatch
	SSE_SUB_ERR_CALIBRATION_FAILED	= 5,			// Auto calibration process caused serious fault
	SSE_SUB_ERR_INTERNAL_SYSTEM_ERROR 				// Stack is damaged
									= 6,
	SSE_SUB_ERR_ENCODER_CALIB_BAD_SCALE 			// Estimated scale differs a lot from configured
									= 7,
	SSE_SUB_ERR_OVER_TEMPERATURE 	= 8, 			// MCU or power board over temperature
	SSE_UB_ERR_BAD_MOTOR_POLES_INVERT 				// Motor n.poles or inversion is wrong
									= 9,
	SSE_SUB_ERR_NOT_ENOUGH_MEMORY 	= 10, 			// static_malloc() can't allocate memory
	SSE_SUB_ERR_IMU_SENSOR_NOT_RESPONDING
									= 11, 			// Lost connection to IMU sensor
	SSE_SUB_ERR_CAN_HARD 			= 12, 			// CAN on board hardware error
	SSE_SUB_ERR_MOTOR_OVERHEAT_PROTECTION 			// Overheat protection is triggered
									= 13,
	SSE_SUB_ERR_MOTOR_IS_LOCKED 	= 14, 			// Motor is locked during automated task
	SSE_SUB_ERR_BAD_IMU_HEALTH 		= 15, 			// IMU gyroscope and accelerometer error is too big:
													// sensor sends corrupted data or wrong use conditions
	SSE_SUB_ERR_INFINITE_RESET 		= 16, 			// Infinite reset loop is detected
	SSE_SUB_ERR_WRONG_INITIAL_POSITION				// Wrong position: failed to detect encoder angle,
									= 17, 			// or angle is outside soft limits */
	SSE_SUB_ERR_MOTOR_LOAD_TIME_EXCEEDED
									= 18, 			// Motors are fully loaded too long time
	SSE_SUB_ERR_CAN_DRV_OVERCURRENT	= 19,			// Hardware short-circuit protection
	SSE_SUB_ERR_CAN_DRV_UNDERVOLTAGE				// Hardware or software under-voltage protection
									= 20,
	SSE_SUB_ERR_CAN_DRV_EMERGENCY_PIN				// External emergency is triggered
									= 21,
	SSE_SUB_ERR_CAN_DRV_FOC_DURATION				// FOC algorithm duration error
									= 22,
	SSE_SUB_ERR_CAN_DRV_MCU_OVERHEAT 				// Driver temperature is to high
									= 23,
	SSE_SUB_ERR_CAN_DRV_MOTOR_OVERHEAT 				// Motor temperature is to high
									= 24,
	SSE_SUB_ERR_CAN_DRV_OVERCURRENT_SOFT 			// Current through motor exceed limit
									= 25,
	SSE_SUB_ERR_CAN_DRV_SEVERAL		= 26, 			// Several errors on driver
	SSE_SUB_ERR_CAN_EXT_BUS_OFF 	= 27, 			// CAN bus high rate errors of slave controller
	SSE_SUB_ERR_CAN_INT_BUS_OFF 	= 28, 			// CAN bus high rate errors of main controller
	SSE_SUB_ERR_ENCODER_NOT_FOUND 	= 29, 			// No any answer from encoder during init
	SSE_SUB_ERR_CAN_DRV_NOT_RESPONDING 				// Lost connection to CAN Drv
									= 30,
	SSE_SUB_ERR_CAN_DRV_WRONG_PARAMS 				// Some params of CAN Drv isn't correct
									= 31,
	SSE_SUB_ERR_OVERCURRENT 		= 32, 			// Fast over current protection of main controller,
													// or short circuit detection on startup
	SSE_SUB_ERR_UNSAFE_VOLTAGE 		= 33, 			// Under voltage protection or supply protection controller fault
	SSE_SUB_ERR_WRONG_FULL_BAT_VOLTAGE_PARAM 		// battery voltage is higher than expected at startup sequence
									= 34,
	SSE_SUB_ERR_EEPROM_PARAMS_CORRUPTED 			// Parameters are corrupted in EEPROM and
									= 35 			// can't be restored from backup slot

}	SystemSubError_t;


/**	@note	RealTimeData_t.RT_DataFlags
 */
typedef enum
{
	RTDF_MOTORS_OFF					= 0,
	RTDF_MOTORS_ON					= 1

}	RT_DataFlag_t;


/**	@note	RealTimeData_t.curProfile
 */
typedef enum
{
	CP_PROFILE_1 					= 0,
	CP_PROFILE_2 					= 1,
	CP_PROFILE_3 					= 2,
	CP_PROFILE_4 					= 3,
	CP_PROFILE_5 					= 4,

}	CurProfile_t;


/**	@note	RealTimeData_t.calibMode
 */
typedef enum
{
	/* If not 0, calibration or automatic
	   task is performed: */
	CalibM_CALIB_MODE_EXT_GAIN 		= 1,
	CalibM_CALIB_MODE_SET_ANGLE_AND_SAVE
									= 2,
	CalibM_CALIB_MODE_POLES 		= 3,
	CalibM_CALIB_MODE_ACC 			= 4,
	CalibM_CALIB_MODE_GYRO 			= 5,
	CalibM_CALIB_MODE_ENCODER_OFFSET
									= 6,
	CalibM_CALIB_MODE_ENCODER_FLD_OFFSET
									= 7,
	CalibM_CALIB_MODE_AUTO_PID 		= 8,
	CalibM_CALIB_MODE_BODE_TEST 	= 9,
	CalibM_CALIB_MODE_GYRO_TEMP 	= 10,
	CalibM_CALIB_MODE_ACC_TEMP 		= 11,
	CalibM_CALIB_MODE_MAG 			= 12,
	CalibM_CALIB_MODE_SET_ANGLE 	= 13,
	CalibM_CALIB_MODE_SYSTEM_IDENT	= 14,
	CalibM_CALIB_MODE_MOTOR_MAG_LINK
									= 15,
	CalibM_CALIB_MODE_SEARCH_LIMITS	= 16,
	CalibM_CALIB_MODE_SET_OPERATION_POS
									= 17,
	CalibM_CALIB_MODE_IMU_ORIENTATION_CORR
									= 18,
	CalibM_CALIB_MODE_TIMELAPSE 	= 19,
	CalibM_CALIB_MODE_MOMENTUM 		= 20,
	CalibM_CALIB_MODE_MOMENTUM_AUTO	= 21,
	CalibM_CALIB_MODE_COGGING 		= 22,
	CalibM_CALIB_MODE_ACC_EXT_REF	= 23,
	CalibM_CALIB_MODE_SAFE_STOP 	= 24,
	CalibM_CALIB_MODE_ACC_SPHERE 	= 25,
	CalibM_CALIB_MODE_GYRO_AXES_ALIGNMENT
									= 26,
	CalibM_CALIB_MODE_EXT_IMU_GYRO	= 27,
	CalibM_CALIB_MODE_EXT_IMU_ALIGN	= 28,
	CalibM_CALIB_MODE_ACC_GYRO_MULTIPOINT
									= 34

}	CalibMode_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 									 RC Inputs Flags
 */
/**	@addtogroup	RC_Inputs
 * 	@{
 */
/**	@note @ref	SBGC32_ReadRC_Inputs, 3 arg
 */
typedef enum
{
	ICF_DONT_TRY_TO_INIT_INPUT		= 0,
	ICF_TRY_TO_INIT_INPUT			= 1

}	InitCfgFlag_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								   Debug Var 3 Flags
 */
/**	@addtogroup	Debug_Var_3
 * 	@{
 */
/**	@note	DebugVar_t.varType
 *
 *	Can be combined with @ref VarType_t
 */
typedef enum
{
	VT_VAR_FLAG_ROLL 				= BIT_4_SET,
	VT_VAR_FLAG_PITCH 				= BIT_5_SET,
	VT_VAR_FLAG_YAW 				= (BIT_4_SET | BIT_5_SET),
	VT_VAR_FLAG_ANGLE14 			= BIT_6_SET

}	VarTypeFlag_t;

/**	@brief	Used as a mask to extract the
 * 			variable type from
 * 			DebugVar_t.varType
 *
 * 	@param	value (DebugVar_t.varType)
 *
 * 	@return	Variable type
 */
static inline VarType_t GetVarType (ui8 value)
{
	return (VarType_t)(value & 0b00001111);
}

/**	@brief	Used as a mask to extract the
 * 			variable's flag from
 * 			DebugVar_t.varType
 *
 * 	@param	value (DebugVar_t.varType)
 *
 * 	@return	Variable's flag
 */
static inline VarTypeFlag_t GetVarFlag (ui8 value)
{
	return (VarTypeFlag_t)(value & 0b11110000);
}
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								  Select IMU 3 Flags
 */
/**	@addtogroup	IMU_Select_3
 * 	@{
 */
/**	@note	DebugVar_t.varType
 */
typedef enum
{
	SIMUA_SIMPLE_SELECT 			= 0,
	SIMUA_REGULAR_CALIBRATION 		= 1,
	SIMUA_RESET_ALL_CALIB_AND_RESTART
									= 2,
	SIMUA_TEMPERATURE_CALIBRATION 	= 3,
	SIMUA_ENABLE_TEMP_CALIB_DATA_IF_PRESENT
									= 4,
	SIMUA_DISABLE_TEMP_CALIB_DATA	= 5,
	SIMUA_RESTORE_FACTORY_CALIB 	= 6,
	SIMUA_COPY_CALIB_FROM_MAIN_EEPROM
									= 7

}	SelectIMU_Action_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 					  Data Stream Interval Structure
 */
/**	@addtogroup	Data_Stream_Interval Data Stream Interval
 * 	@{
 */
/**	@brief	Structure type for work with
 *  		DataStreamInterval parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			CMD_DATA_STREAM_INTERVAL
 *
 *			TX 16 bytes
 *
 *	@ref	SBGC32_RequestDataStream function
 */
typedef struct __PACKED__
{
	ui8		cmdID;									/*!<  See @ref DataStreamCommand_t enumeration										*/
	ui16	intervalMs;								/*!<  Depends on the syncToData parameter											*/
	ui8		config [8];								/*!<  Configuration specific to each command, depends on the cmdID parameter		*/
	ui8		syncToData;								/*!<  See @ref SyncToData_t enumeration												*/
	ui8		reserved [9];

}			DataStreamInterval_t;


#if (SYS_BIG_ENDIAN || SBGC_REF_INFO)
	/**	@cond
	 */
	extern const ParameterReferenceInfo_t dataStreamIntervalReferenceInfoArray [];
	extern const ui8 dataStreamIntervalReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 					  Realtime Data Custom Structure
 */
/**	@addtogroup	Realtime_Data_Custom
 * 	@{
 */
/**	@brief	Structure type for work with
 *  		RealTimeDataCustom parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			CMD_REALTIME_DATA_CUSTOM
 *
 *			RX (2 + ?) bytes
 *
 *	@ref	SBGC32_RequestRealTimeDataCustom function
 */
typedef struct __PACKED__
{
	ui16	timestampMs;							/*!<  Units: ms																		*/

	i16		IMU_Angles [3],							/*!<  Units: 0.02197265625 degree. Main IMU angles (Euler)							*/
			targetAngles [3],						/*!<  Units: 0.02197265625 degree. Target angles that gimbal should keep (Euler)	*/
			targetSpeed [3],						/*!<  Units: 0.06103701895 degree/sec. Target speed that gimbal should keep (Euler)	*/
			frameCamAngle [3],						/*!<  Units: 0.02197265625 degree. Relative angle of joints (motors)				*/
			gyroData [3],							/*!<  Units: 0.06103701895 degree/sec. Data from the gyroscope sensor				*/
			RC_Data [6];							/*!<  -16384 --> 16384. Value -32768 is for 'undefined' signal						*/

	float	Z_Vector [3],							/*!<  -1.0f --> 1.0f																*/
			H_Vector [3];							/*!<  -1.0f --> 1.0f																*/

	i16		RC_Channels [18];						/*!<  -16384 --> 16384. Value -32768 is for 'undefined' signal						*/
	i16		ACC_Data [3];							/*!<  Units: 1/512 G																*/

	Motor4_Control_t	motor4_Control;				/*!<  See @ref Motor4_Control_t structure type										*/
	AHRS_DebugInfo_t	AHRS_DebugInfo;				/*!<  See @ref AHRS_DebugInfo_t structure type										*/

	ui8		encoderRaw24 [3][3];					/*!<  3 bytes for each encoder in a sequence for
														  ROLL, PITCH, YAW motors, lower byte first. Frw. ver. 2.68+					*/
	float 	IMU_AnglesRad [3];						/*!<  Main IMU Euler angles in radians. Frw. ver. 2.68b7+							*/

}			RealTimeDataCustom_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 					 Realtime Data 3 (-4) Structures
 */
/**	@addtogroup	Realtime_Data_3_4
 *	@{
 */
/**	@brief	Part of RealTimeData_t structure
 *
 * 	@note	RealTimeData_t.AxisRTD
 */
typedef struct __PACKED__
{
	i16     ACC_Data;                           	/*!<  Units: 1/512 G																*/
	i16     gyroData;                           	/*!<  Units: 0.06103701895 degree/sec												*/

}           AxisRTD_t;

/** @brief	Structure type for work with
 *  		RealTimeData3 (-4) parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			CMD_REALTIME_DATA_3
 *			CMD_REALTIME_DATA_4
 *
 *			RX 63 (_3) or 124 (_4) bytes
 *
 *			Receive real-time data as simple
 *			or extended formats
 *
 *	@ref	SBGC32_ReadRealTimeData3 function\n
 *	@ref	SBGC32_ReadRealTimeData4 function
 */
typedef struct __PACKED__
{
	AxisRTD_t	AxisRTD [3];						/*!<  ROLL : PITCH : YAW															*/

    ui16    serialErrCnt;                           /*!<  0 --> 65535																	*/
    ui16    systemError;                            /*!<  See @ref SystemError_t enumeration											*/
    ui8     systemSubError;                         /*!<  See @ref SystemSubError_t enumeration											*/
    ui8     reserved [3];

    i16     RC_ROLL,                                /*!<  ...																			*/
            RC_PITCH,                               /*!<  ...																			*/
            RC_YAW,                                 /*!<  RC control channels values (PWM or normalized analog)							*/

			RC_Cmd,                                 /*!<  1000 --> 2000. RC command channel value (PWM or normalized analog)			*/

			ExtFC_ROLL,                             /*!<  1000 --> 2000. External FC PWM values. May be zero if their...				*/
            ExtFC_PITCH;                            /*!<  ...inputs are mapped to RC control or command									*/

    i16     IMU_Angle [3];                          /*!<  -32768 --> 32767. Units: 0.02197265625 degree									*/
    i16     frameIMU_Angle [3];                     /*!<  -32768 --> 32767. Units: 0.02197265625 degree									*/
    i16     targetAngle [3];                        /*!<  -32768 --> 32767. Units: 0.02197265625 degree									*/
    ui16    cycleTime;                              /*!<  Units: ms																		*/
    ui16    I2C_ErrorCount;							/*!<  Number of registered errors on I2C bus										*/
    ui8     errorCode;                              /*!<  Deprecated, replaced by the SYSTEM_ERROR variable								*/
    ui16    batLevel;                               /*!<  Units: 0.01 volt																*/
    ui8     RT_DataFlags;							/*!<  See @ref RT_DataFlag_t enumeration											*/
    ui8     curIMU;									/*!<  See @ref IMU_Type_t enumeration												*/
    ui8     curProfile;                             /*!<  See @ref CurProfile_t enumeration												*/
    ui8     motorPower [3];                         /*!<  0 --> 255																		*/

    /* Realtime Data 4 */
    i16     frameCamAngle [3];                   	/*!<  Units: 0.02197265625 degree													*/
    ui8     reserved1;
    i16     balanceError [3];                       /*!<  -512 --> 512. Error in balance												*/
    ui16    current;                                /*!<  Units: mA																		*/
    i16     magData [3];                            /*!<  -1000 --> 1000 (Units: relative, calibrated for								*/
                                                    /*!<                 current environment for each axis)								*/
    i8      IMU_Temperature,                        /*!<  -127 --> 127. Units: Celsius													*/
            frameIMU_Temperature;                   /*!<  -127 --> 127. Units: Celsius													*/

    ui8     IMU_G_Err,                              /*!<  0 --> 255. Units: 0.1 degree													*/
            IMU_H_Err;                              /*!<  0 --> 255. Units: 0.1 degree													*/

    i16     motorOut [3];                           /*!<  -10000 --> 10000. Encoder firmware ver. 2.61+									*/
    ui8     calibMode;                              /*!<  See @ref CalibMode_t enumeration												*/
    ui8     CAN_IMU_ExtSensErr;						/*!<  Error code from the external sensor connected to the CAN_IMU					*/
    ui8     reserved2 [28];

}           RealTimeData_t;


#if (SYS_BIG_ENDIAN || SBGC_REF_INFO)
	/**	@cond
	 */
	extern const ParameterReferenceInfo_t realTimeDataReferenceInfoArray [];
	extern const ui8 realTimeDataReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 							   Get Angles Structures
 */
/**	@addtogroup	Get_Angles
 * 	@{
 */
/**	@brief	Part of GetAngles_t structure
 *
 * 	@note	GetAngles_t.AxisGA
 */
typedef struct __PACKED__
{
	i16		IMU_Angle,								/*!<  Units: 0.02197265625 degree													*/
			targetAngle,							/*!<  Units: 0.02197265625 degree													*/
			targetSpeed;							/*!<  Units: 0.1220740379 degree/sec												*/

}			AxisGA_t;

/** @brief	Structure type for work with
 *  		GetAngles parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			CMD_GET_ANGLES
 *
 *			RX 18 bytes
 *
 *	@ref	SBGC32_GetAngles function
 */
typedef struct __PACKED__
{
	AxisGA_t	AxisGA [3];							/*!<  ROLL : PITCH : YAW															*/

}				GetAngles_t;


#if (SYS_BIG_ENDIAN || SBGC_REF_INFO)
	/**	@cond
	 */
	extern const ParameterReferenceInfo_t getAnglesReferenceInfoArray [];
	extern const ui8 getAnglesReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif


/**	@brief	Part of GetAnglesExt_t structure
 *
 * 	@note	GetAnglesExt_t.AxisGAE
 */
typedef struct __PACKED__
{
	i16		IMU_Angle;								/*!<  Units: 0.02197265625 degree													*/
	i16 	targetAngle;							/*!<  Units: 0.02197265625 degree													*/
	i32		frameCamAngle;							/*!<  Units: 0.02197265625 degree													*/
	ui8		reserved [10];

}			AxisGAE_t;

/** @brief	Structure type for work with
 *  		GetAnglesExt parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			CMD_GET_ANGLES_EXT
 *
 *			RX 54 bytes
 *
 *	@ref	SBGC32_GetAnglesExt function
 */
typedef struct __PACKED__
{
	AxisGAE_t	AxisGAE [3];						/*!<  ROLL : PITCH : YAW															*/

}				GetAnglesExt_t;


#if (SYS_BIG_ENDIAN || SBGC_REF_INFO)
	/**	@cond
	 */
	extern const ParameterReferenceInfo_t getAnglesExtReferenceInfoArray [];
	extern const ui8 getAnglesExtReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								 RC Inputs Structure
 */
/**	@addtogroup	RC_Inputs
 * 	@{
 */
/**	@brief	Structure type for work with
 *  		RC_Inputs parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			CMD_READ_RC_INPUTS
 *
 *	@ref	SBGC32_ReadRC_Inputs function
 */
typedef struct
{
	i16		RC_Val;									/*!<  Values for each RC source														*/
	ui8		RC_Src;									/*!<  See @ref RC_MapSourceType_t and @ref RC_MapSource_t enumerations				*/

}			RC_Inputs_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 							   Debug Var 3 Structure
 */
/**	@addtogroup	Debug_Var_3
 * 	@{
 */
/**	@brief	Part of DebugVars3_t structure
 *
 * 	@note	DebugVars3_t.DebugVar
 */
typedef struct
{
	ui8			varNameLength;						/*!<  This is a 1st byte from varName parameter										*/
	char		varName [256];						/*!<  This is a string, ended which '\0'											*/
	VarType_t	varType;							/*!<  See @ref VarType_t and @ref VarTypeFlag_t enumerations						*/

	ui32		varValue;							/*!<  Read-Only																		*/

}				DebugVar_t;

/**	@brief	Structure type for work with
 *  		DebugVars3 parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			CMD_DEBUG_VARS_INFO_3
 *			CMD_DEBUG_VARS_3
 *
 *			TX/RX ?/? bytes
 *
 *			Works both with information about
 *			variables and with their values
 *
 *	@ref	SBGC32_RequestDebugVarInfo3 function\n
 *	@ref	SBGC32_RequestDebugVarValue3 function
 */
typedef struct
{
	ui8			varNum;								/*!<  1 --> 255. Number of variables in this structure								*/

	DebugVar_t	DebugVar [MAX_DEBUG_VARS_QUAN];		/*!<  See @ref MAX_DEBUG_VARS_QUAN definition										*/

}			DebugVars3_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								 Function Prototypes
 */
/**	@addtogroup	Data_Stream_Interval
 * 	@{
 */
TxRxStatus_t SBGC32_RequestDataStream (GeneralSBGC_t *generalSBGC, DataStreamInterval_t *dataStreamInterval);
TxRxStatus_t SBGC32_StopDataStream (GeneralSBGC_t *generalSBGC, DataStreamInterval_t *dataStreamInterval);
TxRxStatus_t SBGC32_ParseDataStream (GeneralSBGC_t *generalSBGC, void *dataStreamStruct, SBGC_Command_t cmdID);
/**	@}
 */


/**	@addtogroup	Realtime_Data_Custom
 * 	@{
 */
TxRxStatus_t SBGC32_RequestRealTimeDataCustom (GeneralSBGC_t *generalSBGC, RealTimeDataCustom_t *realTimeDataCustom, RealTimeDataCustomFlag_t flags);
/**	@}
 */


/**	@addtogroup	Realtime_Data_3_4
 * 	@{
 */
TxRxStatus_t SBGC32_ReadRealTimeData3 (GeneralSBGC_t *generalSBGC, RealTimeData_t *realTimeData);
TxRxStatus_t SBGC32_ReadRealTimeData4 (GeneralSBGC_t *generalSBGC, RealTimeData_t *realTimeData);
/**	@}
 */


/**	@addtogroup	Get_Angles
 * 	@{
 */
TxRxStatus_t SBGC32_GetAngles (GeneralSBGC_t *generalSBGC, GetAngles_t *getAngles);
TxRxStatus_t SBGC32_GetAnglesExt (GeneralSBGC_t *generalSBGC, GetAnglesExt_t *getAnglesExt);
/**	@}
 */


/**	@addtogroup	RC_Inputs
 * 	@{
 */
TxRxStatus_t SBGC32_ReadRC_Inputs (GeneralSBGC_t *generalSBGC, RC_Inputs_t *RC_Inputs, InitCfgFlag_t cfgFlags, ui8 srcQuan);
/**	@}
 */


/**	@addtogroup	Debug_Var_3
 * 	@{
 */
TxRxStatus_t SBGC32_RequestDebugVarInfo3 (GeneralSBGC_t *generalSBGC, DebugVars3_t *debugVars3);
TxRxStatus_t SBGC32_RequestDebugVarValue3 (GeneralSBGC_t *generalSBGC, DebugVars3_t *debugVars3);
/**	@}
 */


/**	@addtogroup	IMU_Select_3
 * 	@{
 */
TxRxStatus_t SBGC32_SelectIMU_3 (GeneralSBGC_t *generalSBGC, IMU_Type_t IMU_Type, SelectIMU_Action_t action,
								 ui16 timeMs);
/**	@}
 */

#endif		/* SBGC_REALTIME_MODULE */


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef 		__cplusplus
			}
#endif

#endif      /* _REALTIME_H_ */
