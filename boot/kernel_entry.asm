[bits 32] ; Protected mode
[extern kmain] ; Declare external symbol 'main' for linker to find the real address
call kmain ; Invoke main() in C kernel
jmp $
