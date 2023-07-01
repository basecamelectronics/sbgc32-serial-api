/** ____________________________________________________________________
 *
 * 	SBGC32 Serial API Library v1.0
 *
 *	@file		profiles.c
 *
 *	@brief 		Profiles source file
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


#if (SBGC_PROFILES_MODULE)

#if (SYS_BIG_ENDIAN || SBGC_REF_INFO)

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *					Big Endian Mapping and Reference Info Structures
	 */
	/**	@addtogroup	Profile_Params_3
	 * 	@{
	 */
	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t mainParams3_ReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Profile ID",				_UNSIGNED_CHAR_				),  // 0
		PARAM_BLOCK_(	"P [ROLL]",					_UNSIGNED_CHAR_				),  // 1
		PARAM_BLOCK_(	"I [ROLL]",					_UNSIGNED_CHAR_				),  // 2
		PARAM_BLOCK_(	"D [ROLL]",					_UNSIGNED_CHAR_				),  // 3
		PARAM_BLOCK_(	"Power [ROLL]",				_UNSIGNED_CHAR_				),  // 4
		PARAM_BLOCK_(	"Invert [ROLL]",			_UNSIGNED_CHAR_				),  // 5
		PARAM_BLOCK_(	"Poles [ROLL]",				_UNSIGNED_CHAR_				),  // 6
		PARAM_BLOCK_(	"P [PITCH]",				_UNSIGNED_CHAR_				),  // 7
		PARAM_BLOCK_(	"I [PITCH]",				_UNSIGNED_CHAR_				),  // 8
		PARAM_BLOCK_(	"D [PITCH]",				_UNSIGNED_CHAR_				),  // 9
		PARAM_BLOCK_(	"Power [PITCH]",			_UNSIGNED_CHAR_				),  // 10
		PARAM_BLOCK_(	"Invert [PITCH]",			_UNSIGNED_CHAR_				),  // 11
		PARAM_BLOCK_(	"Poles [PITCH]",			_UNSIGNED_CHAR_				),  // 12
		PARAM_BLOCK_(	"P [YAW]",					_UNSIGNED_CHAR_				),  // 13
		PARAM_BLOCK_(	"I [YAW]",					_UNSIGNED_CHAR_				),  // 14
		PARAM_BLOCK_(	"D [YAW]",					_UNSIGNED_CHAR_				),  // 15
		PARAM_BLOCK_(	"Power [YAW]",				_UNSIGNED_CHAR_				),  // 16
		PARAM_BLOCK_(	"Invert [YAW]",				_UNSIGNED_CHAR_				),  // 17
		PARAM_BLOCK_(	"Poles [YAW]",				_UNSIGNED_CHAR_				),  // 18
		PARAM_BLOCK_(	"Acc Limiter All",			_UNSIGNED_CHAR_				),  // 19
		PARAMS_BLOCK_(	"Ext FC Gain",				_SIGNED_CHAR_,		2		),  // 20
		PARAM_BLOCK_(	"RC Min Angle [ROLL]",		_SIGNED_SHORT_				),  // 21
		PARAM_BLOCK_(	"RC Max Angle [ROLL]",		_SIGNED_SHORT_				),  // 22
		PARAM_BLOCK_(	"RC Mode [ROLL]",			_UNSIGNED_CHAR_				),  // 23
		PARAM_BLOCK_(	"RC LPF [ROLL]",			_UNSIGNED_CHAR_				),  // 24
		PARAM_BLOCK_(	"RC Speed [ROLL]",			_UNSIGNED_CHAR_				),  // 25
		PARAM_BLOCK_(	"RC Follow [ROLL]",			_SIGNED_CHAR_				),  // 26
		PARAM_BLOCK_(	"RC Min Angle [PITCH]",		_SIGNED_SHORT_				),  // 27
		PARAM_BLOCK_(	"RC Max Angle [PITCH]",		_SIGNED_SHORT_				),  // 28
		PARAM_BLOCK_(	"RC Mode [PITCH]",			_UNSIGNED_CHAR_				),  // 29
		PARAM_BLOCK_(	"RC LPF [PITCH]",			_UNSIGNED_CHAR_				),  // 30
		PARAM_BLOCK_(	"RC Speed [PITCH]",			_UNSIGNED_CHAR_				),  // 31
		PARAM_BLOCK_(	"RC Follow [PITCH]",		_SIGNED_CHAR_				),  // 32
		PARAM_BLOCK_(	"RC Min Angle [YAW]",		_SIGNED_SHORT_				),  // 33
		PARAM_BLOCK_(	"RC Max Angle [YAW]",		_SIGNED_SHORT_				),  // 34
		PARAM_BLOCK_(	"RC Mode [YAW]",			_UNSIGNED_CHAR_				),  // 35
		PARAM_BLOCK_(	"RC LPF [YAW]",				_UNSIGNED_CHAR_				),  // 36
		PARAM_BLOCK_(	"RC Speed [YAW]",			_UNSIGNED_CHAR_				),  // 37
		PARAM_BLOCK_(	"RC Follow [YAW]",			_SIGNED_CHAR_				),  // 38
		PARAM_BLOCK_(	"Gyro Trust",				_UNSIGNED_CHAR_				),  // 39
		PARAM_BLOCK_(	"Use Model",				_UNSIGNED_CHAR_				),  // 40
		PARAM_BLOCK_(	"PWM Freq",					_UNSIGNED_CHAR_				),  // 41
		PARAM_BLOCK_(	"Serial Speed",				_UNSIGNED_CHAR_				),  // 42
		PARAMS_BLOCK_(	"RC Trim",					_SIGNED_CHAR_,		3		),  // 43
		PARAM_BLOCK_(	"RC Dead Band",				_UNSIGNED_CHAR_				),  // 44
		PARAM_BLOCK_(	"RC Expo Rate",				_UNSIGNED_CHAR_				),  // 45
		PARAM_BLOCK_(	"RC Virt Mode",				_UNSIGNED_CHAR_				),  // 46
		PARAM_BLOCK_(	"RC Map ROLL",				_UNSIGNED_CHAR_				),  // 47
		PARAM_BLOCK_(	"RC Map PITCH",				_UNSIGNED_CHAR_				),  // 48
		PARAM_BLOCK_(	"RC Map YAW",				_UNSIGNED_CHAR_				),  // 49
		PARAM_BLOCK_(	"RC Map Cmd",				_UNSIGNED_CHAR_				),  // 50
		PARAM_BLOCK_(	"RC Map FC ROLL",			_UNSIGNED_CHAR_				),  // 51
		PARAM_BLOCK_(	"RC Map FC PITCH",			_UNSIGNED_CHAR_				),  // 52
		PARAM_BLOCK_(	"RC Mix FC ROLL",			_UNSIGNED_CHAR_				),  // 53
		PARAM_BLOCK_(	"RC Mix FC PITCH",			_UNSIGNED_CHAR_				),  // 54
		PARAM_BLOCK_(	"Follow Mode",				_UNSIGNED_CHAR_				),  // 55
		PARAM_BLOCK_(	"Follow Dead Band",			_UNSIGNED_CHAR_				),  // 56
		PARAM_BLOCK_(	"Follow Expo Rate",			_UNSIGNED_CHAR_				),  // 57
		PARAMS_BLOCK_(	"Follow Offset",			_SIGNED_CHAR_,		3		),  // 58
		PARAM_BLOCK_(	"Axis Top",					_SIGNED_CHAR_				),  // 59
		PARAM_BLOCK_(	"Axis Right",				_SIGNED_CHAR_				),  // 60
		PARAM_BLOCK_(	"Frame Axis Top",			_SIGNED_CHAR_				),  // 61
		PARAM_BLOCK_(	"Frame Axis Right",			_SIGNED_CHAR_				),  // 62
		PARAM_BLOCK_(	"Frame IMU Pos",			_UNSIGNED_CHAR_				),  // 63
		PARAM_BLOCK_(	"Gyro Dead Band",			_UNSIGNED_CHAR_				),  // 64
		PARAM_BLOCK_(	"Gyro Sens",				_UNSIGNED_CHAR_				),  // 65
		PARAM_BLOCK_(	"I2C Speed Fast",			_UNSIGNED_CHAR_				),  // 66
		PARAM_BLOCK_(	"Skip Gyro Calib",			_UNSIGNED_CHAR_				),  // 67
		PARAM_BLOCK_(	"RC Cmd Low",				_UNSIGNED_CHAR_				),  // 68
		PARAM_BLOCK_(	"RC Cmd Mid",				_UNSIGNED_CHAR_				),  // 69
		PARAM_BLOCK_(	"RC Cmd High",				_UNSIGNED_CHAR_				),  // 70
		PARAM_BLOCK_(	"Menu Btn Cmd 1",			_UNSIGNED_CHAR_				),  // 71
		PARAM_BLOCK_(	"Menu Btn Cmd 2",			_UNSIGNED_CHAR_				),  // 72
		PARAM_BLOCK_(	"Menu Btn Cmd 3",			_UNSIGNED_CHAR_				),  // 73
		PARAM_BLOCK_(	"Menu Btn Cmd 4",			_UNSIGNED_CHAR_				),  // 74
		PARAM_BLOCK_(	"Menu Btn Cmd 5",			_UNSIGNED_CHAR_				),  // 75
		PARAM_BLOCK_(	"Menu Btn Cmd Long",		_UNSIGNED_CHAR_				),  // 76
		PARAMS_BLOCK_(	"Motor Output",				_UNSIGNED_CHAR_,	3		),  // 77
		PARAM_BLOCK_(	"Bat Threshold Alarm",		_SIGNED_SHORT_				),  // 78
		PARAM_BLOCK_(	"Bat Threshold Motors",		_SIGNED_SHORT_				),  // 79
		PARAM_BLOCK_(	"Bat Comp Ref",				_SIGNED_SHORT_				),  // 80
		PARAM_BLOCK_(	"Beeper Modes",				_UNSIGNED_CHAR_				),  // 81
		PARAM_BLOCK_(	"Follow ROLL Mix Start",	_UNSIGNED_CHAR_				),  // 82
		PARAM_BLOCK_(	"Follow ROLL Mix Range",	_UNSIGNED_CHAR_				),  // 83
		PARAMS_BLOCK_(	"Booster Power",			_UNSIGNED_CHAR_,	3		),  // 84
		PARAMS_BLOCK_(	"Follow Speed",				_UNSIGNED_CHAR_,	3		),  // 85
		PARAM_BLOCK_(	"Frame Angle from Motors",	_UNSIGNED_CHAR_				),  // 86
		PARAMS_BLOCK_(	"RC Memory",				_SIGNED_SHORT_,		3		),  // 87
		PARAM_BLOCK_(	"Servo 1 Out",				_UNSIGNED_CHAR_				),  // 88
		PARAM_BLOCK_(	"Servo 2 Out",				_UNSIGNED_CHAR_				),  // 89
		PARAM_BLOCK_(	"Servo 3 Out",				_UNSIGNED_CHAR_				),  // 90
		PARAM_BLOCK_(	"Servo 4 Out",				_UNSIGNED_CHAR_				),  // 91
		PARAM_BLOCK_(	"Servo Rate",				_UNSIGNED_CHAR_				),  // 92
		PARAM_BLOCK_(	"Adaptive PID Enabled",		_UNSIGNED_CHAR_				),  // 93
		PARAM_BLOCK_(	"Adaptive PID Threshold",	_UNSIGNED_CHAR_				),  // 94
		PARAM_BLOCK_(	"Adaptive PID Rate",		_UNSIGNED_CHAR_				),  // 95
		PARAM_BLOCK_(	"Adaptive PID Recovery Factor",
													_UNSIGNED_CHAR_				),  // 96
		PARAMS_BLOCK_(	"Follow LPF",				_UNSIGNED_CHAR_,	3		),  // 97
		PARAM_BLOCK_(	"General Flags 1",			(_UNSIGNED_SHORT_ | _FLAG_)	),  // 98
		PARAM_BLOCK_(	"Profile Flags 1",			(_UNSIGNED_SHORT_ | _FLAG_)	),  // 99
		PARAM_BLOCK_(	"Spectrum Mode",			_UNSIGNED_CHAR_				),  // 100
		PARAM_BLOCK_(	"Order of Axes",			_UNSIGNED_CHAR_				),  // 101
		PARAM_BLOCK_(	"Euler Order",				_UNSIGNED_CHAR_				),  // 102
		PARAM_BLOCK_(	"Cur IMU",					_UNSIGNED_CHAR_				),  // 103
		PARAM_BLOCK_(	"Cur Profile ID",			_UNSIGNED_CHAR_				),  // 104

	};

	const ui8 mainParams3_ReferenceInfoArrayElCnt = countof_(mainParams3_ReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Profile_Params_Ext
	 * 	@{
	 */
	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t mainParamsExtReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Profile ID",				_UNSIGNED_CHAR_				),  // 0
		PARAM_BLOCK_(	"Notch Freq [ROLL]",		_UNSIGNED_CHAR_				),  // 1
		PARAM_BLOCK_(	"Notch Width [ROLL]",		_UNSIGNED_CHAR_				),  // 2
		PARAM_BLOCK_(	"Notch Freq [PITCH]",		_UNSIGNED_CHAR_				),  // 3
		PARAM_BLOCK_(	"Notch Width [PITCH]",		_UNSIGNED_CHAR_				),  // 4
		PARAM_BLOCK_(	"Notch Freq [YAW]",			_UNSIGNED_CHAR_				),  // 5
		PARAM_BLOCK_(	"Notch Width [YAW]",		_UNSIGNED_CHAR_				),  // 6
		PARAMS_BLOCK_(	"LPF Freq",					_UNSIGNED_SHORT_,	3		),  // 7
		PARAMS_BLOCK_(	"Filters En",				_UNSIGNED_CHAR_,	3		),  // 8
		PARAMS_BLOCK_(	"Encoder Offset",			_SIGNED_SHORT_,		3		),  // 9
		PARAMS_BLOCK_(	"Encoder Fld Offset",		_SIGNED_SHORT_,		3		),  // 10
		PARAMS_BLOCK_(	"Encoder Manual Set Time",	_UNSIGNED_CHAR_,	3		),  // 11
		PARAMS_BLOCK_(	"Motor Heating Factor",		_UNSIGNED_CHAR_,	3		),  // 12
		PARAMS_BLOCK_(	"Motor Cooling Factor",		_UNSIGNED_CHAR_,	3		),  // 13
		PARAMS_BLOCK_(	"Filters En",				_UNSIGNED_CHAR_,	3		),  // 14
		PARAMS_BLOCK_(	"Reserved",					_RESERVED_CHAR_,	2		),  // 15
		PARAM_BLOCK_(	"Follow Inside Dead Band",	_UNSIGNED_CHAR_				),  // 16
		PARAMS_BLOCK_(	"Motor Mag Link",			_UNSIGNED_CHAR_,	3		),  // 17
		PARAMS_BLOCK_(	"Motor Gearing",			_UNSIGNED_SHORT_,	3		),  // 18
		PARAMS_BLOCK_(	"Encoder Limit Min",		_SIGNED_CHAR_,		3		),  // 19
		PARAMS_BLOCK_(	"Encoder Limit Max",		_SIGNED_CHAR_,		3		),  // 20
		PARAMS_BLOCK_(	"Notch 1 Gain",				_SIGNED_CHAR_,		3		),  // 21
		PARAMS_BLOCK_(	"Notch 2 Gain",				_SIGNED_CHAR_,		3		),  // 22
		PARAMS_BLOCK_(	"Notch 3 Gain",				_SIGNED_CHAR_,		3		),  // 23
		PARAM_BLOCK_(	"Beeper Volume",			_UNSIGNED_CHAR_				),  // 24
		PARAMS_BLOCK_(	"Encoder Gear Ratio",		_UNSIGNED_SHORT_,	3		),  // 25
		PARAMS_BLOCK_(	"Encoder Type",				_UNSIGNED_CHAR_,	3		),  // 26
		PARAMS_BLOCK_(	"Encoder Cfg",				_UNSIGNED_CHAR_,	3		),  // 27
		PARAMS_BLOCK_(	"Outer P",					_UNSIGNED_CHAR_,	3		),  // 28
		PARAMS_BLOCK_(	"Outer I",					_UNSIGNED_CHAR_,	3		),  // 29
		PARAM_BLOCK_(	"Mag Axis Top",				_SIGNED_CHAR_				),  // 30
		PARAM_BLOCK_(	"Mag Axis Right",			_SIGNED_CHAR_				),  // 31
		PARAM_BLOCK_(	"Mag Trust",				_UNSIGNED_CHAR_				),  // 32
		PARAM_BLOCK_(	"Mag Declination",			_SIGNED_CHAR_				),  // 33
		PARAM_BLOCK_(	"Acc LPF Freq",				_UNSIGNED_SHORT_			),  // 34
		PARAMS_BLOCK_(	"D Term LPF Freq",			_UNSIGNED_CHAR_,	3		),  // 35

	};

	const ui8 mainParamsExtReferenceInfoArrayElCnt = countof_(mainParamsExtReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Profile_Params_Ext_2
	 * 	@{
	 */
	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t mainParamsExt2_ReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Profile ID",				_UNSIGNED_CHAR_				),  // 0
		PARAM_BLOCK_(	"MAV Src [CH0]",			_UNSIGNED_CHAR_				),  // 1
		PARAM_BLOCK_(	"MAV Sys ID [CH0]",			_UNSIGNED_CHAR_				),  // 2
		PARAM_BLOCK_(	"MAV Comp ID [CH0]",		_UNSIGNED_CHAR_				),  // 3
		PARAM_BLOCK_(	"MAV Cfg Flags [CH0]",		_UNSIGNED_CHAR_				),  // 4
		PARAMS_BLOCK_(	"MAV Reserved [CH0]",		_RESERVED_CHAR_,	4		),  // 5
		PARAM_BLOCK_(	"MAV Src [CH1]",			_UNSIGNED_CHAR_				),  // 6
		PARAM_BLOCK_(	"MAV Sys ID [CH1]",			_UNSIGNED_CHAR_				),  // 7
		PARAM_BLOCK_(	"MAV Comp ID [CH1]",		_UNSIGNED_CHAR_				),  // 8
		PARAM_BLOCK_(	"MAV Cfg Flags [CH1]",		_UNSIGNED_CHAR_				),  // 9
		PARAMS_BLOCK_(	"MAV Reserved [CH1]",		_RESERVED_CHAR_,	4		),  // 10
		PARAMS_BLOCK_(	"Motor Mag Link Fine",		_UNSIGNED_SHORT_,	3		),  // 11
		PARAMS_BLOCK_(	"Acc Limiter",				_UNSIGNED_CHAR_,	3		),  // 12
		PARAMS_BLOCK_(	"PID Gain",					_UNSIGNED_CHAR_,	3		),  // 13
		PARAM_BLOCK_(	"Frame IMU LPF Freq",		_UNSIGNED_CHAR_				),  // 14
		PARAM_BLOCK_(	"Auto PID Cfg",				_UNSIGNED_CHAR_				),  // 15
		PARAM_BLOCK_(	"Auto PID Gain",			_UNSIGNED_CHAR_				),  // 16
		PARAMS_BLOCK_(	"Frame Cam Angle Min",		_SIGNED_SHORT_,		3		),  // 17
		PARAMS_BLOCK_(	"Frame Cam Angle Max",		_SIGNED_SHORT_,		3		),  // 18
		PARAM_BLOCK_(	"General Flags 2",			(_UNSIGNED_SHORT_ | _FLAG_)	),  // 19
		PARAM_BLOCK_(	"Auto Speed",				_UNSIGNED_CHAR_				),  // 20
		PARAM_BLOCK_(	"Auto Acc Limiter",			_UNSIGNED_CHAR_				),  // 21
		PARAMS_BLOCK_(	"IMU Orientation Corr",		_SIGNED_SHORT_,		3		),  // 22
		PARAM_BLOCK_(	"Timelapse Time",			_UNSIGNED_SHORT_			),  // 23
		PARAM_BLOCK_(	"Emergency Stop Restart Delay",
													_UNSIGNED_SHORT_			),  // 24
		PARAM_BLOCK_(	"Timelapse Acc Part",		_UNSIGNED_CHAR_				),  // 25
		PARAMS_BLOCK_(	"Momentum",					_UNSIGNED_SHORT_,	3		),  // 26
		PARAMS_BLOCK_(	"Momentum Calib Stimulus",	_UNSIGNED_CHAR_,	3		),  // 27
		PARAMS_BLOCK_(	"Momentum Ellipticity",		_UNSIGNED_CHAR_,	3		),  // 28
		PARAMS_BLOCK_(	"Follow Range",				_UNSIGNED_CHAR_,	3		),  // 29
		PARAMS_BLOCK_(	"Stab Axis",				_UNSIGNED_CHAR_,	3		),  // 30
		PARAM_BLOCK_(	"Outer Mot Tilt Angle",		_SIGNED_CHAR_				),  // 31
		PARAMS_BLOCK_(	"Startup Action",			_UNSIGNED_CHAR_,	4		),  // 32
		PARAMS_BLOCK_(	"Startup Action Src",		_UNSIGNED_CHAR_,	8		),  // 33
		PARAMS_BLOCK_(	"Startup Action Threshold",	_SIGNED_CHAR_,		8		),  // 34
		PARAMS_BLOCK_(	"Stab Axis",				_UNSIGNED_CHAR_,	3		),  // 35
		PARAM_BLOCK_(	"Step Signal Src [#0]",		_UNSIGNED_CHAR_				),  // 36
		PARAM_BLOCK_(	"Step Signal Cfg [#0]",		_UNSIGNED_CHAR_				),  // 37
		PARAM_BLOCK_(	"Step Signal Src [#1]",		_UNSIGNED_CHAR_				),  // 38
		PARAM_BLOCK_(	"Step Signal Cfg [#1]",		_UNSIGNED_CHAR_				),  // 39
		PARAM_BLOCK_(	"Step Signal Src [#2]",		_UNSIGNED_CHAR_				),  // 40
		PARAM_BLOCK_(	"Step Signal Cfg [#2]",		_UNSIGNED_CHAR_				),  // 41
		PARAM_BLOCK_(	"Step Signal Src [#3]",		_UNSIGNED_CHAR_				),  // 42
		PARAM_BLOCK_(	"Step Signal Cfg [#3]",		_UNSIGNED_CHAR_				),  // 43
		PARAM_BLOCK_(	"Step Signal Src [#4]",		_UNSIGNED_CHAR_				),  // 44
		PARAM_BLOCK_(	"Step Signal Cfg [#4]",		_UNSIGNED_CHAR_				),  // 45
		PARAM_BLOCK_(	"Step Signal Src [#5]",		_UNSIGNED_CHAR_				),  // 46
		PARAM_BLOCK_(	"Step Signal Cfg [#5]",		_UNSIGNED_CHAR_				),  // 47
		PARAM_BLOCK_(	"RC Calib Src [#0]",		_UNSIGNED_CHAR_				),  // 48
		PARAM_BLOCK_(	"RC Calib Offset [#0]",		_SIGNED_CHAR_				),  // 49
		PARAM_BLOCK_(	"RC Calib Neg Scale [#0]",	_UNSIGNED_CHAR_				),  // 50
		PARAM_BLOCK_(	"RC Calib Pos Scale [#0]",	_UNSIGNED_CHAR_				),  // 51
		PARAM_BLOCK_(	"RC Calib Src [#1]",		_UNSIGNED_CHAR_				),  // 52
		PARAM_BLOCK_(	"RC Calib Offset [#1]",		_SIGNED_CHAR_				),  // 53
		PARAM_BLOCK_(	"RC Calib Neg Scale [#1]",	_UNSIGNED_CHAR_				),  // 54
		PARAM_BLOCK_(	"RC Calib Pos Scale [#1]",	_UNSIGNED_CHAR_				),  // 55
		PARAM_BLOCK_(	"RC Calib Src [#2]",		_UNSIGNED_CHAR_				),  // 56
		PARAM_BLOCK_(	"RC Calib Offset [#2]",		_SIGNED_CHAR_				),  // 57
		PARAM_BLOCK_(	"RC Calib Neg Scale [#2]",	_UNSIGNED_CHAR_				),  // 58
		PARAM_BLOCK_(	"RC Calib Pos Scale [#2]",	_UNSIGNED_CHAR_				),  // 59
		PARAM_BLOCK_(	"RC Calib Src [#3]",		_UNSIGNED_CHAR_				),  // 60
		PARAM_BLOCK_(	"RC Calib Offset [#3]",		_SIGNED_CHAR_				),  // 61
		PARAM_BLOCK_(	"RC Calib Neg Scale [#3]",	_UNSIGNED_CHAR_				),  // 62
		PARAM_BLOCK_(	"RC Calib Pos Scale [#3]",	_UNSIGNED_CHAR_				),  // 63
		PARAM_BLOCK_(	"RC Calib Src [#4]",		_UNSIGNED_CHAR_				),  // 64
		PARAM_BLOCK_(	"RC Calib Offset [#4]",		_SIGNED_CHAR_				),  // 65
		PARAM_BLOCK_(	"RC Calib Neg Scale [#4]",	_UNSIGNED_CHAR_				),  // 66
		PARAM_BLOCK_(	"RC Calib Pos Scale [#4]",	_UNSIGNED_CHAR_				),  // 67
		PARAM_BLOCK_(	"Parking Pos Cfg",			_UNSIGNED_CHAR_				),  // 68
		PARAM_BLOCK_(	"Ext LED Pin ID",			_UNSIGNED_CHAR_				),  // 69
		PARAM_BLOCK_(	"Interrupt Cfg",			_UNSIGNED_SHORT_			),  // 70
		PARAM_BLOCK_(	"Overload Time",			_UNSIGNED_CHAR_				),  // 71
		PARAM_BLOCK_(	"Auto PID Momentum",		_UNSIGNED_CHAR_				),  // 72
		PARAMS_BLOCK_(	"Jerk Slope",				_UNSIGNED_CHAR_,	3		),  // 73
		PARAM_BLOCK_(	"MAV Control Mode",			_UNSIGNED_CHAR_				),  // 74
		PARAM_BLOCK_(	"RC Serial Speed",			_UNSIGNED_CHAR_				),  // 75
		PARAM_BLOCK_(	"UART2 Speed",				_UNSIGNED_CHAR_				),  // 76
		PARAMS_BLOCK_(	"Motor Res",				_UNSIGNED_CHAR_,	3		),  // 77
		PARAM_BLOCK_(	"Current Limit",			_UNSIGNED_SHORT_			),  // 78
		PARAM_BLOCK_(	"Middle Mot Tilt Angle",	_SIGNED_CHAR_				),  // 79

	};

	const ui8 mainParamsExt2_ReferenceInfoArrayElCnt = countof_(mainParamsExt2_ReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Profile_Params_Ext_3
	 * 	@{
	 */
	/** @brief	Sample for big endian mapping and reference info
	 */
	const ParameterReferenceInfo_t mainParamsExt3_ReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Profile ID",				_UNSIGNED_CHAR_				),  // 0
		PARAMS_BLOCK_(	"Reserved 1",				_RESERVED_CHAR_,	21		),  // 1
		PARAM_BLOCK_(	"Ext IMU Type",				_UNSIGNED_CHAR_				),  // 2
		PARAM_BLOCK_(	"Ext IMU Port",				_UNSIGNED_CHAR_				),  // 3
		PARAM_BLOCK_(	"Ext IMU Position",			_UNSIGNED_CHAR_				),  // 4
		PARAM_BLOCK_(	"Ext IMU Orientation",		_UNSIGNED_CHAR_				),  // 5
		PARAM_BLOCK_(	"Ext IMU Flags",			(_UNSIGNED_SHORT_ | _FLAG_)	),  // 6
		PARAMS_BLOCK_(	"Ext IMU Reserved",			_RESERVED_CHAR_,	12		),  // 7
		PARAMS_BLOCK_(	"Soft Limit Width",			_UNSIGNED_CHAR_,	3		),  // 8
		PARAMS_BLOCK_(	"ADC Replace Src",			_UNSIGNED_CHAR_,	3		),  // 9
		PARAM_BLOCK_(	"Glock Mid Mot Pos Corr Rate",
													_UNSIGNED_CHAR_				),  // 10
		PARAMS_BLOCK_(	"Extra Btn Cfg",			_UNSIGNED_CHAR_,	5		),  // 11
		PARAMS_BLOCK_(	"Power Ctrl Cfg",			_UNSIGNED_CHAR_,	8		),  // 12
		PARAMS_BLOCK_(	"Reserved 2",				_RESERVED_CHAR_,	3		),  // 13

		PARAM_BLOCK_(	"CAN IMU Ext Sens Type",	_UNSIGNED_CHAR_				),  // 14
		PARAM_BLOCK_(	"Profile Flags 2",			(_UNSIGNED_SHORT_ | _FLAG_)	),  // 15
		PARAMS_BLOCK_(	"Reserved 3",				_RESERVED_CHAR_,	3		),  // 16
		PARAM_BLOCK_(	"General Flags 3",			(_UNSIGNED_INT_ | _FLAG_)	),  // 17
		PARAMS_BLOCK_(	"Follow Offset Ext",		_SIGNED_SHORT_,		3		),  // 18
		PARAM_BLOCK_(	"Motor Startup Delay",		_UNSIGNED_SHORT_			),  // 19
		PARAMS_BLOCK_(	"Reserved 4",				_RESERVED_CHAR_,	140		),  // 20

	};

	const ui8 mainParamsExt3_ReferenceInfoArrayElCnt = countof_(mainParamsExt3_ReferenceInfoArray);
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
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_ManageProfileSet (GeneralSBGC_t *generalSBGC, Profile_t slot, ProfileSetAction_t action)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_PROFILE_SET);
	WriteByte(&cmd, ++slot);  // 1..5: regular slots, 6 – backup slot
	WriteByte(&cmd, action);
	WriteEmptyBuff(&cmd, 8);  // reserved[8]
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Action required before and after uploading profile settings
 *
 * 	@attention	Firmware: 2.70b4+
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	action - stop/start operation
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_WriteParamsSet (GeneralSBGC_t *generalSBGC, ProfileWritingFlag_t action)
{
	#if (SBGC_DEBUG_MODE == SET_OFF)

		if (generalSBGC->_firmwareVersion < 2704)
			return NOT_SUPPORTED_BY_FIRMWARE;

	#endif

	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_WRITE_PARAMS_SET);
	WriteByte(&cmd, action);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
}


/**	@brief	Writes profile names to EEPROM
 *
 *	@param	*generalSBGC - serial connection descriptor
 *	@param	*profileNames - structure with written profile names
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_WriteProfileNames (GeneralSBGC_t *generalSBGC, const ProfileNames_t *profileNames)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_WRITE_PROFILE_NAMES);
	WriteBuff(&cmd, profileNames, sizeof(ProfileNames_t), PM_DEFAULT_8BIT);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
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

	return generalSBGC->_parserCurrentStatus;
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
	return generalSBGC->_parserCurrentStatus;
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
 *
 *	@note	MainParams3_t.profileID is target profile slot\n
 *			After writing this profile will be active
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_WriteParams3 (GeneralSBGC_t *generalSBGC, const MainParams3_t *mainParams3)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_WRITE_PARAMS_3);
	WriteBuff(&cmd, mainParams3, sizeof(MainParams3_t), PM_MAIN_PARAMS_3);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
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

	return generalSBGC->_parserCurrentStatus;
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
 *
 *	@note	MainParamsExt_t.profileID is target profile slot\n
 *			After writing this profile will be active
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_WriteParamsExt (GeneralSBGC_t *generalSBGC, const MainParamsExt_t *mainParamsExt)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_WRITE_PARAMS_EXT);
	WriteBuff(&cmd, mainParamsExt, sizeof(MainParamsExt_t), PM_MAIN_PARAMS_EXT);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
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

	return generalSBGC->_parserCurrentStatus;
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
 *
 *	@note	MainParamsExt2_t.profileID is target profile slot\n
 *			After writing this profile will be active
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_WriteParamsExt2 (GeneralSBGC_t *generalSBGC, const MainParamsExt2_t *mainParamsExt2)
{
	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_WRITE_PARAMS_EXT2);
	WriteBuff(&cmd, mainParamsExt2, sizeof(MainParamsExt2_t), PM_MAIN_PARAMS_EXT_2);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
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

	return generalSBGC->_parserCurrentStatus;
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
 *
 *	@note	MainParamsExt3_t.profileID is target profile slot\n
 *			After writing this profile will be active
 *
 *	@return Communication status
 */
TxRxStatus_t SBGC32_WriteParamsExt3 (GeneralSBGC_t *generalSBGC, const MainParamsExt3_t *mainParamsExt3)
{
	#if (SBGC_DEBUG_MODE == SET_OFF)

		if (generalSBGC->_firmwareVersion < 2660)
			return NOT_SUPPORTED_BY_FIRMWARE;

	#endif

	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_WRITE_PARAMS_EXT3);
	WriteBuff(&cmd, mainParamsExt3, sizeof(MainParamsExt3_t), PM_MAIN_PARAMS_EXT_3);
	SBGC32_TX(generalSBGC, &cmd);
	SBGC32_CheckConfirmation(generalSBGC, cmd.commandID);
	return generalSBGC->_parserCurrentStatus;
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
	#if (SBGC_DEBUG_MODE == SET_OFF)

		if (generalSBGC->_firmwareVersion < 2660)
			return NOT_SUPPORTED_BY_FIRMWARE;

	#endif

	SerialCommand_t cmd;
	InitCmdWrite(&cmd, CMD_READ_PARAMS_EXT3);
	WriteByte(&cmd, profileN);

	if (CheckReceipt(generalSBGC, SBGC32_TX_RX(generalSBGC, &cmd, CMD_READ_PARAMS_EXT3), "Main Parameters Ext 3:") == TX_RX_OK)
		ReadBuff(&cmd, mainParamsExt3, sizeof(MainParamsExt3_t), PM_MAIN_PARAMS_EXT_3);

	return generalSBGC->_parserCurrentStatus;
}
/**	@}
 */

#endif /* SBGC_PROFILES_MODULE */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
