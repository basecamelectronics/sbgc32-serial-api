/** ____________________________________________________________________
 *
 *	@file		gimbal.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_GIMBAL_H_
#define		_GIMBAL_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"sbgc32.h"
#include	"createWidget.h"
#include	"UART.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								  Macros & Constants
 */
#define		CTRLP_1					0
#define		CTRLP_2					1
#define		CTRLP_3					2

#define		JOY_X					0
#define		JOY_Y					1
#define		POT						2

#define		NOT_ASSIGNED			3				// ROLL : PITCH : YAW : N/A

#define		SBGC_BLOCKED_DEFENDED_ACTION(code)\
											while (SBGC32_Device.GeneralSBGC._parserCurrentStatus != TX_RX_OK);\
											code;

#define		SBGC_TEMP_DEFENDED_ACTION(code, timer)\
											ui32 watchDogTimer = osGetTickCount();\
											while ((SBGC32_Device.GetParserCurrentStatus() != TX_RX_OK) &&\
												   ((osGetTickCount() - watchDogTimer) < timer));\
											code;

#define		MENU_RC_NUM_CHANNELS	(SBGC_RC_CHANNELS_NUM + SBGC_RC_ADC_CHANNELS_NUM)

#define		GIMBAL_CONTROL_MAX_SENSITIVITY	10000


typedef enum
{
	PROCESS_READY					= 0,
	PROCESS_STARTED,
	PROCESS_FINISHED

}	ProcessStatus_t;


typedef enum
{
	AVSS_SYNCHRONIZED				= 0,
	AVSS_NOT_SYNCHRONIZED

}	AdjVarsSyncState_t;


typedef enum
{
	GIMBAL_NO_CONTROL				= 0,
	GIMBAL_ABSOLUTE_CONTROL,
	GIMBAL_INCREMENTAL_CONTROL,
	GIMBAL_RC_CONTROL

}	GimbalControlMode_t;


typedef enum
{
	AVAC_ACTIVE_ADJVARS				= 0,
	AVAC_OTHER_ADJVARS

}	AdjVarActiveClass_t;


typedef enum
{
	SBGC_NO_INIT					= 0,
	SBGC_NORMAL						= BIT_0_SET,

	SBGC_REBOOT						= BIT_1_SET,
	SBGC_MOTORS_OFF					= BIT_2_SET,
	SBGC_CONTROL					= BIT_3_SET,
	SBGC_SCRIPT_EXE					= BIT_4_SET,
	SBGC_CALIBRATE_IMU				= BIT_5_SET,	// Gyro or Acc
	SBGC_PID_AUTOTUNE				= BIT_6_SET,

	SBGC_LOST_CONNECTION			= BIT_7_SET,

}	SBGC_CurrentState_t;


static inline sbgcBoolean_t SBGC_ControlApprovedStateMask (SBGC_CurrentState_t state)
{
	return (sbgcBoolean_t)(toboolean_(state & ~(SBGC_LOST_CONNECTION | SBGC_MOTORS_OFF | SBGC_REBOOT |
									  SBGC_CALIBRATE_IMU | SBGC_PID_AUTOTUNE)));
}


static inline sbgcBoolean_t SBGC_NoConnectionStateMask (SBGC_CurrentState_t state)
{
	return (sbgcBoolean_t)(toboolean_(state & SBGC_LOST_CONNECTION));
}

#define		gimbalConnected_		(!SBGC_NoConnectionStateMask(Gimbal.GetCurrentState()))


static inline sbgcBoolean_t SBGC_RebootStateMask (SBGC_CurrentState_t state)
{
	return (sbgcBoolean_t)(toboolean_(state & SBGC_REBOOT));
}


static inline sbgcBoolean_t SBGC_CalibrationStateMask (SBGC_CurrentState_t state)
{
	return (sbgcBoolean_t)(toboolean_(state & SBGC_CALIBRATE_IMU));
}


