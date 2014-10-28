#include <common.h>
#include <video.h>

void *memset(void *dest, char val, int count)
{
    char *buf = (char*)dest;
    for (int i = 0; i < count; i++) {
        buf[i] = val;
    }
    return dest;
}

int strlen(const char *s)
{
    int len;
    for (len = 0; *s; s++)
        len++;
    return len;
}

 // Write a byte out to the specified port.
 void outb(u16 port, u8 value)
 {
     asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
 }

 u8 inb(u16 port)
 {
     u8 ret;
     asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
     return ret;
 }

 u16 inw(u16 port)
 {
     u16 ret;
     asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
     return ret;
 }


extern void panic(const char *message, const char *file, u32 line)
{
    // We encountered a massive problem and have to stop.
    asm volatile("cli"); // Disable interrupts.

    printf("PANIC(%s) at %s : %d\n", message, file, line);
    // Halt by going into an infinite loop.
    for(;;);
}

extern void panic_assert(const char *file, u32 line, const char *desc)
{
    // An assertion failed, and we have to panic.
    asm volatile("cli"); // Disable interrupts.

    printf("ASSERTION-FAILED(%s) at %s:%d\n", desc, file, line);
    // Halt by going into an infinite loop.
    for(;;);
}
