/** ____________________________________________________________________
 *
 *	@file		hardware.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_HARDWARE_H_
#define		_HARDWARE_H_

#ifdef		__cplusplus
extern 		"C" {
#endif
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"../initialConfig.h"
#include	"../../HighLayer/projectConfig.h"


/*  = = = = = = = = = = = = = = = = = = = = = = = */
/*			### Peripheral Inclusion ###		  */
/*  = = = = = = = = = = = = = = = = = = = = = = = */

#define		HW_USE_DISPLAY			sbgcON

/*  - - - - - User Defined Parameters - - - - - - */
#define		HW_USE_DIGITAL_JOYSTICK			sbgcON
	#define	HW_NUM_DIGITAL_JOYSTICKS		1

#define		HW_USE_ABS_ENCODER		sbgcON
	#define	HW_NUM_ABS_ENCODERS		1

#define		HW_USE_INC_ENCODER		sbgcON
	#define	HW_NUM_INC_ENCODERS		2

#define		HW_USE_ANALOG_CHANNELS	sbgcON
	#define	HW_NUM_ANALOG_CHANNELS	3

#define		HW_USE_DIGITAL_CHANNELS	sbgcON
	#define	HW_NUM_DIGITAL_CHANNELS	6


/*  = = = = = = = = = = = = = = = = = = = = = = = */
/*			### Low Layer Peripheral ###		  */
/*  = = = = = = = = = = = = = = = = = = = = = = = */

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									 Common Settings
 */
#define		MCU_HCLK_FREQUENCY		100000000

/*	Note: UART ---> SBGC32 hardware link produce
 *	in the <SBGC32_Driver/driver_STM32.h> file
 */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								   ST7735 LCD 80x160
 */
#if (HW_USE_DISPLAY)
	/* LCD SPI GPIO Config -------------------------
	 */
	/* LCD SPI MOSI pin */
	#define	LCD_SPI_MOSI_GPIO_PORT	GPIOA
	#define	LCD_SPI_MOSI_PIN		GPIO_PIN_7
	#define	LCD_SPI_MOSI_PIN_AF		GPIO_AF5_SPI1

	/* LCD SPI SCL pin */
	#define	LCD_SPI_SCL_GPIO_PORT	GPIOA
	#define	LCD_SPI_SCL_PIN			GPIO_PIN_5
	#define	LCD_SPI_SCL_PIN_AF		GPIO_AF5_SPI1

	#define	LCD_SPI_GPIO_CLOCK_ENABLE()		__HAL_RCC_GPIOA_CLK_ENABLE()

	/* LCD SPI Module Config -----------------------
	 */
	#define	LCD_SPI_INSTANCE		SPI1

	#define	LCD_SPI_CLOCK_ENABLE()	__HAL_RCC_SPI1_CLK_ENABLE()

	/* LCD SPI DMA Module Config -------------------
	 */
	#define	LCD_SPI_TX_DMA_STREAM	DMA2_Stream3
	#define	LCD_SPI_TX_DMA_CHANNEL	DMA_CHANNEL_3

	#define LCD_SPI_TX_DMA_CH_IRQN			DMA2_Stream3_IRQn
	#define	LCD_SPI_TX_DMA_IRQ_HANDLER		DMA2_Stream3_IRQHandler

	#define	LCD_SPI_DMA_CLOCK_ENABLE()		__HAL_RCC_DMA2_CLK_ENABLE()

	/* LCD Other Pins Config -----------------------
	 */
	/* LCD SPI CS pin */
	#define	LCD_SPI_CS_GPIO_PORT	GPIOB
	#define	LCD_SPI_CS_PIN			GPIO_PIN_1

	/* LCD SPI DC pin */
	#define	LCD_SPI_DC_GPIO_PORT	GPIOA
	#define	LCD_SPI_DC_PIN			GPIO_PIN_6

	/* LCD SPI RES pin */
	#define	LCD_SPI_RES_GPIO_PORT	GPIOB
	#define	LCD_SPI_RES_PIN			GPIO_PIN_0

	#define	LCD_GPIO_CLOCK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE();\
									__HAL_RCC_GPIOB_CLK_ENABLE();\

	/* LCD TIM Pin Config --------------------------
	 */
	/* LCD TIM PWM pin */
	#define	LCD_TIM_PWM_GPIO_PORT	GPIOA
	#define	LCD_TIM_PWM_PIN			GPIO_PIN_8
	#define	LCD_TIM_PWM_PIN_AF		GPIO_AF1_TIM1

	#define	LCD_TIM_PWM_GPIO_CLOCK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()

	/* LCD TIM Module Config -----------------------
	 */
	#define	LCD_TIM_INSTANCE		TIM1
	#define	LCD_TIM_PWM_CHANNEL		TIM_CHANNEL_1

	#define	LCD_TIM_BUS_FREQ		100000000

	#define	LCD_TIM_CLOCK_ENABLE()	__HAL_RCC_TIM1_CLK_ENABLE()
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									Digital Joystick
 */
