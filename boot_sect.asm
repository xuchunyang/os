; boot_sect.asm -- A simple boot sector program that print message vis BIOS

bits 16                   
org 0x7c00                      ; tell NASM to correct address of label

KERNEL_OFFSET equ 0x1000 ; This is the memory offset to which we will load our kernel

start:
    mov [BOOT_DRIVE], dl        ; Store boot driver in DL

    mov bp, 0x8000              ; Set stack in a safe place
    mov sp, bp                  ; at 0x8000

    mov si, boot_msg
    call print_str

    call load_kernel

;----------Entering Protected Mode----------;
    cli
    lgdt [gdt_desc]         ; Load the GDT descriptor

    mov eax, cr0            ; Copy the contents of CR0 into EAX
    or eax, 1               ; Set bit 0     (0xFE = Real Mode)
    mov cr0, eax            ; Copy the contents of EAX into CR0

    jmp KERNEL_CODE:init_pm ; Jump to code segment, offset init_pm

    jmp $


;---------------------------------------------------------------
load_kernel:
    mov  si, LOAD_KERNEL_MSG
    call print_str

    ; todo load kernel (from disk)
    mov bx, KERNEL_OFFSET       ; Load 15 sector(2-16) to 0x0000(ES):0x1000(BX)
    mov dh, 15                  ; from disk
    mov dl, [BOOT_DRIVE]
    call disk_load

    ret

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
; Data
boot_msg db 'Booting OS...', 0
HEX_OUT  db '0x0000', 0
hexstr   db '0123456789ABCDEF'
outstr16 db '0x0000', 0  ;register value string
reg16    dw    0         ; pass values to printreg16
DISK_ERROR_MSG db 'Disk read error!', 0
BOOT_DRIVE db 0
LOAD_KERNEL_MSG db 'Loading Kernel...', 0

;----------Global Descriptor Table----------;

gdt:                            ; Address for the GDT

gdt_null:                       ; Null Segment
        dd 0
        dd 0


KERNEL_CODE             equ $-gdt
gdt_kernel_code:
        dw 0FFFFh               ; Limit 0xFFFF
        dw 0                    ; Base 0:15
        db 0                    ; Base 16:23
        db 09Ah                 ; Present, Ring 0, Code, Non-conforming, Readable
        db 0CFh                 ; Page-granular
        db 0                    ; Base 24:31

KERNEL_DATA             equ $-gdt
gdt_kernel_data:
        dw 0FFFFh               ; Limit 0xFFFF
        dw 0                    ; Base 0:15
        db 0                    ; Base 16:23
        db 092h                 ; Present, Ring 0, Data, Expand-up, Writable
        db 0CFh                 ; Page-granular
        db 0                    ; Base 24:32

gdt_end:                        ; Used to calculate the size of the GDT

gdt_desc:                       ; The GDT descriptor
        dw gdt_end - gdt - 1    ; Limit (size)
        dd gdt                  ; Address of the GDT

;------------------------------------------------------------------------------
bits 32
init_pm:
    mov ax, KERNEL_DATA
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    call KERNEL_OFFSET

    jmp $

db 'X_END_X'

times 510-($-$$) db 0   ; Pad remainder of boot sector with 0s
dw 0xAA55               ; boot signature
