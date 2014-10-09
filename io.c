#include <io.h>

void outb(u16 port, u8 val)
{
    asm volatile ("outb %1, %0" :: "dN" (port), "a" (val));;
}

u8 inb(u16 port)
{
    u8 rtv;
    asm volatile ("inb %1, %0": "=a" (rtv) : "dN" (port));
    return rtv;
}

void outl(u16 port, u32 val)
{
    asm volatile ("outl %1, %0" : : "dN" (port), "a" (val));
}

u32 inl(u16 port)
{
    u32 rtv;
    asm volatile("inl %1, %0" : "=a" (rtv) : "dN" (port));
    return rtv;
}

void cpu_type_string(char *out)
{
    u32 *lout = (s32*)out;
    asm volatile (
        "cpuid" :
        "=b" (*(lout+0)),
        "=c" (*(lout+2)),
        "=d" (*(lout+1)) :
        "a" (0)
    );
}