#if (HW_USE_DIGITAL_JOYSTICK)
	/* DJoy X-Channel TIM Pin Config ---------------
	 */
	#define	DJOY_XCH_TIM_IC_GPIO_PORT		GPIOA
	#define	DJOY_XCH_TIM_IC_PIN				GPIO_PIN_0
	#define	DJOY_XCH_TIM_IC_PIN_AF			GPIO_AF1_TIM2

	#define	DJOY_XCH_TIM_GPIO_CLOCK_ENABLE()		__HAL_RCC_GPIOA_CLK_ENABLE()

	/* DJoy X-Channel TIM Module Config ------------
	 */
	#define	DJOY_XCH_TIM_INSTANCE	TIM2

	#define	DJOY_XCH_TIM_IC_CHANNEL	TIM_CHANNEL_1

	#define	DJOY_XCH_TIM_IRQN				TIM2_IRQn
	#define	DJOY_XCH_TIM_IRQ_HANDLER		TIM2_IRQHandler

	#define	DJOY_XCH_TIM_CLOCK_ENABLE()		__HAL_RCC_TIM2_CLK_ENABLE()


	/* DJoy Y-Channel TIM Pin Config ---------------
	 */
	#define	DJOY_YCH_TIM_IC_GPIO_PORT		GPIOA
	#define	DJOY_YCH_TIM_IC_PIN				GPIO_PIN_1
	#define	DJOY_YCH_TIM_IC_PIN_AF			GPIO_AF2_TIM5

	#define	DJOY_YCH_TIM_GPIO_CLOCK_ENABLE()		__HAL_RCC_GPIOA_CLK_ENABLE()

	/* DJoy Y-Channel TIM Module Config ------------
	 */
	#define	DJOY_YCH_TIM_INSTANCE	TIM5

	#define	DJOY_YCH_TIM_IC_CHANNEL	TIM_CHANNEL_2

	#define	DJOY_YCH_TIM_IRQN				TIM5_IRQn
	#define	DJOY_YCH_TIM_IRQ_HANDLER		TIM5_IRQHandler

	#define	DJOY_YCH_TIM_CLOCK_ENABLE()		__HAL_RCC_TIM5_CLK_ENABLE()
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									Absolute Encoder
 */
#if (HW_USE_ABS_ENCODER)
	/* Absolute Encoder I2C GPIO Config ------------
	 */
	/* Absolute Encoder I2C SDA pin */
	#define	ABS_ENC_I2C_SDA_GPIO_PORT		GPIOB
	#define	ABS_ENC_I2C_SDA_PIN				GPIO_PIN_9
	#define	ABS_ENC_I2C_SDA_PIN_AF			GPIO_AF4_I2C1

	/* Absolute Encoder I2C SCL pin */
	#define	ABS_ENC_I2C_SCL_GPIO_PORT		GPIOB
	#define	ABS_ENC_I2C_SCL_PIN				GPIO_PIN_8
	#define	ABS_ENC_I2C_SCL_PIN_AF			GPIO_AF4_I2C1

	#define	ABS_ENC_I2C_GPIO_CLOCK_ENABLE()	__HAL_RCC_GPIOB_CLK_ENABLE()

	/* Absolute Encoder I2C Module Config ----------
	 */
	#define	ABS_ENC_I2C_INSTANCE			I2C1

	#define	ABS_ENC_I2C_CLOCK_ENABLE()		__HAL_RCC_I2C1_CLK_ENABLE()

	#define	ABS_ENC_I2C_ADDRESS				0x40
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *						Incremental (Rotary) Encoder
 */
