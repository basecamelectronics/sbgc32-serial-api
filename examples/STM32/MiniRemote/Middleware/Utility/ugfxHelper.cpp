/** ____________________________________________________________________
 *
 *	@file		ugfxHelper.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "ugfxHelper.h"
#include "gfx.h"
#include "src/gwin/gwin_class.h"
#include "Utils.h"
#include "printf.h"
#include "system.h"


void image_conversion (GDisplay *pPixmap, gColor fg, gColor bg);


#define		gw2obj					((GLabelObject *)gw)
void gwinLabelDrawJustifiedCustom(GWidgetObject *gw, void *param) {
	gCoord				w, h;
	gColor				c;

	gJustify justify = (gJustify)((uint32_t)param);

//	// is it a valid handle?
//	if (gw->g.vmt != (gwinVMT *)&labelVMT)
//		return;

	w = gw->g.width;
	h = gw->g.height;
	c = (gw->g.flags & GWIN_FLG_SYSENABLED) ? gw->pstyle->enabled.text : gw->pstyle->disabled.text;

	// Set the clipping region so we do not override the frame.
#if GDISP_NEED_CLIP
	gdispGSetClip(gdispGetDisplay(0), gw->g.x, gw->g.y, gw->g.width, gw->g.height);
	gdispGSetClip(gdispGetDisplay(1), gw->g.x, gw->g.y, gw->g.width, gw->g.height);
#endif

	// clear all
	gdispGFillArea(gdispGetDisplay(0), gw->g.x, gw->g.y, gw->g.width, gw->g.height, gw->pstyle->background);
	gdispGFillArea(gdispGetDisplay(1), gw->g.x, gw->g.y, gw->g.width, gw->g.height, (gColor)0xFF000000);


	#if GWIN_LABEL_ATTRIBUTE
		if (gw2obj->attr) {
			gdispGDrawStringBox(gw->g.display, gw->g.x, gw->g.y, gw2obj->tab, h, gw2obj->attr, gw->g.font, c, justify);
			gdispGDrawStringBox(gw->g.display, gw->g.x + gw2obj->tab, gw->g.y,
								w-gw2obj->tab, h, gw->text, gw->g.font, c, justify);
		} else
			gdispGDrawStringBox(gw->g.display, gw->g.x, gw->g.y, w, h, gw->text, gw->g.font, c, justify);
	#else
		gdispGDrawStringBox(gw->g.display, gw->g.x, gw->g.y, w, h, gw->text, gw->g.font, c, justify);
	#endif

	// render the border (if any)
	if (gw->g.flags & GLABEL_FLG_BORDER)
		gdispGDrawBox(gw->g.display, gw->g.x, gw->g.y, w, h, (gw->g.flags & GWIN_FLG_SYSENABLED) ?
				gw->pstyle->enabled.edge : gw->pstyle->disabled.edge);
}
#undef gw2obj

void _gwinUpdateCustom(GHandle gh) {
	_gwinUpdate(gh);
}


void gwinCheckboxDraw_Custom(GWidgetObject *gw, void *param)
{

#if(GDISP_NEED_PIXMAP == GFXON)
	#define gsw			((GSliderObject*)gw)
	#define gpixmap			((GDisplay**)param)

	//if (gw->g.vmt != (gwinVMT *)&checkboxVMT)	return;

#if GDISP_NEED_CLIP
	gdispGSetClip(gdispGetDisplay(0), gw->g.x, gw->g.y, gw->g.width, gw->g.height);
	gdispGSetClip(gdispGetDisplay(1), gw->g.x, gw->g.y, gw->g.width, gw->g.height);
#endif


		GDisplay *pPixmap;
		if(gwinCheckboxIsChecked(&gw->g)){
			pPixmap = gpixmap[1];
		}else{
			pPixmap = gpixmap[0];
		}

		pixel_t *_buffer = gdispPixmapGetBits(pPixmap);
		coord_t PixmapWidth = gdispGGetWidth(pPixmap);
		coord_t PixmapHeight = gdispGGetHeight(pPixmap);

		// clear slider area
		gdispGFillArea(gdispGetDisplay(0), gw->g.x, gw->g.y, gw->g.width, gw->g.height, GFX_WHITE);

		gdispGBlitArea(gdispGetDisplay(1),
				gw->g.x + (float)(gw->g.width-PixmapWidth)/2,
				gw->g.y+1+(gw->g.height - PixmapHeight)/2,
				PixmapWidth,
				PixmapHeight,
				0, 0, PixmapWidth, _buffer);


	#undef gsw
	#undef gpixmap

#endif
}

void gwinRectangleDrawCustom(GWidgetObject *gw, void *param) {
	(void)				param;

	// Set the clipping region so we do not override the frame.
#if GDISP_NEED_CLIP
	gdispGSetClip(gdispGetDisplay(0), gw->g.x, gw->g.y, gw->g.width, gw->g.height);
#if (GDISP_TOTAL_DISPLAYS==2)
	gdispGSetClip(gdispGetDisplay(1), gw->g.x, gw->g.y, gw->g.width, gw->g.height);
#endif
#endif

	// clear all
	gdispGFillArea(gdispGetDisplay(0), gw->g.x, gw->g.y, gw->g.width, gw->g.height, GFX_BLACK);
#if (GDISP_TOTAL_DISPLAYS==2)
	gdispGFillArea(gdispGetDisplay(1), gw->g.x, gw->g.y, gw->g.width, gw->g.height, GFX_BLACK);
#endif
}

void gwinProgressbarDrawCustom(GWidgetObject *gw, void *param) {
	#define gsw			((GProgressbarObject *)gw)

	const GColorSet *	pcol;
	(void)				param;

	// Set the clipping region so we do not override the frame.
#if GDISP_NEED_CLIP
	gdispGSetClip(gdispGetDisplay(0), gw->g.x, gw->g.y, gw->g.width, gw->g.height);
	gdispGSetClip(gdispGetDisplay(1), gw->g.x, gw->g.y, gw->g.width, gw->g.height);
#endif

	// clear all
	gdispGFillArea(gdispGetDisplay(0), gw->g.x, gw->g.y, gw->g.width, gw->g.height, gw->pstyle->background);
	gdispGFillArea(gdispGetDisplay(1), gw->g.x, gw->g.y, gw->g.width, gw->g.height, (gColor)0xFF000000);


	// get the colors right
	if ((gw->g.flags & GWIN_FLG_SYSENABLED))
		pcol = &gw->pstyle->enabled;
	else
		pcol = &gw->pstyle->disabled;

	// Vertical progressbar
	if (gw->g.width < gw->g.height) {
		if (gsw->dpos != gw->g.height-1)
			gdispGFillArea(gw->g.display, gw->g.x, gw->g.y+gsw->dpos, gw->g.width, gw->g.height - gsw->dpos, pcol->progress);
		if (gsw->dpos != 0)
			gdispGFillArea(gw->g.display, gw->g.x, gw->g.y, gw->g.width, gsw->dpos, pcol->fill);
		gdispGDrawBox(gw->g.display, gw->g.x, gw->g.y, gw->g.width, gw->g.height, pcol->edge);
		gdispGDrawLine(gw->g.display, gw->g.x, gw->g.y+gsw->dpos, gw->g.x+gw->g.width-1, gw->g.y+gsw->dpos, pcol->edge);

	// Horizontal progressbar
	} else {
		if (gsw->dpos != gw->g.width-1)
			gdispGFillArea(gw->g.display, gw->g.x+gsw->dpos, gw->g.y, gw->g.width-gsw->dpos, gw->g.height, pcol->fill);
		if (gsw->dpos != 0)
			gdispGFillArea(gw->g.display, gw->g.x, gw->g.y, gsw->dpos, gw->g.height, pcol->progress);
		gdispGDrawBox(gw->g.display, gw->g.x, gw->g.y, gw->g.width, gw->g.height, pcol->edge);
		gdispGDrawLine(gw->g.display, gw->g.x+gsw->dpos, gw->g.y, gw->g.x+gsw->dpos, gw->g.y+gw->g.height-1, pcol->edge);
	}
	gdispGDrawStringBox(gw->g.display, gw->g.x+1, gw->g.y+1, gw->g.width-2, gw->g.height-2,
						gw->text, gw->g.font, pcol->text, gJustifyCenter);

	#undef gsw
}


#include "gdisp_driver.h"
#include "../gdriver/gdriver.h"


/* For prevention of heap fragmentation and speed up */
GDisplay *gdispPixmapCreateCustom (gCoord width, gCoord height)
{
	static bool isCreated = false;
	static GDisplay *g;

	if (!isCreated)
	{
		isCreated = true;
		g = gdispPixmapCreate(CONTAINER_TOP_BOTTOM_HEIGHT, DISPLAY_WIDTH);
	}

	g->g.Width = width;
	g->g.Height = height;
	g->clipx1 = width;
	g->clipy1 = height;

	return g;
}


