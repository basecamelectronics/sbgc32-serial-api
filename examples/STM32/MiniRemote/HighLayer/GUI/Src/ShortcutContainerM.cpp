/** ____________________________________________________________________
 *
 *	@file		ShortcutContainerM.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "createWidget.h"
#include "gimbal.h"


ShortcutParameters_t shortcutParametersReferenceArray [] =
	/*
	||		  SHORTCUT		 || # || 	STATUS	  ||				IMAGE PATH					||		 TEXT	  ||
	 */
	{ {	SHORTCUT_GYRO_CALIB,	0,	SCS_NORMAL,		imagePathsReferenceArray[IPR_GYRO_CALIB],		"Gyro Calib"
	},{	SHORTCUT_ACC_CALIB,		1,	SCS_NORMAL,		imagePathsReferenceArray[IPR_ACC_CALIB],		"ACC Calib"
	},{	SHORTCUT_MOTOR_SWITCH,	2,	SCS_NORMAL,		imagePathsReferenceArray[IPR_MOTORS_SWITCH],	"Motors ON/OFF"
	},{	SHORTCUT_AUTO_PID,		3,	SCS_NORMAL,		imagePathsReferenceArray[IPR_AUTO_PID],			"Auto PID"
	},{	SHORTCUT_RESET,			4,	SCS_NORMAL,		imagePathsReferenceArray[IPR_RESET],			"Restart"
	},{	SHORTCUT_SCRIPT_1,		5,	SCS_NORMAL,		imagePathsReferenceArray[IPR_SCRIPT_1],			"Script 1"
	},{	SHORTCUT_SCRIPT_2,		6,	SCS_NORMAL,		imagePathsReferenceArray[IPR_SCRIPT_2],			"Script 2"
	},{	SHORTCUT_SCRIPT_3,		7,	SCS_NORMAL,		imagePathsReferenceArray[IPR_SCRIPT_3],			"Script 3"
	},{	SHORTCUT_SCRIPT_4,		8,	SCS_NORMAL,		imagePathsReferenceArray[IPR_SCRIPT_4],			"Script 4"
	},{	SHORTCUT_SCRIPT_5,		9,	SCS_NORMAL,		imagePathsReferenceArray[IPR_SCRIPT_5],			"Script 5"

	}};


static ui32 lastCalibInfoTime = 0;

ui32 lastAutoTuneTime = 0;
static TaskHandle_t TaskPID_AutoTuneFinishCheckHandle = NULL;
volatile bool PID_AutoTuneFinishFlag = true;

static ui32 lastResetTime = 0;

static TaskHandle_t TaskScriptExeFinishWaitHandle = NULL;
static volatile bool ScriptExeFinishFlag = true;


void CShortcutContainerM::Init (void)
{
	GWidgetStyle *pstyle;
	gdispImage *imageBuff;

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

	/* Title label */
	wi.g.width = DISPLAY_WIDTH - (WIDGET_IMAGE_SIZE * 2);
	wi.g.height = LARGE_FONT_HEIGHT;
	wi.g.x = WIDGET_IMAGE_SIZE;
	wi.g.y = 0;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
	wi.customParam = (void*)justifyCenter;
	wi.customDraw = gwinLabelDrawJustifiedCustomMono;
	ghLabelSelect = gwinLabelCreate(0, &wi);

	/* Return arrow */
	Utils::imageOpenFile(imageBuff, imagePathsReferenceArray[IPR_ARROW_RETURN_UP]);
	wi.g.x = 0;
	wi.g.y = 0;
	wi.g.height = imageBuff->height;
	wi.g.width = imageBuff->width;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
	wi.customDraw = gwinImageWOpenAndDrawCustom_Mono;
	wi.customParam = (void*)imagePathsReferenceArray[IPR_ARROW_RETURN_UP];
	ghImageReturn = gwinImageWCreate(0, &wi);
	Utils::imageCloseFile(imageBuff);

	/* Shortcuts */
	ui8 strlenTemp;

	for (ui8 i = 0; i < SHORTCUT_TOTAL_NUM; i++)
	{
		shortcut[i].number = shortcutParametersReferenceArray[i].number;
		shortcut[i].currentPosition = shortcutParametersReferenceArray[i].currentPosition;
		shortcut[i].status = shortcutParametersReferenceArray[i].status;

		strlenTemp = strlen(shortcutParametersReferenceArray[i].name) + 1;
		shortcut[i].name = (char*)osMalloc(strlenTemp);
		memcpy((void*)shortcut[i].name, shortcutParametersReferenceArray[i].name, strlenTemp);

		strlenTemp = strlen(shortcutParametersReferenceArray[i].imagePath) + 1;
		shortcut[i].imagePath = (char*)osMalloc(strlenTemp);
		memcpy((void*)shortcut[i].imagePath, shortcutParametersReferenceArray[i].imagePath, strlenTemp);
	}

	ui8 xCoordPointer = SIDE_ARROW_IMAGE_WIDTH + SIDE_ARROW_IMAGE_CLEARANCE;

	/* Pre-loading */
	for (ui8 i = 0; i < INITIAL_SHORTCUT_NUM; i++)
		for (ui8 k = 0; k < SHORTCUT_TOTAL_NUM; k++)
			if (shortcut[k].currentPosition == i)
			{
				Utils::imageOpenFile(imageBuff, shortcut[k].imagePath);
				wi.g.x = xCoordPointer;
				wi.g.y = SHORTCUT_IMAGE_Y_POS;
				wi.g.height = imageBuff->height;
				wi.g.width = imageBuff->width;
				wi.text = "";

				if (shortcut[k].status & SCS_ACTIVE)
					pstyle = (!invertionTemp ? &CWidgetStyle::MonoImgStyleNormal : &CWidgetStyle::MonoImgStyleInvert);

				else if (shortcut[k].status & SCS_NOT_ACTIVE)
					pstyle = &CWidgetStyle::MonoImgStyleInactive;

				else if (shortcut[k].status & SCS_TURNED_ON)
					pstyle = &CWidgetStyle::MonoImgStyleInvert;

				else
					pstyle = &CWidgetStyle::MonoImgStyleNormal;

				wi.customStyle = pstyle;

				wi.customDraw = gwinImageWOpenAndDrawCustom_Mono;
				wi.customParam = (void*)shortcut[k].imagePath;
				ghImageShortcut[i] = gwinImageWCreate(0, &wi);
				Utils::imageCloseFile(imageBuff);

				xCoordPointer += SHORTCUT_X_STEP;
			}

	/* Down arrow */
	Utils::imageOpenFile(imageBuff, imagePathsReferenceArray[IPR_ARROW_DOWN]);
	wi.g.x = (DISPLAY_WIDTH / 2) - (SELECT_ARROW_SIZE / 2) - 1;
	wi.g.y = SELECT_SC_ARROW_Y_POS;
	wi.g.height = imageBuff->height;
	wi.g.width = imageBuff->width;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
	wi.customDraw = gwinImageWOpenAndDrawCustom_Mono;
	wi.customParam = (void*)imagePathsReferenceArray[IPR_ARROW_DOWN];
	ghImageArrow = gwinImageWCreate(0, &wi);
	Utils::imageCloseFile(imageBuff);

	/* Profiles */
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
	wi.g.x = 0;
	wi.customParam = (void*)justifyCenter;

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

	/* Variables init */
	currentPosition = ((ui8)(INITIAL_SHORTCUT_NUM / 2));
	displayPosition = currentPosition;

	displayTimestamp = 0;
	invertionTemp = 0;
}


