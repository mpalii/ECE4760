# Makefile
SOURCE		= ./src/main.c
PROJECT 	= 02_SimpleMultitasking_Correct
DEVICE 		= atmega644
PROGRAMMER 	= usbasp

default: build

build : clean
	@mkdir target
	@avr-gcc -Wall -Os -mmcu=$(DEVICE) -c $(SOURCE) -o ./target/$(PROJECT).o
	@avr-gcc -Wall -Os -mmcu=$(DEVICE) -o ./target/$(PROJECT).elf ./target/$(PROJECT).o
	@avr-objcopy -j .text -j .data -O ihex ./target/$(PROJECT).elf ./target/$(PROJECT).hex
	@echo "INFO: Build finished successfully"

disasm: target/$(PROJECT).elf
	avr-objdump -d target/$(PROJECT).elf

clean: 
	@if [ -d ./target ]; \
	then \
		rm ./target/$(PROJECT).hex ; \
		rm ./target/$(PROJECT).elf ; \
		rm ./target/$(PROJECT).o ; \
		rmdir ./target; \
		echo "INFO: Previously generated target files removed";	\
	else \
		echo "INFO: No generated target files"; \
	fi

size:
	@avr-size --format=avr --mcu=$(DEVICE) ./target/$(PROJECT).elf

check:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -v

erease:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -e

upload:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -v -U flash:w:./target/$(PROJECT).hex:i

fuse-default:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -U lfuse:w:0x62:m -U hfuse:w:0x99:m -U efuse:w:0xff:m

fuse-no-divider-ext-clk:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -U lfuse:w:0xff:m -U hfuse:w:0x99:m -U efuse:w:0xff:m
