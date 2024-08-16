/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.0
 *
 *	@file		realtime.h
 *
 *	@brief		Realtime header file
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
 *	@defgroup	Realtime SBGC32 Realtime
 *	@ingroup	Modules
 *		@brief	SBGC32 Realtime Title Module
 *	____________________________________________________________________
 *
 *	@defgroup	Data_Stream_Interval Data Stream Interval
 *	@ingroup	Realtime
 *		@brief	Data Stream Interval Module
 *
 *				Covered Commands:
 *
 *				### CMD_EVENT
 *				### CMD_CAN_DRV_TELEMETRY
 *				### CMD_EXT_MOTORS_STATE
 *				### CMD_DATA_STREAM_INTERVAL
 *
 *	@defgroup	Realtime_Data_Custom Realtime Data Custom
 *	@ingroup	Realtime
 *		@brief	Realtime Data Custom Module
 *
 *				Covered Commands:
 *
 *				### CMD_REALTIME_DATA_CUSTOM
 *
 *	@defgroup	Realtime_Data_3_4 Realtime Data 3(-4)
 *	@ingroup	Realtime
 *		@brief	Realtime Data 3(-4) Module
 *
 *				Covered Commands:
 *
 *				### CMD_REALTIME_DATA_3
 *				### CMD_REALTIME_DATA_4
 *
 *	@defgroup	Get_Angles Get Angles
 *	@ingroup	Realtime
 *		@brief	Get Angles Module
 *
 *				Covered Commands:
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
 *
 *	@defgroup	Control_Quat_Status Control Quat Status
 *	@ingroup	Realtime
 *		@brief	Control Quat Status Module
 *
 *				Covered Commands:
 *
 *				### CMD_CONTROL_QUAT_STATUS
 *	____________________________________________________________________
 */

#ifndef		MODULES_REALTIME_H_
#define		MODULES_REALTIME_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../sbgc32.h"


#if (SBGC_REALTIME_MODULE)


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						  Data Stream Interval Flags
 */
/**	@addtogroup	Data_Stream_Interval
 *	@{
 */
/**	@note	sbgcEvent_t.eventID \n
 *			@ref ParserSBGC32_EventID_AndTypeToStream, 2 arg
 *			Available value for the sbgcDataStreamInterval_t.config
 */
typedef enum
{
	EID_EVENT_ID_MENU_BUTTON		= 1,
	EID_EVENT_ID_MOTOR_STATE		= 2,
	EID_EVENT_ID_EMERGENCY_STOP		= 3,
	EID_EVENT_ID_CAMERA				= 4,
	/* frw. ver. 2.68b8+ */
	EID_EVENT_ID_SCRIPT				= 5

}	sbgcEventID_t;


/**	@note	sbgcEvent_t.eventType \n
 *			@ref ParserSBGC32_EventID_AndTypeToStream, 3 arg
 *			Available value for the sbgcDataStreamInterval_t.config
 */
typedef enum
{
	/* Applicable for EID_EVENT_ID_MENU_BUTTON,
   	   EID_EVENT_ID_MOTOR_STATE,
   	   EID_EVENT_ID_EMERGENCY_STOP,
   	   EID_EVENT_ID_SCRIPT */
	EVENT_TYPE_OFF					= 1,
	EVENT_TYPE_ON					= 2,
	EVENT_TYPE_HOLD					= 4,

	/* Applicable for EID_EVENT_ID_CAMERA */
	EVENT_TYPE_REC_PHOTO			= 1,
	EVENT_TYPE_PHOTO				= 2

}	sbgcEventType_t;


/**	@note	sbgcDataStreamInterval_t.cmdID \n
 *			@ref SBGC32_ReadDataStream, 2 arg
 */
typedef enum
{
	DSC_CMD_REALTIME_DATA_3			= CMD_REALTIME_DATA_3,
	DSC_CMD_REALTIME_DATA_4			= CMD_REALTIME_DATA_4,
	DSC_CMD_REALTIME_DATA_CUSTOM	= CMD_REALTIME_DATA_CUSTOM,
	DSC_CMD_AHRS_HELPER				= CMD_AHRS_HELPER,
	/* frw.ver. 2.65b7+ */
	DSC_CMD_EVENT					= CMD_EVENT,
	/* frw.ver. 2.72b0+ ("Extended" family only) */
	DSC_CMD_CAN_DRV_TELEMETRY		= CMD_CAN_DRV_TELEMETRY,
	/* frw.ver. 2.73+ */
	DSC_CMD_EXT_MOTORS_STATE		= CMD_EXT_MOTORS_STATE

}	sbgcDataStreamCommand_t;


/**	@note	sbgcDataStreamInterval_t.syncToData
 */
typedef enum
{
	STD_SYNC_OFF					= 0,
	STD_SYNC_ON						= 1

}	sbgcSyncToData_t;


/**	@note	These flags have come in if CAN_DRV_TF_PIN_STATE
 *			flag was set and requested in the
 *			@ref SBGC32_StartDataStream function.
 *
 *			See @ref sbgcCAN_DriverTelemetryFlag_t enumeration
 */
typedef enum
{
	CAN_DRV_TPS_LIMIT				= BIT_0_SET,
	CAN_DRV_TPS_INDEX				= BIT_1_SET,
	CAN_DRV_TPS_EMERGENCY			= BIT_2_SET,
	CAN_DRV_TPS_AUX1				= BIT_3_SET,
	CAN_DRV_TPS_AUX2				= BIT_4_SET,
	CAN_DRV_TPS_AUX3				= BIT_5_SET,
	CAN_DRV_TPS_HALF_BRIDGE_ENADLE	= BIT_6_SET,
	CAN_DRV_TPS_ENCODER_SPI_CS		= BIT_7_SET

}	sbgcCAN_DriverTelemetryPinState_t;


/**	@note	@ref ParserSBGC32_CAN_DT_FlagsAndID_ToStream, 2 arg\n
 *			Available value for the sbgcDataStreamInterval_t.config
 */
