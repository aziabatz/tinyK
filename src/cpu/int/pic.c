#include <cpu/int/pic.h>

static bool pic_enabled = false;

void pic_set(bool enable)
{
    pic_enabled = enable;
}

bool pic_is_enabled()
{
    //read a bool is way faster than reading io ports
    return pic_enabled;
}

void pic_remap()
{
    
    __out8(PIC_MASTER, (PIC_INIT | PIC_ICW4));
    asm("mov $0x80, %al; out %al, $0");
    __out8(PIC_SLAVE, (PIC_INIT | PIC_ICW4));
    asm("mov $0x80, %al; out %al, $0");
    __out8(PIC_MASTER_DATA, PIC_MASTER);
    asm("mov $0x80, %al; out %al, $0");
    __out8(PIC_SLAVE_DATA, PIC_MASTER+PIC_MASTER_LINES);
    asm("mov $0x80, %al; out %al, $0");
    __out8(PIC_MASTER_DATA,0b100);
    asm("mov $0x80, %al; out %al, $0");
    __out8(PIC_SLAVE_DATA, 0b10);
    asm("mov $0x80, %al; out %al, $0");
    __out8(PIC_MASTER_DATA, PIC_ICW4);
    asm("mov $0x80, %al; out %al, $0");
    __out8(PIC_SLAVE_DATA, PIC_ICW4);
    asm("mov $0x80, %al; out %al, $0");

    //discard masks
    __out8(PIC_MASTER_DATA, 0x0);
    __out8(PIC_SLAVE_DATA,0x0);
    //asm("sti");
}

void pic_remap_offset(uint8 master, uint8 slave)
{

}

void pic_ack(bool ack_slave)
{
    if(ack_slave)
    {
        __out8(PIC_SLAVE_COMMAND, 0x20);
    }
    __out8(PIC_MASTER_COMMAND, 0x20);

    //End Of Interrupt
}