void CShortcutContainerM::OnHide (void)
{
	;
}


void CShortcutContainerM::vTask (void *pvParameters)
{
	unused_(pvParameters);

	ui32 calibrationExitTimeout = osGetTickCount();

	static ui8 currentPositionTemp = 0xFF;
	static ShortcutCurrentStatus_t shortcutCurrentStatusTempArray [SHORTCUT_TOTAL_NUM];  // for replacing effects

	static Boolean_t needReturnShortcutStatusesFlag = FALSE__;

	/* Initialization container by communication parameters */
	CommunicationInit();
	DisplayShortcutInit();

	/* Draw container */
	gwinShow(ghContainer);

	/* Side arrows init */
	SideArrowsHandle();


	NavigationDirection_t nav;
	ButtonState_t enterButton = BS_INIT;
	ButtonState_t exitButton = BS_INIT;

	TickType_t xNavigationBlockTime = osGetTickCount();
	while (osGetTickCount() < (xNavigationBlockTime + NAVIGATION_INIT_BLOCK_TIME));

	while (1)
	{
		/* Inputs handle */
		MiniRemote.ProcessNavigationDirection();
		nav =  MiniRemote.GetNavigationDirection();
		MiniRemote.ProcessFunction(CSF_NAVIGATION_ENTER, &enterButton);
		MiniRemote.ProcessFunction(CSF_NAVIGATION_EXIT, &exitButton);

		/* State swapping */
		if (enterButton == BS_CONTINUOUS)
		{
			if (!containerStatus)
			{
				/* SCS_NOT_ACTIVE state while replacing */
				for (ui8 i = 0; i < SHORTCUT_TOTAL_NUM; i++)
				{
					shortcutCurrentStatusTempArray[i] = shortcut[i].status;
					SetStatusAndTrigger(&shortcut[i], SCS_NOT_ACTIVE);
				}

				SetStatusAndTrigger(FindCurrentShortcut(), SCS_MOVED);

				containerStatus = !containerStatus;
			}

			else
			{
				for (ui8 i = 0; i < SHORTCUT_TOTAL_NUM; i++)
				{
					shortcut[i].status = shortcutCurrentStatusTempArray[i];  // Return to old states
					SetTriggerFlag(&shortcut[i]);

					/* Saving an order at exit */
					MiniRemote.Presets.shortcutsOrderArr[i] = (ShortcutList_t)shortcut[i].currentPosition;
				}

				containerStatus = !containerStatus;
			}

			enterButton = BS_BLOCKED;
		}

		/* Exit case */
		if ((nav == ND_UP) || (exitButton == BS_PRESSED))
		{
			CStateManager::SetState({ PREVIOUS_STATE, 0 });  // Exit
			while (1);
		}


		/* SBGC32 Execution. Launch if gimbal is idle (normal state) */
		if ((nav == ND_DOWN) && (!containerStatus) &&
			!SBGC_NoConnectionStateMask(Gimbal.GetCurrentState()) &&

			((Gimbal.processStatus != PROCESS_STARTED) ||
			(IsScriptShortcut(FindActiveShortcut()) || (FindActiveShortcut()->number == SHORTCUT_RESET))))
			/* Finding and executing assigned shortcut */
			ExecuteShortcutAssignedFunction(FindCurrentShortcut());

		if ((Gimbal.processStatus == PROCESS_FINISHED) ||
			needReturnShortcutStatusesFlag)
		{
			if (Gimbal.processStatus == PROCESS_FINISHED)
				Gimbal.processStatus = PROCESS_READY;

			if (containerStatus)
				needReturnShortcutStatusesFlag = TRUE__;

			else
				/* Shortcuts don't replacing anymore */
			{
				TurnOnAllShortcuts();
				SetStatusAndTrigger(FindActiveShortcut(), SCS_NORMAL);
				needReturnShortcutStatusesFlag = FALSE__;
			}
		}


		/* Navigation */
		if ((nav == ND_LEFT) || (nav == (ND_LEFT | ND_CONTINUOUS)))
			if (currentPosition)
				LeftScroll();

		if ((nav == ND_RIGHT) || (nav == (ND_RIGHT | ND_CONTINUOUS)))
			if (currentPosition < (SHORTCUT_TOTAL_NUM - 1))
				RightScroll();


		/* Side arrows handle */
		SideArrowsHandle();


		/* Text label */
		if (currentPositionTemp != currentPosition)
		{
			gwinSetText(ghLabelSelect, FindCurrentShortcut()->name, FALSE);
			currentPositionTemp = currentPosition;
		}


		/* Process shortcuts effects */
		ShortcutLengthProcess();


		/* Calib Info handle */
		if (((osGetTickCount() - lastCalibInfoTime) > CALIB_INFO_UPDATE_TIME) &&
			SBGC_CalibrationStateMask(Gimbal.GetCurrentState()))
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
				Gimbal.FindCommand(&cmd, CMD_CONFIRM, SBGC_REQ_WAITING);

				if (cmd.commandID == CMD_CONFIRM)  // Calibration is finished successfully
				{
					Gimbal.ClearCurrentState(SBGC_CALIBRATE_IMU);
					gwinHide(ghProgressbar);
					Gimbal.processStatus = PROCESS_FINISHED;
				}

				CommunicationInit();
			}

			calibrationExitTimeout = osGetTickCount();
		}

		if (((osGetTickCount() - calibrationExitTimeout) > CALIBRATION_TIMEOUT_WAITING) &&
			(SBGC_CalibrationStateMask(Gimbal.GetCurrentState())))
		{
			Gimbal.ClearCurrentState(SBGC_CALIBRATE_IMU);
			gwinHide(ghProgressbar);
			Gimbal.processStatus = PROCESS_FINISHED;
		}

		/* PID auto tune handle */
		if ((Gimbal.GetCurrentState() & SBGC_PID_AUTOTUNE) &&
			(PID_AutoTuneFinishFlag || ((osGetTickCount() - lastAutoTuneTime) > (AUTO_PID_TIMEOUT * 1000))))
		{
			Gimbal.ClearCurrentState(SBGC_PID_AUTOTUNE);
			Gimbal.processStatus = PROCESS_FINISHED;

			if (TaskPID_AutoTuneFinishCheckHandle != NULL)
				osTaskDelete(TaskPID_AutoTuneFinishCheckHandle);

			TaskPID_AutoTuneFinishCheckHandle = NULL;
		}

		/* Reset timeout handle */
		else if (((osGetTickCount() - lastResetTime) > RESET_UPDATE_TIME) &&
				 (FindShortcut(SHORTCUT_RESET)->status & SCS_ACTIVE))
		{
			Gimbal.ClearCurrentState(SBGC_REBOOT);
			Gimbal.processStatus = PROCESS_FINISHED;

			for (ui8 i = 0; i < SHORTCUT_TOTAL_NUM; i++)
				SetStatusAndTrigger(&shortcut[i], SCS_NORMAL);

			SetStatusAndTrigger(FindShortcut(SHORTCUT_MOTOR_SWITCH), SCS_TURNED_ON);

			if (Gimbal.GetCommunicationState())
			{
				Gimbal.ConfigGimbalControl();  // Return control configurations
				lastResetTime = osGetTickCount();
			}
		}


		/* Timestamp getting */
		displayTimestamp = osGetTickCount();

		osDelay(CONTAINER_PROCESS_DELAY);
	}
}


