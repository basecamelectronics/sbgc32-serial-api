/** ____________________________________________________________________
 *
 *	@file		gwinImgW.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_GWIN_IMG_W_H_
#define		_GWIN_IMG_W_H_

/* This file is included within "src/gwin/gwin_widget.h" */
#include "gfx.h"

/**
 * @brief	The button widget structure
 * @note	Do not use the members directly - treat it as a black-box.
 */
typedef struct GImageWObject {
	GWidgetObject		w;
} GImageWObject;

/**
 * @brief   Create a button widget.
 * @return  NULL if there is no resultant drawing area, otherwise a window handle.
 *
 * @param[in] g			The GDisplay to display this window on
 * @param[in] gb		The GButtonObject structure to initialise. If this is NULL the structure is dynamically allocated.
 * @param[in] pInit		The initialisation parameters
 *
 * @note				The drawing color and the background color get set to the current defaults. If you haven't called
 * 						@p gwinSetDefaultColor() or @p gwinSetDefaultBgColor() then these are GFX_WHITE and GFX_BLACK respectively.
 * @note				The font gets set to the current default font. If you haven't called @p gwinSetDefaultFont() then there
 * 						is no default font and text drawing operations will no nothing.
 * @note				A button remembers its normal drawing state. If there is a window manager then it is automatically
 * 						redrawn if the window is moved or its visibility state is changed.
 * @note				A button supports mouse and a toggle input.
 * @note				When assigning a toggle, only one toggle is supported. If you try to assign more than one toggle it will
 * 						forget the previous toggle. When assigning a toggle the role parameter must be 0.
 *
 * @api
 */	
GHandle gwinGImageWCreate(GDisplay *g, GImageWObject *gb, const GWidgetInit *pInit);
#define gwinImageWCreate(gb, pInit)			gwinGImageWCreate(GDISP, gb, pInit)


#if GDISP_NEED_IMAGE || defined(__DOXYGEN__)
	/**
	 * @brief				Renders a button using individual images for each button state.
	 *
	 * @param[in] gw		The widget object (must be a button object)
	 * @param[in] param		A parameter passed in from the user. Must be an image handle. See note below.
	 *
	 * @note				The image must be already opened before calling  @p gwinSetCustomDraw(). The image should be 3
	 * 						times the height of the button. The button image is repeated 3 times vertically, the first (top) for
	 * 						the "up" image, the 2nd for the "down" image, and the third (bottom) image for the disabled state. If
	 * 						the disabled state is never going to be used then the image can be just 2 times the button height.
	 * 						No checking is done to compare the size of the button to the size of the image.
	 * 						Note text is drawn on top of the image.
	 *
	 * @pre					GDISP_NEED_IMAGE must be set to GFXON
	 *
	 * @api
	 */
	void gwinImageWDraw(GWidgetObject *gw, void *param);
	void gwinImageWDrawCenter(GWidgetObject *gw, void *param);
#endif
/** @} */

#endif /* _GWIN_IMG_W_H_ */
/** @} */
