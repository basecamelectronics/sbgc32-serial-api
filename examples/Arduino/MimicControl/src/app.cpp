/** ____________________________________________________________________
 *
 *	@file		app.cpp
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
void ReadADC_Inputs (InputsInfo_t *inputsInfo)
{
	inputsInfo->_curChannel = 0;
	inputsInfo->ADC_INx[inputsInfo->_curChannel++] = analogRead(JOY_X_ANALOG_PIN);
	inputsInfo->ADC_INx[inputsInfo->_curChannel++] = analogRead(JOY_Y_ANALOG_PIN);
}


ui8 ReadButtonState (ui8 pin)
{
	return digitalRead(pin);
}

/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ */
/*					https://www.basecamelectronics.com  			  */
/* __________________________________________________________________ */
