/** ____________________________________________________________________
 *
 *	@file		system.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_SYSTEM_H_
#define		_SYSTEM_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"gfx.h"

#include	"projectConfig.h"
#include	"mixes.h"
#include	"printf.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *											 Objects
 */
typedef enum
{
	BS_RELEASED						= 0,
	BS_PRESSED						= BIT_0_SET,
	BS_LOCKED						= BIT_1_SET,	// Until a button has BS_CONTINUOUS state
	BS_CONTINUOUS					= BIT_2_SET,
	BS_BLOCKED						= BIT_3_SET,	// Blocked from external side. Needed if BS_CONTINUOUS is handled once

	BS_INIT							= BIT_7_SET		// Reset continuous state timer and lock button

}	ButtonState_t;


typedef enum
{
	TS_CENTER						= BIT_0_SET,
	TS_UP							= BIT_1_SET,
	TS_DOWN							= BIT_2_SET,

	TS_TRIGGER_FLAG					= BIT_6_SET,	// Breaks from outside code
	TS_INIT							= BIT_7_SET		// Needed only at declaration

}	TogglerState_t;


typedef enum
{
	ND_CENTER						= 0,			// No action

	ND_UP							= BIT_0_SET,
	ND_DOWN							= BIT_1_SET,
	ND_RIGHT						= BIT_2_SET,
	ND_LEFT							= BIT_3_SET,

	ND_UP_RIGHT						= (ND_UP | ND_RIGHT),
	ND_DOWN_RIGHT					= (ND_DOWN | ND_RIGHT),
	ND_DOWN_LEFT					= (ND_DOWN | ND_LEFT),
	ND_UP_LEFT						= (ND_UP | ND_LEFT),

	ND_CONTINUOUS					= BIT_6_SET,
	ND_LOCKED						= BIT_7_SET,

	ND_COMPLEX_MASK					= (ND_CONTINUOUS | ND_LOCKED)

}	NavigationDirection_t;


typedef enum
{
	DM_NEED_TO_SHOW					= 0,			// Communication was corrupted
	DM_SHOWED

}	DisconnectionMessageState_t;


typedef enum
{
	AVS_REMOTE_PRIORITY				= 0,
	AVS_GIMBAL_PRIORITY				= 1

}	AdjVarsSync_t;


/* A really const SC number */
typedef enum
{
	SHORTCUT_GYRO_CALIB				= 0,
	SHORTCUT_ACC_CALIB				= 1,
	SHORTCUT_MOTOR_SWITCH			= 2,
	SHORTCUT_AUTO_PID				= 3,
	SHORTCUT_RESET					= 4,
	SHORTCUT_SCRIPT_1				= 5,			// Note: attached with Serial API script slot
	SHORTCUT_SCRIPT_2				= 6,
	SHORTCUT_SCRIPT_3				= 7,
	SHORTCUT_SCRIPT_4				= 8,
	SHORTCUT_SCRIPT_5				= 9,

	SHORTCUT_TOTAL_NUM				= 10,

	NO_SHORTCUT						= 255

}	ShortcutList_t;


typedef enum
{
	CW_UART							= 0,
	CW_RS422						= 1

}	CommunicationWay_t;


typedef enum
{
	/* Mutually exclusive */
	MR_GIMBAL_CONROL				= BIT_0_SET,
	MR_MENU_CONTROL					= BIT_1_SET,

	/* Simple */
	MR_ENERGY_ECONOMIC				= BIT_2_SET,

	MR_ERROR						= BIT_7_SET

}	MiniRemoteState_t;


typedef struct
{
	i32		avgBuff;
	i32		avgRes;

	ui8		_factor;

}			AverageValue_t;


typedef struct
{
	font_t			smallFont,
					mediumFont,
					largeFont;

	DisconnectionMessageState_t
					disconnectionMessage;

	sbgcBoolean_t	redrawMenuFlag;
	sbgcBoolean_t	redrawPrimitiveObjectsFlag;			// For menu items redrawing like circles, rectangles etc.

}	MiniRemoteGUI_t;


typedef struct
{
	/* Joystick calibs */
	i32		joyX_Min,
			joyX_Max,
			joyX_Zero,

			joyY_Min,
			joyY_Max,
			joyY_Zero;

	/* Potentiometer calibs */
	ui16	potMin,
			potMax,
			potZero;

}	MiniRemoteCalibs_t;


typedef struct __attribute__((aligned(4)))
{
	ui32			firmwareVersion;

	/* Communication way */
	CommunicationWay_t
					communicationWay;

	/* Mixes */
	MixChannel_t	mixChannel [MIX_CHANNELS_TOTAL_NUMBER];

	/* Brightness */
	ui16			activeBrightness,				// Percents, absolute exp
					dimmedBrightnessRatio,			// Percents
					brightnessTimer;				// Seconds

	MiniRemoteCalibs_t
					handlersCalibs;

	/* Other settings */
	AdjVarsSync_t	adjVarsSync;

	ui8				shortcutsOrderArr [SHORTCUT_TOTAL_NUM];

}	MiniRemotePresets_t;


class MiniRemoteGeneral
{
	private :

		/* System */
		ui32				lastResponseTime;

		NavigationDirection_t
							navDirection;

		/* GUI */
		MiniRemoteGUI_t		GUI;

		/* State machine */
		MiniRemoteState_t	currentState;

		/* Other */
		ui16				currentBrightness,
							tempBrightness;


	public :

		/* Presets */
		MiniRemotePresets_t	Presets;

		/* Outputs */
		ui8					outputFunctionsNumber;
		SystemFunction_t	*outputFunction;

		/* State machine */
		xSemaphoreHandle	xSemaphoreCurrentState;