#if (HW_USE_INC_ENCODER)
	/* Inc Encoder 1 A-Channel TIM Pin Config ------
	 */
	#define	INC_ENC1_ACH_TIM_EM_GPIO_PORT	GPIOB
	#define	INC_ENC1_ACH_TIM_EM_PIN			GPIO_PIN_4
	#define	INC_ENC1_ACH_TIM_EM_PIN_AF		GPIO_AF2_TIM3

	#define	INC_ENC1_ACH_TIM_GPIO_CLOCK_ENABLE()	__HAL_RCC_GPIOB_CLK_ENABLE()

	/* Inc Encoder 1 B-Channel TIM Pin Config ------
	 */
	#define	INC_ENC1_BCH_TIM_EM_GPIO_PORT	GPIOB
	#define	INC_ENC1_BCH_TIM_EM_PIN			GPIO_PIN_5
	#define	INC_ENC1_BCH_TIM_EM_PIN_AF		GPIO_AF2_TIM3

	#define	INC_ENC1_BCH_TIM_GPIO_CLOCK_ENABLE()	__HAL_RCC_GPIOB_CLK_ENABLE()

	/* Inc Encoder 1 TIM Module Config -------------
	 */
	#define	INC_ENC1_TIM_INSTANCE	TIM3

	#define	INC_ENC1_TIM_CLOCK_ENABLE()		__HAL_RCC_TIM3_CLK_ENABLE()


	/* Inc Encoder 2 A-Channel TIM Pin Config ------
	 */
	#define	INC_ENC2_ACH_TIM_EM_GPIO_PORT	GPIOB
	#define	INC_ENC2_ACH_TIM_EM_PIN			GPIO_PIN_6
	#define	INC_ENC2_ACH_TIM_EM_PIN_AF		GPIO_AF2_TIM4

	#define	INC_ENC2_ACH_TIM_GPIO_CLOCK_ENABLE()	__HAL_RCC_GPIOB_CLK_ENABLE()

	/* Inc Encoder 2 B-Channel TIM Pin Config ------
	 */
	#define	INC_ENC2_BCH_TIM_EM_GPIO_PORT	GPIOB
	#define	INC_ENC2_BCH_TIM_EM_PIN			GPIO_PIN_7
	#define	INC_ENC2_BCH_TIM_EM_PIN_AF		GPIO_AF2_TIM4

	#define	INC_ENC2_BCH_TIM_GPIO_CLOCK_ENABLE()	__HAL_RCC_GPIOB_CLK_ENABLE()

	/* Inc Encoder 2 TIM Module Config -------------
	 */
	#define	INC_ENC2_TIM_INSTANCE	TIM4

	#define	INC_ENC2_TIM_CLOCK_ENABLE()		__HAL_RCC_TIM4_CLK_ENABLE()
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									 Analog Channels
 */
#if (HW_USE_ANALOG_CHANNELS)
	/* AJoy X-Channel Analog Pin Config ------------
	 */
	#define	AJOY_XCH_ADC_GPIO_PORT	GPIOA
	#define	AJOY_XCH_ADC_PIN		GPIO_PIN_0

	#define	AJOY_XCH_ADC_CHANNEL	ADC_CHANNEL_0

	/* AJoy Y-Channel Analog Pin Config ------------
	 */
	#define	AJOY_YCH_ADC_GPIO_PORT	GPIOA
	#define	AJOY_YCH_ADC_PIN		GPIO_PIN_1

	#define	AJOY_YCH_ADC_CHANNEL	ADC_CHANNEL_1

	/* Potentiometer Analog Pin Config -------------
	 */
	#define	POT_ADC_GPIO_PORT		GPIOA
	#define	POT_ADC_PIN				GPIO_PIN_4

	#define	POT_ADC_CHANNEL			ADC_CHANNEL_4

	#define	ADC_GPIO_CLOCK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()

	/* ADC Module Config ---------------------------
	 */
	#define	GENERAL_ADC_INSTANCE	ADC1

	#define	GENERAL_ADC_CLOCK_ENABLE()		__HAL_RCC_ADC1_CLK_ENABLE()

	/* ADC DMA Module Config -----------------------
	 */
	#define	GENERAL_ADC_DMA_INSTANCE		DMA2
	#define	GENERAL_ADC_DMA_CHANNEL			DMA_CHANNEL_0
	#define	GENERAL_ADC_DMA_STREAM			DMA2_Stream0

	#define GENERAL_ADC_DMA_CH_IRQN			DMA2_Stream0_IRQn
	#define	GENERAL_ADC_DMA_IRQ_HANDLER		DMA2_Stream0_IRQHandler

	#define	GENERAL_ADC_DMA_CLOCK_ENABLE()	__HAL_RCC_DMA2_CLK_ENABLE()
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									Digital Channels
 */
