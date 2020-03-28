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
<<<<<<< HEAD
    
    //kprint_int(6969);
    kprint("Hello MajaOS!");
=======
    kprint("Hello in MaJaOS!");
    
    send_port_byte(0x3d4, 14);
    int position = get_port_byte(0x3d5) << 8;
    send_port_byte(0x3d4, 15);
    position += get_port_byte(0x3d5);
    vga_set_point(1, 1);
    kprint_int(position);
>>>>>>> 0a0bb344412ac665fc0b194cd04a9ed568bf09eb
}