#include<stdint.h>
#include<stdbool.h>
#include "ports.h"
#include "screen.h"

char* VGA_MEMORY;
int VGA_WIDTH;
int VGA_HEIGHT;
int vga_column;
int vga_row;
int vga_cursor_column;
int vga_cursor_row;
uint8_t vga_color;


uint8_t vga_get_color(enum VGA_COLOR foreground, enum VGA_COLOR background)
{
    return foreground | background << 4;
}
void screen_init(void)
{
    VGA_MEMORY = (char*)0xb8000; // pamięć VRAM
    VGA_WIDTH = 80;
    VGA_HEIGHT = 25;
    vga_column = 0;
    vga_row = 0;
    int cursor_pos = vga_get_cursor_pos();
    vga_cursor_column = cursor_pos / VGA_WIDTH;
    vga_cursor_row = cursor_pos % VGA_WIDTH;
    vga_color = vga_get_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
}
int calc_vga_offset(int x, int y)
{
    // ponieważ pamięć VRAM jest 80x25 a każdy znak zajmuje 2 bajty
    return 2 * (y * VGA_WIDTH + x);
}

void vga_clear()
{
    int c = 0;
    int offset = 0;
    while (80 * 25 > c)
    {
        *(VGA_MEMORY+offset) = 0;
        *(VGA_MEMORY+offset + 1) = vga_color;
        c++;
        offset = c * 2;
    }
    vga_column = 0;
    vga_row = 0;
}

void kprint(char* str)
{
    // petla wypisująca na ekran ciąg stringa
    int c = 0;
    int offset = calc_vga_offset(vga_column, vga_row);
    while (*(str+c) != 0)
    {
        if(vga_row >= VGA_HEIGHT - 3)
        {
            vga_row = 0;
            vga_column = 0;
            offset = calc_vga_offset(vga_column, vga_row);
        }
        if(*(str+c) == '\n')
        {
            vga_column = 0;
            vga_row++;
            offset = calc_vga_offset(vga_column, vga_row);
            c++;
            vga_cursor_row++;
            continue;
        }
        *(VGA_MEMORY+offset) = *(str+c);
        *(VGA_MEMORY+offset + 1) = vga_color;
        c++;
        vga_column++;
        offset = calc_vga_offset(vga_column, vga_row);
    }
    vga_cursor_row++;
    vga_update_cursor();
}
void kprint_int(int a)
{
    if (a == 0)
    {
        kprintch('0', vga_column, vga_row);
        vga_column += 1;
        return;
    }
    int digits[10];
    int i;
    for (i = 9; i >= 0; i--)
    {
        digits[i] = a % 10;
        a /= 10;
    }
    bool foundStart = false;
    for (i = 0; i < 10; i++)
    {
        if (digits[i] == 0 && !foundStart)
        {
            continue;
        }
        else if (digits[i] != 0 && !foundStart)
        {
            foundStart = true;
        }
        if (foundStart)
        {
            kprintch(digits[i] + 48, vga_column, vga_row);
            vga_column += 1;
        }
    }
}
int vga_get_cursor_pos()
{
    send_port_byte(0x3d4, 14);
    int position = get_port_byte(0x3d5) << 8;
    send_port_byte(0x3d4, 15);
    position += get_port_byte(0x3d5);
    return position;
}
void vga_update_cursor()
{
    uint16_t cursor_pos = vga_cursor_row * VGA_WIDTH + vga_cursor_column;

    send_port_byte(0x3D4, 0x0F);
    send_port_byte(0X3D5, (uint8_t)(cursor_pos & 0xFF));
    send_port_byte(0x3D4, 0x0E);
    send_port_byte(0X3D5, (uint8_t)((cursor_pos >> 8) & 0xFF));
}
void vga_set_point(int x, int y)
{
    vga_column = x;
    vga_row = y;
}
void kprintch(char c, int x, int y)
{
    vga_set_point(x, y);
    int offset = calc_vga_offset(vga_column, vga_row);
    *(VGA_MEMORY + offset) = c;
    *(VGA_MEMORY + offset + 1) = vga_color;
}