/*
 * LiquidCrystal.h - LiquidCrystal Library for STM32 ARM microcontrollers
 *
 *  Created on: April 12, 2018
 *      Author: S. Saeed Hosseini (sayidhosseini@hotmail.com)
 *      Ported from: Arduino, Adafruit (https://github.com/arduino-libraries/LiquidCrystal)
 *      Published to: Github (https://github.com/SayidHosseini/STM32LiquidCrystal)
 */

#ifndef LiquidCrystal_h
#define LiquidCrystal_h

#include <inttypes.h>
#include "gpio.h"

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 * 									   Modified Part
 */
#ifdef 		HAL_GPIO_MODULE_ENABLED
	#define	WRITE_PIN(PORT, PIN, S)	HAL_GPIO_WritePin(PORT, PIN, S)

	#define		DELAY_MS(ms)			HAL_Delay(ms)
#else		/* LL_GPIO */
	#define	WRITE_PIN(PORT, PIN, S)	((S) ? LL_GPIO_SetOutputPin(PORT, PIN) : LL_GPIO_ResetOutputPin(PORT, PIN))

	#define		DELAY_MS(ms)			LL_mDelay(ms)
#endif

/*  - - - - - User Defined Parameters - - - - - - */

#define		LCD_SET_RS(S)			WRITE_PIN(LCD_RS_GPIO_Port, LCD_RS_Pin, S)
#define		LCD_SET_EN(S)			WRITE_PIN(LCD_EN_GPIO_Port, LCD_EN_Pin, S)

#define		LCD_SET_D4(S)			WRITE_PIN(LCD_D4_GPIO_Port, LCD_D4_Pin, S)
#define		LCD_SET_D5(S)			WRITE_PIN(LCD_D5_GPIO_Port, LCD_D5_Pin, S)
#define		LCD_SET_D6(S)			WRITE_PIN(LCD_D6_GPIO_Port, LCD_D6_Pin, S)
#define		LCD_SET_D7(S)			WRITE_PIN(LCD_D7_GPIO_Port, LCD_D7_Pin, S)
/*  - - - - - - - - - - - - - - - - - - - - - - - */


// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00


// low-level functions
void send(uint8_t, uint8_t);
void write4bits(uint8_t);
void write8bits(uint8_t);
void pulseEnable(void);

// initializers
void LiquidCrystal(uint16_t rs, uint16_t rw, uint16_t enable,
  uint16_t d0, uint16_t d1, uint16_t d2, uint16_t d3);

void init(uint8_t fourbitmode, uint16_t rs, uint16_t rw, uint16_t enable,
    uint16_t d0, uint16_t d1, uint16_t d2, uint16_t d3,
    uint16_t d4, uint16_t d5, uint16_t d6, uint16_t d7);

void begin(uint8_t cols, uint8_t rows);
//void enableClock(void);

// high-level functions
void clear(void);
void home(void);

void noDisplay(void);
void display(void);
void noBlink(void);
void blink(void);
void noCursor(void);
void cursor(void);
void scrollDisplayLeft(void);
void scrollDisplayRight(void);
void leftToRight(void);
void rightToLeft(void);
void autoscroll(void);
void noAutoscroll(void);
uint32_t print_str(const char str[]);
uint32_t print_char(const char simb);

void setRowOffsets(int row1, int row2, int row3, int row4);
void createChar(uint8_t, uint8_t[]);
void setCursor(uint8_t, uint8_t);
uint32_t write(uint8_t);
void command(uint8_t);

#endif
