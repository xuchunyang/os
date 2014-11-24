#include <video.h>
#include <gdt.h>

void kmain(void)
{
    init_screen();
    init_gdt();

    printf("I am %s, %d(0x%x) years old.\n", "Chunyang Xu", 22, 22);
}
