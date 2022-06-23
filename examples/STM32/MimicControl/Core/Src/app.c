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
