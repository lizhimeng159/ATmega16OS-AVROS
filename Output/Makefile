###############################################################################
# Makefile for the project ATmega16OS
###############################################################################

## General Flags
PROJECT = ATmega16OS
MCU = atmega16
TARGET = ATmega16OS.elf
CC = avr-gcc

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2                     -DF_CPU=16000000  -Os  -funsigned-char  -funsigned-bitfields  -fpack-struct  -fshort-enums
CFLAGS += -Wp,-M,-MP,-MT,$(*F).o,-MF,dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=ATmega16OS.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0


## Include Directories
INCLUDES = -I"C:\Users\Administrator\Desktop\ATmega16OS工程\ATmega16OS\ATmega16OS" -I"C:\Users\Administrator\Desktop\ATmega16OS工程\ATmega16OS\User" -I"C:\Users\Administrator\Desktop\ATmega16OS工程\ATmega16OS\Device\Delay" -I"C:\Users\Administrator\Desktop\ATmega16OS工程\ATmega16OS\Device\LED" -I"C:\Users\Administrator\Desktop\ATmega16OS工程\ATmega16OS\Device\74HC595" -I"C:\Users\Administrator\Desktop\ATmega16OS工程\ATmega16OS\Device\Tube" -I"C:\Users\Administrator\Desktop\ATmega16OS工程\ATmega16OS\Device\PWM" 

## Objects that must be built in order to link
OBJECTS = Main.o ATmega16OS.o 74HC595.o Delay.o tube.o App.o PWM.o 

## Build
all: $(TARGET) ATmega16OS.hex ATmega16OS.eep ATmega16OS.lss

## Compile
Main.o: ../User/Main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c   $< -o $@

ATmega16OS.o: ../ATmega16OS/ATmega16OS.c
	$(CC) $(INCLUDES) $(CFLAGS) -c   $< -o $@

74HC595.o: ../Device/74HC595/74HC595.c
	$(CC) $(INCLUDES) $(CFLAGS) -c   $< -o $@

Delay.o: ../Device/Delay/Delay.c
	$(CC) $(INCLUDES) $(CFLAGS) -c   $< -o $@

tube.o: ../Device/Tube/tube.c
	$(CC) $(INCLUDES) $(CFLAGS) -c   $< -o $@

App.o: ../User/App.c
	$(CC) $(INCLUDES) $(CFLAGS) -c   $< -o $@

PWM.o: ../Device/PWM/PWM.c
	$(CC) $(INCLUDES) $(CFLAGS) -c   $< -o $@

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) ATmega16OS.elf dep/ ATmega16OS.hex ATmega16OS.eep ATmega16OS.lss ATmega16OS.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

