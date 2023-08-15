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

#define		MENU_RC_NUM_CHANNELS	(RC_NUM_CHANNELS + RC_NUM_ADC_CHANNELS)

#define		GIMBAL_CONTROL_MAX_SENSITIVITY	10000


typedef enum
{
	PROCESS_READY					= 0,
	PROCESS_STARTED,
	PROCESS_FINISHED

}	ProcessStatus_t;


typedef enum
{
	AVSS_SYNCHRONIZED						= 0,
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


static inline Boolean_t SBGC_ControlApprovedStateMask (SBGC_CurrentState_t state)
{
	return (Boolean_t)(toboolean_(state & ~(SBGC_LOST_CONNECTION | SBGC_MOTORS_OFF | SBGC_REBOOT |
											SBGC_CALIBRATE_IMU | SBGC_PID_AUTOTUNE)));
}


static inline Boolean_t SBGC_NoConnectionStateMask (SBGC_CurrentState_t state)
{
	return (Boolean_t)(toboolean_(state & SBGC_LOST_CONNECTION));
}


static inline Boolean_t SBGC_RebootStateMask (SBGC_CurrentState_t state)
{
	return (Boolean_t)(toboolean_(state & SBGC_REBOOT));
}


static inline Boolean_t SBGC_CalibrationStateMask (SBGC_CurrentState_t state)
{
	return (Boolean_t)(toboolean_(state & SBGC_CALIBRATE_IMU));
}


static inline Boolean_t SBGC_ScriptExeStateMask (SBGC_CurrentState_t state)
{
	return (Boolean_t)(toboolean_(state & SBGC_SCRIPT_EXE));
}


static inline Boolean_t SBGC_ControlStateMask (SBGC_CurrentState_t state)
{
	return (Boolean_t)(toboolean_(state & SBGC_CONTROL));
}


static inline Boolean_t SBGC_NormalStateMask (SBGC_CurrentState_t state)
{
	return (Boolean_t)(toboolean_(state & SBGC_NORMAL));
}


typedef struct
{
	ui16				speed;						// 0 Min --> 16383 Max
	ui8					LPF;						// 0 Min --> 15 Max
	ui8					sensitivity;				// 0 Min --> 50 Max
	Boolean_t			invert;
	ui8					attachedAxis;				// ROLL : PITCH : YAW
	GimbalControlMode_t	controlMode;				// ABS : INC : RC

}	ControlHandler_t;


typedef struct
{
	ui8					number;						// Itself number. CTRLP_1 : CTRLP_2 : CTRLP_3
	ControlHandler_t	controlHandler [3];			// JOY_X : JOY_Y : POT

}	ControlProfile_t;


typedef struct
{
	AdjVarGeneral_t	AdjVarGeneral;

	bool			activeFlag;

}	AdjVarsSettings_t;


typedef struct
{
	ControlProfile_t	ControlProfile [3];			// CTRLP_1 : CTRLP_2 : CTRLP_3
	ui8					activeControlProfile;		// CTRLP_1 : CTRLP_2 : CTRLP_3

	AdjVarGeneral_t		AdjVarGeneral [ADJ_VARS_QUANTITY];

}	GimbalPresets_t;


class SBGC32_System
{
	private:

		SBGC_CurrentState_t		previousState,		// Automatically change only
								currentState;

		/* Data structures */
		GeneralSBGC_t			GeneralSBGC;

		BoardInfo_t				BoardInfo;
		BoardInfo3_t			BoardInfo3;

		ProfileNames_t			ProfileNames;

		MainParams3_t			MainParams3;
		MainParamsExt_t			MainParamsExt;
		MainParamsExt2_t		MainParamsExt2;
		MainParamsExt3_t		MainParamsExt3;

		RealTimeData_t			RealTimeData;
		GetAngles_t				GetAngles;
		DataStreamInterval_t	DataStreamInterval;

		RC_Inputs_t				RC_Inputs [MENU_RC_NUM_CHANNELS];
		ui8						RC_InputsActiveNum;

		IMU_ExtCalib_t			IMU_ExtCalib;
		CalibInfo_t				CalibInfo;


	public:

		/* Objects */
		GimbalPresets_t			Presets;			// Preserved parameters

		Control_t				Control;
		ControlConfig_t			ControlConfig;

		/* Menu-context only variables */
		ui8						chosenProfile,		// CTRLP_1 : CTRLP_2 : CTRLP_3
								chosenHandler;		// JOY_X : JOY_Y : POT

		i16						frameCamAngle [3];	// for data stream parsing

		AutoPID_t				AutoPID;

		BeeperSettings_t		BeeperSettings;

		i32						EEPROM_AdjVarsValue [ADJ_VARS_QUANTITY];


		xSemaphoreHandle		xSemaphoreDebugConsole;

		/* Statuses */
		ProcessStatus_t			processStatus;
		AdjVarsSyncState_t		adjVarsSyncState;

		/* Methods */
		TxRxStatus_t			Init (__UART_TYPE_DEF *uart, __TIMER_TYPE_DEF *tim);
		void					ResetDriver (__UART_TYPE_DEF *uart, __TIMER_TYPE_DEF *tim);
		void					SetDefaultSettings (void);
		TxRxStatus_t			RecoverParameters (void);

		TxRxStatus_t			FindCommand (SerialCommand_t *cmd, SBGC_Command_t cmdID, ui32 timeout);
		void					ResetUnexpCommandBuff (void);

		TxRxStatus_t			CheckConfirmation (SBGC_Command_t cmdID);
		void					ClearConfirmationStruct (void);

		TxRxStatus_t			ControlGimbal (void);
		TxRxStatus_t			ConfigGimbalControl (void);

		ControlProfile_t		*GetChosenControlProfile (void)
								{
									return &Presets.ControlProfile[chosenProfile];
								}

		ControlHandler_t		*GetChosenControlHandler (void)
								{
									return &Presets.ControlProfile[chosenProfile].controlHandler[chosenHandler];
								}

		ControlProfile_t		*GetActiveControlProfile (void)
								{
									return &Presets.ControlProfile[Presets.activeControlProfile];
								}

		ControlHandler_t		*GetHandlerOfActiveControlProfileByAxis (ui8 axis)
								{
									for (ui8 i = 0; i < 3; i++)
										if (GetActiveControlProfile()->controlHandler[i].attachedAxis == axis)
											return &GetActiveControlProfile()->controlHandler[i];

									return NULL;
								}

		ui8						GetFreeFromHandlerAxisInActiveProfile (void)
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

		TxRxStatus_t			PlayBeeper (void);

		TxRxStatus_t			ReadProfileNames (void);
		TxRxStatus_t			WriteProfileName (Profile_t profileN, const char *profileName);
		TxRxStatus_t			ReadProfileParams (Profile_t profileN);

		TxRxStatus_t			ReadRealTimeData (void);
		TxRxStatus_t			ReadAngles (void);
		TxRxStatus_t			RunRealTimeDataCustomStream (ui16 intervalMs);
		TxRxStatus_t			ParseRealTimeDataCustomStream (void);
		TxRxStatus_t			StopDataStream (void);

		void					TurnOnAdjVar (AdjVarID_t ID);
		void					TurnOffAdjVar (AdjVarID_t ID);
		ui8						CountActiveAdjVars (void);
		ui8						FindNextAdjVar (AdjVarActiveClass_t adjVarClass, ui8 originID);
		ui8						FindPreviousAdjVar (AdjVarActiveClass_t adjVarClass, ui8 originID);
		TxRxStatus_t			ReadAdjVarValues (AdjVarGeneral_t *adjVarGeneral, ui8 adjVarQuan);
		TxRxStatus_t			ReadAllAdjVarValues (void);
		TxRxStatus_t			SetAdjVarValue (AdjVarGeneral_t *adjVarGeneral);
		TxRxStatus_t			SetAllAdjVarValues (AdjVarGeneral_t *adjVarGeneral);
		TxRxStatus_t			SaveAllAdjVarsToEEPROM (void);
		TxRxStatus_t			ReadEEPROM_AdjVarsSafety (AdjVarGeneral_t *adjVarGeneral);
		TxRxStatus_t			UpdateEEPROM_AdjVars (void);
		void					UpdatePID_EEPROM_AdjVars (MainParams3_t *mainParams3);

		void					AppoinRC_InputSource (ui8 num, ui8 source);
		TxRxStatus_t 			ReadRC_Inputs (InitCfgFlag_t cfgFlags, ui8 srcQuan);

		TxRxStatus_t			RequestCalibInfo (IMU_Type_t IMU_Type);
		TxRxStatus_t			CalibAcc (void);
		TxRxStatus_t			CalibGyro (void);

		TxRxStatus_t			ReadBoardInfo (ui16 cfg);
		TxRxStatus_t			ExecuteMenu (MenuCommand_t cmdID);
		TxRxStatus_t			TuneAutoPID (void);

		TxRxStatus_t			TurnOffMotors (void);
		TxRxStatus_t			TurnOnMotors (void);
		TxRxStatus_t			ToggleMotors (void);


		TxRxStatus_t			RunScript (ScriptSlotNum_t slot);
		TxRxStatus_t			StopScript (ScriptSlotNum_t slot);

		TxRxStatus_t			Reset (void);

		void		 			PrintMessageConsole (char *str, ui16 length);
		void					PrintStructElementConsole (void *data, const char *str, VarType_t vType);


		/* Getters / Setters */
		void					SetCurrentState (SBGC_CurrentState_t newState);
		SBGC_CurrentState_t		GetPreviousState (void);
		SBGC_CurrentState_t		GetCurrentState (void);
		void					AddCurrentState (SBGC_CurrentState_t newState);
		void					ClearCurrentState (SBGC_CurrentState_t clearedState);

		TxRxStatus_t			GetParserCurrentStatus (void) { return GeneralSBGC._parserCurrentStatus; }
		void					SetParserCurrentStatus (TxRxStatus_t newParserStatus) { GeneralSBGC._parserCurrentStatus = newParserStatus; }
		ConfirmationStatus_t	GetConfirmationCurrentStatus (void) { return GeneralSBGC._confirmationStatus; }

		GimbalPresets_t			*GetAddressGimbalSettings (void) { return &Presets; }

		GeneralSBGC_t			*GetAddressGeneralSBGC (void) { return &GeneralSBGC; }
		void					*GetAddressGeneralSBGC_Driver (void) { return GeneralSBGC.Drv; }

		BoardInfo_t				*GetAddressBoardInfo (void) { return &BoardInfo; }
		BoardInfo3_t			*GetAddressBoardInfo3 (void) { return &BoardInfo3; }

		char					*GetAddressProfileNames (ui8 profileN) { return ((char*)&ProfileNames + ((ui8)profileN * MAX_PROFILE_NAME_LENGTH)); }

		MainParams3_t			*GetAddressProfileParams3 (void) { return &MainParams3; }
		MainParamsExt_t			*GetAddressProfileParamsExt (void) { return &MainParamsExt; }
		MainParamsExt2_t		*GetAddressProfileParamsExt2 (void) { return &MainParamsExt2; }
		MainParamsExt3_t		*GetAddressProfileParamsExt3 (void) { return &MainParamsExt3; }

		RealTimeData_t			*GetAddressRealTimeData (void) { return &RealTimeData; }

		RC_Inputs_t				*GetAddressRC_Inputs (void) { return RC_Inputs; }
		ui8						GetRC_InputsActiveNum (void) { return RC_InputsActiveNum; }
		void					SetRC_InputsActiveNum (ui8 newValue) { RC_InputsActiveNum = newValue; }

		CalibInfo_t				*GetAddressCalibInfo (void) { return &CalibInfo; }

		/* Simple functions */
		Boolean_t				GetCommunicationState (void) { return getcommstatus_(GeneralSBGC._parserCurrentStatus); }

		void					*GetStructureElement (const void* structure, ParserMap_t parserMap, ui8 num)
								{
									return GetStructureElementAddress(&GeneralSBGC, structure, parserMap, num);
								}

};


extern SBGC32_System Gimbal;

/* From DebugConsoleContainerM */
extern ConsoleData_t ConsoleData;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 					  Function Prototypes and Inline
 */
void ResetControlAxis (Control_t *control);
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


/* Note: input: 0 --> 4095 */
static inline i16 ConvertPotentiometerValueToControl (ui16 value)
{
	return BIT_14_SET - (value * 8);
}


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _GIMBAL_H_ */
