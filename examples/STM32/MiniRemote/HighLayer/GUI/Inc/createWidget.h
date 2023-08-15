/** ____________________________________________________________________
 *
 *	@file		createWidget.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_CREATE_WIDGET_H_
#define		_CREATE_WIDGET_H_

#ifdef		__cplusplus

#include	"gfx.h"
#include	"menuStructure.h"
#include	"colors.h"
#include	"imagePaths.h"
#include	"system.h"
#include	"printf.h"
#include	"src/gwin/gwin_class.h"
#include	"gwinImgW.h"

#define		STATE_LIFO_MASK			(STATE_LIFO_SIZE - 1)


class CCreateWidget
{
	public:

		static GListener	gl;

		static void			ClearContainerArea (GHandle ghContainer);
		static void			Init (void);
		static void			PreInit (void);

};


class CXContainer
{
	public:

		GHandle				ghContainer;
		xTaskHandle			pxTask;

		virtual void		vTask (void *pvParameters) { unused_(pvParameters); }
		virtual void		OnHide (void) { ; }
		virtual void		Init (void) { ; }
		virtual void		OnShow (ui32 Param) { ; }

		GHandle				&GetContainer (void) { return ghContainer; }

};


#include	"AdjVarEditContainerM.h"
#include	"ControlContainerM.h"
#include	"DebugConsoleContainerM.h"
#include	"MainChoiceContainerM.h"
#include	"MenuContainerM.h"
#include	"MessageWindowContainerM.h"
#include	"ParameterEditContainerM.h"
#include	"PotentiometerCalibContainerM.h"
#include	"ProfileContainerM.h"
#include	"SBGCInfoContainerM.h"
#include	"ShortcutContainerM.h"
#include	"StickCalibContainerM.h"


struct sDevState
{
	ui8 state;
	ui32 Param;

};


class CStateManager
{
	private :

		static ui8 stateStart;
		static ui8 stateEnd;
		static sDevState stateArr [STATE_LIFO_SIZE];
		static sDevState menuRoot;
		static sDevState currentState;

		static void LIFO_Clear (void) { stateStart = 0; stateEnd = 0; }

		static void LIFO_Add (sDevState &value)
		{
			if ((value.state == menuRoot.state) &&
				(value.Param == menuRoot.Param))
				LIFO_Clear();

			else
			{
				/* LIFO is full? */
				if (LIFO_Count() == (STATE_LIFO_SIZE - 1))
					stateStart = (stateStart + 1) & STATE_LIFO_MASK;

				stateArr[stateEnd] = value;
				stateEnd = (stateEnd + 1) & STATE_LIFO_MASK;
			}
		}

		static void LIFO_Remove (sDevState& value)
		{
			/* LIFO is empty? */
			if (stateEnd == stateStart)
				value = menuRoot;

			else
			{
				stateEnd = (stateEnd - 1) & STATE_LIFO_MASK;
				value = stateArr[stateEnd];

				if (value.state == menuRoot.state)
					LIFO_Clear();
			}
		}

		static ui8 LIFO_Count (void) { return ((stateEnd - stateStart) & STATE_LIFO_MASK); }

		static xQueueHandle xQueueSwitchState;
		static void vTaskSetState (void *pvParameters);

		static CXContainer *GetContainer (ui8 state);


	public :

		static void Init ();
		static void SetState (sDevState State);
		static void SetStateDirectly (sDevState State);
		static ui8 GetCurrentState () { return currentState.state; }

		static void ExeFunction (ui8 FuncID, ui32 param)
		{
			switch (FuncID)
			{
				case FUNC_SET_STATE:
					SetState((sDevState){ (ui8)param, 0 });
					break;

				default:
					break;
			}
		}

};


extern CAdjVarEditContainerM exCAdjVarEditContainerM;
extern CControlContainerM exCControlContainerM;
extern CDebugConsoleContainerM exDebugConsoleContainerM;
extern CMainChoiceContainerM exCMainChoiceContainerM;
extern CMenuContainerM exCMenuContainerM;
extern CMessageWindowContainerM exCMessageWindowContainerM;
extern CParameterEditContainerM exCParameterEditContainerM;
extern CPotentiometerCalibContainerM exCPotentiometerCalibContainerM;
extern CProfileContainerM exCProfileContainerM;
extern CSBGCInfoContainerM exCSBGCInfoContainerM;
extern CStickCalibContainerM exCStickCalibContainerM;
extern CShortcutContainerM exCShortcutContainerM;

#endif		/* __cplusplus */


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _CREATE_WIDGET_H_ */
