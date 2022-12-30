/** ____________________________________________________________________
 *
 * 	@file		core.h
 *
 *	@brief 		Header file of the core for the custom usage library
 *				SerialAPI
 *
 *				<center><a href="https://www.basecamelectronics.com">
 *				www.basecamelectronics.com</a>
 *	____________________________________________________________________
 *
 *	@attention	<center><h3>
 *	Copyright © 2023 BaseCam Electronics™.</h3></center>
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
/** ____________________________________________________________________
 *
 * 	@defgroup	Core SBGC32 Core
 *	@ingroup	Sources
 *		@brief	SBGC32 Core Title Module
 *  ____________________________________________________________________
 *
 *	@defgroup	General General Objects
 *  @ingroup	Core
 *  	@brief	General Objects Module
 *
 * 	@defgroup	Communication Communication
 * 	@ingroup	Core
 * 		@brief	Communication Module
 *
 *  @defgroup	Parser_Memory Parser and Memory
 *  @ingroup	Core
 *  	@brief	Parser and Memory Module
 *
 *  @defgroup	Common Common
 *  @ingroup	Core
 *  	@brief	Common Module
 *
 *  @defgroup	Verification Verification Functions
 *  @ingroup	Core
 *  	@brief	Verification Functions Module
 *
 * 				Covered Commands:
 *
 *				### CMD_CONFIRM
 *				### CMD_ERROR
 *
 *	@defgroup	Other_External Other External Objects
 *  @ingroup	Core
 *  	@brief	Other External Objects Module
 *
 *  @defgroup	Debug Debug Functions
 *  @ingroup	Core
 *  	@brief	Debug Functions Module
 *
 *	____________________________________________________________________
 */

#ifndef     _CORE_H_
#define     _CORE_H_

#ifdef 		__cplusplus
extern 		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"adjunct.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *					 LL Communication Function Types
 */
/* Note : If you want to create your gimbal
 * communication driver, create it based on
 * these function type templates:
 */
typedef		ui32					(*GetTimeFunc_t)(void *Driver);

typedef     ui8 					(*TxFunc_t)(void *Driver, ui8 *data, ui16 size);
typedef     ui8 					(*RxFunc_t)(void *Driver, ui8 *data);
typedef		ui16					(*AvailableBytesFunc_t)(void *Driver);

typedef     void 					(*TxDebugFunc_t)(char *data, ui16 length);


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								Macros and Constants
 */
/*  - - - - - User Defined Parameters - - - - - - */
#define		SYS_BIG_ENDIAN			SET_OFF			/*!<  Memory organization of target-control device.
	 	 	 	 	 	 	 	 	 	 	 	 	 	  LITTLE ENDIAN if the SYS_BIG_ENDIAN macro is set off							*/
#define		SBGC_DEBUG_MODE			SET_ON			/*!<  Debug mode flag for handling detailed system information						*/

#define     MAX_BUFF_SIZE           256				/*!<  256 is recommended value. Maximum buffer size for communication with SBGC32	*/

#define		UNEXP_CMD_BUFFER_SIZE	512				/*!<  0 Min (command buffering is disabled) --> 65535 Max.
														  Buffer size for received unexpected serial commands							*/

#define		SBGC_TX_WAITING			100				/*!<  Units: milliseconds. Data transfer wait parameter on SBGC32
														  for the @ref SBGC32_DefaultInit function										*/
#define		SBGC_RX_WAITING			300				/*!<  Units: milliseconds. Data transfer wait parameter on SBGC32
														  for the @ref SBGC32_DefaultInit function										*/
#define		SBGC_STARTUP_DELAY		3000			/*!<  Units: milliseconds. System startup delay parameter							*/
/*  - - - - - - - - - - - - - - - - - - - - - - - */

/* - - System Defined Parameters (don't edit) - - */
#define 	RC_NUM_CHANNELS			6				/*!<  RC_ROLL : RC_PITCH : RC_YAW : CMD : FC_ROLL : FC_PITCH						*/

#define 	RC_NUM_ADC_CHANNELS		3
#define 	RC_INPUT_ADC_1 			33
#define 	RC_INPUT_ADC_2 			34
#define 	RC_INPUT_ADC_3 			35

#define 	RC_NUM_AUX_CHANNELS		3

#define 	VIRT_CHANNELS_QUANTITY 	31
#define  	RC_NUM_ALL_CHANNELS		RC_NUM_CHANNELS + VIRT_CHANNELS_QUANTITY + RC_NUM_ADC_CHANNELS + RC_NUM_AUX_CHANNELS
/*  - - - - - - - - - - - - - - - - - - - - - - - */

/*  - - - - - - - Other Constants - - - - - - - - */
#define		RX_BUFFER_OVERFLOW_FLAG	0xFFFFU

#define     PR1_START_CHARACTER     0x3EU			/*!<  '>'																			*/
#define     PR2_START_CHARACTER     0x24U           /*!<  '$'																			*/

#define     ROLL                    0
#define     PITCH                   1
#define     YAW                     2

#define		CMD_					3
#define		FC_ROLL					4
#define		FC_PITCH				5

#define     AXIS_X                  0
#define     AXIS_Y                  1
#define     AXIS_Z                  2

#define 	RC_INPUT_NO 			0
#define 	RC_INPUT_ROLL 			1
#define 	RC_INPUT_PITCH 			2
#define 	RC_INPUT_YAW 			3
#define 	RC_INPUT_FC_ROLL 		4
#define 	RC_INPUT_FC_PITCH 		5

#define 	RC_MIN_VAL 				-500
#define		RC_MAX_VAL 				500

