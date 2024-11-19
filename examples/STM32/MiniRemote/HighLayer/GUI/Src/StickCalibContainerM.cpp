/** ____________________________________________________________________
 *
 *	@file		StickCalibContainerM.cpp
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


sContainerDraw sStickCalibContainerDraw = {"Joystick Calib.", "Press \"Enter\" for OK"};


void CStickCalibContainerM::Init (void)
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
	wi.customParam = &sStickCalibContainerDraw;
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
	ghLabelPercentY = gwinLabelCreate(0, &wi);

	/* Joystick */
	wi.g.width = CALIB_WINDOW_SIZE;
	wi.g.height = CALIB_WINDOW_SIZE;
	wi.g.x = CALIB_WINDOW_X_COORD;
	wi.g.y = CALIB_WINDOW_Y_COORD;
	wi.text = 0;
	wi.customParam = &joyY_Temp;
	wi.customDraw = gwinProgressbarDrawJoystickVisualMono;
	wi.customStyle = &CWidgetStyle::MonoProgressbarStyle;
	ghJoystickVisual = gwinProgressbarCreate(0, &wi);
}


void CStickCalibContainerM::OnHide (void)
{
	SettingsLoader.SaveRemoteParameter(&MiniRemote.Presets.handlersCalibs.joyX_Min);
	SettingsLoader.SaveRemoteParameter(&MiniRemote.Presets.handlersCalibs.joyX_Max);
	SettingsLoader.SaveRemoteParameter(&MiniRemote.Presets.handlersCalibs.joyX_Zero);

	SettingsLoader.SaveRemoteParameter(&MiniRemote.Presets.handlersCalibs.joyY_Min);
	SettingsLoader.SaveRemoteParameter(&MiniRemote.Presets.handlersCalibs.joyY_Max);
	SettingsLoader.SaveRemoteParameter(&MiniRemote.Presets.handlersCalibs.joyY_Zero);
}


void CStickCalibContainerM::vTask (void *pvParameters)
{
	unused_(pvParameters);

	char percentBuff [10];
	ui32 timestamp = osGetTickCount();
	bool isZeroApplied = false;

	ui16	joyX_ValueRaw, joyX_ValueNormalized,
			joyY_ValueRaw, joyY_ValueNormalized;

	ui32	avgX = 0;
	ui32	avgY = 0;
	ui16	avgN = 0;

	MiniRemote.Presets.handlersCalibs.joyX_Min = IN_MIDDLE_VALUE / 2;
	MiniRemote.Presets.handlersCalibs.joyX_Max = IN_MIDDLE_VALUE + (IN_MIDDLE_VALUE / 2);
	MiniRemote.Presets.handlersCalibs.joyY_Min = IN_MIDDLE_VALUE / 2;
	MiniRemote.Presets.handlersCalibs.joyY_Max = IN_MIDDLE_VALUE + (IN_MIDDLE_VALUE / 2);

	gwinShow(ghContainer);

	ButtonState_t exitButton = BS_INIT;
	ButtonState_t enterButton = BS_INIT;

	TickType_t xNavigationBlockTime = osGetTickCount();
	while (osGetTickCount() < (xNavigationBlockTime + NAVIGATION_INIT_BLOCK_TIME));

	while (1)
	{
		MiniRemote.ProcessFunction(CSF_NAVIGATION_EXIT, &exitButton);
		MiniRemote.ProcessFunction(CSF_NAVIGATION_ENTER, &enterButton);

		if ((exitButton == BS_PRESSED) || (enterButton == BS_PRESSED))
		{
			CStateManager::SetState({ PREVIOUS_STATE, 0 });
			while (1);
		}

		MiniRemote.ProcessFunction(CSF_NAVIGATION_X, &joyX_ValueRaw);
		MiniRemote.ProcessFunction(CSF_NAVIGATION_Y, &joyY_ValueRaw);

		MiniRemote.ProcessFunction(CSF_NAVIGATION_X, &joyX_ValueNormalized);
		MiniRemote.ProcessFunction(CSF_NAVIGATION_Y, &joyY_ValueNormalized);

		MiniRemote.NormalizeJoystickValues(&joyX_ValueNormalized, &joyY_ValueNormalized);

		snprintf_(percentBuff, sizeof(percentBuff), "%i%% %i%%",
				  (joyX_ValueNormalized * 100) / IN_MAX_VALUE, (joyY_ValueNormalized * 100) / IN_MAX_VALUE);
		gwinSetText(ghLabelPercentY, (const char*)percentBuff, FALSE);

		/* Bounds calibration */
		if ((osGetTickCount() - timestamp) > STICK_CALIB_BOUNDS_PASS_TIME)
		{
			gwinSetText(ghLabelStatus, "Bound. calib.", FALSE);

			if (!isZeroApplied)
			{
				MiniRemote.Presets.handlersCalibs.joyX_Zero = avgX / avgN;
				MiniRemote.Presets.handlersCalibs.joyY_Zero = avgY / avgN;
				isZeroApplied = true;
			}
		}

		/* Origin calibration */
		else if ((osGetTickCount() - timestamp) > STICK_CALIB_ORIGIN_PASS_TIME)
		{
			gwinSetText(ghLabelStatus, "Origin calib.", FALSE);

			avgX += joyX_ValueRaw;
			avgY += joyY_ValueRaw;
			avgN++;
		}

		else
			gwinSetText(ghLabelStatus, "Align center", FALSE);

		/* Min/Max correction */
		if (joyX_ValueRaw < MiniRemote.Presets.handlersCalibs.joyX_Min)
			MiniRemote.Presets.handlersCalibs.joyX_Min = joyX_ValueRaw;

		if (joyX_ValueRaw > MiniRemote.Presets.handlersCalibs.joyX_Max)
			MiniRemote.Presets.handlersCalibs.joyX_Max = joyX_ValueRaw;

		if (joyY_ValueRaw < MiniRemote.Presets.handlersCalibs.joyY_Min)
			MiniRemote.Presets.handlersCalibs.joyY_Min = joyY_ValueRaw;

		if (joyY_ValueRaw > MiniRemote.Presets.handlersCalibs.joyY_Max)
			MiniRemote.Presets.handlersCalibs.joyY_Max = joyY_ValueRaw;


		joyY_Temp = (joyY_ValueNormalized * 100) / IN_MAX_VALUE;
		gwinProgressbarSetPosition(ghJoystickVisual, (joyX_ValueNormalized * 100) / IN_MAX_VALUE);

		/* System awaking */
		MiniRemote.UpdateLastResponseTime();

		osDelay(CONTAINER_PROCESS_DELAY);
	}
}
