#include <video.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

uint16_t* video_buffer;
int cursor_column;
int cursor_row;

void init_screen(void)
{
    video_buffer = (uint16_t *)0xB8000;
    cursor_row = 0;
    cursor_column = 0;
    memset((uint8_t *)0xB8000, 0, VBUFFER_SIZE);
}

void scroll_screen (void)
{
    memcpy((uint8_t *)0xB8000, (uint8_t *)0xB8000 + SCREEN_WIDTH * 2,
           VBUFFER_SIZE - SCREEN_WIDTH * 2);
    memset((uint8_t *)0xB8000 + VBUFFER_SIZE - SCREEN_WIDTH * 2, 0,
           SCREEN_WIDTH * 2);
    cursor_row = SCREEN_HEIGHT - 1;
    cursor_column = 0;
}

void putch_at (char ch, int column, int row)
{
    int offset = (row * SCREEN_WIDTH) + column;
    video_buffer[offset] = ch | (0x07 << 8);
}

void putch (char ch)
{
    if (ch == '\n') {
        ++cursor_row;
        cursor_column = 0;
        if (cursor_row >= SCREEN_HEIGHT)
            scroll_screen();
    } else {
        putch_at(ch, cursor_column, cursor_row);

        ++cursor_column;
        if (cursor_column >= SCREEN_WIDTH) {
            ++cursor_row;
            cursor_column = 0;
            if (cursor_row >= SCREEN_HEIGHT)
                scroll_screen();
        }
    }
}

void puts(const char *s)
{
    int i;
    for (i = 0; s[i] != '\0'; ++i)
        putch(s[i]);
}

static void print(const char* data, size_t data_length)
{
    for (size_t i = 0; i < data_length; i++)
        putch((int) ((const unsigned char*) data)[i]);
}

int printf(const char* restrict format, ...)
{
    va_list parameters;
    va_start(parameters, format);

    int written = 0;
    size_t amount;
    bool rejected_bad_specifier = false;

    while (*format != '\0') {
        if (*format != '%') {
        print_c:
            amount = 1;
            while (format[amount] && format[amount] != '%')
                amount++;
            print(format, amount);
            format += amount;
            written += amount;
            continue;
        }

        const char* format_begun_at = format;

        if (*(++format) == '%')
            goto print_c;

        if (rejected_bad_specifier) {
        incomprehensible_conversion:
            rejected_bad_specifier = true;
            format = format_begun_at;
            goto print_c;
        }

        if (*format == 'c') {
            format++;
            char c = (char) va_arg(parameters, int /* char promotes to int */);
            print(&c, sizeof(c));
        } else if (*format == 's') {
            format++;
            const char* s = va_arg(parameters, char*);
            print(s, strlen(s));
        } else if (*format == 'd') {
            format++;
            int d = va_arg(parameters, int);
            char buf[10] = "";
            itoa(d, buf, 10);
            print(buf, strlen(buf));
        } else if (*format == 'x') {
            format++;
            int d = va_arg(parameters, int);
            char buf[10] = "";
            itoa(d, buf, 16);
            print(buf, strlen(buf));
        } else {
            goto incomprehensible_conversion;
        }
    }

    va_end(parameters);

    return written;
}
