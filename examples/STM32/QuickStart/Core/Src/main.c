/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/*	____________________________________________________________________
 *
 *	This is an example sketch for STM32, that shows how to control
 *	SimpleBGC-driven gimbal via Serial API. API specs are available at
 *	http://www.basecamelectronics.com/serialapi/
 *	____________________________________________________________________
 */

/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "sbgc32.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define		SBGC_GET_ANGLES_TIMEOUT			15000
#define		SBGC_GET_ANGLES_INTERVAL		1000

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

static		sbgcMainParams3_t		MainParams3;

static		sbgcRealTimeData_t		RealTimeData;
static		sbgcGetAnglesExt_t		GetAnglesExt;

static		sbgcBoardInfo_t			BoardInfo;

static		sbgcConfirm_t			Confirm;

static		sbgcTicks_t				timestamp;


#if (SBGC_NON_BLOCKING_MODE)

	void CallbackReadRealTimeData (void *param)
	{
		unused_(param);

		DebugSBGC32_PrintMessage(&SBGC32_Device, "Realtime data received!\n");

		/* This data may be obtained from the RealTimeData structure */
	}


	void CallbackGetAnglesExt (void *param)
	{
		i32 frameCamAngleTemp = sbgcDegreeToAngle(GetAnglesExt.AxisGAE[PITCH].frameCamAngle);

		/* If the callback argument was NULL, the library defaults to passing a pointer to the SBGC32_Device object */
		DebugSBGC32_PrintStructElement((sbgcGeneral_t*)param, &frameCamAngleTemp, "Current Angle Pitch =", sbgcINT);
	}

