#ifndef IO_H
#define IO_H

#include "common.h"

class Io {
    public:
        u8int inb(u16int port);
        void outb(u16int port, u8int data);
        int get_cursor();
        void set_cursor(u32int offset);
        void putc(u8int character);
        void printk(char str[]);
        void clear_screen();
        void print_nl();
    private:
        u32int vga_addr = 0xB8000;
        u32int vga_ctl_reg = 0x3D4;
        u32int vga_data_reg = 0x3D5;
        enum {
            BLACK = 0x0,
            BLUE = 0x1,
            GREEN = 0x2,
            CYAN = 0xB,
            RED = 0xC,
            MAGENTA = 0xD,
            BROWN = 0xE,
            LIGHT_GRAY = 0xF
        };
};

#endif