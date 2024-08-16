/** ____________________________________________________________________
 *
 *	@file		AdjVarEditContainerM.cpp
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
#include "parameters.h"


sContainerDraw sAdjVarEditContainerDraw = { "", "" };

static i32 minInitValue, minTempValue, maxInitValue, maxTempValue;

static AdjVarActiveClass_t containerPhase;
static ParameterHandle_t ParameterHandle;

static sbgcBoolean_t editLock = sbgcFALSE;

static sbgcBoolean_t needDisplayUpdate = sbgcTRUE;

extern MessageWindowDialogAnswer_t dialogAnswer;

extern ui8 activeAdjVarsCount;
extern ui8 selectedAdjVarID;


static void InitAdjVarEditContainerHandler (ui8 adjVarID)
{
	ParameterHandle.type = FUNC_EDIT_ADJVAR;
	ParameterHandle.operatingValue = &Gimbal.Presets.AdjVarGeneral[adjVarID].value;
	ParameterHandle.initValue = Gimbal.Presets.AdjVarGeneral[adjVarID].value;
	ParameterHandle.minValue = Gimbal.Presets.AdjVarGeneral[adjVarID].minValue;
	ParameterHandle.maxValue = Gimbal.Presets.AdjVarGeneral[adjVarID].maxValue;
	ParameterHandle.name = &adjVarsReferenceInfoArray[adjVarID].name[SBGC_ADJ_VAR_NAME_CUT];
	ParameterHandle.sensitivity = EDIT_SENS_PARAMETER_ADJUST;

	ParameterHandle.tempValue = ParameterHandle.initValue;
	ParameterHandle.divider = (adjVarsReferenceInfoArray[selectedAdjVarID].maxValue - adjVarsReferenceInfoArray[selectedAdjVarID].minValue) *
							   ParameterHandle.sensitivity;

	/* Locking check */
	if (ParameterHandle.initValue == ADJVAR_LOCK_VALUE)
		editLock = sbgcTRUE;

	else
		editLock = sbgcFALSE;

	needDisplayUpdate = sbgcTRUE;

	MiniRemote.ProcessFunction(CSF_PARAMETER_CHANGE, &ParameterHandle.newControlValue);
}


/* Input --> Output processing */
static void ParameterProcessOperating (ButtonState_t enterButton)
{
	/* Input handler */
	if (enterButton == BS_PRESSED)
	{
		if (ParameterHandle.sensitivity == EDIT_SENS_PARAMETER_ADJUST)
			ParameterHandle.sensitivity /= 1000.0F;

		else
			ParameterHandle.sensitivity = EDIT_SENS_PARAMETER_ADJUST;

		ParameterHandle.divider = (adjVarsReferenceInfoArray[selectedAdjVarID].maxValue - adjVarsReferenceInfoArray[selectedAdjVarID].minValue) *
								   ParameterHandle.sensitivity;
	}

	else if (enterButton == BS_CONTINUOUS)
	{
		if (Gimbal.Presets.AdjVarGeneral[selectedAdjVarID].custom.activeFlag)
		{
			/* Delete from active */
			dialogAnswer = MWDA_NO;
			exCMessageWindowContainerM.SetMessage(TEXT_LENGTH_("Delete variable?"), MW_DIALOG_STATE, MW_MEDIUM_FONT, 0);
			CStateManager::SetState({ MESSAGE_WINDOW_STATE, 0 });
			while (1);
		}

		else
		{
			/* Add to active */
			dialogAnswer = MWDA_YES;
			exCMessageWindowContainerM.SetMessage(TEXT_LENGTH_("Add variable?"), MW_DIALOG_STATE, MW_MEDIUM_FONT, 0);
			CStateManager::SetState({ MESSAGE_WINDOW_STATE, 0 });
			while (1);
		}

		CStateManager::SetState({ PREVIOUS_STATE, 0 });
		while (1);
	}

	/* Output handle */
	if ((ParameterHandle.tempValue != *(i32*)ParameterHandle.operatingValue) ||
		(minTempValue != ParameterHandle.minValue) ||
		(maxTempValue != ParameterHandle.maxValue))
		needDisplayUpdate = sbgcTRUE;

	if (needDisplayUpdate)
	{
		MiniRemote.UpdateLastResponseTime();

		if (gimbalConnected_ || MiniRemote.Presets.adjVarsSync == AVS_REMOTE_PRIORITY)
			SerialAPI_EditAdjVarValue(&Gimbal.Presets.AdjVarGeneral[selectedAdjVarID], ParameterHandle.tempValue);

		if (gimbalConnected_)
		{
			Gimbal.SetAdjVarValue(&Gimbal.Presets.AdjVarGeneral[selectedAdjVarID],
								  SCParam_NO, SCPrior_NORMAL, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);
		}
	}
}


