/** ____________________________________________________________________
 *
 *	@file		watchDog.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_WATCH_DOG_H_
#define		_WATCH_DOG_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"hardware.h"


class WatchDogHandle
{
	private :

		IWDG_TypeDef		*instance;
		IWDG_HandleTypeDef	hiwdg;

		ui32				reloadValue;

	public :

		WatchDogHandle(		IWDG_TypeDef *instance,
							ui32 reloadValue)
							{
								this->instance = instance;

								this->reloadValue = reloadValue;
							}

		void				Init (void);
		void				Refresh (void);

};

extern WatchDogHandle WatchDog;


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _WATCH_DOG_H_ */
