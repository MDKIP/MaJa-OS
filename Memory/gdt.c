#include<stdint.h>
#include<stdbool.h>
#include "gdt.h"

struct gdt_entry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t limit_high_and_flags;
    uint8_t base_high;
}__attribute__((packed));

struct gdt_descriptor
{
    uint16_t size;
    uint32_t ptr;
}__attribute__((packed));

struct gdt_entry_hl
{
    uint32_t base;
    uint32_t limit;
    // access
    bool accessed;
    bool can_write;
    bool grow_direction; // 0 w góre, 1 w dół
    bool executable;
    bool is_code_or_data;
    uint8_t privillege; // 0-3
    // flags
    bool is_32_pm;
    bool is_page_granularity;
};


struct gdt_entry main_gdt[3];
struct gdt_descriptor main_gdt_descriptor;

extern void gdt_load();

void gdt_set_entry(int i, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    // ustawianie base
    main_gdt[i].base_low = base & 0xFFFF;
    main_gdt[i].base_middle = (base >> 16) & 0xFF;
    main_gdt[i].base_high = (base >> 24) & 0xFF;

    // ustawianie limit
    main_gdt[i].limit_low = limit & 0xFFFF;
    main_gdt[i].limit_high_and_flags = (limit >> 16) & 0x0F;

    // ustawianie dostępu i flag
    main_gdt[i].access = access;
    main_gdt[i].limit_high_and_flags |= (flags << 4) & 0xF0;
}
void gdt_set_entry_hl(int i, struct gdt_entry_hl entry)
{
    // NOT IMPLEMENTED YET
}
void gdt_install()
{
    // przygotowywanie deskryptora
    main_gdt_descriptor.size = (sizeof(struct gdt_entry) * 3) - 1;
    main_gdt_descriptor.ptr = &main_gdt;

    // NULL
    gdt_set_entry(0, 0, 0, 0, 0);
    // CODE
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0b10011010, 0b00001100);
    // DATA
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0b10010010, 0b00001100);
    
    gdt_load();
}