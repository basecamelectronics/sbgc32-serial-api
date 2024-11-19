/** ____________________________________________________________________
 *
 *	@file		system.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "system.h"


MiniRemoteGeneral MiniRemote(	gdispOpenFont("DejaVuSans16_aa"),
								gdispOpenFont("DejaVuSans20_aa"),
								gdispOpenFont("DejaVuSans24_aa"),
								SYSTEM_FUNCTIONS_TOTAL_NUMBER);


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														   Class Methods
 */
void MiniRemoteGeneral::Init (void)
{
	/* Mixes init */
	/* - - - - A space for manual mixer remapping - - - - */

	/* It must be referenceInputID or referenceOutputID */

	/*  - - - - - - - - - - - - - - - - - - - - - - - - - */

	/* System init */
	AttachMixesFunctionsByReferenceSources(outputFunction, MIX_CHANNELS_TOTAL_NUMBER, Presets.mixChannel);

	/* GUI init */
	currentBrightness = Presets.activeBrightness;
	gdispSetBacklight(currentBrightness);

	gwinSetDefaultFont(MiniRemote.GetMediumFont());

	GUI.redrawPrimitiveObjectsFlag = sbgcTRUE;

	/* State machine init */
	osSemaphoreCreate(xSemaphoreCurrentState);
	osSemaphoreGive(xSemaphoreCurrentState);

	/* OS tasks init */
	osTaskCreate(	TaskStartPeripheral,
					"StartPeripheral",
					configMINIMAL_STACK_SIZE * 2,
					NULL,
					OS_HIGH_PRIORITY,
					NULL);


	static MixChannel_t* mixChannelTemp = Presets.mixChannel;

	osTaskCreate(	[](void *params) { MixesProcess(MIX_CHANNELS_TOTAL_NUMBER, mixChannelTemp); },
					"InputProcess",
					configMINIMAL_STACK_SIZE * 3,
					NULL,
					OS_HIGH_PRIORITY,
					NULL);

	SetTempBrightness(MiniRemote.Presets.activeBrightness);
	UpdateLastResponseTime();
}


void MiniRemoteGeneral::SetDefaultSettings (void)
{
	Presets.firmwareVersion = MINI_REMOTE_FIRMWARE_VERSION;

	/* Mixers */
	ParseMixesInitReference(outputFunction, MIX_CHANNELS_TOTAL_NUMBER, Presets.mixChannel);

	/* GUI */
	Presets.activeBrightness = DEFAULT_INITIAL_BRIGHTNESS;
	Presets.dimmedBrightnessRatio = DEFAULT_ENERGY_ECONOMIC_RATIO;
	Presets.brightnessTimer = DEFAULT_ENERGY_ECONOMIC_TIMER;

	/* Handlers calibration */
	Presets.handlersCalibs.joyX_Min = IN_MIDDLE_VALUE / 2;
	Presets.handlersCalibs.joyX_Max = IN_MIDDLE_VALUE + (IN_MIDDLE_VALUE / 2);
	Presets.handlersCalibs.joyX_Zero = IN_MIDDLE_VALUE;
	Presets.handlersCalibs.joyY_Min = IN_MIDDLE_VALUE / 2;
	Presets.handlersCalibs.joyY_Max = IN_MIDDLE_VALUE + (IN_MIDDLE_VALUE / 2);
	Presets.handlersCalibs.joyY_Zero = IN_MIDDLE_VALUE;

	Presets.handlersCalibs.potMin = 0;
	Presets.handlersCalibs.potMax = ANALOG_IN_MAX_VALUE;
	Presets.handlersCalibs.potZero = ANALOG_IN_MIDDLE_VALUE;

	/* Adjustable variables synchronization */
	Presets.adjVarsSync = REMOTE_DEFAULT_AV_SYNC_PRIORITY;

	/* Shortcuts order */
	for (ui8 i = 0; i < SHORTCUT_TOTAL_NUM; i++)
		Presets.shortcutsOrderArr[i] = i;
}


