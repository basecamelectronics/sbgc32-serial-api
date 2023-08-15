/** ____________________________________________________________________
 *
 *	@file		ProfileContainerM.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "createWidget.h"
#include "gwinImgW.h"
#include "gimbal.h"


static const char *emptyProfileNames [] = { "Profile 1", "Profile 2", "Profile 3", "Profile 4", "Profile 5" };


void CProfileContainerM::Init (void)
{
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

	/* Profile name label */
	wi.g.width = DISPLAY_WIDTH;
	wi.g.height = LARGE_FONT_HEIGHT;
	wi.g.x = 0;
	wi.g.y = DISPLAY_HEIGHT - LARGE_FONT_HEIGHT - 1;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
	wi.customParam = (void*)justifyCenter;
	wi.customDraw = gwinLabelDrawJustifiedCustomMono;
	ghLabelProfileName = gwinLabelCreate(0, &wi);

	/* Profile button labels */
	const char *nums [PROFILES_QUANTITY] = { "1", "2", "3", "4", "5" };

	wi.g.x = PROFILE_BUTTON_MARGINS;

	for (ui8 i = 0; i < PROFILES_QUANTITY; i++)
	{
		wi.g.width = PROFILE_BUTTONS_WIDTH;
		wi.g.height = PROFILE_BUTTONS_HEIGHT;
		wi.g.y = PROFILE_BUTTONS_Y_COORD;
		wi.text = nums[i];
		wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
		wi.customParam = (void*)justifyCenter;
		wi.customDraw = gwinLabelDrawJustifiedCustomMono;
		ghLabelProfileButtons[i] = gwinLabelCreate(0, &wi);

		wi.g.x += PROFILE_BUTTON_MARGINS + PROFILE_BUTTONS_WIDTH;
	}

	/* Up arrow */
	Utils::imageOpenFile(imageBuff, imagePathsReferenceArray[IPR_ARROW_UP]);
	wi.g.x = SELECT_PROFILE_ARROW_X_COORD;
	wi.g.y = SELECT_PROFILE_ARROW_Y_COORD;
	wi.g.height = imageBuff->height;
	wi.g.width = imageBuff->width;
	wi.text = "";
	wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
	wi.customDraw = gwinImageWOpenAndDrawCustom_Mono;
	wi.customParam = (void*)imagePathsReferenceArray[IPR_ARROW_UP];
	ghImageArrow = gwinImageWCreate(0, &wi);
	Utils::imageCloseFile(imageBuff);
}


void CProfileContainerM::OnHide (void)
{
	;
}


void CProfileContainerM::vTask (void *pvParameters)
{
	unused_(pvParameters);

	Gimbal.ReadRealTimeData();

	ui8 nProf = Gimbal.GetAddressRealTimeData()->curProfile;

	gwinMove(ghImageArrow, SELECT_PROFILE_ARROW_X_COORD + (PROFILE_BUTTON_X_STEP * nProf), ghImageArrow->y);

	gwinSetText(ghLabelProfileName, (const char*)Gimbal.GetAddressProfileNames(nProf), FALSE);

	gwinShow(ghContainer);

	NavigationDirection_t nav;
	ButtonState_t exitButton = BS_INIT;

	TickType_t xNavigationBlockTime = osGetTickCount();
	while (osGetTickCount() < (xNavigationBlockTime + NAVIGATION_INIT_BLOCK_TIME));

	while (1)
	{
		/* Navigation */
		MiniRemote.ProcessNavigationDirection();
		nav =  MiniRemote.GetNavigationDirection();
		MiniRemote.ProcessFunction(CSF_NAVIGATION_EXIT, &exitButton);

		if ((nav == ND_DOWN) || exitButton == BS_PRESSED)
			CStateManager::SetState({ PREVIOUS_STATE, 0 });


		if ((nav == ND_RIGHT) || (nav == (ND_RIGHT | ND_CONTINUOUS)))
			if (nProf<(PROFILES_QUANTITY - 1))
			{
				gwinMove(ghImageArrow, ghImageArrow->x + PROFILE_BUTTON_X_STEP, ghImageArrow->y);
				nProf++;
			}


		if ((nav == ND_LEFT) || (nav == (ND_LEFT | ND_CONTINUOUS)))
			if (nProf)
			{
				gwinMove(ghImageArrow, ghImageArrow->x - PROFILE_BUTTON_X_STEP, ghImageArrow->y);
				nProf--;
			}

		/* Execution */
		if ((nav == ND_UP) &&
			(!SBGC_NoConnectionStateMask(Gimbal.GetCurrentState())) &&
			(Gimbal.GetAddressRealTimeData()->curProfile != nProf))
		{
			switch (nProf)
			{
				case 0 :
					Gimbal.ExecuteMenu(MENU_CMD_PROFILE1);
					break;

				case 1 :
					Gimbal.ExecuteMenu(MENU_CMD_PROFILE2);
					break;

				case 2 :
					Gimbal.ExecuteMenu(MENU_CMD_PROFILE3);
					break;

				case 3 :
					Gimbal.ExecuteMenu(MENU_CMD_PROFILE4);
					break;

				case 4 :
					Gimbal.ExecuteMenu(MENU_CMD_PROFILE5);
					break;

				default :
					break;
			}

			if (Gimbal.GetAddressGeneralSBGC()->_confirmationStatus == CONFIRMATION_OK)
				Gimbal.GetAddressRealTimeData()->curProfile = nProf;  // Implicit value assignment to private struct field
		}

		/* Drawing buttons */
		for (ui8 i = 0; i < PROFILES_QUANTITY; i++)
		{
			if (i == Gimbal.GetAddressRealTimeData()->curProfile)
				gwinSetStyle(ghLabelProfileButtons[i], &CWidgetStyle::MonoImgStyleLabelInvert);

			else if (i == nProf)
				gwinSetStyle(ghLabelProfileButtons[i], &CWidgetStyle::MonoImgStyleLabelNormalFramed);

			else
				gwinSetStyle(ghLabelProfileButtons[i], &CWidgetStyle::MonoImgStyleLabelNormal);
		}

		if (*Gimbal.GetAddressProfileNames((Profile_t)nProf) == '\0')
			gwinSetText(ghLabelProfileName, emptyProfileNames[nProf], FALSE);

		else
			gwinSetText(ghLabelProfileName, (const char*)Gimbal.GetAddressProfileNames((Profile_t)nProf), FALSE);


		osDelay(CONTAINER_PROCESS_DELAY);
	}
}
