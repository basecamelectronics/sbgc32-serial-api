/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.2
 *
 *	@file		core.h
 *
 *	@brief		Header file of the core layers glue
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

#ifndef		SERIAL_API_CORE_H_
#define		SERIAL_API_CORE_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../sbgc32.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *					 LL Communication Function Types
 */
typedef		sbgcTicks_t				(*sbgcGetTime_t)(void);

typedef		ui8						(*sbgcTx_t)(void *drv, ui8 *data, ui16 size);
typedef		ui8						(*sbgcRx_t)(void *drv, ui8 *data);
typedef		ui16					(*sbgcAvailableBytes_t)(void *drv);

/* Secondary debug functions */
typedef		void					(*sbgcTxDebug_t)(char *data, ui16 length);
typedef		int						(*sbgcSprintf_t)(char *buffer, const char *format, ...);

/* Serial Buffers' Parameters ----------------------
 */
#define		SBGC_TX_BUFF_POW		(SBGC_TX_BUFFER_SIZE + 7)
#define		SBGC_RX_BUFF_POW		(SBGC_RX_BUFFER_SIZE + 7)

#define		SBGC_TX_BUFF_TOTAL_SIZE	(1 << SBGC_TX_BUFF_POW)
#define		SBGC_RX_BUFF_TOTAL_SIZE	(1 << SBGC_RX_BUFF_POW)

#define		SBGC_TX_BUFF_SIZE_MASK	(SBGC_TX_BUFF_TOTAL_SIZE - 1)
#define		SBGC_RX_BUFF_SIZE_MASK	(SBGC_RX_BUFF_TOTAL_SIZE - 1)

#define		SBGC_MAX_SER_BUFF_SIZE	256U

/* Checks ------------------------------------------
 */
#if (SBGC_SYS_BIG_ENDIAN)
	#define	SBGC_SYS_LITTLE_ENDIAN	sbgcOFF
#else
	#define	SBGC_SYS_LITTLE_ENDIAN	sbgcON
#endif

#if (SBGC_PROTOCOL_VERSION == 1)
	#define	SBGC_SERVICE_BYTES_NUM	5
#else
	#define	SBGC_SERVICE_BYTES_NUM	6
#endif

#if (SBGC_NON_BLOCKING_MODE)
	#define	SBGC_USES_BLOCKING_MODE	sbgcOFF
#else
	#define	SBGC_USES_BLOCKING_MODE	sbgcON
#endif

#if (SBGC_NON_BLOCKING_MODE && SBGC_NEED_TOKENS && (SBGC_USES_OS_SUPPORT == sbgcOFF))
	#define	SBGC_USES_TOKENS		sbgcON
#else
	#define	SBGC_USES_TOKENS		sbgcOFF
#endif

#if (SBGC_NEED_CALLBACKS && SBGC_NON_BLOCKING_MODE)
	#define	SBGC_USES_CALLBACKS		sbgcON
#else
	#define	SBGC_USES_CALLBACKS		sbgcOFF
#endif

#if (SBGC_NEED_DEBUG && (SBGC_LOG_COMMAND_TIME || SBGC_LOG_COMMAND_NUMBER || SBGC_LOG_COMMAND_DIR || SBGC_LOG_COMMAND_NAME ||\
						 SBGC_LOG_COMMAND_ID || SBGC_LOG_COMMAND_STATUS || SBGC_LOG_COMMAND_PARAM))
	#define	SBGC_USES_LOGS			sbgcON
#else
	#define	SBGC_USES_LOGS			sbgcOFF
#endif

#if (SBGC_NEED_DEBUG && SBGC_CUSTOM_SPRINTF)
	#define	SBGC_USES_CUSTOM_SPRINTF		sbgcON
#else
	#define	SBGC_USES_CUSTOM_SPRINTF		sbgcOFF
#endif

#if (SBGC_SYS_BIG_ENDIAN || SBGC_NEED_REF_INFO)
	#define	SBGC_USES_REF_INFO		sbgcON
#else
	#define	SBGC_USES_REF_INFO		sbgcOFF
#endif

#if (SBGC_USES_BLOCKING_MODE)
	#undef	SBGC_MAX_COMMAND_NUM
	#define	SBGC_MAX_COMMAND_NUM	1
#endif

/* Substitutions -----------------------------------
 */
#if (SBGC_USES_OS_SUPPORT)
	#define	serialAPI_Yield()		{ SystemSBGC32_Yield(); }

	#define	serialAPI_Suspend()		{ if (gSBGC->_api->busyFlag) {\
									  gSBGC->_api->busyFlag = sbgcFALSE; SystemSBGC32_SuspendThread(&gSBGC->_api->threadHandle); }\
									  serialAPI_Yield() }
	#define	serialAPI_Resume()		{ if (!gSBGC->_api->busyFlag){\
									  gSBGC->_api->busyFlag = sbgcTRUE ; SystemSBGC32_ResumeThread(&gSBGC->_api->threadHandle); }\
									  serialAPI_Yield() }

	#define	serialAPI_TakeMutex()	{ SystemSBGC32_TakeMutex(&gSBGC->_api->mutexSerialAPI); }
	#define	serialAPI_GiveMutex()	{ SystemSBGC32_GiveMutex(&gSBGC->_api->mutexSerialAPI); }

	#define	serialAPI_DemoteThreadPrior()	{ SystemSBGC32_SetThreadPriority(&gSBGC->_api->threadHandle, SBGC_THREAD_QUIET_PRIOR); }
	#define	serialAPI_RestoreThreadPrior()	{ SystemSBGC32_SetThreadPriority(&gSBGC->_api->threadHandle, SBGC_THREAD_PRIOR); }

#else
	#define	serialAPI_Yield()
	#define	serialAPI_Suspend()
	#define	serialAPI_Resume()
	#define	serialAPI_TakeMutex()
	#define	serialAPI_GiveMutex()
	#define	serialAPI_DemoteThreadPrior()
	#define	serialAPI_RestoreThreadPrior()
#endif

#if (SBGC_SEND_IMMEDIATELY)
	#undef	SBGC_TX_BUFFER_SIZE
	#define	SBGC_TX_BUFFER_SIZE		1
#endif

