/**	____________________________________________________________________
 *
 *	SBGC32 Serial API Library v2.1
 *
 *	@file		sbgc32.h
 *
 *	@brief		Assembly header file of the Library
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
 *	@defgroup	Common Common
 *		@brief	Common library block
 *
 *	@defgroup	Core Core
 *		@brief	Core library block
 *
 *	@defgroup	Drivers Drivers
 *		@brief	Drivers support library block
 *
 *	@defgroup	Modules Modules
 *		@brief	Sources library block
 *
 *	@defgroup	OS OS
 *		@brief	OS support library block
 *
 *	@defgroup	Readme Readme
 *	____________________________________________________________________
 */
/**	____________________________________________________________________
 *
 *	@defgroup	Readme_S1 Initializing
 *	@ingroup	Readme
 *
 *	@defgroup	Readme_S2 Operating Modes
 *	@ingroup	Readme
 *
 *	@defgroup	Readme_S3 Advanced Parameters
 *	@ingroup	Readme
 *
 *	@defgroup	Readme_S4 List of Available Functions
 *	@ingroup	Readme
 *
 *	@defgroup	Readme_S5 STM32 Driver Initialization
 *	@ingroup	Readme
 *
 *	@defgroup	Readme_S6 Additional Information
 *	@ingroup	Readme
 *
 *	@defgroup	Readme_S7 Feedback
 *	@ingroup	Readme
 *	____________________________________________________________________
 */
