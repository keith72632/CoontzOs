#include "../includes/io.h"

extern "C" int start_kernel()
{
    char string[] = "Hello!";
    Io Io;
    Io.clear_screen();
    //Io.putc('X');
    Io.printk(string);
    return 0;
}