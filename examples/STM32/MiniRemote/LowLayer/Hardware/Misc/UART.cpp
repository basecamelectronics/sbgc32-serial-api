/** ____________________________________________________________________
 *
 *	@file		CRC32.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "UART.h"


UART_DriverSBGC32 DriverSBGC32;


void UART_DriverSBGC32::Init (ui8 uartN)
{
	if (uartN == 0)
	{
		/* Configure the UART peripheral */
		GPIO_InitTypeDef SBGC_GPIO_InitStruct;

		__HAL_RCC_GPIOA_CLK_ENABLE();

		/* UART Tx GPIO pin configuration */
		SBGC_GPIO_InitStruct.Pin		= GPIO_PIN_9;
		SBGC_GPIO_InitStruct.Mode		= GPIO_MODE_AF_PP;
		SBGC_GPIO_InitStruct.Pull		= GPIO_PULLUP;
		SBGC_GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_HIGH;
		SBGC_GPIO_InitStruct.Alternate	= GPIO_AF7_USART1;

		HAL_GPIO_Init(GPIOA, &SBGC_GPIO_InitStruct);

		/* UART Rx GPIO pin configuration */
		SBGC_GPIO_InitStruct.Pin		= GPIO_PIN_10;
		SBGC_GPIO_InitStruct.Alternate	= GPIO_AF7_USART1;

		HAL_GPIO_Init(GPIOA, &SBGC_GPIO_InitStruct);


		/* Configure the DMA handler for reception process */
		__HAL_RCC_DMA2_CLK_ENABLE();
		__HAL_RCC_USART1_CLK_ENABLE();

		hdmaRx.Instance					= DMA2_Stream2;
		hdmaRx.Init.Channel				= DMA_CHANNEL_4;
		hdmaRx.Init.Direction			= DMA_PERIPH_TO_MEMORY;
		hdmaRx.Init.PeriphInc			= DMA_PINC_DISABLE;
		hdmaRx.Init.MemInc				= DMA_MINC_ENABLE;
		hdmaRx.Init.PeriphDataAlignment	= DMA_PDATAALIGN_BYTE;
		hdmaRx.Init.MemDataAlignment	= DMA_MDATAALIGN_BYTE;
		hdmaRx.Init.Mode				= DMA_CIRCULAR;
		hdmaRx.Init.Priority			= DMA_PRIORITY_HIGH;
		hdmaRx.Init.FIFOMode			= DMA_FIFOMODE_DISABLE;

		if (HAL_DMA_Init(&hdmaRx) != HAL_OK)
			while (1);

		/* Associate the initialized DMA handle to the UART handle */
		__HAL_LINKDMA(&huart, hdmarx, hdmaRx);


		/* Configure the DMA handler for transmission process */
		hdmaTx.Instance					= DMA2_Stream7;
		hdmaTx.Init.Channel				= DMA_CHANNEL_4;
		hdmaTx.Init.Direction			= DMA_MEMORY_TO_PERIPH;
		hdmaTx.Init.PeriphInc			= DMA_PINC_DISABLE;
		hdmaTx.Init.MemInc				= DMA_MINC_ENABLE;
		hdmaTx.Init.PeriphDataAlignment	= DMA_PDATAALIGN_BYTE;
		hdmaTx.Init.MemDataAlignment	= DMA_MDATAALIGN_BYTE;
		hdmaTx.Init.Mode				= DMA_NORMAL;
		hdmaTx.Init.Priority			= DMA_PRIORITY_HIGH;
		hdmaTx.Init.FIFOMode			= DMA_FIFOMODE_DISABLE;

		if (HAL_DMA_Init(&hdmaTx) != HAL_OK)
			while (1);

		/* Associate the initialized DMA handle to the UART handle */
		__HAL_LINKDMA(&huart, hdmatx, hdmaTx);

		/* DMAx Interrupts Init */
		HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 7, 0);
		HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);

		HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 7, 0);
		HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);


		/* Configure the UART peripheral */
		HAL_NVIC_DisableIRQ(USART1_IRQn);

		huart.Instance				= USART1;
		huart.Init.BaudRate			= 115200;
		huart.Init.WordLength		= UART_WORDLENGTH_8B;
		huart.Init.StopBits			= UART_STOPBITS_1;
		huart.Init.Parity			= UART_PARITY_NONE;
		huart.Init.HwFlowCtl		= UART_HWCONTROL_NONE;
		huart.Init.Mode				= UART_MODE_TX_RX;
		huart.Init.OverSampling		= UART_OVERSAMPLING_16;

		if (HAL_UART_Init(&huart) != HAL_OK)
			while (1);

		/* UARTx Interrupt Init */
		HAL_NVIC_SetPriority(USART1_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(USART1_IRQn);
	}

	else if (uartN == 1)
	{
		/* Configure the UART peripheral */
		GPIO_InitTypeDef SBGC_GPIO_InitStruct = {0};

		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();

		/* RS-422 DE GPIO pin configuration */
		SBGC_GPIO_InitStruct.Pin		= GPIO_PIN_15;
		SBGC_GPIO_InitStruct.Mode		= GPIO_MODE_OUTPUT_PP;
		SBGC_GPIO_InitStruct.Pull		= GPIO_NOPULL;
		SBGC_GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_HIGH;

		HAL_GPIO_Init(GPIOC, &SBGC_GPIO_InitStruct);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);

		/* UART Tx GPIO pin configuration */
		SBGC_GPIO_InitStruct.Pin		= GPIO_PIN_2;
		SBGC_GPIO_InitStruct.Mode		= GPIO_MODE_AF_PP;
		SBGC_GPIO_InitStruct.Pull		= GPIO_PULLUP;
		SBGC_GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_HIGH;
		SBGC_GPIO_InitStruct.Alternate	= GPIO_AF7_USART2;

		HAL_GPIO_Init(GPIOA, &SBGC_GPIO_InitStruct);

		/* UART Rx GPIO pin configuration */
		SBGC_GPIO_InitStruct.Pin		= GPIO_PIN_3;
		SBGC_GPIO_InitStruct.Alternate	= GPIO_AF7_USART2;

		HAL_GPIO_Init(GPIOA, &SBGC_GPIO_InitStruct);


		/* Configure the DMA handler for reception process */
		__HAL_RCC_DMA1_CLK_ENABLE();
		__HAL_RCC_USART2_CLK_ENABLE();

		hdmaRx.Instance					= DMA1_Stream5;
		hdmaRx.Init.Channel				= DMA_CHANNEL_4;
		hdmaRx.Init.Direction			= DMA_PERIPH_TO_MEMORY;
		hdmaRx.Init.PeriphInc			= DMA_PINC_DISABLE;
		hdmaRx.Init.MemInc				= DMA_MINC_ENABLE;
		hdmaRx.Init.PeriphDataAlignment	= DMA_PDATAALIGN_BYTE;
		hdmaRx.Init.MemDataAlignment	= DMA_MDATAALIGN_BYTE;
		hdmaRx.Init.Mode				= DMA_CIRCULAR;
		hdmaRx.Init.Priority			= DMA_PRIORITY_HIGH;
		hdmaRx.Init.FIFOMode			= DMA_FIFOMODE_DISABLE;

		if (HAL_DMA_Init(&hdmaRx) != HAL_OK)
			while (1);

		/* Associate the initialized DMA handle to the UART handle */
		__HAL_LINKDMA(&huart, hdmarx, hdmaRx);


		/* Configure the DMA handler for transmission process */
		hdmaTx.Instance					= DMA1_Stream6;
		hdmaTx.Init.Channel				= DMA_CHANNEL_4;
		hdmaTx.Init.Direction			= DMA_MEMORY_TO_PERIPH;
		hdmaTx.Init.PeriphInc			= DMA_PINC_DISABLE;
		hdmaTx.Init.MemInc				= DMA_MINC_ENABLE;
		hdmaTx.Init.PeriphDataAlignment	= DMA_PDATAALIGN_BYTE;
		hdmaTx.Init.MemDataAlignment	= DMA_MDATAALIGN_BYTE;
		hdmaTx.Init.Mode				= DMA_NORMAL;
		hdmaTx.Init.Priority			= DMA_PRIORITY_HIGH;
		hdmaTx.Init.FIFOMode			= DMA_FIFOMODE_DISABLE;

		if (HAL_DMA_Init(&hdmaTx) != HAL_OK)
			while (1);

		/* Associate the initialized DMA handle to the UART handle */
		__HAL_LINKDMA(&huart, hdmatx, hdmaTx);

		/* DMAx Interrupts Init */
		HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 7, 0);
		HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

		HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 7, 0);
		HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);


		/* Configure the UART peripheral */
		HAL_NVIC_DisableIRQ(USART2_IRQn);

		huart.Instance				= USART2;
		huart.Init.BaudRate			= 115200;
		huart.Init.WordLength		= UART_WORDLENGTH_8B;
		huart.Init.StopBits			= UART_STOPBITS_1;
		huart.Init.Parity			= UART_PARITY_NONE;
		huart.Init.HwFlowCtl		= UART_HWCONTROL_NONE;
		huart.Init.Mode				= UART_MODE_TX_RX;
		huart.Init.OverSampling		= UART_OVERSAMPLING_16;

		if (HAL_UART_Init(&huart) != HAL_OK)
			while (1);

		/* UARTx Interrupt Init */
		HAL_NVIC_SetPriority(USART2_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(USART2_IRQn);
	}

	else  // 2
	{
		/* Configure the UART peripheral */
		GPIO_InitTypeDef SBGC_GPIO_InitStruct = {0};

		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();

		/* RS-422 DE GPIO pin configuration */
		SBGC_GPIO_InitStruct.Pin		= GPIO_PIN_2;
		SBGC_GPIO_InitStruct.Mode		= GPIO_MODE_OUTPUT_PP;
		SBGC_GPIO_InitStruct.Pull		= GPIO_NOPULL;
		SBGC_GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_HIGH;

		HAL_GPIO_Init(GPIOB, &SBGC_GPIO_InitStruct);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);

		/* UART Tx GPIO pin configuration */
		SBGC_GPIO_InitStruct.Pin		= GPIO_PIN_11;
		SBGC_GPIO_InitStruct.Mode		= GPIO_MODE_AF_PP;
		SBGC_GPIO_InitStruct.Pull		= GPIO_PULLUP;
		SBGC_GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_HIGH;
		SBGC_GPIO_InitStruct.Alternate	= GPIO_AF8_USART6;

		HAL_GPIO_Init(GPIOA, &SBGC_GPIO_InitStruct);

		/* UART Rx GPIO pin configuration */
		SBGC_GPIO_InitStruct.Pin		= GPIO_PIN_12;
		SBGC_GPIO_InitStruct.Alternate	= GPIO_AF8_USART6;

		HAL_GPIO_Init(GPIOA, &SBGC_GPIO_InitStruct);

		/* Configure the UART peripheral */
		__HAL_RCC_USART6_CLK_ENABLE();

		huart.Instance				= USART6;
		huart.Init.BaudRate			= 9600;
		huart.Init.WordLength		= UART_WORDLENGTH_8B;
		huart.Init.StopBits			= UART_STOPBITS_1;
		huart.Init.Parity			= UART_PARITY_NONE;
		huart.Init.HwFlowCtl		= UART_HWCONTROL_NONE;
		huart.Init.Mode				= UART_MODE_TX_RX;
		huart.Init.OverSampling		= UART_OVERSAMPLING_16;

		if (HAL_UART_Init(&huart) != HAL_OK)
			while (1);

		while (1)
		{
			HAL_UART_Transmit(&huart, (ui8*)"Hello!", sizeof("Hello!"), 10);
		}
	}
}
