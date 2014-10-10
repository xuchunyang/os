#include <memory.h>

void *memset(void *dest,  uint8_t val, uint32_t count)
{
    char *buf = (char*)dest;
    uint32_t i;
    for (i = 0; i < count; i++) {
        buf[i] = val;
    }
    return dest;
}