void MiniRemoteGeneral::SetCurrentState (MiniRemoteState_t newState)
{
	if (osSemaphoreTake(xSemaphoreCurrentState, 0) != pdTRUE)
		osSemaphoreTake(xSemaphoreCurrentState, osMaxDelay);

	ui8 temp;

	if (newState == MR_GIMBAL_CONROL)
		temp = (currentState | newState) & ~MR_MENU_CONTROL;

	else if (newState == MR_MENU_CONTROL)
		temp = (currentState | newState) & ~MR_GIMBAL_CONROL;

	else
		temp = currentState | newState;

	currentState = (MiniRemoteState_t)temp;

	osSemaphoreGive(xSemaphoreCurrentState);
}


void MiniRemoteGeneral::ClearCurrentState (MiniRemoteState_t clearedState)
{
	if (osSemaphoreTake(xSemaphoreCurrentState, 0) != pdTRUE)
		osSemaphoreTake(xSemaphoreCurrentState, osMaxDelay);

	ui8 temp = currentState & ~clearedState;
	currentState = (MiniRemoteState_t)temp;

	osSemaphoreGive(xSemaphoreCurrentState);
}


MiniRemoteState_t MiniRemoteGeneral::GetCurrentState (void)
{
	return currentState;
}


MixChannel_t *MiniRemoteGeneral::FindMixFromInput (InputID_t ID)
{
	if (ID == PRPH_NO_INPUT)
		return NULL;

	for (ui8 i = 0; i < HW_NUM_INPUTS; i++)
		if (Presets.mixChannel[i].source->GetID() == ID)
			return &Presets.mixChannel[i];

	return NULL;
}


void MiniRemoteGeneral::SetMixInput (MixChannel_t *mix, InputID_t ID)
{
	mix->referenceInputID = ID;

	if (ID != PRPH_NO_INPUT)
		mix->source = inputClassesArray[ID];

	else
		mix->source = MIX_HAVENO_INPUT;
}


MixChannel_t *MiniRemoteGeneral::FindMixFromOutput (SystemFunctionID_t ID)
{
	if (ID == SF_NO)
		return NULL;

	for (ui8 i = 0; i < SYSTEM_FUNCTIONS_TOTAL_NUMBER; i++)
		if (Presets.mixChannel[i].target->ID == ID)
			return &Presets.mixChannel[i];

	return NULL;
}


void MiniRemoteGeneral::SetMixOutput (MixChannel_t *mix, SystemFunctionID_t ID)
{
	mix->referenceOutputID = ID;

	if (ID != SF_NO)
	{
		for (ui8 i = 0; i < outputFunctionsNumber; i++)  // Finding associate
			if (outputFunction[i].ID == ID)
				mix->target = &outputFunction[i];
	}

	else
		mix->target = MIX_HAVENO_OUTPUT;
}


ui16 MiniRemoteGeneral::GetFunctionValue (SystemFunctionID_t ID)
{
	for (ui8 i = 0; i < outputFunctionsNumber; i++)
		if (outputFunction[i].ID == ID)
			return outputFunction[i].value;

	/* Function haven't found */
	return 0;
}


void MiniRemoteGeneral::ProcessFunction (SystemFunctionID_t ID, void *res)
{
	ui16 valueTemp = GetFunctionValue(ID);

	switch (ID)
	{
		case CSF_NAVIGATION_ENTER :
		case CSF_NAVIGATION_EXIT :
		case VSF_NAVIGATION_CONTROL_TOGGLE :
		case VSF_SC_MENU_ADJ_VARS :
			ProcessButton(valueTemp, (ButtonState_t*)res);
			break;

		case VSF_CONTROL_PROFILE_TOGGLE :
			ProcessToggleSwitch(valueTemp, (TogglerState_t*)res);
			break;

		case CSF_NAVIGATION_X :  // Separated Control | Navigation
		case CSF_NAVIGATION_Y :
			*(ui16*)res = valueTemp;
			break;

		case CSF_PARAMETER_CHANGE :
			*(ui16*)res = valueTemp;
			break;

		case VSF_AXIS_CONTROL_SENS :
			*(ui16*)res = valueTemp;
			break;

		case VSF_AXIS_TRIMMING :
			*(ui16*)res = valueTemp;
			break;

		default :
			break;
	}
}


