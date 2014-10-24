; boot_sect.asm -- A simple boot sector program that print message vis BIOS

bits 16                   
org 0x7c00                      ; tell NASM to correct address of label

start:
    mov bp, 0x8000              ; Set stack in a safe place
    mov sp, bp                  ; at 0x8000

    mov si, boot_msg
    call print_str

    ; todo load kernel (from disk)

;----------Entering Protected Mode----------;
enter_pm:
    cli
    lgdt [gdt_desc]         ; Load the GDT descriptor

    mov eax, cr0            ; Copy the contents of CR0 into EAX
    or eax, 1               ; Set bit 0     (0xFE = Real Mode)
    mov cr0, eax            ; Copy the contents of EAX into CR0

    jmp KERNEL_CODE:init_pm ; Jump to code segment, offset init_pm

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
DISK_ERROR_MSG db "Disk read error!", 0
BOOT_DRIVE db 0

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

gdt_interrupts:
        dw 0FFFFh
        dw 01000h
        db 0
        db 10011110b
        db 11001111b
        db 0

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
    
    mov ebp, 0x90000
    mov esp, ebp

    mov edx, 0xb8000
    mov al, 'X'
    mov ah, 0x2f
    mov [edx], ax

    add edx, 30
    mov word [edx], 0x1234

    jmp $

db 'X_END_X'

times 510-($-$$) db 0   ; Pad remainder of boot sector with 0s
dw 0xAA55               ; boot signature
