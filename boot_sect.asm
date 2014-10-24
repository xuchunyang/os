; boot_sect.asm -- A simple boot sector program that print message vis BIOS

bits 16

start:
    mov ah, 0x0e
    mov al, 'H'
    int 0x10     ; (INT 0x10 / AH=0x0E) -> Video display char

    jmp $

times 510-($-$$) db 0   ; Pad remainder of boot sector with 0s
dw 0xAA55               ; boot signature
