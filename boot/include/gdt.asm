[bits 16]
; GDT
gdt_start:

; GDT 中有五条描述符，这里使用前三个
; 一个 GDT 描述符长度为8 bytes，包括一个 32 bits 的基址(Base)和 20 bits 的长度(Limit)。Base 制定了段从哪里开始，Limit指定了段的长度，20 bits长度能表示
; 2^20 = 1 MB，再由 G 选项指定单位是1 bytes 还是 4 k bytes

; 第一个是 Intel 要求的空描述符
gdt_null: ; null descriptor (8 bytes each GDT descriptor)
    dd 0x0
    dd 0x0

; 第二个是为 CS 准备的描述符
gdt_code: ; the code segment descriptor
    ; base = 0x00, limit = 0xfffff
    ; 1st flags: (present)1 (privilege)00 (descriptor type)1 -> 1001b
    ; type flags: (code)1 (conforming)0 (readable)1 (accessed)0 -> 1010b
    ; 2nd flags: (granularity)1 (32-bit default)1 (64-bit seg)0 (AVL)0 -> 1100b
    dw 0xffff ; Limit[0:15]
    dw 0x0    ; Base[0:15]
    db 0x0    ; Base[16:23]
    db 10011010b ; 1st flags, type flags
    db 11001111b ; 2nd flags, Limit[16:19]
    db 0x0       ; Base[24:32]

; 第三个是 DS 准备的描述符
gdt_data: ; the data segment descriptor
    ; Same as code segment except for the type flags:
    ; type flags: (code)0 (expand down)0 (writable)1 (accessed)0 -> 0010b
    dw 0xffff ; Limit[0:15]
    dw 0x0    ; Base[0:15]
    db 0x0    ; Base[16:23]
    db 10010010b ; 1st flags, type flags
    db 11001111b ; 2nd flags, Limit[16:19]
    db 0x0       ; Base[24:32]

gdt_end:

; GDT descriptor
gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; Size of our GDT, always less one of the true size
    dd gdt_start               ; Start address of our GDT

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
