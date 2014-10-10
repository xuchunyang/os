#ifndef VIDEO_H
#define VIDEO_H

#include <types.h>

/* Hardware text mode color constants. */
enum vga_color
{
    COLOR_BLACK         = 0,
    COLOR_BLUE          = 1,
    COLOR_GREEN         = 2,
    COLOR_CYAN          = 3,
    COLOR_RED           = 4,
    COLOR_MAGENTA       = 5,
    COLOR_BROWN         = 6,
    COLOR_LIGHT_GREY    = 7,
    COLOR_DARK_GREY     = 8,
    COLOR_LIGHT_BLUE    = 9,
    COLOR_LIGHT_GREEN   = 10,
    COLOR_LIGHT_CYAN    = 11,
    COLOR_LIGHT_RED     = 12,
    COLOR_LIGHT_MAGENTA = 13,
    COLOR_LIGHT_BROWN   = 14,
    COLOR_WHITE         = 15,
};

#define VGA_WIDTH   80
#define VGA_HEIGHT  25

void init_video(void);
void write_char(char c);
void write_str(const char* str);
void write_color_str(const char* str, enum vga_color fg, enum vga_color bg);

#endif