# Mac OS X does not use ELF binaries, a cross-compiler is necessary.
CC = i386-elf-gcc
LD = i386-elf-ld

# '-I./ -nostdinc': do not include sys header files, only use in directories specified with -I
CFLAGS = -Wall -O0 -I./kernel/ -nostdinc -fno-builtin -fomit-frame-pointer

# Automatically generate lists of sources using wildcards.
C_SOURCES = $(wildcard kernel/*.c)
HEADERS = $(wildcard kernel/*.h)

OBJ = $(C_SOURCES:.c=.o)

all: os.img run

run: os.img
	qemu-system-i386 -serial stdio $<

# For QEMU, 'qemu os.bin' does not work
os.img: os.bin
	qemu-img create -f raw $@ 1.4M
	dd conv=notrunc if=$< of=$@

# This is the actual disk image that the computer loads,
# which is the combination of compiled bootsector and kernel.
os.bin: boot/boot_sect.bin kernel.bin
	cat $^ > $@

# Assemble the boot sector to raw machine code
# 	The -I options tells nasm where to find assembly
# 	routines which included in boot_sect.asm
# boot_sect.bin: boot/boot_sect.asm

# This builds the binary of the kernel from two object files:
# - the kernel_entry, which jump to main() in the kernel
# - the compiled C kernel
kernel.bin: kernel/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

# Generic rule for building 'somefile.o' from 'somefile.c'
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

# Build the kernel entry object file
%.o: %.asm
	nasm $< -f elf -o $@

# Build the boot sector binary object file
%.bin: %.asm ${ASM_DEPS}
	nasm -f bin -I './boot/include/' $< -o $@

clean:
	rm -f *.bin *.o os.img
	rm -f boot/*.o boot/*.bin
	rm -f kernel/*.o kernel/*.bin
