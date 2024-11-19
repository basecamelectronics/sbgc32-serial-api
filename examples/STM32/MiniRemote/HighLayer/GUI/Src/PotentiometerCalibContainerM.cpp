/** ____________________________________________________________________
 *
 *	@file		PotentiometerCalibContainerM.cpp
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


sContainerDraw sPotentiometerCalibContainerDraw = {"Pot. Calib.", "Press \"Enter\" for OK"};


void CPotentiometerCalibContainerM::Init (void)
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
	wi.customParam = &sPotentiometerCalibContainerDraw;
	ghContainer = gwinContainerCreate(0, &wi, 0);
	wi.g.show = TRUE;
	wi.g.parent = ghContainer;

	/* Exit image */
	Utils::imageOpenFile(gdispImageReturn, imagePathsReferenceArray[IPR_EXIT]);
	wi.g.x = 0;
	wi.g.y = 0;
	wi.g.height = gdispImageReturn->height;
	wi.g.width = gdispImageReturn->width;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
	wi.customDraw = gwinImageWOpenAndDrawCustom_Mono;
	wi.customParam = (void*)imagePathsReferenceArray[IPR_EXIT];
	ghImageReturn = gwinImageWCreate(0, &wi);
	Utils::imageCloseFile(gdispImageReturn);

	/* Current status label */
	wi.g.width = CALIB_STATE_LABEL_WIDTH;
	wi.g.height = MEDIUM_FONT_HEIGHT;
	wi.g.x = CALIB_STATE_LABEL_X_COORD;
	wi.g.y = CALIB_STATE_LABEL_Y_COORD;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
	wi.customParam = (void*)justifyCenter;
	wi.customDraw = gwinLabelDrawJustifiedCustomMono;
	ghLabelStatus = gwinLabelCreate(0, &wi);

	/* Percents label */
	wi.g.width = CALIB_VALUES_LABEL_WIDTH;
	wi.g.height = MEDIUM_FONT_HEIGHT;
	wi.g.x = CALIB_VALUES_LABEL_X_COORD;
	wi.g.y = CALIB_VALUES_LABEL_Y_COORD;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
	wi.customParam = (void*)justifyCenter;
	wi.customDraw = gwinLabelDrawJustifiedCustomMono;
	ghLabelPercent = gwinLabelCreate(0, &wi);

	/* Joystick */
	wi.g.width = CALIB_WINDOW_SIZE;
	wi.g.height = CALIB_WINDOW_SIZE;
	wi.g.x = CALIB_WINDOW_X_COORD;
	wi.g.y = CALIB_WINDOW_Y_COORD;
	wi.text = "";
	wi.customDraw = gwinProgressbarDrawPotentiometerVisualMono;
	wi.customStyle = &CWidgetStyle::MonoProgressbarStyle;
	ghPotentiometerVisual = gwinProgressbarCreate(0, &wi);
	gwinProgressbarSetRange(ghPotentiometerVisual, 0, ANALOG_IN_MAX_VALUE);
}


void CPotentiometerCalibContainerM::OnHide (void)
{
	SettingsLoader.SaveRemoteParameter(&MiniRemote.Presets.handlersCalibs.potMin);
	SettingsLoader.SaveRemoteParameter(&MiniRemote.Presets.handlersCalibs.potMax);
	SettingsLoader.SaveRemoteParameter(&MiniRemote.Presets.handlersCalibs.potZero);
}


void CPotentiometerCalibContainerM::vTask (void *pvParameters)
{
	unused_(pvParameters);

	ui16 potRaw, potNorm;
	char percentBuff [5];

	ui16	minTemp = MiniRemote.Presets.handlersCalibs.potMin,
			maxTemp = MiniRemote.Presets.handlersCalibs.potMax,
			zeroTemp = MiniRemote.Presets.handlersCalibs.potZero;

	MiniRemote.Presets.handlersCalibs.potMin = 0;
	MiniRemote.Presets.handlersCalibs.potMax = ANALOG_IN_MAX_VALUE;
	MiniRemote.Presets.handlersCalibs.potZero = ANALOG_IN_MIDDLE_VALUE;

	calibState = PCPS_ZERO_CALIB;
	gwinSetText(ghLabelStatus, "Zero calib.", FALSE);

	gwinSetText(ghLabelPercent, "", FALSE);

	gwinShow(ghContainer);

	NavigationDirection_t nav;
	ButtonState_t exitButton = BS_INIT;
	ButtonState_t enterButton = BS_INIT;

	TickType_t xNavigationBlockTime = osGetTickCount();
	while (osGetTickCount() < (xNavigationBlockTime + NAVIGATION_INIT_BLOCK_TIME));

	while (1)
	{
		MiniRemote.ProcessNavigationDirection();
		nav = MiniRemote.GetNavigationDirection();
		MiniRemote.ProcessFunction(CSF_NAVIGATION_EXIT, &exitButton);
		MiniRemote.ProcessFunction(CSF_NAVIGATION_ENTER, &enterButton);
		MiniRemote.ProcessFunction(VSF_AXIS_TRIMMING, &potRaw);
		MiniRemote.ProcessFunction(VSF_AXIS_TRIMMING, &potNorm);
		MiniRemote.NormalizePotentiometerValue(&potNorm);

		if ((nav == ND_LEFT) || (exitButton == BS_PRESSED))
		/* Abort calibration */
		{
			MiniRemote.Presets.handlersCalibs.potMin = minTemp;
			MiniRemote.Presets.handlersCalibs.potMax = maxTemp;
			MiniRemote.Presets.handlersCalibs.potZero = zeroTemp;

			CStateManager::SetState({ PREVIOUS_STATE, 0 });
			while (1);
		}

		/* State switching */
		if (enterButton == BS_PRESSED)
		{
			if (calibState == PCPS_ZERO_CALIB)
			{
				MiniRemote.Presets.handlersCalibs.potZero = potRaw;
				gwinSetText(ghLabelStatus, "Min. calib.", FALSE);
			}

			else if (calibState == PCPS_MIN_CALIB)
			{
				if (potRaw >= MiniRemote.Presets.handlersCalibs.potZero)
					continue;

				MiniRemote.Presets.handlersCalibs.potMin = potRaw;
				gwinSetText(ghLabelStatus, "Max. calib.", FALSE);
			}

			else if (calibState == PCPS_MAX_CALIB)
			{
				if (potRaw <= MiniRemote.Presets.handlersCalibs.potZero)
					continue;

				MiniRemote.Presets.handlersCalibs.potMax = potRaw;
				gwinSetText(ghLabelStatus, "Save calibs?", FALSE);
			}

			else if (calibState == PCPS_WAIT_FINISH)
			{
				CStateManager::SetState({ PREVIOUS_STATE, 0 });
				while (1);
			}

			calibState = (PotCalibProcessState_t)(calibState + 1);
		}

		/* Drawing */
		snprintf_(percentBuff, sizeof(percentBuff), "%d%%", (ui16)((potRaw * 1.0F / 4096) * 100));
		gwinSetText(ghLabelPercent, (const char*)percentBuff, FALSE);

		gwinProgressbarSetPosition(ghPotentiometerVisual, potNorm);

		/* System awaking */
		MiniRemote.UpdateLastResponseTime();

		osDelay(CONTAINER_PROCESS_DELAY);
	}
}
