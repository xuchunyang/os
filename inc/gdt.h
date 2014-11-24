// Basic Operating System.
// The GDT.

#ifndef GDT_H
#define GDT_H

#include <stdint.h>

// An entry of the GDT.
typedef struct
{
    uint16_t limit_0_15;
    uint16_t base_0_15;
    uint8_t  base_16_23;
    uint8_t  access_byte;
    uint8_t  flags_and_limit_16_19;
    uint8_t  base_24_31;
} __attribute__ ((packed)) gdt_entry_t;

// A descriptor of the GDT.
typedef struct
{
    uint16_t size;
    uint32_t address;
} __attribute__ ((packed)) gdt_ptr_t;

/* start.asm */
extern void load_gdt();

void init_gdt(void);

#endif /* !GDT_H */
