################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include serialAPI/sources/service/subdir.mk
-include serialAPI/sources/realtime/subdir.mk
-include serialAPI/sources/profiles/subdir.mk
-include serialAPI/sources/imu/subdir.mk
-include serialAPI/sources/gimbalControl/subdir.mk
-include serialAPI/sources/eeprom/subdir.mk
-include serialAPI/sources/core/subdir.mk
-include serialAPI/sources/calib/subdir.mk
-include serialAPI/sources/adjvar/subdir.mk
-include serialAPI/drivers/STM32_Driver/subdir.mk
-include serialAPI/drivers/LinuxDriver/subdir.mk
-include serialAPI/drivers/ArduinoDriver/subdir.mk
-include serialAPI/subdir.mk
-include Middleware/uGFX/src/gdisp/subdir.mk
-include Middleware/uGFX/src/subdir.mk
-include Middleware/uGFX/drivers/gdisp/ST7735/subdir.mk
-include Middleware/Utility/subdir.mk
-include Middleware/Resources/subdir.mk
-include Middleware/FreeRTOS/portable/MemMang/subdir.mk
-include Middleware/FreeRTOS/portable/GCC/ARM_CM4F/subdir.mk
-include Middleware/FreeRTOS/subdir.mk
-include LowLayer/it/subdir.mk
-include LowLayer/Hardware/Misc/subdir.mk
-include LowLayer/Hardware/Inputs/subdir.mk
-include LowLayer/Hardware/subdir.mk
-include LowLayer/Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include LowLayer/Drivers/subdir.mk
-include HighLayer/System/subdir.mk
-include HighLayer/Gimbal/subdir.mk
-include HighLayer/GUI/Src/subdir.mk
-include HighLayer/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := MiniRemote
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
MiniRemote.elf \

MAP_FILES += \
MiniRemote.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
MiniRemote.list \

OBJCOPY_BIN += \
MiniRemote.bin \


# All Target
all: main-build

# Main-build Target
main-build: MiniRemote.elf secondary-outputs

# Tool invocations
MiniRemote.elf MiniRemote.map: $(OBJS) $(USER_OBJS) D:\basecam\SBGC32_Library\sbgc32-serial-api\examples\STM32\MiniRemote\STM32F411CEUX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-g++ -o "MiniRemote.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\basecam\SBGC32_Library\sbgc32-serial-api\examples\STM32\MiniRemote\STM32F411CEUX_FLASH.ld" -Wl,-Map="MiniRemote.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

MiniRemote.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "MiniRemote.list"
	@echo 'Finished building: $@'
	@echo ' '

MiniRemote.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "MiniRemote.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) MiniRemote.bin MiniRemote.elf MiniRemote.list MiniRemote.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
