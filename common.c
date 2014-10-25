#include "common.h"

void *memset(void *dest, char val, int count)
{
    char *buf = (char*)dest;
    for (int i = 0; i < count; i++) {
        buf[i] = val;
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