/**	____________________________________________________________________
 *
 *	@addtogroup	Readme
 *	@{
 *
 *	## SimpleBGC32 Serial API Open Source C Library
 *
 *	<h4>For a deeper understanding of this software, it is also
 *	advisable to refer directly to the SerialAPI documentation:</h4>
 *	<i>https://www.basecamelectronics.com/serialapi/</i>
 *
 *	This note contains comprehensive information about the library,
 *	including how to use it more effectively and its specific features.
 *
 *	@}
 *
 *	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	@addtogroup	Readme_S1
 *	@{
 *
 *	### Initializing
 *
 *	Use the followed code to initialize the library:
 *
 *	@code

			// Link the library files
			#include "sbgc32.h"

			#if (SBGC_USES_CUSTOM_SPRINTF)

				// Link custom sprintf function
				void SerialAPI_LinkSprintf (sbgcGeneral_t *gSBGC)
				{
					gSBGC->_ll->debugSprintf = userSprintf;
				}

			#endif

			// Declare a general SBGC32 object
			sbgcGeneral_t SBGC32_Device;

			#if (SBGC_USES_CUSTOM_DRIVER)

				// Link user-defined driver functions
				SerialAPI_LinkDriver(&SBGC32_Device, UserTx, UserRx, UserAvailableBytes, UserTxDebug, UserGetTime);

				// Initialize the library
				SBGC32_SetupLibrary(&SBGC32_Device);

			#else

				// Initialize the library
				SBGC32_Init(&SBGC32_Device);

			#endif

 *	@endcode
 *
 *	@}
 *
 *	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	@addtogroup	Readme_S2
 *	@{
 *
 *	### Operating Modes
 *
 *	The library operates using three different algorithms. The specific
 *	mode of operation is determined by the following parameters:
 *
 *	**Blocking mode:**\n
 *	@ref SBGC_NON_BLOCKING_MODE == sbgcOFF - Such a configuration
 *	instructs the control device to operate in blocking mode. This
 *	means that each SBGC32_ request will consume all system time,
 *	freezing the execution of further program code until its time has
 *	expired. The time parameter is called @ref SBGC_DEFAULT_TIMEOUT
 *	and it specifies how much time in milliseconds is allocated to
 *	each command for executing the data sending and receiving
 *	operations.\n
 *	*Protocol function return behavior: result only after the complete
 *	transmission-reception cycle (either Tx or Rx only) is finished.*
 *
 *	**Non-blocking mode:**\n
 *	@ref SBGC_NON_BLOCKING_MODE == sbgcON, but the library don't use
 *	any OS helper driver - the classic non-blocking mode. By operating
 *	this way, all SBGC32_ functions no longer interact with the
 *	SBGC32 controller directly but simply register command packets
 *	awaiting processing. For more information, see the documentation
 *	for the next functions: @ref SBGC32_Transmit, @ref SBGC32_Receive,
 *	@ref SBGC32_TransmitAllCommands, @ref SBGC32_ReceiveAllCommands,
 *	@ref SBGC32_ProcessAllCommands. Thus, the timing for each serial
 *	command starts only when its execution begins.\n
 *	*Protocol function return behavior: command registration result.*
 *
 *	**OS-mode:**\n
 *	@ref SBGC_NON_BLOCKING_MODE == sbgcON and the library are using an
 *	OS helper driver (@ref SBGC_USE_AZURE_RTOS, @ref SBGC_USE_FREE_RTOS
 *	or @ref SBGC_USE_LINUX_OS setting is sbgcON) - non-blocking mode
 *	with OS-oriented functions implementation. The @ref SBGC32_Init
 *	function creates its own thread, initializes the library core
 *	within it and deletes it. Then it creates a new thread to run a
 *	handler function that monitors all registered commands. See
 *	@ref SBGC32_HandlerThread.
 *	A crucial parameter is the priority of this thread -
 *	@ref SBGC_THREAD_PRIOR. Set it with particular care, considering
 *	the priorities of other threads in your program. This function
 *	operates by checking all registered commands in a single pass,
 *	processing them, and then returning control to other threads.
 *	Therefore, it typically does not require a high priority.
 *	Note that, for instance, you can register a command with a long
 *	timeout, which may block lower-priority threads. However, you can
 *	dynamically adjust the priority and other parameters of the handler
 *	thread manually. You can access it using the
 *	@ref SerialAPI_GetHandlerThread function.
 *	Similarly to the non-blocking mode you can also block the execution
 *	of the thread where a SBGC32_ command is called. Just provide this
 *	function with SCParam_FREEZE parameter for this.\n
 *	*Protocol function return behavior: command registration result. If
 *	command(-s) was registered with the SCParam_FREEZE parameter, the
 *	function will complete its execution only upon successful command
 *	execution or upon timeout expiration.*
 *
 *	@}
 *
 *	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	@addtogroup	Readme_S3
 *	@{
 *
 *	### Advanced Parameters
 *
 *	The advanced parameters of the SBGC32_ functions are available in
 *	the non-blocking and OS modes:
 *
 *	* Advanced parameters:
 *
 *		- Common features (@ref SBGC_NON_BLOCKING_MODE == sbgcON):
 *
 *			+ @b parameters - The additional parameters to register and
 *			using this function. See @ref serialAPI_CommandParam_t
 *			enumeration;\n
 *			+ @b priority - Set a priority of serial command(-s) that
 *			inside the SBGC32_ function. In this order functions will
 *			be processed further See @ref serialAPI_CommandPriority_t
 *			enumeration;\n
 *			+ @b timeout - Units: milliseconds. Shows how long the
 *			serial command(-s) can remain in processing.\n
 *
 *		- Tokens (@ref SBGC_NEED_TOKENS == sbgcON):
 *
 *			+ @b commandToken - a special unit to get SBGC32_ function
 *			identifier. See documentation of the  @ref SBGC32_Transmit
 *			and @ref SBGC32_Receive functions for more.\n
 *
 *		- Callbacks (@ref SBGC_NEED_CALLBACKS == sbgcON):
 *
 *			+ @b callback - Pointer to a user-defined function to be
 *			executed upon serial command(-s) completion. Warning!
 *			Registering new serial commands in these functions
 *			will not produce any results;\n
 *			+ @b callbackArg - Any argument associated with the
 *			callback function. If it's NULL, a pointer to the
 *			sbgcGeneral_t object is passed by default.
 *
 *	Many SBGC32_ commands receive confirmation from the controller to
 *	indicate successful execution. Examples of such functions use the
 *	@ref SBGC_NO_CONFIRM placeholder. However, it's possible to check
 *	the confirmation status through the corresponding structure. See
 *	sbgcConfirm_t struct type description for more. If command
 *	confirmation is not required, fill this field with the
 *	@ref SBGC_NO_CONFIRM value.
 *
 *	@}
 *
 *	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	@addtogroup	Readme_S4
 *	@{
 *
 *	### List of Available Functions
 *
 *	The library contains a large number of different useful functions.
 *	They can be categorized by their purpose as follows:
 *
 *	* @b SBGC32_ - The main functions in this library. They register
 *	serial commands that subsequently will interact with the physical
 *	SBGC32 device;\n
 *	* @b ParserSBGC32_ - Are auxiliary functions that parse the serial
 *	command and another data;\n
 *	* @b DebugSBGC32_ - Print various debug information;\n
 *	* @b SerialAPI_ - Are auxiliary functions that perform
 *	various roles.
 *
 *	Here is a list of useful functions contained in the library:
 *
 *	* Adjustable variables functions (see @ref Adjvar module):
 *
 *		- @ref Adjvar_Values module:
 *
 *			+ @ref SerialAPI_InitAdjVar - Automatically initializes adjustable variable					\n
 *			+ @ref SerialAPI_InitAllAdjVars - Automatically initializes all adjustable variables		\n
 *			+ @ref SerialAPI_FindAdjVarByID - Finds adjustable variable by its ID						\n
 *			+ @ref SerialAPI_EditAdjVarValue - Changes the value of adjustable variable					\n
 *			+ @ref SBGC32_SetAdjVarValue - Sets a new value for the adjustable variable					\n
 *			+ @ref SBGC32_SetAdjVarValues - Sets new values for a set of adjustable variables			\n
 *			+ @ref SBGC32_GetAdjVarValue - Queries the actual value of selected variable				\n
 *			+ @ref SBGC32_GetAdjVarValues - Requires the value of adjustable variables					\n
 *			+ @ref SBGC32_SaveAdjVarToEEPROM - Saves current value of adjustable variable to EEPROM		\n
 *			+ @ref SBGC32_SaveAdjVarsToEEPROM - Saves current adjustable variables' value to EEPROM		\n
 *			+ @ref SBGC32_SaveAllActiveAdjVarsToEEPROM - Saves all not saved active variables			\n
 *
 *		- @ref Adjvar_Configs module:
 *
 *			+ @ref SBGC32_WriteAdjVarsCfg - Writes configuration of mapping of control
 *			inputs to adjustable variables																\n
 *			+ @ref SBGC32_ReadAdjVarsCfg - Request configuration of mapping of control
 *			inputs to adjustable variables																\n
 *
 *		- @ref Adjvar_State module:
 *
 *			+ @ref SBGC32_RequestAdjVarsState - Request the state of adjustable variable
 *			in the given trigger and analog slots														\n
 *
 *		- @ref Adjvar_Info module:
 *
 *			+ @ref SBGC32_RequestAdjVarsInfo - Requests the list of all available adjustable variables	\n
 *
 *	* Gimbal calibration functions (see @ref Calib_IMU module):
 *
 *		- @ref Calib_IMU module:
 *
 *			+ @ref SBGC32_CalibAcc - Calibrates accelerometer											\n
 *			+ @ref SBGC32_CalibGyro - Calibrates gyroscope												\n
 *			+ @ref SBGC32_CalibMag - Calibrates magnetometer											\n
 *			+ @ref SBGC32_CalibAccExt - Extended format of accelerometer calibration					\n
 *			+ @ref SBGC32_CalibGyroExt - Extended format of gyroscope calibration						\n
 *			+ @ref SBGC32_CalibMagExt - Extended format of magnetometer calibration						\n
 *
 *		- @ref Calib_IMU_Info module:
 *
 *			+ @ref SBGC32_RequestCalibInfo - Requests information about current IMU calibration state	\n
 *
 *		- @ref Calib_Encoders_Offset module:
 *
 *			+ @ref SBGC32_CalibEncodersOffset - Calibrates offset of encoders							\n
 *			+ @ref SBGC32_CalibEncodersFldOffset - Starts field offset calibration of encoders			\n
 *			+ @ref SBGC32_CalibEncodersFldOffsetExt - Starts field offset calibration of encoders
 *			in extended format																			\n
 *
 *		- @ref Calib_Other module:
 *
 *			+ @ref SBGC32_CalibPoles - Calibrates poles and direction									\n
 *			+ @ref SBGC32_CalibOffset - Calibrates follow offset										\n
 *			+ @ref SBGC32_CalibBat - Calibrates internal voltage sensor									\n
 *			+ @ref SBGC32_CalibOrientCorr - Starts the calibration of sensor misalignment correction	\n
 *			+ @ref SBGC32_CalibAccExtRef - Refine the accelerometer calibration of the main IMU sensor	\n
 *			+ @ref SBGC32_CalibCogging - Starts the motor non-linearities calibration					\n
 *
 *	* EEPROM data functions (see @ref EEPROM module):
 *
 *		- @ref EEPROM_I2C_Reg_Buff module:
 *
 *			+ @ref SBGC32_WriteRegBuffI2C - Writes data to any device connected to I2C line				\n
 *			+ @ref SBGC32_ReadRegBuffI2C - Requests reading from any device connected to an I2C line	\n
 *
 *		- @ref EEPROM_Data module:
 *
 *			+ @ref SBGC32_WriteEEPROM - Writes a block of data to EEPROM to a specified address			\n
 *			+ @ref SBGC32_ReadEEPROM - Requests a reading of block of data from EEPROM
 *			at the specified address and size															\n
 *
 *		- @ref EEPROM_External_Data module:
 *
 *			+ @ref SBGC32_WriteExternalData - Stores any user data to the dedicated area in the EEPROM	\n
 *			+ @ref SBGC32_ReadExternalData - Requests user data, stored in the EEPROM					\n
 *
 *		- @ref EEPROM_File module:
 *
 *			+ @ref SBGC32_WriteFile - Writes the file to the internal filesystem						\n
 *			+ @ref SBGC32_ReadFile - Reads the file from internal filesystem							\n
 *
 *		- @ref EEPROM_Clear module:
 *
 *			+ @ref SBGC32_ClearFileSystem - Deletes all files from internal filesystem					\n
 *
 *	* Gimbal control functions (see @ref Gimbal_Control module):
 *
 *		- @ref Control module:
 *
 *			+ @ref ParserSBGC32_GetControlMode - Used as a mask to extract the Control mode value from
 *			sbgcControl_t.mode																			\n
 *			+ @ref ParserSBGC32_GetControlFlag - Used as a mask to extract the Control flag value from
 *			sbgcControl_t.mode																			\n
 *			+ @ref SBGC32_Control - Controls gimbal movement											\n
 *			+ @ref SBGC32_ControlExt - Controls gimbal movement in extended format						\n
 *			+ @ref SBGC32_ControlQuat - Controls gimbal movement in quaternions							\n
 *
 *		- @ref Control_Config module:
 *
 *			+ @ref SBGC32_ControlConfig - Configure the handling of CMD_CONTROL command					\n
 *			+ @ref SBGC32_ControlQuatConfig - Configures the handling of CMD_CONTROL_QUAT command		\n
 *
 *		- @ref Virt_Channels module:
 *
 *			+ @ref SBGC32_SetAPI_VirtChControl - Sets the value of virtual channels						\n
 *			+ @ref SBGC32_SetAPI_VirtChHR_Control - Sets the value of virtual channels in
 *			high resolution																				\n
 *
 *	* IMU functions (see @ref IMU module):
 *
 *		- @ref Ext_IMU_Debug_Info module:
 *
 *			+ @ref SBGC32_RequestExtIMU_DebugInfo - Requests debug information for the
 *			external IMU sensor																			\n
 *
 *		- @ref Ext_IMU_Cmd module:
 *
 *			+ @ref SBGC32_SendCmdToExtIMU - Performs data exchange between the gimbal
 *			and an external IMU sensor																	\n
 *			+ @ref SBGC32_SendCmdToExtSens - Forwards message to the GPS_IMU sensor						\n
 *
 *		- @ref Gyro_Correction module:
 *
 *			+ @ref SBGC32_CorrectionGyro - Corrects the gyroscope sensor's zero bias manually			\n
 *
 *		- @ref AHRS_Helper module:
 *
 *			+ @ref SBGC32_CallAHRS_Helper - Send or request attitude of the IMU sensor					\n
 *			+ @ref ParserSBGC32_PackAHRS_HelperMode - Used as a function of joining AHRS helper modes	\n
 *
 *		- @ref Helper_Data module:
 *
 *			+ @ref SBGC32_ProvideHelperData - Provides helper data for the AHRS system					\n
 *			+ @ref SBGC32_ProvideHelperDataExt - Provides extended helper data for the AHRS system		\n
 *
 *	* Profiles management functions (see @ref Profiles module):
 *
 *		- @ref Profile_Common module:
 *
 *			+ @ref SBGC32_ManageProfileSet - Performs a specific action on a profile					\n
 *			+ @ref SBGC32_WriteParamsSet - Action required before and after uploading profile settings	\n
 *			+ @ref SBGC32_WriteProfileNames - Writes profile names to EEPROM							\n
 *			+ @ref SBGC32_ReadProfileNames - Request profile names stored in EEPROM						\n
 *			+ @ref SBGC32_UseDefaults - Reset to factory defaults										\n
 *
 *		- @ref Profile_Params_3 module:
 *
 *			+ @ref SBGC32_WriteParams3 - Write system configuration part 1								\n
 *			+ @ref SBGC32_ReadParams3 - Reads system configuration part 1								\n
 *			+ @ref ParserSBGC32_GetRC_Mode - Used as a mask to extract the RC mode value from
 *			sbgcAxisRC_MP3_t.RC_Mode																	\n
 *			+ @ref ParserSBGC32_GetRC_ModeControl - Used as a mask to extract the RC mode control
 *			value from sbgcAxisRC_MP3_t.RC_Mode															\n
 *			+ @ref ParserSBGC32_GetRC_MixFC_Rate - Used as a mask to extract the RC-Mix-FC rate value
 *			from sbgcMainParams3_t.RC_MixFC_Roll or sbgcMainParams3_t.RC_MixFC_Pitch					\n
 *			+ @ref ParserSBGC32_GetRC_MixFC_Target - Used as a mask to extract the RC-Mix-FC target
 *			value from sbgcMainParams3_t.RC_MixFC_Roll or sbgcMainParams3_t.RC_MixFC_Pitch				\n
 *			+ @ref ParserSBGC32_PackRC_MixFC - Used as a function of joining RC-Mix-FC rate
 *			and RC-Mix-FC target values																	\n
 *
 *		- @ref Profile_Params_Ext module:
 *
 *			+ @ref SBGC32_WriteParamsExt - Write system configuration part 2							\n
 *			+ @ref SBGC32_ReadParamsExt - Reads system configuration part 2								\n
 *			+ @ref ParserSBGC32_GetEncoderType - Used as a mask to extract the encoder type
 *			value from sbgcMainParamsExt_t.encoderType													\n
 *
 *		- @ref Profile_Params_Ext_2 module:
 *
 *			+ @ref SBGC32_WriteParamsExt2 - Write system configuration part 3							\n
 *			+ @ref SBGC32_ReadParamsExt2 - Reads system configuration part 3							\n
 *			+ @ref ParserSBGC32_GetStabAxis - Used as a mask to extract the stab axis value from
 *			sbgcMainParamsExt2_t.stabAxis																\n
 *			+ @ref ParserSBGC32_GetStabAxisSelection - Used as a mask to extract the stab axis
 *			selection value from sbgcMainParamsExt2_t.stabAxis											\n
 *			+ @ref ParserSBGC32_GetForcePositionCfgSnap - Used as a mask to extract the force
 *			position config snap value from sbgcMainParamsExt2_t.forcePositionCfg						\n
 *			+ @ref ParserSBGC32_GetForcePositionCfgFlags - Used as a mask to extract the force
 *			position config flags from sbgcMainParamsExt2_t.forcePositionCfg							\n
 *			+ @ref ParserSBGC32_GetStepSignalCfgNumber - Used as a mask to extract the step signal
 *			config number value from sbgcStepSignalN_t.stepSignalCfg									\n
 *			+ @ref ParserSBGC32_GetStepSignalCfgMode - Used as a mask to extract the step signal
 *			config mode value from sbgcStepSignalN_t.stepSignalCfg										\n
 *			+ @ref ParserSBGC32_PackStepSignalCfg - Used as a function of joining step signal
 *			config number, step signal config mode and step signal additionally flags values			\n
 *			+ @ref ParserSBGC32_GetInterruptCfg - Used as a mask to extract the interrupt config
 *			value from sbgcMainParamsExt2_t.interruptCfg												\n
 *			+ @ref ParserSBGC32_GetInterruptPinID - Used as a mask to extract the interrupt pin
 *			ID from sbgcMainParamsExt2_t.interruptCfg													\n
 *
 *		- @ref Profile_Params_Ext_3 module:
 *
 *			+ @ref SBGC32_WriteParamsExt3 - Write system configuration part 4							\n
 *			+ @ref SBGC32_ReadParamsExt3 - Reads system configuration part 4							\n
 *			+ @ref ParserSBGC32_GetExtraBtnCfg - Used as a mask to extract the extra button
 *			config value from sbgcMainParamsExt3_t.powerCtrlCfg											\n
 *			+ @ref ParserSBGC32_GetExtraBtnPinID - Used as a mask to extract the extra button
 *			pin ID from sbgcMainParamsExt3_t.powerCtrlCfg												\n
 *
 *	* Realtime data functions (see @ref Realtime module):
 *
 *		- @ref Data_Stream_Interval
 *
 *			+ @ref SBGC32_StartDataStream - Registers or updates a data stream							\n
 *			+ @ref SBGC32_StopDataStream - Stops a data stream											\n
 *			+ @ref SBGC32_ReadDataStream - Parses the requested data stream								\n
 *			+ @ref ParserSBGC32_RTDC_FlagsToStream - Fills sbgcDataStreamInterval_t.config field		\n
 *			+ @ref ParserSBGC32_AHRSH_IMU_TypeToStream - Fills sbgcDataStreamInterval_t.config field	\n
 *			+ @ref ParserSBGC32_EventID_AndTypeToStream - Fills sbgcDataStreamInterval_t.config field	\n
 *			+ @ref ParserSBGC32_CAN_DT_FlagsAndID_ToStream - Fills sbgcDataStreamInterval_t.config field\n
 *			+ @ref ParserSBGC32_EMS_ID_AndSetToStream - Fills sbgcDataStreamInterval_t.config field		\n
 *
 *		- @ref Realtime_Data_Custom
 *
 *			+ @ref SBGC32_RequestRealTimeDataCustom - Requests configurable realtime data				\n
 *
 *		- @ref Realtime_Data_3_4
 *
 *			+ @ref SBGC32_ReadRealTimeData3 - Receives real-time data									\n
 *			+ @ref SBGC32_ReadRealTimeData4 - Receives extended version of real-time data				\n
 *
 *		- @ref Get_Angles
 *
 *			+ @ref SBGC32_GetAngles - Get information about the actual gimbal control state				\n
 *			+ @ref SBGC32_GetAnglesExt - Get information about angles in different format				\n
 *
 *		- @ref RC_Inputs
 *
 *			+ @ref SBGC32_ReadRC_Inputs - Reads values for the selected RC inputs						\n
 *
 *		- @ref Debug_Var_3
 *
 *			+ @ref SBGC32_RequestDebugVarInfo3 - Requests information about debug variables				\n
 *			+ @ref SBGC32_RequestDebugVarValue3 - Requests values of debug variables					\n
 *			+ @ref ParserSBGC32_GetVarType - Used as a mask to extract the variable type from
 *			sbgcDebugVar_t.type																			\n
 *			+ @ref ParserSBGC32_GetVarFlag - Used as a mask to extract the variable's flag from
 *			sbgcDebugVar_t.type																			\n
 *
 *		- @ref IMU_Select_3
 *
 *			+ @ref SBGC32_SelectIMU_3 - Selects which IMU to configure									\n
 *
 *		- @ref Control_Quat_Status
 *
 *			+ @ref SBGC32_ControlQuatStatus - Requests quaternions realtime data						\n
 *
 *	* Service functions (see @ref Service module):
 *
 *		- @ref Board_Info
 *
 *			+ @ref SBGC32_ReadBoardInfo - Reads version and board information 							\n
 *			+ @ref SBGC32_ReadBoardInfo3 - Reads additional board information							\n
 *
 *		- @ref Auto_PID
 *
 *			+ @ref SBGC32_TuneAutoPID - Starts automatic PID calibration								\n
 *			+ @ref SBGC32_BreakAutoPID_Tuning - Interrupts PID tuning									\n
 *			+ @ref SBGC32_TuneAutoPID2 - Starts automatic PID calibration ver. 2						\n
 *			+ @ref SBGC32_ReadAutoPID_StateCmd - Parses progress of PID auto tuning data				\n
 *			+ @ref ParserSBGC32_PackAPID_AxisFlag - Used as a function of joining AutoPID2 axis
 *			flags and AutoPID2 axis notch filter flags													\n
 *
 *		- @ref Motors_State
 *
 *			+ @ref SBGC32_SetMotorsON - Switches motors ON												\n
 *			+ @ref SBGC32_SetMotorsOFF - Switches motors OFF											\n
 *			+ @ref SBGC32_SynchronizeMotors - Mechanically aligns motors working in parallel
 *			for a single axis																			\n
 *			+ @ref SBGC32_RequestMotorState - Requests real-time status and current values of
 *			parameters related to motion control														\n
 *			+ @ref SBGC32_ReadMotorState - Reads real-time status and current values of
 *			parameters related to motion control														\n
 *
 *		- @ref Boot_Mode
 *
 *			+ @ref SBGC32_SetBootMode - Enters bootloader mode to upload firmware						\n
 *			+ @ref SBGC32_SetBootModeExt - Enters bootloader mode to upload firmware in extended format	\n
 *
 *		- @ref Scripts
 *
 *			+ @ref SBGC32_RunScript - Starts or stops user-written script. Also starts script
 *			debug if needed																				\n
 *			+ @ref SBGC32_ReadScriptDebugInfo - Parses script debug info								\n
 *
 *		- @ref State_Vars
 *
 *			+ @ref SBGC32_WriteStateVars - Writes system persistent state variables,
 *			cumulative statistics and maintenance data													\n
 *			+ @ref SBGC32_ReadStateVars - Requests reading system persistent state variables,
 *			cumulative statistics and maintenance data													\n
 *
 *		- @ref Debug_Port
 *
 *			+ @ref SBGC32_SetDebugPort - Sets this port for debugging									\n
 *			+ @ref SBGC32_ReadDebugPort - Reads debug port data											\n
 *
 *		- @ref Transparent_SerialAPI
 *
 *			+ @ref SBGC32_SendTransparentCommand - Sends data to serial port on any device via CAN bus	\n
 *			+ @ref SBGC32_ReadTransparentCommand - Receives data from serial port on
 *			any device via CAN bus																		\n
 *			+ @ref ParserSBGC32_PackTC_Target - Used as a function of joining the port, device
 *			kind and flag parameters of the SerialAPI transparent command								\n
 *
 *		- @ref Service_Other
 *
 *			+ @ref SBGC32_Reset - Resets the controller													\n
 *			+ @ref SBGC32_SetTriggerPin - Triggers output pin											\n
 *			+ @ref SBGC32_ExecuteMenu - Executes menu command											\n
 *			+ @ref SBGC32_SetServoOut - Sets output PWM signal on the specified pins					\n
 *			+ @ref SBGC32_SetServoOutExt - Sets output PWM signal on the specified
 *			pins in extended format																		\n
 *			+ @ref SBGC32_PlayBeeper - Plays melody by motors or emit standard beep sound				\n
 *			+ @ref SBGC32_SignMessage - Signs the user message											\n
 *			+ @ref SBGC32_CAN_DeviceScan - Scans CAN bus devices										\n
 *			+ @ref SBGC32_RequestModuleList - Requests version information for connected CAN devices	\n
 *
 *	The library also contains utility functions that are used in
 *	conjunction with the main protocol functions
 *	or perform specialized roles:
 *
 *	* Utility functions:
 *
 *		- @ref Common
 *
 *			+ @ref SBGC32_Init - General initialization function. Launches SBGC32 thread if OS support
 *			is on. Links embedded driver functions to the low-layer, sets library variables from
 *			configurations, gets firmware and hardware versions of the board. Explore its
 *			documentation for more details																\n
 *			+ @ref SerialAPI_FatalErrorHandler (WEAK) - Will be executed upon any error occurrence		\n
 *			+ @ref SerialAPI_CommandWaitingHandler (WEAK) - Called every time while waiting
 *			for sending/receiving a command																\n
 *
 *		- @ref High_Layer
 *
 *			+ @ref SBGC32_Transmit - Transmits one serial command by its token							\n
 *			+ @ref SBGC32_Receive - Receives one serial command by its token							\n
 *			+ @ref SBGC32_TransmitAllCommands - Transmits all ready serial commands						\n
 *			+ @ref SBGC32_ReceiveAllCommands - Receives all expected serial commands					\n
 *			+ @ref SBGC32_ProcessAllCommands - Transmits and receives all prepared serial commands		\n
 *			+ @ref SBGC32_SetupLibrary - Sets custom values of library variables for communication		\n
 *			+ @ref SBGC32_CheckConfirmation - Manually expects the CMD_CONFIRM or CMD_ERROR
 *			serial commands from the controller															\n
 *			+ @ref SBGC32_SendRawCommand - Sends a serial command with manually full data				\n
 *			+ @ref SBGC32_ExpectCommand - Expect a serial command from controller						\n
 *			+ @ref SBGC32_DeleteCommand - Deletes a serial command from the main command buffer			\n
 *			+ @ref SerialAPI_LinkDriver - Links driver functions to the lower level of the library		\n
 *			+ @ref SerialAPI_LinkSprintf (WEAK) - Links custom sprintf function to
 *			the lower level of the library																\n
 *			+ @ref SerialAPI_ResetTxBuffer - Resets Tx data serial buffer								\n
 *			+ @ref SerialAPI_ResetRxBuffer - Resets Rx data serial buffer								\n
 *			+ @ref SerialAPI_LogCommandQueue - Displays command queue detailed info						\n
 *			+ @ref SerialAPI_GetStatus - Returns last SBGC32 command status								\n
 *			+ @ref SerialAPI_GetSerialStatus - Returns last SBGC32 serial command low-layer status		\n
 *			+ @ref SerialAPI_GetConfirmStatus - Returns the status of confirmation						\n
 *			+ @ref SerialAPI_GetBoardVersion - Returns the current board version						\n
 *			+ @ref SerialAPI_GetFirmwareVersion - Returns the current firmware version					\n
 *			+ @ref SerialAPI_GetBoardFeatures - Returns the board features part 1						\n
 *			+ @ref SerialAPI_GetBoardFeatures2 - Returns the board features part 2						\n
 *			+ @ref SerialAPI_GetAdjVarNumber - Returns the number of available adjustable variables		\n
 *			+ @ref SerialAPI_GetTxErrorsNumber - Returns the number of command transmission errors		\n
 *			+ @ref SerialAPI_GetRxErrorsNumber - Returns the number of command read errors				\n
 *			+ @ref SerialAPI_GetQueueCommandNumber - Returns the number of active commands in the queue	\n
 *			+ @ref SerialAPI_GetTotalCommandNumber - Returns the total number of processed commands		\n
 *			+ @ref SerialAPI_GetBytesAvailable - Gets the number of available bytes for reading			\n
 *			+ @ref SerialAPI_IsTxEmpty - Indicates whether the Tx command buffer is empty				\n
 *			+ @ref SerialAPI_IsRxEmpty - Indicates whether the Rx command buffer is empty				\n
 *
 *		- @ref Debug
 *
 *			+ @ref DebugSBGC32_PrintMessage - Displays debug information								\n
 *			+ @ref DebugSBGC32_PrintBuffer - Displays the contents of buffer							\n
 *			+ @ref DebugSBGC32_PrintStructElement - Displays any variable by its address				\n
 *			+ @ref DebugSBGC32_PrintWholeStruct - Prints the SerialAPI structures entirely				\n
 *
 *		- @ref Data_Parse
 *
 *			+ @ref ParserSBGC32_GetElementAddress - Gives address of structure element by number		\n
 *			+ @ref ParserSBGC32_ConvertSerialStatusToString - Converts the serial status to string		\n
 *			+ @ref ParserSBGC32_ConvertCommunicationStatusToString - Converts the communication
 *			status to string																			\n
 *			+ @ref ParserSBGC32_ConvertCommandID_ToString - Converts the serial command ID to string	\n
 *			+ @ref ParserSBGC32_ConvertCommandStatusToString - Converts the serial command
 *			status to string																			\n
 *			+ @ref ParserSBGC32_FormatDeviceType - Transforms SBGC32 device type to string				\n
 *			+ @ref ParserSBGC32_FormatBoardVersion - Transforms the board version variable to string	\n
 *			+ @ref ParserSBGC32_FormatFirmwareVersion - Transforms the firmware version
 *			variable to string																			\n
 *
 *	Also, use the helper macros for data operations and so on:
 *
 *	* Helper macros:
 *
 *		- @ref High_Layer
 *
 *			+ @ref sbgcSpeedToValue - Converts speed value to system speed (0.1220740379 degree/sec)	\n
 *			+ @ref sbgcValueToSpeed - Converts system speed value (0.1220740379 degree/sec) to
 *			degrees per seconds																			\n
 *			+ @ref sbgcSpeedToValueHR - Converts speed value to system speed in high resolution
 *			(0.001 degree/sec)																			\n
 *			+ @ref sbgcAngleToDegree - Converts angle value to system degree value
 *			(0.02197265625 degree)																		\n
 *			+ @ref sbgcDegreeToAngle - Converts system degree value (0.02197265625 degree) to angle		\n
 *			+ @ref sbgcRadiansToDegree - Converts radians to degree										\n
 *			+ @ref sbgcDegreeToRadians - Converts degree to radians										\n
 *			+ @ref sbgcBlockQueue - Blocks further execution of the code until the
 *			serial command queue is empty																\n
 *			+ @ref sbgcBlockCommand - Blocks further execution of the code until the
 *			serial command completes																	\n
 *
 *		- Common glue-macros whose operation depends on the driver or operating system:
 *
 *			+ @ref sbgcDelay - Delays the system for a specified number of milliseconds					\n
 *			+ @ref sbgcGetTick - Returns current system time in milliseconds							\n
 *			+ @ref sbgcMalloc - Allocates specified bytes quantity										\n
 *			+ @ref sbgcFree - Frees part of memory														\n
 *
 *	@}
 *
 *	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	@addtogroup	Readme_S5
 *	@{
 *
 *	### STM32 Driver Initialization
 *
 *	When using this library with STM32, it is necessary to link the
 *	built-in driver with the microcontroller's interrupts. Open
 *	the *stm32XXxx_it.c* file and apply the following code:
 *
 *	@code

			#include "sbgc32.h"

			extern sbgcGeneral_t SBGC32_Device;

			// if your application works without RTOS:
			void TIMx_IRQHandler (void)
			{
				sbgcTimerIRQ_Handler(&SBGC32_Device);

				HAL_TIM_IRQHandler(SBGC_REFERENCE_TIMER);  // if the HAL driver is using
			}

			// if UART is not operated by means of the DMA LL drivers
			void USARTx_IRQHandler (void)
			{
				sbgcUART_IRQ_Handler(&SBGC32_Device);

				HAL_UART_IRQHandler(SBGC_SERIAL_PORT);
			}

			// if UART works by means of DMA with the LL driver:
			void DMAx_Streamx_IRQHandler (void)
			{
				sbgcUART_DMA_TX_IRQ_Handler();
			}

			void DMAx_Streamx_IRQHandler (void)
			{
				sbgcUART_DMA_RX_IRQ_Handler();
			}

 *	@endcode
 *
 *	@}
 *
 *	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	@addtogroup	Readme_S6
 *	@{
 *
 *	### Additional Information
 *
 *	The library's algorithm is designed such that if a command consists
 *	of two parts (Tx and Rx) and the first (Tx) part, which transmits
 *	data, fails to execute for some reason, the second (Rx) part will
 *	not be registered or executed. Instead, it will return an error
 *	from the function and log the error if logging is enabled.
 *
 *	See @ref sbgcCommandStatus_t enumeration to examine all possible
 *	high-layer errors. You can get this error code from the any SBGC32_
 *	function return value and from the sbgcGeneral_t._lastCommandStatus
 *	field. Also see @ref serialAPI_CommandStatus_t enumeration to
 *	investigate all possible lower-layer errors. It's possible to
 *	obtain this data from the sbgcGeneral_t._lastSerialCommandStatus
 *	field. Use the @ref SerialAPI_GetStatus and
 *	@ref SerialAPI_GetSerialStatus functions for more convenient
 *	handling of these values.
 *
 *	* Notes and tips:
 *
 *		- @anchor Note1
 *		*- If* @ref SBGC_SEVERAL_DEVICES == sbgcON, *it's possible to
 *		use internal driver functions having manually initialized
 *		driver structure. Arduino driver is exception. You need to
 *		manage the driver functions manually in that case;*
 *
 *		- @anchor Note2
 *		*- When* @ref SBGC_OPTIMIZE_COMMANDS == sbgcON, *such commands
 *		like the CMD_EXECUTE_MENU, CMD_CONTROL (CMD_CONFIRM) anyway
 *		will be registered again and won't be optimized;*
 *
 *		- @anchor Note3
 *		*- Be careful when working with* @ref SBGC_SEND_IMMEDIATELY ==
 *		sbgcON. *The following feature may not wait for the previous
 *		command to complete and might exit with an error;*
 *
 *		- @anchor Note4
 *		*- Reducing the* @ref SBGC_MAX_COMMAND_NUM,
 *		@ref SBGC_TX_BUFFER_SIZE *and* @ref SBGC_RX_BUFFER_SIZE
 *		*parameters you also reduce the load on the stack;*
 *
 *		- @anchor Note5
 *		*- Be careful with* @ref SBGC_THREAD_STACK_SIZE *parameter.
 *		With dynamic memory allocation, this parameter loses its
 *		significance. Default value for AzureRTOS is 1024. You can
 *		also monitor the exact memory usage of this task using
 *		specific RTOS functions or debugging tools in the IDE;*
 *
 *		*- This file looks at the settings from the serialAPI_Config.h
 *		file. Rename the serialAPI_ConfigTemplate.h file like this;*\n
 *
 *		*- The default speed of the SimpleBGC32 devices
 *		is 115200 bits per second;*\n
 *
 *		*- If you are connecting a SBGC32 through UART, the RX pin is
 *		recommended to be pulled up;*\n
 *
 *		*- If you want to create your own gimbal communication driver,
 *		create it based on the necessary functions. Their types are
 *		defined in a note in the core/lowLayer.c file;*\n
 *
 *		*- If you are using PlatformIO for Arduino, you need to add the
 *		serialAPI_Config.h file to the build directory:
 *		.pio/libdeps/ArduinoXX/serialAPI;*\n
 *
 *		*- Starting to work with the gimbal using Arduino don't forget
 *		to check the **SERIAL_TX_BUFFER_SIZE** and
 *		**SERIAL_RX_BUFFER_SIZE** constants in the "HardwareSerial.h"
 *		file. Strongly recommend increasing these values to 256;*\n
 *
 *		*- When a SBGC32 connected with Linux device you need to set
 *		**choose mode** for this connection to **read, write, and
 *		executable**. Use the next command for terminal:
 *		<sudo chmod a+rwx /dev/ttyXXxx>;*\n
 *
 *		*- The communication driver for STM32 devices supports the HAL
 *		and LL libraries also supporting the integration of the
 *		STM32CubeMX code generation;*\n
 *
 *		*- Use the SBGC_DEFAULT_ARGS_, SBGC_DEFAULT_FEATURES_,
 *		SBGC_NO_CALLBACK_, SCParam_NO, SCTimeout_DEFAULT and
 *		SBGC_NO_TOKEN for non-blocking and OS (except SBGC_NO_TOKEN)
 *		modes for more convenient function usage if you don't need
 *		the advanced arguments for some commands;*\n
 *
 *		*- The most optimal strategy for determining the size of the Tx
 *		buffer* (@ref SBGC_TX_BUFFER_SIZE) *is to align it with the
 *		size of the driver's Tx buffer. For Arduino, it is 256 bytes
 *		(as mentioned earlier), for Linux, it is 4096 bytes, and,
 *		similarly a dynamic adjustable range for STM32;*\n
 *
 *		*- Set the* @ref SBGC_SYS_BIG_ENDIAN *constant to sbgcON, if
 *		your general processing system uses BIG ENDIAN memory;*\n
 *
 *		*- All examples provided in the documentation for the
 *		functions are presented for blocking mode. Add the
 *		SBGC_DEFAULT_ARGS_ substitution or fill the rest
 *		parameters manually in the non-blocking mode;*\n
 *
 *		*- The adjvar.c file contains a data block
 *		"adjVarsReferenceInfoArray" with auxiliary information about
 *		all adjustable variables at the time of the current version;*\n
 *
 *		*- In the OS mode, the command timeout is converted into its
 *		period. Now, this command will be processed once every x
 *		milliseconds regardless of the execution result;*\n
 *
 *		*- It is possible to use the* @ref sbgcMalloc *macro to
 *		allocate memory space, but be careful when using AzureRTOS
 *		software. In that case you should expand the SerialAPI's bytes
 *		pool. See* @ref SBGC_AZURE_TX_MEM_POOL_SIZE *constant;*\n
 *
 *		*- The "..." notes in structure fields documentation means that
 *		this variable has similar description like the lower object
 *		of this group.*
 *
 *	1 tab == 4 spaces. The library is written with the
 *	following alignment:
 *
 *	5	>>	13	>>	21	>>	29	>>	37	>>	45	>>	53
 *
 *	72 - notes constraint, 137 - object description constraint;
 *	150 - maximal number of the symbols in one string
 *
 *	@}
 *
 *	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	@addtogroup	Readme_S7
 *	@{
 *
 *	### Feedback
 *
 *	If you have any questions or suggestions about using this library,
 *	you can contact at:
 *
 *	support@basecamelectronics.com
 *
 *	@}
 *
 *	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                    *
 *	                https://www.basecamelectronics.com                *
 *                                                                    *
 *	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

#ifndef		SERIAL_API_SBGC32_H_
#define		SERIAL_API_SBGC32_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									  Configurations
 */
