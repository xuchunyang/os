/*
 * Data type
 */
typedef unsigned char  uint8_t;
typedef signed char    int8_t;
typedef unsigned short uint16_t;
typedef signed short   int16_t;
typedef unsigned int   uint32_t;
typedef signed int     int32_t;

/*
 * Video
 */
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

uint32_t strlen(const char* str)
{
    uint32_t ret = 0;
    while ( str[ret] != 0 )
        ret++;
    return ret;
}

static const uint32_t VGA_WIDTH = 80;
static const uint32_t VGA_HEIGHT = 25;

uint32_t screen_row;
uint32_t screen_column;
uint8_t screen_color;
uint16_t* screen_buffer;

void screen_clear()
{
    screen_row = 0;
    screen_column = 0;
    screen_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
    screen_buffer = (uint16_t*) 0xB8000; // video memory begins at address 0xb8000
    for ( uint32_t y = 0; y < VGA_HEIGHT; y++ )
    {
        for ( uint32_t x = 0; x < VGA_WIDTH; x++ )
        {
            const uint32_t index = y * VGA_WIDTH + x;
            screen_buffer[index] = make_vgaentry(' ', screen_color);
        }
    }
}

void screen_scroll()
{
    screen_buffer = (uint16_t*) 0xB8000;
    for (uint32_t y = 0; y < VGA_HEIGHT - 1; y++) {
        for (uint32_t x = 0; x < VGA_WIDTH; x++) {
            const uint32_t index = y * VGA_WIDTH + x;
            screen_buffer[index] = screen_buffer[index + VGA_WIDTH];
        }
    }
    --screen_row;
    /* clear last line */
    screen_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
    for (uint32_t x = 0; x < VGA_WIDTH; x++)
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

void screen_putchar(char c)
{
    if (c != '\n')
    {
        screen_putentryat(c, screen_color, screen_column, screen_row);
        if ( ++screen_column == VGA_WIDTH )
        {
            screen_column = 0;
            if ( ++screen_row == VGA_HEIGHT )
                // screen_row = 0;
                screen_scroll();
        }
    }
    else
    {
        screen_column = 0;
        if ( ++screen_row == VGA_HEIGHT )
            // screen_row = 0;
            screen_scroll();
    }
}

void screen_write_string(const char* data)
{
    uint32_t datalen = strlen(data);
    for ( uint32_t i = 0; i < datalen; i++ )
        screen_putchar(data[i]);
}

void screen_write_string_with_color(const char *data, enum vga_color fg, enum vga_color bg)
{
    screen_color = make_color(fg, bg);
    uint32_t len = strlen(data);
    for ( uint32_t i = 0; i < len; i++ )
        screen_putchar(data[i]);
    /* Restore default color */
    screen_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
}

void kmain()
{
    screen_clear();
    for ( uint32_t i = 0; i < VGA_HEIGHT; i++ )
        screen_write_string("Hello, Kernel World!\n");

    screen_write_string_with_color("this is NOT my own kernel.\n", COLOR_RED, COLOR_WHITE);
    screen_write_string("yet another line.\n");
}
