/** ____________________________________________________________________
 *
 *	@file		absoluteEncoder.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_ABSOLUTE_ENCODER_H_
#define		_ABSOLUTE_ENCODER_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"inputs.h"

#define		AS5048_ANGLE_REG_MB		0xFEU
#define		AS5048_ANGLE_REG_LB		0xFFU

#define		AS5048_MAX_DISPERSION	80U				// 80U without averaging

#define		AS5048_FULL_TURN_VALUE	16384U
#define		AS5048_HALF_TURN_VALUE	(AS5048_FULL_TURN_VALUE / 2.0F)

/* Math coefficient for filter function */
#define		AS5048_NONLINEAR_SENSITIVITY	1.3


typedef enum
{
	AED_CLOCKWISE					= 0,
	AED_COUNTER_CLOCKWISE

}	AbsoluteEncoderDirection_t;


class AbsoluteEncoderI2C : public Input
{
	private :

		/* Driver */
		I2C_HandleTypeDef	hi2c;
		I2C_TypeDef			*instance;

		InputClockFunc_t	ModuleClockEnable;

		/* Other */
		ui8					hardwareAddress;

		AbsoluteEncoderDirection_t
							direction;


	public :

		AbsoluteEncoderI2C(	I2C_TypeDef *instance,
							ui8 hardwareAddress,
							AbsoluteEncoderDirection_t direction,
							InputID_t ID,
							const GPIO_Channel_t *GPIO_Channel,
							ui8 pinsNum,
							InputClockFunc_t InputClockEnable,
							InputClockFunc_t ModuleClockEnable,
							InputProcess_t InputProcess) : Input (ID, pinsNum, InputClockEnable, InputProcess)
							{
								this->instance			= instance;
								this->hardwareAddress	= hardwareAddress;
								this->direction			= direction;

								this->GPIO_Channel		= GPIO_Channel;

								this->ModuleClockEnable = ModuleClockEnable;
							}

		I2C_HandleTypeDef	*GetAddressI2C_Handle (void) { return &hi2c; }
		ui8					GetHardwareAddress (void) { return hardwareAddress; }

		AbsoluteEncoderDirection_t
							GetDirection (void) { return direction; }

		void				Init (void);

};

extern AbsoluteEncoderI2C AbsoluteEncoder;


void AbsoluteEncoderReadAngle (void);


static inline i32 FilterEncoderValue (ui16 oldValue, ui16 newValue, float divider)
{
	/* Important note: encoder turn don't must exceeds AS5048_HALF_TURN_VALUE */
	i32 delta = newValue - oldValue;
	ui16 deltaABS = abs(delta);

	float deltaFeedbackCoeff = 0;

	/* Check */
	if ((deltaABS < AS5048_MAX_DISPERSION) || (deltaABS > AS5048_HALF_TURN_VALUE))
		return 0;

	/* Result */
	else
	{
		deltaFeedbackCoeff = pow((AS5048_HALF_TURN_VALUE / deltaABS), AS5048_NONLINEAR_SENSITIVITY);
		return (((deltaABS / divider) > 1.0F) ? ((delta * deltaFeedbackCoeff) / divider) : ((delta > 0) ? 1 : -1));
	}
}


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _ABSOLUTE_ENCODER_H_ */
