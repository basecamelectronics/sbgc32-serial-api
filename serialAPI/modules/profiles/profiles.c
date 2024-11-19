/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.1
 *
 *	@file		profiles.c
 *
 *	@brief		Profiles source file
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


#if (SBGC_PROFILES_MODULE)

#if (SBGC_USES_REF_INFO)

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 *					Big Endian Mapping and Reference Info Structures
	 */
	/**	@addtogroup	Profile_Params_3
	 *	@{
	 */
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t mainParams3_ReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Profile ID",				sbgcUCHAR						),  // 0
		PARAM_BLOCK_(	"P [ROLL]",					sbgcUCHAR						),  // 1
		PARAM_BLOCK_(	"I [ROLL]",					sbgcUCHAR						),  // 2
		PARAM_BLOCK_(	"D [ROLL]",					sbgcUCHAR						),  // 3
		PARAM_BLOCK_(	"Power [ROLL]",				sbgcUCHAR						),  // 4
		PARAM_BLOCK_(	"Invert [ROLL]",			sbgcUCHAR						),  // 5
		PARAM_BLOCK_(	"Poles [ROLL]",				sbgcUCHAR						),  // 6
		PARAM_BLOCK_(	"P [PITCH]",				sbgcUCHAR						),  // 7
		PARAM_BLOCK_(	"I [PITCH]",				sbgcUCHAR						),  // 8
		PARAM_BLOCK_(	"D [PITCH]",				sbgcUCHAR						),  // 9
		PARAM_BLOCK_(	"Power [PITCH]",			sbgcUCHAR						),  // 10
		PARAM_BLOCK_(	"Invert [PITCH]",			sbgcUCHAR						),  // 11
		PARAM_BLOCK_(	"Poles [PITCH]",			sbgcUCHAR						),  // 12
		PARAM_BLOCK_(	"P [YAW]",					sbgcUCHAR						),  // 13
		PARAM_BLOCK_(	"I [YAW]",					sbgcUCHAR						),  // 14
		PARAM_BLOCK_(	"D [YAW]",					sbgcUCHAR						),  // 15
		PARAM_BLOCK_(	"Power [YAW]",				sbgcUCHAR						),  // 16
		PARAM_BLOCK_(	"Invert [YAW]",				sbgcUCHAR						),  // 17
		PARAM_BLOCK_(	"Poles [YAW]",				sbgcUCHAR						),  // 18
		PARAM_BLOCK_(	"Acc Limiter All",			sbgcUCHAR						),  // 19
		PARAMS_BLOCK_(	"Ext FC Gain",				sbgcCHAR,					2	),  // 20
		PARAM_BLOCK_(	"RC Min Angle [ROLL]",		sbgcSHORT						),  // 21
		PARAM_BLOCK_(	"RC Max Angle [ROLL]",		sbgcSHORT						),  // 22
		PARAM_BLOCK_(	"RC Mode [ROLL]",			sbgcUCHAR						),  // 23
		PARAM_BLOCK_(	"RC LPF [ROLL]",			sbgcUCHAR						),  // 24
		PARAM_BLOCK_(	"RC Speed [ROLL]",			sbgcUCHAR						),  // 25
		PARAM_BLOCK_(	"RC Follow [ROLL]",			sbgcCHAR						),  // 26
		PARAM_BLOCK_(	"RC Min Angle [PITCH]",		sbgcSHORT						),  // 27
		PARAM_BLOCK_(	"RC Max Angle [PITCH]",		sbgcSHORT						),  // 28
		PARAM_BLOCK_(	"RC Mode [PITCH]",			sbgcUCHAR						),  // 29
		PARAM_BLOCK_(	"RC LPF [PITCH]",			sbgcUCHAR						),  // 30
		PARAM_BLOCK_(	"RC Speed [PITCH]",			sbgcUCHAR						),  // 31
		PARAM_BLOCK_(	"RC Follow [PITCH]",		sbgcCHAR						),  // 32
		PARAM_BLOCK_(	"RC Min Angle [YAW]",		sbgcSHORT						),  // 33
		PARAM_BLOCK_(	"RC Max Angle [YAW]",		sbgcSHORT						),  // 34
		PARAM_BLOCK_(	"RC Mode [YAW]",			sbgcUCHAR						),  // 35
		PARAM_BLOCK_(	"RC LPF [YAW]",				sbgcUCHAR						),  // 36
		PARAM_BLOCK_(	"RC Speed [YAW]",			sbgcUCHAR						),  // 37
		PARAM_BLOCK_(	"RC Follow [YAW]",			sbgcCHAR						),  // 38
		PARAM_BLOCK_(	"Gyro Trust",				sbgcUCHAR						),  // 39
		PARAM_BLOCK_(	"Use Model",				sbgcUCHAR						),  // 40
		PARAM_BLOCK_(	"PWM Freq",					sbgcUCHAR						),  // 41
		PARAM_BLOCK_(	"Serial Speed",				sbgcUCHAR						),  // 42
		PARAMS_BLOCK_(	"RC Trim",					sbgcCHAR,					3	),  // 43
		PARAM_BLOCK_(	"RC Dead Band",				sbgcUCHAR						),  // 44
		PARAM_BLOCK_(	"RC Expo Rate",				sbgcUCHAR						),  // 45
		PARAM_BLOCK_(	"RC Virt Mode",				sbgcUCHAR						),  // 46
		PARAM_BLOCK_(	"RC Map ROLL",				sbgcUCHAR						),  // 47
		PARAM_BLOCK_(	"RC Map PITCH",				sbgcUCHAR						),  // 48
		PARAM_BLOCK_(	"RC Map YAW",				sbgcUCHAR						),  // 49
		PARAM_BLOCK_(	"RC Map cmdTx",				sbgcUCHAR						),  // 50
		PARAM_BLOCK_(	"RC Map FC ROLL",			sbgcUCHAR						),  // 51
		PARAM_BLOCK_(	"RC Map FC PITCH",			sbgcUCHAR						),  // 52
		PARAM_BLOCK_(	"RC Mix FC ROLL",			sbgcUCHAR						),  // 53
		PARAM_BLOCK_(	"RC Mix FC PITCH",			sbgcUCHAR						),  // 54
		PARAM_BLOCK_(	"Follow Mode",				sbgcUCHAR						),  // 55
		PARAM_BLOCK_(	"Follow Dead Band",			sbgcUCHAR						),  // 56
		PARAM_BLOCK_(	"Follow Expo Rate",			sbgcUCHAR						),  // 57
		PARAMS_BLOCK_(	"Follow Offset",			sbgcCHAR,					3	),  // 58
		PARAM_BLOCK_(	"Axis Top",					sbgcCHAR						),  // 59
		PARAM_BLOCK_(	"Axis Right",				sbgcCHAR						),  // 60
		PARAM_BLOCK_(	"Frame Axis Top",			sbgcCHAR						),  // 61
		PARAM_BLOCK_(	"Frame Axis Right",			sbgcCHAR						),  // 62
		PARAM_BLOCK_(	"Frame IMU Pos",			sbgcUCHAR						),  // 63
		PARAM_BLOCK_(	"Gyro Dead Band",			sbgcUCHAR						),  // 64
		PARAM_BLOCK_(	"Gyro Sens",				sbgcUCHAR						),  // 65
		PARAM_BLOCK_(	"I2C Speed Fast",			sbgcUCHAR						),  // 66
		PARAM_BLOCK_(	"Skip Gyro Calib",			sbgcUCHAR						),  // 67
		PARAM_BLOCK_(	"RC cmdTx Low",				sbgcUCHAR						),  // 68
		PARAM_BLOCK_(	"RC cmdTx Mid",				sbgcUCHAR						),  // 69
		PARAM_BLOCK_(	"RC cmdTx High",			sbgcUCHAR						),  // 70
		PARAM_BLOCK_(	"Menu Btn cmdTx 1",			sbgcUCHAR						),  // 71
		PARAM_BLOCK_(	"Menu Btn cmdTx 2",			sbgcUCHAR						),  // 72
		PARAM_BLOCK_(	"Menu Btn cmdTx 3",			sbgcUCHAR						),  // 73
		PARAM_BLOCK_(	"Menu Btn cmdTx 4",			sbgcUCHAR						),  // 74
		PARAM_BLOCK_(	"Menu Btn cmdTx 5",			sbgcUCHAR						),  // 75
		PARAM_BLOCK_(	"Menu Btn cmdTx Long",		sbgcUCHAR						),  // 76
		PARAMS_BLOCK_(	"Motor Output",				sbgcUCHAR,					3	),  // 77
		PARAM_BLOCK_(	"Bat Threshold Alarm",		sbgcSHORT						),  // 78
		PARAM_BLOCK_(	"Bat Threshold Motors",		sbgcSHORT						),  // 79
		PARAM_BLOCK_(	"Bat Comp Ref",				sbgcSHORT						),  // 80
		PARAM_BLOCK_(	"Beeper Modes",				sbgcUCHAR						),  // 81
		PARAM_BLOCK_(	"Follow ROLL Mix Start",	sbgcUCHAR						),  // 82
		PARAM_BLOCK_(	"Follow ROLL Mix Range",	sbgcUCHAR						),  // 83
		PARAMS_BLOCK_(	"Booster Power",			sbgcUCHAR,					3	),  // 84
		PARAMS_BLOCK_(	"Follow Speed",				sbgcUCHAR,					3	),  // 85
		PARAM_BLOCK_(	"Frame Angle from Motors",	sbgcUCHAR						),  // 86
		PARAMS_BLOCK_(	"RC Memory",				sbgcSHORT,					3	),  // 87
		PARAM_BLOCK_(	"Servo 1 Out",				sbgcUCHAR						),  // 88
		PARAM_BLOCK_(	"Servo 2 Out",				sbgcUCHAR						),  // 89
		PARAM_BLOCK_(	"Servo 3 Out",				sbgcUCHAR						),  // 90
		PARAM_BLOCK_(	"Servo 4 Out",				sbgcUCHAR						),  // 91
		PARAM_BLOCK_(	"Servo Rate",				sbgcUCHAR						),  // 92
		PARAM_BLOCK_(	"Adaptive PID Enabled",		sbgcUCHAR						),  // 93
		PARAM_BLOCK_(	"Adaptive PID Threshold",	sbgcUCHAR						),  // 94
		PARAM_BLOCK_(	"Adaptive PID Rate",		sbgcUCHAR						),  // 95
		PARAM_BLOCK_(	"Adaptive PID Recovery Factor",
													sbgcUCHAR						),  // 96
		PARAMS_BLOCK_(	"Follow LPF",				sbgcUCHAR,					3	),  // 97
		PARAM_BLOCK_(	"General Flags 1",			(sbgcUSHORT | sbgcFLAG)			),  // 98
		PARAM_BLOCK_(	"Profile Flags 1",			(sbgcUSHORT | sbgcFLAG)			),  // 99
		PARAM_BLOCK_(	"Spectrum Mode",			sbgcUCHAR						),  // 100
		PARAM_BLOCK_(	"Order of Axes",			sbgcUCHAR						),  // 101
		PARAM_BLOCK_(	"Euler Order",				sbgcUCHAR						),  // 102
		PARAM_BLOCK_(	"Cur IMU",					sbgcUCHAR						),  // 103
		PARAM_BLOCK_(	"Cur Profile ID",			sbgcUCHAR						),  // 104

	};

	const ui8 mainParams3_ReferenceInfoArrayElCnt = countof_(mainParams3_ReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Profile_Params_Ext
	 *	@{
	 */
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t mainParamsExtReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Profile ID",				sbgcUCHAR						),  // 0
		PARAMS_BLOCK_(	"Notch Freq [ROLL]",		sbgcUCHAR,					3	),  // 1
		PARAMS_BLOCK_(	"Notch Width [ROLL]",		sbgcUCHAR,					3	),  // 2
		PARAMS_BLOCK_(	"Notch Freq [PITCH]",		sbgcUCHAR,					3	),  // 3
		PARAMS_BLOCK_(	"Notch Width [PITCH]",		sbgcUCHAR,					3	),  // 4
		PARAMS_BLOCK_(	"Notch Freq [YAW]",			sbgcUCHAR,					3	),  // 5
		PARAMS_BLOCK_(	"Notch Width [YAW]",		sbgcUCHAR,					3	),  // 6
		PARAMS_BLOCK_(	"LPF Freq",					sbgcUSHORT,					3	),  // 7
		PARAMS_BLOCK_(	"Filters En",				sbgcUCHAR,					3	),  // 8
		PARAMS_BLOCK_(	"Encoder Offset",			sbgcSHORT,					3	),  // 9
		PARAMS_BLOCK_(	"Encoder Fld Offset",		sbgcSHORT,					3	),  // 10
		PARAMS_BLOCK_(	"Encoder Manual Set Time",	sbgcUCHAR,					3	),  // 11
		PARAMS_BLOCK_(	"Motor Heating Factor",		sbgcUCHAR,					3	),  // 12
		PARAMS_BLOCK_(	"Motor Cooling Factor",		sbgcUCHAR,					3	),  // 13
		PARAMS_BLOCK_(	"Reserved",					sbgcRCHAR,					2	),  // 14
		PARAM_BLOCK_(	"Follow Inside Dead Band",	sbgcUCHAR						),  // 15
		PARAMS_BLOCK_(	"Motor Mag Link",			sbgcUCHAR,					3	),  // 16
		PARAMS_BLOCK_(	"Motor Gearing",			sbgcUSHORT,					3	),  // 17
		PARAMS_BLOCK_(	"Encoder Limit Min",		sbgcCHAR,					3	),  // 18
		PARAMS_BLOCK_(	"Encoder Limit Max",		sbgcCHAR,					3	),  // 19
		PARAMS_BLOCK_(	"Notch 1 Gain",				sbgcCHAR,					3	),  // 20
		PARAMS_BLOCK_(	"Notch 2 Gain",				sbgcCHAR,					3	),  // 21
		PARAMS_BLOCK_(	"Notch 3 Gain",				sbgcCHAR,					3	),  // 22
		PARAM_BLOCK_(	"Beeper Volume",			sbgcUCHAR						),  // 23
		PARAMS_BLOCK_(	"Encoder Gear Ratio",		sbgcUSHORT,					3	),  // 24
		PARAMS_BLOCK_(	"Encoder Type",				sbgcUCHAR,					3	),  // 25
		PARAMS_BLOCK_(	"Encoder Cfg",				sbgcUCHAR,					3	),  // 26
		PARAMS_BLOCK_(	"Outer P",					sbgcUCHAR,					3	),  // 27
		PARAMS_BLOCK_(	"Outer I",					sbgcUCHAR,					3	),  // 28
		PARAM_BLOCK_(	"Mag Axis Top",				sbgcCHAR						),  // 29
		PARAM_BLOCK_(	"Mag Axis Right",			sbgcCHAR						),  // 30
		PARAM_BLOCK_(	"Mag Trust",				sbgcUCHAR						),  // 31
		PARAM_BLOCK_(	"Mag Declination",			sbgcCHAR						),  // 32
		PARAM_BLOCK_(	"Acc LPF Freq",				sbgcUSHORT						),  // 33
		PARAMS_BLOCK_(	"D Term LPF Freq",			sbgcUCHAR,					3	),  // 34

	};

	const ui8 mainParamsExtReferenceInfoArrayElCnt = countof_(mainParamsExtReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Profile_Params_Ext_2
	 *	@{
	 */
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t mainParamsExt2_ReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Profile ID",				sbgcUCHAR						),  // 0
		PARAM_BLOCK_(	"MAV Src [CH0]",			sbgcUCHAR						),  // 1
		PARAM_BLOCK_(	"MAV Sys ID [CH0]",			sbgcUCHAR						),  // 2
		PARAM_BLOCK_(	"MAV Comp ID [CH0]",		sbgcUCHAR						),  // 3
		PARAM_BLOCK_(	"MAV Cfg Flags [CH0]",		sbgcUCHAR						),  // 4
		PARAMS_BLOCK_(	"MAV Reserved [CH0]",		sbgcRCHAR,					4	),  // 5
		PARAM_BLOCK_(	"MAV Src [CH1]",			sbgcUCHAR						),  // 6
		PARAM_BLOCK_(	"MAV Sys ID [CH1]",			sbgcUCHAR						),  // 7
		PARAM_BLOCK_(	"MAV Comp ID [CH1]",		sbgcUCHAR						),  // 8
		PARAM_BLOCK_(	"MAV Cfg Flags [CH1]",		sbgcUCHAR						),  // 9
		PARAMS_BLOCK_(	"MAV Reserved [CH1]",		sbgcRCHAR,					4	),  // 10
		PARAMS_BLOCK_(	"Motor Mag Link Fine",		sbgcUSHORT,					3	),  // 11
		PARAMS_BLOCK_(	"Acc Limiter",				sbgcUCHAR,					3	),  // 12
		PARAMS_BLOCK_(	"PID Gain",					sbgcUCHAR,					3	),  // 13
		PARAM_BLOCK_(	"Frame IMU LPF Freq",		sbgcUCHAR						),  // 14
		PARAM_BLOCK_(	"Auto PID Cfg",				sbgcUCHAR						),  // 15
		PARAM_BLOCK_(	"Auto PID Gain",			sbgcUCHAR						),  // 16
		PARAMS_BLOCK_(	"Frame Cam Angle Min",		sbgcSHORT,					3	),  // 17
		PARAMS_BLOCK_(	"Frame Cam Angle Max",		sbgcSHORT,					3	),  // 18
		PARAM_BLOCK_(	"General Flags 2",			(sbgcUSHORT | sbgcFLAG)			),  // 19
		PARAM_BLOCK_(	"Auto Speed",				sbgcUCHAR						),  // 20
		PARAM_BLOCK_(	"Auto Acc Limiter",			sbgcUCHAR						),  // 21
		PARAMS_BLOCK_(	"IMU Orientation Corr",		sbgcSHORT,					3	),  // 22
		PARAM_BLOCK_(	"Timelapse Time",			sbgcUSHORT						),  // 23
		PARAM_BLOCK_(	"Emergency Stop Restart Delay",
													sbgcUSHORT						),  // 24
		PARAM_BLOCK_(	"Timelapse Acc Part",		sbgcUCHAR						),  // 25
		PARAMS_BLOCK_(	"Momentum",					sbgcUSHORT,					3	),  // 26
		PARAMS_BLOCK_(	"Momentum Calib Stimulus",	sbgcUCHAR,					3	),  // 27
		PARAMS_BLOCK_(	"Momentum Ellipticity",		sbgcUCHAR,					3	),  // 28
		PARAMS_BLOCK_(	"Follow Range",				sbgcUCHAR,					3	),  // 29
		PARAMS_BLOCK_(	"Stab Axis",				sbgcUCHAR,					3	),  // 30
		PARAM_BLOCK_(	"Outer Mot Tilt Angle",		sbgcCHAR						),  // 31
		PARAMS_BLOCK_(	"Startup Action",			sbgcUCHAR,					4	),  // 32
		PARAMS_BLOCK_(	"Startup Action Src",		sbgcUCHAR,					8	),  // 33
		PARAMS_BLOCK_(	"Startup Action Threshold",	sbgcCHAR,					8	),  // 34
		PARAMS_BLOCK_(	"Stab Axis",				sbgcUCHAR,					3	),  // 35
		PARAM_BLOCK_(	"Step Signal Src [#0]",		sbgcUCHAR						),  // 36
		PARAM_BLOCK_(	"Step Signal Cfg [#0]",		sbgcUCHAR						),  // 37
		PARAM_BLOCK_(	"Step Signal Src [#1]",		sbgcUCHAR						),  // 38
		PARAM_BLOCK_(	"Step Signal Cfg [#1]",		sbgcUCHAR						),  // 39
		PARAM_BLOCK_(	"Step Signal Src [#2]",		sbgcUCHAR						),  // 40
		PARAM_BLOCK_(	"Step Signal Cfg [#2]",		sbgcUCHAR						),  // 41
		PARAM_BLOCK_(	"Step Signal Src [#3]",		sbgcUCHAR						),  // 42
		PARAM_BLOCK_(	"Step Signal Cfg [#3]",		sbgcUCHAR						),  // 43
		PARAM_BLOCK_(	"Step Signal Src [#4]",		sbgcUCHAR						),  // 44
		PARAM_BLOCK_(	"Step Signal Cfg [#4]",		sbgcUCHAR						),  // 45
		PARAM_BLOCK_(	"Step Signal Src [#5]",		sbgcUCHAR						),  // 46
		PARAM_BLOCK_(	"Step Signal Cfg [#5]",		sbgcUCHAR						),  // 47
		PARAM_BLOCK_(	"RC Calib Src [#0]",		sbgcUCHAR						),  // 48
		PARAM_BLOCK_(	"RC Calib Offset [#0]",		sbgcCHAR						),  // 49
		PARAM_BLOCK_(	"RC Calib Neg Scale [#0]",	sbgcUCHAR						),  // 50
		PARAM_BLOCK_(	"RC Calib Pos Scale [#0]",	sbgcUCHAR						),  // 51
		PARAM_BLOCK_(	"RC Calib Src [#1]",		sbgcUCHAR						),  // 52
		PARAM_BLOCK_(	"RC Calib Offset [#1]",		sbgcCHAR						),  // 53
		PARAM_BLOCK_(	"RC Calib Neg Scale [#1]",	sbgcUCHAR						),  // 54
		PARAM_BLOCK_(	"RC Calib Pos Scale [#1]",	sbgcUCHAR						),  // 55
		PARAM_BLOCK_(	"RC Calib Src [#2]",		sbgcUCHAR						),  // 56
		PARAM_BLOCK_(	"RC Calib Offset [#2]",		sbgcCHAR						),  // 57
		PARAM_BLOCK_(	"RC Calib Neg Scale [#2]",	sbgcUCHAR						),  // 58
		PARAM_BLOCK_(	"RC Calib Pos Scale [#2]",	sbgcUCHAR						),  // 59
		PARAM_BLOCK_(	"RC Calib Src [#3]",		sbgcUCHAR						),  // 60
		PARAM_BLOCK_(	"RC Calib Offset [#3]",		sbgcCHAR						),  // 61
		PARAM_BLOCK_(	"RC Calib Neg Scale [#3]",	sbgcUCHAR						),  // 62
		PARAM_BLOCK_(	"RC Calib Pos Scale [#3]",	sbgcUCHAR						),  // 63
		PARAM_BLOCK_(	"RC Calib Src [#4]",		sbgcUCHAR						),  // 64
		PARAM_BLOCK_(	"RC Calib Offset [#4]",		sbgcCHAR						),  // 65
		PARAM_BLOCK_(	"RC Calib Neg Scale [#4]",	sbgcUCHAR						),  // 66
		PARAM_BLOCK_(	"RC Calib Pos Scale [#4]",	sbgcUCHAR						),  // 67
		PARAM_BLOCK_(	"Parking Pos Cfg",			sbgcUCHAR						),  // 68
		PARAM_BLOCK_(	"Ext LED Pin ID",			sbgcUCHAR						),  // 69
		PARAM_BLOCK_(	"Interrupt Cfg",			sbgcUSHORT						),  // 70
		PARAM_BLOCK_(	"Overload Time",			sbgcUCHAR						),  // 71
		PARAM_BLOCK_(	"Auto PID Momentum",		sbgcUCHAR						),  // 72
		PARAMS_BLOCK_(	"Jerk Slope",				sbgcUCHAR,					3	),  // 73
		PARAM_BLOCK_(	"MAV Control Mode",			sbgcUCHAR						),  // 74
		PARAM_BLOCK_(	"RC Serial Speed",			sbgcUCHAR						),  // 75
		PARAM_BLOCK_(	"UART2 Speed",				sbgcUCHAR						),  // 76
		PARAMS_BLOCK_(	"Motor Res",				sbgcUCHAR,					3	),  // 77
		PARAM_BLOCK_(	"Current Limit",			sbgcUSHORT						),  // 78
		PARAM_BLOCK_(	"Middle Mot Tilt Angle",	sbgcCHAR						),  // 79

	};

	const ui8 mainParamsExt2_ReferenceInfoArrayElCnt = countof_(mainParamsExt2_ReferenceInfoArray);
	/**	@}
	 */


	/**	@addtogroup	Profile_Params_Ext_3
	 *	@{
	 */
	/**	@brief	Sample for big endian mapping and reference info
	 */
	const sbgcParameterReferenceInfo_t mainParamsExt3_ReferenceInfoArray [] =
	{
		PARAM_BLOCK_(	"Profile ID",				sbgcUCHAR						),  // 0
		PARAMS_BLOCK_(	"Reserved 1",				sbgcRCHAR,					21	),  // 1
		PARAM_BLOCK_(	"Ext IMU Type",				sbgcUCHAR						),  // 2
		PARAM_BLOCK_(	"Ext IMU Port",				sbgcUCHAR						),  // 3
		PARAM_BLOCK_(	"Ext IMU Position",			sbgcUCHAR						),  // 4
		PARAM_BLOCK_(	"Ext IMU Orientation",		sbgcUCHAR						),  // 5
		PARAM_BLOCK_(	"Ext IMU Flags",			(sbgcUSHORT | sbgcFLAG)			),  // 6
		PARAMS_BLOCK_(	"Ext IMU Reserved",			sbgcRCHAR,					12	),  // 7
		PARAMS_BLOCK_(	"Soft Limit Width",			sbgcUCHAR,					3	),  // 8
		PARAMS_BLOCK_(	"ADC Replace Src",			sbgcUCHAR,					3	),  // 9
		PARAM_BLOCK_(	"Glock Mid Mot Pos Corr Rate",
													sbgcUCHAR						),  // 10
		PARAMS_BLOCK_(	"Extra Btn Cfg",			sbgcUCHAR,					5	),  // 11
		PARAMS_BLOCK_(	"Power Ctrl Cfg",			sbgcUCHAR,					8	),  // 12
		PARAMS_BLOCK_(	"Reserved 2",				sbgcRCHAR,					3	),  // 13
		PARAM_BLOCK_(	"CAN IMU Ext Sens Type",	sbgcUCHAR						),  // 14
		PARAM_BLOCK_(	"Profile Flags 2",			(sbgcUSHORT | sbgcFLAG)			),  // 15
		PARAMS_BLOCK_(	"Reserved 3",				sbgcRCHAR,					3	),  // 16
		PARAM_BLOCK_(	"General Flags 3",			(sbgcUINT | sbgcFLAG)			),  // 17
		PARAMS_BLOCK_(	"Follow Offset Ext",		sbgcSHORT,					3	),  // 18
		PARAM_BLOCK_(	"Motor Startup Delay",		sbgcUSHORT						),  // 19
		PARAM_BLOCK_(	"IMU Model Main",			sbgcUCHAR						),  // 20
		PARAM_BLOCK_(	"IMU Model Frame",			sbgcUCHAR						),  // 21
		PARAMS_BLOCK_(	"Stab Threshold Angle",		sbgcUCHAR,					3	),  // 22
		PARAM_BLOCK_(	"Ext Buzzer Pin",			sbgcUCHAR						),  // 23
		PARAMS_BLOCK_(	"Encoder Limit Return Speed",
													sbgcUCHAR,					3	),  // 24
		PARAM_BLOCK_(	"Tripod Mode Auto Threshold",
													sbgcUCHAR						),  // 25
		PARAM_BLOCK_(	"RC Deadband Pitch",		sbgcUCHAR						),  // 26
		PARAM_BLOCK_(	"RC Deadband Yaw",			sbgcUCHAR						),  // 27
		PARAM_BLOCK_(	"RC Expo Rate Pitch",		sbgcUCHAR						),  // 28
		PARAM_BLOCK_(	"RC Expo Rate Yaw",			sbgcUCHAR						),  // 29
		PARAM_BLOCK_(	"Profile Flags 3",			(sbgcUINT | sbgcFLAG)			),  // 30
		PARAM_BLOCK_(	"Default Profile",			sbgcUCHAR						),  // 31
		PARAMS_BLOCK_(	"Retracted Angle",			sbgcSHORT,					3	),  // 32
		PARAMS_BLOCK_(	"Amplitude",				sbgcUCHAR,					3	),  // 33
		PARAM_BLOCK_(	"Frequency Range",			sbgcUCHAR						),  // 34
		PARAM_BLOCK_(	"Pause Period",				sbgcUCHAR						),  // 35
		PARAM_BLOCK_(	"Pause Balance",			sbgcUCHAR						),  // 36
		PARAM_BLOCK_(	"Pause Attenuation",		sbgcUCHAR						),  // 37
		PARAM_BLOCK_(	"Pause Randomness",			sbgcUCHAR						),  // 38
		PARAM_BLOCK_(	"Pause Phase Var",			sbgcUCHAR						),  // 39
		PARAMS_BLOCK_(	"Resonance Gain",			sbgcUCHAR,					3	),  // 40
		PARAM_BLOCK_(	"Resonance Frequency",		sbgcUCHAR						),  // 41
		PARAMS_BLOCK_(	"Frequency Shift",			sbgcCHAR,					3	),  // 42
		PARAMS_BLOCK_(	"Reserved 4",				sbgcRCHAR,					5	),  // 43
		PARAMS_BLOCK_(	"Reserved 5",				sbgcRCHAR,					93	),  // 44

	};

	const ui8 mainParamsExt3_ReferenceInfoArrayElCnt = countof_(mainParamsExt3_ReferenceInfoArray);
	/**	@}
	 */

#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													Executable Functions
 */
/**	@addtogroup	Profile_Common
 *	@{
 */
/**	@brief	Performs a specific action on a profile
 *
 *	####	TX —> CMD_PROFILE_SET :	10 bytes
 *	####	RX <— CMD_CONFIRM :		1-6 bytes
 *
 *	@attention	Firmware: 2.65+
 *
 *	@code

			// Load the first profile set
			SBGC32_ManageProfileSet(&SBGC32_Device, sbgcPROFILE_SET_1, PSA_PROFILE_SET_ACTION_LOAD, SBGC_NO_CONFIRM);

			// ...

			// Save the backup profile set
			SBGC32_ManageProfileSet(&SBGC32_Device, sbgcPROFILE_SET_BACKUP, PSA_PROFILE_SET_ACTION_SAVE, SBGC_NO_CONFIRM);

			// ...

			// Clear the fifth profile set
			SBGC32_ManageProfileSet(&SBGC32_Device, sbgcPROFILE_SET_5, PSA_PROFILE_SET_ACTION_CLEAR, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	slot - slot to operate
 *	@param	action - action on the slot
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ManageProfileSet (sbgcGeneral_t *gSBGC, sbgcProfileSet_t slot, sbgcProfileSetAction_t action, sbgcConfirm_t *confirm
											 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2650)

	gSBGC->_api->startWrite(gSBGC, CMD_PROFILE_SET SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, slot);
	gSBGC->_api->writeByte(gSBGC, action);
	gSBGC->_api->writeEmptyBuff(gSBGC, 8);  // reserved[8]
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_PROFILE_SET SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Action required before and after uploading profile settings
 *
 *	####	TX —> CMD_WRITE_PARAMS_SET :	1 byte
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@pre	The profile parameters need to be changed
 *			by the SBGC32_WriteParamsX functions
 *
 *	@attention	Firmware: 2.70b4+
 *
 *	@code

			sbgcMainParams3_t MainParams3;
			sbgcMainParamsExt_t MainParamsExt;
			sbgcMainParamsExt2_t MainParamsExt2;
			sbgcMainParamsExt3_t MainParamsExt3;

			// Read all current profile data
			SBGC32_ReadParams3(&SBGC32_Device, &MainParams3, sbgcCURRENT_PROFILE);
			SBGC32_ReadParamsExt(&SBGC32_Device, &MainParamsExt, sbgcCURRENT_PROFILE);
			SBGC32_ReadParamsExt2(&SBGC32_Device, &MainParamsExt2, sbgcCURRENT_PROFILE);
			SBGC32_ReadParamsExt3(&SBGC32_Device, &MainParamsExt3, sbgcCURRENT_PROFILE);

			// Edit required parameters in MainParamsX
			// ...

			// Prepare for writing
			SBGC32_WriteParamsSet(&SBGC32_Device, PWF_START_WRITING, SBGC_NO_CONFIRM);

			SBGC32_WriteParams3(&SBGC32_Device, &MainParams3, SBGC_NO_CONFIRM);
			SBGC32_WriteParamsExt(&SBGC32_Device, &MainParamsExt, SBGC_NO_CONFIRM);
			SBGC32_WriteParamsExt2(&SBGC32_Device, &MainParamsExt2, SBGC_NO_CONFIRM);
			SBGC32_WriteParamsExt3(&SBGC32_Device, &MainParamsExt3, SBGC_NO_CONFIRM);

			// Stop writing
			SBGC32_WriteParamsSet(&SBGC32_Device, PWF_STOP_WRITING, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	action - stop/start operation
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_WriteParamsSet (sbgcGeneral_t *gSBGC, sbgcProfileWritingFlag_t action, sbgcConfirm_t *confirm
										   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2704)

	gSBGC->_api->startWrite(gSBGC, CMD_WRITE_PARAMS_SET SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, action);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_WRITE_PARAMS_SET SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Writes profile names to EEPROM
 *
 *	####	TX —> CMD_WRITE_PROFILE_NAMES :	240 bytes
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@code

			sbgcProfileNames_t ProfileNames;

			memcpy(ProfileNames.profile1, TEXT_LENGTH_("First profile"));
			memcpy(ProfileNames.profile2, TEXT_LENGTH_("Second profile"));
			memcpy(ProfileNames.profile3, TEXT_LENGTH_("Third profile"));
			memcpy(ProfileNames.profile4, TEXT_LENGTH_("Fourth profile"));
			memcpy(ProfileNames.profile5, TEXT_LENGTH_("Fifth profile"));

			SBGC32_WriteProfileNames(&SBGC32_Device, &ProfileNames, SBGC_NO_CONFIRM);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*profileNames - structure with written profile names
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_WriteProfileNames (sbgcGeneral_t *gSBGC, const sbgcProfileNames_t *profileNames, sbgcConfirm_t *confirm
											  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_WRITE_PROFILE_NAMES SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeBuff(gSBGC, profileNames, sizeof(sbgcProfileNames_t));
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_WRITE_PROFILE_NAMES SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Request profile names stored in EEPROM
 *
 *	####	TX —> CMD_READ_PROFILE_NAMES :	with no payload
 *	####	RX <— CMD_READ_PROFILE_NAMES :	240 bytes
 *
 *	@code

			sbgcProfileNames_t ProfileNames;

			SBGC32_ReadProfileNames(&SBGC32_Device, &ProfileNames);

			#if (SBGC_NEED_DEBUG)

				// Note that empty profile name that the GUI displays as ProfileX is default
				// This example will not print default profile names
				DebugSBGC32_PrintMessage(&SBGC32_Device, ProfileNames.profile1);
				DebugSBGC32_PrintMessage(&SBGC32_Device, " \n");
				DebugSBGC32_PrintMessage(&SBGC32_Device, ProfileNames.profile2);
				DebugSBGC32_PrintMessage(&SBGC32_Device, " \n");
				DebugSBGC32_PrintMessage(&SBGC32_Device, ProfileNames.profile3);
				DebugSBGC32_PrintMessage(&SBGC32_Device, " \n");
				DebugSBGC32_PrintMessage(&SBGC32_Device, ProfileNames.profile4);
				DebugSBGC32_PrintMessage(&SBGC32_Device, " \n");
				DebugSBGC32_PrintMessage(&SBGC32_Device, ProfileNames.profile5);

			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*profileNames - structure for storing profile names
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ReadProfileNames (sbgcGeneral_t *gSBGC, sbgcProfileNames_t *profileNames
											 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_READ_PROFILE_NAMES SBGC_ADVANCED_ARGS__);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_READ_PROFILE_NAMES SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, NULL, profileNames, SBGC_MAX_PROF_NAME_LEN * SBGC_PROFILES_NUM);
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Reset to factory defaults
 *
 *	####	TX —> CMD_USE_DEFAULTS :		1 byte
 *
 *	@attention	<h3>This function will erase
 *				all profile settings!</h3>
 *
 *	@code

			// Attention! This function will erase all profile settings!

			// Return the default values for the active profile
			SBGC32_UseDefaults(&SBGC32_Device, sbgcCURRENT_PROFILE);

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	profileID - profile ID
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_UseDefaults (sbgcGeneral_t *gSBGC, sbgcProfile_t profileID
										/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_USE_DEFAULTS SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, profileID);
	gSBGC->_api->finishWrite(gSBGC);
	/* No need confirmation */

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Profile_Params_3
 *	@{
 */
/**	@brief	Write system configuration part 1
 *
 *	####	TX —> CMD_WRITE_PARAMS_3 :		134 bytes
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@pre	Use the @ref SBGC32_ReadParams3 function to
 *			obtain this data previously for changing
 *
 *	@post	sbgcMainParams3_t.profileID is target profile slot.
 *			After writing this profile will be active
 *
 *	@note	Use the @ref SBGC32_WriteParamsSet if it's
 *			necessary to use multiple SBGC32_WriteParamsX
 *			functions simultaneously
 *
 *	@code

			sbgcMainParams3_t MainParams3;

			// Read all current profile data
			SBGC32_ReadParams3(&SBGC32_Device, &MainParams3, sbgcCURRENT_PROFILE);

			// Edit required parameters in MainParams3
			// ...

			// Assign another profile to copy the current settings into it
			// Or leave this field unchanged to edit the current profile
			MainParams3.profileID = sbgcPROFILE_5;

			SBGC32_WriteParams3(&SBGC32_Device, &MainParams3, SBGC_NO_CONFIRM);

			// Some changes require system to be restarted, so full reset occurs in 1 second
			// after this command, if there are no other CMD_WRITE_PARAMSxx have came
			// in that time. It's recommended to send these commands in the
			// "configuration" mode, activated by the SBGC32_WriteParamsSet()

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*mainParams3 - structure with written profile parameters
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_WriteParams3 (sbgcGeneral_t *gSBGC, const sbgcMainParams3_t *mainParams3, sbgcConfirm_t *confirm
										 /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_WRITE_PARAMS_3 SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeBuff(gSBGC, mainParams3, sizeof(sbgcMainParams3_t));
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_WRITE_PARAMS_3 SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Reads system configuration part 1
 *
 *	####	TX —> CMD_READ_PARAMS_3 :		1 byte
 *	####	RX <— CMD_READ_PARAMS_3 :		134 bytes
 *
 *	@post	Use the @ref DebugSBGC32_PrintWholeStruct
 *			function with PM_MAIN_PARAMS_3 to print
 *			received data
 *
 *	@code

			sbgcMainParams3_t MainParams3;

			// Read all current profile data
			SBGC32_ReadParams3(&SBGC32_Device, &MainParams3, sbgcCURRENT_PROFILE);

			#if (SBGC_NEED_DEBUG && SBGC_NEED_REF_INFO)

				DebugSBGC32_PrintMessage(&SBGC32_Device, "Current profile settings:\n");
				DebugSBGC32_PrintWholeStruct(&SBGC32_Device, &MainParams3, PM_MAIN_PARAMS_3);

			#endif

 *	@endcode
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*mainParams3 - structure for storing profile parameters
 *	@param	profileID - profile number
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ReadParams3 (sbgcGeneral_t *gSBGC, sbgcMainParams3_t *mainParams3, sbgcProfile_t profileID
										/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	#if (SBGC_NEED_ASSERTS)
		if ((profileID > sbgcPROFILE_5) && (profileID != sbgcCURRENT_PROFILE)) return sbgcCOMMAND_PARAM_ASSERT_ERROR;
	#endif

	gSBGC->_api->startWrite(gSBGC, CMD_READ_PARAMS_3 SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, profileID);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_READ_PARAMS_3 SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, NULL, mainParams3, sizeof(sbgcMainParams3_t));
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Profile_Params_Ext
 *	@{
 */
/**	@brief	Write system configuration part 2
 *
 *	####	TX —> CMD_WRITE_PARAMS_EXT :	104 bytes
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@pre	Use the @ref SBGC32_ReadParamsExt function to
 *			obtain this data previously for changing
 *
 *	@post	sbgcMainParamsExt_t.profileID is target profile slot.
 *			After writing this profile will be active
 *
 *	@note	This function is similar to
 *			@ref SBGC32_WriteParams3. Refer to its
 *			documentation for code example details
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*mainParamsExt - structure with written profile parameters
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_WriteParamsExt (sbgcGeneral_t *gSBGC, const sbgcMainParamsExt_t *mainParamsExt, sbgcConfirm_t *confirm
										   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_WRITE_PARAMS_EXT SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeBuff(gSBGC, mainParamsExt, sizeof(sbgcMainParamsExt_t));
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_WRITE_PARAMS_EXT SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Reads system configuration part 2
 *
 *	####	TX —> CMD_READ_PARAMS_EXT :		1 byte
 *	####	RX <— CMD_READ_PARAMS_EXT :		104 bytes
 *
 *	@post	Use the @ref DebugSBGC32_PrintWholeStruct
 *			function with PM_MAIN_PARAMS_EXT to print
 *			received data
 *
 *	@note	This function is similar to
 *			@ref SBGC32_ReadParams3. Refer to its
 *			documentation for code example details
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*mainParamsExt - structure for storing profile parameters
 *	@param	profileID - profile number
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ReadParamsExt (sbgcGeneral_t *gSBGC, sbgcMainParamsExt_t *mainParamsExt, sbgcProfile_t profileID
										  /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	#if (SBGC_NEED_ASSERTS)
		if ((profileID > sbgcPROFILE_5) && (profileID != sbgcCURRENT_PROFILE)) return sbgcCOMMAND_PARAM_ASSERT_ERROR;
	#endif

	gSBGC->_api->startWrite(gSBGC, CMD_READ_PARAMS_EXT SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, profileID);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_READ_PARAMS_EXT SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, NULL, mainParamsExt, sizeof(sbgcMainParamsExt_t));
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Profile_Params_Ext_2
 *	@{
 */
/**	@brief	Write system configuration part 3
 *
 *	####	TX —> CMD_WRITE_PARAMS_EXT2 :	151 bytes
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@pre	Use the @ref SBGC32_ReadParamsExt2 function to
 *			obtain this data previously for changing
 *
 *	@post	sbgcMainParamsExt2_t.profileID is target profile slot.
 *			After writing this profile will be active
 *
 *	@note	This function is similar to
 *			@ref SBGC32_WriteParams3. Refer to its
 *			documentation for code example details
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*mainParamsExt2 - structure with written profile parameters
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_WriteParamsExt2 (sbgcGeneral_t *gSBGC, const sbgcMainParamsExt2_t *mainParamsExt2, sbgcConfirm_t *confirm
											/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	gSBGC->_api->startWrite(gSBGC, CMD_WRITE_PARAMS_EXT2 SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeBuff(gSBGC, mainParamsExt2, sizeof(sbgcMainParamsExt2_t));
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_WRITE_PARAMS_EXT2 SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Reads system configuration part 3
 *
 *	####	TX —> CMD_READ_PARAMS_EXT2 :	1 byte
 *	####	RX <— CMD_READ_PARAMS_EXT2 :	151 bytes
 *
 *	@post	Use the @ref DebugSBGC32_PrintWholeStruct
 *			function with PM_MAIN_PARAMS_EXT2 to print
 *			received data
 *
 *	@note	This function is similar to
 *			@ref SBGC32_ReadParams3. Refer to its
 *			documentation for code example details
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*mainParamsExt2 - structure for storing profile parameters
 *	@param	profileID - profile number
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ReadParamsExt2 (sbgcGeneral_t *gSBGC, sbgcMainParamsExt2_t *mainParamsExt2, sbgcProfile_t profileID
										   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	#if (SBGC_NEED_ASSERTS)
		if ((profileID > sbgcPROFILE_5) && (profileID != sbgcCURRENT_PROFILE)) return sbgcCOMMAND_PARAM_ASSERT_ERROR;
	#endif

	gSBGC->_api->startWrite(gSBGC, CMD_READ_PARAMS_EXT2 SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, profileID);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_READ_PARAMS_EXT2 SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, NULL, mainParamsExt2, sizeof(sbgcMainParamsExt2_t));
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */


/**	@addtogroup	Profile_Params_Ext_3
 *	@{
 */
/**	@brief	Write system configuration part 4
 *
 *	####	TX —> CMD_WRITE_PARAMS_EXT3 :	221 bytes
 *	####	RX <— CMD_CONFIRM :				1-6 bytes
 *
 *	@pre	Use the @ref SBGC32_ReadParamsExt3 function to
 *			obtain this data previously for changing
 *
 *	@post	sbgcMainParamsExt3_t.profileID is target profile slot.
 *			After writing this profile will be active
 *
 *	@attention	Firmware: 2.66+
 *
 *	@note	This function is similar to
 *			@ref SBGC32_WriteParams3. Refer to its
 *			documentation for code example details
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*mainParamsExt3 - structure with written profile parameters
 *	@param	*confirm - confirmation result storage structure
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_WriteParamsExt3 (sbgcGeneral_t *gSBGC, const sbgcMainParamsExt3_t *mainParamsExt3, sbgcConfirm_t *confirm
											/** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	sbgcAssertFrwVer(2660)

	gSBGC->_api->startWrite(gSBGC, CMD_WRITE_PARAMS_EXT3 SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeBuff(gSBGC, mainParamsExt3, sizeof(sbgcMainParamsExt3_t));
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->addConfirm(gSBGC, confirm, CMD_WRITE_PARAMS_EXT3 SBGC_ADVANCED_ARGS__);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}


/**	@brief	Reads system configuration part 4
 *
 *	####	TX —> CMD_READ_PARAMS_EXT3 :	1 byte
 *	####	RX <— CMD_READ_PARAMS_EXT3 :	221 bytes
 *
 *	@post	Use the @ref DebugSBGC32_PrintWholeStruct
 *			function with PM_MAIN_PARAMS_EXT3 to print
 *			received data
 *
 *	@attention	Firmware: 2.66+
 *
 *	@note	This function is similar to
 *			@ref SBGC32_ReadParams3. Refer to its
 *			documentation for code example details
 *
 *	@param	*gSBGC - serial connection descriptor
 *	@param	*mainParamsExt3 - structure for storing profile parameters
 *	@param	profileID - profile number
 *
 *	@return	Communication status. See @ref Readme_S2
 */
sbgcCommandStatus_t SBGC32_ReadParamsExt3 (sbgcGeneral_t *gSBGC, sbgcMainParamsExt3_t *mainParamsExt3, sbgcProfile_t profileID
										   /** @cond */ SBGC_ADVANCED_PARAMS__ /** @endcond */ )
{
	#if (SBGC_NEED_ASSERTS)
		if ((profileID > sbgcPROFILE_5) && (profileID != sbgcCURRENT_PROFILE)) return sbgcCOMMAND_PARAM_ASSERT_ERROR;
	#endif

	sbgcAssertFrwVer(2660)

	gSBGC->_api->startWrite(gSBGC, CMD_READ_PARAMS_EXT3 SBGC_ADVANCED_ARGS__);
	gSBGC->_api->writeByte(gSBGC, profileID);
	gSBGC->_api->finishWrite(gSBGC);

	gSBGC->_api->startRead(gSBGC, CMD_READ_PARAMS_EXT3 SBGC_ADVANCED_ARGS__);
	gSBGC->_api->assignEvent(gSBGC, NULL, mainParamsExt3, sizeof(sbgcMainParamsExt3_t));
	gSBGC->_api->finishRead(gSBGC);

	gSBGC->_api->link(gSBGC);

	serialAPI_GiveToken()

	return gSBGC->_api->exit(gSBGC);
}
/**	@}
 */

#endif /* SBGC_PROFILES_MODULE */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                 https://www.basecamelectronics.com                 */
/* __________________________________________________________________ */
