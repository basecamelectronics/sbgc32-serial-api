/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2
 *
 *	@file		gimbalControl.h
 *
 *	@brief		Gimbal control header file
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
/**	____________________________________________________________________
 *
 *	@defgroup	Gimbal_Control SBGC32 Gimbal Control
 *	@ingroup	Modules
 *		@brief	Gimbal Control Title Module
 *	____________________________________________________________________
 *
 *	@defgroup	Control Control
 *	@ingroup	Gimbal_Control
 *		@brief	Control Module
 *
 *				Covered Commands:
 *
 *				### CMD_CONTROL
 *				### CMD_CONTROL_EXT
 *				### CMD_CONTROL_QUAT
 *				### CMD_EXT_MOTORS_ACTION
 *				### CMD_EXT_MOTORS_CONTROL
 *
 *	@defgroup	Control_Config Control Configuration
 *	@ingroup	Gimbal_Control
 *		@brief	Control Configuration Module
 *
 *				Covered Commands:
 *
 *				### CMD_CONTROL_CONFIG
 *				### CMD_CONTROL_QUAT_CONFIG
 *				### CMD_EXT_MOTORS_CONTROL_CONFIG
 *
 *	@defgroup	Virt_Channels Virtual Channels
 *	@ingroup	Gimbal_Control
 *		@brief	Virtual Channels Module
 *
 *				Covered Commands:
 *
 *				### CMD_API_VIRT_CH_CONTROL
 *				### CMD_API_VIRT_CH_HIGH_RES
 *	____________________________________________________________________
 */

#ifndef		MODULES_GIMBAL_CONTROL_H_
#define		MODULES_GIMBAL_CONTROL_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../sbgc32.h"


#if (SBGC_CONTROL_MODULE)

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									   Control Flags
 */
/**	@addtogroup	Control
 *	@{
 */
/**	@note	sbgcControl_t.mode \n
 *			sbgcAxisCE_t.mode \n
 *
 *	Can be combined with @ref sbgcControlFlag_t
 */
typedef enum
{
	CtrlMODE_NO_CONTROL				= 0,			/*!<  Finish serial control and restore normal RC control							*/
	CtrlMODE_SPEED					= 1,			/*!<  Gimbal travels with the given speed in the Euler coordinates until the next
														  CMD_CONTROL command comes. Given angle is ignored								*/
	CtrlMODE_ANGLE					= 2,			/*!<  Gimbal travels to the given Euler angle with the automatically calculated
														  speed according to the acceleration limit. The nominal speed may be provided
														  by the SPEED parameter. Speed is additionally attenuated near target to keep
														  the control smooth (if CONTROL_FLAG_TARGET_PRECISE is not set).
														  Gimbal travels to the new absolute setpoint angle, making multiple turns if
														  needed, but limiting a rotation by ±720° per command due to limited
														  16bit parameter range															*/
	CtrlMODE_SPEED_ANGLE			= 3,			/*!<  Gimbal travels with the given SPEED parameter. Additionally, controller keeps
														  the given angle and fixes the accumulated error by adjusting the actual speed
														  in a direction of error minimization, defined by the "Outer P" GUI parameter.
														  This error may appear because the estimated target angle (integral of SPEED
														  by dt) may differ from the actual target angle, because the actual target
														  speed is internally filtered by LPF and acceleration limit, if they are
														  enabled. This mode should be chosen when it's required to exactly repeat
														  the rotation of the user-operated device (like joystick or wheel),
														  precisely tracking its speed and angle										*/
	CtrlMODE_RC						= 4,			/*!<  The ANGLE parameter is used as RC signal and overrides any other signal
														  source, assigned to this axis. Normal working range is -500..500. A special
														  value -10000 encodes a "signal lost" condition. The flag
														  CONTROL_FLAG_AUTO_TASK can affect this mode.
														  Prior to 2.61 frw. ver., 'SPEED' parameter is ignored.						*/
	CtrlMODE_ANGLE_REL_FRAME		= 5,			/*!<  First, the neutral point of a camera relative to a frame is found in the
														  Euler coordinates for a given axis. Than, the given angle (in ±360° range)
														  is added to this point, and camera travels to it. Note that the given angle
														  does not relate to a particular motor, it relates to global Euler angles!		*/
	/* frw. ver. 2.66b2+ */
	CtrlMODE_RC_HIGH_RES			= 6,			/*!<  The same as the MODE_RC, but the range of the ANGLE parameter has better
														  resolution: -16384..16384. A special value -32768 encodes a "signal lost"
														  condition. Frw. ver. 2.66b2+													*/
	/* frw. ver. 2.70b4+ */
	CtrlMODE_IGNORE					= 7,			/*!<  Ignore this axis and all parameters, keeping it in the actual state.
														  Frw. ver. 2.70b4+																*/
	/* frw. ver. 2.70b7+ */
	CtrlMODE_ANGLE_SHORTEST			= 8				/*!<  Gimbal travels to the given Euler angle with the automatically calculated
														  speed according to the acceleration limit. The nominal speed may be provided
														  by the SPEED parameter. Speed is additionally attenuated near target to keep
														  the control smooth (if CONTROL_FLAG_TARGET_PRECISE is not set).
														  Gimbal travels to the point on a 360° circle by the shortest path, taking
														  into account the software limits of encoders when choosing a direction
														  (it can go by the long path if the short path is blocked). Frw. ver. 2.70b7+	*/

}	sbgcControlMode_t;

