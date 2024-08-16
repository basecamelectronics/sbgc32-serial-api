/** ____________________________________________________________________
 *
 *	@file		absoluteEncoder.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "absoluteEncoder.h"
#include "EEPROM.h"


AbsoluteEncoderI2C AbsoluteEncoder(	ABS_ENC_I2C_INSTANCE,
									ABS_ENC_I2C_ADDRESS,
									AED_COUNTER_CLOCKWISE,
									PRPH_ABSOLUTE_ENCODER_EEPROM,
									&GPIO_ReferenceArray[ABS_ENC_EEPROM_PRPH_OFFSET],
									ABS_ENC_EEPROM_PRPH_PINS_NUM,
									lambdafunc_(ABS_ENC_I2C_GPIO_CLOCK_ENABLE()),
									lambdafunc_(ABS_ENC_I2C_CLOCK_ENABLE()),
									AbsoluteEncoderReadAngle);


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														   Class Methods
 */
void AbsoluteEncoderI2C::Init (void)
{
	#if (LOADER_USE_EXTERNAL_EEPROM)
		hi2c = *EEPROM.GetAddressI2C_Handle();
	#else

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


	#endif

	SetState(IN_ON);
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														  Free Functions
 */
void AbsoluteEncoderReadAngle (void)
{
	if (AbsoluteEncoder.GetAddressI2C_Handle()->Lock != HAL_UNLOCKED)
		return;

	ui8 regAddr [2] = { AS5048_ANGLE_REG_MB, AS5048_ANGLE_REG_LB };
	ui8 data [2];

	HAL_I2C_Master_Transmit(AbsoluteEncoder.GetAddressI2C_Handle(), AbsoluteEncoder.GetHardwareAddress() << 1, regAddr, 2, 1);

	if (HAL_I2C_Master_Receive(AbsoluteEncoder.GetAddressI2C_Handle(), AbsoluteEncoder.GetHardwareAddress() << 1, data, 2, 1) != HAL_OK)
	{
		HAL_I2C_DeInit(AbsoluteEncoder.GetAddressI2C_Handle());
		osDelay(5);

		#if (LOADER_USE_EXTERNAL_EEPROM)

			EEPROM.Init();
			osDelay(1);
			*AbsoluteEncoder.GetAddressI2C_Handle() = *EEPROM.GetAddressI2C_Handle();

		#else
			AbsoluteEncoder.Init();
			osDelay(1);
		#endif

		return;
	}

	if (AbsoluteEncoder.GetDirection() == AED_CLOCKWISE)
		AbsoluteEncoder.SetValue((((ui16)data[0] << 6) & 0x3FC0) | ((ui16)data[1] & 0x00C0));

	else
		AbsoluteEncoder.SetValue((AS5048_FULL_TURN_VALUE - (((ui16)data[0] << 6) & 0x3FC0)) | ((ui16)data[1] & 0x00C0));
}