#if (SBGC_NON_BLOCKING_MODE)
	#define	SCTimeout_DEFAULT		SBGC_DEFAULT_TIMEOUT
	#define	SCTimeout_MAX			0xFFFFFFFF
	#define	SBGC_DEFAULT_FEATURES_	SCParam_NO, SCPrior_LOW, SCTimeout_DEFAULT

	#if (SBGC_USES_TOKENS)

	#define	SBGC_EMPTY_TOKEN		0xFFFFU

		#if (SBGC_USES_CALLBACKS)
			#define	SBGC_NO_CALLBACK_		NULL, NULL

			#define	SBGC_ADVANCED_PARAMS__	, ui8 parameters, serialAPI_CommandPriority_t priority, ui32 timeout,\
											sbgcCommandToken_t *commandToken, serialAPI_Callback_t callback, void *callbackArg
			#define	SBGC_ADVANCED_PARAMS_	ui8 parameters, serialAPI_CommandPriority_t priority, ui32 timeout,\
											sbgcCommandToken_t *commandToken, serialAPI_Callback_t callback, void *callbackArg
			#define	SBGC_ADVANCED_ARGS__	, parameters, priority, timeout, commandToken, callback, callbackArg
			#define	SBGC_ADVANCED_ARGS_		parameters, priority, timeout, commandToken, callback, callbackArg

			#define	SBGC_DEFAULT_ARGS__		, SBGC_DEFAULT_FEATURES_, SBGC_NO_TOKEN, SBGC_NO_CALLBACK_
			#define	SBGC_DEFAULT_ARGS_		SBGC_DEFAULT_FEATURES_, SBGC_NO_TOKEN, SBGC_NO_CALLBACK_

		#else
			#define	SBGC_ADVANCED_PARAMS__	, ui8 parameters, serialAPI_CommandPriority_t priority, ui32 timeout,\
											sbgcCommandToken_t *commandToken
			#define	SBGC_ADVANCED_PARAMS_	ui8 parameters, serialAPI_CommandPriority_t priority, ui32 timeout,\
											sbgcCommandToken_t *commandToken
			#define	SBGC_ADVANCED_ARGS__	, parameters, priority, timeout, commandToken
			#define	SBGC_ADVANCED_ARGS_		parameters, priority, timeout, commandToken

			#define	SBGC_DEFAULT_ARGS__		, SBGC_DEFAULT_FEATURES_, SBGC_NO_TOKEN
			#define	SBGC_DEFAULT_ARGS_		SBGC_DEFAULT_FEATURES_, SBGC_NO_TOKEN
		#endif

	#else
		#if (SBGC_USES_CALLBACKS)
			#define	SBGC_NO_CALLBACK_		NULL, NULL

			#define	SBGC_ADVANCED_PARAMS__	, ui8 parameters, serialAPI_CommandPriority_t priority, ui32 timeout,\
											serialAPI_Callback_t callback, void *callbackArg
			#define	SBGC_ADVANCED_PARAMS_	ui8 parameters, serialAPI_CommandPriority_t priority, ui32 timeout,\
											serialAPI_Callback_t callback, void *callbackArg
			#define	SBGC_ADVANCED_ARGS__	, parameters, priority, timeout, callback, callbackArg
			#define	SBGC_ADVANCED_ARGS_		parameters, priority, timeout, callback, callbackArg

			#define	SBGC_DEFAULT_ARGS__		, SBGC_DEFAULT_FEATURES_, SBGC_NO_CALLBACK_
			#define	SBGC_DEFAULT_ARGS_		SBGC_DEFAULT_FEATURES_, SBGC_NO_CALLBACK_

		#else
			#define	SBGC_ADVANCED_PARAMS__	, ui8 parameters, serialAPI_CommandPriority_t priority, ui32 timeout
			#define	SBGC_ADVANCED_PARAMS_	ui8 parameters, serialAPI_CommandPriority_t priority, ui32 timeout
			#define	SBGC_ADVANCED_ARGS__	, parameters, priority, timeout
			#define	SBGC_ADVANCED_ARGS_		parameters, priority, timeout

			#define	SBGC_DEFAULT_ARGS__		, SBGC_DEFAULT_FEATURES_
			#define	SBGC_DEFAULT_ARGS_		SBGC_DEFAULT_FEATURES_
		#endif
	#endif

#else
	#define	SBGC_ADVANCED_PARAMS__
	#define	SBGC_ADVANCED_PARAMS_
	#define	SBGC_ADVANCED_ARGS__
	#define	SBGC_ADVANCED_ARGS_

	#define	SBGC_DEFAULT_ARGS__
	#define	SBGC_DEFAULT_ARGS_
#endif

#if (SBGC_NEED_REF_INFO)
	#define	PARAM_BLOCK_(name, type)		{ name, type, 1 }
	#define	PARAMS_BLOCK_(name, type, len)	{ name, type, len }

#elif (SBGC_SYS_BIG_ENDIAN)
	#define	PARAM_BLOCK_(name, type)		{ type, 1 }
	#define	PARAMS_BLOCK_(name, type, len)	{ type, len }
#endif

#if (SBGC_NEED_ASSERTS)
	#define	sbgcAssertBoardVer(board)		{ if (gSBGC->_api->boardVersion < (board)) { gSBGC->_lastCommandStatus =\
											  sbgcCOMMAND_NOT_SUPPORTED_BY_HARDWARE; return sbgcCOMMAND_NOT_SUPPORTED_BY_HARDWARE; } }
	#define	sbgcAssertFrwVer(frw)			{ if (gSBGC->_api->baseFirmwareVersion < (frw)) { gSBGC->_lastCommandStatus =\
											  sbgcCOMMAND_NOT_SUPPORTED_BY_FIRMWARE; return sbgcCOMMAND_NOT_SUPPORTED_BY_FIRMWARE; } }
	#define	sbgcAssertFeature(ftr)			{ if (!(gSBGC->_api->boardFeatures & (ftr))) return sbgcCOMMAND_NOT_SUPPORTED_FEATURE; }
	#define	sbgcAssertFeature2(ftr)			{ if (!(gSBGC->_api->boardFeatures2 & (ftr))) return sbgcCOMMAND_NOT_SUPPORTED_FEATURE; }
	#define	sbgcAssertParam(val, min, max)	{ if (((val) < (min)) || ((val) > (max))) {\
											  gSBGC->_lastCommandStatus = sbgcCOMMAND_PARAM_ASSERT_ERROR;\
											  return sbgcCOMMAND_PARAM_ASSERT_ERROR; } }
	#define	sbgcAssertUnsParam(val, max)	{ if (((val) > (max))) {\
											  gSBGC->_lastCommandStatus = sbgcCOMMAND_PARAM_ASSERT_ERROR;\
											  return sbgcCOMMAND_PARAM_ASSERT_ERROR; } }

#else
	#define	sbgcAssertBoardVer(board)
	#define	sbgcAssertFrwVer(frw)
	#define	sbgcAssertFeature(ftr)
	#define	sbgcAssertFeature2(ftr)
	#define	sbgcAssertParam(val, min, max)
	#define	sbgcAssertUnsParam(val, max)
#endif

#define		serialAPI_Assert()		{ if (gSBGC->_api->serialAPI_Status != serialAPI_FORMING) return; }

#if (SBGC_USES_TOKENS)
	#define	serialAPI_GiveToken()	{ if (commandToken) { *commandToken = gSBGC->_api->lastCommandToken; } }
#else
	#define	serialAPI_GiveToken()
#endif

#define		serialAPI_GetTick()		gSBGC->_ll->drvGetTime()

#define		serialAPI_Lock()		{ serialAPI_TakeMutex();\
									  if (gSBGC->_api->serialAPI_Status != serialAPI_OK) return;\
									  gSBGC->_api->serialAPI_Status = serialAPI_FORMING; }

#define		serialAPI_LockBus()		{ serialAPI_TakeMutex();\
									  if (gSBGC->_api->serialAPI_Status != serialAPI_OK) return sbgcCOMMAND_SERIAL_API_BUSY_ERROR;\
									  gSBGC->_api->serialAPI_Status = serialAPI_HANDLING; }

#define		serialAPI_LockRead()	{ serialAPI_TakeMutex();\
									  if (gSBGC->_api->serialAPI_Status != serialAPI_OK) return sbgcCOMMAND_SERIAL_API_BUSY_ERROR;\
									  gSBGC->_api->serialAPI_Status = serialAPI_FORMING; }

#define		serialAPI_Unlock()		{ gSBGC->_api->serialAPI_Status = serialAPI_OK;\
									  serialAPI_GiveMutex(); }

