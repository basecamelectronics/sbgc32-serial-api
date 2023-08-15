/** ____________________________________________________________________
 *
 *	@file		digitalJoystick.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_DIGITAL_JOYSTICK_H_
#define		_DIGITAL_JOYSTICK_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"inputs.h"


class DigitalJoystickChannel : public Input
{
	private :

		/* Driver */
		TIM_HandleTypeDef	htim;
		TIM_TypeDef			*instance;
		ui16				IC_Channel;

		InputClockFunc_t	ModuleClockEnable;


	public :

		DigitalJoystickChannel(
							TIM_TypeDef *instance,
							IRQn_Type IRQn,
							ui16 IC_Channel,
							InputID_t ID,
							const GPIO_Channel_t *GPIO_Channel,
							ui8 pinsNum,
							InputClockFunc_t InputClockEnable,
							InputClockFunc_t ModuleClockEnable,
							InputProcess_t InputProcess) : Input (ID, pinsNum, InputClockEnable, InputProcess)
							{
								this->instance			= instance;
								this->IC_Channel		= IC_Channel;
								this->IRQn				= IRQn;

								this->GPIO_Channel		= GPIO_Channel;

								this->ModuleClockEnable = ModuleClockEnable;
							}

		TIM_HandleTypeDef	*GetAddressTimHandle (void) { return &htim; }
		ui16				GetIC_Channel (void) { return IC_Channel; }

		void				Init (void);

};

extern DigitalJoystickChannel DigitalJoystickChannelX;
extern DigitalJoystickChannel DigitalJoystickChannelY;


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _DIGITAL_JOYSTICK_H_ */
