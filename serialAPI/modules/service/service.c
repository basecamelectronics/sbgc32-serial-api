/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2.1
 *
 *	@file		service.c
 *
 *	@brief		Service source file
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


#if (SBGC_SERVICE_MODULE)

/* Borrowed Functions  -------------------------------------------------
 */
extern sbgcCommandStatus_t SBGC32_SendEmptyCommand (sbgcGeneral_t *gSBGC, serialAPI_CommandID_t cmdID
													/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */);


#if (SBGC_USES_REF_INFO)

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *					Big Endian Mapping and Reference Info Structures
	 */
	/**	@addtogroup	Board_Info
	 *	@{
	 */
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t boardInfoReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Board Ver",				sbgcUCHAR						),  // 0
		PARAM_BLOCK_(	"Firmware Ver",				sbgcUSHORT						),  // 1
		PARAM_BLOCK_(	"State Flags 1",			(sbgcUCHAR | sbgcFLAG)			),  // 2
		PARAM_BLOCK_(	"Board Features",			(sbgcUSHORT | sbgcFLAG)			),  // 3
		PARAM_BLOCK_(	"Connection Flag",			(sbgcUCHAR | sbgcFLAG)			),  // 4
		PARAM_BLOCK_(	"Frw Extra ID",				sbgcUINT						),  // 5
		PARAM_BLOCK_(	"Board Features Ext",		(sbgcUSHORT | sbgcFLAG)			),  // 6
		PARAM_BLOCK_(	"Main IMU Sens Model",		sbgcUCHAR						),  // 7
		PARAM_BLOCK_(	"Frame IMU Sens Model",		sbgcUCHAR						),  // 8
		PARAM_BLOCK_(	"Build Number",				sbgcUCHAR						),  // 9
		PARAM_BLOCK_(	"Base Frw Ver",				sbgcUSHORT						),  // 10

	};

	const ui8 boardInfoReferenceInfoArrayElCnt = countof_(boardInfoReferenceInfoArray);


	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t boardInfo3_ReferenceInfoArray [] =
	{
		PARAMS_BLOCK_(	"Device ID",				sbgcUCHAR,					9	),  // 0
		PARAMS_BLOCK_(	"MCU ID",					sbgcUCHAR,					12	),  // 1
		PARAM_BLOCK_(	"EEPROM Size",				sbgcUINT						),  // 2
		PARAM_BLOCK_(	"Script Slot 1 Size",		sbgcUSHORT						),  // 3
		PARAM_BLOCK_(	"Script Slot 2 Size",		sbgcUSHORT						),  // 4
		PARAM_BLOCK_(	"Script Slot 3 Size",		sbgcUSHORT						),  // 5
		PARAM_BLOCK_(	"Script Slot 4 Size",		sbgcUSHORT						),  // 6
		PARAM_BLOCK_(	"Script Slot 5 Size",		sbgcUSHORT						),  // 7
		PARAM_BLOCK_(	"Profile Set Slots",		sbgcUCHAR						),  // 8
		PARAM_BLOCK_(	"Profile Set Cur",			sbgcUCHAR						),  // 9
		PARAMS_BLOCK_(	"IMU Calib Info",			sbgcUCHAR,					2	),  // 10
		PARAM_BLOCK_(	"Script Slot 6 Size",		sbgcUSHORT						),  // 11
		PARAM_BLOCK_(	"Script Slot 7 Size",		sbgcUSHORT						),  // 12
		PARAM_BLOCK_(	"Script Slot 8 Size",		sbgcUSHORT						),  // 13
		PARAM_BLOCK_(	"Script Slot 9 Size",		sbgcUSHORT						),  // 14
		PARAM_BLOCK_(	"Script Slot 10 Size",		sbgcUSHORT						),  // 15
		PARAM_BLOCK_(	"Hardware Flags",			(sbgcUSHORT | sbgcFLAG)			),  // 16
		PARAM_BLOCK_(	"Board Features Ext 2",		(sbgcUINT | sbgcFLAG)			),  // 17
		PARAM_BLOCK_(	"CAN Drv Main Limit",		sbgcUCHAR						),  // 18
		PARAM_BLOCK_(	"CAN Drv Aux Limit",		sbgcUCHAR						),  // 19
		PARAM_BLOCK_(	"Adj Vars Total Num",		sbgcUCHAR						),  // 20
		PARAMS_BLOCK_(	"Reserved",					sbgcRCHAR,					10	),  // 21

	};

	const ui8 boardInfo3_ReferenceInfoArrayElCnt = countof_(boardInfo3_ReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Auto_PID
	 *	@{
	 */
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t autoPID_ReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Profile ID",				sbgcUCHAR						),  // 0
		PARAM_BLOCK_(	"Cfg Flags",				sbgcUCHAR						),  // 1
		PARAM_BLOCK_(	"Gain VS Stability",		sbgcUCHAR						),  // 2
		PARAM_BLOCK_(	"Momentum",					sbgcUCHAR						),  // 3
		PARAM_BLOCK_(	"Action",					sbgcUCHAR						),  // 4
		PARAMS_BLOCK_(	"Reserved",					sbgcRCHAR,					14	),  // 5

	};

	const ui8 autoPID_ReferenceInfoArrayElCnt = countof_(autoPID_ReferenceInfoArray);


	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t autoPID2_ReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Action",					sbgcUCHAR						),  // 0
		PARAM_BLOCK_(	"Cmd Flags",				(sbgcUSHORT | sbgcFLAG)			),  // 1
		PARAMS_BLOCK_(	"Reserved 1",				sbgcRCHAR,					8	),  // 2
		PARAM_BLOCK_(	"Cfg Version",				sbgcUCHAR						),  // 3
		PARAM_BLOCK_(	"Axis Flag [ROLL]",			(sbgcUCHAR | sbgcFLAG)			),  // 4
		PARAM_BLOCK_(	"Gain [ROLL]",				sbgcUCHAR						),  // 5
		PARAM_BLOCK_(	"Stimulus Gain [ROLL]",		sbgcUSHORT						),  // 6
		PARAM_BLOCK_(	"Effective Freq [ROLL]",	sbgcUCHAR						),  // 7
		PARAM_BLOCK_(	"Problem Freq [ROLL]",		sbgcUCHAR						),  // 8
		PARAM_BLOCK_(	"Problem Margin [ROLL]",	sbgcUCHAR						),  // 9
		PARAMS_BLOCK_(	"Reserved 2 [ROLL]",		sbgcRCHAR,					6	),  // 10
		PARAM_BLOCK_(	"Axis Flag [PITCH]",		(sbgcUCHAR | sbgcFLAG)			),  // 11
		PARAM_BLOCK_(	"Gain [PITCH]",				sbgcUCHAR						),  // 12
		PARAM_BLOCK_(	"Stimulus Gain [PITCH]",	sbgcUSHORT						),  // 13
		PARAM_BLOCK_(	"Effective Freq [PITCH]",	sbgcUCHAR						),  // 14
		PARAM_BLOCK_(	"Problem Freq [PITCH]",		sbgcUCHAR						),  // 15
		PARAM_BLOCK_(	"Problem Margin [PITCH]",	sbgcUCHAR						),  // 16
		PARAMS_BLOCK_(	"Reserved 2 [PITCH]",		sbgcRCHAR,					6	),  // 17
		PARAM_BLOCK_(	"Axis Flag [YAW]",			(sbgcUCHAR | sbgcFLAG)			),  // 18
		PARAM_BLOCK_(	"Gain [YAW]",				sbgcUCHAR						),  // 19
		PARAM_BLOCK_(	"Stimulus Gain [YAW]",		sbgcUSHORT						),  // 20
		PARAM_BLOCK_(	"Effective Freq [YAW]",		sbgcUCHAR						),  // 21
		PARAM_BLOCK_(	"Problem Freq [YAW]",		sbgcUCHAR						),  // 22
		PARAM_BLOCK_(	"Problem Margin [YAW]",		sbgcUCHAR						),  // 23
		PARAMS_BLOCK_(	"Reserved 2 [YAW]",			sbgcRCHAR,					6	),  // 24
		PARAM_BLOCK_(	"General Flags",			(sbgcUSHORT | sbgcFLAG)			),  // 25
		PARAM_BLOCK_(	"Reserved 3",				sbgcRCHAR						),  // 26
		PARAM_BLOCK_(	"Test Frequency From",		sbgcUCHAR						),  // 27
		PARAM_BLOCK_(	"Test Frequency To",		sbgcUCHAR						),  // 28
		PARAM_BLOCK_(	"Multi Pos Flag",			(sbgcUCHAR | sbgcFLAG)			),  // 29
		PARAMS_BLOCK_(	"Multi Pos Angle",			sbgcCHAR,					4	),  // 30
		PARAMS_BLOCK_(	"Reserved 4",				sbgcRCHAR,					12	),  // 31

	};

	const ui8 autoPID2_ReferenceInfoArrayElCnt = countof_(autoPID2_ReferenceInfoArray);


	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t autoPID_StateReferenceInfoArray [] =
	{
		PARAMS_BLOCK_(	"P",						sbgcUCHAR,					3	),  // 0
		PARAMS_BLOCK_(	"I",						sbgcUCHAR,					3	),  // 1
		PARAMS_BLOCK_(	"D",						sbgcUCHAR,					3	),  // 2
		PARAMS_BLOCK_(	"LPF Freq",					sbgcUSHORT,					3	),  // 3
		PARAM_BLOCK_(	"Iteration Cnt",			sbgcUSHORT						),  // 4
		PARAM_BLOCK_(	"Tracking Error [ROLL]",	sbgcFLOAT						),  // 5
		PARAMS_BLOCK_(	"Reserved 1 [ROLL]",		sbgcRCHAR,					6	),  // 6
		PARAM_BLOCK_(	"Tracking Error [PITCH]",	sbgcFLOAT						),  // 7
		PARAMS_BLOCK_(	"Reserved 1 [PITCH]",		sbgcRCHAR,					6	),  // 8
		PARAM_BLOCK_(	"Tracking Error [YAW]",		sbgcFLOAT						),  // 9
		PARAMS_BLOCK_(	"Reserved 1 [YAW]",			sbgcRCHAR,					6	),  // 10
		PARAMS_BLOCK_(	"Reserved 2",				sbgcRCHAR,					10	),  // 11

	};

	const ui8 autoPID_StateReferenceInfoArrayElCnt = countof_(autoPID_StateReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Motors_State
	 *	@{
	 */
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t syncMotorsReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Axis",						sbgcUCHAR						),  // 0
		PARAM_BLOCK_(	"Power",					sbgcUCHAR						),  // 1
		PARAM_BLOCK_(	"Time Ms",					sbgcUSHORT						),  // 2
		PARAM_BLOCK_(	"Angle",					sbgcUSHORT						),  // 3

	};

	const ui8 syncMotorsReferenceInfoArrayElCnt = countof_(syncMotorsReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Scripts
	 *	@{
	 */
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t scriptDebugInfoReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Cur Com Counter",			sbgcUSHORT						),  // 0
		PARAM_BLOCK_(	"Err Core",					sbgcUCHAR						),  // 1

	};

	const ui8 scriptDebugInfoReferenceInfoArrayElCnt = countof_(scriptDebugInfoReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	State_Vars
	 *	@{
	 */
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t stateVarsReferenceInfoArray [] =
	{
		PARAMS_BLOCK_(	"Step Signal Vars",			sbgcUCHAR,					6	),  // 0
		PARAM_BLOCK_(	"Sub Error",				sbgcUCHAR						),  // 1
		PARAM_BLOCK_(	"Max Acc",					sbgcUCHAR						),  // 2
		PARAM_BLOCK_(	"Work Time",				sbgcUINT						),  // 3
		PARAM_BLOCK_(	"Startup Cnt",				sbgcUSHORT						),  // 4
		PARAM_BLOCK_(	"Max Current",				sbgcUSHORT						),  // 5
		PARAM_BLOCK_(	"IMU Temp Main",			sbgcUCHAR						),  // 6
		PARAM_BLOCK_(	"IMU Temp Max",				sbgcUCHAR						),  // 7
		PARAM_BLOCK_(	"MCU Temp Min",				sbgcUCHAR						),  // 8
		PARAM_BLOCK_(	"MCU Temp Max",				sbgcUCHAR						),  // 9
		PARAMS_BLOCK_(	"Shock Cnt",				sbgcUCHAR,					4	),  // 10
		PARAM_BLOCK_(	"Energy Time",				sbgcUINT						),  // 11
		PARAM_BLOCK_(	"Energy",					sbgcFLOAT						),  // 12
		PARAM_BLOCK_(	"Avg Current Time",			sbgcUINT						),  // 13
		PARAM_BLOCK_(	"Avg Current",				sbgcFLOAT						),  // 14
		PARAMS_BLOCK_(	"Reserved",					sbgcRCHAR,					152	),  // 15

	};

	const ui8 stateVarsReferenceInfoArrayElCnt = countof_(stateVarsReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Service_Other
	 *	@{
	 */
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t CAN_DeviceScanReferenceInfoArray [] =
	{
		PARAMS_BLOCK_(	"UID",						sbgcUCHAR,					12	),  // 0
		PARAM_BLOCK_(	"ID",						sbgcUCHAR						),  // 1
		PARAM_BLOCK_(	"Type",						sbgcUCHAR						),  // 2
	};

	const ui8 CAN_DeviceScanReferenceInfoArrayElCnt = countof_(CAN_DeviceScanReferenceInfoArray);

	/**	@}
	 */

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	Board_Info
 *	@{
 */
/**	@brief	Reads version and board information
 *
 *	####	TX —> CMD_BOARD_INFO :	2 bytes
 *	####	RX <— CMD_BOARD_INFO :	18 bytes
 *
 *	@post	Use the @ref DebugSBGC32_PrintWholeStruct
 *			function with PM_BOARD_INFO to print
 *			received data
 *
 *	@code

			sbgcBoardInfo_t BoardInfo;

			SBGC32_ReadBoardInfo(&SBGC32_Device, &BoardInfo, 0);

			#if (SBGC_NEED_DEBUG && SBGC_NEED_REF_INFO)
				DebugSBGC32_PrintWholeStruct(&SBGC32_Device, &BoardInfo, PM_BOARD_INFO);
			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*boardInfo - structure storing board information
 *	@param	cfg - configuration for this serial driver. For UARTs –
 *			period (in ms) between 20-bytes packets for BLE mode.
 *			For USB – not used
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ReadBoardInfo (sbgcGeneral_t *gSBGC, sbgcBoardInfo_t *boardInfo, ui16 cfg
										  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_BOARD_INFO SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeWord(gSBGC, cfg);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_BOARD_INFO SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, NULL, boardInfo, sizeof(sbgcBoardInfo_t));
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Reads additional board information
 *
 *	####	TX —> CMD_BOARD_INFO_3			with no payload
 *	####	RX <— CMD_BOARD_INFO_3 :		69 bytes
 *
 *	@post	Use the @ref DebugSBGC32_PrintWholeStruct
 *			function with PM_BOARD_INFO_3 to print
 *			received data
 *
 *	@note	This function is similar to
 *			@ref SBGC32_ReadBoardInfo. Refer to its
 *			documentation for code example details
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*boardInfo3 - structure storing additional board information
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ReadBoardInfo3 (sbgcGeneral_t *gSBGC, sbgcBoardInfo3_t *boardInfo3
										   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_BOARD_INFO_3 SBGC_ADVANCED_ARGS__);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_BOARD_INFO_3 SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, NULL, boardInfo3, sizeof(sbgcBoardInfo3_t));
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Auto_PID
 *	@{
 */
/**	@brief	Starts automatic PID calibration
 *
 *	####	TX —> CMD_AUTO_PID :	19 bytes
 *	####	RX <— CMD_CONFIRM :		1-6 bytes
 *
 *	@pre	Can start a data stream with current tuned values if
 *			APIDCF_AUTO_PID_CFG_SEND_GUI flag is set.
 *			See @ref SBGC32_ReadAutoPID_StateCmd function
 *
 *	@post	When finished, the controller sends
 *			a full set of tuned parameters:\n
 *			See @ref Profile_Params_Ext,\n
 *			@ref Profile_Params_Ext_2 and\n
 *			@ref Profile_Params_Ext_3 modules
 *
 *	@post	To interrupt currently running auto-tuning process send
 *			this command with zero values in autoPID structure or
 *			use the @ref SBGC32_BreakAutoPID_Tuning function
 *
 *	@attention	Firmware: prior to 2.73
 *
 *	@code

			if (SerialAPI_GetFirmwareVersion(&SBGC32_Device) >= 2730)
				donothing_;  // Use the SBGC32_TuneAutoPID2 function

			#define	SBGC_AUTO_PID_PROFILE 0
			#define	SBGC_AUTO_PID_GAIN_STAB 127
			#define SBGC_AUTO_PID_STATE_READ_TIME 3000

			sbgcAutoPID_t AutoPID = { 0 };
			sbgcAutoPID_State_t AutoPID_State;

			// Tune PIDs in first profile and request debug information
			AutoPID.profileID = SBGC_AUTO_PID_PROFILE;
			AutoPID.cfgFlags = APIDC_FLAG_SEND_GUI | APIDC_FLAG_TUNE_LPF_FREQ;
			AutoPID.Gain_VS_Stability = SBGC_AUTO_PID_GAIN_STAB;

			SBGC32_TuneAutoPID(&SBGC32_Device, &AutoPID, SBGC_NO_CONFIRM);

			// Check the PID tune status
			SBGC32_ReadAutoPID_StateCmd(&SBGC32_Device, &AutoPID_State);
			sbgcDelay(SBGC_AUTO_PID_STATE_READ_TIME);

			// ...

			SBGC32_ReadAutoPID_StateCmd(&SBGC32_Device, &AutoPID_State);
			sbgcDelay(SBGC_AUTO_PID_STATE_READ_TIME);

			// ...
			// And break PID tuning if necessary
			SBGC32_BreakAutoPID_Tuning(&SBGC32_Device, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*autoPID - structure with written auto-PID configurations
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_TuneAutoPID (sbgcGeneral_t *gSBGC, const sbgcAutoPID_t *autoPID, sbgcConfirm_t *confirm
										/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	#if (SBGC_NEED_ASSERTS)

		if (gSBGC->_api->baseFirmwareVersion >= 2730)
		{
			gSBGC->_lastCommandStatus = sbgcCOMMAND_NOT_SUPPORTED_BY_FIRMWARE;
			return sbgcCOMMAND_NOT_SUPPORTED_BY_FIRMWARE;
		}

	#endif

	gSBGC->_api->startWrite(gSBGC, CMD_AUTO_PID SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeBuff(gSBGC, autoPID, sizeof(sbgcAutoPID_t));
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_AUTO_PID SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Interrupts PID tuning
 *
 *	####	TX —> CMD_AUTO_PID :	19 bytes
 *	####	RX <— CMD_CONFIRM :		1-6 bytes
 *
 *	@pre	Applies to the @ref SBGC32_TuneAutoPID function
 *
 *	@note	See @ref SBGC32_TuneAutoPID function
 *			documentation for usage example
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_BreakAutoPID_Tuning (sbgcGeneral_t *gSBGC, sbgcConfirm_t *confirm
												/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAutoPID_t AutoPID = {0};

	gSBGC->_api->startWrite(gSBGC, CMD_AUTO_PID SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeBuff(gSBGC, &AutoPID, sizeof(sbgcAutoPID_t));
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_AUTO_PID SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Starts automatic PID calibration ver. 2
 *
 *	####	TX —> CMD_AUTO_PID2 :	11/73 bytes
 *	####	RX <— CMD_CONFIRM :		1-6 bytes
 *
 *	@pre	If sbgcAutoPID2_t.action field is APID2_ACTION_START or
 *			APID2_ACTION_START or APID2_ACTION_START_SAVE,
 *			the next fields must be set:\n
 *			sbgcAutoPID2_t.cfgVersion \n
 *			sbgcAutoPID2_t.AxisAPID2 \n
 *			sbgcAutoPID2_t.generalFlags \n
 *			sbgcAutoPID2_t.testFreqFrom \n
 *			sbgcAutoPID2_t.testFreqTo
 *
 *	@post	When finished, the controller sends
 *			a full set of tuned parameters:\n
 *			See @ref Profile_Params_Ext,\n
 *			@ref Profile_Params_Ext_2 and\n
 *			@ref Profile_Params_Ext_3 modules
 *
 *	@attention	Firmware: 2.73+
 *
 *	@code

			if (SerialAPI_GetFirmwareVersion(&SBGC32_Device) < 2730)
				donothing_;  // Use the SBGC32_TuneAutoPID function

			#define	SBGC_AUTO_PID_GAIN_STAB 127
			#define SBGC_AUTO_PID_STIM_GAIN 1000
			#define SBGC_AUTO_PID_EFFECTIVE_FREQ 20
			#define SBGC_AUTO_PID_PROBLEM_FREQ 50
			#define SBGC_AUTO_PID_PROBLEM_MARGIN 50
			#define SBGC_AUTO_PID_TEST_FREQ_FROM 10
			#define SBGC_AUTO_PID_TEST_FREQ_TO 150

			sbgcAutoPID2_t AutoPID2 = { 0 };

			// Do demo tune
			AutoPID2.action = APID2_ACTION_START;
			AutoPID2.cfgVersion = 1;

			for (ui8 i = 0; i < 3; i++)
			{
				AutoPID2.AxisAPID2[i].axisFlag = APID2AF_AXIS_IS_ENABLED | APID2AF_TUNE_LPF;

				AutoPID2.AxisAPID2[i].gain = SBGC_AUTO_PID_GAIN_STAB;
				AutoPID2.AxisAPID2[i].stimulusGain = SBGC_AUTO_PID_STIM_GAIN;
				AutoPID2.AxisAPID2[i].effectiveFreq = SBGC_AUTO_PID_EFFECTIVE_FREQ;
				AutoPID2.AxisAPID2[i].problemFreq = SBGC_AUTO_PID_PROBLEM_FREQ;
				AutoPID2.AxisAPID2[i].problemMargin = SBGC_AUTO_PID_PROBLEM_FREQ;
			}

			AutoPID2.generalFlags = APID2GF_START_FROM_CURRENT_VALUES | APID2GF_SAVE_RESULT_TO_ALL_PROFILES;

			AutoPID2.testFreqFrom = SBGC_AUTO_PID_TEST_FREQ_FROM;
			AutoPID2.testFreqTo = SBGC_AUTO_PID_TEST_FREQ_TO;

			SBGC32_TuneAutoPID2(&SBGC32_Device, &AutoPID2, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*autoPID2 - structure with written auto-PID configurations
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_TuneAutoPID2 (sbgcGeneral_t *gSBGC, const sbgcAutoPID2_t *autoPID2, sbgcConfirm_t *confirm
										 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2730)

	gSBGC->_api->startWrite(gSBGC, CMD_AUTO_PID2 SBGC_ADVANCED_ARGS__);

	if ((autoPID2->action == APID2_ACTION_START) || (autoPID2->action == APID2_ACTION_SAVE) ||
		(autoPID2->action == APID2_ACTION_START_SAVE))
		gSBGC->_api->writeBuff(gSBGC, autoPID2, sizeof(sbgcAutoPID2_t));

	else
	{
		gSBGC->_api->writeByte(gSBGC, autoPID2->action);
		gSBGC->_api->writeEmptyBuff(gSBGC, 10);  // reserved[10]
	}

	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_AUTO_PID2 SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Parses progress of PID auto tuning data
 *
 *	####	RX <— CMD_AUTO_PID :	57 bytes
 *
 *	@pre	Use the @ref SBGC32_TuneAutoPID function
 *			to start tuning first
 *
 *	@note	See @ref SBGC32_TuneAutoPID function
 *			documentation for usage example
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*autoPID_State - structure storing progress of PID
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ReadAutoPID_StateCmd (sbgcGeneral_t *gSBGC, sbgcAutoPID_State_t *autoPID_State
												 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	/* It's necessary to lock SerialAPI before Rx operation */
	serialAPI_LockRead()

	gSBGC->_api->startRead(gSBGC, CMD_AUTO_PID SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, NULL, autoPID_State, sizeof(sbgcAutoPID_State_t));
	gSBGC->_api->finishRead(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Motors_State
 *	@{
 */
/**	@brief	Switches motors ON
 *
 *	####	TX —> CMD_MOTORS_ON		with no payload
 *	####	RX <— CMD_CONFIRM :		1-6 bytes
 *
 *	@code

			// Turn on the motors
			SBGC32_SetMotorsON(&SBGC32_Device, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SetMotorsON (sbgcGeneral_t *gSBGC, sbgcConfirm_t *confirm
										/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_MOTORS_ON SBGC_ADVANCED_ARGS__);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_MOTORS_ON SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Switches motors OFF
 *
 *	####	TX —> CMD_MOTORS_OFF :	1 byte (frw. ver. prior to 2.68b7 - with no payload)
 *	####	RX <— CMD_CONFIRM :		1-6 bytes
 *
 *	@attention	Firmware: 2.68b7+ for parameter "mode"
 *
 *	@code

			// Turn off the motors safely
			// The second argument is ignored if the firmware version is below than 2.68b7
			SBGC32_SetMotorsOFF(&SBGC32_Device, MOTOR_MODE_SAFE_STOP, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	mode - possible way for turn off motors
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SetMotorsOFF (sbgcGeneral_t *gSBGC, sbgcMotorsMode_t mode, sbgcConfirm_t *confirm
										 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_MOTORS_OFF SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, mode);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_MOTORS_OFF SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Mechanically aligns motors working
 *			in parallel for a single axis
 *
 *	####	TX —> CMD_SYNC_MOTORS :	6 bytes
 *	####	RX <— CMD_CONFIRM :		1-6 bytes
 *
 *	@attention	Firmware: 2.70b9+
 *
 *	@code

			#define SBGC_SYNC_MOTORS_POWER 50
			#define SBGC_SYNC_MOTORS_TIME 5000

			sbgcSyncMotors_t SyncMotors = { 0 };

			// Synchronize motors by the pitch axis
			SyncMotors.axis = SYNC_MOTOR_AXIS_PITCH;
			SyncMotors.power = SBGC_SYNC_MOTORS_POWER;
			SyncMotors.timeMs = SBGC_SYNC_MOTORS_TIME;

			SBGC32_SynchronizeMotors(&SBGC32_Device, &SyncMotors, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*syncMotors - structure with synchronization parameters
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SynchronizeMotors (sbgcGeneral_t *gSBGC, sbgcSyncMotors_t *syncMotors, sbgcConfirm_t *confirm
											  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2709)

	gSBGC->_api->startWrite(gSBGC, CMD_SYNC_MOTORS SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeBuff(gSBGC, syncMotors, sizeof(sbgcSyncMotors_t));
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_SYNC_MOTORS SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_RequestMotorState function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostRequestMotorState (sbgcGeneral_t *gSBGC)
{
	ui8 bytesSkip = sizeof(ui8) + sizeof(ui32);  // motorID + dataSet

	if (curCmd_->_destinationSize < (curCmd_->_payloadSize - bytesSkip))
		SerialAPI_FatalErrorHandler();

	gSBGC->_api->skipBytes(gSBGC, bytesSkip);
	gSBGC->_api->readBuff(gSBGC, curCmdDest_, curCmd_->_payloadSize - bytesSkip);

	/* A big-endian memory parser will be released in the next versions */
}

/**	@brief	Requests real-time status and current values
 *			of parameters related to motion control
 *
 *	####	TX —> CMD_EXT_MOTORS_STATE :			5 bytes
 *	####	RX <— CMD_EXT_MOTORS_STATE (opt.) :		5 + ? bytes
 *
 *	@pre	Must be set:\n
 *			sbgcExtMotorsStateReference_t.dataSet :
 *				bit0:		sbgcExtMotorsStateReference_t.controlMode					MSDS_CONTROL_MODE								\n
 *				bit1:		sbgcExtMotorsStateReference_t.torque						MSDS_TORQUE										\n
 *				bit2:		sbgcExtMotorsStateReference_t.torqueSetpoint				MSDS_TORQUE_SETPOINT							\n
 *				bit3:		sbgcExtMotorsStateReference_t.speed16						MSDS_SPEED16									\n
 *				bit4:		sbgcExtMotorsStateReference_t.speed16_Setpoint				MSDS_SPEED16									\n
 *				bit5:		sbgcExtMotorsStateReference_t.speed32						MSDS_SPEED32									\n
 *				bit6:		sbgcExtMotorsStateReference_t.speed32_Setpoint				MSDS_SPEED32_SETPOINT							\n
 *				bit7:		sbgcExtMotorsStateReference_t.angle16						MSDS_ANGLE16									\n
 *				bit8:		sbgcExtMotorsStateReference_t.angle16_Setpoint				MSDS_ANGLE16_SETPOINT							\n
 *				bit9:		sbgcExtMotorsStateReference_t.angle32						MSDS_ANGLE32									\n
 *				bit10:		sbgcExtMotorsStateReference_t.angle32_Setpoint				MSDS_ANGLE32_SETPOINT							\n
 *				bit11:		sbgcExtMotorsStateReference_t.stateFlags					MSDS_STATE_FLAGS								\n
 *				bit12:		sbgcExtMotorsStateReference_t.maxSpeed						MSDS_MAX_SPEED									\n
 *				bit13:		sbgcExtMotorsStateReference_t.maxAcceleration				MSDS_MAX_ACCELERATION							\n
 *				bit14:		sbgcExtMotorsStateReference_t.jerkSlope						MSDS_JERK_SLOPE									\n
 *				bit15:		sbgcExtMotorsStateReference_t.maxTorque						MSDS_MAX_TORQUE									\n
 *				bit16:		sbgcExtMotorsStateReference_t.current						MSDS_CURRENT									\n
 *				bit17:		sbgcExtMotorsStateReference_t.batteryVoltage				MSDS_BATTERY_VOLTAGE							\n
 *				bit18:		sbgcExtMotorsStateReference_t.motorTemperature				MSDS_MOTOR_TEMPERATURE							\n
 *				bit19:		sbgcExtMotorsStateReference_t.driverTemperature				MSDS_DRIVER_TEMPERATURE							\n
 *
 *	@post	Use the @ref SBGC32_ReadMotorState function,
 *			if it's necessary to process data from
 *			multiple motors together
 *
 *	@attention	Firmware: 2.73+
 *
 *	@code

			// Example 1

			struct PACKED__ ExtMotorsStateStruct
			{
				// Mandatory field, don't remove!
				ui32 dataSet;

				// Additional fields, depended on 'dataSet'
				ui8 controlMode;
				i16 torque;
				i16 speed16;
				i16 angle16;
				i8 motorTemperature;

			}	ExtMotorsState;

			ExtMotorsState.dataSet = MSDS_CONTROL_MODE | MSDS_TORQUE | MSDS_SPEED16 | MSDS_ANGLE16 | MSDS_MOTOR_TEMPERATURE;

			SBGC32_RequestMotorState(&SBGC32_Device, EXT_MOTOR_ID_1, &ExtMotorsState, sizeof(ExtMotorsState));

			#if (SBGC_NEED_DEBUG)

				DebugSBGC32_PrintStructElement(&SBGC32_Device, &ExtMotorsState.torque, "Motor Torque =", sbgcSHORT);
				DebugSBGC32_PrintStructElement(&SBGC32_Device, &ExtMotorsState.speed16, "Motor Speed16 =", sbgcSHORT);
				DebugSBGC32_PrintStructElement(&SBGC32_Device, &ExtMotorsState.angle16, "Motor Angle16 =", sbgcSHORT);
				DebugSBGC32_PrintStructElement(&SBGC32_Device, &ExtMotorsState.motorTemperature, "Motor Temperature =", sbgcCHAR);

			#endif


			// Example 2

			struct PACKED__ ExtMotorsStateStruct
			{
				// Mandatory field, don't remove!
				ui32 dataSet;

				// Additional fields, depended on 'dataSet'
				ui8 controlMode;
				i16 torque;
				i16 speed16;
				i16 angle16;
				i8 motorTemperature;

			}	ExtMotorsState1, ExtMotorsState2;

			ExtMotorsState1.dataSet = MSDS_CONTROL_MODE | MSDS_TORQUE | MSDS_SPEED16 | MSDS_ANGLE16 | MSDS_MOTOR_TEMPERATURE;
			ExtMotorsState2.dataSet = ExtMotorsState1.dataSet;

			// Request motors state data (no matter what struct use)
			SBGC32_RequestMotorState(&SBGC32_Device, EXT_MOTOR_ID_1 | EXT_MOTOR_ID_2, &ExtMotorsState1, sizeof(ExtMotorsState1));

			// Read motors state data by order
			SBGC32_ReadMotorState(&SBGC32_Device, &ExtMotorsState1, sizeof(ExtMotorsState1));
			SBGC32_ReadMotorState(&SBGC32_Device, &ExtMotorsState2, sizeof(ExtMotorsState2));

			#if (SBGC_NEED_DEBUG)

				DebugSBGC32_PrintStructElement(&SBGC32_Device, &ExtMotorsState1.torque, "Motor 1 Torque =", sbgcSHORT);
				DebugSBGC32_PrintStructElement(&SBGC32_Device, &ExtMotorsState1.motorTemperature, "Motor 1 Temperature =", sbgcCHAR);
				DebugSBGC32_PrintStructElement(&SBGC32_Device, &ExtMotorsState2.torque, "Motor 2 Torque =", sbgcSHORT);
				DebugSBGC32_PrintStructElement(&SBGC32_Device, &ExtMotorsState2.motorTemperature, "Motor 2 Temperature =", sbgcCHAR);

			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	motorID - motor identifier flags
 *	@param	*extMotorsState - structure for storing
 *			any pieces of external motors state data. Using a
 *			big-endian memory organization device
 *			it is necessary to pass the full
 *			sbgcExtMotorsStateReference_t structure
 *	@param	size - data buffer size
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_RequestMotorState (sbgcGeneral_t *gSBGC, sbgcExtMotorID_t motorID, void *extMotorsState, ui16 size
											  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2730)

	ui32 dataSet = *(ui32*)extMotorsState;

	gSBGC->_api->startWrite(gSBGC, CMD_EXT_MOTORS_STATE SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, motorID);
	gSBGC->_api->writeLong(gSBGC, dataSet);
	gSBGC->_api->finishWrite(gSBGC);

	if (!(motorID & (motorID - 1)))
	/* motorID has only one motor */
	{
		gSBGC->_api->startRead(gSBGC, CMD_EXT_MOTORS_STATE SBGC_ADVANCED_ARGS__);
		gSBGC->_api->assignEvent(gSBGC, PostRequestMotorState, extMotorsState, size);
		gSBGC->_api->finishRead(gSBGC);

		gSBGC->_api->link(gSBGC);
	}

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Reads real-time status and current values
 *			of parameters related to motion control
 *
 *	####	RX <— CMD_EXT_MOTORS_STATE (opt.) :		5 + ? bytes
 *
 *	@pre	Use the @ref SBGC32_RequestMotorState function
 *			to request motors state data first
 *
 *	@attention	Firmware: 2.73+
 *
 *	@note	See @ref SBGC32_RequestMotorState function
 *			documentation for usage example
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*data - user-defined receiving data array
 *	@param	size - data buffer size
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ReadMotorState (sbgcGeneral_t *gSBGC, void *data, ui16 size
										   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2730)

	/* It's necessary to lock SerialAPI before Rx operation */
	serialAPI_LockRead()

	gSBGC->_api->startRead(gSBGC, CMD_EXT_MOTORS_STATE SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, PostRequestMotorState, data, size);
	gSBGC->_api->finishRead(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Boot_Mode
 *	@{
 */
/**	@brief	Enters bootloader mode to upload firmware
 *
 *	####	TX —> CMD_BOOT_MODE_3	with no payload
 *
 *	@attention	Don't send any Serial API messages to the port after
 *				this command is issued, as it can confuse the
 *				bootloader and it’s ability to communicate
 *				further using the STM32 boot protocol
 *
 *	@code

			// Enter the controller into bootloader mode
			SBGC32_SetBootMode(&SBGC32_Device);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SetBootMode (sbgcGeneral_t *gSBGC
										/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	return SBGC32_SendEmptyCommand(gSBGC, CMD_BOOT_MODE_3 SBGC_ADVANCED_ARGS__);
}


/**	@brief	Enters bootloader mode to upload firmware
 *			in extended format
 *
 *	####	TX —> CMD_BOOT_MODE_3 :	3 bytes
 *
 *	@post	The confirmation command is processed manually
 *			after controller reset.
 *			Call the @ref SBGC32_CheckConfirmation function
 *			passing it the CMD_BOOT_MODE_3 argument
 *
 *	@attention	Don't send any Serial API messages to the port after
 *				this command is issued, as it can confuse the
 *				bootloader and it’s ability to communicate
 *				further using the STM32 boot protocol
 *
 *	@code

			#define SBGC_SET_BOOT_MODE_RESET_TIME 2000

			// Enter the controller into bootloader mode
			SBGC32_SetBootModeExt(&SBGC32_Device, sbgcTRUE, SBGC_SET_BOOT_MODE_RESET_TIME);

			// ...

			#if (SBGC_NEED_CONFIRM_CMD)
				SBGC32_CheckConfirmation(&SBGC32_Device, SBGC_NO_CONFIRM, CMD_BOOT_MODE_3);
			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	needConfirm - yes/no confirmation after reset
 *	@param	delayMs - waiting for a given time before reset
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SetBootModeExt (sbgcGeneral_t *gSBGC, sbgcBoolean_t needConfirm, ui16 delayMs
										   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_BOOT_MODE_3 SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, needConfirm);
	gSBGC->_api->writeWord(gSBGC, delayMs);
	gSBGC->_api->finishWrite(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Scripts
 *	@{
 */
/**	@brief	Starts or stops user-written script.
 *			Also starts script debug if needed
 *
 *	####	TX —> CMD_RUN_SCRIPT :	34 bytes
 *
 *	@pre	Board requirements:\n
 *			SCRIPTING = (1 << 4)
 *
 *	@post	Use the @ref SBGC32_ReadScriptDebugInfo function
 *			for parse script debug info
 *
 *	@code

			#define SBGC_SCRIPT_EXE_TIME 20000

			sbgcScriptDebugInfo_t ScriptDebugInfo;
			sbgcTicks_t scriptExeTick;

			// Start a script from the first slot with debug
			SBGC32_RunScript(&SBGC32_Device, ScrtM_START_WITH_DEBUG, ScrtSN_SLOT_1);

			scriptExeTick = sbgcGetTick();

			while (sbgcGetTick() < (scriptExeTick + SBGC_SCRIPT_EXE_TIME))
			{
				// Wait until get a full command
				while (SerialAPI_GetBytesAvailable(&SBGC32_Device) < sizeof(sbgcScriptDebugInfo_t));

				SBGC32_ReadScriptDebugInfo(&SBGC32_Device, &ScriptDebugInfo);

				#if (SBGC_NEED_DEBUG)

					// Print script iteration count every second
					DebugSBGC32_PrintStructElement(&SBGC32_Device, &ScriptDebugInfo.curComCounter, "Script Iteration =", sbgcUSHORT);

				#endif
			}

			// Stop the script if it is still running
			SBGC32_RunScript(&SBGC32_Device, ScrtM_STOP, ScrtSN_SLOT_1);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	mode - script's action
 *	@param	slot - script's slot
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_RunScript (sbgcGeneral_t *gSBGC, sbgcScriptMode_t mode, sbgcScriptSlotNum_t slot
									  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFeature(BF_SCRIPTING)

	gSBGC->_api->startWrite(gSBGC, CMD_RUN_SCRIPT SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, mode);
	gSBGC->_api->writeByte(gSBGC, slot);
	gSBGC->_api->writeEmptyBuff(gSBGC, 32);  // reserved[32]
	gSBGC->_api->finishWrite(gSBGC);
	/* No need confirmation */

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_ReadScriptDebugInfo function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostReadScriptDebugInfo (sbgcGeneral_t *gSBGC)
{
	sbgcScriptDebugInfo_t *scriptDebugInfo = (sbgcScriptDebugInfo_t*)curCmdDest_;

    gSBGC->_api->readBuff(gSBGC, scriptDebugInfo, sizeof(sbgcScriptDebugInfo_t));
}

/**	@brief	Parses script debug info
 *
 *	####	RX <— CMD_SCRIPT_DEBUG :		3 bytes
 *
 *	@pre	Call the @ref SBGC32_RunScript function with
 *			ScrtM_START_WITH_DEBUG mode for script debug.
 *			Refer to its documentation for code example details
 *
 *	@pre	Board requirements:\n
 *			SCRIPTING = (1 << 4)
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*scriptDebugInfo - structure storing debug information
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ReadScriptDebugInfo (sbgcGeneral_t *gSBGC, sbgcScriptDebugInfo_t *scriptDebugInfo
												/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFeature(BF_SCRIPTING)

	/* It's necessary to lock SerialAPI before Rx operation */
	serialAPI_LockRead()

	gSBGC->_api->startRead(gSBGC, CMD_SCRIPT_DEBUG SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, PostReadScriptDebugInfo, scriptDebugInfo, sizeof(sbgcScriptDebugInfo_t));
	gSBGC->_api->finishRead(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	State_Vars
 *	@{
 */
/**	@brief	Writes system persistent state variables, cumulative
 *			statistics and maintenance data
 *
 *	####	TX —> CMD_WRITE_STATE_VARS :	192 bytes
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@pre	Use the @ref SBGC32_ReadStateVars function to
 *			obtain this data previously for changing
 *
 *	@pre	Board requirements:\n
 *			STATE_VARS = (1 << 18) (ext.)
 *
 *	@attention	Firmware: 2.68b7+ ("Extended" family only)
 *
 *	@code

			sbgcStateVars_t StateVars;

			SBGC32_ReadStateVars(&SBGC32_Device, &StateVars);

			// Edit required parameters
			// ...

			SBGC32_WriteStateVars(&SBGC32_Device, &StateVars, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*stateVars - structure with written var state parameters
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_WriteStateVars (sbgcGeneral_t *gSBGC, const sbgcStateVars_t *stateVars, sbgcConfirm_t *confirm
										   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertBoardVer(36)
	sbgcAssertFrwVer(2687)
	sbgcAssertFeature(BF_STATE_VARS)

	gSBGC->_api->startWrite(gSBGC, CMD_WRITE_STATE_VARS SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeBuff(gSBGC, stateVars, sizeof(sbgcStateVars_t));
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_WRITE_STATE_VARS SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Requests reading system persistent state variables, cumulative
 *			statistics and maintenance data
 *
 *	####	TX —> CMD_READ_STATE_VARS		with no payload
 *	####	RX <— CMD_READ_STATE_VARS :		192 bytes
 *
 *	@pre	Board requirements:\n
 *			STATE_VARS = (1 << 18) (ext.)
 *
 *	@attention	Firmware: 2.68b7+ ("Extended" family only)
 *
 *	@note	Refer to @ref SBGC32_WriteStateVars function
 *			documentation for code example details
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*stateVars - structure for storing var state parameters
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ReadStateVars (sbgcGeneral_t *gSBGC, sbgcStateVars_t *stateVars
										  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertBoardVer(36)
	sbgcAssertFrwVer(2687)
	sbgcAssertFeature(BF_STATE_VARS)

	gSBGC->_api->startWrite(gSBGC, CMD_READ_STATE_VARS SBGC_ADVANCED_ARGS__);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_READ_STATE_VARS SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, NULL, stateVars, sizeof(sbgcStateVars_t));
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Debug_Port
 *	@{
 */
/**	@brief	Sets this port for debugging
 *
 *	####	TX —> CMD_SET_DEBUG_PORT :		16 bytes
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@pre	Board requirements:\n
 *			PLUS_VER = (1 << 0) (ext.2) when using 'filter'
 *
 *	@code

			sbgcDebugPortData_t DebugPortData;
			ui8 debugPortPayload [SBGC_MAX_PAYLOAD_SIZE];

			DebugPortData.payload = debugPortPayload;

			// Start debugging with filter for CMD_REALTIME_DATA_CUSTOM and CMD_CONTROL commands
			SBGC32_SetDebugPort(&SBGC32_Device, DPA_START_USING_DEBUG_PORT, DPF_CMD_REALTIME_DATA_CUSTOM | DPF_CMD_CONTROL, SBGC_NO_CONFIRM);

			// ...
			// Retrieve the next data from the debug port
			SBGC32_ReadDebugPort(&SBGC32_Device, &DebugPortData);

			// ...
			// Stop debugging
			SBGC32_SetDebugPort(&SBGC32_Device, DPA_STOP_USING_DEBUG_PORT, 0, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	action - stop or start debug
 *	@param	filter - prevent sending heavy-duty
 *			commands to the debug port. See
 *			@ref sbgcDebugPortFilter_t enumeration
 *			(for "plus" version only)
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SetDebugPort (sbgcGeneral_t *gSBGC, sbgcDebugPortAction_t action, ui32 filter, sbgcConfirm_t *confirm
										 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	#if (SBGC_NEED_ASSERTS)

		if (filter)
			sbgcAssertFeature2(BFE2_PLUS_VER)

	#endif

	gSBGC->_api->startWrite(gSBGC, CMD_SET_DEBUG_PORT SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, action);
	gSBGC->_api->writeLong(gSBGC, filter);
	gSBGC->_api->writeEmptyBuff(gSBGC, 11);  // reserved[11]
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_SET_DEBUG_PORT SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_ReadDebugPort function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostReadDebugPort (sbgcGeneral_t *gSBGC)
{
	sbgcDebugPortData_t *debugPortData = (sbgcDebugPortData_t*)curCmdDest_;

	debugPortData->timeMs = gSBGC->_api->readWord(gSBGC);
	debugPortData->portAndDir = gSBGC->_api->readByte(gSBGC);
	debugPortData->cmdID = gSBGC->_api->readByte(gSBGC);

	gSBGC->_api->readBuff(gSBGC, debugPortData->payload, curCmd_->_payloadSize - 4);
}

/**	@brief	Reads debug port data
 *
 *	####	RX <— CMD_SET_DEBUG_PORT :		4 + ? bytes
 *
 *	@pre	Use the @ref SBGC32_SetDebugPort function for
 *			start or stop debugging
 *
 *	@note	See @ref SBGC32_SetDebugPort function
 *			documentation for usage example
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*debugPortSettings - structure to receive port data
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ReadDebugPort (sbgcGeneral_t *gSBGC, sbgcDebugPortData_t *debugPortSettings
										  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	/* It's necessary to lock SerialAPI before Rx operation */
	serialAPI_LockRead()

	gSBGC->_api->startRead(gSBGC, CMD_SET_DEBUG_PORT SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, PostReadDebugPort, debugPortSettings, SBGC_MAX_PAYLOAD_SIZE);
	gSBGC->_api->finishRead(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Transparent_SerialAPI
 *	@{
 */
/**	@brief	Sends data to serial port on
 *			any device via CAN bus
 *
 *	####	TX —> CMD_TRANSPARENT_SAPI :	1 + ? bytes
 *
 *	@attention	Firmware: 2.72b0+ ("Extended" family only)
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*cmd - pointer to prepared serial command
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SendTransparentCommand (sbgcGeneral_t *gSBGC, const sbgcTransparentCommand_t *cmd
												   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertBoardVer(36)
	sbgcAssertFrwVer(2720)
	sbgcAssertParam(cmd->payloadSize, 0, SBGC_MAX_PAYLOAD_SIZE - 1)

	gSBGC->_api->startWrite(gSBGC, CMD_TRANSPARENT_SAPI SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, cmd->target);
	gSBGC->_api->writeBuff(gSBGC, cmd->payload, cmd->payloadSize);
	gSBGC->_api->finishWrite(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_ReadTransparentCommand function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostReadTransparentCommand (sbgcGeneral_t *gSBGC)
{
	sbgcTransparentCommand_t *cmd = (sbgcTransparentCommand_t*)curCmdDest_;

	if (curCmd_->_destinationSize < (curCmd_->_payloadSize - 1))
		SerialAPI_FatalErrorHandler();

	cmd->target = gSBGC->_api->readByte(gSBGC);
	gSBGC->_api->readBuff(gSBGC, cmd->payload, curCmd_->_payloadSize - 1);
}

/**	@brief	Receives data from serial port on
 *			any device via CAN bus
 *
 *	####	RX <— CMD_TRANSPARENT_SAPI :	1 + ? bytes
 *
 *	@pre	sbgcTransparentCommand_t.payloadSize must be filled
 *			to prevent payload buffer overflow when
 *			receiving the serial command
 *
 *	@attention	Firmware: 2.72b0+ ("Extended" family only)
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*cmd - pointer to serial command to store
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ReadTransparentCommand (sbgcGeneral_t *gSBGC, sbgcTransparentCommand_t *cmd
												   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertBoardVer(36)
	sbgcAssertFrwVer(2720)

	/* It's necessary to lock SerialAPI before Rx operation */
	serialAPI_LockRead()

	gSBGC->_api->startRead(gSBGC, CMD_TRANSPARENT_SAPI SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, PostReadTransparentCommand, cmd, cmd->payloadSize);
	gSBGC->_api->finishRead(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Servo_Out
 *	@{
 */
/**	@brief	Sets output PWM signal on the specified pins
 *
 *	####	TX —> CMD_SERVO_OUT :	8 bytes
 *
 *	@note	Although command takes 4 values, the real
 *			number of hardware outputs depends on
 *			board version and may be less
 *
 *	@note	Firmware 2.70b8+: in a special PWM duty cycle output
 *			mode, value 1000  corresponds to 0% duty cycle,
 *			value 2000 to 100% duty cycle
 *
 *	@note	Servo mode is available on the ports:\n
 *			Servo1 - EXT_FC_ROLL\n
 *			Servo2 - EXT_FC_PITCH\n
 * 			Servo3 - RC_PITCH 3\n
 *			Servo4 - AUX1
 *
 *	@code

			i16 servoTime [] = { 10000, SBGC_SERVO_OUT_DISABLED, 1000, SBGC_SERVO_OUT_LIMIT_VALUE };

			SBGC32_SetServoOut(&SBGC32_Device, servoTime);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*servoTime - an array contained @ref SBGC_SERVO_OUTS_NUM
 *			(4) elements with PWM duty cycle values
 *			for each output in microseconds.
 *			Use the @ref SBGC_SERVO_OUT_DISABLED (-1) value to
 *			disable selected output
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SetServoOut (sbgcGeneral_t *gSBGC, const i16 *servoTime
										/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	for (ui8 i = 0; i < SBGC_SERVO_OUTS_NUM; i++)
		sbgcAssertParam(servoTime[i], SBGC_SERVO_OUT_DISABLED, SBGC_SERVO_OUT_LIMIT_VALUE)

	gSBGC->_api->startWrite(gSBGC, CMD_SERVO_OUT SBGC_ADVANCED_ARGS__);
	for (ui8 i = 0; i < SBGC_SERVO_OUTS_NUM; i++) gSBGC->_api->writeWord(gSBGC, servoTime[i]);
	gSBGC->_api->writeEmptyBuff(gSBGC, 8);
	gSBGC->_api->finishWrite(gSBGC);
	/* No need confirmation */

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Sets output PWM signal on the specified
 *			pins in extended format
 *
 *	####	TX —> CMD_SERVO_OUT_EXT :		4 + (2 * nBits) bytes
 *
 *	@attention	Firmware 2.73.2+
 *
 *	@note	Although command takes 4 values, the real
 *			number of hardware outputs depends on
 *			board version and may be less
 *
 *	@note	Even if the actual PWM value for the servo motor is set to
 *			@ref SBGC_SERVO_OUT_MAX_VALUE (2500), the function is not
 *			limited by this value and can output up to a 100% duty
 *			cycle. See @ref SBGC_SERVO_OUT_LIMIT_VALUE (20000)
 *
 *	@code

			i16 servoTime [] = { SBGC_SERVO_OUT_MIN_VALUE, SBGC_SERVO_OUT_MIDDLE_VALUE, SBGC_SERVO_OUT_MAX_VALUE };

			SBGC32_SetServoOutExt(&SBGC32_Device, SOI_PIN_FC_ROLL | SOI_PIN_RC_PITCH | SOI_PIN_AUX_1, servoTime);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	bits - defining the servo output pins for which
 *			this command takes effect. See
 *			@ref sbgcServoOutput_t enumeration
 *	@param	*servoTime - an array contained chosen in the 'bits'
 *			parameter number of elements with PWM duty cycle
 *			values for each output in microseconds.
 *			Use the @ref SBGC_SERVO_OUT_DISABLED (-1) value to
 *			disable selected output
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SetServoOutExt (sbgcGeneral_t *gSBGC, ui32 bits, i16 *servoTime
										   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_SERVO_OUT_EXT SBGC_ADVANCED_ARGS__);

	for (ui8 i = 0; i < 18; i ++)
		if (bits & (1 << i))
			gSBGC->_api->writeWord(gSBGC, *(servoTime++));

	gSBGC->_api->finishWrite(gSBGC);
	/* No need confirmation */

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Service_Other
 *	@{
 */
/**	@brief	Resets the controller
 *
 *	####	TX —> CMD_RESET :		3 bytes
 *
 *	@post	The SBGC32 will send CMD_RESET command
 *			as confirmation if the 'flag' parameter
 *			includes RESET_FLAG_NEED_CONFIRMATION
 *
 *	@code

			#define SBGC_RESET_DELAY 100

			// Restart the controller after 100 ms with confirmation
			SBGC32_Reset(&SBGC32_Device, RESET_FLAG_NEED_CONFIRMATION | RESET_FLAG_RESTORE_STATE, SBGC_RESET_DELAY);

			// Wait the same time for confirmation
			sbgcDelay(SBGC_RESET_DELAY);

			SBGC32_ExpectCommand(&SBGC32_Device, CMD_RESET);

			// Wait a little until the SBGC32 is ready
			sbgcDelay(5000);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	flag - reset action. See @ref sbgcResetFlag_t enumeration
 *	@param	delayMs - waiting for a given time before reset
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_Reset (sbgcGeneral_t *gSBGC, ui8 flag, ui16 delayMs
								  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_RESET SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, flag);
	gSBGC->_api->writeWord(gSBGC, delayMs);
	gSBGC->_api->finishWrite(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Triggers output pin
 *
 *	@note	Pin doesn't must be occupied for other functions
 *			and was really triggered
 *
 *	####	TX —> CMD_TRIGGER_PIN :	2 bytes
 *	####	RX <— CMD_CONFIRM :		1-6 bytes
 *
 *	@code

			// Set RC_ROLL pin to +3.3 V with 40 mA maximal current
			SBGC32_SetTriggerPin(&SBGC32_Device, sbgcPIN_RC_ROLL, sbgcPIN_STATE_HIGH, SBGC_NO_CONFIRM);

			if (SerialAPI_GetFirmwareVersion(&SBGC32_Device) >= 2660)
				// Set AUX1 pin floating
				SBGC32_SetTriggerPin(&SBGC32_Device, sbgcPIN_AUX_1, sbgcPIN_STATE_FLOATING, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	pinID - trigger pin identifier
 *	@param	state - the physical state of the pin
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SetTriggerPin (sbgcGeneral_t *gSBGC, sbgcTriggerPinID_t pinID, sbgcPinState_t state, sbgcConfirm_t *confirm
										  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	#if (SBGC_NEED_ASSERTS)

		if ((gSBGC->_api->baseFirmwareVersion < 2660) && (state == sbgcPIN_STATE_FLOATING))
			return sbgcCOMMAND_NOT_SUPPORTED_BY_FIRMWARE;

	#endif

	gSBGC->_api->startWrite(gSBGC, CMD_TRIGGER_PIN SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, pinID);
	gSBGC->_api->writeByte(gSBGC, state);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_TRIGGER_PIN SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Executes menu command
 *
 *	####	TX —> CMD_EXECUTE_MENU :		1 byte
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@pre	Board requirements:\n
 *			SCRIPTING = (1 << 4) when using MENU_CMD_RUN_SCRIPTx or
 *			MENU_CMD_STOP_SCRIPT \n
 *			MAG_SENSOR = (1 << 6) when using MENU_CMD_CALIB_MAG \n
 *			SHAKE_GENERATOR = (1 << 1) when using MENU_CMD_RETRACTED_POSITION
 *			or MENU_CMD_SHAKE_GENERATOR_OFF or MENU_CMD_SHAKE_GENERATOR_ON
 *
 *	@code

			// Turn on/off the motors
			SBGC32_ExecuteMenu(&SBGC32_Device, MENU_CMD_MOTOR_TOGGLE, SBGC_NO_CONFIRM);

			// Return the gimbal to the home position
			SBGC32_ExecuteMenu(&SBGC32_Device, MENU_CMD_HOME_POSITION, SBGC_NO_CONFIRM);

			// Run third-slot script
			SBGC32_ExecuteMenu(&SBGC32_Device, MENU_CMD_RUN_SCRIPT3, SBGC_NO_CONFIRM);

			// Just ping the controller with confirmation command
			SBGC32_ExecuteMenu(&SBGC32_Device, MENU_CMD_NO, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	menuCmdID - menu command identifier
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ExecuteMenu (sbgcGeneral_t *gSBGC, sbgcMenuCommand_t menuCmdID, sbgcConfirm_t *confirm
										/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertParam(menuCmdID, MENU_CMD_NO, MENU_CMD_SHAKE_GENERATOR_ON)

	#if (SBGC_NEED_ASSERTS)

		if (((menuCmdID >= MENU_CMD_RUN_SCRIPT1) && (menuCmdID <= MENU_CMD_RUN_SCRIPT5)) || (menuCmdID == MENU_CMD_STOP_SCRIPT))
			sbgcAssertFeature(BF_SCRIPTING)

		if (menuCmdID == MENU_CMD_CALIB_MAG)
			sbgcAssertFeature(BF_MAG_SENSOR)

		if ((menuCmdID >= MENU_CMD_RETRACTED_POSITION) && (menuCmdID <= MENU_CMD_SHAKE_GENERATOR_ON))
			sbgcAssertFeature2(BFE2_SHAKE_GENERATOR)

	#endif

	gSBGC->_api->startWrite(gSBGC, CMD_EXECUTE_MENU SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, menuCmdID);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_EXECUTE_MENU SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


#if (SBGC_NEED_CONFIRM_CMD)

	/**	@brief	Executes menu command with optional flags
	 *
	 *	####	TX —> CMD_EXECUTE_MENU :		2 bytes
	 *	####	RX <— CMD_CONFIRM (opt.) :		1-6 bytes
	 *
	 *	@pre	Board requirements:\n
	 *			SCRIPTING = (1 << 4) when using MENU_CMD_RUN_SCRIPTx or
	 *			MENU_CMD_STOP_SCRIPT \n
	 *			MAG_SENSOR = (1 << 6) when using MENU_CMD_CALIB_MAG \n
	 *			SHAKE_GENERATOR = (1 << 1) when using MENU_CMD_RETRACTED_POSITION
	 *			or MENU_CMD_SHAKE_GENERATOR_OFF or MENU_CMD_SHAKE_GENERATOR_ON
	 *
	 *	@code

				// Turn on/off the motors without confirmation
				SBGC32_ExecuteMenuExt(&SBGC32_Device, MENU_CMD_MOTOR_TOGGLE, MC_FLAG_NO, SBGC_NO_CONFIRM);

				// Return the gimbal to the home position, get confirm on a finish
				SBGC32_ExecuteMenuExt(&SBGC32_Device, MENU_CMD_HOME_POSITION, MC_FLAG_CONFIRM_ON_FINISH, SBGC_NO_CONFIRM);

				// Run third-slot script, get confirm on a start and wait for a finish
				SBGC32_ExecuteMenuExt(&SBGC32_Device, MENU_CMD_RUN_SCRIPT3, MC_FLAG_CONFIRM | MC_FLAG_CONFIRM_ON_FINISH, SBGC_NO_CONFIRM);
				SBGC32_CheckConfirmation(&SBGC32_Device, SBGC_NO_CONFIRM, CMD_EXECUTE_MENU);

				// Just ping the controller with confirmation command
				SBGC32_ExecuteMenuExt(&SBGC32_Device, MENU_CMD_NO, MC_FLAG_CONFIRM, SBGC_NO_CONFIRM);

	 *	@endcode
	 *
	 *	@param	*gSBGC - serial connection descriptor
	 *	@param	menuCmdID - menu command identifier
	 *	@param	flags - optional parameter
	 *	@param	*confirm - confirmation result storage structure
	 *
	 *	@return	Communication status. See @ref Readme_S2
	 */
	sbgcCommandStatus_t SBGC32_ExecuteMenuExt (sbgcGeneral_t *gSBGC, sbgcMenuCommand_t menuCmdID, sbgcMenuCmdFlag_t flags, sbgcConfirm_t *confirm
											   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
	{
		sbgcAssertParam(menuCmdID, MENU_CMD_NO, MENU_CMD_SERVO_MODE_TOGGLE)

		#if (SBGC_NEED_ASSERTS)

			if (((menuCmdID >= MENU_CMD_RUN_SCRIPT1) && (menuCmdID <= MENU_CMD_RUN_SCRIPT5)) || (menuCmdID == MENU_CMD_STOP_SCRIPT))
				sbgcAssertFeature(BF_SCRIPTING)

			if (menuCmdID == MENU_CMD_CALIB_MAG)
				sbgcAssertFeature(BF_MAG_SENSOR)

			if ((menuCmdID >= MENU_CMD_RETRACTED_POSITION) && (menuCmdID <= MENU_CMD_SHAKE_GENERATOR_ON))
				sbgcAssertFeature2(BFE2_SHAKE_GENERATOR)

		#endif

		gSBGC->_api->startWrite(gSBGC, CMD_EXECUTE_MENU SBGC_ADVANCED_ARGS__);
		gSBGC->_api->writeByte(gSBGC, menuCmdID);
		gSBGC->_api->finishWrite(gSBGC);

		if ((flags & MC_FLAG_CONFIRM) | (flags & MC_FLAG_CONFIRM_ON_FINISH))
		{
			gSBGC->_api->addConfirm(gSBGC, confirm, CMD_EXECUTE_MENU SBGC_ADVANCED_ARGS__);

			gSBGC->_api->link(gSBGC);
		}

		serialAPI_GiveToken()

		return gSBGC->_api->exit(gSBGC);
	}

#endif


/**	@brief	Plays melody by motors or emit standard beep sound
 *
 *	####	TX —> CMD_BEEP_SOUND :	12 + ? bytes
 *
 *	@code

			sbgcBeeperSettings_t BeeperSettings = { 0 };

			// Play the confirmation sound
			BeeperSettings.mode = BEEP_MODE_CONFIRM;

			SBGC32_PlayBeeper(&SBGC32_Device, &BeeperSettings);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*beeperSettings - structure with prescribed
 *			beeper playback settings
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_PlayBeeper (sbgcGeneral_t *gSBGC, const sbgcBeeperSettings_t *beeperSettings
									   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_BEEP_SOUND SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeWord(gSBGC, beeperSettings->mode);
	gSBGC->_api->writeByte(gSBGC, beeperSettings->noteLength);
	gSBGC->_api->writeByte(gSBGC, beeperSettings->decayFactor);
	gSBGC->_api->writeEmptyBuff(gSBGC, 8);  // reserved[8]

	if (beeperSettings->mode == BEEP_MODE_CUSTOM_MELODY)
		for (ui8 i = 0; i < beeperSettings->notesQuan; i++)
			gSBGC->_api->writeWord(gSBGC, beeperSettings->notesFreqHz[i]);

	gSBGC->_api->finishWrite(gSBGC);
	/* No need confirmation */

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Signs the user message
 *
 *	####	TX —> CMD_SIGN_MESSAGE :		33 bytes
 *	####	RX <— CMD_SIGN_MESSAGE :		32 bytes
 *
 *	@note	size of txMessage[] and rxMessage[] must be ==
 *			@ref SBGC_MAX_MESSAGE_LENGTH bytes (32)
 *
 *	@code

			#define SBGC_SIGN_MESSAGE_TYPE 1

			char txMessage [SBGC_MAX_MESSAGE_LENGTH] = { 0 };
			char rxMessage [SBGC_MAX_MESSAGE_LENGTH] = { 0 };

			memcpy(txMessage, TEXT_LENGTH_("The message to sign"));

			SBGC32_SignMessage(&SBGC32_Device, SBGC_SIGN_MESSAGE_TYPE, txMessage, rxMessage);

			#if (SBGC_NEED_DEBUG)
				DebugSBGC32_PrintBuffer(&SBGC32_Device, rxMessage, SBGC_MAX_MESSAGE_LENGTH);
			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	signType - set of keys to be used
 *	@param	*txMessage - the user's input message
 *	@param	*rxMessage - signed message
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SignMessage (sbgcGeneral_t *gSBGC, ui8 signType, const char *txMessage, char *rxMessage
										/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_SIGN_MESSAGE SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, signType);
	gSBGC->_api->writeBuff(gSBGC, txMessage, SBGC_MAX_MESSAGE_LENGTH);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_SIGN_MESSAGE SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, NULL, rxMessage, SBGC_MAX_MESSAGE_LENGTH);
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Scans CAN bus devices
 *
 *	####	TX —> CMD_CAN_DEVICE_SCAN		with no payload
 *	####	RX <— CMD_CAN_DEVICE_SCAN :		14 bytes
 *
 *	@pre	Board requirements:\n
 *			CAN_PORT = (1 << 10)
 *
 *	@post	Use the @ref DebugSBGC32_PrintWholeStruct
 *			function with PM_CAN_DEVICE_SCAN to print
 *			received data
 *
 *	@code

			sbgcCAN_DeviceScan_t CAN_DeviceScan;

			SBGC32_CAN_DeviceScan(&SBGC32_Device, &CAN_DeviceScan);

			#if (SBGC_NEED_DEBUG && SBGC_NEED_REF_INFO)
				DebugSBGC32_PrintWholeStruct(&SBGC32_Device, &CAN_DeviceScan, PM_CAN_DEVICE_SCAN);
			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*CAN_DeviceScan - structure to save scanning results
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_CAN_DeviceScan (sbgcGeneral_t *gSBGC, sbgcCAN_DeviceScan_t *CAN_DeviceScan
										   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFeature(BF_CAN_PORT)

	gSBGC->_api->startWrite(gSBGC, CMD_CAN_DEVICE_SCAN SBGC_ADVANCED_ARGS__);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_CAN_DEVICE_SCAN SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, NULL, CAN_DeviceScan, sizeof(sbgcCAN_DeviceScan_t));
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_RequestModuleList function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostRequestModuleList (sbgcGeneral_t *gSBGC)
{
	if (curCmd_->_destinationSize < (curCmd_->_payloadSize - 1))
		SerialAPI_FatalErrorHandler();

	gSBGC->_api->skipBytes(gSBGC, 1);
	gSBGC->_api->readBuff(gSBGC, curCmdDest_, curCmd_->_payloadSize - 1);

	ui8 freeSpaceSize = curCmd_->_destinationSize - (curCmd_->_payloadSize - 1);

	if (freeSpaceSize)
	/* Fill the remaining space with zeros */
		memset(((ui8*)curCmd_->_pDestination) + (curCmd_->_payloadSize - 1), 0, freeSpaceSize);
}


/**	@brief	Requests version information for connected CAN devices
 *
 *	####	TX —> CMD_MODULE_LIST	with no payload
 *	####	RX <— CMD_MODULE_LIST :	1 + (13 * ?) bytes
 *
 *	@pre	Board requirements:\n
 *			CAN_PORT = (1 << 10)
 *
 *	@post	The number of structures can be allocated with a margin.
 *			Any extra space will be filled with zeros. This way,
 *			it will be possible to determine the actual number
 *			of devices on the CAN bus line
 *
 *	@code

			#define CAN_DEVICE_NUM 4

			sbgcCAN_ModuleInfo_t CAN_ModuleInfo [CAN_DEVICE_NUM];

			SBGC32_RequestModuleList(&SBGC32_Device, CAN_ModuleInfo, CAN_DEVICE_NUM, SBGC_DEFAULT_ARGS_);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*CAN_ModuleInfo - structure to save device information
 *	@param	deviceNumMax - size of CAN_ModuleInfo buffer.
 *			Maximum number of structures to fill
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_RequestModuleList (sbgcGeneral_t *gSBGC, sbgcCAN_ModuleInfo_t *CAN_ModuleInfo, ui8 deviceNumMax
											  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFeature(BF_CAN_PORT)

	gSBGC->_api->startWrite(gSBGC, CMD_MODULE_LIST SBGC_ADVANCED_ARGS__);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_MODULE_LIST SBGC_ADVANCED_ARGS__);
	/* Ignore Rx 'deviceNum' variable */
	gSBGC->_api->assignEvent(gSBGC, PostRequestModuleList, CAN_ModuleInfo, sizeof(sbgcCAN_ModuleInfo_t) * deviceNumMax);
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */

#endif /* SBGC_SERVICE_MODULE */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
