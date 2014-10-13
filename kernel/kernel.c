#include <types.h>
#include <video.h>
#include <string.h>
#include <io.h>
#include <debug.h>

void kmain()
{
    debug_init();
    debug_puts("OS started kmain()");

    init_video();
    kprintf("My name is %s, I'm %d years old.\n", "Chunyang Xu", 22);
    kprintf("My name is %s, I'm %d years old.\n", "", 22);

    debug_puts("OS ended kmain()");
}
