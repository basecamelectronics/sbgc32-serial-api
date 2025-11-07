/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2.1
 *
 *	@file		imu.h
 *
 *	@brief		IMU header file
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
 *	@defgroup	IMU SBGC32 IMU
 *	@ingroup	Modules
 *		@brief	SBGC32 IMU Title Module
 *	____________________________________________________________________
 *
 *	@defgroup	Ext_IMU_Debug_Info External IMU Debug Information
 *	@ingroup	IMU
 *		@brief	External IMU Debug Information Module
 *
 *				Covered Commands:
 *
 *				### CMD_EXT_IMU_DEBUG_INFO
 *
 *	@defgroup	Ext_IMU_Cmd External IMU Commands
 *	@ingroup	IMU
 *		@brief	External IMU Commands Module
 *
 *				Covered Commands:
 *
 *				### CMD_EXT_IMU_CMD
 *				### CMD_EXT_SENS_CMD
 *
 *	@defgroup	Gyro_Correction Gyroscope Correction
 *	@ingroup	IMU
 *		@brief	Gyroscope Correction Module
 *
 *				Covered Commands:
 *
 *				### CMD_GYRO_CORRECTION
 *
 *	@defgroup	AHRS_Helper AHRS Helper
 *	@ingroup	IMU
 *		@brief	AHRS Helper Module
 *
 *				Covered Commands:
 *
 *				### CMD_AHRS_HELPER
 *
 *	@defgroup	Helper_Data Helper Data
 *	@ingroup	IMU
 *		@brief	Helper Data Module
 *
 *				Covered Commands:
 *
 *				### CMD_HELPER_DATA
 *	____________________________________________________________________
 */

#ifndef		MODULES_IMU_H_
#define		MODULES_IMU_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../sbgc32.h"


#if (SBGC_IMU_MODULE)

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								   Ext IMU Cmd Flags
 */
/**	@addtogroup	Ext_IMU_Cmd
 *	@{
 */
/**	@note	sbgcExtIMU_Command_t.commandID
 */
typedef enum
{
	IMU_CMD_CONFIRM					= 1,			/*!<  RX <-- Confirmation of previous command or finished calibration				*/
	IMU_CMD_RESET					= 2,			/*!<  TX --> Reset device															*/
	IMU_CMD_RESET_NOTIFY			= 3,			/*!<  RX <-- Notification on device reset											*/
	IMU_CMD_GET_DEVICE_INFO			= 4,			/*!<  TX --> Request board and firmware information									*/
	IMU_CMD_DEVICE_INFO				= 5,			/*!<  RX <-- Board and firmware information											*/
	IMU_CMD_GET_DATA				= 6,			/*!<  TX --> Request configurable realtime data										*/
	IMU_CMD_GET_DATA_STREAM			= 7,			/*!<  TX --> Register or update data stream											*/
	IMU_CMD_DATA					= 8,			/*!<  RX <-- Configurable realtime data												*/
	IMU_CMD_CALIB					= 9,			/*!<  TX --> Calibration of the built-in sensors									*/
	IMU_CMD_BOOT_MODE				= 10,			/*!<  TX --> Enter firmware update mode (STM32 hardware loader)						*/
	IMU_CMD_USER_DATA_LOG			= 11,			/*!<  TX --> Contains data for logging to SD										*/
	IMU_CMD_GET_USER_CONF_LOG		= 12,			/*!<  TX --> Request configuration of user data log									*/
	IMU_CMD_USER_CONF_LOG			= 13			/*!<  RX <-- Configuration of user data log											*/

}	sbgcExtIMU_CommandID_t;


/**	@note	@ref SBGC32_SendCmdToExtIMU, 3 arg
 *			@ref SBGC32_SendCmdToExtSens, 4 arg
 */
typedef enum
{
	EXT_IMU_CMD_TYPE_TX				= 0,
	EXT_IMU_CMD_TYPE_RX,
	EXT_IMU_CMD_TYPE_TX_RX

}	sbgcExtIMU_CommandType_t;


