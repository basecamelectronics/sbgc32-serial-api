################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middleware/FreeRTOS/croutine.c \
../Middleware/FreeRTOS/event_groups.c \
../Middleware/FreeRTOS/list.c \
../Middleware/FreeRTOS/queue.c \
../Middleware/FreeRTOS/stream_buffer.c \
../Middleware/FreeRTOS/tasks.c \
../Middleware/FreeRTOS/timers.c 

C_DEPS += \
./Middleware/FreeRTOS/croutine.d \
./Middleware/FreeRTOS/event_groups.d \
./Middleware/FreeRTOS/list.d \
./Middleware/FreeRTOS/queue.d \
./Middleware/FreeRTOS/stream_buffer.d \
./Middleware/FreeRTOS/tasks.d \
./Middleware/FreeRTOS/timers.d 

OBJS += \
./Middleware/FreeRTOS/croutine.o \
./Middleware/FreeRTOS/event_groups.o \
./Middleware/FreeRTOS/list.o \
./Middleware/FreeRTOS/queue.o \
./Middleware/FreeRTOS/stream_buffer.o \
./Middleware/FreeRTOS/tasks.o \
./Middleware/FreeRTOS/timers.o 


# Each subdirectory must supply rules for building sources it contributes
Middleware/FreeRTOS/%.o Middleware/FreeRTOS/%.su Middleware/FreeRTOS/%.cyclo: ../Middleware/FreeRTOS/%.c Middleware/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -DSTM32F411xx -c -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../LowLayer/Drivers/CMSIS/Include -I../LowLayer/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../LowLayer/it -I../Middleware/FreeRTOS/include -I../Middleware/FreeRTOS/portable/GCC/ARM_CM4F -I../Middleware/uGFX -I../Middleware/uGFX/src -I../LowLayer/Hardware -I../Middleware/Resources -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middleware-2f-FreeRTOS

clean-Middleware-2f-FreeRTOS:
	-$(RM) ./Middleware/FreeRTOS/croutine.cyclo ./Middleware/FreeRTOS/croutine.d ./Middleware/FreeRTOS/croutine.o ./Middleware/FreeRTOS/croutine.su ./Middleware/FreeRTOS/event_groups.cyclo ./Middleware/FreeRTOS/event_groups.d ./Middleware/FreeRTOS/event_groups.o ./Middleware/FreeRTOS/event_groups.su ./Middleware/FreeRTOS/list.cyclo ./Middleware/FreeRTOS/list.d ./Middleware/FreeRTOS/list.o ./Middleware/FreeRTOS/list.su ./Middleware/FreeRTOS/queue.cyclo ./Middleware/FreeRTOS/queue.d ./Middleware/FreeRTOS/queue.o ./Middleware/FreeRTOS/queue.su ./Middleware/FreeRTOS/stream_buffer.cyclo ./Middleware/FreeRTOS/stream_buffer.d ./Middleware/FreeRTOS/stream_buffer.o ./Middleware/FreeRTOS/stream_buffer.su ./Middleware/FreeRTOS/tasks.cyclo ./Middleware/FreeRTOS/tasks.d ./Middleware/FreeRTOS/tasks.o ./Middleware/FreeRTOS/tasks.su ./Middleware/FreeRTOS/timers.cyclo ./Middleware/FreeRTOS/timers.d ./Middleware/FreeRTOS/timers.o ./Middleware/FreeRTOS/timers.su

.PHONY: clean-Middleware-2f-FreeRTOS

