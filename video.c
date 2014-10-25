#include "types.h"
#include "common.h" // memset, inb, outb
#include "video.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

u16 *screen = (u16 *)0xb8000;
u8 col = 0;
u8 row = 0; // 行

#define WHITE_ON_BLACK 0x07
u8 attr = WHITE_ON_BLACK; // default attr

// Scrolls the text on the screen up by one line.
static void scroll()
{
    u16 *video_memory = (u16 *)0xB8000;

    // Get a space character with the default colour attributes.
    u8 attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    u16 blank = 0x20 /* space */ | (attributeByte << 8);

    // Row 25 is the end, this means we need to scroll up
    if(row >= 25)
    {
        // Move the current text chunk that makes up the screen
        // back in the buffer by a line
        int i;
        for (i = 0*80; i < 24*80; i++)
        {
            video_memory[i] = video_memory[i+80];
        }

        // The last line should now be blank. Do this by writing
        // 80 spaces to it.
        for (i = 24*80; i < 25*80; i++)
        {
            video_memory[i] = blank;
        }
        // The cursor should now be on the last line.
        row = 24;
    }
}

void screen_clear()
{
    memset((u8 *)screen, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 2);
}

void put_char(char c)
{
    if (c != '\n') {
        screen[col + row * SCREEN_WIDTH] = c | (u16)(attr) << 8;
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
        put_char(*s);
        s++;
    }
}

void reverse(char s[])
{
    int length = strlen(s) ;
    int c, i, j;

    for (i = 0, j = length - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

// Obtain an approximation of the number of digits for MAX_INT
#define INT_STR_MAX (3 *sizeof (int))

int uint32_to_str(int value, char str[INT_STR_MAX])
{
    char *wstr = str;
    do
       *wstr++ = (char) "0123456789"[value % 10];
    while (value /= 10);
    *wstr = '\0';
    // Reverse string
    reverse(str);
    return wstr - str;
}

void printf(const char *fmt, ...)
{
    va_list ap; // points to each unnamed arg in turn
    // TODO: Fix 'const' warning, use fmt[i] to index instead of pointer
    const char *p;
    int ival;
    char *sval;
    char int_str_buf[INT_STR_MAX];

    va_start(ap, fmt); // make ap point to 1st unamed arg
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            put_char(*p);
            continue;
        }
        switch (*++p) {
        case 'd': // "%d", decimal
            ival = va_arg(ap, int);
            // TODO Only positive number is supported
            uint32_to_str(ival, int_str_buf);
            puts(int_str_buf);
            break;
        case 'h': // "%h" hexadecimal
            ival = va_arg(ap, int);
            // TODO Convert hexadecimal to string
            sval = "Not Implement yet";
            puts(sval);
            break;
        case 's':
            for (sval = va_arg(ap, char *); *sval; sval++)
                put_char(*sval);
            break;
        default:
            put_char(*p);
            break;
        }
    }
    va_end(ap);
}