/* Specific configurations. Originate from the
   serialAPI_ConfigTemplate.h file */
#include	"serialAPI_Config.h"

/* Auxiliary code */
#include	"adjunct.h"

/* Configuration Protection ------------------------
 */
#ifndef	SBGC_ADJVAR_MODULE
	#define	SBGC_ADJVAR_MODULE		sbgcOFF
#endif

#ifndef	SBGC_CALIB_MODULE
	#define	SBGC_CALIB_MODULE		sbgcOFF
#endif

#ifndef	SBGC_EEPROM_MODULE
	#define	SBGC_EEPROM_MODULE		sbgcOFF
#endif

#ifndef	SBGC_CONTROL_MODULE
	#define	SBGC_CONTROL_MODULE		sbgcOFF
#endif

#ifndef	SBGC_IMU_MODULE
	#define	SBGC_IMU_MODULE			sbgcOFF
#endif

#ifndef	SBGC_PROFILES_MODULE
	#define	SBGC_PROFILES_MODULE	sbgcOFF
#endif

#ifndef	SBGC_REALTIME_MODULE
	#define	SBGC_REALTIME_MODULE	sbgcOFF
#endif

#ifndef	SBGC_SERVICE_MODULE
	#define	SBGC_SERVICE_MODULE		sbgcOFF
