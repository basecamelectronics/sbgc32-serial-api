/** ____________________________________________________________________
 *
 *	@file		peripheral.h
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#ifndef		_PERIPHERAL_H_
#define		_PERIPHERAL_H_

/*  = = = = = = = = = = = = = = = = = = = = = = = */

/* Inputs */
#include	"analogInput.h"
#include	"digitalInput.h"
#include	"digitalJoystick.h"
#include	"absoluteEncoder.h"
#include	"incrementalEncoder.h"

/* Miscellaneous */
#include	"CRC32.h"
#include	"EEPROM.h"
#include	"internalFlash.h"
#include	"watchDog.h"


extern JoystickDetermineState_t joystickDetermineState;
extern Input *inputClassesArray [];


void TaskStartPeripheral (void *params);
void TaskInputsManage (void *params);


/*  = = = = = = = = = = = = = = = = = = = = = = = */

#endif		/* _PERIPHERAL_H_ */
