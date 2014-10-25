CC = i386-elf-gcc
LD = i386-elf-ld

CFLAGS = -std=gnu99 -ffreestanding -fno-builtin -nostdlib -nostdinc
CFLAGS += -g -Wall

C_HEADERS = $(wildcard *.h)
C_SRCS = $(wildcard *.c)
C_OBJS = $(C_SRCS:.c=.o)

all:  floppy.img

floppy.img: boot_sect.bin kernel.bin
	cat boot_sect.bin kernel.bin /dev/zero | dd bs=512 count=2880 of=floppy.img

# '0x1000' find correct address of labels
kernel.bin: loader.o $(C_OBJS) ${C_HEADERS}
	${LD} -o kernel.bin -Ttext 0x1000 loader.o $(C_OBJS) --oformat binary

boot_sect.bin: boot_sect.asm
	nasm -f bin $< -o $@

loader.o: loader.asm
	nasm -f elf loader.asm -o loader.o

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

run: floppy.img
	qemu-system-i386 floppy.img

clean:
	rm -f *.bin *.o floppy.img
