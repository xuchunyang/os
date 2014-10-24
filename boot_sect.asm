; boot_sect.asm -- A simple boot sector program that print message vis BIOS

bits 16                   
org 0x7c00 ; tell NASM to correct address of label

start:
    mov si, boot_msg
    call print_str
    
    mov dx, 0xabcd
    mov [reg16], dx
    call printreg16

    jmp $

;---------------------------------------------------------------
; @si (address of string)
print_str:
    mov ah, 0x0e
.repeat:
    lodsb      ; load byte at address DS:(E)SI into AL
    cmp al, 0
    je .done ; if ( al == 0 ), end loop
    int 0x10        ; else, loop again
    jmp .repeat
.done:
    ret

;---------------------------------------------------------------
; @ [reg16] (save double-bytes to [reg16]
printreg16:
   mov di, outstr16 + 2
   mov ax, [reg16]
   mov si, hexstr
   mov cx, 4   ;four places
hexloop:
   rol ax, 4   ;leftmost will
   mov bx, ax   ; become
   and bx, 0x0f   ; rightmost
   mov bl, [si + bx];index into hexstr
   mov [di], bl
   inc di
   dec cx
   jnz hexloop
 
   mov si, outstr16
   call print_str
 
   ret
 

;---------------------------------------------------------------
; Data
boot_msg: 
    db 'Booting OS...', 0
; Variable
HEX_OUT: db '0x0000', 0
hexstr   db '0123456789ABCDEF'
outstr16   db '0x0000', 0  ;register value string
reg16   dw    0  ; pass values to printreg16


times 510-($-$$) db 0   ; Pad remainder of boot sector with 0s
dw 0xAA55               ; boot signature
