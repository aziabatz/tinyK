.section .text
.global __install_gdt
.global __flush_gdt

__install_gdt:
    xchgw %bx,%bx
    mov 4(%esp), %eax
    lgdt (%eax)

    movl %cr0, %eax
    orl $1, %eax
    movl %eax, %cr0

    //TODO needed??
    cli

    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss

    ljmp $0x08,$long_jump

    long_jump:
ret