#define		serialAPI_Abort()		{ gSBGC->_api->abortLast(gSBGC); return; }

#define		serialAPI_Error()		{ gSBGC->_api->serialAPI_Status = serialAPI_ERROR; return; }


#define		api_					(gSBGC->_api)

#define		curCmd_					(gSBGC->_api->currentSerialCommand)
#define		curCmdDest_				(gSBGC->_api->currentSerialCommand->_pDestination)


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *					  List of the SerialAPI commands
 */
/**	@addtogroup	Core
 *	@{
 */
/**	@brief	SerialAPI command identifier. Various commands
 *			mean different actions for SBGC32
 *
 *	@note	serialAPI_Command_t._commandID and much more
 */
typedef enum
{
	sbgcANY_SERIAL_COMMAND			= 1,			/*!<  A special case of the library when it doesn't matter what command receive		*/

	CMD_BOARD_INFO_3				= 20,			/*!<  Request additional board information											*/
	CMD_READ_PARAMS_3				= 21,			/*!<  Request parameters from the board												*/
	CMD_WRITE_PARAMS_3				= 22,			/*!<  Write parameters to board and saves to EEPROM									*/
	CMD_REALTIME_DATA_3				= 23,			/*!<  Request real-time data														*/
	CMD_SELECT_IMU_3				= 24,			/*!<  Select which IMU to calibrate or send realtime data							*/
	CMD_REALTIME_DATA_4				= 25,			/*!<  Receive extended version of real-time data									*/
	CMD_ENCODERS_CALIB_OFFSET_4		= 26,			/*!<  Calibrate offset of encoders													*/
	CMD_ENCODERS_CALIB_FLD_OFFSET_4	= 27,			/*!<  Start field offset calibration of encoders									*/
	CMD_READ_PROFILE_NAMES			= 28,			/*!<  Request profile names stored in EEPROM										*/
	CMD_WRITE_PROFILE_NAMES			= 29,			/*!<  Writes profile names to EEPROM												*/
	CMD_QUEUE_PARAMS_INFO_3			= 30,
	CMD_SET_ADJ_VARS_VAL			= 31,			/*!<  Update the value of selected parameter(-s)									*/
	CMD_SAVE_PARAMS_3				= 32,			/*!<  Saves current values of parameters linked to adjustable variables in EEPROM	*/
	CMD_READ_PARAMS_EXT				= 33,			/*!<  Request extended parameters part 1											*/
	CMD_WRITE_PARAMS_EXT			= 34,			/*!<  Write extended parameters part 2												*/
	CMD_AUTO_PID					= 35,			/*!<  Starts automatic PID calibration												*/
	CMD_SERVO_OUT					= 36,			/*!<  Output PWM signal on the servo1..4 pins										*/
	CMD_BODE_TEST_START_STOP		= 37,
	CMD_I2C_WRITE_REG_BUF			= 39,			/*!<  Writes data to any device connected to I2C line								*/
	CMD_I2C_READ_REG_BUF			= 40,			/*!<  Requests reading from any device connected to I2C line						*/
	CMD_WRITE_EXTERNAL_DATA			= 41,			/*!<  Stores any user data to the dedicated area in the EEPROM						*/
	CMD_READ_EXTERNAL_DATA			= 42,			/*!<  Request user data, stored in the EEPROM										*/
	CMD_READ_ADJ_VARS_CFG			= 43,			/*!<  Request configuration of mapping of control inputs to adjustable variables	*/
	CMD_WRITE_ADJ_VARS_CFG			= 44,			/*!<  Writes configuration of mapping of control inputs to adjustable variables		*/
	CMD_API_VIRT_CH_CONTROL			= 45,			/*!<  Update a state of 32 virtual channels											*/
	CMD_ADJ_VARS_STATE				= 46,			/*!<  Request the state of adj. variable in the given trigger and analog slots		*/
	CMD_EEPROM_WRITE				= 47,			/*!<  Writes a block of data to EEPROM to specified address							*/
	CMD_EEPROM_READ					= 48,			/*!<  Request a reading of block of data from EEPROM at the specified addr. & size	*/
	CMD_CALIB_INFO					= 49,			/*!<  Request information required for the "Calibration helper" dialog window		*/
	CMD_SIGN_MESSAGE				= 50,			/*!<  Sign message by secret keys													*/
	CMD_BOOT_MODE_3					= 51,			/*!<  Enter bootloader mode to upload firmware										*/
	CMD_SYSTEM_STATE				= 52,
	CMD_READ_FILE					= 53,			/*!<  Read file from internal filesystem											*/
	CMD_WRITE_FILE					= 54,			/*!<  Write file to internal filesystem												*/
	CMD_FS_CLEAR_ALL				= 55,			/*!<  Delete all files from internal filesystem										*/
	CMD_AHRS_HELPER					= 56,			/*!<  Send or request attitude of the IMU sensor									*/
	CMD_RUN_SCRIPT					= 57,			/*!<  Start or stop user-written script												*/
	CMD_SCRIPT_DEBUG				= 58,			/*!<  State of execution of user-written script										*/
	CMD_CALIB_MAG					= 59,			/*!<  Calibrate magnetometer														*/
	CMD_GET_ANGLES_EXT				= 61,			/*!<  Request information related to IMU angles and RC control state				*/
	CMD_READ_PARAMS_EXT2			= 62,			/*!<  Request extended parameters part 2											*/
	CMD_WRITE_PARAMS_EXT2			= 63,			/*!<  Writes extended parameters part 2												*/
	CMD_GET_ADJ_VARS_VAL			= 64,			/*!<  Query the actual value of selected parameter(-s)								*/
	CMD_CALIB_ACC					= 65,			/*!<  Calibrate accelerometer														*/
	CMD_CALIB_BAT					= 66,			/*!<  Calibrate internal voltage sensor												*/
	CMD_CONFIRM						= 67,			/*!<  Confirmation of previous command or finished calibration						*/
	CMD_CONTROL						= 67,			/*!<  Controls gimbal movement														*/
	CMD_REALTIME_DATA				= 68,			/*!<  Request real-time data														*/
	CMD_EXECUTE_MENU				= 69,			/*!<  Execute menu command															*/
	CMD_USE_DEFAULTS				= 70,			/*!<  Reset to  factory defaults													*/
	CMD_CALIB_EXT_GAIN				= 71,			/*!<  Calibrate EXT_FC gains														*/
	CMD_HELPER_DATA					= 72,			/*!<  Provide helper data for AHRS system											*/
	CMD_GET_ANGLES					= 73,			/*!<  Request information related to IMU angles and RC control state				*/
	CMD_CALIB_MOTOR_MAG_LINK		= 74,
	CMD_GYRO_CORRECTION				= 75,			/*!<  Correct the gyroscope sensor's zero bias manually								*/
	CMD_MODULE_LIST					= 76,			/*!<  Version information for the connected CAN devices								*/
	CMD_MOTORS_ON					= 77,			/*!<  Switch motors ON																*/
	CMD_CALIB_OFFSET				= 79,			/*!<  Calibrate follow offset														*/
	CMD_CALIB_POLES					= 80,			/*!<  Calibrate poles and direction													*/
	CMD_READ_PARAMS					= 82,			/*!<  Request parameters from the board												*/
	CMD_TRIGGER_PIN					= 84,			/*!<  Trigger output pin															*/
	CMD_DATA_STREAM_INTERVAL		= 85,			/*!<  Register or update data stream - a commands sent by the controller			*/
	CMD_BOARD_INFO					= 86,			/*!<  Request board and firmware information										*/
	CMD_WRITE_PARAMS				= 87,			/*!<  Writes parameters from the board												*/
	CMD_REALTIME_DATA_CUSTOM		= 88,			/*!<  Request configurable realtime data											*/
	CMD_BEEP_SOUND					= 89,			/*!<  Play melody by motors or emit standard beep sound								*/
	CMD_CONTROL_CONFIG				= 90,			/*!<  Configure the handling of CMD_CONTROL command									*/
	CMD_CALIB_ORIENT_CORR			= 91,			/*!<  Start the calibration of sensor misalignment correction						*/
	CMD_COGGING_CALIB_INFO			= 92,
	CMD_CALIB_COGGING				= 93,			/*!<  Starts  the motor non-linearities calibration									*/
	CMD_CALIB_ACC_EXT_REF			= 94,			/*!<  Refine the accelerometer calibration of the main IMU sensor					*/
	CMD_PROFILE_SET					= 95,			/*!<  Manage profile sets															*/
	CMD_CAN_DEVICE_SCAN				= 96,			/*!<  Scan for the connected CAN devices											*/
	CMD_CAN_DRV_HARD_PARAMS			= 97,
	CMD_CAN_DRV_STATE				= 98,
	CMD_CAN_DRV_CALIBRATE			= 99,
	CMD_READ_RC_INPUTS				= 100,			/*!<  Read values for the selected RC inputs										*/
	CMD_REALTIME_DATA_CAN_DRV		= 101,
	CMD_EVENT						= 102,			/*!<  Sent when event is triggered													*/
	CMD_CALIB_GYRO					= 103,			/*!<  Calibrate gyroscope															*/
	CMD_READ_PARAMS_EXT3			= 104,			/*!<  Request extended parameters part 3											*/
	CMD_WRITE_PARAMS_EXT3			= 105,			/*!<  Writes extended parameters part 3												*/
	CMD_EXT_IMU_DEBUG_INFO			= 106,			/*!<  Debug information for the external IMU sensor									*/
	CMD_SET_DEVICE_ADDR				= 107,
	CMD_AUTO_PID2					= 108,			/*!<  Starts automatic PID calibration ver.2										*/
	CMD_MOTORS_OFF					= 109,			/*!<  Switch motors OFF																*/
	CMD_EXT_IMU_CMD					= 110,			/*!<  Forward message from the controller to the connected external IMU sensor		*/
	CMD_READ_STATE_VARS				= 111,			/*!<  Request reading system persistent state vars., statistics & maintenance data	*/
	CMD_WRITE_STATE_VARS			= 112,			/*!<  Write reading system persistent state vars., statistics & maintenance data	*/
	CMD_SERIAL_PROXY				= 113,
	CMD_RESET						= 114,			/*!<  Tx: reset device / Rx: notification on device reset							*/
	CMD_IMU_ADVANCED_CALIB			= 115,
	CMD_API_VIRT_CH_HIGH_RES		= 116,			/*!<  Update a state of 31 virtual channels											*/
	CMD_CALIB_ENCODER_LUT			= 117,
	CMD_CALIB_ENCODER_LUT_RES		= 118,
	CMD_WRITE_PARAMS_SET			= 119,			/*!<  Start or end of the writing parameters sequence								*/
	CMD_CALIB_CUR_SENS				= 120,
	CMD_CONTROL_EXT					= 121,			/*!<  Controls gimbal movement, extended version									*/
	CMD_SYNC_MOTORS					= 123,			/*!<  Mechanically align motors working in parallel for a single axis				*/
	CMD_CAN_DRV_TELEMETRY			= 127,			/*!<  Receive CAN_DRV telemetry														*/
	CMD_EXT_MOTORS_ACTION			= 128,			/*!<  Execute an action on the selected motor(s)									*/
	CMD_EXT_MOTORS_CONTROL			= 129,			/*!<  Control the selected motor(s)													*/
	CMD_EXT_MOTORS_CONTROL_CONFIG	= 130,			/*!<  Configure run-time parameters for the selected motor(s)						*/
	CMD_EXT_MOTORS_STATE			= 131,			/*!<  Request real-time data related to auxiliary motors							*/
	CMD_ADJ_VARS_INFO				= 132,			/*!<  Query the list of all available variables										*/
	CMD_SERVO_OUT_EXT				= 133,			/*!<  Output PWM signal on the servo pins (internal and external)					*/
	CMD_SET_ADJ_VARS_VAL_F			= 134,			/*!<  Set the values of selected parameter(s) to floating points					*/
	CMD_GET_ADJ_VARS_VAL_F			= 135,			/*!<  Query the actual value of selected parameter(s) in floating points			*/
	CMD_CONTROL_QUAT				= 140,			/*!<  Control gimbal position in quaternions										*/
	CMD_CONTROL_QUAT_STATUS			= 141,			/*!<  Request real-time data related to gimbal control in quaternions				*/
	CMD_CONTROL_QUAT_CONFIG			= 142,			/*!<  Configure the quaternion-based control mode									*/
	CMD_EXT_SENS_CMD				= 150,			/*!<  Forward message to the GPS_IMU sensor											*/
	CMD_TRANSPARENT_SAPI			= 151,			/*!<  Send data to serial port on any device via CAN bus							*/
	CMD_SET_DEBUG_PORT				= 249,			/*!<  Use this port for debugging													*/
	CMD_MAVLINK_INFO				= 250,
	CMD_MAVLINK_DEBUG				= 251,
	CMD_DEBUG_VARS_INFO_3			= 253,			/*!<  Request information about debug variables										*/
	CMD_DEBUG_VARS_3				= 254,			/*!<  Request values of debug variables												*/
	CMD_ERROR						= 255			/*!<  Error executing previous command												*/

}	serialAPI_CommandID_t;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *					  Main SBGC Service Enumerations
 */
