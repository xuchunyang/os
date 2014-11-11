# CROSS_PREFIX = i386-elf-
CC = $(CROSS_PREFIX)gcc
LD = $(CROSS_PREFIX)ld
AS = nasm

CFLAGS = -Wall -ffreestanding -nostdlib

all: myos.iso

start.o: start.asm
	nasm -f elf32 $< -o $@

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel.bin: start.o kernel.o
	$(LD) -m elf_i386 -T link.ld $^ -o $@

myos.iso: kernel.bin
	@./disk.sh

run-qemu: myos.iso
	qemu-system-i386 -cdrom myos.iso -boot cd -m 64

clean:
	rm -f start.o kernel.o kernel.bin myos.iso
