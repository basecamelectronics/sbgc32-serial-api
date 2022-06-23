/** ____________________________________________________________________
 *
 * 	@file		imu.h
 *
 *	@brief 		IMU header file
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
 * 	@defgroup	IMU SBGC32 IMU
 *	@ingroup	Sources
 *		@brief	SBGC32 IMU Title Module
 *  ____________________________________________________________________
 *
 * 	@defgroup	Ext_IMU_Debug_Info External IMU Debug Information
 * 	@ingroup	IMU
 * 		@brief	External IMU Debug Information Module
 *
 *				Covered Commands:
 *
 *				### CMD_EXT_IMU_DEBUG_INFO
 *
 * 	@defgroup	Ext_IMU_Cmd External IMU Commands
 * 	@ingroup	IMU
 * 		@brief	External IMU Commands Module
 *
 *				Covered Commands:
 *
 *				### CMD_EXT_IMU_CMD
 *
 * 	@defgroup	Gyro_Correction Gyroscope Correction
 * 	@ingroup	IMU
 * 		@brief	Gyroscope Correction Module
 *
 *				Covered Commands:
 *
 *				### CMD_GYRO_CORRECTION
 *
 * 	@defgroup	AHRS_Helper AHRS Helper
 * 	@ingroup	IMU
 * 		@brief	AHRS Helper Module
 *
 *				Covered Commands:
 *
 *				### CMD_AHRS_HELPER
 *
 * 	@defgroup	Helper_Data Helper Data
 * 	@ingroup	IMU
 * 		@brief	Helper Data Module
 *
 *				Covered Commands:
 *
 *				### CMD_HELPER_DATA
 *	____________________________________________________________________
 */

#ifndef		_IMU_H_
#define		_IMU_H_

#ifdef 		__cplusplus
extern 		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include 	"../core/core.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								   Ext IMU Cmd Flags
 */
/**	@addtogroup	Ext_IMU_Cmd
 * 	@{
 */
/**	@note @ref	SBGC32_SendCmdToExtIMU, 3 arg
 */
typedef enum
{
	EXT_IMU_TX,
	EXT_IMU_RX,
	EXT_IMU_TX_RX

}	ExtIMU_CommandType_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								   AHRS Helper Flags
 */
/**	@addtogroup	AHRS_Helper
 * 	@{
 */
/**	@note	AHRS_Helper_t.mode
 */
typedef enum
{
	AHRSHMD_GET						= 0,
	AHRSHMD_SET						= 1

}	AHRS_HelperModeDir_t;

/**	@note	AHRS_Helper_t.mode
 */
typedef enum
{
	AHRSHML_CAMERA_PLATFORM			= 0,
	AHRSHML_FRAME					= 1

}	AHRS_HelperModeLoc_t;

/**	@note	AHRS_Helper_t.mode
 */
typedef enum
{
	AHRSHMC_BOTH_VECTORS			= 0,
	AHRSHMC_Z_VECTOR				= BIT_0_SET,
	AHRSHMC_H_VECTOR				= BIT_1_SET,

}	AHRS_HelperModeCorr_t;

/**	@note	AHRS_Helper_t.mode
 *
 *	@attention	Firmware: 2.69b5+
 */
typedef enum
{
	AHRSHMT_TRANSLATE_BOTH_VECTORS	= 0,
	AHRSHMT_TRANSLATE_Z_VECTOR		= BIT_0_SET,
	AHRSHMT_TRANSLATE_H_VECTOR		= BIT_1_SET

}	AHRS_HelperModeTr_t;

/**	@note	AHRS_Helper_t.mode
 *
 *	@attention	Firmware: 2.69b5+\n
 *				only for 2-byte mode
 */
typedef enum
{
	AHRSHMR_SAME_AS_FRAME_IMU	 	= 0,
	AHRSHMR_ON_THE_FRAME			= BIT_0_SET,
	AHRSHMR_BELOW_OUTER				= BIT_1_SET,

}	AHRS_HelperModeRef_t;

