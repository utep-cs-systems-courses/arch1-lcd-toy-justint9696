	.arch msp430g2553
	.p2align 1,0

	.data
c:
	.word 0

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
	mov &c, r12			; move c into r12
	add #1, r12			; add 1 to r12
	mov jt(r12), r0			; jmp to jt(r12)
	
case0:
	mov #1, &c		 	; c = 1
	mov #0xf800, &shapeColor 	; shapeColor = COLOR_BLUE
	jmp end				; break
	
case1:
	mov #0, &c		 	; c = 0
	mov #0x053f, &shapeColor 	; shapeColor = COLOR_ORANGE
	jmp end				; break
	
default:
	mov #0, &c			; c = 0	
	mov #0x053f, &shapeColor 	; shapeColor = COLOR_ORANGE
	jmp end				; break

end:
	pop r0
