/** ____________________________________________________________________
 *
 * 	@file		MCU_Config.h
 *
 *	@brief 		STM32 MCU configurations header file
 *
 *				<center><a href="https://www.basecamelectronics.com">
 *				www.basecamelectronics.com</a>
 *	____________________________________________________________________
 *
 *	@attention	<center><h3>
 *	Copyright © 2023 BaseCam Electronics™.</h3></center>
 *	<center>All rights reserved.</center>
 *
 *	Licensed under the Apache License, Version 2.0 (the "License");
 *	you may not use this file except in compliance with the License.
 *	You may obtain a copy of the License at
 *
 *	http://www.apache.org/licenses/LICENSE-2.0
 *
 *	Unless required by applicable law or agreed to in writing, software
 *	distributed under the License is distributed on an "AS IS" BASIS,
 *	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 *	implied. See the License for the specific language governing
 *	permissions and limitations under the License.
 *	____________________________________________________________________
 */

#ifndef		_MCU_CONFIG_H_
#define		_MCU_CONFIG_H_

#ifdef 		__cplusplus
extern 		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../../sources/core/adjunct.h"


/*  - - - - - User Defined Parameters - - - - - - */
#define		STM32F7__								/*!<  STM32 controller family														*/

#define		DRV_USE_FREERTOS		SET_OFF			/*!<  UART driver required FreeRTOS support											*/

#define		DRV_CUSTOM_SETTING		SET_OFF			/*!<  Whole SBGC32 driver configured manually through HAL or LL without CubeMX		*/

#if (DRV_USE_FREERTOS == SET_OFF)
	#define	DRV_HAL_TIMER			SET_ON			/*!<  Timer driver works with NVIC through HAL										*/
	#define	DRV_LL_TIMER			SET_OFF			/*!<  Timer driver works with NVIC through LL										*/
#endif

#define		DRV_HAL_NVIC_UART		SET_ON			/*!<  UART driver works with NVIC through HAL										*/
#define		DRV_HAL_DMA_UART		SET_OFF			/*!<  UART driver works with DMA through HAL										*/
#define		DRV_LL_NVIC_UART		SET_OFF			/*!<  UART driver works with NVIC through LL										*/
#define		DRV_LL_DMA_UART			SET_OFF			/*!<  UART driver works with DMA through LL											*/

#define		DRV_USE_UART_DEBUG		SET_ON			/*!<  UART debug flag																*/


/* Include driver files */
#if (DRV_CUSTOM_SETTING)
	#if (DRV_HAL_TIMER) || (DRV_HAL_NVIC_UART) || (DRV_HAL_DMA_UART)
		#include					"stm32f7xx_hal.h"
	#else
		#include					"stm32f7xx.h"
	#endif

	#if (DRV_LL_TIMER)
		#include					"stm32f7xx_ll_tim.h"
	#endif

	#if (DRV_LL_TIMER) || (DRV_LL_NVIC_UART) || (DRV_LL_DMA_UART)
		#include					"stm32f7xx_ll_bus.h"
		#include					"stm32f7xx_ll_pwr.h"
		#include					"stm32f7xx_ll_rcc.h"
		#include					"stm32f7xx_ll_system.h"
		#include					"stm32f7xx_ll_utils.h"

		#if (DRV_LL_NVIC_UART) || (DRV_LL_DMA_UART)
			#include				"stm32f7xx_ll_usart.h"
			#include				"stm32f7xx_ll_gpio.h"

			#if (DRV_LL_DMA_UART)
				#include			"stm32f7xx_ll_dma.h"
			#endif
		#endif
	#endif
/*  - - - - - - - - - - - - - - - - - - - - - - - */

	#include "stm32_it.h"

#else
	#include "tim.h"
	#include "usart.h"
#endif


#if ((DRV_USE_FREERTOS == SET_OFF) && ((DRV_HAL_TIMER) + (DRV_LL_TIMER)) != -1)
	#error "Error! Please, select a one time-control method!"
#endif

#if (((DRV_HAL_NVIC_UART) + (DRV_HAL_DMA_UART) + (DRV_LL_NVIC_UART) + (DRV_LL_DMA_UART)) != -1)
	#error "Error! Please, select a one UART-communication method!"
#endif

/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef 		__cplusplus
			}
#endif

#endif		/* _MCU_CONFIG_H_ */
