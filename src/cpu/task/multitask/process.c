#include <cpu/task/process.h>
#include <mem/virt/vm_mgr.h>
#include <cpu/task/gdt.h>


static heap_t * heap = NULL;

void set_kernel_heap(heap_t * kernel_heap)
{
    heap = kernel_heap;
}

proc_t * new_process(uint32 pid, uint32 entry, uint8 ring0)
{
    //reg_frame_t * frame = kmalloc(heap, sizeof(reg_frame_t));
    //pg_dir_t * dir =  TODO implement kmallocp
    proc_t * process = kmalloc(heap, sizeof(proc_t));

    uint8 * new_stack = kmalloc(heap, 256);

    new_stack += 256;
    reg_frame_t * frame = new_stack - sizeof(reg_frame_t);


    *frame = (reg_frame_t) {
        .gs = KERNEL_DS,
        .fs = KERNEL_DS,
        .es = KERNEL_DS,
        .ds = KERNEL_DS,

        .edi = 0,
        .esi = 0,
        .ebp = 0,
        .esp = 0,
        .ebx = 0,
        .edx = 0,
        .ecx = 0,
        .eax = 0,

        .int_no = 0,
        .err_code = 0,

        .eip = entry,
        .cs = KERNEL_CS,
        .eflags = 0x202,
        .useresp = 0,
        .ss = KERNEL_DS
    };

    frame->esp = frame + (4*12);

    process->pid = pid;
    process->cpu_frame = frame;
    process->dir = 0;
    process->state = PROC_STATE_DONE;
    process->ring0 = true;

    return process;
}


void delete_process(proc_t * process)
{
    kfree(heap, process->cpu_frame);
    //kfree(heap, process->dir);
    kfree(heap, process);
}