static inline sbgcBoolean_t SBGC_ScriptExeStateMask (SBGC_CurrentState_t state)
{
	return (sbgcBoolean_t)(toboolean_(state & SBGC_SCRIPT_EXE));
}


static inline sbgcBoolean_t SBGC_ControlStateMask (SBGC_CurrentState_t state)
{
	return (sbgcBoolean_t)(toboolean_(state & SBGC_CONTROL));
}


static inline sbgcBoolean_t SBGC_NormalStateMask (SBGC_CurrentState_t state)
{
	return (sbgcBoolean_t)(toboolean_(state & SBGC_NORMAL));
}


typedef struct
{
	ui16			speed;						// 0 Min --> 50 Max. System: 0 Min --> 16383 Max
	ui8				LPF;						// 0 Min --> 15 Max
	ui8				sensitivity;				// 0 Min --> 50 Max. System: 0 Min --> 1000 Max
	ui8				exponent;					// 0 Min --> 100 Max. System: 0.2 Min --> 5 Max
	sbgcBoolean_t	invert;
	ui8				attachedAxis;				// ROLL : PITCH : YAW

	GimbalControlMode_t
					controlMode;				// ABS : INC : RC

}	ControlHandler_t;


typedef struct
{
	ui8				number;						// Itself number. CTRLP_1 : CTRLP_2 : CTRLP_3

	ControlHandler_t
					controlHandler [3];			// JOY_X : JOY_Y : POT

}	ControlProfile_t;


typedef struct __attribute__((aligned(4)))
{
	ControlProfile_t		ControlProfile [3];		// CTRLP_1 : CTRLP_2 : CTRLP_3
	ui8						activeControlProfile;	// CTRLP_1 : CTRLP_2 : CTRLP_3

	sbgcAdjVarGeneral_t		AdjVarGeneral [SBGC_ADJ_VARS_MAX_QUANTITY];

}	GimbalPresets_t;


class SBGC32_System
{
	private:

		SBGC_CurrentState_t	previousState,			// Automatically change only
							currentState;

		/* Data structures */
		sbgcGeneral_t		GeneralSBGC;

		sbgcBoardInfo_t		BoardInfo;
		sbgcBoardInfo3_t	BoardInfo3;

		sbgcProfileNames_t	ProfileNames;

		sbgcMainParams3_t	MainParams3;
		sbgcMainParamsExt_t	MainParamsExt;
		sbgcMainParamsExt2_t
							MainParamsExt2;
		sbgcMainParamsExt3_t
							MainParamsExt3;

		sbgcRealTimeData_t	RealTimeData;
		sbgcGetAngles_t		GetAngles;
		sbgcDataStreamInterval_t
							DataStreamInterval;

		sbgcRC_Inputs_t		RC_Inputs [MENU_RC_NUM_CHANNELS];
		ui8					RC_InputsActiveNum;

		sbgcIMU_ExtCalib_t	IMU_ExtCalib;
		sbgcCalibInfo_t		CalibInfo;


	public:

		/* Objects */
		GimbalPresets_t		Presets;				// Preserved parameters

		sbgcControl_t		Control;
		sbgcControlConfig_t	ControlConfig;

		/* Menu-context only variables */
		ui8					chosenProfile,			// CTRLP_1 : CTRLP_2 : CTRLP_3
							chosenHandler;			// JOY_X : JOY_Y : POT

		struct PACKED__
		{
							ui16 timestamp;

							i16 frameCamAngle [3];

		} DataStreamStruct;

		sbgcAutoPID_t		AutoPID;

		sbgcBeeperSettings_t
							BeeperSettings;

		sbgcConfirm_t		Confirm;				// Common confirmation struct

		i32					EEPROM_AdjVarValues [SBGC_ADJ_VARS_MAX_QUANTITY];


		xSemaphoreHandle	xSemaphoreDebugConsole;

		/* Statuses */
		ProcessStatus_t		processStatus;
		AdjVarsSyncState_t	adjVarsSyncState;

