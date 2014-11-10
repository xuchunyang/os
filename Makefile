AS = nasm
LD = i386-elf-ld

all: os.img

os.img: boot.bin
	dd if=$^ of=$@ bs=512 count=1

boot.bin: boot.asm
	$(AS) -f elf $^ -o boot.elf
	$(LD) -m elf_i386 boot.elf -o $@ -T boot.ld

run: os.img
	qemu-system-i386 -m 128 -fda $^

clean:
	rm -f boot.elf boot.bin os.img
