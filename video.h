#ifndef VIDEO_H
#define VIDEO_H

void screen_clear();
void screen_write_char(u8 col, u8 row, u8 attr, char c);
void screen_write_string(u8 col, u8 row, u8 attr, char *str);
void printf();

#endif
