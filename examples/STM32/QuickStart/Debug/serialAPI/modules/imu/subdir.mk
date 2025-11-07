################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/modules/imu/imu.c 

OBJS += \
./serialAPI/modules/imu/imu.o 

C_DEPS += \
./serialAPI/modules/imu/imu.d 


# Each subdirectory must supply rules for building sources it contributes
serialAPI/modules/imu/imu.o: D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/modules/imu/imu.c serialAPI/modules/imu/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../../../../serialAPI -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-serialAPI-2f-modules-2f-imu

clean-serialAPI-2f-modules-2f-imu:
	-$(RM) ./serialAPI/modules/imu/imu.cyclo ./serialAPI/modules/imu/imu.d ./serialAPI/modules/imu/imu.o ./serialAPI/modules/imu/imu.su

.PHONY: clean-serialAPI-2f-modules-2f-imu