typedef enum
{
	CAN_DRV_TF_CAN_BUS_FLAGS		= BIT_0_SET,
	CAN_DRV_TF_CAN_BUS_ERR_CNT		= BIT_1_SET,
	CAN_DRV_TF_TEMP_BOARD			= BIT_2_SET,
	CAN_DRV_TF_TEMP_MOTOR			= BIT_3_SET,
	CAN_DRV_TF_AVG_CURRENT			= BIT_4_SET,
	CAN_DRV_TF_BUS_VOLTAGE			= BIT_5_SET,
	CAN_DRV_TF_PIN_STATE			= BIT_6_SET,	// See sbgcCAN_DriverTelemetryPinState_t enumeration
	CAN_DRV_TF_PHASE_CURRENT		= BIT_7_SET,
	CAN_DRV_TF_ENCODER_ERROR_CNT	= BIT_8_SET,
	CAN_DRV_TF_IQ_ID_CURRENT		= BIT_9_SET,
	CAN_DRV_TF_MOTOR_SPEED			= BIT_10_SET,
	CAN_DRV_TF_PID_POS_ERR			= BIT_11_SET,
	CAN_DRV_TF_PID_SPEED_ERR		= BIT_12_SET,
	CAN_DRV_TF_IQ_REF				= BIT_13_SET,
	CAN_DRV_TF_PID_CURRENT_ERR		= BIT_14_SET

}	sbgcCAN_DriverTelemetryFlag_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						  Realtime Data Custom Flags
 */
/**	@addtogroup	Realtime_Data_Custom
 *	@{
 */
/**	@brief	Motor info flags
 *
 *	@note	sbgcAxisMPS_t.motorFlags
 */
typedef enum
{
	sbgcMF_SOFTWARE_LIMIT_VIOLATED	= BIT_0_SET,
	sbgcMF_CURRENT_EXCEED_LIMIT		= BIT_1_SET,
	sbgcMF_MOTOR_DRIVER_ENABLED		= BIT_2_SET

}	sbgcMotorFlag_t;


/**	@brief	Details about system power management
 *
 *	@note	sbgcSystemPowerState_t.systemPowerState
 */
typedef enum
{
	sbgcSPSG_ON_FROM_BACKUP			= -2,			/*!<  Internal use																	*/
	sbgcSPSG_STARTUP				= -1,			/*!<  Internal use																	*/

	sbgcSPSG_OFF					= 0,			/*!<  Motors are OFF																*/
	sbgcSPSG_ON						= 1,			/*!<  Motors are ON																	*/
	sbgcSPSG_OFF_TEMPORARY			= 2,			/*!<  Motors are temporarily OFF for calibration									*/
	sbgcSPSG_OFF_PARKING			= 3,			/*!<  Motors are temporarily OFF when entering parking position						*/
	sbgcSPSG_ON_SAFE_STOP			= 4,			/*!<  Motors are energized to softly drop the unbalanced payload before going OFF	*/

}	sbgcSystemPowerStateGeneral_t;


/**	@brief	System power state flags
 *
 *	@note	sbgcSystemPowerState_t.systemFlags
 */
typedef enum
{
	sbgcMSF_SOFTWARE_LIMIT_VIOLATED_ANY
									= BIT_0_SET,
	sbgcMSF_OVERHEAT_WARNING		= BIT_1_SET

}	sbgcMotorSystemFlags_t;


/**	@brief	CAN communication error flags
 *
 *	@note	sbgcCommunicationErrors_t.CAN_ErrFlags
 */
typedef enum
{
	CAN_ERROR_FLAG_WARN_IRQ			= BIT_0_SET,
	CAN_ERROR_FLAG_PASSIVE_IRQ		= BIT_1_SET,
	CAN_ERROR_FLAG_BUS_OFF_IRQ		= BIT_2_SET

}	sbgcCAN_ErrFlag_t;


/**	@note	@ref SBGC32_RequestRealTimeDataCustom, 3 arg\n
 *			@ref ParserSBGC32_RTDC_FlagsToStream, 2 arg\n
 *			Available value for the sbgcDataStreamInterval_t.config
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
	RTDCF_IMU_ANGLES_RAD			= BIT_12_SET,
	RTDCF_SCRIPT_VARS_FLOAT			= BIT_13_SET,
	RTDCF_SCRIPT_VARS_INT16			= BIT_14_SET,
	RTDCF_SYSTEM_POWER_STATE		= BIT_15_SET,
	RTDCF_FRAME_CAM_RATE			= BIT_16_SET,
	RTDCF_IMU_ANGLES_20				= BIT_17_SET,
	RTDCF_TARGET_ANGLES_20			= BIT_18_SET,
	RTDCF_COMM_ERRORS				= BIT_19_SET,
	RTDCF_SYSTEM_STATE_FLAGS		= BIT_20_SET

}	sbgcRealTimeDataCustomFlag_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						  Realtime Data 3 (-4) Flags
 */
/**	@addtogroup	Realtime_Data_3_4
 *	@{
 */
/**	@note	sbgcRealTimeData_t.systemError
 */
typedef enum
{
	SE_NO_ERROR						= 0,
	SE_ERR_NO_SENSOR				= BIT_0_SET,
	SE_ERR_CALIB_ACC				= BIT_1_SET,
	SE_ERR_SET_POWER				= BIT_2_SET,
	SE_ERR_CALIB_POLES				= BIT_3_SET,
	SE_ERR_PROTECTION				= BIT_4_SET,
	SE_ERR_SERIAL					= BIT_5_SET,
	/* Beside that, extended error contains bits: */
	SE_ERR_LOW_BAT1					= BIT_6_SET,
	SE_ERR_LOW_BAT2					= BIT_7_SET,
	SE_ERR_GUI_VERSION				= BIT_8_SET,
	SE_ERR_MISS_STEPS				= BIT_9_SET,
	SE_ERR_SYSTEM					= BIT_10_SET,
	SE_ERR_EMERGENCY_STOP			= BIT_11_SET

}	sbgcSystemError_t;


/**	@note	sbgcRealTimeData_t.systemSubError
 */
