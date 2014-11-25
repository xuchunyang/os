#ifndef IDT_H
#define IDT_H

#include <stdint.h>

struct idt_entry
{
    uint16_t base_lo;           /* The lower 16 bits of the address to jump to
                                   when this interrupt fires */
    uint16_t sel;               /* Kernel segment selector */
    uint8_t  always0;           /* This must always be zero */
    uint8_t  flags;             /* More flag, see documentation */
    uint16_t base_hi;           /* The upper 16 bits of the address to jump to */
} __attribute__((__packed__));
typedef struct idt_entry idt_entry_t;

struct idt_ptr
{
    uint16_t limit;             /* TODO: WHY 'limit'? what's the meaning of this word? */
    uint32_t base;              /* The address of 1st element in the idt_entry_t array */
} __attribute__((__packed__));
typedef struct idt_ptr idt_ptr_t;

void init_idt(void);

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

#endif
