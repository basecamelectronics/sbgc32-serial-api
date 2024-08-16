/** ____________________________________________________________________
 *
 *	@file		ShortcutContainerM.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_SHORTCUT_CONTAINER_M_H_
#define		_SHORTCUT_CONTAINER_M_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"gfx.h"

#define		INITIAL_SHORTCUT_NUM	5				// Number of shortcuts on displayed at the same time

#define		SIDE_ARROW_IMAGE_CLEARANCE		2		// Units: pixels. Clearance from sides
#define		SIDE_ARROW_IMAGE_HEIGHT			10		// Units: pixels
#define		SIDE_ARROW_IMAGE_WIDTH			4		// Units: pixels

#define		SIDE_ARROW_IMAGE_Y_POS			((DISPLAY_HEIGHT - SIDE_ARROW_IMAGE_HEIGHT) / 2)

#define		SHORTCUT_IMAGE_SIZE				28		// Units: pixels (28 x 28)
#define		SHORTCUT_IMAGE_CLEARANCE		((DISPLAY_WIDTH / 6) - SHORTCUT_IMAGE_SIZE)

#define		DOWN_ARROW_IMAGE_CLEARANCE		6		// Units: pixels. Clearance from bottom of shortcuts
#define		DOWN_ARROW_Y_POS				((DISPLAY_HEIGHT / 2) + (SHORTCUT_IMAGE_SIZE / 2) + SELECT_ARROW_CLEARANCE)

/* Units: pixels */
#define		SHORTCUT_IMAGE_Y_POS			((DISPLAY_HEIGHT - SHORTCUT_IMAGE_SIZE) / 2)
#define		SHORTCUT_X_STEP					(SHORTCUT_IMAGE_SIZE + SHORTCUT_IMAGE_CLEARANCE)

#define		SHORTCUT_ACTIVE_BLINK_TIME		100		// Units: milliseconds
#define		SHORTCUT_MOVED_BLINK_TIME		200		// Units: milliseconds


typedef enum
{
	/* Mutually exclusive */
	SCS_NORMAL						= BIT_0_SET,	// Also used as OFF shortcut state (compatible with SCS_TURNED_ON)
	SCS_ACTIVE						= BIT_1_SET,
	SCS_NOT_ACTIVE					= BIT_2_SET,
	SCS_MOVED						= BIT_3_SET,
	SCS_TURNED_ON					= BIT_4_SET,

	/* Flag that say that shortcut needs to be redrawed */
	SCS_TRIGGER_FLAG				= 0x80

}	ShortcutCurrentStatus_t;


typedef struct
{
	ShortcutList_t			number;
	ui8						currentPosition;		// May be changed by user

	ShortcutCurrentStatus_t	status;

	const char				*imagePath;
	const char				*name;

}	ShortcutParameters_t;


class CShortcutContainerM : public CXContainer
{
	private:

		ui32				displayTimestamp;

		ui8					invertionTemp;

		ui8					currentPosition;		// Absolute position of the scroll length
		ui8					displayPosition;		// <0> | 1 | 2 | 3 | <4>

		ui8					containerStatus;		// 0 - normal | 1 - replacing

		/* Always placed by shortcutParametersReferenceArray or settings pre-setted order */
		ShortcutParameters_t
							shortcut [SHORTCUT_TOTAL_NUM];

		ShortcutCurrentStatus_t
							previousShortcutStatuses [SHORTCUT_TOTAL_NUM];

		GHandle				ghLabelSelect;
		GHandle				ghProgressbar;
		GHandle				ghImageReturn;
		GHandle				ghImageArrow;
		GHandle				ghImageShortcut [INITIAL_SHORTCUT_NUM];


	public:

		void				Init (void);
		void				vTask (void *pvParameters);
		void				OnHide (void);

		void				SaveCurrentStatuses (void)
							{
								for (ui8 i = 0; i < SHORTCUT_TOTAL_NUM; i++)
									previousShortcutStatuses[i] = shortcut[i].status;
							}

