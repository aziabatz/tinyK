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
.extern _kmain, code, bss, end
.global __start
.global __stop

.align 4

mboot:
.long MAGIC
.long FLAGS
.long CHECKSUM
.long mboot
.long code
.long bss
.long end
.long __start 


/**
 *
 */
__start:
    cli
    mov $_kernel_stack, %esp
    push $STACK_SIZE // kernel stack addr esp+12
    push %eax //Magic Number pointer esp+8
    push %ebx // Multiboot structure pointer esp+4
    call __boot_idpag
    xor %ebp, %ebp
    call _kmain

.global __hold_on
.global __stop
__hold_on:
    hlt
    nop
    jmp __hold_on

__stop:
    cli
    hlt
    jmp __stop

.global __boot_idpag
__boot_idpag:
    mov $0, %eax // start vaddr
    mov $_boot_pt, %ebx //page table start
    mov $_end, %ecx //last addr

    idpag:
        andl $0xFFFFF000, %eax // discard bits for alignment
        orl $0x3, %eax //Add present and rw flags


        movl %eax, (%ebx)
        

        addl $0x4, %ebx //next pte
        addl $0x1000, %eax //next 4096 address
        subl $0x1000, %ecx //have we paged until/after end

        cmpl $0, %ecx
        jg idpag

    //we have set the pt entries
    //now we must set the pd entry pointing to pt
    movl $_boot_pt, %eax
    orl $0x3, %eax 
    movl $_boot_pd, %ebx
    movl %eax, (%ebx)

    pushl %ebx //push _boot_pd
    call __load_pd
    pop %ebx

    call __set_pg //set paging flag
ret

.section .bss
_kernel_stack_bottom:
.space STACK_SIZE
_kernel_stack:


.section .data
.align 4096 //Align 4K for paging

/*
                    ...
    ...            _boot_pt[2]
    _boot_pd[1]    _boot_pt[1]
    _boot_pd[0] -> _boot_pt[0]
*/
_boot_pd:
.space 4*1024, 0x0//1024 entries of 4 bytes each.
_boot_pt:
.space 4*1024, 0x0//Fill them with Supervisor|RW|Not Present flags