		/* Methods */
		void				Init (SBGC_ADVANCED_PARAMS_);
		void				ResetDriver (SBGC_DRV_UART_TYPE_DEF__ *uart, SBGC_DRV_TIMER_TYPE_DEF__ *tim);
		void				SetDefaultSettings (void);
		void				RecoverParameters (SBGC_ADVANCED_PARAMS_);

		sbgcCommandStatus_t	CheckConfirmation (serialAPI_CommandID_t commandID, SBGC_ADVANCED_PARAMS_);
		sbgcCommandStatus_t	ExpectCommand (serialAPI_CommandID_t commandID, SBGC_ADVANCED_PARAMS_);
		sbgcBoolean_t		DeleteSerialCommand (serialAPI_CommandID_t commandID);
		void				ControlGimbal (SBGC_ADVANCED_PARAMS_);
		void				ConfigGimbalControl (SBGC_ADVANCED_PARAMS_);

		ControlProfile_t	*GetChosenControlProfile (void)
							{
								return &Presets.ControlProfile[chosenProfile];
							}

		ControlHandler_t	*GetChosenControlHandler (void)
							{
								return &Presets.ControlProfile[chosenProfile].controlHandler[chosenHandler];
							}

		ControlProfile_t	*GetActiveControlProfile (void)
							{
								return &Presets.ControlProfile[Presets.activeControlProfile];
							}

		ControlHandler_t	*GetHandlerOfActiveControlProfileByAxis (ui8 axis)
							{
								for (ui8 i = 0; i < 3; i++)
									if (GetActiveControlProfile()->controlHandler[i].attachedAxis == axis)
										return &GetActiveControlProfile()->controlHandler[i];

								return NULL;
							}

		ui8					GetFreeFromHandlerAxisInActiveProfile (void)
							{
								ui8 axisBuff [] = { ROLL, PITCH, YAW, NOT_ASSIGNED };

								for (ui8 i = 0; i < SBGC_CONTROL_HANDLERS_NUM; i++)
									if (GetActiveControlProfile()->controlHandler[i].attachedAxis != NOT_ASSIGNED)
										axisBuff[GetActiveControlProfile()->controlHandler[i].attachedAxis] = NOT_ASSIGNED;

								for (ui8 i = 0; i < 4; i++)
									if (axisBuff[i] < NOT_ASSIGNED)
										return axisBuff[i];

								return NOT_ASSIGNED;  // Better than nothing
							}

		void				PlayBeeper (SBGC_ADVANCED_PARAMS_);

		void				ReadProfileNames (SBGC_ADVANCED_PARAMS_);
		void				WriteProfileName (sbgcProfile_t profileN, const char *profileName, SBGC_ADVANCED_PARAMS_);
		void				ReadProfileParams (sbgcProfile_t profileN, SBGC_ADVANCED_PARAMS_);

		sbgcCommandStatus_t	ReadRealTimeData (SBGC_ADVANCED_PARAMS_);
		void				ReadAngles (SBGC_ADVANCED_PARAMS_);
		void				RunRealTimeDataCustomStream (ui16 intervalMs, SBGC_ADVANCED_PARAMS_);
		void				ParseRealTimeDataCustomStream (SBGC_ADVANCED_PARAMS_);
		void				StopRealTimeDataCustomStream (SBGC_ADVANCED_PARAMS_);

		sbgcBoolean_t		GetRealTimeDataCustomStreamStatus (void);

		void				TurnOnAdjVar (sbgcAdjVarID_t ID);
		void				TurnOffAdjVar (sbgcAdjVarID_t ID);
		ui8					CountActiveAdjVars (void);
		ui8					FindNextAdjVar (AdjVarActiveClass_t adjVarClass, ui8 originID);
		ui8					FindPreviousAdjVar (AdjVarActiveClass_t adjVarClass, ui8 originID);

