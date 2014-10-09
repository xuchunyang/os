#include <types.h>
#include <video.h>

uint32_t strlen(const char* str)
{
    uint32_t ret = 0;
    while (str[ret] != 0)
        ret++;
    return ret;
}

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

static const uint32_t VGA_WIDTH  = 80;
static const uint32_t VGA_HEIGHT = 25;

uint32_t  screen_row;
uint32_t  screen_column;
uint8_t   screen_color;
uint16_t* screen_buffer;


uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
    return fg | bg << 4;
}

uint16_t make_vgaentry(char c, uint8_t color)
{
    uint16_t c16 = c;
    uint16_t color16 = color;
    return c16 | color16 << 8;
}

void init_video(void)
{
    uint32_t x, y;

    screen_row = 0;
    screen_column = 0;
    screen_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
    screen_buffer = (uint16_t*) 0xB8000; // video memory begins at address 0xb8000
    for (y = 0; y < VGA_HEIGHT; y++)
    {
        for (x = 0; x < VGA_WIDTH; x++)
        {
            const uint32_t index = y * VGA_WIDTH + x;
            screen_buffer[index] = make_vgaentry(' ', screen_color);
        }
    }
}

void screen_scroll()
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

void screen_setcolor(uint8_t color)
{
    screen_color = color;
}

void screen_putentryat(char c, uint8_t color, uint32_t x, uint32_t y)
{
    const uint32_t index = y * VGA_WIDTH + x;
    screen_buffer[index] = make_vgaentry(c, color);
}

void write_char(char c)
{
    if (c != '\n')
    {
        screen_putentryat(c, screen_color, screen_column, screen_row);
        if (++screen_column == VGA_WIDTH)
        {
            screen_column = 0;
            if (++screen_row == VGA_HEIGHT)
                // screen_row = 0;
                screen_scroll();
        }
    }
    else
    {
        screen_column = 0;
        if (++screen_row == VGA_HEIGHT)
            // screen_row = 0;
            screen_scroll();
    }
}

void write_str(const char* str)
{
    uint32_t len = strlen(str);
    uint32_t i;
    for (i = 0; i < len; i++)
        write_char(str[i]);
}

void write_color_str(const char* str, uint8_t color)
{
    // TODO
}
