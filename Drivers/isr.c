#include<stdint.h>

struct idt_entry
{
    uint16_t offset_low;
    uint16_t selector; //RPL(2), TI(1), index(13)
    uint8_t zero;
    uint8_t flags; // type(4), storage(1), DPL(2), present(1)
    uint16_t offset_high;
}__attribute__((packed));
struct idt_descriptor
{
    uint16_t size;
    uint32_t ptr;
}__attribute__((packed));

struct idt_entry IDT[256];
struct idt_descriptor IDT_descriptor;

extern void load_idt();
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void idt_set_entry(int i, uint32_t code_ptr, uint16_t selector, uint8_t flags)
{
    // ustawianie wskaźnika do kodu
    IDT[i].offset_low = code_ptr & 0xFFFF;
    IDT[i].offset_high = (code_ptr & 0xFFFF0000) >> 16;

    // ustawianie flag i selectora
    IDT[i].selector = selector;
    IDT[i].flags = flags;

    // ustawianie stałych
    IDT[i].zero = 0;
}
void idt_init()
{
    // przygotowywanie deskryptora
    IDT_descriptor.size = 256 * 64 - 1;
    IDT_descriptor.ptr = &IDT;

    // ustawianie rekordów
    uint16_t selector = 0x08;
    uint8_t flags = 0b10001110;
    idt_set_entry(0, (uint32_t)irq0, selector, flags);
    idt_set_entry(1, (uint32_t)irq1, selector, flags);
    idt_set_entry(2, (uint32_t)irq2, selector, flags);
    idt_set_entry(3, (uint32_t)irq3, selector, flags);
    idt_set_entry(4, (uint32_t)irq4, selector, flags);
    idt_set_entry(5, (uint32_t)irq5, selector, flags);
    idt_set_entry(6, (uint32_t)irq6, selector, flags);
    idt_set_entry(7, (uint32_t)irq7, selector, flags);
    idt_set_entry(8, (uint32_t)irq8, selector, flags);
    idt_set_entry(9, (uint32_t)irq9, selector, flags);
    idt_set_entry(10, (uint32_t)irq10, selector, flags);
    idt_set_entry(11, (uint32_t)irq11, selector, flags);
    idt_set_entry(12, (uint32_t)irq12, selector, flags);
    idt_set_entry(13, (uint32_t)irq13, selector, flags);
    idt_set_entry(14, (uint32_t)irq14, selector, flags);
    idt_set_entry(15, (uint32_t)irq15, selector, flags);

    // ładowanie IDT
    load_idt();
}

void irq0_handler()
{

}
void irq1_handler()
{
    
}
void irq2_handler()
{
    
}
void irq3_handler()
{
    
}
void irq4_handler()
{
    
}
void irq5_handler()
{
    
}
void irq6_handler()
{
    
}
void irq7_handler()
{
    
}
void irq8_handler()
{
    
}
void irq9_handler()
{
    
}
void irq10_handler()
{
    
}
void irq11_handler()
{
    
}
void irq12_handler()
{
    
}
void irq13_handler()
{
    
}
void irq14_handler()
{
    
}
void irq15_handler()
{
    
}