/** ____________________________________________________________________
 *
 *	@file		CRC32.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "CRC32.h"


CRC_HardwareHandler CRC32_Module(CRC_INSTANCE);


void CRC_HardwareHandler::Init (void)
{
	CRC32_CLOCK_ENABLE;

	hcrc.Instance = instance;

	if (HAL_CRC_Init(&hcrc) != HAL_OK)
		HardwareErrorHandler();
}


ui32 CRC_HardwareHandler::CalculateCRC32 (ui32 *buff, ui16 size)
{
	return HAL_CRC_Calculate(&hcrc, buff, size);
}


