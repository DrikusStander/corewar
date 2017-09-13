.name "temp"
.comment "fichier de test"

start:	fork %:l2
l1:	sti r1, %:live1, %1
live1:	live %1
	ld %42, r2
	ld %0, r3
	add r2,r1,r3
	sub r3, r1, r3

	
zjump1:	ld %42, r4
	sub r3, r4, r3
	zjmp %:test1
	sti r1, %:live2, %1
live2:	live %42
	ld %42, r3
	xor r2, r3, r4
	zjmp %:live2
test1:	zjmp %:l2

l2:	sti r1, %:live3, %1
	xor r1, r1, r2
live3:	live %1
	zjmp %:live3