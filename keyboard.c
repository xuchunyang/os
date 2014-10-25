#include "keyboard.h"
#include "isr.h"
#include "video.h"

static void keyboard_handler(registers_t *regs)
{
    // Read from the keyboard buffer
    u8 scancode = inb(0x60);
    printf("scancode: %d\n", scancode);
}

void keyboard_init()
{
    printf("keyboard_init\n");

    // Firstly, register our timer callback.
    register_interrupt_handler(IRQ1, &keyboard_handler);

    // Enable the keyboard interrupt.
    // This tells the first interrupt controller to only pay
    // attention to IRQ1, which is the keyboard.
    // FIXME: This should be done in a more respectful way that
    // doesn't force all of the other IRQs off.
    outb(0x21, ~2);
    // Mask everything on the second interrupt controller.
    outb(0xa1, ~0);
}
