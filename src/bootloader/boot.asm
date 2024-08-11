BITS 16
ORG 0x7C00



_start:

    ; Set stack segment
    mov ax, 0x9000
    mov ss, ax
    mov sp, 0xFFFE

    ; Set data segment
    mov ax, 0x0000
    mov ds, ax

    ; Set video mode
    mov ax, 0x0003
    int 0x10

    ;Boot kernel from drive
    mov ax, 0x7e00
    mov es, ax
    mov ah, 0x02
    mov al, 10
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, 0x80
    mov bx, 0x0000
    int 0x13


; GDT
gdt_start:

    ; Null Descriptor
    dd 0x00000000, 0x00000000

    ; Kernel mode Code segment
    dw 0x0000
    dw 0xFFFF
    db 0x9A
    db 0xC

    ; Kernel mode Data segment
    dw 0x0000
    dw 0xFFFF
    db 0x92
    db 0xC

    ; User mode Code segment
    dw 0x0000
    dw 0xFFFF
    db 0xFA
    db 0xC

    ; User mode Data segment
    dw 0x0000
    dw 0xFFFF
    db 0xF2
    db 0xC

gdt_end:
    gdt_descriptor:
        dw gdt_end - gdt_start - 1
        dd gdt_start

    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    jmp KERNEL_CODE_SEG:start_pm

KERNEL_CODE_SEG equ 0x0008
KERNEL_DATA_SEG equ 0x0010
USER_CODE_SEG equ 0x001B
USER_DATA_SEG equ 0x0023
BITS 32

; Load kernel mode goes here
start_pm:
    mov ax, KERNEL_DATA_SEG
    mov ds, ax
    mov es, ax

    jmp 0x7e00:0x0000  ; Jump to the loaded stage 2 compiler

    times 510 - ($-$$) db 0
    dw 0xAA55