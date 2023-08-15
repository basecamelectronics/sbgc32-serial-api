/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef		_GDISP_LLD_BOARD_H
#define		_GDISP_LLD_BOARD_H

#include	"ST7735.h"
#include	<stdbool.h>
#include	"hardware.h"

#define		DELAY					0x80

/* Processor delay for slowly ST7735 drivers */
#define		__CustomDelayDisplayTiming		/* __ProcessorDelay(5) */


#pragma		GCC diagnostic ignored "-Wmisleading-indentation"


volatile bool SPI_TxDMA_TC_Flag = true;

static SPI_HandleTypeDef qspi1;
static DMA_HandleTypeDef qdma2_tx_spi1;
TIM_HandleTypeDef qtim1;


void LCD_SPI_TX_DMA_IRQ_HANDLER (void)
{
	HAL_DMA_IRQHandler(&qdma2_tx_spi1);
}


void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	SPI_TxDMA_TC_Flag = 1;
}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
	HardwareErrorHandler();
}


// call before initializing any SPI devices
void ST7735_Unselect();
void ST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void ST7735_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void ST7735_FillScreen(uint16_t color);
void ST7735_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data);


static const uint8_t
  init_cmds1[] = {            // Init for 7735R, part 1 (red or green tab)
    15,                       // 15 commands in list:
    ST7735_SWRESET,   DELAY,  //  1: Software reset, 0 args, w/delay
      150,                    //     150 ms delay
    ST7735_SLPOUT ,   DELAY,  //  2: Out of sleep mode, 0 args, w/delay
      255,                    //     500 ms delay
    ST7735_FRMCTR1, 3      ,  //  3: Frame rate ctrl - normal mode, 3 args:
      0x01, 0x2C, 0x2D,       //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ST7735_FRMCTR2, 3      ,  //  4: Frame rate control - idle mode, 3 args:
      0x01, 0x2C, 0x2D,       //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ST7735_FRMCTR3, 6      ,  //  5: Frame rate ctrl - partial mode, 6 args:
      0x01, 0x2C, 0x2D,       //     Dot inversion mode
      0x01, 0x2C, 0x2D,       //     Line inversion mode
    ST7735_INVCTR , 1      ,  //  6: Display inversion ctrl, 1 arg, no delay:
      0x07,                   //     No inversion
    ST7735_PWCTR1 , 3      ,  //  7: Power control, 3 args, no delay:
      0xA2,
      0x02,                   //     -4.6V
      0x84,                   //     AUTO mode
    ST7735_PWCTR2 , 1      ,  //  8: Power control, 1 arg, no delay:
      0xC5,                   //     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
    ST7735_PWCTR3 , 2      ,  //  9: Power control, 2 args, no delay:
      0x0A,                   //     Opamp current small
      0x00,                   //     Boost frequency
    ST7735_PWCTR4 , 2      ,  // 10: Power control, 2 args, no delay:
      0x8A,                   //     BCLK/2, Opamp current small & Medium low
      0x2A,
    ST7735_PWCTR5 , 2      ,  // 11: Power control, 2 args, no delay:
      0x8A, 0xEE,
    ST7735_VMCTR1 , 1      ,  // 12: Power control, 1 arg, no delay:
      0x0E,
    ST7735_INVOFF , 0      ,  // 13: Don't invert display, no args, no delay
    ST7735_MADCTL , 1      ,  // 14: Memory access control (directions), 1 arg:
      ST7735_ROTATION,        //     row addr/col addr, bottom to top refresh
    ST7735_COLMOD , 1      ,  // 15: set color mode, 1 arg, no delay:
      0x05 },                 //     16-bit color

