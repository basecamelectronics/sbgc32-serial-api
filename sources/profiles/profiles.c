/** ____________________________________________________________________
 *
 *	@file		profiles.c
 *
 *	@brief 		Profiles source file
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

#include "profiles.h"


#ifdef	SYS_BIG_ENDIAN

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *								Parser Big Endian Mapping Structures
	 */
	/**	@addtogroup	Profile_Params_3
	 * 	@{
	 */
	/** @brief	Sample for Big Endian Mapping
	 *
	 * 	@ref	MainParams3_ParserStructDB
	 */
	const MainParams3_t mainParams3_ParserStruct;

	const ParserBlock_t MainParams3_ParserStructDB [] =
	{
		VAR_BLOCK(mainParams3_ParserStruct.profileID),
		VAR_BLOCK(mainParams3_ParserStruct.AxisCMP3[ROLL].p),
		VAR_BLOCK(mainParams3_ParserStruct.AxisCMP3[ROLL].i),
		VAR_BLOCK(mainParams3_ParserStruct.AxisCMP3[ROLL].d),
		VAR_BLOCK(mainParams3_ParserStruct.AxisCMP3[ROLL].power),
		VAR_BLOCK(mainParams3_ParserStruct.AxisCMP3[ROLL].invert),
		VAR_BLOCK(mainParams3_ParserStruct.AxisCMP3[ROLL].poles),
		VAR_BLOCK(mainParams3_ParserStruct.AxisCMP3[PITCH].p),
		VAR_BLOCK(mainParams3_ParserStruct.AxisCMP3[PITCH].i),
		VAR_BLOCK(mainParams3_ParserStruct.AxisCMP3[PITCH].d),
		VAR_BLOCK(mainParams3_ParserStruct.AxisCMP3[PITCH].power),
		VAR_BLOCK(mainParams3_ParserStruct.AxisCMP3[PITCH].invert),
		VAR_BLOCK(mainParams3_ParserStruct.AxisCMP3[PITCH].poles),
		VAR_BLOCK(mainParams3_ParserStruct.AxisCMP3[YAW].p),
		VAR_BLOCK(mainParams3_ParserStruct.AxisCMP3[YAW].i),
		VAR_BLOCK(mainParams3_ParserStruct.AxisCMP3[YAW].d),
		VAR_BLOCK(mainParams3_ParserStruct.AxisCMP3[YAW].power),
		VAR_BLOCK(mainParams3_ParserStruct.AxisCMP3[YAW].invert),
		VAR_BLOCK(mainParams3_ParserStruct.AxisCMP3[YAW].poles),
		VAR_BLOCK(mainParams3_ParserStruct.ACC_LimiterAll),
		DATA_BLOCK(mainParams3_ParserStruct.ExtFC_Gain),
		VAR_BLOCK(mainParams3_ParserStruct.AxisRC_MP3[ROLL].RC_MinAngle),
		VAR_BLOCK(mainParams3_ParserStruct.AxisRC_MP3[ROLL].RC_MaxAngle),
		VAR_BLOCK(mainParams3_ParserStruct.AxisRC_MP3[ROLL].RC_Mode),
		VAR_BLOCK(mainParams3_ParserStruct.AxisRC_MP3[ROLL].RC_LPF),
		VAR_BLOCK(mainParams3_ParserStruct.AxisRC_MP3[ROLL].RC_Speed),
		VAR_BLOCK(mainParams3_ParserStruct.AxisRC_MP3[ROLL].RC_Follow),
		VAR_BLOCK(mainParams3_ParserStruct.AxisRC_MP3[PITCH].RC_MinAngle),
		VAR_BLOCK(mainParams3_ParserStruct.AxisRC_MP3[PITCH].RC_MaxAngle),
		VAR_BLOCK(mainParams3_ParserStruct.AxisRC_MP3[PITCH].RC_Mode),
		VAR_BLOCK(mainParams3_ParserStruct.AxisRC_MP3[PITCH].RC_LPF),
		VAR_BLOCK(mainParams3_ParserStruct.AxisRC_MP3[PITCH].RC_Speed),
		VAR_BLOCK(mainParams3_ParserStruct.AxisRC_MP3[PITCH].RC_Follow),
		VAR_BLOCK(mainParams3_ParserStruct.AxisRC_MP3[YAW].RC_MinAngle),
		VAR_BLOCK(mainParams3_ParserStruct.AxisRC_MP3[YAW].RC_MaxAngle),
		VAR_BLOCK(mainParams3_ParserStruct.AxisRC_MP3[YAW].RC_Mode),
		VAR_BLOCK(mainParams3_ParserStruct.AxisRC_MP3[YAW].RC_LPF),
		VAR_BLOCK(mainParams3_ParserStruct.AxisRC_MP3[YAW].RC_Speed),
		VAR_BLOCK(mainParams3_ParserStruct.AxisRC_MP3[YAW].RC_Follow),
		VAR_BLOCK(mainParams3_ParserStruct.gyroTrust),
		VAR_BLOCK(mainParams3_ParserStruct.useModel),
		VAR_BLOCK(mainParams3_ParserStruct.PWM_Freq),
		VAR_BLOCK(mainParams3_ParserStruct.serialSpeed),
		DATA_BLOCK(mainParams3_ParserStruct.RC_Trim),
		VAR_BLOCK(mainParams3_ParserStruct.RC_DeadBand),
		VAR_BLOCK(mainParams3_ParserStruct.RC_ExpoRate),
		VAR_BLOCK(mainParams3_ParserStruct.RC_VirtMode),
		VAR_BLOCK(mainParams3_ParserStruct.RC_MapROLL),
		VAR_BLOCK(mainParams3_ParserStruct.RC_MapPITCH),
		VAR_BLOCK(mainParams3_ParserStruct.RC_MapYAW),
		VAR_BLOCK(mainParams3_ParserStruct.RC_MapCmd),
		VAR_BLOCK(mainParams3_ParserStruct.RC_MapFC_ROLL),
		VAR_BLOCK(mainParams3_ParserStruct.RC_MapFC_PITCH),
		VAR_BLOCK(mainParams3_ParserStruct.RC_MixFC_ROLL),
		VAR_BLOCK(mainParams3_ParserStruct.RC_MixFC_PITCH),
		VAR_BLOCK(mainParams3_ParserStruct.followMode),
		VAR_BLOCK(mainParams3_ParserStruct.followDeadBand),
		VAR_BLOCK(mainParams3_ParserStruct.followExpoRate),
		DATA_BLOCK(mainParams3_ParserStruct.followOffset),
		VAR_BLOCK(mainParams3_ParserStruct.axisTop),
		VAR_BLOCK(mainParams3_ParserStruct.axisRight),
		VAR_BLOCK(mainParams3_ParserStruct.frameAxisTop),
		VAR_BLOCK(mainParams3_ParserStruct.frameAxisRight),
		VAR_BLOCK(mainParams3_ParserStruct.frameIMU_Pos),
		VAR_BLOCK(mainParams3_ParserStruct.gyroDeadBand),
		VAR_BLOCK(mainParams3_ParserStruct.gyroSens),
		VAR_BLOCK(mainParams3_ParserStruct.I2C_SpeedFast),
		VAR_BLOCK(mainParams3_ParserStruct.skipGyroCalib),
		VAR_BLOCK(mainParams3_ParserStruct.RC_Cmd_Low),
		VAR_BLOCK(mainParams3_ParserStruct.RC_Cmd_Mid),
		VAR_BLOCK(mainParams3_ParserStruct.RC_Cmd_High),
		VAR_BLOCK(mainParams3_ParserStruct.MenuBtnCmd1),
		VAR_BLOCK(mainParams3_ParserStruct.MenuBtnCmd2),
		VAR_BLOCK(mainParams3_ParserStruct.MenuBtnCmd3),
		VAR_BLOCK(mainParams3_ParserStruct.MenuBtnCmd4),
		VAR_BLOCK(mainParams3_ParserStruct.MenuBtnCmd5),
		VAR_BLOCK(mainParams3_ParserStruct.MenuBtnCmdLong),
		DATA_BLOCK(mainParams3_ParserStruct.motorOutput),
		VAR_BLOCK(mainParams3_ParserStruct.batThresholdAlarm),
		VAR_BLOCK(mainParams3_ParserStruct.batThresholdMotors),
		VAR_BLOCK(mainParams3_ParserStruct.batCompRef),
		VAR_BLOCK(mainParams3_ParserStruct.beeperModes),
		VAR_BLOCK(mainParams3_ParserStruct.followROLL_MixStart),
		VAR_BLOCK(mainParams3_ParserStruct.followROLL_MixRange),
		DATA_BLOCK(mainParams3_ParserStruct.boosterPower),
		DATA_BLOCK(mainParams3_ParserStruct.followSpeed),
		VAR_BLOCK(mainParams3_ParserStruct.frameAngleFromMotors),
		DATA_BLOCK(mainParams3_ParserStruct.RC_Memory),
		VAR_BLOCK(mainParams3_ParserStruct.servo1_Out),
		VAR_BLOCK(mainParams3_ParserStruct.servo2_Out),
		VAR_BLOCK(mainParams3_ParserStruct.servo3_Out),
		VAR_BLOCK(mainParams3_ParserStruct.servo4_Out),
		VAR_BLOCK(mainParams3_ParserStruct.servoRate),
		VAR_BLOCK(mainParams3_ParserStruct.adaptivePID_Enabled),
		VAR_BLOCK(mainParams3_ParserStruct.adaptivePID_Treshold),
		VAR_BLOCK(mainParams3_ParserStruct.adaptivePID_Rate),
		VAR_BLOCK(mainParams3_ParserStruct.adaptivePID_RecoveryFactor),
		DATA_BLOCK(mainParams3_ParserStruct.followLPF),
		VAR_BLOCK(mainParams3_ParserStruct.generalFlags1),
		VAR_BLOCK(mainParams3_ParserStruct.profileFlags1),
		VAR_BLOCK(mainParams3_ParserStruct.spektrumMode),
		VAR_BLOCK(mainParams3_ParserStruct.orderOfAxes),
		VAR_BLOCK(mainParams3_ParserStruct.EulerOrder),
		VAR_BLOCK(mainParams3_ParserStruct.curIMU),
		VAR_BLOCK(mainParams3_ParserStruct.curProfileID),
	};

	const ui8 MainParams3_ParserStructDB_Size = countof(MainParams3_ParserStructDB);
	/**	@}
	 */


	/**	@addtogroup	Profile_Params_Ext
	 * 	@{
	 */
	/** @brief	Sample for Big Endian Mapping
	 *
	 * 	@ref	MainParamsExt_ParserStructDB
	 */
	const MainParamsExt_t mainParamsExt_ParserStruct;

	const ParserBlock_t MainParamsExt_ParserStructDB [] =
	{
		VAR_BLOCK(mainParamsExt_ParserStruct.profileID),
		VAR_BLOCK(mainParamsExt_ParserStruct.AxisMPE[ROLL].notchFreq),
		VAR_BLOCK(mainParamsExt_ParserStruct.AxisMPE[ROLL].notchWidth),
		VAR_BLOCK(mainParamsExt_ParserStruct.AxisMPE[PITCH].notchFreq),
		VAR_BLOCK(mainParamsExt_ParserStruct.AxisMPE[PITCH].notchWidth),
		VAR_BLOCK(mainParamsExt_ParserStruct.AxisMPE[YAW].notchFreq),
		VAR_BLOCK(mainParamsExt_ParserStruct.AxisMPE[YAW].notchWidth),
		DATA_BLOCK(mainParamsExt_ParserStruct.LPF_Freq),
		DATA_BLOCK(mainParamsExt_ParserStruct.filtersEn),
		DATA_BLOCK(mainParamsExt_ParserStruct.encoderOffset),
		DATA_BLOCK(mainParamsExt_ParserStruct.encoderFLD_Offset),
		DATA_BLOCK(mainParamsExt_ParserStruct.encoderManualSetTime),
		DATA_BLOCK(mainParamsExt_ParserStruct.motorHeatingFactor),
		DATA_BLOCK(mainParamsExt_ParserStruct.motorCoolingFactor),
		DATA_BLOCK(mainParamsExt_ParserStruct.reserved),
		VAR_BLOCK(mainParamsExt_ParserStruct.followInsideDeadBand),
		DATA_BLOCK(mainParamsExt_ParserStruct.motorMagLink),
		DATA_BLOCK(mainParamsExt_ParserStruct.motorGearing),
		DATA_BLOCK(mainParamsExt_ParserStruct.encoderLimitMin),
		DATA_BLOCK(mainParamsExt_ParserStruct.encoderLimitMax),
		DATA_BLOCK(mainParamsExt_ParserStruct.notch1_Gain),
		DATA_BLOCK(mainParamsExt_ParserStruct.notch2_Gain),
		DATA_BLOCK(mainParamsExt_ParserStruct.notch3_Gain),
		DATA_BLOCK(mainParamsExt_ParserStruct.encoderGearRatio),
		DATA_BLOCK(mainParamsExt_ParserStruct.encoderType),
		DATA_BLOCK(mainParamsExt_ParserStruct.encoderCfg),
		DATA_BLOCK(mainParamsExt_ParserStruct.outerP),
		DATA_BLOCK(mainParamsExt_ParserStruct.outerI),
		VAR_BLOCK(mainParamsExt_ParserStruct.beeperVolume),
		VAR_BLOCK(mainParamsExt_ParserStruct.magAxisTop),
		VAR_BLOCK(mainParamsExt_ParserStruct.magAxisRight),
		VAR_BLOCK(mainParamsExt_ParserStruct.magTrust),
		VAR_BLOCK(mainParamsExt_ParserStruct.magDeclination),
		VAR_BLOCK(mainParamsExt_ParserStruct.ACC_LPF_Freq),
		DATA_BLOCK(mainParamsExt_ParserStruct.D_TermLPF_Freq),
	};

	const ui8 MainParamsExt_ParserStructDB_Size = countof(MainParamsExt_ParserStructDB);
	/**	@}
	 */


	/**	@addtogroup	Profile_Params_Ext_2
	 * 	@{
	 */
	/** @brief	Sample for Big Endian Mapping
	 *
	 * 	@ref	MainParamsExt2_ParserStructDB
	 */
	const MainParamsExt2_t mainParamsExt2_ParserStruct;

	const ParserBlock_t MainParamsExt2_ParserStructDB [] =
	{
		VAR_BLOCK(mainParamsExt2_ParserStruct.profileID),
		VAR_BLOCK(mainParamsExt2_ParserStruct.MAV_CMPE_Channel[0].MAV_Src),
		VAR_BLOCK(mainParamsExt2_ParserStruct.MAV_CMPE_Channel[0].MAV_SysID),
		VAR_BLOCK(mainParamsExt2_ParserStruct.MAV_CMPE_Channel[0].MAV_CompID),
		VAR_BLOCK(mainParamsExt2_ParserStruct.MAV_CMPE_Channel[0].MAV_CfgFlags),
		VAR_BLOCK(mainParamsExt2_ParserStruct.MAV_CMPE_Channel[0].MAV_Reserved),
		VAR_BLOCK(mainParamsExt2_ParserStruct.MAV_CMPE_Channel[1].MAV_Src),
		VAR_BLOCK(mainParamsExt2_ParserStruct.MAV_CMPE_Channel[1].MAV_SysID),
		VAR_BLOCK(mainParamsExt2_ParserStruct.MAV_CMPE_Channel[1].MAV_CompID),
		VAR_BLOCK(mainParamsExt2_ParserStruct.MAV_CMPE_Channel[1].MAV_CfgFlags),
		VAR_BLOCK(mainParamsExt2_ParserStruct.MAV_CMPE_Channel[1].MAV_Reserved),
		DATA_BLOCK(mainParamsExt2_ParserStruct.motorMagLinkFine),
		DATA_BLOCK(mainParamsExt2_ParserStruct.ACC_Limiter),
		DATA_BLOCK(mainParamsExt2_ParserStruct.PID_Gain),
		VAR_BLOCK(mainParamsExt2_ParserStruct.frameIMU_LPF_Freq),
		VAR_BLOCK(mainParamsExt2_ParserStruct.autoPID_Cfg),
		VAR_BLOCK(mainParamsExt2_ParserStruct.autoPID_Gain),
		DATA_BLOCK(mainParamsExt2_ParserStruct.frameCamAngleMax),
		VAR_BLOCK(mainParamsExt2_ParserStruct.generalFlags2),
		VAR_BLOCK(mainParamsExt2_ParserStruct.autoSpeed),
		VAR_BLOCK(mainParamsExt2_ParserStruct.autoACC_Limiter),
		DATA_BLOCK(mainParamsExt2_ParserStruct.IMU_OrientationCorr),
		VAR_BLOCK(mainParamsExt2_ParserStruct.timelapseTime),
		VAR_BLOCK(mainParamsExt2_ParserStruct.emergencyStopRestartDelay),
		VAR_BLOCK(mainParamsExt2_ParserStruct.timelapseACC_Part),
		DATA_BLOCK(mainParamsExt2_ParserStruct.momentum),
		DATA_BLOCK(mainParamsExt2_ParserStruct.momentumCalibStimulus),
		DATA_BLOCK(mainParamsExt2_ParserStruct.momentumElitpicity),
		DATA_BLOCK(mainParamsExt2_ParserStruct.followRange),
		DATA_BLOCK(mainParamsExt2_ParserStruct.stabAxis),
		VAR_BLOCK(mainParamsExt2_ParserStruct.outerMotTiltAngle),
		DATA_BLOCK(mainParamsExt2_ParserStruct.startupAction),
		DATA_BLOCK(mainParamsExt2_ParserStruct.startupActionSrc),
		DATA_BLOCK(mainParamsExt2_ParserStruct.startupActionThreshold),
		DATA_BLOCK(mainParamsExt2_ParserStruct.forcePositionCfg),
		VAR_BLOCK(mainParamsExt2_ParserStruct.StepSignalN[0].stepSignalSrc),
		VAR_BLOCK(mainParamsExt2_ParserStruct.StepSignalN[0].stepSignalCfg),
		VAR_BLOCK(mainParamsExt2_ParserStruct.StepSignalN[1].stepSignalSrc),
		VAR_BLOCK(mainParamsExt2_ParserStruct.StepSignalN[1].stepSignalCfg),
		VAR_BLOCK(mainParamsExt2_ParserStruct.StepSignalN[2].stepSignalSrc),
		VAR_BLOCK(mainParamsExt2_ParserStruct.StepSignalN[2].stepSignalCfg),
		VAR_BLOCK(mainParamsExt2_ParserStruct.StepSignalN[3].stepSignalSrc),
		VAR_BLOCK(mainParamsExt2_ParserStruct.StepSignalN[3].stepSignalCfg),
		VAR_BLOCK(mainParamsExt2_ParserStruct.StepSignalN[4].stepSignalSrc),
		VAR_BLOCK(mainParamsExt2_ParserStruct.StepSignalN[4].stepSignalCfg),
		VAR_BLOCK(mainParamsExt2_ParserStruct.StepSignalN[5].stepSignalSrc),
		VAR_BLOCK(mainParamsExt2_ParserStruct.StepSignalN[5].stepSignalCfg),
		VAR_BLOCK(mainParamsExt2_ParserStruct.RC_CalibN[0].RC_CalibSrc),
		VAR_BLOCK(mainParamsExt2_ParserStruct.RC_CalibN[0].RC_CalibOffset),
		VAR_BLOCK(mainParamsExt2_ParserStruct.RC_CalibN[0].RC_CalibNegScale),
		VAR_BLOCK(mainParamsExt2_ParserStruct.RC_CalibN[0].RC_CalibPosScale),
		VAR_BLOCK(mainParamsExt2_ParserStruct.RC_CalibN[1].RC_CalibSrc),
		VAR_BLOCK(mainParamsExt2_ParserStruct.RC_CalibN[1].RC_CalibOffset),
		VAR_BLOCK(mainParamsExt2_ParserStruct.RC_CalibN[1].RC_CalibNegScale),
		VAR_BLOCK(mainParamsExt2_ParserStruct.RC_CalibN[1].RC_CalibPosScale),
		VAR_BLOCK(mainParamsExt2_ParserStruct.RC_CalibN[2].RC_CalibSrc),
		VAR_BLOCK(mainParamsExt2_ParserStruct.RC_CalibN[2].RC_CalibOffset),
		VAR_BLOCK(mainParamsExt2_ParserStruct.RC_CalibN[2].RC_CalibNegScale),
		VAR_BLOCK(mainParamsExt2_ParserStruct.RC_CalibN[2].RC_CalibPosScale),
		VAR_BLOCK(mainParamsExt2_ParserStruct.RC_CalibN[3].RC_CalibSrc),
		VAR_BLOCK(mainParamsExt2_ParserStruct.RC_CalibN[3].RC_CalibOffset),
		VAR_BLOCK(mainParamsExt2_ParserStruct.RC_CalibN[3].RC_CalibNegScale),
		VAR_BLOCK(mainParamsExt2_ParserStruct.RC_CalibN[3].RC_CalibPosScale),
		VAR_BLOCK(mainParamsExt2_ParserStruct.RC_CalibN[4].RC_CalibSrc),
		VAR_BLOCK(mainParamsExt2_ParserStruct.RC_CalibN[4].RC_CalibOffset),
		VAR_BLOCK(mainParamsExt2_ParserStruct.RC_CalibN[4].RC_CalibNegScale),
		VAR_BLOCK(mainParamsExt2_ParserStruct.RC_CalibN[4].RC_CalibPosScale),
		VAR_BLOCK(mainParamsExt2_ParserStruct.parkingPosCfg),
		VAR_BLOCK(mainParamsExt2_ParserStruct.extLED_PinID),
		VAR_BLOCK(mainParamsExt2_ParserStruct.interruptCfg),
		VAR_BLOCK(mainParamsExt2_ParserStruct.overloadTime),
		VAR_BLOCK(mainParamsExt2_ParserStruct.autoPID_Momentum),
		DATA_BLOCK(mainParamsExt2_ParserStruct.jerkSlope),
		VAR_BLOCK(mainParamsExt2_ParserStruct.MAV_ControlMode),
		VAR_BLOCK(mainParamsExt2_ParserStruct.RC_SerialSpeed),
		VAR_BLOCK(mainParamsExt2_ParserStruct.UART2_Speed),
		DATA_BLOCK(mainParamsExt2_ParserStruct.motorRes),
		VAR_BLOCK(mainParamsExt2_ParserStruct.currentLimit),
		VAR_BLOCK(mainParamsExt2_ParserStruct.middleMotTiltAngle),
	};

	const ui8 MainParamsExt2_ParserStructDB_Size = countof(MainParamsExt2_ParserStructDB);
	/**	@}
	 */


	/**	@addtogroup	Profile_Params_Ext_3
	 * 	@{
	 */
	/** @brief	Sample for Big Endian Mapping
	 *
	 * 	@ref	MainParamsExt3_ParserStructDB
	 */
	const MainParamsExt3_t mainParamsExt3_ParserStruct;

	const ParserBlock_t MainParamsExt3_ParserStructDB [] =
	{
		VAR_BLOCK(mainParamsExt3_ParserStruct.profileID),
		DATA_BLOCK(mainParamsExt3_ParserStruct.reserved1),
		VAR_BLOCK(mainParamsExt3_ParserStruct.extIMU_Type),
		VAR_BLOCK(mainParamsExt3_ParserStruct.extIMU_Port),
		VAR_BLOCK(mainParamsExt3_ParserStruct.extIMU_Position),
		VAR_BLOCK(mainParamsExt3_ParserStruct.extIMU_Orientation),
		VAR_BLOCK(mainParamsExt3_ParserStruct.extIMU_Flags),
		DATA_BLOCK(mainParamsExt3_ParserStruct.extIMU_Reserved),
		DATA_BLOCK(mainParamsExt3_ParserStruct.softLimitWidth),
		DATA_BLOCK(mainParamsExt3_ParserStruct.ADC_ReplaceSrc),
		VAR_BLOCK(mainParamsExt3_ParserStruct.glockMidMotPosCorrRate),
		DATA_BLOCK(mainParamsExt3_ParserStruct.extraBtnCfg),
		DATA_BLOCK(mainParamsExt3_ParserStruct.powerCtrlCfg),
		DATA_BLOCK(mainParamsExt3_ParserStruct.reserved2),
		VAR_BLOCK(mainParamsExt3_ParserStruct.CAN_IMU_ExtSensType),
		VAR_BLOCK(mainParamsExt3_ParserStruct.profileFlags2),
		DATA_BLOCK(mainParamsExt3_ParserStruct.reserved3),
		VAR_BLOCK(mainParamsExt3_ParserStruct.generalFlags3),
		DATA_BLOCK(mainParamsExt3_ParserStruct.followOffsetExt),
		VAR_BLOCK(mainParamsExt3_ParserStruct.motorStartupDelay),
		DATA_BLOCK(mainParamsExt3_ParserStruct.reserved4),
	};

	const ui8 MainParamsExt3_ParserStructDB_Size = countof(MainParamsExt3_ParserStructDB);
	/**	@}
	 */

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	Profile_Common
 * 	@{
 */
/**	@brief	Performs a specific action on a profile
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	slot - slot to operate
 *	@param	action - action on the slot
 *	@param	*confirmationState - confirmation structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ManageProfileSet (GeneralSBGC_t *generalSBGC, Profile_t slot, ProfileSetAction_t action, ConfirmationState_t *confirmationState)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_PROFILE_SET);
	WriteByte(&cmd, ++slot);  // 1..5: regular slots, 6 – backup slot
	WriteByte(&cmd, action);
	WriteEmptyBuff(&cmd, 8);  // reserved[8]
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, cmd.commandID);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Action required before and after uploading profile settings
 *
 * 	@attention	Firmware: 2.70b4+
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	action - stop/start operation
 *	@param	*confirmationState - confirmation structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_WriteParamsSet (GeneralSBGC_t *generalSBGC, ProfileWritingFlag_t action, ConfirmationState_t *confirmationState)
{
	if (generalSBGC->_firmwareVersion < 2704)
		return NOT_SUPPORTED_BY_FIRMWARE;

	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_WRITE_PARAMS_SET);
	WriteByte(&cmd, action);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, cmd.commandID);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Writes profile names to EEPROM
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*profileNames - structure with written profile names
 *	@param	*confirmationState - confirmation structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_WriteProfileNames (GeneralSBGC_t *generalSBGC, const ProfileNames_t *profileNames, ConfirmationState_t *confirmationState)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_WRITE_PROFILE_NAMES);
	WriteBuff(&cmd, profileNames, sizeof(ProfileNames_t), PM_DEFAULT_8BIT);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, cmd.commandID);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Request profile names stored in EEPROM
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*profileNames - structure for storing profile names
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ReadProfileNames (GeneralSBGC_t *generalSBGC, ProfileNames_t *profileNames)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_READ_PROFILE_NAMES);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_READ_PROFILE_NAMES), "Profile Names:") == TX_RX_OK)
		ReadBuff(&cmd, profileNames, sizeof(ProfileNames_t), PM_DEFAULT_8BIT);

	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Reset to factory defaults
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param 	profileID - profile slot
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_UseDefaults (GeneralSBGC_t *generalSBGC, Profile_t profileID)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_USE_DEFAULTS);
	WriteByte(&cmd, profileID);
	SBGC32_TX(generalSBGC, &cmd);
	/* no need confirmation */
	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Profile_Params_3
 * 	@{
 */
/**	@brief	Write system configuration part 1
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*mainParams3 - structure with written profile parameters
 *	@param	*confirmationState - confirmation structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_WriteParams3 (GeneralSBGC_t *generalSBGC, const MainParams3_t *mainParams3, ConfirmationState_t *confirmationState)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_WRITE_PARAMS_3);
	WriteBuff(&cmd, mainParams3, sizeof(MainParams3_t), PM_MAIN_PARAMS_3);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, cmd.commandID);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Reads system configuration part 1
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*mainParams3 - structure for storing profile parameters
 *	@param 	profileN - profile slot
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ReadParams3 (GeneralSBGC_t *generalSBGC, MainParams3_t *mainParams3, Profile_t profileN)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_READ_PARAMS_3);
	WriteByte(&cmd, profileN);

	if(CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_READ_PARAMS_3), "Main Parameters 3:") == TX_RX_OK)
		ReadBuff(&cmd, mainParams3, sizeof(MainParams3_t), PM_MAIN_PARAMS_3);

	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Profile_Params_Ext
 * 	@{
 */
/**	@brief	Write system configuration part 2
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*mainParamsExt - structure with written profile parameters
 *	@param	*confirmationState - confirmation structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_WriteParamsExt (GeneralSBGC_t *generalSBGC, const MainParamsExt_t *mainParamsExt, ConfirmationState_t *confirmationState)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_WRITE_PARAMS_EXT);
	WriteBuff(&cmd, mainParamsExt, sizeof(MainParamsExt_t), PM_MAIN_PARAMS_EXT);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, cmd.commandID);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Reads system configuration part 2
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*mainParamsExt - structure for storing profile parameters
 *	@param 	profileN - profile slot
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ReadParamsExt (GeneralSBGC_t *generalSBGC, MainParamsExt_t *mainParamsExt, Profile_t profileN)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_READ_PARAMS_EXT);
	WriteByte(&cmd, profileN);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_READ_PARAMS_EXT), "Main Parameters Ext:") == TX_RX_OK)
		ReadBuff(&cmd, mainParamsExt, sizeof(MainParamsExt_t), PM_MAIN_PARAMS_EXT);

	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Profile_Params_Ext_2
 * 	@{
 */
/**	@brief	Write system configuration part 3
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*mainParamsExt2 - structure with written profile parameters
 *	@param	*confirmationState - confirmation structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_WriteParamsExt2 (GeneralSBGC_t *generalSBGC, const MainParamsExt2_t *mainParamsExt2, ConfirmationState_t *confirmationState)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_WRITE_PARAMS_EXT2);
	WriteBuff(&cmd, mainParamsExt2, sizeof(MainParamsExt2_t), PM_MAIN_PARAMS_EXT_2);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, cmd.commandID);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Reads system configuration part 3
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*mainParamsExt2 - structure for storing profile parameters
 *	@param 	profileN - profile slot
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ReadParamsExt2 (GeneralSBGC_t *generalSBGC, MainParamsExt2_t *mainParamsExt2, Profile_t profileN)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_READ_PARAMS_EXT2);
	WriteByte(&cmd, profileN);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_READ_PARAMS_EXT2), "Main Parameters Ext 2:") == TX_RX_OK)
		ReadBuff(&cmd, mainParamsExt2, sizeof(MainParamsExt2_t), PM_MAIN_PARAMS_EXT_2);

	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */


/**	@addtogroup	Profile_Params_Ext_3
 * 	@{
 */
/**	@brief	Write system configuration part 4
 *
 *	@attention	Firmware: 2.66+
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*mainParamsExt3 - structure with written profile parameters
 *	@param	*confirmationState - confirmation structure
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_WriteParamsExt3 (GeneralSBGC_t *generalSBGC, const MainParamsExt3_t *mainParamsExt3, ConfirmationState_t *confirmationState)
{
	if (generalSBGC->_firmwareVersion < 2660)
		return NOT_SUPPORTED_BY_FIRMWARE;

	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_WRITE_PARAMS_EXT3);
	WriteBuff(&cmd, mainParamsExt3, sizeof(MainParamsExt3_t), PM_MAIN_PARAMS_EXT_3);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, confirmationState, cmd.commandID);
	return generalSBGC->_ParserCurrentStatus;
}


/**	@brief	Reads system configuration part 4
 *
 *	@attention	Firmware: 2.66+
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*mainParamsExt3 - structure for storing profile parameters
 *	@param 	profileN - profile slot
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ReadParamsExt3 (GeneralSBGC_t *generalSBGC, MainParamsExt3_t *mainParamsExt3, Profile_t profileN)
{
	if (generalSBGC->_firmwareVersion < 2660)
		return NOT_SUPPORTED_BY_FIRMWARE;

	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_READ_PARAMS_EXT3);
	WriteByte(&cmd, profileN);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_READ_PARAMS_EXT3), "Main Parameters Ext 3:") == TX_RX_OK)
		ReadBuff(&cmd, mainParamsExt3, sizeof(MainParamsExt3_t), PM_MAIN_PARAMS_EXT_3);

	return generalSBGC->_ParserCurrentStatus;
}
/**	@}
 */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
