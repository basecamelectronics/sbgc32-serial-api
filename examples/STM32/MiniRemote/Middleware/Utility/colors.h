/** ____________________________________________________________________
 *
 *	@file		colors.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_COLORS_H_
#define		_COLORS_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"ugfxHelper.h"

#define		GFX_DARK_GRAY			HTML2COLOR(0x404040)
#define		GFX_LIGHT_GRAY			HTML2COLOR(0xC0C0C0)


class CMenuColors
{
	public:

		static color_t button_select;
		static color_t button;
		static color_t edit_link;
		static color_t select;
		static color_t non_select;
		static color_t title;

};


class CWidgetStyle
{
	public :

		static GWidgetStyle MonoProgressbarStyle;

		static GWidgetStyle MonoProfileStyleSelect;
		static GWidgetStyle MonoProfileStyleDeselect;
		static GWidgetStyle MonoProfileStyleChoice;
		static GWidgetStyle MonoProfileStyleChoiceSelect;

		static GWidgetStyle MonoImgStyleNormal;
		static GWidgetStyle MonoImgStyleInvert;
		static GWidgetStyle MonoImgStyleInactive;
		static GWidgetStyle MonoFocusStyle;

		static GWidgetStyle MonoImgStyleLabelNormal;
		static GWidgetStyle MonoImgStyleLabelNormalFramed;
		static GWidgetStyle MonoImgStyleLabelDimmed;
		static GWidgetStyle MonoImgStyleLabelInvert;
		static GWidgetStyle MonoImgStyleLabelInvertGray;

};


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _COLORS_H_ */
