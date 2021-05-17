.DEFAULT_GOAL=dist/os-image.bin
.PHONY: clean run all full

# config
C_COMPILER ?= gcc -m32
C_FLAGS ?= -ffreestanding -fno-pie -Os -c
ASM_COMPILER ?= nasm
ASM_FORMAT ?= elf32
LINKER ?= ld -m elf_i386 -s
EMULATOR ?= qemu-system-i386

KERNEL_C_SOURCES := $(wildcard kernel/*.c)
KERNEL_C_OBJECTS := $(patsubst kernel/%.c, mk/kernel/%.o, $(KERNEL_C_SOURCES))
DRIVER_C_SOURCES := $(wildcard drivers/*.c)
DRIVER_C_OBJECTS := $(patsubst drivers/%.c, mk/drivers/%.o, $(DRIVER_C_SOURCES))
FIRMWARE_C_SOURCES := $(wildcard firmware/*.c)
FIRMWARE_C_OBJECTS := $(patsubst firmware/%.c, mk/firmware/%.o, $(FIRMWARE_C_SOURCES))
LIB_C_SOURCES := $(wildcard lib/*.c)
LIB_C_OBJECTS := $(patsubst lib/%.c, mk/lib/%.o, $(LIB_C_SOURCES))

C_HEADERS = $(wildcard */*.h)

KERNEL_OBJECTS = $(KERNEL_C_OBJECTS) mk/kernel/kernel_entry.o
DRIVER_OBJECT = $(DRIVER_C_OBJECTS)
FIRMWARE_OBJECTS = $(FIRMWARE_C_OBJECTS) mk/firmware/interrupt.o
LIB_OBJECTS = $(LIB_C_OBJECTS)

dist/os-image.bin: mk/bin/kernel.bin mk/bin/bootsect.bin
	rm -f dist/os-image.bin
	cat mk/bin/* > $@
	chmod +x dist/os-image.bin

# bin
mk/bin/kernel.bin: $(KERNEL_OBJECTS) $(DRIVER_OBJECT) $(FIRMWARE_OBJECTS) $(LIB_OBJECTS)
	$(LINKER) -o $@ -Ttext 0x1000 $^ --oformat binary

mk/bin/bootsect.bin: boot/*
	$(ASM_COMPILER) -f bin -o $@ boot/bootsect.asm
	chmod +x $@

# C files
mk/kernel/%.o: kernel/%.c
	$(C_COMPILER) $(C_FLAGS) -c $< -o $@

mk/drivers/%.o: drivers/%.c
	$(C_COMPILER) $(C_FLAGS) -c $< -o $@

mk/firmware/%.o: firmware/%.c
	$(C_COMPILER) $(C_FLAGS) -c $< -o $@

mk/lib/%.o: lib/%.c
	$(C_COMPILER) $(C_FLAGS) -c $< -o $@

# specific
mk/kernel/kernel_entry.o: kernel/kernel_entry.asm
	$(ASM_COMPILER) -f $(ASM_FORMAT) -o $@ $<

mk/firmware/interrupt.o:
	$(ASM_COMPILER) -f $(ASM_FORMAT) -o $@ firmware/interrupt.asm

# phony
run:
	make clean
	make
	$(EMULATOR) dist/os-image.bin

clean:
	rm -f dist/*
	rm -f mk/bin/*
	rm -f mk/kernel/*
	rm -f mk/drivers/*
	rm -f mk/firmware/*
	rm -f mk/lib/*
