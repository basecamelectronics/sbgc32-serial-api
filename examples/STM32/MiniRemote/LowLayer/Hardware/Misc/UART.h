/** ____________________________________________________________________
 *
 *	@file		UART.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_UART_H_
#define		_UART_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"hardware.h"
#include	"sbgc32.h"

#define		SBGC_UART1_IRQ_HANDLER	USART1_IRQHandler
#define		SBGC_UART2_IRQ_HANDLER	USART2_IRQHandler

#define		SBGC_UART1_DMA_TX_CH_IRQ_HANDLER		DMA2_Stream7_IRQHandler
#define		SBGC_UART1_DMA_RX_CH_IRQ_HANDLER		DMA2_Stream2_IRQHandler

#define		SBGC_UART2_DMA_TX_CH_IRQ_HANDLER		DMA1_Stream6_IRQHandler
#define		SBGC_UART2_DMA_RX_CH_IRQ_HANDLER		DMA1_Stream5_IRQHandler


class UART_DriverSBGC32
{
	private :

		SBGC_DRV_UART_TYPE_DEF__
							huart;

		SBGC_DRV_DMA_TYPE_DEF__
							hdmaTx, hdmaRx;

	public :

		void				Init (ui8 uartN);

		SBGC_DRV_UART_TYPE_DEF__
							*GetAddressUART_Handle (void) { return &huart; }

};


extern UART_DriverSBGC32 DriverSBGC32;


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _UART_H_ */