/* Target is 0 --> INITIAL_SHORTCUT_NUM borders */
void CShortcutContainerM::PlaceShortcut (ui8 target, ShortcutParameters_t *newShortcut)
{
	gwinDestroy(ghImageShortcut[target]);  // destroy old image

	GWidgetStyle *pstyle;
	gdispImage *imageShortcutTemp;

	static GWidgetInit wi;
	gwinWidgetClearInit(&wi);

	Utils::imageOpenFile(imageShortcutTemp, newShortcut->imagePath);
	wi.g.x = ghImageShortcut[target]->x;
	wi.g.y = ghImageShortcut[target]->y;
	wi.g.height = ghImageShortcut[target]->height;
	wi.g.width = ghImageShortcut[target]->width;
	wi.text = "";

	if (newShortcut->status & SCS_ACTIVE)
		pstyle = (!invertionTemp ? &CWidgetStyle::MonoImgStyleNormal : &CWidgetStyle::MonoImgStyleInvert);

	else if (newShortcut->status & SCS_NOT_ACTIVE)
		pstyle = &CWidgetStyle::MonoImgStyleInactive;

	else if (newShortcut->status & SCS_TURNED_ON)
		pstyle = &CWidgetStyle::MonoImgStyleInvert;

	else  // IDLE
		pstyle = &CWidgetStyle::MonoImgStyleNormal;

	wi.customStyle = pstyle;

	wi.customDraw = gwinImageWOpenAndDrawCustom_Mono;
	wi.customParam = (void*)newShortcut->imagePath;
	wi.g.parent = ghContainer;
	ghImageShortcut[target] = gwinImageWCreate(0, &wi);
	Utils::imageCloseFile(imageShortcutTemp);

	gwinShow(ghImageShortcut[target]);
}


