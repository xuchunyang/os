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

void outb(u16 port, u8 value);
u8 inb(u16 port);
u16 inw(u16 port);

// serial.c
void init_serial();
void serial_debug_puts(char *msg);
void serial_debug_putsl(char *msg, u32 val);


#define PANIC(msg) panic(msg, __FILE__, __LINE__);
#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))

extern void panic(const char *message, const char *file, u32 line);
extern void panic_assert(const char *file, u32 line, const char *desc);


#endif