/**	@brief	Internal system state at current moment
 *
 *	@note	serialAPI_General_t.serialAPI_Status
 */
typedef enum
{
	serialAPI_OK					= 0,			/*!<  System is free and ready to act with serial commands							*/

	serialAPI_FORMING,								/*!<  A new serial command(-s) is forming											*/
	serialAPI_HANDLING,								/*!<  The low level are trying to transmit or receive and parse a serial command	*/

	serialAPI_ERROR									/*!<  A new serial command(-s) was corrupted during form or handle					*/

}	serialAPI_Status_t;


/**	@brief	Low-level SerialAPI communication status
 *
 *	@note	sbgcGeneral_t._lastSerialCommandStatus
 */
typedef enum
{
	serialAPI_TX_RX_OK				= 0,			/*!<  Serial command transmitted or received successful								*/

	#if (SBGC_NEED_CONFIRM_CMD == sbgcOFF)
		serialAPI_RX_REJECTED_CONFIRM_CMD,			/*!<  The command parser rejected a confirmation serial command						*/
	#endif

	/* Error cases */
	serialAPI_TX_BUS_BUSY_ERROR		= 2,			/*!<  Serial driver is busy now for transmit										*/

	serialAPI_RX_EMPTY_BUFF_ERROR,					/*!<  No data to receive. Driver's Rx buffer is empty								*/
	serialAPI_RX_BUFFER_REALTIME_ERROR,				/*!<  No data after the start byte was received										*/
	serialAPI_RX_HEADER_CHECKSUM_ERROR,				/*!<  Serial command's header was corrupted											*/
	serialAPI_RX_PAYLOAD_CHECKSUM_ERROR,			/*!<  Serial command's payload was corrupted										*/

	serialAPI_RX_NOT_FOUND_ERROR,					/*!<  The necessary serial command miss in the Rx buffers (high and low -layers)	*/
	serialAPI_RX_BUFFER_OVERFLOW_ERROR,				/*!<  High-level Rx buffer is full for a new command. May appear only if the
														  SBGC_RX_CMD_OLD_PRIOR parameter is enabled									*/

}	serialAPI_CommandStatus_t;


