#include "../includes/io.h"

u8int Io::inb(u16int port)
{
    u8int result;
    asm volatile("inb %1, %0": "=a"(result) : "dN"(port));
    return result;
}

void Io::outb(u16int port, u8int data)
{
    asm volatile("outb %1, %0"::"dN"(port), "a"(data));
}

int Io::get_cursor()
{
    u32int offset;
    //request high bit
    outb(vga_ctl_reg, 0x0e);
    offset = inb(vga_data_reg)<<8;
    //request low byte
    outb(vga_ctl_reg, 0x0f);
    offset += inb(vga_data_reg);
    return offset * 2;
}

void Io::set_cursor(u32int offset)
{
    offset /= 2;
    //writing to high bit
    outb(vga_ctl_reg, 0x0e);
    outb(vga_data_reg, (u8int)(offset >> 8));
    //wrting to low bit
    outb(vga_ctl_reg, 0x0f);
    outb(vga_data_reg, (u8int)(offset & 0xff));
}

void Io::putc(u8int character)
{
    u32int offset = get_cursor();
    u8int *vga = (u8int*)vga_addr;
    vga[offset] = character;
    vga[offset + 1] = GREEN;
    offset += 2;
    set_cursor(offset);
}

void Io::printk(char str[]){
    int i = 0;
    while(str[i] != '\0')
    {
        if(str[i] == '\n')
        {
            print_nl();
            break;
        }
        else
        {
            putc(str[i]);
            i++;
        }
    }
}

void Io::clear_screen()
{
    int offset = 0;
    set_cursor(offset);
    int num = (80 * 25) * 2;
    
    for(int i = 0; i < num; i++, offset += 2)
    {
        putc(' ');
        set_cursor(offset);
    }
    set_cursor(0);
}

void Io::print_nl()
{
    int offset = get_cursor();
    int pos = offset / (80 * 2);
    set_cursor((pos + 1) * 80 * 2);
}
