#include "driver_Linux.h"

#include "gimbalControl/gimbalControl.h"
#include "profiles/profiles.h"
#include "realtime/realtime.h"
#include "service/service.h"


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

static		RealTimeData_t			RealTimeData;

static		BeeperSettings_t		BeeperSettings;


TxRxStatus_t PrintBoardParameters (GeneralSBGC_t *generalSBGC, Profile_t slot);
TxRxStatus_t SBGC32_Demo (GeneralSBGC_t *generalSBGC);

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

    ControlConfig.AxisCC[ROLL].angleLPF = 6;
    ControlConfig.AxisCC[PITCH].angleLPF = 7;
    ControlConfig.AxisCC[YAW].angleLPF = 7;

    ControlConfig.AxisCC[ROLL].angleLPF = 6;
    ControlConfig.AxisCC[PITCH].speedLPF = 7;
    ControlConfig.AxisCC[YAW].speedLPF = 7;
    ControlConfig.flags = RTCCF_CONTROL_CONFIG_FLAG_NO_CONFIRM;

    Control.controlMode[ROLL] = CtrlM_MODE_ANGLE | CtrlF_CONTROL_FLAG_TARGET_PRECISE;
    Control.controlMode[PITCH] = CtrlM_MODE_ANGLE | CtrlF_CONTROL_FLAG_TARGET_PRECISE;
    Control.controlMode[YAW] = CtrlM_MODE_ANGLE | CtrlF_CONTROL_FLAG_TARGET_PRECISE;

    Control.AxisC[ROLL].angle = 0;
    Control.AxisC[PITCH].angle = 0;
    Control.AxisC[YAW].angle = 0;

    Control.AxisC[PITCH].speed = 500;
    Control.AxisC[YAW].speed = 500;

    // SBGC32_Reset(&SBGC_1, RF_RESET_WITH_RESTORING_STATES, 500);
    // SBGC32_CheckConfirmation(&SBGC_1, &Confirm, CMD_RESET);
    // sleep(5);

    SBGC32_ControlConfig(&SBGC_1, &ControlConfig, &Confirm);

    PrintBoardParameters(&SBGC_1, P_CURRENT_PROFILE);
    SBGC32_Demo(&SBGC_1);

    return 0;
}


