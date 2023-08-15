/** ____________________________________________________________________
 *
 *	@file		watchDog.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "watchDog.h"


WatchDogHandle WatchDog(IWDG_INSTANCE,
						IWDG_RELOAD_VALUE);


/* ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *														   Class Methods
 */
void WatchDogHandle::Init (void)
{
	hiwdg.Instance = instance;

	hiwdg.Init.Prescaler	= IWDG_PRESCALER_32;
	hiwdg.Init.Reload		= reloadValue;

	if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
		HardwareErrorHandler();
}


void WatchDogHandle::Refresh (void)
{
	HAL_IWDG_Refresh(&hiwdg);
}
