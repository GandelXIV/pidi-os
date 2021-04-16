.DEFAULT_GOAL=os-image.bin
.SILENT:run

C_COMPILER ?= gcc
ASSEMBLER ?= nasm
FORMAT ?= elf64
LINKER ?= ld
EMULATOR ?= qemu-system-x86_64


os-image.bin: mk/kernel.bin mk/bootsect.bin
	cat mk/bootsect.bin mk/kernel.bin > os-image.bin
	chmod +x os-image.bin

mk/kernel.bin: mk/kernel.o mk/kernel_entry.o
	$(LINKER) -o mk/kernel.bin -Ttext 0x1000 mk/kernel_entry.o mk/kernel.o --oformat binary

mk/kernel.o: kernel/ drivers/
	$(C_COMPILER) -ffreestanding -c kernel/kernel.c -o mk/kernel.o

mk/kernel_entry.o: kernel/kernel_entry.asm
	$(ASSEMBLER) -f $(FORMAT) kernel/kernel_entry.asm -o mk/kernel_entry.o

mk/bootsect.bin: boot/
	$(ASSEMBLER) -f bin -o mk/bootsect.bin boot/bootsect.asm
	chmod +x mk/bootsect.bin

run: os-image.bin
	$(EMULATOR) os-image.bin

clean:
	rm -f mk/*
	rm -f os-image.bin
