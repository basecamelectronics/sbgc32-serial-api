/** ____________________________________________________________________
 *
 *	@file		AdjVarEditContainerM.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_ADJ_VAR_EDIT_CONTAINER_M_H_
#define		_ADJ_VAR_EDIT_CONTAINER_M_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"gfx.h"

#define		ADJVAR_EDIT_Y_CENTER_OFFSET		1

#define		AVEC_VALUE_BUFF_SIZE	7
#define		AVEC_NAME_BUFF_SIZE		25

#define		ADJVAR_LOCK_VALUE		32767			// Now, only for FRAME_HEADING_ANGLE


typedef enum
{
	AVES_EDIT_VALUE					= 0,
	AVES_EDIT_MIN,
	AVES_EDIT_MAX

}	AdjVarEditState_t;


class CAdjVarEditContainerM : public CXContainer
{
	private :

		GHandle				ghImageReturn,
							ghImageEdit,
							ghImageAdd,
							ghImageRemove,
							ghValueProgressbar,
							ghLabelTitle,
							ghLabelValue,
							ghLabelMinValue,
							ghLabelMaxValue,
							ghLabelName;

		char				valueBuff [AVEC_VALUE_BUFF_SIZE],
							nameBuff [AVEC_NAME_BUFF_SIZE],
							minBuff [AVEC_VALUE_BUFF_SIZE],
							maxBuff [AVEC_VALUE_BUFF_SIZE];

		AdjVarEditState_t	editState;


	public:

		void				Init (void);
		void				vTask (void *pvParameters);
		void				OnHide (void);

		void				Redraw (void);
		void				ValueToggle (void);

};


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _ADJ_VAR_EDIT_CONTAINER_M_H_ */
