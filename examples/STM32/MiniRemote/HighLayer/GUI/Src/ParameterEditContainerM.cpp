/** ____________________________________________________________________
 *
 *	@file		ParameterEditContainerM.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "createWidget.h"
#include "parameters.h"


sContainerDraw sParameterEditContainerDraw = { "", "" };

static sbgcBoolean_t needDisplayUpdate = sbgcTRUE;


static sbgcBoolean_t ParameterValueComparation (ParameterHandle_t *parameterHandle)
{
	switch (parameterHandle->typeValue)
	{
		case sbgcUCHAR :
		case sbgcCHAR :
		{
			if (parameterHandle->tempValue != (i8)round(*(i8*)parameterHandle->operatingValue / parameterHandle->origDivider))
				return sbgcTRUE;

			break;
		}

		case sbgcUSHORT :
		case sbgcSHORT :
		{
			if (parameterHandle->tempValue != (i16)round(*(i16*)parameterHandle->operatingValue / parameterHandle->origDivider))
				return sbgcTRUE;

			break;
		}

		case sbgcUINT :
		case sbgcINT :
		{
			if (parameterHandle->tempValue != (i32)round(*(i32*)parameterHandle->operatingValue / parameterHandle->origDivider))
				return sbgcTRUE;

			break;
		}

		case sbgcFLOAT :
		{
			if (parameterHandle->tempValue != (float)(*(float*)parameterHandle->operatingValue / parameterHandle->origDivider))
				return sbgcTRUE;

			break;
		}

		default :
			break;
	}

	return sbgcFALSE;
}


/* Input --> Output processing */
static void ParameterProcessOperating (ParameterHandle_t *parameterHandle, ButtonState_t enterButton)
{
	/* Input handler */
	if (enterButton == BS_PRESSED)
	{
		if (parameterHandle->sensitivity == EDIT_SENS_PARAMETER_ADJUST)
			parameterHandle->sensitivity /= 1000.0F;

		else
			parameterHandle->sensitivity = EDIT_SENS_PARAMETER_ADJUST;

		parameterHandle->divider = (parameterHandle->maxValue - parameterHandle->minValue) * parameterHandle->sensitivity;
	}

	else if (enterButton == BS_CONTINUOUS)
		parameterHandle->tempValue = parameterHandle->initValue;

	/* Output handle */
	if (needDisplayUpdate == sbgcFALSE)
	/* If external event set it to true, it doesn't to updates now */
		needDisplayUpdate = ParameterValueComparation(parameterHandle);

	if (needDisplayUpdate)
	{
		MiniRemote.UpdateLastResponseTime();

		switch (parameterHandle->type)
		{
			case FUNC_EDIT_SYSTEM_BRIGHTNESS :
				MiniRemote.SetBrightness(parameterHandle->tempValue);
				break;

			case FUNC_EDIT_SYSTEM_EE_RATIO :
				MiniRemote.SetDimmedBrightnessRatio(parameterHandle->tempValue);
				break;

			case FUNC_EDIT_SYSTEM_EE_TIMER :
				if (parameterHandle->tempValue == ENERGY_ECONOMIC_TIMER_MAX)
					MiniRemote.SetBrightnessTimer(0xFFFF);

				else
					MiniRemote.SetBrightnessTimer(parameterHandle->tempValue);

				break;

			case FUNC_EDIT_PARAMETER :
				/* Attention! An <operatingValue> pointer must include 32-bit value only.
				   Otherwise, a third argument of memcpy can be chosen by parameter value type */
				memcpy(parameterHandle->operatingValue, &parameterHandle->tempValue, 4);
				break;

			case FUNC_EDIT_CONTROL_SPEED :
				*(ui16*)parameterHandle->operatingValue = parameterHandle->tempValue * parameterHandle->origDivider;
				break;

			case FUNC_EDIT_CONTROL_LPF :
			case FUNC_EDIT_CONTROL_EXP :
				*(ui8*)parameterHandle->operatingValue = parameterHandle->tempValue * parameterHandle->origDivider;
				break;

			case FUNC_EDIT_CONTROL_SENS :
				*(i16*)parameterHandle->operatingValue = parameterHandle->tempValue * parameterHandle->origDivider;
				break;

			default :
				break;
		}
	}
}


