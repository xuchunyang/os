// Basic Operating System.
// The GDT.

#include <gdt.h>

// The GDT itself.
gdt_entry_t gdt[5];
gdt_ptr_t gdt_ptr;

// Set a GDT entry.
static void set_gdt_entry(unsigned int entry, uint32_t base, uint32_t limit,
                          uint8_t access_byte, uint8_t flags_and_limit_16_19)
{
    gdt[entry].limit_0_15 = limit & 0xFFFF;
    gdt[entry].base_0_15 = base & 0xFFFF;
    gdt[entry].base_16_23 = (base >> 16) & 0xFF;
    gdt[entry].access_byte = access_byte;
    gdt[entry].flags_and_limit_16_19 = flags_and_limit_16_19;
    gdt[entry].base_24_31 = (base >> 24) & 0xFF;
}

// Initialize and load the GDT.
void init_gdt(void)
{
    // Fill in the GDT descriptor.
    gdt_ptr.size = sizeof (gdt_entry_t) * 5 - 1;
    gdt_ptr.address = (uint32_t) &gdt;

    // Fill in the GDT.
    set_gdt_entry (0, 0x00000000, 0x00000000, 0x00, 0x00); // null
    set_gdt_entry (1, 0x00000000, 0xFFFFFFFF, 0x9A, 0xCF); // ring0 code
    set_gdt_entry (2, 0x00000000, 0xFFFFFFFF, 0x92, 0xCF); // ring0 data
    set_gdt_entry (3, 0x00000000, 0xFFFFFFFF, 0xFA, 0xCF); // ring3 code
    set_gdt_entry (4, 0x00000000, 0xFFFFFFFF, 0xF2, 0xCF); // ring3 data

    // Load the GDT.
    load_gdt();
}
