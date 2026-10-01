#include <stdint.h>
#include "./std/stddef.h"
#include "./std/string.h"
#include "./std/io.h"
#include "./std/stdbool.h"
#include "./drivers/vga.h"
#include "./idt.h"
#include "./irq.h"
#include "./std/util.h"
#include "./drivers/keyboard.h"
#include "./drivers/timer.h"
#include "./virt/paging.h"
void main(){
    clear_screen();
    idt_init();
    init_timer(50);
    while (inb(0x64) & 1) inb(0x60);
    outb(0x21, 0xFC);
    PGE_t* identity_table = (PGE_t*)alloc_frame();

    uint32_t phys_frame = 0x00000000;
    for (int i = 0 ; i < 1024; i++) {
        map_pagetableentry(identity_table, i, phys_frame);
        phys_frame += 0x1000;
    }

    map_pagedirentry(pagedir, 0, identity_table);

    init_paging();

    test_paging();
    asm volatile("sti");
}
