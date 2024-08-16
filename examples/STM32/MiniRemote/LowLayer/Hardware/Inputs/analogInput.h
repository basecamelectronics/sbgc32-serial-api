/** ____________________________________________________________________
 *
 *	@file		analogInput.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_ANALOG_INPUTS_H_
#define		_ANALOG_INPUTS_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"inputs.h"

#define		ANALOG_VALUES_AVERAGE	16

#define		ANALOG_IN_MIDDLE_VALUE	2048
#define		ANALOG_IN_MAX_VALUE		4095


typedef enum
{
	ADC_INIT_FINISHED				= 0,
	ADC_DEINITED

}	ADC_InitState_t;


class AnalogInput : public Input
{
	private :

		ui32				analogChannel;


	public :

		/* Driver */
		static ADC_HandleTypeDef
							hadc;

		static ADC_TypeDef
							*instance;

		static InputClockFunc_t
							ModuleClockEnable;

		static DMA_HandleTypeDef
							hdma;

		static DMA_Stream_TypeDef
							*DMA_Stream;

		static InputClockFunc_t
							DMA_ClockEnable;

		static ui32			DMA_Channel;

		static ADC_InitState_t
							initFlag;

		/* Other */
		static ui8			channelsNum;
		static volatile ui16
							*anValue;

		static InputClockFunc_t
							InputsClockEnable;

		AnalogInput(		ui32 analogChannel,
							InputID_t ID,
							const GPIO_Channel_t *GPIO_Channel,
							ui8 pinsNum,
							InputProcess_t InputProcess) : Input (ID, pinsNum, NULL, InputProcess)
							{
								this->analogChannel	= analogChannel;

								this->GPIO_Channel	= GPIO_Channel;
							}

		void				Init (void);

		ui32				GetAnalogChannel (void) { return analogChannel; }

};

extern AnalogInput Potentiometer;
extern AnalogInput AnalogJoystickChannelX;
extern AnalogInput AnalogJoystickChannelY;


void AnalogJoystickX_ChannelReadValue (void);
void AnalogJoystickY_ChannelReadValue (void);
void PotentiometerReadValue (void);


/* Note: input: 0 --> 4095; output: from 300 degree to 240 degree */
static inline double ConvertPotentiometerValueToAngle (ui16 value)
{
	/* 240.0 degree is first part of potentiometer turn */

	double potFullTurn = ((300.0 / 360.0) * 4096.0);

	if (value < potFullTurn)
		return 240.0 - (value / (potFullTurn / 240.0));

	else
		return 360.0 - ((value - potFullTurn) / (potFullTurn / 240.0));
}


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _ANALOG_INPUTS_H_ */
