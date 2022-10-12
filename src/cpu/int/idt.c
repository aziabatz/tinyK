#include <cpu/int/idt.h>

static idt_gate_t idt_gates[MAX_IDT_ENTRIES];
static idt_t idt;

extern void _int_0x00();
extern void _int_0x01();
extern void _int_0x02();
extern void _int_0x03();
extern void _int_0x04();
extern void _int_0x05();
extern void _int_0x06();
extern void _int_0x07();
extern void _inte_0x08();
extern void _int_0x09();
extern void _inte_0x0A();
extern void _inte_0x0B();
extern void _inte_0x0C();
extern void _inte_0x0D();
extern void _inte_0x0E();
extern void _int_0x0F();
extern void _int_0x10();
extern void _inte_0x11();
extern void _int_0x12();
extern void _int_0x13();
extern void _int_0x14();
extern void _int_0x15();
extern void _int_0x16();
extern void _int_0x17();
extern void _int_0x18();
extern void _int_0x19();
extern void _int_0x1A();
extern void _int_0x1B();
extern void _int_0x1C();
extern void _int_0x1D();
extern void _inte_0x1E();
extern void _int_0x1F();

void idt_set_gate(uint32 entry,
    uint32 offset/** handler */,
    uint16 selector,
    uint8 flags)
{
    idt_gates[entry].offset_low = offset & 0xFFFF;
    idt_gates[entry].seg_sel = selector;
    idt_gates[entry].flags = flags;
    idt_gates[entry].offset_high = (offset >> 16) & 0xFFFF;  
}

void install_gates(uint16 selector, uint8 flags)
{
    idt_set_gate(0x00,(uint32)_int_0x00, selector, flags);
    idt_set_gate(0x01,(uint32)_int_0x01, selector, flags);
    idt_set_gate(0x02,(uint32)_int_0x02, selector, flags);
    idt_set_gate(0x03,(uint32)_int_0x03, selector, flags);
    idt_set_gate(0x04,(uint32)_int_0x04, selector, flags);
    idt_set_gate(0x05,(uint32)_int_0x05, selector, flags);
    idt_set_gate(0x06,(uint32)_int_0x06, selector, flags);
    idt_set_gate(0x07,(uint32)_int_0x07, selector, flags);
    idt_set_gate(0x08,(uint32)_inte_0x08, selector, flags);
    idt_set_gate(0x09,(uint32)_int_0x09, selector, flags);
    idt_set_gate(0x0A,(uint32)_inte_0x0A, selector, flags);
    idt_set_gate(0x0B,(uint32)_inte_0x0B, selector, flags);
    idt_set_gate(0x0C,(uint32)_inte_0x0C, selector, flags);
    idt_set_gate(0x0D,(uint32)_inte_0x0D, selector, flags);
    idt_set_gate(0x0E,(uint32)_inte_0x0E, selector, flags);
    idt_set_gate(0x0F,(uint32)_int_0x0F, selector, flags);
    idt_set_gate(0x10,(uint32)_int_0x10, selector, flags);
    idt_set_gate(0x11,(uint32)_inte_0x11, selector, flags);
    idt_set_gate(0x12,(uint32)_int_0x12, selector, flags);
    idt_set_gate(0x13,(uint32)_int_0x13, selector, flags);
    idt_set_gate(0x14,(uint32)_int_0x14, selector, flags);
    idt_set_gate(0x15,(uint32)_int_0x15, selector, flags);
    idt_set_gate(0x16,(uint32)_int_0x16, selector, flags);
    idt_set_gate(0x17,(uint32)_int_0x17, selector, flags);
    idt_set_gate(0x18,(uint32)_int_0x18, selector, flags);
    idt_set_gate(0x19,(uint32)_int_0x19, selector, flags);
    idt_set_gate(0x1A,(uint32)_int_0x1A, selector, flags);
    idt_set_gate(0x1B,(uint32)_int_0x1B, selector, flags);
    idt_set_gate(0x1C,(uint32)_int_0x1C, selector, flags);
    idt_set_gate(0x1D,(uint32)_int_0x1D, selector, flags);
    idt_set_gate(0x1E,(uint32)_inte_0x1E, selector, flags);
    idt_set_gate(0x1F,(uint32)_int_0x1F, selector, flags);
}

void idt_init()
{
    install_gates(KERNEL_CS, (IDT_P|IDT_DPL(0)|IDT_GATE_INT32));

    idt.base = (uint32) &idt_gates;
    idt.limit = (MAX_IDT_ENTRIES * sizeof(idt_gate_t))-1;

    __asm__ __volatile__("lidtl (%0)"::"r"(&idt));
}

void isr_handler(reg_frame_t * regs)
{

}