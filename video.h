#ifndef VIDEO_H
#define VIDEO_H

#include "types.h"

void screen_clear();
void screen_write_char(u8 col, u8 row, u8 attr, char c);
void screen_write_string(u8 col, u8 row, u8 attr, char *str);

void puts(const char *s);
void printf(const char *fmt, ...);

#endif
