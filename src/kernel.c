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
#include <mem/virt/paging.h>
#include <mem/phys/pm_map.h>
#include <mem/phys/pm_mgr.h>
#include <mem/virt/vm_mgr.h>
#include <mem/heap/heap.h>

extern void __hold_on();
extern void __boot_idpag();

void test()
{
    kprintf("%s\n", "testing kprintf:");
    kprintf("Hello %s, a random number in hex: %x\n", "world", 0xA83ED);
    kprintf("And now a char %c and a null str: %s\n", 'a', NULL);
    kprintf("Let's try a formatting... %h and %%\n");
    kprintf("Ohh, last test, some decimals(signed): %d, %d\n", 43232, -543);
    kprintf("Also let's try the -543 of before unsigned: %u\n", -543);
}

void charmap()
{
    kprintf("ASCII CHARMAP\n");
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            kprintf("%c ", 16 * i + j);
        }
        kprintf("\n");
    }
}

int _kmain(pg_dir_t *kdir,
           multiboot_info_t *multiboot,
           uint32 magicnum,
           size_t stack_size,
           void * stack)
{
    driver_t *vga = install_vga();
    set_tty_dev(vga);

    kinfo(INFO, "Bootstrap OK!");

    mboot_mmap_load(multiboot);

    mboot_show_mmap();

    // memory detection
    if (multiboot->mem_upper < (10 * 1024))
    {
        kinfo(WARNING, "Total system RAM is below 10Mib!");
    }
    kprintf("\t\tRecognized memory: low=%d(KB)    high=%d(KB)\n", multiboot->mem_lower, multiboot->mem_upper);

    // init system
    gdt_init();
    kinfo(INFO, "GDT Loaded");

    irq_init();
    kinfo(INFO, "IRQ is set");

    idt_init();
    kinfo(INFO, "IDT Loaded");
    pg_set_handler();
    kinfo(INFO, "Page Fault handler set");

    timer_init();

    
    pm_mgr_init(NULL, multiboot->mem_lower + multiboot->mem_upper, kdir);

    size_t total, free;
    pm_mgr_get_status(&total, &free);

/*     kprintf("Physical Memory Manager:\n"
        "Total pages: %u\n"
        "Free pages: %u\n"
        "Used pages: %u\n"
        "Aprox. use: %u%%\n",
        total, free, total-free, 100*(total-free)/total);

    kprintf("Allocated %u block(s) at %x\n", 1, pm_mgr_alloc(1));
    kprintf("Allocated %u block(s) at %x\n", 3, pm_mgr_alloc(3));
    kprintf("Allocated %u block(s) at %x\n", 4, pm_mgr_alloc(4));
    kprintf("Allocated %u block(s) at %x\n", 600, pm_mgr_alloc(600));


    pm_mgr_get_status(&total, &free);

    kprintf("Physical Memory Manager:\n"
        "Total pages: %u\n"
        "Free pages: %u\n"
        "Used pages: %u\n"
        "Aprox. use: %u%%\n",
        total, free, total-free, 100*(total-free)/total); */

    heap_t * kheap = init_kheap(kdir, (PG_PTE_READ_WRITE | PG_PTE_PRESENT));

    virt_t allocs[5];
    for (size_t i = 0; i < 5; i++)
    {  
        
        allocs[i] = kmalloc(kheap, i * 2);
        if(allocs[i]){
        heap_block_t * hp = (uintptr_t)(allocs[i])-sizeof(heap_block_t);
        
        kprintf("reserved with malloc at 0x%x with:\n"
        "base:0x%x length:0x%x\n", hp, hp->base, hp->length);
        }
        else{
            kprintf("%s\n", "Error allocating");
        }
    }

    for (size_t i = 0; i < 5; i++)
    {
        if(kfree(kheap, allocs[i]))
            kprintf("freed with kfree chunk at 0x%x\n", allocs[i]);
        else
            kprintf("kfree thrown error freeing chunk at 0x%x\n", allocs[i]);
    }
    
    pg_dir_t * old_dir = kdir;
    kdir = vm_clone_dir(kdir);

    kprintf("Cloned directory, new 0x%x from 0x%x\n", old_dir, kdir);

    install_tss(GDT_TSS_ENTRY, KERNEL_DS, stack);
    kinfo(INFO, "TSS was set up in %TR register");

    __hold_on();
}
