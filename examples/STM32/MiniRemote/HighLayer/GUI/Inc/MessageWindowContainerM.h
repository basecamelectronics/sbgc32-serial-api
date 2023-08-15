/** ____________________________________________________________________
 *
 *	@file		MessageWindowContainerM.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_MESSAGE_WINDOW_CONTAINER_M_H_
#define		_MESSAGE_WINDOW_CONTAINER_M_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"gfx.h"

#define		MESSAGE_WINDOW_MARGINS			0


typedef enum
{
	/* Common */
	MW_DIALOG_STATE					= 0,
	MW_NOTE_STATE,

	/* Service */
	MW_GIMBAL_ACC_CALIB_STATE,
	MW_GIMBAL_GYRO_CALIB_STATE,
	MW_GIMBAL_PID_TUNE_STATE,
	MW_GIMBAL_INIT_OK_STATE

}	MessageWindowState_t;


typedef enum
{
	MW_SMALL_FONT					= 0,
	MW_MEDIUM_FONT,
	MW_LARGE_FONT

}	MessageWindowFont_t;


typedef enum
{
	MWDA_CLEANED					= 0,
	MWDA_YES,
	MWDA_NO

}	MessageWindowDialogAnswer_t;


class CMessageWindowContainerM : public CXContainer
{
	private :

		GHandle				ghProgressbar;
		GHandle				ghImageReturn;

		char				*message;
		MessageWindowState_t
							currentState;
		MessageWindowFont_t	font;
		ui32				timeout;


	public :

		void				Init (void);
		void				OnHide (void);
		void				vTask (void *pvParameters);

		void				SetMessage (const char *message, ui8 messageLength, MessageWindowState_t messageType,
										MessageWindowFont_t messageFont, ui32 messageTime);
		void				ClearMessage (void);

		void				SetCurrentState (MessageWindowState_t newState) { currentState = newState; }
		MessageWindowState_t
							GetCurrentState (void) { return currentState; }

};


extern MessageWindowDialogAnswer_t dialogAnswer;


#endif		/* _MESSAGE_WINDOW_CONTAINER_M_H_ */