TxRxStatus_t PrintBoardParameters (GeneralSBGC_t *generalSBGC, Profile_t slot)
{
    SBGC32_ReadBoardInfo(generalSBGC, &BoardInfo, 0);
    SBGC32_ReadBoardInfo3(generalSBGC, &BoardInfo3);

    SBGC32_ReadParams3(generalSBGC, &MainParams3, slot);
    SBGC32_ReadParamsExt(generalSBGC, &MainParamsExt, slot);
    SBGC32_ReadParamsExt2(generalSBGC, &MainParamsExt2, slot);
    SBGC32_ReadParamsExt3(generalSBGC, &MainParamsExt3, slot);

    SBGC32_ReadRealTimeData4(generalSBGC, &RealTimeData);

    char boardVersionStr [4];
    char firmwareVersionStr [7];

    FormatBoardVersion(BoardInfo.boardVer, boardVersionStr);
    FormatFirmwareVersion(BoardInfo.firmwareVer, firmwareVersionStr);

    PrintMessage(generalSBGC, TEXT_SIZE_("Board Version: "));
    PrintMessage(generalSBGC, TEXT_SIZE_(boardVersionStr));
    PrintMessage(generalSBGC, TEXT_SIZE_(" \n"));
    PrintMessage(generalSBGC, TEXT_SIZE_("Firmware Version: "));
    PrintMessage(generalSBGC, TEXT_SIZE_(firmwareVersionStr));
    PrintMessage(generalSBGC, TEXT_SIZE_(" \n"));

    PrintStructElement(generalSBGC, BoardInfo3.flashSize, "Flash Size =", _UNSIGNED_CHAR_);

    PrintStructElement(generalSBGC, MainParams3.profileID + 1, "Current profile #", _UNSIGNED_CHAR_);

    PrintStructElement(generalSBGC, MainParams3.AxisCMP3[ROLL].p, "Roll P =", _UNSIGNED_CHAR_);
    PrintStructElement(generalSBGC, MainParams3.AxisCMP3[ROLL].i, "Roll I =", _UNSIGNED_CHAR_);
    PrintStructElement(generalSBGC, MainParams3.AxisCMP3[ROLL].d, "Roll D =", _UNSIGNED_CHAR_);
    PrintStructElement(generalSBGC, MainParams3.AxisCMP3[PITCH].p, "Pitch P =", _UNSIGNED_CHAR_);
    PrintStructElement(generalSBGC, MainParams3.AxisCMP3[PITCH].i, "Pitch I =", _UNSIGNED_CHAR_);
    PrintStructElement(generalSBGC, MainParams3.AxisCMP3[PITCH].d, "Pitch D =", _UNSIGNED_CHAR_);
    PrintStructElement(generalSBGC, MainParams3.AxisCMP3[YAW].p, "Yaw P =", _UNSIGNED_CHAR_);
    PrintStructElement(generalSBGC, MainParams3.AxisCMP3[YAW].i, "Yaw I =", _UNSIGNED_CHAR_);
    PrintStructElement(generalSBGC, MainParams3.AxisCMP3[YAW].d, "Yaw D =", _UNSIGNED_CHAR_);
    PrintStructElement(generalSBGC, MainParams3.ACC_LimiterAll, "ACC Limiter all = ", _UNSIGNED_CHAR_);
    PrintStructElement(generalSBGC, MainParams3.AxisRC_MP3[ROLL].RC_MaxAngle, "RC Max Angle =", _SIGNED_SHORT_);
    PrintStructElement(generalSBGC, MainParams3.AxisRC_MP3[YAW].RC_MinAngle, "RC Min Angle =", _SIGNED_SHORT_);
    PrintStructElement(generalSBGC, MainParams3.RC_MapROLL, "RC Map ROLL =", _UNSIGNED_CHAR_);
    PrintStructElement(generalSBGC, MainParams3.RC_MapPITCH, "RC_MapPITCH =", _UNSIGNED_CHAR_);
    PrintStructElement(generalSBGC, MainParams3.RC_MapYAW, "RC_MapYAW =", _UNSIGNED_CHAR_);
    PrintStructElement(generalSBGC, MainParams3.RC_MapCmd, "RC_MapCmd =", _UNSIGNED_CHAR_);
    PrintStructElement(generalSBGC, MainParams3.RC_MapFC_ROLL, "RC_MapFC_ROLL =", _UNSIGNED_CHAR_);
    PrintStructElement(generalSBGC, MainParams3.RC_MapFC_PITCH, "RC_MapFC_PITCH =", _UNSIGNED_CHAR_);

    PrintStructElement(generalSBGC, MainParamsExt.LPF_Freq[ROLL], "ROLL LPF Frequency =", _UNSIGNED_SHORT_);
    PrintStructElement(generalSBGC, MainParamsExt.LPF_Freq[PITCH], "PITCH LPF Frequency =", _UNSIGNED_SHORT_);
    PrintStructElement(generalSBGC, MainParamsExt.LPF_Freq[YAW], "YAW LPF Frequency =", _UNSIGNED_SHORT_);

    PrintStructElement(generalSBGC, MainParamsExt2.frameIMU_LPF_Freq, "Timelapse Time =", _UNSIGNED_CHAR_);
    PrintStructElement(generalSBGC, MainParamsExt2.timelapseTime, "Timelapse Time =", _UNSIGNED_SHORT_);

    PrintStructElement(generalSBGC, MainParamsExt3.motorStartupDelay, "Motor Startup Delay =", _UNSIGNED_SHORT_);

    PrintMessage(generalSBGC, TEXT_SIZE_(" \n"));
    PrintStructElement(generalSBGC, RealTimeData.frameCamAngle[ROLL], "Roll Current Angle =", _SIGNED_SHORT_);
    PrintStructElement(generalSBGC, RealTimeData.frameCamAngle[PITCH], "Pitch Current Angle =", _SIGNED_SHORT_);
    PrintStructElement(generalSBGC, RealTimeData.frameCamAngle[YAW], "Yaw Current Angle =", _SIGNED_SHORT_);

    PrintStructElement(generalSBGC, RealTimeData.IMU_Temperature, "IMU Temperature =", _SIGNED_CHAR_);

    return generalSBGC->_ParserCurrentStatus;
}


TxRxStatus_t SBGC32_Demo (GeneralSBGC_t *generalSBGC)
{
    Control.AxisC[YAW].angle = DEGREE_TO_ANGLE_INT(50);
    Control.AxisC[PITCH].angle = DEGREE_TO_ANGLE_INT(-20);
    SBGC32_Control(generalSBGC, &Control);
    sleep(5);

    Control.AxisC[PITCH].angle = DEGREE_TO_ANGLE_INT(20);
    SBGC32_Control(generalSBGC, &Control);
    sleep(5);

    Control.AxisC[YAW].angle = DEGREE_TO_ANGLE_INT(-50);
    SBGC32_Control(generalSBGC, &Control);
    sleep(5);

    Control.AxisC[PITCH].angle = DEGREE_TO_ANGLE_INT(-20);
    SBGC32_Control(generalSBGC, &Control);
    sleep(5);

    Control.AxisC[YAW].angle = DEGREE_TO_ANGLE_INT(0);
    Control.AxisC[PITCH].angle = DEGREE_TO_ANGLE_INT(0);
    SBGC32_Control(generalSBGC, &Control);
    sleep(5);

    BeeperSettings.mode = BM_BEEPER_MODE_COMPLETE;
    SBGC32_PlayBeeper(generalSBGC, &BeeperSettings);

    return generalSBGC->_ParserCurrentStatus;
}