void CParameterEditContainerM::Init (void)
{
	static gdispImage *gdispImageReturn;

	static GWidgetInit wi;
	gwinWidgetClearInit(&wi);

	/* Container */
	wi.g.show = FALSE;
	wi.g.x = 0;
	wi.g.y = 0;
	wi.g.width = gdispGetWidth();
	wi.g.height = gdispGetHeight();
	wi.customDraw = ContainerDrawMono;
	wi.customParam = &sParameterEditContainerDraw;
	ghContainer = gwinContainerCreate(0, &wi, 0);
	wi.g.show = TRUE;
	wi.g.parent = ghContainer;

	/* Return image */
	Utils::imageOpenFile(gdispImageReturn, imagePathsReferenceArray[IPR_ARROW_RETURN_LEFT]);
	wi.g.x = 0;
	wi.g.y = 0;
	wi.g.height = gdispImageReturn->height;
	wi.g.width = gdispImageReturn->width;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
	wi.customDraw = gwinImageWOpenAndDrawCustom_Mono;
	wi.customParam = (void*)imagePathsReferenceArray[IPR_ARROW_RETURN_LEFT];
	ghImageReturn = gwinImageWCreate(0, &wi);
	Utils::imageCloseFile(gdispImageReturn);

	/* Label title */
	wi.g.width = DISPLAY_WIDTH - (WIDGET_IMAGE_SIZE * 2);
	wi.g.height = LARGE_FONT_HEIGHT;
	wi.g.x = WIDGET_IMAGE_SIZE;
	wi.g.y = ((EDIT_TITLE_TOTAL_HEIGHT - MEDIUM_FONT_HEIGHT) / 2) - 1;
	wi.text = "Parameter Edit";
	wi.customStyle = &CWidgetStyle::MonoImgStyleLabelDimmed;
	wi.customParam = (void*)justifyCenter;
	wi.customDraw = gwinLabelDrawJustifiedCustomMono;
	ghLabelTitle = gwinLabelCreate(0, &wi);

	/* Label value */
	wi.g.width = DISPLAY_WIDTH;
	wi.g.height = MEDIUM_FONT_HEIGHT;
	wi.g.x = 0;
	wi.g.y = (DISPLAY_HEIGHT / 2) - MEDIUM_FONT_HEIGHT + PARAM_EDIT_Y_CENTER_OFFSET;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleLabelDimmed;
	wi.customParam = (void*)justifyCenter;
	wi.customDraw = gwinLabelDrawJustifiedCustomMono;
	ghLabelValue = gwinLabelCreate(0, &wi);

	/* Label name */
	wi.g.width = DISPLAY_WIDTH;
	wi.g.height = SMALL_FONT_HEIGHT + EDIT_TOP_BOTTOM_LABELS_RAISE;
	wi.g.x = 0;
	wi.g.y = DISPLAY_HEIGHT - SMALL_FONT_HEIGHT - EDIT_TOP_BOTTOM_LABELS_RAISE;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleLabelDimmed;
	wi.customParam = (void*)justifyCenter;
	wi.customDraw = gwinLabelDrawJustifiedCustomMono;
	ghLabelName = gwinLabelCreate(0, &wi);
	gwinSetFont(ghLabelName, MiniRemote.GetSmallFont());

	/* Progressbar */
	wi.g.width = EDIT_PROGRESSBARS_WIDTH;
	wi.g.height = PROGRESSBARS_THICK;
	wi.g.x = (gdispGetWidth() - wi.g.width) / 2;
	wi.g.y = (gdispGetHeight() / 2) + EDIT_VALUE_PRBAR_CLEARANCE + PARAM_EDIT_Y_CENTER_OFFSET;
	wi.text = 0;
	wi.customDraw = gwinProgressbarDrawCustom_Mono;
	wi.customStyle = &CWidgetStyle::MonoProgressbarStyle;
	ghValueProgressbar = gwinProgressbarCreate(0, &wi);
}


void CParameterEditContainerM::OnHide (void)
{
	if (parameterHandle->type == FUNC_EDIT_SYSTEM_BRIGHTNESS)
	{
		parameterHandle->operatingValue = &MiniRemote.Presets.activeBrightness;
		MiniRemote.SetTempBrightness(MiniRemote.Presets.activeBrightness);
	}

	if (parameterHandle->membership == PMS_REMOTE)
		SettingsLoader.SaveRemoteParameter(parameterHandle->operatingValue);

	else
		SettingsLoader.SaveGimbalParameter(parameterHandle->operatingValue);
}