		void				ReturnPreviousStatuses (void)
							{
								for (ui8 i = 0; i < SHORTCUT_TOTAL_NUM; i++)
									SetStatusAndTrigger(&shortcut[i], previousShortcutStatuses[i]);
							}

		void				PlaceShortcut (ui8 target, ShortcutParameters_t *newShortcut);
		void				SwapShortcuts (ShortcutParameters_t *pulledShortcut, ShortcutParameters_t *nextShortcut);
		void				LeftScroll (void);
		void				RightScroll (void);
		void				UpdateShortcutsImages (void);

		void				DrawLeftArrow (sbgcBoolean_t color);
		void				DrawRightArrow (sbgcBoolean_t color);
		void				SideArrowsHandle (void);

		void				CommunicationInit (void);
		void				DisplayShortcutInit (void);
		void				ExecuteShortcutAssignedFunction (ShortcutParameters_t *shortcut);

		ShortcutParameters_t
							*FindActiveShortcut (void);
		ShortcutParameters_t
							*FindCurrentShortcut (void);
		ShortcutParameters_t
							*FindShortcut (ShortcutList_t shortcutNum);
		void				GetShortcutSortedByOrder (ShortcutParameters_t **buffShortcut);
		void				GetDisplayedShortcuts (ShortcutParameters_t **buffShortcut);

		void				ShortcutLengthProcess (void);

		bool				GetTriggerFlag (ShortcutParameters_t *shortcut) { return shortcut->status & SCS_TRIGGER_FLAG; }
		void				SetStatusAndTrigger (ShortcutParameters_t *shortcut, ShortcutCurrentStatus_t newStatus)
							{
								if (shortcut == NULL) return;
								shortcut->status = newStatus;
								shortcut->status = (ShortcutCurrentStatus_t)((ui8)shortcut->status | SCS_TRIGGER_FLAG);
							}

		void				SetTriggerFlag (ShortcutParameters_t *shortcut)
							{
								if (shortcut == NULL) return;
								shortcut->status = (ShortcutCurrentStatus_t)((ui8)shortcut->status | SCS_TRIGGER_FLAG);
							}

		void				ClearTriggerFlag (ShortcutParameters_t *shortcut)
							{
								if (shortcut == NULL) return;
								shortcut->status = (ShortcutCurrentStatus_t)((ui8)shortcut->status & ~SCS_TRIGGER_FLAG);
							}

		void				TurnOffAllShortcuts (void)
							{
								for (ui8 i = 0; i < SHORTCUT_TOTAL_NUM; i++)
									SetStatusAndTrigger(&shortcut[i], SCS_NOT_ACTIVE);

								SetStatusAndTrigger(FindShortcut(SHORTCUT_MOTOR_SWITCH), SCS_NORMAL);
							}

		void				TurnOnAllShortcuts (void)
							{
								for (ui8 i = 0; i < SHORTCUT_TOTAL_NUM; i++)
									SetStatusAndTrigger(&shortcut[i], SCS_NORMAL);

								SetStatusAndTrigger(FindShortcut(SHORTCUT_MOTOR_SWITCH), SCS_TURNED_ON);
							}


		friend void			SBGC32_CalibrationFinishSC_Callback (void *gSBGC);

};


void TaskPID_AutoTuneFinishCheck (void *params);
void TaskScriptExeFinishWait (void *params);


static inline sbgcBoolean_t IsScriptShortcut (ShortcutParameters_t *shortcut)
{
	if ((shortcut->number == SHORTCUT_SCRIPT_1) ||
		(shortcut->number == SHORTCUT_SCRIPT_2) ||
		(shortcut->number == SHORTCUT_SCRIPT_3) ||
		(shortcut->number == SHORTCUT_SCRIPT_4) ||
		(shortcut->number == SHORTCUT_SCRIPT_5))
		return sbgcTRUE;

	return sbgcFALSE;
}


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _SHORTCUT_CONTAINER_M_H_ */
