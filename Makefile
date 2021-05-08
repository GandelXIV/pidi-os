.DEFAULT_GOAL=build/os-image.bin
.PHONY: clean run all full

C_COMPILER ?= gcc -m32
C_FLAGS ?= -ffreestanding -fno-PIC -Os -c
ASSEMBLER ?= nasm
FORMAT ?= elf32
LINKER ?= ld -m elf_i386 -s
EMULATOR ?= qemu-system-i386

# os-image
build/os-image.bin: mk/ build/ mk/kernel.bin mk/bootsect.bin
	@echo "[!] BUILDING OS IMAGE"
	cat mk/bootsect.bin mk/kernel.bin > build/os-image.bin
	chmod +x build/os-image.bin

build/os-image.zip: build/os-image.bin
	@echo "[!] BUILDING IMAGE ZIP"
	zip build/os-image.zip build/os-image.bin

build/os-image.tar: build/os-image.bin
	@echo "[!] BUILDING IMAGE TAR"
	tar -cf build/os-image.tar build/os-image.bin

# kernel
mk/kernel.bin: mk/kernel.o mk/kernel_entry.o mk/display.o mk/keyboard.o mk/port.o mk/idt.o mk/isr.o mk/interrupt.o
	@echo "[!] LINKING KERNEL"
	$(LINKER) -no-PIE -o mk/kernel.bin -Ttext 0x1000 mk/kernel_entry.o mk/kernel.o mk/display.o mk/port.o mk/keyboard.o mk/idt.o mk/interrupt.o mk/isr.o --oformat binary

mk/kernel.o: kernel/kernel.c kernel/*.h kernel/debug.h drivers/*.h firmware/*.h  lib/*
	@echo "[!] COMPILING KERNEL CORE"
	$(C_COMPILER) $(C_FLAGS) kernel/kernel.c -o mk/kernel.o

kernel/debug.h:
	touch kernel/debug.h

mk/kernel_entry.o: kernel/kernel_entry.asm
	@echo "[!] ASSEMBLING KERNEL ENTRY"
	$(ASSEMBLER) -f $(FORMAT) kernel/kernel_entry.asm -o mk/kernel_entry.o

# drivers
mk/display.o: drivers/display.c drivers/display.h drivers/display_color.h lib/type.h firmware/port.h
	@echo "[!] COMPILING DISPLAY DRIVER"
	$(C_COMPILER) $(C_FLAGS) drivers/display.c -o mk/display.o

mk/keyboard.o: drivers/keyboard.c drivers/keyboard.h lib/type.h	firmware/port.h
	@echo "[!] COMPILING KEYBOARD DRIVER"
	$(C_COMPILER) $(C_FLAGS) drivers/keyboard.c -o mk/keyboard.o

# firmware
mk/port.o: firmware/port.c firmware/port.h lib/type.h
	@echo "[!] COMPILING PORT FIRMWARE"
	$(C_COMPILER) $(C_FLAGS) firmware/port.c -o mk/port.o

mk/idt.o: firmware/idt.c firmware/idt.h lib/type.h
	@echo "[!] COMPILING IDT FIRMWARE"
	$(C_COMPILER) $(C_FLAGS) firmware/idt.c -o mk/idt.o

mk/interrupt.o: firmware/interrupt.asm
	@echo "[!] COMPILING INTERRUPT FIRMWARE"
	$(ASSEMBLER) -f $(FORMAT) -o mk/interrupt.o firmware/interrupt.asm

mk/isr.o: firmware/isr.c firmware/isr.h lib/type.h drivers/display.h firmware/idt.h
	@echo "[!] COMPILING ISR FIRMWARE"
	$(C_COMPILER) $(C_FLAGS) firmware/isr.c -o mk/isr.o

# bootsector
mk/bootsect.bin: boot/*
	@echo "[!] ASSEMBLING BOOTSECTOR"
	$(ASSEMBLER) -f bin -o mk/bootsect.bin boot/bootsect.asm
	chmod +x mk/bootsect.bin

# misc
mk/: Makefile
	@echo "[!] CREATING MAKE DIRECTORY"
	mkdir -p mk/

build/:
	@echo "[!] CREATING BUILD DIRECTORY"
	mkdir -p build

tree.png: Makefile
	@echo "[!] RENDERING DEPENDENCY TREE"
	makefile2dot | dot -Tpng > tree.png

colors:
	@echo "[!] COMBINING VGA COLORS"
	tools/gencolors.py drivers/display_color.h

# control
all: tree.png colors build/os-image.zip build/os-image.tar
full: clean all

run: build/os-image.bin
	@echo "[!] RUNNING IMAGE"
	$(EMULATOR) build/os-image.bin

clean:
	@echo "[!] CLEANING"
	rm -f mk/*
	rm -f build/*
	rm -f tree.png
