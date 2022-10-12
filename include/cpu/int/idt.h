#ifndef TK_IDT_H
#define TK_IDT_H

#include <cpu/desc/descriptor.h>
#include <cpu/regs.h>

#define MAX_IDT_ENTRIES 256

#define IDT_GATE_TASK 0x5
#define IDT_GATE_INT16 0x6
#define IDT_GATE_TRAP16 0x07
#define IDT_GATE_INT32 0x0E
#define IDT_GATE_TRAP32 0x0F

#define IDT_DPL(dpl) (dpl<<5)
#define IDT_P (1 << 7)

#ifndef KERNEL_CS
#define KERNEL_CS 0x08
#endif

struct idt_gate_desc
{
    uint16 offset_low;
    uint16 seg_sel;
    uint8 reserved;
    uint8 flags;
    uint16 offset_high;
}__attribute__((packed));

typedef struct idt_gate_desc idt_gate_t;
typedef descriptor_t idt_t;

void idt_init();

void isr_handler(reg_frame_t * regs);

#endif