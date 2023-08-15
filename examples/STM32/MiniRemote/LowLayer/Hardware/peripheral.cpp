/** ____________________________________________________________________
 *
 *	@file		peripheral.cpp
 *
 *				BaseCamElectronics Team
 *
 *				Mini-Remote Controller project
 *
 *				https://www.basecamelectronics.com
 *  ____________________________________________________________________
 */

#include "peripheral.h"


Input *inputClassesArray [] =
{
	&DigitalJoystickChannelX,
	&DigitalJoystickChannelY,
	&AbsoluteEncoder,
	&LeftIncrementalEncoder,
	&RightIncrementalEncoder,
	&Potentiometer,
	&Encoder1_Button,
	&Encoder2_Button,
	&Button1,
	&Button2,
	&ToggleSwitch1,
	&ToggleSwitch2

	/* Total members quantity must be equal HW_NUM_INPUTS */
};


void TaskStartPeripheral (void *params)
{
	/* Inputs peripheral init */
	osTaskCreate(	TaskInputsManage,
					"PeripheralManage",
					configMINIMAL_STACK_SIZE * 2,
					NULL,
					OS_HIGHEST_PRIORITY,
					NULL);

	osTaskDelete(NULL);

	while (1);
}


void TaskInputsManage (void *params)
{
	for (ui8 i = 0; i < countof_(inputClassesArray); i++)
	{
		if (inputClassesArray[i]->GetState() == IN_NEED_INIT)
			inputClassesArray[i]->Init();

		else if (inputClassesArray[i]->GetState() == IN_NEED_DEINIT)
			inputClassesArray[i]->Deinit();
	}

	osTaskDelete(NULL);

	while (1);
}
