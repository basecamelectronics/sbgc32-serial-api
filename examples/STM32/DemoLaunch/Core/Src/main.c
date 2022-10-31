/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

#include "driver_STM32.h"

#include "adjvar/adjvar.h"
#include "gimbalControl/gimbalControl.h"
#include "profiles/profiles.h"
#include "realtime/realtime.h"
#include "service/service.h"

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
/*   					Global Software Objects  					  */
/* __________________________________________________________________ */

            GeneralSBGC_t 			SBGC_1;

static 		ConfirmationState_t		Confirm;

static 		Control_t    			Control;
static 		ControlConfig_t    		ControlConfig;

static 		BoardInfo_t         	BoardInfo;
static 		BoardInfo3_t        	BoardInfo3;
static 		MainParams3_t       	MainParams3;
static 		MainParamsExt_t     	MainParamsExt;
static 		MainParamsExt2_t    	MainParamsExt2;
static 		MainParamsExt3_t   		MainParamsExt3;

static		RealTimeDataCustom_t	RealTimeDataCustom;
static		RealTimeData_t			RealTimeData;

static		AdjVarsGeneral_t		AdjVarsGeneral [3];
extern const
			AdjVarsDebugInfo_t		AdjVarsDebugInfoArray [];

static		DataStreamInterval_t	DataStreamInterval;

static		BeeperSettings_t		BeeperSettings;


static		ui8	DataStreamBuff [20];


TxRxStatus_t PrintBoardParameters (Profile_t slot);
TxRxStatus_t SBGC32_DemoControl (void);
void PrintDataStream (ui8 *pBuff);

/*  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
	/*                         Initialization                         */
	/* ______________________________________________________________ */

	/*  - - - - - - - - - - - - Hardware Init - - - - - - - - - - - - */

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

	/*  - - - - - - - - SBGC Hardware-Software Init - - - - - - - - - */

	/* Driver Init */
	SBGC_1.Drv = malloc(sizeof(Driver_t));
	DriverInit(SBGC_1.Drv, SBGC_SERIAL_PORT, INTERNAL_MAIN_TIMER);

	/* SimpleBGC32 Init */
	SBGC32_DefaultInit(&SBGC_1, UartTransmitData, UartReceiveByte, GetAvailableBytes,
			  		   UartTransmitDebugData, GetTimeMs, SBGC_PROTOCOL_V2);

	/* - - - - - - - - - High Layer Software Init - - - - - - - - - - */

	/* Control Configurations */
	ControlConfig.AxisCC[ROLL].angleLPF = 6;
	ControlConfig.AxisCC[PITCH].angleLPF = 6;
	ControlConfig.AxisCC[YAW].angleLPF = 7;

	ControlConfig.AxisCC[ROLL].angleLPF = 6;
	ControlConfig.AxisCC[PITCH].speedLPF = 6;
	ControlConfig.AxisCC[YAW].speedLPF = 7;
	ControlConfig.flags = RTCCF_CONTROL_CONFIG_FLAG_NO_CONFIRM;

	Control.controlMode[ROLL] = CtrlM_MODE_ANGLE | CtrlF_CONTROL_FLAG_TARGET_PRECISE;
	Control.controlMode[PITCH] = CtrlM_MODE_ANGLE | CtrlF_CONTROL_FLAG_TARGET_PRECISE;
	Control.controlMode[YAW] = CtrlM_MODE_ANGLE | CtrlF_CONTROL_FLAG_TARGET_PRECISE;

	Control.AxisC[ROLL].angle = 0;
	Control.AxisC[PITCH].angle = 0;
	Control.AxisC[YAW].angle = 0;

	Control.AxisC[PITCH].speed = SPEED_TO_VALUE(50);
	Control.AxisC[YAW].speed = SPEED_TO_VALUE(50);

	/* Data Stream Configurations */
	DataStreamInterval.cmdID = CMD_REALTIME_DATA_CUSTOM;
	DataStreamInterval.intervalMs = 1000;
	DataStreamInterval.syncToData = STD_SYNC_OFF;

	/* For more information see the SBGC32_RequestRealTimeDataCustom function.
	   Total packets length = 20 bytes:
	   ui16 timestampMs						 i16 [3]				i16 [3]			i16 [3] */
	ui32 DataStreamIntervalConfig = RTDCF_STATOR_ROTOR_ANGLE | RTDCF_GYRO_DATA | RTDCF_ACC_DATA;
	memcpy(DataStreamInterval.config, &DataStreamIntervalConfig, sizeof(DataStreamIntervalConfig));


	/* Adj Vars Setting */
	/* Note: If your microprocessor has little size of RAM,
			 initialize these variables manually,
			 without AdjVarsDebugInfoArray [] */
	InitAdjVar(&AdjVarsGeneral[0], &AdjVarsDebugInfoArray[ADJ_VAL_ACC_LIMITER_ROLL]);
	InitAdjVar(&AdjVarsGeneral[1], &AdjVarsDebugInfoArray[ADJ_VAL_ACC_LIMITER_PITCH]);
	InitAdjVar(&AdjVarsGeneral[2], &AdjVarsDebugInfoArray[ADJ_VAL_ACC_LIMITER_YAW]);


	/* - - - - - - - - - - - - Program Launch - - - - - - - - - - - - */

	/* SBGC32_Reset(&SBGC_1, RF_RESET_WITH_RESTORING_STATES, 500);
	SBGC32_CheckConfirmation(&SBGC_1, &Confirm, CMD_RESET);
	delay(5000); */

	PrintBoardParameters(P_CURRENT_PROFILE);

	SBGC32_ControlConfig(&SBGC_1, &ControlConfig, &Confirm);
	SBGC32_DemoControl();

	SBGC32_RequestDataStream(&SBGC_1, &DataStreamInterval, &Confirm);

	/*  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  	/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
		/*                     Start Worker Cycle                     */
		/* __________________________________________________________ */

		SBGC32_ParseDataStream(&SBGC_1, DataStreamBuff, (SBGC_Commands_t)DataStreamInterval.cmdID);
		PrintDataStream(DataStreamBuff);

		HAL_Delay(20);

		/*  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */
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

