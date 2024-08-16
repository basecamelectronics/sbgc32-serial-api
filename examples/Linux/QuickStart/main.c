/*	____________________________________________________________________
 *
 *	This is an example sketch for Linux OS, that shows how to control
 *	SimpleBGC-driven gimbal via Serial API. API specs are available at
 *	http://www.basecamelectronics.com/serialapi/
 *	____________________________________________________________________
 */

#include "sbgc32.h"


#define		SBGC_GET_ANGLES_TIMEOUT			15000
#define		SBGC_GET_ANGLES_INTERVAL		1000


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


int main ()
{
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
			return 0;  // Stop the program here
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
			return 0;  // Stop the program here
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
			return 0;  // Stop the program here
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
}
