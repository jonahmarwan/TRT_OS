/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
void dummy_test_entrypoint() {
}
#include <stdint.h>
#include "./std/io.h"
#include "./drivers/vga.h"
#include "./idt.h"


void main(){
    clear_screen();
    outb(0x3d4, 14);
    int position = inb(0x3d5);
    position = position << 8;
    outb(0x3d4, 15);
    position += inb(0x3d5);
    int curposoff = position * 2;
    idt_init();
    char *vga = 0xb8000;
    vga[curposoff] = 'X';
    vga[curposoff+1] = 0x0f;

    int x = 5 / 0;
    while(1){
        asm volatile("hlt");
    }
}
