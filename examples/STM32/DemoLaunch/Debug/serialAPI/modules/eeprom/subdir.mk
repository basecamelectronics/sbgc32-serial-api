################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/modules/eeprom/eeprom.c 

OBJS += \
./serialAPI/modules/eeprom/eeprom.o 

C_DEPS += \
./serialAPI/modules/eeprom/eeprom.d 


# Each subdirectory must supply rules for building sources it contributes
serialAPI/modules/eeprom/eeprom.o: D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/modules/eeprom/eeprom.c serialAPI/modules/eeprom/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -DSTM32_THREAD_SAFE_STRATEGY=2 -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Core/ThreadSafe -I../../../../serialAPI -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-serialAPI-2f-modules-2f-eeprom

clean-serialAPI-2f-modules-2f-eeprom:
	-$(RM) ./serialAPI/modules/eeprom/eeprom.cyclo ./serialAPI/modules/eeprom/eeprom.d ./serialAPI/modules/eeprom/eeprom.o ./serialAPI/modules/eeprom/eeprom.su

.PHONY: clean-serialAPI-2f-modules-2f-eeprom