#define 	RC_UNDEF			 	-10000
/*  - - - - - - - - - - - - - - - - - - - - - - - */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *					  Main SBGC Service Enumerations
 */
/**	@addtogroup	Communication
 *	@{
 */
/**	@note	SerialCommand_t.commandID
 */
typedef enum
{
	CMD_BOARD_INFO_3				= 20,
	CMD_READ_PARAMS_3				= 21,
	CMD_WRITE_PARAMS_3				= 22,
	CMD_REALTIME_DATA_3             = 23,
	CMD_SELECT_IMU_3                = 24,
	CMD_REALTIME_DATA_4            	= 25,
	CMD_ENCODERS_CALIB_OFFSET_4     = 26,
	CMD_ENCODERS_CALIB_FLD_OFFSET_4 = 27,
	CMD_READ_PROFILE_NAMES          = 28,
	CMD_WRITE_PROFILE_NAMES         = 29,
	CMD_QUEUE_PARAMS_INFO_3         = 30,
	CMD_SET_ADJ_VARS_VAL            = 31,
	CMD_SAVE_PARAMS_3               = 32,
	CMD_READ_PARAMS_EXT             = 33,
	CMD_WRITE_PARAMS_EXT            = 34,
	CMD_AUTO_PID                    = 35,
	CMD_SERVO_OUT                   = 36,
	CMD_I2C_WRITE_REG_BUF           = 39,
	CMD_I2C_READ_REG_BUF            = 40,
	CMD_WRITE_EXTERNAL_DATA			= 41,
	CMD_READ_EXTERNAL_DATA          = 42,
	CMD_READ_ADJ_VARS_CFG           = 43,
	CMD_WRITE_ADJ_VARS_CFG          = 44,
	CMD_API_VIRT_CH_CONTROL         = 45,
	CMD_ADJ_VARS_STATE              = 46,
	CMD_EEPROM_WRITE                = 47,
	CMD_EEPROM_READ                 = 48,
	CMD_CALIB_INFO                  = 49,
	CMD_SIGN_MESSAGE                = 50,
	CMD_BOOT_MODE_3                 = 51,
	CMD_SYSTEM_STATE                = 52,
	CMD_READ_FILE                   = 53,
	CMD_WRITE_FILE                  = 54,
	CMD_FS_CLEAR_ALL                = 55,
	CMD_AHRS_HELPER                 = 56,
	CMD_RUN_SCRIPT                  = 57,
	CMD_SCRIPT_DEBUG                = 58,
	CMD_CALIB_MAG                   = 59,
	CMD_GET_ANGLES_EXT              = 61,
	CMD_READ_PARAMS_EXT2           	= 62,
	CMD_WRITE_PARAMS_EXT2           = 63,
	CMD_GET_ADJ_VARS_VAL            = 64,
	CMD_CALIB_ACC                   = 65,
	CMD_CALIB_BAT                  	= 66,
	CMD_CONFIRM                     = 67,
	CMD_CONTROL                     = 67,
	CMD_REALTIME_DATA               = 68,
	CMD_EXECUTE_MENU                = 69,
	CMD_USE_DEFAULTS                = 70,
	CMD_CALIB_EXT_GAIN              = 71,
	CMD_HELPER_DATA                 = 72,
	CMD_GET_ANGLES                  = 73,
	CMD_CALIB_MOTOR_MAG_LINK        = 74,
	CMD_GYRO_CORRECTION             = 75,
	CMD_MOTORS_ON                   = 77,
	CMD_CALIB_OFFSET                = 79,
	CMD_CALIB_POLES                 = 80,
	CMD_READ_PARAMS                 = 82,
	CMD_TRIGGER_PIN                 = 84,
	CMD_DATA_STREAM_INTERVAL        = 85,
	CMD_BOARD_INFO                 	= 86,
	CMD_WRITE_PARAMS                = 87,
	CMD_REALTIME_DATA_CUSTOM        = 88,
	CMD_BEEP_SOUND                  = 89,
	CMD_CONTROL_CONFIG              = 90,
	CMD_CALIB_ORIENT_CORR           = 91,
	CMD_COGGING_CALIB_INFO          = 92,
	CMD_CALIB_COGGING               = 93,
	CMD_CALIB_ACC_EXT_REF           = 94,
	CMD_PROFILE_SET                 = 95,
	CMD_CAN_DEVICE_SCAN             = 96,
	CMD_CAN_DRV_HARD_PARAMS			= 97,
	CMD_CAN_DRV_STATE               = 98,
	CMD_CAN_DRV_CALIBRATE           = 99,
	CMD_READ_RC_INPUTS              = 100,
	CMD_REALTIME_DATA_CAN_DRV       = 101,
	CMD_EVENT                       = 102,
	CMD_CALIB_GYRO                  = 103,
	CMD_READ_PARAMS_EXT3            = 104,
	CMD_WRITE_PARAMS_EXT3           = 105,
	CMD_EXT_IMU_DEBUG_INFO          = 106,
	CMD_SET_DEVICE_ADDR             = 107,
	CMD_AUTO_PID2                   = 108,
	CMD_MOTORS_OFF                  = 109,
	CMD_EXT_IMU_CMD                	= 110,
	CMD_READ_STATE_VARS             = 111,
	CMD_WRITE_STATE_VARS            = 112,
	CMD_SERIAL_PROXY                = 113,
	CMD_RESET                      	= 114,
	CMD_IMU_ADVANCED_CALIB          = 115,
	CMD_API_VIRT_CH_HIGH_RES        = 116,
	CMD_CALIB_ENCODER_LUT			= 117,
	CMD_CALIB_ENCODER_LUT_RES		= 118,
	CMD_WRITE_PARAMS_SET			= 119,
	CMD_CALIB_CUR_SENS				= 120,
	CMD_SET_DEBUG_PORT              = 249,
	CMD_MAVLINK_INFO                = 250,
	CMD_MAVLINK_DEBUG              	= 251,
	CMD_DEBUG_VARS_INFO_3           = 253,
	CMD_DEBUG_VARS_3                = 254,
	CMD_ERROR                       = 255

}	SBGC_Command_t;


