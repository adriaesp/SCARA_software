################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../drivers/include/ \
../drivers \
../drivers/src/


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../drivers/src/hardware_config.c \
../drivers/src/moviment.c \
../drivers/src/timer0_delay.c \
../main.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
drivers/src/hardware_config.o \
drivers/src/moviment.o \
drivers/src/timer0_delay.o \
main.o

OBJS_AS_ARGS +=  \
drivers/src/hardware_config.o \
drivers/src/moviment.o \
drivers/src/timer0_delay.o \
main.o

C_DEPS +=  \
drivers/src/hardware_config.d \
drivers/src/moviment.d \
drivers/src/timer0_delay.d \
main.d

C_DEPS_AS_ARGS +=  \
drivers/src/hardware_config.d \
drivers/src/moviment.d \
drivers/src/timer0_delay.d \
main.d

OUTPUT_FILE_PATH +=v1.elf

OUTPUT_FILE_PATH_AS_ARGS +=v1.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
drivers/src/hardware_config.o: ../drivers/src/hardware_config.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Users\adrie\Programes\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Users\adrie\Programes\7.0\Packs\atmel\ATmega_DFP\1.7.374\include" -I"..\/drivers/include" -I"..\/drivers/src"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega328pb -B "C:\Users\adrie\Programes\7.0\Packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega328pb" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

drivers/src/moviment.o: ../drivers/src/moviment.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Users\adrie\Programes\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Users\adrie\Programes\7.0\Packs\atmel\ATmega_DFP\1.7.374\include" -I"..\/drivers/include" -I"..\/drivers/src"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega328pb -B "C:\Users\adrie\Programes\7.0\Packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega328pb" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

drivers/src/timer0_delay.o: ../drivers/src/timer0_delay.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Users\adrie\Programes\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Users\adrie\Programes\7.0\Packs\atmel\ATmega_DFP\1.7.374\include" -I"..\/drivers/include" -I"..\/drivers/src"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega328pb -B "C:\Users\adrie\Programes\7.0\Packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega328pb" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./main.o: .././main.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Users\adrie\Programes\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Users\adrie\Programes\7.0\Packs\atmel\ATmega_DFP\1.7.374\include" -I"..\/drivers/include" -I"..\/drivers/src"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega328pb -B "C:\Users\adrie\Programes\7.0\Packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega328pb" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 5.4.0
	$(QUOTE)C:\Users\adrie\Programes\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="v1.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega328pb -B "C:\Users\adrie\Programes\7.0\Packs\atmel\ATmega_DFP\1.7.374\gcc\dev\atmega328pb"  
	@echo Finished building target: $@
	"C:\Users\adrie\Programes\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "v1.elf" "v1.hex"
	"C:\Users\adrie\Programes\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "v1.elf" "v1.eep" || exit 0
	"C:\Users\adrie\Programes\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "v1.elf" > "v1.lss"
	"C:\Users\adrie\Programes\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "v1.elf" "v1.srec"
	"C:\Users\adrie\Programes\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "v1.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "v1.elf" "v1.a" "v1.hex" "v1.lss" "v1.eep" "v1.map" "v1.srec" "v1.usersignatures"
	