/**	@brief	High-level SBGC32 communication status
 *
 *	@note	sbgcGeneral_t._lastCommandStatus
 */
typedef enum
{
	sbgcCOMMAND_OK					= 0,			/*!<  Command (request) successful complete											*/

	sbgcCOMMAND_PROCESSING,							/*!<  Intermediate state when the command is still being processed					*/
	sbgcCOMMAND_QUEUE_IS_EMPTY,						/*!<  Can appear as a return value of the @ref SBGC32_TransmitAllCommands,
														  @ref SBGC32_ReceiveAllCommands and  @ref SBGC32_ProcessAllCommands functions.
														  Indicates that there are no Tx or Rx commands in the command buffer			*/
	/* Low-layer errors */
	sbgcCOMMAND_TX_ERROR,							/*!<  Tx error. See sbgcGeneral_t._lastSerialCommandStatus field to more details	*/
	sbgcCOMMAND_RX_ERROR,							/*!<  Rx error. See sbgcGeneral_t._lastSerialCommandStatus field to more details	*/

	/* User-layer errors */
	sbgcCOMMAND_NOT_SUPPORTED_BY_FIRMWARE,			/*!<  The current firmware of the SBGC32 device is old for requested command		*/
	sbgcCOMMAND_NOT_SUPPORTED_BY_HARDWARE,			/*!<  The feature isn't supported by this board										*/
	sbgcCOMMAND_NOT_SUPPORTED_FEATURE,				/*!<  Function isn't supported by the board due to firmware or hardware limitations	*/
	sbgcCOMMAND_PARAM_ASSERT_ERROR,					/*!<  Command was tried to run with wrong argument(-s). Check the sent values		*/
	sbgcCOMMAND_NOTHING_TO_CHANGE,					/*!<  The SBGC32 device currently stores such data									*/
	sbgcCOMMAND_DESTINATION_IS_NULL,				/*!<  There is no place to write requested data. Check the destination pointer		*/
	sbgcCOMMAND_BUFFER_OVERFLOW_ERROR,				/*!<  The main commands buffer has run out of space for new commands				*/
	sbgcCOMMAND_SERIAL_API_BUSY_ERROR,				/*!<  Some serial command is being processed - SerialAPI is busy					*/

	#if (SBGC_USES_TOKENS)
		sbgcCOMMAND_TOKEN_NOT_FOUND,				/*!<  There are no serial commands with such token									*/
	#endif

	#if (SBGC_OPTIMIZE_COMMANDS)
		sbgcCOMMAND_BUFFER_OPTIMIZED				/*!<  A similar serial command is already in the queue								*/
	#endif

}	sbgcCommandStatus_t;


#if (SBGC_USES_TOKENS)
	/** Stores the chained commands in the next format: 0-7 bits - Tx lowest 8-bit ID | 8-15 bits - Rx lowest 8-bit ID */
	typedef	ui16					sbgcCommandToken_t;
#endif


/**	@brief	Realtime state of serial command
 *
 *	@note	serialAPI_Command_t._state
 */
typedef enum
{
	SCState_FORMING					= 1,			/*!<  Serial command is filling now													*/
	SCState_PREPARED,								/*!<  Serial command is ready to handle. For non-blocking mode only					*/
	SCState_PROCESSING,								/*!<  Serial command is processing - transmit or receive							*/
	SCState_RELOAD,									/*!<  Serial command reloads after communication error.
														  May appear if SCParam_RETAIN flag is enabled									*/
	/* The commands are finished with these statuses */
	SCState_ABORTED,								/*!<  Serial command error was occurred												*/
	SCState_ERROR,									/*!<  Serial command wasn't delivered or received									*/
	SCState_PROCESSED				= 255			/*!<  Serial command has finished executing											*/

}	serialAPI_CommandState_t;


/**	@brief	Parameters flag for serial command
 *			It is assigned to all serial commands
 *			in the SBGC32 command request
 *
 *	@pre	@ref SBGC_NON_BLOCKING_MODE == sbgcON
 *
 *	@note	serialAPI_Command_t.parameters
 */
typedef enum
{
	SCParam_NO					= 0x00,			/*!<  Serial command has no additional parameters										*/

	SCParam_TX_CALLBACK			= 0x01,			/*!<  If SBGC32 command consists of	Tx and Rx serial commands, user callback will
													  be launched after successful transmission	without waiting for receiving			*/

	SCParam_FORCE_CALLBACK		= 0x02,			/*!<  The command's callback will be called on any result of the command completion		*/

	SCParam_RETAIN				= 0x04,			/*!<  Serial command won't be deleted until the same SBGC32_ command is called
													  without this parameter. Note that serial command timeout becomes period
													  of this command in the OS-mode 													*/

	#if (SBGC_USES_LOGS)
		SCParam_NO_NEED_LOG		= 0x08,			/*!<  No need to log this serial command												*/
	#endif

	#if (SBGC_USES_OS_SUPPORT)
		SCParam_FREEZE			= 0x10			/*!<  Freeze a code (thread) until the serial command completes. Be careful!
													  A frozen thread must have a priority of at least SBGC_THREAD_PRIORITY				*/
	#endif

}	serialAPI_CommandParam_t;

#if (SBGC_NON_BLOCKING_MODE)

	/**	@brief	Priority of serial command
	 *			It is assigned to all serial commands
	 *			in the SBGC32 command request
	 *
	 *	@note	serialAPI_Command_t.priority
	 */
	typedef enum
	{
		SCPrior_LOW					= 1,			/*!< Serial command has low priority												*/
		SCPrior_NORMAL				= 2,			/*!< Serial command has normal priority												*/
		SCPrior_HIGH				= 3,			/*!< Serial command has high priority												*/
		SCPrior_SUPREME				= 4				/*!< Serial command has supreme priority											*/

	}	serialAPI_CommandPriority_t;

#endif

#if (SBGC_USES_OS_SUPPORT)

	/**	@note	serialAPI_General_t.threadState
	 */
	typedef enum
	{
		SATS_NORMAL					= 0,			/*!<  The handler thread is normal processing or suspended							*/
		SATS_LOW_PRIOR				= 1,			/*!<  The handler thread priority is reduced due to retained commands handle		*/
		SATS_FREEZE_HANDLE			= 2				/*!<  The handler thread handles a freeze command									*/

	}	serialAPI_ThreadState_t;

#endif

#if (SBGC_NEED_CONFIRM_CMD)

	/**	@note	sbgcConfirm_t.status
	*/
	typedef enum
	{
		sbgcCONFIRM_NOT_RECEIVED	= 0,			/*!<  Serial communication error. No command received								*/
		sbgcCONFIRM_RECEIVED,						/*!<  Serial command is confirmed													*/
		sbgcCONFIRM_ERROR							/*!<  Serial command confirmation returned with an error. See
														  sbgcConfirm_t.errorCode and sbgcConfirm_t.errorData							*/

	}	sbgcConfirmStatus_t;

