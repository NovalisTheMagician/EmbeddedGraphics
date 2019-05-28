LD_FILE = layout.ld

CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m7 -mthumb -c -Wall -mfpu=fpv5-sp-d16 -mfloat-abi=hard -MMD -I.

LDFLAGS = --specs=nano.specs -mcpu=cortex-m7 -mthumb -mfpu=fpv5-sp-d16 -mfloat-abi=hard -T $(LD_FILE)

LIBS = -lm

OC = arm-none-eabi-objcopy
OCFLAGS = -O ihex

SOURCES := $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

EXECUTABLE = graphics

all: $(EXECUTABLE).hex

$(EXECUTABLE).elf: $(OBJECTS) $(LD_FILE)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS)

%.hex: %.elf
	$(OC) $(OCFLAGS) $< $@

-include $(OBJECTS:.o=.d)

.PHONY: clean

# for unix terminals use
#rm -f *.o *.d $(EXECUTABLE).elf $(EXECUTABLE).hex
# for windows cmd use
#del *.o *.d $(EXECUTABLE).elf $(EXECUTABLE).hex

clean:
	rm -f *.o *.d $(EXECUTABLE).elf $(EXECUTABLE).hex
	
