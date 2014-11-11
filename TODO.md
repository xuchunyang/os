# TODO

> the less knowledgable you are, the more you think you know. In effect, you fail to recognize the scope of knowledge. There is so much stuff to learn, that merely by learning more, you recognize how little you know.
> 
> -- The Dunning-Kruger effect


The Bootloader:

- [x] Boot loader (bring to kernel C code)

   For now, my kernel is multiboot compliant and loads with GRUB(1.x).  
   I still do not know how and when to use GRUB, but I think It's not necessary for now, since I can learn more latter. Some resources, which I ignoreed when I am doing this TODO, may be useful
   
   + [kernel-101-lets-write-a-kernel](http://arjunsreedharan.org/post/82710718100/kernel-101-lets-write-a-kernel)
   + [Chapter 3: First boot with GRUB (from "How to make a Computer Operating System")](https://github.com/SamyPesse/How-to-Make-a-Computer-Operating-System/tree/master/Chapter-3)

   Beside, I also use `grub-mkrescue` to generate a `*.iso` for my OS, this idea is borrowed from [Basic_OS](https://github.com/ExeTwezz/Basic_OS).
   
   In the end, I assembly/compile/link and create iso on my Ubuntu virtual box and run os with qemu from OS X (for qemu the GUI front end)

The Kernel:

- [ ] Setup GDT to define Kenrel and userland memory layout
- [ ] Setup IDT to handle interrupt
