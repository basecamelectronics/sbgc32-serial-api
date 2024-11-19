/** ____________________________________________________________________
 *
 *	@file		gwinMenuPref.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include	"gwinMenuPref.h"
#include	"gfx.h"

#ifdef		__cplusplus
extern		"C"
			{
#endif

#include	"src/gwin/gwin_class.h"

#ifdef		__cplusplus
			}
#endif

#include	<string.h>
#include	<stdlib.h>
#include	"createWidget.h"
#include	"colors.h"
#include	"parameters.h"


// Macro's to assist in data type conversions
#define		gh2obj					((GMenuObject *)gh)
#define		gw2obj					((GMenuObject *)gw)
#define		ple						((GEventGWinMenu *)pe)


extern sbgcAdjVarReferenceInfo_t AdjVarsReferenceInfoArray [];


static const gwidgetVMT menuVMT =
{
	{	"Menu",																			// The class name
		sizeof(GMenuObject),															// The object size
		[](GHandle gh) { static_cast<CGWIN_Menu*>(gh2obj->class_obj)->Destroy(gh); },	// The destroy routine
		_gwidgetRedraw,																	// The redraw routine
		0,																				// The after-clear routine
	},

	[](GWidgetObject *gw, void *param) { static_cast<CGWIN_Menu*>(gw2obj->class_obj)->Draw(gw, param); }  // default drawing routine
};


GHandle CGWIN_Menu::Create (GDisplay *g, GMenuObject *gobj, GWidgetInit *pInit, MenuTypeEnum_t _MenuType,
							void *_Items_, ui16 sMenuCount, ui16 select)
{
	if (!(gobj = (GMenuObject *) _gwidgetCreate(g, &gobj->w, pInit, &menuVMT)))
		return 0;

	gobj->class_obj = new CGWIN_Menu(_MenuType);
	gobj->class_obj->SelectedItemIdx = select;

	gobj->class_obj->psMenu = _Items_;
	gobj->class_obj->sMenuCount = sMenuCount;

	gobj->class_obj->itemsOnWidth = 1;
	gobj->class_obj->noInitFlag = 1;

	gobj->class_obj->top = 0;

	gobj->class_obj->nItemsTotal = 0;
	for (ui8 i = 0; i < gobj->class_obj->sMenuCount; i++)
		gobj->class_obj->nItemsTotal += ((sMenu*)gobj->class_obj->psMenu)[i].nItems;

	gobj->class_obj->UpdateRes(&gobj->w);

	gobj->class_obj->ButtonRigth((GWidgetObject *) gobj);
	if(gobj->class_obj->SelectedItemIdx != select){
		gobj->class_obj->ButtonLeft((GWidgetObject *) gobj);
	}

	gwinSetVisible(&gobj->w.g, pInit->g.show);

	return (GHandle) gobj;
}


void CGWIN_Menu::Destroy (GHandle gh)
{
	delete gh2obj->class_obj;
}


void CGWIN_Menu::UpdateRes (GWidgetObject *gw)
{
	UpdateTotalHeight(gw);
	scrollBarEnabled = gw->g.height < totalHeight;

	noInitFlag = 0;
	static bool MenuPrefNoInit = 1;

	if (MenuPrefNoInit)
		MenuPrefNoInit = 0;
}


void CGWIN_Menu::ButtonUp (GWidgetObject *gw)
{
	i16 backupSelectedItemIdx = SelectedItemIdx;

	if (--SelectedItemIdx < 0)
		SelectedItemIdx = backupSelectedItemIdx;

	MiniRemote.SetRedrawMenuFlag(sbgcTRUE);
	MiniRemote.SetRedrawPrimitiveObjectsFlag(sbgcTRUE);

	ViewItem(gw);
	_gwinUpdate(&gw->g);
}


void CGWIN_Menu::ButtonDown (GWidgetObject *gw)
{
	i16 backupSelectedItemIdx = SelectedItemIdx;

	if (++SelectedItemIdx >= nItemsTotal)
		SelectedItemIdx = backupSelectedItemIdx;

	MiniRemote.SetRedrawMenuFlag(sbgcTRUE);
	MiniRemote.SetRedrawPrimitiveObjectsFlag(sbgcTRUE);

	ViewItem(gw);
	_gwinUpdate(&gw->g);
}


void CGWIN_Menu::ButtonLeft (GWidgetObject *gw)
{
	i16 backupSelectedItemIdx = SelectedItemIdx;

	while (1)
	{
		if (--SelectedItemIdx < 0)
		{
			SelectedItemIdx = backupSelectedItemIdx;
			break;
		}

		if ((((sMenuItem*)GetSelectedItem())->ItemType != ITEM_TYPE_TEXT))
			break;
	}

	MiniRemote.SetRedrawMenuFlag(sbgcTRUE);

	ViewItem(gw);
	_gwinUpdate(&gw->g);
}


void CGWIN_Menu::ButtonRigth (GWidgetObject* gw)
{
	i16 backupSelectedItemIdx = SelectedItemIdx;

	while (1)
	{
		if (++SelectedItemIdx >= nItemsTotal)
		{
			SelectedItemIdx = backupSelectedItemIdx;
			break;
		}

		if ((((sMenuItem *)GetSelectedItem())->ItemType != ITEM_TYPE_TEXT))
			break;
	}

	MiniRemote.SetRedrawMenuFlag(sbgcTRUE);

	ViewItem(gw);
	_gwinUpdate(&gw->g);
}


void CGWIN_Menu::ButtonEnter (GWidgetObject *gw)
{
	Enter(gw);
	_gwinUpdate(&gw->g);
}


void CGWIN_Menu::UpdateMenu (GWidgetObject *gw)
{
	ViewItem(gw);
	_gwinUpdate(&gw->g);
}


coord_t CGWIN_Menu::GetGridItemPoz (GWidgetObject *gw, sMenuItem *psItem)
{
	unused_(psItem);
	int32_t x = gw->g.x;
	return x;
}


#pragma GCC push_options
#pragma GCC optimize ("O3")
void CGWIN_Menu::Enter (GWidgetObject *gw)
{
	unused_(gw);

	sMenuItem *psCurrentItem = GetSelectedItem();

	if (psCurrentItem == 0)
		return;

	MiniRemote.SetRedrawMenuFlag(sbgcTRUE);
	MiniRemote.SetRedrawPrimitiveObjectsFlag(sbgcTRUE);

	switch (psCurrentItem->ItemType)
	{
		case ITEM_TYPE_CHECKBOX :
			switch (psCurrentItem->FuncID)
			{
				case FUNC_SWITCH_AV_SYNC_PRIORITY :
					if (MiniRemote.Presets.adjVarsSync == AVS_REMOTE_PRIORITY)
						MiniRemote.Presets.adjVarsSync = AVS_GIMBAL_PRIORITY;

					else if (MiniRemote.Presets.adjVarsSync == AVS_GIMBAL_PRIORITY)
						MiniRemote.Presets.adjVarsSync = AVS_REMOTE_PRIORITY;

					SettingsLoader.SaveRemoteParameter(&MiniRemote.Presets.adjVarsSync);

					break;

				case FUNC_SWITCH_COMMUNICATION_WAY :
					if (MiniRemote.Presets.communicationWay == CW_UART)
						MiniRemote.Presets.communicationWay = CW_RS422;

					else if (MiniRemote.Presets.communicationWay == CW_RS422)
						MiniRemote.Presets.communicationWay = CW_UART;

					SettingsLoader.SaveRemoteParameter(&MiniRemote.Presets.communicationWay);

					break;

				case FUNC_EDIT_MIXER_INVERSION :
					if (MiniRemote.Presets.mixChannel[MiniRemote.GetCurrentMixerChannel()].inversion == MIX_CHANNEL_DIRECT)
						MiniRemote.Presets.mixChannel[MiniRemote.GetCurrentMixerChannel()].inversion = MIX_CHANNEL_INVERTED;

					else
						MiniRemote.Presets.mixChannel[MiniRemote.GetCurrentMixerChannel()].inversion = MIX_CHANNEL_DIRECT;

					SettingsLoader.SaveRemoteParameter(&MiniRemote.Presets.mixChannel[MiniRemote.GetCurrentMixerChannel()].inversion);
					break;

				case FUNC_EDIT_CONTROL_INVERSION :
					Gimbal.GetChosenControlHandler()->invert = (sbgcBoolean_t)!Gimbal.GetChosenControlHandler()->invert;
					SettingsLoader.SaveGimbalParameter(&Gimbal.GetChosenControlHandler()->invert);
					break;

				case FUNC_TURN_ATTACHED_AXIS :
					if (SelectedItemIdx != NOT_ASSIGNED)
					{
						/* It's need to swap axes */
						if (Gimbal.GetChosenControlHandler()->attachedAxis != NOT_ASSIGNED)
						{
							Gimbal.GetHandlerOfActiveControlProfileByAxis(SelectedItemIdx)->attachedAxis =
									Gimbal.GetChosenControlHandler()->attachedAxis;
						}

						else
						/* else at least one of axes is free */
							Gimbal.GetHandlerOfActiveControlProfileByAxis(SelectedItemIdx)->attachedAxis =
									Gimbal.GetFreeFromHandlerAxisInActiveProfile();
					}

					Gimbal.GetChosenControlHandler()->attachedAxis = SelectedItemIdx;  // ROLL : PITCH : YAW

					if (Gimbal.GetChosenControlHandler()->attachedAxis == NOT_ASSIGNED)
					{
						Gimbal.GetChosenControlHandler()->controlMode = GIMBAL_NO_CONTROL;
						Gimbal.ConfigGimbalControl(SCParam_NO, SCPrior_HIGH, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);
					}

					else
						if (Gimbal.GetChosenControlHandler()->controlMode == GIMBAL_NO_CONTROL)
							/* Turn to default mode */
							Gimbal.GetChosenControlHandler()->controlMode = SBGC_DEFAULT_CONTROL_MODE;

					SettingsLoader.SaveGimbalParameter(&Gimbal.GetChosenControlProfile()->controlHandler[ROLL].attachedAxis);
					SettingsLoader.SaveGimbalParameter(&Gimbal.GetChosenControlProfile()->controlHandler[PITCH].attachedAxis);
					SettingsLoader.SaveGimbalParameter(&Gimbal.GetChosenControlProfile()->controlHandler[YAW].attachedAxis);

					break;

				case FUNC_TURN_CONTROL_MODE :
					if (Gimbal.GetChosenControlHandler()->controlMode != GIMBAL_NO_CONTROL)
					{
						Gimbal.GetChosenControlHandler()->controlMode = (GimbalControlMode_t)(SelectedItemIdx + 1);  // ABS : INC : RC
						Gimbal.ConfigGimbalControl(SCParam_NO, SCPrior_HIGH, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);
					}

					else
						psCurrentItem->param = 1;  // And then it be inverted to 0

					SettingsLoader.SaveGimbalParameter(&Gimbal.GetChosenControlHandler()->controlMode);

					break;

				default :
					break;
			}

			if (psCurrentItem->FuncID != FUNC_EDIT_MIXER_INVERSION)
			/* Toggling */
			{
				if (psCurrentItem->param <= 0xFF)
					psCurrentItem->param = !psCurrentItem->param;

				else
				{
					ui8 paramTemp = *(ui8*)psCurrentItem->param;
					*(ui8*)psCurrentItem->param = !paramTemp;
				}
			}

			break;

		case ITEM_TYPE_MENU:
			if (psCurrentItem->pSubMenu != 0)
			{
				psCurrentItem->pSubMenu->nSelect = 0;

				if (MenuType == MENU_SBGC_INFO)
					CStateManager::SetState((sDevState){ GIMBAL_MENU_STATE, (ui32)psCurrentItem->pSubMenu });

				else if (MenuType == MENU_REMOTE)
					CStateManager::SetState((sDevState){ REMOTE_MENU_STATE, (ui32)psCurrentItem->pSubMenu });
			}

			break;

		case ITEM_TYPE_FUNCTION:
		{
			switch (psCurrentItem->FuncID)
			{
				/* Remote parameters and functions */
				case FUNC_RESTART :
					NVIC_SystemReset();
					break;

				case FUNC_CLEAR_EEPROM :
					SettingsLoader.ClearAll();
					break;

				case FUNC_SET_STATE :
					CStateManager::ExeFunction(psCurrentItem->FuncID, psCurrentItem->param);
					while (1);
					break;

				case FUNC_EDIT_SYSTEM_BRIGHTNESS :
				{
					MiniRemote.SwitchDisplayToNormalState();

					ParameterHandle_t *parameterHandle = (ParameterHandle_t*)osMalloc(sizeof(ParameterHandle_t));

					parameterHandle->type = FUNC_EDIT_SYSTEM_BRIGHTNESS;
					parameterHandle->membership = PMS_REMOTE;
					parameterHandle->operatingValue = MiniRemote.GetAddressBrightness();
					parameterHandle->origDivider = 1.0F;
					parameterHandle->initValue = MiniRemote.GetBrightness();
					parameterHandle->minValue = BRIGHTNESS_MIN_VALUE;
					parameterHandle->maxValue = BRIGHTNESS_MAX_VALUE;
					parameterHandle->typeValue = sbgcUCHAR;
					parameterHandle->name = psCurrentItem->pTitle;
					parameterHandle->sensitivity = EDIT_SENS_PARAMETER_ADJUST;

					CStateManager::SetState((sDevState){ (ui8)PARAMETER_EDIT_STATE, (ui32)parameterHandle });
					while (1);
					break;
				}

				case FUNC_EDIT_SYSTEM_EE_RATIO :
				{
					ParameterHandle_t *parameterHandle = (ParameterHandle_t*)osMalloc(sizeof(ParameterHandle_t));

					parameterHandle->type = FUNC_EDIT_SYSTEM_EE_RATIO;
					parameterHandle->membership = PMS_REMOTE;
					parameterHandle->operatingValue = MiniRemote.GetAddressDimmedBrightnessRatio();
					parameterHandle->origDivider = 1.0F;
					parameterHandle->initValue = MiniRemote.GetDimmedBrightnessRatio();
					parameterHandle->minValue = ENERGY_ECONOMIC_RATIO_MIN;
					parameterHandle->maxValue = ENERGY_ECONOMIC_RATIO_MAX;
					parameterHandle->typeValue = sbgcUSHORT;
					parameterHandle->name = psCurrentItem->pTitle;
					parameterHandle->sensitivity = EDIT_SENS_PARAMETER_ADJUST;

					CStateManager::SetState((sDevState){ (ui8)PARAMETER_EDIT_STATE, (ui32)parameterHandle });
					while (1);
					break;
				}

				case FUNC_EDIT_SYSTEM_EE_TIMER :
				{
					ParameterHandle_t *parameterHandle = (ParameterHandle_t*)osMalloc(sizeof(ParameterHandle_t));

					parameterHandle->type = FUNC_EDIT_SYSTEM_EE_TIMER;
					parameterHandle->membership = PMS_REMOTE;
					parameterHandle->operatingValue = MiniRemote.GetAddressBrightnessTimer();
					parameterHandle->origDivider = 1.0F;
					parameterHandle->initValue = MiniRemote.GetBrightnessTimer();
					parameterHandle->minValue = ENERGY_ECONOMIC_TIMER_MIN;
					parameterHandle->maxValue = ENERGY_ECONOMIC_TIMER_MAX;
					parameterHandle->typeValue = sbgcUSHORT;
					parameterHandle->name = psCurrentItem->pTitle;
					parameterHandle->sensitivity = EDIT_SENS_PARAMETER_ADJUST;

					CStateManager::SetState((sDevState){ (ui8)PARAMETER_EDIT_STATE, (ui32)parameterHandle });
					while (1);
					break;
				}

				case FUNC_EDIT_PARAMETER :
				{
					/* Mixers */
					ParameterHandle_t *parameterHandle = (ParameterHandle_t*)osMalloc(sizeof(ParameterHandle_t));

					memcpy(parameterHandle, (void*)psCurrentItem->param, sizeof(ParameterHandle_t));
					parameterHandle->sensitivity = EDIT_SENS_PARAMETER_ADJUST;

					CStateManager::SetState((sDevState){ (ui8)PARAMETER_EDIT_STATE, (ui32)parameterHandle });
					while (1);
					break;
				}

				case FUNC_SAVE_ADJVARS_TO_GIMBAL :
				{
					if (gimbalConnected_)
						if (Gimbal.SaveAllAdjVarsToEEPROM(SCParam_FREEZE, SCPrior_NORMAL, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_) == sbgcCOMMAND_OK)
							/* Getting EEPROM adjustable variable values */
							Gimbal.UpdateEEPROM_AdjVars(SCParam_FREEZE, SCPrior_NORMAL, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);

					CStateManager::SetState((sDevState){ REFRESH_THE_STATE, 0 });
					while (1);
					break;
				}
				case FUNC_SAVE_ADJVARS_TO_REMOTE :
				{
					for (ui8 i = 0; i < SBGC_ADJ_VARS_MAX_QUANTITY; i++)
						SettingsLoader.SaveGimbalParameter(&Gimbal.Presets.AdjVarGeneral[i].value);

					CStateManager::SetState((sDevState){ REFRESH_THE_STATE, 0 });
					while (1);
					break;
				}

				case FUNC_RESET_ADJVARS :
					if (MiniRemote.Presets.adjVarsSync == AVS_REMOTE_PRIORITY)
						SettingsLoader.RecoverAdjVars();

					else if (gimbalConnected_)
						Gimbal.ReadProfileParams((sbgcProfile_t)Gimbal.GetAddressRealTimeData()->curProfile,
												 SCParam_FREEZE, SCPrior_NORMAL, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);

					CStateManager::SetState((sDevState){ REFRESH_THE_STATE, 0 });
					while (1);
					break;


				/* Gimbal parameters */
				case FUNC_EDIT_CONTROL_SPEED :
				{
					ParameterHandle_t *parameterHandle = (ParameterHandle_t*)osMalloc(sizeof(ParameterHandle_t));

					parameterHandle->type = FUNC_EDIT_CONTROL_SPEED;
					parameterHandle->membership = PMS_GIMBAL;
					parameterHandle->operatingValue = &Gimbal.GetChosenControlHandler()->speed;
					parameterHandle->origDivider = SBGC_CONTROL_SPEED_DIVIDER;
					parameterHandle->initValue = Gimbal.GetChosenControlHandler()->speed;
					parameterHandle->minValue = SBGC_CONTROL_SPEED_MIN_VALUE;
					parameterHandle->maxValue = SBGC_CONTROL_SPEED_MAX_VALUE;
					parameterHandle->typeValue = sbgcUSHORT;
					parameterHandle->name = psCurrentItem->pTitle;
					parameterHandle->sensitivity = EDIT_SENS_PARAMETER_ADJUST;

					CStateManager::SetState((sDevState){ (ui8)PARAMETER_EDIT_STATE, (ui32)parameterHandle });
					while (1);
					break;
				}

				case FUNC_EDIT_CONTROL_LPF :
				{
					ParameterHandle_t *parameterHandle = (ParameterHandle_t*)osMalloc(sizeof(ParameterHandle_t));

					parameterHandle->type = FUNC_EDIT_CONTROL_LPF;
					parameterHandle->membership = PMS_GIMBAL;
					parameterHandle->operatingValue = &Gimbal.GetChosenControlHandler()->LPF;
					parameterHandle->origDivider = 1.0F;
					parameterHandle->initValue = Gimbal.GetChosenControlHandler()->LPF;
					parameterHandle->minValue = SBGC_CONTROL_LPF_MIN_VALUE;
					parameterHandle->maxValue = SBGC_CONTROL_LPF_MAX_VALUE;
					parameterHandle->typeValue = sbgcUCHAR;
					parameterHandle->name = psCurrentItem->pTitle;
					parameterHandle->sensitivity = EDIT_SENS_PARAMETER_ADJUST;

					CStateManager::SetState((sDevState){ (ui8)PARAMETER_EDIT_STATE, (ui32)parameterHandle });
					while (1);
					break;
				}

				case FUNC_EDIT_CONTROL_SENS :
				{
					ParameterHandle_t *parameterHandle = (ParameterHandle_t*)osMalloc(sizeof(ParameterHandle_t));

					parameterHandle->type = FUNC_EDIT_CONTROL_SENS;
					parameterHandle->membership = PMS_GIMBAL;
					parameterHandle->operatingValue = &Gimbal.GetChosenControlHandler()->sensitivity;
					parameterHandle->origDivider = 1.0F;
					parameterHandle->initValue = Gimbal.GetChosenControlHandler()->sensitivity;
					parameterHandle->minValue = SBGC_CONTROL_SENS_MIN_VALUE;
					parameterHandle->maxValue = SBGC_CONTROL_SENS_MAX_VALUE;
					parameterHandle->typeValue = sbgcUCHAR;
					parameterHandle->name = psCurrentItem->pTitle;
					parameterHandle->sensitivity = EDIT_SENS_PARAMETER_ADJUST;

					CStateManager::SetState((sDevState){ (ui8)PARAMETER_EDIT_STATE, (ui32)parameterHandle });
					while (1);
					break;
				}

				case FUNC_EDIT_CONTROL_EXP :
				{
					ParameterHandle_t *parameterHandle = (ParameterHandle_t*)osMalloc(sizeof(ParameterHandle_t));

					parameterHandle->type = FUNC_EDIT_CONTROL_EXP;
					parameterHandle->membership = PMS_GIMBAL;
					parameterHandle->operatingValue = &Gimbal.GetChosenControlHandler()->exponent;
					parameterHandle->origDivider = 1.0F;
					parameterHandle->initValue = Gimbal.GetChosenControlHandler()->exponent;
					parameterHandle->minValue = SBGC_CONTROL_EXP_MIN_VALUE;
					parameterHandle->maxValue = SBGC_CONTROL_EXP_MAX_VALUE;
					parameterHandle->typeValue = sbgcUCHAR;
					parameterHandle->name = psCurrentItem->pTitle;
					parameterHandle->sensitivity = EDIT_SENS_PARAMETER_ADJUST;

					CStateManager::SetState((sDevState){ (ui8)PARAMETER_EDIT_STATE, (ui32)parameterHandle });
					while (1);
					break;
				}

				default :
					break;
			}

			break;
		}

		case ITEM_TYPE_ADJVAR :
		{
			CStateManager::SetState((sDevState){ (ui8)ADJ_VAR_EDIT_STATE, (ui32)psCurrentItem->param });
			while (1);
			break;
		}

		default:
			break;
	}
}
#pragma GCC pop_options


