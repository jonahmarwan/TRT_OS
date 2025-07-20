/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
void dummy_test_entrypoint() {
}
#include <stdint.h>
#include "./io.h"
struct InterruptDescriptor32 {
   uint16_t offset_1;        // offset bits 0..15
   uint16_t selector;        // a code segment selector in GDT or LDT
   uint8_t  zero;            // unused, set to 0
   uint8_t  type_attributes; // gate type, dpl, and p fields
   uint16_t offset_2;        // offset bits 16..31
};

#define IDT_size 256
struct InterruptDescriptor32 idt[IDT_size];

struct IDTPointer {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct IDTPointer idt_ptr;

extern void isr0();

static void set_idt_gate(int n, uint32_t handler) {
    idt[n].offset_1 = handler & 0xFFFF;
    idt[n].selector = 0x08; // kernel code segment
    idt[n].zero = 0;
    idt[n].type_attributes = 0x8E;
    idt[n].offset_2 = (handler >> 16) & 0xFFFF;
}

static void idt_load() {
    asm volatile("lidt (%0)" : : "r"(&idt_ptr));
}

void write_text(const char* str, uint8_t row, uint8_t col) {
    volatile char* video = (volatile char*) 0xB8000 + (row * 80 + col) * 2;
    while (*str) {
        *video++ = *str++;
        *video++ = 0x0F; // white text
    }
}

void idt_init() {
    set_idt_gate(0, (uint32_t)isr0); // for divide-by-zero
    idt_ptr.limit = (sizeof(struct InterruptDescriptor32) * IDT_size) - 1;
    idt_ptr.base = (uint32_t)&idt;

    idt_load();
}

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define WHITE_ON_BLACK 0x0f
#define VIDEO_MEMORY ((uint16_t*)0xB8000)

void clear_screen() {
    uint16_t blank = (' ' | (WHITE_ON_BLACK << 8));
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        VIDEO_MEMORY[i] = blank;
    }
}


void main(){
    clear_screen();
    write_text("Hello from Kernel!", 0, 0);
    idt_init();
    int x = 5 / 2;
    while(1){
        asm volatile("hlt");
    }
}
