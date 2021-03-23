QEMU ?= qemu-system-x86_64 os-image

run: os-image
	$(QEMU)

os-image: mk/bootsector.bin mk/kernel.bin
	rm -f os-image
	cat mk/bootsector.bin >> os-image
	cat mk/kernel.bin >> os-image

mk/bootsector.bin: boot/
	nasm -f bin boot/bootsector.asm -o mk/bootsector.bin

mk/kernel.bin: mk/kernel.o
	ld -o mk/kernel.bin -Ttext 0x1000 --oformat binary mk/kernel.o

mk/kernel.o: kernel/kernel.c
	gcc -ffreestanding -c kernel/kernel.c -o mk/kernel.o

clean:
	rm mk/*
	rm os-image
