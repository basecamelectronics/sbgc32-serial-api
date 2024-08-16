/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.0
 *
 *	@file		profiles.h
 *
 *	@brief		Profiles header file
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
/**	____________________________________________________________________
 *
 *	@defgroup	Profiles SBGC32 Profiles
 *	@ingroup	Modules
 *		@brief	SBGC32 Profiles Title Module
 *	____________________________________________________________________
 *
 *	@defgroup	Profile_Common Profile Common
 *	@ingroup	Profiles
 *		@brief	Profile Common Module
 *
 *				Covered Commands:
 *
 *				### CMD_PROFILE_SET
 *				### CMD_WRITE_PARAMS_SET
 *				### CMD_WRITE_PROFILE_NAMES
 *				### CMD_READ_PROFILE_NAMES
 *				### CMD_USE_DEFAULTS
 *
 *	@defgroup	Profile_Params_3 Profile Params 3
 *	@ingroup	Profiles
 *		@brief	Profile Params 3 Module
 *
 *				Covered Commands:
 *
 *				### CMD_WRITE_PARAMS_3
 *				### CMD_READ_PARAMS_3
 *
 *	@defgroup	Profile_Params_Ext Profile Params Extended
 *	@ingroup	Profiles
 *		@brief	Profile Params Extended Module
 *
 *				Covered Commands:
 *
 *				### CMD_WRITE_PARAMS_EXT
 *				### CMD_READ_PARAMS_EXT
 *
 *	@defgroup	Profile_Params_Ext_2 Profile Params Extended 2
 *	@ingroup	Profiles
 *		@brief	Profile Params Extended 2 Module
 *
 *				Covered Commands:
 *
 *				### CMD_WRITE_PARAMS_EXT2
 *				### CMD_READ_PARAMS_EXT2
 *
 *	@defgroup	Profile_Params_Ext_3 Profile Params Extended 3
 *	@ingroup	Profiles
 *		@brief	Profile Params Extended 3 Module
 *
 *				Covered Commands:
 *
 *				### CMD_WRITE_PARAMS_EXT3
 *				### CMD_READ_PARAMS_EXT3
 *	____________________________________________________________________
 */

#ifndef		MODULES_PROFILES_H_
#define		MODULES_PROFILES_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../sbgc32.h"


#if (SBGC_PROFILES_MODULE)

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *										   Constants
 */
/** Available SBGC32 profiles quantity */
#define		SBGC_PROFILES_NUM		5

/** Maximum allowed profile name length */
#define		SBGC_MAX_PROF_NAME_LEN	48


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								Profile Common Flags
 */
/**	@addtogroup	Profile_Common
 *	@{
 */
/**	@note	@ref SBGC32_ManageProfileSet, 3 arg
 */
typedef enum
{
	PSA_PROFILE_SET_ACTION_SAVE		= 1,
	PSA_PROFILE_SET_ACTION_CLEAR	= 2,
	PSA_PROFILE_SET_ACTION_LOAD		= 3

}	sbgcProfileSetAction_t;


/**	@note	@ref SBGC32_WriteParamsSet, 2 arg
 */
typedef enum
{
	PWF_STOP_WRITING				= 0,
	PWF_START_WRITING				= 1

}	sbgcProfileWritingFlag_t;


/**	@note	@ref SBGC32_ManageProfileSet, 2 arg
 */
typedef enum
{
	sbgcPROFILE_SET_1					= 1,
	sbgcPROFILE_SET_2					= 2,
	sbgcPROFILE_SET_3					= 3,
	sbgcPROFILE_SET_4					= 4,
	sbgcPROFILE_SET_5					= 5,

	sbgcPROFILE_SET_BACKUP				= 6

}	sbgcProfileSet_t;


/**	@note	sbgcMainParams3_t.serialSpeed \n
 *			sbgcMainParamsExt2_t.RC_SerialSpeed \n
 *			sbgcMainParamsExt2_t.UART2_Speed
 */
typedef enum
{
	SSpeed_115200					= 0,
	SSpeed_57600					= 1,
	SSpeed_38400					= 2,
	SSpeed_19200					= 3,
	SSpeed_9600						= 4,
	SSpeed_256000					= 5

}	sbgcSerialSpeed_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							  Profile Params 3 Flags
 */
/**	@addtogroup	Profile_Params_3
 *	@{
 */
/**	@note	sbgcAxisRC_MP3_t.RC_Mode \n
 *			Part of sbgcMainParams3_t \n
 *
 *	Can be combined with @ref sbgcRC_ModeControl_t
 */
typedef enum
{
	RCMode_RC_MODE_ANGLE			= 0,
	RCMode_RC_MODE_SPEED			= 1,

}	sbgcRC_Mode_t;

/**	@note	sbgcAxisRC_MP3_t.RC_Mode \n
 *			Part of sbgcMainParams3_t \n
 *
 *	Can be combined with @ref sbgcRC_Mode_t
 */
typedef enum
{
	RCModeC_RC_MODE_CONTROL_NOT_INVERTED
									= 0,
	RCModeC_RC_MODE_CONTROL_INVERTED
									= 1,

}	sbgcRC_ModeControl_t;

/**	@brief	Used as a mask to extract the
 *			RC mode value from
 *			sbgcAxisRC_MP3_t.RC_Mode
 *
 *	@param	value (sbgcAxisRC_MP3_t.RC_Mode)
 *	@return	RC Mode
 */
static inline sbgcRC_Mode_t ParserSBGC32_GetRC_Mode (ui8 value)
{
	return (sbgcRC_Mode_t)(value & 0b00000111);  // 0..2 bits – mode
}

/**	@brief	Used as a mask to extract the
 *			RC mode control value from
 *			sbgcAxisRC_MP3_t.RC_Mode
 *
 *	@param	value (sbgcAxisRC_MP3_t.RC_Mode)
 *	@return	RC Mode Control
 */
static inline sbgcRC_ModeControl_t ParserSBGC32_GetRC_ModeControl (ui8 value)
{
	return (sbgcRC_ModeControl_t)((value & 0b00001000) >> 3);
}


/**	@note	sbgcMainParams3_t.PWM_Freq
 */
typedef enum
{
	PWMF_PWM_FREQ_LOW				= 0,
	PWMF_PWM_FREQ_HIGH				= 1,
	PWMF_PWM_FREQ_ULTRA_HIGH		= 2

}	sbgcPWM_Freq_t;


/**	@note	sbgcMainParams3_t.RC_VirtMode
 */
typedef enum
{
	RCVM_RC_VIRT_MODE_NORMAL		= 0,
	RCVM_RC_VIRT_MODE_CPPM			= 1,
	RCVM_RC_VIRT_MODE_SBUS			= 2,
	RCVM_RC_VIRT_MODE_SPEKTRUM		= 3,
	RCVM_RC_VIRT_MODE_API			= 10

}	sbgcRC_VirtMode_t;


/**	@note	sbgcMainParams3_t.RC_MixFC_Roll \n
 *			sbgcMainParams3_t.RC_MixFC_Pitch \n
 *
 *	Can be combined with rate value
 */
typedef enum
{
	RCMFC_TARGET_NO_MIX				= 0,
	RCMFC_TARGET_ROLL				= 1,
	RCMFC_TARGET_PITCH				= 2,
	RCMFC_TARGET_YAW				= 3

}	sbgcRC_MixFC_Target_t;

/**	@brief	Used as a mask to extract the
 *			RC-Mix-FC rate value from
 *			sbgcMainParams3_t.RC_MixFC_Roll or
 *			sbgcMainParams3_t.RC_MixFC_Pitch
 *
 *	@param	value (sbgcMainParams3_t.RC_MixFC_Roll or
 *				   sbgcMainParams3_t.RC_MixFC_Pitch)
 *
 *	@return	RC-Mix-FC rate
 */
static inline ui8 ParserSBGC32_GetRC_MixFC_Rate (ui8 value)
{
	return value & 0b00111111;
}

/**	@brief	Used as a mask to extract the
 *			RC-Mix-FC target value from
 *			sbgcMainParams3_t.RC_MixFC_Roll or
 *			sbgcMainParams3_t.RC_MixFC_Pitch
 *
 *	@param	value (sbgcMainParams3_t.RC_MixFC_Roll or
 *				   sbgcMainParams3_t.RC_MixFC_Pitch)
 *
 *	@return	RC-Mix-FC target
 */
static inline sbgcRC_MixFC_Target_t ParserSBGC32_GetRC_MixFC_Target (ui8 value)
{
	return (sbgcRC_MixFC_Target_t)((value & 0b11000000) >> 6);
}

