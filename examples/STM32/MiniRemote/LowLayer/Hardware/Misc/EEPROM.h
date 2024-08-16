/** ____________________________________________________________________
 *
 *	@file		EEPROM.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_EEPROM_H_
#define		_EEPROM_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"inputs.h"

#define		EEPROM_BLOCK_DATA_SIZE	64


class ExternalEEPROM : public Input
{
	private :

		/* Driver */
		I2C_HandleTypeDef	hi2c;
		I2C_TypeDef			*instance;

		InputClockFunc_t	ModuleClockEnable;

		/* Other */
		ui8					hardwareAddress;


	public :

		ExternalEEPROM(		I2C_TypeDef *instance,
							ui8 hardwareAddress,
							InputID_t ID,
							const GPIO_Channel_t *GPIO_Channel,
							ui8 pinsNum,
							InputClockFunc_t InputClockEnable,
							InputClockFunc_t ModuleClockEnable) : Input (ID, pinsNum, InputClockEnable, NULL)
							{
								this->instance			= instance;
								this->hardwareAddress	= hardwareAddress;

								this->GPIO_Channel		= GPIO_Channel;

								this->ModuleClockEnable = ModuleClockEnable;
							}

		I2C_HandleTypeDef	*GetAddressI2C_Handle (void) { return &hi2c; }
		ui8					GetHardwareAddress (void) { return hardwareAddress; }

		void				Init (void);

		void				WriteByte (ui16 regAddr, ui8 byte);
		void				ReadByte (ui16 regAddr, ui8 *byte);
		void				WriteData (ui16 regAddr, ui8 *data, ui8 size);
		void				ReadData (ui16 regAddr, ui8 *data, ui16 size);
		void				ClearAll (void);

};

extern ExternalEEPROM EEPROM;


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _EEPROM_H_ */
