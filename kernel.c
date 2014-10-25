#include "types.h"
#include "video.h"
#include "descriptor_tables.h"
#include "timer.h"

void kmain ()
{
    screen_clear();
    puts("Hello, kernel\n");

    init_descriptor_tables();

    asm volatile("sti");
    init_timer(50); // Initialise timer to 50Hz

    printf("DONE %d \n", 2323);
}