#if (HW_USE_DIGITAL_CHANNELS)
	/* Inc Encoder 1 Button Pin Config -------------
	 */
	#define	ENC1_BUT_GPIO_PORT		GPIOC
	#define	ENC1_BUT_PIN			GPIO_PIN_13

	/* Inc Encoder 2 Button Pin Config -------------
	 */
	#define	ENC2_BUT_GPIO_PORT		GPIOC
	#define	ENC2_BUT_PIN			GPIO_PIN_14

	/* Button 1 Pin Config -------------------------
	 */
	#define	BUT1_GPIO_PORT			GPIOB
	#define	BUT1_PIN				GPIO_PIN_15

	/* Button 2 Pin Config -------------------------
	 */
	#define	BUT2_GPIO_PORT			GPIOB
	#define	BUT2_PIN				GPIO_PIN_14

	/* Toggle Switch 1 Pin Config ------------------
	 */
	#define	TSW1_GPIO_PORT			GPIOB
	#define	TSW1_PIN				GPIO_PIN_12

	/* Toggle Switch 2 Pin Config ------------------
	 */
	#define	TSW2_GPIO_PORT			GPIOB
	#define	TSW2_PIN				GPIO_PIN_13


	#define	DIG_CH_GPIO_CLOCK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE();\
											__HAL_RCC_GPIOC_CLK_ENABLE()
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *										  CRC Module
 */
/* CRC Module Config ---------------------------
 */
#define		CRC_INSTANCE			CRC

#define		CRC32_CLOCK_ENABLE		__HAL_RCC_CRC_CLK_ENABLE()


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *											  EEPROM
 */
/* EEPROM I2C GPIO Config ------------
 */
/* EEPROM I2C SDA pin */
#define		EEPROM_I2C_SDA_GPIO_PORT		GPIOB
#define		EEPROM_I2C_SDA_PIN				GPIO_PIN_9
#define		EEPROM_I2C_SDA_PIN_AF			GPIO_AF4_I2C1

/* EEPROM I2C SCL pin */
#define		EEPROM_I2C_SCL_GPIO_PORT		GPIOB
#define		EEPROM_I2C_SCL_PIN				GPIO_PIN_8
#define		EEPROM_I2C_SCL_PIN_AF			GPIO_AF4_I2C1

#define		EEPROM_I2C_GPIO_CLOCK_ENABLE()	__HAL_RCC_GPIOB_CLK_ENABLE()

/* Absolute Encoder I2C Module Config ----------
 */
#define		EEPROM_I2C_INSTANCE		I2C1

#define		EEPROM_I2C_CLOCK_ENABLE()		__HAL_RCC_I2C1_CLK_ENABLE()

#define		EEPROM_I2C_ADDRESS		0x50


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *										 IWDG Module
 */
#define		IWDG_INSTANCE			IWDG

#define		IWDG_RELOAD_VALUE		4095

/*  - - - - - - - - - - - - - - - - - - - - - - - */


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *										Service code
 */
#if (HW_USE_DIGITAL_JOYSTICK == sbgcOFF)
	#undef	HW_NUM_DIGITAL_JOYSTICKS
	#define	HW_NUM_DIGITAL_JOYSTICKS		0
#endif

#if (HW_USE_ABS_ENCODER == sbgcOFF)
	#undef	HW_NUM_ABS_ENCODERS
	#define	HW_NUM_ABS_ENCODERS		0
