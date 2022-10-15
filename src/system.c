/*
 * Created: Friday, October 14th 2022, 4:39:38 pm
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
 */

#include <system.h>
#include <dev/io/screen/tty.h>
#include <dev/io/screen/text_color.h>
#include <cpu/regs.h>
#include <printf.h>

char * const RESERVED = "Reserved Exception - SHOULDN'T HAPPEN";

static  char * exceptions[256] = 
{
    "Divide by zero",
    "Debug",
    "Non-maskable?",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "No device",
    "Double Fault",
    "Coprocesor Overrun",
    "Bad TSS",
    "Segment not present",
    "Stack-Segment Fault",
    "General protection Fault",
    "Page Fault",
    RESERVED,
    "FPU Error",
    "Alignment Check",
    "Machine Check",
    "SIMD Float Exception",
    "Virtualization Error",
    "Control Protection Error",
    RESERVED,
    "Hypervisor Exception",
    "VMM Communication Exception",
    "Security Exception",
    RESERVED,
    "Triple Fault"
};

void set_bg(uint8 bg);

void kpanic(char * err, char * file, int line, reg_frame_t * regs)
{
    set_bg(RED);
    //set_fg(WHITE);
    kprintf("STOP!!! KERNEL PANIC!!!\n");
    kprintf("Cause: %s\nError Code: %x\n", exceptions[regs->int_no], regs->err_code);
    kprintf("Caused by %s:%d\n\n", file, line);
    kprintf("CPU FRAME - REGISTERS DUMP\n"PANIC_MSG,
    regs->eax, regs->ebx, regs->ecx, 
    regs->edx, regs->edi, regs->esi,
    regs->esp, regs->ebp, regs->ss,
    regs->eip, regs->cs,
    regs->gs,regs->fs, regs->es, regs->ds,
    regs->eflags);

    //error code and intno
    //TODO EFLAGS

    asm("__panic:;hlt;jmp __panic");

    
}