#include "gdt.h"
#include "video.h"
#include "common.h"

extern void gdt_flush(u32);
static void gdt_set_gate(int, u32, u32, u8, u8);

struct gdt_entry gdt_entries[5];
struct gdt_ptr   gdtr;

void init_gdt()
{
    screen_write_string(0, 1, 0x07, "init_gdt");
    gdtr.limit = sizeof(gdt_entries) - 1;
    gdtr.base  = (u32)&gdt_entries;

    // Setup 4 GB address, code/data segment overlaps
    gdt_set_gate(0, 0, 0, 0, 0);                // null segment (0x00 Selector)
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // kernel code segment (0x08 Selector)
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // kernel data segment (0x10 Selector)
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User Mode code segment (0x18 Selector)
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User Mode data segment (0x20 Selector)

    gdt_flush((u32)&gdtr);
    screen_write_string(0, 2, 0x07, "done");
}

static void gdt_set_gate(int num, u32 base, u32 limit, u8 access, u8 gran)
{
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access      = access;
}

extern void idt_flush(u32);

static void idt_set_gate(u8, u32, u16, u8);

struct idt_entry idt_entries[256];
struct idt_ptr   idtr;

void init_idt()
{
    screen_write_string(0, 10, 0x07, "init_ide...");

    idtr.limit = sizeof(idt_entries) - 1;
    idtr.base  = (u32)&idt_entries;

    memset(&idt_entries, 0, sizeof(idt_entries));

    idt_set_gate( 0, (u32)isr0, 0x08, 0x8E);
    idt_set_gate( 1, (u32)isr1, 0x08, 0x8E);
    idt_set_gate( 2, (u32)isr2, 0x03, 0x8E);
    idt_set_gate( 3, (u32)isr3, 0x08, 0x8E);
    idt_set_gate( 4, (u32)isr4, 0x08, 0x8E);
    idt_set_gate( 5, (u32)isr5, 0x08, 0x8E);
    idt_set_gate( 6, (u32)isr6, 0x08, 0x8E);
    idt_set_gate( 7, (u32)isr7, 0x08, 0x8E);
    idt_set_gate( 8, (u32)isr8, 0x08, 0x8E);
    idt_set_gate( 9, (u32)isr9, 0x08, 0x8E);
    idt_set_gate( 10, (u32)isr11, 0x08, 0x8E);
    idt_set_gate( 11, (u32)isr12, 0x08, 0x8E);
    idt_set_gate( 12, (u32)isr13, 0x08, 0x8E);
    idt_set_gate( 13, (u32)isr14, 0x08, 0x8E);
    idt_set_gate( 14, (u32)isr15, 0x08, 0x8E);
    idt_set_gate( 15, (u32)isr15, 0x08, 0x8E);
    idt_set_gate( 16, (u32)isr16, 0x08, 0x8E);
    idt_set_gate( 17, (u32)isr17, 0x08, 0x8E);
    idt_set_gate( 18, (u32)isr18, 0x08, 0x8E);
    idt_set_gate( 19, (u32)isr19, 0x08, 0x8E);
    idt_set_gate( 20, (u32)isr20, 0x08, 0x8E);
    idt_set_gate( 21, (u32)isr21, 0x08, 0x8E);
    idt_set_gate( 22, (u32)isr22, 0x08, 0x8E);
    idt_set_gate( 23, (u32)isr23, 0x08, 0x8E);
    idt_set_gate( 24, (u32)isr24, 0x08, 0x8E);
    idt_set_gate( 25, (u32)isr25, 0x08, 0x8E);
    idt_set_gate( 26, (u32)isr26, 0x08, 0x8E);
    idt_set_gate( 27, (u32)isr27, 0x08, 0x8E);
    idt_set_gate( 28, (u32)isr28, 0x08, 0x8E);
    idt_set_gate( 29, (u32)isr29, 0x08, 0x8E);
    idt_set_gate( 30, (u32)isr30, 0x08, 0x8E);
    idt_set_gate( 31, (u32)isr31, 0x08, 0x8E);

   idt_flush((u32)&idtr);
   screen_write_string(0, 11, 0x07, "done");
}


static void idt_set_gate(u8 num, u32 base, u16 sel, u8 flags)
{
   idt_entries[num].base_low = base & 0xFFFF;
   idt_entries[num].base_high= (base >> 16) & 0xFFFF;

   idt_entries[num].sel     = sel;
   idt_entries[num].always0 = 0;
   // We must uncomment the OR below when we get to using user-mode.
   // It sets the interrupt gate's privilege level to 3.
   idt_entries[num].flags   = flags /* | 0x60 */;
}