void CAdjVarEditContainerM::Init (void)
{
	static gdispImage *gdispImageBuff;

	static GWidgetInit wi;
	gwinWidgetClearInit(&wi);

	/* Container */
	wi.g.show = FALSE;
	wi.g.x = 0;
	wi.g.y = 0;
	wi.g.width = gdispGetWidth();
	wi.g.height = gdispGetHeight();
	wi.customDraw = ContainerDrawMono;
	wi.customParam = &sAdjVarEditContainerDraw;
	ghContainer = gwinContainerCreate(0, &wi, 0);
	wi.g.show = TRUE;
	wi.g.parent = ghContainer;

	/* Return image */
	Utils::imageOpenFile(gdispImageBuff, imagePathsReferenceArray[IPR_ARROW_RETURN_LEFT]);
	wi.g.x = 0;
	wi.g.y = 0;
	wi.g.height = gdispImageBuff->height;
	wi.g.width = gdispImageBuff->width;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
	wi.customDraw = gwinImageWOpenAndDrawCustom_Mono;
	wi.customParam = (void*)imagePathsReferenceArray[IPR_ARROW_RETURN_LEFT];
	ghImageReturn = gwinImageWCreate(0, &wi);
	Utils::imageCloseFile(gdispImageBuff);

	/* Edit image */
	Utils::imageOpenFile(gdispImageBuff, imagePathsReferenceArray[IPR_ADJ_VARS_EDIT]);
	wi.g.x = DISPLAY_WIDTH - (WIDGET_IMAGE_SIZE * 2);
	wi.g.y = 0;
	wi.g.height = gdispImageBuff->height;
	wi.g.width = gdispImageBuff->width;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
	wi.customDraw = gwinImageWOpenAndDrawCustom_Mono;
	wi.customParam = (void*)imagePathsReferenceArray[IPR_ADJ_VARS_EDIT];
	ghImageEdit = gwinImageWCreate(0, &wi);
	Utils::imageCloseFile(gdispImageBuff);

	/* Add image */
	Utils::imageOpenFile(gdispImageBuff, imagePathsReferenceArray[IPR_ADJ_VARS_ADD]);
	wi.g.x = DISPLAY_WIDTH - WIDGET_IMAGE_SIZE;
	wi.g.y = 0;
	wi.g.height = gdispImageBuff->height;
	wi.g.width = gdispImageBuff->width;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
	wi.customDraw = gwinImageWOpenAndDrawCustom_Mono;
	wi.customParam = (void*)imagePathsReferenceArray[IPR_ADJ_VARS_ADD];
	ghImageAdd = gwinImageWCreate(0, &wi);
	Utils::imageCloseFile(gdispImageBuff);
	gwinHide(ghImageAdd);

	/* Remove image */
	Utils::imageOpenFile(gdispImageBuff, imagePathsReferenceArray[IPR_ADJ_VARS_REMOVE]);
	wi.g.x = DISPLAY_WIDTH - WIDGET_IMAGE_SIZE;
	wi.g.y = 0;
	wi.g.height = gdispImageBuff->height;
	wi.g.width = gdispImageBuff->width;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
	wi.customDraw = gwinImageWOpenAndDrawCustom_Mono;
	wi.customParam = (void*)imagePathsReferenceArray[IPR_ADJ_VARS_REMOVE];
	ghImageRemove = gwinImageWCreate(0, &wi);
	Utils::imageCloseFile(gdispImageBuff);

	/* Label title */
	wi.g.width = DISPLAY_WIDTH - (WIDGET_IMAGE_SIZE * 4);
	wi.g.height = LARGE_FONT_HEIGHT;
	wi.g.x = WIDGET_IMAGE_SIZE * 2;
	wi.g.y = ((EDIT_TITLE_TOTAL_HEIGHT - MEDIUM_FONT_HEIGHT) / 2) - 1;
	wi.text = "Adjvar. Edit";
	wi.customStyle = &CWidgetStyle::MonoImgStyleLabelDimmed;
	wi.customParam = (void*)justifyCenter;
	wi.customDraw = gwinLabelDrawJustifiedCustomMono;
	ghLabelTitle = gwinLabelCreate(0, &wi);

	/* Label value */
	wi.g.width = DISPLAY_WIDTH;
	wi.g.height = MEDIUM_FONT_HEIGHT;
	wi.g.x = 0;
	wi.g.y = (DISPLAY_HEIGHT / 2) - MEDIUM_FONT_HEIGHT - ADJVAR_EDIT_Y_CENTER_OFFSET;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleLabelDimmed;
	wi.customParam = (void*)justifyCenter;
	wi.customDraw = gwinLabelDrawJustifiedCustomMono;
	ghLabelValue = gwinLabelCreate(0, &wi);

	/* Minimum of value */
	wi.g.width = EDIT_BOUND_LABELS_WIDTH;
	wi.g.height = SMALL_FONT_HEIGHT;
	wi.g.x = EDIT_MIN_LABEL_X_COORD;
	wi.g.y = (DISPLAY_HEIGHT / 2) - ADJVAR_EDIT_Y_CENTER_OFFSET + 12;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleLabelDimmed;
	wi.customParam = (void*)justifyCenter;
	wi.customDraw = gwinLabelDrawJustifiedCustomMono;
	ghLabelMinValue = gwinLabelCreate(0, &wi);
	gwinSetFont(ghLabelMinValue, MiniRemote.GetSmallFont());

	/* Maximum of value */
	wi.g.x = EDIT_MAX_LABEL_X_COORD;
	wi.text = "";
	wi.customParam = (void*)justifyCenter;
	ghLabelMaxValue = gwinLabelCreate(0, &wi);
	gwinSetFont(ghLabelMaxValue, MiniRemote.GetSmallFont());

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
	wi.g.y = (gdispGetHeight() / 2) + EDIT_VALUE_PRBAR_CLEARANCE - ADJVAR_EDIT_Y_CENTER_OFFSET;
	wi.text = 0;
	wi.customDraw = gwinProgressbarDrawCustom_Mono;
	wi.customStyle = &CWidgetStyle::MonoProgressbarStyle;
	ghValueProgressbar = gwinProgressbarCreate(0, &wi);
}


