#include <string.h>

u32 strlen(const char* str)
{
    u32 ret = 0;
    while (str[ret] != 0)
        ret++;
    return ret;
}