void gwinArrow_Mono (GWidgetObject *gw, void *param)
{
	unused_(param);

	const GColorSet *pcol;

	/* Get the colors right */
	if ((gw->g.flags & GWIN_FLG_SYSENABLED))
		pcol = &gw->pstyle->enabled;
	else
		pcol = &gw->pstyle->disabled;

	gJustify justify = *((gJustify*)(&param));

	GDisplay *pPixmap = gdispPixmapCreateCustom(gw->g.width, gw->g.height);

	gdispGFillArea(pPixmap, 0, 0, gw->g.width, gw->g.height, gw->pstyle->background);

	int* coord_buf;

	int bufLeft[] = {
			gw->g.width, 0, 0, gw->g.height/2,
			0, gw->g.height/2, gw->g.width, gw->g.height
	};

	int bufRight[] = {
			0, 0, gw->g.width - 1, gw->g.height/2,
			gw->g.width, gw->g.height/2, 0, gw->g.height
	};

	int bufTop[] = {
			0, gw->g.height, gw->g.width/2, 0,
			gw->g.width/2, 0, gw->g.width, gw->g.height
	};

	int bufBottom[] = {
			0, 0, gw->g.width/2, gw->g.height - 1,
			gw->g.width/2, gw->g.height, gw->g.width, 0
	};

	switch (justify) {
		case gJustifyLeft:
			coord_buf = bufLeft;
			break;
		case gJustifyRight:
			coord_buf = bufRight;
			break;
		case gJustifyTop:
			coord_buf = bufTop;
			break;
		case gJustifyBottom:
			coord_buf = bufBottom;
			break;
		default:
			coord_buf = NULL;
			break;
	}

	gdispGDrawLineWu(pPixmap, coord_buf[0],coord_buf[1],coord_buf[2],coord_buf[3], pcol->text, gw->pstyle->background);
	gdispGDrawLineWu(pPixmap, coord_buf[4],coord_buf[5],coord_buf[6],coord_buf[7], pcol->text, gw->pstyle->background);
	gdispGBlitArea(gw->g.display, gw->g.x, gw->g.y, gw->g.width, gw->g.height, 0, 0, gw->g.width, gdispPixmapGetBits(pPixmap));
}


