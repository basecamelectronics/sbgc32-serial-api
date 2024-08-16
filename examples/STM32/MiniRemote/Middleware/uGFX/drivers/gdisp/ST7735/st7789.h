#ifndef		_ST7789_H_
#define		_ST7789_H_

#include	"hardware.h"

#include	"stdlib.h"
#include	"string.h"

#define 	ST7789_SPI_HAL 			hspi1
		
#define		ST7789_IS_135X240						// 1.14" 135 x 240 ST7789


extern SPI_HandleTypeDef ST7789_SPI_HAL;

extern uint16_t ST7789_Width, ST7789_Height;

extern uint16_t ST7789_X_Start;
extern uint16_t ST7789_Y_Start;

#define		RGB565(r, g, b)			(((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

#define   	ST7789_BLACK   			0x0000
#define   	ST7789_BLUE    			0x001F
#define   	ST7789_RED     			0xF800
#define   	ST7789_GREEN   			0x07E0
#define 	ST7789_CYAN    			0x07FF
#define 	ST7789_MAGENTA 			0xF81F
#define		ST7789_YELLOW  			0xFFE0
#define		ST7789_WHITE   			0xFFFF

#define		ST7789_ColorMode_65K    0x50
#define		ST7789_ColorMode_262K  	0x60
#define		ST7789_ColorMode_12bit 	0x03
#define		ST7789_ColorMode_16bit 	0x05
#define		ST7789_ColorMode_18bit 	0x06
#define		ST7789_ColorMode_16M   	0x07

#define		ST7789_MADCTL_MY  		0x80
#define		ST7789_MADCTL_MX  		0x40
#define		ST7789_MADCTL_MV  		0x20
#define		ST7789_MADCTL_ML  		0x10
#define		ST7789_MADCTL_RGB 		0x00
#define		ST7789_MADCTL_BGR 		0x08
#define		ST7789_MADCTL_MH  		0x04

#define		ST7789_SWRESET 			0x01
#define		ST7789_SLPIN   			0x10
#define		ST7789_SLPOUT  			0x11
#define		ST7789_NORON   			0x13
#define		ST7789_INVOFF  			0x20
#define		ST7789_INVON   			0x21
#define		ST7789_DISPOFF 			0x28
#define		ST7789_DISPON  			0x29
#define		ST7789_CASET   			0x2A
#define		ST7789_RASET   			0x2B
#define		ST7789_RAMWR   			0x2C
#define		ST7789_COLMOD  			0x3A
#define 	ST7789_MADCTL  			0x36

#define		DELAY 					0x80

#define		ST7789_WIDTH  			240
#define		ST7789_HEIGHT 			135
#define		ST7789_XSTART 			40
#define		ST7789_YSTART 			52
#define		ST7789_ROTATION 		(ST7789_MADCTL_RGB | ST7789_MADCTL_MY | ST7789_MADCTL_MV)
	

void ST7789_Init (void);
void ST7789_Blit (ui16 x, ui16 y, ui16 w, ui16 h, ui8* data);
void ST7789_HardReset (void);
void ST7789_FillRect (i16 x, i16 y, i16 w, i16 h, ui16 color);
void ST7789_DrawPixel (i16 x, i16 y, ui16 color);
void ST7789_SetBacklight (ui16 val);
void init_board (void);

#endif		/* _ST7789_H_ */
