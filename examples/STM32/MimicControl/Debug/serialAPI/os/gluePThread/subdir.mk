################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/os/gluePThread/gluePThread.c 

OBJS += \
./serialAPI/os/gluePThread/gluePThread.o 

C_DEPS += \
./serialAPI/os/gluePThread/gluePThread.d 


# Each subdirectory must supply rules for building sources it contributes
serialAPI/os/gluePThread/gluePThread.o: D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/os/gluePThread/gluePThread.c serialAPI/os/gluePThread/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F767xx -DSTM32_THREAD_SAFE_STRATEGY=2 -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Core/ThreadSafe -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../../../serialAPI -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-serialAPI-2f-os-2f-gluePThread

clean-serialAPI-2f-os-2f-gluePThread:
	-$(RM) ./serialAPI/os/gluePThread/gluePThread.cyclo ./serialAPI/os/gluePThread/gluePThread.d ./serialAPI/os/gluePThread/gluePThread.o ./serialAPI/os/gluePThread/gluePThread.su

.PHONY: clean-serialAPI-2f-os-2f-gluePThread