void ContainerDrawMono (GWidgetObject *gw, void *param)
{
	const GColorSet *pcol;

	/* Get the colors right */
	if (gw->g.flags & GWIN_FLG_SYSENABLED)
		pcol = &gw->pstyle->enabled;

	else
		pcol = &gw->pstyle->disabled;

	GDisplay *pPixmap = gdispPixmapCreateCustom(gw->g.width, CONTAINER_TOP_BOTTOM_HEIGHT);

	/* Top label */
	gdispGFillArea(pPixmap, 0, 0, gw->g.width, CONTAINER_TOP_BOTTOM_HEIGHT, gw->pstyle->background);
	gdispGDrawStringBox(pPixmap, 0, 0, gw->g.width, CONTAINER_TOP_BOTTOM_HEIGHT,
			((sContainerDraw*)param)->textTop, MiniRemote.GetLargeFont(), GFX_GRAY, gJustifyCenter);
	gdispGBlitArea(gw->g.display, gw->g.x, WIDGET_VERT_MARGIN,
			gw->g.width, CONTAINER_TOP_BOTTOM_HEIGHT, 0, 0, gw->g.width, gdispPixmapGetBits(pPixmap));

	/* Top line */
	gdispGDrawLine(gw->g.display, gw->g.x, gw->g.y + EDIT_TITLE_TOTAL_HEIGHT,
			gw->g.x + gw->g.width, gw->g.y + EDIT_TITLE_TOTAL_HEIGHT, pcol->text);

	/* Bottom label */
	gdispGFillArea(pPixmap, 0, 0, gw->g.width, CONTAINER_TOP_BOTTOM_HEIGHT, gw->pstyle->background);
	gdispGDrawStringBox(pPixmap, 0, 0, gw->g.width, CONTAINER_TOP_BOTTOM_HEIGHT,
			((sContainerDraw*)param)->textBottom, MiniRemote.GetSmallFont(), GFX_GRAY, gJustifyCenter);
	gdispGBlitArea(gw->g.display, gw->g.x, DISPLAY_HEIGHT - SMALL_FONT_HEIGHT - WIDGET_VERT_MARGIN - 2,
			gw->g.width, CONTAINER_TOP_BOTTOM_HEIGHT, 0, 0, gw->g.width, gdispPixmapGetBits(pPixmap));
}


