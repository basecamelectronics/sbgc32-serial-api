################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/os/glueFreeRTOS/glueFreeRTOS.c 

C_DEPS += \
./serialAPI/os/glueFreeRTOS/glueFreeRTOS.d 

OBJS += \
./serialAPI/os/glueFreeRTOS/glueFreeRTOS.o 


# Each subdirectory must supply rules for building sources it contributes
serialAPI/os/glueFreeRTOS/glueFreeRTOS.o: D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/os/glueFreeRTOS/glueFreeRTOS.c serialAPI/os/glueFreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -DSTM32F411xx -c -I../../../../serialAPI -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../LowLayer/Drivers/CMSIS/Include -I../LowLayer/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middleware/FreeRTOS/include -I../Middleware/FreeRTOS/portable/GCC/ARM_CM4F -I../Middleware/uGFX -I../Middleware/uGFX/src -I../LowLayer/Hardware -I../Middleware/Resources -I../Middleware/uGFX/src/gadc -I../Middleware/uGFX/src/gaudio -I../Middleware/uGFX/src/gdisp -I../Middleware/uGFX/src/gdriver -I../Middleware/uGFX/src/gevent -I../Middleware/uGFX/src/gfile -I../Middleware/uGFX/src/ginput -I../Middleware/uGFX/src/gmisc -I../Middleware/uGFX/src/gos -I../Middleware/uGFX/src/gqueue -I../Middleware/uGFX/src/gtimer -I../Middleware/uGFX/src/gtrans -I../Middleware/uGFX/src/gwin -I../Middleware/uGFX/src/gdisp/mcufont -I../Middleware/Utility -I../HighLayer/System -I../HighLayer/GUI/Inc -I../Middleware/uGFX/drivers/gdisp/ST7735 -I../HighLayer -I../LowLayer -I../LowLayer/Hardware/Inputs -I../LowLayer/Hardware/Misc -I../LowLayer/Drivers -I../HighLayer/Gimbal -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-serialAPI-2f-os-2f-glueFreeRTOS

clean-serialAPI-2f-os-2f-glueFreeRTOS:
	-$(RM) ./serialAPI/os/glueFreeRTOS/glueFreeRTOS.cyclo ./serialAPI/os/glueFreeRTOS/glueFreeRTOS.d ./serialAPI/os/glueFreeRTOS/glueFreeRTOS.o ./serialAPI/os/glueFreeRTOS/glueFreeRTOS.su

.PHONY: clean-serialAPI-2f-os-2f-glueFreeRTOS

