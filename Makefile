CROSS_PREFIX = /opt/local/bin/i386-elf

# For kernel-101 (32 Bits and boot from  GRUB)
build:
	nasm -f elf kernel.asm -o kasm.o
	$(CROSS_PREFIX)-gcc -m32 -std=c99 -c kernel.c -o kc.o
	$(CROSS_PREFIX)-ld -m elf_i386 -T linker.ld -o kernel kasm.o kc.o

run:
	qemu-system-i386 -kernel kernel

# For original simple os in Assembly (16 Bits CPU mode)
build_img:
	@echo "building virtual floppy disk image..."
	qemu-img create -f raw kernel.flp 1.4M
	dd status=noxfer conv=notrunc if=kernel.bin of=kernel.flp

run_img:
	@echo "running floppy disk image under qemu..."
	qemu-system-i386 -fda kernel.flp

# build a CD-ROM ISO image with bootable floppy disk emulation, burn the ISO to a CD-R and boot it from a real PC
build_iso:
	@echo "building iso..."
	mkisofs -o kernel.iso -b kernel.flp cdiso/
