#ifndef PAGEDIR_H
#define PAGEDIR_H
typedef union PDE_t {
    uint32_t value;
    struct{
        uint32_t P : 1;
        uint32_t RW : 1;
        uint32_t US : 1;
        uint32_t PWT : 1;
        uint32_t PCD : 1;
        uint32_t A : 1;
        uint32_t AVL1 : 1;
        uint32_t PS : 1;
        uint32_t AVL2 : 4;
        uint32_t ADDR : 20;
   } __attribute__((packed));
} PDE_t;

typedef union PGE_t {
    uint32_t value;
    struct{
        uint32_t P : 1;
        uint32_t RW : 1;
        uint32_t US : 1;
        uint32_t PWT : 1;
        uint32_t PCD : 1;
        uint32_t A : 1;
        uint32_t D : 1;
        uint32_t PAT : 1;
        uint32_t G : 1;
        uint32_t AVL : 3;
        uint32_t ADDR : 20;
    } __attribute__((packed));
} PGE_t;

union PDE_t pagedir[1024] __attribute__((aligned(4096)));
union PGE_t pagetable[1024] __attribute__((aligned(4096)));


void init_pagedir(){
    for(int i = 0; i < 1024; i++){
        pagetable[i].value = 0;
        pagetable[i].P = 1;
        pagetable[i].RW = 1;
        uint32_t address = (i*0x1000) >> 12;
        pagetable[i].ADDR = address;
    }

    pagedir[0].value = 0;
    pagedir[0].P = 1;
    pagedir[0].RW = 1;
    pagedir[0].ADDR = ((uint32_t)&pagetable) >> 12;

    for(int i = 1; i < 1024; i++){
        pagedir[i].value = 0;
    }

    asm volatile(
            "mov %0, %%cr3\n"
            "mov %%cr0, %%eax\n"
            "or $0x80000000, %%eax\n"
            "mov %%eax, %%cr0\n"
            : 
            : "r"(&pagedir)
            : "eax"
     );
}
#endif