#if (defined(ST7735_IS_128X128) || defined(ST7735_IS_160X128))
  init_cmds2[] = {            // Init for 7735R, part 2 (1.44" display)
    2,                        //  2 commands in list:
    ST7735_CASET  , 4      ,  //  1: Column addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x7F,             //     XEND = 127
    ST7735_RASET  , 4      ,  //  2: Row addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x7F },           //     XEND = 127
#endif // ST7735_IS_128X128

#ifdef ST7735_IS_160X80
  init_cmds2[] = {            // Init for 7735S, part 2 (160x80 display)
    3,                        //  3 commands in list:
    ST7735_CASET  , 4      ,  //  1: Column addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x4F,             //     XEND = 79
    ST7735_RASET  , 4      ,  //  2: Row addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x9F ,            //     XEND = 159
    ST7735_INVON, 0 },        //  3: Invert colors
#endif

  init_cmds3[] = {            // Init for 7735R, part 3 (red or green tab)
    4,                        //  4 commands in list:
    ST7735_GMCTRP1, 16      , //  1: Gamma Adjustments (pos. polarity), 16 args, no delay:
      0x02, 0x1c, 0x07, 0x12,
      0x37, 0x32, 0x29, 0x2d,
      0x29, 0x25, 0x2B, 0x39,
      0x00, 0x01, 0x03, 0x10,
    ST7735_GMCTRN1, 16      , //  2: Gamma Adjustments (neg. polarity), 16 args, no delay:
      0x03, 0x1d, 0x07, 0x06,
      0x2E, 0x2C, 0x29, 0x2D,
      0x2E, 0x2E, 0x37, 0x3F,
      0x00, 0x00, 0x02, 0x10,
    ST7735_NORON  ,    DELAY, //  3: Normal display on, no args, w/delay
      10,                     //     10 ms delay
    ST7735_DISPON ,    DELAY, //  4: Main screen turn on, no args w/delay
      100 };                  //     100 ms delay



static void __SPI_Transmit (SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
	HAL_SPI_Transmit(hspi, pData, Size, 100);
}


static void __SPI_Transmit_DMA (SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
	/* Required condition for some controllers */
	ATOMIC_SET_BIT(hspi->Instance->CR1, SPI_CR1_DFF);

	SPI_TxDMA_TC_Flag = false;
	HAL_SPI_Transmit_DMA(hspi, pData, Size);

	while (!SPI_TxDMA_TC_Flag);

	/* Return to 8-bit */
	ATOMIC_CLEAR_BIT(hspi->Instance->CR1, SPI_CR1_DFF);
}


static void ST7735_Select() {
    HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET);

    __CustomDelayDisplayTiming;
}

void ST7735_Unselect() {
    HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_SET);

    __CustomDelayDisplayTiming;
}


static void ST7735_Reset() {
    HAL_GPIO_WritePin(ST7735_RES_GPIO_Port, ST7735_RES_Pin, GPIO_PIN_RESET);
    __DelayMs(5);
    HAL_GPIO_WritePin(ST7735_RES_GPIO_Port, ST7735_RES_Pin, GPIO_PIN_SET);
    __DelayMs(5);
}

static void ST7735_WriteCommand(uint8_t cmd) {
    HAL_GPIO_WritePin(ST7735_DC_GPIO_Port, ST7735_DC_Pin, GPIO_PIN_RESET);
    __CustomDelayDisplayTiming;

    __SPI_Transmit(&qspi1, &cmd, 1);
    __CustomDelayDisplayTiming;
}

static void ST7735_WriteData(uint8_t* buff, size_t buff_size) {
    HAL_GPIO_WritePin(ST7735_DC_GPIO_Port, ST7735_DC_Pin, GPIO_PIN_SET);
    __CustomDelayDisplayTiming;

    __SPI_Transmit(&qspi1, buff, buff_size);
    __CustomDelayDisplayTiming;
}

static void ST7735_ExecuteCommandList(const uint8_t *addr) {
    uint8_t numCommands, numArgs;
    uint16_t ms;

    numCommands = *addr++;
    while(numCommands--) {
        uint8_t cmd = *addr++;
        ST7735_WriteCommand(cmd);

        numArgs = *addr++;
        // If high bit set, delay follows args
        ms = numArgs & DELAY;
        numArgs &= ~DELAY;
        if(numArgs) {
            ST7735_WriteData((uint8_t*)addr, numArgs);
            addr += numArgs;
        }

        if(ms) {
            ms = *addr++;
            if(ms == 255) ms = 500;
            __DelayMs(ms);
        }
    }
}

