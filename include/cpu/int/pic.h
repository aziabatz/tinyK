/*
 * Created: Wednesday, October 12th 2022, 6:00:22 pm
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
#ifndef TK_PIC_H
#define TK_PIC_H

#include <stdbool.h>
#include <dev/io/port.h>

#define PIC_MASTER          0x20
#define PIC_MASTER_COMMAND  PIC_MASTER
#define PIC_MASTER_DATA     PIC_MASTER+1

#define PIC_SLAVE           0xA0
#define PIC_SLAVE_COMMAND   PIC_SLAVE
#define PIC_SLAVE_DATA      PIC_SLAVE+1

#define PIC_ICW4            0x01
#define PIC_INIT            0x10

#define PIC_MASTER_LINES    8
#define PIC_SLAVE_LINES     8
#define PIC_MAX_LINES       PIC_MASTER_LINES + PIC_SLAVE_LINES

#define PIC_OFFSET          PIC_MASTER

void pic_set(bool enable);

bool pic_is_enabled();

void pic_remap();

void pic_remap_offset(uint8 master, uint8 slave);

void pic_ack(bool ack_slave);

#endif