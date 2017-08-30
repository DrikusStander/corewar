.name "test"
.comment "this doesn't work very well"

start:
	sti		r1, %:zork, %4
	sti		r1, %:live2, %4
	fork	%:preattack

zork:
	live	%42
	and		%0, %0, r16
	zjmp	%:zork

preattack:
	ld		%0, r3
	ld		%1, r4
	ld		%42, r2

attack:
	sti		r2, %:target, r3
	add		r3, r4, r3

live2:
	live	%42
	and		%0, %0, r16
	zjmp	%:attack

target:
	
