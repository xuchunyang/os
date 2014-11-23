#include <video.h>
#include <string.h>
#include <stdint.h>

uint16_t* video_buffer;
int cursor_column;
int cursor_row;

void init_screen(void)
{
    video_buffer = (uint16_t *)0xB8000;
    cursor_row = 0;
    cursor_column = 0;
    memset((uint8_t *)0xB8000, 0, VBUFFER_SIZE);
}

void scroll_screen (void)
{
    memcpy((uint8_t *)0xB8000, (uint8_t *)0xB8000 + SCREEN_WIDTH * 2,
            VBUFFER_SIZE - SCREEN_WIDTH * 2);
    memset((uint8_t *)0xB8000 + VBUFFER_SIZE - SCREEN_WIDTH * 2, 0,
            SCREEN_WIDTH * 2);
    cursor_row = SCREEN_HEIGHT - 1;
    cursor_column = 0;
}

void putch_at (char ch, int column, int row)
{
    int offset = (row * SCREEN_WIDTH) + column;
    video_buffer[offset] = ch | (0x07 << 8);
}

void putch (char ch)
{
    if (ch == '\n') {
        ++cursor_row;
        cursor_column = 0;
        if (cursor_row >= SCREEN_HEIGHT)
            scroll_screen();
    } else {
        putch_at(ch, cursor_column, cursor_row);

        ++cursor_column;
        if (cursor_column >= SCREEN_WIDTH) {
            ++cursor_row;
            cursor_column = 0;
            if (cursor_row >= SCREEN_HEIGHT)
                scroll_screen();
        }
    }
}

// Print a string.
void puts(const char *s)
{
    int i;
    for (i = 0; s[i] != '\0'; ++i)
        putch(s[i]);
}
