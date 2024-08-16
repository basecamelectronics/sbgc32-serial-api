/** ____________________________________________________________________
 *
 *	@file		ControlContainerM.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "createWidget.h"
#include "src/gdisp/gdisp_driver.h"
#include "gimbal.h"
#include "parameters.h"


static void DrawPotentiometerCircle (gCoord x, gCoord y, gCoord r)
{
	ui8	x0_Temp, y0_Temp, x1_Temp, y1_Temp;

	gdispDrawArc(x, y, r, 300, 240, GFX_LIGHT_GRAY);
	gdispDrawArc(x, y, r - CONTROL_CIRCLE_THICK, 300, 240, GFX_LIGHT_GRAY);

	x0_Temp = x - (r * sin(sbgcDegreeToRadians(30)));
	y0_Temp = y + (r * cos(sbgcDegreeToRadians(30)));
	x1_Temp = x - ((r - CONTROL_CIRCLE_THICK) * sin(sbgcDegreeToRadians(30)));
	y1_Temp = y + ((r - CONTROL_CIRCLE_THICK) * cos(sbgcDegreeToRadians(30)));

	gdispDrawLine(x0_Temp, y0_Temp, x1_Temp, y1_Temp, GFX_LIGHT_GRAY);

	x0_Temp = x + (r * sin(sbgcDegreeToRadians(30)));
	y0_Temp = y + (r * cos(sbgcDegreeToRadians(30)));
	x1_Temp = x + ((r - CONTROL_CIRCLE_THICK) * sin(sbgcDegreeToRadians(30)));
	y1_Temp = y + ((r - CONTROL_CIRCLE_THICK) * cos(sbgcDegreeToRadians(30)));

	gdispDrawLine(x0_Temp, y0_Temp, x1_Temp, y1_Temp, GFX_LIGHT_GRAY);
}


static void DrawPotentiometerArrow (gCoord x, gCoord y, gCoord length, double angle, gColor color)
{
	ui8	x0_Temp, y0_Temp, x1_Temp, y1_Temp;

	double	sinTemp = sin(sbgcDegreeToRadians(angle)),
			cosTemp = cos(sbgcDegreeToRadians(angle));

	if (angle < 90)
	{
		x0_Temp = x + (length * cosTemp);
		y0_Temp = y - (length * sinTemp);
		x1_Temp = x + ((length - CONTROL_CIRCLE_ARROW_LENGHT) * cosTemp);
		y1_Temp = y - ((length - CONTROL_CIRCLE_ARROW_LENGHT) * sinTemp);
	}

	else if (angle < 180)
	{
		x0_Temp = x + (length * cosTemp);
		y0_Temp = y - (length * sinTemp);
		x1_Temp = x + ((length - CONTROL_CIRCLE_ARROW_LENGHT) * cosTemp);
		y1_Temp = y - ((length - CONTROL_CIRCLE_ARROW_LENGHT) * sinTemp);
	}

	else if (angle < 270)
	{
		x0_Temp = x + (length * cosTemp);
		y0_Temp = y - (length * sinTemp);
		x1_Temp = x + ((length - CONTROL_CIRCLE_ARROW_LENGHT) * cosTemp);
		y1_Temp = y - ((length - CONTROL_CIRCLE_ARROW_LENGHT) * sinTemp);
	}

	else if (angle < 360)
	{
		x0_Temp = x + (length * cosTemp);
		y0_Temp = y - (length * sinTemp);
		x1_Temp = x + ((length - CONTROL_CIRCLE_ARROW_LENGHT) * cosTemp);
		y1_Temp = y - ((length - CONTROL_CIRCLE_ARROW_LENGHT) * sinTemp);
	}

	gdispDrawLine(x1_Temp, y1_Temp, x0_Temp, y0_Temp, color);
}


void CControlContainerM::RewriteControlValues (void)
{
	#define attchAxis Gimbal.GetActiveControlProfile()->controlHandler[i].attachedAxis

	i16 handlerControlValues [SBGC_CONTROL_HANDLERS_NUM];
	ui16 handlersRawValues [SBGC_CONTROL_HANDLERS_NUM];
	ui16 handlersTolerances [SBGC_CONTROL_HANDLERS_NUM];

	handlerControlValues[JOY_X] = (ControlFilterExpo[JOY_X].Calculate(xRes - IN_MIDDLE_VALUE) / IN_MAX_VALUE *
								  Gimbal.GetActiveControlProfile()->controlHandler[JOY_X].sensitivity) *
								  SBGC_CONTROL_SENS_MULTIPLIER * (Gimbal.GetActiveControlProfile()->controlHandler[JOY_X].invert ? -1 : 1);

	handlerControlValues[JOY_Y] = (ControlFilterExpo[JOY_Y].Calculate(yRes - IN_MIDDLE_VALUE) / IN_MAX_VALUE *
								  Gimbal.GetActiveControlProfile()->controlHandler[JOY_Y].sensitivity) *
								  SBGC_CONTROL_SENS_MULTIPLIER * (Gimbal.GetActiveControlProfile()->controlHandler[JOY_Y].invert ? -1 : 1);

	handlerControlValues[POT] = (ControlFilterExpo[POT].Calculate(ConvertPotentiometerValueToControl(pRes) - IN_MIDDLE_VALUE) / IN_MAX_VALUE *
								Gimbal.GetActiveControlProfile()->controlHandler[POT].sensitivity) * SBGC_CONTROL_SENS_MULTIPLIER *
								(Gimbal.GetActiveControlProfile()->controlHandler[POT].invert ? -1 : 1);

	handlersRawValues[JOY_X] = xRes;
	handlersRawValues[JOY_Y] = yRes;
	handlersRawValues[POT] = pRes;

	handlersTolerances[JOY_X] = CONTROL_AXIS_X_DEADBAND;
	handlersTolerances[JOY_Y] = CONTROL_AXIS_Y_DEADBAND;
	handlersTolerances[POT] = 0;

	for (ui8 i = 0; i < SBGC_CONTROL_HANDLERS_NUM; i++)
	{
		if (attchAxis == NOT_ASSIGNED)
			continue;

		if (Gimbal.GetActiveControlProfile()->controlHandler[i].controlMode == GIMBAL_ABSOLUTE_CONTROL)
		{
			if (deadbandcross_(handlersRawValues[i], IN_MIDDLE_VALUE, handlersTolerances[i]))
				Gimbal.Control.AxisC[attchAxis].angle = sbgcAngleToDegree(handlerControlValues[i]);

			else
				Gimbal.Control.AxisC[attchAxis].angle = 0;
		}

		else
		{
			if (deadbandcross_(handlersRawValues[i], IN_MIDDLE_VALUE, handlersTolerances[i]))
				Gimbal.Control.AxisC[attchAxis].speed = sbgcSpeedToValue(handlerControlValues[i]);

			else
				Gimbal.Control.AxisC[attchAxis].speed = 0;
		}
	}
}


void CControlContainerM::Init (void)
{
	static GWidgetInit wi;
	gwinWidgetClearInit(&wi);

	/* Container */
	wi.g.show = FALSE;
	wi.g.x = 0;
	wi.g.y = 0;
	wi.g.width = gdispGetWidth();
	wi.g.height = gdispGetHeight();
	ghContainer = gwinContainerCreate(0, &wi, 0);
	wi.g.show = TRUE;
	wi.g.parent = ghContainer;

	/* Progressbar X */
	wi.g.width = CONTROL_PROGRESSBAR_X_LENGTH;
	wi.g.height = CONTROL_PROGRESSBAR_THICK;
	wi.g.x = CONTROL_PROGRESSBAR_X_COORD_X;
	wi.g.y = CONTROL_PROGRESSBAR_X_COORD_Y;
	wi.customDraw = gwinProgressbarDrawCustom_Mono;
	wi.customStyle = &CWidgetStyle::MonoProgressbarStyle;
	ghProgressbarX = gwinProgressbarCreate(0, &wi);
	gwinProgressbarSetRange(ghProgressbarX, 0, CONTROL_PROGRESSBAR_RESOLUTION);

	/* Progressbar Y */
	wi.g.width = CONTROL_PROGRESSBAR_THICK;
	wi.g.height = CONTROL_PROGRESSBAR_Y_LENGTH;
	wi.g.x = CONTROL_PROGRESSBAR_Y_COORD_X;
	wi.g.y = CONTROL_PROGRESSBAR_Y_COORD_Y;
	wi.customDraw = gwinProgressbarDrawCustom_Mono;
	wi.customStyle = &CWidgetStyle::MonoProgressbarStyle;
	ghProgressbarY = gwinProgressbarCreate(0, &wi);
	gwinProgressbarSetRange(ghProgressbarY, 0, CONTROL_PROGRESSBAR_RESOLUTION);


	/* Gimbal profile label */
	wi.g.width = CONTROL_LABEL_GMB_PRF_WIDTH;
	wi.g.height = CONTROL_PROFILE_LABELS_HEIGHT;
	wi.g.x = CONTROL_LABEL_GMB_PRF_COORD_X;
	wi.g.y = CONTROL_LABEL_GMB_PRF_COORD_Y;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleLabelNormalFramed;
	wi.customParam = (void*)(justifyCenter | justifyMiddle);
	wi.customDraw = gwinLabelDrawJustifiedCustomMono;
	ghLabelGimbalProfile = gwinLabelCreate(0, &wi);

	/* Control profile label */
	wi.g.width = CONTROL_LABEL_CTRL_PRF_WIDTH;
	wi.g.height = CONTROL_PROFILE_LABELS_HEIGHT;
	wi.g.x = CONTROL_LABEL_CTRL_PRF_COORD_X;
	wi.g.y = CONTROL_LABEL_CTRL_PRF_COORD_Y;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleLabelNormalFramed;
	wi.customParam = (void*)(justifyCenter | justifyMiddle);
	wi.customDraw = gwinLabelDrawJustifiedCustomMono;
	ghLabelControlProfile = gwinLabelCreate(0, &wi);

	/* Control sensitivity adjust label */
	wi.g.width = CONTROL_SENS_ADJ_WIDTH;
	wi.g.height = CONTROL_LABELS_HEIGHT;
	wi.g.x = CONTROL_SENS_ADJ_COORD_X;
	wi.g.y = CONTROL_SENS_ADJ_COORD_Y;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
	wi.customParam = (void*)justifyRight;
	wi.customDraw = gwinLabelDrawJustifiedCustomMono;
	ghLabelControlSens = gwinLabelCreate(0, &wi);
	gwinSetFont(ghLabelControlSens, MiniRemote.GetMediumFont());


	/* Axis X name label */
	wi.g.width = CONTROL_LABEL_AXIS_X_WIDTH;
	wi.g.height = CONTROL_LABELS_HEIGHT;
	wi.g.x = CONTROL_LABEL_AXIS_X_COORD_X;
	wi.g.y = CONTROL_LABEL_AXIS_X_COORD_Y;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
	wi.customParam = (void*)justifyRight;
	ghLabelAxisX = gwinLabelCreate(0, &wi);
	gwinSetFont(ghLabelAxisX, MiniRemote.GetMediumFont());

	/* Axis X angle label */
	wi.g.width = CONTROL_LABEL_ANGLE_X_WIDTH;
	wi.g.height = CONTROL_LABELS_HEIGHT;
	wi.g.x = CONTROL_LABEL_ANGLE_X_COORD_X;
	wi.g.y = CONTROL_LABEL_ANGLE_X_COORD_Y;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleLabelDimmed;
	wi.customParam = (void*)justifyRight;
	ghLabelAngleX = gwinLabelCreate(0, &wi);
	gwinSetFont(ghLabelAngleX, MiniRemote.GetSmallFont());


	/* Axis Y name label */
	wi.g.width = CONTROL_LABEL_AXIS_Y_WIDTH;
	wi.g.height = CONTROL_LABELS_HEIGHT;
	wi.g.x = CONTROL_LABEL_AXIS_Y_COORD_X;
	wi.g.y = CONTROL_LABEL_AXIS_Y_COORD_Y;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
	wi.customParam = (void*)justifyLeft;
	ghLabelAxisY = gwinLabelCreate(0, &wi);
	gwinSetFont(ghLabelAxisY, MiniRemote.GetMediumFont());

	/* Axis Y angle label */
	wi.g.width = CONTROL_LABEL_ANGLE_Y_WIDTH;
	wi.g.height = CONTROL_LABELS_HEIGHT;
	wi.g.x = CONTROL_LABEL_ANGLE_Y_COORD_X;
	wi.g.y = CONTROL_LABEL_ANGLE_Y_COORD_Y;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleLabelDimmed;
	wi.customParam = (void*)justifyLeft;
	ghLabelAngleY = gwinLabelCreate(0, &wi);
	gwinSetFont(ghLabelAngleY, MiniRemote.GetSmallFont());


	/* Axis C name label */
	wi.g.width = CONTROL_LABEL_AXIS_P_WIDTH;
	wi.g.height = CONTROL_LABELS_HEIGHT;
	wi.g.x = CONTROL_LABEL_AXIS_P_COORD_X;
	wi.g.y = CONTROL_LABEL_AXIS_P_COORD_Y;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
	wi.customParam = (void*)justifyLeft;
	ghLabelAxisP = gwinLabelCreate(0, &wi);
	gwinSetFont(ghLabelAxisP, MiniRemote.GetMediumFont());

	/* Axis C angle label */
	wi.g.width = CONTROL_LABEL_ANGLE_P_WIDTH;
	wi.g.height = CONTROL_LABELS_HEIGHT;
	wi.g.x = CONTROL_LABEL_ANGLE_P_COORD_X;
	wi.g.y = CONTROL_LABEL_ANGLE_P_COORD_Y;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleLabelDimmed;
	wi.customParam = (void*)justifyLeft;
	ghLabelAngleP = gwinLabelCreate(0, &wi);
	gwinSetFont(ghLabelAngleP, MiniRemote.GetSmallFont());

	/* Values init */
	xRes = 0,
	yRes = 0,
	pRes = 0;
	pResOld = 0;
}


