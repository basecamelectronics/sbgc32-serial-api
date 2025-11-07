/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2.1
 *
 *	@file		realtime.c
 *
 *	@brief		Realtime source file
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


#if (SBGC_REALTIME_MODULE)

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									Static Constants
 */
#define		SIZEOF_REALTIME_DATA_3	63


#if (SBGC_USES_REF_INFO)

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *					Big Endian Mapping and Reference Info Structures
	 */
	/**	@addtogroup	Data_Stream_Interval Data Stream Interval
	 *	@{
	 */
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t dataStreamIntervalReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Command ID",				sbgcUCHAR						),  // 0
		PARAM_BLOCK_(	"Interval Ms",				sbgcUSHORT						),  // 1
		PARAMS_BLOCK_(	"Config",					sbgcUCHAR,					8	),  // 2
		PARAM_BLOCK_(	"Sync to Data",				sbgcUCHAR						),  // 3
		PARAMS_BLOCK_(	"Reserved",					sbgcRCHAR,					9	),  // 4

	};

	const ui8 dataStreamIntervalReferenceInfoArrayElCnt = countof_(dataStreamIntervalReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Realtime_Data_Custom
	 *	@{
	 */
	/** @brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t systemPowerStateReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Motor Power [ROLL]",		sbgcSHORT						),  // 0
		PARAM_BLOCK_(	"Motor Current [ROLL]",		sbgcUSHORT						),  // 1
		PARAM_BLOCK_(	"Motor Temp [ROLL]",		sbgcCHAR						),  // 2
		PARAM_BLOCK_(	"Motor Flags [ROLL]",		(sbgcUSHORT | sbgcFLAG)			),  // 3
		PARAMS_BLOCK_(	"Reserved [ROLL]",			sbgcRCHAR,					6	),  // 4
		PARAM_BLOCK_(	"Motor Power [PITCH]",		sbgcSHORT						),  // 5
		PARAM_BLOCK_(	"Motor Current [PITCH]",	sbgcUSHORT						),  // 6
		PARAM_BLOCK_(	"Motor Temp [PITCH]",		sbgcCHAR						),  // 7
		PARAM_BLOCK_(	"Motor Flags [PITCH]",		(sbgcUSHORT | sbgcFLAG)			),  // 8
		PARAMS_BLOCK_(	"Reserved [PITCH]",			sbgcRCHAR,					6	),  // 9
		PARAM_BLOCK_(	"Motor Power [YAW]",		sbgcSHORT						),  // 10
		PARAM_BLOCK_(	"Motor Current [YAW]",		sbgcUSHORT						),  // 11
		PARAM_BLOCK_(	"Motor Temp [YAW]",			sbgcCHAR						),  // 12
		PARAM_BLOCK_(	"Motor Flags [YAW]",		(sbgcUSHORT | sbgcFLAG)			),  // 13
		PARAMS_BLOCK_(	"Reserved [YAW]",			sbgcRCHAR,					6	),  // 14
		PARAM_BLOCK_(	"System Power State",		sbgcCHAR						),  // 15
		PARAM_BLOCK_(	"Battery Voltage",			sbgcUSHORT						),  // 16
		PARAM_BLOCK_(	"Total Current",			sbgcUSHORT						),  // 17
		PARAM_BLOCK_(	"System Flags",				sbgcUSHORT						),  // 18

	};

	const ui8 systemPowerStateReferenceInfoArrayElCnt = countof_(systemPowerStateReferenceInfoArray);


	/** @brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t communicationErrorsReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"I2C Errors",				sbgcUSHORT						),  // 0
		PARAM_BLOCK_(	"Serial Errors",			sbgcUSHORT						),  // 1
		PARAM_BLOCK_(	"CAN Errors",				sbgcUSHORT						),  // 2
		PARAM_BLOCK_(	"CAN Error Flags",			sbgcUCHAR						),  // 3

	};

	const ui8 communicationErrorsReferenceInfoArrayElCnt = countof_(communicationErrorsReferenceInfoArray);


	/** @brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t systemStateReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Flags",					sbgcUINT						),  // 0
		PARAM_BLOCK_(	"Calib Mode",				sbgcUCHAR						),  // 1
		PARAMS_BLOCK_(	"Reserved",					sbgcRCHAR,					8	),  // 2

	};

	const ui8 systemStateReferenceInfoArrayElCnt = countof_(systemStateReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Realtime_Data_3_4
	 *	@{
	 */
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t realTimeDataReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Acc Data [ROLL]",			sbgcSHORT						),  // 0
		PARAM_BLOCK_(	"Gyro Data [ROLL]",			sbgcSHORT						),  // 1
		PARAM_BLOCK_(	"Acc Data [PITCH]",			sbgcSHORT						),  // 2
		PARAM_BLOCK_(	"Gyro Data [PITCH]",		sbgcSHORT						),  // 3
		PARAM_BLOCK_(	"Acc Data [YAW]",			sbgcSHORT						),  // 4
		PARAM_BLOCK_(	"Gyro Data [YAW]",			sbgcSHORT						),  // 5
		PARAM_BLOCK_(	"Serial Error Count",		sbgcUSHORT						),  // 6
		PARAM_BLOCK_(	"System Error",				sbgcUSHORT						),  // 7
		PARAM_BLOCK_(	"System Sub Error",			sbgcUCHAR						),  // 8
		PARAMS_BLOCK_(	"Reserved",					sbgcRCHAR,					3	),  // 9
		PARAM_BLOCK_(	"RC ROLL",					sbgcSHORT						),  // 10
		PARAM_BLOCK_(	"RC PITCH",					sbgcSHORT						),  // 11
		PARAM_BLOCK_(	"RC YAW",					sbgcSHORT						),  // 12
		PARAM_BLOCK_(	"RC cmdTx",					sbgcSHORT						),  // 13
		PARAM_BLOCK_(	"Ext FC ROLL",				sbgcSHORT						),  // 14
		PARAM_BLOCK_(	"Ext FC PITCH",				sbgcSHORT						),  // 15
		PARAMS_BLOCK_(	"IMU Angle",				sbgcSHORT,					3	),  // 16
		PARAMS_BLOCK_(	"Frame IMU Angle",			sbgcSHORT,					3	),  // 17
		PARAMS_BLOCK_(	"Target Angle",				sbgcSHORT,					3	),  // 18
		PARAM_BLOCK_(	"Cycle Time",				sbgcUSHORT						),  // 19
		PARAM_BLOCK_(	"I2C Error Count",			sbgcUSHORT						),  // 20
		PARAM_BLOCK_(	"Error Code",				sbgcUCHAR						),  // 21
		PARAM_BLOCK_(	"Bat Level",				sbgcUSHORT						),  // 22
		PARAM_BLOCK_(	"RT Data Flags",			(sbgcUCHAR | sbgcFLAG)			),  // 23
		PARAM_BLOCK_(	"Cur IMU",					sbgcUCHAR						),  // 24
		PARAM_BLOCK_(	"Cur Profile",				sbgcUCHAR						),  // 25
		PARAMS_BLOCK_(	"Motor Power",				sbgcUCHAR,					3	),  // 26
		/* Realtime Data 4 */
		PARAMS_BLOCK_(	"Frame Camera Angle",		sbgcSHORT,					3	),  // 27
		PARAM_BLOCK_(	"Reserved 1",				sbgcRCHAR						),  // 28
		PARAMS_BLOCK_(	"Balance Error",			sbgcSHORT,					3	),  // 29
		PARAM_BLOCK_(	"Current",					sbgcUSHORT						),  // 30
		PARAMS_BLOCK_(	"Mag Data",					sbgcSHORT,					3	),  // 31
		PARAM_BLOCK_(	"IMU Temperature",			sbgcCHAR						),  // 32
		PARAM_BLOCK_(	"Frame IMU Temperature",	sbgcCHAR						),  // 33
		PARAM_BLOCK_(	"IMU G Err",				sbgcUCHAR						),  // 34
		PARAM_BLOCK_(	"IMU H Err",				sbgcUCHAR						),  // 35
		PARAMS_BLOCK_(	"Motor Out",				sbgcSHORT,					3	),  // 36
		PARAM_BLOCK_(	"Calib Mode",				sbgcUCHAR						),  // 37
		PARAM_BLOCK_(	"CAN IMU Ext Sens Err",		sbgcUCHAR						),  // 38
		PARAMS_BLOCK_(	"Actual Angle",				sbgcSHORT,					3	),  // 39
		PARAM_BLOCK_(	"System State Flags",		(sbgcUINT | sbgcFLAG)			),  // 40
		PARAMS_BLOCK_(	"Reserved 2",				sbgcRCHAR,					18	),  // 41

	};

	const ui8 realTimeDataReferenceInfoArrayElCnt = countof_(realTimeDataReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Get_Angles
	 *	@{
	 */
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t getAnglesReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"IMU Angle [ROLL]",			sbgcSHORT						),  // 0
		PARAM_BLOCK_(	"Target Angle [ROLL]",		sbgcSHORT						),  // 1
		PARAM_BLOCK_(	"Target Speed [ROLL]",		sbgcSHORT						),  // 2
		PARAM_BLOCK_(	"IMU Angle [PITCH]",		sbgcSHORT						),  // 3
		PARAM_BLOCK_(	"Target Angle [PITCH]",		sbgcSHORT						),  // 4
		PARAM_BLOCK_(	"Target Speed [PITCH]",		sbgcSHORT						),  // 5
		PARAM_BLOCK_(	"IMU Angle [YAW]",			sbgcSHORT						),  // 6
		PARAM_BLOCK_(	"Target Angle [YAW]",		sbgcSHORT						),  // 7
		PARAM_BLOCK_(	"Target Speed [YAW]",		sbgcSHORT						),  // 8

	};

	const ui8 getAnglesReferenceInfoArrayElCnt = countof_(getAnglesReferenceInfoArray);


	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t getAnglesExtReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"IMU Angle [ROLL]",			sbgcSHORT						),  // 0
		PARAM_BLOCK_(	"Target Angle [ROLL]",		sbgcSHORT						),  // 1
		PARAM_BLOCK_(	"Frame Cam Angle [ROLL]",	sbgcINT							),  // 2
		PARAMS_BLOCK_(	"Reserved [ROLL]",			sbgcRCHAR,					10	),  // 3
		PARAM_BLOCK_(	"IMU Angle [PITCH]",		sbgcSHORT						),  // 4
		PARAM_BLOCK_(	"Target Angle [PITCH]",		sbgcSHORT						),  // 5
		PARAM_BLOCK_(	"Frame Cam Angle [PITCH]",	sbgcINT							),  // 6
		PARAMS_BLOCK_(	"Reserved [PITCH]",			sbgcRCHAR,					10	),  // 7
		PARAM_BLOCK_(	"IMU Angle [YAW]",			sbgcSHORT						),  // 8
		PARAM_BLOCK_(	"Target Angle [YAW]",		sbgcSHORT						),  // 9
		PARAM_BLOCK_(	"Frame Cam Angle [YAW]",	sbgcINT							),  // 10
		PARAMS_BLOCK_(	"Reserved [YAW]",			sbgcRCHAR,					10	),  // 11

	};

	const ui8 getAnglesExtReferenceInfoArrayElCnt = countof_(getAnglesExtReferenceInfoArray);
	/**	@}
	 */

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														Static Functions
 */
