#ifndef _VIDEO_H
#define _VIDEO_H

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define VBUFFER_SIZE SCREEN_HEIGHT * SCREEN_WIDTH * 2

void init_screen(void);
void putchar(char c);
void puts(const char* str);

#endif
