	.arch msp430g2553
	.p2align 1,0

	.text

	.global shape_handler
	.extern redrawShape

shape_handler:
	call #outOfBounds
	cmp #2, r12
	jhs p1_score
	cmp #1, r12
	jz p2_score
	pop r0

p1_score:
	mov #1, r12
	call addScore
	mov #1, redrawShape
	pop r0
	
p2_score:
	mov #2, r12
	call addScore
	mov #1, redrawShape
	pop r0
	
