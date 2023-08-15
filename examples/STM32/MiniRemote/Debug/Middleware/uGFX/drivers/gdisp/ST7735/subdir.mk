################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middleware/uGFX/drivers/gdisp/ST7735/gdisp_lld_ST7735.c 

C_DEPS += \
./Middleware/uGFX/drivers/gdisp/ST7735/gdisp_lld_ST7735.d 

OBJS += \
./Middleware/uGFX/drivers/gdisp/ST7735/gdisp_lld_ST7735.o 


# Each subdirectory must supply rules for building sources it contributes
Middleware/uGFX/drivers/gdisp/ST7735/%.o Middleware/uGFX/drivers/gdisp/ST7735/%.su: ../Middleware/uGFX/drivers/gdisp/ST7735/%.c Middleware/uGFX/drivers/gdisp/ST7735/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -DSTM32F411xx -c -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../LowLayer/Drivers/CMSIS/Include -I../LowLayer/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../LowLayer/Inc -I../LowLayer/it -I../LowLayer/SBGC32_Driver -I../HighLayer/main -I../Middleware/FreeRTOS/include -I../Middleware/FreeRTOS/portable/GCC/ARM_CM4F -I../LowLayer/Drivers/Inc -I../Middleware/uGFX -I../Middleware/uGFX/src -I../LowLayer/Hardware -I../Middleware/Resources -I../Middleware/Resources/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middleware-2f-uGFX-2f-drivers-2f-gdisp-2f-ST7735

clean-Middleware-2f-uGFX-2f-drivers-2f-gdisp-2f-ST7735:
	-$(RM) ./Middleware/uGFX/drivers/gdisp/ST7735/gdisp_lld_ST7735.d ./Middleware/uGFX/drivers/gdisp/ST7735/gdisp_lld_ST7735.o ./Middleware/uGFX/drivers/gdisp/ST7735/gdisp_lld_ST7735.su

.PHONY: clean-Middleware-2f-uGFX-2f-drivers-2f-gdisp-2f-ST7735

