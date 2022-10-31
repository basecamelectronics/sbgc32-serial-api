################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: ARM_TC
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/basecam/SBGC32_Library/sbgc32-serial-api/sources/realtime/realtime.c 

OBJS += \
./sources/realtime/realtime.o 

C_DEPS += \
./sources/realtime/realtime.d 


# Each subdirectory must supply rules for building sources it contributes
sources/realtime/realtime.o: D:/basecam/SBGC32_Library/sbgc32-serial-api/sources/realtime/realtime.c sources/realtime/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -DSTM32_THREAD_SAFE_STRATEGY=2 -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Core/ThreadSafe -I../../../../drivers/STM32_Driver -I../../../../sources -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-sources-2f-realtime

clean-sources-2f-realtime:
	-$(RM) ./sources/realtime/realtime.d ./sources/realtime/realtime.o ./sources/realtime/realtime.su

.PHONY: clean-sources-2f-realtime