/**	@note	@ref SBGC32_SendCmdToExtSens, 3 arg
 */
typedef enum
{
	EXT_SENS_CMD_LOW_PRIOR			= 0,
	EXT_SENS_CMD_HIGH_PRIOR			= BIT_0_SET

}	sbgcExtSensCommandFlag_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								   AHRS Helper Flags
 */
/**	@addtogroup	AHRS_Helper
 *	@{
 */
/**	@note	@ref SBGC32_CallAHRS_Helper, 3 arg
 */
typedef enum
{
	AHRSHMD_GET						= 0,
	AHRSHMD_SET						= BIT_0_SET

}	sbgcAHRS_HelperModeDir_t;

/**	@note	@ref SBGC32_CallAHRS_Helper, 3 arg
 */
typedef enum
{
	AHRSHML_CAMERA_PLATFORM			= 0,
	AHRSHML_FRAME					= BIT_1_SET

}	sbgcAHRS_HelperModeLoc_t;

/**	@note	@ref SBGC32_CallAHRS_Helper, 3 arg
 */
typedef enum
{
	AHRSHMC_BOTH_VECTORS			= 0,
	AHRSHMC_Z_VECTOR				= BIT_4_SET,
	AHRSHMC_H_VECTOR				= BIT_5_SET,

}	sbgcAHRS_HelperModeCorr_t;

/**	@note	@ref SBGC32_CallAHRS_Helper, 3 arg
 *
 *	@attention	Firmware: 2.69b5+
 */
typedef enum
{
	AHRSHMT_TRANSLATE_BOTH_VECTORS	= 0,
	AHRSHMT_TRANSLATE_Z_VECTOR		= BIT_6_SET,
	AHRSHMT_TRANSLATE_H_VECTOR		= BIT_7_SET

}	sbgcAHRS_HelperModeTr_t;

/**	@note	@ref SBGC32_CallAHRS_Helper, 3 arg
 *
 *	@attention	Firmware: 2.69b5+\n
 *				only for 2-byte mode
 */
typedef enum
{
	AHRSHMR_SAME_AS_FRAME_IMU		= 0,
	AHRSHMR_ON_THE_FRAME			= BIT_8_SET,
	AHRSHMR_BELOW_OUTER				= BIT_9_SET

}	sbgcAHRS_HelperModeRef_t;

/**	@note	@ref SBGC32_CallAHRS_Helper, 3 arg
 */
typedef enum
{
	AHRSHMO_NO_ANOTHER_FLAGS		= 0,

	AHRSHMO_USE_AS_REFERENCE_ONLY	= BIT_2_SET,
	AHRSHMO_TRANSLATE_FROM_CAMERA_TO_FRAME
									= BIT_3_SET,
	/* frw.ver. 2.70b1+ */
	AHRSHMO_DISABLE_INTERNAL_CORRECTION
									= BIT_10_SET

}	sbgcAHRS_HelperModeOther_t;

/**	@brief	Used as a function of joining
 *			AHRS helper modes
 *
 *	@param	direction - clean value of AHRS helper direction
 *	@param	location - clean value of AHRS helper location
 *	@param	correction - clean value of AHRS helper correction
 *	@param	translate - clean value of AHRS helper translate
 *	@param	reference - clean value of AHRS helper reference
 *	@param	other - clean value of AHRS helper other flags
 *
 *	@return	Packed value for 3rd parameter of the
 *			@ref SBGC32_CallAHRS_Helper function
 */
static inline ui16 ParserSBGC32_PackAHRS_HelperMode (sbgcAHRS_HelperModeDir_t direction, sbgcAHRS_HelperModeLoc_t location,
													 sbgcAHRS_HelperModeCorr_t correction, sbgcAHRS_HelperModeTr_t translate,
													 sbgcAHRS_HelperModeRef_t reference, sbgcAHRS_HelperModeOther_t other)
{
	return (ui16)direction | ((location << 1) & (ui16)0b00000010) | ((correction << 4) & (ui16)0b00110000) |
		   ((translate << 6) & (ui16)0b11000000) | ((reference << 8) & 0b0000001100000000) | other;
}
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								   Helper Data Flags
 */
