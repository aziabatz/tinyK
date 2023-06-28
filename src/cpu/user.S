.set USER_CS, 0x18
.set USER_DS, 0x20

.set CS_DPL, (USER_CS | 0x3)
.set DS_DPL, (USER_DS | 0x3)

.section .data

_user_stack_bottom:
.space 1024, 0
_user_stack:

fmt: .asciz "%s\n"
hola: .asciz "Hola Mundo desde espacio de usuario!\n"

.section .text
.global __jump_user
__jump_user:
    cli
    xchgw %bx,%bx
    mov $0x23, %eax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    mov $_user_stack, %eax

    pushl $0x23 // SS ESP EFLAGS CS EIP
    pushl %eax

    pushfl
    pop %eax
    or $0x200, %eax
    push %eax

    pushl $0x1b
    push $user_entry
    
iret


    
user_entry:
        
    mov $fmt, %ebx
    pushl %ebx
    mov $hola, %ebx
    pushl %ebx
    call kprintf

    add $8, %esp

    
    nop
    nop
    nop
    jmp user_entry


