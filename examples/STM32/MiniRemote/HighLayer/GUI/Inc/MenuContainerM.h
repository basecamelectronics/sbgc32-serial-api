/** ____________________________________________________________________
 *
 *	@file		MenuContainerM.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_MENU_CONTAINER_M_H_
#define		_MENU_CONTAINER_M_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"gfx.h"
#include	"menuStructure.h"

#define		ADJ_VARS_SYNC_NOTE_TEXT_HEIGHT	14
#define		ADJ_VARS_SYNC_NOTE_HEIGHT		(ADJ_VARS_SYNC_NOTE_TEXT_HEIGHT * 2)
#define		ADJ_VARS_SYNC_NOTE_Y_COORD		(DISPLAY_HEIGHT - ADJ_VARS_SYNC_NOTE_HEIGHT)


typedef enum
{
	REMOTE_MENU_ROOT				= 0,

	/* Second level */
	REMOTE_MENU_COMMUNICATION_WAY,
	REMOTE_MENU_INPUTS_REMAP,
	REMOTE_MENU_STICK_CALIBRATION,
	REMOTE_MENU_CALIBRATION,
	REMOTE_MENU_ADJ_VARS_SYNC_PRIORITY,

	REMOTE_MENU_MIX_CHANNELS,

	/* Third level */
	REMOTE_MENU_MIX_CHANNEL_SETTINGS,

	/* Fourth level */
	REMOTE_MENU_MIX_CHANNEL_SETTINGS_INPUT,
	REMOTE_MENU_MIX_CHANNEL_SETTINGS_OUTPUT

}	RemoteMenuState_t;


class CMenuContainerM : public CXContainer
{
	private :

		static RemoteMenuState_t
							menuCurrentState;


	public:

		GHandle				ghMenu;
		sPrefMenu			*PrefMenu;
		uint16_t			PrefMenuSize;
		GHandle				ghLabelTitle;
		GHandle				ghImageReturn;

		sbgcBoolean_t		oneTimeDrawObjectsFlag;


		CMenuContainerM (void) : PrefMenu(0)
							{
								oneTimeDrawObjectsFlag = sbgcFALSE;
							}

		static RemoteMenuState_t
							GetState (void)
							{
								return menuCurrentState;
							}

		static void			SwitchState (RemoteMenuState_t menuNewState)
							{
								menuCurrentState = menuNewState;
							}

		void				Init (void);
		void				vTask (void *pvParameters);
		void				OnHide (void);
		bool				EnterPrefMenu (sPrefMenu *menu_path);

		void				Process (RemoteMenuState_t currentState);

};


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _MENU_CONTAINER_M_H_ */
