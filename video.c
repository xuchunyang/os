#include <types.h>
#include <video.h>
#include <string.h> // strlen()
#include <memory.h> // memset()

u32  screen_row;
u32  screen_column;
u8   screen_color;
u16* screen_buffer = (u16 *)0xB8000; // video memory begins at address 0xb8000

static u8 make_color(enum vga_color fg, enum vga_color bg)
{
    return fg | bg << 4;
}

static u16 make_vgaentry(char c, u8 color)
{
    u16 c16 = c;
    u16 color16 = color;
    return c16 | color16 << 8;
}

void init_video(void)
{
    memset((u8 *)screen_buffer, 0, VGA_WIDTH * VGA_HEIGHT * 2);
    screen_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
}

static void screen_scroll()
{
    u32 x, y;

    screen_buffer = (u16*) 0xB8000;
    for (y = 0; y < VGA_HEIGHT - 1; y++) {
        for (x = 0; x < VGA_WIDTH; x++) {
            const u32 index = y * VGA_WIDTH + x;
            screen_buffer[index] = screen_buffer[index + VGA_WIDTH];
        }
    }
    --screen_row;
    /* clear last line */
    screen_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
    for (x = 0; x < VGA_WIDTH; x++)
        screen_buffer[ (VGA_HEIGHT-1) * (VGA_WIDTH) + x ] = make_vgaentry(' ', screen_color);
}

static void screen_putentryat(char c, u8 color, u32 x, u32 y)
{
    const u32 index = y * VGA_WIDTH + x;
    screen_buffer[index] = make_vgaentry(c, color);
}

void write_char(char c)
{
    if (c == '\n') {
        screen_column = 0;
        if (++screen_row == VGA_HEIGHT)
            screen_scroll();
    } else {
        screen_putentryat(c, screen_color, screen_column, screen_row);
        if (++screen_column == VGA_WIDTH) {
            screen_column = 0;
            if (++screen_row == VGA_HEIGHT)
                screen_scroll();
        }
    }
}

void write_str(const char* str)
{
    u32 len = strlen(str);
    u32 i;
    for (i = 0; i < len; i++)
        write_char(str[i]);
}

void write_color_str(const char* str, enum vga_color fg, enum vga_color bg)
{
    screen_color = make_color(fg, bg);
    write_str(str);
}
