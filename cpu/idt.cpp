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
    set_idt_gate(1, (u32int)isr1, 0x08, 0x8E);
    set_idt_gate(2, (u32int)isr2, 0x08, 0x8E);
    set_idt_gate(3, (u32int)isr3, 0x08, 0x8E);
    set_idt_gate(4, (u32int)isr4, 0x08, 0x8E);
    set_idt_gate(5, (u32int)isr5, 0x08, 0x8E);
    set_idt_gate(6, (u32int)isr6, 0x08, 0x8E);
    set_idt_gate(7, (u32int)isr7, 0x08, 0x8E);
    set_idt_gate(8, (u32int)isr8, 0x08, 0x8E);
    set_idt_gate(9, (u32int)isr9, 0x08, 0x8E);
    set_idt_gate(10, (u32int)isr10, 0x08, 0x8E);
    set_idt_gate(11, (u32int)isr11, 0x08, 0x8E);
    set_idt_gate(12, (u32int)isr12, 0x08, 0x8E);
    set_idt_gate(13, (u32int)isr13, 0x08, 0x8E);
    set_idt_gate(14, (u32int)isr14, 0x08, 0x8E);
    set_idt_gate(15, (u32int)isr15, 0x08, 0x8E);
    set_idt_gate(16, (u32int)isr16, 0x08, 0x8E);
    set_idt_gate(17, (u32int)isr17, 0x08, 0x8E);
    set_idt_gate(18, (u32int)isr18, 0x08, 0x8E);
    set_idt_gate(19, (u32int)isr19, 0x08, 0x8E);
    set_idt_gate(20, (u32int)isr20, 0x08, 0x8E);
    set_idt_gate(21, (u32int)isr21, 0x08, 0x8E);
    set_idt_gate(22, (u32int)isr22, 0x08, 0x8E);
    set_idt_gate(23, (u32int)isr23, 0x08, 0x8E);
    set_idt_gate(24, (u32int)isr24, 0x08, 0x8E);
    set_idt_gate(25, (u32int)isr25, 0x08, 0x8E);
    set_idt_gate(26, (u32int)isr26, 0x08, 0x8E);
    set_idt_gate(27, (u32int)isr27, 0x08, 0x8E);
    set_idt_gate(28, (u32int)isr28, 0x08, 0x8E);
    set_idt_gate(29, (u32int)isr29, 0x08, 0x8E);
    set_idt_gate(30, (u32int)isr30, 0x08, 0x8E);
    set_idt_gate(31, (u32int)isr31, 0x08, 0x8E);


    idt_flush((u32int)&idt_ptr);
}

extern "C" void isr_handler(registers_t regs)
{
    char message[] = "Interrupt recieved: ";
    io.printk(message);

}