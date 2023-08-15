/*
 This is a part of SimpleBGC project source code
 Copyright (c) 2014 Aleksei Moskalenko
*/

#ifndef _UTILS_H_
#define _UTILS_H_

#include "hardware.h"
#include "gfx.h"

#ifdef __cplusplus

// Delayed reset time
#define	RESET_DELAY_MS  1000

#ifndef __STD_NEW_OPERATOR
#define __STD_NEW_OPERATOR 1

#pragma GCC visibility push(default)

void* operator new(size_t numBytes) throw();
/* Placement operators */
//inline void* operator new(size_t, void* ptr) throw() {return ptr; }

void operator delete(void* ptr) throw();

#endif /* __STD_NEW_OPERATOR */


class Utils
{
public:

    inline static void  fill_arr_16(int16_t arr[], int16_t val, uint16_t size) {
        while(size-- > 0) arr[size] = val;
    }

    static void imageCloseFile(gdispImage*& img);
    static void imageOpenFile(gdispImage*& img, const char *filename);

    static void DrawImageAlligned(GWidgetObject* gw, gdispImage * pImg, coord_t x, coord_t y,
    		coord_t iwidth, coord_t iheight, justify_t justify, bool doFill, color_t color);

    static void showLogo (void);
};


#endif //__cplusplus

#endif
