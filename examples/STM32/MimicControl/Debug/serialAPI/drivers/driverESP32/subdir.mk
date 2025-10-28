################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/drivers/driverESP32/driverESP32.c 

OBJS += \
./serialAPI/drivers/driverESP32/driverESP32.o 

C_DEPS += \
./serialAPI/drivers/driverESP32/driverESP32.d 


# Each subdirectory must supply rules for building sources it contributes
serialAPI/drivers/driverESP32/driverESP32.o: D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/drivers/driverESP32/driverESP32.c serialAPI/drivers/driverESP32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F767xx -DSTM32_THREAD_SAFE_STRATEGY=2 -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Core/ThreadSafe -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../../../serialAPI -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-serialAPI-2f-drivers-2f-driverESP32

clean-serialAPI-2f-drivers-2f-driverESP32:
	-$(RM) ./serialAPI/drivers/driverESP32/driverESP32.cyclo ./serialAPI/drivers/driverESP32/driverESP32.d ./serialAPI/drivers/driverESP32/driverESP32.o ./serialAPI/drivers/driverESP32/driverESP32.su

.PHONY: clean-serialAPI-2f-drivers-2f-driverESP32

