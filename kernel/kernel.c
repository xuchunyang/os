#include <types.h>
#include <video.h>
#include <string.h>
#include <gdt.h>

#define sti() __asm__ ("sti")
#define cli() __asm__ ("cli")

void kmain()
{
    init_video();
    kprintf("Enter kernel\n");

    cli();
    gdt_init();

    kprintf("todo: xxx\n");
}
