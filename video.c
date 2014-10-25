#include "types.h"
#include "common.h" // memset
#include "video.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

u16 *screen = (u16 *)0xb8000;
u8 col = 0;
u8 row = 0; // 行

#define WHITE_ON_BLACK 0x07
u8 attr = WHITE_ON_BLACK; // default attr

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
