#include "../includes/idt.h"
#include "../includes/io.h"

idt_gate_t idt[256];
idt_pointer_t *idt_ptr;

extern "C" void idt_flush(u32int);

Io io;

void set_idt_gate(u32int index, u32int base, u16int sel, u8int flags)
{
    idt[index].low_off = base & 0xffff;
    idt[index].selector = sel;
    idt[index].flags = flags;
    idt[index].always_0 = 0;
    idt[index].high_off = (base >> 16) & 0xffff;
}

void idt_init()
{
    idt_ptr->base = (u32int)&idt;
    idt_ptr->limit = 256 * (sizeof(idt_gate_t)) - 1;

    set_idt_gate(0, (u32int)isr0, 0x08, 0x8E);

    idt_flush((u32int)&idt_ptr);
}

extern "C" void isr_handler(registers_t regs)
{
    char message[] = "Interrupt recieved: ";
    io.printk(message);

}