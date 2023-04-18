#include <cpu/task/scheduler.h>
#include <dev/pit/timer.h>
#include <ds/linkedlist.h>
#include <mem.h>
#include <assert.h>
#include <cpu/int/pic.h>

static uint32 quantum = 0;
static list_t * tasks = NULL;
static list_node_t * running = NULL;
static uint32 times = 0;

static reg_frame_t kernel_task_cpu_frame;
static proc_t kernel_task;
static reg_frame_t temp_frame;

extern void __hold_on();
extern void __attribute__((noreturn)) __task_trampoline(proc_t * new_proc);

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

    //kernel_task.cpu_frame = &kernel_task_cpu_frame;

    //kernel_task.cpu_frame = &kernel_task_cpu_frame;
    kernel_task.pid = 0;
    kernel_task.ring0 = true;
    kernel_task.state = PROC_STATE_EXEC;

    //add_process(&kernel_task, "kernel");
}

static char * procs[] = {
    "kernel",
    "procA",
    "procB",
    "procC",
};

static inline save_context(reg_frame_t * regs, proc_t * current)
{
    kprintf("Copying %x to %x \n", regs, current->stack_current);
    memcpy(&temp_frame, regs, sizeof(reg_frame_t));
    current->stack_current = regs;
    memcpy(current->stack_current, &temp_frame, sizeof(reg_frame_t));
    
    // current->cpu_frame->gs = regs->gs;
    // current->cpu_frame->fs = regs->fs;
    // current->cpu_frame->es = regs->es;
    // current->cpu_frame->ds = regs->ds;
    // current->cpu_frame->edi = regs->edi;
    // current->cpu_frame->esi = regs->esi;
    // current->cpu_frame->ebp = regs->ebp;
    // current->cpu_frame->esp = regs->esp;
    // current->cpu_frame->ebx = regs->ebx;
    // current->cpu_frame->edx = regs->edx;
    // current->cpu_frame->ecx = regs->ecx;
    // current->cpu_frame->eax = regs->eax;
    // current->cpu_frame->int_no = regs->int_no;
    // current->cpu_frame->err_code = regs->err_code;
    // current->cpu_frame->eip = regs->eip;
    // current->cpu_frame->cs = regs->cs;
    // current->cpu_frame->eflags = regs->eflags;
    // current->cpu_frame->useresp = regs->useresp;
    // current->cpu_frame->ss = regs->ss;
}

static inline restore_context(){/*Unused*/}

static do_switch(reg_frame_t * regs, proc_t * current, proc_t * next)
{
    
    //asm volatile("xchg %bx,%bx");
    
   // memcpy(regs, next->cpu_frame, sizeof(reg_frame_t));
    //kprintf("Copying %x to %x \n", next->cpu_frame, regs);
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
        // Si hay proceso corriendo
        // guardar los registros del proceso actual
        save_context(regs, running->data);
        
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
    //do_switch(regs, current_proc, next_proc);
    next_proc->state = PROC_STATE_EXEC;

    /* 
    TODO change paging directory
    */

    running = next;
    pic_ack(regs->int_no>=40);

    

    __task_trampoline(next_proc);
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
            0, new->stack_current);
    }
    
    return true;
}