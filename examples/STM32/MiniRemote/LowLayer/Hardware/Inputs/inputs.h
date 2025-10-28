/** ____________________________________________________________________
 *
 *	@file		inputs.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_INPUTS_H_
#define		_INPUTS_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"hardware.h"

#define		NO_PROCESS_FUNC			NULL

#define		IN_MIN_VALUE			0
#define		IN_MIDDLE_VALUE			32768
#define		IN_MAX_VALUE			65535

#define		VALUE_MP_14B_TO_16B		4U


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *								Common Input Objects
 */
typedef enum
{
	JDS_PROCESS						= 0,
	JDS_DIGITAL,
	JDS_ANALOG,
	JDS_ERROR

}	JoystickDetermineState_t;


typedef enum
{
	IN_ON,
	IN_NEED_INIT,
	IN_NEED_DEINIT,
	IN_OFF,

}	InputState_t;


/*	Note:	This is only auxiliary peripheral enumeration
 *			Needs for manual mixers initialization
 *
 *			It must have elements order like an inputClassesArray []
 */
typedef enum
{
	PRPH_DIGITAL_JOYSTICK_CHANNEL_X	= 0,
	PRPH_DIGITAL_JOYSTICK_CHANNEL_Y,
	PRPH_ABSOLUTE_ENCODER_EEPROM,					// They have one I2C line
	PRPH_LEFT_INCREMENTAL_ENCODER,
	PRPH_RIGHT_INCREMENTAL_ENCODER,
	PRPH_ANALOG_JOYSTICK_CHANNEL_X,
	PRPH_ANALOG_JOYSTICK_CHANNEL_Y,
	PRPH_POTENTIOMETER,
	PRPH_ENCODER1_BUTTON,
	PRPH_ENCODER2_BUTTON,
	PRPH_BUTTON1,
	PRPH_BUTTON2,
	PRPH_TOGGLE_SWITCH1,
	PRPH_TOGGLE_SWITCH2,

	/* Attention: Only for init and writing. A real empty-in mixer doesn't have this field */
	PRPH_NO_INPUT					= 255

}	PeripheralReferenceOrder_t, InputID_t;


typedef void		(*InputClockFunc_t)(void);
typedef void		(*InputProcess_t)(void);


typedef class Input
{
	private :

		ui16				value;
		InputID_t			ID;
		InputState_t		state;


	public :

		const GPIO_Channel_t
							*GPIO_Channel;

		IRQn_Type			IRQn;

		InputClockFunc_t	InputClockEnable;
		InputProcess_t		InputProcess;

		Input(				InputID_t ID,
							ui8 pinsNum,
							InputClockFunc_t InputClockEnable,
							InputProcess_t InputProcess)
							{
								this->ID		= ID;
								state			= IN_OFF;

								GPIO_Channel	= (GPIO_Channel_t*)osMalloc(sizeof(GPIO_Channel_t) * pinsNum);

								this->InputClockEnable = InputClockEnable;
								this->InputProcess = InputProcess;
							}

		virtual void		Init (void) { ; }
		virtual void		Deinit (void) { ; }

		void				SetValue (ui16 value) { this->value = value; }
		ui16				GetValue (void) { return value; }

		InputID_t			GetID (void) { return ID; }
		InputID_t			*GetAddressID (void) { return &ID; }

		void				SetState (InputState_t state) { this->state = state; }
		InputState_t		GetState (void) { return state; }

}		Input_t;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									Static Functions
 */
static inline ui16 ConvertValue14_BitTo16_Bit (ui16 value)
{
	return (value * VALUE_MP_14B_TO_16B);
}


static inline ui16 ConvertValue1_BitTo16_Bit (ui16 value)
{
	return (value ? IN_MAX_VALUE : IN_MIN_VALUE);
}


static inline ui16 ConvertValueBinary16_FlagToDecade (ui16 flag)
{
	for (ui8 i = 0; i < 16; i++)
	{
		if (flag == 1)
			return i;

		flag >>= 1;
	}

	return 0;
}


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _INPUTS_H_ */
