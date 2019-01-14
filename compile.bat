arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -nostdlib -c -o crt0.o blink.c
arm-none-eabi-ld -T layout.ld -o crt0.elf crt0.o
arm-none-eabi-objcopy -O ihex -R .eeprom crt0.elf crt0.hex