typedef enum
{
	/* Specifies the reason of emergency stop: */
	SSE_I2C_ERRORS					= 1,			// High rate of I2C errors
	SSE_DRV_OTW						= 2,			// Driver over-temperature protection
	SSE_DRV_FAULT					= 3,			// Driver fault (under-voltage, over-current, short circuit)
	SSE_ENCODER_IMU_ANGLE			= 4,			// Encoder/IMU angles mismatch
	SSE_CALIBRATION_FAILED			= 5,			// Auto calibration process caused serious fault
	SSE_INTERNAL_SYSTEM_ERROR		= 6,			// Stack is damaged
	SSE_ENCODER_CALIB_BAD_SCALE		= 7,			// Estimated scale differs a lot from configured
	SSE_OVER_TEMPERATURE			= 8,			// MCU or power board over temperature
	SSE_UB_ERR_BAD_MOTOR_POLES_INVERT
									= 9,			// Motor n.poles or inversion is wrong
	SSE_NOT_ENOUGH_MEMORY			= 10,			// static_malloc() can't allocate memory
	SSE_IMU_SENSOR_NOT_RESPONDING	= 11,			// Lost connection to IMU sensor
	SSE_CAN_HARD					= 12,			// CAN on board hardware error
	SSE_MOTOR_OVERHEAT_PROTECTION	= 13,			// Overheat protection is triggered
	SSE_MOTOR_IS_LOCKED				= 14,			// Motor is locked during automated task
	SSE_BAD_IMU_HEALTH				= 15,			// IMU gyroscope and accelerometer error is too big:
													// sensor sends corrupted data or wrong use conditions
	SSE_INFINITE_RESET				= 16,			// Infinite reset loop is detected
	SSE_WRONG_INITIAL_POSITION		= 17,			// Wrong position: failed to detect encoder angle,
													// or angle is outside soft limits
	SSE_MOTOR_LOAD_TIME_EXCEEDED	= 18,			// Motors are fully loaded too long time
	SSE_CAN_DRV_OVERCURRENT			= 19,			// Hardware short-circuit protection
	SSE_CAN_DRV_UNDERVOLTAGE		= 20,			// Hardware or software under-voltage protection
	SSE_CAN_DRV_EMERGENCY_PIN		= 21,			// External emergency is triggered
	SSE_CAN_DRV_FOC_DURATION		= 22,			// FOC algorithm duration error
	SSE_CAN_DRV_MCU_OVERHEAT		= 23,			// Driver temperature is to high
	SSE_CAN_DRV_MOTOR_OVERHEAT		= 24,			// Motor temperature is to high
	SSE_CAN_DRV_OVERCURRENT_SOFT	= 25,			// Current through motor exceed limit
	SSE_CAN_DRV_SEVERAL				= 26,			// Several errors on driver
	SSE_CAN_EXT_BUS_OFF				= 27,			// CAN bus high rate errors of slave controller
	SSE_CAN_INT_BUS_OFF				= 28,			// CAN bus high rate errors of main controller
	SSE_ENCODER_NOT_FOUND			= 29,			// No any answer from encoder during init
	SSE_CAN_DRV_NOT_RESPONDING		= 30,			// Lost connection to CAN Drv
	SSE_CAN_DRV_WRONG_PARAMS		= 31,			// Some params of CAN Drv isn't correct
	SSE_OVERCURRENT					= 32,			// Fast over current protection of main controller,
													// or short circuit detection on startup
	SSE_UNSAFE_VOLTAGE				= 33,			// Under voltage protection or supply protection controller fault
	SSE_WRONG_FULL_BAT_VOLTAGE_PARAM
									= 34,			// Battery voltage is higher than expected at startup sequence
	SSE_EEPROM_PARAMS_CORRUPTED		= 35,			// Parameters are corrupted in EEPROM and
													// can't be restored from backup slot
	SSE_ENCODER_UNSUPPORTED_TYPE	= 36,			// Unsupported type of encoder
	SSE_EXT_IMU_UNSUPPORTED_TYPE	= 37,			// Unsupported type of external imu of CAN Imu, need update CAN Imu FW
	SSE_EXT_IMU_SENSOR_NOT_RESPONDING
									= 38,			// Lost connection to external imu of CAN Imu
	SSE_EXT_IMU_WRONG_PARAMS		= 39,			// Some errors in self test in external imu of CAN Imu,
													// or difference of int. and ext. is too big
	SSE_DRIVER_INIT					= 40,			// Initialization of ext. motor driver failed
	SSE_EEPROM_VARS_OUT_OF_BORDERS	= 41,			// _write_vars() or _read_vars() out of  borders
	SSE_IWDG_RESET					= 42,			// System was reset by watch-dog timer
	SSE_ADC_WAIT					= 43,			// Error waiting for ADC samples
	SSE_CALIB_MOTOR_OFF				= 44,			// Need power motor for calibration process
	SSE_TIMEOUT						= 45,
	SSE_CAN_DRV_CALIB_UNEXPECTED_RES
									= 46,			// CAN DRV RL calibration error
	SSE_MAG_SENSOR_NOT_RESPONDING	= 47,			// Lost connection to MAG sensor
	SSE_CAN_DRV_OVERSPEED			= 48,			// CAN Drv spin too fast
	SSE_ENC_SELF_CALIB_FAILED		= 49,			// Encoder self calibration failed
	SSE_CAN_VERSION_MISMATCH		= 50,			// Major version of CAN module don't match SBGC firmware version
	SSE_CAN_SERIAL_INIT				= 51,			// Serial-over-CAN can't be configured with the  current parameters
	SSE_CAN_SERIAL_CONFLICT			= 52,			// Serial-over-CAN conflict
	SSE_CAN_DRV_INIT_STAGE			= 53,			// CAN Drv initialization sequence failed though it responds
	SSE_ENCODER_DATA_TIMEOUT		= 54,			// No fresh data from encoder for a long time
	SSE_HSE_START_FAIL				= 56,			// HSE (quartz) start problem
	SSE_FRAME_IMU_SENSOR_NOT_RESPONDING
									= 57,			// Lost connection to FRAME IMU  sensor
	SSE_PARAMETERS_MODIFIED			= 58,			// Can't write parameters - they were modified  in runtime
	SSE_NOT_NORMAL_POSITION			= 59,			// Can do certain calibrations only in a normal position (frame is inverted)
	SSE_CAN_DRV_LIMIT_EXCEED		= 60			// CAN Drv modules number exceed license

}	sbgcSystemSubError_t;


/**	@note	sbgcRealTimeData_t.RT_DataFlags
 */
typedef enum
{
	RTDF_MOTORS_OFF					= 0,
	RTDF_MOTORS_ON					= 1

}	sbgcRT_DataFlag_t;


/**	@note	sbgcRealTimeData_t.calibMode
 */
