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

#ifndef		_POTENTIOMETER_CALIB_CONTAINER_M_H_
#define		_POTENTIOMETER_CALIB_CONTAINER_M_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"gfx.h"


typedef enum
{
	PCPS_ZERO_CALIB					= 0,
	PCPS_MIN_CALIB					= 1,
	PCPS_MAX_CALIB					= 2,
	PCPS_WAIT_FINISH				= 3

}	PotCalibProcessState_t;


class CPotentiometerCalibContainerM : public CXContainer
{
	private:

		GHandle				ghPotentiometerVisual,
							ghLabelStatus,
							ghImageReturn,
							ghLabelPercent;

		PotCalibProcessState_t
							calibState;


	public:

		void				Init (void);
		void				vTask (void *pvParameters);
		void				OnHide (void);

};


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _POTENTIOMETER_CALIB_CONTAINER_M_H_ */
