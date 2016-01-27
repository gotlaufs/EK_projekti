# Thanks to funkfinger for the Makefile
# original available at https://gist.github.com/funkfinger/943607

# Needs gcc-avr and avr-libc packages
# In Ubuntu/Debian/Mint, execute the following command to get these packages
# sudo apt-get install avr-libc gcc-avr

DEVICE     = attiny24
CLOCK      = 1000000
PROGRAMMER = -c avrispmkII
PROJ_NAME  = Dice_code
OBJECTS    = $(PROJ_NAME).o

AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

all:	$(PROJ_NAME).hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:$(PROJ_NAME).hex:i

install: flash

load: all
	bootloadHID $(PROJ_NAME).hex

clean:
	rm -f $(PROJ_NAME).hex $(PROJ_NAME).elf $(OBJECTS)

$(PROJ_NAME).elf: $(OBJECTS)
	$(COMPILE) -o $(PROJ_NAME).elf $(OBJECTS)

$(PROJ_NAME).hex: $(PROJ_NAME).elf
	rm -f $(PROJ_NAME).hex
	avr-objcopy -j .text -j .data -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex

disasm:	$(PROJ_NAME).elf
	avr-objdump -d $(PROJ_NAME).elf

cpp:
	$(COMPILE) -E $(PROJ_NAME).c