/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.1
 *
 *	@file		gimbalControl.c
 *
 *	@brief		Gimbal control source file
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


#if (SBGC_CONTROL_MODULE)

#if (SBGC_USES_REF_INFO)

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *					Big Endian Mapping and Reference Info Structures
	 */
	/**	@addtogroup	Control
	 *	@{
	 */
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t controlReferenceInfoArray [] =
	{
		PARAMS_BLOCK_(	"Control Mode",				sbgcUCHAR,					3	),  // 0
		PARAM_BLOCK_(	"Speed [ROLL]",				sbgcSHORT						),  // 1
		PARAM_BLOCK_(	"Angle [ROLL]",				sbgcSHORT						),  // 2
		PARAM_BLOCK_(	"Speed [PITCH]",			sbgcSHORT						),  // 3
		PARAM_BLOCK_(	"Angle [PITCH]",			sbgcSHORT						),  // 4
		PARAM_BLOCK_(	"Speed [YAW]",				sbgcSHORT						),  // 5
		PARAM_BLOCK_(	"Angle [YAW]",				sbgcSHORT						),  // 6

	};

	const ui8 controlReferenceInfoArrayElCnt = countof_(controlReferenceInfoArray);


	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t controlExtReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Data Set",					sbgcUSHORT						),  // 0
		PARAM_BLOCK_(	"Control Mode [ROLL]",		sbgcUSHORT						),  // 1
		PARAM_BLOCK_(	"Speed [ROLL]",				sbgcSHORT						),  // 2
		PARAM_BLOCK_(	"Angle [ROLL]",				sbgcINT							),  // 3
		PARAM_BLOCK_(	"Control Mode [PITCH]",		sbgcUSHORT						),  // 4
		PARAM_BLOCK_(	"Speed [PITCH]",			sbgcSHORT						),  // 5
		PARAM_BLOCK_(	"Angle [PITCH]",			sbgcINT							),  // 6
		PARAM_BLOCK_(	"Control Mode [YAW]",		sbgcUSHORT						),  // 7
		PARAM_BLOCK_(	"Speed [YAW]",				sbgcSHORT						),  // 8
		PARAM_BLOCK_(	"Angle [YAW]",				sbgcINT							),  // 9

	};

	const ui8 controlExtReferenceInfoArrayElCnt = countof_(controlExtReferenceInfoArray);


	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t controlQuatReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Mode",						sbgcUCHAR						),  // 0
		PARAM_BLOCK_(	"Flags",					sbgcUCHAR						),  // 1
		PARAMS_BLOCK_(	"Target Attitude",			sbgcFLOAT,					4	),  // 2
		PARAMS_BLOCK_(	"Target Speed",				sbgcFLOAT,					3	),  // 3

	};

	const ui8 controlQuatReferenceInfoArrayElCnt = countof_(controlQuatReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Control_Config
	 *	@{
	 */
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t controlConfigReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Timeout Ms",				sbgcUSHORT						),  // 0
		PARAM_BLOCK_(	"Ch1 Priority",				sbgcUCHAR						),  // 1
		PARAM_BLOCK_(	"Ch2 Priority",				sbgcUCHAR						),  // 2
		PARAM_BLOCK_(	"Ch3 Priority",				sbgcUCHAR						),  // 3
		PARAM_BLOCK_(	"Ch4 Priority",				sbgcUCHAR						),  // 4
		PARAM_BLOCK_(	"This Ch Priority",			sbgcUCHAR						),  // 5
		PARAM_BLOCK_(	"Angle LPF [ROLL]",			sbgcUCHAR						),  // 6
		PARAM_BLOCK_(	"Speed LPF [ROLL]",			sbgcUCHAR						),  // 7
		PARAM_BLOCK_(	"RC LPF [ROLL]",			sbgcUCHAR						),  // 8
		PARAM_BLOCK_(	"Acc Limit [ROLL]",			sbgcUSHORT						),  // 9
		PARAM_BLOCK_(	"Jerk Slope [ROLL]",		sbgcUCHAR						),  // 10
		PARAM_BLOCK_(	"Reserved 1 [ROLL]",		sbgcRCHAR						),  // 11
		PARAM_BLOCK_(	"Angle LPF [PITCH]",		sbgcUCHAR						),  // 12
		PARAM_BLOCK_(	"Speed LPF [PITCH]",		sbgcUCHAR						),  // 13
		PARAM_BLOCK_(	"RC LPF [PITCH]",			sbgcUCHAR						),  // 14
		PARAM_BLOCK_(	"Acc Limit [PITCH]",		sbgcUSHORT						),  // 15
		PARAM_BLOCK_(	"Jerk Slope [PITCH]",		sbgcUCHAR						),  // 16
		PARAM_BLOCK_(	"Reserved 1 [PITCH]",		sbgcRCHAR						),  // 17
		PARAM_BLOCK_(	"Angle LPF [YAW]",			sbgcUCHAR						),  // 18
		PARAM_BLOCK_(	"Speed LPF [YAW]",			sbgcUCHAR						),  // 19
		PARAM_BLOCK_(	"RC LPF [YAW]",				sbgcUCHAR						),  // 20
		PARAM_BLOCK_(	"Acc Limit [YAW]",			sbgcUSHORT						),  // 21
		PARAM_BLOCK_(	"Jerk Slope [YAW]",			sbgcUCHAR						),  // 22
		PARAM_BLOCK_(	"Reserved 1 [YAW]",			sbgcRCHAR						),  // 23
		PARAM_BLOCK_(	"RC Expo Rate",				sbgcUCHAR						),  // 24
		PARAM_BLOCK_(	"Flags",					(sbgcUSHORT | sbgcFLAG)			),  // 25
		PARAM_BLOCK_(	"Euler Order",				sbgcUCHAR						),  // 26
		PARAMS_BLOCK_(	"Reserved 2",				sbgcRCHAR,					9	),  // 27

	};

	const ui8 controlConfigReferenceInfoArrayElCnt = countof_(controlConfigReferenceInfoArray);


	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t controlQuatConfigReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Data Set",					sbgcUSHORT						),  // 0
		PARAMS_BLOCK_(	"Max Speed",				sbgcUSHORT,					3	),  // 1
		PARAMS_BLOCK_(	"Acc Limit",				sbgcUSHORT,					3	),  // 2
		PARAMS_BLOCK_(	"Jerk Slope",				sbgcUSHORT,					3	),  // 3
		PARAM_BLOCK_(	"Flags",					sbgcUSHORT						),  // 4
		PARAM_BLOCK_(	"Attitude LPF Frequency",	sbgcUCHAR						),  // 5
		PARAM_BLOCK_(	"Speed LPF Frequency",		sbgcUCHAR						),  // 6

	};

	const ui8 controlQuatConfigReferenceInfoArrayElCnt = countof_(controlQuatConfigReferenceInfoArray);


	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t extMotorsControlConfigReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"For Motors",				sbgcUCHAR						),  // 0
		PARAM_BLOCK_(	"Data Set",					sbgcUSHORT						),  // 1
		PARAM_BLOCK_(	"Mode",						sbgcUCHAR						),  // 2
		PARAM_BLOCK_(	"Max Speed",				sbgcUCHAR						),  // 3
		PARAM_BLOCK_(	"Max Acceleration",			sbgcUSHORT						),  // 4
		PARAM_BLOCK_(	"Jerk Slope",				sbgcUSHORT						),  // 5
		PARAM_BLOCK_(	"Max Torque",				sbgcUSHORT						),  // 6

	};

	const ui8 extMotorsControlConfigReferenceInfoArrayElCnt = countof_(extMotorsControlConfigReferenceInfoArray);
	/**	@}
	 */

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	Control
 *	@{
 */
/**	@brief	Controls gimbal movement
 *
 *	####	TX —> CMD_CONTROL		15 bytes
 *
 *	@pre	Additional control configurations may be
 *			adjusted with the @ref SBGC32_ControlConfig
 *			function
 *
 *	@post	If sbgcControlConfig_t.flags is set to
 *			CtrlCONFIG_FLAG_NEED_CONFIRM, SBGC32
 *			will send confirmation command
 *			after each successful transfer that
 *			need to be handled manually.
 *			Call the @ref SBGC32_CheckConfirmation function
 *			passing it the CMD_CONTROL argument
 *
 *	@code

			sbgcControl_t Control = { 0 };

			#if (SBGC_NEED_CONFIRM_CMD)

				sbgcControlConfig_t ControlConfig = { 0 };

				ControlConfig.flags = CtrlCONFIG_FLAG_NO_CONFIRM;
				SBGC32_ControlConfig(&SBGC32_Device, &ControlConfig, SBGC_NO_CONFIRM);

			#endif

			// Angle control
			Control.mode[ROLL] = CtrlMODE_NO_CONTROL;
			Control.mode[PITCH] = CtrlMODE_ANGLE;
			Control.mode[YAW] = CtrlMODE_ANGLE;

			Control.AxisC[PITCH].speed = sbgcSpeedToValue(15);
			Control.AxisC[PITCH].angle = sbgcAngleToDegree(30);
			Control.AxisC[YAW].speed = sbgcSpeedToValue(45);
			Control.AxisC[YAW].angle = sbgcAngleToDegree(90);
			SBGC32_Control(&SBGC32_Device, &Control);
			sbgcDelay(3000);

			Control.AxisC[YAW].speed = sbgcSpeedToValue(90);
			Control.AxisC[YAW].angle = sbgcAngleToDegree(-90);
			SBGC32_Control(&SBGC32_Device, &Control);
			sbgcDelay(3000);

			// Switch to speed mode
			Control.mode[PITCH] = CtrlMODE_SPEED;
			Control.mode[YAW] = CtrlMODE_SPEED;

			Control.AxisC[PITCH].speed = sbgcSpeedToValue(-15);
			Control.AxisC[YAW].speed = sbgcSpeedToValue(45);
			SBGC32_Control(&SBGC32_Device, &Control);
			sbgcDelay(2000);

			#if (SBGC_NEED_CONFIRM_CMD)

				ControlConfig.flags = CtrlCONFIG_FLAG_NEED_CONFIRM;
				SBGC32_ControlConfig(&SBGC32_Device, &ControlConfig, SBGC_NO_CONFIRM);
				// From this point on the gimbal will send a confirmation command to each control operation

			#endif

			// Stop at the center
			Control.AxisC[PITCH].speed = sbgcSpeedToValue(0);
			Control.AxisC[YAW].speed = sbgcSpeedToValue(0);
			SBGC32_Control(&SBGC32_Device, &Control);

			#if (SBGC_NEED_CONFIRM_CMD)
				SBGC32_CheckConfirmation(&SBGC32_Device, SBGC_NO_CONFIRM, CMD_CONTROL);
			#endif

			// Unlock gimbal for another control signals
			Control.mode[ROLL] = CtrlMODE_NO_CONTROL;
			Control.mode[PITCH] = CtrlMODE_NO_CONTROL;
			Control.mode[YAW] = CtrlMODE_NO_CONTROL;

			SBGC32_Control(&SBGC32_Device, &Control);

			#if (SBGC_NEED_CONFIRM_CMD)
				SBGC32_CheckConfirmation(&SBGC32_Device, SBGC_NO_CONFIRM, CMD_CONTROL);
			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*control - structure containing gimbal control data
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_Control (sbgcGeneral_t *gSBGC, const sbgcControl_t *control
									/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_CONTROL SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeBuff(gSBGC, control, sizeof(sbgcControl_t));
	gSBGC->_api->finishWrite(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Controls gimbal movement in extended format
 *
 *	####	TX —> CMD_CONTROL_EXT	20/26 bytes
 *
 *	@pre	Additional control configurations may be
 *			adjusted with the @ref SBGC32_ControlConfig
 *			function
 *
 *	@post	If sbgcControlConfig_t.flags is set to
 *			CtrlCONFIG_FLAG_NEED_CONFIRM, SBGC32
 *			will send confirmation command
 *			after each successful transfer
 *
 *	@attention	Firmware: 2.68+
 *
 *	@code

			sbgcControlExt_t ControlExt = { 0 };

			#if (SBGC_NEED_CONFIRM_CMD)

				sbgcControlConfig_t ControlConfig = { 0 };

				ControlConfig.flags = CtrlCONFIG_FLAG_NEED_CONFIRM;
				SBGC32_ControlConfig(&SBGC32_Device, &ControlConfig, SBGC_NO_CONFIRM);

			#endif

			// Setting the ROLL axis to rotate by angle
			ControlExt.dataSet = CEDS_ROLL_SPEED | CEDS_ROLL_ANGLE;

			ControlExt.AxisCE[ROLL].mode = CtrlMODE_ANGLE;

			ControlExt.AxisCE[ROLL].speed = sbgcSpeedToValue(15);
			ControlExt.AxisCE[ROLL].angle = sbgcAngleToDegree(30);
			SBGC32_ControlExt(&SBGC32_Device, &ControlExt);
			sbgcDelay(3000);

			ControlExt.AxisCE[ROLL].speed = sbgcSpeedToValue(30);
			ControlExt.AxisCE[ROLL].angle = sbgcAngleToDegree(-30);
			SBGC32_ControlExt(&SBGC32_Device, &ControlExt);
			sbgcDelay(3000);

			ControlExt.AxisCE[ROLL].speed = sbgcSpeedToValue(15);
			ControlExt.AxisCE[ROLL].angle = sbgcAngleToDegree(0);
			SBGC32_ControlExt(&SBGC32_Device, &ControlExt);
			sbgcDelay(3000);

			// Setting the PITCH and YAW axes to control by angle
			ControlExt.dataSet = CEDS_PITCH_SPEED | CEDS_PITCH_ANGLE | CEDS_YAW_SPEED | CEDS_YAW_ANGLE;

			ControlExt.AxisCE[PITCH].mode = CtrlMODE_ANGLE;
			ControlExt.AxisCE[PITCH].speed = sbgcSpeedToValue(60);

			ControlExt.AxisCE[YAW].mode = CtrlMODE_ANGLE;
			ControlExt.AxisCE[YAW].speed = sbgcSpeedToValue(60);

			// Do a little demo
			ControlExt.AxisCE[YAW].angle = sbgcAngleToDegree(60);
			SBGC32_ControlExt(&SBGC32_Device, &ControlExt);
			sbgcDelay(1000);

			ControlExt.AxisCE[PITCH].angle = sbgcAngleToDegree(15);
			SBGC32_ControlExt(&SBGC32_Device, &ControlExt);
			sbgcDelay(250);

			ControlExt.AxisCE[PITCH].angle = sbgcAngleToDegree(-15);
			SBGC32_ControlExt(&SBGC32_Device, &ControlExt);
			sbgcDelay(500);

			ControlExt.AxisCE[PITCH].angle = sbgcAngleToDegree(0);
			SBGC32_ControlExt(&SBGC32_Device, &ControlExt);
			sbgcDelay(250);

			ControlExt.AxisCE[YAW].angle = sbgcAngleToDegree(-60);
			SBGC32_ControlExt(&SBGC32_Device, &ControlExt);
			sbgcDelay(2000);

			ControlExt.AxisCE[PITCH].angle = sbgcAngleToDegree(15);
			SBGC32_ControlExt(&SBGC32_Device, &ControlExt);
			sbgcDelay(250);

			ControlExt.AxisCE[PITCH].angle = sbgcAngleToDegree(-15);
			SBGC32_ControlExt(&SBGC32_Device, &ControlExt);
			sbgcDelay(500);

			ControlExt.AxisCE[PITCH].angle = sbgcAngleToDegree(0);
			SBGC32_ControlExt(&SBGC32_Device, &ControlExt);
			sbgcDelay(250);

			#if (SBGC_NEED_CONFIRM_CMD)

				ControlConfig.flags = CtrlCONFIG_FLAG_NEED_CONFIRM;
				SBGC32_ControlConfig(&SBGC32_Device, &ControlConfig, SBGC_NO_CONFIRM);
				// From this point on the gimbal will send a confirmation command to each control operation

			#endif

			// Stop at the center
			ControlExt.AxisCE[YAW].angle = sbgcAngleToDegree(0);
			SBGC32_ControlExt(&SBGC32_Device, &ControlExt);
			sbgcDelay(1000);

			#if (SBGC_NEED_CONFIRM_CMD)
				SBGC32_CheckConfirmation(&SBGC32_Device, SBGC_NO_CONFIRM, CMD_CONTROL_EXT);
			#endif

			// Unlock gimbal for another control signals
			ControlExt.AxisCE[ROLL].mode = CtrlMODE_NO_CONTROL;
			ControlExt.AxisCE[PITCH].mode = CtrlMODE_NO_CONTROL;
			ControlExt.AxisCE[YAW].mode = CtrlMODE_NO_CONTROL;
			SBGC32_ControlExt(&SBGC32_Device, &ControlExt);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*controlExt - structure containing
 *			gimbal control data
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ControlExt (sbgcGeneral_t *gSBGC, const sbgcControlExt_t *controlExt
									   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2680)
	sbgcAssertParam(controlExt->dataSet, 1, 0xFFFF)

	gSBGC->_api->startWrite(gSBGC, CMD_CONTROL_EXT SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeWord(gSBGC, controlExt->dataSet);

	for (ui8 i = 0; i < 3; i++)
	{
		if (controlExt->dataSet & (0x001F << (i * 5)))
		/* If this axis is enabled */
		{
			gSBGC->_api->writeByte(gSBGC, controlExt->AxisCE[i].mode);
			gSBGC->_api->writeByte(gSBGC, controlExt->AxisCE[i].modeFlags);

			/* Write speed */
			if (controlExt->dataSet & (0x01 << (i * 5)))
				gSBGC->_api->writeWord(gSBGC, controlExt->AxisCE[i].speed);

			else if (controlExt->dataSet & (0x08 << (i * 5)))
				gSBGC->_api->writeLong(gSBGC, controlExt->AxisCE[i].speed);

			/* Write angle */
			if (controlExt->dataSet & (0x02 << (i * 5)))
				gSBGC->_api->writeWord(gSBGC, controlExt->AxisCE[i].angle);

			else if (controlExt->dataSet & (0x04 << (i * 5)))
				gSBGC->_api->writeLong(gSBGC, controlExt->AxisCE[i].angle);
		}
	}

	gSBGC->_api->finishWrite(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Controls gimbal movement in quaternions
 *
 *	####	TX —> CMD_CONTROL_QUAT	30 bytes
 *
 *	@pre	Additional control configurations may be
 *			adjusted with the @ref SBGC32_ControlConfig
 *			function
 *
 *	@post	If sbgcControlQuat_t.flags is set to
 *			CtrlQ_FLAG_NEED_CONFIRM, SBGC32
 *			will send confirmation command
 *			after each successful transfer.
 *			Call the @ref SBGC32_CheckConfirmation function
 *			passing it the CMD_CONTROL_QUAT argument
 *
 *	@attention	Firmware: 2.73+
 *
 *	@code

			sbgcControlQuat_t ControlQuat = { 0 };

			// Speed control
			ControlQuat.mode = CtrlQ_MODE_SPEED;

			ControlQuat.speed[YAW] = sbgcDegreeToRadians(15);

			SBGC32_ControlQuat(&SBGC32_Device, &ControlQuat);

			sbgcDelay(2000);

			ControlQuat.speed[YAW] = sbgcDegreeToRadians(-15);

			SBGC32_ControlQuat(&SBGC32_Device, &ControlQuat);

			sbgcDelay(4000);

			ControlQuat.speed[YAW] = sbgcDegreeToRadians(15);

			SBGC32_ControlQuat(&SBGC32_Device, &ControlQuat);

			sbgcDelay(2000);

			#if (SBGC_NEED_CONFIRM_CMD)
				ControlQuat.flags = CtrlQ_FLAG_NEED_CONFIRM;
			#endif

			ControlQuat.speed[YAW] = sbgcDegreeToRadians(0);

			SBGC32_ControlQuat(&SBGC32_Device, &ControlQuat);

			#if (SBGC_NEED_CONFIRM_CMD)

				// Get confirmation that gimbal stops
				SBGC32_CheckConfirmation(&SBGC32_Device, SBGC_NO_CONFIRM, CMD_CONTROL_QUAT);

			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*controlQuat - structure containing
 *			gimbal control data in quaternions
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ControlQuat (sbgcGeneral_t *gSBGC, const sbgcControlQuat_t *controlQuat
										/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2730)
	sbgcAssertFeature2(BFE2_QUAT_CONTROL)

	gSBGC->_api->startWrite(gSBGC, CMD_CONTROL_QUAT SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, controlQuat->mode);
	gSBGC->_api->writeByte(gSBGC, controlQuat->flags);

	if ((controlQuat->mode == CtrlQ_MODE_ATTITUDE) || (controlQuat->mode == CtrlQ_MODE_SPEED_ATTITUDE))
		gSBGC->_api->writeBuff(gSBGC, controlQuat->attitude, sizeof(controlQuat->attitude));

	if ((controlQuat->mode == CtrlQ_MODE_SPEED) || (controlQuat->mode == CtrlQ_MODE_SPEED_ATTITUDE) ||
		(controlQuat->mode == CtrlQ_MODE_SPEED_LIMITED))
		gSBGC->_api->writeBuff(gSBGC, controlQuat->speed, sizeof(controlQuat->speed));

	gSBGC->_api->finishWrite(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Execute an action on the motor(s)
 *
 *	@post	If id is set to EXT_MOTOR_NEED_CONFIRM
 *			SBGC32 will send confirmation command
 *			after each successful transfer
 *
 *	@attention	Firmware: 2.73+
 *
 *	@code

			// Return 3 motors to the home position
			SBGC32_ExtMotorsAction(&SBGC32_Device, EXT_MOTOR_ID_1 | EXT_MOTOR_ID_2 | EXT_MOTOR_ID_3, EXT_HOME_POSITION, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	id - motor identifiers. Can be combined
 *			with each other
 *	@param	action - actions for motor execution
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ExtMotorsAction (sbgcGeneral_t *gSBGC, sbgcExtMotorID_t id, sbgcExtMotorAction_t action, sbgcConfirm_t *confirm
											/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2730)

	gSBGC->_api->startWrite(gSBGC, CMD_EXT_MOTORS_ACTION SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, id);
	gSBGC->_api->writeByte(gSBGC, action);
	gSBGC->_api->finishWrite(gSBGC);

	if (id & EXT_MOTOR_NEED_CONFIRM)
	/* Handle incoming confirmation command */
	{
		gSBGC->_api->addConfirm(gSBGC, confirm, CMD_EXT_MOTORS_ACTION SBGC_ADVANCED_ARGS__);

		gSBGC->_api->link(gSBGC);
	}

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Controls selected gimbal motor(s)
 *
 *	@post	If sbgcControlExtMotors_t.forMotors is set to
 *			EXT_MOTOR_NEED_CONFIRM, SBGC32
 *			will send confirmation command
 *			after each successful transfer
 *
 *	@attention	Firmware: 2.73+
 *
 *	@code

			sbgcControlExtMotors_t controlExtMotors [3] = { 0 };

			// Move motors to various position
			controlExtMotors[0].setpoint = sbgcAngleToDegree(15);
			controlExtMotors[1].setpoint = sbgcAngleToDegree(30);
			controlExtMotors[2].setpoint = sbgcAngleToDegree(45);

			SBGC32_ControlExtMotors(&SBGC32_Device, controlExtMotors, EXT_MOTOR_ID_1 | EXT_MOTOR_ID_2 | EXT_MOTOR_ID_3,
									EMP_16BIT_SETPOINT, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*controlExtMotors - structure containing
 *			gimbal control data
 *	@param	id - motor identifiers. Can be combined
 *			with each other
 *	@param	dataSet -
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ControlExtMotors (sbgcGeneral_t *gSBGC, sbgcControlExtMotors_t *controlExtMotors, sbgcExtMotorID_t id,
											 sbgcExtMotorParam_t dataSet, sbgcConfirm_t *confirm
											 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2730)

	gSBGC->_api->startWrite(gSBGC, CMD_EXT_MOTORS_CONTROL SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, id);
	gSBGC->_api->writeByte(gSBGC, dataSet);

	for (ui8 i = 0; i < SBGC_EXTRA_MOTORS_NUM; i++)
	{
		if (dataSet & EMP_32BIT_SETPOINT)
			gSBGC->_api->writeLong(gSBGC, controlExtMotors->setpoint);

		else
			gSBGC->_api->writeWord(gSBGC, (i16)controlExtMotors->setpoint);

		if (dataSet & EMP_PARAM1_IS_16BIT)
			gSBGC->_api->writeWord(gSBGC, (i16)controlExtMotors->param1);

		else if (dataSet & EMP_PARAM1_IS_32BIT)
			gSBGC->_api->writeLong(gSBGC, controlExtMotors->param1);
	}

	gSBGC->_api->finishWrite(gSBGC);

	if (id & EXT_MOTOR_NEED_CONFIRM)
	/* Handle incoming confirmation command */
	{
		gSBGC->_api->addConfirm(gSBGC, confirm, CMD_EXT_MOTORS_CONTROL SBGC_ADVANCED_ARGS__);

		gSBGC->_api->link(gSBGC);
	}

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Control_Config
 *	@{
 */
/**	@brief	Configure the handling of CMD_CONTROL command
 *
 *	####	TX —> CMD_CONTROL_CONFIG :		41 bytes
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@attention	Firmware: 2.61+
 *
 *	@code

			#define SBGC_PITCH_LPF 5
			#define SBGC_PITCH_ACC_LIMIT 500
			#define SBGC_PITCH_JERK_SLOPE_DISABLE 1

			sbgcControlConfig_t ControlConfig = { 0 };

			ControlConfig.flags = CtrlCONFIG_FLAG_NO_CONFIRM;

			// Setup the pitch axis
			ControlConfig.AxisCCtrl[PITCH].angleLPF = SBGC_PITCH_LPF;
			ControlConfig.AxisCCtrl[PITCH].speedLPF = SBGC_PITCH_LPF;
			ControlConfig.AxisCCtrl[PITCH].accLimit = SBGC_PITCH_ACC_LIMIT;
			ControlConfig.AxisCCtrl[PITCH].jerkSlope = SBGC_PITCH_JERK_SLOPE_DISABLE;

			SBGC32_ControlConfig(&SBGC32_Device, &ControlConfig, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*controlConfig - structure containing gimbal
 *			control configuration data
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ControlConfig (sbgcGeneral_t *gSBGC, const sbgcControlConfig_t *controlConfig, sbgcConfirm_t *confirm
										  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2610)

	gSBGC->_api->startWrite(gSBGC, CMD_CONTROL_CONFIG SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeBuff(gSBGC, controlConfig, sizeof(sbgcControlConfig_t));
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_CONTROL_CONFIG SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Configures the handling of CMD_CONTROL_QUAT command
 *
 *	####	TX —> CMD_CONTROL_QUAT_CONFIG :	1-24 bytes
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@attention	Firmware: 2.73+
 *
 *	@code

			sbgcControlQuatConfig_t ControlQuatConfig = { 0 };

			// Setup maximal speed
			ControlQuatConfig.dataSet = CQCP_MAX_SPEED;
			ControlQuatConfig.maxSpeed[ROLL] = sbgcSpeedToValue(10);
			ControlQuatConfig.maxSpeed[PITCH] = sbgcSpeedToValue(30);
			ControlQuatConfig.maxSpeed[YAW] = sbgcSpeedToValue(45);

			SBGC32_ControlQuatConfig(&SBGC32_Device, &ControlQuatConfig, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*controlQuatConfig - structure containing gimbal
 *			quaternions control configuration data
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ControlQuatConfig (sbgcGeneral_t *gSBGC, const sbgcControlQuatConfig_t *controlQuatConfig, sbgcConfirm_t *confirm
											  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2730)
	sbgcAssertFeature2(BFE2_QUAT_CONTROL)

	gSBGC->_api->startWrite(gSBGC, CMD_CONTROL_QUAT_CONFIG SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeWord(gSBGC, controlQuatConfig->dataSet);

	if (controlQuatConfig->dataSet & CQCP_MAX_SPEED)
		gSBGC->_api->writeBuff(gSBGC, controlQuatConfig->maxSpeed, sizeof(controlQuatConfig->maxSpeed));

	if (controlQuatConfig->dataSet & CQCP_ACC_LIMIT)
		gSBGC->_api->writeBuff(gSBGC, controlQuatConfig->accLimit, sizeof(controlQuatConfig->accLimit));

	if (controlQuatConfig->dataSet & CQCP_JERK_SLOPE)
		gSBGC->_api->writeBuff(gSBGC, controlQuatConfig->jerkSlope, sizeof(controlQuatConfig->jerkSlope));

	if (controlQuatConfig->dataSet & CQCP_FLAGS)
		gSBGC->_api->writeWord(gSBGC, controlQuatConfig->flags);

	if (controlQuatConfig->dataSet & CQCP_ATTITUDE_LPF_FREQ)
		gSBGC->_api->writeByte(gSBGC, controlQuatConfig->attitudeLPF_Freq);

	if (controlQuatConfig->dataSet & CQCP_SPEED_LPF_FREQ)
		gSBGC->_api->writeByte(gSBGC, controlQuatConfig->speedLPF_Freq);

	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_CONTROL_QUAT_CONFIG SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Configures run-time parameters
 *			for the selected motor(s)
 *
 *	@attention	Firmware: 2.73+
 *
 *	@code

			sbgcExtMotorsControlConfig_t ExtMotorsControlConfig = { 0 };

			ExtMotorsControlConfig.forMotors = EXT_MOTOR_ID_1 | EXT_MOTOR_ID_2 | EXT_MOTOR_ID_3;
			ExtMotorsControlConfig.dataSet = EMCC_PARAM_MAX_SPEED | EMCC_PARAM_MAX_ACCELERATION;
			ExtMotorsControlConfig.maxSpeed = 200 / 2;
			ExtMotorsControlConfig.maxAcceleration = 60 / 2;

			SBGC32_ExtMotorsControlConfig(&SBGC32_Device, &ExtMotorsControlConfig, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*extMotorsControlConfig - structure containing
 *			motors control configuration data
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ExtMotorsControlConfig (sbgcGeneral_t *gSBGC, const sbgcExtMotorsControlConfig_t *extMotorsControlConfig,
												   sbgcConfirm_t *confirm
												   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2730)

	gSBGC->_api->startWrite(gSBGC, CMD_EXT_MOTORS_CONTROL_CONFIG SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, extMotorsControlConfig->forMotors);
	gSBGC->_api->writeWord(gSBGC, extMotorsControlConfig->dataSet);

	if (extMotorsControlConfig->dataSet & EMCC_PARAM_MODE)
		gSBGC->_api->writeByte(gSBGC, extMotorsControlConfig->mode);

	if (extMotorsControlConfig->dataSet & EMCC_PARAM_MAX_SPEED)
		gSBGC->_api->writeWord(gSBGC, extMotorsControlConfig->maxSpeed);

	if (extMotorsControlConfig->dataSet & EMCC_PARAM_MAX_ACCELERATION)
		gSBGC->_api->writeWord(gSBGC, extMotorsControlConfig->maxAcceleration);

	if (extMotorsControlConfig->dataSet & EMCC_PARAM_JERK_SLOPE)
		gSBGC->_api->writeWord(gSBGC, extMotorsControlConfig->jerkSlope);

	if (extMotorsControlConfig->dataSet & EMCC_PARAM_MAX_TORQUE)
		gSBGC->_api->writeWord(gSBGC, extMotorsControlConfig->maxTorque);

	gSBGC->_api->finishWrite(gSBGC);

	if (extMotorsControlConfig->forMotors & EXT_MOTOR_NEED_CONFIRM)
	/* Handle incoming confirmation command */
	{
		gSBGC->_api->addConfirm(gSBGC, confirm, CMD_EXT_MOTORS_CONTROL_CONFIG SBGC_ADVANCED_ARGS__);

		gSBGC->_api->link(gSBGC);
	}

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Virt_Channels
 *	@{
 */
/**	@brief	Sets the value of virtual channels
 *
 *	####	TX —> CMD_API_VIRT_CH_CONTROL :	chQuan * 2 bytes (frw. ver. prior to 2.70b5 - 62 bytes)
 *
 *	@attention	If the firmware version is below 2.70b5, chQuan
 *				must be equal 31 (SBGC_VIRTUAL_CHANNELS_NUM)
 *				and the API_VirtCh field must strictly
 *				contain 31 virtual channel values
 *
 *	@code

			if (SerialAPI_GetFirmwareVersion(&SBGC32_Device) >= 2705)
			{
				// Configure the first three API channels
				i16 API_VirtCh [3] = { -250, 100, SBGC_RC_MAX_VAL };

				SBGC32_SetAPI_VirtChControl(&SBGC32_Device, API_VirtCh, countof_(API_VirtCh));
			}

			else
			{
				i16 API_VirtCh [SBGC_VIRTUAL_CHANNELS_NUM] = { 0 };

				// Configure the 0th, 2nd and 10th API channels
				API_VirtCh[0] = -250;
				API_VirtCh[2] = 100;
				API_VirtCh[10] = SBGC_RC_MAX_VAL;

				SBGC32_SetAPI_VirtChControl(&SBGC32_Device, API_VirtCh, SBGC_VIRTUAL_CHANNELS_NUM);
			}

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*API_VirtCh - -500 --> 500
 *			(SBGC_RC_MIN_VAL --> SBGC_RC_MAX_VAL).
 *			Array with virtual channel values. Use a special value
 *			-10000 (SBGC_RC_UNDEF) to mark that channel has
 * 			"undefined" state (its treated as "signal lost"
 * 			like with the regular RC inputs)
 *	@param	chQuan - number of virtual channels
 *			starting with API_VIRT_CH_1
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SetAPI_VirtChControl (sbgcGeneral_t *gSBGC, const i16 *API_VirtCh, ui8 chQuan
												 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertParam(chQuan, 1, SBGC_VIRTUAL_CHANNELS_NUM)

	#if (SBGC_NEED_ASSERTS)
		if (gSBGC->_api->baseFirmwareVersion < 2705) sbgcAssertParam(chQuan, SBGC_VIRTUAL_CHANNELS_NUM, SBGC_VIRTUAL_CHANNELS_NUM)
	#endif

	gSBGC->_api->startWrite(gSBGC, CMD_API_VIRT_CH_CONTROL SBGC_ADVANCED_ARGS__);

	for (ui8 i = 0; i< chQuan; i++)
	{
		#if (SBGC_NEED_ASSERTS)

			if (API_VirtCh[i] != SBGC_RC_UNDEF)
				gSBGC->_api->writeWord(gSBGC, constrain_(API_VirtCh[i], SBGC_RC_MIN_VAL, SBGC_RC_MAX_VAL));

			else
				gSBGC->_api->writeWord(gSBGC, API_VirtCh[i]);

		#else
			gSBGC->_api->writeWord(gSBGC, API_VirtCh[i]);
		#endif
	}

	gSBGC->_api->finishWrite(gSBGC);
	/* No need confirmation */

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Sets the value of virtual channels in high resolution
 *
 *	####	TX —> CMD_API_VIRT_CH_HIGH_RES :		chQuan * 2 bytes
 *
 *	@code

			// Configure the first three API channels
			i16 API_VirtCh [3] = { SBGC_RC_MIN_VAL_HR, 1000, SBGC_RC_UNDEF_HR };

			SBGC32_SetAPI_VirtChHR_Control(&SBGC32_Device, API_VirtCh, countof_(API_VirtCh));

 *	@endcode
 *
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*API_VirtCh - -16384 --> 16384
 *			(SBGC_RC_MIN_VAL_HR --> SBGC_RC_MAX_VAL_HR).
 *			Array with written virtual channel values in
 *			high resolution. Special value -32768 (SBGC_RC_UNDEF_HR)
 *			sets channel to undefined state (input is ignored)
 *	@param	chQuan - number of virtual channels
 *			starting with API_VIRT_CH_1
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SetAPI_VirtChHR_Control (sbgcGeneral_t *gSBGC, const i16 *API_VirtCh, ui8 chQuan
													/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertParam(chQuan, 1, SBGC_VIRTUAL_CHANNELS_NUM)

	gSBGC->_api->startWrite(gSBGC, CMD_API_VIRT_CH_HIGH_RES SBGC_ADVANCED_ARGS__);

	for (ui8 i = 0; i< chQuan; i++)
	{
		#if (SBGC_NEED_ASSERTS)

			if (API_VirtCh[i] != SBGC_RC_UNDEF_HR)
				gSBGC->_api->writeWord(gSBGC, constrain_(API_VirtCh[i], SBGC_RC_MIN_VAL_HR, SBGC_RC_MAX_VAL_HR));

			else
				gSBGC->_api->writeWord(gSBGC, API_VirtCh[i]);

		#else
			gSBGC->_api->writeWord(gSBGC, API_VirtCh[i]);
		#endif
	}

	gSBGC->_api->finishWrite(gSBGC);
	/* No need confirmation */

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */

#endif /* SBGC_CONTROL_MODULE */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
