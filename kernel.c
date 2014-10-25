#include "types.h"
#include "video.h"

void kmain () 
{
    screen_clear();
    screen_write_string(0, 0, 0x07, "Hello, kernel");
    screen_write_string(0, 1, 0x70, "screen_write_string");
}