/**	@brief	Used as a function of joining
 *			RC-Mix-FC rate and RC-Mix-FC target values
 *
 *	@param	rate (0 --> 63) - clean value RC-Mix-FC rate
 *	@param	target - clean value RC-Mix-FC target
 *
 *	@return	Packed value to sbgcMainParams3_t.RC_MixFC_Roll
 *			or sbgcMainParams3_t.RC_MixFC_Pitch
 */
static inline ui8 ParserSBGC32_PackRC_MixFC (ui8 rate, sbgcRC_MixFC_Target_t target)
{
	return constrain_(rate, 0, 63) | ((target << 6) & 0b11000000);
}


/**	@note	sbgcMainParams3_t.followMode
 */
typedef enum
{
	FM_FOLLOW_MODE_DISABLED			= 0,
	FM_FOLLOW_MODE_FC				= 1,
	FM_FOLLOW_MODE_PITCH			= 2

}	sbgcFollowMode_t;


/**	@note	sbgcMainParams3_t.axisTop \n
 *			sbgcMainParams3_t.axisRight \n
 *			sbgcMainParams3_t.frameAxisTop \n
 *			sbgcMainParams3_t.frameAxisRight
 */
typedef enum
{
	IMUO_IMU_ORIENTATION_X			= 1,
	IMUO_IMU_ORIENTATION_Y			= 2,
	IMUO_IMU_ORIENTATION_Z			= 3,
	IMUO_IMU_ORIENTATION_MINUS_X	= -1,
	IMUO_IMU_ORIENTATION_MINUS_Y	= -2,
	IMUO_IMU_ORIENTATION_MINUS_Z	= -3

}	sbgcIMU_Orientation_t;


/**	@note	sbgcMainParams3_t.frameIMU_Pos
 */
typedef enum
{
	FIMUP_FRAME_IMU_DISABLED		= 0,
	FIMUP_FRAME_IMU_BELOW_YAW		= 1,
	FIMUP_FRAME_IMU_ABOVE_YAW		= 2,
	FIMUP_FRAME_IMU_BELOW_YAW_PID_SOURCE
									= 3

}	sbgcFrameIMU_Pos_t;


/**	@note	sbgcMainParams3_t.I2C_SpeedFast
 */
typedef enum
{
	I2CSF_400HZ						= 0,
	I2CSF_800HZ						= 1,

}	sbgcI2C_SpeedFast_t;


/**	@note	sbgcMainParams3_t.skipGyroCalib
 */
typedef enum
{
	SGC_DO_NOT_SKIP					= 0,
	SGC_SKIP_ALWAYS					= 1,
	SGC_TRY_TO_CALIBRATE			= 2				// ... but skip if motion detected

}	sbgcSkipGyroCalib_t;


/**	@note	sbgcMainParams3_t.motorOutput
 */
typedef enum
{
	MOTOR_OUTPUT_DISABLED			= 0,
	MOTOR_OUTPUT_ROLL				= 1,
	MOTOR_OUTPUT_PITCH				= 2,
	MOTOR_OUTPUT_YAW				= 3,
	MOTOR_OUTPUT_I2C_DRV_1			= 4,
	MOTOR_OUTPUT_I2C_DRV_2			= 5,
	MOTOR_OUTPUT_I2C_DRV_3			= 6,
	MOTOR_OUTPUT_I2C_DRV_4			= 7

}	sbgcMotorOutput_t;


/**	@note	sbgcMainParams3_t.adaptivePID_Enabled
 */
typedef enum
{
	APE_DISABLE_ALL_BITS			= 0,
	APE_EN_ROLL						= BIT_0_SET,
	APE_EN_PITCH					= BIT_1_SET,
	APE_EN_YAW						= BIT_2_SET

}	sbgcAdaptivePinEnabled_t;


/**	@note	sbgcMainParams3_t.generalFlags1
 */
typedef enum
{
	GF1_REMEMBER_LAST_USED_PROFILE	= BIT_0_SET,
	GF1_UPSIDE_DOWN_AUTO			= BIT_1_SET,
	GF1_SWAP_FRAME_MAIN_IMU			= BIT_2_SET,
	GF1_BLINK_PROFILE				= BIT_3_SET,
	GF1_EMERGENCY_STOP				= BIT_4_SET,
	GF1_MAGNETOMETER_POS_FRAME		= BIT_5_SET,
	GF1_FRAME_IMU_FF				= BIT_6_SET,
	GF1_OVERHEAT_STOP_MOTORS		= BIT_7_SET,
	GF1_CENTER_YAW_AT_STARTUP		= BIT_8_SET,
	GF1_SWAP_RC_SERIAL_UART_B		= BIT_9_SET,
	GF1_UART_B_SERIAL_API			= BIT_10_SET,
	GF1_BLINK_BAT_LEVEL				= BIT_11_SET,
	GF1_ADAPTIVE_GYRO_TRUST			= BIT_12_SET,
	/* frw. ver. 2.66+ */
	GF1_IS_UPSIDE_DOWN				= BIT_13_SET

}	sbgcGeneralFlag1_t;


/**	@note	sbgcMainParams3_t.profileFlags1
 */
typedef enum
{
	PF1_ADC1_AUTO_DETECTION			= BIT_0_SET,
	PF1_ADC2_AUTO_DETECTION			= BIT_1_SET,
	PF1_ADC3_AUTO_DETECTION			= BIT_2_SET,
	PF1_FOLLOW_USE_FRAME_IMU		= BIT_4_SET,
	PF1_BRIEFCASE_AUTO_DETECTION	= BIT_5_SET,
	PF1_UPSIDE_DOWN_AUTO_ROTATE		= BIT_6_SET,
	PF1_FOLLOW_LOCK_OFFSET_CORRECTION
									= BIT_7_SET,
	PF1_START_NEUTRAL_POSITION		= BIT_8_SET,
	PF1_MENU_BUTTON_DISABLE_FOLLOW	= BIT_9_SET,
	PF1_TIMELAPSE_FRAME_FIXED		= BIT_10_SET,
	PF1_RC_KEEP_MIX_RATE			= BIT_11_SET,
	PF1_RC_KEEP_CUR_POS_ON_INIT		= BIT_12_SET,
	/* frw. ver. 2.66+ */
	PF1_OUTER_MOTOR_LIMIT_FREE_ROTATION
									= BIT_13_SET,
	/* frw. ver. 2.67b1+ */
	PF1_EULER_ORDER_AUTO			= BIT_14_SET

}	sbgcProfileFlag1_t;


/**	@note	sbgcMainParams3_t.spektrumMode
 */
typedef enum
{
	SM_AUTO_DETECTION				= 0,			// Default
	SM_DSM2_11MS_10BIT				= 1,
	SM_DSM2_11MS_11BIT				= 2,
	SM_DSM2_22MS_10BIT				= 3,
	SM_DSM2_22MS_11BIT				= 4,
	SM_DSMX_11MS_10BIT				= 5,
	SM_DSMX_11MS_11BIT				= 6,
	SM_DSMX_22MS_10BIT				= 7,
	SM_DSMX_22MS_11BIT				= 8

}	sbgcSpectrumMode_t;


/**	@note	sbgcMainParams3_t.orderOfAxes
 */
typedef enum
{
	OOA_PITCH_ROLL_YAW				= 0,
	OOA_YAW_ROLL_PITCH				= 1,
	OOA_ROLL_YAW_PITCH				= 2,
	OOA_ROLL_PITCH_YAW				= 3

}	sbgcOrderOfAxes_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							Profile Params Ext Flags
 */
/**	@addtogroup	Profile_Params_Ext
 *	@{
 */
/**	@note	sbgcMainParamsExt_t.filtersEn
 */
typedef enum
{
	FE_DISABLE_ALL_BITS				= 0,
	FE_EN_NOTCH1					= BIT_0_SET,
	FE_EN_NOTCH2					= BIT_1_SET,
	FE_EN_NOTCH3					= BIT_2_SET,
	FE_EN_LPF						= BIT_3_SET

}	sbgcFiltersEnable_t;


/**	@note	sbgcMainParamsExt_t.encoderType
 */