typedef enum
{
	/* If not 0, calibration or automatic
	   task is performed: */
	CalibM_CALIB_MODE_EXT_GAIN		= 1,
	CalibM_CALIB_MODE_SET_ANGLE_AND_SAVE
									= 2,
	CalibM_CALIB_MODE_POLES			= 3,
	CalibM_CALIB_MODE_ACC			= 4,
	CalibM_CALIB_MODE_GYRO			= 5,
	CalibM_CALIB_MODE_ENCODER_OFFSET
									= 6,
	CalibM_CALIB_MODE_ENCODER_FLD_OFFSET
									= 7,
	CalibM_CALIB_MODE_AUTO_PID		= 8,
	CalibM_CALIB_MODE_BODE_TEST		= 9,
	CalibM_CALIB_MODE_GYRO_TEMP		= 10,
	CalibM_CALIB_MODE_ACC_TEMP		= 11,
	CalibM_CALIB_MODE_MAG			= 12,
	CalibM_CALIB_MODE_SET_ANGLE		= 13,
	CalibM_CALIB_MODE_SYSTEM_IDENT	= 14,
	CalibM_CALIB_MODE_MOTOR_MAG_LINK
									= 15,
	CalibM_CALIB_MODE_SEARCH_LIMITS	= 16,
	CalibM_CALIB_MODE_SET_OPERATION_POS
									= 17,
	CalibM_CALIB_MODE_IMU_ORIENTATION_CORR
									= 18,
	CalibM_CALIB_MODE_TIMELAPSE		= 19,
	CalibM_CALIB_MODE_MOMENTUM		= 20,
	CalibM_CALIB_MODE_MOMENTUM_AUTO	= 21,
	CalibM_CALIB_MODE_COGGING		= 22,
	CalibM_CALIB_MODE_ACC_EXT_REF	= 23,
	CalibM_CALIB_MODE_SAFE_STOP		= 24,
	CalibM_CALIB_MODE_ACC_SPHERE	= 25,
	CalibM_CALIB_MODE_GYRO_AXES_ALIGNMENT
									= 26,
	CalibM_CALIB_MODE_EXT_IMU_GYRO	= 27,
	CalibM_CALIB_MODE_EXT_IMU_ALIGN	= 28,
	CalibM_CALIB_MODE_ACC_GYRO_MULTIPOINT
									= 34

}	sbgcCalibMode_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									 RC Inputs Flags
 */
/**	@addtogroup	RC_Inputs
 *	@{
 */
/**	@note	@ref SBGC32_ReadRC_Inputs, 3 arg
 */
typedef enum
{
	ICF_DONT_TRY_TO_INIT_INPUT		= 0,
	ICF_TRY_TO_INIT_INPUT			= 1

}	sbgcInitCfgFlag_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								   Debug Var 3 Flags
 */
/**	@addtogroup	Debug_Var_3
 *	@{
 */
/**	@note	sbgcDebugVar_t.varType
 *
 *	Can be combined with @ref sbgcVarType_t
 */
typedef enum
{
	VT_VAR_FLAG_ROLL				= BIT_4_SET,
	VT_VAR_FLAG_PITCH				= BIT_5_SET,
	VT_VAR_FLAG_YAW					= (BIT_4_SET | BIT_5_SET),
	VT_VAR_FLAG_ANGLE14				= BIT_6_SET

}	sbgcVarTypeFlag_t;

/**	@brief	Used as a mask to extract the
 *			variable type from
 *			sbgcDebugVar_t.varType
 *
 *	@param	value (sbgcDebugVar_t.varType)
 *
 *	@return	Variable type
 */
static inline sbgcVarType_t ParserSBGC32_GetVarType (ui8 value)
{
	return (sbgcVarType_t)(value & 0b00001111);
}

/**	@brief	Used as a mask to extract the
 *			variable's flag from
 *			sbgcDebugVar_t.varType
 *
 *	@param	value (sbgcDebugVar_t.varType)
 *
 *	@return	Variable's flag
 */
static inline sbgcVarTypeFlag_t ParserSBGC32_GetVarFlag (ui8 value)
{
	return (sbgcVarTypeFlag_t)(value & 0b11110000);
}
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								  Select IMU 3 Flags
 */
/**	@addtogroup	IMU_Select_3
 *	@{
 */
/**	@note	sbgcDebugVar_t.varType
 */
typedef enum
{
	SIMUA_SIMPLE_SELECT				= 0,
	SIMUA_REGULAR_CALIBRATION		= 1,
	SIMUA_RESET_ALL_CALIB_AND_RESTART
									= 2,
	SIMUA_TEMPERATURE_CALIBRATION	= 3,
	SIMUA_ENABLE_TEMP_CALIB_DATA_IF_PRESENT
									= 4,
	SIMUA_DISABLE_TEMP_CALIB_DATA	= 5,
	SIMUA_RESTORE_FACTORY_CALIB		= 6,
	SIMUA_COPY_CALIB_FROM_MAIN_EEPROM
									= 7

}	sbgcSelectIMU_Action_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						   Control Quat Status Flags
 */
/**	@addtogroup	Control_Quat_Status
 *	@{
 */
/**	@note	@ref SBGC32_ControlQuatStatus, 3 arg
 */
typedef enum
{
	CQSF_MODE_AND_FLAGS				= BIT_0_SET,
	CQSF_TARGET_ATTITUDE			= BIT_1_SET,
	CQSF_SETPOINT_ATTITUDE			= BIT_2_SET,
	CQSF_ACTUAL_ATTITUDE			= BIT_3_SET,
	CQSF_TARGET_SPEED				= BIT_4_SET,
	CQSF_SETPOINT_SPEED				= BIT_5_SET,
	CQSF_ACTUAL_SPEED				= BIT_6_SET,
	CQSF_TARGET_ATTITUDE_PACKED		= BIT_7_SET,
	CQSF_SETPOINT_ATTITUDE_PACKED	= BIT_8_SET,
	CQSF_ACTUAL_ATTITUDE_PACKED		= BIT_9_SET

}	sbgcControlQuatStatusFlag_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *					  Data Stream Interval Structure
 */
/**	@addtogroup	Data_Stream_Interval Data Stream Interval
 *	@{
 */
/**	@brief	Structure type for work with
 *			Event parameters
 *
 *	@ref	SBGC32_StartDataStream function\n
 *	@ref	SBGC32_ReadDataStream function
 */
