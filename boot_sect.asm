; boot_sect.asm -- A simple boot sector program that print message vis BIOS

bits 16                   
org 0x7c00 ; tell NASM to correct address of label

start:
    mov ah, 0x0e

    mov al, [sample_char] ; do not need to fix label address now
    int 0x10

    jmp $

sample_char: db 'X' ; find its absoult memory address

times 510-($-$$) db 0   ; Pad remainder of boot sector with 0s
dw 0xAA55               ; boot signature
