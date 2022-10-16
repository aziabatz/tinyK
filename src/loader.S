//Multiboot structure
.set MAGIC, 0x1badb002
.set STACK_SIZE, 4096
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)


.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM


//Kernel start code
.section .text
.extern kmain, code, bss, end
.global start
.global _stop

.align 4

mboot:
.long MAGIC
.long FLAGS
.long CHECKSUM
.long mboot
.long code
.long bss
.long end
.long start 

start:
    cli
    mov $kernel_stack, %esp
    push $STACK_SIZE
    push %eax
    push %ebx
    xor %ebp, %ebp
    call _kmain

.global __hold_on
__hold_on:
    hlt
    nop
    jmp __hold_on

_stop:
    cli
    hlt
    jmp _stop


.section .bss
.space STACK_SIZE
kernel_stack:

