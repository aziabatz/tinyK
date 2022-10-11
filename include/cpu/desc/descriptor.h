#ifndef TK_DESCRIPTOR_H
#define TK_DESCRIPTOR_H

#include <types.h>

struct descriptor
{
    uint16 limit;
    uint32 base;
}__attribute__((packed));

typedef struct descriptor descriptor_t;

#endif