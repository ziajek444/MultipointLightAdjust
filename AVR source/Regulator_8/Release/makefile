################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
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
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Regulator_8.lss \

FLASH_IMAGE += \
Regulator_8.hex \

EEPROM_IMAGE += \
Regulator_8.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Regulator_8.elf secondary-outputs

# Tool invocations
Regulator_8.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Regulator_8.map -mmcu=atmega8 -o "Regulator_8.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Regulator_8.lss: Regulator_8.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Regulator_8.elf  >"Regulator_8.lss"
	@echo 'Finished building: $@'
	@echo ' '

Regulator_8.hex: Regulator_8.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Regulator_8.elf  "Regulator_8.hex"
	@echo 'Finished building: $@'
	@echo ' '

Regulator_8.eep: Regulator_8.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Regulator_8.elf  "Regulator_8.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Regulator_8.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 Regulator_8.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Regulator_8.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
