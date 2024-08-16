/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "app.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                       Global Software Objects                      */
/* __________________________________________________________________ */

			sbgcGeneral_t			SBGC32_Device;

static		sbgcControl_t			Control;
static		sbgcControlConfig_t		ControlConfig;

static		sbgcConfirm_t			Confirm;

			InputsInfo_t			InputsInfo;

static		i16 servoOut [SBGC_SERVO_OUTS_NUM] = {	SBGC_SERVO_OUT_DISABLED, SBGC_SERVO_OUT_DISABLED,
													SBGC_SERVO_OUT_DISABLED, SBGC_SERVO_OUT_DISABLED};

static		AverageValue_t JoystickAverage [2];

static		ui32 currentTime;
static		ui32 lastControlTime = 0;
static		ui32 lastButtonTime;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */

  	InitADC(&InputsInfo, JOYSTICK_ADC);

	/* SimpleBGC32 Init */
	SBGC32_Init(&SBGC32_Device);

	/* Control Configurations */
	Control.mode[PITCH] = CtrlMODE_ANGLE;
	Control.mode[YAW] = CtrlMODE_ANGLE;

	Control.AxisC[PITCH].angle = 0;
	Control.AxisC[YAW].angle = 0;

	#ifdef SET_SPEED

		Control.AxisC[PITCH].speed = SET_SPEED;
		Control.AxisC[YAW].speed = SET_SPEED;

	#endif

	ControlConfig.flags = CtrlCONFIG_FLAG_NO_CONFIRM;

	InputsInfo.recBtn = BTN_RELEASED;
	InputsInfo.menuBtn = BTN_RELEASED;

	AverageInit(&JoystickAverage[0], LOW_PASS_FACTOR);
	AverageInit(&JoystickAverage[1], LOW_PASS_FACTOR);

	servoOut[PWM_SERVO_OUT_IDX] = PWM_CAM_REC_OFF;


	SBGC32_ControlConfig(&SBGC32_Device, &ControlConfig, SBGC_NO_CONFIRM);

	SBGC32_SetServoOut(&SBGC32_Device, servoOut);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		/* Getting current time */
		currentTime = sbgcGetTick();


		/* - - - - - - - - - - Joystick Handling - - - - - - - - - - */

		ReadADC_Inputs(&InputsInfo);

		AverageValue(&JoystickAverage[0], (i16)sbgcDegreeToAngle(YAW_ANGLE_MIN) +
			(i16)((i32)InputsInfo.ADC_INx[ADC_JOY_Y] * sbgcDegreeToAngle(YAW_ANGLE_MAX - YAW_ANGLE_MIN) / (1 << ADC_RESOLUTION)));

		AverageValue(&JoystickAverage[1], (i16)sbgcDegreeToAngle(PITCH_ANGLE_MIN) +
			(i16)((i32)InputsInfo.ADC_INx[ADC_JOY_X] * sbgcDegreeToAngle(PITCH_ANGLE_MAX - PITCH_ANGLE_MIN) / (1 << ADC_RESOLUTION)));


		if ((currentTime - lastControlTime ) > CMD_CONTROL_DELAY)
		{
			lastControlTime = currentTime;

			Control.AxisC[PITCH].angle = JoystickAverage[1].avgRes;
			Control.AxisC[YAW].angle = JoystickAverage[0].avgRes;

			SBGC32_Control(&SBGC32_Device, &Control);
			/* SBGC32_CheckConfirmation(&SBGC32_Device, CMD_CONTROL, &Confirm); */
		}


		/*  - - - - - - - - - - Buttons Handling - - - - - - - - - - */
		/* Rec Button - for long press */
		if (ReadButtonState(REC_BTN_PORT, REC_BTN_PIN))
		{
			if (InputsInfo.recBtn != BTN_PRESSED)
			{
				lastButtonTime = currentTime;
				InputsInfo.recBtn = BTN_PRESSED;
			}

			if ((currentTime - lastButtonTime > SOFTWARE_ANTI_BOUNCE))
			{
				servoOut[PWM_SERVO_OUT_IDX] = PWM_CAM_REC_ON;
				SBGC32_SetServoOut(&SBGC32_Device, servoOut);
				DEBUG_LED_ON;
			}
		}

		else if ((currentTime - lastButtonTime > SOFTWARE_ANTI_BOUNCE) &&
				 (InputsInfo.recBtn == BTN_PRESSED))
		{
			servoOut[PWM_SERVO_OUT_IDX] = PWM_CAM_REC_OFF;
			SBGC32_SetServoOut(&SBGC32_Device, servoOut);
			DEBUG_LED_OFF;
			InputsInfo.recBtn = BTN_RELEASED;
		}

		/* Menu Button */
		if (ReadButtonState(MENU_BTN_PORT, MENU_BTN_PIN))
		{
			if (InputsInfo.menuBtn == BTN_RELEASED)
			{
				lastButtonTime = currentTime;
				InputsInfo.menuBtn = BTN_PRESSED;
			}

			if ((currentTime - lastButtonTime > SOFTWARE_ANTI_BOUNCE) &&
				(InputsInfo.menuBtn != BTN_POST_PRESSED))
			{
				SBGC32_ExecuteMenu(&SBGC32_Device, MENU_CMD_BUTTON_PRESS, &Confirm);

				if (SerialAPI_GetConfirmStatus(&Confirm) == sbgcCONFIRM_RECEIVED)
					InputsInfo.menuBtn = BTN_POST_PRESSED;
			}
		}

		else if ((currentTime - lastButtonTime > SOFTWARE_ANTI_BOUNCE) &&
				 (InputsInfo.menuBtn != BTN_RELEASED))
			InputsInfo.menuBtn = BTN_RELEASED;


		/* Make a constant sampling time by inserting a delay of 1 ms */
		while ((sbgcGetTick() - currentTime) < 1);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void SerialAPI_FatalErrorHandler (void)
{
	/* User common error handler */
	__disable_irq();

	while (1);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
