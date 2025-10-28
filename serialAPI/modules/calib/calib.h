/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2
 *
 *	@file		calib.h
 *
 *	@brief		Calibration header file
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
 *	@defgroup	Calib SBGC32 Calibration
 *	@ingroup	Modules
 *		@brief	SBGC32 Calibration Title Module
 *	____________________________________________________________________
 *
 *	@defgroup	Calib_IMU IMU Calibration
 *	@ingroup	Calib
 *		@brief	IMU Calibration Module
 *
 *				Covered Commands:
 *
 *				### CMD_CALIB_ACC
 *				### CMD_CALIB_GYRO
 *				### CMD_CALIB_MAG
 *
 *	@defgroup	Calib_IMU_Info IMU Calibration Information
 *	@ingroup	Calib
 *		@brief	IMU Calibration Information Module
 *
 *				Covered Commands:
 *
 *				### CMD_CALIB_INFO
 *
 *	@defgroup	Calib_Encoders_Offset Encoders Offset Calibration
 *	@ingroup	Calib
 *		@brief	Encoders Offset Calibration Module
 *
 *				Covered Commands:
 *
 *				### CMD_ENCODERS_CALIB_OFFSET_4
 *				### CMD_ENCODERS_CALIB_FLD_OFFSET_4
 *
 *	@defgroup	Calib_Other Other Calibrations
 *	@ingroup	Calib
 *		@brief	Other Calibrations Module
 *
 *				Covered Commands:
 *
 *				### CMD_CALIB_POLES
 *				### CMD_CALIB_OFFSET
 *				### CMD_CALIB_BAT
 *				### CMD_CALIB_ORIENT_CORR
 *				### CMD_CALIB_ACC_EXT_REF
 *				### CMD_CALIB_COGGING
 *	____________________________________________________________________
 */

#ifndef		MODULES_CALIB_H_
#define		MODULES_CALIB_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../sbgc32.h"


#if (SBGC_CALIB_MODULE)

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									Calib Info Flags
 */
/**	@addtogroup	Calib_IMU
 *	@{
 */
/**	@note	sbgcIMU_ExtCalib_t.action
 */
typedef enum
{
	IMUECA_DO_REGULAR_CALIBRATION	= 1,
	IMUECA_RESET_CALIB_AND_RESTART	= 2,
	IMUECA_DO_TEMPERATURE_CALIB		= 3,
	IMUECA_ENABLE_TEMP_CALIB_DATA	= 4,
	IMUECA_DISABLE_TEMP_CALIB_DATA	= 5,
	IMUECA_COPY_SENSOR_CALIB_TO_EEPROM
									= 6,
	IMUECA_COPY_EEPROM_CALIB_TO_SENSOR
									= 7

}	sbgcIMU_ExtCalibAction_t;
/**	@}
 */


/**	@addtogroup	Calib_IMU_Info
 *	@{
 */
/**	@note	sbgcCalibInfo_t.AccCurAxis
 */
typedef enum
{
	ACA_ROLL						= 0,
	ACA_PITCH						= 1,
	ACA_YAW							= 2

}	sbgcAccCurAxis_t;


/**	@note	sbgcCalibInfo_t.AccLimitsInfo
 */
typedef enum
{
	ACCLI_X							= 0,
	ACCLI_MINUS_X					= 1,
	ACCLI_Y							= 2,
	ACCLI_MINUS_Y					= 3,
	ACCLI_Z							= 4,
	ACCLI_MINUS_Z					= 5

}	sbgcAccLimitsInfo_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						 Calib Encoders Offset Flags
 */
/**	@addtogroup	Calib_Encoders_Offset
 *	@{
 */
/**	@note	@ref SBGC32_CalibEncodersFldOffset, 2 arg
 */
typedef enum
{
	CALIB_PARAM_ROLL_ONLY			= 0,
	CALIB_PARAM_PITCH_ONLY			= 1,
	CALIB_PARAM_YAW_ONLY			= 2,

	CALIB_PARAM_ALL_AXES			= 255

}	sbgcCalibParameter_t;


/**	@note	sbgcCalibEncodersOffset_t.calibFlags
 */
