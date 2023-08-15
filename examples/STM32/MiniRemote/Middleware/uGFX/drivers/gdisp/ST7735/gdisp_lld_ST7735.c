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

#include "board_ST7735.h"
#include <string.h>   // for memset

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#ifndef GDISP_SCREEN_HEIGHT
	#define GDISP_SCREEN_HEIGHT		ST7735_HEIGHT
#endif
#ifndef GDISP_SCREEN_WIDTH
	#define GDISP_SCREEN_WIDTH		ST7735_WIDTH
#endif
#ifndef GDISP_INITIAL_CONTRAST
	#define GDISP_INITIAL_CONTRAST	100
#endif
#ifndef GDISP_INITIAL_BACKLIGHT
	#define GDISP_INITIAL_BACKLIGHT	100
#endif

#define ST7735_PAGE_WIDTH		GDISP_SCREEN_WIDTH
#define ST7735_PAGE_OFFSET		0


#define GDISP_FLG_NEEDFLUSH			(GDISP_FLG_DRIVER<<0)

#include "ST7735.h"

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

	// Initialise the board interface
	init_board(g);

	// Hardware reset
	setpin_reset(g, gTrue);
	gfxSleepMilliseconds(20);
	setpin_reset(g, gFalse);
	gfxSleepMilliseconds(20);

	acquire_bus(g);


    // Finish Init
    post_init_board(g);

 	// Release the bus
	release_bus(g);

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
		gCoord		sy, ey;
		gCoord		sx, ex;
		gCoord		col;
		unsigned	spage, zpages;
		gU8 *	base;
		gU8		mask;

		switch(g->g.Orientation) {
		default:
		case gOrientation0:
			sx = g->p.x;
			ex = g->p.x + g->p.cx - 1;
			sy = g->p.y;
			ey = sy + g->p.cy - 1;
			break;
		case gOrientation90:
			sx = g->p.y;
			ex = g->p.y + g->p.cy - 1;
			sy = GDISP_SCREEN_HEIGHT - g->p.x - g->p.cx;
			ey = GDISP_SCREEN_HEIGHT-1 - g->p.x;
			break;
		case gOrientation180:
			sx = GDISP_SCREEN_WIDTH - g->p.x - g->p.cx;
			ex = GDISP_SCREEN_WIDTH-1 - g->p.x;
			sy = GDISP_SCREEN_HEIGHT - g->p.y - g->p.cy;
			ey = GDISP_SCREEN_HEIGHT-1 - g->p.y;
			break;
		case gOrientation270:
			sx = GDISP_SCREEN_WIDTH - g->p.y - g->p.cy;
			ex = GDISP_SCREEN_WIDTH-1 - g->p.y;
			sy = g->p.x;
			ey = g->p.x + g->p.cx - 1;
			break;
		}

		ST7735_FillRectangle(g->p.x, g->p.y, g->p.cx, g->p.cy, gdispColor2Native(g->p.color));

		return;

		spage = sy / 8;
		base = RAM(g) + ST7735_PAGE_OFFSET + ST7735_PAGE_WIDTH * spage;
		mask = 0xff << (sy&7);
		zpages = (ey / 8) - spage;

		if (gdispColor2Native(g->p.color) == gdispColor2Native(GFX_BLACK)) {
			while (zpages--) {
				for (col = sx; col <= ex; col++)
					base[col] &= ~mask;
				mask = 0xff;
				base += ST7735_PAGE_WIDTH;
			}
			mask &= (0xff >> (7 - (ey&7)));
			for (col = sx; col <= ex; col++)
				base[col] &= ~mask;
		} else {
			while (zpages--) {
				for (col = sx; col <= ex; col++)
					base[col] |= mask;
				mask = 0xff;
				base += ST7735_PAGE_WIDTH;
			}
			mask &= (0xff >> (7 - (ey&7)));
			for (col = sx; col <= ex; col++)
				base[col] |= mask;
		}
		g->flags |= GDISP_FLG_NEEDFLUSH;
	}
#endif

#if GDISP_HARDWARE_DRAWPIXEL
	LLDSPEC void gdisp_lld_draw_pixel(GDisplay *g) {
		gCoord		x, y;

		switch(g->g.Orientation) {
		default:
		case gOrientation0:
			x = g->p.x;
			y = g->p.y;
			break;
		case gOrientation90:
			x = g->p.y;
			y = GDISP_SCREEN_HEIGHT-1 - g->p.x;
			break;
		case gOrientation180:
			x = GDISP_SCREEN_WIDTH-1 - g->p.x;
			y = GDISP_SCREEN_HEIGHT-1 - g->p.y;
			break;
		case gOrientation270:
			x = GDISP_SCREEN_WIDTH-1 - g->p.y;
			y = g->p.x;
			break;
		}

//		if (gdispColor2Native(g->p.color) != gdispColor2Native(GFX_BLACK))
//			RAM(g)[xyaddr(x, y)] |= xybit(y);
//		else
//			RAM(g)[xyaddr(x, y)] &= ~xybit(y);

		ST7735_DrawPixel(x, y, gdispColor2Native(g->p.color));

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
				acquire_bus(g);
				write_cmd(g, ST7735_DISPOFF);
				release_bus(g);
				break;
			case gPowerOn:
				acquire_bus(g);
				write_cmd(g, ST7735_DISPON);
				release_bus(g);
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

			ST7735_SetBacklight(*blTemp);
			g->g.Backlight = (unsigned)g->p.ptr;
			return;

//		case GDISP_CONTROL_ORIENTATION:
//			if (g->g.Orientation == (gOrientation)g->p.ptr)
//				return;
//			switch((gOrientation)g->p.ptr) {
//			/* Rotation is handled by the drawing routines */
//			case gOrientation0:
//			case gOrientation180:
//				g->g.Height = GDISP_SCREEN_HEIGHT;
//				g->g.Width = GDISP_SCREEN_WIDTH;
//				break;
//			case gOrientation90:
//			case gOrientation270:
//				g->g.Height = GDISP_SCREEN_WIDTH;
//				g->g.Width = GDISP_SCREEN_HEIGHT;
//				break;
//			default:
//				return;
//			}
//			g->g.Orientation = (gOrientation)g->p.ptr;
//			return;
//
//		case GDISP_CONTROL_CONTRAST:
//            if ((unsigned)g->p.ptr > 100)
//            	g->p.ptr = (void *)100;
//			acquire_bus(g);
//			write_cmd2(g, SSD1306_SETCONTRAST, (((unsigned)g->p.ptr)<<8)/101);
//			release_bus(g);
//            g->g.Contrast = (unsigned)g->p.ptr;
//			return;
//
//		// Our own special controller code to inverse the display
//		// 0 = normal, 1 = inverse
//		case GDISP_CONTROL_INVERSE:
//			acquire_bus(g);
//			write_cmd(g, g->p.ptr ? SSD1306_INVERTDISPLAY : SSD1306_NORMALDISPLAY);
//			release_bus(g);
//			return;
		}
	}
#endif // GDISP_NEED_CONTROL

#if GDISP_HARDWARE_BITFILLS
	// Uses p.x,p.y  p.cx,p.cy  p.x1,p.y1 (=srcx,srcy)  p.x2 (=srccx), p.ptr (=buffer)
	LLDSPEC void gdisp_lld_blit_area(GDisplay* g) {
		ST7735_BlitRectangle(g->p.x, g->p.y, g->p.cx, g->p.cy, g->p.ptr);
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
