/*
 This is a part of SimpleBGC project source code
 Copyright (c) 2014 Aleksei Moskalenko
*/
#include <createWidget.h>
#include "Utils.h"
#include "string.h"
#include "ctype.h"


Expo ControlFilterExpo [SBGC_CONTROL_HANDLERS_NUM] =
{
	Expo(IN_MIDDLE_VALUE),
	Expo(IN_MIDDLE_VALUE),
	Expo(IN_MIDDLE_VALUE)

};


void* operator new(size_t numBytes) throw(){

	//C++ stardard 5.3.4.8 requires that a valid pointer be returned for
	//a call to new(0). Thus:
	if(numBytes == 0){
		numBytes = 1;
	}
	void * p = osMalloc(numBytes); /* Freertos heap is used */
	if(p == 0){
		NVIC_SystemReset();
	}
	return p;
}


void operator delete(void* ptr) throw() {
	osFree(ptr);
}


void Utils::imageCloseFile (gdispImage*& img)
{
	gdispImageClose(img);

	if(img)
		osFree(img);
}


void Utils::imageOpenFile (gdispImage*& img, const char *filename)
{
	gdispImageError res = GDISP_IMAGE_ERR_NOSUCHFILE;
	img = (gdispImage*) osMalloc(sizeof(gdispImage));

	if ((res = gdispImageOpenFile(img, filename)) == GDISP_IMAGE_ERR_OK)
		return;

	if (res != GDISP_IMAGE_ERR_OK)
		while (1);
}


void Utils::DrawImageAlligned(GWidgetObject* gw, gdispImage * pImg, coord_t x, coord_t y,
		coord_t iwidth, coord_t iheight, justify_t justify, bool doFill, color_t color) {
	if (pImg == 0)
		return;

	coord_t PixmapWidth = pImg->width;
	coord_t PixmapHeight = pImg->height;
	coord_t PixmapOffset = (iheight - PixmapHeight) / 2;

	coord_t _y = gw->g.y + y + PixmapOffset;  // The start position
	coord_t _cy = PixmapHeight;  // The size of the filled area
	coord_t _srcy = 0;

	if (_y <= gw->g.y) {
		_cy = PixmapHeight - (gw->g.y - _y); // The size of the filled area
		_y = gw->g.y; // The start position
		_srcy = PixmapHeight - _cy;
	}

	if(doFill){
		coord_t fill_y = (gw->g.y) + y;
		coord_t fill_cy = iheight;
		if(fill_y <= gw->g.y){
			fill_cy = iheight - (gw->g.y - fill_y);
			fill_y = gw->g.y;
		}

		gdispSetDisplay(gdispGetDisplay(0));
		gdispFillArea(x, fill_y, iwidth, fill_cy, color);
	}

	if (justify == justifyRight) {
		x += iwidth - PixmapWidth;
	} else if (justify == justifyCenter) {
		x += (iwidth - PixmapWidth) / 2;
	}

	gdispGImageDraw(gdispGetDisplay(1), pImg, x, _y, PixmapWidth, _cy, 0, _srcy);
}

void Utils::showLogo (void)
{
	gdispImage* img = 0;
	Utils::imageOpenFile(img, "logo.bmp");
	HoldDisplayBuf();
	gdispClear(GFX_BLACK);
	ExeDisplayBuf();

	HoldDisplayBuf();
	gdispImageDraw(img, (gdispGetWidth() - img->width) / 2, (gdispGetHeight() - img->height) / 2, img->width, img->height, 0, 0);
	ExeDisplayBuf();
	Utils::imageCloseFile(img);
}

/* Set expo rate, 0..100 */
void Expo::SetRate (ui8 _rate)
{
    float rate = _rate;
    k3 = rate / (100.0F * (float)maxVal * (float)maxVal);
    k1 = (100.0F - rate) / 100.0F;
}

/* Calculate exponent value for given x */
float Expo::Calculate (float x)
{
    if (k3 == 0 || x == 0)
        return x;

    // Math: y = x*x*x  (rate / (100*max_val*max_val)) + x  ((100 - rate)/(100))
    return x * x * x * k3 + x * k1;
}
