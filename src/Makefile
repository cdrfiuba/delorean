CLK = 8000000UL


# TARGET es el nombre del proyecto
TARGET = delorean

# MMCU es el microcontralador para el target para el avr-gcc
# Para ver el listado de posibles opciones hacer:
#      avrdude -p ?
MMCU = atmega8

# TARGET_P es el microcontrolador para el target del programador
# Para el Atemga8: m8
# Para ver el listado de posibles opciones ir a:
#      http://avr-libc.nongnu.org/user-manual/index.html
TARGET_P = m8

# HFUSE 
# Para el Atmega8 0xD9 es el default  (pagina 223)
HFUSE = 0xD9

# LFUSE
# Para el Atemega8:  (pagina 224)
# 0xE1 es el default, con oscilador interno de 1Mhz
# 0xE4 es el default + oscilador interno de 8Mhz
LFUSE = 0xE4

# SRC contiene el nombre de todos los .c existentes en el directorio actual
SRC = $(shell find . -name '*.[c]')

# INC contiene el nombre de todos los .h existentes en el directorio actual
INC = $(shell find . -name '*.[h]')

# Flags de optimizacion '-Os' tamaño '-O3' velocidad '-O0
# Si se deja -O vacio ¿elije el compilador?
CFLAGS = -O -Wall

CDEFINES = -DF_CPU=$(CLK)

all: hex

hex: $(SRC) $(INC)
	avr-gcc $(CFLAGS) $(CDEFINES) -mmcu=$(MMCU)  -o $(TARGET).bin -I/usr/avr/include/ $(SRC)
	avr-objcopy -j .text -O ihex  $(TARGET).bin $(TARGET).hex
	avr-size $(TARGET).bin

program: hex
	avrdude -c usbtiny -p $(TARGET_P) -U flash:w:$(TARGET).hex:i

asm: $(SRC) $(INC)
	avr-gcc -mmcu=$(MMCU) $(CFLAGS) -S -o $(TARGET).s $<

asmdebug: $(SRC) $(INC)
	avr-gcc -mmcu=$(MMCU) -O -S -o $(TARGET).s $<

fuses:
	avrdude -c usbtiny -p $(TARGET_P) -U hfuse:w:$(HFUSE):m
	avrdude -c usbtiny -p $(TARGET_P) -U lfuse:w:$(LFUSE):m

clean:
	rm -rf $(TARGET).hex $(TARGET).bin $(TARGET).s

editgvim:
	gvim -p $(SRC) $(INC) Makefile

