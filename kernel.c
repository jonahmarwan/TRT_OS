#include <stdint.h>
#include "./std/io.h"
#include "./std/stdbool.h"
#include "./drivers/vga.h"
#include "./idt.h"
#include "./irq.h"
#include "./std/util.h"
#include "./drivers/keyboard.h"
#include "./drivers/timer.h"
#include "./mmu/pagedir.h"
extern void print_hex;
void main(){
    clear_screen();
    idt_init();
    init_pagedir();
    init_timer(50);
    while (inb(0x64) & 1) inb(0x60);
    outb(0x21, 0xFD);
    asm volatile("sti");
}
