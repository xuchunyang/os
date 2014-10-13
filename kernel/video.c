#include <types.h>
#include <video.h>
#include <string.h> // strlen() and memset()
#include <io.h>    // outb()

#define VGA_WIDTH   80
#define VGA_HEIGHT  25

uint32_t  screen_row = 0;
uint32_t  screen_column = 0;
uint8_t   screen_color;
uint16_t* screen_buffer = (uint16_t *)0xB8000; // video memory begins at address 0xb8000

static uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
    return fg | bg << 4;
}

static uint16_t make_vgaentry(char c, uint8_t color)
{
    uint16_t c16 = c;
    uint16_t color16 = color;
    return c16 | color16 << 8;
}

// Updates the hardware cursor.
static void move_cursor()
{
    // The screen is 80 characters wide...
    uint16_t cursorLocation = screen_row * VGA_WIDTH + screen_column;
    outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
    outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
    outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
    outb(0x3D5, cursorLocation);      // Send the low cursor byte.
}


void init_video(void)
{
    memset((uint8_t *)screen_buffer, 0, VGA_WIDTH * VGA_HEIGHT * 2);
    screen_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);

    screen_row = 0;
    screen_column = 0;
    move_cursor();
}

static void screen_scroll()
{
    uint32_t x, y;

    screen_buffer = (uint16_t*) 0xB8000;
    for (y = 0; y < VGA_HEIGHT - 1; y++) {
        for (x = 0; x < VGA_WIDTH; x++) {
            const uint32_t index = y * VGA_WIDTH + x;
            screen_buffer[index] = screen_buffer[index + VGA_WIDTH];
        }
    }
    --screen_row;
    /* clear last line */
    screen_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
    for (x = 0; x < VGA_WIDTH; x++)
        screen_buffer[ (VGA_HEIGHT-1) * (VGA_WIDTH) + x ] = make_vgaentry(' ', screen_color);
}

static void screen_putentryat(char c, uint8_t color, uint32_t x, uint32_t y)
{
    const uint32_t index = y * VGA_WIDTH + x;
    screen_buffer[index] = make_vgaentry(c, color);
}

void putch(char c)
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

    move_cursor();
}

void puts_mid_str(const char* str)
{
    char c;
    while ((c = *str++))
        putch(c);
}

void puts_color_str(const char* str, enum vga_color fg, enum vga_color bg)
{
    screen_color = make_color(fg, bg);
    puts_mid_str(str);
}