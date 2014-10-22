[bits 32]
[SECTION .text]

global gdt_flush
extern gp
gdt_flush:
    lgdt [gp]
;;; set ds/es etc to data seg
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret
