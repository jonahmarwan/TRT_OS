#ifndef STDLIB_H
#define STDLIB_H

#define SYSMMAP 0x09
#define SYSMUNMAP 0x0B

void *malloc(size_t size) {
    void *addr;
    asm volatile (
        "movq %[mmap], %%rax \n\t"
        "movq %[addr]. %%rdi \n\t"
        "movq %[size], %%rsi \n\t"
        "movq $3, %%rdx \n\t"
        "movq $0x22 %%r10 \n\t"
        "movq $-1, %%r8 \n\t"
        "movq $0, %%r9 \n\t"
        "syscall"
        : [addr] "=r" (addr)
        : [size] "r" (size), [mmap] "i" (SYSMMAP)
        : "rax", "rdi", "rsi", "rdx", "r10", "r8", "r9", "memory"
    );
    return addr;
}

void free(void *ptr) {
    asm volatile (
        "movq %[munmap], %%rax \n\t"
        "movq %[addr], %%rdi \n\t"
        "movq %[size], %%rsi \n\t"
        "syscall"
        :
        : [munmap] "i" (SYSMUNMAP), [addr] "r" (ptr), [size] "r" (sizeof(ptr))
        : "rax", "rdi", "rsi"
    );
}


void *calloc(size_t n_items, size_t size){
        return malloc(n_items*size);
};

#endif STDLIB_H
