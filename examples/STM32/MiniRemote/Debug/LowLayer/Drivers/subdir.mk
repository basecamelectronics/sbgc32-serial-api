################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../LowLayer/Drivers/startup_stm32f411ceux.s 

C_SRCS += \
../LowLayer/Drivers/syscalls.c \
../LowLayer/Drivers/sysmem.c \
../LowLayer/Drivers/system_stm32f4xx.c 

S_DEPS += \
./LowLayer/Drivers/startup_stm32f411ceux.d 

C_DEPS += \
./LowLayer/Drivers/syscalls.d \
./LowLayer/Drivers/sysmem.d \
./LowLayer/Drivers/system_stm32f4xx.d 

OBJS += \
./LowLayer/Drivers/startup_stm32f411ceux.o \
./LowLayer/Drivers/syscalls.o \
./LowLayer/Drivers/sysmem.o \
./LowLayer/Drivers/system_stm32f4xx.o 


# Each subdirectory must supply rules for building sources it contributes
LowLayer/Drivers/%.o: ../LowLayer/Drivers/%.s LowLayer/Drivers/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
LowLayer/Drivers/%.o LowLayer/Drivers/%.su LowLayer/Drivers/%.cyclo: ../LowLayer/Drivers/%.c LowLayer/Drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -DSTM32F411xx -c -I../../../../serialAPI -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../LowLayer/Drivers/CMSIS/Include -I../LowLayer/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middleware/FreeRTOS/include -I../Middleware/FreeRTOS/portable/GCC/ARM_CM4F -I../Middleware/uGFX -I../Middleware/uGFX/src -I../LowLayer/Hardware -I../Middleware/Resources -I../Middleware/uGFX/src/gadc -I../Middleware/uGFX/src/gaudio -I../Middleware/uGFX/src/gdisp -I../Middleware/uGFX/src/gdriver -I../Middleware/uGFX/src/gevent -I../Middleware/uGFX/src/gfile -I../Middleware/uGFX/src/ginput -I../Middleware/uGFX/src/gmisc -I../Middleware/uGFX/src/gos -I../Middleware/uGFX/src/gqueue -I../Middleware/uGFX/src/gtimer -I../Middleware/uGFX/src/gtrans -I../Middleware/uGFX/src/gwin -I../Middleware/uGFX/src/gdisp/mcufont -I../Middleware/Utility -I../HighLayer/System -I../HighLayer/GUI/Inc -I../Middleware/uGFX/drivers/gdisp/ST7735 -I../HighLayer -I../LowLayer -I../LowLayer/Hardware/Inputs -I../LowLayer/Hardware/Misc -I../LowLayer/Drivers -I../HighLayer/Gimbal -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-LowLayer-2f-Drivers

clean-LowLayer-2f-Drivers:
	-$(RM) ./LowLayer/Drivers/startup_stm32f411ceux.d ./LowLayer/Drivers/startup_stm32f411ceux.o ./LowLayer/Drivers/syscalls.cyclo ./LowLayer/Drivers/syscalls.d ./LowLayer/Drivers/syscalls.o ./LowLayer/Drivers/syscalls.su ./LowLayer/Drivers/sysmem.cyclo ./LowLayer/Drivers/sysmem.d ./LowLayer/Drivers/sysmem.o ./LowLayer/Drivers/sysmem.su ./LowLayer/Drivers/system_stm32f4xx.cyclo ./LowLayer/Drivers/system_stm32f4xx.d ./LowLayer/Drivers/system_stm32f4xx.o ./LowLayer/Drivers/system_stm32f4xx.su

.PHONY: clean-LowLayer-2f-Drivers