void CShortcutContainerM::SwapShortcuts (ShortcutParameters_t *pulledShortcut, ShortcutParameters_t *nextShortcut)
{
	ui8 shortcutPositionTemp = nextShortcut->currentPosition;

	/* Replacing */
	PlaceShortcut(displayPosition, nextShortcut);
	PlaceShortcut(displayPosition + (nextShortcut->currentPosition - pulledShortcut->currentPosition), pulledShortcut);

	/* Position swapping */
	nextShortcut->currentPosition = pulledShortcut->currentPosition;
	pulledShortcut->currentPosition = shortcutPositionTemp;
}


void CShortcutContainerM::LeftScroll (void)
{
	/* If container is changing at the moment */
	if (containerStatus)
	{
		ShortcutParameters_t *displayedShortcuts [SHORTCUT_TOTAL_NUM];
		GetShortcutSortedByOrder(displayedShortcuts);

		SwapShortcuts(displayedShortcuts[currentPosition], displayedShortcuts[currentPosition - 1]);
	}


	/* [n] <-- [n + 1], where n > 1 and display position is ready to scroll */
	if ((displayPosition == 1) && (currentPosition != 1))
	{
		ShortcutParameters_t *displayedShortcuts [SHORTCUT_TOTAL_NUM];
		GetShortcutSortedByOrder(displayedShortcuts);

		for (ui8 i = 0; i < INITIAL_SHORTCUT_NUM; i++)
			PlaceShortcut(i, displayedShortcuts[currentPosition + i - 2]);

		currentPosition--;
		return;

		/* Arrow is idle */
	}

	/* Just arrow left-moving */
	else if (((displayPosition == 1) && (currentPosition == 1)) || // [0] <-- [1], when length is over by left side
			 (displayPosition > 1))  // or [n] <-- [n + 1], where n > 1 and display position isn't ready to scroll (2, 3, 4)
		gwinMove(ghImageArrow, ghImageArrow->x - SHORTCUT_X_STEP, ghImageArrow->y);

	/* Variables shift */
	if (currentPosition)
		currentPosition--;

	if (displayPosition)
		displayPosition--;
}


void CShortcutContainerM::RightScroll (void)
{
	/* If container is changing at the moment */
	if (containerStatus)
	{
		ShortcutParameters_t *displayedShortcuts [SHORTCUT_TOTAL_NUM];
		GetShortcutSortedByOrder(displayedShortcuts);

		SwapShortcuts(displayedShortcuts[currentPosition], displayedShortcuts[currentPosition + 1]);
	}


	/* [n] --> [n + 1], where n < TOTAL_SHORTCUT_NUM - 2 and display position is ready to scroll */
	if ((displayPosition == (INITIAL_SHORTCUT_NUM - 2)) && (currentPosition != (SHORTCUT_TOTAL_NUM - 2)))
	{
		ShortcutParameters_t *displayedShortcuts [SHORTCUT_TOTAL_NUM];
		GetShortcutSortedByOrder(displayedShortcuts);

		for (ui8 i = 0; i < INITIAL_SHORTCUT_NUM; i++)
			PlaceShortcut(i, displayedShortcuts[currentPosition + i - 2]);

		currentPosition++;
		return;

		/* Arrow is idle */
	}

	/* Just arrow right-moving */
	else if ( /* [TOTAL_SHORTCUT_NUM - 2] --> [TOTAL_SHORTCUT_NUM - 1], when length is over by right side */
			 ((displayPosition == (INITIAL_SHORTCUT_NUM - 2)) && (currentPosition == (SHORTCUT_TOTAL_NUM - 2))) ||
			 /* [n] --> [n + 1], where n < TOTAL_SHORTCUT_NUM - 2 and display position isn't ready to scroll (0, 1, 2) */
			 (displayPosition < (INITIAL_SHORTCUT_NUM - 2)))
		gwinMove(ghImageArrow, ghImageArrow->x + SHORTCUT_X_STEP, ghImageArrow->y);

	/* Variables shift */
	if (currentPosition < (SHORTCUT_TOTAL_NUM - 1))
		currentPosition++;

	if (displayPosition < (INITIAL_SHORTCUT_NUM - 1))
		displayPosition++;
}


/* Updates images by current length parameters */
void CShortcutContainerM::UpdateShortcutsImages (void)
{
	/* Must be displayed */
	ShortcutParameters_t *displayedShortcuts [SHORTCUT_TOTAL_NUM];
	GetShortcutSortedByOrder(displayedShortcuts);

	for (ui8 i = 0; i < INITIAL_SHORTCUT_NUM; i++)
		PlaceShortcut(i, displayedShortcuts[currentPosition - displayPosition + i]);
}


