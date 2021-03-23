[org 0x7c00] ; bootsector offset
KERNEL_OFFSET equ 0x1000
	; load drive
	mov [BOOT_DRIVE], dl

	; init stack
	mov bp, 0x8000
	mov sp, bp

	; real mode
	mov bx, REAL_MODE_MSG
	call print
	call print_nl

	; kernel
	mov bx, KERNEL_LOAD_MSG
	call print
	call print_nl

	call load_kernel

	; PM
	mov bx, PROTECTED_MODE_MSG
	call print
	call print_nl
	%include "boot/clear_screen.asm"

	call switch_to_pm

	jmp $  		; lol this is useless but just for safety

%include "boot/print.asm"
%include "boot/load_disk.asm"
%include "boot/pm/gdt.asm"
%include "boot/pm/switch_to_pm.asm"
%include "boot/pm/print_pm.asm"

[bits 16]
load_kernel:
	mov bx, KERNEL_OFFSET
	mov dh, 15
	mov dl, [BOOT_DRIVE]
	call disk_load
	ret

[bits 32]
BEGIN_PM:
	mov ebx, ENTERED_PROTECTED_MODE_MSG
	call print_pm

	call KERNEL_OFFSET

	jmp $

; data
BOOT_DRIVE: 				db 0
REAL_MODE_MSG: 				db "Entering real mode", 0
KERNEL_LOAD_MSG: 			db "Loading kernel", 0
PROTECTED_MODE_MSG: 			db "Entering protected mode", 0
ENTERED_PROTECTED_MODE_MSG: 		db " Entered protected mode", 0
; padding and magic number
times 510-($-$$) db 0
dw 0xaa55