typedef enum
{
	TX_RX_OK						= 0,

	RX_BUFFERED_COMMAND,

	RX_START_PARSE,
	RX_EMPTY_BUFF_ERROR,
	RX_BUFFER_REALTIME_ERROR,
	RX_HEADER_CHECKSUM_ERROR,
	RX_PAYLOAD_CHECKSUM_ERROR,
	RX_BUFFER_OVERFLOW_ERROR,
	RX_TIMEOUT_ERROR,

	TX_BUFFER_OVERFLOW_ERROR,

	NOT_SUPPORTED_BY_FIRMWARE

}	TxRxStatus_t;


/**	@note @ref SBGC32_DefaultInit, 7 arg
 */
typedef enum
{
	SBGC_PROTOCOL_V1 				= PR1_START_CHARACTER,
	SBGC_PROTOCOL_V2 				= PR2_START_CHARACTER

}	SBGC_ProtocolVersion_t;


typedef enum
{
	STATE_IDLE						= 0,
	STATE_RESYNC,
	STATE_CHECK_HEADER,
	STATE_CHECK_PAYLOAD

}	ParserState_t;
/**	@}
 */


/**	@addtogroup	Parser_Memory
 *	@{
 */
typedef enum
{
	PM_DEFAULT_8BIT					= 0,
	PM_DEFAULT_16BIT,
	PM_DEFAULT_32BIT,

	PM_CONTROL,										/*!<  See @ref Control_ParserStructDB												*/
	PM_CONTROL_CONFIG,								/*!<  See @ref ControlConfig_ParserStructDB											*/
	PM_MAIN_PARAMS_3,								/*!<  See @ref MainParams3_ParserStructDB											*/
	PM_MAIN_PARAMS_EXT,								/*!<  See @ref MainParamsExt_ParserStructDB											*/
	PM_MAIN_PARAMS_EXT_2,							/*!<  See @ref MainParamsExt2_ParserStructDB										*/
	PM_MAIN_PARAMS_EXT_3,							/*!<  See @ref MainParamsExt3_ParserStructDB										*/
	PM_DATA_STREAM_INTERVAL,						/*!<  See @ref DataStreamInterval_ParserStructDB									*/
	PM_REALTIME_DATA_3,								/*!<  See @ref RealTimeData3_ParserStructDB											*/
	PM_REALTIME_DATA_4,								/*!<  See @ref RealTimeData4_ParserStructDB											*/
	PM_GET_ANGLES,									/*!<  See @ref GetAngles_ParserStructDB												*/
	PM_GET_ANGLES_EXT,								/*!<  See @ref GetAnglesExt_ParserStructDB											*/
	PM_AV_STATE_OLD_TX,								/*!<  See @ref AdjVarsStateOldTx_ParserStructDB										*/
	PM_AV_STATE_OLD_RX,								/*!<  See @ref AdjVarsStateOldRx_ParserStructDB										*/
	PM_AV_STATE_TX,									/*!<  See @ref AdjVarsStateTx_ParserStructDB										*/
	PM_AV_STATE_RX,									/*!<  See @ref AdjVarsStateRx_ParserStructDB										*/
	PM_EXT_IMU_DEBUG_INFO,							/*!<  See @ref ExtIMU_DebugInfo_ParserStructDB										*/
	PM_GYRO_CORRECTION,								/*!<  See @ref GyroCorrection_ParserStructDB										*/
	PM_AHRS_HELPER,									/*!<  See @ref AHRS_Helper_ParserStructDB											*/
	PM_HELPER_DATA,									/*!<  See @ref HelperData_ParserStructDB											*/
	PM_HELPER_DATA_EXT,								/*!<  See @ref HelperDataExt_ParserStructDB											*/
	PM_CALIB_INFO,									/*!<  See @ref CalibInfo_ParserStructDB												*/
	PM_BOARD_INFO,									/*!<  See @ref BoardInfo_ParserStructDB												*/
	PM_BOARD_INFO_3,								/*!<  See @ref BoardInfo3_ParserStructDB											*/
	PM_AUTO_PID,									/*!<  See @ref AutoPID_ParserStructDB												*/
	PM_AUTO_PID_2,									/*!<  See @ref AutoPID_2_ParserStructDB												*/
	PM_AUTO_PID_STATE,								/*!<  See @ref AutoPID_State_ParserStructDB											*/
	PM_STATE_VARS,									/*!<  See @ref StateVars_ParserStructDB												*/
	PM_AHRS_DEBUG_INFO,								/*!<  See @ref AHRS_DebugInfo_ParserStructDB										*/
	PM_MOTOR_4_CONTROL								/*!<  See @ref Motor4_Control_ParserStructDB										*/

}	ParserMap_t;
/**	@}
 */


/**	@addtogroup	Verification
 *	@{
 */
typedef enum
{
	CONFIRMATION_OK					= 0,

	CONFIRMATION_ERROR,
	CONFIRMATION_TIMEOUT

}	ConfirmationStatus_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						Main SBGC Service Structures
 */
