#ifndef TK_SCHED_H
#define TK_SCHED_H

#include <types.h>
#include <cpu/regs.h>
#include "process.h"

void init_sched(uint32 quantum);

void pick_next(proc_t * current);

uint8 kill_process(proc_t * current);

uint8 add_process(proc_t * current);

#endif