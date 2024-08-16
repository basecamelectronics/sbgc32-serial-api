################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/os/glueAzureRTOS/glueAzureRTOS.c 

C_DEPS += \
./serialAPI/os/glueAzureRTOS/glueAzureRTOS.d 

OBJS += \
./serialAPI/os/glueAzureRTOS/glueAzureRTOS.o 


# Each subdirectory must supply rules for building sources it contributes
serialAPI/os/glueAzureRTOS/glueAzureRTOS.o: D:/basecam/SBGC32_Library/sbgc32-serial-api/serialAPI/os/glueAzureRTOS/glueAzureRTOS.c serialAPI/os/glueAzureRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -DSTM32F411xx -c -I../../../../serialAPI -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../LowLayer/Drivers/CMSIS/Include -I../LowLayer/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middleware/FreeRTOS/include -I../Middleware/FreeRTOS/portable/GCC/ARM_CM4F -I../Middleware/uGFX -I../Middleware/uGFX/src -I../LowLayer/Hardware -I../Middleware/Resources -I../Middleware/uGFX/src/gadc -I../Middleware/uGFX/src/gaudio -I../Middleware/uGFX/src/gdisp -I../Middleware/uGFX/src/gdriver -I../Middleware/uGFX/src/gevent -I../Middleware/uGFX/src/gfile -I../Middleware/uGFX/src/ginput -I../Middleware/uGFX/src/gmisc -I../Middleware/uGFX/src/gos -I../Middleware/uGFX/src/gqueue -I../Middleware/uGFX/src/gtimer -I../Middleware/uGFX/src/gtrans -I../Middleware/uGFX/src/gwin -I../Middleware/uGFX/src/gdisp/mcufont -I../Middleware/Utility -I../HighLayer/System -I../HighLayer/GUI/Inc -I../Middleware/uGFX/drivers/gdisp/ST7735 -I../HighLayer -I../LowLayer -I../LowLayer/Hardware/Inputs -I../LowLayer/Hardware/Misc -I../LowLayer/Drivers -I../HighLayer/Gimbal -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-serialAPI-2f-os-2f-glueAzureRTOS

clean-serialAPI-2f-os-2f-glueAzureRTOS:
	-$(RM) ./serialAPI/os/glueAzureRTOS/glueAzureRTOS.d ./serialAPI/os/glueAzureRTOS/glueAzureRTOS.o ./serialAPI/os/glueAzureRTOS/glueAzureRTOS.su

.PHONY: clean-serialAPI-2f-os-2f-glueAzureRTOS