void CGWIN_Menu::ViewItem (GWidgetObject *gw)
{
	coord_t iheight = GetTotalIheight(gw);

	sMenuItem *psItem;
	sMenuItem *psSelectedItem = GetSelectedItem();
	coord_t y = 0;

	for (ui8 i = 0; i < sMenuCount; i++)
	{
		for (ui8 j = 0; j < ((sMenu*) psMenu)[i].nItems; j++)
		{
			psItem = &((sMenu*) psMenu)[i].psItems[j];

			if (psSelectedItem == psItem)
			{
				if (top < (y + iheight * 2 - gw->g.height))
					top = (y + iheight * 2 - gw->g.height);

				else if (top > (y - iheight))
					top = y - iheight;

				ConstrainTop(gw);
				return;
			}

			y += iheight;
		}
	}
}


void CGWIN_Menu::DrawScrollBar (GWidgetObject *gw, color_t color)
{
	if (scrollBarEnabled)
	{
		int maxScrollValue = totalHeight - gw->g.height;

		if (maxScrollValue > 0)
		{
			ui32 barHeight = (gw->g.height - MENU_SCROLL_VERT_PAD * 2);
			barHeight *= barHeight;
			barHeight /= totalHeight;

			gdispGFillArea(gw->g.display, gw->g.x + gw->g.width - MENU_SCROLL_HOR_LPAD - MENU_SCROLL_WIDTH,
					gw->g.y, MENU_SCROLL_WIDTH, gw->g.height, gw->pstyle->background);

			gdispGFillArea(gw->g.display, gw->g.x + gw->g.width - MENU_SCROLL_HOR_LPAD - MENU_SCROLL_WIDTH,
					gw->g.y + MENU_SCROLL_VERT_PAD + top * ((gw->g.height - MENU_SCROLL_VERT_PAD * 2) - barHeight) / maxScrollValue,
					MENU_SCROLL_WIDTH, barHeight, color);
		}
	}
}


