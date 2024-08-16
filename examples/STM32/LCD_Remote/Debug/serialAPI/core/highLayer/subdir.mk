################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/core/highLayer/highLayer.c 

OBJS += \
./serialAPI/core/highLayer/highLayer.o 

C_DEPS += \
./serialAPI/core/highLayer/highLayer.d 


# Each subdirectory must supply rules for building sources it contributes
serialAPI/core/highLayer/highLayer.o: D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/core/highLayer/highLayer.c serialAPI/core/highLayer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F767xx -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../../../serialAPI -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-serialAPI-2f-core-2f-highLayer

clean-serialAPI-2f-core-2f-highLayer:
	-$(RM) ./serialAPI/core/highLayer/highLayer.cyclo ./serialAPI/core/highLayer/highLayer.d ./serialAPI/core/highLayer/highLayer.o ./serialAPI/core/highLayer/highLayer.su

.PHONY: clean-serialAPI-2f-core-2f-highLayer

