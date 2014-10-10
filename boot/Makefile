all: os.img

os.img: os.bin
	qemu-img create -f raw os.img 1.4M
	dd conv=notrunc if=os.bin of=os.img

os.bin: boot_sect.bin kernel.bin
	cat boot_sect.bin kernel.bin > $@

boot_sect.bin: boot_sect.asm
	nasm -f bin $< -o $@

kernel.bin: kernel.c
	i386-elf-gcc -ffreestanding -c $< -o kernel.o
	i386-elf-ld -o $@ -Ttext 0x1000 kernel.o --oformat binary

run: os.img
	qemu-system-i386 $<

clean:
	-rm -f *.bin *.o os.img
