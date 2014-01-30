CLK = 8000000UL

# TARGET es el nombre del proyecto
TARGET = delorean

# MMCU es el microcontralador para el target para el avr-gcc
# Para ver el listado de posibles opciones hacer:
#      avrdude -p ?
MMCU = atmega88

# TARGET_P es el microcontrolador para el target del programador
# Para el Atemga8: m8
# Para ver el listado de posibles opciones ir a:
#      http://avr-libc.nongnu.org/user-manual/index.html
TARGET_P = m88

# HFUSE 
# Para el Atmega8 0xD9 es el default  (pagina 223)
# Para el Atmega88 0xDF es el default  (pagina 286)
HFUSE = 0xDF

# LFUSE
# Para el Atemega8:  (pagina 224)
# 0xE1 es el default, con oscilador interno de 1Mhz
# 0xE4 es el default + oscilador interno de 8Mhz
# Para el Atemega88:  (pagina 287)
# 0x62 es el default, con oscilador interno de 1Mhz
# 0xE2 es el default + oscilador interno de 8Mhz
LFUSE = 0xE2

# SRC contiene el nombre de todos los .c existentes en el directorio actual
SRC = delorean.c motores.c sensores.c

# INC contiene el nombre de todos los .h existentes en el directorio actual
INC = delorean.h motores.h board.h sensores.h definiciones.h

# Flags de optimizacion '-Os' tamaño '-O3' velocidad
# Si se deja -O vacio el compilador elige '-01'
CFLAGS = -O2 -Wall

CDEFINES = -DF_CPU=$(CLK)

all: hex

hex: $(SRC) $(INC)
	avr-gcc $(CFLAGS) $(CDEFINES) -mmcu=$(MMCU) -o $(TARGET).bin -I/usr/avr/include/ $(SRC)
	avr-objcopy -j .text -j .data -O ihex  $(TARGET).bin $(TARGET).hex
	avr-objdump -h -S $(TARGET).bin > "$(TARGET).lst"
	av-size -d --format=avr --mcu=$(MMCU) $(TARGET).bin
	avr-size $(TARGET).bin

program: hex
	avrdude -c usbtiny -p $(TARGET_P) -U flash:w:$(TARGET).hex:i

fuses:
	avrdude -c usbtiny -p $(TARGET_P) -U hfuse:w:$(HFUSE):m
	avrdude -c usbtiny -p $(TARGET_P) -U lfuse:w:$(LFUSE):m

clean:
	rm -rf $(TARGET).hex $(TARGET).bin $(TARGET).lst

editgvim:
	gvim -p $(SRC) $(INC) Makefile

eepromread:
	avrdude -c usbtiny -p $(TARGET_P) -U eeprom:r:eeprom.hex:i

eepromwrite:
	avrdude -c usbtiny -p $(TARGET_P) -U eeprom:w:eeprom.hex:i