void CParameterEditContainerM::vTask (void *pvParameters)
{
	parameterHandle = (ParameterHandle_t*)pvParameters;

	if (!parameterHandle->origDivider)
		parameterHandle->origDivider = 1.0F;

	parameterHandle->initValue = round(parameterHandle->initValue / parameterHandle->origDivider);
	parameterHandle->tempValue = parameterHandle->initValue;
	parameterHandle->divider = (parameterHandle->maxValue - parameterHandle->minValue) * parameterHandle->sensitivity;

	MiniRemote.ProcessFunction(CSF_PARAMETER_CHANGE, &parameterHandle->newControlValue);
	parameterHandle->oldControlValue = parameterHandle->newControlValue;

	char	valueTempBuff [7],
			nameBuff [25];

	memcpy(nameBuff, parameterHandle->name, strlen(parameterHandle->name));
	gwinSetText(ghLabelName, parameterHandle->name, FALSE);

	if ((parameterHandle->type == FUNC_EDIT_SYSTEM_EE_TIMER) && (parameterHandle->tempValue >= ENERGY_ECONOMIC_TIMER_MAX))
		gwinSetText(ghLabelValue, "Inf.", FALSE);

	else
	{
		snprintf_((char*)valueTempBuff, sizeof(valueTempBuff), "%i", parameterHandle->tempValue);
		gwinSetText(ghLabelValue, (const char*)valueTempBuff, FALSE);
	}

	gwinProgressbarSetPosition(ghValueProgressbar, parameterHandle->tempValue);
	gwinProgressbarSetRange(ghValueProgressbar, parameterHandle->minValue, parameterHandle->maxValue);

	needDisplayUpdate = sbgcTRUE;

	gwinShow(ghContainer);

	NavigationDirection_t nav;
	ButtonState_t enterButton = BS_INIT;
	ButtonState_t exitButton = BS_INIT;

	TickType_t xNavigationBlockTime = osGetTickCount();
	while (osGetTickCount() < (xNavigationBlockTime + NAVIGATION_INIT_BLOCK_TIME));

	while (1)
	{
		/* Navigation handle */
		MiniRemote.ProcessNavigationDirection();
		nav =  MiniRemote.GetNavigationDirection();
		MiniRemote.ProcessFunction(CSF_NAVIGATION_ENTER, &enterButton);
		MiniRemote.ProcessFunction(CSF_NAVIGATION_EXIT, &exitButton);

		if ((nav == ND_LEFT) || (exitButton == BS_PRESSED))
		{
			gwinSetText(ghLabelTitle, "Parameter Edit", FALSE);
			osFree(parameterHandle);
			osDelay(50);  // Necessary delay
			CStateManager::SetState({ PREVIOUS_STATE, 0 });
			while (1);
		}

		/* Control handle */
		ParameterProcessOperating(parameterHandle, enterButton);

		/* Display processing */
		if (needDisplayUpdate)
		{
			if ((parameterHandle->type == FUNC_EDIT_SYSTEM_EE_TIMER) && (parameterHandle->tempValue >= ENERGY_ECONOMIC_TIMER_MAX))
			{
				gwinProgressbarSetPosition(ghValueProgressbar, parameterHandle->tempValue);
				gwinSetText(ghLabelValue, "Inf.", FALSE);

				if (parameterHandle->initValue != parameterHandle->tempValue)
				{
					if ((parameterHandle->initValue != 0xFFFF) && (parameterHandle->tempValue != ENERGY_ECONOMIC_TIMER_MAX))
						gwinSetText(ghLabelTitle, "Parameter Edit*", FALSE);
				}

				else
					gwinSetText(ghLabelTitle, "Parameter Edit", FALSE);
			}

			else
			{
				gwinProgressbarSetPosition(ghValueProgressbar, parameterHandle->tempValue);
				snprintf_((char*)valueTempBuff, sizeof(valueTempBuff), "%i", parameterHandle->tempValue);
				gwinSetText(ghLabelValue, (const char*)valueTempBuff, FALSE);

				if (parameterHandle->initValue != parameterHandle->tempValue)
					gwinSetText(ghLabelTitle, "Parameter Edit*", FALSE);

				else
					gwinSetText(ghLabelTitle, "Parameter Edit", FALSE);
			}

			needDisplayUpdate = sbgcFALSE;
		}

		/* Control handle */
		MiniRemote.ProcessFunction(CSF_PARAMETER_CHANGE, &parameterHandle->newControlValue);

		if ((abs(parameterHandle->newControlValue - parameterHandle->oldControlValue)) > AS5048_MAX_DISPERSION)
		{
			parameterHandle->filter = FilterEncoderValue(parameterHandle->oldControlValue, parameterHandle->newControlValue,
														 EDIT_FILTER_DIVIDER_CONSTANT) * parameterHandle->divider;
			parameterHandle->tempValue = constrain_((parameterHandle->tempValue + CalculateSignedCeil(parameterHandle->filter)),
													parameterHandle->minValue, parameterHandle->maxValue);

			parameterHandle->oldControlValue = parameterHandle->newControlValue;
		}


		if ((parameterHandle->type == FUNC_EDIT_SYSTEM_BRIGHTNESS) || (parameterHandle->type == FUNC_EDIT_SYSTEM_EE_TIMER) ||
			(parameterHandle->type == FUNC_EDIT_SYSTEM_EE_RATIO))
			MiniRemote.UpdateLastResponseTime();

		osDelay(CONTAINER_PROCESS_DELAY);
	}
}
