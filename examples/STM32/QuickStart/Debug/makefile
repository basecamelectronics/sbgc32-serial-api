################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include serialAPI/os/glueLinuxOS/subdir.mk
-include serialAPI/os/glueFreeRTOS/subdir.mk
-include serialAPI/os/glueAzureRTOS/subdir.mk
-include serialAPI/modules/service/subdir.mk
-include serialAPI/modules/realtime/subdir.mk
-include serialAPI/modules/profiles/subdir.mk
-include serialAPI/modules/imu/subdir.mk
-include serialAPI/modules/gimbalControl/subdir.mk
-include serialAPI/modules/eeprom/subdir.mk
-include serialAPI/modules/calib/subdir.mk
-include serialAPI/modules/adjvar/subdir.mk
-include serialAPI/drivers/driverSTM32/subdir.mk
-include serialAPI/drivers/driverLinux/subdir.mk
-include serialAPI/core/parser/subdir.mk
-include serialAPI/core/highLayer/subdir.mk
-include serialAPI/core/debug/subdir.mk
-include serialAPI/core/subdir.mk
-include serialAPI/subdir.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := SBGC32_QuickStart
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
SBGC32_QuickStart.elf \

MAP_FILES += \
SBGC32_QuickStart.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
SBGC32_QuickStart.list \


# All Target
all: main-build

# Main-build Target
main-build: SBGC32_QuickStart.elf secondary-outputs

# Tool invocations
SBGC32_QuickStart.elf SBGC32_QuickStart.map: $(OBJS) $(USER_OBJS) D:\basecam\SBGC32_Library\sbgc32-serial-api\examples\STM32\QuickStart\STM32F767ZITX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "SBGC32_QuickStart.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"D:\basecam\SBGC32_Library\sbgc32-serial-api\examples\STM32\QuickStart\STM32F767ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="SBGC32_QuickStart.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

SBGC32_QuickStart.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "SBGC32_QuickStart.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) SBGC32_QuickStart.elf SBGC32_QuickStart.list SBGC32_QuickStart.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