void gwinProgressbarDrawJoystickVisualMono (GWidgetObject *gw, void *param)
{
	#define gsw ((GProgressbarObject*)gw)

	const GColorSet *pcol;

	/* Get the colors right */
	if ((gw->g.flags & GWIN_FLG_SYSENABLED))
		pcol = &gw->pstyle->enabled;
	else
		pcol = &gw->pstyle->disabled;

	GDisplay *pPixmap = gdispPixmapCreateCustom(gw->g.width, gw->g.height);

	gdispGFillArea(pPixmap, 1, 1, gw->g.width - 2, gw->g.height - 2, gw->pstyle->background);
	gdispGDrawBox(pPixmap, 0, 0, gw->g.width, gw->g.height, pcol->edge);
	gdispGDrawLine(pPixmap, gw->g.width / 2 - 1, 1, gw->g.width / 2 - 1, gw->g.height, pcol->edge);
	gdispGDrawLine(pPixmap, 0, gw->g.height / 2 - 1, gw->g.width, gw->g.height / 2 - 1, pcol->edge);

	i16 x = gsw->pos / 100. * (gw->g.width - CALIB_CIRCLE_RADIUS) + ((CALIB_CIRCLE_RADIUS / 2) - 1);
	i16 y = (1. - (*(i16*) param) / 100.) * (gw->g.height - CALIB_CIRCLE_RADIUS) + ((CALIB_CIRCLE_RADIUS / 2) - 1);

	gdispGFillCircle(pPixmap, x, y, CALIB_CIRCLE_RADIUS, pcol->edge);

	gdispGBlitArea(gw->g.display, gw->g.x, gw->g.y, gw->g.width, gw->g.height, 0, 0, gw->g.width, gdispPixmapGetBits(pPixmap));

	#undef gsw
}


void gwinProgressbarDrawPotentiometerVisualMono (GWidgetObject *gw, void *param)
{
	unused_(param);

	const GColorSet *pcol;

	ui16	minTemp = MiniRemote.Presets.handlersCalibs.potMin,
			maxTemp = MiniRemote.Presets.handlersCalibs.potMax;

	ui16	lineMinY = (gw->g.height - 1) - (((minTemp * 1.0F) / ANALOG_IN_MAX_VALUE) * gw->g.height),
			lineMaxY = (gw->g.height - 1) - (((maxTemp * 1.0F) / ANALOG_IN_MAX_VALUE) * gw->g.height);

	/* Get the colors right */
	if ((gw->g.flags & GWIN_FLG_SYSENABLED))
		pcol = &gw->pstyle->enabled;
	else
		pcol = &gw->pstyle->disabled;

	GDisplay *pPixmap = gdispPixmapCreateCustom(gw->g.width, gw->g.height);

	gdispGFillArea(pPixmap, 1, 1, gw->g.width - 2, gw->g.height - 2, gw->pstyle->background);
	gdispGDrawBox(pPixmap, 0, 0, gw->g.width, gw->g.height, pcol->edge);

	gdispGDrawLine(pPixmap, 0, lineMinY, gw->g.width - 1, lineMaxY, pcol->edge);

	ui8 x = ((GProgressbarObject*)gw)->pos / (ANALOG_IN_MAX_VALUE + 1.0F) * (gw->g.width - CALIB_CIRCLE_RADIUS) + 1;
	ui8 y = lineMinY - ((lineMinY - lineMaxY) * ((x * 1.0F) / gw->g.width));

	gdispGFillCircle(pPixmap, x, y, CALIB_CIRCLE_RADIUS, pcol->edge);

	gdispGBlitArea(gw->g.display, gw->g.x, gw->g.y, gw->g.width, gw->g.height, 0, 0, gw->g.width, gdispPixmapGetBits(pPixmap));
}


