#include <types.h>
#include <video.h>
#include <io.h>

void kmain(void)
{
    init_video();

    u32 i;
    for (i = 0; i < VGA_HEIGHT; i++)
        write_str("Hello, Kernel World!\n");
    write_str("yet another line.\n");
    write_color_str("COLOR_BROWN on white\n", COLOR_BROWN, COLOR_WHITE);

    char cpu_type_msg[] = "Running ????????????";
    cpu_type_string(cpu_type_msg + 8); // Writes over the question marks.
    write_str(cpu_type_msg);
}