#endif

#ifndef	SBGC_SYS_BIG_ENDIAN
	#define	SBGC_SYS_BIG_ENDIAN		sbgcOFF
#endif

#ifndef SBGC_SEVERAL_DEVICES
	#define	SBGC_SEVERAL_DEVICES	sbgcOFF
#endif

#ifndef	SBGC_PROTOCOL_VERSION
	#define	SBGC_PROTOCOL_VERSION	2
#endif

#ifndef	SBGC_NON_BLOCKING_MODE
	#define	SBGC_NON_BLOCKING_MODE	sbgcOFF
#endif

#ifndef	SBGC_NEED_TOKENS
	#define	SBGC_NEED_TOKENS		sbgcOFF
#endif

#ifndef	SBGC_NEED_CALLBACKS
	#define	SBGC_NEED_CALLBACKS		sbgcOFF
#endif

#ifndef	SBGC_OPTIMIZE_COMMANDS
	#define	SBGC_OPTIMIZE_COMMANDS	sbgcOFF
#endif

#ifndef	SBGC_SEND_IMMEDIATELY
	#define	SBGC_SEND_IMMEDIATELY	sbgcOFF
#endif

#ifndef	SBGC_CHAINED_TIMEOUT
	#define	SBGC_CHAINED_TIMEOUT	sbgcOFF
