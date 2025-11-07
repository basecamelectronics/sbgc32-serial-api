/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2.1
 *
 *	@file		adjvar.c
 *
 *	@brief		Adjustable variables source file
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


#if (SBGC_ADJVAR_MODULE)

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						 Static Macros and Constants
 */
#if (SBGC_NEED_ASSERTS)
	#define	sbgcAssertAdjVar(av)			{ sbgcCommandStatus_t assertStatus = SerialAPI_AssertAdjVar(gSBGC, av);\
											  if (assertStatus != sbgcCOMMAND_OK) { gSBGC->_lastCommandStatus = assertStatus;\
											  return assertStatus; } }

	#define	sbgcAssertAdjVars(av, num)		{ sbgcCommandStatus_t assertStatus; for (ui8 i = 0; i < num; i++) {\
											  assertStatus = SerialAPI_AssertAdjVar(gSBGC, &av[i]); if (assertStatus != sbgcCOMMAND_OK)\
											  { gSBGC->_lastCommandStatus = assertStatus; return assertStatus; } } }
#else
	#define	sbgcAssertAdjVar(av)
	#define	sbgcAssertAdjVars(av, num)
#endif

#if	(SBGC_ADJ_VARS_NAMES)
	#define	ADJ_VAR_BLOCK_(av)		av, nameof_(av)
#else
	#define	ADJ_VAR_BLOCK_(av)		av
#endif


#if (SBGC_ADJ_VARS_REF_INFO)

	/**	@addtogroup	Adjvar
	 *	@{
	 */
	/**	@brief	Global adjustable variables auxiliary array
	 */
	sbgcAdjVarReferenceInfo_t adjVarsReferenceInfoArray [] =
	/*
	||                  ENUM ID + NAME                  ||   MIN   ||   MAX   ||
	 */
	{ {	ADJ_VAR_BLOCK_(ADJ_VAR_P_ROLL),						0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_P_PITCH),					0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_P_YAW),						0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_I_ROLL),						0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_I_PITCH),					0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_I_YAW),						0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_D_ROLL),						0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_D_PITCH),					0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_D_YAW),						0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_POWER_ROLL),					0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_POWER_PITCH),				0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_POWER_YAW),					0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_ACC_LIMITER),				0,			1275
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_SPEED_ROLL),			0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_SPEED_PITCH),			0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_SPEED_YAW),			0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_LPF_ROLL),			0,			15
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_LPF_PITCH),			0,			15
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_LPF_YAW),				0,			15
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_SPEED_ROLL),				0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_SPEED_PITCH),				0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_SPEED_YAW),				0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_LPF_ROLL),				0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_LPF_PITCH),				0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_LPF_YAW),					0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_TRIM_ROLL),				-127,		127
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_TRIM_PITCH),				-127,		127
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_TRIM_YAW),				-127,		127
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_DEADBAND),				0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_EXPO_RATE),				0,			100
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_PITCH),				0,			1
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_FOLLOW_YAW_PITCH),		0,			2
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_DEADBAND),			0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_EXPO_RATE),			0,			100
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_ROLL_MIX_START),		0,			90
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_ROLL_MIX_RANGE),		0,			90
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_GYRO_TRUST),					0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FRAME_HEADING_ANGLE),		-1800,		1800			// Note: Has a special value - 0x7FFF
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_GYRO_HEADING_CORR),			-20000,		20000
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_ACC_LIMITER_ROLL),			0,			10000
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_ACC_LIMITER_PITCH),			0,			10000
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_ACC_LIMITER_YAW),			0,			10000
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_PID_GAIN_ROLL),				0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_PID_GAIN_PITCH),				0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_PID_GAIN_YAW),				0,			255
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_LPF_FREQ_ROLL),				10,			400
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_LPF_FREQ_PITCH),				10,			400
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_LPF_FREQ_YAW),				10,			400
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_TIMELAPSE_TIME),				1,			3600
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_MAV_CTRL_MODE),				0,			2
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_H_CORR_FACTOR),				0,			255				// Frw. ver. 2.68b7+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SW_LIM_MIN_ROLL),			-3600,		3600			// Frw. ver. 2.68b8+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SW_LIM_MAX_ROLL),			-3600,		3600			// Frw. ver. 2.68b8+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SW_LIM_MIN_PITCH),			-3600,		3600			// Frw. ver. 2.68b8+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SW_LIM_MAX_PITCH),			-3600,		3600			// Frw. ver. 2.68b8+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SW_LIM_MIN_YAW),				-3600,		3600			// Frw. ver. 2.68b8+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SW_LIM_MAX_YAW),				-3600,		3600			// Frw. ver. 2.68b8+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_RANGE_ROLL),			0,			255				// Frw. ver. 2.68b9+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_RANGE_PITCH),			0,			255				// Frw. ver. 2.68b9+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_RANGE_YAW),			0,			255				// Frw. ver. 2.68b9+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_AUTO_PID_TARGET),			0,			255				// Frw. ver. 2.68b9+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_MODE_ROLL),				0,			255				// Frw. ver. 2.69b3+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_MODE_PITCH),				0,			255				// Frw. ver. 2.69b3+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_MODE_YAW),				0,			255				// Frw. ver. 2.69b3+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_EULER_ORDER),				0,			255				// Frw. ver. 2.69b3+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_FOLLOW_IN_DBAND),			0,			255				// Frw. ver. 2.70b4+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_LIMIT_MIN_ROLL),			-3600,		3600			// Frw. ver. 2.72b0+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_LIMIT_MAX_ROLL),			-3600,		3600			// Frw. ver. 2.72b0+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_LIMIT_MIN_PITCH),			-3600,		3600			// Frw. ver. 2.72b0+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_LIMIT_MAX_PITCH),			-3600,		3600			// Frw. ver. 2.72b0+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_LIMIT_MIN_YAW),			-3600,		3600			// Frw. ver. 2.72b0+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_LIMIT_MAX_YAW),			-3600,		3600			// Frw. ver. 2.72b0+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_DEADBAND_PITCH),			0,			255				// Frw. ver. 2.72b0+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_DEADBAND_YAW),			0,			255				// Frw. ver. 2.72b0+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_EXPO_RATE_PITCH),			0,			255				// Frw. ver. 2.72b0+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_RC_EXPO_RATE_YAW),			0,			255				// Frw. ver. 2.72b0+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SHAKE_AMP_ROLL),				0,			255				// Frw. ver. 2.73+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SHAKE_AMP_TILT),				0,			255				// Frw. ver. 2.73+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SHAKE_AMP_PAN),				0,			255				// Frw. ver. 2.73+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SHAKE_FREQ),					0,			255				// Frw. ver. 2.73+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SHAKE_FREQ_RANGE),			0,			100				// Frw. ver. 2.73+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SHAKE_PAUSE_PERIOD),			500,		5600			// Frw. ver. 2.73+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SHAKE_PAUSE_BALANCE),		0,			255				// Frw. ver. 2.73+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SHAKE_PAUSE_RANDOMNESS),		0,			100				// Frw. ver. 2.73+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SHAKE_RESONANCE_GAIN_ROLL),	0,			255				// Frw. ver. 2.73+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SHAKE_RESONANCE_GAIN_TILT),	0,			255				// Frw. ver. 2.73+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SHAKE_RESONANCE_GAIN_PAN),	0,			255				// Frw. ver. 2.73+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SHAKE_FREQ_SHIFT_ROLL),		-127,		127				// Frw. ver. 2.73+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SHAKE_FREQ_SHIFT_TILT),		-127,		127				// Frw. ver. 2.73+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SHAKE_FREQ_SHIFT_PAN),		-127,		127				// Frw. ver. 2.73+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SHAKE_MASTER_GAIN),			0,			255				// Frw. ver. 2.73+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_OUTER_P_ROLL),				0,			255				// Frw. ver. 2.73.7+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_OUTER_P_PITCH),				0,			255				// Frw. ver. 2.73.7+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_OUTER_P_YAW),				0,			255				// Frw. ver. 2.73.7+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_D_LPF_FREQ_ROLL),			0,			255				// Frw. ver. 2.73.7+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_D_LPF_FREQ_PITCH),			0,			255				// Frw. ver. 2.73.7+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_D_LPF_FREQ_YAW),				0,			255				// Frw. ver. 2.73.7+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_IMU_ANGLE_CORR_ROLL),		-1000,		1000			// Frw. ver. 2.73.8+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_IMU_ANGLE_CORR_PITCH),		-1000,		1000			// Frw. ver. 2.73.8+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SW_LIM_WIDTH_ROLL),			0,			255				// Frw. ver. 2.73.8+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SW_LIM_WIDTH_PITCH),			0,			255				// Frw. ver. 2.73.8+
	},{	ADJ_VAR_BLOCK_(ADJ_VAR_SW_LIM_WIDTH_YAW),			0,			255				// Frw. ver. 2.73.8+

	}};
	/**	@}
	 */

#endif

