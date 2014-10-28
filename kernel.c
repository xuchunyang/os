#include <types.h>
#include <video.h>
#include <descriptor_tables.h>
#include <timer.h>
#include <kb.h>

void kmain ()
{
    init_serial();
    init_screen();
    init_descriptor_tables();
    init_timer(50);
    init_kb();

    PANIC("XXXXXXX");

    while (1);
}