/**	@addtogroup	General
 *	@{
 */
/**	@brief	General SBGC32 configurations structure
 */
typedef struct
{
	void 					*Drv;					/*!<  Main hardware driver object for STM32 and Linux OS.
	 	 	 	 	 	 	 	 	 	 	 	 	 	  Fully initialized with a Driver_Init function									*/
	TxFunc_t				TxFunc;					/*!<  Pointer to user-defined data buffer transfer function							*/
	RxFunc_t				RxFunc;					/*!<  Pointer to a user-defined function to receive one byte of data				*/
	AvailableBytesFunc_t	AvailableBytesFunc;		/*!<  Pointer to a user-defined function that returns the number of
														  available bytes in the receive buffer											*/
	TxDebugFunc_t			TxDebugFunc;			/*!<  Pointer to user-defined debug-data buffer transfer function					*/

	GetTimeFunc_t			GetTimeFunc;			/*!<  Pointer to a user-defined function that returns
	 	 	 	 	 	 	 	 	 	 	 	 	 	  the current time in milliseconds												*/

	SBGC_ProtocolVersion_t	protocolVersion;		/*!<  Variable storing the current version of the protocol							*/

	ui32					txTimeout,				/*!<  The value of the maximum timeout for sending a SerialCommand					*/
							rxTimeout,				/*!<  The value of the maximum timeout for receiving a SerialCommand				*/
							txrxTimeout;			/*!<  The maximum timeout value for receiving a response to a SerialCommand request	*/

	/* Private variables */							// 	  Values are not allowed to be manually modified by the user!
	ui8 	_boardVersion;							/*!<  PCB version of this device													*/
	ui16	_firmwareVersion;						/*!<  Firmware version of this device												*/

	ui16	_txErrorsCount;							/*!<  Counter of unsuccessful attempts to send SerialCommands						*/
	ui16	_rxErrorsCount;							/*!<  Parser error counter when receiving a SerialCommands							*/

	ui8		_unexpectedCommandsBuff
			[UNEXP_CMD_BUFFER_SIZE];				/*!<  Unexpected commands data buffer. Storage format:
			 	 	 	 	 	 	 	 	 	 	 	  ui8 commandID || ui8 payloadSize || ui8 payload[payloadSize]					*/
	ui16	_unexpectedCommandsBuffTail,			/*!<  Tail point of unexpected commands data buffer									*/
			_unexpectedCommandsBuffHead;			/*!<  Head point of unexpected commands data buffer									*/

	ui16	_missedCommandCount;					/*!<  Counter of skipped commands by Rx parser										*/

	TxRxStatus_t			_ParserCurrentStatus;	/*!<  The current state of the input SerialCommand parser							*/

	ConfirmationStatus_t	_confirmationStatus;	/*!<  System response according CMD_CONFIRM command									*/

}	GeneralSBGC_t;
/**	@}
 */


/**	@addtogroup	Communication
 *	@{
 */
/**	@brief	The type of structure required
 *  		to work with SerialCommands
 */
typedef struct
{
	SBGC_Command_t commandID;						/*!<  Identifier of the SerialCommand												*/
    		   ui8 payload [MAX_BUFF_SIZE];			/*!<  SerialCommand's payload buffer												*/
    		   ui8 payloadSize;						/*!<  Payload size of the SerialCommand												*/
    		   ui8 readPos;							/*!<  The current reading position of the SerialCommand								*/

}				SerialCommand_t;
/**	@}
 */


/**	@addtogroup	Parser_Memory
 *	@{
 */
/**	@brief	Parser auxiliary data structure type
 */
typedef struct
{
	const ui8	size;								/*!<  Variable size in bytes														*/
	const ui8	length;								/*!<  Number of elements in the array												*/

}				ParserBlock_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								 Common System Flags
 */
/**	@addtogroup	Other_External
 *	@{
 */
/**	@note	MainParams3_t.RC_Cmd_Low \n
 *			MainParams3_t.RC_Cmd_Mid \n
 *			MainParams3_t.RC_Cmd_High \n
 *			MainParams3_t.MenuBtnCmd1 \n
 *			MainParams3_t.MenuBtnCmd2 \n
 *			MainParams3_t.MenuBtnCmd3 \n
 *			MainParams3_t.MenuBtnCmd4 \n
 *			MainParams3_t.MenuBtnCmd5 \n
 *			MainParams3_t.MenuBtnCmdLong \n
 *			MainParamsExt2_t.startupAction \n
 *			TriggerSlot_t.triggerAction \n
 *			AdjVarsState_t.triggerAction__old
 */
