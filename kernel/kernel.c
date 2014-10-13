#include <types.h>
#include <video.h>
#include <string.h>

void kmain()
{
    init_video();

    kprintf("My name is %s, I'm %d years old.\n", "Chunyang Xu", 22);
    kprintf("My name is %s, I'm %d years old.\n", "", 22);
}
