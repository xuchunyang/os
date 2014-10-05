# PC boot process
1. Power on: the PC starts up and run the BIOS (basic I/O system) code.
2. The BIOS looks for various media such as floppy disk or hard drive.
3. The BIOS loads a 512 byte boot sector from the specified media and begins run it.
4. Those 512 bytes then go on to load the OS itself, or a more complex bootloader.

Bootloader --> kernel:
When the bootloader passes control to kernel, the kernel is passed a very minimal environment, in which the stack is not set up yet, virtual memory is not yet enabled, hardware is not initialized, and so on.

Multiboot Standard:
is an easy interface between the bootloader and kernel.

Refer: http://www.gnu.org/software/grub/manual/multiboot/multiboot.html

mutlboot header (some magic number)

# Assembly language (asm)
Assembly is a textual way to represent the instructions that a CPU executes.

NASM is used in this project.

# Project structure
* boot.s - kernel entry point that sets up the processor environment
* kernel.c - my actual kernel routines
* linker.ld - for linking the above files
