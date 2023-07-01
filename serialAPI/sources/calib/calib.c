/** ____________________________________________________________________
 *
 * 	SBGC32 Serial API Library v1.0
 *
 *	@file		calib.c
 *
 *	@brief 		Calibration source file
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

#include "../../sbgc32.h"


#if (SBGC_CALIB_MODULE)

#if (SYS_BIG_ENDIAN || SBGC_REF_INFO)

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *					Big Endian Mapping and Reference Info Structures
	 */
	/**	@addtogroup	Calib_IMU
	 * 	@{
	 */
	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t IMU_ExtCalibReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"IMU IDx",					_UNSIGNED_CHAR_				),  // 0
		PARAM_BLOCK_(	"Action",					_UNSIGNED_CHAR_				),  // 1
		PARAM_BLOCK_(	"Time Ms",					_UNSIGNED_SHORT_			),  // 2
		PARAMS_BLOCK_(	"Reserved",					_RESERVED_CHAR_,		8	),  // 3

	};

	const ui8 IMU_ExtCalibReferenceInfoArrayElCnt = countof_(IMU_ExtCalibReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Calib_IMU_Info
	 * 	@{
	 */
	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t calibInfoReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Progress",					_UNSIGNED_CHAR_				),  // 0
		PARAM_BLOCK_(	"IMU Type",					_UNSIGNED_CHAR_				),  // 1
		PARAMS_BLOCK_(	"Acc Data",					_SIGNED_SHORT_,			3	),  // 2
		PARAM_BLOCK_(	"Gyro ABS Val",				_UNSIGNED_SHORT_			),  // 3

		PARAM_BLOCK_(	"Acc Cur Axis",				_UNSIGNED_CHAR_				),  // 4
		PARAM_BLOCK_(	"Acc Limits Info",			_UNSIGNED_CHAR_				),  // 5
		PARAM_BLOCK_(	"IMU Temp Cels",			_SIGNED_CHAR_				),  // 6
		PARAM_BLOCK_(	"Temp Calib Gyro Enabled",	_UNSIGNED_CHAR_				),  // 7

		PARAM_BLOCK_(	"Temp Calib Gyro T Min Cels",
													_SIGNED_CHAR_				),  // 8
		PARAM_BLOCK_(	"Temp Calib Gyro T Max Cels",
													_SIGNED_CHAR_				),  // 9
		PARAM_BLOCK_(	"Temp Calib Acc Enabled",	_UNSIGNED_CHAR_				),  // 10
		PARAMS_BLOCK_(	"Temp Calib Acc Slot Num",	_UNSIGNED_CHAR_,		6	),  // 11
		PARAM_BLOCK_(	"Temp Calib Acc T Min Cels",
													_SIGNED_CHAR_				),  // 12
		PARAM_BLOCK_(	"Temp Calib Acc T Max Cels",
													_SIGNED_CHAR_				),  // 13
		PARAM_BLOCK_(	"H Err Length",				_UNSIGNED_CHAR_				),  // 14
		PARAMS_BLOCK_(	"Reserved",					_RESERVED_CHAR_,		7	),  // 15

	};

	const ui8 calibInfoReferenceInfoArrayElCnt = countof_(calibInfoReferenceInfoArray);
	/**	@}
	 */

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	Calib_IMU
 * 	@{
 */
/**	@brief	Calibrates accelerometer
 *
 *	@note	Starts regular calibration of currently active IMU,
 *			selected by the @ref SBGC32_SelectIMU_3 function
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibAcc (GeneralSBGC_t *generalSBGC)
{
	SBGC32_SendEmptyCommand(generalSBGC, CMD_CALIB_ACC);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Calibrates gyroscope
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
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Calibrates magnetometer
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
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Extended format of accelerometer calibration
 *
 *	@note	If all parameters are valid, confirmation
 *			is sent immediately on reception and in
 *			the end of calibration. This function
 *			handle only start calibration confirmation
 *
 *	@param 	*generalSBGC - serial connection descriptor
 *	@param	*IMU_ExtCalib - additional command's info
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibAccExt (GeneralSBGC_t *generalSBGC, IMU_ExtCalib_t *IMU_ExtCalib)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_CALIB_ACC);
	WriteBuff(&cmd, IMU_ExtCalib, sizeof(IMU_ExtCalib_t), PM_IMU_EXT_CALIB);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Extended format of gyroscope calibration
 *
 *	@note	If all parameters are valid, confirmation
 *			is sent immediately on reception and in
 *			the end of calibration. This function
 *			handle only start calibration confirmation
 *
 *	@param 	*generalSBGC - serial connection descriptor
 *	@param	*IMU_ExtCalib - additional command's info
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibGyroExt (GeneralSBGC_t *generalSBGC, IMU_ExtCalib_t *IMU_ExtCalib)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_CALIB_GYRO);
	WriteBuff(&cmd, IMU_ExtCalib, sizeof(IMU_ExtCalib_t), PM_IMU_EXT_CALIB);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Extended format of magnetometer calibration
 *
 *	@note	If all parameters are valid, confirmation
 *			is sent immediately on reception and in
 *			the end of calibration. This function
 *			handle only start calibration confirmation
 *
 *	@param 	*generalSBGC - serial connection descriptor
 *	@param	*IMU_ExtCalib - additional command's info
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibMagExt (GeneralSBGC_t *generalSBGC, IMU_ExtCalib_t *IMU_ExtCalib)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_CALIB_MAG);
	WriteBuff(&cmd, IMU_ExtCalib, sizeof(IMU_ExtCalib_t), PM_IMU_EXT_CALIB);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
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

	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Calib_Encoders_Offset
 * 	@{
 */
/**	@brief	Calibrates offset of encoders
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibEncodersOffset (GeneralSBGC_t *generalSBGC)
{
	SBGC32_SendEmptyCommand(generalSBGC, CMD_ENCODERS_CALIB_OFFSET_4);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Starts field offset calibration of encoders
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibEncodersFldOffset (GeneralSBGC_t *generalSBGC)
{
	SBGC32_SendEmptyCommand(generalSBGC, CMD_ENCODERS_CALIB_FLD_OFFSET_4);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Starts field offset calibration of encoders
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
	for (ui8 i = 0; i < 3; i++) WriteWord(&cmd, calibEncodersOffset->calibAngle[i]);
	for (ui8 i = 0; i < 3; i++) WriteWord(&cmd, calibEncodersOffset->calibSpeed[i]);
	SBGC32_TX(generalSBGC, &cmd);
	/* no need confirmation */
	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Calib_Other
 * 	@{
 */
/**	@brief	Calibrates EXT_FC gains (MainParams3_t.ExtFC_Gain)
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibExtGain (GeneralSBGC_t *generalSBGC)
{
	SBGC32_SendEmptyCommand(generalSBGC, CMD_CALIB_EXT_GAIN);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Calibrates poles and direction
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibPoles (GeneralSBGC_t *generalSBGC)
{
	SBGC32_SendEmptyCommand(generalSBGC, CMD_CALIB_POLES);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Calibrates follow offset
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibOffset (GeneralSBGC_t *generalSBGC)
{
	SBGC32_SendEmptyCommand(generalSBGC, CMD_CALIB_OFFSET);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Calibrates internal voltage sensor
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 * 	@param	voltage - reference voltage value
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibBat (GeneralSBGC_t *generalSBGC, ui16 voltage)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_CALIB_BAT);
	WriteWord(&cmd, voltage);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Starts the calibration of sensor misalignment correction
 *
 *	@attention	Firmware: 2.61+
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibOrientCorr (GeneralSBGC_t *generalSBGC)
{
	#if (SBGC_DEBUG_MODE == SET_OFF)

		if (generalSBGC->_firmwareVersion < 2610)
			return NOT_SUPPORTED_BY_FIRMWARE;

	#endif

	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_CALIB_ORIENT_CORR);
	WriteEmptyBuff(&cmd, 16);  // reserved[16]
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Refine the accelerometer calibration of the main IMU sensor
 *
 *	@attention	Firmware: 2.62b7+
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *	@param	*AccRef - reference Acc vector [X,Y,Z] in gimbal
 *			frame's coordinates. Units: 1g/512 ≈ 0,019160156 m/s²
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CalibAccExtRef (GeneralSBGC_t *generalSBGC, const i16 AccRef [3])
{
	#if (SBGC_DEBUG_MODE == SET_OFF)

		if (generalSBGC->_firmwareVersion < 2627)
			return NOT_SUPPORTED_BY_FIRMWARE;

	#endif

	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_CALIB_ACC_EXT_REF);
	for (ui8 i = 0; i < 3; i++) WriteWord(&cmd, AccRef[i]);
	WriteEmptyBuff(&cmd, 14);  // reserved[14]
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */

#endif /* SBGC_CALIB_MODULE */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