#if (SBGC_NEED_ASSERTS)

	/**	@brief	Asserts the realtime data custom flags
	 *
	 *	@note	Private function
	 *
	 *	@param	*gSBGC - serial connection descriptor
	 *	@param	flags - required data
	 *
	 *	@return	Assert result
	 */
	static sbgcCommandStatus_t SerialAPI_AssertRealTimeDataCustomFlags (sbgcGeneral_t *gSBGC, ui32 flags)
	{
		if (flags & RTDCF_ENCODER_RAW24)
			sbgcAssertFeature(BF_ENCODERS)

		if ((flags & RTDCF_SCRIPT_VARS_FLOAT) || (flags & RTDCF_SCRIPT_VARS_INT16))
			sbgcAssertFeature(BF_SCRIPTING)

		if (flags & RTDCF_SYSTEM_POWER_STATE)
			sbgcAssertFeature(BF_POWER_MANAGEMENT)

		if ((flags & RTDCF_IMU_QUAT) || (flags & RTDCF_TARGET_QUAT) || (flags & RTDCF_IMU_TO_FRAME_QUAT))
			sbgcAssertFeature2(BFE2_QUAT_CONTROL)

		return sbgcCOMMAND_OK;
	}

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	Data_Stream_Interval
 *	@{
 */
/**	@brief	Registers or updates a data stream
 *
 *	####	TX —> CMD_DATA_STREAM_INTERVAL :		21 bytes
 *	####	RX <— CMD_CONFIRM :						1-6 bytes
 *
 *	@pre	Use the next functions to fill the
 *			sbgcDataStreamInterval_t.config field:\n
 *			@ref ParserSBGC32_RTDC_FlagsToStream \n
 *			@ref ParserSBGC32_AHRSH_IMU_TypeToStream \n
 *			@ref ParserSBGC32_EventID_AndTypeToStream \n
 *			@ref ParserSBGC32_CAN_DT_FlagsAndID_ToStream \n
 *			@ref ParserSBGC32_EMS_ID_AndSetToStream
 *
 *	@pre	Board requirements:\n
 *			ENCODERS = (1 << 2) when using RTDCF_ENCODER_RAW24 \n
 *			SCRIPTING = (1 << 4) when using RTDCF_SCRIPT_VARS_FLOAT or
 *			RTDCF_SCRIPT_VARS_INT16 \n
 *			CAN_PORT = (1 << 10) when using DSC_CMD_CAN_DRV_TELEMETRY \n
 *			POWER_MANAGEMENT = (1 << 19) (ext.) when using RTDCF_SYSTEM_POWER_STATE \n
 *			EXT_MOTORS = (1 << 2) (ext.2) when using DSC_CMD_EXT_MOTORS_STATE \n
 *			QUAT_CONTROL = (1 << 3) (ext.2) when using RTDCF_IMU_QUAT or
 *			RTDCF_TARGET_QUAT or RTDCF_IMU_TO_FRAME_QUAT
 *
 *	@post	Use the @ref SBGC32_ReadDataStream function
 *			for parse the requested data
 *
 *	@attention	Firmware: 2.60+\n
 *				Commands sent by the controller with
 *				the fixed rate without request
 *
 *	@note	Firmware: 2.65+\n
 *			...or based on events
 *
 *	@code

			// Example 1

			#define SBGC_DATA_STREAM_RATE 500
			#define SBGC_DATA_STREAM_TIME 30000
			#define SBGC_DATA_STREAM_DEPTH 1

			sbgcDataStreamInterval_t DataStreamInterval = { 0 };

			struct PACKED__ RealTimeDataStruct
			{
				// Mandatory field, don't remove!
				ui16 timestampMs;

				// Additional fields, depended on 'flags'
				i16 frameCamAngle [3];
				i16 gyroData [3];
				i16 accData [3];

			}	RealTimeData;

			sbgcTicks_t dataStreamTick;

			DataStreamInterval.cmdID = DSC_CMD_REALTIME_DATA_CUSTOM;

			// Wait for data every 500 milliseconds
			DataStreamInterval.syncToData = STD_SYNC_OFF;
			DataStreamInterval.intervalMs = SBGC_DATA_STREAM_RATE;

			// Assign the necessary data for the stream
			ParserSBGC32_RTDC_FlagsToStream(&DataStreamInterval, RTDCF_STATOR_ROTOR_ANGLE | RTDCF_GYRO_DATA | RTDCF_ACC_DATA);

			// Start streaming
			SBGC32_StartDataStream(&SBGC32_Device, &DataStreamInterval, SBGC_NO_CONFIRM);

			dataStreamTick = sbgcGetTick();

			while (sbgcGetTick() < (dataStreamTick + SBGC_DATA_STREAM_TIME))
			{
				// Wait until get a full command
				while (SerialAPI_GetBytesAvailable(&SBGC32_Device) < (sizeof(RealTimeData) * SBGC_DATA_STREAM_DEPTH));

				SBGC32_ReadDataStream(&SBGC32_Device, DSC_CMD_REALTIME_DATA_CUSTOM, &RealTimeData, sizeof(RealTimeData));

				#if (SBGC_NEED_DEBUG)

					// Print camera angles for example
					i16 frameCamAngleTemp;

					frameCamAngleTemp = sbgcDegreeToAngle(RealTimeData.frameCamAngle[ROLL]);
					DebugSBGC32_PrintStructElement(&SBGC32_Device, &frameCamAngleTemp, "FCA ROLL =", sbgcSHORT);

					frameCamAngleTemp = sbgcDegreeToAngle(RealTimeData.frameCamAngle[PITCH]);
					DebugSBGC32_PrintStructElement(&SBGC32_Device, &frameCamAngleTemp, "FCA PITCH =", sbgcSHORT);

					frameCamAngleTemp = sbgcDegreeToAngle(RealTimeData.frameCamAngle[YAW]);
					DebugSBGC32_PrintStructElement(&SBGC32_Device, &frameCamAngleTemp, "FCA YAW =", sbgcSHORT);

				#endif
			}

			// Stop streaming
			SBGC32_StopDataStream(&SBGC32_Device, &DataStreamInterval, SBGC_NO_CONFIRM);


			// Example 2

			#define SBGC_DATA_STREAM_DIV 125
			#define SBGC_DATA_STREAM_TIME 30000
			#define SBGC_DATA_STREAM_DEPTH 1

			sbgcDataStreamInterval_t DataStreamInterval = { 0 };
			sbgcRealTimeData_t RealTimeData;
			sbgcTicks_t dataStreamTick;

			DataStreamInterval.cmdID = DSC_CMD_REALTIME_DATA_4;

			// Wait for data every 1 second
			DataStreamInterval.syncToData = STD_SYNC_ON;
			DataStreamInterval.intervalMs = SBGC_DATA_STREAM_DIV;

			// Start streaming
			SBGC32_StartDataStream(&SBGC32_Device, &DataStreamInterval, SBGC_NO_CONFIRM);

			dataStreamTick = sbgcGetTick();

			while (sbgcGetTick() < (dataStreamTick + SBGC_DATA_STREAM_TIME))
			{
				// Wait until get a full command
				while (SerialAPI_GetBytesAvailable(&SBGC32_Device) < (sizeof(RealTimeData) * SBGC_DATA_STREAM_DEPTH));

				SBGC32_ReadDataStream(&SBGC32_Device, DSC_CMD_REALTIME_DATA_4, &RealTimeData, sizeof(RealTimeData));

				#if (SBGC_NEED_DEBUG)

					// Print camera angles for example
					i16 frameCamAngleTemp;

					frameCamAngleTemp = sbgcDegreeToAngle(RealTimeData.frameCamAngle[ROLL]);
					DebugSBGC32_PrintStructElement(&SBGC32_Device, &frameCamAngleTemp, "FCA ROLL =", sbgcSHORT);

					frameCamAngleTemp = sbgcDegreeToAngle(RealTimeData.frameCamAngle[PITCH]);
					DebugSBGC32_PrintStructElement(&SBGC32_Device, &frameCamAngleTemp, "FCA PITCH =", sbgcSHORT);

					frameCamAngleTemp = sbgcDegreeToAngle(RealTimeData.frameCamAngle[YAW]);
					DebugSBGC32_PrintStructElement(&SBGC32_Device, &frameCamAngleTemp, "FCA YAW =", sbgcSHORT);

				#endif
			}

			// Stop streaming
			SBGC32_StopDataStream(&SBGC32_Device, &DataStreamInterval, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*dataStreamInterval - structure with prepared
 *			command parameters
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_StartDataStream (sbgcGeneral_t *gSBGC, const sbgcDataStreamInterval_t *dataStreamInterval, sbgcConfirm_t *confirm
											/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2600)

	#if (SBGC_NEED_ASSERTS)

		if ((gSBGC->_api->baseFirmwareVersion < 2657) && (dataStreamInterval->cmdID == DSC_CMD_EVENT))
			return sbgcCOMMAND_NOT_SUPPORTED_BY_FIRMWARE;

		if ((gSBGC->_api->baseFirmwareVersion < 2720 || (gSBGC->_api->boardVersion < 36)) &&
			(dataStreamInterval->cmdID == DSC_CMD_CAN_DRV_TELEMETRY))
			return sbgcCOMMAND_NOT_SUPPORTED_BY_FIRMWARE;

		if ((gSBGC->_api->baseFirmwareVersion < 2730) && (dataStreamInterval->cmdID == DSC_CMD_EXT_MOTORS_STATE))
			return sbgcCOMMAND_NOT_SUPPORTED_BY_FIRMWARE;

		if (dataStreamInterval->cmdID == DSC_CMD_CAN_DRV_TELEMETRY)
			sbgcAssertFeature(BF_CAN_PORT)

		if (dataStreamInterval->cmdID == DSC_CMD_EXT_MOTORS_STATE)
			sbgcAssertFeature2(BFE2_EXT_MOTORS)

		if (dataStreamInterval->cmdID == DSC_CMD_REALTIME_DATA_CUSTOM)
		{
			ui32 flags;

			memcpy(&flags, dataStreamInterval->config, sizeof(ui32));

			if (SerialAPI_AssertRealTimeDataCustomFlags(gSBGC, flags) != sbgcCOMMAND_OK)
				return sbgcCOMMAND_NOT_SUPPORTED_FEATURE;
		}

	#endif

	gSBGC->_api->startWrite(gSBGC, CMD_DATA_STREAM_INTERVAL SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeBuff(gSBGC, dataStreamInterval, sizeof(sbgcDataStreamInterval_t));
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_DATA_STREAM_INTERVAL SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Stops a data stream
 *
 *	####	TX —> CMD_DATA_STREAM_INTERVAL :		21 bytes
 *	####	RX <— CMD_CONFIRM :						1-6 bytes
 *
 *	@pre	Use the @ref SBGC32_StartDataStream function
 *			to start data stream first
 *
 *	@attention	Firmware: 2.60+
 *
 *	@note	See @ref SBGC32_StartDataStream function
 *			documentation for usage example
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*dataStreamInterval - working data stream descriptor
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_StopDataStream (sbgcGeneral_t *gSBGC, sbgcDataStreamInterval_t *dataStreamInterval, sbgcConfirm_t *confirm
										   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2600)

	gSBGC->_api->startWrite(gSBGC, CMD_DATA_STREAM_INTERVAL SBGC_ADVANCED_ARGS__);
	dataStreamInterval->intervalMs = 0;
	gSBGC->_api->writeBuff(gSBGC, dataStreamInterval, sizeof(sbgcDataStreamInterval_t));
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_DATA_STREAM_INTERVAL SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_ReadDataStream function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostReadDataStream (sbgcGeneral_t *gSBGC)
{
	if (curCmd_->_destinationSize < curCmd_->_payloadSize)
		SerialAPI_FatalErrorHandler();

	switch (curCmd_->_commandID)
	{
		case CMD_REALTIME_DATA_3 :
		{
			/* dataStreamStruct = &RealTimeData_t struct for reading */
			gSBGC->_api->readBuff(gSBGC, curCmdDest_, SIZEOF_REALTIME_DATA_3);
			break;
		}

					case CMD_REALTIME_DATA_4 :
					{
						/* dataStreamStruct = &RealTimeData_t struct for reading */
						gSBGC->_api->readBuff(gSBGC, curCmdDest_, sizeof(sbgcRealTimeData_t));
						break;
					}

		case CMD_REALTIME_DATA_CUSTOM :
		{
			/* This case will not work correctly in the big endian systems.
			   It is recommended to convert the data manually further.

			   Also, you can get the parsed data to custom data structure and then transfer it to the
			   RealTimeDataCustomReference_t struct. This method can be used, when you need to get
			   separated data arrays.

			   *RealTimeDataCustom = (sbgcRealTimeDataCustomReference_t*)pDestination for reading
			 */

			gSBGC->_api->readBuff(gSBGC, curCmdDest_, curCmd_->_payloadSize);
			break;
		}

					case CMD_AHRS_HELPER :
					{
						/* dataStreamStruct = &RealTimeData_t->Z_Vect[0] field for reading */
						gSBGC->_api->readBuff(gSBGC, curCmdDest_, curCmd_->_payloadSize);
						for (ui8 i = 0; i < 6; i++) gSBGC->_api->readLong(gSBGC);
						break;
					}

		case CMD_EVENT :
		case CMD_CAN_DRV_TELEMETRY :
		case CMD_EXT_MOTORS_STATE :
		{
			/* The structure should be prepared for reading at this point. Read all the data */
			gSBGC->_api->readBuff(gSBGC, curCmdDest_, curCmd_->_payloadSize);
			break;
		}

					default :
					/* The critical point. The library don't have such command to handle */
						break;
	}
}