/**	@note	sbgcControl_t.mode \n
 *
 *	Can be combined with @ref sbgcControlMode_t
 */
typedef enum
{
	CtrlFLAG_MIX_FOLLOW				= BIT_4_SET,	/*!<  Applicable for CtrlMODE_RC, CtrlMODE_SPEED, CtrlMODE_ANGLE
														  or CtrlMODE_ANGLE_SHORTEST. Frw. ver. 2.70b5+									*/
	CtrlFLAG_TARGET_PRECISE			= BIT_5_SET,	/*!<  Applicable for CtrlMODE_ANGLE or CtrlMODE_ANGLE_REL_FRAME. Frw. ver. 2.70b1+	*/
	CtrlFLAG_AUTO_TASK				= BIT_6_SET,	/*!<  Applicable for CtrlMODE_ANGLE or CtrlMODE_ANGLE_REL_FRAME. Frw. ver. 2.62b7+	*/
	CtrlFLAG_FORCE_RC_SPEED			= BIT_6_SET,	/*!<  Applicable for CtrlMODE_RC. Frw. ver. 2.62b7+									*/
	CtrlFLAG_HIGH_RES_SPEED			= BIT_7_SET		/*!<  Frw. ver. 2.60+																*/

}	sbgcControlFlag_t;

/**	@brief	Used as a mask to extract the
 *			Control mode value from
 *			sbgcControl_t.mode
 *
 *	@param	value (sbgcControl_t.mode)
 *
 *	@return	Control mode
 */
static inline sbgcControlMode_t ParserSBGC32_GetControlMode (ui8 value)
{
	return (sbgcControlMode_t)(value & 0b00001111);
}

/**	@brief	Used as a mask to extract the
 *			Control flag value from
 *			sbgcControl_t.mode
 *
 *	@param	value (sbgcControl_t.mode)
 *
 *	@return	Control flag
 */
static inline sbgcControlFlag_t ParserSBGC32_GetControlFlag (ui8 value)
{
	return (sbgcControlFlag_t)(value & 0b11110000);
}


/**	@note	sbgcControlExt_t.dataSet
 */
