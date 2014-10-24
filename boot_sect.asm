; boot_sect.asm -- A simple boot sector program that print message vis BIOS

bits 16                   
org 0x7c00                      ; tell NASM to correct address of label

start:
    mov [BOOT_DRIVE], dl        ; BIOS store our boot driver in DL, save it

    mov bp, 0x8000              ; Set stack in a safe place
    mov sp, bp                  ; at 0x8000

    mov bx, 0x9000              ; Load 5 sectors (2-6) to 0x0000(ES):0x9000(BX)
    mov dh, 5                   ; from the boot disk
    mov dl, [BOOT_DRIVE]
    call disk_load

    mov si, boot_msg
    call print_str
    
    mov dx, [0x9000 + 512]
    mov [reg16], dx
    call printreg16

    mov dx, [0x9000 + 512 - 1]
    mov [reg16], dx
    call printreg16

    jmp $

;---------------------------------------------------------------
; load DH sectors to ES:BX from drive DL
disk_load:
    push dx                     ; Store DX on stack so later we can recall 
                                ; how many sectors were request to be read
    mov ah, 0x02                ; BIOS read sector function
    mov al, dh                  ; Read DH sectors
    mov ch, 0x00                ; Select cylinder 0 
    mov dh, 0x00                ; Select head 0
    mov cl, 0x02                ; Start reading from second sector (i.e.
                                ; after the boot sector)
    int 0x13                    ; BIOS interrupt (INT 0x13, AH = 2 -- read floppy/hard disk in CHS mode)

    jc disk_error               ; Jump if error (i.e. carry flag set)
    
    pop dx                      ; Restore DX from the stack
    cmp dh, al                  ; if AL (sectors read) != DH (sectors expected)
    jne disk_error              ;    display error message
    ret

disk_error:
    
    mov si, DISK_ERROR_MSG
    call print_str
    jmp $


;---------------------------------------------------------------
; @si (address of string)
print_str:
    mov ah, 0x0e
.repeat:
    lodsb               ; load byte at address DS:(E)SI into AL
    cmp al, 0
    je .done            ; if ( al == 0 ), end loop
    int 0x10            ; else, loop again
    jmp .repeat
.done:
    ret

;---------------------------------------------------------------
; @ [reg16] (save double-bytes to [reg16]
printreg16:
   mov di, outstr16 + 2
   mov ax, [reg16]
   mov si, hexstr
   mov cx, 4            ; four places
hexloop:
   rol ax, 4            ; leftmost will
   mov bx, ax           ; become
   and bx, 0x0f         ; rightmost
   mov bl, [si + bx]    ;index into hexstr
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
reg16   dw    0         ; pass values to printreg16
DISK_ERROR_MSG db "Disk read error!", 0
BOOT_DRIVE db 0

times 510-($-$$) db 0   ; Pad remainder of boot sector with 0s
dw 0xAA55               ; boot signature

times 256 dw 0xdada             ; 2nd sector
times 256 dw 0xface             ; 3rd sector