void CShortcutContainerM::DrawLeftArrow (Boolean_t color)
{
	gColor arrowColor;

	if (color)
		arrowColor = GFX_GRAY;

	else
		arrowColor = GFX_BLACK;

	gdispDrawLine(0, (DISPLAY_HEIGHT / 2), (SIDE_ARROW_IMAGE_WIDTH - 1), (DISPLAY_HEIGHT / 2) + SIDE_ARROW_IMAGE_HEIGHT, arrowColor);
	gdispDrawLine(0, (DISPLAY_HEIGHT / 2), (SIDE_ARROW_IMAGE_WIDTH - 1), (DISPLAY_HEIGHT / 2) - SIDE_ARROW_IMAGE_HEIGHT, arrowColor);
}


void CShortcutContainerM::DrawRightArrow (Boolean_t color)
{
	gColor arrowColor;

	if (color)
		arrowColor = GFX_GRAY;

	else
		arrowColor = GFX_BLACK;

	gdispDrawLine((DISPLAY_WIDTH - 1), (DISPLAY_HEIGHT / 2), (DISPLAY_WIDTH - 1 - (SIDE_ARROW_IMAGE_WIDTH - 1)),
				(DISPLAY_HEIGHT / 2) + SIDE_ARROW_IMAGE_HEIGHT, arrowColor);
	gdispDrawLine((DISPLAY_WIDTH - 1), (DISPLAY_HEIGHT / 2), (DISPLAY_WIDTH - 1 - (SIDE_ARROW_IMAGE_WIDTH - 1)),
				(DISPLAY_HEIGHT / 2) - SIDE_ARROW_IMAGE_HEIGHT, arrowColor);

	if (color == FALSE__)
		ghContainer->color = GFX_LIGHT_GRAY;
}


/* Side arrows handler */
void CShortcutContainerM::SideArrowsHandle (void)
{
	/* Left arrow */
	if ((currentPosition - (displayPosition - 3)) > (INITIAL_SHORTCUT_NUM - 2))
		DrawLeftArrow(TRUE__);

	else
		DrawLeftArrow(FALSE__);

	/* Right arrow */
	if ((currentPosition - (displayPosition - 3)) < (SHORTCUT_TOTAL_NUM - 2))
		DrawRightArrow(TRUE__);

	else
		DrawRightArrow(FALSE__);
}


void CShortcutContainerM::CommunicationInit (void)
{
	static Boolean_t disconnectionCaseFlag = FALSE__;
	static ShortcutList_t activatedRecentlyShortcutTemp = NO_SHORTCUT;  // Needed in case when link was interrupted during active process

	/* Progressbar handle */
	if ((Gimbal.processStatus == PROCESS_STARTED) &&
		(SBGC_CalibrationStateMask(Gimbal.GetCurrentState())))
		gwinShow(ghProgressbar);  // Calibration in progress

	else
		gwinHide(ghProgressbar);

	Gimbal.ReadRealTimeData();

	/* Connection is lost */
	if ((!Gimbal.GetCommunicationState()) ||
		SBGC_NoConnectionStateMask(Gimbal.GetCurrentState()))
	{
		if (FindActiveShortcut() != NULL)
			activatedRecentlyShortcutTemp = FindActiveShortcut()->number;

		for (ui8 i = 0; i < SHORTCUT_TOTAL_NUM; i++)
			if (shortcut[i].status != SCS_NOT_ACTIVE)
				SetStatusAndTrigger(&shortcut[i], SCS_NOT_ACTIVE);

		if ((Gimbal.processStatus == PROCESS_STARTED) && PID_AutoTuneFinishFlag)
		{
			Gimbal.GetAddressCalibInfo()->progress = 0;
			Gimbal.processStatus = PROCESS_FINISHED;
		}

		disconnectionCaseFlag = TRUE__;
	}

	/* Connection is OK */
	if (Gimbal.GetCommunicationState() &&
		(!SBGC_NoConnectionStateMask(Gimbal.GetCurrentState())))
	{
		if (disconnectionCaseFlag)
		{
			for (ui8 i = 0; i < SHORTCUT_TOTAL_NUM; i++)
			{
				if (shortcut[i].status & SCS_NOT_ACTIVE)
					SetStatusAndTrigger(&shortcut[i], SCS_NORMAL);
			}

			disconnectionCaseFlag = FALSE__;
		}

		if (activatedRecentlyShortcutTemp != NO_SHORTCUT)
		{
			Gimbal.RequestCalibInfo(SBGC_TARGET_IMU);

			if (Gimbal.GetAddressCalibInfo()->progress || (!PID_AutoTuneFinishFlag))
			/* If calibration was finished during a loss of connection */
			{
				SetStatusAndTrigger(FindShortcut(activatedRecentlyShortcutTemp), SCS_ACTIVE);
				activatedRecentlyShortcutTemp = NO_SHORTCUT;
			}
		}

		/* Motors state shortcut */
		if ((Gimbal.GetAddressRealTimeData()->RT_DataFlags & RTDF_MOTORS_ON) &&
			(!SBGC_RebootStateMask(Gimbal.GetCurrentState())))
			SetStatusAndTrigger(FindShortcut(SHORTCUT_MOTOR_SWITCH), SCS_TURNED_ON);

		else
			SetStatusAndTrigger(FindShortcut(SHORTCUT_MOTOR_SWITCH), SCS_NORMAL);
	}
}


