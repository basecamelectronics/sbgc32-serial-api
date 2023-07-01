################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/drivers/LinuxDriver/driver_Linux.c 

OBJS += \
./serialAPI/drivers/LinuxDriver/driver_Linux.o 

C_DEPS += \
./serialAPI/drivers/LinuxDriver/driver_Linux.d 


# Each subdirectory must supply rules for building sources it contributes
serialAPI/drivers/LinuxDriver/driver_Linux.o: D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/drivers/LinuxDriver/driver_Linux.c serialAPI/drivers/LinuxDriver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F767xx -DSTM32_THREAD_SAFE_STRATEGY=2 -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Core/ThreadSafe -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../../../serialAPI -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-serialAPI-2f-drivers-2f-LinuxDriver

clean-serialAPI-2f-drivers-2f-LinuxDriver:
	-$(RM) ./serialAPI/drivers/LinuxDriver/driver_Linux.d ./serialAPI/drivers/LinuxDriver/driver_Linux.o ./serialAPI/drivers/LinuxDriver/driver_Linux.su

.PHONY: clean-serialAPI-2f-drivers-2f-LinuxDriver

