SimpleBGC32 Serial API Open Source C Library
==========================================
[![Web-site](https://www.basecamelectronics.com/img/logo.basecam.onwhite.png)](https://www.basecamelectronics.com)

Description
-----------
This library is a helping instrument for communication between the SimpleBGC32 devices and different data processing devices.
For more comfortable interaction with the SBGC32 devices repository contents possible examples of implementations of the
driver algorithms are presented. General source files are placed in the /serialAPI/sources folder. Also, you may include the
pre-made driver files if you rather to create an application using the Arduino (AVR MCUs), STM32 or Linux OS.
Pay attention to the serialAPI_ConfigTemplate file. This file helps to configure the internal functionality of the library.

Files Description
-----------------

**Common files:**

- adjunct.h - Header help-code file;

- sbgc32.c and sbgc32.h - Assembly files of the Library;

- serialAPI_ConfigTemplate.h - Configurations template header file of the Library.

**sources** - a folder that stores a Serial API commands functional sorted by purpose.

**drivers** - a folder containing the driver files.

### Header library files involve: ###

- Macros and constants

- Auxiliary flags and their functions;

- Structure types corresponding to their commands.

### Source library files involve: ###

- Reference data for BIG ENDIAN parsing and debug;

- Executable functions.

The adjvar.c file contains a data block "adjVarsReferenceInfoArray" with auxiliary information about all adjustable variables
at the time of the current version. The core.c and core.h files also contain a lot of general service code.

Requirements
------------
To fully use the functions of this library, it is recommended to use a device with at least **2 KB RAM**
and at least **16 KB FLASH**.

How to use this library
-----------------------
For more convenient work with the library, it is recommended to use the [SimpleBGC32 Serial API protocol
specification](https://www.basecamelectronics.com/serialapi/).

### Initialization ###

	#include "sbgc32.h"

	GeneralSBGC_t SBGC32_Device;

	SBGC32_Init(&SBGC32_Device);

**STM32 note:**
	
*if your application uses CubeMX - stm32fxxx_it.c :*

	#include "sbgc32.h"
	
	extern GeneralSBGC_t SBGC32_Device;

	// if your application works without FreeRTOS:
	void TIMx_IRQHandler (void)
	{
		if (GET_FLAG_TIM_SR_UIF(SBGC_REFERENCE_TIMER) &&
		    GET_FLAG_TIM_DIER_UIE(SBGC_REFERENCE_TIMER))
			TimerDRV_CallBack(SBGC32_Device.Drv);

		HAL_TIM_IRQHandler(SBGC_REFERENCE_TIMER);
	}

	// if UART works by means of NVIC:
	void USARTx_IRQHandler (void)
	{
		if (GET_FLAG_UART_ISR_TC(SBGC_SERIAL_PORT) &&
			GET_FLAG_UART_CR1_TCIE(SBGC_SERIAL_PORT))
			UART_DRV_TxCallBack(SBGC32_Device.Drv);

		if (GET_FLAG_UART_ISR_RXNE(SBGC_SERIAL_PORT) &&
			GET_FLAG_UART_CR1_RXNEIE(SBGC_SERIAL_PORT))
			UART_DRV_RxCallBack(SBGC32_Device.Drv);

		if (GET_FLAG_UART_ISR_ORE(SBGC_SERIAL_PORT))
			CLEAR_UART_ORE(SBGC_SERIAL_PORT);

		HAL_UART_IRQHandler(SBGC_SERIAL_PORT);
	}

	// if UART works by means of DMA with LL:
	void DMAx_Streamx_IRQHandler (void)
	{
		if (GET_FLAG_DMA_HISR_TC_TX)
			CLEAR_DMA_TC_TX;
	}

	void DMAx_Streamx_IRQHandler (void)
	{
		if (GET_FLAG_DMA_HISR_TC_RX)
			CLEAR_DMA_TC_RX;
	}

*Notes:*

*- To connect the library to your project, just place the serialAPI folder in it;*

*- The "sbgc32.h" file looks at the settings from the file "serialAPI_Config.h" file. Rename the "serialAPI_ConfigTemplate.h" file like this;*

*- The default speed of the SimpleBGC32 devices is 115200 bits per second;*

*- If you are connecting a SBGC32 through UART, the RX pin should be pulled up;*

*- If you want to create your gimbal communication driver, create it based on the necessary functions defined in the GeneralSBGC_t structure;*

*- If you are using PlatformIO for Arduino, you need to add the serialAPI_Config.h file to the build directory: .pio/libdeps/ArduinoXX/serialAPI;*

*- Starting to work with the gimbal using Arduino don't forget to check the **SERIAL_TX_BUFFER_SIZE** and **SERIAL_RX_BUFFER_SIZE** constants
in "HardwareSerial.h" file. Strongly recommend increasing this value to 256;*

*- When SBGC32 device connected with Linux device you need to set **choose mode** for this connection to **read, write, and executable** 
using the terminal (sudo chmod a+rwx /dev/ttyUSBx);*

*- The communication driver for STM32 devices supports the HAL and LL libraries;*

*- Set the SYS_BIG_ENDIAN constant to SET_ON, if your general processing system have a BIG ENDIAN memory type;*

*- Reducing the MAX_BUFF_SIZE and UNEXP_CMD_BUFFER_SIZE parameters you also reduce the load on the stack.*

### Data handling ###

Each function beginning with SBGC32_... communicates with a SBGC32 device in one way or another.

- Transmit functions required preparing data in the target writable structures or other arguments. Such structures are
marked by the **const** keyword. Besides, for most -TX functions after sending data, the SBGC32 device sends a confirmation
command processed automatically in the function's body.

- Request functions require partial filling of the fields of the target structure or nothing at all. Received data is stored
in this structure. Confirmation of correct data reception is a returned status value of this function.

- For manual data management use the **SBGC32_TX** and **SBGC32_RX** functions.

The rest of the details are contained in the descriptions inside the library itself. Also, you can generate project documentation
using a doxyfile in the /doxygen folder.

 ### Feedback ###

If you have any questions about using this library, you can ask for help at:

support@basecamelectronics.com

a.ivanisov@basecamelectronics.com