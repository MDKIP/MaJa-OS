#include<stdint.h>
#include "ports.h"

uint8_t get_port_byte(uint16_t port)
{
    uint8_t byte_in;
    __asm__("in %%dx, %%al" : "=a" (byte_in) : "d" (port));
    return byte_in;
}
void send_port_byte(uint16_t port, uint8_t byte_out)
{
    __asm__("out %%ax, %%dx" : : "a" (byte_out), "d" (port));
}