#include <string.h>
#include <stdint.h>

// Convert a 32-bit number to a string.
// copied directly from https://github.com/ExeTwezz/Basic_OS
char *itoa (int32_t number, char *str, uint32_t base)
{
    char *rc;
    char *ptr;
    char *low;

    // Check for supported base.
    if (base < 2 || base > 36) {
        *str = '\0';
        return str;
    }

    rc = ptr = str;

    // Set '-' for negative decimals.
    if (number < 0 && base == 10) {
        *ptr++ = '-';
    }

    // Remember where the number starts.
    low = ptr;

    // The actual conversion.
    do {
        // Modulo is negative for negative number. This trick makes
        // abs() unnecessary.
        *ptr++ = "ZYXWVUTSRQPONMLKJIHGFEDCBA9876543210123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[35 + number % base];
        number /= base;
    } while (number);

    // Terminate the string.
    *ptr-- = '\0';

    // Invert the numbers.
    while (low < ptr) {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }

    return rc;
}

uint32_t strlen(const char *str )
{
    uint32_t i;
    for (i = 0; str[i] != '\0'; i++)
        ;
    return i;
}

void strcpy(char *dest, const char *src)
{
    while (*src)
        *dest++ = *src++;
}

void strncpy(char *dest, const char *src, uint32_t n)
{
    for (uint32_t i = 0; i < n; i++) {
        if (i <= strlen(src))
            dest[i] = src[i];
        else
            dest[i] = '\0';
    }
}

uint8_t *memcpy(uint8_t *dest, uint8_t *src, uint32_t count)
{
    for (uint32_t i = 0; i < count; i++)
        dest[i] = src[i];
    return dest;
}

uint8_t *memset(uint8_t *dest, uint8_t val, uint32_t count)
{
    for (uint32_t i = 0; i < count; i++)
        dest[i] = val;
    return dest;
}
