################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middleware/uGFX/src/gdisp/gdisp_pixmap.c 

C_DEPS += \
./Middleware/uGFX/src/gdisp/gdisp_pixmap.d 

OBJS += \
./Middleware/uGFX/src/gdisp/gdisp_pixmap.o 


# Each subdirectory must supply rules for building sources it contributes
Middleware/uGFX/src/gdisp/%.o Middleware/uGFX/src/gdisp/%.su: ../Middleware/uGFX/src/gdisp/%.c Middleware/uGFX/src/gdisp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -DSTM32F411xx -c -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../LowLayer/Drivers/CMSIS/Include -I../LowLayer/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../LowLayer/it -I../Middleware/FreeRTOS/include -I../Middleware/FreeRTOS/portable/GCC/ARM_CM4F -I../Middleware/uGFX -I../Middleware/uGFX/src -I../LowLayer/Hardware -I../Middleware/Resources -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middleware-2f-uGFX-2f-src-2f-gdisp

clean-Middleware-2f-uGFX-2f-src-2f-gdisp:
	-$(RM) ./Middleware/uGFX/src/gdisp/gdisp_pixmap.d ./Middleware/uGFX/src/gdisp/gdisp_pixmap.o ./Middleware/uGFX/src/gdisp/gdisp_pixmap.su

.PHONY: clean-Middleware-2f-uGFX-2f-src-2f-gdisp

