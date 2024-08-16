#include "st7789.h"
#include <stdbool.h>

SPI_HandleTypeDef hspi1;
TIM_HandleTypeDef htim1;
static DMA_HandleTypeDef hdma2_tx_spi1;

ui16 ST7789_X_Start = ST7789_XSTART;
ui16 ST7789_Y_Start = ST7789_YSTART;

ui16 ST7789_Width = 0;
ui16 ST7789_Height = 0;

volatile bool LCD_SPI_TxDMA_TC_Flag = true;


static void ST7789_Unselect(void);
static void ST7789_Select(void);

void LCD_SPI_TX_DMA_IRQ_HANDLER (void)
{
	HAL_DMA_IRQHandler(&hdma2_tx_spi1);
}


void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	LCD_SPI_TxDMA_TC_Flag = 1;
}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
	HardwareErrorHandler();
}


static void LCD_SPI_Transmit_DMA (SPI_HandleTypeDef *hspi, ui8 *pData, ui16 Size)
{
	ST7789_Select();

	/* Required condition for some controllers */
	ATOMIC_SET_BIT(hspi->Instance->CR1, SPI_CR1_DFF);

	LCD_SPI_TxDMA_TC_Flag = false;
	HAL_SPI_Transmit_DMA(hspi, pData, Size);

	while (!LCD_SPI_TxDMA_TC_Flag);

	/* Return to 8-bit */
	ATOMIC_CLEAR_BIT(hspi->Instance->CR1, SPI_CR1_DFF);

	ST7789_Unselect();
}



static void ST7789_ExecuteCommandList (const ui8 *addr);
static void ST7789_SendCmd (ui8 Cmd);
static void ST7789_SendData (ui8 Data );
static void ST7789_SendDataMASS (ui8* buff, size_t buff_size);
static void ST7789_SetWindow (ui16 x0, ui16 y0, ui16 x1, ui16 y1);
static void ST7789_ColumnSet (ui16 ColumnStart, ui16 ColumnEnd);
static void ST7789_RowSet (ui16 RowStart, ui16 RowEnd);


static const ui8 init_cmds[] =
{
	9,                       			// 9 commands in list:
	ST7789_SWRESET,   DELAY,    		// 1: Software reset, no args, w/delay
	  150,                     			//    150 ms delay
	ST7789_SLPOUT ,  DELAY,    			// 2: Out of sleep mode, no args, w/delay
	  255,                            	//    255 = 500 ms delay
	ST7789_COLMOD , 1+DELAY,    		// 3: Set color mode, 1 arg + delay:
	  (ST7789_ColorMode_65K | ST7789_ColorMode_16bit),           //    16-bit color 0x55
	  10,                             	//    10 ms delay


	ST7789_MADCTL , 1,                 	// 4: Memory access ctrl (directions), 1 arg:
	  ST7789_ROTATION,                  //    Row addr/col addr, bottom to top refresh


	ST7789_CASET  , 4,                 	// 5: Column addr set, 4 args, no delay:
	  ST7789_XSTART>>8,ST7789_XSTART&0xff,  //    XSTART = 0>>8, 0&0xff,
	  (ST7789_WIDTH-1)>>8,(ST7789_WIDTH-1)&0xff,    //    XEND = (320-1)>>8,(320-1)&0xff,

	ST7789_RASET  , 4,                 	// 6: Row addr set, 4 args, no delay:
	  ST7789_YSTART>>8,ST7789_YSTART&0xff,  //    YSTART = 0>>8, 0&0xff,
	  (ST7789_HEIGHT-1)>>8,(ST7789_HEIGHT-1)&0xff,  //    YEND = (320-1)>>8,(320-1)&0xff,



	ST7789_INVON ,   DELAY,     		// 7: Inversion ON
	  10,
	ST7789_NORON  ,   DELAY,    		// 8: Normal display on, no args, w/delay
	  10,                              	// 10 ms delay
	ST7789_DISPON ,   DELAY,    		// 9: Main screen turn on, no args, w/delay
	  1
};