void CControlContainerM::OnHide (void)
{
	;
}


void CControlContainerM::vTask (void *pvParameters)
{
	unused_(pvParameters);

	static ui32 dataStreamLastTime;

	ui16	incrementalCounter,
			incrementalCounterOld;

	i8		incrementalCounterDelta;

	ControlSensAdj_t sensAdjStateTemp;

	ui32	controlSensLastTime;


	char	gimbalProfileBuff [5],
			controlProfileBuff [5],
			controlSensAdjBuff [10],
			axisX_Buff [10],
			angleX_Buff [10],
			axisY_Buff [10],
			angleY_Buff [10],
			axisP_Buff [10],
			angleC_Buff [10];

	ui32	lastRealTimeDataTime = 0,
			lastControlTime = 0;

	ui16	pwmResX,
			pwmResY;

	static AverageValue_t potentiometerAverage;

	sbgcBoolean_t firstTimeShowing = sbgcTRUE;

	/* Initialization */
	if (!SBGC_NoConnectionStateMask(Gimbal.GetCurrentState()))
		snprintf_((char*)gimbalProfileBuff, sizeof(gimbalProfileBuff), "GP%d", Gimbal.GetAddressRealTimeData()->curProfile + 1);

	else
		snprintf_((char*)gimbalProfileBuff, sizeof(gimbalProfileBuff), "GPx");

	gwinSetText(ghLabelGimbalProfile, (const char*)gimbalProfileBuff, FALSE);


	snprintf_((char*)controlProfileBuff, sizeof(controlProfileBuff), "CP%d", Gimbal.GetActiveControlProfile()->number + 1);
	gwinSetText(ghLabelControlProfile, (const char*)controlProfileBuff, FALSE);


	gwinSetText(ghLabelControlSens, "       ", FALSE);
	gwinSetText(ghLabelAngleX, "       ", FALSE);
	gwinSetText(ghLabelAngleY, "       ", FALSE);
	gwinSetText(ghLabelAngleP, "       ", FALSE);

	AxisNameAndModeControlFromHandler(&Gimbal.GetActiveControlProfile()->controlHandler[JOY_X], axisX_Buff);
	gwinSetText(ghLabelAxisX, (const char*)axisX_Buff, FALSE);

	AxisNameAndModeControlFromHandler(&Gimbal.GetActiveControlProfile()->controlHandler[JOY_Y], axisY_Buff);
	gwinSetText(ghLabelAxisY, (const char*)axisY_Buff, FALSE);

	AxisNameAndModeControlFromHandler(&Gimbal.GetActiveControlProfile()->controlHandler[POT], axisP_Buff);
	gwinSetText(ghLabelAxisP, (const char*)axisP_Buff, FALSE);

	currentSensAdjState = CSA_NO;
	sensAdjStateTemp = CSA_NO;
	gwinHide(ghLabelControlSens);


	gwinShow(ghContainer);

	for (ui8 i = 0; i < SBGC_CONTROL_HANDLERS_NUM; i++)
		ControlFilterExpo[i].SetRate(Gimbal.GetActiveControlProfile()->controlHandler[i].exponent);

	DrawPotentiometerCircle(CONTROL_CIRCLE_COORD_X, CONTROL_CIRCLE_COORD_Y, CONTROL_CIRCLE_RADIUS);
	AverageInit(&potentiometerAverage, CONTROL_POT_AVERAGE_FACTOR);

	MiniRemote.ProcessFunction(VSF_AXIS_CONTROL_SENS, &incrementalCounter);

	MiniRemote.ProcessFunction(VSF_AXIS_TRIMMING, &pRes);
	potentiometerAverage.avgBuff = pRes << potentiometerAverage._factor;

	/* Data stream init */
	if (!Gimbal.GetRealTimeDataCustomStreamStatus())
	{
		Gimbal.RunRealTimeDataCustomStream(CONROL_ANGLES_DATA_STREAM_RATE, SCParam_FREEZE, SCPrior_NORMAL, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);
		dataStreamLastTime = osGetTickCount();
	}

	ButtonState_t controlSenseToggleButton = BS_INIT;

	while (1)
	{
		/* Data stream */
		if (((osGetTickCount() - dataStreamLastTime) > CONROL_ANGLES_DATA_STREAM_RATE) &&
			(!SBGC_NoConnectionStateMask(Gimbal.GetCurrentState())))
		{
			Gimbal.ParseRealTimeDataCustomStream(SCParam_NO, SCPrior_LOW, CONROL_ANGLES_DATA_STREAM_RATE + SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);
			dataStreamLastTime = osGetTickCount();
		}

		/* User's control handling */
		pResOld = pRes;
		incrementalCounterOld = incrementalCounter;

		MiniRemote.ProcessFunction(VSF_SC_MENU_ADJ_VARS, &controlSenseToggleButton);  // Control sensitivity adjust for this container
		MiniRemote.ProcessFunction(CSF_NAVIGATION_X, &xRes);
		MiniRemote.ProcessFunction(CSF_NAVIGATION_Y, &yRes);
		MiniRemote.ProcessFunction(VSF_AXIS_CONTROL_SENS, &incrementalCounter);
		MiniRemote.ProcessFunction(VSF_AXIS_TRIMMING, &pRes);

		MiniRemote.NormalizeJoystickValues(&xRes, &yRes);
		AverageValue(&potentiometerAverage, pRes);
		pRes = potentiometerAverage.avgRes;
		MiniRemote.NormalizePotentiometerValue(&pRes);

		/* Angles converting */
		if ((osGetTickCount() - lastRealTimeDataTime) > REALTIME_DATA_UPDATE_TIME)
		{
			if (Gimbal.GetActiveControlProfile()->controlHandler[JOY_X].attachedAxis != NOT_ASSIGNED)
			{
				snprintf_((char*)angleX_Buff, sizeof(angleX_Buff), "%.1f°",
						sbgcDegreeToAngle(Gimbal.DataStreamStruct.frameCamAngle[
								Gimbal.GetActiveControlProfile()->controlHandler[JOY_X].attachedAxis]));
				gwinSetText(ghLabelAngleX, (const char*)angleX_Buff, FALSE);
			}

			else
				gwinSetText(ghLabelAngleX, "-", FALSE);

			if (Gimbal.GetActiveControlProfile()->controlHandler[JOY_Y].attachedAxis != NOT_ASSIGNED)
			{
				snprintf_((char*)angleY_Buff, sizeof(angleY_Buff), "%.1f°",
						sbgcDegreeToAngle(Gimbal.DataStreamStruct.frameCamAngle[
								Gimbal.GetActiveControlProfile()->controlHandler[JOY_Y].attachedAxis]));
				gwinSetText(ghLabelAngleY, (const char*)angleY_Buff, FALSE);
			}

			else
				gwinSetText(ghLabelAngleY, "-", FALSE);

			if (Gimbal.GetActiveControlProfile()->controlHandler[POT].attachedAxis != NOT_ASSIGNED)
			{
				snprintf_((char*)angleC_Buff, sizeof(angleC_Buff), "%.1f°",
						sbgcDegreeToAngle(Gimbal.DataStreamStruct.frameCamAngle[
								Gimbal.GetActiveControlProfile()->controlHandler[POT].attachedAxis]));
				gwinSetText(ghLabelAngleP, (const char*)angleC_Buff, FALSE);
			}

			else
				gwinSetText(ghLabelAngleP, "-", FALSE);

			lastRealTimeDataTime = osGetTickCount();
		}

		/* Sensitivity adjust */
		if (incrementalCounter != incrementalCounterOld)
		{
			currentSensAdjState = sensAdjStateTemp;
			sensAdjStateTemp = CSA_NO;

			if (currentSensAdjState == CSA_NO)  // First enter
				currentSensAdjState = CSA_AXIS_X;

			if ((incrementalCounter == 16383) && (incrementalCounterOld == 0))
				incrementalCounterDelta = (0) ? INCREMENTAL_ENCODER_LOGIC;

			else if ((incrementalCounterOld == 16383) && (incrementalCounter == 0))
				incrementalCounterDelta = (1) ? INCREMENTAL_ENCODER_LOGIC;

			else
				incrementalCounterDelta = (incrementalCounter > incrementalCounterOld) ? INCREMENTAL_ENCODER_LOGIC;

			Gimbal.GetActiveControlProfile()->controlHandler[currentSensAdjState - 1].sensitivity =
					constrain_(Gimbal.GetActiveControlProfile()->controlHandler[currentSensAdjState - 1].sensitivity +
							incrementalCounterDelta, SBGC_CONTROL_SENS_MIN_VALUE, SBGC_CONTROL_SENS_MAX_VALUE);
		}

		if (controlSenseToggleButton == BS_PRESSED)
		{
			/* Save old parameter */
			SettingsLoader.SaveGimbalParameter(&Gimbal.GetActiveControlProfile()->controlHandler[currentSensAdjState - 1].sensitivity);

			currentSensAdjState = (ControlSensAdj_t)((currentSensAdjState + 1) & SBGC_CONTROL_HANDLERS_NUM);
			sensAdjStateTemp = CSA_NO;

			if (currentSensAdjState == CSA_NO)
				currentSensAdjState = CSA_AXIS_X;
		}

		if ((currentSensAdjState != sensAdjStateTemp) &&
			(currentSensAdjState != CSA_NO))
		{
			switch (currentSensAdjState)
			{
				case CSA_AXIS_X :
					snprintf_((char*)controlSensAdjBuff, sizeof(controlSensAdjBuff), "%cX: %d",
							  Gimbal.GetActiveControlProfile()->controlHandler[JOY_X].invert ? '-' : ' ',
							  Gimbal.GetActiveControlProfile()->controlHandler[JOY_X].sensitivity);
					break;

				case CSA_AXIS_Y :
					snprintf_((char*)controlSensAdjBuff, sizeof(controlSensAdjBuff), "%cY: %d",
							  Gimbal.GetActiveControlProfile()->controlHandler[JOY_Y].invert ? '-' : ' ',
							  Gimbal.GetActiveControlProfile()->controlHandler[JOY_Y].sensitivity);
					break;

				case CSA_AXIS_P :
					snprintf_((char*)controlSensAdjBuff, sizeof(controlSensAdjBuff), "%cP: %d",
							  Gimbal.GetActiveControlProfile()->controlHandler[POT].invert ? '-' : ' ',
							  Gimbal.GetActiveControlProfile()->controlHandler[POT].sensitivity);
					break;

				default :
					break;
			}

			sensAdjStateTemp = currentSensAdjState;
			controlSensLastTime = osGetTickCount();

			gwinSetText(ghLabelControlSens, (const char*)controlSensAdjBuff, FALSE);

			gwinShow(ghLabelControlSens);
		}

		if (incrementalCounterOld != incrementalCounter)
			controlSensLastTime = osGetTickCount();

		if ((osGetTickCount() - controlSensLastTime) > CONTROL_SENS_ADJ_TIMEOUT &&
			(currentSensAdjState != CSA_NO))
		{
			/* Save parameter */
			SettingsLoader.SaveGimbalParameter(&Gimbal.GetActiveControlProfile()->controlHandler[currentSensAdjState - 1].sensitivity);

			sensAdjStateTemp = currentSensAdjState;
			currentSensAdjState = CSA_NO;
			gwinHide(ghLabelControlSens);
		}

		/* Control Part */
		if (((osGetTickCount() - lastControlTime) > CONTROL_UPDATE_TIME) &&
			SBGC_ControlApprovedStateMask(Gimbal.GetCurrentState()))
		{
			lastControlTime = osGetTickCount();

			if (SBGC_ControlStateMask(Gimbal.GetCurrentState()))
			{
				RewriteControlValues();
				Gimbal.ControlGimbal(SCParam_NO, SCPrior_HIGH, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);
			}
		}

		/* Draw progressbars */
		if ((deadbandcross_(xRes, IN_MIDDLE_VALUE, CONTROL_AXIS_X_DEADBAND)) ||
			(deadbandcross_(yRes, IN_MIDDLE_VALUE, CONTROL_AXIS_Y_DEADBAND)) ||
			firstTimeShowing)
		{
			pwmResX = (xRes / 65535.) * CONTROL_PROGRESSBAR_RESOLUTION;
			pwmResY = (yRes / 65535.) * CONTROL_PROGRESSBAR_RESOLUTION;

			if (gwinProgressbarGetPosition(ghProgressbarX) != pwmResX)
				gwinProgressbarSetPosition(ghProgressbarX, pwmResX);

			if (gwinProgressbarGetPosition(ghProgressbarY) != pwmResY)
				gwinProgressbarSetPosition(ghProgressbarY, pwmResY);
		}

		/* Draw pot's circle */
		if (deadbandcross_(pRes, pResOld, CONTROL_POT_DEADBAND) ||
			firstTimeShowing)
		{
			gdispFillCircle(CONTROL_CIRCLE_COORD_X, CONTROL_CIRCLE_COORD_Y,
							CONTROL_CIRCLE_RADIUS - CONTROL_CIRCLE_THICK - 1, GFX_BLACK);

			DrawPotentiometerArrow(CONTROL_CIRCLE_COORD_X, CONTROL_CIRCLE_COORD_Y,
								   CONTROL_CIRCLE_RADIUS - CONTROL_CIRCLE_THICK - 2,
								   ConvertPotentiometerValueToAngle(pRes), GFX_LIGHT_GRAY);
		}

		if (firstTimeShowing)
			firstTimeShowing = sbgcFALSE;


		/* System awaking */
		MiniRemote.UpdateLastResponseTime();

		osDelay(CONTROL_CONTAINER_PROCESS_DELAY);
	}
}
