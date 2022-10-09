.section .text
.global __out8
.global __out16
.global __out32

.global __in8
.global __in16
.global __in32

__out8:
    movw 4(%esp), %dx
    movb 8(%esp), %al
    outb %al, %dx
ret

__out16:
    movw 4(%esp), %dx
    movw 8(%esp), %ax
    outw %ax, %dx
ret

__out32:
    movw 4(%esp), %dx
    movl 8(%esp), %eax
    outl %eax, %dx
ret

__in8:
    movw 4(%esp), %dx
    movl 8(%esp), %ecx
    inb %dx, %al
    movb %al, (%ecx)
ret

__in16:
    movw 4(%esp), %dx
    movl 8(%esp), %ecx
    inw %dx, %ax
    movw %ax, (%ecx)
ret

__in32:
    movw 4(%esp), %dx
    movl 8(%esp), %ecx
    inl %dx, %eax
    movl %eax, (%ecx)
ret