		ui8					GetAdjVarsNumber (void) { return GeneralSBGC._api->adjVarsNumber; }
		void				ReadAdjVarValues (sbgcAdjVarGeneral_t *adjVarGeneral, ui8 adjVarQuan, SBGC_ADVANCED_PARAMS_);
		void				ReadAllAdjVarValues (SBGC_ADVANCED_PARAMS_);
		void				SetAdjVarValue (sbgcAdjVarGeneral_t *adjVarGeneral, SBGC_ADVANCED_PARAMS_);
		void				SetAllAdjVarValues (sbgcAdjVarGeneral_t *adjVarGeneral, SBGC_ADVANCED_PARAMS_);
		sbgcCommandStatus_t	SaveAllAdjVarsToEEPROM (SBGC_ADVANCED_PARAMS_);
		void				ReadEEPROM_AdjVarsSafety (sbgcAdjVarGeneral_t *adjVarGeneral, SBGC_ADVANCED_PARAMS_);
		sbgcCommandStatus_t	UpdateEEPROM_AdjVars (SBGC_ADVANCED_PARAMS_);
		void				UpdatePID_EEPROM_AdjVars (sbgcMainParams3_t *mainParams3);

		void				AppoinRC_InputSource (ui8 num, ui8 source);
		void		 		ReadRC_Inputs (sbgcInitCfgFlag_t cfgFlags, ui8 srcQuan, SBGC_ADVANCED_PARAMS_);

		sbgcCommandStatus_t	RequestCalibInfo (sbgcIMU_Type_t IMU_Type, SBGC_ADVANCED_PARAMS_);
		sbgcCommandStatus_t	CalibAcc (SBGC_ADVANCED_PARAMS_);
		sbgcCommandStatus_t	CalibGyro (SBGC_ADVANCED_PARAMS_);

		void				ReadBoardInfo (ui16 cfg, SBGC_ADVANCED_PARAMS_);
		void				ExecuteMenu (sbgcMenuCommand_t cmdID, SBGC_ADVANCED_PARAMS_);
		sbgcCommandStatus_t	TuneAutoPID (SBGC_ADVANCED_PARAMS_);

		sbgcCommandStatus_t	TurnOffMotors (SBGC_ADVANCED_PARAMS_);
		sbgcCommandStatus_t	TurnOnMotors (SBGC_ADVANCED_PARAMS_);
		sbgcCommandStatus_t	ToggleMotors (SBGC_ADVANCED_PARAMS_);


		sbgcCommandStatus_t	RunScript (sbgcScriptSlotNum_t slot, SBGC_ADVANCED_PARAMS_);
		sbgcCommandStatus_t	StopScript (sbgcScriptSlotNum_t slot, SBGC_ADVANCED_PARAMS_);
		sbgcCommandStatus_t	ReadScriptDebugInfo (sbgcScriptDebugInfo_t *scriptDebugInfo, SBGC_ADVANCED_PARAMS_);

		sbgcCommandStatus_t	Reset (SBGC_ADVANCED_PARAMS_);

		void				PrintStructElementConsole (void *data, const char *str, sbgcVarType_t vType);


		/* Getters / Setters */
		void				SetCurrentState (SBGC_CurrentState_t newState);
		SBGC_CurrentState_t	GetPreviousState (void);
		SBGC_CurrentState_t	GetCurrentState (void);
		void				AddCurrentState (SBGC_CurrentState_t newState);
		void				ClearCurrentState (SBGC_CurrentState_t clearedState);

		sbgcConfirmStatus_t	GetConfirmStatus (void) { return SerialAPI_GetConfirmStatus(&Confirm); }

		sbgcCommandStatus_t	GetParserCurrentStatus (void) { return GeneralSBGC._lastCommandStatus; }
		void				SetParserCurrentStatus (sbgcCommandStatus_t newParserStatus)
							{
								GeneralSBGC._lastCommandStatus = newParserStatus;
							}

		GimbalPresets_t		*GetAddressGimbalSettings (void) { return &Presets; }

		sbgcGeneral_t		*GetAddressGeneralSBGC (void) { return &GeneralSBGC; }
		void				*GetAddressGeneralSBGC_Driver (void) { return GeneralSBGC._ll->drv; }

