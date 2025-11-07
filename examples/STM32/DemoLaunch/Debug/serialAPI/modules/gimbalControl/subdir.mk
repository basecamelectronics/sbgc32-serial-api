################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/modules/gimbalControl/gimbalControl.c 

OBJS += \
./serialAPI/modules/gimbalControl/gimbalControl.o 

C_DEPS += \
./serialAPI/modules/gimbalControl/gimbalControl.d 


# Each subdirectory must supply rules for building sources it contributes
serialAPI/modules/gimbalControl/gimbalControl.o: D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/modules/gimbalControl/gimbalControl.c serialAPI/modules/gimbalControl/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -DSTM32_THREAD_SAFE_STRATEGY=2 -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Core/ThreadSafe -I../../../../serialAPI -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-serialAPI-2f-modules-2f-gimbalControl

clean-serialAPI-2f-modules-2f-gimbalControl:
	-$(RM) ./serialAPI/modules/gimbalControl/gimbalControl.cyclo ./serialAPI/modules/gimbalControl/gimbalControl.d ./serialAPI/modules/gimbalControl/gimbalControl.o ./serialAPI/modules/gimbalControl/gimbalControl.su

.PHONY: clean-serialAPI-2f-modules-2f-gimbalControl

