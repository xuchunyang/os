CROSS = i686-elf-

CC = $(CROSS)gcc
LD = $(CROSS)ld
AS = nasm
CFLAGS = -std=c99 -Wall -Wextra -ffreestanding -nostdlib -lgcc

ASOURCES = start.asm
AOBJECTS = $(ASOURCES:.asm=.o)
CSOURCES = kernel.c
COMPILES = $(CSOURCES:.c=.o)

OBJECTS = $(AOBJECTS) $(COMPILES)

OUTPUT = kernel.elf

all: build

build: $(OBJECTS) linker.ld
	@echo "Linking kernel..."
	$(CC) $(CFLAGS) -T linker.ld -o $(OUTPUT) $(OBJECTS)
	@echo 'Making iso...'
	@cp $(OUTPUT) isofiles/boot/
	@grub-mkrescue -o os.iso isofiles/

%.o: %.asm
	$(AS) -f elf32 $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(OUTPUT) os.iso
	rm -f isofiles/boot/$(OUTPUT)

qemu: build
	@echo "Running QEMU..."
	qemu-system-i386 -boot d -cdrom os.iso -m 64

qemu-gdb: build
	@echo "***************"
	@echo "* Run gdb now *"
	@echo "***************"
	qemu-system-i386 -boot d -cdrom os.iso -m 64 -s -S

gdb:
	@echo "***************"
	@echo "* Running gdb *"
	@echo "***************"
	$(CROSS)gdb

ALLFILES := $(shell git ls-files)
todolist:
	-@for file in $(ALLFILES:Makefile=); do grep -n -F -H -e TODO -e FIXME $$file; done; true
