/** ____________________________________________________________________
 *
 *	@file		internalFlash.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "internalFlash.h"


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														   Class Methods
 */
void InternalFlashHandle::Unlock (void)
{
	HAL_FLASH_Unlock();
}


void InternalFlashHandle::Lock (void)
{
	HAL_FLASH_Lock();
}


void InternalFlashHandle::SaveWord (ui32 address, ui32 word)
{
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, (ui64)word);
}


ui32 InternalFlashHandle::ReadWord (ui32 address)
{
	__IO ui32 word = *(__IO ui32*)address;
	return (ui32)word;
}


void InternalFlashHandle::EraseSector (ui32 sector, ui8 sectorsNumber)
{
	FLASH_EraseInitTypeDef EraseInit = {0};

	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
						   FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

	EraseInit.TypeErase    = FLASH_TYPEERASE_SECTORS;
	EraseInit.Sector       = sector;
	EraseInit.NbSectors    = sectorsNumber;
	EraseInit.VoltageRange = voltageRange;

	if (HAL_FLASHEx_Erase(&EraseInit, &sectorError) != HAL_OK)
		HardwareErrorHandler();

	/* FLASH_Erase_Sector(sector, voltageRange); */
	osDelay(1);
}
