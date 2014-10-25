#include "types.h"
#include "common.h" // memset
#include "video.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

u16 *screen = (u16 *)0xb8000;

void screen_clear()
{
    memset((u8 *)screen, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 2);
}

void screen_write_char(u8 col, u8 row, u8 attr, char c)
{
    screen[col + row * SCREEN_WIDTH] = c | (u16)(attr) << 8;
}

void screen_write_string(u8 col, u8 row, u8 attr, char *str)
{
    u16 *pos = &(screen[col + row * SCREEN_WIDTH]);

    for (; *str != 0; pos++, str++) {
        *pos = ((u16)(*str)) | (u16)(attr) << 8;
    }
}