#endif

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
  /* USER CODE BEGIN 2 */

	/* SimpleBGC32 Init */
	SBGC32_Init(&SBGC32_Device);

	/* Configure the gimbal movement */
	ControlConfig.flags = CtrlCONFIG_FLAG_NEED_CONFIRM;

	ControlConfig.AxisCCtrl[PITCH].angleLPF = 1;
	ControlConfig.AxisCCtrl[PITCH].speedLPF = 1;

	Control.mode[PITCH] = CtrlMODE_ANGLE;

	Control.AxisC[PITCH].angle = sbgcAngleToDegree(30);
	Control.AxisC[PITCH].speed = sbgcSpeedToValue(3);

	/* Let's consider several operational modes */
	#if (SBGC_USES_TOKENS)

		/* Creating the tokens */
		static sbgcCommandToken_t tokenMP3, tokenRTD, tokenGAE, tokenBI, tokenCtrl;

		/* Register the serial commands */
		/* It's possible to use the commands without tokens in this mode */
		/* Configure gimbal to further control */
		SBGC32_ControlConfig(&SBGC32_Device, &ControlConfig, &Confirm, SBGC_DEFAULT_ARGS_);

		/* Send and receive the 2 registered serial commands */
		sbgcBlockQueue(SBGC32_ProcessAllCommands(&SBGC32_Device));

		if (SerialAPI_GetConfirmStatus(&Confirm) == sbgcCONFIRM_RECEIVED)
			DebugSBGC32_PrintMessage(&SBGC32_Device, "The gimbal configured successfully!\n");

		else if (SerialAPI_GetConfirmStatus(&Confirm) == sbgcCONFIRM_ERROR)
			DebugSBGC32_PrintMessage(&SBGC32_Device, "Gimbal configuration parameters error!\n");

		else  // sbgcCONFIRM_NOT_RECEIVED
			DebugSBGC32_PrintMessage(&SBGC32_Device, "Communication Error! The confirmation command was not received at all!\n");

		/* This command will enter the user callback after successful reception */
		SBGC32_ReadRealTimeData4(&SBGC32_Device, &RealTimeData, SBGC_DEFAULT_FEATURES_, &tokenRTD, CallbackReadRealTimeData, NULL);

		/* It's also possible to use a single token for two commands if each of
		   those commands consists of just one internal serial command */
		SBGC32_Control(&SBGC32_Device, &Control, SBGC_DEFAULT_FEATURES_, &tokenCtrl, SBGC_NO_CALLBACK_);
		/* The SBGC32_Control function doesn't automatically process the confirmation command, so it must be registered manually */
		SBGC32_CheckConfirmation(&SBGC32_Device, &Confirm, CMD_CONTROL, SBGC_DEFAULT_FEATURES_, &tokenCtrl, SBGC_NO_CALLBACK_);

		/* Register usual commands */
		SBGC32_ReadBoardInfo(&SBGC32_Device, &BoardInfo, 0, SBGC_DEFAULT_FEATURES_, &tokenBI, SBGC_NO_CALLBACK_);
		SBGC32_ReadParams3(&SBGC32_Device, &MainParams3, sbgcCURRENT_PROFILE, SBGC_DEFAULT_FEATURES_, &tokenMP3, SBGC_NO_CALLBACK_);

		/* Register the serial commands that will not be deleted */
		SBGC32_GetAnglesExt(&SBGC32_Device, &GetAnglesExt, SCParam_RETAIN | SCParam_NO_NEED_LOG, SCPrior_LOW, SCTimeout_DEFAULT,
				&tokenGAE, CallbackGetAnglesExt, NULL);

		/* Thus there are 10 serial commands in the main command queue */

		/* Using tokens, it's possible to manage the serial commands in any order */
		sbgcBlockCommand(SBGC32_Transmit(&SBGC32_Device, &tokenBI));

		sbgcBlockCommand(SBGC32_Transmit(&SBGC32_Device, &tokenRTD));

		sbgcBlockCommand(SBGC32_Receive(&SBGC32_Device, &tokenBI));

		sbgcBlockCommand(SBGC32_Transmit(&SBGC32_Device, &tokenMP3));

		sbgcBlockCommand(SBGC32_Receive(&SBGC32_Device, &tokenRTD));

		sbgcBlockCommand(SBGC32_Transmit(&SBGC32_Device, &tokenCtrl));

		sbgcBlockCommand(SBGC32_Receive(&SBGC32_Device, &tokenMP3));

		sbgcBlockCommand(SBGC32_Receive(&SBGC32_Device, &tokenCtrl));

		/* sbgcBlockCommand is a stub to successful handle of the serial commands.
		   It's possible to avoid using this stub by waiting for specific time
		   intervals or sending/receiving commands with a significant delay
		   after executing external user code */

		if (SerialAPI_GetConfirmStatus(&Confirm) != sbgcCONFIRM_RECEIVED)
		{
			DebugSBGC32_PrintMessage(&SBGC32_Device, "No confirmation of control detected! Terminating the program...");

			/* There is no point in proceeding without starting the data stream */
			while (1);  // Stop the program here
		}

		/* Get current time */
		timestamp = sbgcGetTick();

		/* Get the current PITCH angle over a period of SBGC_GET_ANGLES_TIMEOUT */
		while ((sbgcGetTick() - timestamp) < SBGC_GET_ANGLES_TIMEOUT)
		{
			SBGC32_Transmit(&SBGC32_Device, &tokenGAE);

			sbgcDelay(SBGC_GET_ANGLES_INTERVAL);

			SBGC32_Receive(&SBGC32_Device, &tokenGAE);
		}

		/* Free this command by exchanging SCParam_RETAIN parameter with SCParam_NO */
		SBGC32_GetAnglesExt(&SBGC32_Device, &GetAnglesExt, SCParam_NO, SCPrior_LOW, SCTimeout_DEFAULT, &tokenGAE, SBGC_NO_CALLBACK_);

		/* Return camera to the start position */
		SBGC32_ExecuteMenu(&SBGC32_Device, MENU_CMD_HOME_POSITION, &Confirm, SBGC_DEFAULT_ARGS_);

		/* Finish the last 4 serial commands */
		sbgcBlockQueue(SBGC32_ProcessAllCommands(&SBGC32_Device));


	#elif (SBGC_NON_BLOCKING_MODE)

		/* Register the serial commands */
		/* Configure gimbal to further control */
		SBGC32_ControlConfig(&SBGC32_Device, &ControlConfig, &Confirm, SBGC_DEFAULT_ARGS_);

		/* Send and receive the 2 registered serial commands */
		sbgcBlockQueue(SBGC32_ProcessAllCommands(&SBGC32_Device));

		if (SerialAPI_GetConfirmStatus(&Confirm) == sbgcCONFIRM_RECEIVED)
			DebugSBGC32_PrintMessage(&SBGC32_Device, "The gimbal configured successfully!\n");

		else if (SerialAPI_GetConfirmStatus(&Confirm) == sbgcCONFIRM_ERROR)
			DebugSBGC32_PrintMessage(&SBGC32_Device, "Gimbal configuration parameters error!\n");

		else  // sbgcCONFIRM_NOT_RECEIVED
			DebugSBGC32_PrintMessage(&SBGC32_Device, "Communication Error! The confirmation command was not received at all!\n");

		/* This command will enter the user callback after successful reception */
		SBGC32_ReadRealTimeData4(&SBGC32_Device, &RealTimeData, SBGC_DEFAULT_FEATURES_, CallbackReadRealTimeData, NULL);

		/* The SBGC32_Control function doesn't automatically process the confirmation command, so it must be registered manually */
		SBGC32_Control(&SBGC32_Device, &Control, SBGC_DEFAULT_FEATURES_, SBGC_NO_CALLBACK_);
		SBGC32_CheckConfirmation(&SBGC32_Device, &Confirm, CMD_CONTROL, SCParam_FORCE_CALLBACK, SCPrior_LOW, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);

		/* Register usual commands */
		SBGC32_ReadBoardInfo(&SBGC32_Device, &BoardInfo, 0, SBGC_DEFAULT_FEATURES_, SBGC_NO_CALLBACK_);
		SBGC32_ReadParams3(&SBGC32_Device, &MainParams3, sbgcCURRENT_PROFILE, SBGC_DEFAULT_ARGS_);

		/* Thus there are 8 serial commands in the main command queue */
		/* Process these serial command */
		sbgcBlockQueue(SBGC32_ProcessAllCommands(&SBGC32_Device));

		if (SerialAPI_GetConfirmStatus(&Confirm) != sbgcCONFIRM_RECEIVED)
		{
			DebugSBGC32_PrintMessage(&SBGC32_Device, "No confirmation of control detected! Terminating the program...");

			/* There is no point in proceeding without starting the data stream */
			while (1);  // Stop the program here
		}

		/* Register the serial commands that will not be deleted */
		SBGC32_GetAnglesExt(&SBGC32_Device, &GetAnglesExt, SCParam_RETAIN | SCParam_NO_NEED_LOG, SCPrior_LOW, SCTimeout_DEFAULT,
				CallbackGetAnglesExt, NULL);

		/* Get current time */
		timestamp = sbgcGetTick();

		/* Get the current PITCH angle over a period of SBGC_GET_ANGLES_TIMEOUT */
		while ((sbgcGetTick() - timestamp) < SBGC_GET_ANGLES_TIMEOUT)
		{
			SBGC32_TransmitAllCommands(&SBGC32_Device);

			sbgcDelay(SBGC_GET_ANGLES_INTERVAL);

			SBGC32_ReceiveAllCommands(&SBGC32_Device);
		}

		/* Free this command by exchanging SCParam_RETAIN parameter with SCParam_NO */
		SBGC32_GetAnglesExt(&SBGC32_Device, &GetAnglesExt, SCParam_NO, SCPrior_LOW, SCTimeout_DEFAULT, SBGC_NO_CALLBACK_);

		/* Return camera to the start position */
		SBGC32_ExecuteMenu(&SBGC32_Device, MENU_CMD_HOME_POSITION, &Confirm, SBGC_DEFAULT_ARGS_);

		/* Finish the last 4 serial commands */
		sbgcBlockQueue(SBGC32_ProcessAllCommands(&SBGC32_Device));


	#elif (SBGC_USES_BLOCKING_MODE)

		/* In blocking mode, the buffer automatically compresses to hold only one command */
		/* A registered command is processed immediately with a total wait time of SBGC_DEFAULT_TIMEOUT */
		/* Configure gimbal to further control */
		SBGC32_ControlConfig(&SBGC32_Device, &ControlConfig, &Confirm);

		if (SerialAPI_GetConfirmStatus(&Confirm) == sbgcCONFIRM_RECEIVED)
			DebugSBGC32_PrintMessage(&SBGC32_Device, "The gimbal configured successfully!\n");

		else if (SerialAPI_GetConfirmStatus(&Confirm) == sbgcCONFIRM_ERROR)
			DebugSBGC32_PrintMessage(&SBGC32_Device, "Gimbal configuration parameters error!\n");

		else  // sbgcCONFIRM_NOT_RECEIVED
			DebugSBGC32_PrintMessage(&SBGC32_Device, "Communication Error! The confirmation command was not received at all!\n");

		if (SBGC32_ReadRealTimeData4(&SBGC32_Device, &RealTimeData) == sbgcCOMMAND_OK)
		{
			DebugSBGC32_PrintMessage(&SBGC32_Device, "Realtime data received!\n");

			/* This data may be obtained from the RealTimeData structure */
		}

		/* Process other commands */
		SBGC32_ReadBoardInfo(&SBGC32_Device, &BoardInfo, 0);
		SBGC32_ReadParams3(&SBGC32_Device, &MainParams3, sbgcCURRENT_PROFILE);

		/* The SBGC32_Control function doesn't automatically process the confirmation command, so it must be received manually */
		SBGC32_Control(&SBGC32_Device, &Control);
		SBGC32_CheckConfirmation(&SBGC32_Device, &Confirm, CMD_CONTROL);

		if (SerialAPI_GetConfirmStatus(&Confirm) != sbgcCONFIRM_RECEIVED)
		{
			DebugSBGC32_PrintMessage(&SBGC32_Device, "No confirmation of control detected! Terminating the program...");

			/* There is no point in proceeding without starting the data stream */
			while (1);  // Stop the program here
		}

		/* Get current time */
		timestamp = sbgcGetTick();

		i32 frameCamAngleTemp;

		/* Get the current PITCH angle over a period of SBGC_GET_ANGLES_TIMEOUT */
		while ((sbgcGetTick() - timestamp) < SBGC_GET_ANGLES_TIMEOUT)
		{
			if (SBGC32_GetAnglesExt(&SBGC32_Device, &GetAnglesExt) == sbgcCOMMAND_OK)
			{
				frameCamAngleTemp = sbgcDegreeToAngle(GetAnglesExt.AxisGAE[PITCH].frameCamAngle);

				DebugSBGC32_PrintStructElement(&SBGC32_Device, &frameCamAngleTemp, "Current Angle Pitch =", sbgcINT);
			}

			sbgcDelay(SBGC_GET_ANGLES_INTERVAL);
		}

		/* Return camera to the start position */
		SBGC32_ExecuteMenu(&SBGC32_Device, MENU_CMD_HOME_POSITION, &Confirm);

	#endif

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
