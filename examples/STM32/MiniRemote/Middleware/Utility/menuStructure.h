/** ____________________________________________________________________
 *
 *	@file		menuStructure.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_MENU_STRUCTURE_H_
#define		_MENU_STRUCTURE_H_

#include	"Utils.h"


typedef enum
{
	MENU_SBGC_INFO					= 0,
	MENU_REMOTE

}	MenuTypeEnum_t;


typedef enum
{
	ITEM_TYPE_MENU					= 1,

	ITEM_TYPE_FUNCTION,
	ITEM_TYPE_ADJVAR,

	ITEM_TYPE_TEXT,
	ITEM_TYPE_VALUE,
	ITEM_TYPE_CHECKBOX,

}	ItemTypeEnum_t;


typedef enum
{
	/* System functions */
	FUNC_RESTART					= 0,
	FUNC_CLEAR_EEPROM,
	FUNC_SET_STATE,

	FUNC_SWITCH_COMMUNICATION_WAY,
	FUNC_EDIT_MIXER_INVERSION,
	FUNC_EDIT_SYSTEM_BRIGHTNESS,
	FUNC_EDIT_SYSTEM_EE_RATIO,
	FUNC_EDIT_SYSTEM_EE_TIMER,
	FUNC_EDIT_PARAMETER,							// Only software changing
	FUNC_SWITCH_AV_SYNC_PRIORITY,

	/* Gimbal functions */
	FUNC_EDIT_ADJVAR,
	FUNC_SAVE_ADJVARS_TO_GIMBAL,
	FUNC_SAVE_ADJVARS_TO_REMOTE,
	FUNC_RESET_ADJVARS,

	FUNC_EDIT_CONTROL_SPEED,
	FUNC_EDIT_CONTROL_LPF,
	FUNC_EDIT_CONTROL_SENS,
	FUNC_EDIT_CONTROL_EXP,
	FUNC_EDIT_CONTROL_INVERSION,
	FUNC_TURN_ATTACHED_AXIS,
	FUNC_TURN_CONTROL_MODE

}	FuncIdEnum_t;


enum DeviceStateEnum
{
	/* State manager service */
	PREF_MENU_STATE					= 1,
	REFRESH_THE_STATE,
	PREVIOUS_STATE,

	/* Common states */
	MAIN_CHOICE_STATE,
	CONTROL_STATE,
	MESSAGE_WINDOW_STATE,
	PARAMETER_EDIT_STATE,

	/* Menu root states */
	GIMBAL_MENU_STATE,
	REMOTE_MENU_STATE,
	PROFILE_STATE,
	SHORTCUT_STATE,

	/* Special states */
	ADJ_VAR_EDIT_STATE,
	DEBUG_CONSOLE_STATE,

	STICK_CALIB_STATE,
	POTENTIOMETER_CALIB_STATE,

};


typedef struct sMenuItem*	tMenuItem;
typedef struct sMenu*		tMenu;


#pragma pack(push, 4)

typedef struct
{
	sMenu	*Menu;
	ui16	nItems;
	ui16	nSelect;
	ui8		menuType;								// GimbalMenuState_t or RemoteMenuState_t

}	sPrefMenu;


typedef struct sMenuItem
{
	ItemTypeEnum_t	ItemType;
	const char		*pTitle;

	ui8				FuncID;
	ui32			param;

	sPrefMenu		*pSubMenu;
	sPrefMenu		*pPrevMenu;

	char			*value;

}	sMenuItem;


typedef struct sMenu
{
	const char	*pszTitle;
	tMenuItem	psItems;
	ui8			nItems;

}	sMenu;

#pragma pack(pop)


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _MENU_STRUCTURE_H_ */
