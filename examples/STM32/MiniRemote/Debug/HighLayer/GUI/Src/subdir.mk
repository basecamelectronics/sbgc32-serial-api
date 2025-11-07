################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../HighLayer/GUI/Src/AdjVarEditContainerM.cpp \
../HighLayer/GUI/Src/ControlContainerM.cpp \
../HighLayer/GUI/Src/DebugConsoleContainerM.cpp \
../HighLayer/GUI/Src/MainChoiceContainerM.cpp \
../HighLayer/GUI/Src/MenuContainerM.cpp \
../HighLayer/GUI/Src/MessageWindowContainerM.cpp \
../HighLayer/GUI/Src/ParameterEditContainerM.cpp \
../HighLayer/GUI/Src/PotentiometerCalibContainerM.cpp \
../HighLayer/GUI/Src/ProfileContainerM.cpp \
../HighLayer/GUI/Src/SBGCInfoContainerM.cpp \
../HighLayer/GUI/Src/ShortcutContainerM.cpp \
../HighLayer/GUI/Src/StickCalibContainerM.cpp \
../HighLayer/GUI/Src/createWidget.cpp 

OBJS += \
./HighLayer/GUI/Src/AdjVarEditContainerM.o \
./HighLayer/GUI/Src/ControlContainerM.o \
./HighLayer/GUI/Src/DebugConsoleContainerM.o \
./HighLayer/GUI/Src/MainChoiceContainerM.o \
./HighLayer/GUI/Src/MenuContainerM.o \
./HighLayer/GUI/Src/MessageWindowContainerM.o \
./HighLayer/GUI/Src/ParameterEditContainerM.o \
./HighLayer/GUI/Src/PotentiometerCalibContainerM.o \
./HighLayer/GUI/Src/ProfileContainerM.o \
./HighLayer/GUI/Src/SBGCInfoContainerM.o \
./HighLayer/GUI/Src/ShortcutContainerM.o \
./HighLayer/GUI/Src/StickCalibContainerM.o \
./HighLayer/GUI/Src/createWidget.o 

CPP_DEPS += \
./HighLayer/GUI/Src/AdjVarEditContainerM.d \
./HighLayer/GUI/Src/ControlContainerM.d \
./HighLayer/GUI/Src/DebugConsoleContainerM.d \
./HighLayer/GUI/Src/MainChoiceContainerM.d \
./HighLayer/GUI/Src/MenuContainerM.d \
./HighLayer/GUI/Src/MessageWindowContainerM.d \
./HighLayer/GUI/Src/ParameterEditContainerM.d \
./HighLayer/GUI/Src/PotentiometerCalibContainerM.d \
./HighLayer/GUI/Src/ProfileContainerM.d \
./HighLayer/GUI/Src/SBGCInfoContainerM.d \
./HighLayer/GUI/Src/ShortcutContainerM.d \
./HighLayer/GUI/Src/StickCalibContainerM.d \
./HighLayer/GUI/Src/createWidget.d 


# Each subdirectory must supply rules for building sources it contributes
HighLayer/GUI/Src/%.o HighLayer/GUI/Src/%.su HighLayer/GUI/Src/%.cyclo: ../HighLayer/GUI/Src/%.cpp HighLayer/GUI/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -DSTM32F411xx -c -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc -I../LowLayer/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../LowLayer/Drivers/CMSIS/Include -I../LowLayer/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middleware/FreeRTOS/include -I../Middleware/FreeRTOS/portable/GCC/ARM_CM4F -I../Middleware/uGFX -I../Middleware/uGFX/src -I../LowLayer/Hardware -I../Middleware/Resources -I../Middleware/uGFX/src/gadc -I../Middleware/uGFX/src/gaudio -I../Middleware/uGFX/src/gdisp -I../Middleware/uGFX/src/gdriver -I../Middleware/uGFX/src/gevent -I../Middleware/uGFX/src/gfile -I../Middleware/uGFX/src/ginput -I../Middleware/uGFX/src/gmisc -I../Middleware/uGFX/src/gos -I../Middleware/uGFX/src/gqueue -I../Middleware/uGFX/src/gtimer -I../Middleware/uGFX/src/gtrans -I../Middleware/uGFX/src/gwin -I../Middleware/uGFX/src/gdisp/mcufont -I../Middleware/Utility -I../HighLayer/System -I../HighLayer/GUI/Inc -I../Middleware/uGFX/drivers/gdisp/ST7735 -I../HighLayer -I../LowLayer -I../LowLayer/Hardware/Inputs -I../LowLayer/Hardware/Misc -I../LowLayer/Drivers -I../HighLayer/Gimbal -I../../../../serialAPI -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-HighLayer-2f-GUI-2f-Src