typedef enum
{
	/* Bits 0..3: */
	ET_ENC_TYPE_AS5048A				= 1,
	ET_ENC_TYPE_AS5048B				= 2,
	ET_ENC_TYPE_AS5048_PWM			= 3,
	ET_ENC_TYPE_AMT203				= 4,
	ET_ENC_TYPE_MA3_10BIT			= 5,
	ET_ENC_TYPE_MA3_12BIT			= 6,
	ET_ENC_TYPE_ANALOG				= 7,
	ET_ENC_TYPE_I2C_DRV1			= 8,
	ET_ENC_TYPE_I2C_DRV2			= 9,
	ET_ENC_TYPE_I2C_DRV3			= 10,
	ET_ENC_TYPE_I2C_DRV4			= 11,
	ET_ENC_TYPE_AS5600_PWM			= 12,
	ET_ENC_TYPE_AS5600_I2C			= 13,
	ET_ENC_TYPE_RLS_ORBIS			= 14,
	ET_TYPE_RLS_ORBIS_PWM			= 15

}	sbgcEncoderType_t;


/**	@note	sbgcMainParamsExt_t.encoderType
 */
typedef enum
{
	ET_SKIP_DETECTION				= BIT_4_SET,
	ET_ENCODER_IS_GEARED			= BIT_7_SET

}	sbgcEncoderFlag_t;

/**	@brief	Used as a mask to extract the
 *			encoder type value from
 *			sbgcMainParamsExt_t.encoderType
 *
 *	@param	value (sbgcMainParamsExt_t.encoderType)
 *
 *	@return	Encoder type
 */
static inline sbgcEncoderType_t ParserSBGC32_GetEncoderType (ui8 value)
{
	return (sbgcEncoderType_t)(value & 0b00001111);
}


/**	@note	sbgcMainParamsExt_t.encoderCfg
 */
typedef enum
{
	/* For SPI encoders: */
	EC_SPI_SPEED_1MHz				= 0,
	EC_SPI_SPEED_2MHz				= 1,
	EC_SPI_SPEED_4MHz				= 2,
	EC_SPI_SPEED_500kHz				= 3
	/* For I2C_DRV: internal encoder type */

}	sbgcEncoderCfg_t;


/**	@note	sbgcMainParamsExt_t.magAxisTop
 *	@note	sbgcMainParamsExt_t.magAxisRight
 */
typedef enum
{
	MA_MAG_ORIENTATION_X			= 1,
	MA_MAG_ORIENTATION_Y			= 2,
	MA_MAG_ORIENTATION_Z			= 3,
	MA_MAG_ORIENTATION_MINUS_X		= -1,
	MA_MAG_ORIENTATION_MINUS_Y		= -2,
	MA_MAG_ORIENTATION_MINUS_Z		= -3

}	sbgcMagAxis_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						  Profile Params Ext 2 Flags
 */
/**	@addtogroup	Profile_Params_Ext_2
 *	@{
 */
/**	@note	sbgcMAV_CMPE_Channel_t.MAV_Src \n
 *			Part of sbgcMainParamsExt2_t
 */
typedef enum
{
	MAVS_DISABLED					= 0,
	MAVS_UART1						= 1,
	MAVS_RC_SERIAL					= 2,
	MAVS_UART2						= 3,
	MAVS_USB_VCP					= 4

}	sbgcMAV_Src_t;


/**	@note	sbgcMAV_CMPE_Channel_t.MAV_CfgFlags \n
 *			Part of sbgcMainParamsExt2_t
 */
typedef enum
{
	MAVCF_FLAG_BAUD_MASK			= (BIT_0_SET | BIT_1_SET | BIT_2_SET),
	MAVCF_FLAG_PARITY_EVEN			= BIT_3_SET,
	MAVCF_FLAG_HEARTBEAT			= BIT_4_SET,
	MAVCF_FLAG_DEBUG				= BIT_5_SET,
	MAVCF_FLAG_RC					= BIT_6_SET,

}	sbgcMAV_CfgFlag_t;


/**	@note	sbgcMainParamsExt2_t.autoPID_Cfg
 */
typedef enum
{
	APIDC_AUTO_PID_STOP				= 0,
	APIDC_AUTO_PID_CFG_ROLL			= BIT_0_SET,
	APIDC_AUTO_PID_CFG_PITCH		= BIT_1_SET,
	APIDC_AUTO_PID_CFG_YAW			= BIT_2_SET,
	APIDC_AUTO_PID_CFG_SEND_GUI		= BIT_3_SET,
	APIDC_AUTO_PID_CFG_KEEP_CURRENT	= BIT_4_SET,
	APIDC_AUTO_PID_CFG_TUNE_LPF_FREQ
									= BIT_5_SET,
	APIDC_AUTO_PID_CFG_ALL_PROFILES	= BIT_6_SET,

}	sbgcAutoPID_Cfg_t;


/**	@note	sbgcMainParamsExt2_t.generalFlags2
 */
typedef enum
{
	/* frw. ver. 2.61+ */
	GF2_SEARCH_LIMIT_ROLL			= BIT_0_SET,
	GF2_SEARCH_LIMIT_PITCH			= BIT_1_SET,
	GF2_SEARCH_LIMIT_YAW			= BIT_2_SET,
	/* frw. ver. 2.62b7+ */
	GF2_AUTO_CALIBRATE_MOMENTUM		= BIT_3_SET,
	GF2_USE_MOMENTUM_FEED_FORWARD	= BIT_4_SET,
	GF2_MOTORS_OFF_AT_STARTUP		= BIT_5_SET,
	GF2_FC_BELOW_OUTER				= BIT_6_SET,
	/* frw. ver. 2.66+ */
	GF2_DO_NOT_CHECK_ENCODER_LIMITS	= BIT_7_SET,
	GF2_AUTO_SAVE_BACKUP_SLOT		= BIT_8_SET,
	GF2_FC_BELOW_MIDDLE				= BIT_9_SET,
	/* frw. ver. 2.67b2+ */
	GF2_ENVIRONMENT_TEMP_UNKNOWN	= BIT_10_SET,
	GF2_LPF_EXTENDED_RANGE			= BIT_11_SET,
	GF2_SAVE_SYSTEM_STAT			= BIT_12_SET,
	GF2_FLAG2_DISABLE_ACC			= BIT_13_SET,
	GF2_FLAG2_DISABLE_POWER_MANAGER	= BIT_14_SET,
	GF2_ALLOW_FRAME_IMU_AS_MAIN		= BIT_15_SET

}	sbgcGeneralFlag2_t;


/**	@note	sbgcMainParamsExt2_t.stabAxis \n
 *
 *	Can be combined with @ref sbgcStabAxisSelection_t
 */
typedef enum
{
	STAB_AXIS_DEFAULT				= 0,
	STAB_AXIS_ROLL					= 1,
	STAB_AXIS_PITCH					= 2,
	STAB_AXIS_YAW					= 3,

}	sbgcStabAxis_t;

/**	@note	sbgcMainParamsExt2_t.stabAxis \n
 *
 *	Can be combined with @ref sbgcStabAxis_t
 */
typedef enum
{
	SAS_AUTOMATIC_ROLL				= BIT_2_SET,
	SAS_AUTOMATIC_PITCH				= BIT_3_SET,
	SAS_AUTOMATIC_YAW				= BIT_4_SET

}	sbgcStabAxisSelection_t;

/**	@brief	Used as a mask to extract the
 *			stab axis value from
 *			sbgcMainParamsExt2_t.stabAxis
 *
 *	@param	value (sbgcMainParamsExt2_t.stabAxis)
 *
 *	@return	Stab axis
 */
static inline sbgcStabAxis_t ParserSBGC32_GetStabAxis (ui8 value)
{
	return (sbgcStabAxis_t)(value & 0b00000011);
}

/**	@brief	Used as a mask to extract the
 *			stab axis selection value from
 *			sbgcMainParamsExt2_t.stabAxis
 *
 *	@param	value (sbgcMainParamsExt2_t.stabAxis)
 *
 *	@return	Stab axis selection
 */
static inline sbgcStabAxisSelection_t ParserSBGC32_GetStabAxisSelection (ui8 value)
{
	return (sbgcStabAxisSelection_t)((value & 0b00011100) >> 2);
}


/**	@note	sbgcMainParamsExt2_t.forcePositionCfg \n
 *
 *	Can be combined with @ref sbgcForcePositionCfgFlag_t
 */
typedef enum
{
	FPCS_SNAP_ANGLE_0				= 0,
	FPCS_SNAP_ANGLE_45				= BIT_0_SET,
	FPCS_SNAP_ANGLE_90				= BIT_1_SET,
	FPCS_SNAP_ANGLE_180				= (BIT_0_SET | BIT_1_SET),

}	sbgcForcePositionCfgSnap_t;

