#include <types.h>
#include <video.h>
#include <string.h>
#include <io.h>
#include <debug.h>

#include <dbg.h>

void kmain()
{
    debug_init();
    debug_puts("OS started kmain()");

    init_video();
    log_info("enter C code: kmain()");

    debug_puts("OS ended kmain()");
}
