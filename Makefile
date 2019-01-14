CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m7 -mthumb -c -Wall -mfpu=fpv5-d16 -mfloat-abi=hard -MMD -I.

LD = arm-none-eabi-ld
LDFLAGS = --specs=nano.specs -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard -T layout.ld

OC = arm-none-eabi-objcopy
OCFLAGS = -O ihex

SOURCES = startup.c gpio.c sdram.c rcc.c tft.c spi.c renderer.c delay.c main.c systick.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = graphics

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@.elf $(OBJECTS)
	$(OC) $(OCFLAGS) $@.elf $@.hex

.c.o: 
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm *.o
	rm *.hex
	rm *.elf