void CAdjVarEditContainerM::OnHide (void)
{
	editState = AVES_EDIT_VALUE;

	if ((Gimbal.Presets.AdjVarGeneral[selectedAdjVarID].minValue != ParameterHandle.minValue) ||
		(Gimbal.Presets.AdjVarGeneral[selectedAdjVarID].maxValue != ParameterHandle.maxValue))
	{
		Gimbal.Presets.AdjVarGeneral[selectedAdjVarID].minValue = (i16)ParameterHandle.minValue;
		Gimbal.Presets.AdjVarGeneral[selectedAdjVarID].maxValue = (i16)ParameterHandle.maxValue;

		SettingsLoader.SaveGimbalParameter(&Gimbal.Presets.AdjVarGeneral[selectedAdjVarID].minValue);
		SettingsLoader.SaveGimbalParameter(&Gimbal.Presets.AdjVarGeneral[selectedAdjVarID].maxValue);
	}
}


void CAdjVarEditContainerM::vTask (void *pvParameters)
{
	if (dialogAnswer == MWDA_YES)
	{
		if (exCSBGCInfoContainerM.GetState() == SBGC_MENU_ADJVARS_DATA)
		{
			Gimbal.Presets.AdjVarGeneral[selectedAdjVarID].custom.activeFlag = false;
			activeAdjVarsCount--;

			exCSBGCInfoContainerM.DecreaseSelectedItemNumber();

			dialogAnswer = MWDA_CLEANED;
			CStateManager::SetState({ PREVIOUS_STATE, 0 });
			while (1);
		}

		else if (exCSBGCInfoContainerM.GetState() == SBGC_MENU_OTHER_ADJVARS_DATA)
		{
			Gimbal.Presets.AdjVarGeneral[selectedAdjVarID].custom.activeFlag = true;
			activeAdjVarsCount++;

			exCSBGCInfoContainerM.DecreaseSelectedItemNumber();

			dialogAnswer = MWDA_CLEANED;
			CStateManager::SetState({ PREVIOUS_STATE, 0 });
			while (1);
		}
	}

	MiniRemote.ProcessFunction(CSF_PARAMETER_CHANGE, &ParameterHandle.newControlValue);
	ParameterHandle.oldControlValue = ParameterHandle.newControlValue;

	selectedAdjVarID = *(ui32*)pvParameters;
	InitAdjVarEditContainerHandler(selectedAdjVarID);

	/* Adjvars class determination */
	if (Gimbal.Presets.AdjVarGeneral[selectedAdjVarID].custom.activeFlag)
		containerPhase = AVAC_ACTIVE_ADJVARS;

	else
		containerPhase = AVAC_OTHER_ADJVARS;

	/* Upper panel's widgets definition */
	if (exCSBGCInfoContainerM.GetState() == SBGC_MENU_ADJVARS_DATA)
	{
		gwinHide(ghImageAdd);
		gwinShow(ghImageRemove);
	}

	else
	{
		gwinShow(ghImageAdd);
		gwinHide(ghImageRemove);
	}

	ui8 inversionTemp = 0;

	Redraw();

	gwinShow(ghContainer);

	NavigationDirection_t nav;
	ButtonState_t enterButton = BS_INIT;
	ButtonState_t exitButton = BS_INIT;

	TickType_t xBlinkTime = osGetTickCount();

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
			gwinSetText(ghLabelTitle, "Adjvar. Edit", FALSE);
			osDelay(50);  // Necessary delay
			CStateManager::SetState({ PREVIOUS_STATE, 0 });
			while (1);
		}

		/* List moving */
		if ((nav == ND_UP) && (editState == AVES_EDIT_VALUE))
		{
			selectedAdjVarID = Gimbal.FindPreviousAdjVar(containerPhase, selectedAdjVarID);
			InitAdjVarEditContainerHandler(selectedAdjVarID);
			Redraw();
		}

		if ((nav == ND_DOWN) && (editState == AVES_EDIT_VALUE))
		{
			selectedAdjVarID = Gimbal.FindNextAdjVar(containerPhase, selectedAdjVarID);
			InitAdjVarEditContainerHandler(selectedAdjVarID);
			Redraw();
		}

		if (editLock == sbgcFALSE)
		{
			/* Target value toggle */
			if (nav == ND_RIGHT)
				ValueToggle();

			/* Control handle */
			ParameterProcessOperating(enterButton);

			/* Display processing */
			if (needDisplayUpdate)
			{
				if ((ParameterHandle.minValue != minTempValue) || (ParameterHandle.maxValue != maxTempValue))
				{
					ParameterHandle.minValue = constrain_(minTempValue, adjVarsReferenceInfoArray[selectedAdjVarID].minValue,
																		ParameterHandle.maxValue);

					ParameterHandle.maxValue = constrain_(maxTempValue, ParameterHandle.minValue,
																		adjVarsReferenceInfoArray[selectedAdjVarID].maxValue);

					gwinProgressbarSetRange(ghValueProgressbar, ParameterHandle.minValue, ParameterHandle.maxValue);

					if (ParameterHandle.tempValue < ParameterHandle.minValue)
						ParameterHandle.tempValue = ParameterHandle.minValue;

					else if (ParameterHandle.tempValue > ParameterHandle.maxValue)
						ParameterHandle.tempValue = ParameterHandle.maxValue;

					gwinProgressbarSetPosition(ghValueProgressbar, ParameterHandle.tempValue);

					snprintf_((char*)minBuff, sizeof(minBuff), "%i", ParameterHandle.minValue);
					gwinSetText(ghLabelMinValue, (const char*)minBuff, FALSE);

					snprintf_((char*)maxBuff, sizeof(maxBuff), "%i", ParameterHandle.maxValue);
					gwinSetText(ghLabelMaxValue, (const char*)maxBuff, FALSE);
				}

				snprintf_((char*)valueBuff, sizeof(valueBuff), "%i", ParameterHandle.tempValue);
				gwinSetText(ghLabelValue, (const char*)valueBuff, FALSE);

				if ((ParameterHandle.initValue != ParameterHandle.tempValue) ||
					(minInitValue != minTempValue) ||
					(maxInitValue != maxTempValue))
					gwinSetText(ghLabelTitle, "Adjvar. Edit*", FALSE);

				else
					gwinSetText(ghLabelTitle, "Adjvar. Edit", FALSE);

				gwinProgressbarSetPosition(ghValueProgressbar, ParameterHandle.tempValue);

				needDisplayUpdate = sbgcFALSE;
			}

			if (editState != AVES_EDIT_VALUE)
			{
				switch (editState)
				{
					case AVES_EDIT_MIN :
						inversionTemp ? gwinSetText(ghLabelMinValue, (const char*)minBuff, FALSE) : gwinSetText(ghLabelMinValue, "", FALSE);
						break;

					case AVES_EDIT_MAX :
						inversionTemp ? gwinSetText(ghLabelMaxValue, (const char*)maxBuff, FALSE) : gwinSetText(ghLabelMaxValue, "", FALSE);
						break;

					default :
						break;
				}

				if ((osGetTickCount() - xBlinkTime) > CONTAINER_BLINK_DELAY)
				{
					inversionTemp = !inversionTemp;
					xBlinkTime = osGetTickCount();
				}
			}

			/* Control handle */
			MiniRemote.ProcessFunction(CSF_PARAMETER_CHANGE, &ParameterHandle.newControlValue);

			if ((abs(ParameterHandle.newControlValue - ParameterHandle.oldControlValue)) > AS5048_MAX_DISPERSION)
			{

				switch (editState)
				{
					case AVES_EDIT_VALUE :
						ParameterHandle.filter = FilterEncoderValue(ParameterHandle.oldControlValue, ParameterHandle.newControlValue,
																  EDIT_FILTER_DIVIDER_CONSTANT) * ParameterHandle.divider;
						ParameterHandle.tempValue = constrain_((ParameterHandle.tempValue + CalculateSignedCeil(ParameterHandle.filter)),
																ParameterHandle.minValue, ParameterHandle.maxValue);
						break;

					case AVES_EDIT_MIN :
						ParameterHandle.filter = FilterEncoderValue(ParameterHandle.oldControlValue, ParameterHandle.newControlValue,
																  EDIT_FILTER_DIVIDER_CONSTANT) * ParameterHandle.divider;
						minTempValue = constrain_((minTempValue + CalculateSignedCeil(ParameterHandle.filter)),
												   adjVarsReferenceInfoArray[selectedAdjVarID].minValue,
												   adjVarsReferenceInfoArray[selectedAdjVarID].maxValue);
						break;

					case AVES_EDIT_MAX :
						ParameterHandle.filter = FilterEncoderValue(ParameterHandle.oldControlValue, ParameterHandle.newControlValue,
																  EDIT_FILTER_DIVIDER_CONSTANT) * ParameterHandle.divider;
						maxTempValue = constrain_((maxTempValue + CalculateSignedCeil(ParameterHandle.filter)),
												   adjVarsReferenceInfoArray[selectedAdjVarID].minValue,
												   adjVarsReferenceInfoArray[selectedAdjVarID].maxValue);
						break;
				}

				ParameterHandle.oldControlValue = ParameterHandle.newControlValue;
			}
		}

		/* If variable is locked, but it's need to fill progressbar */
		else if (needDisplayUpdate == sbgcTRUE)
		{
			gwinProgressbarSetPosition(ghValueProgressbar, ADJVAR_LOCK_VALUE);
			needDisplayUpdate = sbgcFALSE;
		}


		osDelay(CONTAINER_PROCESS_DELAY);
	}
}