#endif
/**	@}
 */


/**	@addtogroup	Data_Parse
 *	@{
 */
/**	@brief	Key for big-endian parsing of the data structures
 *
 *	@note	DebugSBGC32_PrintWholeStruct, 3 arg\n
 *			SerialAPI_GetElementAddress, 2 arg\n
 *
 *			`*` - These arrays aren't directly associated
 *			with any specific command. They're part
 *			of other composite commands
 */
typedef enum
{
	PM_DEFAULT_8BIT					= 0,
	PM_DEFAULT_16BIT,
	PM_DEFAULT_32BIT,

	PM_AV_CONFIG,									/*!<  See @ref adjVarsCfgReferenceInfoArray											*/
	PM_AV_STATE_OLD_TX,								/*!<  See @ref adjVarsStateOldTxReferenceInfoArray									*/
	PM_AV_STATE_OLD_RX,								/*!<  See @ref adjVarsStateOldRxReferenceInfoArray									*/
	PM_AV_STATE_TX,									/*!<  See @ref adjVarsStateTxReferenceInfoArray										*/
	PM_AV_STATE_RX,									/*!<  See @ref adjVarsStateRxReferenceInfoArray										*/
	PM_IMU_EXT_CALIB,								/*!<  See @ref IMU_ExtCalibReferenceInfoArray										*/
	PM_CALIB_INFO,									/*!<  See @ref calibInfoReferenceInfoArray											*/
	PM_CALIB_COGGING,								/*!<  See @ref calibCoggingReferenceInfoArray										*/
	PM_AHRS_DEBUG_INFO,								/*!<  See @ref AHRS_DebugInfoReferenceInfoArray*									*/
	PM_MOTOR_4_CONTROL,								/*!<  See @ref motor4_ControlReferenceInfoArray*									*/
	PM_CONTROL,										/*!<  See @ref controlReferenceInfoArray											*/
	PM_CONTROL_EXT,									/*!<  See @ref controlExtReferenceInfoArray											*/
	PM_CONTROL_QUAT,								/*!<  See @ref controlQuatReferenceInfoArray										*/
	PM_CONTROL_CONFIG,								/*!<  See @ref controlConfigReferenceInfoArray										*/
	PM_CONTROL_QUAT_CONFIG,							/*!<  See @ref controlQuatConfigReferenceInfoArray									*/
	PM_EXT_MOTORS_CONTROL_CONFIG,					/*!<  See @ref extMotorsControlConfigReferenceInfoArray								*/
	PM_EXT_IMU_DEBUG_INFO,							/*!<  See @ref extIMU_DebugInfoReferenceInfoArray									*/
	PM_GYRO_CORRECTION,								/*!<  See @ref gyroCorrectionReferenceInfoArray										*/
	PM_AHRS_HELPER,									/*!<  See @ref AHRS_HelperReferenceInfoArray										*/
	PM_HELPER_DATA,									/*!<  See @ref helperDataReferenceInfoArray											*/
	PM_HELPER_DATA_EXT,								/*!<  See @ref helperDataExtReferenceInfoArray										*/
	PM_MAIN_PARAMS_3,								/*!<  See @ref mainParams3_ReferenceInfoArray										*/
	PM_MAIN_PARAMS_EXT,								/*!<  See @ref mainParamsExtReferenceInfoArray										*/
	PM_MAIN_PARAMS_EXT2,							/*!<  See @ref mainParamsExt2_ReferenceInfoArray									*/
	PM_MAIN_PARAMS_EXT3,							/*!<  See @ref mainParamsExt3_ReferenceInfoArray									*/
	PM_DATA_STREAM_INTERVAL,						/*!<  See @ref dataStreamIntervalReferenceInfoArray									*/
	PM_SYSTEM_POWER_STATE,							/*!<  See @ref systemPowerStateReferenceInfoArray*									*/
	PM_COMMUNICATION_ERRORS,						/*!<  See @ref communicationErrorsReferenceInfoArray*								*/
	PM_SYSTEM_STATE,								/*!<  See @ref systemStateReferenceInfoArray*										*/
	PM_REALTIME_DATA_3,								/*!<  See @ref realTimeDataReferenceInfoArray										*/
	PM_REALTIME_DATA_4,								/*!<  See @ref realTimeDataReferenceInfoArray										*/
	PM_GET_ANGLES,									/*!<  See @ref getAnglesReferenceInfoArray											*/
	PM_GET_ANGLES_EXT,								/*!<  See @ref getAnglesExtReferenceInfoArray										*/
	PM_BOARD_INFO,									/*!<  See @ref boardInfoReferenceInfoArray											*/
	PM_BOARD_INFO_3,								/*!<  See @ref boardInfo3_ReferenceInfoArray										*/
	PM_AUTO_PID,									/*!<  See @ref autoPID_ReferenceInfoArray											*/
	PM_AUTO_PID_2,									/*!<  See @ref autoPID2_ReferenceInfoArray											*/
	PM_AUTO_PID_STATE,								/*!<  See @ref autoPID_StateReferenceInfoArray										*/
	PM_SYNC_MOTORS,									/*!<  See @ref syncMotorsReferenceInfoArray											*/
    PM_SCRIPT_DEBUG_INFO,                           /*!<  See @ref scriptDebugInfoReferenceInfoArray									*/
	PM_STATE_VARS,									/*!<  See @ref stateVarsReferenceInfoArray											*/
	PM_CAN_DEVICE_SCAN								/*!<  See @ref CAN_DeviceScanReferenceInfoArray										*/

}	sbgcParserMap_t;
/**	@}
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						Main SBGC Service Structures
 */
/**	@addtogroup	Core
 *	@{
 */
/**	@brief	Structure type for operating with
 *			confirmation serial commands.
 *			Uses for all SBGC32 commands that
 *			send confirmation after reception
 *
 *	@pre	@ref SBGC_NEED_CONFIRM_CMD == sbgcON
 *
 *	@code

			// Create confirmation structure
			sbgcConfirm_t Confirm;

			#if (SBGC_CALIB_MODULE)

				sbgcCalibCogging_t CalibCogging = { 0 };

				SBGC32_CalibCogging(&SBGC32_Device, &CalibCogging, &Confirm);

				if (SerialAPI_GetConfirmStatus(&Confirm) == sbgcCONFIRM_ERROR)
				// An error is guaranteed here because an empty structure was sent
				{
					DebugSBGC32_PrintMessage(&SBGC32_Device, "Confirmation Error! ");
					DebugSBGC32_PrintStructElement(&SBGC32_Device, &Confirm.errorCode, "Code =", sbgcUCHAR);
				}

			#endif

			#if (SBGC_SERVICE_MODULE)

				// Ping the controller
				SBGC32_ExecuteMenu(&SBGC32_Device, MENU_CMD_NO, &Confirm);

				if (SerialAPI_GetConfirmStatus(&Confirm) != sbgcCONFIRM_RECEIVED)
				{
					// User confirmation error handler
					;
				}

				// Turn the motors off
				SBGC32_SetMotorsOFF(&SBGC32_Device, MOTOR_MODE_SAFE_STOP, &Confirm);

				if (SerialAPI_GetConfirmStatus(&Confirm) != sbgcCONFIRM_RECEIVED)
				{
					// User confirmation error handler
					;
				}

			#endif

 *	@endcode
 */
