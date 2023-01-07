# [ECE4760](http://people.ece.cornell.edu/land/courses/ece4760/)  

[Old AVR-based home page](http://people.ece.cornell.edu/land/courses/ece4760/index_2015_atmega1284.html)  
[Old Homework](http://people.ece.cornell.edu/land/courses/ece4760/homework/oldhomework.html)  
See Spring 2012  

check:  
	avrdude -c usbasp -p atmega328p -v  

erease:  
	avrdude -c usbasp -p atmega328p -e  

upload:  
	avrdude -c usbasp -p atmega328p -v -U flash:w:./target/$(PROJECT).hex:i  

fuse-no-divider:  
	avrdude -c usbasp -p atmega328p -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m  

fuse-no-divider-ext-clk:  
	avrdude -c usbasp -p atmega328p -U lfuse:w:0xff:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m  
