#include <types.h>

// GDT reference:
// 1. http://wiki.osdev.org/Global_Descriptor_Table
// 2. http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html

/*
 *    7  6  5    4  3    0
 *  +---------------------+
 *  | P | DPL | DT | Type |
 *  +---------------------+
 *  Access byte format
 *
 *  P: is segment present? (1 = Yes)
 *  DPL: Descriptor Privilege Level - Ring 0-3
 *  DT: Descriptor Type
 *  Type: Segment type - code segment / data segment
 *
 *   7   6   5   4
 *  +---------------+
 *  | G | D | 0 | A |
 *  +---------------+
 *  Flags
 *
 *  G: Granularity (间隔尺度) (0 = 1 byte, 1 = 1 kbyte)
 *  D: Operand size (0 = 16bit, 1 = 32bit)
 *  0: Shoud always be zero.
 *  A: Available for system use (always zero).
 */
struct gdt_entry_struct {
    uint32_t        limit0_15:16; // limit low
    uint32_t        base0_15 :16; // base low
    uint32_t        base16_23:8;  // base next 8 bits
    uint32_t        acces:8;      // Access flags, determine what ring this segment can be used in.
    uint32_t        limit16_19:4;
    uint32_t        flags:4;     // Flags
    uint32_t        base24_31:8; // base hight
} __attribute__ ((packed));
typedef struct gdt_entry_struct gdt_entry_t;


struct gdt_ptr_struct {
    uint16_t limit;      // The size of the GDT table
    uint32_t base;        // The address of the first gdt_entry_t struct
} __attribute__ ((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

// TODO: Init GDT
// Initialisation function is publicly accessible.
void init_gdt();
