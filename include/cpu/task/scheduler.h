#ifndef TK_SCHED_H
#define TK_SCHED_H

#include <types.h>
#include <cpu/regs.h>
#include "process.h"

void init_sched(uint32 quantum, heap_t * heap);

void pick_next(reg_frame_t * regs);

uint8 kill_process(uint32 pid);

uint8 add_process(proc_t * new, char * new_alias);

#endif