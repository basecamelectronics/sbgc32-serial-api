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

#include "sbgc32.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define		SBGC_CONTROL_AXES_LPF			2

#define		SBGC_ADJ_VAR_INCREASING_STEP	200

#define		SBGC_DATA_STREAM_BUFF_DEPTH		1
#define		SBGC_DEMO_CONTROL_ITERATIONS	4
#define		SBGC_DATA_STREAM_INTERVAL		1000

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

			sbgcGeneral_t 			SBGC32_Device;

static		sbgcAdjVarGeneral_t		AdjVarGeneral [3];

static		sbgcControl_t			Control;
static		sbgcControlConfig_t		ControlConfig;

static		sbgcMainParams3_t		MainParams3;
static		sbgcMainParamsExt_t		MainParamsExt;
static		sbgcMainParamsExt2_t	MainParamsExt2;
static		sbgcMainParamsExt3_t	MainParamsExt3;

static		sbgcRealTimeData_t		RealTimeData;
static		sbgcDataStreamInterval_t
									DataStreamInterval;

static		sbgcBoardInfo_t			BoardInfo;
static		sbgcBoardInfo3_t		BoardInfo3;
static		sbgcBeeperSettings_t	BeeperSettings;

static		sbgcConfirm_t			Confirm;


struct PACKED__ RealTimeDataCustomStruct
{
	// Mandatory field, don't remove!
	ui16 timestampMs;

	// Additional fields, depended on 'flags'
	i16 frameCamAngle [3];
	i16 gyroData [3];
	i16 accData [3];

}	static RealTimeDataCustom;


/* Function prototypes */
sbgcCommandStatus_t PrintBoardParameters (sbgcProfile_t profileID);
sbgcCommandStatus_t DemoControl (void);
void PrintDataStream (void);

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

	/* Control Configurations */
	ControlConfig.AxisCCtrl[PITCH].angleLPF = SBGC_CONTROL_AXES_LPF;
	ControlConfig.AxisCCtrl[YAW].angleLPF = SBGC_CONTROL_AXES_LPF;

	ControlConfig.AxisCCtrl[PITCH].speedLPF = SBGC_CONTROL_AXES_LPF;
	ControlConfig.AxisCCtrl[YAW].speedLPF = SBGC_CONTROL_AXES_LPF;

	ControlConfig.flags = CtrlCONFIG_FLAG_NO_CONFIRM;

	Control.mode[PITCH] = CtrlMODE_ANGLE | CtrlFLAG_TARGET_PRECISE;
	Control.mode[YAW] = CtrlMODE_ANGLE | CtrlFLAG_TARGET_PRECISE;

	Control.AxisC[PITCH].angle = 0;
	Control.AxisC[YAW].angle = 0;

	Control.AxisC[PITCH].speed = sbgcSpeedToValue(25);
	Control.AxisC[YAW].speed = sbgcSpeedToValue(50);

	/* Data Stream Configurations */
	DataStreamInterval.cmdID = DSC_CMD_REALTIME_DATA_CUSTOM;
	DataStreamInterval.intervalMs = SBGC_DATA_STREAM_INTERVAL;
	DataStreamInterval.syncToData = STD_SYNC_OFF;

	ParserSBGC32_RTDC_FlagsToStream(&DataStreamInterval, RTDCF_STATOR_ROTOR_ANGLE | RTDCF_GYRO_DATA | RTDCF_ACC_DATA);

	/* Adj Vars Setting. SBGC_ADJ_VARS_REF_INFO parameter must be sbgcON  */
	SerialAPI_InitAdjVar(&AdjVarGeneral[0], ADJ_VAR_ACC_LIMITER_ROLL);
	SerialAPI_InitAdjVar(&AdjVarGeneral[1], ADJ_VAR_ACC_LIMITER_PITCH);
	SerialAPI_InitAdjVar(&AdjVarGeneral[2], ADJ_VAR_ACC_LIMITER_YAW);

	/* Program launch */
	/* SBGC32_Reset(&SBGC32_Device, RESET_FLAG_NEED_CONFIRMATION, 0);
	SBGC32_ExpectCommand(&SBGC32_Device, CMD_RESET);
	sbgcDelay(5000); */

	PrintBoardParameters(sbgcCURRENT_PROFILE);

	SBGC32_ControlConfig(&SBGC32_Device, &ControlConfig, SBGC_NO_CONFIRM);

	DemoControl();

	SBGC32_StartDataStream(&SBGC32_Device, &DataStreamInterval, &Confirm);

	if (SerialAPI_GetConfirmStatus(&Confirm) != sbgcCONFIRM_RECEIVED)
	{
		DebugSBGC32_PrintMessage(&SBGC32_Device, "Confirmation Error! Program is stopped");

		/* There is no point in proceeding without starting the data stream */
		while (1);  // Stop the program here
	}

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

		/* Wait until get a full command */
		while (SerialAPI_GetBytesAvailable(&SBGC32_Device) < ((sizeof(RealTimeDataCustom) + SBGC_SERVICE_BYTES_NUM) * SBGC_DATA_STREAM_BUFF_DEPTH));

		SBGC32_ReadDataStream(&SBGC32_Device, DSC_CMD_REALTIME_DATA_CUSTOM, &RealTimeDataCustom, sizeof(RealTimeDataCustom));
		PrintDataStream();
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

