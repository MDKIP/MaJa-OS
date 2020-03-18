#include<stdint.h>

char* VGA_MEMORY;
int VGA_WIDTH;
int VGA_HEIGHT;
int vga_column;
int vga_row;
uint8_t vga_color;
enum VGA_COLOR
{
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

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
    vga_color = vga_get_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
}
int calc_vga_offset(int x, int y)
{
    // ponieważ pamięć VRAM jest 80x25 a każdy znak zajmuje 2 bajty
    return 2 * (y * VGA_WIDTH + x);
}
void kprint(char* str)
{
    // petla wypisująca na ekran ciąg stringa
    int c = 0;
    int offset = calc_vga_offset(vga_column, vga_row);
    while (*(str+c) != 0)
    {
        *(VGA_MEMORY+offset+2*c) = *(str+c);
        *(VGA_MEMORY+offset+2*c+1) = vga_color;
        c++;
    }
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