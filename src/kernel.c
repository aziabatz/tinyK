#include <types.h>
#include <boot/multiboot.h>

/*

int ta_main();
int tb_main();

extern void read_mem();

extern int mmap_ent;
extern int lower_mem;

extern void enable_A20();

extern void __stop();

boolean is_a20();
extern void enter_8086(uint32 ss, uint32 esp, uint32 cs, uint32 eip);



void kmain(multiboot_info_t
           *multiboot,
           uint32 magicnum, uint32
           stack) {

    clearScreen();
    isr_install();
    irq_install();
    set_idt();
    gdt_init();
#if TIMER_ENABLE
    init_timer(0);
#endif
#if KB_ENABLE
    install_kb();
#endif
#if MOUSE_ENABLE
    install_mouse();
#endif
    enable_pic();
    print("Total memory recognized:");
    setup_mmap(multiboot);
    int * total_memory = (((size_t) multiboot) + 8);
    print(itos(*total_memory));
    print(" kBYTES (stack):");
    print(itos(stack));
    print("\n");
    print("CPUVendor:\t");
    string cpuvendor0 = "CPUXCPUYCPUZ";
    cpuvendor0 = cpu_name(&cpuvendor0);
    print("\n");
    print("\n");
    if (detect_apic()) {
        printf("APIC is available in this processor. ");
        if (pic_status())
            printf("Using legacy PIC instead.");
        printf("\n");
    } else {
        printf("No APIC available!!\n");
    }
    printf("Build timestamp: %s %s\n", __DATE__, __TIME__);
    init_early_heap(0xc0000000, *total_memory);

#if PAG
    install_paging(total_memory);
#   if PAG_INFO
    info_paging();
#   endif
#endif

#if MT_SCHED
    init_tasking(NULL, NULL, NULL);
    add_task(&ta_main);
 //   add_task(&tb_main);
    show_procs();
#endif

#if VESA
    printf("Vesa Information:\n");
    vbe_info_block_t * vbe_info = multiboot->vbe_control_info;
    printf("Vesa signature: %s\n", vbe_info->vbe_signature);
    unsigned char * version = &vbe_info->version;
    printf("Vesa version: %d.%d\n", version[1],version[0]);
    vbe_mode_block_t * mode_block = multiboot->vbe_mode_info;
    printf("Screen resolution: %dx%d (Width x Height)\n", mode_block->Xres, mode_block->Yres);
#endif

show_mem_map();
printf("Usable RAM blocks: %d\nUsable RAM size: %x\n",
        get_ram_type_blocks(USABLE_RAM), 
        get_ram_type_size(USABLE_RAM));

int *a =0xA0000000;

#if sh
    shell_main();
#endif

#if PCI_INFO
    for(int bus=0;bus<256;bus++){
        for(int dev =0;dev<32;dev++){
            is_device(bus, dev);
            get_char(false);
        }
    }
#endif

    haltForEver();
}

 */

#include <dev/io/screen/vga.h>
#include <str.h>
#include <cpu/task/gdt.h>
#include <cpu/int/idt.h>

int _kmain(multiboot_info_t *multiboot,
           uint32 magicnum,
           uint32 stack)
    {
/*         unsigned short * video = 0xb8000;
        char * str = "Hola mundo! Hola SO.";
        
        for(int i = 0; str[i]!=0; i++)
        {
            video[i] = 0x9f00 | str[i];
        } */
        driver_t * vga = install_vga();

        driver_data_t ddata = {
            .info = NULL,
            .data = "Ahmed\t",
            .size = 6
        };

        for(int i = 0; i<3; i++)
        {
            vga->write(&ddata);
        }

        gdt_init();
        idt_init();

        //TODO min libc
        //TODO gdt
        //TODO idt
        //TODO isr
        //TODO irq
        //TODO keyboard and timer
        //TODO paging
        

        for(;;);
    } 
