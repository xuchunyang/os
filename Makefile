# Make sure cross compiler tools is in PATH
CROSS_PREFIX = i386-elf
# C Compiler
CC = ${CROSS_PREFIX}-gcc
CFLAGS := -I./ -Wall -O0 -m32 -ffreestanding -fno-exceptions -fno-stack-protector -nostdinc -fno-builtin

# Linker
LD = ${CROSS_PREFIX}-ld
LDFLAG = -m elf_i386 -static -L ./ -T ./linker.ld

# Assembly compiler
AS = nasm
ASMFLAG = -f elf


SOURCES = memory.c string.c video.c kernel.c io.c
OBJECTS = $(SOURCES:.c=.o)

all: kernel run

kernel: boot.o ${OBJECTS}
	${LD} ${LDFLAG} -o $@ $^

boot.o: boot.asm
	${AS} ${ASMFLAG} $<

%.o: %.c
	${CC} ${CFLAGS}  $< -c -o $@

run:
	qemu-system-i386 -kernel kernel

clean:
	rm -f *.o kernel
