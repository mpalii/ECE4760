# Makefile
SOURCES		= $(wildcard *.c)
OBJECTS 	= $(SOURCES:.c=.o)
DEVICE 		= atmega644
PROGRAMMER 	= usbasp



default: build

build : clean
	@mkdir target
	@avr-gcc -Wall -Os -mmcu=$(DEVICE) -c $(SOURCES) -o ./target/$(OBJECTS).o

disasm: target/$(OBJECTS).elf
	avr-objdump -d target/$(OBJECTS).elf

clean: 
	@if [ -d ./target ]; \
	then \
		rm ./target/$(OBJECTS).hex ; \
		rm ./target/$(OBJECTS).elf ; \
		rm ./target/$(OBJECTS).o ; \
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
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -v -U flash:w:./target/$(OBJECTS).hex:i

fuse-default:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -U lfuse:w:0x62:m -U hfuse:w:0x99:m -U efuse:w:0xff:m

fuse-no-divider-ext-clk:
	@avrdude -c $(PROGRAMMER) -p $(DEVICE) -U lfuse:w:0xff:m -U hfuse:w:0x99:m -U efuse:w:0xff:m

	
	@avr-gcc -Wall -Os -mmcu=$(DEVICE) -o ./target/$(OBJECTS).elf ./target/$(OBJECTS).o
	@avr-objcopy -j .text -j .data -O ihex ./target/$(OBJECTS).elf ./target/$(OBJECTS).hex
	@echo "INFO: Build finished successfully"