typedef enum
{
	CEDS_ROLL_SPEED					= BIT_0_SET,	/*!<  SPEED parameter is given for ROLL axis										*/
	CEDS_ROLL_ANGLE					= BIT_1_SET,	/*!<  ANGLE parameter is given for ROLL axis										*/
	CEDS_ROLL_ANGLE_INC_RES			= BIT_2_SET,	/*!<  4 bytes ANGLE with increased resolution for ROLL axis							*/
	CEDS_ROLL_SPEED_INC_RES			= BIT_3_SET,	/*!<  4 bytes SPEED with increased resolution for ROLL axis							*/

	CEDS_PITCH_SPEED				= BIT_5_SET,	/*!<  SPEED parameter is given for PITCH axis										*/
	CEDS_PITCH_ANGLE				= BIT_6_SET,	/*!<  ANGLE parameter is given for PITCH axis										*/
	CEDS_PITCH_ANGLE_INC_RES		= BIT_7_SET,	/*!<  4 bytes ANGLE with increased resolution for PITCH axis						*/
	CEDS_PITCH_SPEED_INC_RES		= BIT_8_SET,	/*!<  4 bytes SPEED with increased resolution for PITCH axis						*/

	CEDS_YAW_SPEED					= BIT_10_SET,	/*!<  SPEED parameter is given for YAW axis											*/
	CEDS_YAW_ANGLE					= BIT_11_SET,	/*!<  ANGLE parameter is given for YAW axis											*/
	CEDS_YAW_ANGLE_INC_RES			= BIT_12_SET,	/*!<  4 bytes ANGLE with increased resolution for YAW axis							*/
	CEDS_YAW_SPEED_INC_RES			= BIT_13_SET,	/*!<  4 bytes SPEED with increased resolution for YAW axis							*/

}	sbgcControlExtDataSet_t;


/**	@note	sbgcAxisCE_t.modeFlags
 */
typedef enum
{
	CEF_DISABLE_ANGLE_ERR_CORR		= BIT_0_SET		/*!<  Disable the setpoint angle error correction. If disabled, the actual angle
														  may not precisely match the commanded angle when controlling gimbal in
														  ANGLE-related modes (including follow-mix and servo mode). The effect
														  is equal to setting 'OuterP' parameter to 0									*/

}	sbgcControlExtFlag_t;


/**	@note	@ref SBGC32_ExtMotorsAction, 3 arg
 */
typedef enum
{
	EXT_MOTOR_OFF_FLOATING			= 1,			/*!<  Turn off and leave floating													*/
	EXT_MOTOR_OFF_BRAKE				= 2,			/*!<  Turn off and break															*/
	EXT_MOTOR_OFF_SAFE				= 3,			/*!<  Compensate for external force to slow down the rotation,
														  then turn off with brake														*/
	EXT_MOTOR_ON					= 4,			/*!<  Turn on																		*/
	EXT_HOME_POSITION				= 5,			/*!<  Move to home position															*/
	EXT_SEARCH_HOME					= 6				/*!<  Search home period for multiturn or geared motors								*/

}	sbgcExtMotorAction_t;


/**	@note	@ref SBGC32_ControlExtMotors, 4 arg
 */
typedef enum
{
	EMP_16BIT_SETPOINT				= 0,
	EMP_32BIT_SETPOINT				= BIT_0_SET,
	EMP_PARAM1_IS_16BIT				= BIT_1_SET,
	EMP_PARAM1_IS_32BIT				= BIT_2_SET

}	sbgcExtMotorParam_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								Control Config Flags
 */
/**	@addtogroup	Control_Config
 *	@{
 */
/**	@note	sbgcControlConfig_t.flags
 */
typedef enum
{
	CtrlCONFIG_FLAG_NEED_CONFIRM	= 0,
	CtrlCONFIG_FLAG_NO_CONFIRM		= BIT_0_SET,
	/* frw. ver. 2.72b0+ */
	CtrlCONFIG_FLAG_SERVO_MODE_ENABLE
									= BIT_1_SET,
	CtrlCONFIG_FLAG_SERVO_MODE_DISABLE
									= BIT_2_SET,
	/* frw. ver. 2.72b3+ */
	CtrlCONFIG_FLAG_LPF_EXT_RANGE	= BIT_3_SET

}	sbgcControlConfigFlag_t;


/**	@note	sbgcControlQuatConfig_t.dataSet
 */
