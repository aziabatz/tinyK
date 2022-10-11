#ifndef TK_IDT_H
#define TK_IDT_H

#include <cpu/desc/descriptor.h>

#define MAX_IDT_ENTRIES 256

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

void set_idt();

#endif