#include "common.h"
#include "isr.h"
#include "video.h"

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
    screen_write_string(0, 20, 0x07, "isr_handler");
}