/**	@addtogroup	Helper_Data
 *	@{
 */
/**	@note	sbgcHelperData_t.flags
 */
typedef enum
{
	HDF_COORD_SYS_GROUND_YAW_ROTATED
									= 1,
	HDF_COORD_SYS_GROUND			= 2,
	HDF_COORD_SYS_FRAME				= 3,
	/** frw. ver. 2.70b7+ */
	HDF_COMPUTED_IN_EULER_ORDER		= BIT_6_SET,
	/** frw. ver. 2.62b7+ */
	HDF_FRAME_HEADING				= BIT_7_SET

}	sbgcHelperDataFlag_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						Ext IMU Debug Info Structure
 */
/**	@addtogroup	Ext_IMU_Debug_Info
 *	@{
 */
/**	@brief	Structure type for work with
 *			ExtIMU_DebugInfo parameters
 *
 *	@ref	SBGC32_RequestExtIMU_DebugInfo function
 */
typedef struct PACKED__
{
	sbgcAHRS_DebugInfo_t	AHRS_DebugInfo;			/*!<  See @ref sbgcAHRS_DebugInfo_t structure										*/
	float					DCM [9];				/*!<  -1.0f --> 1.0f																*/
	float					accBody [3];			/*!<  Linear acceleration in sensor's local coordinates								*/

}	sbgcExtIMU_DebugInfo_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t extIMU_DebugInfoReferenceInfoArray [];
	extern const ui8 extIMU_DebugInfoReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							   Ext IMU Cmd Structure
 */
/**	@addtogroup	Ext_IMU_Cmd
 *	@{
 */
/**	@brief	Structure type for work with
 *			external IMU serial commands
 *
 *	@ref	SBGC32_SendCmdToExtIMU function\n
 *	@ref	SBGC32_SendCmdToExtSens function
 */
typedef struct
{
	sbgcExtIMU_CommandID_t	commandID;				/*!<  SerialAPI identifier of the serial command.
														  See @ref sbgcExtIMU_CommandID_t enumeration									*/
	ui8						payloadSize;			/*!<  Payload size of the serial command											*/
	ui8						*payload;				/*!<  Serial command's payload buffer. Initialized manually by user. It's
														  recommended to allocate @ref SBGC_MAX_PAYLOAD_SIZE (255) bytes
														  of space for this buffer														*/

}	sbgcExtIMU_Command_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						   Gyro Correction Structure
 */
/**	@addtogroup	Gyro_Correction
 *	@{
 */
/**	@brief	Structure type for work with
 *			GyroCorrection parameters
 *
 *	@ref	SBGC32_CorrectionGyro function
 */
typedef struct PACKED__
{
	ui8		IMU_Type;								/*!<  0 – main IMU, 1 – frame IMU. Also use @ref sbgcIMU_Type_t enumeration,
														  decreasing its values by 1													*/
	i16		gyroZeroCorr [3];						/*!<  Units: 0.001 gyro sensor unit													*/
	i16		gyroZeroHeadingCorr;					/*!<  Units: 0.001 gyro sensor unit													*/

}	sbgcGyroCorrection_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t gyroCorrectionReferenceInfoArray [];
	extern const ui8 gyroCorrectionReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							   AHRS Helper Structure
 */
/**	@addtogroup	AHRS_Helper
 *	@{
 */
/**	@brief	Structure type for work with
 *			AHRS_Helper parameters
 *
 *	@ref	SBGC32_CallAHRS_Helper function
 */
typedef struct PACKED__
{
	float	Z_Vector [3],							/*!<  -1.0f --> 1.0f. Unit vector that points down in END the coordinate system		*/
			H_Vector [3];							/*!<  -1.0f --> 1.0f. Unit vector that points towards North in
														  the END coordinate system														*/

}	sbgcAHRS_Helper_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t AHRS_HelperReferenceInfoArray [];
	extern const ui8 AHRS_HelperReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							   Helper Data Structure
 */
