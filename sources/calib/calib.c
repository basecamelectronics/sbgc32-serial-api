/** ____________________________________________________________________
 *
 *	@file		calib.c
 *
 *	@brief 		Calibration source file
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

#include "calib.h"


#ifdef	SYS_BIG_ENDIAN

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *								Parser Big Endian Mapping Structures
	 */
	/**	@addtogroup	Calib_IMU_Info
	 * 	@{
	 */
	/** @brief	Sample for Big Endian Mapping
	 *
	 * 	@ref	CalibInfo_ParserStructDB
	 */
	CalibInfo_t	calibInfo_ParserStruct;

	const ParserBlock_t CalibInfo_ParserStructDB [] =
	{
		VAR_BLOCK(calibInfo_ParserStruct.progress),
		VAR_BLOCK(calibInfo_ParserStruct.IMU_Type),
		DATA_BLOCK(calibInfo_ParserStruct.ACC_Data),
		VAR_BLOCK(calibInfo_ParserStruct.gyroABS_Val),
		VAR_BLOCK(calibInfo_ParserStruct.ACC_CurAxis),
		VAR_BLOCK(calibInfo_ParserStruct.ACC_LimitsInfo),
		VAR_BLOCK(calibInfo_ParserStruct.IMU_TempCels),
		VAR_BLOCK(calibInfo_ParserStruct.tempCalibGyroEnabled),
		VAR_BLOCK(calibInfo_ParserStruct.tempCalibGyroT_MinCels),
		VAR_BLOCK(calibInfo_ParserStruct.tempCalibGyroT_MaxCels),
		VAR_BLOCK(calibInfo_ParserStruct.tempCalibACC_Enabled),
		DATA_BLOCK(calibInfo_ParserStruct.tempCalibACC_SlotNum),
		VAR_BLOCK(calibInfo_ParserStruct.tempCalibACC_T_MinCels),
		VAR_BLOCK(calibInfo_ParserStruct.tempCalibACC_T_MaxCels),
		VAR_BLOCK(calibInfo_ParserStruct.H_ErrLength),
		DATA_BLOCK(calibInfo_ParserStruct.reserved),
	};

	const ui8 CalibInfo_ParserStructDB_Size = countof(CalibInfo_ParserStructDB);
	/**	@}
	 */

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	Calib_IMU
 * 	@{
 */
/**	@brief	Calibrate accelerometer
 *
 *	@note	Starts regular calibration of currently active IMU,
 *			selected by the @ref SBGC32_SelectIMU_3 function
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibACC (GeneralSBGC_t *generalSBGC)
{
	SBGC32_SendEmptyCommand(generalSBGC, CMD_CALIB_ACC);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Calibrate gyroscope
 *
 *	@note	Starts regular calibration of currently active IMU,
 *			selected by the @ref SBGC32_SelectIMU_3 function
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibGyro (GeneralSBGC_t *generalSBGC)
{
	SBGC32_SendEmptyCommand(generalSBGC, CMD_CALIB_GYRO);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Calibrate magnetometer
 *
 *	@note	Starts regular calibration of currently active IMU,
 *			selected by the @ref SBGC32_SelectIMU_3 function
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibMag (GeneralSBGC_t *generalSBGC)
{
	SBGC32_SendEmptyCommand(generalSBGC, CMD_CALIB_MAG);
	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Calib_IMU_Info
 * 	@{
 */
/**	@brief	Requests information about current IMU calibration state
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *	@param	*calibInfo - structure storing IMU calibration state
 *	@param	IMU_Type - IMU sensor in calibration process
 *
 * 	@return Communication status
 */
TxRxStatus_t SBGC32_RequestCalibInfo (GeneralSBGC_t *generalSBGC, CalibInfo_t *calibInfo, IMU_Type_t IMU_Type)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_CALIB_INFO);
	WriteByte(&cmd, IMU_Type);
	WriteEmptyBuff(&cmd, 11);  // reserved[11]

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_CALIB_INFO), "IMU Calibration Info:") == TX_RX_OK)
		ReadBuff(&cmd, calibInfo, sizeof(CalibInfo_t), PM_CALIB_INFO);

	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Calib_Encoders_Offset
 * 	@{
 */
/**	@brief	Calibrate offset of encoders
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibEncodersOffset (GeneralSBGC_t *generalSBGC)
{
	SBGC32_SendEmptyCommand(generalSBGC, CMD_ENCODERS_CALIB_OFFSET_4);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Start field offset calibration of encoders
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibEncodersFldOffset (GeneralSBGC_t *generalSBGC)
{
	SBGC32_SendEmptyCommand(generalSBGC, CMD_ENCODERS_CALIB_FLD_OFFSET_4);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Start field offset calibration of encoders
 * 			in extended format
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 * 	@param	*calibEncodersOffset - writable structure with extended
 *			information about encoders offset calibration
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibEncodersFldOffsetExt (GeneralSBGC_t *generalSBGC, const CalibEncodersOffset_t *calibEncodersOffset)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_ENCODERS_CALIB_FLD_OFFSET_4);
	WriteByte(&cmd, calibEncodersOffset->motor);
	FOR_(i, 3) WriteWord(&cmd, calibEncodersOffset->calibAngle[i]);
	FOR_(i, 3) WriteWord(&cmd, calibEncodersOffset->calibSpeed[i]);
	SBGC32_TX(generalSBGC, &cmd);
	/* no need confirmation */
	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Calib_Other
 * 	@{
 */
/**	@brief	Calibrate EXT_FC gains (MainParams3_t.ExtFC_Gain)
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibExtGain (GeneralSBGC_t *generalSBGC)
{
	SBGC32_SendEmptyCommand(generalSBGC, CMD_CALIB_EXT_GAIN);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Calibrate poles and direction
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibPoles (GeneralSBGC_t *generalSBGC)
{
	SBGC32_SendEmptyCommand(generalSBGC, CMD_CALIB_POLES);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Calibrate follow offset
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibOffset (GeneralSBGC_t *generalSBGC)
{
	SBGC32_SendEmptyCommand(generalSBGC, CMD_CALIB_OFFSET);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Calibrate internal voltage sensor
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 * 	@param	voltage - reference voltage value
 *	@param	*confirmationState - confirmation structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibBat (GeneralSBGC_t *generalSBGC, ui16 voltage, ConfirmationState_t *confirmationState)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_CALIB_BAT);
	WriteWord(&cmd, voltage);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, cmd.commandID);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Start the calibration of sensor misalignment correction
 *
 *	@attention	Firmware: 2.61+
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *	@param	*confirmationState - confirmation structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibOrientCorr (GeneralSBGC_t *generalSBGC, ConfirmationState_t *confirmationState)
{
	if (generalSBGC->_firmwareVersion < 2610)
		return NOT_SUPPORTED_BY_FIRMWARE;

	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_CALIB_ORIENT_CORR);
	WriteEmptyBuff(&cmd, 16);  // reserved[16]
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, cmd.commandID);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Refine the accelerometer calibration of the main IMU sensor
 *
 *	@attention	Firmware: 2.62b7+
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *	@param	*ACC_Ref - reference ACC vector [X,Y,Z] in gimbal
 *			frame's coordinates. Units: 1g/512 ≈ 0,019160156 m/s²
 *	@param	*confirmationState - confirmation structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibACC_ExtRef (GeneralSBGC_t *generalSBGC, const i16 ACC_Ref [3], ConfirmationState_t *confirmationState)
{
	if (generalSBGC->_firmwareVersion < 2627)
		return NOT_SUPPORTED_BY_FIRMWARE;

	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_CALIB_ACC_EXT_REF);
	FOR_(i, 3) WriteWord(&cmd, ACC_Ref[i]);
	WriteEmptyBuff(&cmd, 14);  // reserved[14]
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, cmd.commandID);
	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