/**	@note	sbgcMainParamsExt2_t.forcePositionCfg \n
 *
 *	Can be combined with @ref sbgcForcePositionCfgSnap_t
 */
typedef enum
{
	FPCF_FORCE_POSITION_FLAG_BUTTON_PRESS
									= BIT_4_SET,
	FPCF_FORCE_POSITION_FLAG_STARTUP
									= BIT_5_SET,
	FPCF_FORCE_POSITION_FLAG_IGNORE_LIMITS
									= BIT_6_SET,
	FPCF_FORCE_POSITION_FLAG_FINE_ADJUST
									= BIT_7_SET

}	sbgcForcePositionCfgFlag_t;

/**	@brief	Used as a mask to extract the
 *			force position config snap value from
 *			sbgcMainParamsExt2_t.forcePositionCfg
 *
 *	@param	value (sbgcMainParamsExt2_t.forcePositionCfg)
 *
 *	@return	Force position config snap
 */
static inline sbgcForcePositionCfgSnap_t ParserSBGC32_GetForcePositionCfgSnap (ui8 value)
{
	return (sbgcForcePositionCfgSnap_t)(value & 0b00000111);  // bits 0..2: snap angle
}

/**	@brief	Used as a mask to extract the
 *			force position config flags from
 *			sbgcMainParamsExt2_t.forcePositionCfg
 *
 *	@param	value (sbgcMainParamsExt2_t.forcePositionCfg)
 *
 *	@return	Force position config flags
 */
static inline sbgcForcePositionCfgFlag_t ParserSBGC32_GetForcePositionCfgFlags (ui8 value)
{
	return (sbgcForcePositionCfgFlag_t)(value & 0b11110000);
}


/**	@note	sbgcStepSignalN_t.stepSignalCfg \n
 *			Part of sbgcMainParamsExt2_t \n
 *
 *	Can be combined with @ref sbgcStepSignalCfgMode_t
 */
typedef enum
{
	SSC_STEP_2						= 0,
	SSC_STEP_3						= 1,
	SSC_STEP_5						= 2,
	SSC_STEP_10						= 3,
	SSC_STEP_15						= 4,
	SSC_STEP_25						= 5,
	SSC_STEP_50						= 6,
	SSC_STEP_100					= 7

}	sbgcStepSignalCfgNumber_t;

/**	@note	sbgcStepSignalN_t.stepSignalCfg \n
 *			Part of sbgcMainParamsExt2_t \n
 *
 *	Can be combined with @ref sbgcStepSignalCfgNumber_t
 */
typedef enum
{
	SSC_MODE_LEVEL_LOW				= 0,
	SSC_MODE_LEVEL_HIGH				= 1,
	SSC_MODE_LEVEL_LOW_HIGH			= 2

}	sbgcStepSignalCfgMode_t;

/**	@note	sbgcStepSignalN_t.stepSignalCfg \n
 *			Part of sbgcMainParamsExt2_t
 */
typedef enum
{
	/* Bit 3: if set, menu button should be pressed */
	SSC_MENU_BUTTON_PRESSED			= BIT_3_SET,
	/* Bit 5: if set, initial value is zero */
	SSC_INITIAL_VALUE_ZERO			= BIT_5_SET

}	sbgcStepSignalCfgAdd_t;

/**	@brief	Used as a mask to extract the
 *			step signal config number value from
 *			sbgcStepSignalN_t.stepSignalCfg
 *
 *	@param	value (sbgcStepSignalN_t.stepSignalCfg)
 *
 *	@return	Step signal config number
 */
static inline sbgcStepSignalCfgNumber_t ParserSBGC32_GetStepSignalCfgNumber (ui8 value)
{
	return (sbgcStepSignalCfgNumber_t)(value & 0b00000111);
}

/**	@brief	Used as a mask to extract the
 *			step signal config mode value from
 *			sbgcStepSignalN_t.stepSignalCfg
 *
 *	@param	value (sbgcStepSignalN_t.stepSignalCfg)
 *
 *	@return	Step signal config mode
 */
static inline sbgcStepSignalCfgMode_t ParserSBGC32_GetStepSignalCfgMode (ui8 value)
{
	return (sbgcStepSignalCfgMode_t)((value & 0b11000000) >> 6);
}

/**	@brief	Used as a function of joining
 *			step signal config number,
 *			step signal config mode and
 *			step signal additionally flags values
 *
 *	@param	num - clean value of step signal config number
 *	@param	mode - clean value of step signal config mode
 *	@param	add - additionally flags values
 *
 *	@return	Packed value to sbgcStepSignalN_t.stepSignalCfg
 */
static inline ui8 ParserSBGC32_PackStepSignalCfg (sbgcStepSignalCfgNumber_t num, sbgcStepSignalCfgMode_t mode,
												  sbgcStepSignalCfgAdd_t add)
{
	return (num & 0b00000111) | ((mode << 6) & 0b11000000) | add;
}


/**	@note	sbgcMainParamsExt2_t.parkingPosCfg
 */
typedef enum
{
	/* ROLL: bit 0 – negative border, bit 1 – positive border */
	PPC_ROLL_NEGATIVE_BORDER		= BIT_0_SET,
	PPC_ROLL_POSITIVE_BORDER		= BIT_1_SET,
	/* PITCH: bit 2 – negative border, bit 3 – positive border */
	PPC_PITCH_NEGATIVE_BORDER		= BIT_2_SET,
	PPC_PITCH_POSITIVE_BORDER		= BIT_3_SET,
	/* YAW: bit 4 – negative border, bit 5 – positive border */
	PPC_YAW_NEGATIVE_BORDER			= BIT_4_SET,
	PPC_YAW_POSITIVE_BORDER			= BIT_5_SET

}	sbgcParkingPosCfg_t;


/**	@note	sbgcMainParamsExt2_t.interruptCfg \n
 *
 *	Can be combined with @ref sbgcTriggerPinID_t
 */
typedef enum
{
	/* Bit 5: generate interrupt on emergency stop */
	IC_INTERRUPT_EMERGENCY_STOP		= BIT_5_SET,
	/* Bit 6: generate interrupt on entering parking position */
	IC_INTERRUPT_ENTERING_PARKING_POSITION
									= BIT_6_SET

}	sbgcInterruptCfg_t;

/**	@brief	Used as a mask to extract the
 *			interrupt config value from
 *			sbgcMainParamsExt2_t.interruptCfg
 *
 *	@param	value (sbgcMainParamsExt2_t.interruptCfg)
 *
 *	@return	Interrupt config
 */
static inline sbgcInterruptCfg_t ParserSBGC32_GetInterruptCfg (ui8 value)
{
	return (sbgcInterruptCfg_t)(value & 0b01100000);
}

/**	@brief	Used as a mask to extract the
 *			interrupt pin ID from
 *			sbgcMainParamsExt2_t.interruptCfg
 *
 *	@param	value (sbgcMainParamsExt2_t.interruptCfg)
 *
 *	@return	Interrupt pin ID
 */
static inline sbgcTriggerPinID_t ParserSBGC32_GetInterruptPinID (ui8 value)
{
	return (sbgcTriggerPinID_t)(value & 0b00011111);
}


/**	@note	sbgcMainParamsExt2_t.MAV_ControlMode
 */
typedef enum
{
	MAVCM_DISABLED					= 0,
	MAVCM_ROLL_PITCH_AXES			= 1,
	MAVCM_ALL_AXES					= 2

}	sbgcMAV_CtrlMode_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						  Profile Params Ext 3 Flags
 */
/**	@addtogroup	Profile_Params_Ext_3
 *	@{
 */
/**	@note	sbgcMainParamsExt3_t.extIMU_Type
 */
typedef enum
{
	EIMUT_MAV_LINK_1				= 1,
	EIMUT_MAV_LINK_2				= 2,
	EIMUT_VECTORNAV_VN200			= 3,
	EIMUT_INERTIALSENSE_UAHRS		= 4

}	sbgcExtIMU_Type_t;


/**	@note	sbgcMainParamsExt3_t.extIMU_Port
 */
typedef enum
{
	EIMUPort_DISABLED				= 0,
	EIMUPort_UART1					= 1,
	EIMUPort_RC_SERIAL				= 2,
	EIMUPort_UART2					= 3,
	EIMUPort_USB_VCP				= 4

}	sbgcExtIMU_Port_t;


/**	@note	sbgcMainParamsExt3_t.extIMU_Position
 */