typedef struct PACKED__
{
	ui8		eventID,								/*!<  See @ref sbgcEventID_t enumeration											*/
			eventType;								/*!<  See @ref sbgcEventType_t enumeration											*/

	ui8		param [2];								/*!<  Possible value and its meaning depends on the eventID & eventType parameters	*/
	/* This command may be expanded by extra
	   parameters in future versions... */
}			sbgcEvent_t;


/**	@brief	Structure type for work with
 *			CAN_Driver telemetry
 *
 *	@ref	SBGC32_StartDataStream function\n
 *	@ref	SBGC32_ReadDataStream function
 */
typedef struct PACKED__
{
	ui8		drvID;									/*!<  0 --> 6. Driver ID sending the telemetry										*/
	ui16	timestampMs;							/*!<  System local time in milliseconds												*/
	void	*data;									/*!<  Depends on the 'flags' parameter of the request, where bits 0..31 defines
														  the variables to be sent in response. Initialized manually by user. See
														  @ref sbgcCAN_DriverTelemetryFlag_t enumeration.
														  Also for more, see the CMD_CAN_DRV_TELEMETRY command in the
														  <a href=https://www.basecamelectronics.com/serialapi/>
														  SimpleBGC32 Serial API protocol specification</a>								*/

}			sbgcCAN_DrvTelemetry_t;


/**	@brief	Structure type for work with
 *			DataStreamInterval parameters
 *
 *	@ref	SBGC32_StartDataStream function
 */
typedef struct PACKED__
{
	ui8		cmdID;									/*!<  See @ref sbgcDataStreamCommand_t enumeration									*/
	ui16	intervalMs;								/*!<  Depends on the syncToData parameter.
														  If syncToData = STD_SYNC_ON, this parameter will specify the sample rate
														  divider. For example: syncToData = STD_SYNC_ON, intervalMs = 125, required
														  data update frequency = 125 Hz. In total data will be sent 1 time per second.
														  Else if syncToData = STD_SYNC_OFF the data will be sent with intervalMs
														  period. However, if intervalMs = 1, this is automatically equal to 0.8 ms.	*/
	ui8		config [8];								/*!<  Configuration specific to each command, depends on the cmdID parameter.
														  Learn more at SerialAPI protocol specification								*/
	ui8		syncToData;								/*!<  See @ref sbgcSyncToData_t enumeration. Frw. ver. 2.70b1+						*/
	ui8		reserved [9];

}			sbgcDataStreamInterval_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t dataStreamIntervalReferenceInfoArray [];
	extern const ui8 dataStreamIntervalReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *					  Realtime Data Custom Structure
 */
/**	@addtogroup	Realtime_Data_Custom
 *	@{
 */
/**	@brief	Part of sbgcSystemPowerState_t structure
 *
 *	@note	sbgcSystemPowerState_t.AxisMPS
 */
typedef struct PACKED__
{
	i16		motorPower;								/*!<  -10000 --> 10000. Effective power that produces torque, 10000 for 100%		*/
	ui16	motorCurrent;							/*!<  0 --> 65535. Units: mA. Estimated or measured current consumption per motor	*/
	i8		motorTemp;								/*!<  Motor temperature estimated by heating model (if configured) or
														  measured by the hardware sensors (if present)									*/
	ui16	motorFlags;								/*!<  See @ref sbgcMotorFlag_t enumeration											*/
	ui8		reserved [6];

}			sbgcAxisMPS_t;

/**	@brief	Type of structure provides the
 *			system power information
 */
typedef struct PACKED__
{
	sbgcAxisMPS_t	AxisMPS [3];					/*!<  ROLL : PITCH : YAW															*/

	i8		systemPowerState;						/*!<  See @ref sbgcSystemPowerStateGeneral_t enumeration							*/
	ui16	batteryVoltage;							/*!<  Units: 0.01 V. Voltage measured by the hardware voltage sensor				*/
	ui16	totalCurrent;							/*!<  0 --> 65535. Units: mA. Overall system current consumption measured
														  by the hardware current sensor (if present)									*/
	ui16	systemFlags;							/*!<  See @ref sbgcMotorSystemFlags_t enumeration									*/

}			sbgcSystemPowerState_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t systemPowerStateReferenceInfoArray [];
	extern const ui8 systemPowerStateReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif


/**	@brief	Type of structure provides the system
 *			communication errors information
 *
 *	@note	Part of sbgcRealTimeDataCustom_t
 *			structure
 */
typedef struct PACKED__
{
	ui16	I2C_Errors,								/*!<  System errors according to the I2C protocol									*/
			serialErrors,							/*!<  SerialAPI protocol communication errors										*/
			CAN_Errors;								/*!<  Communication errors according to the CAN protocol							*/

	ui8		CAN_ErrFlags;							/*!<  See @ref sbgcCAN_ErrFlag_t enumeration										*/

}			sbgcCommunicationErrors_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t communicationErrorsReferenceInfoArray [];
	extern const ui8 communicationErrorsReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif


/**	@brief	Structure reference for work with
 *			RealTimeDataCustom parameters
 *
 *	@note	Deprecated implementation.\n
 *			Use this structure type as a reference
 *			for filling a custom real-time data
 *			structure
 *
 *	@ref	SBGC32_RequestRealTimeDataCustom function
 */
