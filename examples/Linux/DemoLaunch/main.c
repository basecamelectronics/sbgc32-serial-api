/*	____________________________________________________________________
 *
 *	This is an example sketch for Linux OS, that shows how to control
 *	SimpleBGC-driven gimbal via Serial API. API specs are available at
 *	http://www.basecamelectronics.com/serialapi/
 *	____________________________________________________________________
 */

#include "sbgc32.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*   					Global Software Objects  					  */
/* __________________________________________________________________ */

            GeneralSBGC_t 			SBGC32_Device;

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

static		AdjVarGeneral_t			AdjVarGeneral [3];

static		DataStreamInterval_t	DataStreamInterval;

static		BeeperSettings_t		BeeperSettings;


static		ui8	DataStreamBuff [20];


TxRxStatus_t PrintBoardParameters (Profile_t slot);
TxRxStatus_t SBGC32_DemoControl (void);
void PrintDataStream (ui8 *pBuff);

/*  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */

int main ()
{
    /* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
    /*                         Initialization                         */
    /* ______________________________________________________________ */

    /*  - - - - - - - - - - Software Initialization - - - - - - - - - */

    /* SimpleBGC32 Init */
    SBGC32_Init(&SBGC32_Device);

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

    /* Adj Vars Setting. SBGC_ADJ_VARS_REF_INFO parameter must be SET_ON  */
    InitAdjVar(&AdjVarGeneral[0], ADJ_VAL_ACC_LIMITER_ROLL);
    InitAdjVar(&AdjVarGeneral[1], ADJ_VAL_ACC_LIMITER_PITCH);
    InitAdjVar(&AdjVarGeneral[2], ADJ_VAL_ACC_LIMITER_YAW);


    /* - - - - - - - - - - - - Program Launch - - - - - - - - - - - - */

    /* SBGC32_Reset(&SBGC32_Device, RF_RESTART_CONFIRMATION, 5000);
    SBGC32_CheckConfirmation(&SBGC32_Device, CMD_RESET);
    DELAY_MS_(5000); */

    PrintBoardParameters(P_CURRENT_PROFILE);

    SBGC32_ControlConfig(&SBGC32_Device, &ControlConfig);
    SBGC32_DemoControl();

    SBGC32_RequestDataStream(&SBGC32_Device, &DataStreamInterval);

    /*  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */

    while (1)
    {
        /* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
        /* 						  Start Worker Cycle					  */
        /* ______________________________________________________________ */

        SBGC32_ParseDataStream(&SBGC32_Device, DataStreamBuff, (SBGC_Command_t)DataStreamInterval.cmdID);
        PrintDataStream(DataStreamBuff);

        DELAY_MS_(DataStreamInterval.intervalMs - 1);

        /*  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */
    }

    return 0;
}


