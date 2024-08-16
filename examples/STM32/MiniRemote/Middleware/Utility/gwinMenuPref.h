/** ____________________________________________________________________
 *
 *	@file		gwinMenuPref.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_GWIN_MENU_PREF_H_
#define		_GWIN_MENU_PREF_H_

#include	"menuStructure.h"

#define		MENU_VERT_PAD			2
#define		MENU_SCROLL_WIDTH		3

#define		MENU_SCROLL_VERT_PAD	0

#define		MENU_SCROLL_HOR_LPAD	1
#define		MENU_SCROLL_HOR_RPAD	4

#define		MENU_ITEM_HOR_PAD		2
#define		MENU_ITEM_VERT_PAD		2

#define		MENU_ITEM_BUTTON_HOR_PAD		2
#define		MENU_ITEM_BUTTON_VERT_PAD		2

#define		MENU_IMAGE_MARGIN		5

#define		MOUSE_MOVE_DETECTION_THRESHOLD	10

#define		MENU_ITEM_VALUE_MAX_X_POS		148
#define		MENU_ITEM_VALUE_MIN_SPACING		4


struct GMenuObject;


class CGWIN_Menu
{
	private :

		MenuTypeEnum_t		MenuType;

		ui8					nItemsTotal;
		coord_t				totalHeight;

		void				*psMenu;

		ui8					sMenuCount,
							noInitFlag,
							itemsOnWidth;

		int					top;					// Viewing offset in pixels from the top of the list
		bool				scrollBarEnabled;


	public:

		CGWIN_Menu(			MenuTypeEnum_t MenuType)
							{
								this->MenuType = MenuType;
							}

		i16					SelectedItemIdx;

		void				ConstrainTop (GWidgetObject *gw)
							{
								if (top >= (totalHeight - gw->g.height))
									top = totalHeight - gw->g.height - 1;

								if (top < 0)
									top = 0;
							}

		void				UpdateRes (GWidgetObject *gw);
		void				Enter (GWidgetObject *gw);
		void				ViewItem (GWidgetObject *gw);

		static GHandle		Create (GDisplay *g, GMenuObject *gobj, GWidgetInit *pInit, MenuTypeEnum_t _MenuType,
									void *_Items_, ui16 sMenuCount, ui16 select);
		void				Destroy (GHandle gh);

		coord_t				GetGridItemSize (GWidgetObject *gw) { return GetIwidth(gw); }
		coord_t				GetGridItemPoz (GWidgetObject *gw, sMenuItem *psItem);

		void				DrawScrollBar (GWidgetObject *gw, color_t color);

		int					GetTextIheight (GWidgetObject *gw)
							{
								return gdispGetFontMetric(gw->g.font, fontHeight) + MENU_VERT_PAD;
							}

		int					GetTotalIheight (GWidgetObject *gw) { return GetTextIheight(gw); }

		void				UpdateTotalHeight (GWidgetObject *gw)
							{
								totalHeight = 0;

								for (uint8_t i = 0; i < sMenuCount; i++)
									for (uint8_t j = 0; j < ((sMenu*) psMenu)[i].nItems; j++)
										totalHeight += GetTotalIheight(gw);  // menu item height
							}

		sMenuItem			*GetSelectedItem (void)
							{
								ui16 idx = 0;

								for (ui8 i = 0; i < sMenuCount; i++)
								{
									idx += ((sMenu*) psMenu)[i].nItems;

									if (SelectedItemIdx < idx)
										return &((sMenu*)psMenu)[i].psItems[((sMenu*)psMenu)[i].nItems - (idx - SelectedItemIdx)];
								}

								return 0;
							}

		int					GetIwidth (GWidgetObject *gw)
							{
								return scrollBarEnabled ?
										(gw->g.width - MENU_SCROLL_HOR_LPAD - MENU_SCROLL_WIDTH - MENU_SCROLL_HOR_RPAD) :
										gw->g.width;
							}

		void				Draw (GWidgetObject* gw, void* param);

		void				ButtonUp (GWidgetObject* gw);
		void				ButtonDown (GWidgetObject* gw);
		void				ButtonLeft (GWidgetObject* gw);
		void				ButtonRigth (GWidgetObject* gw);
		void				ButtonEnter (GWidgetObject* gw);

		void				UpdateMenu (GWidgetObject *gw);

};


typedef struct GMenuObject
{
	GWidgetObject	w;
	CGWIN_Menu		*class_obj;

}	GMenuObject;


typedef enum
{
	PMS_REMOTE				= 0,
	PMS_GIMBAL

}	ParameterMembership_t;


typedef struct
{
	FuncIdEnum_t	type;

	ParameterMembership_t
					membership;

	void			*operatingValue;
	float			origDivider;

	i32				initValue,
					tempValue,
					minValue,
					maxValue;

	sbgcVarType_t	typeValue;

	const char		*name;

	float			sensitivity,
					filter,
					divider;

	ui16			oldControlValue,
					newControlValue;

}	ParameterHandle_t;


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _GWIN_MENU_PREF_H_ */
