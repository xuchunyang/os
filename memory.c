#include <memory.h>

void *memset(void *dest,  u8 val, int count)
{
    char *buf = (char*)dest;
    int i;
    for (i = 0; i < count; i++) {
        buf[i] = val;
    }
    return dest;
}
