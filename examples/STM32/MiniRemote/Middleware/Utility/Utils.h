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


static inline i32 CalculateSignedCeil (float value)
{
	return (value > 0.) ? (ceil(value)) : -(ceil(abs(value)));
}


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


class Expo
{
	private:

		float maxVal;
		float k1;
		float k3;


	public:

		inline Expo (void) { ; }

		// Parameters:
		// max - estimated range of input parameter. Outside this range, output becomes linear
		inline Expo (float _max) : maxVal(_max) { ; }

		void SetRate (ui8 rate);
		float Calculate (float x);
		inline void Configure (ui8 rate, float _max)
		{
			maxVal = _max;
			SetRate(rate);
		}

		inline float GetMax (void) { return maxVal; }

};

extern Expo ControlFilterExpo [3];


#endif //__cplusplus

#endif
