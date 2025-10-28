/*	____________________________________________________________________
 *
 *	This is an example sketch for Arduino, that shows how to control
 *	SimpleBGC-driven gimbal via Serial API. API specs are available at
 *	http://www.basecamelectronics.com/serialapi/
 *	____________________________________________________________________
 */

#include "sbgc32.h"


#define		SBGC_CONTROL_AXES_LPF			2

#define		SBGC_DATA_STREAM_BUFF_DEPTH		1
#define		SBGC_DEMO_CONTROL_ITERATIONS	4
#define		SBGC_DATA_STREAM_INTERVAL		1000


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*                       Global Software Objects                      */
/* __________________________________________________________________ */

			sbgcGeneral_t 			SBGC32_Device;

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

/*  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */

void setup()
{
	/* Pull-up Serial 1 Rx pin */
	pinMode(19, INPUT_PULLUP);

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
}


void loop()
{
	/* Wait until get a full command */
	while (SerialAPI_GetBytesAvailable(&SBGC32_Device) < ((sizeof(RealTimeDataCustom) + SBGC_SERVICE_BYTES_NUM) * SBGC_DATA_STREAM_BUFF_DEPTH));

	SBGC32_ReadDataStream(&SBGC32_Device, DSC_CMD_REALTIME_DATA_CUSTOM, &RealTimeDataCustom, sizeof(RealTimeDataCustom));
	PrintDataStream();
}


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
	/* Run the Demonstration Cycle */
	for (ui8 i = 0; i < SBGC_DEMO_CONTROL_ITERATIONS; i++)
	{
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

		DebugSBGC32_PrintMessage(&SBGC32_Device, "____________________________\n\n");

		sbgcDelay(500);
	}

	DebugSBGC32_PrintMessage(&SBGC32_Device, "____________________________\n\n");

	Control.mode[PITCH] = CtrlMODE_NO_CONTROL;
	Control.mode[YAW] = CtrlMODE_NO_CONTROL;
	SBGC32_Control(&SBGC32_Device, &Control);

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
