#include "types.h"
#include "video.h"
#include "gdt.h"

void kmain ()
{
    screen_clear();
    puts("Hello, kernel\n");

    init_gdt();

    init_idt();
    asm volatile ("int $0x3");
    asm volatile ("int $0x8");
}
