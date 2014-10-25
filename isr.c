#include "common.h"
#include "isr.h"
#include "video.h"

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
    printf("isr_handle %d\n", regs.int_no);
}
