#include<stdint.h>
#include<stdbool.h>

extern char* VGA_MEMORY;
extern int VGA_WIDTH;
extern int VGA_HEIGHT;
extern int vga_column;
extern int vga_row;
extern int vga_cursor_column;
extern int vga_cursor_row;
extern uint8_t vga_color;
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

void screen_init(void);
void kprint(char* str);
void kprint_int(int a);
void vga_clear();
void vga_set_point(int x, int y);
int vga_get_cursor_pos();
void vga_update_cursor();
uint8_t vga_get_color(enum VGA_COLOR foreground, enum VGA_COLOR background);
int calc_vga_offset(int x, int y);
void kprintch(char c, int x, int y);

