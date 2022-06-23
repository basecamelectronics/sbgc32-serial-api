/*  ____________________________________________________________________
 *
 *	Copyright © 2022 BaseCam Electronics™.
 *	All rights reserved.
 *
 *	Licensed under the Apache License, Version 2.0 (the "License");
 *	you may not use this file except in compliance with the License.
 *	You may obtain a copy of the License at
 *
 *	http://www.apache.org/licenses/LICENSE-2.0
 *
 *	Unless required by applicable law or agreed to in writing, software
 *	distributed under the License is distributed on an "AS IS" BASIS,
 *	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 *	implied. See the License for the specific language governing
 *	permissions and limitations under the License.
 *  ____________________________________________________________________
 */

#include "app.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													High-Layer Functions
 */
/* Process incoming commands. Call it as frequently as possible,
   to prevent overrun of serial input buffer */
void ProcessHandler (GeneralSBGC_t *generalSBGC, LCD_RemoteGeneral_t *LCD_RemoteGeneral,
					 RealTimeData_t *realTimeData, AdjVarsGeneral_t *adjVarGeneral)
{
	if (generalSBGC->_ParserCurrentStatus == TX_RX_OK)
	{
		if (LCD_RemoteGeneral->connectFlag == 0)
		{
			LCD_RemoteGeneral->connectFlag = 1;
			SBGC32_GetAdjVarValues(generalSBGC, adjVarGeneral, LCD_RemoteGeneral->adjVarQuan);
		}

		ui32 err = (ui32)(abs(realTimeData->IMU_Angle[ROLL] - realTimeData->targetAngle[ROLL])
				 + abs(realTimeData->IMU_Angle[PITCH] - realTimeData->targetAngle[PITCH])
				 + abs(realTimeData->IMU_Angle[YAW] - realTimeData->targetAngle[YAW])) * (ui32)(ANGLE_DEGREE_SCALE * 1000);

		 AverageValue(&LCD_RemoteGeneral->TargetErrorAverage, CONSTRAINT(err, 0, 999));
	}

	/* If no commands for a long time, set connected state to false */
	if (LCD_RemoteGeneral->connectFlag && (LCD_RemoteGeneral->currentTimeMs - LCD_RemoteGeneral->rtReqCmdTimeMs) > MAX_WAIT_TIME_MS)
		LCD_RemoteGeneral->connectFlag = 0; // last_bt_connect_ms = currentTimeMs;
}


/* De-bounce button: it should keep it's state for a given period
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
void UpdateDisplay (GeneralSBGC_t *generalSBGC, LCD_RemoteGeneral_t *LCD_RemoteGeneral,
					RealTimeData_t *realTimeData, AdjVarsGeneral_t *adjVarGeneral)
{
	/* First raw */
	setCursor(0, 0);

	char buf [17];

	ui8 pos = 0;

	LCD_RemoteGeneral->currentPage = (LCD_RemoteGeneral->currentPage + 50) % 5;  // Should be in the range of available pages

	switch (LCD_RemoteGeneral->currentPage)
	{
		case 0 : /* PAGE 0 */
			if (LCD_RemoteGeneral->connectFlag)
				sprintf(buf, "%2d.%02dV P:%d E:%03d", realTimeData->batLevel / 100, realTimeData->batLevel % 100,
						realTimeData->curProfile + 1, LCD_RemoteGeneral->TargetErrorAverage.avgRes);

			else
				LCD_PrintProgress(LCD_RemoteGeneral, print_str("CONNECTING"));

			break;

		case 1 :  /* PAGE 1 */
			sprintf(buf, "SE: %03d FM:", generalSBGC->_rxErrorsCount);
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

	pos = print_str(buf);

	LCD_FillSpace(&pos, LCD_COLS);

	/* Second raw */
	setCursor(0, 1);

	#ifdef SBGC_DEBUG_MODE

		/* Currently selected adj. variable name and value */
		for (pos = 0; pos < ADJ_VAR_NAME_MAX_LENGTH; pos++)
		{
			if (!(adjVarGeneral[LCD_RemoteGeneral->currentAdjVarIndex].name[pos + 8]))
				break;

			sprintf(&buf[pos], "%c", adjVarGeneral[LCD_RemoteGeneral->currentAdjVarIndex].name[pos + 8]);  // offset due to ADJ_VAR_ (+ 8)
		}

	#endif

	sprintf(&buf[pos], ":%li", adjVarGeneral[LCD_RemoteGeneral->currentAdjVarIndex].value);
	pos = print_str(buf);

	LCD_FillSpace(&pos, LCD_COLS);

	LCD_RemoteGeneral->lowRateTimeMs = LCD_RemoteGeneral->currentTimeMs;
	LCD_RemoteGeneral->updateDisplayFlag = DISPLAY_UPDATED;
}