void CShortcutContainerM::DisplayShortcutInit (void)
{
	static GWidgetStyle *pstyle;

	ShortcutParameters_t *buffShortcut [INITIAL_SHORTCUT_NUM];
	GetDisplayedShortcuts(buffShortcut);

	/* Connection is lost */
	if ((!Gimbal.GetCommunicationState()) ||
		SBGC_NoConnectionStateMask(Gimbal.GetCurrentState()))
	{
		for (ui8 i = 0; i < INITIAL_SHORTCUT_NUM; i++)
			if (buffShortcut[i]->status & SCS_NOT_ACTIVE)
			{
				pstyle = &CWidgetStyle::MonoImgStyleInactive;
				gwinSetStyle(ghImageShortcut[i], pstyle);
			}
	}

	/* Connection is OK */
	if (Gimbal.GetCommunicationState() && (Gimbal.processStatus != PROCESS_STARTED) &&
		(!SBGC_NoConnectionStateMask(Gimbal.GetCurrentState())))
	{
		for (ui8 i = 0; i < INITIAL_SHORTCUT_NUM; i++)
			if (buffShortcut[i]->status & SCS_NOT_ACTIVE)
			{
				pstyle = &CWidgetStyle::MonoImgStyleNormal;
				gwinSetStyle(ghImageShortcut[i], pstyle);
			}
	}
}


void CShortcutContainerM::ExecuteShortcutAssignedFunction (ShortcutParameters_t *shortcut)
{
	switch (shortcut->number)
	{
		case SHORTCUT_GYRO_CALIB :
			Gimbal.CalibGyro();

			if (Gimbal.GetCommunicationState())
			{
				Gimbal.AddCurrentState(SBGC_CALIBRATE_IMU);
				Gimbal.processStatus = PROCESS_STARTED;

				/* Shortcuts status changing */
				TurnOffAllShortcuts();
				SetStatusAndTrigger(shortcut, SCS_ACTIVE);

				lastCalibInfoTime = osGetTickCount();

				exCMessageWindowContainerM.SetMessage(TEXT_SIZE_("Don't touch the gimbal during calibration"),
													  MW_GIMBAL_GYRO_CALIB_STATE, MW_MEDIUM_FONT, 0);
				CStateManager::SetState({ MESSAGE_WINDOW_STATE, 0 });
				while (1);
			}

			break;

		case SHORTCUT_ACC_CALIB :
			Gimbal.TurnOffMotors();

			if (Gimbal.GetConfirmationCurrentStatus() == CONFIRMATION_OK)
			{
				Gimbal.GetAddressRealTimeData()->RT_DataFlags = RTDF_MOTORS_OFF;  // Implicit value assignment to private struct field

				/* Shortcuts status changing */
				TurnOffAllShortcuts();
				SetStatusAndTrigger(shortcut, SCS_ACTIVE);

				exCMessageWindowContainerM.SetMessage(TEXT_SIZE_("Don't touch the gimbal during calibration"),
													  MW_GIMBAL_ACC_CALIB_STATE, MW_MEDIUM_FONT, 0);
				CStateManager::SetState({ MESSAGE_WINDOW_STATE, 0 });
				while (1);
			}

			break;

		case SHORTCUT_MOTOR_SWITCH :
			Gimbal.ToggleMotors();

			if (Gimbal.GetAddressGeneralSBGC()->_confirmationStatus == CONFIRMATION_OK)
			{
				Gimbal.GetAddressRealTimeData()->RT_DataFlags ^= RTDF_MOTORS_ON;  // Implicit value assignment to private struct field

				if (Gimbal.GetAddressRealTimeData()->RT_DataFlags == RTDF_MOTORS_OFF)
				{
					SetStatusAndTrigger(FindShortcut(SHORTCUT_SCRIPT_1), SCS_NORMAL);
					SetStatusAndTrigger(FindShortcut(SHORTCUT_SCRIPT_2), SCS_NORMAL);
					SetStatusAndTrigger(FindShortcut(SHORTCUT_SCRIPT_3), SCS_NORMAL);
					SetStatusAndTrigger(FindShortcut(SHORTCUT_SCRIPT_4), SCS_NORMAL);
					SetStatusAndTrigger(FindShortcut(SHORTCUT_SCRIPT_5), SCS_NORMAL);
					SetStatusAndTrigger(shortcut, SCS_NORMAL);
					Gimbal.AddCurrentState(SBGC_MOTORS_OFF);
				}

				else
				{
					SetStatusAndTrigger(FindShortcut(SHORTCUT_SCRIPT_1), SCS_NOT_ACTIVE);
					SetStatusAndTrigger(FindShortcut(SHORTCUT_SCRIPT_2), SCS_NOT_ACTIVE);
					SetStatusAndTrigger(FindShortcut(SHORTCUT_SCRIPT_3), SCS_NOT_ACTIVE);
					SetStatusAndTrigger(FindShortcut(SHORTCUT_SCRIPT_4), SCS_NOT_ACTIVE);
					SetStatusAndTrigger(FindShortcut(SHORTCUT_SCRIPT_5), SCS_NOT_ACTIVE);
					SetStatusAndTrigger(shortcut, SCS_TURNED_ON);
					Gimbal.ClearCurrentState(SBGC_MOTORS_OFF);
				}
			}

			break;

		case SHORTCUT_AUTO_PID :
			Gimbal.TuneAutoPID();

			if (Gimbal.GetAddressGeneralSBGC()->_confirmationStatus == CONFIRMATION_OK)
			{
				Gimbal.AddCurrentState(SBGC_PID_AUTOTUNE);
				Gimbal.processStatus = PROCESS_STARTED;

				/* Shortcuts status changing */
				TurnOffAllShortcuts();
				SetStatusAndTrigger(shortcut, SCS_ACTIVE);

				PID_AutoTuneFinishFlag = false;
				lastAutoTuneTime = osGetTickCount();

				osTaskCreate(	TaskPID_AutoTuneFinishCheck,
								"AutoTuneFinishWait",
								configMINIMAL_STACK_SIZE * 5,
								NULL,
								OS_LOW_PRIORITY,
								&TaskPID_AutoTuneFinishCheckHandle);

				osDelay(5);
				Gimbal.ReadRealTimeData();

				exCMessageWindowContainerM.SetMessage(TEXT_SIZE_("Don't touch the gimbal during calibration"),
													  MW_GIMBAL_PID_TUNE_STATE, MW_MEDIUM_FONT, 0);
				CStateManager::SetState({ MESSAGE_WINDOW_STATE, 0 });
				while (1);
			}

			break;

		case SHORTCUT_RESET :
			Gimbal.Reset();

			if (Gimbal.GetCommunicationState())
			{
				for (ui8 i = 0; i < SHORTCUT_TOTAL_NUM; i++)
					SetStatusAndTrigger(&this->shortcut[i], SCS_NOT_ACTIVE);

				Gimbal.AddCurrentState(SBGC_REBOOT);
				Gimbal.processStatus = PROCESS_STARTED;
				SetStatusAndTrigger(shortcut, SCS_ACTIVE);
				SetStatusAndTrigger(FindShortcut(SHORTCUT_MOTOR_SWITCH), SCS_NORMAL);

				lastResetTime = osGetTickCount();
			}

			break;

		case SHORTCUT_SCRIPT_1 :
		case SHORTCUT_SCRIPT_2 :
		case SHORTCUT_SCRIPT_3 :
		case SHORTCUT_SCRIPT_4 :
		case SHORTCUT_SCRIPT_5 :
			if ((Gimbal.processStatus == PROCESS_READY) &&
				(!SBGC_ScriptExeStateMask(Gimbal.GetCurrentState())))
			{
				Gimbal.RunScript((ScriptSlotNum_t)(shortcut->number - SHORTCUT_SCRIPT_1));

				if (Gimbal.GetCommunicationState())
				{
					ScriptExeFinishFlag = false;

					osTaskCreate(	TaskScriptExeFinishWait,
									"ScriptExeFinishWait",
									configMINIMAL_STACK_SIZE * 5,
									NULL,
									OS_LOW_PRIORITY,
									&TaskScriptExeFinishWaitHandle);

					osDelay(5);

					Gimbal.AddCurrentState(SBGC_SCRIPT_EXE);
					Gimbal.processStatus = PROCESS_STARTED;

					/* Shortcuts status changing */
					TurnOffAllShortcuts();
					SetStatusAndTrigger(shortcut, SCS_ACTIVE);
				}
			}

			else if ((Gimbal.processStatus == PROCESS_STARTED) &&
					 (SBGC_ScriptExeStateMask(Gimbal.GetCurrentState())))
			{
				Gimbal.StopScript((ScriptSlotNum_t)(shortcut->number - SHORTCUT_SCRIPT_1));

				if (Gimbal.GetCommunicationState())
				{
					Gimbal.ClearCurrentState(SBGC_SCRIPT_EXE);
					Gimbal.processStatus = PROCESS_FINISHED;

					/* Shortcuts status changing */
					TurnOnAllShortcuts();

					if (TaskScriptExeFinishWaitHandle != NULL)
						osTaskDelete(TaskScriptExeFinishWaitHandle);

					TaskScriptExeFinishWaitHandle = NULL;
				}
			}

			break;

		default:
			break;
	}
}


