all: os.img

run: os.img
	qemu-system-i386 $<

# For QEMU, 'qemu os.bin' does not work
os.img: os.bin
	qemu-img create -f raw $@ 1.4M
	dd conv=notrunc if=$< of=$@

# This is the actual disk image that the computer loads,
# which is the combination of compiled bootsector and kernel.
os.bin: boot_sect.bin kernel.bin
	cat $^ > $@

# Assemble the boot sector to raw machine code
# 	The -I options tells nasm where to find assembly
# 	routines which included in boot_sect.asm
boot_sect.bin: boot_sect.asm
	nasm -f bin -I './' $< -o $@

# This builds the binary of the kernel from two object files:
# - the kernel_entry, which jump to main() in the kernel
# - the compiled C kernel
kernel.bin: kernel_entry.o kernel.o
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Build the kernel object file
kernel.o: kernel.c
	i386-elf-gcc -ffreestanding -c $< -o $@

# Build the kernel entry object file
kernel_entry.o: kernel_entry.asm
	nasm $< -f elf -o $@


clean:
	-rm -f *.bin *.o os.img
