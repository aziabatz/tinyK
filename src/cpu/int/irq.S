/*
 * Created: Wednesday, October 12th 2022, 10:33:48 am
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

 #define TK_GUARD_IRQ_HANDLER

.set HW_OFFSET, 0x20

.section .text

.macro _irq_ num
.global _irq_\num
_irq_\num:
    pushl $\num
    pushl $\num+HW_OFFSET
    jmp _irq_common
.endm

_irq_common:
    pushal
    
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    cld

    push %esp
    call irq_handler

    addl $4, %esp

    popl %gs
    popl %fs
    popl %es
    popl %ds

    popal

    addl $8,%esp

iret

_irq_ 0x00
_irq_ 0x01
_irq_ 0x02
_irq_ 0x03
_irq_ 0x04
_irq_ 0x05
_irq_ 0x06
_irq_ 0x07
_irq_ 0x08
_irq_ 0x09
_irq_ 0x0A
_irq_ 0x0B
_irq_ 0x0C
_irq_ 0x0D
_irq_ 0x0E
_irq_ 0x0F
