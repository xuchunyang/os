#include <types.h>
#include <video.h>

void kmain()
{
    init_video();
    uint32_t i;
    for (i = 0; i < 20; i++)
        write_str("Hello, Kernel World!\n");

    write_str("yet another line.\n");
}
