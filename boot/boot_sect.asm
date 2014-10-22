[bits 16]
[org 0x7c00] ; correct label reference
KERNEL_OFFSET equ 0x1000 ; kernel memory offset, which we will load our kernel

    mov [BOOT_DRIVE], dl ; Rememer boot dirve (BIOS stores it in DL)

    mov ax, 0x0
    mov es, ax
    mov bp, 0x8000       ; Set-up the stack
    mov sp, bp

    mov si, MSG_REAL_MODE
    call print_string

    call load_kernel

    call switch_to_pm ; Note that we never return from here

    jmp $

%include "print_sting_bios.asm"
%include "disk_load.asm"
%include "gdt.asm"
%include "print_string_pm.asm"
%include "switch_to_pm.asm"

[bits 16]
load_kernel:
    mov si, MSG_LOAD_KERNEL
    call print_string

    mov bx, KERNEL_OFFSET ; Set-up parameters for our disk_load routine, so
    mov dh, 30            ; that we load the first 15 sectors (excluding the boot sector) from the boot disk
    mov dl, [BOOT_DRIVE]  ; (i.e. our kernel code) to address KERNEL_OFFSET
    call disk_load        ;

    ret


[bits 32]
BEGIN_PM:
; This is where we arrive after switching to and initialising protect mode

    mov ebx, MSG_PROT_MODE
    call print_string_pm

    call KERNEL_OFFSET ; now jump to the address of our loaded
                       ; kernel code, assume the brace positon.
                       ; and cross your fingers. Here we go!

    jmp $

; Global variables
BOOT_DRIVE db 0
MSG_REAL_MODE db 'Started in 16 bit Real Mode', 13, 10, 0
MSG_PROT_MODE db 'Successfully landed in 32 bit Protected Mode', 13, 10, 0
MSG_LOAD_KERNEL db 'Loading kernel into memory.', 13, 10, 0

; Padding
times 510 - ($ - $$) db 0
dw 0xaa55
