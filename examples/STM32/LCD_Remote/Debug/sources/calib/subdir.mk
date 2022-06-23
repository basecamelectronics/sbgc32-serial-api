################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: ARM_TC
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/basecam/SBGC32_Library/trunc/sources/calib/calib.c 

OBJS += \
./sources/calib/calib.o 

C_DEPS += \
./sources/calib/calib.d 


# Each subdirectory must supply rules for building sources it contributes
sources/calib/calib.o: D:/basecam/SBGC32_Library/trunc/sources/calib/calib.c sources/calib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F767xx -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../../../sources -I../../../../drivers/STM32_Driver -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-sources-2f-calib

clean-sources-2f-calib:
	-$(RM) ./sources/calib/calib.d ./sources/calib/calib.o ./sources/calib/calib.su

.PHONY: clean-sources-2f-calib