/**	@note	AHRS_Helper_t.mode
 */
typedef enum
{
	AHRSHMO_USE_AS_REFERENCE_ONLY	= BIT_2_SET,
	AHRSHMO_TRANSLATE_FROM_CAMERA_TO_FRAME
									= BIT_3_SET,
	/** frw.ver.2.70b1+ */
	AHRSHMO_DISABLE_INTERNAL_CORRECTION
									= BIT_10_SET

}	AHRS_HelperModeOther_t;

inline ui16 PackAHRS_HelperMode (AHRS_HelperModeDir_t direction,
								 AHRS_HelperModeLoc_t location,
								 AHRS_HelperModeCorr_t correction,
								 AHRS_HelperModeTr_t translate,
								 AHRS_HelperModeRef_t reference,
								 AHRS_HelperModeOther_t other)
{
	return (direction & (ui16)0b00000001) |
		   ((location << 1) & (ui16)0b00000010) |
		   ((correction << 4) & (ui16)0b00110000) |
		   ((translate << 6) & (ui16)0b11000000) |
		   ((reference << 8) & 0b0000001100000000) |
		   other;
}
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								   Helper Data Flags
 */
/**	@addtogroup	Helper_Data
 * 	@{
 */
/**	@note	HelperData_t.flags
 */
typedef enum
{
	HDF_COORD_SYS_GROUND_YAW_ROTATED
									= 1,
	HDF_COORD_SYS_GROUND			= 2,
	HDF_COORD_SYS_FRAME				= 3,
	/** frw. ver. 2.62b7+ */
	HDF_FRAME_HEADING				= BIT_7_SET

}	HelperDataFlags_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						Ext IMU Debug Info Structure
 */
/**	@addtogroup	Ext_IMU_Debug_Info
 * 	@{
 */
/**	@brief	Structure type for work with
 *  		ExtIMU_DebugInfo parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			Firmware: 2.66+
 *
 *			CMD_EXT_IMU_DEBUG_INFO
 *
 *			RX 74 bytes
 *
 *	@ref	SBGC32_RequestExtIMU_DebugInfo function
 */
typedef struct __PACKED__
{
	AHRS_DebugInfo_t 	AHRS_DebugInfo;				/*!<  See @ref AHRS_DebugInfo_t structure											*/
	float				DCM [9];					/*!<  -1.0f --> 1.0f																*/
	float				ACC_Body [3];				/*!<  Linear acceleration in sensor's local coordinates								*/

}			ExtIMU_DebugInfo_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						   Gyro Correction Structure
 */
/**	@addtogroup	Gyro_Correction
 * 	@{
 */
/**	@brief	Structure type for work with
 *  		GyroCorrection parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			CMD_GYRO_CORRECTION
 *
 *			TX 9 bytes
 *
 *	@ref	SBGC32_CorrectionGyro function
 */
typedef struct __PACKED__
{
	ui8		IMU_Type;								/*!<  0 – main IMU, 1 – frame IMU													*/
	i16		gyroZeroCorr [3];						/*!<  Units: 0.001 gyro sensor unit													*/
	i16		gyroZeroHeadingCorr;					/*!<  Units: 0.001 gyro sensor unit													*/

}			GyroCorrection_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							   AHRS Helper Structure
 */
/**	@addtogroup	AHRS_Helper
 * 	@{
 */
/**	@brief	Structure type for work with
 *  		AHRS_Helper parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			CMD_AHRS_HELPER
 *
 *			TX/RX 2/24 bytes
 *
 *			Current attitude in vector form
 *
 *	@ref	SBGC32_CallAHRS_Helper function
 */