typedef enum
{
	CALIB_FLAG_IGNORE_IMU_CHECK		= BIT_0_SET,	/*!<  Ignore IMU angle vs motor angle validity check								*/
	CALIB_FLAG_IGNORE_ENCODER_CHECK	= BIT_1_SET		/*!<  Ignore encoder angle vs motor angle validity check							*/

}	sbgcCalibFlag_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								   Other Calib Flags
 */
/**	@note	sbgcCalibCogging_t.action
 */
typedef enum
{
	CCA_CALIBRATE					= 1,
	CCA_DELETE_CALIBRATION_DATA		= 2

}	sbgcCalibCoggingAction_t;


/**	@note	sbgcCalibCogging_t.axisToCalibrate
 */
typedef enum
{
	CCAC_ROLL						= BIT_0_SET,
	CCAC_PITCH						= BIT_1_SET,
	CCAC_YAW						= BIT_2_SET

}	sbgcCalibCoggingAxis_t;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								 Calib IMU Structure
 */
/**	@addtogroup	Calib_IMU
 *	@{
 */
/**	@brief	Structure type for work with
 *			accelerometer, gyroscope and
 *			magnetometer calibrations
 *			in extended format
 *
 *	@ref	SBGC32_CalibAccExt function\n
 *	@ref	SBGC32_CalibGyroExt function\n
 *	@ref	SBGC32_CalibMagExt function
 */
typedef struct PACKED__
{
	ui8						IMU_IDx;				/*!<  See @ref sbgcIMU_Type_t enumeration											*/
	ui8						action;					/*!<  See @ref sbgcIMU_ExtCalibAction_t enumeration									*/
	ui16					timeMs;					/*!<  Units: ms. Time for gyroscope calibration. If set to 0, default time is used
														  (~ 4 seconds), which is good balance between precision and speed				*/
	ui8						reserved [8];

}	sbgcIMU_ExtCalib_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t IMU_ExtCalibReferenceInfoArray [];
	extern const ui8 IMU_ExtCalibReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								Calib Info Structure
 */
/**	@addtogroup	Calib_IMU_Info
 *	@{
 */
/**	@brief	Structure type for work with
 *			CalibInfo parameters
 *
 *	@ref	SBGC32_RequestCalibInfo function
 */
typedef struct PACKED__
{
	ui8		progress;								/*!<  0 --> 100. Progress of operation in percents									*/
	ui8		IMU_Type;								/*!<  See @ref sbgcIMU_Type_t enumeration											*/
	i16		accData [3];							/*!<  Units: 1/512 G																*/
	ui16	gyroABS_Val;							/*!<  Amplitude of gyro signal														*/
	ui8		accCurAxis;								/*!<  See @ref sbgcAccCurAxis_t enumeration											*/
	ui8		accLimitsInfo;							/*!<  See @ref sbgcAccLimitsInfo_t enumeration										*/
	i8		IMU_TempCels;							/*!<  -127 --> 127. Units: Celsius													*/
	ui8		tempCalibGyroEnabled;					/*!<  0 --> 1																		*/

	i8		tempCalibGyroT_MinCels,					/*!<  ...																			*/
			tempCalibGyroT_MaxCels;					/*!<  ...Range of temperature calibration. Units: Celsius							*/

	ui8		tempCalibAccEnabled;					/*!<  0 --> 1																		*/
	ui8		tempCalibAccSlotNum [6];				/*!<  0 --> 3. The number of calibrated temperature slots for accelerometer
														  for each limit in order [+X : +Y : +Z : -X : -Y : -Z]							*/

	i8		tempCalibAccT_MinCels,					/*!<  ...																			*/
			tempCalibAccT_MaxCels;					/*!<  ...Units: Celsius. Range of temperature calibration 							*/

	ui8		H_ErrLength;							/*!<  0 --> 255. Units: vector = 100. The length of error vector between
														  estimated and referenced heading vectors										*/
	ui8		reserved [7];

}	sbgcCalibInfo_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t calibInfoReferenceInfoArray [];
	extern const ui8 calibInfoReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *					 Calib Encoders Offset Structure
 */
/**	@addtogroup	Calib_Encoders_Offset
 *	@{
 */
/**	@brief	Structure type for work with encoders
 *			field extended offset
 *
 *	@ref	SBGC32_CalibEncodersFldOffsetExt function
 */
