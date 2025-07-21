/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
void dummy_test_entrypoint() {
}
#include <stdint.h>
#include "./std/io.h"
#include "./drivers/vga.h"
#include "./idt.h"
#include "./std/util.h"


void main(){
    clear_screen();
    idt_init();
    write_text("Hello from Kernel!", 0, 0); 
    asm volatile("int $31");
    while(1){
        asm volatile("hlt");
    }
}