#endif

#ifndef	SBGC_MAX_COMMAND_NUM
	#define	SBGC_MAX_COMMAND_NUM	2
#endif

#ifndef	SBGC_TX_BUFFER_SIZE
	#define	SBGC_TX_BUFFER_SIZE		1
#endif

#ifndef	SBGC_RX_BUFFER_SIZE
	#define	SBGC_RX_BUFFER_SIZE		1
#endif

#ifndef	SBGC_RX_CMD_OLD_PRIOR
	#define	SBGC_RX_CMD_OLD_PRIOR	sbgcOFF
#endif

#ifndef SBGC_NEED_DEBUG
	#define	SBGC_NEED_DEBUG			sbgcOFF
#endif

#ifndef SBGC_LOG_COMMAND_TIME
	#define	SBGC_LOG_COMMAND_TIME	sbgcOFF
#endif

#ifndef SBGC_LOG_COMMAND_NUMBER
	#define	SBGC_LOG_COMMAND_NUMBER	sbgcOFF
#endif

#ifndef SBGC_LOG_COMMAND_DIR
	#define	SBGC_LOG_COMMAND_DIR	sbgcOFF
#endif

#ifndef SBGC_LOG_COMMAND_NAME
	#define	SBGC_LOG_COMMAND_NAME	sbgcOFF