TxRxStatus_t PrintBoardParameters (Profile_t slot)
{
    SBGC32_ReadBoardInfo(&SBGC_1, &BoardInfo, 0);
    SBGC32_ReadBoardInfo3(&SBGC_1, &BoardInfo3);

    SBGC32_ReadParams3(&SBGC_1, &MainParams3, slot);
    SBGC32_ReadParamsExt(&SBGC_1, &MainParamsExt, slot);
    SBGC32_ReadParamsExt2(&SBGC_1, &MainParamsExt2, slot);
    SBGC32_ReadParamsExt3(&SBGC_1, &MainParamsExt3, slot);

    SBGC32_ReadRealTimeData4(&SBGC_1, &RealTimeData);

    char boardVersionStr [4];
    char firmwareVersionStr [7];

    FormatBoardVersion(BoardInfo.boardVer, boardVersionStr);
    FormatFirmwareVersion(BoardInfo.firmwareVer, firmwareVersionStr);

    PrintMessage(&SBGC_1, TEXT_SIZE_((char*)"Board Version: "));
    PrintMessage(&SBGC_1, TEXT_SIZE_(boardVersionStr));
    PrintMessage(&SBGC_1, TEXT_SIZE_((char*)" \n"));
    PrintMessage(&SBGC_1, TEXT_SIZE_((char*)"Firmware Version: "));
    PrintMessage(&SBGC_1, TEXT_SIZE_(firmwareVersionStr));
    PrintMessage(&SBGC_1, TEXT_SIZE_((char*)" \n"));

    PrintStructElement(&SBGC_1, &BoardInfo3.flashSize, "Flash Size =", _UNSIGNED_CHAR_);

    PrintStructElement(&SBGC_1, &MainParams3.profileID, "Current profile #", _UNSIGNED_CHAR_);  // Note: -1
    PrintStructElement(&SBGC_1, &MainParams3.AxisCMP3[ROLL].p, "Roll P =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC_1, &MainParams3.AxisCMP3[ROLL].i, "Roll I =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC_1, &MainParams3.AxisCMP3[ROLL].d, "Roll D =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC_1, &MainParams3.AxisCMP3[PITCH].p, "Pitch P =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC_1, &MainParams3.AxisCMP3[PITCH].i, "Pitch I =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC_1, &MainParams3.AxisCMP3[PITCH].d, "Pitch D =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC_1, &MainParams3.AxisCMP3[YAW].p, "Yaw P =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC_1, &MainParams3.AxisCMP3[YAW].i, "Yaw I =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC_1, &MainParams3.AxisCMP3[YAW].d, "Yaw D =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC_1, &MainParams3.ACC_LimiterAll, "ACC Limiter all = ", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC_1, &MainParams3.AxisRC_MP3[ROLL].RC_MaxAngle, "RC Max Angle =", _SIGNED_SHORT_);
    PrintStructElement(&SBGC_1, &MainParams3.AxisRC_MP3[YAW].RC_MinAngle, "RC Min Angle =", _SIGNED_SHORT_);
    PrintStructElement(&SBGC_1, &MainParams3.RC_MapROLL, "RC Map Roll =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC_1, &MainParams3.RC_MapPITCH, "RC Map Pitch =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC_1, &MainParams3.RC_MapYAW, "RC Map Yaw =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC_1, &MainParams3.RC_MapCmd, "RC Map Cmd =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC_1, &MainParams3.RC_MapFC_ROLL, "RC Map FC Roll =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC_1, &MainParams3.RC_MapFC_PITCH, "RC Map FC Pitch =", _UNSIGNED_CHAR_);

    PrintStructElement(&SBGC_1, &MainParamsExt.LPF_Freq[ROLL], "LPF Frequency Roll =", _UNSIGNED_SHORT_);
    PrintStructElement(&SBGC_1, &MainParamsExt.LPF_Freq[PITCH], "LPF Frequency Pitch =", _UNSIGNED_SHORT_);
    PrintStructElement(&SBGC_1, &MainParamsExt.LPF_Freq[YAW], "LPF Frequency Yaw =", _UNSIGNED_SHORT_);

    PrintStructElement(&SBGC_1, &MainParamsExt2.frameIMU_LPF_Freq, "Frame IMU LPF Freq =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC_1, &MainParamsExt2.timelapseTime, "Timelapse Time =", _UNSIGNED_SHORT_);

    PrintStructElement(&SBGC_1, &MainParamsExt3.motorStartupDelay, "Motor Startup Delay =", _UNSIGNED_SHORT_);

    PrintMessage(&SBGC_1, TEXT_SIZE_((char*)" \n"));

	PrintStructElement(&SBGC_1, &RealTimeData.AxisRTD[ROLL].ACC_Data, "ACC Roll =", _SIGNED_SHORT_);
	PrintStructElement(&SBGC_1, &RealTimeData.AxisRTD[PITCH].ACC_Data, "ACC Pitch =", _SIGNED_SHORT_);
	PrintStructElement(&SBGC_1, &RealTimeData.AxisRTD[YAW].ACC_Data, "ACC Yaw =", _SIGNED_SHORT_);

    PrintStructElement(&SBGC_1, &RealTimeData.frameCamAngle[ROLL], "Roll Current Angle =", _SIGNED_SHORT_);
    PrintStructElement(&SBGC_1, &RealTimeData.frameCamAngle[PITCH], "Pitch Current Angle =", _SIGNED_SHORT_);
    PrintStructElement(&SBGC_1, &RealTimeData.frameCamAngle[YAW], "Yaw Current Angle =", _SIGNED_SHORT_);

    PrintStructElement(&SBGC_1, &RealTimeData.IMU_Temperature, "IMU Temperature =", _SIGNED_CHAR_);

    return SBGC_1._ParserCurrentStatus;
}


TxRxStatus_t SBGC32_DemoControl (void)
{
	/* Getting adjvars values */
	/* Note: AdjVarsGeneral.ID fields are already filled */
	SBGC32_GetAdjVarValues(&SBGC_1, AdjVarsGeneral, countof(AdjVarsGeneral));

	/* Run the Demonstration Cycle */
	FOR_(i, 4)
	{
		/* Printing */
		FOR_(k, countof(AdjVarsGeneral))
			PrintStructElement(&SBGC_1, &AdjVarsGeneral[k].value, AdjVarsGeneral[k].name, AdjVarsGeneral[k].varType);

		Control.AxisC[YAW].angle = DEGREE_TO_ANGLE_INT(50);
		Control.AxisC[PITCH].angle = DEGREE_TO_ANGLE_INT(-20);
		SBGC32_Control(&SBGC_1, &Control);
		HAL_Delay(5000);

		Control.AxisC[PITCH].angle = DEGREE_TO_ANGLE_INT(20);
		SBGC32_Control(&SBGC_1, &Control);
		HAL_Delay(5000);

		Control.AxisC[YAW].angle = DEGREE_TO_ANGLE_INT(-50);
		SBGC32_Control(&SBGC_1, &Control);
		HAL_Delay(5000);

		Control.AxisC[PITCH].angle = DEGREE_TO_ANGLE_INT(-20);
		SBGC32_Control(&SBGC_1, &Control);
		HAL_Delay(5000);

		Control.AxisC[YAW].angle = DEGREE_TO_ANGLE_INT(0);
		Control.AxisC[PITCH].angle = DEGREE_TO_ANGLE_INT(0);
		SBGC32_Control(&SBGC_1, &Control);
		HAL_Delay(5000);

		BeeperSettings.mode = BM_BEEPER_MODE_COMPLETE;
		SBGC32_PlayBeeper(&SBGC_1, &BeeperSettings);

		/* Adjustable Variables Re-Setting */
		FOR_(k, countof(AdjVarsGeneral))
			/* Toggle Min : Max adjvars contrast */
			EditAdjVarValue(&AdjVarsGeneral[k], ((i % 2 == 0) ? AdjVarsGeneral[k].maxValue : AdjVarsGeneral[k].minValue));

		SBGC32_SetAdjVarValues(&SBGC_1, AdjVarsGeneral, countof(AdjVarsGeneral), &Confirm);
	}

	/* Saving all changed adjustable variables to EEPROM */
//	SBGC32_SaveAllActiveAdjVarsToEEPROM(&SBGC_1, &Confirm);
//
//	if (Confirm.cmdID == CMD_SAVE_PARAMS_3)
//		FOR_(i, countof(AdjVarsGeneral))
//			if (AdjVarsGeneral[i].saveFlag != SAVED)
//				AdjVarsGeneral[i].saveFlag = SAVED;

	/* or SBGC32_SaveAdjVarsToEEPROM(&SBGC_1, AdjVarsGeneral, countof(AdjVarsGeneral), &Confirm); */

    return SBGC_1._ParserCurrentStatus;
}


void PrintDataStream (ui8 *pBuff)
{
	/* Preparing */
	ui8 BuffRPx = 2;  // ui16 timestampMs offset

	BuffRPx += ConvertWithPM(RealTimeDataCustom.frameCamAngle, &pBuff[BuffRPx],
							sizeof(RealTimeDataCustom.targetAngles), PM_DEFAULT_16BIT);
	BuffRPx += ConvertWithPM(RealTimeDataCustom.gyroData, &pBuff[BuffRPx],
							sizeof(RealTimeDataCustom.gyroData), PM_DEFAULT_16BIT);
	BuffRPx += ConvertWithPM(RealTimeDataCustom.ACC_Data, &pBuff[BuffRPx],
							sizeof(RealTimeDataCustom.ACC_Data), PM_DEFAULT_16BIT);

	/* Printing */
	PrintStructElement(&SBGC_1, &RealTimeDataCustom.frameCamAngle[ROLL], "Frame Camera Angle Roll =", _SIGNED_SHORT_);
	PrintStructElement(&SBGC_1, &RealTimeDataCustom.frameCamAngle[PITCH], "Frame Camera Angle Pitch =", _SIGNED_SHORT_);
	PrintStructElement(&SBGC_1, &RealTimeDataCustom.frameCamAngle[YAW], "Frame Camera Angle Yaw =", _SIGNED_SHORT_);

	PrintStructElement(&SBGC_1, &RealTimeDataCustom.gyroData[ROLL], "Gyro Roll =", _SIGNED_SHORT_);
	PrintStructElement(&SBGC_1, &RealTimeDataCustom.gyroData[PITCH], "Gyro Pitch =", _SIGNED_SHORT_);
	PrintStructElement(&SBGC_1, &RealTimeDataCustom.gyroData[YAW], "Gyro Yaw =", _SIGNED_SHORT_);

	PrintStructElement(&SBGC_1, &RealTimeDataCustom.ACC_Data[ROLL], "ACC Roll =", _SIGNED_SHORT_);
	PrintStructElement(&SBGC_1, &RealTimeDataCustom.ACC_Data[PITCH], "ACC Pitch =", _SIGNED_SHORT_);
	PrintStructElement(&SBGC_1, &RealTimeDataCustom.ACC_Data[YAW], "ACC Yaw =", _SIGNED_SHORT_);

	PrintMessage(&SBGC_1, TEXT_SIZE_((char*)"__________________________\n\n"));
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

