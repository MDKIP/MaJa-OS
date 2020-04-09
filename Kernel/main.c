#include<stdint.h>
#include "../Drivers/screen.h"
#include "../Drivers/ports.h"

void dte()
{
    
}
void main()
{
    // inicjalizacja
    screen_init();

    // powitanie
    kprint("Hello in MaJaOS!");
}