void gwinProgressbarDrawCustom_Mono(GWidgetObject *gw, void *param)
{
	unused_(param);

	#define gsw	((GProgressbarObject*)gw)

	const GColorSet *pcol;

	/* Get the colors right */
	if ((gw->g.flags & GWIN_FLG_SYSENABLED))
		pcol = &gw->pstyle->enabled;
	else
		pcol = &gw->pstyle->disabled;

	/* Vertical progressbar */
	if (gw->g.width < gw->g.height) {
		if (gsw->dpos != gw->g.height-1)
			gdispGFillArea(gw->g.display, gw->g.x, gw->g.y+gsw->dpos, gw->g.width, gw->g.height - gsw->dpos, pcol->progress);
		if (gsw->dpos != 0)
			gdispGFillArea(gw->g.display, gw->g.x+1, gw->g.y+1, gw->g.width-2, gsw->dpos-1, pcol->fill);
		gdispGDrawBox(gw->g.display, gw->g.x, gw->g.y, gw->g.width, gw->g.height, pcol->edge);
		gdispGDrawLine(gw->g.display, gw->g.x, gw->g.y+gsw->dpos, gw->g.x+gw->g.width-1, gw->g.y+gsw->dpos, pcol->edge);

	/* Horizontal progressbar */
	} else {
		if (gsw->dpos != gw->g.width-1)
			gdispGFillArea(gw->g.display, gw->g.x+gsw->dpos, gw->g.y+1, gw->g.width-gsw->dpos-1, gw->g.height-2, pcol->fill);
		if (gsw->dpos != 0)
			gdispGFillArea(gw->g.display, gw->g.x, gw->g.y, gsw->dpos, gw->g.height, pcol->progress);
		gdispGDrawBox(gw->g.display, gw->g.x, gw->g.y, gw->g.width, gw->g.height, pcol->edge);
		gdispGDrawLine(gw->g.display, gw->g.x+gsw->dpos, gw->g.y, gw->g.x+gsw->dpos, gw->g.y+gw->g.height-1, pcol->edge);
	}

	#undef gsw
}


void gwinLabelDrawJustifiedCustomMono (GWidgetObject *gw, void *param)
{
	gColor		c;
	gJustify 	justify = *((gJustify*)(&param));

	#define gw2obj ((GLabelObject*)gw)

	GDisplay *pPixmap = gdispPixmapCreateCustom(gw->g.width, gw->g.height);

	c = (gw->g.flags & GWIN_FLG_SYSENABLED) ? gw->pstyle->enabled.text : gw->pstyle->disabled.text;

	#if GWIN_LABEL_ATTRIBUTE
		if (gw2obj->attr) {
			gdispGFillStringBox(pPixmap, 0, 0, gw2obj->tab, gw->g.height, gw2obj->attr,
								gw->g.font, c, gw->pstyle->background, justify);
			gdispGFillStringBox(pPixmap, gw2obj->tab, 0, gw->g.width-gw2obj->tab, gw->g.height,
								gw->text, gw->g.font, c, gw->pstyle->background, justify);
		} else
			gdispGFillStringBox(pPixmap, 0, 0, gw->g.width, gw->g.height, gw->text, gw->g.font, c, gw->pstyle->background, justify);
	#else
		gdispGFillStringBox(pPixmap, 0, 0, gw->g.width, gw->g.height, gw->text, gw->g.font, c, gw->pstyle->background, justify);
	#endif

	gdispGDrawBox(pPixmap, 0, 0, gw->g.width, gw->g.height, (gw->g.flags & GWIN_FLG_SYSENABLED) ?
				  gw->pstyle->enabled.edge : gw->pstyle->disabled.edge);


	gdispGBlitArea(gw->g.display, gw->g.x, gw->g.y, gw->g.width, gw->g.height, 0, 0, gw->g.width, gdispPixmapGetBits(pPixmap));
}


