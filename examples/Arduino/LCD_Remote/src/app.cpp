/** ____________________________________________________________________
 *
 *	@file		app.cpp
 *
 *				BaseCamElectronics Team
 *
 *				LCD Remote project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "app.h"


LiquidCrystal lcd (LCD_RS_PIN, LCD_ENABLE_PIN, LCD_D4_PIN, 
				   LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													High-Layer Functions
 */
/* Process incoming commands. Call it as frequently as possible,
   to prevent overrun of serial input buffer */
void ProcessHandler (sbgcGeneral_t *sbgcGeneral, LCD_RemoteGeneral_t *LCD_RemoteGeneral,
					 sbgcRealTimeData_t *realTimeData, sbgcAdjVarGeneral_t *adjVarGeneral)
{
	if (SerialAPI_GetStatus(sbgcGeneral) == sbgcCOMMAND_OK)
	{
		if (LCD_RemoteGeneral->connectFlag == 0)
		{
			LCD_RemoteGeneral->connectFlag = 1;
			SBGC32_GetAdjVarValues(sbgcGeneral, adjVarGeneral, LCD_RemoteGeneral->adjVarQuan);
		}

		ui32 err = (ui32)(abs(realTimeData->IMU_Angle[ROLL] - realTimeData->targetAngle[ROLL])
				 + abs(realTimeData->IMU_Angle[PITCH] - realTimeData->targetAngle[PITCH])
				 + abs(realTimeData->IMU_Angle[YAW] - realTimeData->targetAngle[YAW])) * (ui32)((1 / SBGC_ANGLE_SCALE) * 1000);

		 AverageValue(&LCD_RemoteGeneral->TargetErrorAverage, constrain_(err, 0, 999));
	}

	/* If no commands for a long time, set connected state to false */
	if (LCD_RemoteGeneral->connectFlag && (LCD_RemoteGeneral->currentTimeMs - LCD_RemoteGeneral->rtReqCmdTimeMs) > MAX_WAIT_TIME_MS)
		LCD_RemoteGeneral->connectFlag = 0;  // last_bt_connect_ms = currentTimeMs;
}


/* De-bounce button: it should keep its state for a given period
   of time, specified in the BTN_BOUNCE_THRESHOLD_MS returns 1
   if LCD_RemoteGeneral->....triggerState is changed. */
ui8 DebounceNavigationButton (LCD_RemoteGeneral_t *LCD_RemoteGeneral, ButtonDirection_t newState)
{
	if (newState != LCD_RemoteGeneral->NavButton.state)
	{
		LCD_RemoteGeneral->NavButton.state = newState;
		LCD_RemoteGeneral->NavButton.lastTimeMs = LCD_RemoteGeneral->currentTimeMs;
	}

	else if (LCD_RemoteGeneral->NavButton.triggerState != LCD_RemoteGeneral->NavButton.state &&
			 (ui16)(LCD_RemoteGeneral->currentTimeMs - LCD_RemoteGeneral->NavButton.lastTimeMs) > SOFTWARE_ANTI_BOUNCE)
	{
		LCD_RemoteGeneral->NavButton.triggerState = LCD_RemoteGeneral->NavButton.state;
		return 1;
	}

	return 0;
}


/* Reads the state of buttons */
ButtonDirection_t ReadNavigationButtonState (InputsInfo_t *inputsInfo)
{
	ReadADC_Inputs(inputsInfo);  // start next conversions

	ui16 navBtnLevel = inputsInfo->ADC_INx[ADC_NAV];

	if (navBtnLevel >= 3600)
		return NAV_BTN_RELEASED;

	if (navBtnLevel < 150)
		return NAV_BTN_LEFT;
	if (navBtnLevel < 600)
		return NAV_BTN_UP;
	if (navBtnLevel < 1300)
		return NAV_BTN_RIGHT;
	if (navBtnLevel < 2000)
		return NAV_BTN_SELECT;
	if (navBtnLevel < 2900)
		return NAV_BTN_DOWN;
	if (navBtnLevel < 3600)
		return NAV_BTN_ENCODER_SELECT;

	return NAV_BTN_RELEASED;
}


