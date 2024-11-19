/** ____________________________________________________________________
 *
 *	@file		StickCalibContainerM.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_STICK_CALIB_CONTAINER_M_H_
#define		_STICK_CALIB_CONTAINER_M_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"gfx.h"

#define		STICK_CALIB_BOUNDS_PASS_TIME	2000	// Units: ms
#define		STICK_CALIB_ORIGIN_PASS_TIME	1000	// Units: ms


class CStickCalibContainerM : public CXContainer
{
	private:

		GHandle				ghJoystickVisual,
							ghImageReturn,
							ghLabelStatus,
							ghLabelPercentY;

		i16					joyY_Temp;


	public:

		void				Init (void);
		void				vTask (void *pvParameters);
		void				OnHide (void);

};

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _STICK_CALIB_CONTAINER_M_H_ */
