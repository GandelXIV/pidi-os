NEWLINE_COUNT equ 30

clear_screen:
	mov al, 0
	jmp clear_screen_loop

clear_screen_loop:
	cmp al, NEWLINE_COUNT
	je clear_screen_end

	inc al
	call print_nl

	jmp clear_screen_loop

clear_screen_end:
	ret

