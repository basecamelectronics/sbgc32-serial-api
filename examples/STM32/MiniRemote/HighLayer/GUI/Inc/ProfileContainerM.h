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

#define		PROFILE_BUTTONS_WIDTH	35
#define		PROFILE_BUTTONS_HEIGHT	30
#define		PROFILE_BUTTONS_Y_COORD	((DISPLAY_HEIGHT / 2) - (PROFILE_BUTTONS_HEIGHT / 2) + PROFILE_BUTTONS_CLEARANCE)

#define		PROFILE_BUTTONS_CLEARANCE		10

#define		PROFILE_BUTTONS_Y_PADS	10

#define		PROFILE_BUTTON_X_STEP	(PROFILE_BUTTONS_CLEARANCE + PROFILE_BUTTONS_WIDTH)

#define		SELECT_PROFILE_ARROW_X_COORD	(DISPLAY_WIDTH / 2) - (PROFILE_BUTTONS_WIDTH / 2) - ((PROFILE_BUTTONS_WIDTH +\
											PROFILE_BUTTONS_CLEARANCE) * (SBGC_PROFILES_NUM / 2)) +\
											((PROFILE_BUTTONS_WIDTH - SELECT_ARROW_SIZE) / 2) + 1
#define		SELECT_PROFILE_ARROW_Y_COORD	((PROFILE_BUTTONS_Y_COORD - PROFILE_BUTTONS_HEIGHT) + 10)


class CProfileContainerM : public CXContainer
{
	private:

		GHandle				ghLabelProfileButtons [5],
							ghLabelProfileName,
							ghImageArrow;


	public:

		GHandle				ghImageReturn;
		GHandle				ghLabelTitle;

		void				Init (void);
		void				vTask (void *pvParameters);
		void				OnHide (void);

};

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _PROFILE_CONTAINER_M_H_ */
