/** ____________________________________________________________________
 *
 *	@file		ParameterEditContainerM.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_PARAMETER_EDIT_CONTAINER_M_H_
#define		_PARAMETER_EDIT_CONTAINER_M_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"gwinMenuPref.h"

#define		PARAM_EDIT_Y_CENTER_OFFSET		(((EDIT_TITLE_TOTAL_HEIGHT - MEDIUM_FONT_HEIGHT) / 2) - 1)


class CParameterEditContainerM : public CXContainer
{
	private :

		ParameterHandle_t	*parameterHandle;

		GHandle				ghImageReturn,
							ghValueProgressbar,
							ghLabelTitle,
							ghLabelValue,
							ghLabelName;


	public :

		void				Init (void);
		void				vTask (void *pvParameters);
		void				OnHide (void);

};


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _PARAMETER_EDIT_CONTAINER_M_H_ */