clean-HighLayer-2f-GUI-2f-Src:
	-$(RM) ./HighLayer/GUI/Src/AdjVarEditContainerM.cyclo ./HighLayer/GUI/Src/AdjVarEditContainerM.d ./HighLayer/GUI/Src/AdjVarEditContainerM.o ./HighLayer/GUI/Src/AdjVarEditContainerM.su ./HighLayer/GUI/Src/ControlContainerM.cyclo ./HighLayer/GUI/Src/ControlContainerM.d ./HighLayer/GUI/Src/ControlContainerM.o ./HighLayer/GUI/Src/ControlContainerM.su ./HighLayer/GUI/Src/DebugConsoleContainerM.cyclo ./HighLayer/GUI/Src/DebugConsoleContainerM.d ./HighLayer/GUI/Src/DebugConsoleContainerM.o ./HighLayer/GUI/Src/DebugConsoleContainerM.su ./HighLayer/GUI/Src/MainChoiceContainerM.cyclo ./HighLayer/GUI/Src/MainChoiceContainerM.d ./HighLayer/GUI/Src/MainChoiceContainerM.o ./HighLayer/GUI/Src/MainChoiceContainerM.su ./HighLayer/GUI/Src/MenuContainerM.cyclo ./HighLayer/GUI/Src/MenuContainerM.d ./HighLayer/GUI/Src/MenuContainerM.o ./HighLayer/GUI/Src/MenuContainerM.su ./HighLayer/GUI/Src/MessageWindowContainerM.cyclo ./HighLayer/GUI/Src/MessageWindowContainerM.d ./HighLayer/GUI/Src/MessageWindowContainerM.o ./HighLayer/GUI/Src/MessageWindowContainerM.su ./HighLayer/GUI/Src/ParameterEditContainerM.cyclo ./HighLayer/GUI/Src/ParameterEditContainerM.d ./HighLayer/GUI/Src/ParameterEditContainerM.o ./HighLayer/GUI/Src/ParameterEditContainerM.su ./HighLayer/GUI/Src/PotentiometerCalibContainerM.cyclo ./HighLayer/GUI/Src/PotentiometerCalibContainerM.d ./HighLayer/GUI/Src/PotentiometerCalibContainerM.o ./HighLayer/GUI/Src/PotentiometerCalibContainerM.su ./HighLayer/GUI/Src/ProfileContainerM.cyclo ./HighLayer/GUI/Src/ProfileContainerM.d ./HighLayer/GUI/Src/ProfileContainerM.o ./HighLayer/GUI/Src/ProfileContainerM.su ./HighLayer/GUI/Src/SBGCInfoContainerM.cyclo ./HighLayer/GUI/Src/SBGCInfoContainerM.d ./HighLayer/GUI/Src/SBGCInfoContainerM.o ./HighLayer/GUI/Src/SBGCInfoContainerM.su ./HighLayer/GUI/Src/ShortcutContainerM.cyclo ./HighLayer/GUI/Src/ShortcutContainerM.d ./HighLayer/GUI/Src/ShortcutContainerM.o ./HighLayer/GUI/Src/ShortcutContainerM.su ./HighLayer/GUI/Src/StickCalibContainerM.cyclo ./HighLayer/GUI/Src/StickCalibContainerM.d ./HighLayer/GUI/Src/StickCalibContainerM.o ./HighLayer/GUI/Src/StickCalibContainerM.su ./HighLayer/GUI/Src/createWidget.cyclo ./HighLayer/GUI/Src/createWidget.d ./HighLayer/GUI/Src/createWidget.o ./HighLayer/GUI/Src/createWidget.su

.PHONY: clean-HighLayer-2f-GUI-2f-Src

