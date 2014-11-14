CC = i686-elf-gcc
AS = nasm
LD = i686-elf-ld
CFLAGS = -std=gnu99 -g -O0 -Wall -ffreestanding -fno-omit-frame-pointer -fno-builtin -nostdlib -nostdinc -I./inc/
# CFLAGS += -DDEBUG

C_HEADERS = $(wildcard *.h)
C_SRCS = $(wildcard *.c)
C_OBJS = $(C_SRCS:.c=.o)

all:  floppy.img

floppy.img: boot_sect.bin kernel.bin
	cat boot_sect.bin kernel.bin /dev/zero | dd bs=512 count=2880 of=floppy.img

# '0x1000' find correct address of labels
kernel.bin: loader.o gdt.o interrupt.o $(C_OBJS)
	${LD} -o kernel.bin -Ttext 0x1000 -e kmain loader.o $(C_OBJS) gdt.o interrupt.o --oformat binary

boot_sect.bin: boot_sect.asm
	$(AS) -f bin $< -o $@

%.o: %.asm
	$(AS) -f elf $< -o $@

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

qemu: floppy.img
	qemu-system-i386 -net none -cpu pentium3 -serial stdio floppy.img

clean:
	rm -f *.bin *.o floppy.img

# Deps for C-files including headers
$(C_OBJS): $(C_HEADERS)
