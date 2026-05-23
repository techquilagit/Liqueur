ENTRY(startk)
SECTIONS
{
    /* Начинаем строго с 1 МБ (0x00100000) */
    . = 1M;

    /* Выделяем под заголовок отдельную секцию на самом первом месте */
    .multiboot2 : ALIGN(8) {
        KEEP(*(.multiboot2))
    }

    /* Весь остальной код пойдет сразу следом */
    .text : ALIGN(8) {
        *(.text)
    }

    .rodata : { *(.rodata) }
    .data   : { *(.data) }
    .bss    : { *(.bss) }
}