typedef struct __PACKED__
{
	ui16 	mode;									/*!<  See @ref AHRS_HelperModeDir_t, @ref AHRS_HelperModeLoc_t,
														  @ref AHRS_HelperModeCorr_t, @ref AHRS_HelperModeTr_t,
														  @ref AHRS_HelperModeRef_t and @ref AHRS_HelperModeOther_t enumerations		*/

	float	Z_Vect [3],								/*!<  -1.0f --> 1.0f. Unit vector that points down in END coordinate system			*/
			H_Vect [3];								/*!<  -1.0f --> 1.0f. Unit vector that points towards North in END coordinate system*/

}			AHRS_Helper_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							   Helper Data Structure
 */
/**	@addtogroup	Helper_Data
 * 	@{
 */
/**	@brief	Structure type for work with
 *  		HelperData parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			CMD_HELPER_DATA
 *
 *			TX 10 bytes
 *
 *	@ref	SBGC32_ProvideHelperData function
 */
typedef struct __PACKED__
{
	i16		frameACC [3];							/*!<  Units: 1g/512 ≈ 0,019160156 m/s²												*/

	i16		frameAngleRoll,							/*!<  -32768 --> 32767. Inclination of the outer frame in a given coordinate system */
			frameAnglePitch;						/*!<  Units: 0.02197265625 degree. Pass zero values to not use this information		*/

}			HelperData_t;


/**	@brief	Structure type for work with
 *  		HelperDataExt parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			Firmware: 2.60+, beginning with
 *			<flags> parameter
 *
 *			CMD_HELPER_DATA
 *
 *			TX 10 bytes (20 bytes - extended)
 *
 *	@ref	SBGC32_ProvideHelperDataExt function
 */
typedef struct __PACKED__
{
	i16		frameACC [3];							/*!<  Units: 1g/512 ≈ 0,019160156 m/s²												*/

	i16		frameAngleRoll,							/*!<  -32768 --> 32767. Inclination of the outer frame in a given coordinate system */
			frameAnglePitch;						/*!<  Units: 0.02197265625 degree. Pass zero values to not use this information		*/

	/* + Extended format (frw. ver. 2.60+) */
	ui8		flags;									/*!<  See @ref HelperDataFlags_t enumeration										*/
	i16		frameSpeed [3];							/*!<  Units: 0.06103701895 degree/sec. Frw. ver. 2.62b7+							*/
	i16		frameHeading;							/*!<  -16384 --> 16384. Units: 0.02197265625 degree									*/
	ui8		reserved;

}			HelperDataExt_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								 Function Prototypes
 */
/**	@addtogroup	Ext_IMU_Debug_Info
 * 	@{
 */
TxRxStatus_t SBGC32_RequestExtIMU_DebugInfo (GeneralSBGC_t *generalSBGC, ExtIMU_DebugInfo_t *extIMU_DebugInfo);
/**	@}
 */


/**	@addtogroup	Ext_IMU_Cmd
 * 	@{
 */
TxRxStatus_t SBGC32_SendCmdToExtIMU (GeneralSBGC_t *generalSBGC, SerialCommand_t *cmdToIMU, ExtIMU_CommandType_t cmdType);
/**	@}
 */


/**	@addtogroup	Gyro_Correction
 * 	@{
 */
TxRxStatus_t SBGC32_CorrectionGyro (GeneralSBGC_t *generalSBGC, const GyroCorrection_t *gyroCorrection);
/**	@}
 */


/**	@addtogroup	AHRS_Helper
 * 	@{
 */
TxRxStatus_t SBGC32_CallAHRS_Helper (GeneralSBGC_t *generalSBGC, AHRS_Helper_t *AHRS_Helper);
/**	@}
 */


/**	@addtogroup	Helper_Data
 * 	@{
 */
TxRxStatus_t SBGC32_ProvideHelperData (GeneralSBGC_t *generalSBGC, HelperData_t *helperData);
TxRxStatus_t SBGC32_ProvideHelperDataExt (GeneralSBGC_t *generalSBGC, HelperDataExt_t *helperDataExt);
/**	@}
 */

/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef 		__cplusplus
			}
#endif

#endif		/* _IMU_H_ */
