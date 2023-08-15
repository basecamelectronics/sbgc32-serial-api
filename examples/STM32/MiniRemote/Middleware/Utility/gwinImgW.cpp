/** ____________________________________________________________________
 *
 *	@file		gwinImgW.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "gwinImgW.h"

#ifdef __cplusplus
	extern "C" {
#endif

#include "src/gwin/gwin_class.h"

#ifdef __cplusplus
	}
#endif


#if GFX_USE_GWIN && GWIN_NEED_CUSTOM_IMAGE_WIDGET


// The button VMT table
static const gwidgetVMT ImageW_VMT = {
	{
		"ImageW",				// The classname
		sizeof(GImageWObject),	// The object size
		_gwidgetDestroy,		// The destroy routine
		_gwidgetRedraw,			// The redraw routine
		0,						// The after-clear routine
	},
	gwinImageWDraw,			// The default drawing routine
	#if GINPUT_NEED_MOUSE
		{
			0,		// Process mouse down events
			0,			// Process mouse up events
			0,						// Process mouse move events (NOT USED)
		},
	#endif
	#if GINPUT_NEED_KEYBOARD || GWIN_NEED_KEYBOARD
		{
			0			// Process keyboard events
		},
	#endif
	#if GINPUT_NEED_TOGGLE
		{
			0,						// 1 toggle role
			0,		// Assign Toggles
			0,		// Get Toggles
			0,		// Process toggle off events
			0,			// Process toggle on events
		},
	#endif
	#if GINPUT_NEED_DIAL
		{
			0,						// No dial roles
			0,						// Assign Dials (NOT USED)
			0,						// Get Dials (NOT USED)
			0,						// Process dial move events (NOT USED)
		},
	#endif
};

GHandle gwinGImageWCreate(GDisplay *g, GImageWObject *gw, const GWidgetInit *pInit) {
	if (!(gw = (GImageWObject *)_gwidgetCreate(g, &gw->w, pInit, &ImageW_VMT)))
		return 0;

	#if GINPUT_NEED_TOGGLE
		gw->toggle = GWIDGET_NO_INSTANCE;
	#endif
	gwinSetVisible((GHandle)gw, pInit->g.show);
	return (GHandle)gw;
}


#if GDISP_NEED_IMAGE || defined(__DOXYGEN__)
	void gwinImageWDraw(GWidgetObject *gw, void *param)
	{
		gCoord sy = 0;

		if (gw->g.vmt != (gwinVMT *)&ImageW_VMT) return;

		// Set the clipping region so we do not override the frame.
	#if GDISP_NEED_CLIP
		gdispGSetClip(gdispGetDisplay(1), gw->g.x, gw->g.y, gw->g.width, gw->g.height);
	#endif

		// clear all
		gdispGFillArea(gdispGetDisplay(1), gw->g.x, gw->g.y, gw->g.width, gw->g.height, GFX_BLACK);
		gdispGImageDraw(gdispGetDisplay(1), (gdispImage *)param, gw->g.x, gw->g.y, gw->g.width, gw->g.height, 0, sy);
	}

	void gwinImageWDrawCenter(GWidgetObject *gw, void *param)
	{
		gCoord sx = 0, sy = 0;

		if (gw->g.vmt != (gwinVMT *)&ImageW_VMT) return;

		// Set the clipping region so we do not override the frame.
	#if GDISP_NEED_CLIP
		gdispGSetClip(gdispGetDisplay(1), gw->g.x, gw->g.y, gw->g.width, gw->g.height);
	#endif

		// clear all
		gdispGFillArea(gdispGetDisplay(1), gw->g.x, gw->g.y, gw->g.width, gw->g.height, GFX_BLACK);

		if (gw->g.width>((gdispImage *)param)->width)
			sx = (gw->g.width-((gdispImage *)param)->width) / 2;

		if (gw->g.height>((gdispImage *)param)->height)
			sy = (gw->g.height-((gdispImage *)param)->height) / 2;

		gdispGImageDraw(gdispGetDisplay(1), (gdispImage *)param, gw->g.x+sx, gw->g.y+sy, gw->g.width-sx, gw->g.height-sy, 0, 0);
	}
#endif

#endif /* GFX_USE_GWIN && GWIN_NEED_BUTTON */
