/** ____________________________________________________________________
 *
 *	@file		SBGCInfoContainerM.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_SBGC_INFO_CONTAINER_M_H_
#define		_SBGC_INFO_CONTAINER_M_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"gfx.h"
#include	"gimbal.h"

#define		SBGC_MENU_ADJVARS_ADD_FUNC_NUM	3		// Quantity of service function in an Adjvars Data menu


typedef enum
{
	SBGC_MENU_ROOT					= 0,
	SBGC_MENU_BOARD_INFO,
	SBGC_MENU_REALTIME_DATA,
	SBGC_MENU_ADJVARS_DATA,
	SBGC_MENU_OTHER_ADJVARS_DATA,
	SBGC_MENU_RC_INPUTS,
	SBGC_MENU_CONTROL_PROFILES,
	SBGC_MENU_DEBUG_CONSOLE,

	SBGC_MENU_CONTROL_HANDLERS,

	SBGC_MENU_CONTROL_HANDLER_SETTINGS,

	SBGC_MENU_CONTROL_ATTACHED_AXIS,
	SBGC_MENU_CONTROL_MODE

}	GimbalMenuState_t;


typedef struct
{
	AdjVarGeneral_t	buffEditedAdjVar;

	ui8		activeAdjVarsCount;
	bool	activeAdjVarFlag [ADJ_VARS_QUANTITY];

	bool	needUpdateActiveAdjVarsN_Select;

}	AdjVarsMenu_t;


class CSBGCInfoContainerM : public CXContainer
{
	private :

		static GimbalMenuState_t
							menuCurrentState;


	public:

		CSBGCInfoContainerM (void) : PrefMenu(0) {}

		GHandle				ghMenu;
		sPrefMenu			*PrefMenu;
		uint16_t			PrefMenuSize;
		GHandle				ghLabelTitle;
		GHandle				ghImageReturn,
							ghImageSync;


		static GimbalMenuState_t
							GetState (void)
							{
								return menuCurrentState;
							}

		static void			SwitchState (GimbalMenuState_t menuNewState)
							{
								menuCurrentState = menuNewState;
							}

		/* Uses in AdjVar menus */
		void				DecreaseSelectedItemNumber (void)
							{
								if (PrefMenu->nSelect != 0)
									PrefMenu->nSelect--;
							}

		void				SetSelectedItemNumber (ui8 num)
							{
								PrefMenu->nSelect = num;
							}

		void				Init (void);
		void				vTask (void *pvParameters);
		void				OnHide (void);
		bool				EnterPrefMenu (sPrefMenu *menu_path);

		void				Process (GimbalMenuState_t currentState);

};


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _SBGC_INFO_CONTAINER_M_H_ */