/**	@brief	Parses the requested data stream
 *
 *	####	RX <— CMD_REALTIME_DATA_3 :				63 bytes
 *	or
 *	####	RX <— CMD_REALTIME_DATA_4 :				124 bytes
 *	or
 *	####	RX <— CMD_REALTIME_DATA_CUSTOM :		2 + ? bytes
 *	or
 *	####	RX <— CMD_AHRS_HELPER :					26 bytes
 *	or		frw.ver. 2.65b7+
 *	####	RX <— CMD_EVENT :						4 bytes
 *	or		frw.ver. 2.72b0+ ("Extended" family only)
 *	####	RX <— CMD_CAN_DRV_TELEMETRY :			3 + ? bytes
 *	or		frw.ver. 2.73+
 *	####	RX <— CMD_EXT_MOTORS_STATE :			5 + ? bytes
 *
 *	@pre	Use the @ref SBGC32_StartDataStream function
 *			to start data stream first
 *
 *	@attention	Firmware: 2.60+
 *
 *	@note	See @ref SBGC32_StartDataStream function
 *			documentation for usage example
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	cmdID - parameter sent in the
 *			sbgcDataStreamInterval_t.cmdID.
 *			Command for which a response is expected
 *	@param	*dataStreamStruct - one of the relevant
 *			structs to the cmdID parameter
 *	@param	size - data stream buffer size
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ReadDataStream (sbgcGeneral_t *gSBGC, sbgcDataStreamCommand_t cmdID, void *dataStreamStruct, ui8 size
										   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2600)

	#if (SBGC_NEED_ASSERTS)

		if ((gSBGC->_api->baseFirmwareVersion < 2657) && (cmdID == DSC_CMD_EVENT))
			return sbgcCOMMAND_NOT_SUPPORTED_BY_FIRMWARE;

		if ((gSBGC->_api->baseFirmwareVersion < 2720 || (gSBGC->_api->boardVersion < 36)) && (cmdID == DSC_CMD_CAN_DRV_TELEMETRY))
			return sbgcCOMMAND_NOT_SUPPORTED_BY_FIRMWARE;

		if ((gSBGC->_api->baseFirmwareVersion < 2730) && (cmdID == DSC_CMD_EXT_MOTORS_STATE))
			return sbgcCOMMAND_NOT_SUPPORTED_BY_FIRMWARE;

	#endif

	/* It's necessary to lock SerialAPI before Rx operation */
	serialAPI_LockRead()

	gSBGC->_api->startRead(gSBGC, (serialAPI_CommandID_t)cmdID SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, PostReadDataStream, dataStreamStruct, size);
	gSBGC->_api->finishRead(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Realtime_Data_Custom
 *	@{
 */
/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_RequestRealTimeDataCustom function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostRequestRealTimeDataCustom (sbgcGeneral_t *gSBGC)
{
	if (curCmd_->_destinationSize < curCmd_->_payloadSize)
	{
		SerialAPI_FatalErrorHandler();
	}

	#if (SBGC_SYS_LITTLE_ENDIAN)

		/* Skip flags and read */
		gSBGC->_api->readBuff(gSBGC, ((ui8*)curCmdDest_) + 4, curCmd_->_payloadSize);

	#else

		sbgcRealTimeDataCustomReference_t *realTimeDataCustom = curCmdDest_;

		realTimeDataCustom->timestampMs = gSBGC->_api->readWord(gSBGC);

		/* Data Parsing */
		if (realTimeDataCustom->flags & RTDCF_IMU_ANGLES)
		{
			realTimeDataCustom->IMU_Angles[ROLL] = (i16)gSBGC->_api->readWord(gSBGC);
			realTimeDataCustom->IMU_Angles[PITCH] = (i16)gSBGC->_api->readWord(gSBGC);
			realTimeDataCustom->IMU_Angles[YAW] = (i16)gSBGC->_api->readWord(gSBGC);
		}

					if (realTimeDataCustom->flags &  RTDCF_TARGET_ANGLES)
					{
						realTimeDataCustom->targetAngles[SBGC_X] = (i16)gSBGC->_api->readWord(gSBGC);
						realTimeDataCustom->targetAngles[SBGC_Y] = (i16)gSBGC->_api->readWord(gSBGC);
						realTimeDataCustom->targetAngles[SBGC_Z] = (i16)gSBGC->_api->readWord(gSBGC);
					}

		if (realTimeDataCustom->flags & RTDCF_TARGET_SPEED)
		{
			realTimeDataCustom->targetSpeed[SBGC_X] = (i16)gSBGC->_api->readWord(gSBGC);
			realTimeDataCustom->targetSpeed[SBGC_Y] = (i16)gSBGC->_api->readWord(gSBGC);
			realTimeDataCustom->targetSpeed[SBGC_Z] = (i16)gSBGC->_api->readWord(gSBGC);
		}

					if (realTimeDataCustom->flags & RTDCF_STATOR_ROTOR_ANGLE)
					{
						realTimeDataCustom->frameCamAngle[ROLL] = (i16)gSBGC->_api->readWord(gSBGC);
						realTimeDataCustom->frameCamAngle[PITCH] = (i16)gSBGC->_api->readWord(gSBGC);
						realTimeDataCustom->frameCamAngle[YAW] = (i16)gSBGC->_api->readWord(gSBGC);
					}

		if (realTimeDataCustom->flags & RTDCF_GYRO_DATA)
		{
			realTimeDataCustom->gyroData[SBGC_X] = (i16)gSBGC->_api->readWord(gSBGC);
			realTimeDataCustom->gyroData[SBGC_Y] = (i16)gSBGC->_api->readWord(gSBGC);
			realTimeDataCustom->gyroData[SBGC_Z] = (i16)gSBGC->_api->readWord(gSBGC);
		}

					if (realTimeDataCustom->flags & RTDCF_RC_DATA)
					{
						realTimeDataCustom->RC_Data[SBGC_RC_ROLL] = (i16)gSBGC->_api->readWord(gSBGC);
						realTimeDataCustom->RC_Data[SBGC_RC_PITCH] = (i16)gSBGC->_api->readWord(gSBGC);
						realTimeDataCustom->RC_Data[SBGC_RC_YAW] = (i16)gSBGC->_api->readWord(gSBGC);
						realTimeDataCustom->RC_Data[SBGC_CMD] = (i16)gSBGC->_api->readWord(gSBGC);
						realTimeDataCustom->RC_Data[SBGC_FC_ROLL] = (i16)gSBGC->_api->readWord(gSBGC);
						realTimeDataCustom->RC_Data[SBGC_FC_PITCH] = (i16)gSBGC->_api->readWord(gSBGC);
					}

		if (realTimeDataCustom->flags & RTDCF_Z_VECTOR_H_VECTOR)
		{
			realTimeDataCustom->Z_Vector[SBGC_X] = (float)gSBGC->_api->readLong(gSBGC);
			realTimeDataCustom->Z_Vector[SBGC_Y] = (float)gSBGC->_api->readLong(gSBGC);
			realTimeDataCustom->Z_Vector[SBGC_Z] = (float)gSBGC->_api->readLong(gSBGC);
			realTimeDataCustom->H_Vector[SBGC_X] = (float)gSBGC->_api->readLong(gSBGC);
			realTimeDataCustom->H_Vector[SBGC_Y] = (float)gSBGC->_api->readLong(gSBGC);
			realTimeDataCustom->H_Vector[SBGC_Z] = (float)gSBGC->_api->readLong(gSBGC);
		}

					if (realTimeDataCustom->flags & RTDCF_RC_CHANNELS)
					{
						for (ui8 k = 0; k < 18; k++)
							realTimeDataCustom->RC_Channels[k] = (i16)gSBGC->_api->readWord(gSBGC);
					}

		if (realTimeDataCustom->flags & RTDCF_ACC_DATA)
		{
			realTimeDataCustom->accData[SBGC_X] = (i16)gSBGC->_api->readWord(gSBGC);
			realTimeDataCustom->accData[SBGC_Y] = (i16)gSBGC->_api->readWord(gSBGC);
			realTimeDataCustom->accData[SBGC_Z] = (i16)gSBGC->_api->readWord(gSBGC);
		}

					if (realTimeDataCustom->flags & RTDCF_MOTOR4_CONTROL)
					{
						curCmd_->_payload +=
								gSBGC->_api->convWithPM(&realTimeDataCustom->Motor4_Control, curCmd_->_payload,
														sizeof(sbgcMotor4_Control_t), PM_MOTOR_4_CONTROL);
					}

		if (realTimeDataCustom->flags & RTDCF_AHRS_DEBUG_INFO)
		{
			curCmd_->_payload += gSBGC->_api->convWithPM(&realTimeDataCustom->AHRS_DebugInfo, curCmd_->_payload,
			sizeof(sbgcAHRS_DebugInfo_t), PM_AHRS_DEBUG_INFO);
		}

					if (realTimeDataCustom->flags & RTDCF_ENCODER_RAW24)
					{
						gSBGC->_api->readBuff(gSBGC, realTimeDataCustom->encoderRaw24[SBGC_X], 3);
						gSBGC->_api->readBuff(gSBGC, realTimeDataCustom->encoderRaw24[SBGC_Y], 3);
						gSBGC->_api->readBuff(gSBGC, realTimeDataCustom->encoderRaw24[SBGC_Z], 3);
					}

		if (realTimeDataCustom->flags & RTDCF_IMU_ANGLES_RAD)
		{
			realTimeDataCustom->IMU_AnglesRad[SBGC_X] = (float)gSBGC->_api->readLong(gSBGC);
			realTimeDataCustom->IMU_AnglesRad[SBGC_Y] = (float)gSBGC->_api->readLong(gSBGC);
			realTimeDataCustom->IMU_AnglesRad[SBGC_Z] = (float)gSBGC->_api->readLong(gSBGC);
		}

					if (realTimeDataCustom->flags & RTDCF_SCRIPT_VARS_FLOAT)
					{
						for (ui8 k = 0; k < 10; k++)
							realTimeDataCustom->scriptVarsFloat[k] = (float)gSBGC->_api->readLong(gSBGC);
					}

		if (realTimeDataCustom->flags & RTDCF_SCRIPT_VARS_INT16)
		{
			for (ui8 k = 0; k < 10; k++)
				realTimeDataCustom->scriptVarsInt16[k] = (i16)gSBGC->_api->readWord(gSBGC);
		}

					if (realTimeDataCustom->flags & RTDCF_SYSTEM_POWER_STATE)
					{
						curCmd_->_payload +=
								gSBGC->_api->convWithPM(&realTimeDataCustom->SystemPowerState, curCmd_->_payload,
														sizeof(sbgcSystemPowerState_t), PM_SYSTEM_POWER_STATE);
					}

		if (realTimeDataCustom->flags & RTDCF_FRAME_CAM_RATE)
		{
			realTimeDataCustom->frameCamRate[ROLL] = (i16)gSBGC->_api->readWord(gSBGC);
			realTimeDataCustom->frameCamRate[PITCH] = (i16)gSBGC->_api->readWord(gSBGC);
			realTimeDataCustom->frameCamRate[YAW] = (i16)gSBGC->_api->readWord(gSBGC);
		}

					if (realTimeDataCustom->flags & RTDCF_IMU_ANGLES_20)
					{
						realTimeDataCustom->IMU_Angles20[ROLL] = (i32)gSBGC->_api->readLong(gSBGC);
						realTimeDataCustom->IMU_Angles20[PITCH] = (i32)gSBGC->_api->readLong(gSBGC);
						realTimeDataCustom->IMU_Angles20[YAW] = (i32)gSBGC->_api->readLong(gSBGC);
					}

		if (realTimeDataCustom->flags & RTDCF_TARGET_ANGLES_20)
		{
			realTimeDataCustom->IMU_Angles20[ROLL] = (i32)gSBGC->_api->readLong(gSBGC);
			realTimeDataCustom->IMU_Angles20[PITCH] = (i32)gSBGC->_api->readLong(gSBGC);
			realTimeDataCustom->IMU_Angles20[YAW] = (i32)gSBGC->_api->readLong(gSBGC);
		}

					if (realTimeDataCustom->flags & RTDCF_COMM_ERRORS)
					{
						curCmd_->_payload +=
								gSBGC->_api->convWithPM(&realTimeDataCustom->CommunicationErrors, curCmd_->_payload,
														sizeof(sbgcCommunicationErrors_t), PM_COMMUNICATION_ERRORS);
					}

		if (realTimeDataCustom->flags & RTDCF_SYSTEM_STATE)
		{
			curCmd_->_payload +=
					gSBGC->_api->convWithPM(&realTimeDataCustom->SystemState, curCmd_->_payload,
							sizeof(sbgcSystemState_t), PM_SYSTEM_STATE);
		}

					if (realTimeDataCustom->flags & RTDCF_IMU_QUAT)
						 gSBGC->_api->readBuff(gSBGC, realTimeDataCustom->IMU_Quat, sizeof(realTimeDataCustom->IMU_Quat));

		if (realTimeDataCustom->flags & RTDCF_TARGET_QUAT)
			gSBGC->_api->readBuff(gSBGC, realTimeDataCustom->targetQuat, sizeof(realTimeDataCustom->targetQuat));

					if (realTimeDataCustom->flags & RTDCF_IMU_TO_FRAME_QUAT)
						gSBGC->_api->readBuff(gSBGC, realTimeDataCustom->IMU_ToFrameQuat, sizeof(realTimeDataCustom->IMU_ToFrameQuat));

		if (realTimeDataCustom->flags & RTDCF_ADC_CH_RAW)
			for (ui8 k = 0; k < 4; k++)
				realTimeDataCustom->ADC_ChRaw[k] = gSBGC->_api->readWord(gSBGC);

					if (realTimeDataCustom->flags & RTDCF_SW_LIMITS_DIST)
						for (ui8 k = 0; k < 3; k++)
						{
							realTimeDataCustom->swLimitsDist[k][0] = (i16)gSBGC->_api->readWord(gSBGC);
							realTimeDataCustom->swLimitsDist[k][1] = (i16)gSBGC->_api->readWord(gSBGC);
						}

		if (realTimeDataCustom->flags & RTDCF_FOLLOW_DIST)
			for (ui8 k = 0; k < 3; k++)
				realTimeDataCustom->followDist[k] = (i16)gSBGC->_api->readWord(gSBGC);

					if (realTimeDataCustom->flags & RTDCF_EXT_TARGET_LIMIT)
					{
						realTimeDataCustom->extTargetLimitMin[ROLL] = (i32)gSBGC->_api->readLong(gSBGC);
						realTimeDataCustom->extTargetLimitMin[PITCH] = (i32)gSBGC->_api->readLong(gSBGC);
						realTimeDataCustom->extTargetLimitMin[YAW] = (i32)gSBGC->_api->readLong(gSBGC);
						realTimeDataCustom->extTargetLimitMax[ROLL] = (i32)gSBGC->_api->readLong(gSBGC);
						realTimeDataCustom->extTargetLimitMax[PITCH] = (i32)gSBGC->_api->readLong(gSBGC);
						realTimeDataCustom->extTargetLimitMax[YAW] = (i32)gSBGC->_api->readLong(gSBGC);
					}

	#endif
}


/**	@brief	Requests configurable realtime data
 *
 *	####	TX —> CMD_REALTIME_DATA_CUSTOM :		10 bytes
 *	####	RX <— CMD_REALTIME_DATA_CUSTOM :		2 + ? bytes
 *
 *	@pre	Must be set:\n
 *			sbgcRealTimeDataCustomReference_t.flags :
 *				bit0:		sbgcRealTimeDataCustomReference_t.IMU_Angles [3]			RTDCF_IMU_ANGLES								\n
 *				bit1:		sbgcRealTimeDataCustomReference_t.targetAngles [3]			RTDCF_TARGET_ANGLES								\n
 *				bit2:		sbgcRealTimeDataCustomReference_t.targetSpeed [3]			RTDCF_TARGET_SPEED								\n
 *				bit3:		sbgcRealTimeDataCustomReference_t.frameCamAngle [3]			RTDCF_STATOR_ROTOR_ANGLE						\n
 *				bit4:		sbgcRealTimeDataCustomReference_t.gyroData [3]				RTDCF_GYRO_DATA									\n
 *				bit5:		sbgcRealTimeDataCustomReference_t.RC_Data [6]				RTDCF_RC_DATA									\n
 *				bit6:		sbgcRealTimeDataCustomReference_t.Z_Vector [3],
 *							sbgcRealTimeDataCustomReference_t.H_Vector [3]				RTDCF_Z_VECTOR_H_VECTOR							\n
 *				bit7:		sbgcRealTimeDataCustomReference_t.RC_Channels [18]			RTDCF_RC_CHANNELS								\n
 *				bit8:		sbgcRealTimeDataCustomReference_t.accData [3]				RTDCF_ACC_DATA									\n
 *				bit9:		sbgcRealTimeDataCustomReference_t.Motor4_Control struct		RTDCF_MOTOR4_CONTROL							\n
 *				bit10:		sbgcRealTimeDataCustomReference_t.AHRS_DebugInfo struct		RTDCF_AHRS_DEBUG_INFO							\n
 *				bit11:		sbgcRealTimeDataCustomReference_t.encoderRaw24 [3][3]		RTDCF_ENCODER_RAW24			Frw. ver. 2.68+		\n
 *				bit12:		sbgcRealTimeDataCustomReference_t.IMU_AnglesRad [3]			RTDCF_IMU_ANGLES_RAD		Frw. ver. 2.68b7+	\n
 *				bit13:		sbgcRealTimeDataCustomReference_t.scriptVarsFloat [10]		RTDCF_SCRIPT_VARS_FLOAT		Frw. ver. 2.68b7+	\n
 *				bit14:		sbgcRealTimeDataCustomReference_t.scriptVarsInt16 [10]		RTDCF_SCRIPT_VARS_INT16		Frw. ver. 2.68b7+	\n
 *				bit15:		sbgcRealTimeDataCustomReference_t.SystemPowerState struct	RTDCF_SYSTEM_POWER_STATE	Frw. ver. 2.70b6+	\n
 *				bit16:		sbgcRealTimeDataCustomReference_t.frameCamRate [3]			RTDCF_FRAME_CAM_RATE		Frw. ver. 2.70b6+	\n
 *				bit17:		sbgcRealTimeDataCustomReference_t.IMU_Angles20 [3]			RTDCF_IMU_ANGLES_20			Frw. ver. 2.70b8+	\n
 *				bit18:		sbgcRealTimeDataCustomReference_t.targetAngles20 [3]		RTDCF_TARGET_ANGLES_20		Frw. ver. 2.70b8+	\n
 *				bit19:		sbgcRealTimeDataCustomReference_t.CommunicationErrors		RTDCF_COMM_ERRORS			Frw. ver. 2.72b0+	\n
 *				bit20:		sbgcRealTimeDataCustomReference_t.SystemStateFlags			RTDCF_SYSTEM_STATE			Frw. ver. 2.73+		\n
 *				bit21:		sbgcRealTimeDataCustomReference_t.IMU_Quat [8]				RTDCF_IMU_QUAT				Frw. ver. 2.73+		\n
 *				bit22:		sbgcRealTimeDataCustomReference_t.targetQuat [8]			RTDCF_TARGET_QUAT			Frw. ver. 2.73+		\n
 *				bit23:		sbgcRealTimeDataCustomReference_t.IMU_ToFrameQuat [8]		RTDCF_IMU_TO_FRAME_QUAT		Frw. ver. 2.73+		\n
 *				bit24:		sbgcRealTimeDataCustomReference_t.ADC_ChRaw [4]				RTDCF_ADC_CH_RAW			Frw. ver. 2.73+		\n
 *				bit25:		sbgcRealTimeDataCustomReference_t.swLimitsDist [3][2]		RTDCF_SW_LIMITS_DIST		Frw. ver. 2.73.8+	\n
 *				bit26:		sbgcRealTimeDataCustomReference_t.followDist [3]			RTDCF_FOLLOW_DIST			Frw. ver. 2.73.8+	\n
 *				bit27:		sbgcRealTimeDataCustomReference_t.extTargetLimitMin [3],
 *							sbgcRealTimeDataCustomReference_t.extTargetLimitMax [3]		RTDCF_EXT_TARGET_LIMIT		Frw. ver. 2.73.8+
 *
 *	@pre	Board requirements:\n
 *			ENCODERS = (1 << 2) when using RTDCF_ENCODER_RAW24 \n
 *			SCRIPTING = (1 << 4) when using RTDCF_SCRIPT_VARS_FLOAT or
 *			RTDCF_SCRIPT_VARS_INT16 \n
 *			POWER_MANAGEMENT = (1 << 19) (ext.) when using RTDCF_SYSTEM_POWER_STATE \n
 *			QUAT_CONTROL = (1 << 3) (ext.2) when using RTDCF_IMU_QUAT or
 *			RTDCF_TARGET_QUAT or RTDCF_IMU_TO_FRAME_QUAT
 *
 *	@post	Use the @ref DebugSBGC32_PrintWholeStruct
 *			function with PM_MOTOR_4_CONTROL or
 *			PM_AHRS_DEBUG_INFO or PM_SYSTEM_POWER_STATE or
 *			PM_COMMUNICATION_ERRORS or PM_SYSTEM_STATE to
 *			print received data. The function should receive a
 *			pointer to this part of the common structure exact
 *
 *	@attention	Firmware: 2.60+
 *
 *	@code

			#if (SBGC_SYS_LITTLE_ENDIAN)

				struct PACKED__ RealTimeDataCustomStruct
				{
					// Mandatory fields, don't remove!
					ui32 flags;
					ui16 timestampMs;

					// Additional fields, depended on 'flags'
					i16 frameCamAngle [3];
					i16 gyroData [3];
					i16 accData [3];

					sbgcAHRS_DebugInfo_t AHRS_DebugInfo;

				}	RealTimeDataCustom;

			#else
				sbgcRealTimeDataCustomReference_t RealTimeDataCustom;
			#endif

			RealTimeDataCustom.flags = RTDCF_STATOR_ROTOR_ANGLE | RTDCF_GYRO_DATA |
									   RTDCF_ACC_DATA | RTDCF_AHRS_DEBUG_INFO;

			SBGC32_RequestRealTimeDataCustom(&SBGC32_Device, &RealTimeDataCustom, sizeof(RealTimeDataCustom));

			#if (SBGC_NEED_DEBUG)

				// Print camera angles for example
				i16 frameCamAngleTemp;

				frameCamAngleTemp = sbgcDegreeToAngle(RealTimeDataCustom.frameCamAngle[ROLL]);
				DebugSBGC32_PrintStructElement(&SBGC32_Device, &frameCamAngleTemp, "FCA ROLL =", sbgcSHORT);

				frameCamAngleTemp = sbgcDegreeToAngle(RealTimeDataCustom.frameCamAngle[PITCH]);
				DebugSBGC32_PrintStructElement(&SBGC32_Device, &frameCamAngleTemp, "FCA PITCH =", sbgcSHORT);

				frameCamAngleTemp = sbgcDegreeToAngle(RealTimeDataCustom.frameCamAngle[YAW]);
				DebugSBGC32_PrintStructElement(&SBGC32_Device, &frameCamAngleTemp, "FCA YAW =", sbgcSHORT);

				#if (SBGC_NEED_REF_INFO)

					// Also print whole AHRS debug data
					DebugSBGC32_PrintWholeStruct(&SBGC32_Device, &RealTimeDataCustom.AHRS_DebugInfo, PM_AHRS_DEBUG_INFO);

				#endif

			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*realTimeDataCustom - structure for storing
 *			any pieces of real-time data. Using a
 *			big-endian memory organization device
 *			it is necessary to pass the full
 *			sbgcRealTimeDataCustomReference_t structure
 *	@param	size - data structure size
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_RequestRealTimeDataCustom (sbgcGeneral_t *gSBGC, void *realTimeDataCustom, ui8 size
													  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2600)

	ui32 flags = *(ui32*)realTimeDataCustom;

	#if (SBGC_NEED_ASSERTS)

		if (SerialAPI_AssertRealTimeDataCustomFlags(gSBGC, flags) != sbgcCOMMAND_OK)
			return sbgcCOMMAND_NOT_SUPPORTED_FEATURE;

	#endif

	#if (SBGC_NEED_ASSERTS)

		if (((gSBGC->_api->baseFirmwareVersion < 2680) && (flags >= RTDCF_ENCODER_RAW24)) ||
			((gSBGC->_api->baseFirmwareVersion < 2687) && (flags >= RTDCF_IMU_ANGLES_RAD)) ||
			((gSBGC->_api->baseFirmwareVersion < 2706) && (flags >= RTDCF_SYSTEM_POWER_STATE)) ||
			((gSBGC->_api->baseFirmwareVersion < 2708) && (flags >= RTDCF_IMU_ANGLES_20)) ||
			((gSBGC->_api->baseFirmwareVersion < 2720) && (flags >= RTDCF_COMM_ERRORS)) ||
			((gSBGC->_api->baseFirmwareVersion < 2730) && (flags >= RTDCF_SYSTEM_STATE)))
			return sbgcCOMMAND_NOT_SUPPORTED_BY_FIRMWARE;

	#endif

	gSBGC->_api->startWrite(gSBGC, CMD_REALTIME_DATA_CUSTOM SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeLong(gSBGC, flags);
	gSBGC->_api->writeEmptyBuff(gSBGC, 6);  // reserved[6]
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_REALTIME_DATA_CUSTOM SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, PostRequestRealTimeDataCustom, realTimeDataCustom, size);
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Realtime_Data_3_4
 *	@{
 */
/**	@brief	Receives real-time data
 *
 *	####	TX —> CMD_REALTIME_DATA_3 :		with no payload
 *	####	RX <— CMD_REALTIME_DATA_3 :		63 bytes
 *
 *	@post	Use the @ref DebugSBGC32_PrintWholeStruct
 *			function with PM_REALTIME_DATA_3 to print
 *			received data
 *
 *	@code

			sbgcRealTimeData_t RealTimeData;

			SBGC32_ReadRealTimeData3(&SBGC32_Device, &RealTimeData);

			#if (SBGC_NEED_DEBUG && SBGC_NEED_REF_INFO)
				DebugSBGC32_PrintWholeStruct(&SBGC32_Device, &RealTimeData, PM_REALTIME_DATA_3);
			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*realTimeData - structure for storing real-time data
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ReadRealTimeData3 (sbgcGeneral_t *gSBGC, sbgcRealTimeData_t *realTimeData
											  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_REALTIME_DATA_3 SBGC_ADVANCED_ARGS__);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_REALTIME_DATA_3 SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, NULL, realTimeData, SIZEOF_REALTIME_DATA_3);
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Receives extended version of real-time data
 *
 *	####	TX —> CMD_REALTIME_DATA_4 :		with no payload
 *	####	RX <— CMD_REALTIME_DATA_4 :		124 bytes
 *
 *	@post	Use the @ref DebugSBGC32_PrintWholeStruct
 *			function with PM_REALTIME_DATA_4 to print
 *			received data
 *
 *	@note	This function is similar to
 *			@ref SBGC32_ReadRealTimeData3. Refer to
 *			its documentation for code example details
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*realTimeData - structure for storing real-time data
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ReadRealTimeData4 (sbgcGeneral_t *gSBGC, sbgcRealTimeData_t *realTimeData
											  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_REALTIME_DATA_4 SBGC_ADVANCED_ARGS__);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_REALTIME_DATA_4 SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, NULL, realTimeData, sizeof(sbgcRealTimeData_t));
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Get_Angles
 *	@{
 */
/**	@brief	Get information about the actual gimbal control state
 *
 *	####	TX —> CMD_GET_ANGLES :	with no payload
 *	####	RX <— CMD_GET_ANGLES :	18 bytes
 *
 *	@post	Use the @ref DebugSBGC32_PrintWholeStruct
 *			function with PM_GET_ANGLES to print
 *			received data
 *
 *	@code

			sbgcGetAngles_t GetAngles;

			SBGC32_GetAngles(&SBGC32_Device, &GetAngles);

			#if (SBGC_NEED_DEBUG && SBGC_NEED_REF_INFO)
				DebugSBGC32_PrintWholeStruct(&SBGC32_Device, &GetAngles, PM_GET_ANGLES);
			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*getAngles - structure for storing angles state
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_GetAngles (sbgcGeneral_t *gSBGC, sbgcGetAngles_t *getAngles
									  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_GET_ANGLES SBGC_ADVANCED_ARGS__);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_GET_ANGLES SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, NULL, getAngles, sizeof(sbgcGetAngles_t));
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Get information about angles in different format
 *
 *	####	TX —> CMD_GET_ANGLES_EXT :		with no payload
 *	####	RX <— CMD_GET_ANGLES_EXT :		54 bytes
 *
 *	@post	Use the @ref DebugSBGC32_PrintWholeStruct
 *			function with PM_GET_ANGLES_EXT to print
 *			received data
 *
 *	@note	This function is similar to
 *			@ref SBGC32_GetAngles. Refer to its
 *			documentation for code example details
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*getAnglesExt - structure for storing
 *			angles state in extended format
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_GetAnglesExt (sbgcGeneral_t *gSBGC, sbgcGetAnglesExt_t *getAnglesExt
										 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_GET_ANGLES_EXT SBGC_ADVANCED_ARGS__);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_GET_ANGLES_EXT SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, NULL, getAnglesExt, sizeof(sbgcGetAnglesExt_t));
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	RC_Inputs
 *	@{
 */
/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_ReadRC_Inputs function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostReadRC_Inputs (sbgcGeneral_t *gSBGC)
{
	if (curCmd_->_destinationSize < curCmd_->_payloadSize)
		SerialAPI_FatalErrorHandler();

	sbgcRC_Inputs_t *RC_Inputs = (sbgcRC_Inputs_t*)curCmdDest_;

	for (ui8 i = 0; i < (curCmd_->_payloadSize / 2); i++)
		RC_Inputs[i].RC_Val = (i16)gSBGC->_api->readWord(gSBGC);
}

/**	@brief	Reads values for the selected RC inputs
 *
 *	####	TX —> CMD_READ_RC_INPUTS :		1 + srcQuan bytes
 *	####	RX <— CMD_READ_RC_INPUTS :		srcQuan * 2 bytes
 *
 *	@pre	Must be set:\n
 *			sbgcRC_Inputs_t.RC_Src
 *
 *	@note	It can be an array of structures with no more
 *			than SBGC_ALL_RC_CHANNELS_NUM (42) elements
 *
 *	@code

			sbgcRC_Inputs_t RC_Inputs [SBGC_RC_ADC_CHANNELS_NUM];

			// Try to read analog RC channels
			RC_Inputs[0].RC_Src = sbgcRCMap_ADC_1;
			RC_Inputs[1].RC_Src = sbgcRCMap_ADC_2;
			RC_Inputs[2].RC_Src = sbgcRCMap_ADC_3;

			SBGC32_ReadRC_Inputs(&SBGC32_Device, RC_Inputs, ICF_DONT_TRY_TO_INIT_INPUT, SBGC_RC_ADC_CHANNELS_NUM);

			#if (SBGC_NEED_DEBUG)

				DebugSBGC32_PrintStructElement(&SBGC32_Device, &RC_Inputs[0].RC_Val, "RC ADC CH 1 =", sbgcSHORT);
				DebugSBGC32_PrintStructElement(&SBGC32_Device, &RC_Inputs[1].RC_Val, "RC ADC CH 2 =", sbgcSHORT);
				DebugSBGC32_PrintStructElement(&SBGC32_Device, &RC_Inputs[2].RC_Val, "RC ADC CH 3 =", sbgcSHORT);
				// * a -32768 value means that this channel isn't active

			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*RC_Inputs - structure to send and store RC Inputs info
 *	@param	cfgFlags - RC configuration flags
 *	@param	srcQuan - quantity of RC sources
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ReadRC_Inputs (sbgcGeneral_t *gSBGC, sbgcRC_Inputs_t *RC_Inputs, sbgcInitCfgFlag_t cfgFlags, ui8 srcQuan
										  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertParam(srcQuan, 1, SBGC_ALL_RC_CHANNELS_NUM)

	gSBGC->_api->startWrite(gSBGC, CMD_READ_RC_INPUTS SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeWord(gSBGC, cfgFlags);
	for (ui8 i = 0; i < srcQuan; i++) gSBGC->_api->writeByte(gSBGC, RC_Inputs[i].RC_Src);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_READ_RC_INPUTS SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, PostReadRC_Inputs, RC_Inputs, sizeof(RC_Inputs->RC_Val) * srcQuan);
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Debug_Var_3
 *	@{
 */
/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_RequestDebugVarInfo3 function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostRequestDebugVarInfo3 (sbgcGeneral_t *gSBGC)
{
	sbgcDebugVar3_Info_t *debugVars3_Info = (sbgcDebugVar3_Info_t*)curCmdDest_;
	ui8 payloadSize = curCmd_->_payloadSize;

	ui8 varNum = gSBGC->_api->readByte(gSBGC);

	if (curCmd_->_destinationSize < (sizeof(sbgcDebugVar3_Info_t) * varNum))
		SerialAPI_FatalErrorHandler();

	payloadSize--;

	for (ui8 i = 0; i < varNum; i++)
	{
		if (payloadSize == 0)
			break;

		debugVars3_Info[i].nameLength = gSBGC->_api->readByte(gSBGC);
		gSBGC->_api->readBuff(gSBGC, debugVars3_Info[i].name, debugVars3_Info[i].nameLength);
		debugVars3_Info[i].name[debugVars3_Info[i].nameLength] = '\0';
		debugVars3_Info[i].type = gSBGC->_api->readByte(gSBGC);
		gSBGC->_api->skipBytes(gSBGC, 2);

		payloadSize -= (4 + debugVars3_Info[i].nameLength);
	}
}

/**	@brief	Requests information about debug variables
 *
 *	####	TX —> CMD_DEBUG_VARS_INFO_3 :	1 byte (prior to frw. ver. 2.72b0 - with no payload)
 *	####	RX <— CMD_DEBUG_VARS_INFO_3 :	srcQuan * 2 bytes
 *
 *	@pre	It's necessary to know about actual
 *			debug variables quantity
 *
 *	@code

			#define SBGC_DEBUG_VARS_NUM 23
			#define SBGC_DEBUG_VARS_NAME_LENGHT 10

			sbgcDebugVars3_t DebugVars3;
			sbgcDebugVar3_Info_t DebugVar3_Info [SBGC_DEBUG_VARS_NUM] = { 0 };
			ui8 count = 0;

			DebugVars3.debugVar3_Info = DebugVar3_Info;

			for (ui8 i = 0; i < SBGC_DEBUG_VARS_NUM; i++)
				DebugVar3_Info[i].name = (char*)sbgcMalloc(SBGC_DEBUG_VARS_NAME_LENGHT);

			// First request
			SBGC32_RequestDebugVarInfo3(&SBGC32_Device, DebugVar3_Info, 0, SBGC_DEBUG_VARS_NUM);

			for ( ; count < SBGC_DEBUG_VARS_NUM; count++)
				if (DebugVar3_Info[count].nameLength == 0)
					break;

			if (count < SBGC_DEBUG_VARS_NUM)
			// Second request
				SBGC32_RequestDebugVarInfo3(&SBGC32_Device, &DebugVar3_Info[count], count, SBGC_DEBUG_VARS_NUM);

			// Don't use masks, accessing all variables
			DebugVars3.mask = NULL;

			// Read debug variable values
			SBGC32_RequestDebugVarValue3(&SBGC32_Device, &DebugVars3);

 *	@endcode
 *
 *	@note	Firmware 2.72b0+ for startIndex parameter
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*debugVar3_Info - structure to storing
 *			debug variables information
 *	@param	startIndex - defines which index to start from
 *	@param	varQuan - maximal number of debug variables
 *			the buffer can hold
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_RequestDebugVarInfo3 (sbgcGeneral_t *gSBGC, sbgcDebugVar3_Info_t *debugVar3_Info, ui8 startIndex, ui8 varQuan
												 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_DEBUG_VARS_INFO_3 SBGC_ADVANCED_ARGS__);

	if (gSBGC->_api->baseFirmwareVersion >= 2720)
		gSBGC->_api->writeByte(gSBGC, startIndex);

	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_DEBUG_VARS_INFO_3 SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, PostRequestDebugVarInfo3, debugVar3_Info, sizeof(sbgcDebugVar3_Info_t) * varQuan);
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_RequestDebugVarValue3 function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostRequestDebugVarValue3 (sbgcGeneral_t *gSBGC)
{
	sbgcDebugVars3_t *debugVars3 = (sbgcDebugVars3_t*)curCmdDest_;
	ui8 payloadSize = curCmd_->_payloadSize;
	ui8 varNum = 0;

	for ( ; payloadSize; varNum++)
	{
		if ((gSBGC->_api->baseFirmwareVersion > 2720) && (debugVars3->mask != NULL))
			payloadSize -= sizeof(ui32);  // mask

		payloadSize -= gSBGC->_api->typeToSize(debugVars3->debugVar3_Info[varNum].type);
	}

	for (ui8 i = 0; i < varNum; i++)
	{
		switch (gSBGC->_api->typeToSize(debugVars3->debugVar3_Info[i].type))
		{
			case 1 :
				debugVars3->debugVar3_Info[i].value = gSBGC->_api->readByte(gSBGC);
				break;

			case 2 :
				debugVars3->debugVar3_Info[i].value = gSBGC->_api->readWord(gSBGC);
				break;

			case 4 :
				debugVars3->debugVar3_Info[i].value = gSBGC->_api->readLong(gSBGC);
				break;
		}
	}
}

/**	@brief	Requests values of debug variables
 *
 *	####	TX —> CMD_DEBUG_VARS_3 :		4 * maskQuan bytes (prior to frw. ver. 2.72b0 - with no payload)
 *	####	RX <— CMD_DEBUG_VARS_3 :		(4 + ?) * maskQuan bytes
 *
 *	@pre	Before using need get information about debug variables
 *			through @ref SBGC32_RequestDebugVarInfo3 function
 *
 *	@pre	Must be set:\n
 *			Frw. ver. 2.72b0+\n
 *			sbgcDebugVars3_t.mask \n
 *			sbgcDebugVars3_t.maskQuan
 *
 *	@note	See @ref SBGC32_RequestDebugVarInfo3 function
 *			documentation for usage example
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*debugVars3 - structure to storing debug variables
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_RequestDebugVarValue3 (sbgcGeneral_t *gSBGC, sbgcDebugVars3_t *debugVars3
												  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_DEBUG_VARS_3 SBGC_ADVANCED_ARGS__);

	if ((gSBGC->_api->baseFirmwareVersion >= 2720) && (debugVars3->mask != NULL))
		for (ui8 i = 0; i < debugVars3->maskQuan; i++)
			gSBGC->_api->writeLong(gSBGC, debugVars3->mask[i]);

	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_DEBUG_VARS_3 SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, PostRequestDebugVarValue3, debugVars3, SBGC_MAX_PAYLOAD_SIZE);
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	IMU_Select_3
 *	@{
 */
/**	@brief	Selects which IMU to configure
 *
 *	####	TX —> CMD_SELECT_IMU_3 :		1/11 bytes
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@pre	For select in simple format, the 'action' parameter
 *			should be set to SIMUA_SIMPLE_SELECT
 *
 *	@code

			// Select a frame IMU sensor for the next actions
			SBGC32_SelectIMU_3(&SBGC32_Device, sbgcIMU_TYPE_FRAME, SIMUA_SIMPLE_SELECT, 0, SBGC_NO_CONFIRM);

			// ...
			// Do regular calibration for a main IMU sensor
			SBGC32_SelectIMU_3(&SBGC32_Device, sbgcIMU_TYPE_MAIN, SIMUA_REGULAR_CALIBRATION, 0, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	IMU_Type - main or frame IMU sensor
 *	@param	action - action with IMU sensor
 *	@param	timeMs - time for gyroscope calibration, in milliseconds.
 *			If set to 0, default time is used (~4 seconds), which
 *			is good balance between precision and speed
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SelectIMU_3 (sbgcGeneral_t *gSBGC, sbgcIMU_Type_t IMU_Type, sbgcSelectIMU_Action_t action, ui16 timeMs,
										sbgcConfirm_t *confirm
										/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_SELECT_IMU_3 SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, IMU_Type);

	if (action)  // != SIMUA_SIMPLE_SELECT
	{
		gSBGC->_api->writeByte(gSBGC, action);
		gSBGC->_api->writeWord(gSBGC, timeMs);
		gSBGC->_api->writeEmptyBuff(gSBGC, 8);  // reserved[8]
	}

	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_SELECT_IMU_3 SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Control_Quat_Status
 *	@{
 */
/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_ControlQuatStatus function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostControlQuatStatus (sbgcGeneral_t *gSBGC)
{
	ui8 bytesSkip = sizeof(ui32);

	if (curCmd_->_destinationSize < (curCmd_->_payloadSize - bytesSkip))
		SerialAPI_FatalErrorHandler();

	gSBGC->_api->skipBytes(gSBGC, bytesSkip);
	gSBGC->_api->readBuff(gSBGC, curCmdDest_, curCmd_->_payloadSize - bytesSkip);
}

/**	@brief	Requests quaternions realtime data
 *
 *	####	TX —> CMD_CONTROL_QUAT_STATUS :	4 bytes
 *	####	RX <— CMD_CONTROL_QUAT_STATUS : ? bytes
 *
 *	@pre	Board requirements:\n
 *			QUAT_CONTROL = (1 << 3) (ext.2)
 *
 *	@code

			#if (SBGC_SYS_LITTLE_ENDIAN)

				struct PACKED__ ControlQuatStatusStruct
				{
					ui8		mode;
					ui16	flags;

					i16		targetSpeed [3],
							setPointSpeed [3],
							actualSpeed [3];

				}	ControlQuatStatus = { 0 };

			#else
				sbgcControlQuatStatusReference_t ControlQuatStatus = { 0 };
			#endif

			SBGC32_ControlQuatStatus(&SBGC32_Device, CQSF_MODE_AND_FLAGS | CQSF_TARGET_SPEED | CQSF_SETPOINT_SPEED | CQSF_ACTUAL_SPEED,
					&ControlQuatStatus, sizeof(ControlQuatStatus));

			#if (SBGC_NEED_DEBUG)

				// Print target speed of the roll axis for example
				i16 targetSpeedTemp;

				targetSpeedTemp = sbgcValueToSpeed(ControlQuatStatus.targetSpeed[ROLL]);
				DebugSBGC32_PrintStructElement(&SBGC32_Device, &targetSpeedTemp, "TS ROLL =", sbgcSHORT);

				targetSpeedTemp = sbgcValueToSpeed(ControlQuatStatus.targetSpeed[PITCH]);
				DebugSBGC32_PrintStructElement(&SBGC32_Device, &targetSpeedTemp, "TS PITCH =", sbgcSHORT);

				targetSpeedTemp = sbgcValueToSpeed(ControlQuatStatus.targetSpeed[YAW]);
				DebugSBGC32_PrintStructElement(&SBGC32_Device, &targetSpeedTemp, "TS YAW =", sbgcSHORT);

			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	flags - bit mask defining required data
 *	@param	*data - initialized manually by user. See
 *			@ref sbgcControlQuatStatusFlag_t enumeration.
 *			Also for more, see the CMD_CONTROL_QUAT_STATUS command in the
 *			<a href=https://www.basecamelectronics.com/serialapi/>
 *			SimpleBGC32 Serial API protocol specification</a>. Using a
 *			big-endian memory organization device
 *			it is necessary to pass the full
 *			sbgcControlQuatStatusReference_t structure
 *	@param	size - data structure size
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ControlQuatStatus (sbgcGeneral_t *gSBGC, sbgcControlQuatStatusFlag_t flags, void *data, ui8 size
											  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFeature2(BFE2_QUAT_CONTROL)

	gSBGC->_api->startWrite(gSBGC, CMD_CONTROL_QUAT_STATUS SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeLong(gSBGC, flags);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_CONTROL_QUAT_STATUS SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, PostControlQuatStatus, data, size);
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */

#endif /* SBGC_REALTIME_MODULE */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