sbgcCommandStatus_t PrintBoardParameters (sbgcProfile_t profileID)
{
	char boardVersionStr [5];
	char firmwareVersionStr [8];

	SBGC32_ReadBoardInfo(&SBGC32_Device, &BoardInfo, 0);
	SBGC32_ReadBoardInfo3(&SBGC32_Device, &BoardInfo3);

	SBGC32_ReadParams3(&SBGC32_Device, &MainParams3, profileID);
	SBGC32_ReadParamsExt(&SBGC32_Device, &MainParamsExt, profileID);
	SBGC32_ReadParamsExt2(&SBGC32_Device, &MainParamsExt2, profileID);
	SBGC32_ReadParamsExt3(&SBGC32_Device, &MainParamsExt3, profileID);

	SBGC32_ReadRealTimeData4(&SBGC32_Device, &RealTimeData);

	ParserSBGC32_FormatBoardVersion(&SBGC32_Device, BoardInfo.boardVer, BUFF_SIZE_(boardVersionStr));
	ParserSBGC32_FormatFirmwareVersion(&SBGC32_Device, BoardInfo.firmwareVer, BUFF_SIZE_(firmwareVersionStr));

	DebugSBGC32_PrintMessage(&SBGC32_Device, "Board Version: ");
	DebugSBGC32_PrintMessage(&SBGC32_Device, boardVersionStr);
	DebugSBGC32_PrintMessage(&SBGC32_Device, " \n");
	DebugSBGC32_PrintMessage(&SBGC32_Device, "Firmware Version: ");
	DebugSBGC32_PrintMessage(&SBGC32_Device, firmwareVersionStr);
	DebugSBGC32_PrintMessage(&SBGC32_Device, " \n");

	DebugSBGC32_PrintStructElement(&SBGC32_Device, &BoardInfo3.flashSize, "Flash Size =", sbgcUCHAR);

	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParams3.profileID, "Current profile #", sbgcUCHAR);  // Note: 0 --> 4
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParams3.AxisCMP3[ROLL].p, "Roll P =", sbgcUCHAR);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParams3.AxisCMP3[ROLL].i, "Roll I =", sbgcUCHAR);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParams3.AxisCMP3[ROLL].d, "Roll D =", sbgcUCHAR);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParams3.AxisCMP3[PITCH].p, "Pitch P =", sbgcUCHAR);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParams3.AxisCMP3[PITCH].i, "Pitch I =", sbgcUCHAR);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParams3.AxisCMP3[PITCH].d, "Pitch D =", sbgcUCHAR);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParams3.AxisCMP3[YAW].p, "Yaw P =", sbgcUCHAR);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParams3.AxisCMP3[YAW].i, "Yaw I =", sbgcUCHAR);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParams3.AxisCMP3[YAW].d, "Yaw D =", sbgcUCHAR);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParams3.accLimiterAll, "Acc Limiter All = ", sbgcUCHAR);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParams3.AxisRC_MP3[ROLL].RC_MaxAngle, "RC Max Angle =", sbgcSHORT);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParams3.AxisRC_MP3[YAW].RC_MinAngle, "RC Min Angle =", sbgcSHORT);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParams3.RC_MapRoll, "RC Map Roll =", sbgcUCHAR);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParams3.RC_MapPitch, "RC Map Pitch =", sbgcUCHAR);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParams3.RC_MapYaw, "RC Map Yaw =", sbgcUCHAR);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParams3.RC_MapCmd, "RC Map Cmd =", sbgcUCHAR);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParams3.RC_MapFC_Roll, "RC Map FC Roll =", sbgcUCHAR);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParams3.RC_MapFC_Pitch, "RC Map FC Pitch =", sbgcUCHAR);

	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParamsExt.LPF_Freq[ROLL], "LPF Frequency Roll =", sbgcUSHORT);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParamsExt.LPF_Freq[PITCH], "LPF Frequency Pitch =", sbgcUSHORT);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParamsExt.LPF_Freq[YAW], "LPF Frequency Yaw =", sbgcUSHORT);

	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParamsExt2.frameIMU_LPF_Freq, "Frame IMU LPF Freq =", sbgcUCHAR);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParamsExt2.timelapseTime, "Timelapse Time =", sbgcUSHORT);

	DebugSBGC32_PrintStructElement(&SBGC32_Device, &MainParamsExt3.motorStartupDelay, "Motor Startup Delay =", sbgcUSHORT);

	DebugSBGC32_PrintMessage(&SBGC32_Device, " \n");

	DebugSBGC32_PrintStructElement(&SBGC32_Device, &RealTimeData.AxisRTD[ROLL].accData, "Acc Roll =", sbgcSHORT);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &RealTimeData.AxisRTD[PITCH].accData, "Acc Pitch =", sbgcSHORT);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &RealTimeData.AxisRTD[YAW].accData, "Acc Yaw =", sbgcSHORT);

	RealTimeData.frameCamAngle[ROLL] = sbgcDegreeToAngle(RealTimeData.frameCamAngle[ROLL]);
	RealTimeData.frameCamAngle[PITCH] = sbgcDegreeToAngle(RealTimeData.frameCamAngle[PITCH]);
	RealTimeData.frameCamAngle[YAW] = sbgcDegreeToAngle(RealTimeData.frameCamAngle[YAW]);

	DebugSBGC32_PrintStructElement(&SBGC32_Device, &RealTimeData.frameCamAngle[ROLL], "Current Angle Roll =", sbgcSHORT);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &RealTimeData.frameCamAngle[PITCH], "Current Angle Pitch =", sbgcSHORT);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &RealTimeData.frameCamAngle[YAW], "Current Angle Yaw =", sbgcSHORT);

	DebugSBGC32_PrintStructElement(&SBGC32_Device, &RealTimeData.IMU_Temperature, "IMU Temperature =", sbgcCHAR);

	DebugSBGC32_PrintMessage(&SBGC32_Device, "____________________________\n\n");

	return SerialAPI_GetStatus(&SBGC32_Device);
}


