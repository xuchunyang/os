; boot_sect.asm -- A simple boot sector program that loops forever.

bits 16

start:
    jmp $

times 510-($-$$) db 0   ; Pad remainder of boot sector with 0s
dw 0xAA55               ; boot signature
