all: delorean.hex

delorean.hex: delorean.c motores.c boxes.c
	avr-gcc -O -mmcu=atmega8 -Wall -o delorean.bin -I/usr/avr/include/ delorean.c motores.c boxes.c
	avr-objcopy -j .text -O ihex  delorean.bin delorean.hex

program: delorean.hex
	avrdude -c usbtiny -p m8 -U flash:w:delorean.hex:i

fuses:
	# 0xD9 es el default
	avrdude -c usbtiny -p m8 -U hfuse:w:0xD9:m
	# 0xE1 es el default, con oscilador interno de 1Mhz
	# 0xE4 es el default + oscilador interno de 8Mhz
	avrdude -c usbtiny -p m8 -U lfuse:w:0xE4:m

clean:
	rm  *.bin

editgvim:
	gvim -p delorean.h delorean.c motores.h motores.c board.h definiciones.h boxes.h boxes.c makefile