typedef enum
{
	CQCP_MAX_SPEED					= BIT_0_SET,
	CQCP_ACC_LIMIT					= BIT_1_SET,
	CQCP_JERK_SLOPE					= BIT_2_SET,
	CQCP_FLAGS						= BIT_3_SET,
	CQCP_ATTITUDE_LPF_FREQ			= BIT_4_SET,
	CQCP_SPEED_LPF_FREQ				= BIT_5_SET

}	sbgcControlQuatConfigParam_t;


/**	@note	sbgcControlQuatConfig_t.flags
 */
typedef enum
{
	CQCF_MOTION_PROFILE_SPLIT_XYZ	= BIT_0_SET		/*!<  Applicable for: CtrlQ_MODE_ATTITUDE, CtrlQ_MODE_SPEED_LIMITED.
														  Default value: disabled. If set, the motion profile is applied separately
														  for X,Y,Z axes according to the acceleration limit settings for ROLL (Y),
														  PITCH (X), YAW (Z) axes. If not set, the motion profile is applied to the
														  speed along the shortest path trajectory. Configuration is taken from the
														  X axis (PITCH in Euler settings)												*/

}	sbgcControlQuatConfigFlag_t;


/**	@note	sbgcExtMotorsControlConfig_t.dataSet
 */
typedef enum
{
	EMCC_PARAM_MODE					= BIT_0_SET,
	EMCC_PARAM_MAX_SPEED			= BIT_1_SET,
	EMCC_PARAM_MAX_ACCELERATION		= BIT_2_SET,
	EMCC_PARAM_JERK_SLOPE			= BIT_3_SET,
	EMCC_PARAM_MAX_TORQUE			= BIT_4_SET

}	sbgcExtMotorsControlConfigParam_t;


/**	@note	sbgcExtMotorsControlConfig_t.mode
 */
typedef enum
{
	EMCC_MODE_POSITION				= 0,
	EMCC_MODE_SPEED					= 1,
	EMCC_MODE_TORQUE				= 2

}	sbgcExtMotorsControlConfigMode_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						 Realtime Control Structures
 */
/**	@addtogroup	Control
 *	@{
 */
/**	@brief	Part of sbgcControl_t structure
 *
 *	@note	sbgcControl_t.AxisC
 */
typedef struct PACKED__
{
	i16		speed,									/*!<  Units: 0.1220740379 degrees/sec or
														  Units: 0.001 degrees/sec, if CtrlFLAG_HIGH_RES_SPEED is set.
														  See @ref sbgcControlFlag_t enumeration and sbgcControl_t.mode
														  field. Use the @ref sbgcSpeedToValue or the @ref sbgcSpeedToValueHR
														  macros to comfortable work with this field									*/
			angle;									/*!<  Units: 0.02197265625 degree. Use the @ref sbgcAngleToDegree macro
														  to comfortable work with this field											*/

}	sbgcAxisC_t;

/**	@brief	Structure type for real-time gimbal
 *			position control operation
 *
 *	@ref	SBGC32_Control function
 */
typedef struct PACKED__
{
	ui8				mode [3];						/*!<  See @ref sbgcControlMode_t and @ref sbgcControlFlag_t enumerations			*/

	sbgcAxisC_t		AxisC [3];						/*!<  ROLL : PITCH : YAW															*/

}	sbgcControl_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t controlReferenceInfoArray [];
	extern const ui8 controlReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif


/**	@brief	Part of sbgcControlExt_t structure
 *
 *	@note	sbgcControlExt_t.AxisCE
 */
