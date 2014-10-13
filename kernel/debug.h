#ifndef DEBUG_H
#define DEBUG_H

#include <types.h>

void debug_init();
void debug_puts(char *msg);
void debug_putsl(char *msg, uint32_t val);

#endif // DEBUG_H
