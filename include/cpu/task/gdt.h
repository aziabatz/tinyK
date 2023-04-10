#ifndef TK_GDT_H
#define TK_GDT_H

#include <cpu/desc/descriptor.h>

#define KERNEL_CS 0x8
#define KERNEL_DS 0x10
#define MAX_GDT_ENTRIES 10


#define GDT_NULL_ENTRY 0
#define GDT_KERNEL_CS_ENTRY 1
#define GDT_KERNEL_DS_ENTRY 2
#define GDT_USER_CS_ENTRY 3
#define GDT_USER_DS_ENTRY 4
#define GDT_TSS_ENTRY 5

//access
#define GDT_P (1 << 7)
#define GDT_DPL(dpl) (dpl << 5)
#define GDT_S (1 << 4)
#define GDT_EX (1 << 3)
#define GDT_DC (1 << 2)
#define GDT_RW (1 << 1)
#define GDT_A 1

//flags
#define GDT_L (1 << 5)
#define GDT_DB (1 << 6)
#define GDT_G (1 << 7)

struct gdt_seg_desc
{
    uint16 limit_low;
    uint16 base_low;
    uint8 base_mid;
    uint8 access;
    uint8 flags_limit_hi;
    uint8 base_hi;
}__attribute__((packed));

typedef struct gdt_seg_desc gdt_entry_t;

typedef descriptor_t gdt_t;

void gdt_init();

void install_tss (uint32 entry, uint16 ss, uint32 esp);

#endif