typedef struct
{
	/* Sent parameters */
	ui32	flags;									/*!<  See @ref sbgcRealTimeDataCustomFlag_t enumeration								*/

	/* Received parameters */
	ui16	timestampMs;							/*!<  Units: ms. Received in the packet every time regardless of flags				*/

	/* The followed data is regulated
	   by the 'flags' field */
	i16		IMU_Angles [3],							/*!<  Units: 0.02197265625 degree. Main IMU angles (Euler). Use the
														  @ref sbgcDegreeToAngle macro to obtain this data conveniently					*/
			targetAngles [3],						/*!<  Units: 0.02197265625 degree. Target angles that gimbal should keep (Euler).
														  Use the @ref sbgcDegreeToAngle macro to obtain this data conveniently			*/
			targetSpeed [3],						/*!<  Units: 0.06103701895 degree/sec. Target speed that gimbal should keep (Euler)	*/
			frameCamAngle [3],						/*!<  Units: 0.02197265625 degree. Relative angle of joints (motors). Use the
														  @ref sbgcDegreeToAngle macro to obtain this data conveniently					*/
			gyroData [3],							/*!<  Units: 0.06103701895 degree/sec. Data from the gyroscope sensor				*/
			RC_Data [6];							/*!<  -16384 --> 16384. Value -32768 is for 'undefined' signal						*/

	float	Z_Vector [3],							/*!<  ...																			*/
			H_Vector [3];							/*!<  ...-1.0f --> 1.0f																*/

	i16		RC_Channels [18];						/*!<  -16384 --> 16384. Value -32768 is for 'undefined' signal						*/
	i16		accData [3];							/*!<  Units: 1/512 G																*/

	sbgcMotor4_Control_t	Motor4_Control;			/*!<  See @ref sbgcMotor4_Control_t structure type									*/
	sbgcAHRS_DebugInfo_t	AHRS_DebugInfo;			/*!<  See @ref sbgcAHRS_DebugInfo_t structure type									*/

	ui8		encoderRaw24 [3][3];					/*!<  3 bytes for each encoder in a sequence for
														  ROLL, PITCH, YAW motors, lower byte first. Frw. ver. 2.68+					*/
	float	IMU_AnglesRad [3];						/*!<  Main IMU Euler angles in radians. Frw. ver. 2.68b7+							*/

	float	scriptVarsFloat [10];					/*!<  Script variables in floats													*/
	i16		scriptVarsInt16 [10];					/*!<  Script variables in 16-byte signed integers									*/

	sbgcSystemPowerState_t	SystemPowerState;		/*!<  Information about the system power and motors. Frw. ver. 2.70b6+				*/

	i16		frameCamRate [3];						/*!<  Units: 0.06103701895 degree/sec. Rate of rotation of frame-to-camera
														  joints (motors) Frw. ver. 2.70b6+												*/
	i32		IMU_Angles20 [3],						/*!<  Units: 0.00034332275390625 degrees. Main IMU angles in 20bit resolution.
														  Frw. ver. 2.70b8+																*/
			targetAngles20 [3];						/*!<  Units: 0.00034332275390625 degrees. Target angles in 20bit resolution.
														  Frw. ver. 2.70b8+																*/
	sbgcCommunicationErrors_t
					CommunicationErrors;			/*!<  System communication errors information. Frw. ver. 2.72b0+					*/

	ui32	systemStateFlags;						/*!<  See @ref sbgcStateFlag_t enumeration. Frw. ver. 2.73+							*/

}			sbgcRealTimeDataCustomReference_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *					 Realtime Data 3 (-4) Structures
 */
/**	@addtogroup	Realtime_Data_3_4
 *	@{
 */
/**	@brief	Part of sbgcRealTimeData_t structure
 *
 *	@note	sbgcRealTimeData_t.AxisRTD
 */
typedef struct PACKED__
{
	i16		accData;								/*!<  Units: 1/512 G																*/
	i16		gyroData;								/*!<  Units: 0.06103701895 degree/sec												*/

}			sbgcAxisRTD_t;

/**	@brief	Structure type for work with
 *			RealTimeData3 (-4) parameters
 *
 *	@ref	SBGC32_ReadRealTimeData3 function\n
 *	@ref	SBGC32_ReadRealTimeData4 function
 */
typedef struct PACKED__
{
	sbgcAxisRTD_t	AxisRTD [3];					/*!<  ROLL : PITCH : YAW															*/

	ui16	serialErrCnt;							/*!<  0 --> 65535																	*/
	ui16	systemError;							/*!<  See @ref sbgcSystemError_t enumeration										*/
	ui8		systemSubError;							/*!<  See @ref sbgcSystemSubError_t enumeration										*/
	ui8		reserved [3];

	i16		RC_ROLL,								/*!<  ...																			*/
			RC_PITCH,								/*!<  ...																			*/
			RC_YAW,									/*!<  ...RC control channels values (PWM or normalized analog)						*/

			RC_Cmd,									/*!<  1000 --> 2000. RC command channel value (PWM or normalized analog)			*/

			extFC_ROLL,								/*!<  ...																			*/
			extFC_PITCH;							/*!<  ...1000 --> 2000. External FC PWM values. May be zero if their inputs are
														  mapped to RC control or command												*/

	i16		IMU_Angle [3];							/*!<  ...																			*/
	i16		frameIMU_Angle [3];						/*!<  ...																			*/
	i16		targetAngle [3];						/*!<  ...-32768 --> 32767. Units: 0.02197265625 degree. Use the
														  @ref sbgcDegreeToAngle macro to obtain this data conveniently					*/

	ui16	cycleTime;								/*!<  Units: ms																		*/
	ui16	I2C_ErrorCount;							/*!<  Number of registered errors on I2C bus										*/
	ui8		errorCode;								/*!<  Deprecated, replaced by the SYSTEM_ERROR variable								*/
	ui16	batLevel;								/*!<  Units: 0.01 volt																*/
	ui8		RT_DataFlags;							/*!<  See @ref sbgcRT_DataFlag_t enumeration										*/
	ui8		curIMU;									/*!<  See @ref sbgcIMU_Type_t enumeration											*/
	ui8		curProfile;								/*!<  See @ref sbgcProfile_t enumeration											*/
	ui8		motorPower [3];							/*!<  0 --> 255																		*/

	/* Realtime Data 4 */
	i16		frameCamAngle [3];						/*!<  Units: 0.02197265625 degree. Use the @ref sbgcDegreeToAngle macro
														  to obtain this data conveniently												*/
	ui8		reserved1;
	i16		balanceError [3];						/*!<  -512 --> 512. Error in balance												*/
	ui16	current;								/*!<  Units: mA																		*/
	i16		magData [3];							/*!<  -1000 --> 1000 (Units: relative, calibrated for
														  current environment for each axis)											*/
	i8		IMU_Temperature,						/*!<  ...																			*/
			frameIMU_Temperature;					/*!<  ...-127 --> 127. Units: Celsius												*/

	ui8		IMU_G_Err,								/*!<  ...																			*/
			IMU_H_Err;								/*!<  ...0 --> 255. Units: 0.1 degree												*/

	i16		motorOut [3];							/*!<  -10000 --> 10000. Encoder firmware ver. 2.61+									*/
	ui8		calibMode;								/*!<  See @ref sbgcCalibMode_t enumeration											*/
	ui8		CAN_IMU_ExtSensErr;						/*!<  Error code from the external sensor connected to the CAN_IMU					*/

	i16		actualAngle [3];						/*!<  Depending on the current stabilization mode: for inertial angles it's the
														  same as IMU_Angle[3]. for motor-related modes (“Servo mode”, mixed
														  inertial + motor having (M) notation), it encodes the motor angle				*/
	ui32	systemStateFlags;						/*!<  See @ref sbgcStateFlag_t enumeration. Frw. ver. 2.73+							*/

	ui8		reserved2 [18];

}			sbgcRealTimeData_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t realTimeDataReferenceInfoArray [];
	extern const ui8 realTimeDataReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							   Get Angles Structures
 */
