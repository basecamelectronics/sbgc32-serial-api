/** ____________________________________________________________________
 *
 *	@file		MessageWindowContainerM.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "createWidget.h"


MessageWindowDialogAnswer_t dialogAnswer = MWDA_CLEANED;

extern ui32 lastAutoTuneTime;
extern volatile bool PID_AutoTuneFinishFlag;


void CMessageWindowContainerM::Init (void)
{
	static GWidgetInit wi;
	gwinWidgetClearInit(&wi);

	gdispImage *imageBuff;

	/* Container */
	wi.g.show = FALSE;
	wi.g.x = 0;
	wi.g.y = 0;
	wi.g.width = gdispGetWidth();
	wi.g.height = gdispGetHeight();
	ghContainer = gwinContainerCreate(0, &wi, 0);
	wi.g.show = TRUE;
	wi.g.parent = ghContainer;

	/* Return arrow (calibration state only) */
	Utils::imageOpenFile(imageBuff, imagePathsReferenceArray[IPR_ARROW_RETURN_LEFT]);
	wi.g.x = 0;
	wi.g.y = 0;
	wi.g.height = imageBuff->height;
	wi.g.width = imageBuff->width;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
	wi.customDraw = gwinImageWOpenAndDrawCustom_Mono;
	wi.customParam = (void*)imagePathsReferenceArray[IPR_ARROW_RETURN_LEFT];
	ghImageReturn = gwinImageWCreate(0, &wi);
	Utils::imageCloseFile(imageBuff);

	/* Progressbar */
	wi.g.width = ghContainer->width;
	wi.g.height = 6;
	wi.g.x = 0;
	wi.g.y = ghContainer->height - wi.g.height;
	wi.text = 0;
	wi.customParam = 0;
	wi.customDraw = gwinProgressbarDrawCustom_Mono;
	wi.customStyle = &CWidgetStyle::MonoProgressbarStyle;
	ghProgressbar = gwinProgressbarCreate(0, &wi);

	gwinHide(ghProgressbar);
	gwinHide(ghImageReturn);
}


void CMessageWindowContainerM::OnHide (void)
{
	;
}


