################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/modules/profiles/profiles.c 

OBJS += \
./serialAPI/modules/profiles/profiles.o 

C_DEPS += \
./serialAPI/modules/profiles/profiles.d 


# Each subdirectory must supply rules for building sources it contributes
serialAPI/modules/profiles/profiles.o: D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/modules/profiles/profiles.c serialAPI/modules/profiles/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F767xx -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../../../serialAPI -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-serialAPI-2f-modules-2f-profiles

clean-serialAPI-2f-modules-2f-profiles:
	-$(RM) ./serialAPI/modules/profiles/profiles.cyclo ./serialAPI/modules/profiles/profiles.d ./serialAPI/modules/profiles/profiles.o ./serialAPI/modules/profiles/profiles.su

.PHONY: clean-serialAPI-2f-modules-2f-profiles

