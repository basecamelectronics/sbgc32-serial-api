################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: ARM_TC
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/basecam/SBGC32_Library/trunc/sources/adjvar/adjvar.c 

OBJS += \
./sources/adjvar/adjvar.o 

C_DEPS += \
./sources/adjvar/adjvar.d 


# Each subdirectory must supply rules for building sources it contributes
sources/adjvar/adjvar.o: D:/basecam/SBGC32_Library/trunc/sources/adjvar/adjvar.c sources/adjvar/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F767xx -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../../../sources -I../../../../drivers/STM32_Driver -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-sources-2f-adjvar

clean-sources-2f-adjvar:
	-$(RM) ./sources/adjvar/adjvar.d ./sources/adjvar/adjvar.o ./sources/adjvar/adjvar.su

.PHONY: clean-sources-2f-adjvar