/* It is active now. Writes only active shortcut */
ShortcutParameters_t *CShortcutContainerM::FindActiveShortcut (void)
{
	for (ui8 i = 0; i < SHORTCUT_TOTAL_NUM; i++)
		if (shortcut[i].status & SCS_ACTIVE)
			return &shortcut[i];

	return NULL;
}


/* Cursor right here */
ShortcutParameters_t *CShortcutContainerM::FindCurrentShortcut (void)
{
	for (ui8 i = 0; i < SHORTCUT_TOTAL_NUM; i++)
		if (shortcut[i].currentPosition == this->currentPosition)
			return &shortcut[i];

	return NULL;
}


/* Finds shortcut by its own identifier */
ShortcutParameters_t *CShortcutContainerM::FindShortcut (ShortcutList_t shortcutNum)
{
	for (ui8 i = 0; i < SHORTCUT_TOTAL_NUM; i++)
		if (shortcut[i].number == shortcutNum)
			return &shortcut[i];

	return NULL;
}


/* Writes ShortcutParameters_t [TOTAL_SHORTCUT_NUM] array into *buffShortcut buffer */
void CShortcutContainerM::GetShortcutSortedByOrder (ShortcutParameters_t **buffShortcut)
{
	for (ui8 i = 0; i < SHORTCUT_TOTAL_NUM; i++)
		for (ui8 k = 0; k < SHORTCUT_TOTAL_NUM; k++)
			if (shortcut[k].currentPosition == i)
				buffShortcut[i] = &shortcut[k];
}


