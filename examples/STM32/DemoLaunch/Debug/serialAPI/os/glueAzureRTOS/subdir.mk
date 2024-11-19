################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/os/glueAzureRTOS/glueAzureRTOS.c 

OBJS += \
./serialAPI/os/glueAzureRTOS/glueAzureRTOS.o 

C_DEPS += \
./serialAPI/os/glueAzureRTOS/glueAzureRTOS.d 


# Each subdirectory must supply rules for building sources it contributes
serialAPI/os/glueAzureRTOS/glueAzureRTOS.o: D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/os/glueAzureRTOS/glueAzureRTOS.c serialAPI/os/glueAzureRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -DSTM32_THREAD_SAFE_STRATEGY=2 -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Core/ThreadSafe -I../../../../serialAPI -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-serialAPI-2f-os-2f-glueAzureRTOS

clean-serialAPI-2f-os-2f-glueAzureRTOS:
	-$(RM) ./serialAPI/os/glueAzureRTOS/glueAzureRTOS.cyclo ./serialAPI/os/glueAzureRTOS/glueAzureRTOS.d ./serialAPI/os/glueAzureRTOS/glueAzureRTOS.o ./serialAPI/os/glueAzureRTOS/glueAzureRTOS.su

.PHONY: clean-serialAPI-2f-os-2f-glueAzureRTOS

