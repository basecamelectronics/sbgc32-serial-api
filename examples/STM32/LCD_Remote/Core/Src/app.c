/** ____________________________________________________________________
 *
 *	@file		app.c
 *
 *				BaseCamElectronics Team
 *
 *				LCD Remote project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "app.h"


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
			sprintf(buf, "SE: %03d FM:", SerialAPI_GetRxErrorsNumber(sbgcGeneral));
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
	pos = print_str(buf);

	LCD_FillSpace(&pos, LCD_COLS);

	LCD_RemoteGeneral->lowRateTimeMs = LCD_RemoteGeneral->currentTimeMs;
	LCD_RemoteGeneral->updateDisplayFlag = DISPLAY_UPDATED;
}


/* Displays a NULL-terminated string */
void LCD_DebugMessage (ui8 raw, char *str, ui8 length)
{
	ui8 pos = 0;

	setCursor(0, raw);

	while (pos != length)
		print_char(str[pos++]);

	LCD_FillSpace(&pos, LCD_COLS);
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

	#ifdef HAL_UART_MODULE_ENABLED

		sbgcDriver_t *drv = sbgcGeneral->_ll->drv;

		if ((*drv->uart).Init.BaudRate != BLUETOOTH_BAUD)
		{
			(*drv->uart).Init.BaudRate = BLUETOOTH_BAUD;

			if (HAL_UART_Init(drv->uart) != HAL_OK)
				Error_Handler();
		}

	#else

		ui32 periphclk = LL_RCC_GetUSARTClockFreq(LL_RCC_USART1_CLKSOURCE);  // if SBGC_SERIAL_PORT is UART1!

		ui32 USART_Speed = (LL_USART_GetBaudRate(SBGC_SERIAL_PORT, periphclk, LL_USART_OVERSAMPLING_8) / 100) * 100;  // rounding

		if (USART_Speed != BLUETOOTH_BAUD)
			LL_USART_SetBaudRate(SBGC_SERIAL_PORT, periphclk, LL_USART_OVERSAMPLING_8, BLUETOOTH_BAUD);

	#endif

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


void WriteI2C_Data (__I2C_STRUCT, ui8 slaveAddr, ui8 *data, ui8 size)
{
	#ifdef HAL_I2C_MODULE_ENABLED

		HAL_I2C_Master_Transmit(i2c, slaveAddr, data, size, 10);

	#else

		ui8 count = 0;

		while (LL_I2C_IsActiveFlag_BUSY(i2c));

		LL_I2C_HandleTransfer(i2c, slaveAddr, LL_I2C_ADDRSLAVE_7BIT, size, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);

		while (count < size)
		{
			while (!LL_I2C_IsActiveFlag_TXIS(i2c));

			LL_I2C_TransmitData8(i2c, data[count]);
			while (LL_I2C_IsActiveFlag_TCR(i2c));

			count++;
			LL_I2C_HandleTransfer(i2c, slaveAddr, LL_I2C_ADDRSLAVE_7BIT, size - count, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_NOSTARTSTOP);
		}

		while (!LL_I2C_IsActiveFlag_STOP(i2c));
		LL_I2C_ClearFlag_STOP(i2c);

		I2C_CLEAR_CR2(i2c);

	#endif
}


void RequestI2C_Data (__I2C_STRUCT, ui8 slaveAddr, ui8 *data, ui8 size)
{
	#ifdef HAL_I2C_MODULE_ENABLED

		HAL_I2C_Master_Receive(i2c, slaveAddr, data, size, 10);

	#else

		while (LL_I2C_IsActiveFlag_BUSY(i2c));

		LL_I2C_HandleTransfer(i2c, slaveAddr, LL_I2C_ADDRSLAVE_7BIT, size, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_READ);

		ui8 count = 0;

		while (count < size)
		{
			while (!LL_I2C_IsActiveFlag_RXNE(i2c));

			data[count] = LL_I2C_ReceiveData8(i2c);
			while (LL_I2C_IsActiveFlag_TCR(i2c));

			count++;
			LL_I2C_HandleTransfer(i2c, slaveAddr, LL_I2C_ADDRSLAVE_7BIT, size - count, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_NOSTARTSTOP);
		}

		while (!LL_I2C_IsActiveFlag_STOP(i2c));
		LL_I2C_ClearFlag_STOP(i2c);

		I2C_CLEAR_CR2(i2c);

	#endif
}


void GetEncoderAngles (InputsInfo_t *inputsInfo)
{
	ui8 regAddr [2] = {ENCODER_ANGLE_REG_MB, ENCODER_ANGLE_REG_LB};

	WriteI2C_Data(inputsInfo->i2c, ENCODER_I2C_ADDRES, regAddr, 2);
	RequestI2C_Data(inputsInfo->i2c, ENCODER_I2C_ADDRES, inputsInfo->I2C_Buff, 2);

	inputsInfo->FE_CurrentAngle = (((ui16)inputsInfo->I2C_Buff[0] << 6) & 0x3FC0) | ((ui16)inputsInfo->I2C_Buff[1] & 0x00C0);
}

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
