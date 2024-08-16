################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/core/commandBuild.c \
D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/core/lowLayer.c 

OBJS += \
./serialAPI/core/commandBuild.o \
./serialAPI/core/lowLayer.o 

C_DEPS += \
./serialAPI/core/commandBuild.d \
./serialAPI/core/lowLayer.d 


# Each subdirectory must supply rules for building sources it contributes
serialAPI/core/commandBuild.o: D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/core/commandBuild.c serialAPI/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F767xx -DSTM32_THREAD_SAFE_STRATEGY=2 -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Core/ThreadSafe -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../../../serialAPI -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
serialAPI/core/lowLayer.o: D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/core/lowLayer.c serialAPI/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F767xx -DSTM32_THREAD_SAFE_STRATEGY=2 -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Core/ThreadSafe -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../../../serialAPI -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-serialAPI-2f-core

clean-serialAPI-2f-core:
	-$(RM) ./serialAPI/core/commandBuild.d ./serialAPI/core/commandBuild.o ./serialAPI/core/commandBuild.su ./serialAPI/core/lowLayer.d ./serialAPI/core/lowLayer.o ./serialAPI/core/lowLayer.su

.PHONY: clean-serialAPI-2f-core