sbgcCommandStatus_t DemoControl (void)
{
	/* Getting adjvars values */
	SBGC32_GetAdjVarValues(&SBGC32_Device, AdjVarGeneral, countof_(AdjVarGeneral));

	for (ui8 i = 0; i < countof_(AdjVarGeneral); i++)
	/* Start with 0 values */
		SerialAPI_EditAdjVarValue(&AdjVarGeneral[i], 0);

	sbgcDelay(500);

	/* Run the Demonstration Cycle */
	for (ui8 i = 0; i < SBGC_DEMO_CONTROL_ITERATIONS; i++)
	{
		/* Printing. SBGC_ADJ_VARS_NAMES parameter must be sbgcON */
		for (ui8 k = 0; k < countof_(AdjVarGeneral); k++)
			DebugSBGC32_PrintStructElement(&SBGC32_Device, &AdjVarGeneral[k].value, AdjVarGeneral[k].name, sbgcSHORT);

		Control.AxisC[YAW].angle = sbgcAngleToDegree(50);
		Control.AxisC[PITCH].angle = sbgcAngleToDegree(-25);
		SBGC32_Control(&SBGC32_Device, &Control);
		sbgcDelay(5000);

		Control.AxisC[PITCH].angle = sbgcAngleToDegree(25);
		SBGC32_Control(&SBGC32_Device, &Control);
		sbgcDelay(5000);

		Control.AxisC[YAW].angle = sbgcAngleToDegree(-50);
		SBGC32_Control(&SBGC32_Device, &Control);
		sbgcDelay(5000);

		Control.AxisC[PITCH].angle = sbgcAngleToDegree(-25);
		SBGC32_Control(&SBGC32_Device, &Control);
		sbgcDelay(5000);

		Control.AxisC[YAW].angle = 0;
		Control.AxisC[PITCH].angle = 0;
		SBGC32_Control(&SBGC32_Device, &Control);
		sbgcDelay(5000);

		BeeperSettings.mode = BEEP_MODE_COMPLETE;
		SBGC32_PlayBeeper(&SBGC32_Device, &BeeperSettings);

		/* Adjustable variables re-setting */
		for (ui8 k = 0; k < countof_(AdjVarGeneral); k++)
			SerialAPI_EditAdjVarValue(&AdjVarGeneral[k], AdjVarGeneral[k].value + SBGC_ADJ_VAR_INCREASING_STEP);

		SBGC32_SetAdjVarValues(&SBGC32_Device, AdjVarGeneral, countof_(AdjVarGeneral), &Confirm);

		DebugSBGC32_PrintMessage(&SBGC32_Device, "____________________________\n\n");

		sbgcDelay(500);
	}

	for (ui8 i = 0; i < countof_(AdjVarGeneral); i++)
		DebugSBGC32_PrintStructElement(&SBGC32_Device, &AdjVarGeneral[i].value, AdjVarGeneral[i].name, sbgcSHORT);

	DebugSBGC32_PrintMessage(&SBGC32_Device, "____________________________\n\n");

	Control.mode[PITCH] = CtrlMODE_NO_CONTROL;
	Control.mode[YAW] = CtrlMODE_NO_CONTROL;
	SBGC32_Control(&SBGC32_Device, &Control);

	/* Saving all changed adjustable variables to EEPROM */
	/* SBGC32_SaveAllActiveAdjVarsToEEPROM(&SBGC32_Device, &Confirm);

	if (SerialAPI_GetConfirmStatus(&Confirm) == sbgcCONFIRM_RECEIVED)
		for (ui8 i = 0; i < countof_(AdjVarGeneral); i++)
			AdjVarGeneral[i].saveFlag = AV_SAVED; */

	/* or SBGC32_SaveAdjVarsToEEPROM(&SBGC32_Device, AdjVarGeneral, countof_(AdjVarGeneral), SBGC_NO_CONFIRM); */

	return SerialAPI_GetStatus(&SBGC32_Device);
}


