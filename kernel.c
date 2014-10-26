#include "types.h"
#include "video.h"
#include "descriptor_tables.h"
#include "timer.h"
#include "kb.h"

void kmain ()
{
    screen_clear();
    puts("Hello, kernel\n");

    init_descriptor_tables();

    asm volatile("sti");

    printf("DONE %d \n", 2323);

    keyboard_init();
    while (1)
        ;
}
