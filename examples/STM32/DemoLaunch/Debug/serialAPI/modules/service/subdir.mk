################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/modules/service/service.c 

OBJS += \
./serialAPI/modules/service/service.o 

C_DEPS += \
./serialAPI/modules/service/service.d 


# Each subdirectory must supply rules for building sources it contributes
serialAPI/modules/service/service.o: D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/modules/service/service.c serialAPI/modules/service/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -DSTM32_THREAD_SAFE_STRATEGY=2 -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Core/ThreadSafe -I../../../../serialAPI -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-serialAPI-2f-modules-2f-service

clean-serialAPI-2f-modules-2f-service:
	-$(RM) ./serialAPI/modules/service/service.cyclo ./serialAPI/modules/service/service.d ./serialAPI/modules/service/service.o ./serialAPI/modules/service/service.su

.PHONY: clean-serialAPI-2f-modules-2f-service

