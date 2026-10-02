ENTRY(_start)

SECTIONS
{
    /* Replace 0x100000 with the exact address your bootloader loads the kernel to */
    . = 0x100000;

    .text : AT(ADDR(.text))
    {
        /* Forces the main function to the very front of the executable section */
        *(.text._start)
        *(.text .text.*)
    }

    .rodata : { *(.rodata .rodata.*) }
    .data   : { *(.data .data.*) }
    .bss    : { *(.bss .bss.*) }
}