void MiniRemoteGeneral::ProcessNavigationDirection (void)
{
	CalculateNavigationDirection(GetFunctionValue(CSF_NAVIGATION_X), GetFunctionValue(CSF_NAVIGATION_Y), &navDirection);
}


void MiniRemoteGeneral::SwitchDisplayToEnergyEconomicState (void)
{
	if (currentBrightness > GUI_ECONOMIC_BRIGHTNESS)
	{
		SetCurrentState(MR_ENERGY_ECONOMIC);
		tempBrightness = currentBrightness;
		SetBrightness(currentBrightness / (100.0F / Presets.dimmedBrightnessRatio));
		Presets.activeBrightness = tempBrightness;
	}
}


void MiniRemoteGeneral::SwitchDisplayToNormalState (void)
{
	ClearCurrentState(MR_ENERGY_ECONOMIC);
	SetBrightness(tempBrightness);
}


void MiniRemoteGeneral::NormalizeJoystickValues (ui16 *joyX_Value, ui16 *joyY_Value)
{
	i32	joyX_MinTemp = Presets.handlersCalibs.joyX_Min,
		joyX_MaxTemp = Presets.handlersCalibs.joyX_Max,
		joyX_ZeroTemp = Presets.handlersCalibs.joyX_Zero,
		joyX_ValueTemp = *joyX_Value,

		joyY_MinTemp = Presets.handlersCalibs.joyY_Min,
		joyY_MaxTemp = Presets.handlersCalibs.joyY_Max,
		joyY_ZeroTemp = Presets.handlersCalibs.joyY_Zero,
		joyY_ValueTemp = *joyY_Value;


	/* X Channel */
	if (!joyX_ZeroTemp)
		/* If this input doesn't have a zero, calculate from max/min */
		joyX_ZeroTemp = ((ui32)joyX_MaxTemp + joyX_MinTemp) / 2;

	/* Derate min and max by 1% to ensure we can get all the way to 100% */
	joyX_MaxTemp -= (joyX_MaxTemp - joyX_ZeroTemp) / 100;
	joyX_MinTemp += (joyX_ZeroTemp - joyX_MinTemp) / 100;

	if (joyX_ValueTemp >= joyX_ZeroTemp)
	{
		joyX_ValueTemp = (IN_MAX_VALUE / 2) + (joyX_ValueTemp - joyX_ZeroTemp) *
						 (IN_MAX_VALUE / 2) / (joyX_MaxTemp - joyX_ZeroTemp);
	}

	else
	{
		joyX_ValueTemp = (IN_MAX_VALUE / 2) - (joyX_ZeroTemp - joyX_ValueTemp) *
						 (IN_MAX_VALUE / 2) / (joyX_ZeroTemp - joyX_MinTemp);
	}

	/* Bound output */
	joyX_ValueTemp = constrain_(joyX_ValueTemp, IN_MIN_VALUE, IN_MAX_VALUE);

	*joyX_Value = joyX_ValueTemp;


	/* Y Channel */
	if (!joyY_ZeroTemp)
		/* If this input doesn't have a zero, calculate from max/min */
		joyY_ZeroTemp = ((ui32)joyY_MaxTemp + joyY_MinTemp) / 2;

	/* Derate min and max by 1% to ensure we can get all the way to 100% */
	joyY_MaxTemp -= (joyY_MaxTemp - joyY_ZeroTemp) / 100;
	joyY_MinTemp += (joyY_ZeroTemp - joyY_MinTemp) / 100;

	if (joyY_ValueTemp >= joyY_ZeroTemp)
	{
		joyY_ValueTemp = (IN_MAX_VALUE / 2) + (joyY_ValueTemp - joyY_ZeroTemp) *
						 (IN_MAX_VALUE / 2) / (joyY_MaxTemp - joyY_ZeroTemp);
	}

	else
	{
		joyY_ValueTemp = (IN_MAX_VALUE / 2) - (joyY_ZeroTemp - joyY_ValueTemp) *
						 (IN_MAX_VALUE / 2) / (joyY_ZeroTemp - joyY_MinTemp);
	}

	/* Bound output */
	joyY_ValueTemp = constrain_(joyY_ValueTemp, IN_MIN_VALUE, IN_MAX_VALUE);

	*joyY_Value = joyY_ValueTemp;
}


