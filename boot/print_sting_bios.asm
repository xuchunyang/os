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


; dx
print_hex:
    ; todo
    mov ax, dx
    mov di, HEX_OUT + 2 ; jump '0x'
    mov si, hexstr
    mov cx, 4 ; four places
hexloop:
    rol ax, 4 ; leftmost will
    mov bx, ax ; become
    and bx, 0x0f ; rightmost
    mov bl, [si+bx]; index into hexstr
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
    db '01234567890ABCDEF'
