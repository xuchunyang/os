#ifndef VIDEO_H
#define VIDEO_H

#include <types.h>

void init_video(void);
void write_char(char c);
void write_str(const char* str);
void write_color_str(const char* str, uint8_t color);

#endif
