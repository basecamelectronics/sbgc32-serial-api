/** ____________________________________________________________________
 *
 * 	SBGC32 Serial API Library v1.0
 *
 *	@file		imu.c
 *
 *	@brief 		IMU source file
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


#if (SBGC_IMU_MODULE)

#if (SYS_BIG_ENDIAN || SBGC_REF_INFO)

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *					Big Endian Mapping and Reference Info Structures
	 */
	/**	@addtogroup	Ext_IMU_Debug_Info
	* 	@{
	*/
	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t extIMU_DebugInfoReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Main IMU Ref Src",			_UNSIGNED_CHAR_				),  // 0
		PARAM_BLOCK_(	"Frame IMU Ref Src",		_UNSIGNED_CHAR_				),  // 1
		PARAM_BLOCK_(	"Main IMU Z Ref Err",		_UNSIGNED_CHAR_				),  // 2
		PARAM_BLOCK_(	"Main IMU H Ref Err",		_UNSIGNED_CHAR_				),  // 3
		PARAM_BLOCK_(	"Frame IMU Z Ref Err",		_UNSIGNED_CHAR_				),  // 4
		PARAM_BLOCK_(	"Frame IMU H Ref Err",		_UNSIGNED_CHAR_				),  // 5
		PARAM_BLOCK_(	"Ext IMU Status",			_UNSIGNED_CHAR_				),  // 6
		PARAM_BLOCK_(	"Ext IMU Packets Received Cnt",
													_UNSIGNED_SHORT_			),  // 7
		PARAM_BLOCK_(	"Ext IMU Parse Err Cnt",	_UNSIGNED_SHORT_			),  // 8
		PARAM_BLOCK_(	"Ext Corr H Ref",			_UNSIGNED_CHAR_				),  // 9
		PARAM_BLOCK_(	"Ext Corr Z Ref",			_UNSIGNED_CHAR_				),  // 10
		PARAMS_BLOCK_(	"Reserved",					_RESERVED_CHAR_,		13	),  // 11
		PARAMS_BLOCK_(	"DCM",						_FLOAT_,				9	),  // 12
		PARAMS_BLOCK_(	"Acc Body",					_FLOAT_,				3	),  // 13

	};

	const ui8 extIMU_DebugInfoReferenceInfoArrayElCnt = countof_(extIMU_DebugInfoReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Gyro_Correction
	 * 	@{
	 */
	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t gyroCorrectionReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"IMU Type",					_UNSIGNED_CHAR_				),  // 0
		PARAMS_BLOCK_(	"Gyro Zero Corr",			_UNSIGNED_CHAR_,		3	),  // 1
		PARAM_BLOCK_(	"Gyro Zero Heading Corr",	_UNSIGNED_CHAR_				),  // 2

	};

	const ui8 gyroCorrectionReferenceInfoArrayElCnt = countof_(gyroCorrectionReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	AHRS_Helper
	 * 	@{
	 */
	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t AHRS_HelperReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Mode",						_UNSIGNED_SHORT_			),  // 0
		PARAMS_BLOCK_(	"Z Vect",					_FLOAT_,				3	),  // 1
		PARAMS_BLOCK_(	"H Vect",					_FLOAT_,				3	),  // 2

	};

	const ui8 AHRS_HelperReferenceInfoArrayElCnt = countof_(AHRS_HelperReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Helper_Data
	 * 	@{
	 */
	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t helperDataReferenceInfoArray [] =
	{
		PARAMS_BLOCK_(	"Frame Acc",				_SIGNED_SHORT_,			3	),  // 0
		PARAM_BLOCK_(	"Frame Angle Roll",			_SIGNED_SHORT_				),  // 1
		PARAM_BLOCK_(	"Frame Angle Pitch",		_SIGNED_SHORT_				),  // 2

	};

	const ui8 helperDataReferenceInfoArrayElCnt = countof_(helperDataReferenceInfoArray);


	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t helperDataExtReferenceInfoArray [] =
	{
		PARAMS_BLOCK_(	"Frame Acc",				_SIGNED_SHORT_,			3	),  // 0
		PARAM_BLOCK_(	"Frame Angle Roll",			_SIGNED_SHORT_				),  // 1
		PARAM_BLOCK_(	"Frame Angle Pitch",		_SIGNED_SHORT_				),  // 2

		PARAM_BLOCK_(	"Flags",					_UNSIGNED_CHAR_				),  // 3
		PARAMS_BLOCK_(	"Frame Speed",				_SIGNED_SHORT_,			3	),  // 4
		PARAM_BLOCK_(	"Frame Heading",			_SIGNED_SHORT_				),  // 5
		PARAM_BLOCK_(	"Reserved",					_RESERVED_CHAR_				),  // 6

	};

	const ui8 helperDataExtReferenceInfoArrayElCnt = countof_(helperDataExtReferenceInfoArray);
	/**	@}
	 */

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	Ext_IMU_Debug_Info
 * 	@{
 */
/**	@brief	Requests debug information for the external IMU sensor
 *
 *	@attention	Firmware: 2.66+
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*extIMU_DebugInfo - structure to storing
 *			information about external IMU sensor
 *
 * 	@return Communication status
 */
TxRxStatus_t SBGC32_RequestExtIMU_DebugInfo (GeneralSBGC_t *generalSBGC, ExtIMU_DebugInfo_t *extIMU_DebugInfo)
{
	#if (SBGC_DEBUG_MODE == SET_OFF)

		if (generalSBGC->_firmwareVersion < 2660)
			return NOT_SUPPORTED_BY_FIRMWARE;

	#endif

	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_EXT_IMU_DEBUG_INFO);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_EXT_IMU_DEBUG_INFO), "External IMU Debug Info:") == TX_RX_OK)
		ReadBuff(&cmd, extIMU_DebugInfo, sizeof(ExtIMU_DebugInfo_t), PM_EXT_IMU_DEBUG_INFO);

	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Ext_IMU_Cmd
 * 	@{
 */
/**	@brief	Performs data exchange between the gimbal
 * 			and an external IMU sensor
 *
 * 	@note	The whole dataStruct always must be exact filled\n
 * 			For more, see the CMD_EXT_IMU_CMD in the
 *			<a href=https://www.basecamelectronics.com/serialapi/>
 * 			SimpleBGC32 Serial API protocol specification</a>
 *
 * 	@note	This function will also be expanded in future
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*cmdToIMU - command to external IMU in SerialCommand_t format
 *	@param	cmdType - direction of command to external IMU
 *
 * 	@return Communication status
 */
TxRxStatus_t SBGC32_SendCmdToExtIMU (GeneralSBGC_t *generalSBGC, SerialCommand_t *cmdToIMU, ExtIMU_CommandType_t cmdType)
{
	SerialCommand_t cmd;

	if (cmdType == EXT_IMU_TX)
	{
		InitCmdWrite(&cmd, CMD_EXT_IMU_CMD);
		WriteByte(&cmd, cmdToIMU->commandID);
		WriteBuff(&cmd, cmdToIMU->payload, cmdToIMU->payloadSize, PM_DEFAULT_8BIT);
		SBGC32_TX(generalSBGC, &cmd);
	}

	else if (cmdType == EXT_IMU_RX)
	{
		if (CheckReceipt(generalSBGC, SBGC32_RX(generalSBGC, &cmd, generalSBGC->rxTimeout), "External IMU CMD:") == TX_RX_OK)
		{
			cmdToIMU->payloadSize = cmd.payloadSize - 1;
			cmdToIMU->commandID = ReadByte(&cmd);
			ReadBuff(&cmd, cmdToIMU->payload, cmdToIMU->payloadSize, PM_DEFAULT_8BIT);
			/* Later there will also be a data parser function here */
		}
	}

	else  /* EXT_IMU_TX_RX */
	{
		InitCmdWrite(&cmd, CMD_EXT_IMU_CMD);
		WriteByte(&cmd, cmdToIMU->commandID);
		WriteBuff(&cmd, cmdToIMU->payload, cmdToIMU->payloadSize, PM_DEFAULT_8BIT);

		if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_EXT_IMU_DEBUG_INFO), "External IMU CMD:") == TX_RX_OK)
		{
			cmdToIMU->payloadSize = cmd.payloadSize - 1;
			cmdToIMU->commandID = ReadByte(&cmd);
			ReadBuff(&cmd, cmdToIMU->payload, cmdToIMU->payloadSize, PM_DEFAULT_8BIT);
			/* Later there will also be a data parser function here */
		}
	}

	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Gyro_Correction
 * 	@{
 */
/**	@brief	Corrects the gyroscope sensor's zero bias manually
 *
 * 	@param 	*generalSBGC - serial connection descriptor
 *	@param	*gyroCorrection - structure with written
 *			gyroscope zero bias parameters
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CorrectionGyro (GeneralSBGC_t *generalSBGC, const GyroCorrection_t *gyroCorrection)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_GYRO_CORRECTION);
	WriteBuff(&cmd, gyroCorrection, sizeof(GyroCorrection_t), PM_GYRO_CORRECTION);
	SBGC32_TX(generalSBGC, &cmd);
	/* no need confirmation */
	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	AHRS_Helper
 * 	@{
 */
/**	@brief	Send or request attitude of the IMU sensor
 *
 *	@attention	The AHRS_Helper_t.mode parameter must be
 *				1-byte size (ui8) when working with SimpleBGC
 *				controllers in which the firmware is below 2.69b5
 *
 *	@note	Parameter AHRS_Helper_t.mode is very
 *			important for this command\n
 *			For more, see the CMD_AHRS_HELPER command description in the
 *			<a href=https://www.basecamelectronics.com/serialapi/>
 * 			SimpleBGC32 Serial API protocol specification</a>\n
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*AHRS_Helper - structure for data exchange
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_CallAHRS_Helper (GeneralSBGC_t *generalSBGC, AHRS_Helper_t *AHRS_Helper)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_AHRS_HELPER);
	WriteBuff(&cmd, AHRS_Helper, sizeof(AHRS_Helper_t), PM_AHRS_HELPER);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_AHRS_HELPER), "AHRS Helper:") == TX_RX_OK)
	{
		AHRS_Helper->Z_Vect[AXIS_X] = ReadLong(&cmd);
		AHRS_Helper->Z_Vect[AXIS_Y] = ReadLong(&cmd);
		AHRS_Helper->Z_Vect[AXIS_Z] = ReadLong(&cmd);
		AHRS_Helper->H_Vect[AXIS_X] = ReadLong(&cmd);
		AHRS_Helper->H_Vect[AXIS_Y] = ReadLong(&cmd);
		AHRS_Helper->H_Vect[AXIS_Z] = ReadLong(&cmd);

		/* or FOR_(i, 6) ReadLong(&cmd); */
	}

	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Helper_Data
 * 	@{
 */
/**	@brief	Provides helper data for the AHRS system
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*helperData - prepared helper data structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ProvideHelperData (GeneralSBGC_t *generalSBGC, HelperData_t *helperData)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_HELPER_DATA);
	WriteBuff(&cmd, helperData, sizeof(HelperData_t), PM_HELPER_DATA);
	SBGC32_TX(generalSBGC, &cmd);
	/* no need confirmation */
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Provides extended helper data for the AHRS system
 *
 *	@attention	Firmware: 2.60+
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*helperDataExt - prepared extended helper data structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ProvideHelperDataExt (GeneralSBGC_t *generalSBGC, HelperDataExt_t *helperDataExt)
{
	if (generalSBGC->_firmwareVersion < 2600)
		return NOT_SUPPORTED_BY_FIRMWARE;

	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_HELPER_DATA);
	WriteBuff(&cmd, helperDataExt, sizeof(HelperDataExt_t), PM_HELPER_DATA_EXT);
	SBGC32_TX(generalSBGC, &cmd);
	/* no need confirmation */
	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */

#endif /* SBGC_IMU_MODULE */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
