/** ____________________________________________________________________
 *
 *	@file		app.c
 *
 *				BaseCamElectronics Team
 *
 *				Mimic Control project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "app.h"


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
		inputsInfo->_curChannel = 0;
}


ui8 ReadButtonState (__GPIO_STRUCT, ui16 pin)
{
	return READ_PIN(gpio, pin);
}

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
