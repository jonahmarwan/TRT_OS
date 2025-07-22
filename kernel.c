#include <stdint.h>
#include "./std/io.h"
#include "./drivers/vga.h"
#include "./idt.h"
#include "./irq.h"
#include "./std/util.h"
#include "./drivers/keyboard.h"
#include "./drivers/timer.h"

void main(){
    clear_screen();
    idt_init();
    write_text("hi");
    // while (inb(0x64) & 1) inb(0x60);
    init_timer(50);
    outb(0x21, 0xFC);
    asm volatile("sti");
}
