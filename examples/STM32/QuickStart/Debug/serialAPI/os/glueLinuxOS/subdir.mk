################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/os/glueLinuxOS/glueLinuxOS.c 

OBJS += \
./serialAPI/os/glueLinuxOS/glueLinuxOS.o 

C_DEPS += \
./serialAPI/os/glueLinuxOS/glueLinuxOS.d 


# Each subdirectory must supply rules for building sources it contributes
serialAPI/os/glueLinuxOS/glueLinuxOS.o: D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/os/glueLinuxOS/glueLinuxOS.c serialAPI/os/glueLinuxOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../../../../serialAPI -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-serialAPI-2f-os-2f-glueLinuxOS

clean-serialAPI-2f-os-2f-glueLinuxOS:
	-$(RM) ./serialAPI/os/glueLinuxOS/glueLinuxOS.cyclo ./serialAPI/os/glueLinuxOS/glueLinuxOS.d ./serialAPI/os/glueLinuxOS/glueLinuxOS.o ./serialAPI/os/glueLinuxOS/glueLinuxOS.su

.PHONY: clean-serialAPI-2f-os-2f-glueLinuxOS