TxRxStatus_t PrintBoardParameters (Profile_t slot)
{
    SBGC32_ReadBoardInfo(&SBGC32_Device, &BoardInfo, 0);
    SBGC32_ReadBoardInfo3(&SBGC32_Device, &BoardInfo3);

    SBGC32_ReadParams3(&SBGC32_Device, &MainParams3, slot);
    SBGC32_ReadParamsExt(&SBGC32_Device, &MainParamsExt, slot);
    SBGC32_ReadParamsExt2(&SBGC32_Device, &MainParamsExt2, slot);
    SBGC32_ReadParamsExt3(&SBGC32_Device, &MainParamsExt3, slot);

    SBGC32_ReadRealTimeData4(&SBGC32_Device, &RealTimeData);

    char boardVersionStr [4];
    char firmwareVersionStr [7];

    FormatBoardVersion(&SBGC32_Device, BoardInfo.boardVer, boardVersionStr);
    FormatFirmwareVersion(&SBGC32_Device, BoardInfo.firmwareVer, firmwareVersionStr);

    PrintMessage(&SBGC32_Device, TEXT_SIZE_((char*)"Board Version: "));
    PrintMessage(&SBGC32_Device, TEXT_SIZE_(boardVersionStr));
    PrintMessage(&SBGC32_Device, TEXT_SIZE_((char*)" \n"));
    PrintMessage(&SBGC32_Device, TEXT_SIZE_((char*)"Firmware Version: "));
    PrintMessage(&SBGC32_Device, TEXT_SIZE_(firmwareVersionStr));
    PrintMessage(&SBGC32_Device, TEXT_SIZE_((char*)" \n"));

    PrintStructElement(&SBGC32_Device, &BoardInfo3.flashSize, "Flash Size =", _UNSIGNED_CHAR_);

    PrintStructElement(&SBGC32_Device, &MainParams3.profileID + 1, "Current profile #", _UNSIGNED_CHAR_);  // Note: 1 --> 5
    PrintStructElement(&SBGC32_Device, &MainParams3.AxisCMP3[ROLL].p, "Roll P =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC32_Device, &MainParams3.AxisCMP3[ROLL].i, "Roll I =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC32_Device, &MainParams3.AxisCMP3[ROLL].d, "Roll D =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC32_Device, &MainParams3.AxisCMP3[PITCH].p, "Pitch P =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC32_Device, &MainParams3.AxisCMP3[PITCH].i, "Pitch I =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC32_Device, &MainParams3.AxisCMP3[PITCH].d, "Pitch D =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC32_Device, &MainParams3.AxisCMP3[YAW].p, "Yaw P =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC32_Device, &MainParams3.AxisCMP3[YAW].i, "Yaw I =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC32_Device, &MainParams3.AxisCMP3[YAW].d, "Yaw D =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC32_Device, &MainParams3.AccLimiterAll, "Acc Limiter All = ", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC32_Device, &MainParams3.AxisRC_MP3[ROLL].RC_MaxAngle, "RC Max Angle =", _SIGNED_SHORT_);
    PrintStructElement(&SBGC32_Device, &MainParams3.AxisRC_MP3[YAW].RC_MinAngle, "RC Min Angle =", _SIGNED_SHORT_);
    PrintStructElement(&SBGC32_Device, &MainParams3.RC_MapROLL, "RC Map Roll =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC32_Device, &MainParams3.RC_MapPITCH, "RC Map Pitch =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC32_Device, &MainParams3.RC_MapYAW, "RC Map Yaw =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC32_Device, &MainParams3.RC_MapCmd, "RC Map Cmd =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC32_Device, &MainParams3.RC_MapFC_ROLL, "RC Map FC Roll =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC32_Device, &MainParams3.RC_MapFC_PITCH, "RC Map FC Pitch =", _UNSIGNED_CHAR_);

    PrintStructElement(&SBGC32_Device, &MainParamsExt.LPF_Freq[ROLL], "LPF Frequency Roll =", _UNSIGNED_SHORT_);
    PrintStructElement(&SBGC32_Device, &MainParamsExt.LPF_Freq[PITCH], "LPF Frequency Pitch =", _UNSIGNED_SHORT_);
    PrintStructElement(&SBGC32_Device, &MainParamsExt.LPF_Freq[YAW], "LPF Frequency Yaw =", _UNSIGNED_SHORT_);

    PrintStructElement(&SBGC32_Device, &MainParamsExt2.frameIMU_LPF_Freq, "Frame IMU LPF Freq =", _UNSIGNED_CHAR_);
    PrintStructElement(&SBGC32_Device, &MainParamsExt2.timelapseTime, "Timelapse Time =", _UNSIGNED_SHORT_);

    PrintStructElement(&SBGC32_Device, &MainParamsExt3.motorStartupDelay, "Motor Startup Delay =", _UNSIGNED_SHORT_);

    PrintMessage(&SBGC32_Device, TEXT_SIZE_((char*)" \n"));

    PrintStructElement(&SBGC32_Device, &RealTimeData.AxisRTD[ROLL].ACC_Data, "ACC Roll =", _SIGNED_SHORT_);
    PrintStructElement(&SBGC32_Device, &RealTimeData.AxisRTD[PITCH].ACC_Data, "ACC Pitch =", _SIGNED_SHORT_);
    PrintStructElement(&SBGC32_Device, &RealTimeData.AxisRTD[YAW].ACC_Data, "ACC Yaw =", _SIGNED_SHORT_);

    PrintStructElement(&SBGC32_Device, &RealTimeData.frameCamAngle[ROLL], "Roll Current Angle =", _SIGNED_SHORT_);
    PrintStructElement(&SBGC32_Device, &RealTimeData.frameCamAngle[PITCH], "Pitch Current Angle =", _SIGNED_SHORT_);
    PrintStructElement(&SBGC32_Device, &RealTimeData.frameCamAngle[YAW], "Yaw Current Angle =", _SIGNED_SHORT_);

    PrintStructElement(&SBGC32_Device, &RealTimeData.IMU_Temperature, "IMU Temperature =", _SIGNED_CHAR_);

    return SBGC32_Device._parserCurrentStatus;
}


TxRxStatus_t SBGC32_DemoControl (void)
{
    /* Getting adjvars values */
    /* Note: AdjVarGeneral.ID fields are already filled */
    SBGC32_GetAdjVarValues(&SBGC32_Device, AdjVarGeneral, countof_(AdjVarGeneral));

    /* Run the Demonstration Cycle */
    for (ui8 i = 0; i < 4; i++)
    {
        /* Printing. SBGC_ADJ_VARS_NAMES parameter must be SET_ON */
        for (ui8 k = 0; k < countof_(AdjVarGeneral); k++)
            PrintStructElement(&SBGC32_Device, &AdjVarGeneral[k].value, AdjVarGeneral[k].name, AdjVarGeneral[k].varType);

        Control.AxisC[YAW].angle = DEGREE_TO_ANGLE_INT(50);
        Control.AxisC[PITCH].angle = DEGREE_TO_ANGLE_INT(-20);
        SBGC32_Control(&SBGC32_Device, &Control);
        DELAY_MS_(5000);

        Control.AxisC[PITCH].angle = DEGREE_TO_ANGLE_INT(20);
        SBGC32_Control(&SBGC32_Device, &Control);
        DELAY_MS_(5000);

        Control.AxisC[YAW].angle = DEGREE_TO_ANGLE_INT(-50);
        SBGC32_Control(&SBGC32_Device, &Control);
        DELAY_MS_(5000);

        Control.AxisC[PITCH].angle = DEGREE_TO_ANGLE_INT(-20);
        SBGC32_Control(&SBGC32_Device, &Control);
        DELAY_MS_(5000);

        Control.AxisC[YAW].angle = DEGREE_TO_ANGLE_INT(0);
        Control.AxisC[PITCH].angle = DEGREE_TO_ANGLE_INT(0);
        SBGC32_Control(&SBGC32_Device, &Control);
        DELAY_MS_(5000);

        BeeperSettings.mode = BM_BEEPER_MODE_COMPLETE;
        SBGC32_PlayBeeper(&SBGC32_Device, &BeeperSettings);

        /* Adjustable Variables Re-Setting */
        for (ui8 k = 0; k < countof_(AdjVarGeneral); k++)
            /* Toggle Min : Max adjvars contrast */
            EditAdjVarValue(&AdjVarGeneral[k], ((i % 2 == 0) ? AdjVarGeneral[k].maxValue : AdjVarGeneral[k].minValue));

        SBGC32_SetAdjVarValues(&SBGC32_Device, AdjVarGeneral, countof_(AdjVarGeneral));
    }

    /* Saving all changed adjustable variables to EEPROM */
    /* SBGC32_SaveAllActiveAdjVarsToEEPROM(&SBGC32_Device);

    if (SBGC32_Device._confirmationParams.cmdID == CMD_SAVE_PARAMS_3)
        for (ui8 i = 0; i < countof_(AdjVarGeneral); i++)
            if (AdjVarGeneral[i].saveFlag != SAVED)
                AdjVarGeneral[i].saveFlag = SAVED; */

    /* or SBGC32_SaveAdjVarsToEEPROM(&SBGC32_Device, AdjVarGeneral, countof_(AdjVarGeneral)); */

    return SBGC32_Device._parserCurrentStatus;
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
    PrintStructElement(&SBGC32_Device, &RealTimeDataCustom.frameCamAngle[ROLL], "Frame Camera Angle Roll =", _SIGNED_SHORT_);
    PrintStructElement(&SBGC32_Device, &RealTimeDataCustom.frameCamAngle[PITCH], "Frame Camera Angle Pitch =", _SIGNED_SHORT_);
    PrintStructElement(&SBGC32_Device, &RealTimeDataCustom.frameCamAngle[YAW], "Frame Camera Angle Yaw =", _SIGNED_SHORT_);

    PrintStructElement(&SBGC32_Device, &RealTimeDataCustom.gyroData[ROLL], "Gyro Roll =", _SIGNED_SHORT_);
    PrintStructElement(&SBGC32_Device, &RealTimeDataCustom.gyroData[PITCH], "Gyro Pitch =", _SIGNED_SHORT_);
    PrintStructElement(&SBGC32_Device, &RealTimeDataCustom.gyroData[YAW], "Gyro Yaw =", _SIGNED_SHORT_);

    PrintStructElement(&SBGC32_Device, &RealTimeDataCustom.ACC_Data[ROLL], "ACC Roll =", _SIGNED_SHORT_);
    PrintStructElement(&SBGC32_Device, &RealTimeDataCustom.ACC_Data[PITCH], "ACC Pitch =", _SIGNED_SHORT_);
    PrintStructElement(&SBGC32_Device, &RealTimeDataCustom.ACC_Data[YAW], "ACC Yaw =", _SIGNED_SHORT_);

    PrintMessage(&SBGC32_Device, TEXT_SIZE_((char*)"__________________________\n\n"));
}