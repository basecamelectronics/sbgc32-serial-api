/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2
 *
 *	@file		imu.c
 *
 *	@brief		IMU source file
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

#include "../../sbgc32.h"


#if (SBGC_IMU_MODULE)

#if (SBGC_USES_REF_INFO)

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *					Big Endian Mapping and Reference Info Structures
	 */
	/**	@addtogroup	Ext_IMU_Debug_Info
	*	@{
	*/
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t extIMU_DebugInfoReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Main IMU Ref Src",			sbgcUCHAR						),  // 0
		PARAM_BLOCK_(	"Frame IMU Ref Src",		sbgcUCHAR						),  // 1
		PARAM_BLOCK_(	"Main IMU Z Ref Err",		sbgcUCHAR						),  // 2
		PARAM_BLOCK_(	"Main IMU H Ref Err",		sbgcUCHAR						),  // 3
		PARAM_BLOCK_(	"Frame IMU Z Ref Err",		sbgcUCHAR						),  // 4
		PARAM_BLOCK_(	"Frame IMU H Ref Err",		sbgcUCHAR						),  // 5
		PARAM_BLOCK_(	"Ext IMU Status",			sbgcUCHAR						),  // 6
		PARAM_BLOCK_(	"Ext IMU Packets Received Cnt",
													sbgcUSHORT						),  // 7
		PARAM_BLOCK_(	"Ext IMU Parse Err Cnt",	sbgcUSHORT						),  // 8
		PARAM_BLOCK_(	"Ext Corr H Ref",			sbgcUCHAR						),  // 9
		PARAM_BLOCK_(	"Ext Corr Z Ref",			sbgcUCHAR						),  // 10
		PARAMS_BLOCK_(	"Reserved",					sbgcRCHAR,					13	),  // 11
		PARAMS_BLOCK_(	"DCM",						sbgcFLOAT,					9	),  // 12
		PARAMS_BLOCK_(	"Acc Body",					sbgcFLOAT,					3	),  // 13

	};

	const ui8 extIMU_DebugInfoReferenceInfoArrayElCnt = countof_(extIMU_DebugInfoReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Gyro_Correction
	 *	@{
	 */
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t gyroCorrectionReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"IMU Type",					sbgcUCHAR						),  // 0
		PARAMS_BLOCK_(	"Gyro Zero Corr",			sbgcUCHAR,					3	),  // 1
		PARAM_BLOCK_(	"Gyro Zero Heading Corr",	sbgcUCHAR						),  // 2

	};

	const ui8 gyroCorrectionReferenceInfoArrayElCnt = countof_(gyroCorrectionReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	AHRS_Helper
	 *	@{
	 */
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t AHRS_HelperReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Mode",						sbgcUSHORT						),  // 0
		PARAMS_BLOCK_(	"Z Vector",					sbgcFLOAT,					3	),  // 1
		PARAMS_BLOCK_(	"H Vector",					sbgcFLOAT,					3	),  // 2

	};

	const ui8 AHRS_HelperReferenceInfoArrayElCnt = countof_(AHRS_HelperReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Helper_Data
	 *	@{
	 */
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t helperDataReferenceInfoArray [] =
	{
		PARAMS_BLOCK_(	"Frame Acc",				sbgcSHORT,					3	),  // 0
		PARAM_BLOCK_(	"Frame Angle Roll",			sbgcSHORT						),  // 1
		PARAM_BLOCK_(	"Frame Angle Pitch",		sbgcSHORT						),  // 2

	};

	const ui8 helperDataReferenceInfoArrayElCnt = countof_(helperDataReferenceInfoArray);


	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t helperDataExtReferenceInfoArray [] =
	{
		PARAMS_BLOCK_(	"Frame Acc",				sbgcSHORT,					3	),  // 0
		PARAM_BLOCK_(	"Frame Angle Roll",			sbgcSHORT						),  // 1
		PARAM_BLOCK_(	"Frame Angle Pitch",		sbgcSHORT						),  // 2

		PARAM_BLOCK_(	"Flags",					sbgcUCHAR						),  // 3
		PARAMS_BLOCK_(	"Frame Speed",				sbgcSHORT,					3	),  // 4
		PARAM_BLOCK_(	"Frame Heading",			sbgcSHORT						),  // 5
		PARAM_BLOCK_(	"Reserved",					sbgcRCHAR						),  // 6

	};

	const ui8 helperDataExtReferenceInfoArrayElCnt = countof_(helperDataExtReferenceInfoArray);
	/**	@}
	 */

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	Ext_IMU_Debug_Info
 *	@{
 */
/**	@brief	Requests debug information for the external IMU sensor
 *
 *	####	TX —> CMD_EXT_IMU_DEBUG_INFO :	with no payload
 *	####	RX <— CMD_EXT_IMU_DEBUG_INFO :	74 bytes
 *
 *	@pre	Board requirements:\n
 *			EXT_IMU = (1 << 16) (ext.)
 *
 *	@post	Use the @ref DebugSBGC32_PrintWholeStruct
 *			function with PM_EXT_IMU_DEBUG_INFO to print
 *			received data
 *
 *	@attention	Firmware: 2.66+
 *
 *	@code

			sbgcExtIMU_DebugInfo_t ExtIMU_DebugInfo;

			SBGC32_RequestExtIMU_DebugInfo(&SBGC32_Device, &ExtIMU_DebugInfo);

			#if (SBGC_NEED_DEBUG && SBGC_NEED_REF_INFO)
				DebugSBGC32_PrintWholeStruct(&SBGC32_Device, &ExtIMU_DebugInfo, PM_EXT_IMU_DEBUG_INFO);
			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*extIMU_DebugInfo - structure to storing
 *			information about external IMU sensor
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_RequestExtIMU_DebugInfo (sbgcGeneral_t *gSBGC, sbgcExtIMU_DebugInfo_t *extIMU_DebugInfo
													/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2660)
	sbgcAssertFeature(BF_EXT_IMU)

	gSBGC->_api->startWrite(gSBGC, CMD_EXT_IMU_DEBUG_INFO SBGC_ADVANCED_ARGS__);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_EXT_IMU_DEBUG_INFO SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, NULL, extIMU_DebugInfo, sizeof(sbgcExtIMU_DebugInfo_t));
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Ext_IMU_Cmd
 *	@{
 */
/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_SendCmdToExtIMU function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostSendCmdToExtIMU (sbgcGeneral_t *gSBGC)
{
	serialAPI_Command_t *cmdFromIMU = (serialAPI_Command_t*)curCmdDest_;

	if (curCmd_->_destinationSize < (curCmd_->_payloadSize - 1))
		SerialAPI_FatalErrorHandler();

	cmdFromIMU->_commandID = gSBGC->_api->readByte(gSBGC);
	gSBGC->_api->readBuff(gSBGC, cmdFromIMU->_payload, curCmd_->_payloadSize - 1);

	/* Later it'll be advanced external IMU command parser */
}

/**	@brief	Performs data exchange between the gimbal
 *			and an external IMU sensor
 *
 *	####	TX —> CMD_EXT_IMU_CMD (opt.) :	1 + sbgcExtIMU_Command_t.payloadSize bytes
 *	####	RX <— CMD_EXT_IMU_CMD (opt.) :	1 + sbgcExtIMU_Command_t.payloadSize bytes
 *
 *	@pre	The whole dataStruct always must be exact filled.\n
 *			For more, see the CMD_EXT_IMU_CMD command in the
 *			SimpleBGC32 Serial API protocol specification:
 *			https://www.basecamelectronics.com/serialapi/
 *
 *	@pre	sbgcExtIMU_Command_t.payloadSize must be filled
 *			to prevent payload buffer overflow when
 *			receiving the serial command
 *
 *	@pre	Board requirements:\n
 *			EXT_IMU = (1 << 16) (ext.)
 *
 *	@code

			#define SBGC_EXT_IMU_CMD_PAYLOAD_SIZE 42

			sbgcExtIMU_Command_t CmdToIMU;
			ui8 payload [SBGC_EXT_IMU_CMD_PAYLOAD_SIZE];

			CmdToIMU.commandID = IMU_CMD_GET_DEVICE_INFO;
			CmdToIMU.payloadSize = countof_(payload);
			CmdToIMU.payload = payload;

			SBGC32_SendCmdToExtIMU(&SBGC32_Device, &CmdToIMU, EXT_IMU_CMD_TYPE_TX_RX);

			// Upon receiving the command, the CmdToIMU.commandID and payload[] values will be overwritten

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*cmdToIMU - serial command to external IMU
 *	@param	cmdType - direction of external IMU command
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SendCmdToExtIMU (sbgcGeneral_t *gSBGC, sbgcExtIMU_Command_t *cmdToIMU, sbgcExtIMU_CommandType_t cmdType
											/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFeature(BF_EXT_IMU)

	if (cmdType == EXT_IMU_CMD_TYPE_TX)
	{
		gSBGC->_api->startWrite(gSBGC, CMD_EXT_IMU_CMD SBGC_ADVANCED_ARGS__);
		gSBGC->_api->writeByte(gSBGC, cmdToIMU->commandID);
		gSBGC->_api->writeBuff(gSBGC, cmdToIMU->payload, cmdToIMU->payloadSize);
		gSBGC->_api->finishWrite(gSBGC);
	}

	else if (cmdType == EXT_IMU_CMD_TYPE_RX)
	{
		/* It's necessary to lock SerialAPI before Rx operation */
		serialAPI_LockRead()

		gSBGC->_api->startRead(gSBGC, CMD_EXT_IMU_CMD SBGC_ADVANCED_ARGS__);
		gSBGC->_api->assignEvent(gSBGC, PostSendCmdToExtIMU, cmdToIMU, cmdToIMU->payloadSize);
		gSBGC->_api->finishRead(gSBGC);
	}

	else  // EXT_IMU_CMD_TYPE_TX_RX
	{
		gSBGC->_api->startWrite(gSBGC, CMD_EXT_IMU_CMD SBGC_ADVANCED_ARGS__);
		gSBGC->_api->writeByte(gSBGC, cmdToIMU->commandID);
		gSBGC->_api->writeBuff(gSBGC, cmdToIMU->payload, cmdToIMU->payloadSize);
		gSBGC->_api->finishWrite(gSBGC);

		gSBGC->_api->startRead(gSBGC, CMD_EXT_IMU_CMD SBGC_ADVANCED_ARGS__);
		gSBGC->_api->assignEvent(gSBGC, PostSendCmdToExtIMU, cmdToIMU, cmdToIMU->payloadSize);
		gSBGC->_api->finishRead(gSBGC);

		gSBGC->_api->link(gSBGC);
	}

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_SendCmdToExtSens function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostSendCmdToExtSens (sbgcGeneral_t *gSBGC)
{
	serialAPI_Command_t *cmdFromSens = (serialAPI_Command_t*)curCmdDest_;

	if (curCmd_->_destinationSize < (curCmd_->_payloadSize - 1))
		SerialAPI_FatalErrorHandler();

	cmdFromSens->_commandID = gSBGC->_api->readByte(gSBGC);
	gSBGC->_api->readBuff(gSBGC, cmdFromSens->_payload, curCmd_->_payloadSize - 1);

	/* Later it'll be advanced external sensor command parser */
}

/**	@brief	Forwards message to the GPS_IMU sensor
 *
 *	@attention	Firmware: 2.68b7+ ("Extended" family only)
 *
 *	####	TX —> CMD_EXT_SENS_CMD (opt.) :	1 + sbgcExtIMU_Command_t.payloadSize bytes
 *	####	RX <— CMD_EXT_SENS_CMD (opt.) :	1 + sbgcExtIMU_Command_t.payloadSize bytes
 *
 *	@pre	The whole dataStruct always must be exact filled.\n
 *			For more, see the CMD_EXT_SENS_CMD command in the
 *			SimpleBGC32 Serial API protocol specification:
 *			https://www.basecamelectronics.com/serialapi/
 *
 *	@pre	sbgcExtIMU_Command_t.payloadSize must be filled
 *			to prevent payload buffer overflow when
 *			receiving the serial command
 *
 *	@pre	Board requirements:\n
 *			EXT_IMU = (1 << 16) (ext.)
 *
 *	@note	This function is similar to
 *			@ref SBGC32_SendCmdToExtIMU. Refer to its
 *			documentation for code example details
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*cmdToSens - serial command to external sensor
 *	@param	flags - additional command flags
 *	@param	cmdType - direction of external sensor command
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SendCmdToExtSens (sbgcGeneral_t *gSBGC, sbgcExtIMU_Command_t *cmdToSens, sbgcExtSensCommandFlag_t flags,
											 sbgcExtIMU_CommandType_t cmdType
											 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertBoardVer(36)
	sbgcAssertFrwVer(2687)
	sbgcAssertFeature(BF_EXT_IMU)

	if (cmdType == EXT_IMU_CMD_TYPE_TX)
	{
		gSBGC->_api->startWrite(gSBGC, CMD_EXT_SENS_CMD SBGC_ADVANCED_ARGS__);
		gSBGC->_api->writeByte(gSBGC, flags);
		gSBGC->_api->writeByte(gSBGC, cmdToSens->commandID);
		gSBGC->_api->writeBuff(gSBGC, cmdToSens->payload, cmdToSens->payloadSize);
		gSBGC->_api->finishWrite(gSBGC);
	}

	else if (cmdType == EXT_IMU_CMD_TYPE_RX)
	{
		/* It's necessary to lock SerialAPI before Rx operation */
		serialAPI_LockRead()

		gSBGC->_api->startRead(gSBGC, CMD_EXT_SENS_CMD SBGC_ADVANCED_ARGS__);
		gSBGC->_api->assignEvent(gSBGC, PostSendCmdToExtSens, cmdToSens, cmdToSens->payloadSize);
		gSBGC->_api->finishRead(gSBGC);
	}

	else  // EXT_IMU_CMD_TYPE_TX_RX
	{
		gSBGC->_api->startWrite(gSBGC, CMD_EXT_SENS_CMD SBGC_ADVANCED_ARGS__);
		gSBGC->_api->writeByte(gSBGC, flags);
		gSBGC->_api->writeByte(gSBGC, cmdToSens->commandID);
		gSBGC->_api->writeBuff(gSBGC, cmdToSens->payload, cmdToSens->payloadSize);
		gSBGC->_api->finishWrite(gSBGC);

		gSBGC->_api->startRead(gSBGC, CMD_EXT_SENS_CMD SBGC_ADVANCED_ARGS__);
		gSBGC->_api->assignEvent(gSBGC, PostSendCmdToExtSens, cmdToSens, cmdToSens->payloadSize);
		gSBGC->_api->finishRead(gSBGC);

		gSBGC->_api->link(gSBGC);
	}

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Gyro_Correction
 *	@{
 */
/**	@brief	Corrects the gyroscope sensor's zero bias manually
 *
 *	####	TX —> CMD_GYRO_CORRECTION :		9 bytes
 *
 *	@code

			sbgcGyroCorrection_t GyroCorrection = { 0 };
			i16 gyroZeroCorr [] = { x, y, z };
			// where x, y, z are zero offset for each axis. Units: 0.001 gyro sensor unit

			GyroCorrection.IMU_Type = sbgcIMU_TYPE_MAIN - 1;
			memcpy(GyroCorrection.gyroZeroCorr, gyroZeroCorr, sizeof(gyroZeroCorr));

			SBGC32_CorrectionGyro(&SBGC32_Device, &GyroCorrection);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*gyroCorrection - structure with written
 *			gyroscope zero bias parameters
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_CorrectionGyro (sbgcGeneral_t *gSBGC, const sbgcGyroCorrection_t *gyroCorrection
										   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_GYRO_CORRECTION SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeBuff(gSBGC, gyroCorrection, sizeof(sbgcGyroCorrection_t));
	gSBGC->_api->finishWrite(gSBGC);
	/* No need confirmation */

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	AHRS_Helper
 *	@{
 */
/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_CallAHRS_Helper function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostCallAHRS_Helper (sbgcGeneral_t *gSBGC)
{
	sbgcAHRS_Helper_t *AHRS_Helper = (sbgcAHRS_Helper_t*)curCmdDest_;

	AHRS_Helper->Z_Vector[SBGC_X] = (float)gSBGC->_api->readLong(gSBGC);
	AHRS_Helper->Z_Vector[SBGC_Y] = (float)gSBGC->_api->readLong(gSBGC);
	AHRS_Helper->Z_Vector[SBGC_Z] = (float)gSBGC->_api->readLong(gSBGC);
	AHRS_Helper->H_Vector[SBGC_X] = (float)gSBGC->_api->readLong(gSBGC);
	AHRS_Helper->H_Vector[SBGC_Y] = (float)gSBGC->_api->readLong(gSBGC);
	AHRS_Helper->H_Vector[SBGC_Z] = (float)gSBGC->_api->readLong(gSBGC);
}

/**	@brief	Send or request attitude of the IMU sensor
 *
 *	####	TX —> CMD_AHRS_HELPER :	26 bytes (frw. ver. prior to 2.69b5 - 25 bytes)
 *	####	RX <— CMD_AHRS_HELPER :	24 bytes
 *
 *	@attention	The sbgcAHRS_Helper_t.mode parameter must be
 *				1-byte size (ui8) when working with SimpleBGC
 *				controllers in which the firmware is below 2.69b5
 *
 *	@pre	Parameter AHRS_Helper_t.mode is very
 *			important for this command.\n
 *			For more, see the CMD_AHRS_HELPER command description
 *			in the SimpleBGC32 Serial API protocol specification
 *			https://www.basecamelectronics.com/serialapi/
 *
 *	@code

			sbgcAHRS_Helper_t AHRS_Helper;
			ui16 mode = ParserSBGC32_PackAHRS_HelperMode(AHRSHMD_GET, AHRSHML_FRAME,
														 AHRSHMC_BOTH_VECTORS, AHRSHMT_TRANSLATE_BOTH_VECTORS,
														 AHRSHMR_SAME_AS_FRAME_IMU, AHRSHMO_NO_ANOTHER_FLAGS);

			SBGC32_CallAHRS_Helper(&SBGC32_Device, &AHRS_Helper, mode);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*AHRS_Helper - structure for data exchange
 *	@param	mode - a complex variable. For more, see
 *			@ref ParserSBGC32_PackAHRS_HelperMode function
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_CallAHRS_Helper (sbgcGeneral_t *gSBGC, sbgcAHRS_Helper_t *AHRS_Helper, ui16 mode
											/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_AHRS_HELPER SBGC_ADVANCED_ARGS__);

	if (gSBGC->_api->baseFirmwareVersion >= 2695)
		gSBGC->_api->writeWord(gSBGC, mode);

	else
		gSBGC->_api->writeByte(gSBGC, mode);

	if (mode & AHRSHMD_SET)
	{
		gSBGC->_api->writeBuff(gSBGC, AHRS_Helper, sizeof(sbgcAHRS_Helper_t));
		gSBGC->_api->finishWrite(gSBGC);
	}

	else
	{
		gSBGC->_api->finishWrite(gSBGC);

		gSBGC->_api->startRead(gSBGC, CMD_AHRS_HELPER SBGC_ADVANCED_ARGS__);
		gSBGC->_api->assignEvent(gSBGC, PostCallAHRS_Helper, AHRS_Helper, sizeof(sbgcAHRS_Helper_t));
		gSBGC->_api->finishRead(gSBGC);

		gSBGC->_api->link(gSBGC);
	}

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Helper_Data
 *	@{
 */
/**	@brief	Provides helper data for the AHRS system
 *
 *	####	TX —> CMD_HELPER_DATA :	10 bytes
 *
 *	@attention	Firmware: prior to 2.60
 *
 *	@code

			if (SerialAPI_GetFirmwareVersion(&SBGC32_Device) >= 2600)
				donothing_;  // Use the SBGC32_ProvideHelperDataExt function

			sbgcHelperData_t HelperData = { 0 };

			HelperData.frameAngleRoll = sbgcAngleToDegree(-3);
			HelperData.frameAnglePitch = sbgcAngleToDegree(2);

			SBGC32_ProvideHelperData(&SBGC32_Device, &HelperData);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*helperData - prepared helper data structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ProvideHelperData (sbgcGeneral_t *gSBGC, sbgcHelperData_t *helperData
											  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	#if (SBGC_NEED_ASSERTS)

		if (gSBGC->_api->baseFirmwareVersion >= 2600)
		{
			gSBGC->_lastCommandStatus = sbgcCOMMAND_NOT_SUPPORTED_BY_FIRMWARE;
			return sbgcCOMMAND_NOT_SUPPORTED_BY_FIRMWARE;
		}

	#endif

	gSBGC->_api->startWrite(gSBGC, CMD_HELPER_DATA SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeBuff(gSBGC, helperData, sizeof(sbgcHelperData_t));
	gSBGC->_api->finishWrite(gSBGC);
	/* No need confirmation */

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Provides extended helper data for the AHRS system
 *
 *	####	TX —> CMD_HELPER_DATA :	20 bytes
 *
 *	@attention	Firmware: 2.60+
 *
 *	@code

			if (SerialAPI_GetFirmwareVersion(&SBGC32_Device) < 2600)
				donothing_;  // Use the SBGC32_ProvideHelperData function

			sbgcHelperDataExt_t HelperDataExt = { 0 };

			HelperDataExt.frameAngleRoll = sbgcAngleToDegree(-3);
			HelperDataExt.frameAnglePitch = sbgcAngleToDegree(2);
			HelperDataExt.flags = HDF_COORD_SYS_GROUND;
			HelperDataExt.frameHeading = sbgcAngleToDegree(5);

			SBGC32_ProvideHelperDataExt(&SBGC32_Device, &HelperDataExt);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*helperDataExt - prepared extended helper data structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ProvideHelperDataExt (sbgcGeneral_t *gSBGC, sbgcHelperDataExt_t *helperDataExt
												 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2600)

	gSBGC->_api->startWrite(gSBGC, CMD_HELPER_DATA SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeBuff(gSBGC, helperDataExt, sizeof(sbgcHelperDataExt_t));
	gSBGC->_api->finishWrite(gSBGC);
	/* No need confirmation */

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */

#endif /* SBGC_IMU_MODULE */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
