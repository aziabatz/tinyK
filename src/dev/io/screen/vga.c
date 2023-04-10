#include <dev/io/screen/vga.h>
#include <dev/io/port.h>
#include <util.h>
#include <stdbool.h>
#include <dev/io/screen/text_color.h>

//screen related

static uint16 x = 0, y = 0;
static uint8 color = BLUE<<4 | WHITE;

static vga_spec_t vga_spec = {80,25,2,FRAMEBUFFER};

void set_fg(uint8 fg)
{
    color = (color & 0xF0) | fg & 0xF;
}

void set_bg(uint8 bg)
{
    color = ((bg << 4) & 0xF0) | (color & 0xF);
}

uint8 get_color()
{
    return color;
}

void set_color(uint8 new_color)
{
    color = new_color;
}

static inline void clear_line(uint32 line)
{
    for(uint16 cursor = vga_spec.width * line * vga_spec.depth;
        cursor<vga_spec.width * (line+1) * vga_spec.depth;
        cursor+=2)
    {
        vga_spec.fb_start[cursor] = NULL;
        vga_spec.fb_start[cursor+1] = color;
    }
}

void clear_lines(uint32 from, uint32 to)
{
    //TODO add verification for lines below screen max
    for(size_t i = from; i < to; i++)
    {
        clear_line(i);
    }
}

static inline void clear_screen()
{
    clear_lines(0, vga_spec.height);
}

void move_cursor(uint32 new_x, uint32 new_y)
{
    uint32 new_cursor = new_y * vga_spec.width + new_x;
    __out8(VGA_INDEX_PORT, 14);
    __out8(VGA_CHAR_PORT, HIGH_8(new_cursor));
    __out8(VGA_INDEX_PORT, 15);
    __out8(VGA_CHAR_PORT, LOW_8(new_cursor));

    x = new_x;
    y = new_y;
}

static inline void scroll_line()
{
    char * ch ;
    for(uint16 cursor=0;
        cursor < (vga_spec.width * (vga_spec.height-1) * vga_spec.depth);
        cursor+=2)
    {
        //assign to line N the values of line N+1
        vga_spec.fb_start[cursor] = vga_spec.fb_start[cursor+vga_spec.width*vga_spec.depth];
        vga_spec.fb_start[cursor+1] = vga_spec.fb_start[cursor+vga_spec.width*vga_spec.depth+1];
    }
    
    //clear last line
    clear_line(vga_spec.height-1);
    move_cursor(x, y-1);
}

void scroll_lines(uint16 lines)
{
    for(size_t line = 0; line<lines; line++)
    {
        scroll_line();
    }
}

static inline bool is_new_line()
{
    if(y >= vga_spec.height -1)
    {
        return true;
    }
    return false;
}

void putc(char c)
{
#if SERIAL_DEBUG
    //write char to serial port
#endif
    char * fb = vga_spec.fb_start;
    switch(c)
    {
        case 0x08:
            //TODO backspace key
            break;
        case '\t':
            x = (x+8) & ~(8-1);
            break;
        case '\r':
            //TODO carriage return
            x = 0;
            break;
        case '\n':
            //TODO line break
            x = 0;
            y ++;
            break;
        default:
            //FIXME check char is printable
            fb[(y*vga_spec.width+x)*vga_spec.depth] = c;
            fb[(y*vga_spec.width+x)*vga_spec.depth+1] = color;
            x++;
            break;
    }

    if(x > vga_spec.width)
    {
        x = 0;
        y++;
    }

    if(is_new_line())
    {
        scroll_line();
    }

    move_cursor(x,y);
}

//driver related
static bool installed = false;
static driver_info_t vga_info;
static driver_t vga_driver;

driver_t * get_vga_driver()
{
    if(!installed)
        return NULL;
    return &vga_driver;
}

driver_t * install_vga()
{
    if(!installed)
    {
        //install

        vga_info.did = 0;
        vga_info.alias = "VGA";

        vga_driver.info = &vga_info;
        vga_driver.read = vga_read;
        vga_driver.write = vga_write;
        clear_screen();
        
        installed = true;
    }
    return &vga_driver;
}

int32 vga_read(driver_data_t * data)
{
    return 0;
}

int32 vga_write(driver_data_t * data)
{
#if false
    if(data->info != vga_driver.info)
    {
        //TODO warn
        return NULL;
    }
#endif

    if(data->size == 0)
    {
        return NULL;
    }

    char * str = data->data;

    for(size_t c = 0; c < data->size; c++)
    {
        putc(str[c]);
    }

    return data->size;
}