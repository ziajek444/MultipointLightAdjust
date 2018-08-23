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
czujnik_8_.lss \

FLASH_IMAGE += \
czujnik_8_.hex \

EEPROM_IMAGE += \
czujnik_8_.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: czujnik_8_.elf secondary-outputs

# Tool invocations
czujnik_8_.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,czujnik_8_.map -mmcu=atmega8 -o "czujnik_8_.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

czujnik_8_.lss: czujnik_8_.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S czujnik_8_.elf  >"czujnik_8_.lss"
	@echo 'Finished building: $@'
	@echo ' '

czujnik_8_.hex: czujnik_8_.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex czujnik_8_.elf  "czujnik_8_.hex"
	@echo 'Finished building: $@'
	@echo ' '

czujnik_8_.eep: czujnik_8_.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex czujnik_8_.elf  "czujnik_8_.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: czujnik_8_.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 czujnik_8_.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) czujnik_8_.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
