[bits 16]
; GDT

gdt_start:

gdt_null: ; null descriptor
    dd 0x0 ; 'dd' => double world (4 bytes)
    dd 0x0

gdt_code: ; the code segment descriptor
    ; base = 0x0, limit = 0xfffff
    ; 1st flags:
    ; type flags:
    ; 2nd flags
    dw 0xffff ; Limit (bits 0-15)
    dw 0x0
    db 0x0
    db 10011010b ; 1st flags, type flags
    db 11001111b ; 2nd flags, Limit
    db 0x0       ; Base

gdt_data: ; the data segment descriptor
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt_end:

; GDT descriptor
gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; size of our GDT, less one of the true size
    dd gdt_start               ; start address of our GDT

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
