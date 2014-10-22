// Base on gdt.c from Panda (Yukang Chen (moorekang@gmail.com))
#include <string.h>
#include <gdt.h>

struct gdt_entry gdt[NR_GDTENTRY];
struct gdt_ptr gp;

extern void gdt_flush();

void set_seg(struct gdt_entry* seg, u32 base, u32 limit, u32 dpl, u32 type){
    seg->limit_lo = ((limit) >> 12) & 0xffff;
    seg->base_lo  = (base) & 0xffff;
    seg->base_mi  = ((base) >> 16) & 0xff;
    seg->type     = type;
    seg->s        = 1;
    seg->dpl      = dpl;
    seg->present  = 1;
    seg->limit_hi = (u32) (limit) >> 28;
    seg->avl      = 0;
    seg->r        = 0;
    seg->db       = 1;
    seg->g        = 1;
    seg->base_hi  = (base) >> 24;
}

void set_ldt(struct gdt_entry* seg, u32 base){
    set_seg(seg, base, 0, 0, STS_LDT);
    seg->limit_lo = 0x3;
    seg->s = 0;
}

void set_tss(struct gdt_entry* seg, u32 base){
    set_seg(seg, base, 0, 0, STS_TA);
    seg->limit_lo = 0x68;
    seg->s = 0;
}

void gdt_init(void) {
    puts("[gdt]  .... ");
    memset(gdt, 0, sizeof(gdt));
    gp.limit = (sizeof(struct gdt_entry) * NR_GDTENTRY) - 1;
    gp.base = (u32)&gdt;

    set_seg(&gdt[1], 0, 0xffffffff, 0, STA_X | STA_R);
    set_seg(&gdt[2], 0, 0xffffffff, 0, STA_W);
    set_seg(&gdt[3], 0, 0xffffffff, 3, STA_X | STA_R);
    set_seg(&gdt[4], 0, 0xffffffff, 3, STA_W);
    // load gdt
    gdt_flush();
    puts("done\n");
}
