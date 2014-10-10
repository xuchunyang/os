all: kernel.flp

boot_sect.bin: boot_sect.asm
	nasm -f bin $< -o $@

kernel.flp: boot_sect.bin
	qemu-img create -f raw $@ 1.4M
	dd  conv=notrunc if=$< of=$@

run:
	qemu-system-i386 kernel.flp

clean:
	-rm -f boot_sect.bin kernel.flp
