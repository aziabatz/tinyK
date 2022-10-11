#ifndef TK_IRQ_H
#define TK_IRQ_H

#include <stdbool.h>
#include <cpu/regs.h>

void set_irq_handler(uint8 irqn, uint32 handler);

void init_irq();

void set_irq(bool active);

bool is_irq_enabled();

//FIXME should only be visible by asm file
void irq_handler(reg_frame_t * regs);

typedef void (*__handler)(reg_frame_t *);

#endif