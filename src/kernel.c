/*
 * Created: Monday, October 10th 2022, 1:05:09 pm
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
#include <types.h>
#include <boot/multiboot.h>



#include <dev/io/screen/vga.h>
#include <str.h>
#include <cpu/task/gdt.h>
#include <cpu/int/idt.h>
#include <cpu/int/irq.h>
#include <dev/io/screen/tty.h>
#include <printf.h>
#include <debug.h>
#include <dev/pit/timer.h>

void test()
{
    kprintf("%s\n","testing kprintf:");
    kprintf("Hello %s, a random number in hex: %x\n", "world", 0xA83ED);
    kprintf("And now a char %c and a null str: %s\n", 'a', NULL);
    kprintf("Let's try a formatting... %h and %%\n");
    kprintf("Ohh, last test, some decimals(signed): %d, %d\n", 43232, -543);
    kprintf("Also let's try the -543 of before unsigned: %u\n", -543);
}

int _kmain(multiboot_info_t *multiboot,
           uint32 magicnum,
           uint32 stack)
    {
        driver_t * vga = install_vga();
        set_tty_dev(vga);

        gdt_init();
        kinfo(INFO, "GDT Loaded");
        idt_init();
        kinfo(INFO, "IDT Loaded");
        irq_init();
        kinfo(INFO, "IRQ is set");
        

        test();

        timer_init();

        //int a = 3/0;
        
        //kprint("Hola");

        

        //TODO min libc OK
        //TODO gdt OK
        //TODO idt OK
        //TODO isr
        //TODO irq
        //TODO keyboard and timer
        //TODO paging
        

        
    } 
