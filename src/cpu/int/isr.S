/*
 * Created: Wednesday, October 12th 2022, 9:35:09 am
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

#define TK_GUARD_ISR_HANDLER

.section .text

.global reserved

.macro _int_ num
.global _int_\num
_int_\num:
    xchg %bx, %bx
    pushl $0//dummy err-code
    pushl $\num
    jmp _int_common
.endm

.macro _inte_ num
.global _inte_\num
_inte_\num:
    xchg %bx, %bx
    pushl $\num
    jmp _int_common
.endm

_int_common:
    //push gp regs
    pushal

    //push seg regs
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    cld

    push %esp
    call isr_handler

    add $4, %esp //clear push
    

    popl %gs
    popl %fs
    popl %es
    popl %ds

    popal

    //clear push from macro
    add $8, %esp
reserved:
iret

_int_ 0x00
_int_ 0x01
_int_ 0x02
_int_ 0x03
_int_ 0x04
_int_ 0x05
_int_ 0x06
_int_ 0x07
_inte_ 0x08
_int_ 0x09
_inte_ 0x0A
_inte_ 0x0B
_inte_ 0x0C
_inte_ 0x0D
_inte_ 0x0E
_int_ 0x0F
_int_ 0x10
_inte_ 0x11
_int_ 0x12
_int_ 0x13
_int_ 0x14
_int_ 0x15
_int_ 0x16
_int_ 0x17
_int_ 0x18
_int_ 0x19
_int_ 0x1A
_int_ 0x1B
_int_ 0x1C
_int_ 0x1D
_inte_ 0x1E
_int_ 0x1F