static void gdispGFillStringBoxCustom (GDisplay *g, gCoord x, gCoord y, gCoord cx, gCoord cy,
								const char* str, gFont font, gColor color, gColor bgcolor, gJustify justify)
{
	GDisplay *pPixmap = gdispPixmapCreateCustom(cx, cy);
	gdispGFillStringBox(pPixmap, 0, 0, cx, cy, str, font, color, bgcolor, justify);
	gdispGBlitArea(g, x, y, cx, cy, 0, 0, cx, gdispPixmapGetBits(pPixmap));
}


static void gdispGFillStringBoxWithValueCustom (GDisplay *g, gCoord x, gCoord y, gCoord cx, gCoord cy,
												const char *str, const char *value, gFont font, gColor color, gColor bgcolor,
												gJustify justify, ui16 *phase)
{
	/*	Strings analyze */
	gCoord valueLength = gdispGetStringWidthCount(value, font, strlen(value));

	/* Drawing */
	GDisplay *pPixmap = gdispPixmapCreateCustom(cx, cy);
	gdispGFillStringBox(pPixmap, 0, 0, cx, cy, value, font, color, bgcolor, justifyRight);
	gdispGFillStringBox(pPixmap, -(*phase), 0, cx - valueLength - MENU_ITEM_VALUE_MIN_SPACING + (*phase), cy, str, font, color, bgcolor, justify);
	gdispGBlitArea(g, x, y, cx, cy, 0, 0, cx, gdispPixmapGetBits(pPixmap));
}