typedef struct PACKED__
{
	ui8		mode;									/*!<  See @ref sbgcControlMode_t and @ref sbgcControlFlag_t enumerations			*/
	ui8		modeFlags;								/*!<  See @ref sbgcControlExtFlag_t enumeration										*/
	i32		speed;									/*!<  Units: 0.1220740379 degrees/sec or
														  Units: 0.001 degrees/sec, if CtrlFLAG_HIGH_RES_SPEED is set.
														  See @ref sbgcControlFlag_t enumeration and sbgcAxisCE_t.mode field.
														  Frw. ver. 2.72b0+: if CEDS_x_SPEED_INC_RES in sbgcControlExt_t.dataSet is set,
														  SPEED is 32bit signed value with the increased resolution 0.001 degrees/sec.
														  Otherwise, it is 16bit signed value with resolution 0.1220740379 degrees/sec.
														  Use the @ref sbgcSpeedToValue or the @ref sbgcSpeedToValueHR
														  macros to comfortable work with this field.									*/
	i32		angle;									/*!<  Units: 0.02197265625 degree. Use the @ref sbgcAngleToDegree macro
														  to comfortable work with this field											*/

}	sbgcAxisCE_t;

/**	@brief	Structure type for real-time gimbal position
 *			control operation in extended format
 *
 *	@ref	SBGC32_ControlExt function
 */
typedef struct PACKED__
{
	ui16			dataSet;						/*!<  Defines which data is provided in this command with a variable length.
														  See @ref sbgcControlExtDataSet_t enumeration									*/

	sbgcAxisCE_t	AxisCE [3];						/*!<  ROLL : PITCH : YAW															*/

}	sbgcControlExt_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t controlExtReferenceInfoArray [];
	extern const ui8 controlExtReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif


/**	@brief	Structure type for control gimbal
 *			position in quaternions
 *
 *	@ref	SBGC32_ControlQuat function
 */
typedef struct PACKED__
{
	ui8		mode;									/*!<  See @ref sbgcControlQuatMode_t enumeration									*/
	ui8		flags;									/*!<  See @ref sbgcControlQuatFlag_t enumeration									*/
	float	attitude [4];							/*!<  Target attitude in a form of unit quaternion [w, x, y, z]						*/
	float	speed [3];								/*!<  Units: rad/sec. Target speed in a form of rotation vector [x, y, z]			*/

}	sbgcControlQuat_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t controlQuatReferenceInfoArray [];
	extern const ui8 controlQuatReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif


/**	@brief	Structure type for control
 *			extra motors
 *
 *	@ref	SBGC32_ControlExtMotors function
 */
typedef struct PACKED__
{
	i32		setpoint;								/*!<  16-bit:
														  Torque mode: ±32767 for the maximum torque the driver can provide.
														  Speed mode: Units 0.1220740379 degrees/sec. Use the @ref sbgcSpeedToValue
														  macro to comfortable work with this field.
														  Position mode: 14 bits for a turn, units 0.02197265625 degree. There is an
														  unwrap filter for continued rotation properly handling integer overflow.
														  Use the @ref sbgcAngleToDegree macro to comfortable work with this field.
														  32-bit:
														  Torque mode: not applicable.
														  Speed mode: Units 0.1220740379 degrees/sec.
														  Position mode: 14 bits for a turn, units 0.02197265625 degree. There is an
														  unwrap filter for continued rotation properly handling integer overflow.
														  Mutually exclusive with parameter setpoint16									*/
	i32		param1;									/*!<  Speed mode: overrides the internally calculated angle (as if both SPEED and
														  ANGLE setpoints were provided externally).
														  Position mode: overrides the configured max. speed.
														  This parameter is optional and may not be provided at all if none of
														  EMP_PARAM1_IS_16BIT, EMP_PARAM1_IS_32BIT of
														  sbgcControlExtMotors_t.dataSet is set											*/

}	sbgcControlExtMotors_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *				  Realtime Control Config Structures
 */
/**	@addtogroup	Control_Config
 *	@{
 */
/**	@brief	Part of sbgcControlConfig_t structure
 *
 *	@note	sbgcControlConfig_t.AxisCC
 */