typedef enum
{
	MENU_CMD_NO						= 0,
    MENU_CMD_PROFILE1 				= 1,
    MENU_CMD_PROFILE2				= 2,
    MENU_CMD_PROFILE3 				= 3,
    MENU_CMD_SWAP_PITCH_ROLL		= 4,
    MENU_CMD_SWAP_YAW_ROLL   		= 5,
    MENU_CMD_CALIB_ACC 				= 6,
    MENU_CMD_RESET 					= 7,
    MENU_CMD_SET_ANGLE				= 8,
    MENU_CMD_CALIB_GYRO 			= 9,
    MENU_CMD_MOTOR_TOGGLE 			= 10,
    MENU_CMD_MOTOR_ON 				= 11,
    MENU_CMD_MOTOR_OFF 				= 12,
    MENU_CMD_FRAME_UPSIDE_DOWN		= 13,
    MENU_CMD_PROFILE4				= 14,
    MENU_CMD_PROFILE5 				= 15,
    MENU_CMD_AUTO_PID				= 16,
    MENU_CMD_LOOK_DOWN 				= 17,
    MENU_CMD_HOME_POSITION 			= 18,
    MENU_CMD_RC_BIND				= 19,
    MENU_CMD_CALIB_GYRO_TEMP 		= 20,
    MENU_CMD_CALIB_ACC_TEMP			= 21,
    MENU_CMD_BUTTON_PRESS			= 22,
    MENU_CMD_RUN_SCRIPT1			= 23,
    MENU_CMD_RUN_SCRIPT2			= 24,
    MENU_CMD_RUN_SCRIPT3 			= 25,
    MENU_CMD_RUN_SCRIPT4			= 26,
    MENU_CMD_RUN_SCRIPT5			= 27,
    MENU_CMD_CALIB_MAG				= 33,
    MENU_CMD_LEVEL_ROLL_PITCH		= 34,
    MENU_CMD_CENTER_YAW				= 35,
    MENU_CMD_UNTWIST_CABLES			= 36,
    MENU_CMD_SET_ANGLE_NO_SAVE		= 37,
    MENU_CMD_HOME_POSITION_SHORTEST	= 38,
    MENU_CMD_CENTER_YAW_SHORTEST	= 39,
    MENU_CMD_ROTATE_YAW_180			= 40,
    MENU_CMD_ROTATE_YAW_180_FRAME_REL
	 	 	 	 	 	 	 	 	= 41,
    MENU_CMD_SWITCH_YAW_180_FRAME_REL
	 	 	 	 	 	 	 	 	= 42,
    MENU_CMD_SWITCH_POS_ROLL_90 	= 43,
    MENU_CMD_START_TIMELAPSE		= 44,
    MENU_CMD_CALIB_MOMENTUM 		= 45,
    MENU_CMD_LEVEL_ROLL 			= 46,
    MENU_CMD_REPEAT_TIMELAPSE 		= 47,
    MENU_CMD_LOAD_PROFILE_SET1 		= 48,
    MENU_CMD_LOAD_PROFILE_SET2 		= 49,
    MENU_CMD_LOAD_PROFILE_SET3 		= 50,
    MENU_CMD_LOAD_PROFILE_SET4 		= 51,
    MENU_CMD_LOAD_PROFILE_SET5 		= 52,
    MENU_CMD_LOAD_PROFILE_SET_BACKUP
	 	 	 	 	 	 	 	 	= 53,
    MENU_CMD_INVERT_RC_ROLL			= 54,
    MENU_CMD_INVERT_RC_PITCH 		= 55,
    MENU_CMD_INVERT_RC_YAW 			= 56,
    MENU_CMD_SNAP_TO_FIXED_POSITION	= 57,
    MENU_CMD_CAMERA_REC_PHOTO_EVENT	= 58,
    MENU_CMD_CAMERA_PHOTO_EVENT 	= 59,
    MENU_CMD_MOTORS_SAFE_STOP 		= 60,
    MENU_CMD_CALIB_ACC_AUTO 		= 61,
    MENU_CMD_RESET_IMU 				= 62,
    MENU_CMD_FORCED_FOLLOW_TOGGLE 	= 63,
    MENU_CMD_AUTO_PID_GAIN_ONLY 	= 64,
    MENU_CMD_LEVEL_PITCH			= 65,
    MENU_CMD_MOTORS_SAFE_TOGGLE 	= 66,
    MENU_CMD_TIMELAPSE_STEP1 		= 67,
    MENU_CMD_EXT_GYRO_ONLINE_CALIB 	= 68,
    MENU_CMD_DISABLE_FOLLOW_TOGGLE	= 69,
	MENU_CMD_SET_CUR_POS_AS_HOME	= 70,
	MENU_CMD_STOP_SCRIPT			= 71,
	MENU_CMD_TRIPOD_MODE_OFF		= 72,
	MENU_CMD_TRIPOD_MODE_ON			= 73,
	MENU_CMD_SET_RC_TRIM			= 74,

	/** only for MainParamsExt2_t.startupAction */
	MENU_BUTTON_IS_PRESSED			= BIT_7_SET

}	MenuCommand_t;


/**	@note	ConfirmationState_t.errCode \n
 * 			ScriptDebugInfo_t.errCode
 */
typedef enum
{
	NO_ERROR 						= 0,
	ERR_EEPROM_FAULT 				= 1,
	ERR_FILE_NOT_FOUND				= 2,
	ERR_FAT 						= 3,
	ERR_NO_FREE_SPACE 				= 4,
	ERR_FAT_IS_FULL 				= 5,
	ERR_FILE_SIZE 					= 6,
	ERR_CRC 						= 7,
	ERR_LIMIT_REACHED 				= 8,
	ERR_FILE_CORRUPTED 				= 9,
	ERR_WRONG_PARAMS 				= 10

}	ErrorCode_t;


/**	@note @ref	SBGC32_SelectIMU_3, 2 arg\n
 * 			MainParams3_t.curIMU \n
 *			RealTimeData_t.curIMU \n
 *			CalibInfo_t.IMU_Type
 */
typedef enum
{
	IMU_TYPE_CURRENTLY_ACTIVE		= 0,			/*!<  Only for CMD_SELECT_IMU_3 in extended format
	 	 	 	 	 	 	 	 	 	 	 	 	 	  See @ref SBGC32_SelectIMU_3 function											*/
	IMU_TYPE_MAIN					= 1,
	IMU_TYPE_FRAME					= 2

}	IMU_Type_t;


