/** ____________________________________________________________________
 *
 *	@file		MainChoiceContainerM.cpp
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


void CMainChoiceContainerM::Init (void)
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

	wi.g.width = gdispGetWidth();
	wi.g.height = gdispGetHeight();
	wi.g.x = 0;
	wi.g.y = 0;
	wi.text = "";
	wi.customStyle = 0;
	wi.customParam = (void*)justifyCenter;
	wi.customDraw = gwinLabelDrawJustified;


/*  ____________________
   |		 Aw_	 	|
   |	_	|_3_|Ah _	|
   |___|1|____|_Rx_|2|__|
   |   |_|	 _Ry   |_| 	|
   |		|_4_|		|
   |____________________|
*/

	gCoord Aw = ghContainer->width / 5;
	gCoord Ah = ghContainer->height / 8;
	gCoord Rx = ghContainer->width / 2 - Ah;
	gCoord Ry = ghContainer->height / 2 - Ah;
	gCoord W = ghContainer->width;
	gCoord H = ghContainer->height;

	gCoord textH = 16; // textH > Aw
	gCoord textW = ghContainer->width / 2 - Ah;

	gCoord A1x = W / 2 - Rx - Ah;
	gCoord A2x = W / 2 + Rx;
	gCoord A12y = (H - Aw) / 2 ;

	gCoord A3y = H / 2 - Ry - Ah;
	gCoord A4y = H / 2 + Ry;
	gCoord A34x = (W - Aw) / 2 ;

	gPoint arrowsPos [] = { { A1x, A12y }, { A2x, A12y }, { A34x, A3y }, { A34x, A4y } };
	gPoint textPos [] =
	{
		{ (gCoord)(A1x + Ah), (gCoord)(A12y + ((Aw - textH) / 2)) },
		{ (gCoord)(ghContainer->width / 2), (gCoord)(A12y + ((Aw - textH) / 2)) },
		{ (gCoord)((ghContainer->width - textW) / 2), (gCoord)(A3y + Ah + 1)},
		{ (gCoord)((ghContainer->width - textW) / 2), (gCoord)(A4y - textH - 2) }
	};

	const gJustify justify [] = { gJustifyLeft, gJustifyRight, gJustifyTop, gJustifyBottom, };
	const char* names [] = { "Gimbal", "Remote", "Profiles", "Shortcuts" };

	for (uint8_t i = 0; i < 4; ++i)
	{
		/* Text */
		wi.g.height = textH;
		wi.g.width = textW;
		wi.g.x = textPos[i].x;
		wi.g.y = textPos[i].y;
		wi.text = names[i];
		wi.customStyle = &CWidgetStyle::MonoImgStyleLabelDimmed;
		wi.customParam = (i >= 2) ? (void*)gJustifyCenter : (void*)justify[i];
		wi.customDraw = gwinLabelDrawJustifiedCustomMono;
		ghLabel[i] = gwinLabelCreate(0, &wi);
		gwinSetFont(ghLabel[i], MiniRemote.GetSmallFont());

		/* Arrow */
		wi.g.x = arrowsPos[i].x;
		wi.g.y = arrowsPos[i].y;
		wi.g.width = (i >= 2) ? Aw : Ah;
		wi.g.height = (i >= 2) ? Ah : Aw;
		wi.text = "";
		wi.customStyle = &CWidgetStyle::MonoImgStyleNormal;
		wi.customParam = (void*)justify[i];
		wi.customDraw = gwinArrow_Mono;
		ghImageArrow[i] = gwinLabelCreate(0, &wi);
	}
}


void CMainChoiceContainerM::OnHide (void)
{
	;
}


void CMainChoiceContainerM::vTask (void *pvParameters)
{
	UNUSED(pvParameters);

	gwinShow(ghContainer);

	NavigationDirection_t nav;

	TickType_t xNavigationBlockTime = osGetTickCount();
	while (osGetTickCount() < (xNavigationBlockTime + NAVIGATION_INIT_BLOCK_TIME));

	while (1)
	{
		MiniRemote.ProcessNavigationDirection();
		nav =  MiniRemote.GetNavigationDirection();

    	if (nav == ND_UP)
    		CStateManager::SetState({ PROFILE_STATE, 0 });

    	if (nav == ND_DOWN)
			CStateManager::SetState({ SHORTCUT_STATE, 0 });

		if (nav == ND_RIGHT)
		{
			extern sPrefMenu exsPrefRemoteMenu;
			CStateManager::SetState({ REMOTE_MENU_STATE, ((uint32_t)&exsPrefRemoteMenu) });
		}

		if (nav == ND_LEFT)
		{
			extern sPrefMenu exsPrefSBGCInfo;
			CStateManager::SetState({ GIMBAL_MENU_STATE, ((uint32_t)&exsPrefSBGCInfo) });
		}

		vTaskDelay(CONTAINER_PROCESS_DELAY);
	}
}
