.DEFAULT_GOAL=os-image.bin
.SILENT:run

C_COMPILER ?= gcc -m32
C_FLAGS ?= -ffreestanding -fno-PIC -c
ASSEMBLER ?= nasm
FORMAT ?= elf32
LINKER ?= ld -m elf_i386 -s
EMULATOR ?= qemu-system-x86_64

# os-image
os-image.bin: mk/kernel.bin mk/bootsect.bin
	cat mk/bootsect.bin mk/kernel.bin > os-image.bin
	chmod +x os-image.bin

# kernel
mk/kernel.bin: mk/kernel.o mk/kernel_entry.o
	$(LINKER) -no-PIE -o mk/kernel.bin -Ttext 0x1000 mk/kernel_entry.o mk/kernel.o --oformat binary

mk/kernel.o: kernel/kernel.c drivers/display.h
	$(C_COMPILER) $(C_FLAGS) kernel/kernel.c -o mk/kernel.o

mk/kernel_entry.o: kernel/kernel_entry.asm
	$(ASSEMBLER) -f $(FORMAT) kernel/kernel_entry.asm -o mk/kernel_entry.o

# bootsector
mk/bootsect.bin: boot/
	$(ASSEMBLER) -f bin -o mk/bootsect.bin boot/bootsect.asm
	chmod +x mk/bootsect.bin

# control
run: os-image.bin
	$(EMULATOR) os-image.bin

clean:
	rm -f mk/*
	rm -f os-image.bin