void CMessageWindowContainerM::vTask (void *pvParameters)
{
	unused_(pvParameters);

	font_t currentFont;

	gwinShow(ghContainer);

	switch (font)
	{
		case MW_SMALL_FONT :
			currentFont = MiniRemote.GetSmallFont();
			break;

		case MW_MEDIUM_FONT :
			currentFont = MiniRemote.GetMediumFont();
			break;

		case MW_LARGE_FONT :
			currentFont = MiniRemote.GetLargeFont();
			break;
	}


	while (1)
	{
		switch (currentState)
		{
			case MW_NOTE_STATE :
				gdispFillStringBoxSimple(MESSAGE_WINDOW_MARGINS, MESSAGE_WINDOW_MARGINS,
										 ghContainer->width - (MESSAGE_WINDOW_MARGINS * 2), ghContainer->height - (MESSAGE_WINDOW_MARGINS * 2),
										 message, currentFont, GFX_LIGHT_GRAY, GFX_BLACK,
										 (gJustify)(gJustifyCenter | gJustifyMiddle));

				osDelay(timeout);
				ClearMessage();
				CStateManager::SetState({ PREVIOUS_STATE, 0 });
				while (1);
				break;

			case MW_DIALOG_STATE :
			{
				gdispFillStringBoxSimple(MESSAGE_WINDOW_MARGINS, (ghContainer->height / 2) - MESSAGE_WINDOW_DIALOG_CLEARANCE - 2,
										 ghContainer->width - (MESSAGE_WINDOW_MARGINS * 2), LARGE_FONT_HEIGHT,
										 message, currentFont, GFX_LIGHT_GRAY, GFX_BLACK,
										 (gJustify)(gJustifyCenter | gJustifyMiddle));

				/* Choice boxes */
				if (dialogAnswer == MWDA_YES)
				{
					gdispFillStringBox((ghContainer->width / 2) - MESSAGE_WINDOW_DIALOG_BOX_W, (ghContainer->height / 2) +
									   	   	   MESSAGE_WINDOW_DIALOG_CLEARANCE,
									   MESSAGE_WINDOW_DIALOG_BOX_W, MESSAGE_WINDOW_DIALOG_BOX_H,
									   "Yes", currentFont, GFX_BLACK, GFX_LIGHT_GRAY,
									   (gJustify)(gJustifyCenter | gJustifyMiddle));

					gdispFillStringBox((ghContainer->width / 2), (ghContainer->height / 2) + MESSAGE_WINDOW_DIALOG_CLEARANCE,
									   MESSAGE_WINDOW_DIALOG_BOX_W, MESSAGE_WINDOW_DIALOG_BOX_H,
									   "No", currentFont, GFX_LIGHT_GRAY, GFX_BLACK,
									   (gJustify)(gJustifyCenter | gJustifyMiddle));
				}

				else
				{
					gdispFillStringBox((ghContainer->width / 2) - MESSAGE_WINDOW_DIALOG_BOX_W, (ghContainer->height / 2) +
												MESSAGE_WINDOW_DIALOG_CLEARANCE,
									   MESSAGE_WINDOW_DIALOG_BOX_W, MESSAGE_WINDOW_DIALOG_BOX_H,
									   "Yes", currentFont, GFX_LIGHT_GRAY, GFX_BLACK,
									   (gJustify)(gJustifyCenter | gJustifyMiddle));

					gdispFillStringBox((ghContainer->width / 2), (ghContainer->height / 2) + MESSAGE_WINDOW_DIALOG_CLEARANCE,
									   MESSAGE_WINDOW_DIALOG_BOX_W, MESSAGE_WINDOW_DIALOG_BOX_H,
									   "No", currentFont, GFX_BLACK, GFX_LIGHT_GRAY,
									   (gJustify)(gJustifyCenter | gJustifyMiddle));
				}

				NavigationDirection_t nav;
				ButtonState_t enterButton = BS_INIT;

				TickType_t xNavigationBlockTime = osGetTickCount();
				while (osGetTickCount() < (xNavigationBlockTime + NAVIGATION_INIT_BLOCK_TIME));

				while (1)
				{
					/* Navigation handle */
					MiniRemote.ProcessNavigationDirection();
					nav = MiniRemote.GetNavigationDirection();
					MiniRemote.ProcessFunction(CSF_NAVIGATION_ENTER, &enterButton);

					if (nav == ND_RIGHT)
					{
						dialogAnswer = MWDA_NO;

						gdispFillStringBox((ghContainer->width / 2) - MESSAGE_WINDOW_DIALOG_BOX_W, (ghContainer->height / 2) +
										   	   	   MESSAGE_WINDOW_DIALOG_CLEARANCE,
										   MESSAGE_WINDOW_DIALOG_BOX_W, MESSAGE_WINDOW_DIALOG_BOX_H,
										   "Yes", currentFont, GFX_LIGHT_GRAY, GFX_BLACK,
										   (gJustify)(gJustifyCenter | gJustifyMiddle));

						gdispFillStringBox((ghContainer->width / 2), (ghContainer->height / 2) + MESSAGE_WINDOW_DIALOG_CLEARANCE,
										   MESSAGE_WINDOW_DIALOG_BOX_W, MESSAGE_WINDOW_DIALOG_BOX_H,
										   "No", currentFont, GFX_BLACK, GFX_LIGHT_GRAY,
										   (gJustify)(gJustifyCenter | gJustifyMiddle));
					}

					if (nav == ND_LEFT)
					{
						dialogAnswer = MWDA_YES;

						gdispFillStringBox((ghContainer->width / 2) - MESSAGE_WINDOW_DIALOG_BOX_W, (ghContainer->height / 2) +
										   	   	   MESSAGE_WINDOW_DIALOG_CLEARANCE,
										   MESSAGE_WINDOW_DIALOG_BOX_W, MESSAGE_WINDOW_DIALOG_BOX_H,
										   "Yes", currentFont, GFX_BLACK, GFX_LIGHT_GRAY,
										   (gJustify)(gJustifyCenter | gJustifyMiddle));

						gdispFillStringBox((ghContainer->width / 2), (ghContainer->height / 2) + MESSAGE_WINDOW_DIALOG_CLEARANCE,
										   MESSAGE_WINDOW_DIALOG_BOX_W, MESSAGE_WINDOW_DIALOG_BOX_H,
										   "No", currentFont, GFX_LIGHT_GRAY, GFX_BLACK,
										   (gJustify)(gJustifyCenter | gJustifyMiddle));
					}

					/* Exit */
					if (enterButton == BS_PRESSED)
					{
						ClearMessage();
						CStateManager::SetState({ PREVIOUS_STATE, 0 });
						while (1);
					}


					osDelay(CONTAINER_PROCESS_DELAY);
				}

				break;
			}

			case MW_GIMBAL_ACC_CALIB_STATE :
			{
				GHandle	ghLabelCalibration;

				GWidgetInit wi;
				gwinWidgetClearInit(&wi);

				wi.g.width = DISPLAY_WIDTH - (MESSAGE_WINDOW_MARGINS * 2);
				wi.g.height = MEDIUM_FONT_HEIGHT;
				wi.g.x = MESSAGE_WINDOW_MARGINS;
				wi.g.y = MESSAGE_WINDOW_MARGINS + WIDGET_IMAGE_SIZE + (MEDIUM_FONT_HEIGHT * 2) + 8;
				wi.text = "";
				wi.customStyle = &CWidgetStyle::MonoImgStyleLabelNormal;
				wi.customParam = (void*)justifyCenter;
				wi.customDraw = gwinLabelDrawJustifiedCustomMono;
				ghLabelCalibration = gwinLabelCreate(0, &wi);
				gwinShow(ghLabelCalibration);

				gwinProgressbarSetPosition(ghProgressbar, 0);
				gwinHide(ghProgressbar);
				gwinShow(ghImageReturn);

				gdispFillStringBoxSimple(MESSAGE_WINDOW_MARGINS, MESSAGE_WINDOW_MARGINS + WIDGET_IMAGE_SIZE,
										 ghContainer->width - (MESSAGE_WINDOW_MARGINS * 2),
										 MEDIUM_FONT_HEIGHT * 2 + 4,
										 (char*)"Align the gimbal on one of the axes ", currentFont, GFX_GRAY, GFX_BLACK,
										 (gJustify)(gJustifyCenter | gJustifyMiddle));

				char calibrationStarts [30];
				ui8 calibrationT_Minus = MESSAGE_WINDOW_CALIB_DURATION;
				ui32 timestamp = 0;

				NavigationDirection_t nav;
				ButtonState_t exitButton = BS_INIT;

				while (1)
				{
					/* Navigation handle */
					MiniRemote.ProcessNavigationDirection();
					nav = MiniRemote.GetNavigationDirection();
					MiniRemote.ProcessFunction(CSF_NAVIGATION_EXIT, &exitButton);

					/* Exit */
					if ((nav == ND_LEFT) || (exitButton == BS_PRESSED))
					{
						gwinHide(ghProgressbar);
						gwinHide(ghImageReturn);
						osDelay(10);
						break;
					}

					if (osGetTickCount() - timestamp > 1000)
					{
						if (!calibrationT_Minus)
							break;

						sprintf_(calibrationStarts, "Calib. starts at %d...", calibrationT_Minus);
						gwinSetText(ghLabelCalibration, calibrationStarts, FALSE);

						calibrationT_Minus--;
						timestamp = osGetTickCount();
					}
				}

				/* Doing calibration */
				Gimbal.CalibAcc();

				if (Gimbal.GetCommunicationState())
				{
					Gimbal.AddCurrentState(SBGC_CALIBRATE_IMU);
					Gimbal.processStatus = PROCESS_STARTED;
				}

				else
					exCShortcutContainerM.TurnOnAllShortcuts();

				gwinHide(ghProgressbar);
				gwinHide(ghImageReturn);
				osDelay(10);
				CStateManager::SetState({ PREVIOUS_STATE, 0 });
				while (1);

				break;
			}

			case MW_GIMBAL_GYRO_CALIB_STATE :
			case MW_GIMBAL_PID_TUNE_STATE :
			{
				ui32 lastCalibInfoTime = false;
				ui32 calibrationExitTimeout = osGetTickCount();

				gwinProgressbarSetPosition(ghProgressbar, 0);
				gwinHide(ghProgressbar);
				gwinShow(ghImageReturn);

				gdispFillStringBoxSimple(MESSAGE_WINDOW_MARGINS + WIDGET_IMAGE_SIZE, MESSAGE_WINDOW_MARGINS + WIDGET_IMAGE_SIZE - 6,
										 ghContainer->width - (MESSAGE_WINDOW_MARGINS * 2) - (WIDGET_IMAGE_SIZE * 2), ghContainer->height -
										 (MESSAGE_WINDOW_MARGINS * 2) - (WIDGET_IMAGE_SIZE * 2) + 12,
										 message, currentFont, GFX_LIGHT_GRAY, GFX_BLACK,
										 (gJustify)(gJustifyCenter | gJustifyMiddle));

				NavigationDirection_t nav;
				ButtonState_t exitButton = BS_INIT;

				TickType_t xNavigationBlockTime = osGetTickCount();
				while (osGetTickCount() < (xNavigationBlockTime + NAVIGATION_INIT_BLOCK_TIME));

				while (1)
				{
					/* Navigation handle */
					MiniRemote.ProcessNavigationDirection();
					nav = MiniRemote.GetNavigationDirection();

					/* Exit */
					if ((nav == ND_LEFT) || (exitButton == BS_PRESSED))
					{
						gwinHide(ghProgressbar);
						osDelay(10);
						CStateManager::SetState({ PREVIOUS_STATE, 0 });
						while (1);
					}

					/* Auto PID finish handle */
					if ((Gimbal.GetCurrentState() & SBGC_PID_AUTOTUNE) &&
						(PID_AutoTuneFinishFlag || ((osGetTickCount() - lastAutoTuneTime) > (AUTO_PID_TIMEOUT * 1000))))
					{
						gwinHide(ghProgressbar);
						gwinHide(ghImageReturn);
						osDelay(10);
						CStateManager::SetState({ PREVIOUS_STATE, 0 });
						while (1);
					}

					/* Calib Info handle */
					if (((osGetTickCount() - lastCalibInfoTime) > CALIB_INFO_UPDATE_TIME) &&
						(SBGC_CalibrationStateMask(Gimbal.GetCurrentState())) &&
						PID_AutoTuneFinishFlag)  // It's not PID calibration
					{
						Gimbal.RequestCalibInfo(SBGC_TARGET_IMU);

						if (Gimbal.GetCommunicationState())
							lastCalibInfoTime = osGetTickCount();
					}

					if (gwinProgressbarGetPosition(ghProgressbar) != Gimbal.GetAddressCalibInfo()->progress)
					{
						gwinProgressbarSetPosition(ghProgressbar, Gimbal.GetAddressCalibInfo()->progress);

						if (Gimbal.GetAddressCalibInfo()->progress)
						{
							if (Gimbal.processStatus == PROCESS_FINISHED)  // If calibration was interrupted
							{
								Gimbal.AddCurrentState(SBGC_CALIBRATE_IMU);
								Gimbal.processStatus = PROCESS_STARTED;
							}

							gwinShow(ghProgressbar);
						}

						else  // Calibration finished or broke
						{
							SerialCommand_t cmd;
							ClearCmd(&cmd);

							Gimbal.FindCommand(&cmd, CMD_CONFIRM, SBGC_REQ_WAITING);

							if (cmd.commandID == CMD_CONFIRM)  // Calibration is finished successfully
							{
								gwinHide(ghProgressbar);
								osDelay(10);
								Gimbal.ClearCurrentState(SBGC_CALIBRATE_IMU);
								Gimbal.processStatus = PROCESS_FINISHED;
								CStateManager::SetState({ PREVIOUS_STATE, 0 });
								while (1);
							}
						}

						Gimbal.ReadRealTimeData();  // Getting real-time data for motors state info

						calibrationExitTimeout = osGetTickCount();
					}

					if (((osGetTickCount() - calibrationExitTimeout) > CALIBRATION_TIMEOUT_WAITING) &&
						(SBGC_CalibrationStateMask(Gimbal.GetCurrentState())))
					{
						gwinHide(ghProgressbar);
						osDelay(10);
						Gimbal.ClearCurrentState(SBGC_CALIBRATE_IMU);
						Gimbal.processStatus = PROCESS_FINISHED;
						CStateManager::SetState({ PREVIOUS_STATE, 0 });
						while (1);
					}


					/* Disconnection handle */
					if (SBGC_NoConnectionStateMask(Gimbal.GetCurrentState()))
					{
						gwinHide(ghProgressbar);
						gwinHide(ghImageReturn);
						osDelay(10);
						SetCurrentState(MW_NOTE_STATE);
						MiniRemote.SetDisconnectionMessageState(DM_SHOWED);
						SetMessage(TEXT_SIZE_("Connection is lost"), MW_NOTE_STATE, MW_MEDIUM_FONT, SHOW_MESSAGE_TIME);
						break;
					}

					osDelay(CONTAINER_PROCESS_DELAY);
				}

				break;
			}

			case MW_GIMBAL_INIT_OK_STATE :
			{
				char	boardVersionStr [4],
						firmwareVersionStr [7],
						curProfileStr [2],

						totalBuff [100];

				FormatBoardVersion(Gimbal.GetAddressGeneralSBGC(),
								   Gimbal.GetAddressGeneralSBGC()->_boardVersion, boardVersionStr);
				FormatFirmwareVersion(Gimbal.GetAddressGeneralSBGC(),
									  Gimbal.GetAddressGeneralSBGC()->_firmwareVersion, firmwareVersionStr);
				Gimbal.GetAddressGeneralSBGC()->SprintfFunc
				(curProfileStr, "%u", (Gimbal.GetAddressRealTimeData()->curProfile + 1));

				sprintf_(totalBuff,
						 "SBGC32 connected!\nBoard version: %s\nFrw. version: %s\nCurrent profile: %s ",  // Space is necessary here
						 boardVersionStr, firmwareVersionStr, curProfileStr);

				gdispFillStringBoxSimple(MESSAGE_WINDOW_MARGINS, MESSAGE_WINDOW_MARGINS,
										 ghContainer->width - (MESSAGE_WINDOW_MARGINS * 2), ghContainer->height - (MESSAGE_WINDOW_MARGINS * 2),
										 totalBuff, currentFont, GFX_LIGHT_GRAY, GFX_BLACK,
										 (gJustify)(gJustifyLeft | gJustifyMiddle));

				osDelay(timeout);
				gwinClear(ghContainer);
				CStateManager::SetState({ PREVIOUS_STATE, 0 });
				while (1);
				break;
			}
		}
	}
}


void CMessageWindowContainerM::SetMessage (const char *message, ui8 messageLength, MessageWindowState_t messageType,
										   MessageWindowFont_t messageFont, ui32 messageTime)
{
	messageLength += 2;
	this->message = (char*)osMalloc(messageLength);
	memcpy(this->message, message, messageLength - 2);
	this->message[messageLength - 2] = ' ';  // For correct word-wrapping
	this->message[messageLength - 1] = '\0';  // For correct word-wrapping

	currentState = messageType;
	font = messageFont;
	timeout = messageTime;
}


void CMessageWindowContainerM::ClearMessage (void)
{
	gwinClear(ghContainer);
	osFree(this->message);
}

