/** ____________________________________________________________________
 *
 *	@file		colors.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include	"colors.h"


GWidgetStyle CWidgetStyle::MonoProgressbarStyle = {
		GFX_BLACK, GFX_BLACK,
	{GFX_BLACK, GFX_LIGHT_GRAY, GFX_BLACK, GFX_LIGHT_GRAY},
	{GFX_BLACK, GFX_BLACK, GFX_BLACK, GFX_BLACK},
	{GFX_BLACK, GFX_BLACK, GFX_BLACK, GFX_BLACK}
};


GWidgetStyle CWidgetStyle::MonoImgStyleNormal = {
		GFX_BLACK, GFX_BLACK,
	{GFX_LIGHT_GRAY, GFX_BLACK, GFX_BLACK, GFX_BLACK},
	{GFX_LIGHT_GRAY, GFX_BLACK, GFX_BLACK, GFX_BLACK},
	{GFX_LIGHT_GRAY, GFX_BLACK, GFX_BLACK, GFX_BLACK}
};


GWidgetStyle CWidgetStyle::MonoImgStyleInvert = {
		GFX_BLACK, GFX_BLACK,
	{GFX_BLACK, GFX_BLACK, GFX_LIGHT_GRAY, GFX_BLACK},
	{GFX_BLACK, GFX_BLACK, GFX_LIGHT_GRAY, GFX_BLACK},
	{GFX_BLACK, GFX_BLACK, GFX_LIGHT_GRAY, GFX_BLACK}
};


GWidgetStyle CWidgetStyle::MonoImgStyleInactive = {
		GFX_BLACK, GFX_BLACK,
	{GFX_DARK_GRAY, GFX_BLACK, GFX_BLACK, GFX_BLACK},
	{GFX_DARK_GRAY, GFX_BLACK, GFX_BLACK, GFX_BLACK},
	{GFX_DARK_GRAY, GFX_BLACK, GFX_BLACK, GFX_BLACK}
};


GWidgetStyle CWidgetStyle::MonoImgStyleLabelNormal = {
		GFX_BLACK, GFX_BLACK,
	{GFX_LIGHT_GRAY, GFX_BLACK, GFX_BLACK, GFX_BLACK},
	{GFX_LIGHT_GRAY, GFX_BLACK, GFX_BLACK, GFX_BLACK},
	{GFX_LIGHT_GRAY, GFX_BLACK, GFX_BLACK, GFX_BLACK}
};


GWidgetStyle CWidgetStyle::MonoImgStyleLabelNormalFramed = {
		GFX_BLACK, GFX_BLACK,
	{GFX_LIGHT_GRAY, GFX_LIGHT_GRAY, GFX_BLACK, GFX_BLACK},
	{GFX_LIGHT_GRAY, GFX_LIGHT_GRAY, GFX_BLACK, GFX_BLACK},
	{GFX_LIGHT_GRAY, GFX_LIGHT_GRAY, GFX_BLACK, GFX_BLACK}
};


GWidgetStyle CWidgetStyle::MonoImgStyleLabelDimmed = {
		GFX_BLACK, GFX_BLACK,
	{GFX_GRAY, GFX_BLACK, GFX_BLACK, GFX_BLACK},
	{GFX_GRAY, GFX_BLACK, GFX_BLACK, GFX_BLACK},
	{GFX_GRAY, GFX_BLACK, GFX_BLACK, GFX_BLACK}
};


GWidgetStyle CWidgetStyle::MonoImgStyleLabelInvert = {
		GFX_LIGHT_GRAY, GFX_BLACK,
	{GFX_BLACK, GFX_BLACK, GFX_LIGHT_GRAY, GFX_BLACK},
	{GFX_BLACK, GFX_BLACK, GFX_LIGHT_GRAY, GFX_BLACK},
	{GFX_BLACK, GFX_BLACK, GFX_LIGHT_GRAY, GFX_BLACK}
};


GWidgetStyle CWidgetStyle::MonoImgStyleLabelInvertGray = {
		GFX_GRAY, GFX_BLACK,
	{GFX_BLACK, GFX_BLACK, GFX_GRAY, GFX_BLACK},
	{GFX_BLACK, GFX_BLACK, GFX_GRAY, GFX_BLACK},
	{GFX_BLACK, GFX_BLACK, GFX_GRAY, GFX_BLACK}
};
