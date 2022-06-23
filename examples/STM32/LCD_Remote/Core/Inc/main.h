/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MENU_BTN_Pin GPIO_PIN_13
#define MENU_BTN_GPIO_Port GPIOC
#define JOY_BTN_Pin GPIO_PIN_1
#define JOY_BTN_GPIO_Port GPIOC
#define LED_Pin GPIO_PIN_0
#define LED_GPIO_Port GPIOB
#define LCD_RS_Pin GPIO_PIN_12
#define LCD_RS_GPIO_Port GPIOF
#define LCD_D7_Pin GPIO_PIN_13
#define LCD_D7_GPIO_Port GPIOF
#define LCD_D4_Pin GPIO_PIN_14
#define LCD_D4_GPIO_Port GPIOF
#define ENC_B_Pin GPIO_PIN_15
#define ENC_B_GPIO_Port GPIOF
#define ENC_B_EXTI_IRQn EXTI15_10_IRQn
#define LCD_D6_Pin GPIO_PIN_9
#define LCD_D6_GPIO_Port GPIOE
#define LCD_D5_Pin GPIO_PIN_11
#define LCD_D5_GPIO_Port GPIOE
#define ENC_A_Pin GPIO_PIN_13
#define ENC_A_GPIO_Port GPIOE
#define ENC_A_EXTI_IRQn EXTI15_10_IRQn
#define BT_EN_Pin GPIO_PIN_13
#define BT_EN_GPIO_Port GPIOB
#define LCD_BL_Pin GPIO_PIN_14
#define LCD_BL_GPIO_Port GPIOD
#define LCD_EN_Pin GPIO_PIN_15
#define LCD_EN_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
