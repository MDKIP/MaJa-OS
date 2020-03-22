#include "../Drivers/screen.h"

void dte()
{
    
}
void main()
{
    // inicjalizacja
    screen_init();

    // powitanie
    kprint("Hello MaJaOZ!\nHow are You?");
    vga_clear();
    kprint("Hello MaJaOS!\nHow are You?");
}