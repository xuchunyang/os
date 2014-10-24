; Loader.asm
bits 32
extern kmain
global start

start:
  call kmain ; Call our kernel's kmain() function
