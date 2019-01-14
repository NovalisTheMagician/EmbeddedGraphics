MEMORY 
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1024K
    RAM (rwx) : ORIGIN = 0x20010000, LENGTH = 256K
    FRAMEBUFFER (rw) : ORIGIN = 0xC0000000, LENGTH = 1200K
    SDRAM (rwx) : ORIGIN = 0xC012C000, LENGTH = 6992K
}

SECTIONS
{
    .text : 
    {
        KEEP (*(.vectors))
        *(.text .text.*)
        /**(.text .text.* .gnu.linkonce.t.*)*/
		*(.glue_7t) *(.glue_7)
        *(.rodata .rodata*)
		/**(.rodata .rodata* .gnu.linkonce.r.*)*/
    } >FLASH

    . = ALIGN(4);
    _etext = .;

    .data :
    {
        _sdata = .;
        *(.data .data.*)
        . = ALIGN(4);
        _edata = .;
    } >RAM AT >FLASH
    _sflashdata = LOADADDR(.data);

    .bss :
    {
        _sbss = .;
        __bss_start__ = .;
        *(.bss .bss.*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
        __bss_end__ = .;
    } >RAM

    .framebuf :
    {
        _sframebuf = .;
        *(.framebuffer .framebuffer.*)
        _eframebuf = .;
    } >FRAMEBUFFER

    .sdram :
    {
        _ssdram = .;
        *(.sdram .sdram.*)
        _esdram = .;
    } >SDRAM

    _estack = ORIGIN(RAM) + LENGTH(RAM);
}