typedef enum
{
	EIMUPos_BELOW_OUTER				= 1,
	EIMUPos_ABOVE_OUTER				= 2,
	EIMUPos_BELOW_MIDDLE			= 8,
	EIMUPos_MAIN_IMU				= 9

}	sbgcExtIMU_Position_t;


/**	@note	sbgcMainParamsExt3_t.extIMU_Orientation
 */
typedef enum
{
	EIMUOrntTOP_X					= 0,
	EIMUOrntTOP_Y					= 1,
	EIMUOrntTOP_Z					= 2,
	EIMUOrntTOP_MINUS_X				= 3,
	EIMUOrntTOP_MINUS_Y				= 4,
	EIMUOrntTOP_MINUS_Z				= 5,

	EIMUOrntRIGHT_X					= 0,
	EIMUOrntRIGHT_TOP_Y				= (1 << 3),
	EIMUOrntRIGHT_TOP_Z				= (2 << 3),
	EIMUOrntRIGHT_TOP_MINUS_X		= (3 << 3),
	EIMUOrntRIGHT_TOP_MINUS_Y		= (4 << 3),
	EIMUOrntRIGHT_TOP_MINUS_Z		= (5 << 3)

}	sbgcExtIMU_Orientation_t;


/**	@note	sbgcMainParamsExt3_t.extIMU_Flags
 */
typedef enum
{
	EIMUFlagACC_COMP_ONLY			= BIT_1_SET,
	EIMUFlagREPLACE					= BIT_2_SET,
	EIMUFlagFLAG_Z					= BIT_3_SET,
	EIMUFlag_H						= BIT_4_SET,
	EIMUFlagFRAME_UPSIDE_DOWN_UPDATE
									= BIT_5_SET,
	EIMUFlagAS_FRAME_IMU			= BIT_6_SET,
	/* frw.ver. 2.68b7+ */
	EIMUFlagGYRO_CORR				= BIT_7_SET

}	sbgcExtIMU_Flag_t;


/**	@note	sbgcMainParamsExt3_t.powerCtrlCfg \n
 *
 *	Can be combined with @ref sbgcTriggerPinID_t
 */
typedef enum
{
	/* Bit6: latching mode if set */
	EBC_LAUNCHING_MODE_OFFSET		= BIT_6_SET,
	/* Bit7: invert action if set */
	EBC_INVERT_ACTION				= BIT_7_SET

}	sbgcExtraBtnCfg_t;

/**	@brief	Used as a mask to extract the
 *			extra button config value from
 *			sbgcMainParamsExt3_t.powerCtrlCfg
 *
 *	@param	value (sbgcMainParamsExt3_t.powerCtrlCfg)
 *
 *	@return	Extra button config value
 */
static inline sbgcExtraBtnCfg_t ParserSBGC32_GetExtraBtnCfg (ui8 value)
{
	return (sbgcExtraBtnCfg_t)(value & 0b11000000);
}

/**	@brief	Used as a mask to extract the
 *			extra button pin ID from
 *			sbgcMainParamsExt3_t.powerCtrlCfg
 *
 *	@param	value (sbgcMainParamsExt3_t.powerCtrlCfg)
 *
 *	@return	Extra button pin ID
 */
static inline sbgcTriggerPinID_t ParserSBGC32_GetExtraBtnPinID (ui8 value)
{
	return (sbgcTriggerPinID_t)(value & 0b00011111);
}


/**	@note	sbgcMainParamsExt3_t.CAN_IMU_ExtSensType
 */
typedef enum
{
	EST_DISABLED					= 0,
	EST_KVH_1725					= 1,
	EST_KVH_1750_ACC_2G				= 2,
	EST_KVH_1750_ACC_10G			= 3,
	EST_KVH_1750_ACC_30G			= 4,
	EST_KVH_1775_ACC_10G			= 5,
	EST_KVH_1775_ACC_25G			= 6,
	EST_KVH_1760					= 7,
	EST_ADXRS453					= 8,
	EST_ADIS16460					= 9,
	EST_STIM210						= 10,
	EST_STIM300						= 11,
	EST_SCHA63X						= 12,
	EST_VECTORNAV_VN100_200_UART	= 64,
	EST_VECTORNAV_VN100_200_SPI		= 65

}	sbgcCAN_IMU_ExtSensType_t;


/**	@note	sbgcMainParamsExt3_t.profileFlags2
 */
typedef enum
{
	PF2_FOLLOW_PITCH_DISABLED		= BIT_0_SET,
	PF2_LOW_ANGLE_PRIOR_ROLL		= BIT_1_SET,
	PF2_LOW_ANGLE_PRIOR_PITCH		= BIT_2_SET,
	PF2_LOW_ANGLE_PRIOR_YAW			= BIT_3_SET,
	PF2_HEADING_TRIPOD_MODE			= BIT_4_SET

}	sbgcProfileFlag2_t;


/**	@note	sbgcMainParamsExt3_t.generalFlags3
 */
typedef enum
{
	GF3_ENC_LUT_EN_ROLL				= BIT_0_SET,
	GF3_ENC_LUT_EN_PITCH			= BIT_1_SET,
	GF3_ENC_LUT_EN_YAW				= BIT_2_SET,
	GF3_MAVLINK_YAW_ABSOLUTE		= BIT_3_SET

}	sbgcGeneralFlag3_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						   Profile Common Structures
 */
/**	@addtogroup	Profile_Common
 *	@{
 */
/**	@brief	Structure type for writing and reading
 *			profile names
 *
 *	@ref	SBGC32_WriteProfileNames function\n
 *	@ref	SBGC32_ReadProfileNames function
 */
typedef struct PACKED__
{
	char	profile1 [SBGC_MAX_PROF_NAME_LEN],		/*!<  Name of the first profile														*/
			profile2 [SBGC_MAX_PROF_NAME_LEN],		/*!<  Name of the second profile													*/
			profile3 [SBGC_MAX_PROF_NAME_LEN],		/*!<  Name of the third profile														*/
			profile4 [SBGC_MAX_PROF_NAME_LEN],		/*!<  Name of the fourth profile													*/
			profile5 [SBGC_MAX_PROF_NAME_LEN];		/*!<  Name of the fifth profile														*/

}			sbgcProfileNames_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						 Profile Params 3 Structures
 */
/**	@addtogroup	Profile_Params_3
 *	@{
 */
/**	@brief	Part of sbgcMainParams3_t structure
 *
 *	@note	sbgcMainParams3_t.AxisCMP3
 */
typedef struct PACKED__
{
	ui8		p,										/*!<  0 --> 255																		*/
			i,										/*!<  0 --> 255. Divided by 100 when displayed in the GUI							*/
			d,										/*!<  0 --> 255																		*/
			power,									/*!<  0 --> 255																		*/
			invert,									/*!<  0 --> 1																		*/
			poles;									/*!<  0 --> 1																		*/

}			sbgcAxisCMP3_t;

/**	@brief	Part of sbgcMainParams3_t structure
 *
 *	@note	sbgcMainParams3_t.AxisRC_MP3
 */
typedef struct PACKED__
{
	i16		RC_MinAngle;							/*!<  -720 --> 720. Units: degrees													*/
	i16		RC_MaxAngle;							/*!<  -720 --> 720. Units: degrees													*/
	ui8		RC_Mode;								/*!<  See @ref sbgcRC_Mode_t and @ref sbgcRC_ModeControl_t enumerations				*/
	ui8		RC_LPF;									/*!<  0 --> 15, 255. Range depends on the flag “Extend LPF range” in GUI settings	*/
	ui8		RC_Speed;								/*!<  0 --> 255																		*/
	i8		RC_Follow;								/*!<  -127 --> 127																	*/

}			sbgcAxisRC_MP3_t;

/**	@brief	Structure type for work with
 *			MainParams3 parameters
 *
 *	@ref	SBGC32_WriteParams3 function\n
 *	@ref	SBGC32_ReadParams3 function
 */
