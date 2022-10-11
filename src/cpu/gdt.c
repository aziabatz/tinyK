#include <cpu/task/gdt.h>

static gdt_entry_t gdt_entries[MAX_GDT_ENTRIES];
static gdt_t gdt;

void gdt_set_gate(uint32 entry, 
    uint32 limit,
    uint32 base,
    uint8 access,
    uint8 flags)
{
    gdt_entries[entry].limit_low = (limit & 0xFFFF);
    gdt_entries[entry].base_low = (base & 0xFFFF);
    gdt_entries[entry].base_mid = (base >> 16) & 0xFF;
    gdt_entries[entry].access = access;
    gdt_entries[entry].flags_limit_hi =  flags | ((limit >> 16) & 0xF);
    gdt_entries[entry].base_hi = (base >> 24) & 0xFF;    
}

void gdt_init()
{
    //null entry
    gdt_set_gate(0,0,0,0,0);
    //kernel code segment
    gdt_set_gate(1, 0xFFFFFFFF, 0x0, (GDT_P|GDT_S|GDT_EX|GDT_DC), (GDT_G|GDT_DB));
    //kernel data segment
    gdt_set_gate(2, 0xFFFFFFFF, 0x0, (GDT_P|GDT_S|GDT_RW), (GDT_G|GDT_DB));

    gdt.base = (uint32) &gdt_entries;
    gdt.limit = (sizeof(gdt_entry_t)*MAX_GDT_ENTRIES)-1;

    __install_gdt(&gdt);
}