################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../LowLayer/Hardware/Inputs/absoluteEncoder.cpp \
../LowLayer/Hardware/Inputs/analogInput.cpp \
../LowLayer/Hardware/Inputs/digitalInput.cpp \
../LowLayer/Hardware/Inputs/digitalJoystick.cpp \
../LowLayer/Hardware/Inputs/incrementalEncoder.cpp 

OBJS += \
./LowLayer/Hardware/Inputs/absoluteEncoder.o \
./LowLayer/Hardware/Inputs/analogInput.o \
./LowLayer/Hardware/Inputs/digitalInput.o \
./LowLayer/Hardware/Inputs/digitalJoystick.o \
./LowLayer/Hardware/Inputs/incrementalEncoder.o 

CPP_DEPS += \
./LowLayer/Hardware/Inputs/absoluteEncoder.d \
./LowLayer/Hardware/Inputs/analogInput.d \
./LowLayer/Hardware/Inputs/digitalInput.d \
./LowLayer/Hardware/Inputs/digitalJoystick.d \
./LowLayer/Hardware/Inputs/incrementalEncoder.d 


# Each subdirectory must supply rules for building sources it contributes
LowLayer/Hardware/Inputs/%.o LowLayer/Hardware/Inputs/%.su: ../LowLayer/Hardware/Inputs/%.cpp LowLayer/Hardware/Inputs/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -DSTM32F411xx -c -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../LowLayer/Drivers/CMSIS/Include -I../LowLayer/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middleware/FreeRTOS/include -I../Middleware/FreeRTOS/portable/GCC/ARM_CM4F -I../Middleware/uGFX -I../Middleware/uGFX/src -I../LowLayer/Hardware -I../Middleware/Resources -I../Middleware/uGFX/src/gadc -I../Middleware/uGFX/src/gaudio -I../Middleware/uGFX/src/gdisp -I../Middleware/uGFX/src/gdriver -I../Middleware/uGFX/src/gevent -I../Middleware/uGFX/src/gfile -I../Middleware/uGFX/src/ginput -I../Middleware/uGFX/src/gmisc -I../Middleware/uGFX/src/gos -I../Middleware/uGFX/src/gqueue -I../Middleware/uGFX/src/gtimer -I../Middleware/uGFX/src/gtrans -I../Middleware/uGFX/src/gwin -I../Middleware/uGFX/src/gdisp/mcufont -I../Middleware/Utility -I../HighLayer/System -I../HighLayer/GUI/Inc -I../Middleware/uGFX/drivers/gdisp/ST7735 -I../HighLayer -I../LowLayer -I../LowLayer/Hardware/Inputs -I../LowLayer/Hardware/Misc -I../LowLayer/Drivers -I../HighLayer/Gimbal -I../../../../serialAPI -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-LowLayer-2f-Hardware-2f-Inputs

clean-LowLayer-2f-Hardware-2f-Inputs:
	-$(RM) ./LowLayer/Hardware/Inputs/absoluteEncoder.d ./LowLayer/Hardware/Inputs/absoluteEncoder.o ./LowLayer/Hardware/Inputs/absoluteEncoder.su ./LowLayer/Hardware/Inputs/analogInput.d ./LowLayer/Hardware/Inputs/analogInput.o ./LowLayer/Hardware/Inputs/analogInput.su ./LowLayer/Hardware/Inputs/digitalInput.d ./LowLayer/Hardware/Inputs/digitalInput.o ./LowLayer/Hardware/Inputs/digitalInput.su ./LowLayer/Hardware/Inputs/digitalJoystick.d ./LowLayer/Hardware/Inputs/digitalJoystick.o ./LowLayer/Hardware/Inputs/digitalJoystick.su ./LowLayer/Hardware/Inputs/incrementalEncoder.d ./LowLayer/Hardware/Inputs/incrementalEncoder.o ./LowLayer/Hardware/Inputs/incrementalEncoder.su

.PHONY: clean-LowLayer-2f-Hardware-2f-Inputs

