#include <common.h>

/*
 * Base on https://github.com/ExeTwezz/Basic_OS
 */
// Convert a 32-bit number to a string.
char *itoa (int32_t number, char *str, uint32_t base)
{
    char *rc;
    char *ptr;
    char *low;

    // Check for supported base.
    if (base < 2 || base > 36)
    {
        *str = '\0';
        return str;
    }

    rc = ptr = str;

    // Set '-' for negative decimals.
    if (number < 0 && base == 10)
    {
        *ptr++ = '-';
    }

    // Remember where the number starts.
    low = ptr;

    // The actual conversion.
    do
    {
        // Modulo is negative for negative number. This trick makes
        // abs() unnecessary.
        *ptr++ = "ZYXWVUTSRQPONMLKJIHGFEDCBA9876543210123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[35 + number % base];
        number /= base;
    } while (number);

    // Terminate the string.
    *ptr-- = '\0';

    // Invert the numbers.
    while (low < ptr)
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }

    return rc;
}

void *memset(void *dest, uint8_t val, int count)
{
    uint8_t *buf = (uint8_t *)dest;
    int i = 0;

    while (i < count) {
        buf[i++] = val;
    }
    return dest;
}

int strlen(const char *s)
{
    int len;

    for (len = 0; *s; s++)
        len++;
    return len;
}
