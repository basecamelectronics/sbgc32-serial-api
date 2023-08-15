/** ____________________________________________________________________
 *
 *	@file		analogInput.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include  "analogInput.h"


ADC_HandleTypeDef	AnalogInput::hadc;
ADC_TypeDef			*AnalogInput::instance			= GENERAL_ADC_INSTANCE;
InputClockFunc_t	AnalogInput::ModuleClockEnable	= lambafunc_(GENERAL_ADC_CLOCK_ENABLE());
DMA_HandleTypeDef	AnalogInput::hdma;
DMA_Stream_TypeDef	*AnalogInput::DMA_Stream		= GENERAL_ADC_DMA_STREAM;
InputClockFunc_t	AnalogInput::DMA_ClockEnable	= lambafunc_(GENERAL_ADC_DMA_CLOCK_ENABLE());
ui32				AnalogInput::DMA_Channel		= GENERAL_ADC_DMA_CHANNEL;
ADC_InitState_t		AnalogInput::initFlag			= ADC_DEINITED;
ui8					AnalogInput::channelsNum		= HW_NUM_ANALOG_CHANNELS;
volatile ui32		*AnalogInput::anValue			= (ui32*)osMalloc(sizeof(ui32) * HW_NUM_ANALOG_CHANNELS * ANALOG_VALUES_AVERAGE);
InputClockFunc_t	AnalogInput::InputsClockEnable	= lambafunc_(ADC_GPIO_CLOCK_ENABLE());


AnalogInput Potentiometer(	POT_ADC_CHANNEL,
							PRPH_POTENTIOMETER,
						  	&GPIO_ReferenceArray[AN_CH_PRPH_OFFSET],
							AN_CH_PRPH_PINS_NUM,
							PotentiometerReadValue);


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														   Class Methods
 */
void AnalogInput::Init (void)
{
	if (initFlag == ADC_DEINITED)
	{
		ADC_ChannelConfTypeDef sConfig = {0};
		GPIO_InitTypeDef GPIO_InitStruct = {0};

		DMA_ClockEnable();

		hdma.Instance = DMA_Stream;
		hdma.Init.Channel				= DMA_Channel;
		hdma.Init.FIFOMode				= DMA_FIFOMODE_DISABLE;
		hdma.Init.FIFOThreshold			= DMA_FIFO_THRESHOLD_HALFFULL;
		hdma.Init.MemBurst				= DMA_MBURST_SINGLE;
		hdma.Init.PeriphBurst			= DMA_PBURST_SINGLE;
		hdma.Init.Direction				= DMA_PERIPH_TO_MEMORY;
		hdma.Init.PeriphInc				= DMA_PINC_DISABLE;
		hdma.Init.MemInc				= DMA_MINC_ENABLE;
		hdma.Init.PeriphDataAlignment	= DMA_PDATAALIGN_HALFWORD;
		hdma.Init.MemDataAlignment		= DMA_MDATAALIGN_HALFWORD;
		hdma.Init.Mode					= DMA_CIRCULAR;
		hdma.Init.Priority				= DMA_PRIORITY_HIGH;

		if (HAL_DMA_Init(&hdma) != HAL_OK)
			HardwareErrorHandler();

		/* Associate the initialized DMA handle to the ADC handle */
		__HAL_LINKDMA(&hadc, DMA_Handle, hdma);

		HAL_NVIC_SetPriority(GENERAL_ADC_DMA_CH_IRQN, 9, 0);
		HAL_NVIC_EnableIRQ(GENERAL_ADC_DMA_CH_IRQN);

		ModuleClockEnable();

		hadc.Instance = instance;

		hadc.Init.ClockPrescaler		= ADC_CLOCKPRESCALER_PCLK_DIV4;
		hadc.Init.Resolution			= ADC_RESOLUTION_12B;
		hadc.Init.ExternalTrigConvEdge	= ADC_EXTERNALTRIGCONVEDGE_NONE;
		hadc.Init.ExternalTrigConv		= ADC_EXTERNALTRIGCONV_T1_CC1;
		hadc.Init.DiscontinuousConvMode	= DISABLE;
		hadc.Init.DMAContinuousRequests	= ENABLE;
		hadc.Init.EOCSelection			= DISABLE;
		hadc.Init.ScanConvMode			= ENABLE;
		hadc.Init.ContinuousConvMode	= ENABLE;
		hadc.Init.NbrOfDiscConversion	= 0;
		hadc.Init.DataAlign				= ADC_DATAALIGN_RIGHT;
		hadc.Init.NbrOfConversion		= channelsNum;

		if (HAL_ADC_Init(&hadc) != HAL_OK)
			HardwareErrorHandler();

		sConfig.SamplingTime	= ADC_SAMPLETIME_480CYCLES;
		sConfig.Offset			= 0;
		sConfig.Rank			= 0;

		/* Initialize all inputs together */
		InputsClockEnable();

		for (ui8 i = 0; i < channelsNum; i++)
		{
			sConfig.Channel = analogChannel;
			sConfig.Rank++;

			if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
				HardwareErrorHandler();

			/* ADC Channel GPIO pin configuration */
			GPIO_InitStruct.Pin = GPIO_Channel[i].pin;
			GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			HAL_GPIO_Init(GPIO_Channel[i].port, &GPIO_InitStruct);
		}

		initFlag = ADC_INIT_FINISHED;
	}

	if (HAL_ADC_Start_DMA(&hadc, (ui32*)anValue, channelsNum * ANALOG_VALUES_AVERAGE) != HAL_OK)
		HardwareErrorHandler();


	SetState(IN_ON);
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														  Free Functions
 */
void PotentiometerReadValue (void)
{
	ui32 potentiometerAverageValue = 0;

	for (ui8 i = 0; i < ANALOG_VALUES_AVERAGE; i++)
		potentiometerAverageValue += (ui16)(AnalogInput::anValue[i] & 0x0000FFFF);

	potentiometerAverageValue /= ANALOG_VALUES_AVERAGE;

	Potentiometer.SetValue(AnalogInput::anValue[0]);
}
