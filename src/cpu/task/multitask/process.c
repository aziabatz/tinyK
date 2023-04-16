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


    frame->gs = KERNEL_DS;
    frame->fs = KERNEL_DS;
    frame->es = KERNEL_DS;
    frame->ds = KERNEL_DS;
    frame->edi = 0;
    frame->esi = 0;
    frame->ebp = 0;
    frame->esp = 0;
    frame->ebx = 0;
    frame->edx = 0;
    frame->ecx = 0;
    frame->eax = 0   ;
    frame->int_no = 0;
    frame->err_code = 0;
    frame->eip = entry;
    frame->cs = KERNEL_CS;
    frame->eflags = 0x202;
    frame->useresp = 0;
    frame->ss = KERNEL_DS;


    frame->esp = &(frame->int_no);
    kprintf("esp:%x\n", frame->esp);

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