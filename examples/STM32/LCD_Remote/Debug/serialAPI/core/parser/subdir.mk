################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/core/parser/parser.c 

OBJS += \
./serialAPI/core/parser/parser.o 

C_DEPS += \
./serialAPI/core/parser/parser.d 


# Each subdirectory must supply rules for building sources it contributes
serialAPI/core/parser/parser.o: D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/core/parser/parser.c serialAPI/core/parser/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F767xx -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../../../serialAPI -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-serialAPI-2f-core-2f-parser

clean-serialAPI-2f-core-2f-parser:
	-$(RM) ./serialAPI/core/parser/parser.cyclo ./serialAPI/core/parser/parser.d ./serialAPI/core/parser/parser.o ./serialAPI/core/parser/parser.su

.PHONY: clean-serialAPI-2f-core-2f-parser