/**	@note	MainParams3_t.RC_MapROLL \n
 * 			MainParams3_t.RC_MapPITCH \n
 * 			MainParams3_t.RC_MapYAW \n
 * 			MainParams3_t.RC_MapCmd \n
 * 			MainParams3_t.RC_MapFC_ROLL \n
 * 			MainParams3_t.RC_MapFC_PITCH \n
 * 			MainParamsExt2_t.startupActionSrc \n
 * 			StepSignalN_t.stepSignalSrc \n
 * 			RC_CalibN_t.RC_CalibSrc \n
 * 			MainParamsExt3_t.ADC_ReplaceSrc \n
 * 			TriggerSlot_t.triggerSrcCh \n
 * 			AnalogSlot_t.analogSrc \n
 * 			RC_Inputs_t.RC_Src
 */
typedef enum
{
	RCMap_ANALOG_TYPE				= BIT_5_SET,
	RCMap_RC_SERIAL_TYPE			= BIT_6_SET,
	RCMap_API_VIRT_CH_TYPE			= BIT_7_SET,
	RCMap_STEP_SIGNAL_TYPE			= (BIT_5_SET | BIT_7_SET)

}	RC_MapSourceType_t;

/**	@note	MainParams3_t.RC_MapROLL \n
 * 			MainParams3_t.RC_MapPITCH \n
 * 			MainParams3_t.RC_MapYAW \n
 * 			MainParams3_t.RC_MapCmd \n
 * 			MainParams3_t.RC_MapFC_ROLL \n
 * 			MainParams3_t.RC_MapFC_PITCH \n
 * 			MainParamsExt2_t.startupActionSrc \n
 * 			StepSignalN_t.stepSignalSrc \n
 * 			RC_CalibN_t.RC_CalibSrc \n
 * 			MainParamsExt3_t.ADC_ReplaceSrc \n
 * 			TriggerSlot_t.triggerSrcCh \n
 * 			AnalogSlot_t.analogSrc \n
 * 			RC_Inputs_t.RC_Src
 */
typedef enum
{

	RCMap_RC_INPUT_ROLL 			= 1,
	RCMap_RC_INPUT_PITCH	 		= 2,
	RCMap_EXT_FC_INPUT_ROLL 		= 3,
	RCMap_EXT_FC_INPUT_PITCH 		= 4,
	RCMap_RC_INPUT_YAW 				= 5,

	RCMap_ADC_1 					= (RCMap_ANALOG_TYPE + 1),
	RCMap_ADC_2 					= (RCMap_ANALOG_TYPE + 2),
	RCMap_ADC_3 					= (RCMap_ANALOG_TYPE + 3),

	RCMap_SERIAL_VIRT_CH_1			= (RCMap_RC_SERIAL_TYPE + 1),
	/* ... */
	RCMap_SERIAL_VIRT_CH_31			= (RCMap_RC_SERIAL_TYPE + 31),

	RCMap_API_VIRT_CH_1				= (RCMap_API_VIRT_CH_TYPE + 1),
	/* ... */
	RCMap_API_VIRT_CH_31			= (RCMap_API_VIRT_CH_TYPE + 31),

	RCMap_STEP_SIGNAL_CH_1			= (RCMap_STEP_SIGNAL_TYPE + 1),
	/* ... */
	RCMap_STEP_SIGNAL_CH_6			= (RCMap_STEP_SIGNAL_TYPE + 6)

}	RC_MapSource_t;

/**	@brief	Used as a mask to extract the
 * 			RC source type
 *
 *  @param	RC_Src - Map channel source
 *
 *  @return	RC map source type
 */
static inline RC_MapSourceType_t GetRC_SourceType (RC_MapSource_t RC_Src)
{
	return (RC_MapSourceType_t)(RC_Src & 0b11100000);
}


/**	@note	MainParamsExt2_t.extLED_PinID \n
 *			MainParamsExt2_t.interruptCfg \n
 *			@ref SBGC32_SetTriggerPin, 2 arg
 */
typedef enum
{
	/* Triggers pin only if it isn't used for input */
	PIN_RC_ROLL						= 1,
	PIN_RC_PITCH 					= 2,
	PIN_EXT_FC_ROLL 				= 3,
	PIN_EXT_FC_PITCH				= 4,
	PIN_RC_INPUT_YAW 				= 5,
	PIN_AUX_1						= 16,
	PIN_AUX_2						= 17,
	PIN_AUX_3 						= 18,
	PIN_BUZZER						= 32,
	PIN_SSAT_POWER					= 33

}	TriggerPinID_t;


/**	@note	MainParams3_t.beeperModes \n
 *			BeeperSettings_t.mode
 */
typedef enum
{
	BM_BEEPER_MODE_CALIBRATE 		= BIT_0_SET,
	BM_BEEPER_MODE_CONFIRM 			= BIT_1_SET,
	BM_BEEPER_MODE_ERROR 			= BIT_2_SET,
	BM_BEEPER_MODE_CLICK 			= BIT_4_SET,
	BM_BEEPER_MODE_COMPLETE 		= BIT_5_SET,
	BM_BEEPER_MODE_INTRO 			= BIT_6_SET,

	BM_BEEPER_MODE_CUSTOM_MELODY	= BIT_15_SET

}	BeeperMode_t;


/**	@note	AHRS_DebugInfo_t.mainIMU_RefSrc \n
 *			AHRS_DebugInfo_t.frameIMU_RefSrc
 */
typedef enum
{
	AHRSRS_NO_REF					= 0,
	AHRSRS_INTERNAL					= 1,
	AHRSRS_EXTERNAL					= 2,
	AHRSRS_TRANSLATE				= 3

}	AHRS_RefSrc_t;

