# CROSS_PREFIX = i386-elf-
CC = $(CROSS_PREFIX)gcc
LD = $(CROSS_PREFIX)ld
AS = nasm

CFLAGS = -Wall -ffreestanding -fno-builtin -nostdlib -nostdinc -fno-omit-frame-pointer -I./inc/
C_SRCS = kernel.c string.c video.c
C_OBJS = $(C_SRCS:.c=.o)

all: myos.iso

start.o: start.asm
	nasm -f elf32 $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel.bin: start.o $(C_OBJS)
	$(LD) -m elf_i386 -T link.ld $^ -o $@

myos.iso: kernel.bin
	@./disk.sh

run-qemu: myos.iso
	qemu-system-i386 -cdrom myos.iso -boot cd -m 64

clean:
	rm -f start.o $(C_OBJS) kernel.bin myos.iso
