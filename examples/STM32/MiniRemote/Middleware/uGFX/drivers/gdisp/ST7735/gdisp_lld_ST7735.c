/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "gfx.h"

#if GFX_USE_GDISP

#define GDISP_DRIVER_VMT			GDISPVMT_SSD1306
#include "gdisp_lld_config.h"
#include "../../../src/gdisp/gdisp_driver.h"

#include "st7789.h"
#include "stdbool.h"
#include <string.h>   // for memset

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#ifndef GDISP_SCREEN_HEIGHT
	#define GDISP_SCREEN_HEIGHT		135
#endif
#ifndef GDISP_SCREEN_WIDTH
	#define GDISP_SCREEN_WIDTH		240
#endif
#ifndef GDISP_INITIAL_CONTRAST
	#define GDISP_INITIAL_CONTRAST	100
#endif
#ifndef GDISP_INITIAL_BACKLIGHT
	#define GDISP_INITIAL_BACKLIGHT	100
#endif

#define ST7789_PAGE_WIDTH		GDISP_SCREEN_WIDTH
#define ST7789_PAGE_OFFSET		0


#define GDISP_FLG_NEEDFLUSH			(GDISP_FLG_DRIVER<<0)

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

// Some common routines and macros
#define RAM(g)							((gU8 *)g->priv)
#define write_cmd2(g, cmd1, cmd2)		{ write_cmd(g, cmd1); write_cmd(g, cmd2); }
#define write_cmd3(g, cmd1, cmd2, cmd3)	{ write_cmd(g, cmd1); write_cmd(g, cmd2); write_cmd(g, cmd3); }

// Some common routines and macros
#define delay(us)			gfxSleepMicroseconds(us)
#define delayms(ms)			gfxSleepMilliseconds(ms)

#define xyaddr(x, y)		(ST7735_PAGE_OFFSET + (x) + ((y)>>3)*ST7735_PAGE_WIDTH)
#define xybit(y)			(1<<((y)&7))

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * As this controller can't update on a pixel boundary we need to maintain the
 * the entire display surface in memory so that we can do the necessary bit
 * operations. Fortunately it is a small display in monochrome.
 * 64 * 128 / 8 = 1024 bytes.
 */

LLDSPEC gBool gdisp_lld_init(GDisplay *g) {

	// The private area is the display surface.
	g->priv = 0;

	gfxSleepMilliseconds(10);

	// Initialise the board interface
	init_board();

	/* Initialise the GDISP structure */
	g->g.Width = GDISP_SCREEN_WIDTH;
	g->g.Height = GDISP_SCREEN_HEIGHT;
	g->g.Orientation = gOrientation0;
	g->g.Powermode = gPowerOn;
	g->g.Backlight = GDISP_INITIAL_BACKLIGHT;
	g->g.Contrast = GDISP_INITIAL_CONTRAST;
	return gTrue;
}

#if GDISP_HARDWARE_FLUSH
	LLDSPEC void gdisp_lld_flush(GDisplay *g) {
		gU8 * ram;
		unsigned pages;

		// Don't flush if we don't need it.
		if (!(g->flags & GDISP_FLG_NEEDFLUSH))
			return;
		ram = RAM(g);
		pages = GDISP_SCREEN_HEIGHT/8;

		acquire_bus(g);
		write_cmd(g, SSD1306_SETSTARTLINE | 0);

		while (pages--) {
			#if SSD1306_SH1106
				write_cmd(g, SSD1306_PAM_PAGE_START + (7 - pages));
				write_cmd(g, SSD1306_SETLOWCOLUMN + 2);
				write_cmd(g, SSD1306_SETHIGHCOLUMN);
			#endif

			write_data(g, ram, SSD1306_PAGE_WIDTH);
			ram += SSD1306_PAGE_WIDTH;
		}
		release_bus(g);

		g->flags &= ~GDISP_FLG_NEEDFLUSH;
	}
#endif

#if GDISP_HARDWARE_PIXELREAD
	LLDSPEC gColor gdisp_lld_get_pixel_color(GDisplay *g) {
		unused_(g);
		/* We can't read from the display! */
		HardwareErrorHandler();
		return 0;
	}
#endif

#if GDISP_HARDWARE_FILLS
	LLDSPEC void gdisp_lld_fill_area(GDisplay *g) {
		ST7789_FillRect(g->p.x, g->p.y, g->p.cx, g->p.cy, gdispColor2Native(g->p.color));
	}
#endif

#if GDISP_HARDWARE_DRAWPIXEL
	LLDSPEC void gdisp_lld_draw_pixel(GDisplay *g) {
		ST7789_DrawPixel(g->p.x, g->p.y, gdispColor2Native(g->p.color));
		g->flags |= GDISP_FLG_NEEDFLUSH;
	}
#endif

#if GDISP_NEED_CONTROL && GDISP_HARDWARE_CONTROL
	LLDSPEC void gdisp_lld_control(GDisplay *g) {
		ui16 *blTemp;

		switch(g->p.x) {
		case GDISP_CONTROL_POWER:
//			if (g->g.Powermode == (gPowermode)g->p.ptr)
//				return;
			switch((gPowermode)g->p.ptr) {
			case gPowerOff:
			case gPowerSleep:
			case gPowerDeepSleep:
				break;
			case gPowerOn:
				break;
			default:
				return;
			}
			g->g.Powermode = (gPowermode)g->p.ptr;
			return;

		case GDISP_CONTROL_BACKLIGHT:
			blTemp = (ui16*)&(g->p.ptr);

		    if (*blTemp > 100)
		    	g->p.ptr = (void*)100;

		    ST7789_SetBacklight(*blTemp);
			g->g.Backlight = (unsigned)g->p.ptr;
			return;
		}
	}
#endif // GDISP_NEED_CONTROL

#if GDISP_HARDWARE_BITFILLS
	// Uses p.x,p.y  p.cx,p.cy  p.x1,p.y1 (=srcx,srcy)  p.x2 (=srccx), p.ptr (=buffer)
	LLDSPEC void gdisp_lld_blit_area(GDisplay* g) {
		ST7789_Blit(g->p.x, g->p.y, g->p.cx, g->p.cy, g->p.ptr);
	}
#endif


volatile bool display_busy_flag = 0;


void HoldDisplayBuf (void)
{
	while (display_busy_flag)
		vTaskDelay(1);

	display_busy_flag = 1;
}


void ExeDisplayBuf (void)
{
	display_busy_flag = 0;
}


void GiveDisplayBuf (void)
{
	display_busy_flag = 0;
}


#endif // GFX_USE_GDISP
