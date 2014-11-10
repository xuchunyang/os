;
; boot.asm
;

[BITS 16]

; 0x7C00 is specified in 'boot.ld'
[GLOBAL _start]
_start:

    mov si, boot_message
    call print_string

    jmp $

print_string:
    mov ah, 0x0E
.repeat:
    lodsb
    cmp al, 0
    je .done
    int 0x10
    jmp .repeat
.done:
    ret

; Data
boot_message: db 'Booting my OS...', 0

times 510-($-$$) db 0           ; Pad reminder of boot sector with 0s
dw 0xAA55                       ; Boot signature