#endif

#ifndef SBGC_LOG_COMMAND_ID
	#define	SBGC_LOG_COMMAND_ID		sbgcOFF
#endif

#ifndef SBGC_LOG_COMMAND_STATUS
	#define	SBGC_LOG_COMMAND_STATUS	sbgcOFF
#endif

#ifndef SBGC_LOG_COMMAND_PARAM
	#define	SBGC_LOG_COMMAND_PARAM	sbgcOFF
#endif

#ifndef SBGC_LOG_COMMAND_DATA
	#define	SBGC_LOG_COMMAND_DATA	sbgcOFF
#endif

#ifndef SBGC_CUSTOM_SPRINTF
	#define	SBGC_CUSTOM_SPRINTF		sbgcOFF
#endif

#ifndef SBGC_NEED_ASSERTS
	#define	SBGC_NEED_ASSERTS		sbgcOFF
#endif

#ifndef SBGC_NEED_CONFIRM_CMD
	#define	SBGC_NEED_CONFIRM_CMD	sbgcOFF
#endif

#ifndef	SBGC_NEED_REF_INFO
	#define	SBGC_NEED_REF_INFO		sbgcOFF
#endif

#ifndef	SBGC_DEFAULT_TIMEOUT
	#define	SBGC_DEFAULT_TIMEOUT	100
