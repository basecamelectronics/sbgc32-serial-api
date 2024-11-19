################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/modules/calib/calib.c 

OBJS += \
./serialAPI/modules/calib/calib.o 

C_DEPS += \
./serialAPI/modules/calib/calib.d 


# Each subdirectory must supply rules for building sources it contributes
serialAPI/modules/calib/calib.o: D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/modules/calib/calib.c serialAPI/modules/calib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -DSTM32_THREAD_SAFE_STRATEGY=2 -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Core/ThreadSafe -I../../../../serialAPI -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-serialAPI-2f-modules-2f-calib

clean-serialAPI-2f-modules-2f-calib:
	-$(RM) ./serialAPI/modules/calib/calib.cyclo ./serialAPI/modules/calib/calib.d ./serialAPI/modules/calib/calib.o ./serialAPI/modules/calib/calib.su

.PHONY: clean-serialAPI-2f-modules-2f-calib

