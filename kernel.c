/*
 * kernel.c -- My Kernel
 */

#include <common.h>

void kmain(void)
{
    clear_screen();
    puts("Hello, my first kernel\n");
    putn("age", 22, 10);
    putn("age", 22, 16);
}
