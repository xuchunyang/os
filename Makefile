CC = i386-elf-gcc
LD = i386-elf-ld

CFLAGS = -ffreestanding -fno-builtin -nostdlib -nostdinc
CFLAGS += -g -Wall

all:  floppy.img

floppy.img: boot_sect.bin kernel.bin
	cat boot_sect.bin kernel.bin /dev/zero | dd bs=512 count=2880 of=floppy.img

# '0x1000' find correct address of labels
kernel.bin: kernel.c
	${CC} ${CFLAGS} -c kernel.c -o kernel.o
	${LD} -o kernel.bin -Ttext 0x1000 kernel.o --oformat binary

boot_sect.bin: boot_sect.asm
	nasm -f bin $< -o $@

run: floppy.img
	qemu-system-i386 floppy.img

clean:
	rm -f *.bin