void ST7789_Init (void)
{
	ST7789_Width = ST7789_WIDTH;
	ST7789_Height = ST7789_HEIGHT;
	
	ST7789_Select();

	ST7789_HardReset();
	ST7789_ExecuteCommandList(init_cmds);
	
	ST7789_Unselect();
}


static void ST7789_Select (void)
{
	HAL_GPIO_WritePin(LCD_SPI_CS_GPIO_PORT, LCD_SPI_CS_PIN, GPIO_PIN_RESET);
}


static void ST7789_Unselect (void)
{
	HAL_GPIO_WritePin(LCD_SPI_CS_GPIO_PORT, LCD_SPI_CS_PIN, GPIO_PIN_SET);
}


static void ST7789_ExecuteCommandList (const ui8 *addr)
{
	ST7789_SendCmd(ST7789_DISPOFF);

    ui8 numCommands, numArgs;
    ui16 ms;

    numCommands = *addr++;
    while(numCommands--) {
        ui8 cmd = *addr++;
        ST7789_SendCmd(cmd);

        numArgs = *addr++;
        // If high bit set, delay follows args
        ms = numArgs & DELAY;
        numArgs &= ~DELAY;
        if(numArgs) {
            ST7789_SendDataMASS((ui8*)addr, numArgs);
            addr += numArgs;
        }

        if(ms) {
            ms = *addr++;
            if(ms == 255) ms = 500;
            HAL_Delay(ms);
        }
    }
}


void ST7789_Blit (ui16 x, ui16 y, ui16 w, ui16 h, ui8 *data)
{
    ST7789_SetWindow(x, y, x + w - 1, y + h - 1);

    ui16* data16 = (ui16*)data;

    for (ui16 i = 0; i < w * h; ++i)
    {
    	data16[i] = __REV16(data16[i]);
    }
	
	ST7789_Select();
    ST7789_SendDataMASS((ui8*)data16, sizeof(ui16) * w * h);
    ST7789_Unselect();
}


void ST7789_HardReset (void)
{
	HAL_GPIO_WritePin(LCD_SPI_RES_GPIO_PORT, LCD_SPI_RES_PIN, GPIO_PIN_RESET);
	HAL_Delay(20);	
	HAL_GPIO_WritePin(LCD_SPI_RES_GPIO_PORT, LCD_SPI_RES_PIN, GPIO_PIN_SET);
	HAL_Delay(20);
}


