/** ____________________________________________________________________
 *
 *	@file		imu.c
 *
 *	@brief 		IMU source file
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

#include "imu.h"


#ifdef	SYS_BIG_ENDIAN

	extern AHRS_DebugInfo_t AHRS_DebugInfo_ParserStruct;


	/**	@addtogroup	Ext_IMU_Debug_Info
	* 	@{
	*/
	/** @brief	Sample for Big Endian Mapping
	 *
	 * 	@ref	ExtIMU_DebugInfo_ParserStructDB
	 */
	const ExtIMU_DebugInfo_t extIMU_DebugInfo_ParserStruct;

	const ParserBlock_t ExtIMU_DebugInfo_ParserStructDB [] =
	{
		VAR_BLOCK(AHRS_DebugInfo_ParserStruct.mainIMU_RefSrc),
		VAR_BLOCK(AHRS_DebugInfo_ParserStruct.frameIMU_RefSrc),
		VAR_BLOCK(AHRS_DebugInfo_ParserStruct.mainIMU_Z_RefErr),
		VAR_BLOCK(AHRS_DebugInfo_ParserStruct.mainIMU_H_RefErr),
		VAR_BLOCK(AHRS_DebugInfo_ParserStruct.frameIMU_Z_RefErr),
		VAR_BLOCK(AHRS_DebugInfo_ParserStruct.frameIMU_H_RefErr),
		VAR_BLOCK(AHRS_DebugInfo_ParserStruct.extIMU_Status),
		VAR_BLOCK(AHRS_DebugInfo_ParserStruct.extIMU_PacketsReceivedCnt),
		VAR_BLOCK(AHRS_DebugInfo_ParserStruct.extIMU_ParseErrCnt),
		VAR_BLOCK(AHRS_DebugInfo_ParserStruct.extCorrH_Ref),
		VAR_BLOCK(AHRS_DebugInfo_ParserStruct.extCorrZ_Ref),
		DATA_BLOCK(AHRS_DebugInfo_ParserStruct.reserved),
		DATA_BLOCK(extIMU_DebugInfo_ParserStruct.DCM),
		DATA_BLOCK(extIMU_DebugInfo_ParserStruct.ACC_Body),
	};

	const ui8 ExtIMU_DebugInfo_ParserStructDB_Size = countof(ExtIMU_DebugInfo_ParserStructDB);
	/**	@}
	 */


	/**	@addtogroup	Gyro_Correction
	 * 	@{
	 */
	/** @brief	Sample for Big Endian Mapping
	 *
	 * 	@ref	GyroCorrection_ParserStructDB
	 */
	const GyroCorrection_t gyroCorrection_ParserStruct;

	const ParserBlock_t GyroCorrection_ParserStructDB [] =
	{
		VAR_BLOCK(gyroCorrection_ParserStruct.IMU_Type),
		DATA_BLOCK(gyroCorrection_ParserStruct.gyroZeroCorr),
		VAR_BLOCK(gyroCorrection_ParserStruct.gyroZeroHeadingCorr),
	};

	const ui8 GyroCorrection_ParserStructDB_Size = countof(GyroCorrection_ParserStructDB);
	/**	@}
	 */


	/**	@addtogroup	AHRS_Helper
	 * 	@{
	 */
	/** @brief	Sample for Big Endian Mapping
	 *
	 * 	@ref	AHRS_Helper_ParserStructDB
	 */
	const AHRS_Helper_t AHRS_Helper_ParserStruct;

	const ParserBlock_t AHRS_Helper_ParserStructDB [] =
	{
		VAR_BLOCK(AHRS_Helper_ParserStruct.mode),
		DATA_BLOCK(AHRS_Helper_ParserStruct.Z_Vect),
		DATA_BLOCK(AHRS_Helper_ParserStruct.H_Vect),
	};

	const ui8 AHRS_Helper_ParserStructDB_Size = countof(AHRS_Helper_ParserStructDB);
	/**	@}
	 */


	/**	@addtogroup	Helper_Data
	 * 	@{
	 */
	/** @brief	Sample for Big Endian Mapping
	 *
	 * 	@ref	HelperData_ParserSrtructDB \n
	 * 	@ref	HelperDataExt_ParserSrtructDB
	 */
	const HelperDataExt_t HelperData_ParserSrtruct;

	const ParserBlock_t HelperData_ParserStructDB [] =
	{
		DATA_BLOCK(HelperData_ParserSrtruct.frameACC),
		VAR_BLOCK(HelperData_ParserSrtruct.frameAngleRoll),
		VAR_BLOCK(HelperData_ParserSrtruct.frameAnglePitch),
	};

	const ui8 HelperData_ParserStructDB_Size = countof(HelperData_ParserStructDB);


	const ParserBlock_t HelperDataExt_ParserStructDB [] =
	{
		DATA_BLOCK(HelperData_ParserSrtruct.frameACC),
		VAR_BLOCK(HelperData_ParserSrtruct.frameAngleRoll),
		VAR_BLOCK(HelperData_ParserSrtruct.frameAnglePitch),
		VAR_BLOCK(HelperData_ParserSrtruct.flags),
		DATA_BLOCK(HelperData_ParserSrtruct.frameSpeed),
		VAR_BLOCK(HelperData_ParserSrtruct.frameHeading),
		VAR_BLOCK(HelperData_ParserSrtruct.reserved),
	};

	const ui8 HelperDataExt_ParserStructDB_Size = countof(HelperDataExt_ParserStructDB);
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
	if (generalSBGC->_firmwareVersion < 2660)
		return NOT_SUPPORTED_BY_FIRMWARE;

	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_EXT_IMU_DEBUG_INFO);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_EXT_IMU_DEBUG_INFO), "External IMU Debug Info:") == TX_RX_OK)
		ReadBuff(&cmd, extIMU_DebugInfo, sizeof(ExtIMU_DebugInfo_t), PM_EXT_IMU_DEBUG_INFO);

	return generalSBGC->_ParserCurrentStatus;
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

	return generalSBGC->_ParserCurrentStatus;
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
	return generalSBGC->_ParserCurrentStatus;
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

	return generalSBGC->_ParserCurrentStatus;
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
	return generalSBGC->_ParserCurrentStatus;
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
	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
