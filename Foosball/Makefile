# Needs AVR-GCC compiler
CC=avr-gcc
LNK=avr-gcc
HXR=avr-objcopy

MCU=attiny2313
# Compiler flags - code is C99 standard
CFLAGS=-g -Os -mmcu=$(MCU) -std=c99 -c 
# Linker flags
LFLAGS=-g -mmcu=$(MCU) -o 
# Hexer flags
HFLAGS=-j .text -j .data -O ihex 

SOURCE=Foosball.c
OBJECT=$(SOURCE:.c=.o)
LINKED=$(OBJECT:.o=.elf)
HEX=$(LINKED:.elf=.hex)


all: $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE)
	$(LNK) $(LFLAGS) $(LINKED) $(OBJECT)
	$(HXR) $(HFLAGS) $(LINKED) $(HEX)

clean: 
	rm -rf *.elf *.o *.hex