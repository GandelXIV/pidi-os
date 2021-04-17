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
	@echo "[!] BUILDING OS IMAGE"
	cat mk/bootsect.bin mk/kernel.bin > os-image.bin
	chmod +x os-image.bin

# kernel
mk/kernel.bin: mk/kernel.o mk/kernel_entry.o mk/display.o mk/port.o
	@echo "[!] LINKING KERNEL"
	$(LINKER) -no-PIE -o mk/kernel.bin -Ttext 0x1000 mk/kernel_entry.o mk/kernel.o mk/display.o mk/port.o --oformat binary

mk/kernel.o: kernel/* drivers/display.h drivers/port.h
	@echo "[!] COMPILING KERNEL"
	$(C_COMPILER) $(C_FLAGS) kernel/kernel.c -o mk/kernel.o

mk/kernel_entry.o: kernel/kernel_entry.asm
	@echo "[!] ASSEMBLING KERNEL ENTRY"
	$(ASSEMBLER) -f $(FORMAT) kernel/kernel_entry.asm -o mk/kernel_entry.o

# drivers
mk/display.o: drivers/display.c
	@echo "[!] COMPILING DISPLAY DRIVER"
	$(C_COMPILER) $(C_FLAGS) drivers/display.c -o mk/display.o

mk/port.o: drivers/port.c
	@echo "[!] COMPILING PORT DRIVER"
	$(C_COMPILER) $(C_FLAGS) drivers/port.c -o mk/port.o

# bootsector
mk/bootsect.bin: boot/*
	@echo "[!] ASSEMBLING BOOTSECTOR"
	$(ASSEMBLER) -f bin -o mk/bootsect.bin boot/bootsect.asm
	chmod +x mk/bootsect.bin

# control
run: os-image.bin
	$(EMULATOR) os-image.bin

clean:
	@echo "[!] CLEANING"
	rm -f mk/*
	rm -f os-image.bin
