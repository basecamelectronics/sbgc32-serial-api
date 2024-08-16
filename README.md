SimpleBGC32 Serial API Open Source C Library
============================================
[![Web-site](https://www.basecamelectronics.com/img/logo.basecam.onwhite.png)](https://www.basecamelectronics.com)

Description
-----------
This library is a helping instrument for communication between the SimpleBGC32 devices and different data processing devices.
For more comfortable interaction with the SBGC32 devices repository contents possible [examples](examples) of implementations of the
driver algorithms are presented. General protocol source files are placed in the [modules](serialAPI/modules) folder. Also, you may include 
the pre-made driver files if you rather to create an application using the Arduino (AVR MCUs), STM32 or Linux OS. See the
[drivers](serialAPI/drivers) folder. Additionally, the library is compatible with [AzureRTOS, FreeRTOS, and Linux OS](serialAPI/os).
Pay attention to the [serialAPI_ConfigTemplate.h](serialAPI/serialAPI_ConfigTemplate.h) file. This file helps to configure the internal
functionality of the library. Copy it, rename it to "serialAPI_Config.h", move it wherever you want and configure the contents.

Files Description
-----------------

[core/](serialAPI/core) - the kernel library files;

[drivers/](serialAPI/drivers) - the driver files;

[modules/](serialAPI/modules) - a folder that stores a Serial API commands functional sorted by purpose;

[os/](serialAPI/os) - a folder containing the OS-glue driver files;

[adjunct.h](serialAPI/adjunct.h) - Header help-code file;

[sbgc32.c](serialAPI/sbgc32.c) and [sbgc32.h](serialAPI/sbgc32.h) - Assembly files of the l;library;

[serialAPI_ConfigTemplate.h](serialAPI/serialAPI_ConfigTemplate.h) - Configurations template header file of the library.

Requirements
------------
Minimum device requirements for using this library: at least **2 KB RAM** and at least **16 KB** FLASH.
To fully use the functions of this library, it is recommended to use a device with at least **32 KB RAM**
and at least **64 KB FLASH**.

How to use this library
-----------------------
For more convenient work with the library, it is recommended to use the [SimpleBGC32 Serial API protocol
specification](https://www.basecamelectronics.com/serialapi/).
It is recommended to review the QuickStart example for more effective use of the library functions.
For more advanced usage level see [MiniRemote](examples/STM32/MiniRemote) example - a small yet very functional and flexible remote
controller for the SBGC32-based devices. Other examples work exclusively in blocking mode.
Additionally, please refer to the note contained in the [sbgc32.h](serialAPI/sbgc32.h) file. It includes a lot of useful information
about the features of this library.

To connect the library to your project, just place the [serialAPI](serialAPI) folder in it.

**Initialization:**

	// Link the library files
	#include "sbgc32.h"

	// Declare a general SBGC32 object
	sbgcGeneral_t SBGC32_Device;

	// Initialize the library
	SBGC32_Init(&SBGC32_Device);

Documentation
-------------
Use the Doxygen application with the provided [doxygen configuration file](doxygen/doxyfile) to generate the library documentation.

Feedback
--------

If you have any questions or suggestions about using this library, you can contact at:

support@basecamelectronics.com

a.ivanisov@basecamelectronics.com