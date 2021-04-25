[org 0x7c00]

    mov [BOOT_DRIVE], dl
    mov bp, [STACK_OFFSET]
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print
    call print_nl

    call load_kernel
    call switch_to_pm
    jmp $ ; Just for safety lol

%include "boot/print/boot_sect_print.asm"
%include "boot/print/boot_sect_print_hex.asm"
%include "boot/boot_sect_disk.asm"
%include "boot/b32/32bit-gdt.asm"
%include "boot/b32/32bit-print.asm"
%include "boot/b32/32bit-switch.asm"

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print
    call print_nl

    mov bx, KERNEL_OFFSET ; Read from disk and store in 0x1000
    mov dh, [KERNEL_SIZE]
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_string_pm
    call KERNEL_OFFSET ; Call kernel_entry
    mov ebx, MSG_CRASH_KERNEL
    call print_string_pm
    jmp $ ; if the kernel crashes

%include "boot/config.asm"

; padding
times 510 - ($-$$) db 0
dw 0xaa55
