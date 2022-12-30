/** ____________________________________________________________________
 *
 * 	@file		calib.h
 *
 *	@brief 		Calibration header file
 *
 *				<center><a href="https://www.basecamelectronics.com">
 *				www.basecamelectronics.com</a>
 *	____________________________________________________________________
 *
 *	@attention	<center><h3>
 *	Copyright © 2023 BaseCam Electronics™.</h3></center>
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
 * 	@defgroup	Calib SBGC32 Calibration
 *	@ingroup	Sources
 *		@brief	SBGC32 Calibration Title Module
 *  ____________________________________________________________________
 *
 *	@defgroup	Calib_IMU IMU Calibration
 *  @ingroup	Calib
 *  	@brief	IMU Calibration Module
 *
 *  			Covered Commands:
 *
 *				### CMD_CALIB_ACC
 *				### CMD_CALIB_GYRO
 *				### CMD_CALIB_MAG
 *
 *  @defgroup	Calib_IMU_Info IMU Calibration Information
 *  @ingroup	Calib
 *  	@brief	IMU Calibration Information Module
 *
 *  			Covered Commands:
 *
 *				### CMD_CALIB_INFO
 *
 *  @defgroup	Calib_Encoders_Offset Encoders Offset Calibration
 *  @ingroup	Calib
 *  	@brief	Encoders Offset Calibration Module
 *
 *  			Covered Commands:
 *
 *				### CMD_ENCODERS_CALIB_OFFSET_4
 *				### CMD_ENCODERS_CALIB_FLD_OFFSET_4
 *
 *  @defgroup	Calib_Other Other Calibrations
 *  @ingroup	Calib
 *  	@brief	Other Calibrations Module
 *
 *  			Covered Commands:
 *
 *				### CMD_CALIB_EXT_GAIN
 *				### CMD_CALIB_POLES
 *				### CMD_CALIB_OFFSET
 *				### CMD_CALIB_BAT
 *				### CMD_CALIB_ORIENT_CORR
 *				### CMD_CALIB_ACC_EXT_REF
 *	____________________________________________________________________
 */

#ifndef     _CALIB_H_
#define     _CALIB_H_

#ifdef 		__cplusplus
extern 		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include 	"../core/core.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 									Calib Info Flags
 */
/**	@addtogroup	Calib_IMU_Info
 * 	@{
 */
/**	@note	CalibInfo_t.ACC_CurAxis
 */
typedef enum
{
	ACCCA_ROLL						= 0,
	ACCCA_PITCH						= 1,
	ACCCA_YAW						= 2

}	ACC_CurAxis_t;


/**	@note	CalibInfo_t.ACC_LimitsInfo
 */
typedef enum
{
	ACCLI_X							= 0,
	ACCLI_MINUS_X					= 1,
	ACCLI_Y							= 2,
	ACCLI_MINUS_Y					= 3,
	ACCLI_Z							= 4,
	ACCLI_MINUS_Z					= 5

}	ACC_LimitsInfo_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 						 Calib Encoders Offset Flags
 */
/**	@addtogroup	Calib_Encoders_Offset
 * 	@{
 */
/**	@note	CalibEncodersOffset_t.motor
 */
typedef enum
{
	CFM_ROLL						= 0,
	CFM_PITCH						= 1,
	CFM_YAW							= 2,

	CFM_ALL_MOTORS					= 255

}	CalibForMotor_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								Calib Info Structure
 */
/**	@addtogroup	Calib_IMU_Info
 * 	@{
 */
/**	@brief	Structure type for work with
 *  		CalibInfo parameters
 *
 *	@note	<b><i>Parameters:</i></b>
 *
 *			CMD_Calib_IMU_Info
 *
 *			RX 33 bytes
 *
 *			Information required for the
 *			"Calibration helper"
 *
 *	@ref	SBGC32_RequestCalibInfo function
 */
