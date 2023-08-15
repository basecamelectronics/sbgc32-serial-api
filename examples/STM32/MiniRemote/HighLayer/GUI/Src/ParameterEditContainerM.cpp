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
#include "gwinMenuPref.h"


sContainerDraw sParameterEditContainerDraw = { "", "" };

static Boolean_t needDisplayUpdate = TRUE__;


static Boolean_t ParameterValueComparation (ParameterHandle_t *parameterHandle)
{
	switch (parameterHandle->typeValue)
	{
		case _UNSIGNED_CHAR_ :
		case _SIGNED_CHAR_ :
		{
			if (parameterHandle->tempValue != (i8)round(*(i8*)parameterHandle->operatingValue / parameterHandle->origDivider))
				return TRUE__;

			break;
		}

		case _UNSIGNED_SHORT_ :
		case _SIGNED_SHORT_ :
		{
			if (parameterHandle->tempValue != (i16)round(*(i16*)parameterHandle->operatingValue / parameterHandle->origDivider))
				return TRUE__;

			break;
		}

		case _UNSIGNED_INT_ :
		case _SIGNED_INT_ :
		{
			if (parameterHandle->tempValue != (i32)round(*(i32*)parameterHandle->operatingValue / parameterHandle->origDivider))
				return TRUE__;

			break;
		}

		case _FLOAT_ :
		{
			if (parameterHandle->tempValue != (float)(*(float*)parameterHandle->operatingValue / parameterHandle->origDivider))
				return TRUE__;

			break;
		}

		default :
			break;
	}

	return FALSE__;
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
	if (needDisplayUpdate == FALSE__)
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
				/* Attention! An <operatingValue> pointer must include 32-bit value.
				   Otherwise, third argument of memcpy can be chosen by parameter value type */
				memcpy(parameterHandle->operatingValue, &parameterHandle->tempValue, 4);
				break;

			case FUNC_EDIT_CONTROL_SPEED :
				*(ui16*)parameterHandle->operatingValue = parameterHandle->tempValue * parameterHandle->origDivider;
				break;

			case FUNC_EDIT_CONTROL_LPF :
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
	;
}


void CParameterEditContainerM::vTask (void *pvParameters)
{
	ParameterHandle_t ParameterHandle = *(ParameterHandle_t*)pvParameters;

	if (!ParameterHandle.origDivider)
		ParameterHandle.origDivider = 1.0F;

	ParameterHandle.initValue = round(ParameterHandle.initValue / ParameterHandle.origDivider);
	ParameterHandle.tempValue = ParameterHandle.initValue;
	ParameterHandle.divider = (ParameterHandle.maxValue - ParameterHandle.minValue) * ParameterHandle.sensitivity;

	MiniRemote.ProcessFunction(CSF_PARAMETER_CHANGE, &ParameterHandle.newControlValue);

	char	valueTempBuff [7],
			nameBuff [25];

	memcpy(nameBuff, ParameterHandle.name, strlen(ParameterHandle.name));
	gwinSetText(ghLabelName, ParameterHandle.name, FALSE);

	snprintf_((char*)valueTempBuff, sizeof(valueTempBuff), "%i", ParameterHandle.tempValue);
	gwinSetText(ghLabelValue, (const char*)valueTempBuff, FALSE);

	gwinProgressbarSetPosition(ghValueProgressbar, ParameterHandle.tempValue);
	gwinProgressbarSetRange(ghValueProgressbar, ParameterHandle.minValue, ParameterHandle.maxValue);

	needDisplayUpdate = TRUE__;

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
			osFree(ParameterHandle.location);
			__DelayMs(10);
			CStateManager::SetState({ PREVIOUS_STATE, 0 });
			while (1);
		}

		/* Control handle */
		ParameterProcessOperating(&ParameterHandle, enterButton);

		/* Display processing */
		if (needDisplayUpdate)
		{
			if ((ParameterHandle.type == FUNC_EDIT_SYSTEM_EE_TIMER) &&  ParameterHandle.tempValue == ENERGY_ECONOMIC_TIMER_MAX)
			{
				gwinProgressbarSetPosition(ghValueProgressbar, ParameterHandle.tempValue);
				gwinSetText(ghLabelValue, "Inf.", FALSE);

				if (ParameterHandle.initValue != ParameterHandle.tempValue)
				{
					if ((ParameterHandle.initValue != 0xFFFF) && (ParameterHandle.tempValue != ENERGY_ECONOMIC_TIMER_MAX))
						gwinSetText(ghLabelTitle, "Parameter Edit*", FALSE);
				}

				else
					gwinSetText(ghLabelTitle, "Parameter Edit", FALSE);
			}

			else
			{
				gwinProgressbarSetPosition(ghValueProgressbar, ParameterHandle.tempValue);
				snprintf_((char*)valueTempBuff, sizeof(valueTempBuff), "%i", ParameterHandle.tempValue);
				gwinSetText(ghLabelValue, (const char*)valueTempBuff, FALSE);

				if (ParameterHandle.initValue != ParameterHandle.tempValue)
					gwinSetText(ghLabelTitle, "Parameter Edit*", FALSE);

				else
					gwinSetText(ghLabelTitle, "Parameter Edit", FALSE);
			}

			needDisplayUpdate = FALSE__;
		}

		/* Control handle */
		ParameterHandle.oldControlValue = ParameterHandle.newControlValue;
		MiniRemote.ProcessFunction(CSF_PARAMETER_CHANGE, &ParameterHandle.newControlValue);

		ParameterHandle.filter = FilterEncoderValue(ParameterHandle.oldControlValue, ParameterHandle.newControlValue,
													EDIT_FILTER_DIVIDER_CONSTANT) * ParameterHandle.divider;
		ParameterHandle.tempValue = constrain_((ParameterHandle.tempValue + SignedCeil(ParameterHandle.filter)),
												ParameterHandle.minValue, ParameterHandle.maxValue);


		if ((ParameterHandle.type == FUNC_EDIT_SYSTEM_BRIGHTNESS) || (ParameterHandle.type == FUNC_EDIT_SYSTEM_EE_TIMER) ||
			(ParameterHandle.type == FUNC_EDIT_SYSTEM_EE_RATIO))
			MiniRemote.UpdateLastResponseTime();

		osDelay(CONTAINER_PROCESS_DELAY);
	}
}
