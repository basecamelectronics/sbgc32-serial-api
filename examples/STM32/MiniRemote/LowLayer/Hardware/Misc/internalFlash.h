/** ____________________________________________________________________
 *
 *	@file		internalFlash.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_INTERNAL_FLASH_H_
#define		_INTERNAL_FLASH_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"hardware.h"

/* Can be referenced from stm32f4xx_hal_flash_ex.h */
#define		HW_FLASH_VOLTAGE_RANGE	FLASH_VOLTAGE_RANGE_3


class InternalFlashHandle
{
	private:

		ui32				voltageRange;
		ui32				sectorError;

	public :

		InternalFlashHandle()
							{
								this->voltageRange = HW_FLASH_VOLTAGE_RANGE;
							}


		void				Unlock (void);
		void				Lock (void);

		void				SaveByte (ui32 address, ui8 byte);
		ui8					ReadByte (ui32 address);
		void				SaveHalfWord (ui32 address, ui16 halfWord);
		ui16				ReadHalfWord (ui32 address);
		void				SaveWord (ui32 address, ui32 word);
		ui32				ReadWord (ui32 address);

		void				EraseSector (ui32 sector, ui8 sectorsNumber);

		ui32				GetSectorError (void) { return sectorError; }

};

extern InternalFlashHandle InternalFlash;


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *									Static Functions
 */
static inline ui32 AlignCountByWord (ui32 count)
{
	return ((count / 4) * 4) + ((count % 4) ? 4 : 0);
}


static inline void FinishWordWithZeroes (ui32 *address, ui32 size)
{
	ui8 remain = size % 4;

	memset(address + size, 0, remain);
}


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _INTERNAL_FLASH_H_ */
