#include "driver_Linux.h"

#include "adjvar/adjvar.h"
#include "gimbalControl/gimbalControl.h"
#include "profiles/profiles.h"
#include "realtime/realtime.h"
#include "service/service.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*   					Global Software Objects  					  */
/* __________________________________________________________________ */

static      GeneralSBGC_t 			SBGC_1;

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

int main ()
{
    /* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
    /*                         Initialization                         */
    /* ______________________________________________________________ */

    /*  - - - - - - - - SBGC Hardware-Software Init - - - - - - - - - */

    /* Driver Init */
    SBGC_1.Drv = malloc(sizeof(Driver_t));
    DriverInit(SBGC_1.Drv, SBGC_SERIAL_PORT);

    /* High Layer Init */
    SBGC32_DefaultInit(&SBGC_1, PortTransmitData, PortReceiveByte, GetAvailableBytes,
                       PrintDebugData, GetTimeMs, SBGC_PROTOCOL_V2);


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

    while (1)
    {
        /* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
        /*                     Start Worker Cycle                     */
        /* __________________________________________________________ */

        SBGC32_ParseDataStream(&SBGC_1, DataStreamBuff, (SBGC_Commands_t) DataStreamInterval.cmdID);
        PrintDataStream(DataStreamBuff);

        usleep(20000);

        /*  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */
    }

    return 0;
}


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
        sleep(5);

        Control.AxisC[PITCH].angle = DEGREE_TO_ANGLE_INT(20);
        SBGC32_Control(&SBGC_1, &Control);
        sleep(5);
        Control.AxisC[YAW].angle = DEGREE_TO_ANGLE_INT(-50);
        SBGC32_Control(&SBGC_1, &Control);
        sleep(5);

        Control.AxisC[PITCH].angle = DEGREE_TO_ANGLE_INT(-20);
        SBGC32_Control(&SBGC_1, &Control);
        sleep(5);

        Control.AxisC[YAW].angle = DEGREE_TO_ANGLE_INT(0);
        Control.AxisC[PITCH].angle = DEGREE_TO_ANGLE_INT(0);
        SBGC32_Control(&SBGC_1, &Control);
        sleep(5);

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