#endif

#ifndef	SBGC_STARTUP_DELAY
	#define	SBGC_STARTUP_DELAY		1000
#endif

#ifndef	ROLL
	#define	ROLL					0
#endif

#ifndef	PITCH
	#define	PITCH					1
#endif

#ifndef	YAW
	#define	YAW						2
#endif

#ifndef	SBGC_USE_AZURE_RTOS
	#define	SBGC_USE_AZURE_RTOS		sbgcOFF
#endif

#ifndef	SBGC_USE_FREE_RTOS
	#define	SBGC_USE_FREE_RTOS		sbgcOFF
#endif

#ifndef	SBGC_USE_LINUX_OS
	#define	SBGC_USE_LINUX_OS		sbgcOFF
#endif

#ifndef	SBGC_THREAD_STACK_SIZE
	#define	SBGC_THREAD_STACK_SIZE	256
#endif

#ifndef	SBGC_THREAD_PRIOR
	#define	SBGC_THREAD_PRIOR		3
#endif

#ifndef	SBGC_THREAD_QUIET_PRIOR
	#define	SBGC_THREAD_QUIET_PRIOR	1
#endif

#ifndef SBGC_NEED_AUTO_PING
	#define	SBGC_NEED_AUTO_PING		sbgcOFF
#endif

#ifndef SBGC_AUTO_PING_PERIOD
	#define	SBGC_AUTO_PING_PERIOD	1000
#endif

#ifndef SBGC_LOG_AUTO_PING
	#define	SBGC_LOG_AUTO_PING		sbgcOFF
#endif

#ifndef SBGC_AUTO_PING_CALLBACK
	#define	SBGC_AUTO_PING_CALLBACK	sbgcOFF
#endif

#ifndef SBGC_USE_ARDUINO_DRIVER
	#define	SBGC_USE_ARDUINO_DRIVER	sbgcOFF
#endif

#ifndef SBGC_USE_LINUX_DRIVER
	#define	SBGC_USE_LINUX_DRIVER	sbgcOFF
