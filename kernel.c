#include <video.h>
#include <gdt.h>
#include <idt.h>

void kmain(void)
{
    init_screen();

    printf("init_gdt()..."); init_gdt(); printf("done\n");

    printf("init_idt()..."); init_idt(); printf("done\n");

    Printf("Test interrupt by invoking software interrupt:\n");
    __asm__ volatile ("int $0x2");
    __asm__ volatile ("int $0x3");
}