void gwinImageWDrawCustom_Mono(GWidgetObject *gw, void *param)
{
	const GColorSet *pcol;
	gCoord sy = 0;

	// get the colors right
	if ((gw->g.flags & GWIN_FLG_SYSENABLED))
		pcol = &gw->pstyle->enabled;
	else
		pcol = &gw->pstyle->disabled;

	// Set the clipping region so we do not override the frame.
	GDisplay *pPixmap = gdispPixmapCreateCustom(gw->g.width, gw->g.height);

	// clear all
	gdispGFillArea(pPixmap, 0, 0, gw->g.width, gw->g.height, pcol->text);

	if (gw->g.height>((gdispImage*)param)->height)
		sy = (gw->g.height>((gdispImage *)param)->height) / 2;

	gdispImage **param_img = (gdispImage**)param;
	gdispGImageDraw(pPixmap, *param_img, 0, 0, gw->g.width, gw->g.height, 0, sy);

	gPixel	*pixels = gdispPixmapGetBits(pPixmap);
	for (ui16 i = 0; i < (gw->g.width * gw->g.height); ++i)
		pixels[i] = gdispBlendColor(pcol->text, gw->pstyle->background, 255 - GREEN_OF(pixels[i]));

#if GDISP_NEED_CLIP
	gdispGSetClip(gw->g.display, gw->g.x, gw->g.y, gw->g.width, gw->g.height);
#endif
	gdispGBlitArea(gw->g.display, gw->g.x, gw->g.y, gw->g.width, gw->g.height, 0, 0, gw->g.width, gdispPixmapGetBits(pPixmap));
}

void gwinImageWOpenAndDrawCustom_Mono(GWidgetObject *gw, void *param)
{
	const GColorSet *pcol;
	gCoord sy = 0;

	// get the colors right
	if ((gw->g.flags & GWIN_FLG_SYSENABLED))
		pcol = &gw->pstyle->enabled;
	else
		pcol = &gw->pstyle->disabled;

	// Set the clipping region so we do not override the frame.
	GDisplay *pPixmap = gdispPixmapCreateCustom(gw->g.width, gw->g.height);

	// clear all
	gdispGFillArea(pPixmap, 0, 0, gw->g.width, gw->g.height, pcol->fill);
	{
		if (gw->g.height>((gdispImage*)param)->height)
			sy = (gw->g.height>((gdispImage*)param)->height) / 2;
	}

	gdispImage* img = 0;
	Utils::imageOpenFile(img, (const char*)param);
	gdispGImageDraw(pPixmap, img, 0, 0, gw->g.width, gw->g.height, 0, sy);
	Utils::imageCloseFile(img);

	image_conversion(pPixmap, pcol->text, pcol->fill);

#if GDISP_NEED_CLIP
	gdispGSetClip(gw->g.display, gw->g.x, gw->g.y, gw->g.width, gw->g.height);
#endif
	gdispGBlitArea(gw->g.display, gw->g.x, gw->g.y, gw->g.width, gw->g.height, 0, 0, gw->g.width, gdispPixmapGetBits(pPixmap));
}

void image_conversion(GDisplay *pPixmap, gColor fg, gColor bg)
{
	gPixel *pixels = gdispPixmapGetBits(pPixmap);

	for (ui16 i = 0; i < (pPixmap->g.Width * pPixmap->g.Height); ++i)
		pixels[i] = gdispBlendColor(fg, bg, 255-GREEN_OF(pixels[i]));
}

	inline fixed intToFixed(int value) {
	return (value << 16);
}