#endif

#ifndef SBGC_USE_STM32_DRIVER
	#define	SBGC_USE_STM32_DRIVER	sbgcOFF
#endif

/* External flag from doxyfile */
#ifndef SBGC_USES_DOXYGEN
	#define	SBGC_USES_DOXYGEN		sbgcOFF
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *											Warnings
 */
#if (!((SBGC_PROTOCOL_VERSION == 1) || (SBGC_PROTOCOL_VERSION == 2)))
	#error "Error! The protocol version must be 1 or 2"
#endif

#if ((!defined SBGC_USES_OS_SUPPORT) && SBGC_NEED_TOKEN)
	#warning "Warning! The tokens system is useless with OS support"
#endif

#if ((SBGC_MAX_COMMAND_NUM < 1U) || (SBGC_MAX_COMMAND_NUM > 255U))
	#error "Error! The number of commands must be greater than or equal to 1 and less than or equal to 255"
#endif

#if (((SBGC_TX_BUFFER_SIZE < 1U) || (SBGC_TX_BUFFER_SIZE > 8U)) || ((SBGC_RX_BUFFER_SIZE < 1U) || (SBGC_RX_BUFFER_SIZE > 8U)))
	#error "Error! Size of Tx and Rx buffers must be greater than or equal to 1 and less than or equal to 8"
#endif

#if ((ROLL == PITCH) || (PITCH == YAW) || (YAW == ROLL) || (ROLL > 2) || (PITCH > 2) || (YAW > 2))
	#error "Error! The axes must be in the correct order"
#endif

#if (SBGC_NON_BLOCKING_MODE == sbgcOFF)
	#if (SBGC_DEFAULT_TIMEOUT < 10U)
		#warning "Warning! Too little time to wait for some large Rx commands"
	#endif
#endif

#if ((SBGC_USE_AZURE_RTOS && SBGC_USE_FREE_RTOS) ||\
	 (SBGC_USE_FREE_RTOS && SBGC_USE_LINUX_OS) ||\
	 (SBGC_USE_LINUX_OS && SBGC_USE_AZURE_RTOS))
	#error "Error! Select the one target OS"
#endif

#if ((SBGC_NON_BLOCKING_MODE == sbgcOFF) &&\
	 (SBGC_USE_AZURE_RTOS || SBGC_USE_FREE_RTOS ||SBGC_USE_LINUX_OS))
	#error "Error! This software won't work with OS in blocking mode"
#endif

#if ((SBGC_USE_ARDUINO_DRIVER && SBGC_USE_LINUX_DRIVER) ||\
	 (SBGC_USE_LINUX_DRIVER && SBGC_USE_STM32_DRIVER) ||\
	 (SBGC_USE_STM32_DRIVER && SBGC_USE_ARDUINO_DRIVER))
	#error "Error! Select the one driver supply"
#endif

#if (SBGC_USE_AZURE_RTOS && (SBGC_THREAD_PRIOR > SBGC_THREAD_QUIET_PRIOR))
	#error "Error! The lowered priority must not be less than the normal"
#endif

#if (SBGC_USE_FREE_RTOS && (SBGC_THREAD_PRIOR < SBGC_THREAD_QUIET_PRIOR))
	#error "Error! The lowered priority must not be higher than the normal"
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								  Common for Drivers
 */
#define		SBGC_RX_BUFFER_OVERFLOW_FLAG	0xFFFFU

#define		SBGC_DRV_TX_OK_FLAG				0
#define		SBGC_DRV_TX_BUFF_OVERFLOW_FLAG	BIT_0_SET

#define		SBGC_DRV_RX_BUSY_FLAG			0
#define		SBGC_DRV_RX_BUFF_EMPTY_FLAG		BIT_0_SET

#if (SBGC_USE_ARDUINO_DRIVER || SBGC_USE_LINUX_DRIVER ||\
	 SBGC_USE_STM32_DRIVER)
	#define	SBGC_USES_CUSTOM_DRIVER	sbgcOFF
#else
	#define	SBGC_USES_CUSTOM_DRIVER	sbgcON
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									Software modules
 */
/* Enable OS-glue modules ---------------------------
 */
#if (SBGC_USE_AZURE_RTOS)
	#include		"os/glueAzureRTOS/glueAzureRTOS.h"
#elif (SBGC_USE_FREE_RTOS)
	#include		"os/glueFreeRTOS/glueFreeRTOS.h"
#elif (SBGC_USE_LINUX_OS)
	#include		"os/glueLinuxOS/glueLinuxOS.h"
#endif

#ifndef SBGC_USES_OS_SUPPORT
	#define	SBGC_USES_OS_SUPPORT	sbgcOFF

	typedef ui32					sbgcTicks_t;

	#define	sbgcMalloc(size)		malloc(size)
	#define	sbgcFree(ptr)			free(ptr)
#endif

/* Kernel code -------------------------------------
 */
#include	"core/core.h"
#include	"core/parser/parser.h"
#include	"core/debug/debug.h"
#include	"core/highLayer/highLayer.h"

/* Enable used modules -----------------------------
 */
#if (SBGC_ADJVAR_MODULE)
	#include		"modules/adjvar/adjvar.h"
#endif

#if (SBGC_CALIB_MODULE)
	#include		"modules/calib/calib.h"
#endif

#if (SBGC_CONTROL_MODULE)
	#include		"modules/gimbalControl/gimbalControl.h"
#endif

#if (SBGC_EEPROM_MODULE)
	#include		"modules/eeprom/eeprom.h"
#endif

#if (SBGC_IMU_MODULE)
	#include		"modules/imu/imu.h"
#endif

#if (SBGC_PROFILES_MODULE)
	#include		"modules/profiles/profiles.h"
#endif

#if (SBGC_REALTIME_MODULE)
	#include		"modules/realtime/realtime.h"
#endif

#if (SBGC_SERVICE_MODULE)
	#include		"modules/service/service.h"
#endif

/* Enable driver modules ---------------------------
 */
#if (SBGC_USE_LINUX_DRIVER)
	#include		"drivers/driverLinux/driverLinux.h"
#endif

#if (SBGC_USE_STM32_DRIVER)
	#include		"drivers/driverSTM32/driverSTM32.h"
#endif

/**	@cond
 */
/**	@addtogroup	Common
 *	@{
 */
sbgcCommandStatus_t SBGC32_Init (sbgcGeneral_t *sbgcGeneral);
void SerialAPI_FatalErrorHandler (void);
void SerialAPI_CommandWaitingHandler (sbgcGeneral_t *gSBGC);
/**	@}
 */
/**	@endcond
 */

#if (SBGC_USES_DOXYGEN)
	/**	@addtogroup	Configurations
	 *	@{
	 */
	/** General serial connection. See configuration file and look for this for your hardware */
	#define	SBGC_SERIAL_PORT

	/** Debug serial connection. See configuration file and look for this for your hardware */
	#define	SBGC_DEBUG_SERIAL_PORT
	/**	@}
	 */
#endif


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef		__cplusplus
			}
#endif

/* Enable Arduino driver module */
#if (SBGC_USE_ARDUINO_DRIVER)
	#include		<drivers/driverArduino/driverArduino.h>
#endif


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _SBGC32_H_ */
