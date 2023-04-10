//
// Created by Ahmed Ziabat on 10/4/23.
//

#ifndef TK_TSS_H
#define TK_TSS_H

#include <types.h>

struct tss
{
    uint16 prev;
    uint16 reserved0;

    uint32 esp0;
    
    uint16 ss0;
    uint16 reserved1;

    uint32 esp1;

    uint16 ss1;
    uint16 reserved2;

    uint32 esp2;

    uint16 ss2;
    uint16 reserved3;

    uint32 cr3,
    eip,
    eflags,
    eax,
    ecx,
    edx,
    ebx,
    esp,
    ebp,
    esi,
    edi;

    uint16 es;
    uint16 reserved4;

    uint16 cs;
    uint16 reserved5;

    uint16 ss;
    uint16 reserved6;

    uint16 ds;
    uint16 reserved7;

    uint16 fs;
    uint16 reserved8;

    uint16 gs;
    uint16 reserved9;

    uint16 ldt;
    uint16 reserved10;

    uint16 trap_reserved11;
    uint16 iomap;
}__attribute__((packed));

typedef struct tss tss_t;

extern void __flush_tss(uint16 selector);

#endif