/**	@note	AHRS_DebugInfo_t.mainIMU_RefSrc \n
 *			AHRS_DebugInfo_t.frameIMU_RefSrc
 */
typedef enum
{
	FRS_INTERNAL_SENSOR_CONNECTED_USED
									= BIT_6_SET,
	FRS_PROCESSING_IMU_ENABLED		= BIT_7_SET

}	FlagsRefSrc_t;

/**@brief	Used as a mask to extract the
 * 			attitude reference source value from
 * 			AHRS_DebugInfo_t.mainIMU_RefSrc or
 * 			AHRS_DebugInfo_t.frameIMU_RefSrc
 *
 *	@param	value (AHRS_DebugInfo_t.mainIMU_RefSrc or
 *				   AHRS_DebugInfo_t.frameIMU_RefSrc)
 *
 *	@return	Attitude reference source
 */
static inline AHRS_RefSrc_t GetAttitudeRefSrc (ui8 value)
{
	return (AHRS_RefSrc_t)(value & 0b00000111);
}

/**@brief	Used as a mask to extract the
 * 			header reference source value from
 * 			AHRS_DebugInfo_t.mainIMU_RefSrc or
 * 			AHRS_DebugInfo_t.frameIMU_RefSrc
 *
 *	@param	value (AHRS_DebugInfo_t.mainIMU_RefSrc or
 *				   AHRS_DebugInfo_t.frameIMU_RefSrc)
 *
 *	@return	Header reference source
 */
static inline AHRS_RefSrc_t GetHeaderRefSrc (ui8 value)
{
	return (AHRS_RefSrc_t)((value & 0b00111000) >> 3);
}


/**	@note	AHRS_DebugInfo_t.extIMU_Status
 */
typedef enum
{
	EIMUS_DISABLED					= 0,
	EIMUS_NOT_CONNECTED				= 1,
	EIMUS_UNKNOWN					= 2,
	EIMUS_ERROR						= 3,
	EIMUS_BAD						= 4,
	EIMUS_COARSE					= 5,
	EIMUS_GOOD						= 6,
	EIMUS_FINE						= 7

}	ExtIMU_Status_t;

/**	@note	AHRS_DebugInfo_t.extIMU_Status
 */
typedef enum
{
	EIMUSF_BAD_MAG					= BIT_6_SET,
	EIMUSF_NO_GPS_SIGNAL			= BIT_7_SET

}	ExtIMU_StatusFlag_t;

/**@brief	Used as a mask to extract the
 * 			external IMU status value from
 * 			AHRS_DebugInfo_t.extIMU_Status
 *
 *	@param	value (AHRS_DebugInfo_t.extIMU_Status)
 *
 *	@return	external IMU status
 */
static inline ExtIMU_Status_t GetExtIMU_Status (ui8 value)
{
	return (ExtIMU_Status_t)(value & 0b00000111);
}

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *							Common System Structures
 */
/**	@brief	Attitude and heading reference system
 * 			structure type. Information about
 * 			the AHRS state
 *
 *	@note	Parameters:
 *
 * 			Firmware: 2.66+
 *
 *			RX 26 bytes
 *
 *			Included as a part of other commands
 */
typedef struct __PACKED__
{
	ui8		mainIMU_RefSrc,							/*!<  Encodes the source of the reference information for the main/frame IMU...		*/
			frameIMU_RefSrc,						/*!<  ...See @ref AHRS_RefSrc_t and @ref FlagsRefSrc_t enumerations					*/

			mainIMU_Z_RefErr,						/*!<  Units: 0.1°. Error between the reference defined by the mainIMU_RefSrc,
			 	 	 	 	 	 	 	 	 	 	 	  and the estimated attitude													*/
			mainIMU_H_RefErr,						/*!<  Units: 0.1°. Error between the reference defined by the mainIMU_RefSrc,
			 	 	 	 	 	 	 	 	 	 	 	  and the estimated attitude													*/
			frameIMU_Z_RefErr,						/*!<  Units: 0.1°. Error between the reference defined by the frameIMU_RefSrc,
			 	 	 	 	 	 	 	 	 	 	 	  and the estimated attitude													*/
			frameIMU_H_RefErr,						/*!<  Units: 0.1°. Error between the reference defined by the frameIMU_RefSrc,
			 	 	 	 	 	 	 	 	 	 	 	  and the estimated attitude													*/
			extIMU_Status;							/*!<  See @ref ExtIMU_Status_t and @ref ExtIMU_StatusFlag_t enumerations			*/

	ui16	extIMU_PacketsReceivedCnt,				/*!<  0 --> 65535																	*/
			extIMU_ParseErrCnt;						/*!<  0 --> 65535																	*/

	ui8		extCorrH_Ref,							/*!<  Units: 0.1°. Difference between the externally referenced heading
														  and the current heading														*/
			extCorrZ_Ref;							/*!<  Units: 0.1°. Difference between the externally referenced attitude
														  and the current heading														*/

	ui8		reserved [13];

}			AHRS_DebugInfo_t;


/**	@brief	Type of structure provides data
 *  		for the external controller
 *  		of the 4th axis motor
 *
 *	@note	Parameters:
 *
 * 			Firmware: 2.68+
 *
 *			RX 8 bytes
 *
 *			Included as a part of other commands
 */
typedef struct __PACKED__
{
	i16 	FF_Speed;								/*!<  Units: 0.06103701895 degree/sec. Feed-forward control							*/
	i16		angleError;								/*!<  Units: 0.02197265625 degree. Distance to reach the target angle of 4th axis	*/
	float	PID_Out;								/*!<  The output of the internal PID loop running over the ANGLE_ERROR
														  with the FF_SPEED mixed, scaled by the 'scale factor' parameter				*/

}			Motor4_Control_t;
/**	@}
 */