typedef struct PACKED__
{
	ui8		profileID;								/*!<  See @ref sbgcProfile_t enumeration
														  To access current (active) profile, specify 255								*/
	sbgcAxisCMP3_t	AxisCMP3 [3];					/*!<  ROLL : PITCH : YAW															*/

	ui8		accLimiterAll;							/*!<  0 --> 255. Units: 5 degrees/sec². 0 – disabled								*/
	i8		extFC_Gain [2];							/*!<  -127 --> 127																	*/

	sbgcAxisRC_MP3_t
					AxisRC_MP3 [3];					/*!<  ROLL : PITCH : YAW															*/

	ui8		gyroTrust;								/*!<  0 --> 255																		*/
	ui8		useModel;								/*!<  0 --> 1																		*/
	ui8		PWM_Freq;								/*!<  See @ref sbgcPWM_Freq_t enumeration											*/
	ui8		serialSpeed;							/*!<  See @ref sbgcSerialSpeed_t enumeration										*/
	i8		RC_Trim [3];							/*!<  -127 --> 127																	*/
	ui8		RC_DeadBand;							/*!<  0 --> 255																		*/
	ui8		RC_ExpoRate;							/*!<  0 --> 100																		*/
	ui8		RC_VirtMode;							/*!<  See @ref sbgcRC_VirtMode_t enumeration										*/

	ui8		RC_MapRoll,								/*!<  ...																			*/
			RC_MapPitch,							/*!<  ...																			*/
			RC_MapYaw,								/*!<  ...																			*/
			RC_MapCmd,								/*!<  ...																			*/
			RC_MapFC_Roll,							/*!<  ...																			*/
			RC_MapFC_Pitch;							/*!<  ...See @ref sbgcRC_MapSourceType_t and @ref sbgcRC_MapSource_t enumerations	*/

	ui8		RC_MixFC_Roll,							/*!<  ...																			*/
			RC_MixFC_Pitch;							/*!<  ...Mix value - 0 --> 63. Also see @ref sbgcRC_MixFC_Target_t enumeration		*/

	ui8		followMode;								/*!<  See @ref sbgcFollowMode_t enumeration											*/
	ui8		followDeadBand;							/*!<  0 --> 255																		*/
	ui8		followExpoRate;							/*!<  0 --> 100																		*/
	i8		followOffset [3];						/*!<  -127 --> 127																	*/

	i8		axisTop,								/*!<  ...																			*/
			axisRight,								/*!<  ...																			*/
			frameAxisTop,							/*!<  ...																			*/
			frameAxisRight;							/*!<  ...See @ref sbgcIMU_Orientation_t enumeration									*/

	ui8		frameIMU_Pos;							/*!<  See @ref sbgcFrameIMU_Pos_t enumeration										*/
	ui8		gyroDeadBand;							/*!<  0 --> 255. Units: 0.1 of gyro sensor's units									*/
	ui8		gyroSens;								/*!<  Deprecated																	*/
	ui8		I2C_SpeedFast;							/*!<  See @ref sbgcI2C_SpeedFast_t enumeration										*/
	ui8		skipGyroCalib;							/*!<  See @ref sbgcSkipGyroCalib_t enumeration										*/

	ui8		RC_Cmd_Low,								/*!<  ...																			*/
			RC_Cmd_Mid,								/*!<  ...																			*/
			RC_Cmd_High,							/*!<  ...																			*/
			MenuBtnCmd1,							/*!<  ...																			*/
			MenuBtnCmd2,							/*!<  ...																			*/
			MenuBtnCmd3,							/*!<  ...																			*/
			MenuBtnCmd4,							/*!<  ...																			*/
			MenuBtnCmd5,							/*!<  ...																			*/
			MenuBtnCmdLong;							/*!<  ...See @ref sbgcMenuCommand_t enumeration										*/

	ui8		motorOutput [3];						/*!<  See @ref sbgcMotorOutput_t enumeration										*/
	i16		batThresholdAlarm;						/*!<  -3000 --> 3000. Units: 0.01 V													*/
	i16		batThresholdMotors;						/*!<  -3000 --> 3000. Units: 0.01 V													*/
	i16		batCompRef;								/*!<  -3000 --> 3000. Units: 0.01 V													*/
	ui8		beeperModes;							/*!<  See @ref sbgcBeeperMode_t enumeration											*/
	ui8		followROLL_MixStart;					/*!<  0 --> 90																		*/
	ui8		followROLL_MixRange;					/*!<  0 --> 90																		*/
	ui8		boosterPower [3];						/*!<  0 --> 255																		*/
	ui8		followSpeed [3];						/*!<  0 --> 255																		*/
	ui8		frameAngleFromMotors;					/*!<  0 --> 1																		*/
	i16		RC_Memory [3];							/*!<  -32767 --> 32767																*/

	ui8		servo1_Out,								/*!<  ...																			*/
			servo2_Out,								/*!<  ...																			*/
			servo3_Out,								/*!<  ...																			*/
			servo4_Out;								/*!<  ...Disabled = 0. 1..32 - Virt. channel number as source of data to be output	*/

	ui8		servoRate;								/*!<  5 --> 40 (10 Hz)																*/
	ui8		adaptivePID_Enabled;					/*!<  See @ref sbgcAdaptivePinEnabled_t enumeration									*/
	ui8		adaptivePID_Threshold;					/*!<  0 --> 255																		*/
	ui8		adaptivePID_Rate;						/*!<  1 --> 255																		*/
	ui8		adaptivePID_RecoveryFactor;				/*!<  0 --> 10																		*/
	ui8		followLPF [3];							/*!<  0 --> 15																		*/
	ui16	generalFlags1;							/*!<  See @ref sbgcGeneralFlag1_t enumeration										*/
	ui16	profileFlags1;							/*!<  See @ref sbgcProfileFlag1_t enumeration										*/
	ui8		spektrumMode;							/*!<  See @ref sbgcSpectrumMode_t enumeration										*/
	ui8		orderOfAxes;							/*!<  See @ref sbgcOrderOfAxes_t enumeration										*/
	ui8		EulerOrder;								/*!<  See @ref sbgcEulerOrder_t enumeration											*/
	ui8		curIMU;									/*!<  See @ref sbgcIMU_Type_t enumeration											*/
	ui8		curProfileID;							/*!<  See @ref sbgcProfile_t enumeration											*/

}			sbgcMainParams3_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t mainParams3_ReferenceInfoArray [];
	extern const ui8 mainParams3_ReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *					   Profile Params Ext Structures
 */
/**	@addtogroup	Profile_Params_Ext
 *	@{
 */
/**	@brief	Part of sbgcMainParamsExt_t structure
 *
 *	@note	sbgcMainParamsExt_t.AxisMPE
 */
typedef struct PACKED__
{
	ui8		notchFreq [3],							/*!<  0 --> 255																		*/
			notchWidth [3];							/*!<  0 --> 255																		*/

}			sbgcAxisMPE_t;

/**	@brief	Structure type for work with
 *			MainParamsExt parameters
 *
 *	@ref	SBGC32_WriteParamsExt function\n
 *	@ref	SBGC32_ReadParamsExt function
 */
typedef struct PACKED__
{
	ui8		profileID;								/*!<  See @ref sbgcProfile_t enumeration
														  To access current (active) profile, specify 255								*/
	sbgcAxisMPE_t	AxisMPE [3];					/*!<  ROLL : PITCH : YAW															*/

	ui16	LPF_Freq [3];							/*!<  0 --> 1000																	*/
	ui8		filtersEn [3];							/*!<  See @ref sbgcFiltersEnable_t enumeration										*/

	i16		encoderOffset [3],						/*!<  ...																			*/
			encoderFldOffset [3];					/*!<  ...Units: 0.02197265625 degree. Use the @ref sbgcAngleToDegree and
														  @ref sbgcDegreeToAngle macros to comfortable work with this fields			*/

	ui8		encoderManualSetTime [3];				/*!<  0 --> 255. Units: 10 ms														*/
	ui8		motorHeatingFactor [3];					/*!<  0 --> 255																		*/
	ui8		motorCoolingFactor [3];					/*!<  0 --> 255																		*/
	ui8		reserved [2];
	ui8		followInsideDeadBand;					/*!<  0 --> 255																		*/
	ui8		motorMagLink [3];						/*!<  0 --> 255. Deprecated, replaced by the motorMagLinkFine						*/
	ui16	motorGearing [3];						/*!<  1.0f --> 256. Real number encoded as 8.8 fixed point							*/

	i8		encoderLimitMin [3],					/*!<  ...																			*/
			encoderLimitMax [3];					/*!<  ...-127 --> 127. Units: 3 degree. Starting from frw. ver. 2.61
														  is deprecated and replaced by the FRAME_CAM_ANGLE_MIN							*/

	i8		notch1_Gain [3],						/*!<  ...																			*/
			notch2_Gain [3],						/*!<  ...																			*/
			notch3_Gain [3];						/*!<  ...-100 --> 100. Units: dB. Notch gain
														  (positive – notch, negative – peak filter)									*/

	ui8		beeperVolume;							/*!<  0 --> 255																		*/
	ui16	encoderGearRatio [3];					/*!<  Units: 0.001																	*/
	ui8		encoderType [3];						/*!<  See @ref sbgcEncoderType_t and @ref sbgcEncoderFlag_t enumerations			*/
	ui8		encoderCfg [3];							/*!<  See @ref sbgcEncoderCfg_t enumeration											*/
	ui8		outerP [3];								/*!<  0 --> 255																		*/
	ui8		outerI [3];								/*!<  0 --> 255																		*/

	i8		magAxisTop,								/*!<  ...																			*/
			magAxisRight;							/*!<  ...See @ref sbgcMagAxis_t enumeration											*/

	ui8		magTrust;								/*!<  0 --> 255																		*/
	i8		magDeclination;							/*!<  -90 --> 90. Units: degree														*/
	ui16	accLPF_Freq;							/*!<  0 --> 1000. Units: 0.01 Hz													*/
	ui8		D_TermLPF_Freq [3];						/*!<  0 --> 60. Units: 10 Hz														*/

}			sbgcMainParamsExt_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t mainParamsExtReferenceInfoArray [];
	extern const ui8 mainParamsExtReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *					 Profile Params Ext 2 Structures
 */
