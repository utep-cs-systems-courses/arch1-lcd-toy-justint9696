	.arch msp430g2553
	.p2align 1,0

	.data
c:
	.byte 0

	.text
jt:
	.word case0
	.word case1
	.word default
	
	.global change_color
	.extern shapeColor

change_color:
	cmp #2, &c
	jhs default			; if c >= 2
	cmp #1, &c
	jnc case0			; if c < 1
	jmp case1			; c == 1

case0:
	add #1, &c		 	; c = 1
	mov #0xf800, &shapeColor 	; shapeColor = COLOR_BLUE
	jmp end				; break
	
case1:
	sub #1, &c		 	; c = 0
	mov #0x053f, &shapeColor 	; shapeColor = COLOR_ORANGE
	jmp end				; break
	
default:
	mov #0, &c			; c = 0	
	mov #0x053f, &shapeColor 	; shapeColor = COLOR_ORANGE
	jmp end				; break

end:
	pop r0
