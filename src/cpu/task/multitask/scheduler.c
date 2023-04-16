#include <cpu/task/scheduler.h>
#include <dev/pit/timer.h>
#include <ds/linkedlist.h>
#include <mem.h>
#include <assert.h>

static uint32 quantum = 0;
static list_t * tasks = NULL;
static list_node_t * running = NULL;
static uint32 times = 0;

static reg_frame_t kernel_task_cpu_frame;
static proc_t kernel_task; 

extern void __hold_on();

static inline store_kernel_task(reg_frame_t * regs)
{
    memcpy(&kernel_task_cpu_frame, regs, sizeof(reg_frame_t));
    
}

void init_sched(uint32 ticks, heap_t * heap)
{
    assert(ticks);
    quantum = ticks;
    set_sched_ticks(quantum);
    tasks = new_list(heap);

        kernel_task_cpu_frame =(reg_frame_t) {

        .gs = 0x10,
        .fs = 0x10,
        .es = 0x10,
        .ds = 0x10,

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

        .eip = &__hold_on,
        .cs = KERNEL_CS,
        .eflags = 0x202,
        .useresp = 0,
        .ss = 0x10
    };

    kernel_task.cpu_frame = &kernel_task_cpu_frame;

    kernel_task.cpu_frame = &kernel_task_cpu_frame;
    kernel_task.pid = 0;
    kernel_task.ring0 = true;
    kernel_task.state = PROC_STATE_EXEC;

    add_process(&kernel_task, "kernel");
}

static char * procs[] = {
    "kernel",
    "procA",
    "procB",
    "procC",
};

static do_switch(reg_frame_t * regs, proc_t * current, proc_t * next)
{
    
    asm volatile("xchg %bx,%bx");
    memcpy(current->cpu_frame, regs, sizeof(reg_frame_t));
    memcpy(regs, next->cpu_frame, sizeof(reg_frame_t));
    //regs->esp = current->cpu_frame->esp;
    // if(current != next && regs->esp == 0)
    // {
    //     regs->esp = regs->useresp-(4 * 5);
    // }
}

void pick_next(reg_frame_t * regs)
{
    kprintf("picking\n");
    if(tasks->size == 0)
        return;

    
    list_node_t * next;

    if(running)
    {
        next = running->next;
        if(!next)
        {
            next = tasks->first;
        }
    }
    else
    {
        running = tasks->first;
        next = running;
        //store_kernel_task(regs);
    }
    
    proc_t * current_proc = running->data;
    proc_t * next_proc = next->data;

    current_proc->state = PROC_STATE_DONE;
    do_switch(regs, current_proc, next_proc);
    next_proc->state = PROC_STATE_EXEC;

    /* 
    TODO change paging directory
    */
   
   running = next;

   kprintf("Sleeping process \"%s\"Loading EIP: %x ESP: %x actualESP: %x SS: %x CS: %x EFL: %x\n",
    procs[current_proc->pid],
    current_proc->cpu_frame->eip,
    current_proc->cpu_frame->useresp,
    current_proc->cpu_frame->esp,
    current_proc->cpu_frame->ss,
    current_proc->cpu_frame->cs,
    current_proc->cpu_frame->eflags);

   kprintf("Selected process \"%s\"Loading EIP: %x ESP: %x actualESP: %x SS: %x CS: %x EFL: %x\n",
    procs[next_proc->pid],
    next_proc->cpu_frame->eip,
    next_proc->cpu_frame->useresp,
    next_proc->cpu_frame->esp,
    next_proc->cpu_frame->ss,
    next_proc->cpu_frame->cs,
    next_proc->cpu_frame->eflags);
}

uint8 kill_process(uint32 pid)
{
    remove_node_index(tasks, pid);
}

uint8 add_process(proc_t * new, char * new_alias)
{
    if(!new)
        return false;
    if(insert_tail(tasks, new))
    {
        kprintf("Registered new process(%s) with EIP: %x and stack: %x\n",
            new_alias, new->cpu_frame->eip, new->cpu_frame->useresp);
    }
    
    return true;
}