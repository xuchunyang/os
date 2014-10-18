[bits 32]
[SECTION .text]

[GLOBAL gdt_flush]    ; Allows the C code to call gdt_flush().

; TODO C and ASM code, how to pass parameter / return?
gdt_flush:
    mov eax, [esp+4]  ; Get the pointer to the GDT, passed as a parameter.
    lgdt [eax]        ; Load the new GDT pointer

    mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax        ; Load all data segment selectors
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush   ; 0x08 is the offset to our code segment: Far jump!
.flush:
    ret

[GLOBAL idt_flush]    ; Allows the C code to call idt_flush().

idt_flush:
    mov eax, [esp+4]  ; Get the pointer to the IDT, passed as a parameter.
    lidt [eax]        ; Load the IDT pointer.
    ret

; Using ASM code from C code
[global add_two]
add_two:
    ; setup stack
    push ebp
    mov ebp, esp
    mov eax, [ebp+8]; 1st argument
    mov ecx, [ebp+12]; 2nd argument
    add eax, ecx
    pop ebp
    ret

; int add_one(int * num)
[global add_one]
add_one:
    push ebp
    mov  ebp, esp
    mov ecx, [ebp+8]; 1st argument
    mov eax, 1
    add eax, [ecx] ; add one and return result
    mov [ecx], eax ; save result to num
    pop ebp
    ret
