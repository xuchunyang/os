#include "types.h"
#include "video.h"
#include "gdt.h"

void kmain ()
{
    screen_clear();

    init_gdt();

    init_idt();
    asm volatile ("int $0x3");
}
