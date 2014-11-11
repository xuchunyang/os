#include <common.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

uint16_t *screen = (uint16_t *)0xb8000;
uint8_t col = 0;
uint8_t row = 0;

#define WHITE_ON_BLACK 0x07
uint8_t attr = WHITE_ON_BLACK; // default attr

// Scrolls the text on the screen up by one line.
static void scroll()
{
    uint16_t *video_memory = (uint16_t *)0xB8000;

    // Get a space character with the default colour attributes.
    uint8_t attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

    // Row 25 is the end, this means we need to scroll up
    if (row >= 25) {
        // Move the current text chunk that makes up the screen
        // back in the buffer by a line
        int i;
        for (i = 0*80; i < 24*80; i++)
            video_memory[i] = video_memory[i+80];

        // The last line should now be blank. Do this by writing
        // 80 spaces to it.
        for (i = 24*80; i < 25*80; i++)
            video_memory[i] = blank;

        // The cursor should now be on the last line.
        row = 24;
    }
}

void clear_screen()
{
    memset((uint8_t *)screen, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 2);
}

void putch(char c)
{
    if (c != '\n') {
        screen[col + row * SCREEN_WIDTH] = c | (uint16_t)(attr) << 8;
        if (++col == 80) {
            col = 0;
            row++;
        }
    } else {
        col = 0;
        row++;
    }
    scroll();
}

void puts(const char *s)
{
    while (*s) {
        putch(*s);
        s++;
    }
}

// Print a number.
void putn(const char *name, int32_t n, uint32_t radix)
{
    char str[32];
    puts(name);
    puts(" = ");
    if (radix == 16)
        puts("0x");
    puts(itoa(n, str, radix));
    puts("\n");
}
