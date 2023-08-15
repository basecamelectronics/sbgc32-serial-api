/** ____________________________________________________________________
 *
 *	@file		DebugConsoleContainerM.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_DEBUG_CONSOLE_CONTAINER_M_H_
#define		_DEBUG_CONSOLE_CONTAINER_M_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

#include	"gfx.h"


class CDebugConsoleContainerM : public CXContainer
{
	public :

		xSemaphoreHandle	xSemaphoreDebugConsole;

		void				ClearConsoleBuffer (void);

		void				Init (void);
		void				OnHide (void);
		void				vTask (void *pvParameters);

};


typedef struct
{
	char 		CD_Buffer [DEBUG_CONSOLE_BUFFER_SIZE];

	uint16_t	CD_BufferTail,
				CD_BufferHead,
				CD_BufferPointer;

	uint8_t		updateFlag,
				emptyFlag;

}	ConsoleData_t;


extern ConsoleData_t ConsoleData;


#endif		/* _DEBUG_CONSOLE_CONTAINER_M_H_ */