static void ST7735_SetAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
    // column address set
    ST7735_WriteCommand(ST7735_CASET);
    uint8_t data[] = { 0x00, x0 + ST7735_XSTART, 0x00, x1 + ST7735_XSTART };
    ST7735_WriteData(data, sizeof(data));

    // row address set
    ST7735_WriteCommand(ST7735_RASET);
    data[1] = y0 + ST7735_YSTART;
    data[3] = y1 + ST7735_YSTART;
    ST7735_WriteData(data, sizeof(data));

    // write to RAM
    ST7735_WriteCommand(ST7735_RAMWR);
}

void ST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT))
        return;

    ST7735_Select();

    ST7735_SetAddressWindow(x, y, x+1, y+1);
    uint8_t data[] = { color >> 8, color & 0xFF };
    ST7735_WriteData(data, sizeof(data));

    ST7735_Unselect();
}


void ST7735_FillRectangle (uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
	ST7735_Select();
	ST7735_SetAddressWindow(x, y, x + w-1, y + h - 1);

	uint8_t data [] = { color & 0xFF, color >> 8 };

	HAL_GPIO_WritePin(LCD_SPI_DC_GPIO_PORT, LCD_SPI_DC_PIN, GPIO_PIN_SET);
	__CustomDelayDisplayTiming;

	__SPI_Transmit_DMA(&qspi1, data, w * h * 2);

	ST7735_Unselect();
}


void ST7735_BlitRectangle (uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t* data)
{
    ST7735_Select();
    ST7735_SetAddressWindow(x, y, x + w - 1, y + h - 1);

    HAL_GPIO_WritePin(LCD_SPI_DC_GPIO_PORT, LCD_SPI_DC_PIN, GPIO_PIN_SET);
    __CustomDelayDisplayTiming;

    uint16_t* data16 = (uint16_t*)data;

    for (uint16_t i = 0; i < h * w; ++i)
    	data16[i] = __REV16(data16[i]);


//    ui16 r, g, b, avg;
//
//    for (ui16 i = 0; i < h * w; ++i)
//    {
//    	b = data16[i] & ST7735_BLUE;
//    	g = (data16[i] & ST7735_GREEN) >> 6;  // + 1
//    	r = (data16[i] & ST7735_RED) >> 11;
//
//    	avg = (r + g + b) / 3;
//
//    	b = avg;
//    	g = avg << 6;
//    	r = avg << 11;
//
//    	data16[i] = r + g + b;
//
//    	if (avg)
//    		__NOP();
//    }



	/* DMA memory incremental set */
//	qdma2_tx_spi1.Init.MemInc = DMA_MINC_ENABLE;
//	if (HAL_DMA_Init(&qdma2_tx_spi1) != HAL_OK)
//		HardwareErrorHandler();

	__SPI_Transmit(&qspi1, (ui8*)data16, w * h * 2);

	/* DMA memory incremental disable */
//	qdma2_tx_spi1.Init.MemInc = DMA_MINC_DISABLE;
//	if (HAL_DMA_Init(&qdma2_tx_spi1) != HAL_OK)
//		HardwareErrorHandler();

    ST7735_Unselect();
}

void ST7735_SetBacklight (uint16_t val)
{
	LCD_TIM_INSTANCE->CCR1 = 1000 - (pow(val, 3) / 1000);
}

void ST7735_FillScreen(uint16_t color) {
    ST7735_FillRectangle(0, 0, ST7735_WIDTH, ST7735_HEIGHT, color);
}

