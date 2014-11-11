#ifndef COMMON_H
#define COMMON_H

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef char  int8_t;
typedef short int16_t;
typedef int   int32_t;

// string.c
char *itoa (int32_t number, char *str, uint32_t base);
void *memset(void *dest, uint8_t val, int count);
int strlen(const char *str);

// video.c
void clear_screen();
void putch(char ch);
void puts(const char *s);
void putn(const char *name, int32_t n, uint32_t radix);

#endif