typedef struct
{
	i16		calibAngle [3],							/*!<  1 --> -. Units: 0.02197265625 degree. Angle range to move during
														  calibration. If omitted, default is 40°. Frw. ver. 2.62b6+. Use the
														  @ref sbgcAngleToDegree macro to comfortable work with this field				*/
			calibSpeed [3];							/*!<  1 --> -. Units: 0.06103701895 deg/sec. Speed of movement during the
														  calibration. If omitted, default is 100. Frw. ver. 2.71b1+					*/
	ui16	calibFlags;								/*!<  See @ref sbgcCalibFlag_t enumeration. Frw. ver. 2.70b8+						*/

}	sbgcCalibEncodersOffset_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							  Calib Other Structures
 */
/**	@addtogroup	Calib_Other
 *	@{
 */
/**	@brief	Part of sbgcCalibCogging_t structure
 *
 *	@note	sbgcCalibCogging_t.AxisCCog
 */
typedef struct
{
	ui16	angle;									/*!<  20 --> 360. Angle to move, in degrees											*/
	ui8		smooth;									/*!<  0 --> 100. Smooth the resulting curve, in %									*/
	ui8		speed;									/*!<  Speed of rotation, in relative units											*/
	ui16	period;									/*!<  Expected period of non-linearity curve, in degrees. 0 for auto-detection		*/

	ui8		reserved [9];

}	sbgcAxisCCog_t;


/**	@brief	Structure type for work
 *			with cogging calibration
 *
 *	@ref	SBGC32_CalibCogging function
 */
typedef struct
{
	ui8				action;							/*!<  See @ref sbgcCalibCoggingAction_t enumeration									*/
	ui8				axisToCalibrate;				/*!<  See @ref sbgcCalibCoggingAxis_t enumeration									*/

	sbgcAxisCCog_t	AxisCCog [3];					/*!<  ROLL : PITCH : YAW															*/

	ui8				iterationsNum;					/*!<  2 --> -																		*/

	ui8				reserved [9];

}	sbgcCalibCogging_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t calibCoggingReferenceInfoArray [];
	extern const ui8 calibCoggingReferenceInfoArrayElCnt;
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
/**	@addtogroup	Calib_IMU
 *	@{
 */
sbgcCommandStatus_t SBGC32_CalibAcc (sbgcGeneral_t *gSBGC SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_CalibGyro (sbgcGeneral_t *gSBGC SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_CalibMag (sbgcGeneral_t *gSBGC SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_CalibAccExt (sbgcGeneral_t *gSBGC, sbgcIMU_ExtCalib_t *IMU_ExtCalib, sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_CalibGyroExt (sbgcGeneral_t *gSBGC, sbgcIMU_ExtCalib_t *IMU_ExtCalib, sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_CalibMagExt (sbgcGeneral_t *gSBGC, sbgcIMU_ExtCalib_t *IMU_ExtCalib, sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Calib_IMU_Info
 *	@{
 */
sbgcCommandStatus_t SBGC32_RequestCalibInfo (sbgcGeneral_t *gSBGC, sbgcCalibInfo_t *calibInfo, sbgcIMU_Type_t IMU_Type SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Calib_Encoders_Offset
 *	@{
 */
sbgcCommandStatus_t SBGC32_CalibEncodersOffset (sbgcGeneral_t *gSBGC, sbgcCalibParameter_t forMotor SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_CalibEncodersFldOffset (sbgcGeneral_t *gSBGC SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_CalibEncodersFldOffsetExt (sbgcGeneral_t *gSBGC, const sbgcCalibEncodersOffset_t *calibEncodersOffset
													  SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Calib_Other
 *	@{
 */
sbgcCommandStatus_t SBGC32_CalibPoles (sbgcGeneral_t *gSBGC SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_CalibOffset (sbgcGeneral_t *gSBGC SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_CalibBat (sbgcGeneral_t *gSBGC, ui16 voltage, sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_CalibOrientCorr (sbgcGeneral_t *gSBGC, sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_CalibAccExtRef (sbgcGeneral_t *gSBGC, const i16 accRef [3], sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_CalibCogging (sbgcGeneral_t *gSBGC, const sbgcCalibCogging_t *calibCogging, sbgcConfirm_t *confirm
										 SBGC_ADVANCED_PARAMS__);
/**	@}
 */
/**	@endcond
 */

#endif /* SBGC_CALIB_MODULE */


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

#endif		/* MODULES_CALIB_H_ */
