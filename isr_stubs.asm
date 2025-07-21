[bits 32]
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31
DIVIDEBYZERO db "CPU Exception: Divide By Zero", 0
DEBUG db "CPU Exception: Debug Error", 0
NONMASKABLE db "CPU Exception: Non Maskable Interrupt", 0
BREAKPOINT db "CPU Exception: Breakpoint", 0
OVERFLOW db "CPU Exception: Into Detected Overflow", 0
OUTOFBOUNDS db "CPU Exception: Out of Bounds", 0
INVALIDOPCODE db "CPU Exception: Invalid Opcode", 0
NOCOPROCESSOR db "CPU Exception: No Coprocessor", 0
DOUBLEFAULT db "CPU Exception: Double Fault", 0
SEGOVERRUN db "CPU Exception: Coprocessor Segment Overrun", 0
BADTSS db "CPU Exception: Bad TSS", 0
SEGNOTPRESENT db "CPU Exception: Segment Not Present", 0
STACKFAULT db "CPU Exception: Stack Fault", 0
PROTECTIONFAULT db "CPU Exception: General Protection Fault", 0
PAGEFAULT db "CPU Exception: Page Fault", 0
UNKNOWNINT db "CPU Exception: Unknown Interrupt", 0
COPROCESSORFAULT db "CPU Exception: Coprocessor Fault"
ALIGNMENTCHECK db "CPU Exception: Alignment Check", 0
MACHINECHECK db "CPU Exception: Machine Check", 0
RESERVED db "CPU Exception: Reserved", 0
%include "./printpm.asm"

%macro isr_common_stub 1
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10 
    mov ds, ax
    mov fs, ax
    mov gs, ax
    mov es, ax

    mov ebx, %1
    call print_string_pm

    pop eax
    mov ds, ax
    mov fs, ax
    mov gs, ax
    mov es, ax
    popa
    add esp, 8
    sti
    iret
%endmacro


isr0: 
    cli
    push byte 0
    push byte 0 
    isr_common_stub DIVIDEBYZERO

isr1:
    cli
    push byte 0
    push byte 1
    isr_common_stub DEBUG 

isr2:
    cli
    push byte 0
    push byte 2
    isr_common_stub NONMASKABLE

isr3:
    cli
    push byte 0 
    push byte 3
    isr_common_stub BREAKPOINT

isr4:
    cli
    push byte 0
    push byte 4
    isr_common_stub OVERFLOW

isr5:
    cli
    push byte 0
    push byte 5
    isr_common_stub OUTOFBOUNDS
 
isr6: 
    cli
    push byte 0
    push byte 6
    isr_common_stub INVALIDOPCODE
 
isr7:
    cli
    push byte 0
    push byte 7
    isr_common_stub NOCOPROCESSOR

isr8: 
    cli
    push byte 0
    push byte 8
    isr_common_stub DOUBLEFAULT

isr9:
    cli
    push byte 0
    push byte 9
    isr_common_stub SEGOVERRUN

isr10:
    cli
    push byte 0
    push byte 10
    isr_common_stub BADTSS

isr11:
    cli 
    push byte 0
    push byte 11
    isr_common_stub SEGNOTPRESENT

isr12:
    cli
    push byte 0
    push byte 12
    isr_common_stub STACKFAULT

isr13:
    cli
    push byte 0
    push byte 13
    isr_common_stub PROTECTIONFAULT

isr14:
    cli
    push byte 0
    push byte 14
    isr_common_stub PAGEFAULT

isr15:
    cli
    push byte 0
    push byte 15
    isr_common_stub UNKNOWNINT

isr16:
    cli
    push byte 0
    push byte 16
    isr_common_stub COPROCESSORFAULT

isr17:
    cli
    push byte 0
    push byte 17
    isr_common_stub ALIGNMENTCHECK

isr18:
    cli
    push byte 0
    push byte 18
    isr_common_stub MACHINECHECK

isr19:
    cli
    push byte 0
    push byte 19
    isr_common_stub RESERVED

isr20:
    cli
    push byte 0
    push byte 20
    isr_common_stub RESERVED

isr21:
    cli
    push byte 0
    push byte 21
    isr_common_stub RESERVED

isr22:
    cli
    push byte 0
    push byte 22
    isr_common_stub RESERVED


isr23:
    cli
    push byte 0
    push byte 23
    isr_common_stub RESERVED

isr24:
    cli
    push byte 0
    push byte 24
    isr_common_stub RESERVED

isr25:
    cli
    push byte 0
    push byte 25
    isr_common_stub RESERVED

isr26:
    cli
    push byte 0
    push byte 26
    isr_common_stub RESERVED

isr27:
    cli
    push byte 0
    push byte 27
    isr_common_stub RESERVED


isr28:
    cli
    push byte 0
    push byte 28
    isr_common_stub RESERVED

isr29:
    cli
    push byte 0
    push byte 29
    isr_common_stub RESERVED

isr30:
    cli
    push byte 0
    push byte 30
    isr_common_stub RESERVED

isr31:
    cli
    push byte 0
    push byte 31
    isr_common_stub RESERVED
