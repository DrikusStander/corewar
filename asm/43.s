.name           "43"
.comment        "Just a basic Winner Program"

entree:	
live	%42		# entree
	ld	%0,r5
	ld	%0,r5
	zjmp	%:bite

tirf: live	%42
	fork	%:tirop
	live	%742
	sub	r3,r5,r3
	ld	%0,r11
	live	%42
	sti	r10,%-510,%0
	sti	r10,%-404,%0
	sti	r10,%-303,%0
	sti	r10,%-202,%0
	ld	%0,r11
	zjmp	%:tirf

tirop:	ld	%368,r2
	ld	%0,r3
	ld	%4,r4

bite: sti     r2,%:entree,%-4
    sti     r2,%:entree,%-8
	ld	%0,r2
	ld	%8,r3		# prepare les fork
	ld	%1,r4
	ld	%0,r6

p64deb:	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0

	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0

	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0

	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
	zjmp	%0
