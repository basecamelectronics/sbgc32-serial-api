################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middleware/uGFX/src/gfx_mk.c 

C_DEPS += \
./Middleware/uGFX/src/gfx_mk.d 

OBJS += \
./Middleware/uGFX/src/gfx_mk.o 


# Each subdirectory must supply rules for building sources it contributes
Middleware/uGFX/src/%.o Middleware/uGFX/src/%.su Middleware/uGFX/src/%.cyclo: ../Middleware/uGFX/src/%.c Middleware/uGFX/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -DSTM32F411xx -c -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../LowLayer/Drivers/CMSIS/Include -I../LowLayer/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../LowLayer/it -I../Middleware/FreeRTOS/include -I../Middleware/FreeRTOS/portable/GCC/ARM_CM4F -I../Middleware/uGFX -I../Middleware/uGFX/src -I../LowLayer/Hardware -I../Middleware/Resources -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middleware-2f-uGFX-2f-src

clean-Middleware-2f-uGFX-2f-src:
	-$(RM) ./Middleware/uGFX/src/gfx_mk.cyclo ./Middleware/uGFX/src/gfx_mk.d ./Middleware/uGFX/src/gfx_mk.o ./Middleware/uGFX/src/gfx_mk.su

.PHONY: clean-Middleware-2f-uGFX-2f-src