void MiniRemoteGeneral::NormalizePotentiometerValue (ui16 *potValue)
{
	ui16 potValueTemp = *potValue;

	/* Borders check */
	if (potValueTemp >= Presets.handlersCalibs.potMax)
	{
		*potValue = ANALOG_IN_MAX_VALUE;
		return;
	}

	else if (potValueTemp <= Presets.handlersCalibs.potMin)
	{
		*potValue = 0;
		return;
	}

	/* Inside the tolerance */
	ui16	minTemp = Presets.handlersCalibs.potMin,
			maxTemp = Presets.handlersCalibs.potMax,
			zeroTemp = Presets.handlersCalibs.potZero;

	if (potValueTemp > Presets.handlersCalibs.potZero)
	{
		float higherCoeff = (potValueTemp - zeroTemp) / (((maxTemp - minTemp) - (zeroTemp - minTemp)) * 1.0F);
		*potValue = ANALOG_IN_MIDDLE_VALUE + (ANALOG_IN_MIDDLE_VALUE * higherCoeff);
	}

	else if (potValueTemp < Presets.handlersCalibs.potZero)
	{
		float lowerCoeff = (potValueTemp - minTemp) / ((zeroTemp - minTemp) * 1.0F);
		*potValue = ANALOG_IN_MIDDLE_VALUE * lowerCoeff;
	}

	else  // potValueTemp == Presets.joystickCalib.potZero
		*potValue = ANALOG_IN_MIDDLE_VALUE;
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														  Free Functions
 */
void ProcessButton (ui16 bValue, ButtonState_t *buttonState)
{
	static TickType_t xButtonContinuousTime;  // Note: works one for all buttons

	ButtonState_t bState;

	if (bValue >= 1U)
	{
		if (*buttonState == BS_BLOCKED || *buttonState == BS_INIT)
			return;

		else
			bState = BS_PRESSED;
	}

	else
	{
		if (*buttonState == BS_INIT)
		{
			*buttonState = BS_LOCKED;
			xButtonContinuousTime = osGetTickCount();

			return;
		}

		if (*buttonState == BS_BLOCKED)
			*buttonState = BS_RELEASED;

		bState = BS_RELEASED;
	}


	if (*buttonState == BS_CONTINUOUS)
	{
		*buttonState = BS_LOCKED;  // Note: if it is <BS_RELEASED>, the button will work through whole program
		xButtonContinuousTime = osGetTickCount();
	}

	else if (*buttonState == BS_RELEASED)
		*buttonState = bState;

	else if (((*buttonState == BS_PRESSED) || (*buttonState == BS_LOCKED)) &&
			(bState == BS_RELEASED))
		*buttonState = BS_RELEASED;

	else if ((*buttonState == BS_PRESSED) && (bState == BS_PRESSED))
	{
		*buttonState = BS_LOCKED;
		xButtonContinuousTime = osGetTickCount();
	}

	if (((osGetTickCount() - BUTTONS_CONTINUOUS_PASS_TIME) > xButtonContinuousTime) &&
		(*buttonState == BS_LOCKED))
		*buttonState = BS_CONTINUOUS;


	/* System awaking */
	if (!(*buttonState == BS_RELEASED))
		MiniRemote.UpdateLastResponseTime();
}


void ProcessToggleSwitch (ui16 value, TogglerState_t *togglerState)
{
	switch (value)
	{
		case TOGGLE_SWITCH_CENTER_VALUE :
			if ((*togglerState & ~TS_TRIGGER_FLAG) != TS_CENTER)
				*togglerState = (TogglerState_t)(TS_CENTER | TS_TRIGGER_FLAG);

			break;

		case TOGGLE_SWITCH_UP_VALUE :
			if ((*togglerState & ~TS_TRIGGER_FLAG) != TS_UP)
				*togglerState = (TogglerState_t)(TS_UP | TS_TRIGGER_FLAG);

			break;

		case TOGGLE_SWITCH_DOWN_VALUE :
			if ((*togglerState & ~TS_TRIGGER_FLAG) != TS_DOWN)
				*togglerState = (TogglerState_t)(TS_DOWN | TS_TRIGGER_FLAG);

			break;
	}
}


void CalculateNavigationDirection (ui16 xValue, ui16 yValue, NavigationDirection_t *navigationDirection)
{
	static ui16 boundMaxNavX = MiniRemote.FindMixFromOutput(CSF_NAVIGATION_X)->max -
							   ((MiniRemote.FindMixFromOutput(CSF_NAVIGATION_X)->max -
							   MiniRemote.FindMixFromOutput(CSF_NAVIGATION_X)->min) / NAVIGATION_FILTER);
	static ui16 boundMinNavX = MiniRemote.FindMixFromOutput(CSF_NAVIGATION_X)->min +
							   ((MiniRemote.FindMixFromOutput(CSF_NAVIGATION_X)->max -
							   MiniRemote.FindMixFromOutput(CSF_NAVIGATION_X)->min) / NAVIGATION_FILTER);

	static ui16 boundMaxNavY = MiniRemote.FindMixFromOutput(CSF_NAVIGATION_Y)->max -
							   ((MiniRemote.FindMixFromOutput(CSF_NAVIGATION_Y)->max -
							   MiniRemote.FindMixFromOutput(CSF_NAVIGATION_Y)->min) / NAVIGATION_FILTER);
	static ui16 boundMinNavY = MiniRemote.FindMixFromOutput(CSF_NAVIGATION_Y)->min +
							   ((MiniRemote.FindMixFromOutput(CSF_NAVIGATION_Y)->max -
							   MiniRemote.FindMixFromOutput(CSF_NAVIGATION_Y)->min) / NAVIGATION_FILTER);

	static TickType_t xNavigationContinuousTime, xNavigationContinuousStepTime;
	ui8 dirTemp;

	/* X channel */
	if (xValue > boundMaxNavX)
		dirTemp = (ui8)ND_RIGHT;

	else if (xValue < boundMinNavX)
		dirTemp = (ui8)ND_LEFT;

	else
		dirTemp = (ui8)ND_CENTER;

	/* Y channel */
	if (yValue > boundMaxNavY)
		dirTemp |= (ui8)ND_UP;

	else if (yValue < boundMinNavY)
		dirTemp |= (ui8)ND_DOWN;

	else
		dirTemp |= (ui8)ND_CENTER;


	if ((*navigationDirection & ~ND_COMPLEX_MASK) != dirTemp)  // Position has changed
	{
		*navigationDirection = (NavigationDirection_t)dirTemp;
		xNavigationContinuousTime = osGetTickCount();
		xNavigationContinuousStepTime = osGetTickCount();
	}

	else if ((*navigationDirection == dirTemp) && (dirTemp != ND_CENTER))  // Position is holding
		*navigationDirection = (NavigationDirection_t)(dirTemp | ND_LOCKED);

	/* Pass to ND_CONTINUOUS state */
	if (((osGetTickCount() - xNavigationContinuousTime) > NAVIGATION_CONTINUOUS_PASS_TIME) && (dirTemp != ND_CENTER))
	{
		if (((osGetTickCount() - xNavigationContinuousStepTime) > NAVIGATION_CONTINUOUS_STEP_TIME))
		{
			dirTemp = (*navigationDirection | (ui8)ND_CONTINUOUS) & ~(ui8)ND_LOCKED;
			*navigationDirection = (NavigationDirection_t)dirTemp;

			xNavigationContinuousStepTime = osGetTickCount();
		}

		else
			*navigationDirection = (NavigationDirection_t)(dirTemp | ND_LOCKED);
	}

	/* System awaking */
	if (!(*navigationDirection == ND_CENTER))
		MiniRemote.UpdateLastResponseTime();
}