void PrintDataStream (void)
{
	i16 frameCamAngleTemp;

	frameCamAngleTemp = sbgcDegreeToAngle(RealTimeDataCustom.frameCamAngle[ROLL]);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &frameCamAngleTemp, "Current Angle Roll =", sbgcSHORT);

	frameCamAngleTemp = sbgcDegreeToAngle(RealTimeDataCustom.frameCamAngle[PITCH]);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &frameCamAngleTemp, "Current Angle Pitch =", sbgcSHORT);

	frameCamAngleTemp = sbgcDegreeToAngle(RealTimeDataCustom.frameCamAngle[YAW]);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &frameCamAngleTemp, "Current Angle Yaw =", sbgcSHORT);

	DebugSBGC32_PrintStructElement(&SBGC32_Device, &RealTimeDataCustom.gyroData[ROLL], "Gyro Roll =", sbgcSHORT);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &RealTimeDataCustom.gyroData[PITCH], "Gyro Pitch =", sbgcSHORT);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &RealTimeDataCustom.gyroData[YAW], "Gyro Yaw =", sbgcSHORT);

	DebugSBGC32_PrintStructElement(&SBGC32_Device, &RealTimeDataCustom.accData[ROLL], "Acc Roll =", sbgcSHORT);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &RealTimeDataCustom.accData[PITCH], "Acc Pitch =", sbgcSHORT);
	DebugSBGC32_PrintStructElement(&SBGC32_Device, &RealTimeDataCustom.accData[YAW], "Acc Yaw =", sbgcSHORT);

	DebugSBGC32_PrintMessage(&SBGC32_Device, "____________________________\n\n");
}


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
