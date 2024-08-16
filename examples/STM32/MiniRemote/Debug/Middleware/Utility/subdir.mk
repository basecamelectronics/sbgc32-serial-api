################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middleware/Utility/printf.c 

CPP_SRCS += \
../Middleware/Utility/Utils.cpp \
../Middleware/Utility/colors.cpp \
../Middleware/Utility/gwinImgW.cpp \
../Middleware/Utility/gwinMenuPref.cpp \
../Middleware/Utility/ugfxHelper.cpp 

C_DEPS += \
./Middleware/Utility/printf.d 

OBJS += \
./Middleware/Utility/Utils.o \
./Middleware/Utility/colors.o \
./Middleware/Utility/gwinImgW.o \
./Middleware/Utility/gwinMenuPref.o \
./Middleware/Utility/printf.o \
./Middleware/Utility/ugfxHelper.o 

CPP_DEPS += \
./Middleware/Utility/Utils.d \
./Middleware/Utility/colors.d \
./Middleware/Utility/gwinImgW.d \
./Middleware/Utility/gwinMenuPref.d \
./Middleware/Utility/ugfxHelper.d 


# Each subdirectory must supply rules for building sources it contributes
Middleware/Utility/%.o Middleware/Utility/%.su: ../Middleware/Utility/%.cpp Middleware/Utility/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -DSTM32F411xx -c -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../LowLayer/Drivers/CMSIS/Include -I../LowLayer/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middleware/FreeRTOS/include -I../Middleware/FreeRTOS/portable/GCC/ARM_CM4F -I../Middleware/uGFX -I../Middleware/uGFX/src -I../LowLayer/Hardware -I../Middleware/Resources -I../Middleware/uGFX/src/gadc -I../Middleware/uGFX/src/gaudio -I../Middleware/uGFX/src/gdisp -I../Middleware/uGFX/src/gdriver -I../Middleware/uGFX/src/gevent -I../Middleware/uGFX/src/gfile -I../Middleware/uGFX/src/ginput -I../Middleware/uGFX/src/gmisc -I../Middleware/uGFX/src/gos -I../Middleware/uGFX/src/gqueue -I../Middleware/uGFX/src/gtimer -I../Middleware/uGFX/src/gtrans -I../Middleware/uGFX/src/gwin -I../Middleware/uGFX/src/gdisp/mcufont -I../Middleware/Utility -I../HighLayer/System -I../HighLayer/GUI/Inc -I../Middleware/uGFX/drivers/gdisp/ST7735 -I../HighLayer -I../LowLayer -I../LowLayer/Hardware/Inputs -I../LowLayer/Hardware/Misc -I../LowLayer/Drivers -I../HighLayer/Gimbal -I../../../../serialAPI -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middleware/Utility/%.o Middleware/Utility/%.su: ../Middleware/Utility/%.c Middleware/Utility/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -DSTM32F411xx -c -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../LowLayer/Drivers/CMSIS/Include -I../LowLayer/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../LowLayer/it -I../Middleware/FreeRTOS/include -I../Middleware/FreeRTOS/portable/GCC/ARM_CM4F -I../Middleware/uGFX -I../Middleware/uGFX/src -I../LowLayer/Hardware -I../Middleware/Resources -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middleware-2f-Utility

clean-Middleware-2f-Utility:
	-$(RM) ./Middleware/Utility/Utils.d ./Middleware/Utility/Utils.o ./Middleware/Utility/Utils.su ./Middleware/Utility/colors.d ./Middleware/Utility/colors.o ./Middleware/Utility/colors.su ./Middleware/Utility/gwinImgW.d ./Middleware/Utility/gwinImgW.o ./Middleware/Utility/gwinImgW.su ./Middleware/Utility/gwinMenuPref.d ./Middleware/Utility/gwinMenuPref.o ./Middleware/Utility/gwinMenuPref.su ./Middleware/Utility/printf.d ./Middleware/Utility/printf.o ./Middleware/Utility/printf.su ./Middleware/Utility/ugfxHelper.d ./Middleware/Utility/ugfxHelper.o ./Middleware/Utility/ugfxHelper.su

.PHONY: clean-Middleware-2f-Utility

