#include <string.h>
#include <stdint.h>

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