void CGWIN_Menu::Draw (GWidgetObject *gw, void *param)
{
	volatile ui32 st = osGetTickCount();

	(void) param;
	coord_t iheight;
	const GColorSet *ps;

	if (gw->g.vmt != (gwinVMT*)&menuVMT)
		return;

	ps = (gw->g.flags & GWIN_FLG_SYSENABLED) ? &gw->pstyle->enabled : &gw->pstyle->disabled;

	// Set the clipping region so we do not override the frame.
	#if GDISP_NEED_CLIP
		gdispGSetClip(gdispGetDisplay(0), gw->g.x, gw->g.y, gw->g.width, gw->g.height);
	#endif

	iheight = GetTotalIheight(gw);

	static sMenuItem *selectedItemTemp = NULL;

	coord_t _y;  // The start position
	coord_t _cy;  // The size of the filled area
	sMenuItem *psItem;
	sMenuItem *psSelectedItem = GetSelectedItem();
	coord_t y = 0;

	/* Animation variables */
	static sbgcBoolean_t scrollFinishDelayFlag = sbgcFALSE;
	static TickType_t scrollDelayTimer = osGetTickCount();
	static sbgcBoolean_t scrollApplyFlag = sbgcFALSE;

	static ui16 scrollingMargin = 0;
	static i16 scrollingMarginTemp = 0;
	static ui16 selectedItemScroll = 0;

	if ((psSelectedItem->ItemType == ITEM_TYPE_VALUE) || (psSelectedItem->ItemType == ITEM_TYPE_ADJVAR))
	{
		scrollingMarginTemp = DISPLAY_WIDTH - gdispGetStringWidth(psSelectedItem->value, MiniRemote.GetMediumFont()) -
				MENU_ITEM_VALUE_MIN_SPACING - 16 - gdispGetStringWidth(psSelectedItem->pTitle, MiniRemote.GetMediumFont());

		if (scrollingMarginTemp < 0)
		/* We need to calculate the shifting */
		{
			if (selectedItemTemp != psSelectedItem)
			{
				scrollFinishDelayFlag = sbgcFALSE;
				scrollDelayTimer = osGetTickCount();
				scrollApplyFlag = sbgcFALSE;

				selectedItemScroll = 0;
			}

			scrollingMargin = -scrollingMarginTemp;

			if (scrollFinishDelayFlag == sbgcFALSE)
			{
				if ((osGetTickCount() - scrollDelayTimer) > STRING_SCROLLING_START_DELAY)
					scrollApplyFlag = sbgcTRUE;

				else
					scrollingMargin = 0;

				if ((selectedItemScroll < scrollingMargin) && (scrollApplyFlag == sbgcTRUE))
					selectedItemScroll += STRING_SCROLLING_SPEED;

				if ((selectedItemScroll >= scrollingMargin) && (scrollingMargin != 0))
				{
					scrollFinishDelayFlag = sbgcTRUE;
					scrollDelayTimer = osGetTickCount();
				}
			}

			else if ((osGetTickCount() - scrollDelayTimer) > STRING_SCROLLING_FINISH_DELAY)
			{
				scrollFinishDelayFlag = sbgcFALSE;
				selectedItemScroll = 0;
				scrollDelayTimer = osGetTickCount();
			}

			selectedItemTemp = psSelectedItem;
		}
	}

	if ((!scrollApplyFlag) && (!MiniRemote.GetRedrawMenuFlag()))
		return;

	else if (MiniRemote.GetRedrawMenuFlag())
	/* The scroll area */
	{
		DrawScrollBar(gw, GFX_DARK_GRAY);

		selectedItemScroll = 0;
		selectedItemTemp = NULL;
	}

	if (scrollApplyFlag && (selectedItemScroll == 0))
		scrollApplyFlag = sbgcFALSE;

	/* Processing */
	for (ui8 i = 0; i < sMenuCount; i++)
	{
		if ((y - top) > gw->g.height)
			break;

		else if ((y + iheight) > top)
		{
			_y = gw->g.y + (y - top);  // The start position
			_cy = iheight;  // The size of the filled area

			if (_y <= gw->g.y)
			{
				_cy -= gw->g.y - _y;
				_y = gw->g.y;
			}
		}

		for (ui8 j = 0; j < ((sMenu*)psMenu)[i].nItems; j++)
		{
			psItem = &((sMenu*)psMenu)[i].psItems[j];

			if ((y - top) > gw->g.height)
				break;

			else if ((y + iheight) >= top)
			{
				/* Draw item title */
				justify_t justify = justifyLeft;

				coord_t item_width = GetGridItemSize(gw) - MENU_ITEM_HOR_PAD * 2;
				coord_t item_height = iheight;
				coord_t _x = GetGridItemPoz(gw, psItem) + MENU_ITEM_HOR_PAD;
				coord_t _y = gw->g.y + y - top;

				if ((psItem->ItemType == ITEM_TYPE_VALUE) || (psItem->ItemType == ITEM_TYPE_ADJVAR) ||
					(psItem->ItemType == ITEM_TYPE_CHECKBOX))
				{
					;  // Dummy for another cases
				}

				else
				{
					gdispGFillStringBoxCustom(gw->g.display, _x, _y, item_width, item_height, (const char*)psItem->pTitle, gw->g.font,
							(psItem == psSelectedItem) ? gw->pstyle->background : ps->text,
							(psItem == psSelectedItem) ? ps->text : gw->pstyle->background,
							justify);

					justify = justifyRight;
				}

				switch (psItem->ItemType)
				{
					case ITEM_TYPE_CHECKBOX :
					{
						ui16 rightSideMargin = item_width - MEDIUM_FONT_HEIGHT - 6;

						gdispGFillStringBoxCustom(gw->g.display, _x, _y, rightSideMargin, item_height, (const char*)psItem->pTitle, gw->g.font,
								(psItem == psSelectedItem) ? gw->pstyle->background : ps->text,
								(psItem == psSelectedItem) ? ps->text : gw->pstyle->background,
								justifyLeft);

						if (MiniRemote.GetRedrawPrimitiveObjectsFlag())
						{
							/* Clear space */
							gdispGFillArea(gw->g.display, rightSideMargin, _y,
									DISPLAY_WIDTH - rightSideMargin - MENU_SCROLL_HOR_LPAD - MENU_SCROLL_WIDTH,
									item_height, gw->pstyle->background);

							/* Draw circle */
							gdispGDrawCircle(gw->g.display, item_width - (MEDIUM_FONT_HEIGHT / 2),
									_y + (MEDIUM_FONT_HEIGHT / 2), 8, ps->text);
							gdispGFillCircle(gw->g.display, item_width - (MEDIUM_FONT_HEIGHT / 2),
									_y + (MEDIUM_FONT_HEIGHT / 2), 4, gw->pstyle->background);

							gdispGDrawCircle(gw->g.display, item_width - (MEDIUM_FONT_HEIGHT / 2),
									_y + (MEDIUM_FONT_HEIGHT / 2), 8, ps->text);
							gdispGFillCircle(gw->g.display, item_width - (MEDIUM_FONT_HEIGHT / 2),
									_y + (MEDIUM_FONT_HEIGHT / 2), 4, gw->pstyle->background);

							if (psItem->param > 0xFF)  // check that is a pointer
							{
								if (*(ui8*)psItem->param != 0)
									gdispGFillCircle(gw->g.display, item_width - (MEDIUM_FONT_HEIGHT / 2),
											_y + (MEDIUM_FONT_HEIGHT / 2), 4, ps->text);
							}

							else
							{
								if (psItem->param != 0)
									gdispGFillCircle(gw->g.display, item_width - (MEDIUM_FONT_HEIGHT / 2),
											_y + (MEDIUM_FONT_HEIGHT / 2), 4, ps->text);
							}
						}

						break;
					}

					case ITEM_TYPE_VALUE :
					case ITEM_TYPE_ADJVAR :
						if ((psItem != selectedItemTemp) && (!MiniRemote.GetRedrawMenuFlag()))
							break;

						gdispGFillStringBoxWithValueCustom(gw->g.display, _x, _y, item_width, item_height,
								(const char*)psItem->pTitle, (const char*)psItem->value, gw->g.font,
								(psItem == psSelectedItem) ? gw->pstyle->background : ps->text,
								(psItem == psSelectedItem) ? ps->text : gw->pstyle->background,
								justify, (psItem == psSelectedItem) ? &selectedItemScroll : NULL);

						break;

					default:
						break;
				}
			}

			y += iheight;
		}
	}

	st = xTaskGetTickCount() - st;
	st++;


	MiniRemote.SetRedrawMenuFlag(sbgcFALSE);
	MiniRemote.SetRedrawPrimitiveObjectsFlag(sbgcFALSE);
}


#undef		gh2obj
#undef		gw2obj
#undef		ple
