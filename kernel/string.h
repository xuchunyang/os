#ifndef STRING_H
#define STRING_H

#include <types.h>

// TODO Document these macro (userful ref http://skelix.net/skelixos/tutorial03_zh.html)
typedef char* va_list;

#define INTSIZEOF(n) ((sizeof(n)+sizeof(int)-1) & ~(sizeof(int)-1))
#define va_start(ap, format) ( ap = (va_list)(&format) + INTSIZEOF(format))
#define va_end(ap) ( ap=(va_list)0 )
#define va_arg(ap, type) ( *(type*) ((ap += INTSIZEOF(type)) - INTSIZEOF(type)))

// Character array manipulation
void *memset(void *dest, char val, int count);

// String examination
size_t strlen(const char *str);
int strcmp(const char *s1, const char *s2);

// String manipulation
char *strcpy(char *dest, const char *src);

// String I/O (using video)
void puts(const char *str);
void kprintf(const char *fmt, ...);

#endif // STRING_H