/**	@addtogroup	Verification
 *	@{
 */
/**	@brief	Structure type for receiving
 *  		SerialCommand confirmation data
 *
 *	@note	Parameters:
 *
 * 			CMD_CONFIRM
 * 			CMD_ERROR
 *
 *			RX 2-5 bytes
 */
typedef struct __PACKED__
{
	ui8			cmdID;								/*!<  Identifier of the command being confirmed										*/
	ui16		cmdData;							/*!<  Data depends on command to be confirmed										*/

	ui8			errCode;							/*!<  See @ref ErrorCode_t enumeration												*/
	ui8			errData [4];						/*!<  Data depends on error type													*/

}				ConfirmationState_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 								 Function Prototypes
 */
/**	@addtogroup	Communication
 *	@{
 */
TxRxStatus_t SBGC32_TX (GeneralSBGC_t *generalSBGC, SerialCommand_t *serialCommand);
TxRxStatus_t SBGC32_RX (GeneralSBGC_t *generalSBGC, SerialCommand_t *serialCommand, ui32 timeout);
TxRxStatus_t SBGC32_TX_RX (GeneralSBGC_t *generalSBGC, SerialCommand_t *serialCommand, SBGC_Command_t cmdID);
/**	@}
 */


/**	@addtogroup	Parser_Memory
 *	@{
 */
ui8 ConvertWithPM (void *pDestination, const void *pSource, ui8 size, ParserMap_t parserMap);
void WriteBuff (SerialCommand_t *cmd, const void *buff, ui8 size, ParserMap_t parserMap);
void ReadBuff (SerialCommand_t *cmd, void *buff, ui8 size, ParserMap_t parserMap);
void ToLittleEndian (const void *value, ui8 *payload, ui8 size);
void FromLittleEndian (void *value, ui8 *payload, ui8 size);
void SwapBytesInStruct (ui8 *buff, ui8 size, ParserMap_t parserMap);
void SwapMemoryContent (ui8 *p1, ui8 *p2);
void WriteByte (SerialCommand_t *cmd, const ui8 byte);
ui8 ReadByte (SerialCommand_t *cmd);
void WriteWord (SerialCommand_t *cmd, const ui16 word);
ui16 ReadWord (SerialCommand_t *cmd);
void WriteLong (SerialCommand_t *cmd, const ui32 dword);
ui32 ReadLong (SerialCommand_t *cmd);
void WriteEmptyBuff (SerialCommand_t *cmd, ui8 size);
void SkipBytes (SerialCommand_t *cmd, ui8 size);
void InitCmdWrite (SerialCommand_t *cmd, SBGC_Command_t cmdID);
/**	@}
 */


/**	@addtogroup	Common
 *	@{
 */
TxRxStatus_t SBGC32_SendEmptyCommand (GeneralSBGC_t *generalSBGC, SBGC_Command_t cmdID);
TxRxStatus_t SBGC32_DefaultInit (GeneralSBGC_t *generalSBGC, TxFunc_t TxFunc, RxFunc_t RxFunc,
								 AvailableBytesFunc_t AvailableBytesFunc, TxDebugFunc_t TxDebugFunc,
								 GetTimeFunc_t GetTimeFunc, SBGC_ProtocolVersion_t protocolVersion);
/**	@}
 */


/**	@addtogroup	Verification
 *	@{
 */
TxRxStatus_t SBGC32_CheckConfirmation (GeneralSBGC_t *generalSBGC, ConfirmationState_t *confirmationState, SBGC_Command_t cmdID);
ui8 Modulo256_Calculate (ui8 *data, ui16 length);
ui16 CRC16_Calculate (ui8 *data, ui16 length);
TxRxStatus_t CheckReceipt (GeneralSBGC_t *generalSBGC, TxRxStatus_t receiveStatus, char *message);
/**	@}
 */


/**	@addtogroup	Debug
 *	@{
 */
void PrintMessage (GeneralSBGC_t *generalSBGC, char *data, ui16 length);
void PrintStructElement (GeneralSBGC_t *generalSBGC, void *data, const char *str, VarType_t vType);
ui8 ConvertErrorToString (TxRxStatus_t txRxStatus, char *str);


/**	@brief	Transforms the board version variable to string
 *
 *	@param	boardVer - BoardInfo_t.boardVer
 *	@param	*pBuff - buffer to write
 */
static inline void FormatBoardVersion (ui8 boardVer, char* pBuff)
{
	ui8 majorVer = boardVer / 10;
	ui8 minorVer = boardVer % 10;
	sprintf(pBuff, "%u.%u", majorVer, minorVer);
}


/**	@brief	Transforms the firmware version variable to string
 *
 *	@param	firmwareVer - BoardInfo_t.firmwareVer
 *	@param	*pBuff - buffer to write
 */
static inline void FormatFirmwareVersion (ui16 firmwareVer, char* pBuff)
{
	ui8 majorVer = firmwareVer / 1000;
	ui8 minorVer = (firmwareVer % 1000) / 10;
	ui8 betaVer = firmwareVer % 10;

	if (betaVer != 0)
		sprintf(pBuff, "%u.%ub%u", majorVer, minorVer, betaVer);

	else
		sprintf(pBuff, "%u.%u", majorVer, minorVer);
}
/**	@}
 */

/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef 		__cplusplus
			}
#endif

#endif      /* _CORE_H_ */
