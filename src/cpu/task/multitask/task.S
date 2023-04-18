.section .text

/*
 * 
 * struct process_control_block
 * {
 *     uint32 pid;                  +0    
 *     reg_frame_t * cpu_frame;     +4            
 *     pg_dir_t * dir;              +8    
 *     uint8 state;                 +12
 *     uint8 ring0;                 +14
 * };
 * 
 */

/**
 *
 * Function header:
 *     void __attribute__((noreturn)) __task_trampoline(proc_t * new_proc);
 */
.global __task_trampoline
__task_trampoline:

    xchgw %bx, %bx

    mov 4(%esp), %ebx // < Primer argumento (puntero a proc_t)
    mov 8(%ebx), %esp 

    popl %gs
    popl %fs
    popl %es
    popl %ds

    pop %edi
    pop %esi
    pop %ebp
    add $4, %esp //unused esp value

    pop %ebx
    pop %edx
    pop %ecx
    pop %eax

    addl $8, %esp

iret