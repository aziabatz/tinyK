
.section .text

.global __flush_tss

__flush_tss:
    movw 4(%esp), %ax
    orw $3, %ax
    ltr %ax
ret