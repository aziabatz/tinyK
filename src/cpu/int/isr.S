.section .text

.macro _int_ num
.global _int_\num
_int_\num:
    cli
    push $0//dummy err-code
    pushl $\num
    jmp _int_common
.endm

.macro _inte_ num
.global _inte_\num
_inte_\num:
    cli
    pushl $\num
    jmp _int_common
.endm

_int_common:
    //push gp regs
    pushal

    //push seg regs
    push %ds
    push %es
    push %fs
    push %gs

    cld

    push %esp
    call isr_handler
    add $4, %esp //clear push

    pop %gs
    pop %fs
    pop %es
    pop %ds

    popal

    //clear push from macro
    add $8, %esp
iret

_int_ 0x00
_int_ 0x01
_int_ 0x02
_int_ 0x03
_int_ 0x04
_int_ 0x05
_int_ 0x06
_int_ 0x07
_inte_ 0x08
_int_ 0x09
_inte_ 0x0A
_inte_ 0x0B
_inte_ 0x0C
_inte_ 0x0D
_inte_ 0x0E
_int_ 0x0F
_int_ 0x10
_inte_ 0x11
_int_ 0x12
_int_ 0x13
_int_ 0x14
_int_ 0x15
_int_ 0x16
_int_ 0x17
_int_ 0x18
_int_ 0x19
_int_ 0x1A
_int_ 0x1B
_int_ 0x1C
_int_ 0x1D
_inte_ 0x1E
_int_ 0x1F
