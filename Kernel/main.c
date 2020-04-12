#include<stdint.h>
#include "../Drivers/screen.h"
#include "../Drivers/ports.h"
#include "../Memory/gdt.h"

void dte()
{
    
}
void main()
{
    // inicjalizacja
    screen_init();
    kprint("VGA screen initialized\n");
    kprint("GDT installation start...\n");
    gdt_install();
    kprint("GDT instaled successfuly\n");

    // powitanie
    kprint("Hello in MaJaOS!");
}