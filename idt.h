#ifndef IDT_H
#define IDT_H

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


void idt_init() {
    set_idt_gate(0, (uint32_t)isr0); // for divide-by-zero
    idt_ptr.limit = (sizeof(struct InterruptDescriptor32) * IDT_size) - 1;
    idt_ptr.base = (uint32_t)&idt;

    idt_load();
}


#endif

