#ifndef VIDEO_H
#define VIDEO_H

#include "types.h"

// Clear the screen to all black.
void init_screen();

void put_char(char c);

// Output a null-terminated ASCII string to the monitor.
void puts(const char *s);

// Output a hex value to the monitor.
void monitor_write_hex(u32 n);

// Output a decimal value to the monitor.
void monitor_write_dec(u32 n);

void printf(const char *fmt, ...);

#endif
