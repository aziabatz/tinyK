#ifndef TK_PORT_H
#define TK_PORT_H

#include <types.h>

typedef uint16 port_t;

extern void __out8(port_t port, uint8 value);
extern void __out16(port_t port, uint16 value);
extern void __out32(port_t port, uint32 value);

extern void __in8(port_t port, uint8 * value);
extern void __in16(port_t port, uint16 * value);
extern void __in32(port_t port, uint32 * value);

#endif