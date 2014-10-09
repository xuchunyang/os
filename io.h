#ifndef IO_H
#define IO_H

#include <types.h>

void outb(u16 port, u8 data);
u8 inb(u16 port);
void outs(u16 port, u16 data);
u16 ins(u16 port);
void outl(u16 port, u32 data);
u32 inl(u16 port);
void cpu_type_string(char *out);

#endif