typedef struct PACKED__
{
	ui8		commandID;								/*!<  Identifier of the command being confirmed										*/

	union
	{
		ui16		cmdData;						/*!<  Data depends on command to be confirmed										*/

		struct
		{
			ui8		errorCode;						/*!<  See @ref sbgcErrorCode_t enumeration											*/
			ui8		errorData [4];					/*!<  Data depends on error type													*/
		};
	};

	#if (SBGC_NEED_CONFIRM_CMD)
		sbgcConfirmStatus_t
					status;							/*!<  Confirmation status. See @ref sbgcConfirmStatus_t enumeration					*/
	#endif

}	sbgcConfirm_t;


/** User's functions called after successful serial command finish (also after SerialAPI events) */
typedef		void					(*serialAPI_Callback_t)(void *callbackArg);


/**	@brief	The type of structure required to
 *			work with SerialAPI commands
 */
typedef struct
{
	/* Adjustable fields */
	serialAPI_CommandParam_t
							parameters;				/*!<  Various parameter flags of the serial command									*/

	#if (SBGC_NON_BLOCKING_MODE)
		serialAPI_CommandPriority_t
							priority;				/*!<  Priority of the serial command												*/
	#endif

	sbgcTicks_t				timeout;				/*!<  Upon expiration a serial command will be deleted, repeated or idled			*/

	#if (SBGC_USES_CALLBACKS)
		serialAPI_Callback_t
							callback;				/*!<  An user's function that will be called after successful finish				*/
		void				*callbackArg;			/*!<  Pointer to arguments for user callback function. If callback isn't NULL
														  and callbackArg is NULL it will be called with a pointer to the
														  @ref sbgcGeneral_t object														*/
	#endif

	/* High-layer service variables */				// The next fields aren't available to edit!
	ui32					_CID;					/*!<  Sequence number of the serial command. Every command has unique serial number
														  for program session. It starts with 1											*/
	ui32					_chainedCommandID;		/*!<  Identifier of related by SBGC32 command serial command						*/

	void					*_serialAPI_Event;		/*!<  Pointer to system event that will be executed after successful finish			*/
	void					*_pDestination;			/*!<  Pointer to handled data storage												*/
	ui16					_destinationSize;		/*!<  Destination buffer size to prevent overflow errors							*/

	serialAPI_CommandState_t
							_state;					/*!<  Current command state in the workflow											*/

	/* Low-layer service variables */
	serialAPI_CommandID_t	_commandID;				/*!<  SerialAPI identifier of the serial command									*/
	ui8						_payloadSize;			/*!<  Payload size of the serial command											*/
	ui8						*_payload;				/*!<  Serial command's payload buffer. Dynamic allocated							*/

	#if (SBGC_NON_BLOCKING_MODE)
		sbgcTicks_t			_timestamp;				/*!<  The last handle time of a serial command										*/
	#endif

}	serialAPI_Command_t;


/**	@cond
 */
struct sbgcGeneral_t;
/**	@endcond
 */


/**	@brief	Structure type of low-layer
 * 			library objects
 *
 *	@note	Part of sbgcGeneral_t structure
 */
typedef struct
{
	/* Driver objects handle */
	void					*drv;					/*!<  Main hardware driver object													*/

	/* Driver functions */
	/** Pointer to a user-defined function that returns the current time in milliseconds */
	sbgcTicks_t
			(*drvGetTime)	(void);

	/** Pointer to user-defined data buffer transfer function */
	ui8		(*drvTx)		(void*, ui8*, ui16),

	/** Pointer to a user-defined function to receive one byte of data */
			(*drvRx)		(void*, ui8 *data);

	/** Pointer to a user-defined function that returns the number of available bytes in the receive buffer */
	ui16	(*drvAvailableBytes)
							(void*);

	/** Pointer to user-defined debug-data buffer transfer function */
	void	(*drvTxDebug)	(char *data, ui16 length);

	/** Pointer to sprintf() function. Can be customized due to heavy weight */
	int		(*debugSprintf)	(char *buffer, const char *format, ...);

	/* Low-layer protocol functions */
	/** Pointer to private @ref SBGC32_TX function for internal use */
	void	(*tx)			(struct sbgcGeneral_t*),

	/** Pointer to private @ref SBGC32_RX function for internal use */
			(*rx)			(struct sbgcGeneral_t*);

}	sbgcLowLayer_t;


/** System functions called after successful serial command finish */
typedef		void					(*serialAPI_Event_t)(struct sbgcGeneral_t*);


/**	@brief	General SerialAPI structure with
 *			all service library objects
 *
 *	@note	Part of sbgcGeneral_t structure
 */