void ST7735_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data) {
    if((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT)) return;
    if((x + w - 1) >= ST7735_WIDTH) return;
    if((y + h - 1) >= ST7735_HEIGHT) return;

    ST7735_Select();
    ST7735_SetAddressWindow(x, y, x+w-1, y+h-1);
    ST7735_WriteData((uint8_t*)data, sizeof(uint16_t)*w*h);
    ST7735_Unselect();
}


static GFXINLINE void init_board ()
{
	LCD_TIM_CLOCK_ENABLE();
	LCD_TIM_PWM_GPIO_CLOCK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct;

	/* Common configuration for all channels */
	GPIO_InitStruct.Mode		= GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull		= GPIO_PULLUP;
	GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate	= LCD_TIM_PWM_PIN_AF;
	GPIO_InitStruct.Pin			= LCD_TIM_PWM_PIN;
	HAL_GPIO_Init(LCD_TIM_PWM_GPIO_PORT, &GPIO_InitStruct);

	qtim1.Instance = LCD_TIM_INSTANCE;

	qtim1.Init.Prescaler         	= (LCD_TIM_BUS_FREQ / 1000000) - 1;
	qtim1.Init.Period            	= 1000;
	qtim1.Init.ClockDivision     	= 0;
	qtim1.Init.CounterMode       	= TIM_COUNTERMODE_UP;
	qtim1.Init.RepetitionCounter 	= 0;
	qtim1.Init.AutoReloadPreload 	= TIM_AUTORELOAD_PRELOAD_DISABLE;

	if (HAL_TIM_PWM_Init(&qtim1) != HAL_OK)
	{
		/* Initialization Error */
		HardwareErrorHandler();
	}

	TIM_OC_InitTypeDef sConfigOC;

	/* Common configuration for all channels */
	sConfigOC.OCMode       = TIM_OCMODE_PWM1;
	sConfigOC.OCPolarity   = TIM_OCPOLARITY_LOW;
	sConfigOC.OCFastMode   = TIM_OCFAST_DISABLE;
	sConfigOC.OCNPolarity  = TIM_OCNPOLARITY_LOW;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	sConfigOC.OCIdleState  = TIM_OCIDLESTATE_RESET;

	/* Set the pulse value for PWM channel */
	sConfigOC.Pulse = 0;

	if (HAL_TIM_PWM_ConfigChannel(&qtim1, &sConfigOC, LCD_TIM_PWM_CHANNEL) != HAL_OK)
	{
		/* Configuration Error */
		HardwareErrorHandler();
	}

	/* Start PWM channel */
	if (HAL_TIM_PWM_Start(&qtim1, LCD_TIM_PWM_CHANNEL) != HAL_OK)
	{
		/* PWM Generation Error */
		HardwareErrorHandler();
	}


	LCD_GPIO_CLOCK_ENABLE();

	/* SPI GPIO Initializing */
    GPIO_InitStruct.Pin			= LCD_SPI_MOSI_PIN;
    GPIO_InitStruct.Mode		= GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull		= GPIO_NOPULL;
    GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate	= LCD_SPI_MOSI_PIN_AF;
    HAL_GPIO_Init(LCD_SPI_MOSI_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin			= LCD_SPI_SCL_PIN;
    GPIO_InitStruct.Mode		= GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull		= GPIO_NOPULL;
    GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate	= LCD_SPI_SCL_PIN_AF;
    HAL_GPIO_Init(LCD_SPI_SCL_GPIO_PORT, &GPIO_InitStruct);


    LCD_SPI_GPIO_CLOCK_ENABLE();

    HAL_GPIO_WritePin(ST7735_RES_GPIO_Port, ST7735_RES_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ST7735_DC_GPIO_Port, ST7735_DC_Pin, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin			= ST7735_RES_Pin;
    GPIO_InitStruct.Mode		= GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull		= GPIO_NOPULL;
    GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ST7735_RES_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = ST7735_CS_Pin;
    HAL_GPIO_Init(ST7735_CS_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = ST7735_DC_Pin;
    HAL_GPIO_Init(ST7735_DC_GPIO_Port, &GPIO_InitStruct);


    LCD_SPI_CLOCK_ENABLE();

    /* SPI parameter configuration */
    qspi1.Instance = LCD_SPI_INSTANCE;

    qspi1.Init.Mode					= SPI_MODE_MASTER;
    qspi1.Init.Direction			= SPI_DIRECTION_1LINE;
    qspi1.Init.DataSize				= SPI_DATASIZE_8BIT;
    qspi1.Init.CLKPolarity			= SPI_POLARITY_LOW;
    qspi1.Init.CLKPhase				= SPI_PHASE_1EDGE;
    qspi1.Init.NSS					= SPI_NSS_SOFT;
    qspi1.Init.BaudRatePrescaler	= SPI_BAUDRATEPRESCALER_2;
    qspi1.Init.FirstBit				= SPI_FIRSTBIT_MSB;
    qspi1.Init.TIMode				= SPI_TIMODE_DISABLE;
    qspi1.Init.CRCCalculation		= SPI_CRCCALCULATION_DISABLE;

    if (HAL_SPI_Init(&qspi1) != HAL_OK)
    {
    	HardwareErrorHandler();
    }

    SPI_1LINE_TX(&qspi1);
    __HAL_SPI_ENABLE(&qspi1);

    /* Enable DMAx clock */
    LCD_SPI_DMA_CLOCK_ENABLE();

    qdma2_tx_spi1.Instance = LCD_SPI_TX_DMA_STREAM;

    qdma2_tx_spi1.Init.Channel				= LCD_SPI_TX_DMA_CHANNEL;
    qdma2_tx_spi1.Init.Direction				= DMA_MEMORY_TO_PERIPH;
    qdma2_tx_spi1.Init.PeriphInc				= DMA_PINC_DISABLE;
    qdma2_tx_spi1.Init.MemInc					= DMA_MINC_DISABLE;
    qdma2_tx_spi1.Init.PeriphDataAlignment	= DMA_PDATAALIGN_HALFWORD;
    qdma2_tx_spi1.Init.MemDataAlignment		= DMA_MDATAALIGN_HALFWORD;
    qdma2_tx_spi1.Init.Mode					= DMA_NORMAL;
    qdma2_tx_spi1.Init.Priority				= DMA_PRIORITY_HIGH;
    qdma2_tx_spi1.Init.FIFOMode				= DMA_FIFOMODE_DISABLE;

	if (HAL_DMA_Init(&qdma2_tx_spi1) != HAL_OK)
	{
		HardwareErrorHandler();
	}

	__HAL_LINKDMA(&qspi1, hdmatx, qdma2_tx_spi1);

    /* NVIC configuration for DMA transfer complete interrupt */
    HAL_NVIC_SetPriority(LCD_SPI_TX_DMA_CH_IRQN, 2, 0);
    HAL_NVIC_EnableIRQ(LCD_SPI_TX_DMA_CH_IRQN);

	ST7735_Select();
	ST7735_Reset();
	ST7735_ExecuteCommandList(init_cmds1);
	ST7735_ExecuteCommandList(init_cmds2);
	ST7735_ExecuteCommandList(init_cmds3);
	ST7735_Unselect();
}


static GFXINLINE void post_init_board(GDisplay *g) {
}

static GFXINLINE void setpin_reset(GDisplay *g, gBool state) {
	(void) g;
	(void) state;
}

static GFXINLINE void acquire_bus(GDisplay *g) {
	(void) g;
}

static GFXINLINE void release_bus(GDisplay *g) {
	(void) g;
}

static GFXINLINE void write_cmd(GDisplay *g, gU8 cmd) {
	(void) g;
    ST7735_Select();
    ST7735_WriteCommand(cmd);
    ST7735_Unselect();
}

static GFXINLINE void write_data(GDisplay *g, gU8* data, gU16 length) {
	(void) g;
	(void) data;
	(void) length;
}


#endif /* _GDISP_LLD_BOARD_H */