/**	@addtogroup	Get_Angles
 *	@{
 */
/**	@brief	Part of sbgcGetAngles_t structure
 *
 *	@note	sbgcGetAngles_t.AxisGA
 */
typedef struct PACKED__
{
	i16		IMU_Angle,								/*!<  ...																			*/
			targetAngle,							/*!<  ...Units: 0.02197265625 degree. Use the @ref sbgcDegreeToAngle macro
														  to obtain this data conveniently												*/

			targetSpeed;							/*!<  Units: 0.1220740379 degree/sec. Use the @ref sbgcValueToSpeed macro
														  to obtain this data conveniently												*/

}			sbgcAxisGA_t;

/**	@brief	Structure type for work with
 *			GetAngles parameters
 *
 *	@ref	SBGC32_GetAngles function
 */
typedef struct PACKED__
{
	sbgcAxisGA_t	AxisGA [3];						/*!<  ROLL : PITCH : YAW															*/

}	sbgcGetAngles_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t getAnglesReferenceInfoArray [];
	extern const ui8 getAnglesReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif


/**	@brief	Part of sbgcGetAnglesExt_t structure
 *
 *	@note	sbgcGetAnglesExt_t.AxisGAE
 */
typedef struct PACKED__
{
	i16		IMU_Angle;								/*!<  ...																			*/
	i16		targetAngle;							/*!<  ...																			*/
	i32		frameCamAngle;							/*!<  ...Units: 0.02197265625 degree. Use the @ref sbgcDegreeToAngle macro
														  to obtain this data conveniently												*/

	ui8		reserved [10];

}			sbgcAxisGAE_t;

/**	@brief	Structure type for work with
 *			GetAnglesExt parameters
 *
 *	@ref	SBGC32_GetAnglesExt function
 */
typedef struct PACKED__
{
	sbgcAxisGAE_t	AxisGAE [3];					/*!<  ROLL : PITCH : YAW															*/

}	sbgcGetAnglesExt_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t getAnglesExtReferenceInfoArray [];
	extern const ui8 getAnglesExtReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								 RC Inputs Structure
 */
/**	@addtogroup	RC_Inputs
 *	@{
 */
/**	@brief	Structure type for work with
 *			RC_Inputs parameters
 *
 *	@ref	SBGC32_ReadRC_Inputs function
 */
typedef struct
{
	i16		RC_Val;									/*!<  Values for each RC source														*/
	ui8		RC_Src;									/*!<  See @ref sbgcRC_MapSourceType_t and @ref sbgcRC_MapSource_t enumerations		*/

}			sbgcRC_Inputs_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							   Debug Var 3 Structure
 */
/**	@addtogroup	Debug_Var_3
 *	@{
 */
/**	@brief	Structure type for work with
 *			DebugVars3 parameters. Also part of
 *			@ref sbgcDebugVars3_t structure
 *
 *	@note	sbgcDebugVars3_t.debugVar3_Info
 *
 *	@ref	SBGC32_RequestDebugVarInfo3 function
 */
typedef struct
{
	ui8				nameLength;						/*!<  This is a 1st byte from varName parameter										*/
	char			*name;							/*!<  This is a string that doesn't end with '\0'. Initialized manually by user		*/
	sbgcVarType_t	type;							/*!<  See @ref sbgcVarType_t and @ref sbgcVarTypeFlag_t enumerations				*/

	ui32			value;							/*!<  Read-only																		*/

}	sbgcDebugVar3_Info_t;

/**	@brief	Structure type for work with
 *			DebugVars3 parameters
 *
 *	@ref	SBGC32_RequestDebugVarValue3 function
 */
typedef struct
{
	sbgcDebugVar3_Info_t	*debugVar3_Info;		/*!<  Initialized manually by user													*/

	ui32					*mask;					/*!<  Asks to send only the selected variables. Initialized manually by user.
														  Must be NULL to don't use the masks. Each bit in the mask corresponds to
														  the index of the variable as it goes in CMD_DEBUG_VARS_INFO_3, starting
														  from 0. If the total number of variables exceeds 32, several masks
														  should be used - last_idx / 32 + 1. Frw. ver. 2.72b0+							*/
	ui8						maskQuan;				/*!<  Should match the current number of variable masks. Frw. ver. 2.72b0+			*/

}	sbgcDebugVars3_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *					   Control Quat Status Structure
 */
/**	@addtogroup	Control_Quat_Status
 *	@{
 */
/**	@brief	Structure reference for work with
 *			ControlQuatStatus parameters
 *
 *	@note	Use this structure type as a reference
 *			for filling a custom control
 *			quaternions status structure
 *
 *	@ref	SBGC32_ControlQuatStatus function
 */
typedef struct
{
	ui8		mode;									/*!<  See @ref sbgcControlQuatMode_t enumeration									*/
	ui16	flags;									/*!<  See @ref sbgcControlQuatFlag_t enumeration									*/

	float	targetAttitude [4],						/*!<  Externally commanded attitude as a target for a motion plan					*/
			setPointAttitude [4],					/*!<  Attitude currently set as a setpoint that gimbal stabilizes					*/
			actualAttitude [4];						/*!<  Attitude currently measured by the IMU										*/

	i16		targetSpeed [3],						/*!<  Externally commanded speed as a target for a motion plan						*/
			setPointSpeed [3],						/*!<  Current speed setpoint that gimbal stabilizes									*/
			actualSpeed [3];						/*!<  Actual speed measured by the IMU gyroscope sensor								*/

	ui8		targetAttitudePacket [8],				/*!<  ...																			*/
			setPointAttitudePacket [8],				/*!<  ...																			*/
			actualAttitudePacket [8];				/*!<  ...A packed version of corresponding variables. See Appendix F in the
														  <a href=https://www.basecamelectronics.com/serialapi/>
														  SimpleBGC32 Serial API protocol specification</a> for format description		*/

}	sbgcControlQuatStatusReference_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *					  Function Prototypes and Inline
 */
