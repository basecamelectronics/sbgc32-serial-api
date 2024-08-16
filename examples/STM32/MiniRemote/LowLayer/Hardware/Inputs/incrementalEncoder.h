/** ____________________________________________________________________
 *
 *	@file		incrementalEncoder.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_INCREMENTAL_ENCODER_H_
#define		_INCREMENTAL_ENCODER_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"inputs.h"

#define		INCREMENTAL_ENCODER_MAX_VALUE	16383

#define		INCREMENTAL_ENCODER_LOGIC		-1 : 1	// Without braces


class IncrementalEncoder : public Input
{
	private :

		/* Driver */
		TIM_HandleTypeDef	htim;
		TIM_TypeDef			*instance;

		InputClockFunc_t	ModuleClockEnable;


	public:

		IncrementalEncoder(	TIM_TypeDef *instance,
							InputID_t ID,
							const GPIO_Channel_t *GPIO_Channel,
							ui8 pinsNum,
							InputClockFunc_t InputClockEnable,
							InputClockFunc_t ModuleClockEnable,
							InputProcess_t InputProcess) : Input (ID, pinsNum, InputClockEnable, InputProcess)
							{
								this->instance			= instance;

								this->GPIO_Channel		= GPIO_Channel;

								this->ModuleClockEnable	= ModuleClockEnable;
							}

		TIM_HandleTypeDef	*GetAddressTimHandle (void) { return &htim; }

		void				Init (void);

};

extern IncrementalEncoder LeftIncrementalEncoder;
extern IncrementalEncoder RightIncrementalEncoder;


void LeftIncrementalEncoderReadCount (void);
void RightIncrementalEncoderReadCount (void);


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _INCREMENTAL_ENCODER_H_ */