		sbgcBoardInfo_t		*GetAddressBoardInfo (void) { return &BoardInfo; }
		sbgcBoardInfo3_t	*GetAddressBoardInfo3 (void) { return &BoardInfo3; }

		char				*GetAddressProfileNames (ui8 profileN) { return ((char*)&ProfileNames + ((ui8)profileN * SBGC_MAX_PROF_NAME_LEN)); }

		sbgcMainParams3_t	*GetAddressProfileParams3 (void) { return &MainParams3; }
		sbgcMainParamsExt_t	*GetAddressProfileParamsExt (void) { return &MainParamsExt; }
		sbgcMainParamsExt2_t
							*GetAddressProfileParamsExt2 (void) { return &MainParamsExt2; }
		sbgcMainParamsExt3_t
							*GetAddressProfileParamsExt3 (void) { return &MainParamsExt3; }

		sbgcRealTimeData_t	*GetAddressRealTimeData (void) { return &RealTimeData; }

		sbgcRC_Inputs_t		*GetAddressRC_Inputs (void) { return RC_Inputs; }
		ui8					GetRC_InputsActiveNum (void) { return RC_InputsActiveNum; }
		void				SetRC_InputsActiveNum (ui8 newValue) { RC_InputsActiveNum = newValue; }

		sbgcCalibInfo_t		*GetAddressCalibInfo (void) { return &CalibInfo; }

		/* Simple functions */
		sbgcBoolean_t		GetCommunicationState (void) { return (GeneralSBGC._lastCommandStatus == sbgcCOMMAND_OK) ? sbgcTRUE : sbgcFALSE; }

		void				*GetStructureElement (const void* structure, sbgcParserMap_t parserMap, ui8 num)
							{
								return ParserSBGC32_GetElementAddress(structure, parserMap, num);
							}

};


extern SBGC32_System Gimbal;

/* From DebugConsoleContainerM */
extern ConsoleData_t ConsoleData;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 					  Function Prototypes and Inline
 */
void ResetControlAxis (sbgcControl_t *control);
void FillConsoleDataArr (char *data, ui16 length);


static inline ui8 ReallyAxisNumberFromSettings (ui8 attachedAxis, ui8 axis)
{
	for (ui8 i = 0; i < 3; i++)
		if (attachedAxis == axis)
			return i;

	return 0;
}


static inline void AxisNameAndModeControlFromHandler (ControlHandler_t *handler, char *pBuff)
{
	switch (handler->attachedAxis)
	{
		case ROLL :
			if (handler->controlMode == GIMBAL_ABSOLUTE_CONTROL)
				memcpy(pBuff, "R.abs", 6);

			else if (handler->controlMode == GIMBAL_INCREMENTAL_CONTROL)
				memcpy(pBuff, "R.inc", 6);

			else
				memcpy(pBuff, "R.rc", 5);

			break;

		case PITCH :
			if (handler->controlMode == GIMBAL_ABSOLUTE_CONTROL)
				memcpy(pBuff, "P.abs", 6);

			else if (handler->controlMode == GIMBAL_INCREMENTAL_CONTROL)
				memcpy(pBuff, "P.inc", 6);

			else
				memcpy(pBuff, "P.rc", 5);

			break;

		case YAW :
			if (handler->controlMode == GIMBAL_ABSOLUTE_CONTROL)
				memcpy(pBuff, "Y.abs", 6);

			else if (handler->controlMode == GIMBAL_INCREMENTAL_CONTROL)
				memcpy(pBuff, "Y.inc", 6);

			else
				memcpy(pBuff, "Y.rc", 5);

			break;

		case NOT_ASSIGNED :
			memcpy(pBuff, "N/A", 4);
			break;
	}
}


/* Note: input: 0 --> 4095; output: 0 --> 65535 */
static inline ui16 ConvertPotentiometerValueToControl (ui16 value)
{
	return value << 4;
}


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _GIMBAL_H_ */
