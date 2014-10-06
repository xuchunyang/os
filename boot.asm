bits 32

global _start
extern kmain

; Multiboot header
section .multiboot
align 4
    dd 0x1BADB002 ; 'magic number' lets bootloader find the header
    dd 0x00       ; 'flag'
    dd -(0x1BADB002 + 0x00) ; 'checksum'

; Setup the stack
section .bootstrap_stack
align 4
stack_bottom: times 16384 db 0
stack_top:

section .text
_start:
    ; Set up a stack (as it grows downwards)
    mov esp, stack_top

    ; Call C function
    call kmain

    ; clear interrupt ('cli')
    cli
.hang:
    ; halt to stop CPU until next interrupt arrives ('halt')
    hlt
    jmp .hang