void CAdjVarEditContainerM::Redraw (void)
{
	minInitValue = ParameterHandle.minValue;
	minTempValue = minInitValue;

	maxInitValue = ParameterHandle.maxValue;
	maxTempValue = maxInitValue;

	snprintf_(minBuff, sizeof(minBuff), "%i", ParameterHandle.minValue);
	gwinSetText(ghLabelMinValue, (const char*)minBuff, FALSE);

	snprintf_(maxBuff, sizeof(maxBuff), "%i", ParameterHandle.maxValue);
	gwinSetText(ghLabelMaxValue, (const char*)maxBuff, FALSE);

	snprintf_((char*)valueBuff, sizeof(valueBuff), "%i", ParameterHandle.tempValue);
	gwinSetText(ghLabelValue, (const char*)valueBuff, FALSE);

	memcpy(nameBuff, ParameterHandle.name, strlen(ParameterHandle.name));
	gwinSetText(ghLabelName, ParameterHandle.name, FALSE);

	gwinProgressbarSetPosition(ghValueProgressbar, ParameterHandle.tempValue);
	gwinProgressbarSetRange(ghValueProgressbar, ParameterHandle.minValue, ParameterHandle.maxValue);

	needDisplayUpdate = sbgcTRUE;
}


void CAdjVarEditContainerM::ValueToggle (void)
{
	switch (editState)
	{
		case AVES_EDIT_VALUE :
			editState = AVES_EDIT_MIN;
			break;

		case AVES_EDIT_MIN :
			gwinSetText(ghLabelMinValue, (const char*)minBuff, FALSE);
			editState = AVES_EDIT_MAX;
			break;

		case AVES_EDIT_MAX :
			gwinSetText(ghLabelMaxValue, (const char*)maxBuff, FALSE);
			editState = AVES_EDIT_VALUE;
			break;
	}
}
