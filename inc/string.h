#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

/* TODO: implement this, refer to http://tia.mat.br/blog/html/2014/06/23/integer_to_string_conversion.html*/
char *uint32_to_str (uint32_t value, char *buf, uint32_t base);
uint32_t strlen (const char *str);
void strcpy (char *dest, const char *src);
void strncpy (char *dest, const char *src, uint32_t n);

uint8_t *memcpy (uint8_t *, uint8_t *, uint32_t);
uint8_t *memset (uint8_t *, uint8_t, uint32_t);

#endif