void CShortcutContainerM::GetDisplayedShortcuts (ShortcutParameters_t **buffShortcut)
{
	ShortcutParameters_t *buffShortcutTemp [SHORTCUT_TOTAL_NUM];
	GetShortcutSortedByOrder(buffShortcutTemp);

	for (ui8 i = 0; i < INITIAL_SHORTCUT_NUM; i++)
		for (ui8 k = 0; k < SHORTCUT_TOTAL_NUM; k++)
			if (buffShortcutTemp[k]->currentPosition == (currentPosition - displayPosition + i))
				buffShortcut[i] = buffShortcutTemp[k];
}


void CShortcutContainerM::ShortcutLengthProcess (void)
{
	static ui32 effectsTimestamp = 0;
	static GWidgetStyle *pstyle;

	for (ui8 i = 0; i < INITIAL_SHORTCUT_NUM; i++)
		for (ui8 k = 0; k < SHORTCUT_TOTAL_NUM; k++)
			if ((shortcut[k].currentPosition == (currentPosition - displayPosition + i)) &&
				(GetTriggerFlag(&shortcut[k])))
			{
				/* Some switch */
				if (shortcut[k].status & SCS_NORMAL)
				{
					pstyle = &CWidgetStyle::MonoImgStyleNormal;
					gwinSetStyle(ghImageShortcut[i], pstyle);

					ClearTriggerFlag(&shortcut[k]);
				}

				else if (shortcut[k].status & SCS_ACTIVE)
				{
					if (invertionTemp)
						pstyle = &CWidgetStyle::MonoImgStyleInvert;

					else
						pstyle = &CWidgetStyle::MonoImgStyleNormal;

					gwinSetStyle(ghImageShortcut[i], pstyle);

					if ((displayTimestamp - effectsTimestamp) > SHORTCUT_ACTIVE_BLINK_TIME)
					{
						invertionTemp = !invertionTemp;
						effectsTimestamp = displayTimestamp;
					}
				}

				else if (shortcut[k].status & SCS_MOVED)
				{
					if (invertionTemp)
						pstyle = &CWidgetStyle::MonoImgStyleInvert;

					else
						pstyle = &CWidgetStyle::MonoImgStyleNormal;

					gwinSetStyle(ghImageShortcut[i], pstyle);

					if ((displayTimestamp - effectsTimestamp) > SHORTCUT_MOVED_BLINK_TIME)
					{
						invertionTemp = !invertionTemp;
						effectsTimestamp = displayTimestamp;
					}
				}

				else if (shortcut[k].status & SCS_NOT_ACTIVE)
				{
					pstyle = &CWidgetStyle::MonoImgStyleInactive;
					gwinSetStyle(ghImageShortcut[i], pstyle);

					ClearTriggerFlag(&shortcut[k]);
				}

				else if (shortcut[k].status & SCS_TURNED_ON)
				{
					pstyle = &CWidgetStyle::MonoImgStyleInvert;
					gwinSetStyle(ghImageShortcut[i], pstyle);

					ClearTriggerFlag(&shortcut[k]);
				}
			}
}


void TaskPID_AutoTuneFinishCheck (void *params)
{
	SerialCommand_t cmd;

	while (1)
	{
		Gimbal.SetParserCurrentStatus(Gimbal.FindCommand(&cmd, CMD_READ_PARAMS_3, SBGC_REQ_WAITING));

		if (Gimbal.GetCommunicationState() &&
			(cmd.commandID == CMD_READ_PARAMS_3))
		{
			MainParams3_t MainRarams3;

			ConvertWithPM(&MainRarams3, cmd.payload, cmd.payloadSize, PM_MAIN_PARAMS_3);
			Gimbal.UpdatePID_EEPROM_AdjVars(&MainRarams3);

			PID_AutoTuneFinishFlag = true;
			while (1);  // Delete waiting
		}

		osDelay(CONTAINER_PROCESS_DELAY);
	}
}


void TaskScriptExeFinishWait (void *params)
{
	SerialCommand_t cmd;
	ScriptDebugInfo_t ScriptDebugInfo;

	ui32 lastScriptInfoTime = osGetTickCount();

	while (1)
	{
		Gimbal.SetParserCurrentStatus(Gimbal.FindCommand(&cmd, CMD_SCRIPT_DEBUG, SBGC_REQ_WAITING));

		if (Gimbal.GetCommunicationState())
		{
			SBGC32_ParseScriptDebugInfoCmd(&cmd, &ScriptDebugInfo);

			if (ScriptDebugInfo.curComCounter == 0)
			{
				ScriptExeFinishFlag = true;
				Gimbal.ClearCurrentState(SBGC_SCRIPT_EXE);
				Gimbal.processStatus = PROCESS_FINISHED;
				TaskScriptExeFinishWaitHandle = NULL;
				osTaskDelete(NULL);
				while (1);  // Delete waiting
			}

			lastScriptInfoTime = osGetTickCount();
		}

		else if ((osGetTickCount() - lastScriptInfoTime) > SCRIPT_FINISH_CMD_PARSER_WAIT)
			/* If communication was interrupted */
		{
			ScriptExeFinishFlag = true;
			Gimbal.ClearCurrentState(SBGC_SCRIPT_EXE);
			Gimbal.processStatus = PROCESS_FINISHED;
			TaskScriptExeFinishWaitHandle = NULL;
			osTaskDelete(NULL);
			while (1);  // Delete waiting
		}

		osDelay(CONTAINER_PROCESS_DELAY);
	}
}
