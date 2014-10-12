#include <string.h>
#include <video.h>

void *memset(void *dest, char val, int count)
{
    char *buf = (char*)dest;
    int i;
    for (i = 0; i < count; i++) {
        buf[i] = val;
    }
    return dest;
}

size_t strlen(const char* str)
{
    size_t rtv = 0;
    while (str[rtv] != 0)
        rtv++;
    return rtv;
}

void puts(const char* str)
{
    size_t i;
    for (i = 0; i < strlen(str); i++)
        putch(str[i]);
}

void reverse(char s[])
{
    size_t length = strlen(s) ;
    int c, i, j;

    for (i = 0, j = length - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

#define INT_STR_MAX (3 *sizeof (int))

size_t uint32_to_str(uint32_t value, char str[INT_STR_MAX])
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

void kprintf(const char *fmt, ...)
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
            putch(*p);
            continue;
        }
        switch (*++p) {
        case 'd': // "%d", decimal
            ival = va_arg(ap, int);
            // TODO Only positive number is supported
            uint32_to_str(ival, int_str_buf);
            puts(sval);
            break;
        case 'h': // "%h" hexadecimal
            ival = va_arg(ap, int);
            // TODO Convert hexadecimal to string
            sval = "Not Implement yet";
            puts(sval);
            break;
        case 's':
            for (sval = va_arg(ap, char *); *sval; sval++)
                putch(*sval);
            break;
        default:
            putch(*p);
            break;
        }
    }
    va_end(ap);
}
