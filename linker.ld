ENTRY(startk)
SECTIONS
{
    . = 1M;
    .multiboot2 : ALIGN(8) {
        KEEP(*(.multiboot2))
    }
    .text : ALIGN(8) {
        *(.text)
    }

    .rodata : { *(.rodata) }
    .data   : { *(.data) }
    .bss    : { *(.bss) }
}
