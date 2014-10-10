; load DH sectors to ES:BX from drive DL
disk_load:
    push dx

    mov ah, 0x02 ; BIOS read sector func
    mov al, dh ; Read DH sector
    mov ch, 0x00 ; select cylinder 0
    mov dh, 0x00 ; select head 0
    mov cl, 0x02 ; start reading from second sector

    int 0x13 ; bios interrupt

    jc disk_error ; jump if error

    pop dx
    cmp dh, al
    jne disk_error
    ret

disk_error:
    mov si, DISK_ERROR_MSG
    call print_string
    jmp $

DISK_ERROR_MSG db 'Disk read error!', 13, 10, 0