/* Displays a NULL-terminated string */
void LCD_DebugMessage (ui8 raw, char *str, ui8 length)
{
	setCursor(0, raw);
	ui8 pos = 0;
	while (pos != length)
		print_char(str[pos++]);

	LCD_FillSpace(&pos, LCD_COLS);
}


ui8 BT_ReadAnswer (GeneralSBGC_t *generalSBGC, ui8 *buf, ui16 timeout, Boolean_t debug)
{
	HAL_Delay(timeout);
	ui8 size = 0;

	while (!generalSBGC->RxFunc(generalSBGC->Drv, (ui8*)&buf[size]))
		size++;

	buf[size - 2] = '\0';

	if (debug == TRUE__)
	{
		if (size != 0)
			LCD_DebugMessage(1, TEXT_SIZE_((char*)buf));

		else
		{
			LCD_DebugMessage(1, TEXT_SIZE_("NO ANSWER"));
			HAL_Delay(1000);
		}
	}

	return size;
}


void BT_MasterConnect (GeneralSBGC_t *generalSBGC)
{
	ui8 buf [BLUETOOTH_BUF_SIZE];

	LCD_DebugMessage(0, TEXT_SIZE_("BLUETOOTH INIT.."));

	if ((*SBGC_SERIAL_PORT).Init.BaudRate != BLUETOOTH_BAUD)
	{
		(*SBGC_SERIAL_PORT).Init.BaudRate = BLUETOOTH_BAUD;

		if (HAL_UART_Init(SBGC_SERIAL_PORT) != HAL_OK)
			Error_Handler();
	}

	/* generalSBGC->TxFunc(generalSBGC->Drv, (ui8*)"AT+UART=115200,0,0\r\n", strlen("AT+UART=115200,0,0\r\n"));
	HAL_Delay(500);
	LCD_DebugMessage(1, TEXT_SIZE_("115200 SPEED..."));
	BT_ReadAnswer(generalSBGC, buf, 500, TRUE__); */

	generalSBGC->TxFunc(generalSBGC->Drv, (ui8*)"AT+RMAAD\r\n", strlen("AT+RMAAD\r\n"));  // Clear paired devices
	HAL_Delay(500);
	LCD_DebugMessage(1, TEXT_SIZE_("RMAAD..."));
	BT_ReadAnswer(generalSBGC, buf, 500, TRUE__);

	generalSBGC->TxFunc(generalSBGC->Drv, (ui8*)"AT+PSWD=", strlen("AT+PSWD="));
	generalSBGC->TxFunc(generalSBGC->Drv, (ui8*)BLUETOOTH_CLIENT_PIN, strlen(BLUETOOTH_CLIENT_PIN));
	generalSBGC->TxFunc(generalSBGC->Drv, (ui8*)"\r\n", 2);
	HAL_Delay(500);
	LCD_DebugMessage(1, TEXT_SIZE_("PIN..."));
	BT_ReadAnswer(generalSBGC, buf, 500, TRUE__);

	generalSBGC->TxFunc(generalSBGC->Drv, (ui8*)"AT+ROLE=1\r\n", strlen("AT+ROLE=1\r\n"));  // Set 'master' mode
	HAL_Delay(500);
	LCD_DebugMessage(1, TEXT_SIZE_("ROLE = MASTER..."));
	BT_ReadAnswer(generalSBGC, buf, 500, TRUE__);

	generalSBGC->TxFunc(generalSBGC->Drv, (ui8*)"AT+CMODE=0\r\n", strlen("AT+CMODE=0\r\n"));  // Connect only to fixed MAC address
	HAL_Delay(500);
	LCD_DebugMessage(1, TEXT_SIZE_("CMODE = 0..."));
	BT_ReadAnswer(generalSBGC, buf, 500, TRUE__);

//	generalSBGC->TxFunc(generalSBGC->Drv, (ui8*)"AT+INIT\r\n", strlen("AT+INIT\r\n"));  // Initialize 'SPP'
//	HAL_Delay(500);
//	LCD_DebugMessage(1, TEXT_SIZE_("INIT SPP"));
//	BT_ReadAnswer(generalSBGC, buf, 500, TRUE__);

	generalSBGC->TxFunc(generalSBGC->Drv, (ui8*)"AT+LINK=", strlen("AT+LINK="));
	generalSBGC->TxFunc(generalSBGC->Drv, (ui8*)BLUETOOTH_CLIENT_MAC_ADDR, strlen(BLUETOOTH_CLIENT_MAC_ADDR));
	generalSBGC->TxFunc(generalSBGC->Drv, (ui8*)"\r\n", 2);  // Connect to slave HC-05
	BT_ReadAnswer(generalSBGC, buf, 500, TRUE__);
	HAL_Delay(500);
	LCD_DebugMessage(1, TEXT_SIZE_("CONNECTION..."));
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *													 Low-Layer Functions
 */
void InitADC (InputsInfo_t *inputsInfo, __ADC_STRUCT)
{
	inputsInfo->adc = adc;
	DISABLE_ADC_CR1_EOCIE(inputsInfo->adc);

	inputsInfo->_curChannel = 0;
}


void ReadADC_Inputs (InputsInfo_t *inputsInfo)
{
	START_ADC(inputsInfo->adc);
}


void ADC_DRV_EndConvCallBack (InputsInfo_t *inputsInfo)
{
	inputsInfo->ADC_INx[inputsInfo->_curChannel++] = GET_ADC_CONV_DATA(inputsInfo->adc);

	if (inputsInfo->_curChannel >= ADC_CHANNELS_QUAN)
	{
		inputsInfo->_curChannel = 0;
		STOP_ADC(inputsInfo->adc);
	}
}


ui8 ReadButtonState (__GPIO_STRUCT, ui16 pin)
{
	return READ_PIN(gpio, pin);
}


void EXTI_DRV_FallingCallBack (InputsInfo_t *inputsInfo, ui16 pin)
{
	if (pin == ENC_A_Pin)
		inputsInfo->KE_CurrentValue++;

	else
		inputsInfo->KE_CurrentValue--;
}


void InitI2C (InputsInfo_t *inputsInfo, __I2C_STRUCT)
{
	inputsInfo->i2c = i2c;
}


void GetEncoderAngles (InputsInfo_t *inputsInfo)
{
	ui8 regAddr [2] = {ENCODER_ANGLE_REG_MB, ENCODER_ANGLE_REG_LB};

	HAL_I2C_Master_Transmit(ENCODER_I2C, ENCODER_I2C_ADDRES, regAddr, 2, 10);
	HAL_I2C_Master_Receive(ENCODER_I2C, ENCODER_I2C_ADDRES, inputsInfo->I2C_Buff, 2, 10);

	inputsInfo->FE_CurrentAngle = (((ui16)inputsInfo->I2C_Buff[0] << 6) & 0x3FC0) | ((ui16)inputsInfo->I2C_Buff[1] & 0x00C0);
}

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
