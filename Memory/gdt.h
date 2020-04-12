#include<stdint.h>

struct gdt_entry;
struct gdt_descriptor;

void gdt_set_entry(int i, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);
void gdt_install();
