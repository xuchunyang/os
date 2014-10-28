// https://github.com/apparentlymart/ToyOS/blob/master/debug.c

#include <common.h>

#define PORT 0x3f8       // COM!

char hex[] = "0123456789abcdef";

void init_serial() {
    outb(PORT + 1, 0x00); // Disable serial port interrupts
    outb(PORT + 3, 0x80); // Enable setting baud rate divider
    outb(PORT + 0, 0x03); // Set divider for 38400 baud
    outb(PORT + 1, 0x00); // Set divider high byte
    outb(PORT + 3, 0x03); // 8 bits, no partity, one stop bit
    outb(PORT + 2, 0xC7); // enable FIFO
    outb(PORT + 4, 0x0b); // Enable IRQs, RTS and DSR
}

char read_serial()
{
    while ((inb(PORT + 5) & 1) == 0)
        ;
    return inb(PORT);
}

void write_serial(char a)
{
    while ((inb(PORT + 5) & 0x20) == 0)
        ;
    outb(PORT, a);
}

void serial_debug_puts(char *msg) {

    for (char *ch = msg; *ch != 0; ch++) {
        outb(PORT, *ch);
    }

    outb(PORT, '\n');
}

void serial_debug_putsl(char *msg, u32 val) {

    for (char *ch = msg; *ch != 0; ch++) {
        outb(PORT, *ch);
    }
    outb(PORT, ':');
    outb(PORT, ' ');
    outb(PORT, '0');
    outb(PORT, 'x');

    for (int i = 0; i < 8; i++) {
        outb(PORT, hex[val >> 28]);
        val <<= 4;
    }

    outb(PORT, '\n');
}
