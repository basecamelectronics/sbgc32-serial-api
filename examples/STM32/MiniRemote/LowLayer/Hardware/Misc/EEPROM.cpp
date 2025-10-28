/** ____________________________________________________________________
 *
 *	@file		EEPROM.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "EEPROM.h"


ExternalEEPROM EEPROM(	EEPROM_I2C_INSTANCE,
						EEPROM_I2C_ADDRESS,
						PRPH_ABSOLUTE_ENCODER_EEPROM,
						&GPIO_ReferenceArray[ABS_ENC_EEPROM_PRPH_OFFSET],
						ABS_ENC_EEPROM_PRPH_PINS_NUM,
						lambdafunc_(EEPROM_I2C_GPIO_CLOCK_ENABLE()),
						lambdafunc_(EEPROM_I2C_CLOCK_ENABLE()));


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														   Class Methods
 */
void ExternalEEPROM::Init (void)
{
	/* Init order : SDA, SCL */
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	InputClockEnable();

	GPIO_InitStruct.Pin			= GPIO_Channel[0].pin;
	GPIO_InitStruct.Mode		= GPIO_MODE_AF_OD;
	GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate	= GPIO_Channel[0].pinAF;
	HAL_GPIO_Init(GPIO_Channel[0].port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin			= GPIO_Channel[1].pin;
	GPIO_InitStruct.Mode		= GPIO_MODE_AF_OD;
	GPIO_InitStruct.Speed		= GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate	= GPIO_Channel[1].pinAF;
	HAL_GPIO_Init(GPIO_Channel[1].port, &GPIO_InitStruct);

	/* I2C2 clock enable */
	ModuleClockEnable();

	hi2c.Instance = instance;
	hi2c.Init.ClockSpeed		= 400000;
	hi2c.Init.DutyCycle			= I2C_DUTYCYCLE_2;
	hi2c.Init.OwnAddress1		= 0;
	hi2c.Init.AddressingMode	= I2C_ADDRESSINGMODE_7BIT;
	hi2c.Init.DualAddressMode	= I2C_DUALADDRESS_DISABLE;
	hi2c.Init.OwnAddress2		= 0;
	hi2c.Init.GeneralCallMode	= I2C_GENERALCALL_DISABLE;
	hi2c.Init.NoStretchMode		= I2C_NOSTRETCH_DISABLE;

	if (HAL_I2C_Init(&hi2c) != HAL_OK)
		HardwareErrorHandler();

	osDelay(10);
}


void ExternalEEPROM::WriteByte (ui16 regAddr, ui8 byte)
{
	ui8 dataBuff [3];

	dataBuff[0] = ((regAddr & 0xFF00) >> 8);
	dataBuff[1] = regAddr & 0x00FF;
	dataBuff[2] = byte;

	HAL_I2C_Master_Transmit(GetAddressI2C_Handle(), GetHardwareAddress() << 1, dataBuff, 3, 10);
}


void ExternalEEPROM::ReadByte (ui16 regAddr, ui8 *byte)
{
	ui8 regBuff [2];

	regBuff[0] = ((regAddr & 0xFF00) >> 8);
	regBuff[1] = regAddr & 0x00FF;

	HAL_I2C_Master_Transmit(GetAddressI2C_Handle(), GetHardwareAddress() << 1, regBuff, 2, 10);
	HAL_I2C_Master_Receive(GetAddressI2C_Handle(), GetHardwareAddress() << 1, byte, 1, 10);
}


void ExternalEEPROM::WriteData (ui16 regAddr, ui8 *data, ui8 size)
{
	ui8 dataBuff [size + 2];

	dataBuff[0] = ((regAddr & 0xFF00) >> 8);
	dataBuff[1] = regAddr & 0x00FF;

	if ((EEPROM_BLOCK_DATA_SIZE - ((regAddr + EEPROM_BLOCK_DATA_SIZE) % EEPROM_BLOCK_DATA_SIZE)) < size)
	/* There is no aligned to page size. Split this operation to 2 actions */
	{
		ui8 cutSize = EEPROM_BLOCK_DATA_SIZE - ((regAddr + EEPROM_BLOCK_DATA_SIZE) % EEPROM_BLOCK_DATA_SIZE);
		memcpy(dataBuff + 2, data, cutSize);

		HAL_I2C_Master_Transmit(GetAddressI2C_Handle(), GetHardwareAddress() << 1, dataBuff, cutSize + 2, 10);

		for (ui32 i = 0; i < SystemCoreClock / 1000; i++)
			__NOP();

		size = EEPROM_BLOCK_DATA_SIZE - cutSize;

		memcpy(dataBuff + 2, &data[EEPROM_BLOCK_DATA_SIZE - size], size);
	}

	else
		memcpy(dataBuff + 2, data, size);

	HAL_I2C_Master_Transmit(GetAddressI2C_Handle(), GetHardwareAddress() << 1, dataBuff, size + 2, 10);
}


void ExternalEEPROM::ReadData (ui16 regAddr, ui8 *data, ui16 size)
{
	ui8 regBuff [2];

	for (ui16 i = 0; i < size; i++)
	{
		regBuff[0] = ((regAddr & 0xFF00) >> 8);
		regBuff[1] = regAddr & 0x00FF;

		HAL_I2C_Master_Transmit(GetAddressI2C_Handle(), GetHardwareAddress() << 1, regBuff, 2, 10);
		HAL_I2C_Master_Receive(GetAddressI2C_Handle(), GetHardwareAddress() << 1, data + i, 1, 10);

		regAddr++;
	}
}


void ExternalEEPROM::ClearAll (void)
{
	ui8 zeroArr [EEPROM_BLOCK_DATA_SIZE];
	memset(zeroArr, 0, EEPROM_BLOCK_DATA_SIZE);

	for (ui16 i = 0; i < 500; i++)
	{
		osDelay(10);
		WriteData(i * EEPROM_BLOCK_DATA_SIZE, zeroArr, EEPROM_BLOCK_DATA_SIZE);
	}
}