typedef struct PACKED__
{
	ui8		angleLPF;								/*!<  0 --> 15. LPF factor for filtering a sbgcAxisC_t.angle parameter in the modes
														  CtrlMODE_ANGLE, CtrlMODE_SPEED_ANGLE. Helps to keep smooth control even
														  if update rate is slow. Default value is 0 – no filtering is applied			*/
	ui8		speedLPF;								/*!<  0 --> 15. LPF factor for filtering a sbgcAxisC_t.speed parameter in the modes
														  CtrlMODE_ANGLE, CtrlMODE_SPEED_ANGLE. Helps to keep smooth control even
														  if update rate is slow. Default value is 0 – no filtering is applied			*/
	ui8		RC_LPF;									/*!<  0 --> 255. LPF factor for filtering RC signal in the mode CtrlMODE_RC,
														  CtrlMODE_RC_HIGH_RES. Helps to keep smooth control
														  even if update rate is slow. 0 – do not change								*/
	ui16	accLimit;								/*!<  0 --> 65535. Units: degrees/sec². Acceleration limiter filter, applied to
														  speed profile in all control modes. 0 – do not change.
														  If > 0 – it overrides the default value from system
														  settings. Frw. ver. 2.70b1+													*/
	ui8		jerkSlope;								/*!<  0 --> 255. Units: 20 ms. The rate of change of an acceleration, forming
														  S-curve in a speed profile, increasing the smoothness of control. This
														  parameter defines the time required to rise the acceleration from zero
														  to a nominal value. Special values: 0 – ignore this parameter,
														  1 – disable jerk slope function. Frw. ver. 2.70b8+							*/
	ui8		reserved1;

}	sbgcAxisCCtrl_t;

/**	@brief	Structure type for real-time gimbal
 *			position control configuration
 *
 *	@ref	SBGC32_ControlConfig function
 */
typedef struct PACKED__
{
	ui16	timeoutMS;								/*!<  0 --> 65535. Units: ms														*/

	ui8		ch1_Priority,							/*!<  ...																			*/
			ch2_Priority,							/*!<  ...																			*/
			ch3_Priority,							/*!<  ...																			*/
			ch4_Priority,							/*!<  ...																			*/
			thisChPriority;							/*!<  ...0 --> 255. Channels are counted in order: UART1, RC_SERIAL, UART2,
														  USB_VCP/UART3 (how they are named in the User Manual). THIS_CH means
														  current port, where command is sent. Values: 0 - do not change the priority.
														  1..255 - set the priority of a given channel. In case of concurrent
														  CMD_CONTROL commands, they will be accepted only on a channel that
														  has higher or equal priority than others. Default value is 0 for
														  all channels after startup													*/

	sbgcAxisCCtrl_t	AxisCCtrl [3];					/*!<  ROLL : PITCH : YAW															*/

	ui8		RC_ExpoRate;							/*!<  0 --> 100. Default value is taken from the "RC_EXPO_RATE" GUI parameter		*/
	ui16	flags;									/*!<  See @ref sbgcControlConfigFlag_t enumeration									*/
	ui8		EulerOrder;								/*!<  See @ref sbgcEulerOrder_t enumeration. Frw. ver. 2.72b0+						*/
	ui8		reserved2 [9];

}	sbgcControlConfig_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
		extern const sbgcParameterReferenceInfo_t controlConfigReferenceInfoArray [];
		extern const ui8 controlConfigReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif


/**	@brief	Structure type for real-time gimbal
 *			position control configuration
 *
 *	@ref	SBGC32_ControlQuatConfig function
 */
typedef struct
{
	ui16	dataSet;								/*!<  See @ref sbgcControlQuatConfigParam_t enumeration								*/
	ui16	maxSpeed [3];							/*!<  Units: 0.1220740379 degrees/sec. Motion profile max. speed limit for [X,Y,Z]
														  axes. Default value is taken form RC settings. Use the @ref sbgcSpeedToValue
														  macro to comfortable work with this field										*/
	ui16	accLimit [3];							/*!<  Units: degrees/sec². Motion profile acceleration limit for [X,Y,Z] axes.
														  0 – disable. Default value is taken form RC settings							*/
	ui16	jerkSlope [3];							/*!<  Units: milliseconds. The rate of change of an acceleration for [X,Y,Z] axes.
														  This parameter defines the time required to rise the acceleration from zero
														  to a nominal value. Increases the smoothness of control. 0 – disable.
														  Default value is taken form RC settings										*/
	ui16	flags;									/*!<  See @ref sbgcControlQuatConfigFlag_t enumeration								*/

	ui8		attitudeLPF_Freq,						/*!<  ...																			*/
			speedLPF_Freq;							/*!<  ...Units: Hz. LPF cut-off frequency for TARGET_ATTITUDE and TARGET_SPEED
														  parameters correspondingly. Helps to mitigate a step-wise response if
														  update rate is low. 0 – disable LPF. Default value: disabled					*/

}	sbgcControlQuatConfig_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
		extern const sbgcParameterReferenceInfo_t controlQuatConfigReferenceInfoArray [];
		extern const ui8 controlQuatConfigReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif


