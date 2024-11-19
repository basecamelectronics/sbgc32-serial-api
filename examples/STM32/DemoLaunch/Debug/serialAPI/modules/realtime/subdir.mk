################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/modules/realtime/realtime.c 

OBJS += \
./serialAPI/modules/realtime/realtime.o 

C_DEPS += \
./serialAPI/modules/realtime/realtime.d 


# Each subdirectory must supply rules for building sources it contributes
serialAPI/modules/realtime/realtime.o: D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/modules/realtime/realtime.c serialAPI/modules/realtime/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -DSTM32_THREAD_SAFE_STRATEGY=2 -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Core/ThreadSafe -I../../../../serialAPI -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-serialAPI-2f-modules-2f-realtime

clean-serialAPI-2f-modules-2f-realtime:
	-$(RM) ./serialAPI/modules/realtime/realtime.cyclo ./serialAPI/modules/realtime/realtime.d ./serialAPI/modules/realtime/realtime.o ./serialAPI/modules/realtime/realtime.su

.PHONY: clean-serialAPI-2f-modules-2f-realtime

