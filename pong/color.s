	.arch msp430g2553
	.p2align 1,0

	.text
	
	.global set_color_orange
	.global set_color_blue
	
	.global shapeColor

set_color_orange:
	mov #0x053F, &shapeColor

set_color_blue:
	mov #0xF800, &shapeColor
