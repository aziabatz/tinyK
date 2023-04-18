#ifndef TK_PROCESS_H
#define TK_PROCESS_H

#include <types.h>
#include "../regs.h"
#include <mem/virt/paging.h>
#include <mem/heap/heap.h>

// ready
#define PROC_STATE_DONE  0
// running
#define PROC_STATE_EXEC  1
// blocked
#define PROC_STATE_STOP  2
// waiting
#define PROC_STATE_WAIT  3


struct process_control_block
{
    uint32 pid;//0
    uint32 * stack_top;//4
    uint32 * stack_current;//8
    pg_dir_t * dir;
    uint8 state;
    uint8 ring0;
};

typedef struct process_control_block proc_t;

void set_kernel_heap(heap_t * kernel_heap);
proc_t * new_process(uint32 pid, uint32 entry, uint8 ring0);
void delete_process(proc_t * process);

#endif
