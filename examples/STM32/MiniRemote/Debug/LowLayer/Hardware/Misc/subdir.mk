################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../LowLayer/Hardware/Misc/CRC32.cpp \
../LowLayer/Hardware/Misc/EEPROM.cpp \
../LowLayer/Hardware/Misc/UART.cpp \
../LowLayer/Hardware/Misc/internalFlash.cpp \
../LowLayer/Hardware/Misc/watchDog.cpp 

OBJS += \
./LowLayer/Hardware/Misc/CRC32.o \
./LowLayer/Hardware/Misc/EEPROM.o \
./LowLayer/Hardware/Misc/UART.o \
./LowLayer/Hardware/Misc/internalFlash.o \
./LowLayer/Hardware/Misc/watchDog.o 

CPP_DEPS += \
./LowLayer/Hardware/Misc/CRC32.d \
./LowLayer/Hardware/Misc/EEPROM.d \
./LowLayer/Hardware/Misc/UART.d \
./LowLayer/Hardware/Misc/internalFlash.d \
./LowLayer/Hardware/Misc/watchDog.d 


# Each subdirectory must supply rules for building sources it contributes
LowLayer/Hardware/Misc/%.o LowLayer/Hardware/Misc/%.su LowLayer/Hardware/Misc/%.cyclo: ../LowLayer/Hardware/Misc/%.cpp LowLayer/Hardware/Misc/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -DSTM32F411xx -c -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../LowLayer/Drivers/CMSIS/Include -I../LowLayer/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middleware/FreeRTOS/include -I../Middleware/FreeRTOS/portable/GCC/ARM_CM4F -I../Middleware/uGFX -I../Middleware/uGFX/src -I../LowLayer/Hardware -I../Middleware/Resources -I../Middleware/uGFX/src/gadc -I../Middleware/uGFX/src/gaudio -I../Middleware/uGFX/src/gdisp -I../Middleware/uGFX/src/gdriver -I../Middleware/uGFX/src/gevent -I../Middleware/uGFX/src/gfile -I../Middleware/uGFX/src/ginput -I../Middleware/uGFX/src/gmisc -I../Middleware/uGFX/src/gos -I../Middleware/uGFX/src/gqueue -I../Middleware/uGFX/src/gtimer -I../Middleware/uGFX/src/gtrans -I../Middleware/uGFX/src/gwin -I../Middleware/uGFX/src/gdisp/mcufont -I../Middleware/Utility -I../HighLayer/System -I../HighLayer/GUI/Inc -I../Middleware/uGFX/drivers/gdisp/ST7735 -I../HighLayer -I../LowLayer -I../LowLayer/Hardware/Inputs -I../LowLayer/Hardware/Misc -I../LowLayer/Drivers -I../HighLayer/Gimbal -I../../../../serialAPI -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-LowLayer-2f-Hardware-2f-Misc

clean-LowLayer-2f-Hardware-2f-Misc:
	-$(RM) ./LowLayer/Hardware/Misc/CRC32.cyclo ./LowLayer/Hardware/Misc/CRC32.d ./LowLayer/Hardware/Misc/CRC32.o ./LowLayer/Hardware/Misc/CRC32.su ./LowLayer/Hardware/Misc/EEPROM.cyclo ./LowLayer/Hardware/Misc/EEPROM.d ./LowLayer/Hardware/Misc/EEPROM.o ./LowLayer/Hardware/Misc/EEPROM.su ./LowLayer/Hardware/Misc/UART.cyclo ./LowLayer/Hardware/Misc/UART.d ./LowLayer/Hardware/Misc/UART.o ./LowLayer/Hardware/Misc/UART.su ./LowLayer/Hardware/Misc/internalFlash.cyclo ./LowLayer/Hardware/Misc/internalFlash.d ./LowLayer/Hardware/Misc/internalFlash.o ./LowLayer/Hardware/Misc/internalFlash.su ./LowLayer/Hardware/Misc/watchDog.cyclo ./LowLayer/Hardware/Misc/watchDog.d ./LowLayer/Hardware/Misc/watchDog.o ./LowLayer/Hardware/Misc/watchDog.su

.PHONY: clean-LowLayer-2f-Hardware-2f-Misc

