################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/drivers/driverSTM32/driverSTM32.c 

OBJS += \
./serialAPI/drivers/driverSTM32/driverSTM32.o 

C_DEPS += \
./serialAPI/drivers/driverSTM32/driverSTM32.d 


# Each subdirectory must supply rules for building sources it contributes
serialAPI/drivers/driverSTM32/driverSTM32.o: D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/drivers/driverSTM32/driverSTM32.c serialAPI/drivers/driverSTM32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -DSTM32_THREAD_SAFE_STRATEGY=2 -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Core/ThreadSafe -I../../../../serialAPI -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-serialAPI-2f-drivers-2f-driverSTM32

clean-serialAPI-2f-drivers-2f-driverSTM32:
	-$(RM) ./serialAPI/drivers/driverSTM32/driverSTM32.cyclo ./serialAPI/drivers/driverSTM32/driverSTM32.d ./serialAPI/drivers/driverSTM32/driverSTM32.o ./serialAPI/drivers/driverSTM32/driverSTM32.su

.PHONY: clean-serialAPI-2f-drivers-2f-driverSTM32