#endif

#if (HW_USE_INC_ENCODER == sbgcOFF)
	#undef	HW_NUM_INC_ENCODERS
	#define	HW_NUM_INC_ENCODERS		0
#endif

#if (HW_USE_ANALOG_CHANNELS == sbgcOFF)
	#undef	HW_NUM_ANALOG_CHANNELS
	#define	HW_NUM_ANALOG_CHANNELS	0
#endif

#if (HW_USE_DIGITAL_CHANNELS == sbgcOFF)
	#undef	HW_NUM_DIGITAL_CHANNELS
	#define	HW_NUM_DIGITAL_CHANNELS	0
#endif


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *				Global GPIO-Setting Reference Object
 */
/* Peripheral Order Offsets ------------------------
 */
#define		DJOY_XCH_PRPH_OFFSET	0
#define		DJOY_YCH_PRPH_OFFSET	1
#define		DJOY_CH_PRPH_PINS_NUM	1
#define		DJOY_PRPH_PINS_NUM		2

#define		ABS_ENC_EEPROM_PRPH_OFFSET		(DJOY_XCH_PRPH_OFFSET + (HW_NUM_DIGITAL_JOYSTICKS * DJOY_PRPH_PINS_NUM))
	#define	ABS_ENC_EEPROM_PRPH_PINS_NUM	2

#define		INC_ENC_PRPH_OFFSET		(ABS_ENC_EEPROM_PRPH_OFFSET + (HW_NUM_ABS_ENCODERS * ABS_ENC_EEPROM_PRPH_PINS_NUM))
	#define	INC_ENC_PRPH_PINS_NUM	2

#define		AN_CH_PRPH_OFFSET		(INC_ENC_PRPH_OFFSET + (HW_NUM_INC_ENCODERS * INC_ENC_PRPH_PINS_NUM))
	#define	AN_CH_PRPH_PINS_NUM		3

#define		DIG_CH_PRPH_OFFSET		(AN_CH_PRPH_OFFSET + HW_NUM_ANALOG_CHANNELS)
	#define	DIG_CH_PRPH_PINS_NUM	1


/* General inputs constant that uses in most higher software layers */
#define		HW_NUM_INPUTS			((HW_NUM_DIGITAL_JOYSTICKS * DJOY_PRPH_PINS_NUM) +	\
									 (HW_NUM_ABS_ENCODERS) +	\
									 (HW_NUM_INC_ENCODERS) +	\
									 (HW_NUM_ANALOG_CHANNELS) +	\
									 (HW_NUM_DIGITAL_CHANNELS))


typedef struct
{
	ui16			pin;
	GPIO_TypeDef	*port;
	ui8				pinAF;

}	GPIO_Channel_t;


extern const GPIO_Channel_t GPIO_ReferenceArray [];


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									Static Functions
 */
static inline void HardwareErrorHandler (void)
{
	#if (PROJ_NEED_FAULT_RESET)
		NVIC_SystemReset();

	#else

		__disable_irq();

		while (1)
		{
			/* - - - - Custom Hardware Error Handler - - - - */
			;
			/* - - - - - - - - - - - - - - - - - - - - - - - */
		}

	#endif
}


static inline void SoftwareErrorHandler (void)
{
	#if (PROJ_NEED_FAULT_RESET)
		NVIC_SystemReset();

	#else

		__disable_irq();

		while (1)
		{
			/* - - - - Custom Software Error Handler - - - - */
			;
			/* - - - - - - - - - - - - - - - - - - - - - - - */
		}

	#endif
}


static inline void AllGPIO_ClockEnable (void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
}


static inline void AllGPIO_ClockDisable (void)
{
	__HAL_RCC_GPIOA_CLK_DISABLE();
	__HAL_RCC_GPIOB_CLK_DISABLE();
	__HAL_RCC_GPIOC_CLK_DISABLE();
	__HAL_RCC_GPIOH_CLK_DISABLE();
}


/*  = = = = = = = = = = = = = = = = = = = = = = = */
#ifdef 		__cplusplus
			}
#endif

#endif		/* _HARDWARE_H_ */
