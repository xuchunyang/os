#ifndef COMMON_H
#define COMMON_H

#include "types.h"

// TODO Document these macro (userful ref http://skelix.net/skelixos/tutorial03_zh.html)
typedef char* va_list;

#define INTSIZEOF(n) ((sizeof(n)+sizeof(int)-1) & ~(sizeof(int)-1))
#define va_start(ap, format) ( ap = (va_list)(&format) + INTSIZEOF(format))
#define va_end(ap) ( ap=(va_list)0 )
#define va_arg(ap, type) ( *(type*) ((ap += INTSIZEOF(type)) - INTSIZEOF(type)))

void *memset(void *dest, char val, int count);
int strlen(const char *s);

#endif
