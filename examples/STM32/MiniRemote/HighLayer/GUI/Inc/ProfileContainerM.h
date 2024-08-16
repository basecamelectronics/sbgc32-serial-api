/** ____________________________________________________________________
 *
 *	@file		ProfileContainerM.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_PROFILE_CONTAINER_M_H_
#define		_PROFILE_CONTAINER_M_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"gfx.h"

#define		PROFILE_BUTTON_MARGINS	((DISPLAY_WIDTH / 6) - PROFILE_BUTTONS_WIDTH)
#define		PROFILE_BUTTONS_WIDTH	26
#define		PROFILE_BUTTONS_HEIGHT	20
#define		PROFILE_BUTTONS_Y_COORD	((DISPLAY_HEIGHT / 2) - (PROFILE_BUTTONS_HEIGHT / 2))

#define		PROFILE_BUTTON_X_STEP	(PROFILE_BUTTON_MARGINS + PROFILE_BUTTONS_WIDTH)

#define		SELECT_PROFILE_ARROW_X_COORD	((PROFILE_BUTTON_MARGINS + PROFILE_BUTTONS_WIDTH) - (SELECT_ARROW_SIZE / 2))
#define		SELECT_PROFILE_ARROW_Y_COORD	((PROFILE_BUTTONS_Y_COORD - PROFILE_BUTTONS_HEIGHT) + 4)


class CProfileContainerM : public CXContainer
{
	private:

		GHandle				ghLabelProfileButtons [5],
							ghLabelProfileName,
							ghImageArrow;


	public:

		void				Init (void);
		void				vTask (void *pvParameters);
		void				OnHide (void);

};

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _PROFILE_CONTAINER_M_H_ */