/**	@brief	Structure type for configure run-time
 *			parameters for the selected motor(s)
 *
 *	@ref	SBGC32_ExtMotorsControlConfig function
 */
typedef struct PACKED__
{
	ui8		forMotors;								/*!<  See @ref sbgcExtMotorID_t enumeration											*/
	ui16	dataSet;								/*!<  See @ref sbgcExtMotorsControlConfigParam_t enumeration						*/

	ui8		mode;									/*!<  See @ref sbgcExtMotorsControlConfigMode_t enumeration							*/

	ui16	maxSpeed,								/*!<  Units: 2 degrees/sec. Applied for all modes 									*/
			maxAcceleration;						/*!<  Units: 2 degrees/sec². Applied for speed and position modes 					*/

	ui16	jerkSlope;								/*!<  Units: milliseconds. Applied for speed and position modes						*/
	ui16	maxTorque;								/*!<  0 --> 65535. Units: Relative to the max. available torque.
														  Applied for all modes															*/

}	sbgcExtMotorsControlConfig_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
		extern const sbgcParameterReferenceInfo_t extMotorsControlConfigReferenceInfoArray [];
		extern const ui8 extMotorsControlConfigReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								 Function Prototypes
 */
/**	@cond
 */
/**	@addtogroup	Control
 *	@{
 */
sbgcCommandStatus_t SBGC32_Control (sbgcGeneral_t *gSBGC, const sbgcControl_t *control SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ControlExt (sbgcGeneral_t *gSBGC, const sbgcControlExt_t *controlExt SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ControlQuat (sbgcGeneral_t *gSBGC, const sbgcControlQuat_t *controlQuat SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ExtMotorsAction (sbgcGeneral_t *gSBGC, sbgcExtMotorID_t id, sbgcExtMotorAction_t action, sbgcConfirm_t *confirm
											SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ControlExtMotors (sbgcGeneral_t *gSBGC, sbgcControlExtMotors_t *controlExtMotors, sbgcExtMotorID_t id,
											 sbgcExtMotorParam_t dataSet, sbgcConfirm_t *confirm
											 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ );
/**	@}
 */


/**	@addtogroup	Control_Config
 *	@{
 */
sbgcCommandStatus_t SBGC32_ControlConfig (sbgcGeneral_t *gSBGC, const sbgcControlConfig_t *controlConfig, sbgcConfirm_t *confirm
										  SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ControlQuatConfig (sbgcGeneral_t *gSBGC, const sbgcControlQuatConfig_t *controlQuatConfig, sbgcConfirm_t *confirm
											  SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ExtMotorsControlConfig (sbgcGeneral_t *gSBGC, const sbgcExtMotorsControlConfig_t *extMotorsControlConfig,
												   sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Virt_Channels
 *	@{
 */
sbgcCommandStatus_t SBGC32_SetAPI_VirtChControl (sbgcGeneral_t *gSBGC, const i16 *API_VirtCh, ui8 chQuan SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_SetAPI_VirtChHR_Control (sbgcGeneral_t *gSBGC, const i16 *API_VirtCh, ui8 chQuan SBGC_ADVANCED_PARAMS__);
/**	@}
 */
/**	@endcond
 */

#endif /* SBGC_CONTROL_MODULE */


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

#endif		/* MODULES_GIMBAL_CONTROL_H_ */