typedef struct
{
	/* API service objects */
	serialAPI_Status_t		serialAPI_Status;		/*!<  General variable of the all internal processes								*/

	#if (SBGC_USES_OS_SUPPORT)
		sbgcMutex_t			mutexSerialAPI;			/*!<  Mutex protecting internal processes											*/
		sbgcThread_t		threadHandle;			/*!<  Handle of SBGC32_HandlerThread task (thread)									*/
		sbgcBoolean_t		busyFlag;				/*!<  The SBGC32 Handler is at runtime												*/

		serialAPI_ThreadState_t
							threadState;			/*!<  Current handler thread state													*/
	#endif

	ui8						boardVersion;			/*!<  PCB version of this SBGC32 device												*/

	ui16					firmwareVersion,		/*!<  Firmware version of this SBGC32 device										*/
							baseFirmwareVersion;	/*!<  Base firmware version of this SBGC32 device for internal usage				*/

	ui32					boardFeatures,			/*!<  First part of SBGC32 board features. Union of the @ref sbgcBoardFeature_t and
														  @ref sbgcBoardFeatureExt_t enumerations										*/
							boardFeatures2;			/*!<  Second part of SBGC32 board features. See @ref sbgcBoardFeatureExt2_t
														  enumeration																	*/

	#if (SBGC_ADJVAR_MODULE)
		ui8					adjVarsNumber;			/*!<  The real quantity of adjustable variables at current firmware version			*/
	#endif

	ui16					txErrorsCount,			/*!<  Counter of unsuccessful attempts to send the serial commands					*/
							rxErrorsCount;			/*!<  Parser error counter when receiving the serial commands						*/

	serialAPI_Command_t		*commandBuff;			/*!<  Serial commands buffer														*/
	ui8						commandNumber;			/*!<  Number of the existing serial commands in runtime								*/

	#if (SBGC_NON_BLOCKING_MODE)
		ui8					retainedCommandNumber;	/*!<  Number of the active retained serial commands									*/
	#endif

	ui32					commandTotalCount;		/*!<  Quantity of the all serial commands were open in one session					*/

	serialAPI_Command_t		*currentSerialCommand;	/*!<  Pointer to current handled serial command										*/

	#if (SBGC_NON_BLOCKING_MODE)
		sbgcBoolean_t		commandSortFlag;		/*!<  Serial commands sorting flag. sbgcTRUE if the command buffer is sorted		*/
	#endif

	#if (SBGC_USES_TOKENS)
		sbgcCommandToken_t	lastCommandToken;		/*!<  The last command token written after any SBGC32_ function						*/
	#endif

	ui8		*txCommandBuff;							/*!<  Sent command data buffer. Arbitrary length. Storage format:
														  ui8 payload[payloadSize]														*/
	ui16	txCommandBuffTail : SBGC_TX_BUFF_POW,	/*!<  Tail point of sent commands buffer											*/
			txCommandBuffHead : SBGC_TX_BUFF_POW;	/*!<  Head point of sent commands buffer											*/

	ui8		*rxCommandBuff;							/*!<  Received command data buffer. Arbitrary length. Storage format:
														  ui8 commandID || ui8 payloadSize || ui8 payload[payloadSize]					*/
	ui16	rxCommandBuffTail : SBGC_RX_BUFF_POW,	/*!<  Tail point of received commands buffer										*/
			rxCommandBuffHead : SBGC_RX_BUFF_POW,	/*!<  Head point of received commands buffer										*/
			rxCommandBuffCurP : SBGC_RX_BUFF_POW;	/*!<  Point of currently-handle received command at reading operations				*/

	/* Parser functions */
	/** Pointer to private @ref ParserSBGC32_ConvertTypeToSize function for internal use */
	ui8		(*typeToSize)	(sbgcVarType_t);

	#if (SBGC_USES_REF_INFO)
		/** Pointer to private @ref ParserSBGC32_AssignStructByParserMap function for internal use */
		ui8	(*assignByPM)	(const void*, sbgcParserMap_t);
	#endif

	/** Pointer to private @ref ParserSBGC32_ToLittleEndian function for internal use */
	void	(*toLE)			(const void*, ui8*, ui8),

	/** Pointer to private @ref ParserSBGC32_FromLittleEndian function for internal use */
			(*fromLE)		(void*, ui8*, ui8);

	/** Pointer to private @ref ParserSBGC32_GetCommandParserMap function for internal use */
	sbgcParserMap_t
			(*getCmdPM)		(serialAPI_Command_t*);

	/** Pointer to private @ref ParserSBGC32_ConvertWithPM function for internal use */
	ui8		(*convWithPM)	(void*, const void*, ui8, sbgcParserMap_t);

	/* Debug functions */
	#if (SBGC_USES_LOGS)
		/** Pointer to private @ref DebugSBGC32_WriteLog function for internal use */
		void
			(*log)			(struct sbgcGeneral_t*, serialAPI_Command_t*);
	#endif

	/* Command-build functions */
	/** Pointer to private @ref SerialAPI_WriteByte function for internal use */
	void	(*writeByte)	(struct sbgcGeneral_t*, ui8),

	/** Pointer to private @ref SerialAPI_WriteWord function for internal use */
			(*writeWord)	(struct sbgcGeneral_t*, ui16),

	/** Pointer to private @ref SerialAPI_WriteLong function for internal use */
			(*writeLong)	(struct sbgcGeneral_t*, ui32);

	/** Pointer to private @ref SerialAPI_ReadByte function for internal use */
	ui8		(*readByte)		(struct sbgcGeneral_t*);

	/** Pointer to private @ref SerialAPI_ReadWord function for internal use */
	ui16	(*readWord)		(struct sbgcGeneral_t*);

	/** Pointer to private @ref SerialAPI_ReadLong function for internal use */
	ui32	(*readLong)		(struct sbgcGeneral_t*);

	/** Pointer to private @ref SerialAPI_WriteBuff function for internal use */
	void	(*writeBuff)	(struct sbgcGeneral_t*, const void*, ui8),

	/** Pointer to private @ref SerialAPI_ReadBuff function for internal use */
			(*readBuff)		(struct sbgcGeneral_t*, void*, ui8);

	/** Pointer to private @ref SerialAPI_WriteEmptyBuff function for internal use */
	void	(*writeEmptyBuff)
							(struct sbgcGeneral_t*, ui8),

	/** Pointer to private @ref SerialAPI_SkipBytes function for internal use */
			(*skipBytes)	(struct sbgcGeneral_t*, ui8);

	/** Pointer to private @ref SerialAPI_StartWrite function for internal use */
	void	(*startWrite)	(struct sbgcGeneral_t*, serialAPI_CommandID_t SBGC_ADVANCED_PARAMS__),

	/** Pointer to private @ref SerialAPI_StartRead function for internal use */
			(*startRead)	(struct sbgcGeneral_t*, serialAPI_CommandID_t SBGC_ADVANCED_PARAMS__);

	/** Pointer to private @ref SerialAPI_FinishWrite function for internal use */
	void	(*finishWrite)	(struct sbgcGeneral_t*),

	/** Pointer to private @ref SerialAPI_FinishRead function for internal use */
			(*finishRead)	(struct sbgcGeneral_t*),

	/** Pointer to private @ref SerialAPI_AbortLastCmd function for internal use */
			(*abortLast)	(struct sbgcGeneral_t*),

	/** Pointer to private @ref SerialAPI_AddConfirmationCommand function for internal use */
			(*addConfirm)	(struct sbgcGeneral_t*, sbgcConfirm_t*, serialAPI_CommandID_t SBGC_ADVANCED_PARAMS__),

	/** Pointer to private @ref SerialAPI_AssignSystemEvent function for internal use */
			(*assignEvent)	(struct sbgcGeneral_t*, serialAPI_Event_t, void*, ui16),

	/** Pointer to private @ref SerialAPI_DefinePayloadSize function for internal use */
			(*definePayload)
							(struct sbgcGeneral_t*, ui8),

	/** Pointer to private @ref SerialAPI_LinkCommands function for internal use */
			(*link)			(struct sbgcGeneral_t*);

	/** Pointer to private @ref SerialAPI_Exit function for internal use */
	sbgcCommandStatus_t
			(*exit)			(struct sbgcGeneral_t*);

	/* High-layer service functions */
	/** Pointer to private @ref SerialAPI_SaveReceivedCommand function for internal use */
	void	(*saveCmd)		(struct sbgcGeneral_t*, serialAPI_CommandID_t, ui8, ui8 const*);

	/** Pointer to private @ref SerialAPI_FindCommandByCID function for internal use */
	serialAPI_Command_t*
			(*findCmd)		(struct sbgcGeneral_t*, ui32);

	#if (SBGC_USES_BLOCKING_MODE || SBGC_SEND_IMMEDIATELY)
		/** Pointer to private @ref SerialAPI_ProcessCommand function for internal use */
		sbgcBoolean_t
			(*process)		(struct sbgcGeneral_t*, ui8);
	#endif

}	serialAPI_General_t;


/**	@brief	General SBGC32 configurations structure.
 *			Create such an object to work with
 *			all layers of the library
 */
typedef struct sbgcGeneral_t
{
	sbgcLowLayer_t			*_ll;					/*!<  Pointer to low-layer library driver object that contains driver
														  configurations (optional), driver functions and glue functions
														  with the driver that also serve to form the serial packet						*/
	serialAPI_General_t		*_api;					/*!<  Pointer to system serial API handle object									*/

	/* Read-only variables */
	serialAPI_CommandStatus_t
					_lastSerialCommandStatus;		/*!<  The last status of the low-layer communication with SBGC32 device				*/

	sbgcCommandStatus_t
					_lastCommandStatus;				/*!<  The last status of the high-layer communication with SBGC32 device			*/

}	sbgcGeneral_t;
/**	@}
 */

/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

#endif		/* SERIAL_API_CORE_H_ */
