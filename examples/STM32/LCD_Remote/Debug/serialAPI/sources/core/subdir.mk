################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/sources/core/core.c 

OBJS += \
./serialAPI/sources/core/core.o 

C_DEPS += \
./serialAPI/sources/core/core.d 


# Each subdirectory must supply rules for building sources it contributes
serialAPI/sources/core/core.o: D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/sources/core/core.c serialAPI/sources/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F767xx -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../../../serialAPI -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-serialAPI-2f-sources-2f-core

clean-serialAPI-2f-sources-2f-core:
	-$(RM) ./serialAPI/sources/core/core.d ./serialAPI/sources/core/core.o ./serialAPI/sources/core/core.su

.PHONY: clean-serialAPI-2f-sources-2f-core