/**	@addtogroup	Profile_Params_Ext_2
 *	@{
 */
/**	@brief	Part of sbgcMainParamsExt2_t structure
 *
 *	@note	sbgcMainParamsExt2_t.MAV_CMPE_Channel
 */
typedef struct PACKED__
{
	ui8		MAV_Src,								/*!<  See @ref sbgcMAV_Src_t enumeration											*/
			MAV_SysID,								/*!<  0 --> 255																		*/
			MAV_CompID,								/*!<  0 --> 255																		*/
			MAV_CfgFlags,							/*!<  See @ref sbgcMAV_CfgFlag_t enumeration										*/
			MAV_Reserved [4];

}			sbgcMAV_CMPE_Channel_t;

/**	@brief	Part of sbgcMainParamsExt2_t structure
 *
 *	@note	sbgcMainParamsExt2_t.StepSignalN
 */
typedef struct PACKED__
{
	ui8		stepSignalSrc,							/*!<  See @ref sbgcRC_MapSourceType_t and @ref sbgcRC_MapSource_t enumerations		*/
			stepSignalCfg;							/*!<  See @ref sbgcStepSignalCfgNumber_t, @ref sbgcStepSignalCfgMode_t and
														  @ref sbgcStepSignalCfgAdd_t enumerations										*/
}			sbgcStepSignalN_t;

/**	@brief	Part of sbgcMainParamsExt2_t structure
 *
 *	@note	sbgcMainParamsExt2_t.RC_CalibN
 */
typedef struct PACKED__
{
	ui8		RC_CalibSrc;							/*!<  See @ref sbgcRC_MapSourceType_t and @ref sbgcRC_MapSource_t enumerations		*/

	i8		RC_CalibOffset;							/*!<  ...																			*/
	ui8		RC_CalibNegScale,						/*!<  ...																			*/
			RC_CalibPosScale;						/*!<  ...Calibration is applied by the rule:\n
														  val = val + RC_CALIB_OFFSET*(RC_RANGE/2/128);\n
														  if(val > 0) val = val * ( 80 + RC_CALIB_POS_SCALE) / 100;\n
														  else val = val * ( 80 + RC_CALIB_NEG_SCALE) / 100;							*/
}			sbgcRC_CalibN_t;

/**	@brief	Structure type for work with
 *			MainParamsExt2 parameters
 *
 *	@ref	SBGC32_WriteParamsExt2 function\n
 *	@ref	SBGC32_ReadParamsExt2 function
 */
typedef struct PACKED__
{
	ui8		profileID;								/*!<  See @ref sbgcProfile_t enumeration.
														  To access current (active) profile, specify 255								*/
	sbgcMAV_CMPE_Channel_t	MAV_CMPE_Channel [2];	/*!<  0 : 1																			*/

	ui16	motorMagLinkFine [3];					/*!<  0 --> 65000. Units: 0.01														*/
	ui8		accLimiter [3];							/*!<  0 --> 200. Units: 5 degrees/sec²												*/
	ui8		PID_Gain [3];							/*!<  0 --> 255																		*/
	ui8		frameIMU_LPF_Freq;						/*!<  0 --> 200. Units: 1 Hz														*/
	ui8		autoPID_Cfg;							/*!<  See @ref sbgcAutoPID_Cfg_t enumeration. Also pay attention to
														  sbgcAutoPID_t.cfgFlags														*/
	ui8		autoPID_Gain;							/*!<  0 --> 255. Pay attention to sbgcAutoPID_t.Gain_VS_Stability					*/

	i16		frameCamAngleMin [3],					/*!<  ...																			*/
			frameCamAngleMax [3];					/*!<  ...Units: 1 degree. Frw. ver. 2.61+											*/

	ui16	generalFlags2;							/*!<  See @ref sbgcGeneralFlag2_t enumeration										*/
	ui8		autoSpeed;								/*!<  1 --> 255. Frw. ver. 2.61+													*/
	ui8		autoAccLimiter;							/*!<  1 --> 255. Units: 5 degrees/sec². Frw. ver. 2.61+								*/
	i16		IMU_OrientationCorr [3];				/*!<  Units: 0.01 degrees. Frw. ver. 2.61+											*/
	ui16	timelapseTime;							/*!<  Units: seconds. Frw. ver. 2.60+												*/
	ui16	emergencyStopRestartDelay;				/*!<  Units: ms																		*/
	ui8		timelapseAccPart;						/*!<  0 --> 250. Units: 0.2 %														*/
	ui16	momentum [3];							/*!<  Frw. ver. 2.62b7+																*/
	ui8		momentumCalibStimulus [3];				/*!<  1 --> 255. Frw. ver. 2.62b7+													*/
	ui8		momentumEllipticity [3];				/*!<  1 --> 255. Units: 0.05														*/
	ui8		followRange [3];						/*!<  1 --> 180. Frw. ver. 2.62b7+													*/
	ui8		stabAxis [3];							/*!<  See @ref sbgcStabAxis_t and @ref sbgcStabAxisSelection_t enumerations.
														  Frw. ver. 2.62b7+																*/
	i8		outerMotTiltAngle;						/*!<  -90 --> 90. Units: degrees													*/

	/* frw. ver. 2.66+ */
	ui8		startupAction [4];						/*!<  See @ref sbgcMenuCommand_t enumeration										*/
	ui8		startupActionSrc [2][4];				/*!<  See @ref sbgcRC_MapSourceType_t and @ref sbgcRC_MapSource_t enumerations		*/
	i8		startupActionThreshold [2][4];			/*!<  Threshold for RC signal on a given source, multiplied by 10					*/
	ui8		forcePositionCfg [3];					/*!<  See @ref sbgcForcePositionCfgSnap_t and @ref sbgcForcePositionCfgFlag_t
														  enumerations																	*/

	sbgcStepSignalN_t
					StepSignalN [6];				/*!<  0 : 1 : 2 : 3 : 4 : 5															*/

	sbgcRC_CalibN_t	RC_CalibN [5];					/*!<  0 : 1 : 2 : 3 : 4																*/

	ui8		parkingPosCfg;							/*!<  See @ref sbgcParkingPosCfg_t enumeration										*/
	ui8		extLED_PinID;							/*!<  See @ref sbgcTriggerPinID_t enumeration.
														  Use this pin to duplicate the on-board LED function							*/
	ui16	interruptCfg;							/*!<  See @ref sbgcInterruptCfg_t and @ref sbgcTriggerPinID_t enumeration			*/
	ui8		overloadTime;							/*!<  Units: 100 ms																	*/
	ui8		autoPID_Momentum;						/*!<  0 --> 255																		*/
	ui8		jerkSlope [3];							/*!<  Units: ms																		*/
	ui8		MAV_ControlMode;						/*!<  See @ref sbgcMAV_CtrlMode_t enumeration										*/

	ui8		RC_SerialSpeed,							/*!<  ...																			*/
			UART2_Speed;							/*!<  ...See @ref sbgcSerialSpeed_t enumeration										*/

	ui8		motorRes [3];							/*!<  0 --> 255. Units: 100 mOhm. Motor resistance (one phase)						*/
	ui16	currentLimit;							/*!<  0 --> 65535. Units: 10 mA														*/
	i8		middleMotTiltAngle;						/*!<  -90 --> 90. Units: degrees. Frw. ver. 2.67+									*/

}			sbgcMainParamsExt2_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t mainParamsExt2_ReferenceInfoArray [];
	extern const ui8 mainParamsExt2_ReferenceInfoArrayElCnt;
	/**	@endcond
	 */
