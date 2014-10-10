[bits 16]
[org 0x7c00] ; correct label reference

start:
    mov bp, 0x9000
    mov sp, bp

    mov si, MSG_REAL_MODE
    call print_string

    call switch_to_pm ; Note that we never return from here

    jmp $

%include "print_sting_bios.asm"
%include "print_string_pm.asm"
%include "gdt.asm"
%include "switch_to_pm.asm"

[bits 32]
BEGIN_PM:
; This is where we arrive after switching to and initialising protect mode

    mov ebx, MSG_PROT_MODE
    call print_string_pm

    jmp $

; Global variables
MSG_REAL_MODE db 'Started in 16-bit Real Mode', 0
MSG_PROT_MODE db 'Successfully landed in 32-bit Protected Mode', 0

; Padding
times 510 - ($ - $$) db 0
dw 0xaa55
