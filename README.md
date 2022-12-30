SimpleBGC32 Serial API Open Source C Library
==========================================
[![Web-site](https://www.basecamelectronics.com/img/logo.basecam.onwhite.png)](https://www.basecamelectronics.com)

Description
-----------
This library is a helping instrument for communication between the SimpleBGC32 devices and different data processing devices.
For more comfortable interaction with the SBGC32 devices repository contents possible examples of implementations of the
driver algorithms are presented. General source files are placed in the /sources folder. Also, you may include the
pre-made driver files if you rather to create an application using the Arduino (AVR MCUs), STM32 or Linux OS systems.

Pay attention to the **User Defined Parameter** constants, contained in the core.h file. Uncomment the SYS_BIG_ENDIAN constant
if your general processing system have a BIG ENDIAN memory type. Uncomment the SBGC_DEBUG_MODE constant if you need to display
debug information. Reducing the MAX_BUFF_SIZE you also reduce the load on the stack (256 byte is a optimal value).

### Header library files involve: ###

- Macros and constants

- Auxiliary flags and their functions

- Structure types corresponding to their commands

### Source library files involve: ###

- Data blocks for BIG ENDIAN systems

- Executable functions

The adjvar.c file contains a data block "AdjVarsDebugInfoArray" with auxiliary information about all adjustable variables
at the time of the current version. The core.c and core.h files also contain a lot of general service code.

Requirements
------------
To fully use the functions of this library, it is recommended to use a device with at least **2 KB RAM**
and at least **16 KB FLASH**.

Files Description
-----------------
### Source files ###

**Headers (.h):**

- adjvar/adjvar.h - Adjustable variables header file

- calib/calib.h - Calibration commands header file

- core/adjunct.h - Header common help-code file

- core/core.h - Header file of the core for the custom usage SBGC32 Library

- eeprom/eeprom.h - EEPROM module header file

- gimbalControl/gimbalControl.h - Gimbal realtime-control header file

- imu/imu.h - IMU module header file

- profiles/profiles.h - Profile commands header file

- realtime/realtime.h - Realtime operations header file

- service/service.h - Service functions header file

**Sources (.c):**

- adjvar/adjvar.c - Adjustable variables source file

- calib/calib.c - Calibration commands source file

- core/core.c - SBGC32 core source file

- eeprom/eeprom.c - EEPROM module source file

- gimbalControl/gimbalControl.c - Gimbal realtime-control source file

- imu/imu.c - IMU module source file

- profiles/profiles.c - Profile commands source file

- realtime/realtime.c - Realtime operations source file

- service/service.c - Service functions source file

### Driver files ###

**Headers (.h):**

- ArduinoDriver/driver_Arduino.h - Arduino driver header file

- LinuxDriver/driver_Linux.h - Linux driver header file

- STM32_Driver/driver_STM32.h - STM32 driver header file

- STM32_Driver/MCU_Config.h - STM32 MCU configurations header file

- STM32_Driver/stm32_it.h - STM32 interrupts header file

**Sources (.c):**

- ArduinoDriver/driver_Arduino.cpp - Arduino driver source file

- LinuxDriver/driver_Linux.c - Linux driver source file

- STM32_Driver/driver_STM32.c - STM32 driver source file

- STM32_Driver/stm32_it.c - STM32 interrupts source file

How to use this library
-----------------------
For more convenient work with the library, it is recommended to use the [SimpleBGC32 Serial API protocol
specification](https://www.basecamelectronics.com/serialapi/).

### Initialization ###

**Arduino:**

	#include "driver_Arduino.h"
	#include "core.h"
	
	GeneralSBGC_t SBGC32_Device;
	
	void setup ()
	{
		SBGC_SERIAL_PORT.begin(SBGC_SERIAL_SPEED);
		DEBUG_SERIAL_PORT.begin(DEBUG_SERIAL_SPEED);
		
		pinMode(SERIAL2_RX_PIN, INPUT_PULLUP);

		SBGC32_DefaultInit(&SBGC32_Device, UartTransmitData, UartReceiveByte, GetAvailableBytes,
				UartTransmitDebugData, GetTimeMs, SBGC_PROTOCOL_V2);			   	
	}

**Linux:**

	#include "driver_Linux.h"
	#include "core.h"

	int main (void)
	{
		SBGC32_Device.Drv = malloc(sizeof(Driver_t));
		DriverInit(SBGC32_Device.Drv, SBGC_SERIAL_PORT);

		SBGC32_DefaultInit(&SBGC32_Device, PortTransmitData, PortReceiveByte, GetAvailableBytes,
				PrintDebugData, GetTimeMs, SBGC_PROTOCOL_V2);
	}


**STM32:**

*main.c :*

	#include "driver_STM32.h"
	#include "core.h"
	
	GeneralSBGC_t SBGC32_Device;
	
	int main (void)
	{
		USARTx_Init();
		USARTx_Init();
	
		SBGC32_Device.Drv = malloc(sizeof(Driver_t));
		DriverInit(SBGC32_Device.Drv, SBGC_SERIAL_PORT, SBGC_REFERENCE_TIMER);

		SBGC32_DefaultInit(&SBGC32_Device, UartTransmitData, UartReceiveByte, GetAvailableBytes,
				UartTransmitDebugData, GetTimeMs, SBGC_PROTOCOL_V2);
	}
	
*if your application uses CubeMX - stm32fxxx_it.c :*

	#include "driver_STM32.h"
	#include "core.h"
	
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

*- All general library settings are placed in the "core.h" file under "User Defined Parameters" comment;*

*- All general drivers settings are placed in the "driver_xx.h" files under "User Defined Parameters" comment;*

*- The default speed of SimpleBGC32 devices is 115200 bits per second;*

*- Initialize the **DebugData** functions with **NULL** if you don't want to use debug mode;*

*- If you are connecting SBGC32 through UART, the RX pin must be pulled up;*

*- If you want to create your gimbal communication driver, create it based on the necessary functions defined in the GeneralSBGC_t structure;*

*- Starting to work with the gimbal using Arduino don't forget to check the **SERIAL_TX_BUFFER_SIZE** and **SERIAL_RX_BUFFER_SIZE** constants
in "HardwareSerial.h" file. Strongly recommend increasing this value to 256;*

*- When SBGC32 device connected with Linux device you need to set **choose mode** for this connection to **read, write, and executable** 
using the terminal (sudo chmod a+rwx /dev/ttyUSBx);*

*- The communication driver for STM32 devices supports HAL and LL libraries. Common software settings are made in the "MCU_Config.h" file.
Special settings are made in the "driver_STM32.h" file in the relevant sections. If your application doesn't use CubeMX utility,
it is recommended to explore all the configurable driver parameters;*

### Data handling ###

Each function beginning with SBGC32_... communicates with the SBGC32 device in a different way.

- Transmit functions required preparing data in the target writable structures or other arguments. Such structures are
marked by the **const** keyword. Besides, for most -TX functions after sending data, the SBGC32 device sends a confirmation
command processed automatically in the function's body.

- Request functions require partial filling of the fields of the target structure or nothing at all. Received data is stored
in this structure. Confirmation of correct data reception is a returned status value of this function.

- For manual data management use the **SBGC32_TX** and **SBGC32_RX** functions.

The rest of the details are contained in the descriptions inside the library itself. Also, you can generate project documentation
using doxyfile in the /doxygen folder.

 ### Feedback ###

If you have any questions about using this library, you can ask for help at:

support@basecamelectronics.com

qsivey@gmail.com