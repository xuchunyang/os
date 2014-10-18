#include <types.h>
#include <video.h>
#include <string.h>
#include <io.h>
#include <debug.h>

#include <dbg.h>

extern int add_two(int, int);
extern int add_one(int *);

void kmain()
{
    init_video();
    log_info("enter C code: kmain()");

    log_info("1 + 2 = %d", add_two(1, 2));

    int c = 3;
    log_info("4 = %d", add_one(&c));
    log_info("4 = %d", c);
}
