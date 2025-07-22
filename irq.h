#ifndef IRQ_H
#define IRQ_H

typedef unsigned int   u32;
typedef          int   s32;
typedef unsigned short u16;
typedef          short s16;
typedef unsigned char  u8;
typedef          char  s8;

typedef struct {
   u32 ds; /* Data segment selector */
   u32 edi, esi, ebp, esp, ebx, edx, ecx, eax; /* Pushed by pusha. */
   u32 int_no, err_code; /* Interrupt number and error code (if applicable) */
   u32 eip, cs, eflags, useresp, ss; /* Pushed by the processor automatically */
} registers_t;

#include "./std/util.h"
#include "./drivers/keyboard.h"
void irq_handler(registers_t r){
   if(r.int_no == 33){while(1){kbdcallback();}}
   if(r.int_no >= 40) outb(0xa0, 0x20);
    outb(0x20, 0x20);
 
}

#endif
