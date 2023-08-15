/** ____________________________________________________________________
 *
 *	@file		MainChoiceContainerM.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_MAIN_CHOICE_CONTAINER_M_H_
#define		_MAIN_CHOICE_CONTAINER_M_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"gfx.h"


class CMainChoiceContainerM : public CXContainer
{
	private :

		GHandle				ghLabel [4];
		GHandle				ghImageArrow [4];


	public:

		void				Init (void);
		void				vTask (void *pvParameters);
		void				OnHide (void);

};

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _MAIN_CHOICE_CONTAINER_M_H_ */