__inline static void ST7789_SendCmd (ui8 cmd)
{
	HAL_GPIO_WritePin(LCD_SPI_DC_GPIO_PORT, LCD_SPI_DC_PIN, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&ST7789_SPI_HAL, &cmd, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(LCD_SPI_DC_GPIO_PORT, LCD_SPI_DC_PIN, GPIO_PIN_SET);
}


__inline static void ST7789_SendData (ui8 data)
{
	HAL_SPI_Transmit(&ST7789_SPI_HAL, &data, 1, HAL_MAX_DELAY);
}


__inline static void ST7789_SendDataMASS (ui8 *buff, size_t buff_size)
{
	/* DMA memory incremental enable */
//	hdma2_tx_spi1.Init.MemInc = DMA_MINC_ENABLE;
//	if (HAL_DMA_Init(&hdma2_tx_spi1) != HAL_OK)
//		HardwareErrorHandler();

	HAL_SPI_Transmit(&ST7789_SPI_HAL, buff, buff_size, HAL_MAX_DELAY);

	/* DMA memory incremental disable */
//	hdma2_tx_spi1.Init.MemInc = DMA_MINC_DISABLE;
//	if (HAL_DMA_Init(&hdma2_tx_spi1) != HAL_OK)
//		HardwareErrorHandler();
}


void ST7789_FillRect (i16 x, i16 y, i16 w, i16 h, ui16 color)
{
	ST7789_SetWindow(x, y, x + w - 1, y + h - 1);

	ui8 DMA_Buff [] = { (ui8)(color & 0x00FF), color >> 8 };
	LCD_SPI_Transmit_DMA(&hspi1, DMA_Buff, w * h * 2);
}


static void ST7789_SetWindow (ui16 x0, ui16 y0, ui16 x1, ui16 y1)
{
	ST7789_Select();
	ST7789_ColumnSet(x0, x1);
	ST7789_RowSet(y0, y1);
	ST7789_SendCmd(ST7789_RAMWR);
	ST7789_Unselect();
}


static void ST7789_ColumnSet (ui16 ColumnStart, ui16 ColumnEnd)
{
	ColumnStart += ST7789_X_Start;
	ColumnEnd += ST7789_X_Start;

	ST7789_SendCmd(ST7789_CASET);

	ui8 data [] = { ColumnStart >> 8, ColumnStart & 0xFF, ColumnEnd >> 8, ColumnEnd & 0xFF};
	HAL_SPI_Transmit(&ST7789_SPI_HAL, data, 4, HAL_MAX_DELAY);
}


static void ST7789_RowSet (ui16 RowStart, ui16 RowEnd)
{
	RowStart += ST7789_Y_Start;
	RowEnd += ST7789_Y_Start;
	
	ST7789_SendCmd(ST7789_RASET);

	ui8 data [] = { RowStart >> 8, RowStart & 0xFF, RowEnd >> 8, RowEnd & 0xFF};
	HAL_SPI_Transmit(&ST7789_SPI_HAL, data, 4, HAL_MAX_DELAY);
}


void ST7789_DrawPixel(i16 x, i16 y, ui16 color)
{
	ST7789_Select();
	ST7789_ColumnSet(x, x);
	ST7789_RowSet(y, y);
	ST7789_SendCmd(ST7789_RAMWR);

	ui8 buff [2];
	buff[0] = color >> 8;
	buff[1] = color & 0xFF;

	ST7789_SendDataMASS(buff, 2);

	ST7789_Unselect();
}


void init_board (void)
{
	LCD_TIM_CLOCK_ENABLE();
	LCD_TIM_PWM_GPIO_CLOCK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct;

	/* Common configuration for all channels */
	GPIO_InitStruct.Mode		= GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull		= GPIO_NOPULL;
	GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate	= LCD_TIM_PWM_PIN_AF;
	GPIO_InitStruct.Pin			= LCD_TIM_PWM_PIN;
	HAL_GPIO_Init(LCD_TIM_PWM_GPIO_PORT, &GPIO_InitStruct);

	htim1.Instance = LCD_TIM_INSTANCE;

	htim1.Init.Prescaler         	= (LCD_TIM_BUS_FREQ / 1000000) - 1;
	htim1.Init.Period            	= 1000;
	htim1.Init.ClockDivision     	= 0;
	htim1.Init.CounterMode       	= TIM_COUNTERMODE_UP;
	htim1.Init.RepetitionCounter 	= 0;
	htim1.Init.AutoReloadPreload 	= TIM_AUTORELOAD_PRELOAD_DISABLE;

	if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
	{
		/* Initialization Error */
		HardwareErrorHandler();
	}

	TIM_OC_InitTypeDef sConfigOC;

	/* Common configuration for all channels */
	sConfigOC.OCMode       = TIM_OCMODE_PWM1;
	sConfigOC.OCPolarity   = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode   = TIM_OCFAST_DISABLE;
	sConfigOC.OCNPolarity  = TIM_OCNPOLARITY_LOW;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	sConfigOC.OCIdleState  = TIM_OCIDLESTATE_RESET;

	/* Set the pulse value for PWM channel */
	sConfigOC.Pulse = 999;

	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, LCD_TIM_PWM_CHANNEL) != HAL_OK)
	{
		/* Configuration Error */
		HardwareErrorHandler();
	}

	/* Start PWM channel */
	if (HAL_TIM_PWM_Start(&htim1, LCD_TIM_PWM_CHANNEL) != HAL_OK)
	{
		/* PWM Generation Error */
		HardwareErrorHandler();
	}


	LCD_SPI_GPIO_CLOCK_ENABLE();

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


	LCD_GPIO_CLOCK_ENABLE();

	GPIO_InitStruct.Pin			= LCD_SPI_RES_PIN;
	GPIO_InitStruct.Mode		= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull		= GPIO_NOPULL;
	GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LCD_SPI_RES_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LCD_SPI_CS_PIN;
	HAL_GPIO_Init(LCD_SPI_CS_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LCD_SPI_DC_PIN;
	HAL_GPIO_Init(LCD_SPI_DC_GPIO_PORT, &GPIO_InitStruct);

	HAL_GPIO_WritePin(LCD_SPI_RES_GPIO_PORT, LCD_SPI_RES_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_SPI_CS_GPIO_PORT, LCD_SPI_CS_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_SPI_DC_GPIO_PORT, LCD_SPI_DC_PIN, GPIO_PIN_RESET);


	LCD_SPI_CLOCK_ENABLE();

	/* SPI parameter configuration */
	hspi1.Instance = LCD_SPI_INSTANCE;

	hspi1.Init.Mode					= SPI_MODE_MASTER;
	hspi1.Init.Direction			= SPI_DIRECTION_1LINE;
	hspi1.Init.DataSize				= SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity			= SPI_POLARITY_HIGH;
	hspi1.Init.CLKPhase				= SPI_PHASE_2EDGE;
	hspi1.Init.NSS					= SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler	= SPI_BAUDRATEPRESCALER_2;
	hspi1.Init.FirstBit				= SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode				= SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation		= SPI_CRCCALCULATION_DISABLE;

	if (HAL_SPI_Init(&hspi1) != HAL_OK)
	{
		HardwareErrorHandler();
	}

	SPI_1LINE_TX(&hspi1);
	__HAL_SPI_ENABLE(&hspi1);

	/* Enable DMAx clock */
	LCD_SPI_DMA_CLOCK_ENABLE();

	hdma2_tx_spi1.Instance = LCD_SPI_TX_DMA_STREAM;

	hdma2_tx_spi1.Init.Channel				= LCD_SPI_TX_DMA_CHANNEL;
	hdma2_tx_spi1.Init.Direction			= DMA_MEMORY_TO_PERIPH;
	hdma2_tx_spi1.Init.PeriphInc			= DMA_PINC_DISABLE;
	hdma2_tx_spi1.Init.MemInc				= DMA_MINC_DISABLE;
	hdma2_tx_spi1.Init.PeriphDataAlignment	= DMA_PDATAALIGN_HALFWORD;
	hdma2_tx_spi1.Init.MemDataAlignment		= DMA_MDATAALIGN_HALFWORD;
	hdma2_tx_spi1.Init.Mode					= DMA_NORMAL;
	hdma2_tx_spi1.Init.Priority				= DMA_PRIORITY_HIGH;
	hdma2_tx_spi1.Init.FIFOMode				= DMA_FIFOMODE_DISABLE;

	if (HAL_DMA_Init(&hdma2_tx_spi1) != HAL_OK)
		HardwareErrorHandler();

	__HAL_LINKDMA(&hspi1, hdmatx, hdma2_tx_spi1);

	/* NVIC configuration for DMA transfer complete interrupt */
	HAL_NVIC_SetPriority(LCD_SPI_TX_DMA_CH_IRQN, 2, 0);
	HAL_NVIC_EnableIRQ(LCD_SPI_TX_DMA_CH_IRQN);

	ST7789_Init();

	ST7789_FillRect(0, 0, ST7789_Width, ST7789_Height, ST7789_BLACK);
}


void ST7789_SetBacklight (ui16 val)
{
	LCD_TIM_INSTANCE->CCR1 = 1000 - (pow(val, 3) / 1000);
}