		MiniRemoteGeneral(	font_t smallFont,
							font_t mediumFont,
							font_t largeFont,
							ui8 outputFunctionsNumber)
							{
								GUI.smallFont				= smallFont;
								GUI.mediumFont				= mediumFont;
								GUI.largeFont				= largeFont;

								this->outputFunctionsNumber	= outputFunctionsNumber;

								this->outputFunction		= (SystemFunction_t*)osMalloc(sizeof(SystemFunction_t) * outputFunctionsNumber);

								for (ui8 i = 0; i < outputFunctionsNumber; i++)
								{
									outputFunction[i].value	= 0;
									outputFunction[i].ID	= (SystemFunctionID_t)i;
								}
							}

		void				Init (void);
		void				SetDefaultSettings (void);

		void				SetFirmwareVersion (ui32 newVersion) { Presets.firmwareVersion = newVersion; }
		ui32				GetFirmwareVersion (void) { return Presets.firmwareVersion; }

		ui32				GetLastResponseTime (void) { return lastResponseTime; }
		void				UpdateLastResponseTime (void) { lastResponseTime = osGetTickCount(); }

		void				SetCurrentState (MiniRemoteState_t newState);
		void				ClearCurrentState (MiniRemoteState_t clearedState);
		MiniRemoteState_t	GetCurrentState (void);

		MixChannel_t		*GetAddressMixers (void) { return Presets.mixChannel; }

		MixChannel_t		*FindMixFromInput (InputID_t ID);
		void				SetMixInput (MixChannel_t *mix, InputID_t ID);

		MixChannel_t		*FindMixFromOutput (SystemFunctionID_t ID);
		void				SetMixOutput (MixChannel_t *mix, SystemFunctionID_t ID);

		ui16				GetFunctionValue (SystemFunctionID_t ID);
		void				ProcessFunction (SystemFunctionID_t ID, void *res);

		void				ProcessNavigationDirection (void);
		void				SwitchDisplayToEnergyEconomicState (void);
		void				SwitchDisplayToNormalState (void);

		void				NormalizeJoystickValues (ui16 *joyX_Value, ui16 *joyY_Value);
		void				NormalizePotentiometerValue (ui16 *potValue);

		NavigationDirection_t
							GetNavigationDirection (void) { return navDirection; }

		font_t				GetSmallFont (void) { return GUI.smallFont; }
		font_t				GetMediumFont (void) { return GUI.mediumFont; }
		font_t				GetLargeFont (void) { return GUI.largeFont; }

		void				SetTempBrightness (ui16 value) { tempBrightness = value; }
		ui16				*GetAddressBrightness (void) { return &currentBrightness; }
		ui16				GetBrightness (void) { return currentBrightness; }
		void				SetBrightness (ui16 brightness)
							{
								currentBrightness = brightness;
								gdispSetBacklight(brightness);

								Presets.activeBrightness = currentBrightness;
							}

		ui16				*GetAddressDimmedBrightnessRatio (void) { return &Presets.dimmedBrightnessRatio; }
		ui16				GetDimmedBrightnessRatio (void) { return Presets.dimmedBrightnessRatio; }
		void				SetDimmedBrightnessRatio (ui16 newRatio) { Presets.dimmedBrightnessRatio = newRatio; }

		ui16				*GetAddressBrightnessTimer (void) { return &Presets.brightnessTimer; }
		ui16				GetBrightnessTimer (void) { return Presets.brightnessTimer; }
		void				SetBrightnessTimer (ui16 newTime) { Presets.brightnessTimer = newTime; }


		void				SetDisconnectionMessageState (DisconnectionMessageState_t newState) { GUI.disconnectionMessage = newState; }

		DisconnectionMessageState_t
							GetDisconnectionMessageState (void) { return GUI.disconnectionMessage; }

		sbgcBoolean_t		GetRedrawMenuFlag (void) { return GUI.redrawMenuFlag; }
		void				SetRedrawMenuFlag (sbgcBoolean_t newState) { GUI.redrawMenuFlag = newState; }

		sbgcBoolean_t		GetRedrawPrimitiveObjectsFlag (void) { return GUI.redrawPrimitiveObjectsFlag; }
		void				SetRedrawPrimitiveObjectsFlag (sbgcBoolean_t newState) { GUI.redrawPrimitiveObjectsFlag = newState; }

};

extern MiniRemoteGeneral MiniRemote;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *					 Functions Prototypes and Inline
 */
/* Free functions prototypes */
void ProcessButton (ui16 bValue, ButtonState_t *buttonState);
void ProcessToggleSwitch (ui16 value, TogglerState_t *togglerState);
void CalculateNavigationDirection (ui16 xValue, ui16 yValue, NavigationDirection_t *navigationDirection);

/* Task functions prototypes */
void TaskInputsProcess (void *params);


static inline void AverageInit (AverageValue_t *averageValue, ui8 factor)
{
	averageValue->_factor = factor;
	averageValue->avgBuff = 0;
	averageValue->avgRes = 0;
}


static inline void AverageValue (AverageValue_t *averageValue, i32 value)
{
	averageValue->avgBuff += (i32)value - (i32)averageValue->avgRes;
	averageValue->avgRes = (i32)(averageValue->avgBuff >> averageValue->_factor);
}


static inline void FormatMiniRemoteFirmwareVersion (ui32 firmwareVer, char* pBuff)
{
	ui8 majorVer = firmwareVer / 100000;
	ui8 minorVer = (firmwareVer % 100000) / 10000;

	sprintf_(pBuff, "v.%u.%u", majorVer, minorVer);
}


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _SYSTEM_H_ */
