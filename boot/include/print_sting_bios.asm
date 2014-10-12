[bits 16]
; al
print_char:
    mov ah, 0x0e
    int 0x10
    ret

; si
print_string:
    lodsb ; load form si to al byte-by-byte
    cmp al, 0
    je done
    call print_char
    jmp print_string

done:
    ret

; TODO Document this subroutine (including 'rol' instruction)
; dx
print_hex:
    mov di, HEX_OUT + 2
    mov ax, dx ; Save dx, since it will be used for 4 times
    mov si, hexstr
    mov cx, 4
hexloop:
    rol ax, 4
    mov bx, ax
    and bx, 0x0f
    mov bl, [si + bx]
    mov [di], bl
    inc di
    dec cx
    jnz hexloop

    mov si, HEX_OUT
    call print_string

    ret

HELLO_MSG:
    db 'hello world!', 13, 10, 0
GOODBYE_MSG:
    db 'Goodbye!', 13, 10, 0
HEX_OUT:
    db '0x0000', 13, 10, 0
hexstr:
    db '0123456789ABCDEF'
