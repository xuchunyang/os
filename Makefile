# Make sure cross compiler tools is in PATH
CROSS_PREFIX = i386-elf
CC = ${CROSS_PREFIX}-gcc
LD = ${CROSS_PREFIX}-ld
AS = nasm

CFLAGS := -Wall -O0 -m32 -ffreestanding -fno-exceptions -fno-stack-protector -nostdinc -fno-builtin -std=gnu99

SOURCES = kernel.c
OBJECTS = $(SOURCES:.c=.o)

all: kernel run

kernel: boot.o ${OBJECTS}
	${LD} -m elf_i386 -T linker.ld -o $@ $^

boot.o: boot.asm
	${AS} -f elf boot.asm

%.o: %.c
	${CC} ${CFLAGS}  $< -c -o $@

run:
	qemu-system-i386 -kernel kernel

clean:
	rm -f *.o kernel