/**	@addtogroup	Helper_Data
 *	@{
 */
/**	@brief	Structure type for work with
 *			HelperData parameters
 *
 *	@ref	SBGC32_ProvideHelperData function
 */
typedef struct PACKED__
{
	i16		frameAcc [3];							/*!<  Units: 1g/512 ≈ 0.019160156 m/sec²											*/

	i16		frameAngleRoll,							/*!<  ...																			*/
			frameAnglePitch;						/*!<  ...-32768 --> 32767. Inclination of the outer frame in a given coordinate
														  system. Units: 0.02197265625 degree. Pass zero values to not use
														  this information. Use the @ref sbgcAngleToDegree macro to
														  comfortable work with these fields											*/

}	sbgcHelperData_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t helperDataReferenceInfoArray [];
	extern const ui8 helperDataReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif


/**	@brief	Structure type for work with
 *			HelperDataExt parameters
 *
 *	@ref	SBGC32_ProvideHelperDataExt function
 */
typedef struct PACKED__
{
	i16		frameAcc [3];							/*!<  Units: 1g/512 ≈ 0,019160156 m/s²												*/

	i16		frameAngleRoll,							/*!<  ...																			*/
			frameAnglePitch;						/*!<  ...-32768 --> 32767. Inclination of the outer frame in a given coordinate
														  system. Units: 0.02197265625 degree. Pass zero values to not use
														  this information. Use the @ref sbgcAngleToDegree macro to
														  comfortable work with these fields											*/

	/* + Extended format (frw. ver. 2.60+) */
	ui8		flags;									/*!<  See @ref sbgcHelperDataFlag_t enumeration										*/
	i16		frameSpeed [3];							/*!<  Units: 0.06103701895 degree/sec. Frw. ver. 2.62b7+							*/
	i16		frameHeading;							/*!<  -16384 --> 16384. Units: 0.02197265625 degree. Use the @ref sbgcAngleToDegree
														  macro to comfortable work with this field										*/
	ui8		reserved;

}	sbgcHelperDataExt_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t helperDataExtReferenceInfoArray [];
	extern const ui8 helperDataExtReferenceInfoArrayElCnt;
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
/**	@addtogroup	Ext_IMU_Debug_Info
 *	@{
 */
sbgcCommandStatus_t SBGC32_RequestExtIMU_DebugInfo (sbgcGeneral_t *gSBGC, sbgcExtIMU_DebugInfo_t *extIMU_DebugInfo SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Ext_IMU_Cmd
 *	@{
 */
sbgcCommandStatus_t SBGC32_SendCmdToExtIMU (sbgcGeneral_t *gSBGC, sbgcExtIMU_Command_t *cmdToIMU, sbgcExtIMU_CommandType_t cmdType
											SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_SendCmdToExtSens (sbgcGeneral_t *gSBGC, sbgcExtIMU_Command_t *cmdToSens, sbgcExtSensCommandFlag_t flags,
											 sbgcExtIMU_CommandType_t cmdType SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Gyro_Correction
 *	@{
 */
sbgcCommandStatus_t SBGC32_CorrectionGyro (sbgcGeneral_t *gSBGC, const sbgcGyroCorrection_t *gyroCorrection SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	AHRS_Helper
 *	@{
 */
sbgcCommandStatus_t SBGC32_CallAHRS_Helper (sbgcGeneral_t *gSBGC, sbgcAHRS_Helper_t *AHRS_Helper, ui16 mode SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Helper_Data
 *	@{
 */
sbgcCommandStatus_t SBGC32_ProvideHelperData (sbgcGeneral_t *gSBGC, sbgcHelperData_t *helperData SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ProvideHelperDataExt (sbgcGeneral_t *gSBGC, sbgcHelperDataExt_t *helperDataExt SBGC_ADVANCED_PARAMS__);
/**	@}
 */
/**	@endcond
 */

#endif /* SBGC_IMU_MODULE */


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

#endif		/* MODULES_IMU_H_ */
