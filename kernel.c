#include <types.h>
#include <video.h>

void kmain(void)
{
    init_video();

    uint32_t i;
    for (i = 0; i < VGA_HEIGHT; i++)
        write_str("Hello, Kernel World!\n");
    write_str("yet another line.\n");
    write_color_str("COLOR_BROWN on white\n", COLOR_BROWN, COLOR_WHITE);
}