#endif
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *					 Profile Params Ext 3 Structures
 */
/**	@addtogroup	Profile_Params_Ext_3
 *	@{
 */
/**	@brief	Structure type for work with
 *			MainParamsExt3 parameters
 *
 *	@ref	SBGC32_WriteParamsExt3 function\n
 *	@ref	SBGC32_ReadParamsExt3 function
 */
typedef struct PACKED__
{
	ui8		profileID;								/*!<  See @ref sbgcProfile_t enumeration
														  To access current (active) profile, specify 255								*/
	ui8		reserved1 [21];
	ui8		extIMU_Type;							/*!<  See @ref sbgcExtIMU_Type_t enumeration										*/
	ui8		extIMU_Port;							/*!<  See @ref sbgcExtIMU_Port_t enumeration										*/
	ui8		extIMU_Position;						/*!<  See @ref sbgcExtIMU_Position_t enumeration									*/
	ui8		extIMU_Orientation;						/*!<  See @ref sbgcExtIMU_Orientation_t enumeration									*/
	ui16	extIMU_Flags;							/*!<  See @ref sbgcExtIMU_Flag_t enumeration. Frw.ver. 2.68b7+						*/
	ui8		extIMU_Reserved [12];
	ui8		softLimitWidth [3];						/*!<  1 --> 255. Units: 0.1 degrees. Width of the software limits
														  defined by the FRAME_CAM_ANGLE_MIN, FRAME_CAM_ANGLE_MAX						*/
	ui8		ADC_ReplaceSrc [3];						/*!<  See @ref sbgcRC_MapSourceType_t and @ref sbgcRC_MapSource_t enumerations		*/
	ui8		glockMidMotPosCorrRate;					/*!<  0 --> 255																		*/
	ui8		extraBtnCfg [5];						/*!<  See @ref sbgcExtraBtnCfg_t enumeration										*/
	ui8		powerCtrlCfg [8];						/*!<  [0] - overcurrent_protection, units: 0.5 A
														  [1] - power_on_delay, units: 100 ms
														  [2] - power_off_delay, units: 100 ms
														  [3] - power_on_limiter, 0..255
														  [4...7] - reserved															*/
	ui8		reserved2 [3];
	ui8		CAN_IMU_ExtSensType;					/*!<  See @ref sbgcCAN_IMU_ExtSensType_t enumeration								*/
	ui16	profileFlags2;							/*!<  See @ref sbgcProfileFlag2_t enumeration										*/
	ui8		reserved3 [3];
	ui32	generalFlags3;							/*!<  See @ref sbgcGeneralFlag3_t enumeration										*/
	i16		followOffsetExt [3];					/*!<  -16384 --> 16384. Units: 0.02197265625 degree. Frw. ver. 2.70+. Use the
														  @ref sbgcAngleToDegree and @ref sbgcDegreeToAngle macros to comfortable
														  work with this field															*/
	ui16	motorStartupDelay;						/*!<  Units: ms																		*/

	ui8		IMU_ModelMain,
			IMU_ModelFrame;

	ui8		stabThresholdAngle [3];					/*!<  15 --> 80																		*/
	ui8		extBuzzerPin;
	ui8		encLimitReturnSpeed [3];
	ui8		tripodModeAutoThreshold;

	ui8		RC_DeadbandPitch,						/*!<  ...																			*/
			RC_DeadbandYaw,							/*!<  ...																			*/
			RC_ExpoRatePitch,						/*!<  ...																			*/
			RC_ExpoRateYaw;							/*!<  ...If the flag sbgcMainParamsExt3_t.profileFlags2 RC_EXPO_DEADBAND_SPLIT is
														  set, use this values for PITCH and YAW axes; otherwise, common RC_DEADBAND
														  and RC_EXPO_RATE variables are used for all axes								*/

	ui32	profileFlags3;
	ui8		defaultProfile;							/*!<  0 --> 4																		*/
	i16		retractedAngle [3];

	/* Shake generator parameters are listed next */
	ui8		amplitude [3];							/*!<  0 --> 255. Applied in logarithmic scale in order ROLL, TILT, PAN				*/

	ui8		baseFreq,								/*!<  0 --> 255. base_freq_hz = 0.3 + BASE_FREQ * 0.05								*/
			freqRange,								/*!<  0 --> 100. freq_range_mult = 1.5 + FREQ_RANGE * 0.1							*/
			pausePeriod,							/*!<  0 --> 255. pause_period_ms = 500 + PAUSE_PERIOD * 20							*/
			pauseBalance,							/*!<  0 --> 100																		*/
			pauseAttenuation,						/*!<  0 --> 100																		*/
			pauseRandomness,						/*!<  0 --> 100																		*/
			pausePhaseVar;							/*!<  0 --> 100																		*/

	ui8		resonanceGain [3];						/*!<  0 --> 255. resonance_gain_db = RESONANCE_GAIN * 0.2							*/
	ui8		resonanceFreq;							/*!<  0 --> 255. resonance_freq_hz = 0.3 + RESONANCE_FREQ * 0.1						*/
	i8		freqShift [3];							/*!<  -127 --> 127. Mapped to logarithmic scale 1/3 … 3								*/
	ui8		reserved4 [5];
	ui8		reserved5 [93];

}			sbgcMainParamsExt3_t;


#if (SBGC_USES_REF_INFO)
	/**	@cond
	 */
	extern const sbgcParameterReferenceInfo_t mainParamsExt3_ReferenceInfoArray [];
	extern const ui8 mainParamsExt3_ReferenceInfoArrayElCnt;
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
/**	@addtogroup	Profile_Common
 *	@{
 */
sbgcCommandStatus_t SBGC32_ManageProfileSet (sbgcGeneral_t *gSBGC, sbgcProfileSet_t slot, sbgcProfileSetAction_t action, sbgcConfirm_t *confirm
											 SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_WriteParamsSet (sbgcGeneral_t *gSBGC, sbgcProfileWritingFlag_t action, sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_WriteProfileNames (sbgcGeneral_t *gSBGC, const sbgcProfileNames_t *ProfileNames, sbgcConfirm_t *confirm
											  SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ReadProfileNames (sbgcGeneral_t *gSBGC, sbgcProfileNames_t *ProfileNames SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_UseDefaults (sbgcGeneral_t *gSBGC, sbgcProfile_t profileID SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Profile_Params_3
 *	@{
 */
sbgcCommandStatus_t SBGC32_WriteParams3 (sbgcGeneral_t *gSBGC, const sbgcMainParams3_t *mainParams3, sbgcConfirm_t *confirm SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ReadParams3 (sbgcGeneral_t *gSBGC, sbgcMainParams3_t *mainParams3, sbgcProfile_t profileID SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Profile_Params_Ext
 *	@{
 */
sbgcCommandStatus_t SBGC32_WriteParamsExt (sbgcGeneral_t *gSBGC, const sbgcMainParamsExt_t *mainParamsExt, sbgcConfirm_t *confirm
										   SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ReadParamsExt (sbgcGeneral_t *gSBGC, sbgcMainParamsExt_t *mainParamsExt, sbgcProfile_t profileID
										  SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Profile_Params_Ext_2
 *	@{
 */
sbgcCommandStatus_t SBGC32_WriteParamsExt2 (sbgcGeneral_t *gSBGC, const sbgcMainParamsExt2_t *mainParamsExt2, sbgcConfirm_t *confirm
											SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ReadParamsExt2 (sbgcGeneral_t *gSBGC, sbgcMainParamsExt2_t *mainParamsExt2, sbgcProfile_t profileID
										   SBGC_ADVANCED_PARAMS__);
/**	@}
 */


/**	@addtogroup	Profile_Params_Ext_3
 *	@{
 */
sbgcCommandStatus_t SBGC32_WriteParamsExt3 (sbgcGeneral_t *gSBGC, const sbgcMainParamsExt3_t *mainParamsExt3, sbgcConfirm_t *confirm
											SBGC_ADVANCED_PARAMS__);
sbgcCommandStatus_t SBGC32_ReadParamsExt3 (sbgcGeneral_t *gSBGC, sbgcMainParamsExt3_t *mainParamsExt3, sbgcProfile_t profileID
										   SBGC_ADVANCED_PARAMS__);
/**	@}
 */
/**	@endcond
 */

#endif /* SBGC_PROFILES_MODULE */


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

#endif		/* MODULES_PROFILES_H_ */
