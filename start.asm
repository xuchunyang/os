;
; start.asm -- Magic starts here
;
; Base on https://github.com/arjun024/mkernel/blob/master/kernel.asm
;

bits 32

section .text
    align 4
    dd 0x1BADB002
    dd 0x00
    dd - (0x1BADB002 + 0x00)

global start
extern kmain

start:
    cli
    call kmain
    hlt
