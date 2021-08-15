.DEFAULT_GOAL=dist/os-image.bin
.PHONY: clean run iso all full

# config
C_COMPILER ?= gcc -m32
C_FLAGS ?= -ffreestanding -fno-pie -Os -c
ASM_COMPILER ?= nasm
ASM_FORMAT ?= elf32
LINKER ?= ld -m elf_i386 -s
EMULATOR ?= qemu-system-i386
EMULATOR_FLAGS ?= -cdrom

KERNEL_C_SOURCES := $(wildcard kernel/*.c)
KERNEL_C_OBJECTS := $(patsubst kernel/%.c, mk/kernel/%.o, $(KERNEL_C_SOURCES))
DRIVER_C_SOURCES := $(wildcard drivers/*.c)
DRIVER_C_OBJECTS := $(patsubst drivers/%.c, mk/drivers/%.o, $(DRIVER_C_SOURCES))
CPU_C_SOURCES := $(wildcard cpu/*.c)
CPU_C_OBJECTS := $(patsubst cpu/%.c, mk/cpu/%.o, $(CPU_C_SOURCES))
LIB_C_SOURCES := $(wildcard lib/*.c)
LIB_C_OBJECTS := $(patsubst lib/%.c, mk/lib/%.o, $(LIB_C_SOURCES))
FILESYSTEM_C_SOURCES := $(wildcard fs/*.c)
FILESYSTEM_C_OBJECTS := $(patsubst fs/%.c, mk/fs/%.o, $(FILESYSTEM_C_SOURCES))

C_HEADERS = $(wildcard */*.h) $(wildcard kernel/advanced_cmds/*.h)

KERNEL_OBJECTS = $(KERNEL_C_OBJECTS) mk/kernel/kernel_entry.o
DRIVER_OBJECT = $(DRIVER_C_OBJECTS)
CPU_OBJECTS = $(CPU_C_OBJECTS)
LIB_OBJECTS = $(LIB_C_OBJECTS)
FILESYSTEM_OBJECTS = $(FILESYSTEM_C_OBJECTS)

dist/os-image.bin: mk/bin/kernel.bin mk/bin/bootsect.bin
	rm -f dist/os-image.bin
	cat mk/bin/* > $@
	chmod +x dist/os-image.bin

iso: $(.DEFAULT_GOAL)
	mkdir -p mk/iso/
	rm -f dist/os-image.iso
	truncate $(.DEFAULT_GOAL) -s 1200k
	cp $(.DEFAULT_GOAL) mk/iso/kernel.bin
	mkisofs -b kernel.bin -o dist/os-image.iso mk/iso/

# bin
mk/bin/kernel.bin: $(KERNEL_OBJECTS) $(DRIVER_OBJECT) $(CPU_OBJECTS) $(LIB_OBJECTS) $(FILESYSTEM_OBJECTS)
	$(LINKER) -o $@ -Ttext 0x1000 $^ --oformat binary

mk/bin/bootsect.bin: boot/*
	$(ASM_COMPILER) -f bin -o $@ boot/bootsect.asm
	chmod +x $@

# C files
mk/kernel/%.o: kernel/%.c $(C_HEADERS)
	$(C_COMPILER) $(C_FLAGS) -c $< -o $@

mk/drivers/%.o: drivers/%.c $(C_HEADERS)
	$(C_COMPILER) $(C_FLAGS) -c $< -o $@

mk/CPU/%.o: CPU/%.c $(C_HEADERS)
	$(C_COMPILER) $(C_FLAGS) -c $< -o $@

mk/lib/%.o: lib/%.c $(C_HEADERS)
	$(C_COMPILER) $(C_FLAGS) -c $< -o $@

mk/fs/%.o: fs/%.c $(C_HEADERS)
	$(C_COMPILER) $(C_FLAGS) -c $< -o $@

# specific
mk/kernel/kernel_entry.o: kernel/kernel_entry.asm
	$(ASM_COMPILER) -f $(ASM_FORMAT) -o $@ $<

# phony
run: $(.DEFAULT_GOAL)
	$(EMULATOR) dist/os-image.bin

clean:
	rm -f dist/*
	rm -f mk/bin/*
	rm -f mk/kernel/*
	rm -f mk/drivers/*
	rm -f mk/cpu/*
	rm -f mk/lib/*
	rm -f mk/fs/*
	rm -f mk/iso/*
