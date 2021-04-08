#include "../includes/io.h"
#include "../includes/idt.h"

extern "C" int start_kernel()
{
    char string[] = "Hello!";
    Io Io;

    idt_init();

    //Io.clear_screen();

    Io.printk(string);


    for(;;)
        asm volatile("hlt");
    return 0;
}