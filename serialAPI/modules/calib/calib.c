/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.1
 *
 *	@file		calib.c
 *
 *	@brief		Calibration source file
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

#include "../../sbgc32.h"


#if (SBGC_CALIB_MODULE)

/* Borrowed Functions  -------------------------------------------------
 */
extern sbgcCommandStatus_t SBGC32_SendEmptyCommand (sbgcGeneral_t *gSBGC, serialAPI_CommandID_t cmdID
													/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */);


#if (SBGC_USES_REF_INFO)

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *					Big Endian Mapping and Reference Info Structures
	 */
	/**	@addtogroup	Calib_IMU
	 *	@{
	 */
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t IMU_ExtCalibReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"IMU IDx",					sbgcUCHAR						),  // 0
		PARAM_BLOCK_(	"Action",					sbgcUCHAR						),  // 1
		PARAM_BLOCK_(	"Time Ms",					sbgcUSHORT						),  // 2
		PARAMS_BLOCK_(	"Reserved",					sbgcRCHAR,					8	),  // 3

	};

	const ui8 IMU_ExtCalibReferenceInfoArrayElCnt = countof_(IMU_ExtCalibReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Calib_IMU_Info
	 *	@{
	 */
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t calibInfoReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Progress",					sbgcUCHAR						),  // 0
		PARAM_BLOCK_(	"IMU Type",					sbgcUCHAR						),  // 1
		PARAMS_BLOCK_(	"Acc Data",					sbgcSHORT,					3	),  // 2
		PARAM_BLOCK_(	"Gyro ABS Val",				sbgcUSHORT						),  // 3
		PARAM_BLOCK_(	"Acc Cur Axis",				sbgcUCHAR						),  // 4
		PARAM_BLOCK_(	"Acc Limits Info",			sbgcUCHAR						),  // 5
		PARAM_BLOCK_(	"IMU Temp Cels",			sbgcCHAR						),  // 6
		PARAM_BLOCK_(	"Temp Calib Gyro Enabled",	sbgcUCHAR						),  // 7
		PARAM_BLOCK_(	"Temp Calib Gyro T Min Cels",
													sbgcCHAR						),  // 8
		PARAM_BLOCK_(	"Temp Calib Gyro T Max Cels",
													sbgcCHAR						),  // 9
		PARAM_BLOCK_(	"Temp Calib Acc Enabled",	sbgcUCHAR						),  // 10
		PARAMS_BLOCK_(	"Temp Calib Acc Slot Num",	sbgcUCHAR,					6	),  // 11
		PARAM_BLOCK_(	"Temp Calib Acc T Min Cels",
													sbgcCHAR						),  // 12
		PARAM_BLOCK_(	"Temp Calib Acc T Max Cels",
													sbgcCHAR						),  // 13
		PARAM_BLOCK_(	"H Err Length",				sbgcUCHAR						),  // 14
		PARAMS_BLOCK_(	"Reserved",					sbgcRCHAR,					7	),  // 15

	};

	const ui8 calibInfoReferenceInfoArrayElCnt = countof_(calibInfoReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Calib_Other
	 *	@{
	 */
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t calibCoggingReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Action",					sbgcUCHAR						),  // 0
		PARAM_BLOCK_(	"Axis to Calibrate",		sbgcUCHAR						),  // 1
		PARAM_BLOCK_(	"Angle [ROLL]",				sbgcSHORT						),  // 2
		PARAM_BLOCK_(	"Smooth [ROLL]",			sbgcCHAR						),  // 3
		PARAM_BLOCK_(	"Speed [ROLL]",				sbgcCHAR						),  // 4
		PARAM_BLOCK_(	"Period [ROLL]",			sbgcSHORT						),  // 5
		PARAMS_BLOCK_(	"Reserved [ROLL]",			sbgcRCHAR,					9	),  // 6
		PARAM_BLOCK_(	"Angle [PITCH]",			sbgcSHORT						),  // 7
		PARAM_BLOCK_(	"Smooth [PITCH]",			sbgcCHAR						),  // 8
		PARAM_BLOCK_(	"Speed [PITCH]",			sbgcCHAR						),  // 9
		PARAM_BLOCK_(	"Period [PITCH]",			sbgcSHORT						),  // 10
		PARAMS_BLOCK_(	"Reserved [PITCH]",			sbgcRCHAR,					9	),  // 11
		PARAM_BLOCK_(	"Angle [YAW]",				sbgcSHORT						),  // 12
		PARAM_BLOCK_(	"Smooth [YAW]",				sbgcCHAR						),  // 13
		PARAM_BLOCK_(	"Speed [YAW]",				sbgcCHAR						),  // 14
		PARAM_BLOCK_(	"Period [YAW]",				sbgcSHORT						),  // 15
		PARAMS_BLOCK_(	"Reserved [YAW]",			sbgcRCHAR,					9	),  // 16

	};

	const ui8 calibCoggingReferenceInfoArrayElCnt = countof_(calibCoggingReferenceInfoArray);
	/**	@}
	 */

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	Calib_IMU
 *	@{
 */
/**	@brief	Calibrates accelerometer
 *
 *	####	TX —> CMD_CALIB_ACC		with no payload
 *
 *	@pre	It's possible to initially select the sensor by the
 *			@ref SBGC32_SelectIMU_3 function.
 *			For accelerometer calibration, the gimbal must be
 *			fixed in a specific position
 *
 *	@code

			// Select the required sensor (optional)
			SBGC32_SelectIMU_3(&SBGC32_Device, sbgcIMU_TYPE_MAIN, SIMUA_SIMPLE_SELECT, 0, SBGC_NO_CONFIRM);

			// Start calibration
			SBGC32_CalibAcc(&SBGC32_Device);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_CalibAcc (sbgcGeneral_t *gSBGC
									 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	return SBGC32_SendEmptyCommand(gSBGC, CMD_CALIB_ACC SBGC_ADVANCED_ARGS__);
}


/**	@brief	Calibrates gyroscope
 *
 *	####	TX —> CMD_CALIB_GYRO	with no payload
 *
 *	@pre	It's possible to initially select the sensor by the
 *			@ref SBGC32_SelectIMU_3 function.
 *			For gyroscope calibration, try to achieve the most
 *			stationary position of the gimbal
 *
 *	@code

			// Select the required sensor (optional)
			SBGC32_SelectIMU_3(&SBGC32_Device, sbgcIMU_TYPE_MAIN, SIMUA_SIMPLE_SELECT, 0, SBGC_NO_CONFIRM);

			// Start calibration
			SBGC32_CalibGyro(&SBGC32_Device);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_CalibGyro (sbgcGeneral_t *gSBGC
									  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	return SBGC32_SendEmptyCommand(gSBGC, CMD_CALIB_GYRO SBGC_ADVANCED_ARGS__);
}


/**	@brief	Calibrates magnetometer
 *
 *	####	TX —> CMD_CALIB_MAG		with no payload
 *
 *	@pre	It's possible to initially select the sensor by the
 *			@ref SBGC32_SelectIMU_3 function.
 *			Before performing the calibration, review the
 *			instructions provided in the User Manual,
 *			paragraph 16. Magnetometer sensor:
 *			https://www.basecamelectronics.com/files/v3/SimpleBGC_32bit_manual_eng.pdf
 *
 *	@code

			// Select the required sensor (optional)
			SBGC32_SelectIMU_3(&SBGC32_Device, sbgcIMU_TYPE_MAIN, SIMUA_SIMPLE_SELECT, 0, SBGC_NO_CONFIRM);

			// Start calibration
			SBGC32_CalibMag(&SBGC32_Device);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_CalibMag (sbgcGeneral_t *gSBGC
									 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFeature(BF_MAG_SENSOR)

	return SBGC32_SendEmptyCommand(gSBGC, CMD_CALIB_MAG SBGC_ADVANCED_ARGS__);
}


/**	@brief	Extended format of accelerometer calibration
 *
 *	####	TX —> CMD_CALIB_ACC :	12 bytes
 *
 *	@pre	For accelerometer calibration, the gimbal must be
 *			fixed in a specific position
 *
 *	@post	If all parameters are valid, confirmation
 *			is sent immediately on reception and in
 *			the end of calibration. This function
 *			handle only start calibration confirmation.
 *			Call the @ref SBGC32_CheckConfirmation function
 *			passing it the CMD_CALIB_ACC argument
 *
 *	@code

			sbgcIMU_ExtCalib_t IMU_ExtCalib = { 0 };

			// Choose the main IMU for calibration procedure
			IMU_ExtCalib.IMU_IDx = sbgcIMU_TYPE_MAIN;
			IMU_ExtCalib.action = IMUECA_DO_REGULAR_CALIBRATION;

			// Start calibration
			SBGC32_CalibAccExt(&SBGC32_Device, &IMU_ExtCalib, SBGC_NO_CONFIRM);

			#if (SBGC_NEED_CONFIRM_CMD)

				// Wait for calibration finish accompanied with confirmation
				SBGC32_CheckConfirmation(&SBGC32_Device, SBGC_NO_CONFIRM, CMD_CALIB_ACC);

			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*IMU_ExtCalib - additional command's info
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_CalibAccExt (sbgcGeneral_t *gSBGC, sbgcIMU_ExtCalib_t *IMU_ExtCalib, sbgcConfirm_t *confirm
										/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_CALIB_ACC SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeBuff(gSBGC, IMU_ExtCalib, sizeof(sbgcIMU_ExtCalib_t));
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_CALIB_ACC SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Extended format of gyroscope calibration
 *
 *	####	TX —> CMD_CALIB_GYRO :	12 bytes
 *
 *	@pre	For gyroscope calibration, try to achieve the most
 *			stationary position of the gimbal
 *
 *	@post	If all parameters are valid, confirmation
 *			is sent immediately on reception and in
 *			the end of calibration. This function
 *			handle only start calibration confirmation.
 *			Call the @ref SBGC32_CheckConfirmation function
 *			passing it the CMD_CALIB_GYRO argument
 *
 *	@code

			sbgcIMU_ExtCalib_t IMU_ExtCalib = { 0 };

			// Choose the main IMU for calibration procedure
			IMU_ExtCalib.IMU_IDx = sbgcIMU_TYPE_MAIN;
			IMU_ExtCalib.action = IMUECA_DO_REGULAR_CALIBRATION;

			// Start calibration
			SBGC32_CalibGyroExt(&SBGC32_Device, &IMU_ExtCalib, SBGC_NO_CONFIRM);

			#if (SBGC_NEED_CONFIRM_CMD)

				// Wait for calibration finish accompanied with confirmation
				SBGC32_CheckConfirmation(&SBGC32_Device, SBGC_NO_CONFIRM, CMD_CALIB_GYRO);

			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*IMU_ExtCalib - additional command's info
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_CalibGyroExt (sbgcGeneral_t *gSBGC, sbgcIMU_ExtCalib_t *IMU_ExtCalib, sbgcConfirm_t *confirm
										 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_CALIB_GYRO SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeBuff(gSBGC, IMU_ExtCalib, sizeof(sbgcIMU_ExtCalib_t));
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_CALIB_GYRO SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Extended format of magnetometer calibration
 *
 *	####	TX —> CMD_CALIB_MAG :	12 bytes
 *
 *	@pre	Before performing the calibration, review the
 *			instructions provided in the User Manual,
 *			paragraph 16. Magnetometer sensor:
 *			https://www.basecamelectronics.com/files/v3/SimpleBGC_32bit_manual_eng.pdf
 *
 *	@post	If all parameters are valid, confirmation
 *			is sent immediately on reception and in
 *			the end of calibration. This function
 *			handle only start calibration confirmation.
 *			Call the @ref SBGC32_CheckConfirmation function
 *			passing it the CMD_CALIB_MAG argument
 *
 *	@code

			sbgcIMU_ExtCalib_t IMU_ExtCalib = { 0 };

			// Choose the main IMU for calibration procedure
			IMU_ExtCalib.IMU_IDx = sbgcIMU_TYPE_MAIN;
			IMU_ExtCalib.action = IMUECA_DO_REGULAR_CALIBRATION;

			// Start calibration
			SBGC32_CalibMagExt(&SBGC32_Device, &IMU_ExtCalib, SBGC_NO_CONFIRM);

			#if (SBGC_NEED_CONFIRM_CMD)

				// Wait for calibration finish accompanied with confirmation
				SBGC32_CheckConfirmation(&SBGC32_Device, SBGC_NO_CONFIRM, CMD_CALIB_MAG);

			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*IMU_ExtCalib - additional command's info
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_CalibMagExt (sbgcGeneral_t *gSBGC, sbgcIMU_ExtCalib_t *IMU_ExtCalib, sbgcConfirm_t *confirm
										/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFeature(BF_MAG_SENSOR)

	gSBGC->_api->startWrite(gSBGC, CMD_CALIB_MAG SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeBuff(gSBGC, IMU_ExtCalib, sizeof(sbgcIMU_ExtCalib_t));
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_CALIB_MAG SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Calib_IMU_Info
 *	@{
 */
/**	@brief	Requests information about current IMU calibration state
 *
 *	####	TX —> CMD_CALIB_INFO :	12 bytes
 *	####	RX <— CMD_CALIB_INFO :	33 bytes
 *
 *	@pre	The gimbal must remain stationary throughout
 *			the entire calibration process. It makes
 *			sense to run this function only
 *			during gimbal calibration
 *
 *	@post	Use the @ref DebugSBGC32_PrintWholeStruct
 *			function with PM_CALIB_INFO to print
 *			received data
 *
 *	@code

			sbgcCalibInfo_t CalibInfo;

			// Select the required sensor (optional)
			SBGC32_SelectIMU_3(&SBGC32_Device, sbgcIMU_TYPE_MAIN, SIMUA_SIMPLE_SELECT, 0, SBGC_NO_CONFIRM);

			// Start some calibration process
			SBGC32_CalibGyro(&SBGC32_Device);

			// Obtain calibration information
			sbgcDelay(1000);
			SBGC32_RequestCalibInfo(&SBGC32_Device, &CalibInfo, sbgcIMU_TYPE_MAIN);

			sbgcDelay(1000);
			SBGC32_RequestCalibInfo(&SBGC32_Device, &CalibInfo, sbgcIMU_TYPE_MAIN);

			// ...

 *	@endcode
 *
 *	@param 	*gSBGC - serial connection descriptor
 *	@param	*calibInfo - structure storing IMU calibration state
 *	@param	IMU_Type - IMU sensor in calibration process
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_RequestCalibInfo (sbgcGeneral_t *gSBGC, sbgcCalibInfo_t *calibInfo, sbgcIMU_Type_t IMU_Type
											 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertParam(IMU_Type, sbgcIMU_TYPE_MAIN, sbgcIMU_TYPE_FRAME)

	gSBGC->_api->startWrite(gSBGC, CMD_CALIB_INFO SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, IMU_Type);
	gSBGC->_api->writeEmptyBuff(gSBGC, 11);  // reserved[11]
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_CALIB_INFO SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, NULL, calibInfo, sizeof(sbgcCalibInfo_t));
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Calib_Encoders_Offset
 *	@{
 */
/**	@brief	Calibrates offset of encoders
 *
 *	####	TX —> CMD_ENCODERS_CALIB_OFFSET_4 :		1 byte (prior to frw. ver. 2.68b7 - with no payload)
 *
 *	@pre	Before performing the calibration, review the
 *			instructions provided in the Encoders Manual:
 *			https://www.basecamelectronics.com/files/SimpleBGC_32bit_Encoders.pdf
 *
 *	@code

			// Start calibration
			SBGC32_CalibEncodersOffset(&SBGC32_Device, CALIB_PARAM_ALL_AXES);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param 	forMotor - axis to calibrate. Optional parameter.
 *			Frw. ver. 2.68b7+
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_CalibEncodersOffset (sbgcGeneral_t *gSBGC, sbgcCalibParameter_t forMotor
												/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFeature(BF_ENCODERS)

	gSBGC->_api->startWrite(gSBGC, CMD_ENCODERS_CALIB_OFFSET_4 SBGC_ADVANCED_ARGS__);

	if (gSBGC->_api->baseFirmwareVersion >= 2687)
		gSBGC->_api->writeByte(gSBGC, forMotor);

	gSBGC->_api->finishWrite(gSBGC);
	/* No need confirmation */

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Starts field offset calibration of encoders
 *
 *	####	TX —> CMD_ENCODERS_CALIB_FLD_OFFSET_4 :	with no payload
 *
 *	@pre	Before performing the calibration, review the
 *			instructions provided in the Encoders Manual:
 *			https://www.basecamelectronics.com/files/SimpleBGC_32bit_Encoders.pdf
 *
 *	@code

			// Start calibration
			SBGC32_CalibEncodersFldOffset(&SBGC32_Device);

 *	@endcode
 *
 *	@param 	*gSBGC - serial connection descriptor
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_CalibEncodersFldOffset (sbgcGeneral_t *gSBGC
												   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFeature(BF_ENCODERS)

	return SBGC32_SendEmptyCommand(gSBGC, CMD_ENCODERS_CALIB_FLD_OFFSET_4 SBGC_ADVANCED_ARGS__);
}


/**	@brief	Starts field offset calibration of encoders
 *			in extended format
 *
 *	####	TX —> CMD_ENCODERS_CALIB_FLD_OFFSET_4 :	14 bytes
 *
 *	@pre	Before performing the calibration, review the
 *			instructions provided in the Encoders Manual:
 *			https://www.basecamelectronics.com/files/SimpleBGC_32bit_Encoders.pdf
 *
 *	@code

			#define SBGC_CALIB_ENC_OFFSET_SPEED 100
			#define SBGC_CALIB_ENC_OFFSET_ANGLES 15

			sbgcCalibEncodersOffset_t CalibEncodersOffset = { 0 };

			CalibEncodersOffset.calibAngle[ROLL] = sbgcAngleToDegree(SBGC_CALIB_ENC_OFFSET_ANGLES);
			CalibEncodersOffset.calibAngle[PITCH] = sbgcAngleToDegree(SBGC_CALIB_ENC_OFFSET_ANGLES);

			CalibEncodersOffset.calibSpeed[ROLL] = SBGC_CALIB_ENC_OFFSET_SPEED;
			CalibEncodersOffset.calibSpeed[PITCH] = SBGC_CALIB_ENC_OFFSET_SPEED;

			// Start calibration
			SBGC32_CalibEncodersFldOffsetExt(&SBGC32_Device, &CalibEncodersOffset);

 *	@endcode
 *
 *	@param 	*gSBGC - serial connection descriptor
 *	@param	*calibEncodersOffset - writable structure with extended
 *			information about encoders offset calibration
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_CalibEncodersFldOffsetExt (sbgcGeneral_t *gSBGC, const sbgcCalibEncodersOffset_t *calibEncodersOffset
													  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFeature(BF_ENCODERS)

	gSBGC->_api->startWrite(gSBGC, CMD_ENCODERS_CALIB_FLD_OFFSET_4 SBGC_ADVANCED_ARGS__);
	for (ui8 i = 0; i < 3; i++) gSBGC->_api->writeWord(gSBGC, calibEncodersOffset->calibAngle[i]);
	for (ui8 i = 0; i < 3; i++) gSBGC->_api->writeWord(gSBGC, calibEncodersOffset->calibSpeed[i]);
	gSBGC->_api->writeWord(gSBGC, calibEncodersOffset->calibFlags);
	gSBGC->_api->finishWrite(gSBGC);
	/* No need confirmation */

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Calib_Other
 *	@{
 */
/**	@brief	Calibrates poles and direction
 *
 *	####	TX —> CMD_CALIB_POLES :	with no payload
 *
 *	@pre	Don't touch the gimbal during the calibration process
 *
 *	@code

			// Start calibration
			SBGC32_CalibPoles(&SBGC32_Device);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_CalibPoles (sbgcGeneral_t *gSBGC
									   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	return SBGC32_SendEmptyCommand(gSBGC, CMD_CALIB_POLES SBGC_ADVANCED_ARGS__);
}


/**	@brief	Calibrates follow offset
 *
 *	####	TX —> CMD_CALIB_OFFSET :		with no payload
 *
 *	@pre	Position the gimbal as required
 *			and perform the calibration
 *
 *	@code

			// Start calibration
			SBGC32_CalibOffset(&SBGC32_Device);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_CalibOffset (sbgcGeneral_t *gSBGC
										/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	return SBGC32_SendEmptyCommand(gSBGC, CMD_CALIB_OFFSET SBGC_ADVANCED_ARGS__);
}


/**	@brief	Calibrates internal voltage sensor
 *
 *	####	TX —> CMD_CALIB_BAT :	2 bytes
 *	####	RX <— CMD_CONFIRM :		1-6 bytes
 *
 *	@pre	The gimbal must receive power from
 *			the external power supply
 *
 *	@code

			#define SBGC_BATTERY_CALIB_VALUE 2520

			// Nominal value example for a 6S battery ((4.2 * 6) / 0.01)
			SBGC32_CalibBat(&SBGC32_Device, SBGC_BATTERY_CALIB_VALUE, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param 	*gSBGC - serial connection descriptor
 *	@param	voltage - reference voltage value. Units: 0.01 V
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_CalibBat (sbgcGeneral_t *gSBGC, ui16 voltage, sbgcConfirm_t *confirm
									 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFeature(BF_BAT_MONITORING)

	gSBGC->_api->startWrite(gSBGC, CMD_CALIB_BAT SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeWord(gSBGC, voltage);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_CALIB_BAT SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Starts the calibration of sensor misalignment correction
 *
 *	####	TX —> CMD_CALIB_ORIENT_CORR :	16 bytes
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@pre	Turn motors off and firmly fix the joint between
 *			the inner motor (that connects to a camera)
 *			and the middle motor (next in order)
 *
 *	@post	You can also read the newly received IMU_OrientationCorr[3]
 *			data using the @ref SBGC32_ReadParamsExt2 function
 *
 *	@attention	Firmware: 2.61+
 *
 *	@code

			// Start calibration
			SBGC32_CalibOrientCorr(&SBGC32_Device, SBGC_NO_CONFIRM);

			#if (SBGC_PROFILES_MODULE)

				sbgcMainParamsExt2_t MainParamsExt2;

				// Getting updated values
				SBGC32_ReadParamsExt2(&SBGC32_Device, &MainParamsExt2, sbgcCURRENT_PROFILE);

				#if (SBGC_NEED_DEBUG)

					// And print it
					DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParamsExt2.IMU_OrientationCorr[ROLL], "IMU OC ROLL =", sbgcSHORT);
					DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParamsExt2.IMU_OrientationCorr[PITCH], "IMU OC PITCH =", sbgcSHORT);
					DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParamsExt2.IMU_OrientationCorr[YAW], "IMU OC YAW =", sbgcSHORT);

				#endif

			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_CalibOrientCorr (sbgcGeneral_t *gSBGC, sbgcConfirm_t *confirm
											/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2610)

	gSBGC->_api->startWrite(gSBGC, CMD_CALIB_ORIENT_CORR SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeEmptyBuff(gSBGC, 16);  // reserved[16]
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_CALIB_ORIENT_CORR SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Refine the accelerometer calibration of the main IMU sensor
 *
 *	####	TX —> CMD_CALIB_ACC_EXT_REF :	20 bytes
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@attention	Firmware: 2.62b7+ ("Encoder", "plus")
 *
 *	@code

			i16 accRef [] = { x, y, z };
			// where x, y, z are reference ACC vector in gimbal frame's coordinates
			// (X-axis points right, Y-axis points forward, Z-axis points down relative to frame)

			// Start calibration
			SBGC32_CalibAccExtRef(&SBGC32_Device, accRef, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*accRef - reference acc. vector [X,Y,Z] in gimbal
 *			frame's coordinates. Units: 1g/512 ≈ 0.019160156 m/sec²
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_CalibAccExtRef (sbgcGeneral_t *gSBGC, const i16 accRef [3], sbgcConfirm_t *confirm
										   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2627)

	#if (SBGC_NEED_ASSERTS)

		if (!((gSBGC->_api->boardFeatures & BF_ENCODERS) || (gSBGC->_api->boardFeatures2 & BFE2_PLUS_VER)))
			return sbgcCOMMAND_NOT_SUPPORTED_FEATURE;

	#endif

	gSBGC->_api->startWrite(gSBGC, CMD_CALIB_ACC_EXT_REF SBGC_ADVANCED_ARGS__);
	for (ui8 i = 0; i < 3; i++) gSBGC->_api->writeWord(gSBGC, accRef[i]);
	gSBGC->_api->writeEmptyBuff(gSBGC, 14);  // reserved[14]
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_CALIB_ACC_EXT_REF SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Starts the motor non-linearities calibration
 *
 *	####	TX —> CMD_CALIB_COGGING :		57 bytes
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@pre	Before performing the calibration, review the
 *			instructions provided in the User Manual,
 *			paragraph 20. Correction of the motor's "cogging" effect:
 *			https://www.basecamelectronics.com/files/v3/SimpleBGC_32bit_manual_eng.pdf
 *
 *	@post	Another command CMD_CONFIRM with the DATA = 255
 *			is sent when calibration finishes. The function
 *			processes only the first confirmation command
 *			Call the @ref SBGC32_CheckConfirmation function
 *			passing it the CMD_CALIB_COGGING argument
 *
 *	@code

			#define SBGC_COGGING_CALIB_ANGLE 90
			#define SBGC_COGGING_CALIB_SMOOTH 20
			#define SBGC_COGGING_CALIB_SPEED 100
			#define SBGC_COGGING_CALIB_ITTERATION_NUM 10

			sbgcCalibCogging_t CalibCogging = { 0 };

			// Calibrate the pitch axis
			CalibCogging.action = CCA_CALIBRATE;
			CalibCogging.axisToCalibrate = CCAC_PITCH;

			CalibCogging.AxisCCog[PITCH].angle = SBGC_COGGING_CALIB_ANGLE;
			CalibCogging.AxisCCog[PITCH].smooth = SBGC_COGGING_CALIB_SMOOTH;
			CalibCogging.AxisCCog[PITCH].speed = SBGC_COGGING_CALIB_SPEED;

			CalibCogging.iterationsNum = SBGC_COGGING_CALIB_ITTERATION_NUM;

			// Start calibration
			SBGC32_CalibCogging(&SBGC32_Device, &CalibCogging, SBGC_NO_CONFIRM);

			#if (SBGC_NEED_CONFIRM_CMD)

				// Wait for calibration finish accompanied with confirmation
				SBGC32_CheckConfirmation(&SBGC32_Device, SBGC_NO_CONFIRM, CMD_CALIB_COGGING);

			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*calibCogging - data structure with values
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_CalibCogging (sbgcGeneral_t *gSBGC, const sbgcCalibCogging_t *calibCogging, sbgcConfirm_t *confirm
										 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_CALIB_COGGING SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeBuff(gSBGC, calibCogging, sizeof(sbgcCalibCogging_t));
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_CALIB_COGGING SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */

#endif /* SBGC_CALIB_MODULE */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
