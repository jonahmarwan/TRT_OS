[bits 32]
global isr0

DIVIDEBYZERO db "CPU Exception: Divide By Zero", 0
%include "./printpm.asm"
isr0:
    mov ebx, DIVIDEBYZERO
    call print_string_pm
    cli
    hlt



