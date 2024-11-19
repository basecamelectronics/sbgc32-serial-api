/** ____________________________________________________________________
 *
 *	@file		ugfxHelper.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_UGFX_HELPER_H_
#define		_UGFX_HELPER_H_

#ifdef		__cplusplus
extern		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	<stdlib.h>
#include	<string.h>

#include	"stdint.h"
#include	"gfx.h"

#include	"projectConfig.h"


typedef struct GColorSet GColorSet;
typedef struct GWidgetObject GWidgetObject;

typedef struct GWindowObject GWindowObject, *GHandle;

typedef struct sContainerDraw
{
	const char*	textTop;
	const char*	textBottom;

}	sContainerDraw;


typedef struct GDisplay		GDisplay;


/* Own drawing function's */
void gwinLabelDrawJustifiedCustom (GWidgetObject *gw, void *param);
void gwinProgressbarDrawCustom (GWidgetObject *gw, void *param);
GDisplay *gdispPixmapCreateCustom(gCoord width, gCoord height);
void ContainerDrawMono(GWidgetObject* gw, void* param);
void gwinProgressbarDrawCustom_Mono(GWidgetObject *gw, void *param);
void gwinLabelDrawJustifiedCustomMono(GWidgetObject *gw, void *param);
void gwinImageWDrawCustom_Mono(GWidgetObject *gw, void *param);
void gwinImageWOpenAndDrawCustom_Mono(GWidgetObject *gw, void *param);
void gwinProgressbarDrawJoystickVisualMono(GWidgetObject *gw, void *param);
void gwinProgressbarDrawPotentiometerVisualMono (GWidgetObject *gw, void *param);
void gwinArrow_Mono (GWidgetObject *gw, void *param);
void showLogo (void);
void gdispGDrawLineWu (GDisplay *g, gCoord x0, gCoord y0, gCoord x1, gCoord y1, gColor color, gColor background);


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef 		__cplusplus
			}
#endif

#endif		/* _UGFX_HELPER_H_ */
