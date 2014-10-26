# The linker, compiler, their flags, etc.
CC = i386-elf-gcc
AS = nasm
LD = i386-elf-ld
CFLAGS = -std=gnu99 -g -O0 -Wall -Werror -ffreestanding -fno-omit-frame-pointer -fno-builtin -nostdlib -nostdinc -I./

C_HEADERS = $(wildcard *.h)
C_SRCS = $(wildcard *.c)
C_OBJS = $(C_SRCS:.c=.o)

all:  floppy.img

floppy.img: boot_sect.bin kernel.bin
	cat boot_sect.bin kernel.bin /dev/zero | dd bs=512 count=2880 of=floppy.img

# '0x1000' find correct address of labels
kernel.bin: loader.o gdt.o interrupt.o $(C_OBJS)
	${LD} -o kernel.bin -Ttext 0x1000 loader.o $(C_OBJS) gdt.o interrupt.o --oformat binary

boot_sect.bin: boot_sect.asm
	$(AS) -f bin $< -o $@

%.o: %.asm
	$(AS) -f elf $< -o $@

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

run: floppy.img
	qemu-system-i386 -net none -cpu pentium3 -serial stdio floppy.img

clean:
	rm -f *.bin *.o floppy.img

lines:
	@echo "Project contains" `ls *.h | wc -l` "header files," `ls *.c | wc -l` "source files," `ls *.asm | wc -l` "asm files"
	@echo "\ttotaling" `cat *.h *.c *.asm | wc -l` "lines."

todo:
	@grep -n -r TODO *.h *.c *.asm

# Deps for C-files including headers
$(C_OBJS): $(C_HEADERS)
