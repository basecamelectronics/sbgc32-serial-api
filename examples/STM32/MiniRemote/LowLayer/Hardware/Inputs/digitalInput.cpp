/** ____________________________________________________________________
 *
 *	@file		digitalInput.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "digitalInput.h"


DigitalInput Encoder1_Button(	DIN_2POS_SWITCH,
								DINL_INVERT,
								PRPH_ENCODER1_BUTTON,
								&GPIO_ReferenceArray[DIG_CH_PRPH_OFFSET],
								DIG_CH_PRPH_PINS_NUM,
								lambafunc_(DIG_CH_GPIO_CLOCK_ENABLE()),
								Encoder1_ButtonReadValue);

DigitalInput Encoder2_Button(	DIN_2POS_SWITCH,
								DINL_INVERT,
								PRPH_ENCODER2_BUTTON,
								&GPIO_ReferenceArray[DIG_CH_PRPH_OFFSET + 1],
								DIG_CH_PRPH_PINS_NUM,
								lambafunc_(DIG_CH_GPIO_CLOCK_ENABLE()),
								Encoder2_ButtonReadValue);

DigitalInput Button1(			DIN_2POS_SWITCH,
								DINL_INVERT,
								PRPH_BUTTON1,
								&GPIO_ReferenceArray[DIG_CH_PRPH_OFFSET + 2],
								DIG_CH_PRPH_PINS_NUM,
								lambafunc_(DIG_CH_GPIO_CLOCK_ENABLE()),
								Button1_ReadValue);

DigitalInput Button2(			DIN_2POS_SWITCH,
								DINL_INVERT,
								PRPH_BUTTON2,
								&GPIO_ReferenceArray[DIG_CH_PRPH_OFFSET + 3],
								DIG_CH_PRPH_PINS_NUM,
								lambafunc_(DIG_CH_GPIO_CLOCK_ENABLE()),
								Button2_ReadValue);

DigitalInput ToggleSwitch1(		DIN_3POS_SWITCH,
								DINL_INVERT,
								PRPH_TOGGLE_SWITCH1,
								&GPIO_ReferenceArray[DIG_CH_PRPH_OFFSET + 4],
								DIG_CH_PRPH_PINS_NUM,
								lambafunc_(DIG_CH_GPIO_CLOCK_ENABLE()),
								ToggleSwitch1_ReadValue);

DigitalInput ToggleSwitch2(		DIN_3POS_SWITCH,
								DINL_INVERT,
								PRPH_TOGGLE_SWITCH2,
								&GPIO_ReferenceArray[DIG_CH_PRPH_OFFSET + 5],
								DIG_CH_PRPH_PINS_NUM,
								lambafunc_(DIG_CH_GPIO_CLOCK_ENABLE()),
								ToggleSwitch2_ReadValue);


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														   Class Methods
 */
void DigitalInput::Init (void)
{
	InputClockEnable();

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Mode	= GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull	= GPIO_PULLUP;
	GPIO_InitStruct.Pin		= GPIO_Channel->pin;
	HAL_GPIO_Init(GPIO_Channel->port, &GPIO_InitStruct);

	SetState(IN_ON);
}


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														  Free Functions
 */
static ui16 DigitalInputReadValueUni (const GPIO_Channel_t *GPIO_Channel, DigitalInputType_t digitalInputType, DigitalInputLogic_t logic)
{
	if (digitalInputType == DIN_2POS_SWITCH)
		return (HAL_GPIO_ReadPin(GPIO_Channel->port, GPIO_Channel->pin) ^ logic);

	else if (digitalInputType == DIN_3POS_SWITCH)
	{
		ui8 val;
		ui32 temp;
		ui16 offset;

		val = HAL_GPIO_ReadPin(GPIO_Channel->port, GPIO_Channel->pin);

		offset = (ConvertValueBiniry16_FlagToDecade(GPIO_Channel->pin) * 2);
		temp = GPIO_Channel->port->PUPDR;
		temp &= ~(GPIO_PUPDR_PUPDR0 << offset);
		temp |= ((GPIO_PULLDOWN) << offset);
		GPIO_Channel->port->PUPDR = temp;

		for (ui8 i = 0; i < 200; i++) __NOP();

		if (val == HAL_GPIO_ReadPin(GPIO_Channel->port, GPIO_Channel->pin))
			val = ((val ^ logic) ? TOGGLE_SWITCH_DOWN_VALUE : TOGGLE_SWITCH_UP_VALUE);

		else  // Middle position
			val = TOGGLE_SWITCH_CENTER_VALUE;

		temp = GPIO_Channel->port->PUPDR;
		temp &= ~(GPIO_PUPDR_PUPDR0 << offset);
		temp |= ((GPIO_PULLUP) << offset);
		GPIO_Channel->port->PUPDR = temp;

		return val;
	}

	else
		return 0;
}


void Encoder1_ButtonReadValue (void)
{
	Encoder1_Button.SetValue(DigitalInputReadValueUni(Encoder1_Button.GPIO_Channel, Encoder1_Button.GetType(), Encoder1_Button.GetLogic()));
}


void Encoder2_ButtonReadValue (void)
{
	Encoder2_Button.SetValue(DigitalInputReadValueUni(Encoder2_Button.GPIO_Channel, Encoder2_Button.GetType(), Encoder2_Button.GetLogic()));
}


void Button1_ReadValue (void)
{
	Button1.SetValue(DigitalInputReadValueUni(Button1.GPIO_Channel, Button1.GetType(), Button1.GetLogic()));
}


void Button2_ReadValue (void)
{
	Button2.SetValue(DigitalInputReadValueUni(Button2.GPIO_Channel, Button2.GetType(), Button2.GetLogic()));
}


void ToggleSwitch1_ReadValue (void)
{
	ToggleSwitch1.SetValue(DigitalInputReadValueUni(ToggleSwitch1.GPIO_Channel, ToggleSwitch1.GetType(), ToggleSwitch1.GetLogic()));
}


void ToggleSwitch2_ReadValue (void)
{
	ToggleSwitch2.SetValue(DigitalInputReadValueUni(ToggleSwitch2.GPIO_Channel, ToggleSwitch2.GetType(), ToggleSwitch2.GetLogic()));
}
