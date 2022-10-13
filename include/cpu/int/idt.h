/*
 * Created: Tuesday, October 11th 2022, 9:14:23 pm
 * Author: Ahmed Ziabat Ziabat
 * 
 * 
 * BSD 3-Clause License
 * 
 * Copyright (c) 2022, Ahmed Ziabat Ziabat <aziabatz@alumnos.unex.es>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * 
 */
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

void idt_set_gate(uint32 entry, uint32 offset, uint16 selector, uint8 flags);

void isr_handler(reg_frame_t * regs);

#endif