/* Re-paint display */
void UpdateDisplay (sbgcGeneral_t *sbgcGeneral, LCD_RemoteGeneral_t *LCD_RemoteGeneral,
					sbgcRealTimeData_t *realTimeData, sbgcAdjVarGeneral_t *adjVarGeneral)
{
	/* First raw */
	lcd.setCursor(0, 0);

	char buf [17];

	ui8 pos = 0;

	LCD_RemoteGeneral->currentPage = (LCD_RemoteGeneral->currentPage + 50) % 5;  // Should be in the range of available pages

	switch (LCD_RemoteGeneral->currentPage)
	{
		case 0 : /* PAGE 0 */
			if (LCD_RemoteGeneral->connectFlag == 1)
				sprintf(buf, "%2d.%02dV P:%d E:%03d", realTimeData->batLevel / 100, realTimeData->batLevel % 100,
						realTimeData->curProfile + 1, LCD_RemoteGeneral->TargetErrorAverage.avgRes);

			else
				LCD_PrintProgress(LCD_RemoteGeneral, lcd.print("CONNECTING"));

			break;

		case 1 :  /* PAGE 1 */
			sprintf(buf, "SE:%04d  FM:%04dB", SerialAPI_GetRxErrorsNumber(sbgcGeneral), freeMemory());
			break;

		case 2 :  /* PAGE 2 */
			sprintf(buf, " D1:%3d  D2:%3d", LCD_RemoteGeneral->debug1, LCD_RemoteGeneral->debug2);
			break;

		case 3 :  /* PAGE 3 */
			sprintf(buf, " D3:%3d  D4:%3d", LCD_RemoteGeneral->debug3, LCD_RemoteGeneral->debug4);
			break;

		case 4 :  /* PAGE 4 */
			sprintf(buf, "I2C_ERRORS: %03d", realTimeData->I2C_ErrorCount);
			break;
	}

	pos = lcd.print(buf);
	
	LCD_FillSpace(&pos, LCD_COLS);

	/* Second raw */
	lcd.setCursor(0, 1);

	#if (SBGC_NEED_DEBUG)

		/* Currently selected adj. variable name and value */
		for (pos = 0; pos < ADJ_VAR_NAME_MAX_LENGTH; pos++)
		{
			if (!(adjVarGeneral[LCD_RemoteGeneral->currentAdjVarIndex].name[pos + 8]))
				break;

			sprintf(&buf[pos], "%c", adjVarGeneral[LCD_RemoteGeneral->currentAdjVarIndex].name[pos + 8]);  // offset due to ADJ_VAR_ (+ 8)
		}

	#endif

	sprintf(&buf[pos], ":%li", adjVarGeneral[LCD_RemoteGeneral->currentAdjVarIndex].value);
	pos = lcd.print(buf);

	LCD_FillSpace(&pos, LCD_COLS);

	LCD_RemoteGeneral->lowRateTimeMs = LCD_RemoteGeneral->currentTimeMs;
	LCD_RemoteGeneral->updateDisplayFlag = DISPLAY_UPDATED;
}


/* Displays a NULL-terminated string */
void LCD_DebugMessage (ui8 raw, char *str, ui8 length)
{
	ui8 pos = 0;

	lcd.setCursor(0, raw);

	while (pos != length)
		lcd.print(str[pos++]);

	LCD_FillSpace(&pos, LCD_COLS);
}


void LCD_PrintProgress (LCD_RemoteGeneral_t *LCD_RemoteGeneral, ui8 cursor_pos)
{
	for (ui8 i = 0; i < 3; i++)
		cursor_pos += lcd.print(((ui8)(LCD_RemoteGeneral->currentTimeMs / 1000)) % 4 > i ? '.' : ' ');
}


void LCD_FillSpace (ui8 *cursor_pos, ui8 to_pos)
{
	while (*cursor_pos < to_pos)
	{
		lcd.print(' ');
		(*cursor_pos)++;
	}
}


ui8 BT_ReadAnswer (sbgcGeneral_t *sbgcGeneral, ui8 *buff, ui16 timeout, sbgcBoolean_t debug)
{
	sbgcDelay(timeout);

	ui8 size = 0;

	while (!sbgcGeneral->_ll->drvRx(sbgcGeneral->_ll->drv, (ui8*)&buff[size]))
		size++;

	if (debug)
	{
		if (size != 0)
		{
			buff[size - 2] = '\0';
			LCD_DebugMessage(1, TEXT_LENGTH_((char*)buff));
			sbgcDelay(500);
		}

		else
		{
			LCD_DebugMessage(1, TEXT_LENGTH_((char*)"NO ANSWER"));
			sbgcDelay(1000);
		}
	}

	return size;
}