#if (SBGC_USES_REF_INFO)

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *					Big Endian Mapping and Reference Info Structures
	 */
	/**	@addtogroup	Adjvar_Configs
	 *	@{
	 */
	/**	@brief	Sample reference info
	 */
	const sbgcParameterReferenceInfo_t adjVarsCfgReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Trigger Src Ch [SLOT0]",	sbgcUCHAR						),  // 0
		PARAM_BLOCK_(	"Analog Slot [SLOT0]",		sbgcUCHAR						),  // 1
		PARAM_BLOCK_(	"Trigger Src Ch [SLOT1]",	sbgcUCHAR						),  // 2
		PARAM_BLOCK_(	"Analog Slot [SLOT1]",		sbgcUCHAR						),  // 3
		PARAM_BLOCK_(	"Trigger Src Ch [SLOT2]",	sbgcUCHAR						),  // 4
		PARAM_BLOCK_(	"Analog Slot [SLOT2]",		sbgcUCHAR						),  // 5
		PARAM_BLOCK_(	"Trigger Src Ch [SLOT3]",	sbgcUCHAR						),  // 6
		PARAM_BLOCK_(	"Analog Slot [SLOT3]",		sbgcUCHAR						),  // 7
		PARAM_BLOCK_(	"Trigger Src Ch [SLOT4]",	sbgcUCHAR						),  // 8
		PARAM_BLOCK_(	"Analog Slot [SLOT4]",		sbgcUCHAR						),  // 9
		PARAM_BLOCK_(	"Trigger Src Ch [SLOT5]",	sbgcUCHAR						),  // 10
		PARAM_BLOCK_(	"Analog Slot [SLOT5]",		sbgcUCHAR						),  // 11
		PARAM_BLOCK_(	"Trigger Src Ch [SLOT6]",	sbgcUCHAR						),  // 12
		PARAM_BLOCK_(	"Analog Slot [SLOT6]",		sbgcUCHAR						),  // 13
		PARAM_BLOCK_(	"Trigger Src Ch [SLOT7]",	sbgcUCHAR						),  // 14
		PARAM_BLOCK_(	"Analog Slot [SLOT7]",		sbgcUCHAR						),  // 15
		PARAM_BLOCK_(	"Trigger Src Ch [SLOT8]",	sbgcUCHAR						),  // 16
		PARAM_BLOCK_(	"Analog Slot [SLOT8]",		sbgcUCHAR						),  // 17
		PARAM_BLOCK_(	"Trigger Src Ch [SLOT9]",	sbgcUCHAR						),  // 18
		PARAM_BLOCK_(	"Analog Slot [SLOT9]",		sbgcUCHAR						),  // 19
		PARAM_BLOCK_(	"Analog Src [SLOT0]",		sbgcUCHAR						),  // 20
		PARAM_BLOCK_(	"Var ID [SLOT0]",			sbgcUCHAR						),  // 21
		PARAM_BLOCK_(	"Min Val [SLOT0]",			sbgcUCHAR						),  // 22
		PARAM_BLOCK_(	"Max Val [SLOT0]",			sbgcUCHAR						),  // 23
		PARAM_BLOCK_(	"Analog Src [SLOT1]",		sbgcUCHAR						),  // 24
		PARAM_BLOCK_(	"Var ID [SLOT1]",			sbgcUCHAR						),  // 25
		PARAM_BLOCK_(	"Min Val [SLOT1]",			sbgcUCHAR						),  // 26
		PARAM_BLOCK_(	"Max Val [SLOT1]",			sbgcUCHAR						),  // 27
		PARAM_BLOCK_(	"Analog Src [SLOT2]",		sbgcUCHAR						),  // 28
		PARAM_BLOCK_(	"Var ID [SLOT2]",			sbgcUCHAR						),  // 29
		PARAM_BLOCK_(	"Min Val [SLOT2]",			sbgcUCHAR						),  // 30
		PARAM_BLOCK_(	"Max Val [SLOT2]",			sbgcUCHAR						),  // 31
		PARAM_BLOCK_(	"Analog Src [SLOT3]",		sbgcUCHAR						),  // 32
		PARAM_BLOCK_(	"Var ID [SLOT3]",			sbgcUCHAR						),  // 33
		PARAM_BLOCK_(	"Min Val [SLOT3]",			sbgcUCHAR						),  // 34
		PARAM_BLOCK_(	"Max Val [SLOT3]",			sbgcUCHAR						),  // 35
		PARAM_BLOCK_(	"Analog Src [SLOT4]",		sbgcUCHAR						),  // 36
		PARAM_BLOCK_(	"Var ID [SLOT4]",			sbgcUCHAR						),  // 37
		PARAM_BLOCK_(	"Min Val [SLOT4]",			sbgcUCHAR						),  // 38
		PARAM_BLOCK_(	"Max Val [SLOT4]",			sbgcUCHAR						),  // 39
		PARAM_BLOCK_(	"Analog Src [SLOT5]",		sbgcUCHAR						),  // 40
		PARAM_BLOCK_(	"Var ID [SLOT5]",			sbgcUCHAR						),  // 41
		PARAM_BLOCK_(	"Min Val [SLOT5]",			sbgcUCHAR						),  // 42
		PARAM_BLOCK_(	"Max Val [SLOT5]",			sbgcUCHAR						),  // 43
		PARAM_BLOCK_(	"Analog Src [SLOT6]",		sbgcUCHAR						),  // 44
		PARAM_BLOCK_(	"Var ID [SLOT6]",			sbgcUCHAR						),  // 45
		PARAM_BLOCK_(	"Min Val [SLOT6]",			sbgcUCHAR						),  // 46
		PARAM_BLOCK_(	"Max Val [SLOT6]",			sbgcUCHAR						),  // 47
		PARAM_BLOCK_(	"Analog Src [SLOT7]",		sbgcUCHAR						),  // 48
		PARAM_BLOCK_(	"Var ID [SLOT7]",			sbgcUCHAR						),  // 49
		PARAM_BLOCK_(	"Min Val [SLOT7]",			sbgcUCHAR						),  // 50
		PARAM_BLOCK_(	"Max Val [SLOT7]",			sbgcUCHAR						),  // 51
		PARAM_BLOCK_(	"Analog Src [SLOT8]",		sbgcUCHAR						),  // 52
		PARAM_BLOCK_(	"Var ID [SLOT8]",			sbgcUCHAR						),  // 53
		PARAM_BLOCK_(	"Min Val [SLOT8]",			sbgcUCHAR						),  // 54
		PARAM_BLOCK_(	"Max Val [SLOT8]",			sbgcUCHAR						),  // 55
		PARAM_BLOCK_(	"Analog Src [SLOT9]",		sbgcUCHAR						),  // 56
		PARAM_BLOCK_(	"Var ID [SLOT9]",			sbgcUCHAR						),  // 57
		PARAM_BLOCK_(	"Min Val [SLOT9]",			sbgcUCHAR						),  // 58
		PARAM_BLOCK_(	"Max Val [SLOT9]",			sbgcUCHAR						),  // 59
		PARAM_BLOCK_(	"Analog Src [SLOT10]",		sbgcUCHAR						),  // 60
		PARAM_BLOCK_(	"Var ID [SLOT10]",			sbgcUCHAR						),  // 61
		PARAM_BLOCK_(	"Min Val [SLOT10]",			sbgcUCHAR						),  // 62
		PARAM_BLOCK_(	"Max Val [SLOT10]",			sbgcUCHAR						),  // 63
		PARAM_BLOCK_(	"Analog Src [SLOT11]",		sbgcUCHAR						),  // 64
		PARAM_BLOCK_(	"Var ID [SLOT11]",			sbgcUCHAR						),  // 65
		PARAM_BLOCK_(	"Min Val [SLOT11]",			sbgcUCHAR						),  // 66
		PARAM_BLOCK_(	"Max Val [SLOT11]",			sbgcUCHAR						),  // 67
		PARAM_BLOCK_(	"Analog Src [SLOT12]",		sbgcUCHAR						),  // 68
		PARAM_BLOCK_(	"Var ID [SLOT12]",			sbgcUCHAR						),  // 69
		PARAM_BLOCK_(	"Min Val [SLOT12]",			sbgcUCHAR						),  // 70
		PARAM_BLOCK_(	"Max Val [SLOT12]",			sbgcUCHAR						),  // 71
		PARAM_BLOCK_(	"Analog Src [SLOT13]",		sbgcUCHAR						),  // 72
		PARAM_BLOCK_(	"Var ID [SLOT13]",			sbgcUCHAR						),  // 73
		PARAM_BLOCK_(	"Min Val [SLOT13]",			sbgcUCHAR						),  // 74
		PARAM_BLOCK_(	"Max Val [SLOT13]",			sbgcUCHAR						),  // 75
		PARAM_BLOCK_(	"Analog Src [SLOT14]",		sbgcUCHAR						),  // 76
		PARAM_BLOCK_(	"Var ID [SLOT14]",			sbgcUCHAR						),  // 77
		PARAM_BLOCK_(	"Min Val [SLOT14]",			sbgcUCHAR						),  // 78
		PARAM_BLOCK_(	"Max Val [SLOT14]",			sbgcUCHAR						),  // 79

	};

	const ui8 adjVarsCfgReferenceInfoArrayElCnt = countof_(adjVarsCfgReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Adjvar_State
	 *	@{
	 */
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t adjVarsStateOldTxReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Trigger Slot (old)",		sbgcUCHAR						),  // 0
		PARAM_BLOCK_(	"Analog Slot",				sbgcUCHAR						),  // 1

	};

	const ui8 adjVarsStateOldTxReferenceInfoArrayElCnt = countof_(adjVarsStateOldTxReferenceInfoArray);


	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t adjVarsStateOldRxReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Trigger RC Data (old)",	sbgcSHORT						),  // 0
		PARAM_BLOCK_(	"Trigger Action (old)",		sbgcUCHAR						),  // 1
		PARAM_BLOCK_(	"Analog RC Data",			sbgcSHORT						),  // 2
		PARAM_BLOCK_(	"Analog Value",				sbgcINT							),  // 3
		PARAMS_BLOCK_(	"Reserved",					sbgcRCHAR,					6	),  // 4

	};

	const ui8 adjVarsStateOldRxReferenceInfoArrayElCnt = countof_(adjVarsStateOldRxReferenceInfoArray);


	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t adjVarsStateTxReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Trigger Slot",				sbgcUCHAR						),  // 0
		PARAM_BLOCK_(	"Analog Src ID",			sbgcUSHORT						),  // 1
		PARAM_BLOCK_(	"Analog Var ID",			sbgcUCHAR						),  // 2
		PARAM_BLOCK_(	"Lut Src ID",				sbgcUSHORT						),  // 3
		PARAM_BLOCK_(	"Lut Var ID",				sbgcUCHAR						),  // 4

	};

	const ui8 adjVarsStateTxReferenceInfoArrayElCnt = countof_(adjVarsStateTxReferenceInfoArray);


	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t adjVarsStateRxReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Trigger RC Data",			sbgcSHORT						),  // 0
		PARAM_BLOCK_(	"Trigger Action",			sbgcUCHAR						),  // 1
		PARAM_BLOCK_(	"Analog Src Value",			sbgcSHORT						),  // 2
		PARAM_BLOCK_(	"Analog Var Value",			sbgcFLOAT						),  // 3
		PARAM_BLOCK_(	"Lut Src Value",			sbgcSHORT						),  // 4
		PARAM_BLOCK_(	"Lut Var Value",			sbgcFLOAT						),  // 5

	};

	const ui8 adjVarsStateRxReferenceInfoArrayElCnt = countof_(adjVarsStateRxReferenceInfoArray);
	/**	@}
	 */

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	Adjvar
 *	@{
 */
#if (SBGC_NEED_ASSERTS)

	/**	@brief	Checks the presence of an adjustable variable
	 *			in the current firmware version
	 *
	 *	@note	Private function
	 *
	 *	@param	*gSBGC - serial connection descriptor
	 *	@param	*adjVarGeneral - general adjustable variables structure
	 *
	 *	@return	Assert status
	 */
	static sbgcCommandStatus_t SerialAPI_AssertAdjVar (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral)
	{
		/* Fast checking */
		if ((gSBGC->_api->baseFirmwareVersion >= 2738) || (adjVarGeneral->ID < ADJ_VAR_MAV_CTRL_MODE))
			return sbgcCOMMAND_OK;

		/* Check the firmware limitations */
		if (((gSBGC->_api->baseFirmwareVersion < 2687) && (adjVarGeneral->ID >= ADJ_VAR_MAV_CTRL_MODE)) ||
			((gSBGC->_api->baseFirmwareVersion < 2688) && (adjVarGeneral->ID >= ADJ_VAR_SW_LIM_MIN_ROLL)) ||
			((gSBGC->_api->baseFirmwareVersion < 2689) && (adjVarGeneral->ID >= ADJ_VAR_FOLLOW_RANGE_ROLL)) ||
			((gSBGC->_api->baseFirmwareVersion < 2693) && (adjVarGeneral->ID >= ADJ_VAR_RC_MODE_ROLL)) ||
			((gSBGC->_api->baseFirmwareVersion < 2704) && (adjVarGeneral->ID >= ADJ_VAR_FOLLOW_IN_DBAND)) ||
			((gSBGC->_api->baseFirmwareVersion < 2720) && (adjVarGeneral->ID >= ADJ_VAR_RC_LIMIT_MIN_ROLL)) ||
			((gSBGC->_api->baseFirmwareVersion < 2730) && (adjVarGeneral->ID >= ADJ_VAR_SHAKE_AMP_ROLL)) ||
			((gSBGC->_api->baseFirmwareVersion < 2737) && (adjVarGeneral->ID >= ADJ_VAR_OUTER_P_ROLL)) ||
			((gSBGC->_api->baseFirmwareVersion < 2738) && (adjVarGeneral->ID >= ADJ_VAR_IMU_ANGLE_CORR_ROLL)))
			return sbgcCOMMAND_NOT_SUPPORTED_BY_FIRMWARE;

		/* Check that this board supports the shake generator option */
		if ((adjVarGeneral->ID >= ADJ_VAR_SHAKE_AMP_ROLL && adjVarGeneral->ID <= ADJ_VAR_SHAKE_MASTER_GAIN) &&
			(!(gSBGC->_api->boardFeatures2 & BFE2_SHAKE_GENERATOR)))
			return sbgcCOMMAND_NOT_SUPPORTED_FEATURE;

		return sbgcCOMMAND_OK;
	}

#endif


#if (SBGC_ADJ_VARS_REF_INFO)

	/**	@brief	Automatically initializes adjustable variable
	 *
	 *	@param	*adjVarGeneral - general adjustable variables structure
	 *	@param	ID - adjustable variable identifier
	 */
	void SerialAPI_InitAdjVar (sbgcAdjVarGeneral_t *adjVarGeneral, sbgcAdjVarID_t ID)
	{
		memset(adjVarGeneral, 0, sizeof(sbgcAdjVarGeneral_t));

		adjVarGeneral->ID = ID;

		#if (SBGC_ADJ_VARS_NAMES)
			adjVarGeneral->name = adjVarsReferenceInfoArray[ID].name;
		#endif

		adjVarGeneral->minValue = (i16)adjVarsReferenceInfoArray[ID].minValue;
		adjVarGeneral->maxValue = (i16)adjVarsReferenceInfoArray[ID].maxValue;

		adjVarGeneral->syncFlag = AV_NOT_SYNCHRONIZED;
	}

	/**	@brief	Automatically initializes all adjustable variables
	 *
	 *	@note	adjVarGeneral array must includes all used
	 *			adjustable variables, defined by firmware
	 *			version or manually by user
	 *
	 *	@param	*gSBGC - serial connection descriptor
	 *	@param	*adjVarGeneral - general adjustable
	 *			variables structure
	 */
	void SerialAPI_InitAllAdjVars (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral)
	{
		for (ui8 i = 0; i < gSBGC->_api->adjVarsNumber; i++)
			SerialAPI_InitAdjVar(&adjVarGeneral[i], (sbgcAdjVarID_t)i);
	}

#endif


/**	@brief	Finds adjustable variable by its ID
 *
 *	@attention	This function works in whole range of adjustable
 *				variables. If a variable isn't found, the search
 *				will continue until the maximum available
 *				number of adjustable variables for
 *				the current firmware is reached.
 *				See serialAPI_General_t.adjVarsNumber field
 *				for additional information
 *
 *	@code

			// Retrieve a pointer to the required variable from the global array
			sbgcAdjVarGeneral_t *adjVarP_Roll = SerialAPI_FindAdjVarByID(&SBGC32_Device, AdjVarGeneral, ADJ_VAR_P_ROLL);

			// where AdjVarGeneral is a global array that includes all adjustable variables

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*adjVarGeneral - general adjustable variables structure
 *	@param	ID - adjustable variable identifier
 *
 *	@return	Pointer to sbgcAdjVarGeneral_t structure
 */
sbgcAdjVarGeneral_t *SerialAPI_FindAdjVarByID (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral, sbgcAdjVarID_t ID)
{
	#if (SBGC_NEED_ASSERTS)
		if (ID > (gSBGC->_api->adjVarsNumber - 1)) return NULL;
	#endif

	for (ui8 i = 0; i < gSBGC->_api->adjVarsNumber; i++)
		if (adjVarGeneral[i].ID == ID)
			return &adjVarGeneral[i];

	return NULL;
}
/**	@}
 */


/**	@addtogroup	Adjvar_Values
 *	@{
 */
/**	@brief	Changes the value of adjustable variable as int32
 *
 *	@pre	sbgcAdjVarGeneral_t.ID field must be filled
 *
 *	@note	Only use this function to change
 *			the adjustable variable values
 *
 *	@code

			#define ADJ_VAR_P_ROLL_INIT_VALUE 100
			#define ADJ_VAR_P_ROLL_NEW_VALUE 200

			sbgcAdjVarGeneral_t AdjVarP_Roll = { 0 };

			#if (SBGC_ADJ_VARS_REF_INFO)
				SerialAPI_InitAdjVar(&AdjVarP_Roll, ADJ_VAR_P_ROLL);

			#else

				// Method to manually initialize an adjustable variable
				AdjVarP_Roll.ID = ADJ_VAR_P_ROLL;
				AdjVarP_Roll.minValue = 0;
				AdjVarP_Roll.maxValue = 255;

			#endif

			SerialAPI_EditAdjVarValue(&AdjVarP_Roll, ADJ_VAR_P_ROLL_INIT_VALUE);

			// ...
			// Further edit adjustable variable value
			SerialAPI_EditAdjVarValue(&AdjVarP_Roll, ADJ_VAR_P_ROLL_NEW_VALUE);

 *	@endcode
 *
 *	@param	*adjVarGeneral - general adjustable variables structure
 *	@param	value - new value of adjustable variable
 */
void SerialAPI_EditAdjVarValue (sbgcAdjVarGeneral_t *adjVarGeneral, i32 value)
{
	#if (SBGC_NEED_ASSERTS)

		if (adjVarGeneral->value == value)
			return;

		/* Values' borders checking */
		value = constrain_(value, adjVarGeneral->minValue, adjVarGeneral->maxValue);

	#endif

	adjVarGeneral->value = value;
	adjVarGeneral->syncFlag = AV_NOT_SYNCHRONIZED;
}


/**	@brief	Changes the value of adjustable variable as float
 *
 *	@pre	sbgcAdjVarGeneral_t.ID field must be filled
 *
 *	@note	Only use this function to change
 *			the adjustable variable values
 *
 *	@code

			#define ADJ_VAR_P_ROLL_INIT_VALUE 1.61F
			#define ADJ_VAR_P_ROLL_NEW_VALUE 1.75F

			sbgcAdjVarGeneral_t AdjVarP_Roll = { 0 };

			#if (SBGC_ADJ_VARS_REF_INFO)
				SerialAPI_InitAdjVar(&AdjVarP_Roll, ADJ_VAR_P_ROLL);

			#else

				// Method to manually initialize an adjustable variable
				AdjVarP_Roll.ID = ADJ_VAR_P_ROLL;
				AdjVarP_Roll.minValue = 0;
				AdjVarP_Roll.maxValue = 255;

			#endif

			SerialAPI_EditAdjVarValueFloat(&AdjVarP_Roll, ADJ_VAR_P_ROLL_INIT_VALUE);

			// ...
			// Further edit adjustable variable value
			SerialAPI_EditAdjVarValueFloat(&AdjVarP_Roll, ADJ_VAR_P_ROLL_NEW_VALUE);

 *	@endcode
 *
 *	@param	*adjVarGeneral - general adjustable variables structure
 *	@param	value - new value of adjustable variable
 */
void SerialAPI_EditAdjVarValueFloat (sbgcAdjVarGeneral_t *adjVarGeneral, float value)
{
	#if (SBGC_NEED_ASSERTS)

		if (adjVarGeneral->value_f == value)
			return;

		/* Values' borders checking */
		float minValue = adjVarGeneral->minValue;
		float maxValue = adjVarGeneral->maxValue;

		value = constrain_(value, minValue, maxValue);

	#endif

	adjVarGeneral->value_f = value;
	adjVarGeneral->syncFlag = AV_NOT_SYNCHRONIZED;
}


/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_SetAdjVarValue function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostSetAdjVarValue (sbgcGeneral_t *gSBGC)
{
	sbgcAdjVarGeneral_t *adjVarGeneral = (sbgcAdjVarGeneral_t*)curCmdDest_;

	adjVarGeneral->syncFlag = AV_SYNCHRONIZED;
	adjVarGeneral->saveFlag = AV_NOT_SAVED;
}


/**	@brief	Sets a new value for the adjustable variable
 *
 *	####	TX —> CMD_SET_ADJ_VARS_VAL :	6 bytes
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@pre	sbgcAdjVarGeneral_t.ID and sbgcAdjVarGeneral_t.value
 *			fields must be filled
 *
 *	@code

			#define ADJ_VAR_P_ROLL_INIT_VALUE 100
			#define ADJ_VAR_P_ROLL_NEW_VALUE 200

			sbgcAdjVarGeneral_t AdjVarP_Roll = { 0 };

			// Initialize adjustable variable
			#if (SBGC_ADJ_VARS_REF_INFO)
				SerialAPI_InitAdjVar(&AdjVarP_Roll, ADJ_VAR_P_ROLL);
			#else
				AdjVarP_Roll.ID = ADJ_VAR_P_ROLL;
			#endif

			SerialAPI_EditAdjVarValue(&AdjVarP_Roll, ADJ_VAR_P_ROLL_INIT_VALUE);

			// Set initial value
			SBGC32_SetAdjVarValue(&SBGC32_Device, &AdjVarP_Roll, SBGC_NO_CONFIRM);

			// ...
			// Edit and set a new value
			SerialAPI_EditAdjVarValue(&AdjVarP_Roll, ADJ_VAR_P_ROLL_NEW_VALUE);

			SBGC32_SetAdjVarValue(&SBGC32_Device, &AdjVarP_Roll, SBGC_NO_CONFIRM);

			// And save the adjustable variable to EEPROM if needed
			SBGC32_SaveAdjVarToEEPROM(&SBGC32_Device, &AdjVarP_Roll, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*adjVarGeneral - general adjustable variables structure
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SetAdjVarValue (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral, sbgcConfirm_t *confirm
										   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertAdjVar(adjVarGeneral)

	#if (SBGC_NEED_ASSERTS)
		if (adjVarGeneral->syncFlag == AV_SYNCHRONIZED) return sbgcCOMMAND_NOTHING_TO_CHANGE;
	#endif

	gSBGC->_api->startWrite(gSBGC, CMD_SET_ADJ_VARS_VAL SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, 1);
	gSBGC->_api->writeByte(gSBGC, adjVarGeneral->ID);
	gSBGC->_api->writeLong(gSBGC, adjVarGeneral->value);
	gSBGC->_api->assignEvent(gSBGC, PostSetAdjVarValue, adjVarGeneral, sizeof(sbgcAdjVarGeneral_t));
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_SET_ADJ_VARS_VAL SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Sets a new float value for the adjustable variable
 *
 *	####	TX —> CMD_SET_ADJ_VARS_VAL :	6 bytes
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@pre	sbgcAdjVarGeneral_t.ID and sbgcAdjVarGeneral_t.value
 *			fields must be filled
 *
 *	@attention	Firmware: 2.73.4+
 *
 *	@code

			#define ADJ_VAR_P_ROLL_INIT_VALUE 1.61F
			#define ADJ_VAR_P_ROLL_NEW_VALUE 1.75F

			sbgcAdjVarGeneral_t AdjVarP_Roll = { 0 };

			// Initialize adjustable variable
			#if (SBGC_ADJ_VARS_REF_INFO)
				SerialAPI_InitAdjVar(&AdjVarP_Roll, ADJ_VAR_P_ROLL);
			#else
				AdjVarP_Roll.ID = ADJ_VAR_P_ROLL;
			#endif

			SerialAPI_EditAdjVarValueFloat(&AdjVarP_Roll, ADJ_VAR_P_ROLL_INIT_VALUE);

			// Set initial value
			SBGC32_SetAdjVarValueFloat(&SBGC32_Device, &AdjVarP_Roll, SBGC_NO_CONFIRM);

			// ...
			// Edit and set a new value
			SerialAPI_EditAdjVarValueFloat(&AdjVarP_Roll, ADJ_VAR_P_ROLL_NEW_VALUE);

			SBGC32_SetAdjVarValueFloat(&SBGC32_Device, &AdjVarP_Roll, SBGC_NO_CONFIRM);

			// And save the adjustable variable to EEPROM if needed
			SBGC32_SaveAdjVarToEEPROM(&SBGC32_Device, &AdjVarP_Roll, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*adjVarGeneral - general adjustable variables structure
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SetAdjVarValueFloat (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral, sbgcConfirm_t *confirm
												/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2734)
	sbgcAssertAdjVar(adjVarGeneral)

	#if (SBGC_NEED_ASSERTS)
		if (adjVarGeneral->syncFlag == AV_SYNCHRONIZED) return sbgcCOMMAND_NOTHING_TO_CHANGE;
	#endif

	gSBGC->_api->startWrite(gSBGC, CMD_SET_ADJ_VARS_VAL_F SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, 1);
	gSBGC->_api->writeByte(gSBGC, adjVarGeneral->ID);
	gSBGC->_api->writeLong(gSBGC, adjVarGeneral->value_f);
	gSBGC->_api->assignEvent(gSBGC, PostSetAdjVarValue, adjVarGeneral, sizeof(sbgcAdjVarGeneral_t));
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_SET_ADJ_VARS_VAL_F SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_SetAdjVarValues function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostSetAdjVarValues (sbgcGeneral_t *gSBGC)
{
	sbgcAdjVarGeneral_t *adjVarGeneral = (sbgcAdjVarGeneral_t*)curCmdDest_;

	ui8 adjVarQuan = gSBGC->_api->readByte(gSBGC);

	if (curCmd_->_destinationSize < (sizeof(sbgcAdjVarGeneral_t) * adjVarQuan))
		SerialAPI_FatalErrorHandler();

	for (ui8 i = 0; i < adjVarQuan; i++)
	{
		adjVarGeneral[i].syncFlag = AV_SYNCHRONIZED;
		adjVarGeneral[i].saveFlag = AV_NOT_SAVED;
	}
}

/**	@brief	Sets new values for a set of adjustable variables
 *
 *	####	TX —> CMD_SET_ADJ_VARS_VAL :	1 + (adjVarQuan * 5) bytes
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@pre	sbgcAdjVarGeneral_t.ID and sbgcAdjVarGeneral_t.value
 *			fields must be filled
 *
 *	@attention	adjVarQuan should not exceed
 *				SBGC_ADJ_VARS_MAX_NUM_PACKET (40)
 *
 *	@code

			#define	ADJ_VARS_NUMBER	9
			#define ADJ_VARS_EXAMPLE_INIT_VALUE 100
			#define ADJ_VAR_EXAMPLE_NEW_VALUE 200

			sbgcAdjVarGeneral_t AdjVarGeneral [ADJ_VARS_NUMBER];

			for (ui8 i = 0; i < ADJ_VARS_NUMBER; i++)
			// Initialize adjustable variables
			{
				#if (SBGC_ADJ_VARS_REF_INFO)
					SerialAPI_InitAdjVar(&AdjVarGeneral[i], (sbgcAdjVarID_t)i);
				#else
					AdjVarGeneral[i].ID = (sbgcAdjVarID_t)i;
				#endif

				SerialAPI_EditAdjVarValue(&AdjVarGeneral[i], ADJ_VARS_EXAMPLE_INIT_VALUE);
			}

			// Set initial values
			SBGC32_SetAdjVarValues(&SBGC32_Device, AdjVarGeneral, ADJ_VARS_NUMBER, SBGC_NO_CONFIRM);

			SerialAPI_EditAdjVarValue(&AdjVarGeneral[0], ADJ_VAR_EXAMPLE_NEW_VALUE);
			AdjVarGeneral[1].value = ADJ_VAR_EXAMPLE_NEW_VALUE;  // Incorrect assignment
			SerialAPI_EditAdjVarValue(&AdjVarGeneral[2], ADJ_VAR_EXAMPLE_NEW_VALUE);

			// The function will skip AdjVarGeneral[1]. Update only [0] and [2] variables' value
			SBGC32_SetAdjVarValues(&SBGC32_Device, AdjVarGeneral, 3, SBGC_NO_CONFIRM);

			// And save the adjustable variables to EEPROM if needed
			// Only the changed variables will be saved
			SBGC32_SaveAdjVarsToEEPROM(&SBGC32_Device, AdjVarGeneral, ADJ_VARS_NUMBER, SBGC_NO_CONFIRM);

			// Or use this function to automatically save the active adjustable variables
			if (SBGC32_SaveAllActiveAdjVarsToEEPROM(&SBGC32_Device, SBGC_NO_CONFIRM) == sbgcCOMMAND_OK)
			{
				// Manual setting of the save flag
				for (ui8 i = 0; i < ADJ_VARS_NUMBER; i++)
					AdjVarGeneral[i].saveFlag = AV_SAVED;
			}

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*adjVarGeneral - general adjustable variables structure
 *	@param	adjVarQuan - number of adjustable variables
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SetAdjVarValues (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral, ui8 adjVarQuan, sbgcConfirm_t *confirm
											/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertAdjVars(adjVarGeneral, adjVarQuan)
	sbgcAssertParam(adjVarQuan, 1, SBGC_ADJ_VARS_MAX_NUM_PACKET)

	ui8 numParams = 0;

	for (ui8 i = 0; i < adjVarQuan; i++)
		if (adjVarGeneral[i].syncFlag == AV_NOT_SYNCHRONIZED)
			numParams++;

	#if (SBGC_NEED_ASSERTS)
        if (numParams == 0) return sbgcCOMMAND_PARAM_ASSERT_ERROR;
	#endif

	gSBGC->_api->startWrite(gSBGC, CMD_SET_ADJ_VARS_VAL SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, numParams);

	for (ui8 i = 0; i < adjVarQuan; i++)
		if (adjVarGeneral[i].syncFlag == AV_NOT_SYNCHRONIZED)
		{
			gSBGC->_api->writeByte(gSBGC, adjVarGeneral[i].ID);
			gSBGC->_api->writeLong(gSBGC, adjVarGeneral[i].value);
		}

	gSBGC->_api->assignEvent(gSBGC, PostSetAdjVarValues, adjVarGeneral, sizeof(sbgcAdjVarGeneral_t) * adjVarQuan);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_SET_ADJ_VARS_VAL SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}

/**	@brief	Sets new float values for a set of adjustable variables
 *
 *	####	TX —> CMD_SET_ADJ_VARS_VAL :	1 + (adjVarQuan * 5) bytes
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@pre	sbgcAdjVarGeneral_t.ID and sbgcAdjVarGeneral_t.value
 *			fields must be filled
 *
 *	@attention	Firmware: 2.73.4+
 *
 *	@attention	adjVarQuan should not exceed
 *				SBGC_ADJ_VARS_MAX_NUM_PACKET (40)
 *
 *	@code

			#define	ADJ_VARS_NUMBER	9
			#define ADJ_VARS_EXAMPLE_INIT_VALUE 1.61F
			#define ADJ_VAR_EXAMPLE_NEW_VALUE 1.75F

			sbgcAdjVarGeneral_t AdjVarGeneral [ADJ_VARS_NUMBER];

			for (ui8 i = 0; i < ADJ_VARS_NUMBER; i++)
			// Initialize adjustable variables
			{
				#if (SBGC_ADJ_VARS_REF_INFO)
					SerialAPI_InitAdjVar(&AdjVarGeneral[i], (sbgcAdjVarID_t)i);
				#else
					AdjVarGeneral[i].ID = (sbgcAdjVarID_t)i;
				#endif

				SerialAPI_EditAdjVarValueFloat(&AdjVarGeneral[i], ADJ_VARS_EXAMPLE_INIT_VALUE);
			}

			// Set initial values
			SBGC32_SetAdjVarValuesFloat(&SBGC32_Device, AdjVarGeneral, ADJ_VARS_NUMBER, SBGC_NO_CONFIRM);

			SerialAPI_EditAdjVarValueFloat(&AdjVarGeneral[0], ADJ_VAR_EXAMPLE_NEW_VALUE);
			AdjVarGeneral[1].value = ADJ_VAR_EXAMPLE_NEW_VALUE;  // Incorrect assignment
			SerialAPI_EditAdjVarValueFloat(&AdjVarGeneral[2], ADJ_VAR_EXAMPLE_NEW_VALUE);

			// The function will skip AdjVarGeneral[1]. Update only [0] and [2] variables' value
			SBGC32_SetAdjVarValuesFloat(&SBGC32_Device, AdjVarGeneral, 3, SBGC_NO_CONFIRM);

			// And save the adjustable variables to EEPROM if needed
			// Only the changed variables will be saved
			SBGC32_SaveAdjVarsToEEPROM(&SBGC32_Device, AdjVarGeneral, ADJ_VARS_NUMBER, SBGC_NO_CONFIRM);

			// Or use this function to automatically save the active adjustable variables
			if (SBGC32_SaveAllActiveAdjVarsToEEPROM(&SBGC32_Device, SBGC_NO_CONFIRM) == sbgcCOMMAND_OK)
			{
				// Manual setting of the save flag
				for (ui8 i = 0; i < ADJ_VARS_NUMBER; i++)
					AdjVarGeneral[i].saveFlag = AV_SAVED;
			}

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*adjVarGeneral - general adjustable variables structure
 *	@param	adjVarQuan - number of adjustable variables
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SetAdjVarValuesFloat (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral, ui8 adjVarQuan, sbgcConfirm_t *confirm
												 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2734)
	sbgcAssertAdjVars(adjVarGeneral, adjVarQuan)
	sbgcAssertParam(adjVarQuan, 1, SBGC_ADJ_VARS_MAX_NUM_PACKET)

	ui8 numParams = 0;

	for (ui8 i = 0; i < adjVarQuan; i++)
		if (adjVarGeneral[i].syncFlag == AV_NOT_SYNCHRONIZED)
			numParams++;

	#if (SBGC_NEED_ASSERTS)
        if (numParams == 0) return sbgcCOMMAND_PARAM_ASSERT_ERROR;
	#endif

	gSBGC->_api->startWrite(gSBGC, CMD_SET_ADJ_VARS_VAL_F SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, numParams);

	for (ui8 i = 0; i < adjVarQuan; i++)
		if (adjVarGeneral[i].syncFlag == AV_NOT_SYNCHRONIZED)
		{
			ui32 float_;

			memcpy(&float_, &adjVarGeneral[i].value_f, sizeof(float_));

			gSBGC->_api->writeByte(gSBGC, adjVarGeneral[i].ID);
			gSBGC->_api->writeLong(gSBGC, float_);
		}

	gSBGC->_api->assignEvent(gSBGC, PostSetAdjVarValues, adjVarGeneral, sizeof(sbgcAdjVarGeneral_t) * adjVarQuan);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_SET_ADJ_VARS_VAL_F SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_GetAdjVarValue and
 *			@ref SBGC32_GetAdjVarValueFloat
 *			functions
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostGetAdjVarValue (sbgcGeneral_t *gSBGC)
{
	sbgcAdjVarGeneral_t *adjVarGeneral = (sbgcAdjVarGeneral_t*)curCmdDest_;

	(void)gSBGC->_api->readByte(gSBGC);

	#if (SBGC_NEED_ASSERTS)
		if (adjVarGeneral->ID == gSBGC->_api->readByte(gSBGC)) return;
	#else
		(void)gSBGC->_api->readByte(gSBGC);
	#endif

	if (curCmd_->_commandID == CMD_SET_ADJ_VARS_VAL)
		adjVarGeneral->value = (i32)gSBGC->_api->readLong(gSBGC);

	else
	{
		ui32 float_ = gSBGC->_api->readLong(gSBGC);
		memcpy(&adjVarGeneral->value, &float_, sizeof(float_));
	}

	adjVarGeneral->syncFlag = AV_SYNCHRONIZED;
}

/**	@brief	Queries the actual value of selected variable
 *
 *	####	TX —> CMD_GET_ADJ_VARS_VAL :	2 bytes
 *	####	RX <— CMD_SET_ADJ_VARS_VAL :	6 bytes
 *
 *	@pre	sbgcAdjVarGeneral_t.ID field must be filled
 *
 *	@code

			sbgcAdjVarGeneral_t AdjVarP_Roll = { 0 };

			// Initialize adjustable variable
			#if (SBGC_ADJ_VARS_REF_INFO)
				SerialAPI_InitAdjVar(&AdjVarP_Roll, ADJ_VAR_P_ROLL);
			#else
				AdjVarP_Roll.ID = ADJ_VAR_P_ROLL;
			#endif

			SBGC32_GetAdjVarValue(&SBGC32_Device, &AdjVarP_Roll);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*adjVarGeneral - general adjustable variables structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_GetAdjVarValue (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral
										   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertAdjVar(adjVarGeneral)

	gSBGC->_api->startWrite(gSBGC, CMD_GET_ADJ_VARS_VAL SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, 1);
	gSBGC->_api->writeByte(gSBGC, adjVarGeneral->ID);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_SET_ADJ_VARS_VAL SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, PostGetAdjVarValue, adjVarGeneral, sizeof(sbgcAdjVarGeneral_t));
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Queries the actual value of selected variable in float
 *
 *	####	TX —> CMD_GET_ADJ_VARS_VAL :	2 bytes
 *	####	RX <— CMD_SET_ADJ_VARS_VAL :	6 bytes
 *
 *	@pre	sbgcAdjVarGeneral_t.ID field must be filled
 *
 *	@attention	Firmware: 2.73.4+
 *
 *	@code

			sbgcAdjVarGeneral_t AdjVarP_Roll = { 0 };

			// Initialize adjustable variable
			#if (SBGC_ADJ_VARS_REF_INFO)
				SerialAPI_InitAdjVar(&AdjVarP_Roll, ADJ_VAR_P_ROLL);
			#else
				AdjVarP_Roll.ID = ADJ_VAR_P_ROLL;
			#endif

			SBGC32_GetAdjVarValueFloat(&SBGC32_Device, &AdjVarP_Roll);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*adjVarGeneral - general adjustable variables structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_GetAdjVarValueFloat (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral
												/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2734)
	sbgcAssertAdjVar(adjVarGeneral)

	gSBGC->_api->startWrite(gSBGC, CMD_GET_ADJ_VARS_VAL_F SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, 1);
	gSBGC->_api->writeByte(gSBGC, adjVarGeneral->ID);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_SET_ADJ_VARS_VAL_F SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, PostGetAdjVarValue, adjVarGeneral, sizeof(sbgcAdjVarGeneral_t));
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_GetAdjVarValues and
 *			@ref SBGC32_GetAdjVarValuesFloat
 *			functions
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostGetAdjVarValues (sbgcGeneral_t *gSBGC)
{
	sbgcAdjVarGeneral_t *adjVarGeneral = (sbgcAdjVarGeneral_t*)curCmdDest_;

	ui8 adjVarQuan = gSBGC->_api->readByte(gSBGC);

	if (curCmd_->_destinationSize < (sizeof(sbgcAdjVarGeneral_t) * adjVarQuan))
		SerialAPI_FatalErrorHandler();

	for (ui8 i = 0; i < adjVarQuan; i++)
	{
		#if (SBGC_NEED_ASSERTS)

			if (adjVarGeneral[i].ID != gSBGC->_api->readByte(gSBGC))
			{
				(void)gSBGC->_api->readLong(gSBGC);  // skip
				continue;
			}

		#else
			(void)gSBGC->_api->readByte(gSBGC);
		#endif

		if (curCmd_->_commandID == CMD_SET_ADJ_VARS_VAL)
			adjVarGeneral[i].value = (i32)gSBGC->_api->readLong(gSBGC);

		else
		{
			ui32 float_ = gSBGC->_api->readLong(gSBGC);
			memcpy(&adjVarGeneral[i].value, &float_, sizeof(float_));
		}

		adjVarGeneral[i].syncFlag = AV_SYNCHRONIZED;
	}
}

/**	@brief	Requires the value of adjustable variables
 *
 *	####	TX —> CMD_GET_ADJ_VARS_VAL :	1 + adjVarQuan bytes
 *	####	RX <— CMD_SET_ADJ_VARS_VAL :	1 + (adjVarQuan * 5) bytes
 *
 *	@pre	sbgcAdjVarGeneral_t.ID fields must be filled
 *
 *	@attention	adjVarQuan should not exceed
 *				SBGC_ADJ_VARS_MAX_NUM_PACKET (40)
 *
 *	@code

			#define	ADJ_VARS_NUMBER	9

			sbgcAdjVarGeneral_t AdjVarGeneral [ADJ_VARS_NUMBER];

			for (ui8 i = 0; i < ADJ_VARS_NUMBER; i++)
			// Initialize adjustable variables
			{
				#if (SBGC_ADJ_VARS_REF_INFO)
					SerialAPI_InitAdjVar(&AdjVarGeneral[i], (sbgcAdjVarID_t)i);
				#else
					AdjVarGeneral[i].ID = (sbgcAdjVarID_t)i;
				#endif
			}

			SBGC32_GetAdjVarValues(&SBGC32_Device, AdjVarGeneral, ADJ_VARS_NUMBER);

			#if (SBGC_NEED_DEBUG && SBGC_ADJ_VARS_REF_INFO && SBGC_ADJ_VARS_NAMES)

				for (ui8 i = 0; i < ADJ_VARS_NUMBER; i++)
					DebugSBGC32_PrintStructElement(&SBGC32_Device, &AdjVarGeneral[i].value, AdjVarGeneral[i].name, sbgcUCHAR);

			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*adjVarGeneral - general adjustable variables structure
 *	@param	adjVarQuan - number of adjustable variables
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_GetAdjVarValues (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral, ui8 adjVarQuan
											/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertAdjVars(adjVarGeneral, adjVarQuan)
	sbgcAssertParam(adjVarQuan, 1, SBGC_ADJ_VARS_MAX_NUM_PACKET)

	gSBGC->_api->startWrite(gSBGC, CMD_GET_ADJ_VARS_VAL SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, adjVarQuan);

	for (ui8 i = 0; i < adjVarQuan; i++)
		gSBGC->_api->writeByte(gSBGC, adjVarGeneral[i].ID);

	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_SET_ADJ_VARS_VAL SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, PostGetAdjVarValues, adjVarGeneral, sizeof(sbgcAdjVarGeneral_t) * adjVarQuan);
	gSBGC->_api->definePayload(gSBGC, (adjVarQuan * (4 + 1)) + 1);
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}

/**	@brief	Requires the value of adjustable variables in float
 *
 *	####	TX —> CMD_GET_ADJ_VARS_VAL :	1 + adjVarQuan bytes
 *	####	RX <— CMD_SET_ADJ_VARS_VAL :	1 + (adjVarQuan * 5) bytes
 *
 *	@pre	sbgcAdjVarGeneral_t.ID fields must be filled
 *
 *	@attention	Firmware: 2.73.4+
 *
 *	@attention	adjVarQuan should not exceed
 *				SBGC_ADJ_VARS_MAX_NUM_PACKET (40)
 *
 *	@code

			#define	ADJ_VARS_NUMBER	9

			sbgcAdjVarGeneral_t AdjVarGeneral [ADJ_VARS_NUMBER];

			for (ui8 i = 0; i < ADJ_VARS_NUMBER; i++)
			// Initialize adjustable variables
			{
				#if (SBGC_ADJ_VARS_REF_INFO)
					SerialAPI_InitAdjVar(&AdjVarGeneral[i], (sbgcAdjVarID_t)i);
				#else
					AdjVarGeneral[i].ID = (sbgcAdjVarID_t)i;
				#endif
			}

			SBGC32_GetAdjVarValuesFloat(&SBGC32_Device, AdjVarGeneral, ADJ_VARS_NUMBER);

			#if (SBGC_NEED_DEBUG && SBGC_ADJ_VARS_REF_INFO && SBGC_ADJ_VARS_NAMES)

				for (ui8 i = 0; i < ADJ_VARS_NUMBER; i++)
					DebugSBGC32_PrintStructElement(&SBGC32_Device, &AdjVarGeneral[i].value, AdjVarGeneral[i].name, sbgcFLOAT);

			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*adjVarGeneral - general adjustable variables structure
 *	@param	adjVarQuan - number of adjustable variables
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_GetAdjVarValuesFloat (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral, ui8 adjVarQuan
												 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2734)
	sbgcAssertAdjVars(adjVarGeneral, adjVarQuan)
	sbgcAssertParam(adjVarQuan, 1, SBGC_ADJ_VARS_MAX_NUM_PACKET)

	gSBGC->_api->startWrite(gSBGC, CMD_GET_ADJ_VARS_VAL_F SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, adjVarQuan);

	for (ui8 i = 0; i < adjVarQuan; i++)
		gSBGC->_api->writeByte(gSBGC, adjVarGeneral[i].ID);

	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_SET_ADJ_VARS_VAL_F SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, PostGetAdjVarValues, adjVarGeneral, sizeof(sbgcAdjVarGeneral_t) * adjVarQuan);
	gSBGC->_api->definePayload(gSBGC, (adjVarQuan * (4 + 1)) + 1);
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_SaveAdjVarToEEPROM function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostSaveAdjVarToEEPROM (sbgcGeneral_t *gSBGC)
{
	sbgcAdjVarGeneral_t *adjVarGeneral = (sbgcAdjVarGeneral_t*)curCmdDest_;

	adjVarGeneral->saveFlag = AV_SAVED;
}

/**	@brief	Saves the current value of adjustable variable in EEPROM
 *
 *	####	TX —> CMD_SAVE_PARAMS_3 :		1 byte
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@pre	A saved adjustable variable must be changed
 *			by the @ref SBGC32_SetAdjVarValue or
 *			@ref SBGC32_SetAdjVarValues functions first
 *
 *	@note	See @ref SBGC32_SetAdjVarValue function
 *			documentation for usage example
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*adjVarGeneral - general adjustable variables structure
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SaveAdjVarToEEPROM (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral, sbgcConfirm_t *confirm
											   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertAdjVar(adjVarGeneral)

	gSBGC->_api->startWrite(gSBGC, CMD_SAVE_PARAMS_3 SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, adjVarGeneral->ID);
	gSBGC->_api->assignEvent(gSBGC, PostSaveAdjVarToEEPROM, adjVarGeneral, sizeof(sbgcAdjVarGeneral_t));
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_SAVE_PARAMS_3 SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_SaveAdjVarsToEEPROM function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostSaveAdjVarsToEEPROM (sbgcGeneral_t *gSBGC)
{
	sbgcAdjVarGeneral_t *adjVarGeneral = (sbgcAdjVarGeneral_t*)curCmdDest_;

	ui8 adjVarQuan = curCmd_->_payloadSize;

	if (curCmd_->_destinationSize < (sizeof(sbgcAdjVarGeneral_t) * adjVarQuan))
		SerialAPI_FatalErrorHandler();

	ui8 i = 0;

	while (adjVarQuan)
	{
		adjVarGeneral[i++].saveFlag = AV_SAVED;
		adjVarQuan--;

		if (i >= (gSBGC->_api->adjVarsNumber - 1))
			return;
	}
}

/**	@brief	Saves current adjustable variables' value to EEPROM
 *
 *	####	TX —> CMD_SAVE_PARAMS_3 :		adjVarQuan bytes
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@pre	A saved adjustable variables must be changed
 *			by the @ref SBGC32_SetAdjVarValue or
 *			@ref SBGC32_SetAdjVarValues functions first
 *
 *	@attention	adjVarQuan should not exceed a maximal number
 *				of adjustable variables available in the
 *				current firmware
 *
 *	@note	See @ref SBGC32_SetAdjVarValues function
 *			documentation for usage example
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*adjVarGeneral - general adjustable variables structure
 *	@param	adjVarQuan - number of adjustable variables
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SaveAdjVarsToEEPROM (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral, ui8 adjVarQuan, sbgcConfirm_t *confirm
												/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertAdjVars(adjVarGeneral, adjVarQuan)
	sbgcAssertParam(adjVarQuan, 1, gSBGC->_api->adjVarsNumber)

	#if (SBGC_NEED_ASSERTS)

		for (ui8 i = 0; i < adjVarQuan; i++)
		{
			if (adjVarGeneral[i].saveFlag == AV_NOT_SAVED)
				break;

			if (i == (adjVarQuan - 1))
				return sbgcCOMMAND_NOTHING_TO_CHANGE;
		}

	#endif

	gSBGC->_api->startWrite(gSBGC, CMD_SAVE_PARAMS_3 SBGC_ADVANCED_ARGS__);

	for (ui8 i = 0; i < adjVarQuan; i++)
		if (adjVarGeneral[i].saveFlag == AV_NOT_SAVED)
			gSBGC->_api->writeByte(gSBGC, adjVarGeneral[i].ID);

	gSBGC->_api->assignEvent(gSBGC, PostSaveAdjVarsToEEPROM, adjVarGeneral, sizeof(sbgcAdjVarGeneral_t) * adjVarQuan);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_SAVE_PARAMS_3 SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Saves all not saved active variables
 *
 *	####	TX —> CMD_SAVE_PARAMS_3	with no payload
 *	####	RX <— CMD_CONFIRM :		1-6 bytes
 *
 *	@post	Recommended manual setting of the saveFlag
 *			on all (saved) variables
 *
 *	@note	See @ref SBGC32_SetAdjVarValues function
 *			documentation for usage example
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_SaveAllActiveAdjVarsToEEPROM (sbgcGeneral_t *gSBGC, sbgcConfirm_t *confirm
														 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_SAVE_PARAMS_3 SBGC_ADVANCED_ARGS__);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_SAVE_PARAMS_3 SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Adjvar_Configs
 *	@{
 */
/**	@brief	Writes configuration of mapping of control
 *			inputs to adjustable variables
 *
 *	####	TX —> CMD_WRITE_ADJ_VARS_CFG :	128 bytes
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@pre	Use the @ref SBGC32_ReadAdjVarsCfg function to
 *			obtain this data previously for changing
 *
 *	@code

			#define ADJ_VAR_ANALOG_SLOT_MIN 50
			#define ADJ_VAR_ANALOG_SLOT_MAX 200

			sbgcAdjVarsCfg_t AdjVarsCfg;

			// Get old configurations
			SBGC32_ReadAdjVarsCfg(&SBGC32_Device, &AdjVarsCfg);

			// Change first trigger slot configurations
			AdjVarsCfg.TriggerSlot[0].triggerSrcCh = sbgcRCMap_RC_INPUT_ROLL;
			AdjVarsCfg.TriggerSlot[0].triggerAction[0] = MENU_CMD_HOME_POSITION;

			// Change first analog slot configurations
			AdjVarsCfg.AnalogSlot[0].analogSrc = sbgcRCMap_API_VIRT_CH_1;
			AdjVarsCfg.AnalogSlot[0].varID = ADJ_VAR_RC_SPEED_YAW;
			AdjVarsCfg.AnalogSlot[0].minVal = ADJ_VAR_ANALOG_SLOT_MIN;
			AdjVarsCfg.AnalogSlot[0].maxVal = ADJ_VAR_ANALOG_SLOT_MAX;

			SBGC32_WriteAdjVarsCfg(&SBGC32_Device, &AdjVarsCfg, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*adjVarsCfg - structure with written adjustable
 *			variable configuration parameters
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_WriteAdjVarsCfg (sbgcGeneral_t *gSBGC, const sbgcAdjVarsCfg_t *adjVarsCfg, sbgcConfirm_t *confirm
											/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_WRITE_ADJ_VARS_CFG SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeBuff(gSBGC, adjVarsCfg, sizeof(sbgcAdjVarsCfg_t));
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_WRITE_ADJ_VARS_CFG SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Request configuration of mapping of control
 *			inputs to adjustable variables
 *
 *	####	TX —> CMD_READ_ADJ_VARS_CFG		with no payload
 *	####	RX <— CMD_READ_ADJ_VARS_CFG :	128 bytes
 *
 *	@post	Use the @ref DebugSBGC32_PrintWholeStruct
 *			function with PM_AV_CONFIG to print
 *			received data
 *
 *	@code

			sbgcAdjVarsCfg_t AdjVarsCfg;

			SBGC32_ReadAdjVarsCfg(&SBGC32_Device, &AdjVarsCfg);

			#if (SBGC_NEED_DEBUG && SBGC_NEED_REF_INFO)
				DebugSBGC32_PrintWholeStruct(&SBGC32_Device, &AdjVarsCfg, PM_AV_CONFIG);
			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*adjVarsCfg - structure for storing adjustable
 *			variable configuration parameters
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ReadAdjVarsCfg (sbgcGeneral_t *gSBGC, sbgcAdjVarsCfg_t *adjVarsCfg
										   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_READ_ADJ_VARS_CFG SBGC_ADVANCED_ARGS__);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_READ_ADJ_VARS_CFG SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, NULL, adjVarsCfg, sizeof(sbgcAdjVarsCfg_t));
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Adjvar_State
 *	@{
 */
/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_RequestAdjVarsState function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostRequestAdjVarsState (sbgcGeneral_t *gSBGC)
{
	sbgcAdjVarsState_t *adjVarsState = (sbgcAdjVarsState_t*)curCmdDest_;

	if (gSBGC->_api->baseFirmwareVersion < 2625)
	{
		adjVarsState->triggerRC_Data__old = (i16)gSBGC->_api->readWord(gSBGC);
		adjVarsState->triggerAction__old = gSBGC->_api->readByte(gSBGC);
		adjVarsState->analogRC_Data = (i16)gSBGC->_api->readWord(gSBGC);
		adjVarsState->analogValue = (i32)gSBGC->_api->readLong(gSBGC);
	}

	else  // Firmware ver. 2.62b5+
	{
		adjVarsState->triggerRC_Data = (i16)gSBGC->_api->readWord(gSBGC);
		adjVarsState->triggerAction = gSBGC->_api->readByte(gSBGC);
		adjVarsState->analogSrcValue = (i16)gSBGC->_api->readWord(gSBGC);
		adjVarsState->analogVarValue = (float)gSBGC->_api->readLong(gSBGC);
		adjVarsState->lutSrcValue = (i16)gSBGC->_api->readWord(gSBGC);
		adjVarsState->lutVarValue = (float)gSBGC->_api->readLong(gSBGC);
	}
}

/**	@brief	Request the state of adjustable variable
 *			in the given trigger and analog slots
 *
 *	####	TX —> CMD_ADJ_VARS_STATE :		7 bytes (prior to frw. ver. 2.62b5 - 2 bytes)
 *	####	RX <— CMD_ADJ_VARS_STATE :		15 bytes
 *
 *	@pre	Firmware: prior to 2.62b5:\n
 *			Must be set:\n
 *			sbgcAdjVarsState_t.triggerSlot__old \n
 *			sbgcAdjVarsState_t.analogSlot
 *
 *	@pre	Firmware: 2.62b5+:\n
 *			Must be set:\n
 *			sbgcAdjVarsState_t.triggerSlot \n
 *			sbgcAdjVarsState_t.analogSrcID \n
 *			sbgcAdjVarsState_t.analogVarID \n
 *			sbgcAdjVarsState_t.lutSrcID \n
 *			sbgcAdjVarsState_t.lutVarID
 *
 *	@pre	Board requirements:\n
 *			STATE_VARS = (1 << 18) (ext.)
 *
 *	@post	Use the @ref DebugSBGC32_PrintWholeStruct
 *			function with PM_AV_STATE_OLD_RX or
 *			PM_AV_STATE_RX to print received data
 *
 *	@note	This function can work in two ways. It will depend
 *			on the current firmware version of SimpleBGC
 *
 *	@code

			#define ADJ_VAR_TRIGGER_SLOT 0
			#define ADJ_VAR_ANALOG_SRC 1
			#define ADJ_VAR_LUT_SRC 5

			sbgcAdjVarsState_t AdjVarsState = { 0 };

			if (SerialAPI_GetFirmwareVersion(&SBGC32_Device) < 2625)
			{
				AdjVarsState.triggerSlot__old = ADJ_VAR_TRIGGER_SLOT;
				AdjVarsState.analogSlot = ADJ_VAR_ANALOG_SRC;

				SBGC32_RequestAdjVarsState(&SBGC32_Device, &AdjVarsState);

				#if (SBGC_NEED_DEBUG && SBGC_NEED_REF_INFO)
					DebugSBGC32_PrintWholeStruct(&SBGC32_Device, &AdjVarsState, PM_AV_STATE_OLD_RX);
				#endif
			}

			else  // Firmware ver. 2.62b5+
			{
				AdjVarsState.triggerSlot = ADJ_VAR_TRIGGER_SLOT;

				AdjVarsState.analogSrcID = ADJ_VAR_ANALOG_SRC;
				AdjVarsState.analogVarID = ADJ_VAR_RC_SPEED_YAW;

				AdjVarsState.lutSrcID = ADJ_VAR_LUT_SRC;
				AdjVarsState.lutSrcValue = ADJ_VAR_RC_SPEED_PITCH;

				SBGC32_RequestAdjVarsState(&SBGC32_Device, &AdjVarsState);

				#if (SBGC_NEED_DEBUG && SBGC_NEED_REF_INFO)
					DebugSBGC32_PrintWholeStruct(&SBGC32_Device, &AdjVarsState, PM_AV_STATE_RX);
				#endif
			}

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*adjVarsState - structure for writing and storing
 *			adjustable variable configuration parameters
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_RequestAdjVarsState (sbgcGeneral_t *gSBGC, sbgcAdjVarsState_t *adjVarsState
												/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFeature(BF_STATE_VARS)
	sbgcAssertParam(adjVarsState->triggerSlot__old, 0, SBGC_ADJ_VAR_TRIGGER_SLOTS_NUM - 1)
	sbgcAssertParam(adjVarsState->analogSlot, 0, SBGC_ADJ_VAR_ANALOG_SLOTS_NUM - 1)
	sbgcAssertParam(adjVarsState->triggerSlot, 0, SBGC_ADJ_VAR_TRIGGER_SLOTS_NUM - 1)

	gSBGC->_api->startWrite(gSBGC, CMD_ADJ_VARS_STATE SBGC_ADVANCED_ARGS__);

	if (gSBGC->_api->baseFirmwareVersion < 2625)
		gSBGC->_api->writeBuff(gSBGC, adjVarsState, 2);

	else  // Firmware ver. 2.62b5+
		gSBGC->_api->writeBuff(gSBGC, &adjVarsState->triggerSlot, 7);

	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_ADJ_VARS_STATE SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, PostRequestAdjVarsState, adjVarsState, sizeof(sbgcAdjVarsState_t));
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Adjvar_Info
 *	@{
 */
/**	@brief	SerialAPI event
 *
 *	@note	Private function.
 *			See @ref SBGC32_RequestAdjVarsInfo function
 *
 *	@param	*gSBGC - serial connection descriptor
 */
static void PostRequestAdjVarsInfo (sbgcGeneral_t *gSBGC)
{
	sbgcAdjVarGeneral_t *adjVarGeneral = (sbgcAdjVarGeneral_t*)curCmdDest_;

	ui8 payloadSize = curCmd_->_payloadSize - 1;
	ui8 nameLenght;

	gSBGC->_api->skipBytes(gSBGC, sizeof(ui8));

	while (payloadSize)
	{
		adjVarGeneral->ID = gSBGC->_api->readByte(gSBGC);
		nameLenght = gSBGC->_api->readByte(gSBGC);

		#if (SBGC_ADJ_VARS_NAMES)

			gSBGC->_api->readBuff(gSBGC, adjVarGeneral->name, nameLenght);

			if (nameLenght < SBGC_ADJ_VAR_INFO_MAX_NAME)
				adjVarGeneral->name[nameLenght] = '\0';

		#else
			gSBGC->_api->skipBytes(gSBGC, nameLenght);
		#endif

		adjVarGeneral->minValue = (i16)gSBGC->_api->readWord(gSBGC);
		adjVarGeneral->maxValue = (i16)gSBGC->_api->readWord(gSBGC);
		adjVarGeneral->value = (i32)gSBGC->_api->readLong(gSBGC);

		payloadSize -= 10 + nameLenght;

		adjVarGeneral++;
	}
}

/**	@brief	Requests the list of all available adjustable variables
 *
 *	####	TX —> CMD_ADJ_VARS_INFO :		1 byte
 *	####	RX <— CMD_ADJ_VARS_INFO :		1 + ? bytes
 *
 *	@attention	Firmware: 2.73+
 *
 *	@note	Some boards like the SBGC32 Regular don't have
 *			a support of the shake generator. Thus, it's
 *			necessary to skip the ADJ_VAR_SHAKE_...
 *			variables working with these boards
 *
 *	@code

			sbgcAdjVarGeneral_t AdjVarGeneral [SerialAPI_GetAdjVarNumber(&SBGC32_Device)];
			ui8 adjVarPointer = 0;
			sbgcBoolean_t shakeGenAdjVarsGroup = sbgcFALSE;

			if (SerialAPI_GetBoardFeatures2(&SBGC32_Device) & BFE2_SHAKE_GENERATOR)
				shakeGenAdjVarsGroup = sbgcTRUE;

			for (ui8 i = 0; i < SerialAPI_GetAdjVarNumber(&SBGC32_Device); i++)
			{
				AdjVarGeneral[i].ID = ADJ_VAR_UNDEFINED;

				#if (SBGC_ADJ_VARS_NAMES)

					// *See the note about using sbgcMalloc at the sbgc32.h file
					AdjVarGeneral[i].name = (char*)sbgcMalloc(SBGC_ADJ_VAR_INFO_MAX_NAME);

				#endif
			}

			while (adjVarPointer < SerialAPI_GetAdjVarNumber(&SBGC32_Device))
			{
				SBGC32_RequestAdjVarsInfo(&SBGC32_Device, &AdjVarGeneral[adjVarPointer], adjVarPointer);

				for ( ; ; adjVarPointer++)
				{
					if ((shakeGenAdjVarsGroup == sbgcFALSE) & (adjVarPointer == ADJ_VAR_SHAKE_AMP_ROLL))
					{
						#if (SBGC_COMING_SOON)
							adjVarPointer = ADJ_VAR_SHAKE_MASTER_GAIN + 1;  // For the future versions

						#else

							adjVarPointer = SerialAPI_GetAdjVarNumber(&SBGC32_Device);
							break;

						#endif
					}

					if (AdjVarGeneral[adjVarPointer].ID == ADJ_VAR_UNDEFINED)
						break;
				}
			}

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*adjVarGeneral - general adjustable variables structure
 *	@param	ID - adjustable variable ID to start from
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_RequestAdjVarsInfo (sbgcGeneral_t *gSBGC, sbgcAdjVarGeneral_t *adjVarGeneral, sbgcAdjVarID_t ID
											   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_ADJ_VARS_INFO SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, ID);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_ADJ_VARS_INFO SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, PostRequestAdjVarsInfo, adjVarGeneral, sizeof(sbgcAdjVarGeneral_t) * gSBGC->_api->adjVarsNumber);
	gSBGC->_api->finishRead(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */

#endif /* SBGC_ADJVAR_MODULE */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
