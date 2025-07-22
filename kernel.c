#include <stdint.h>
#include "./std/io.h"
#include "./drivers/vga.h"
#include "./idt.h"
#include "./irq.h"
#include "./std/util.h"
#include "./drivers/keyboard.h"

void main(){
    clear_screen();
    idt_init();
    asm volatile("sti");
}
