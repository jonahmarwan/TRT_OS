#ifndef PAGEDIR_H
#define PAGEDIR_H


#define PDE_P_MASK     0x00000001
#define PDE_RW_MASK    0x00000002
#define PDE_US_MASK    0x00000004
#define PDE_PWT_MASK   0x00000008
#define PDE_PCD_MASK   0x00000010
#define PDE_A_MASK     0x00000020
#define PDE_AVL1_MASK  0x00000040
#define PDE_PS_MASK    0x00000080
#define PDE_AVL2_MASK  0x00000F00
#define PDE_ADDR_MASK  0xFFFFF000
#include "../drivers/vga.h"

typedef uint32_t PDE_t;

#define PGE_P_MASK     0x00000001
#define PGE_RW_MASK    0x00000002
#define PGE_US_MASK    0x00000004
#define PGE_PWT_MASK   0x00000008
#define PGE_PCD_MASK   0x00000010
#define PGE_A_MASK     0x00000020
#define PGE_D_MASK     0x00000040
#define PGE_PAT_MASK   0x00000080
#define PGE_G_MASK     0x00000100
#define PGE_AVL_MASK   0x00000E00
#define PGE_ADDR_MASK  0xFFFFF000

typedef uint32_t PGE_t;

#define GET_PDE_ADDR(pde)    ((pde) & PDE_ADDR_MASK)
#define SET_PDE_ADDR(pde, addr) \
    ((pde) = ((pde) & ~PDE_ADDR_MASK) | ((addr) & PDE_ADDR_MASK))

#define GET_PGE_ADDR(pge)    ((pge) & PGE_ADDR_MASK)
#define SET_PGE_ADDR(pge, addr) \
    ((pge) = ((pge) & ~PGE_ADDR_MASK) | ((addr) & PGE_ADDR_MASK))

#define SET_FLAG(val, mask)   ((val) |= (mask))
#define CLEAR_FLAG(val, mask) ((val) &= ~(mask))
#define TEST_FLAG(val, mask)  (((val) & (mask)) != 0)

typedef PDE_t pagedir_t[1024] __attribute__((aligned(4096)));
typedef PGE_t pagetable_t[1024] __attribute__((aligned(4096)));

#define PAGE_ALIGN(addr) ((addr + 4096 - 1) & ~(4096 - 1))

pagedir_t pagedir __attribute__((aligned(4096))) = {0};

uint32_t placement_address = 0x00100000;

void init_paging(){
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

void map_pagedirentry(PDE_t* dir, uint32_t index,  PGE_t* table) {
    PDE_t entry = 0;

    SET_FLAG(entry, PDE_P_MASK);
    SET_FLAG(entry, PDE_RW_MASK);
    SET_PDE_ADDR(entry, (uint32_t)table);

    dir[index] = entry;
}

void map_pagetableentry(PGE_t* table, uint32_t index, uint32_t physical_address) {
    PGE_t entry = 0;

    SET_FLAG(entry, PGE_P_MASK);
    SET_FLAG(entry, PGE_RW_MASK);
    SET_PGE_ADDR(entry, physical_address);

    table[index] = entry;
}
uint32_t alloc_frame(){
    placement_address = PAGE_ALIGN(placement_address);
    uint32_t alloc_ptr = placement_address;
    placement_address += 0x1000;

    memset((void*)placement_address, 0, 4096);
    return alloc_ptr;
}

PGE_t* create_identity_pagetable () {
    PGE_t* new_table = (PGE_t*)alloc_frame();

    for (int i = 0; i < 1024; i++) {
        uint32_t frame = alloc_frame();
        map_pagedirentry(new_table, i, (PGE_t*)frame);
    }
    return new_table;
}


//AI-generated cuz i couldnt be arsed
void test_paging() {
    // 1. Pick a clear virtual address and an empty physical frame
    uint32_t test_virtual_addr = 0x40000000; // 1 GB mark
    uint32_t test_physical_frame = alloc_frame(); // Get a clean physical page

    // 2. Calculate the Directory Index and Table Index for 0x40000000
    // (Each directory entry covers 4MB. 1GB / 4MB = 256)
    uint32_t dir_idx = test_virtual_addr >> 22;          // Result: 256
    uint32_t table_idx = (test_virtual_addr >> 12) & 0x3FF; // Result: 0

    // 3. Allocate a brand new page table for this directory slot
    PGE_t* new_table = (PGE_t*)alloc_frame();

    // 4. Map our specific virtual page entry to our physical frame
    map_pagetableentry(new_table, table_idx, test_physical_frame);
    map_pagedirentry(pagedir, dir_idx, new_table);

    // 5. CRITICAL STEP: Flush the TLB (CPU cache) so it sees the new mapping
    asm volatile("mov %%cr3, %%eax\nmov %%eax, %%cr3" ::: "eax");

    // 6. THE TEST: Write a secret value to the VIRTUAL address
    volatile uint32_t* virtual_ptr = (uint32_t*)test_virtual_addr;
    *virtual_ptr = 0xDEADBEEF;

    // 7. THE PROOF: Read from the PHYSICAL address directly
    volatile uint32_t* physical_ptr = (uint32_t*)test_physical_frame;

    if (*physical_ptr == 0xDEADBEEF) {
        write_text("SUCCESS");
    } else {
        // FAILED: The memory didn't translate.
        write_text("KOS OMAK");
    }
}

#endif
