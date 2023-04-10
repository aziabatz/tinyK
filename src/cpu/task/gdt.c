#include <cpu/task/gdt.h>
#include <cpu/task/tss.h>
#include <mem.h>

static gdt_entry_t gdt_entries[MAX_GDT_ENTRIES];
static gdt_t gdt;


static tss_t kernel_tss, user_tss;

void __install_gdt(gdt_t *);

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
    gdt_set_gate(GDT_NULL_ENTRY,0,0,0,0);
    //kernel code segment
    gdt_set_gate(GDT_KERNEL_CS_ENTRY, 0xFFFFFFFF, 0x0, (GDT_P|GDT_S|GDT_EX|GDT_DC), (GDT_G|GDT_DB));
    //kernel data segment
    gdt_set_gate(GDT_KERNEL_DS_ENTRY, 0xFFFFFFFF, 0x0, (GDT_P|GDT_S|GDT_RW), (GDT_G|GDT_DB));

    gdt.base = (uint32) &gdt_entries;
    gdt.limit = (sizeof(gdt_entry_t)*MAX_GDT_ENTRIES)-1;

    __install_gdt(&gdt);
}

void install_tss (uint32 entry, uint16 ss, uint32 esp)
{
    uint32 base = (uint32) &kernel_tss;
    //I86_GDT_DESC_ACCESS|I86_GDT_DESC_EXEC_CODE|I86_GDT_DESC_DPL|I86_GDT_DESC_MEMORY,0);
    gdt_set_gate(entry, base + sizeof(tss_t), base, 
    (GDT_A | GDT_EX | GDT_P | GDT_DPL(3)), 0);

    memset(&kernel_tss, 0, sizeof(tss_t));

    kernel_tss.ss0 = ss;
    kernel_tss.esp0 = esp;

    kernel_tss.cs=KERNEL_CS;
	kernel_tss.ss = KERNEL_DS;
	kernel_tss.es = KERNEL_DS;
	kernel_tss.ds = KERNEL_DS;
	kernel_tss.fs = KERNEL_DS;
	kernel_tss.gs = KERNEL_DS;

    __flush_tss(entry * sizeof(gdt_entry_t));

}