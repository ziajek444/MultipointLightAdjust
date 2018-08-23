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
Sterownik_32.lss \

FLASH_IMAGE += \
Sterownik_32.hex \

EEPROM_IMAGE += \
Sterownik_32.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Sterownik_32.elf secondary-outputs

# Tool invocations
Sterownik_32.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Sterownik_32.map -mmcu=atmega32 -o "Sterownik_32.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Sterownik_32.lss: Sterownik_32.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Sterownik_32.elf  >"Sterownik_32.lss"
	@echo 'Finished building: $@'
	@echo ' '

Sterownik_32.hex: Sterownik_32.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Sterownik_32.elf  "Sterownik_32.hex"
	@echo 'Finished building: $@'
	@echo ' '

Sterownik_32.eep: Sterownik_32.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Sterownik_32.elf  "Sterownik_32.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Sterownik_32.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Sterownik_32.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Sterownik_32.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