void BT_MasterConnect (sbgcGeneral_t *sbgcGeneral)
{
	ui8 buff [BLUETOOTH_BUF_SIZE];

	LCD_DebugMessage(0, TEXT_LENGTH_((char*)"BLUETOOTH INIT.."));

	if (SBGC_SERIAL_SPEED != BLUETOOTH_BAUD)  // for SBGC_SERIAL_PORT.begin(SBGC_SERIAL_SPEED) initialization
		SBGC_SERIAL_PORT.begin(BLUETOOTH_BAUD);

	/* UART speed re-setting (optional) */
	/* sbgcGeneral->_ll->drvTx(sbgcGeneral->_ll->drv, (ui8*)"AT+UART=115200,0,0\r\n", strlen("AT+UART=115200,0,0\r\n"));
	LCD_DebugMessage(1, TEXT_LENGTH_((char*)"115200 SPEED..."));
	BT_ReadAnswer(sbgcGeneral, buff, 500, sbgcTRUE); */

	sbgcGeneral->_ll->drvTx(sbgcGeneral->_ll->drv, (ui8*)"AT+RMAAD\r\n", strlen("AT+RMAAD\r\n"));  // Clear paired devices
	LCD_DebugMessage(1, TEXT_LENGTH_((char*)"RMAAD..."));
	BT_ReadAnswer(sbgcGeneral, buff, 500, sbgcTRUE);

	sbgcGeneral->_ll->drvTx(sbgcGeneral->_ll->drv, (ui8*)"AT+PSWD=", strlen("AT+PSWD="));
	sbgcGeneral->_ll->drvTx(sbgcGeneral->_ll->drv, (ui8*)BLUETOOTH_CLIENT_PIN, strlen(BLUETOOTH_CLIENT_PIN));
	sbgcGeneral->_ll->drvTx(sbgcGeneral->_ll->drv, (ui8*)"\r\n", 2);
	LCD_DebugMessage(1, TEXT_LENGTH_((char*)"PIN..."));
	BT_ReadAnswer(sbgcGeneral, buff, 500, sbgcTRUE);

	sbgcGeneral->_ll->drvTx(sbgcGeneral->_ll->drv, (ui8*)"AT+ROLE=1\r\n", strlen("AT+ROLE=1\r\n"));  // Set 'master' mode
	LCD_DebugMessage(1, TEXT_LENGTH_((char*)"ROLE = MASTER..."));
	BT_ReadAnswer(sbgcGeneral, buff, 500, sbgcTRUE);

	sbgcGeneral->_ll->drvTx(sbgcGeneral->_ll->drv, (ui8*)"AT+CMODE=0\r\n", strlen("AT+CMODE=0\r\n"));  // Connect only to fixed MAC address
	LCD_DebugMessage(1, TEXT_LENGTH_((char*)"CMODE = 0..."));
	BT_ReadAnswer(sbgcGeneral, buff, 500, sbgcTRUE);

	/* sbgcGeneral->_ll->drvTx(sbgcGeneral->_ll->drv, (ui8*)"AT+INIT\r\n", strlen("AT+INIT\r\n"));  // Initialize 'SPP'
	LCD_DebugMessage(1, TEXT_LENGTH_((char*)"INIT SPP"));
	BT_ReadAnswer(sbgcGeneral, buff, 500, sbgcTRUE); */

	sbgcGeneral->_ll->drvTx(sbgcGeneral->_ll->drv, (ui8*)"AT+LINK=", strlen("AT+LINK="));
	sbgcGeneral->_ll->drvTx(sbgcGeneral->_ll->drv, (ui8*)BLUETOOTH_CLIENT_MAC_ADDR, strlen(BLUETOOTH_CLIENT_MAC_ADDR));
	sbgcGeneral->_ll->drvTx(sbgcGeneral->_ll->drv, (ui8*)"\r\n", 2);  // Connect to slave HC-05
	BT_ReadAnswer(sbgcGeneral, buff, 500, sbgcTRUE);
	LCD_DebugMessage(1, TEXT_LENGTH_((char*)"CONNECTION..."));
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													 Low-Layer Functions
 */
void ReadADC_Inputs (InputsInfo_t *inputsInfo)
{
	inputsInfo->_curChannel = 0;
	inputsInfo->ADC_INx[inputsInfo->_curChannel++] = analogRead(NAV_BTN_ANALOG_PIN);
	inputsInfo->ADC_INx[inputsInfo->_curChannel++] = analogRead(JOY_X_ANALOG_PIN);
	inputsInfo->ADC_INx[inputsInfo->_curChannel++] = analogRead(JOY_Y_ANALOG_PIN);
}


ui8 ReadButtonState (ui8 pin)
{
	return digitalRead(pin);
}


void GetEncoderAngles (InputsInfo_t *inputsInfo)
{
	Wire.beginTransmission(ENCODER_I2C_ADDRES);
	Wire.write(ENCODER_ANGLE_REG_MB);
	Wire.write(ENCODER_ANGLE_REG_LB);
	Wire.endTransmission();

	Wire.requestFrom(ENCODER_I2C_ADDRES, 2);

	ui16 count = 0;
    while (Wire.available())
	{   /* Prevent [-Wmisleading-indentation] */
        inputsInfo->I2C_Buff[count++] = Wire.read();
	}

	inputsInfo->FE_CurrentAngle = (((ui16)inputsInfo->I2C_Buff[0] << 6) & 0x3FC0) | ((ui16)inputsInfo->I2C_Buff[1] & 0x00C0);
}

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
