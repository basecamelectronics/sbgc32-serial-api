/** ____________________________________________________________________
 *
 *	@file		digitalInput.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_DIGITALINPUTS_H_
#define		_DIGITALINPUTS_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"inputs.h"

#define		TOGGLE_SWITCH_CENTER_VALUE		1
#define		TOGGLE_SWITCH_UP_VALUE			2
#define		TOGGLE_SWITCH_DOWN_VALUE		0


typedef enum
{
	DIN_2POS_SWITCH					= 0,
	DIN_3POS_SWITCH

}	DigitalInputType_t;


typedef enum
{
	DINL_DIRECT						= 0,
	DINL_INVERT

}	DigitalInputLogic_t;


class DigitalInput : public Input
{
	private :

		DigitalInputType_t	inType;
		DigitalInputLogic_t	logic;


	public :

		DigitalInput(		DigitalInputType_t	inType,
							DigitalInputLogic_t	logic,
							InputID_t ID,
							const GPIO_Channel_t *GPIO_Channel,
							ui8 pinsNum,
							InputClockFunc_t InputClockEnable,
							InputProcess_t InputProcess) : Input (ID, pinsNum, InputClockEnable, InputProcess)
							{
								this->inType		= inType;
								this->logic			= logic;

								this->GPIO_Channel	= GPIO_Channel;
							}

		void				Init (void);

		DigitalInputType_t	GetType (void) { return inType; }
		DigitalInputLogic_t	GetLogic (void) { return logic; }

};


extern DigitalInput Encoder1_Button;
extern DigitalInput Encoder2_Button;
extern DigitalInput Button1;
extern DigitalInput Button2;
extern DigitalInput ToggleSwitch1;
extern DigitalInput ToggleSwitch2;


void Encoder1_ButtonReadValue (void);
void Encoder2_ButtonReadValue (void);
void Button1_ReadValue (void);
void Button2_ReadValue (void);
void ToggleSwitch1_ReadValue (void);
void ToggleSwitch2_ReadValue (void);


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _DIGITALINPUTS_H_ */