inline int fixedToInt(fixed value) {
	if (value < 0)
		return ((value >> 16) - 1);
	else
		return (value >> 16);
}

//writes the ratio (a / b) in the format of a fixed-point numbers
inline fixed fracToFixed(int a, int b) {
	return (a << 16) / b;
}

inline float fractionalPart(fixed a) {

	int p = a - intToFixed(fixedToInt(a));
	int s = 1 << 16;
	float d = p;
	//if (d / s) throw new int;
	return d / s;
}

inline void swap(gCoord &a, gCoord &b) {
	int t;
	t = a;
	a = b;
	b = t;
}

void gdispGDrawLineWu(GDisplay *g, gCoord x0, gCoord y0, gCoord x1, gCoord y1, gColor color, gColor background){

	float alpha;

	//The calculation of the coordinates
	int dx = (x1 > x0) ? (x1 - x0) : (x0 - x1);
	int dy = (x1 > x0) ? (y1 - y0) : (y0 - y1);

	//If the line is parallel to one of the axis, draw an usual line - fill all the pixels in a row
	if (dx == 0) {
		if (y1 < y0) {
			swap(x0, x1);
			swap(y0, y1);
		}
		for (int i = y0; i <= y1; i++) {
			//SetPixel(hdc, x1, i, color);
			gdispGDrawPixel(g, x1, i, color);
		}
		return;
	}
	if (dy == 0) {

		if (x1 < x0) {
			swap(x0, x1);
			swap(y0, y1);
		}
		for (int i = x0; i <= x1; i++) {
			//SetPixel(hdc, i, y0, color);
			gdispGDrawPixel(g, i, y0, color);
		}
		return;
	}

	//For the X-line (slope coefficient < 1)
	if (abs(dy) < dx) {
		//The first point must have a smaller x coordinate
		if (x1 < x0) {
			swap(x0, x1);
			swap(y0, y1);
		}

		fixed grad = fracToFixed(dy, dx);
		fixed intery = intToFixed(y0) + grad;

		//First point
		//SetPixel(hdc, x0, y0, color);
		gdispGDrawPixel(g, x0, y0, color);

		for (int x = x0 + 1; x < x1; x++) {
			alpha = (fractionalPart(intery));

			//SetPixel(hdc, x, fixedToInt(intery), RGB(255 * alpha, 255 * alpha, 255 * alpha));
			gdispGDrawPixel(g, x, fixedToInt(intery), gdispBlendColor(color, background, 255 * (1. - alpha)));

			//SetPixel(hdc, x, fixedToInt(intery) + 1, (RGB(255 * (1 - alpha), 255 * (1 - alpha), 255 * (1 - alpha))));
			gdispGDrawPixel(g, x, fixedToInt(intery) + 1, gdispBlendColor(color, background, 255 * (alpha)));
			intery += grad;
		}
		//Last point
		//SetPixel(hdc, x1, y1, color);
		gdispGDrawPixel(g, x1, y1, color);

	}
	//For the Y-line (slope coefficient > 1)
	else {
		if (y1 < y0) {
			swap(x0, x1);
			swap(y0, y1);
		}

		fixed grad = fracToFixed(dx, dy);

		fixed interx = intToFixed(x0) + grad;

		//SetPixel(hdc, x0, y0, color);
		gdispGDrawPixel(g, x0, y0, color);

		for (int y = y0 + 1; y < y1; y++) {
			alpha = (fractionalPart(interx));

			//SetPixel(hdc, fixedToInt(interx), y, RGB(255 * alpha, 255 * alpha, 255 * alpha));
			gdispGDrawPixel(g, fixedToInt(interx), y, gdispBlendColor(color, background, 255 * (1. - alpha)));

			//SetPixel(hdc, fixedToInt(interx) + 1, y, (RGB(255 * (1 - alpha), 255 * (1 - alpha), 255 * (1 - alpha))));
			gdispGDrawPixel(g, fixedToInt(interx) + 1, y, gdispBlendColor(color, background, 255 * (alpha)));
			interx += grad;

		}
		//SetPixel(hdc, x1, y1, color);
		gdispGDrawPixel(g, x1, y1, color);
	}
}
