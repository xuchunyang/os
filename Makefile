all:  floppy.img

floppy.img: boot_sect.bin
	cat boot_sect.bin /dev/zero | dd bs=512 count=2880 of=floppy.img

boot_sect.bin: boot_sect.asm
	nasm -f bin $< -o $@

run: floppy.img
	qemu-system-i386 floppy.img

clean:
	rm -f *.bin