typedef struct __PACKED__
{
	ui8		progress;								/*!<  0 --> 100. Progress of operation in percents									*/
	ui8		IMU_Type;								/*!<  @see IMU_Type_t enumeration													*/
	i16		ACC_Data [3];							/*!<  Units: 1/512 G																*/
	ui16	gyroABS_Val;							/*!<  Amplitude of gyro signal														*/
	ui8		ACC_CurAxis;							/*!<  @see ACC_CurAxis_t enumeration												*/
	ui8		ACC_LimitsInfo;							/*!<  @see ACC_LimitsInfo_t enumeration												*/
	i8		IMU_TempCels;							/*!<  -127 --> 127. Units: Celsius													*/
	ui8		tempCalibGyroEnabled;					/*!<  0 --> 1																		*/

	i8		tempCalibGyroT_MinCels,					/*!<  ...																			*/
			tempCalibGyroT_MaxCels;					/*!<  Range of temperature calibration. Units: Celsius								*/

	ui8 	tempCalibACC_Enabled;					/*!<  0 --> 1																		*/
	ui8		tempCalibACC_SlotNum [6];				/*!<  0 --> 3. The number of calibrated temperature slots for accelerometer
	 	 	 	 	 	 	 	 	 	 	 	 	 	  for each limit in order [+X : +Y : +Z : -X : -Y : -Z] 						*/

	i8		tempCalibACC_T_MinCels,					/*!<  ...																			*/
			tempCalibACC_T_MaxCels;					/*!<  Range of temperature calibration. Units: Celsius								*/

	ui8		H_ErrLength;							/*!<  0 --> 255. Units: vector = 100												*/
	ui8		reserved [7];

}			CalibInfo_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 					 Calib Encoders Offset Structure
 */
/**	@addtogroup	Calib_Encoders_Offset
 * 	@{
 */
/**	@brief	Structure type for work with
 *  		@ref SBGC32_CalibEncodersFldOffsetExt
 *  		function
 *
 *  @note	Extended data for command
 *			CMD_ENCODERS_CALIB_FLD_OFFSET_4
 *			(13 bytes)
 */
typedef struct
{
	CalibForMotor_t	motor;							/*!<  See @ref CalibForMotor_t enumeration. Calibrate offset for the given motor	*/

	i16		calibAngle [3],							/*!<  1 --> -. Units: 0.02197265625 degree. Angle range to move during
														  calibration. If omitted, default is 40°. Frw. ver. 2.62b6+					*/
			calibSpeed [3];							/*!<  1 --> -. Units: 0.06103701895 deg/sec. Speed of movement during the
														  calibration. If omitted, default is 100. Frw. ver. 2.71b1+					*/

}			CalibEncodersOffset_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								 Function Prototypes
 */
/**	@addtogroup	Calib_IMU
 * 	@{
 */
TxRxStatus_t SBGC32_CalibACC (GeneralSBGC_t *generalSBGC);
TxRxStatus_t SBGC32_CalibGyro (GeneralSBGC_t *generalSBGC);
TxRxStatus_t SBGC32_CalibMag (GeneralSBGC_t *generalSBGC);
/**	@}
 */


/**	@addtogroup	Calib_IMU_Info
 * 	@{
 */
TxRxStatus_t SBGC32_RequestCalibInfo (GeneralSBGC_t *generalSBGC, CalibInfo_t *calibInfo, IMU_Type_t IMU_Type);
/**	@}
 */


/**	@addtogroup	Calib_Encoders_Offset
 * 	@{
 */
TxRxStatus_t SBGC32_CalibEncodersOffset (GeneralSBGC_t *generalSBGC);
TxRxStatus_t SBGC32_CalibEncodersFldOffset (GeneralSBGC_t *generalSBGC);
TxRxStatus_t SBGC32_CalibEncodersFldOffsetExt (GeneralSBGC_t *generalSBGC, const CalibEncodersOffset_t *calibEncodersOffset);
/**	@}
 */


/**	@addtogroup	Calib_Other
 * 	@{
 */
TxRxStatus_t SBGC32_CalibExtGain (GeneralSBGC_t *generalSBGC);
TxRxStatus_t SBGC32_CalibPoles (GeneralSBGC_t *generalSBGC);
TxRxStatus_t SBGC32_CalibOffset (GeneralSBGC_t *generalSBGC);
TxRxStatus_t SBGC32_CalibBat (GeneralSBGC_t *generalSBGC, ui16 voltage, ConfirmationState_t *confirmationState);
TxRxStatus_t SBGC32_CalibOrientCorr (GeneralSBGC_t *generalSBGC, ConfirmationState_t *confirmationState);
TxRxStatus_t SBGC32_CalibACC_ExtRef (GeneralSBGC_t *generalSBGC, const i16 ACC_Ref [3], ConfirmationState_t *confirmationState);
/**	@}
 */

/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef 		__cplusplus
			}
#endif

#endif      /* _CALIB_H_ */
