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