/**	@addtogroup	Data_Stream_Interval
 *	@{
 */
/**	@brief	Fills sbgcDataStreamInterval_t.config field
 *
 *	@param	*dataStreamInterval - data stream structure
 *	@param	flags - realtime data custom parameter. See
 *			@ref sbgcRealTimeDataCustomFlag_t enumeration
 */
static inline void ParserSBGC32_RTDC_FlagsToStream (sbgcDataStreamInterval_t *dataStreamInterval, ui32 flags)
{
	memcpy(dataStreamInterval->config, &flags, sizeof(flags));
}

/**	@brief	Helps to fill sbgcDataStreamInterval_t.config field
 *
 *	@param	*dataStreamInterval - data stream structure
 *	@param	type - type of the IMU sensor
 */
static inline void ParserSBGC32_AHRSH_IMU_TypeToStream (sbgcDataStreamInterval_t *dataStreamInterval, sbgcIMU_Type_t type)
{
	dataStreamInterval->config[0] = type;
}

/**	@brief	Fills sbgcDataStreamInterval_t.config field
 *
 *	@param	*dataStreamInterval - data stream structure
 *	@param	ID - one of the event IDs
 *	@param	type - bitwise combination of the event type
 */
static inline void ParserSBGC32_EventID_AndTypeToStream (sbgcDataStreamInterval_t *dataStreamInterval, sbgcEventID_t ID, sbgcEventType_t type)
{
	dataStreamInterval->config[0] = ID;
	dataStreamInterval->config[1] = type;
}

/**	@brief	Fills sbgcDataStreamInterval_t.config field
 *
 *	@param	*dataStreamInterval - data stream structure
 *	@param	flags - CAN_Driver telemetry flags. See
 *			@ref sbgcCAN_DriverTelemetryFlag_t enumeration
 *	@param	ID - CAN_Driver identifier
 */
static inline void ParserSBGC32_CAN_DT_FlagsAndID_ToStream (sbgcDataStreamInterval_t *dataStreamInterval, ui32 flags, sbgcExtMotorID_t ID)
{
	memcpy(dataStreamInterval->config, &flags, sizeof(flags));
	dataStreamInterval->config[4] = ID;
}

/**	@brief	Fills sbgcDataStreamInterval_t.config field
 *
 *	@param	*dataStreamInterval - data stream structure
 *	@param	ID - motor ID bit
 *	@param	dataSet - requested motor data flags. See
 *			@ref sbgcMotorsStateDataSet_t enumeration
 */
static inline void ParserSBGC32_EMS_ID_AndSetToStream (sbgcDataStreamInterval_t *dataStreamInterval, ui8 ID, ui32 dataSet)
{
	dataStreamInterval->config[0] = ID;
	memcpy(dataStreamInterval->config + sizeof(ID), &dataSet, sizeof(dataSet));
}


/**	@cond
 */
sbgcCommandStatus_t SBGC32_StartDataStream (sbgcGeneral_t *gSBGC, const sbgcDataStreamInterval_t *dataStreamInterval, sbgcConfirm_t *confirm
											SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_StopDataStream (sbgcGeneral_t *gSBGC, sbgcDataStreamInterval_t *dataStreamInterval, sbgcConfirm_t *confirm
										   SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ReadDataStream (sbgcGeneral_t *gSBGC, sbgcDataStreamCommand_t cmdID, void *dataStreamStruct, ui8 size
										   SBGC_ADVANCED_PARAMS__);
/**	@endcond
 */
/**	@}
 */


/**	@cond
 */
/**	@addtogroup	Realtime_Data_Custom
 *	@{
 */
sbgcCommandStatus_t SBGC32_RequestRealTimeDataCustom (sbgcGeneral_t *gSBGC, void *realTimeDataCustom, ui8 size SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Realtime_Data_3_4
 *	@{
 */
sbgcCommandStatus_t SBGC32_ReadRealTimeData3 (sbgcGeneral_t *gSBGC, sbgcRealTimeData_t *realTimeData SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ReadRealTimeData4 (sbgcGeneral_t *gSBGC, sbgcRealTimeData_t *realTimeData SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Get_Angles
 *	@{
 */
sbgcCommandStatus_t SBGC32_GetAngles (sbgcGeneral_t *gSBGC, sbgcGetAngles_t *getAngles SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_GetAnglesExt (sbgcGeneral_t *gSBGC, sbgcGetAnglesExt_t *getAnglesExt SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	RC_Inputs
 *	@{
 */
sbgcCommandStatus_t SBGC32_ReadRC_Inputs (sbgcGeneral_t *gSBGC, sbgcRC_Inputs_t *RC_Inputs, sbgcInitCfgFlag_t cfgFlags, ui8 srcQuan
										  SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Debug_Var_3
 *	@{
 */
sbgcCommandStatus_t SBGC32_RequestDebugVarInfo3 (sbgcGeneral_t *gSBGC, sbgcDebugVar3_Info_t *debugVar3_Info, ui8 startIndex, ui8 varQuan
												 SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_RequestDebugVarValue3 (sbgcGeneral_t *gSBGC, sbgcDebugVars3_t *debugVars3 SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	IMU_Select_3
 *	@{
 */
sbgcCommandStatus_t SBGC32_SelectIMU_3 (sbgcGeneral_t *gSBGC, sbgcIMU_Type_t IMU_Type, sbgcSelectIMU_Action_t action, ui16 timeMs,
										sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
/**	@}
 */
/**	@addtogroup	Control_Quat_Status
 *	@{
 */
sbgcCommandStatus_t SBGC32_ControlQuatStatus (sbgcGeneral_t *gSBGC, sbgcControlQuatStatusFlag_t flags, void *data, ui8 size SBGC_ADVANCED_PARAMS__);
/**	@}
 */
/**	@endcond
 */

#endif /* SBGC_REALTIME_MODULE */


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

#endif		/* MODULES_REALTIME_H_ */
