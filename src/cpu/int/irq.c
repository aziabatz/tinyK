#include <cpu/int/irq.h>
#include <cpu/int/idt.h>
#include <cpu/int/pic.h>
#include <stddef.h>
#include <printf.h>

extern void _irq_0x00();
extern void _irq_0x01();
extern void _irq_0x02();
extern void _irq_0x03();
extern void _irq_0x04();
extern void _irq_0x05();
extern void _irq_0x06();
extern void _irq_0x07();
extern void _irq_0x08();
extern void _irq_0x09();
extern void _irq_0x0A();
extern void _irq_0x0B();
extern void _irq_0x0C();
extern void _irq_0x0D();
extern void _irq_0x0E();
extern void _irq_0x0F();

static __handler irq_handlers[PIC_MAX_LINES];

void install_irq()
{
    //clear irq lines handlers
    for(size_t i = 0; i < PIC_MAX_LINES; i++)
    {
        irq_handlers[i] = NULL;
    }

    uint16 selector = KERNEL_CS;
    uint8 flags = IDT_P | IDT_DPL(0) | IDT_GATE_INT32;


    idt_set_gate(0x00 + PIC_OFFSET, (uint32) _irq_0x00, selector, flags);
    idt_set_gate(0x01 + PIC_OFFSET, (uint32) _irq_0x01, selector, flags);
    idt_set_gate(0x02 + PIC_OFFSET, (uint32) _irq_0x02, selector, flags);
    idt_set_gate(0x03 + PIC_OFFSET, (uint32) _irq_0x03, selector, flags);
    idt_set_gate(0x04 + PIC_OFFSET, (uint32) _irq_0x04, selector, flags);
    idt_set_gate(0x05 + PIC_OFFSET, (uint32) _irq_0x05, selector, flags);
    idt_set_gate(0x06 + PIC_OFFSET, (uint32) _irq_0x06, selector, flags);
    idt_set_gate(0x07 + PIC_OFFSET, (uint32) _irq_0x07, selector, flags);
    idt_set_gate(0x08 + PIC_OFFSET, (uint32) _irq_0x08, selector, flags);
    idt_set_gate(0x09 + PIC_OFFSET, (uint32) _irq_0x09, selector, flags);
    idt_set_gate(0x0A + PIC_OFFSET, (uint32) _irq_0x0A, selector, flags);
    idt_set_gate(0x0B + PIC_OFFSET, (uint32) _irq_0x0B, selector, flags);
    idt_set_gate(0x0C + PIC_OFFSET, (uint32) _irq_0x0C, selector, flags);
    idt_set_gate(0x0D + PIC_OFFSET, (uint32) _irq_0x0D, selector, flags);
    idt_set_gate(0x0E + PIC_OFFSET, (uint32) _irq_0x0E, selector, flags);
    idt_set_gate(0x0F + PIC_OFFSET, (uint32) _irq_0x0F, selector, flags);

    
}

void irq_init()
{
    pic_remap();
    install_irq();
    pic_set(true);
    asm("sti");
}

void set_irq_handler(uint32 line, __handler handler)
{
    irq_handlers[line] = handler;
}


void irq_handler(reg_frame_t * regs)
{
    //check we have received IRQ and not another interrupt
    kprintf("irq %d\n", regs->int_no);
    asm("xchgw %bx,%bx");
    if(regs->int_no >= 32 && regs->int_no <=47)
    {
        __handler handler = irq_handlers[regs->int_no-PIC_OFFSET];
        if(handler)
        {
            handler(regs);
        }

        //if irq is from slave pic, send EOI to both pic
        bool is_slave = regs->int_no >= 40;
        pic_ack(is_slave);
    }

    return;
}