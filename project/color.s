	.arch msp430g2553
	.p2align 1,0

	.text
	
	.global change_color
	.global color_handler
	
	.global shapeFgColor

change_color:
	sub #0x053F, r12
	jnz notOrange
	mov #0xF800, r12
	pop r0

notOrange:
	mov #0x053F, r12
	pop r0

color_handler:
	mov &shapeFgColor, r12
	call #change_color
	mov r12, &shapeFgColor
	
