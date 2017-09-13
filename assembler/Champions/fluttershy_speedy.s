.name		"fluttershy speedy"
.comment	"oh, my, what a speedy project"

#init
entry:
	fork	%:coregeni
	st		r1, 6
	live	%42
	fork	%:t1gi
	st		r1, 6
	live	%42
	fork	%:t1gi
	st		r1, 6
	live	%42
	fork	%:t3gi

#core generator
coregeni:
	st		r1, 6				#5

coregen:
	live	%123012				#10
	fork	%:coregen			#800

#core liver
coreinit:
	st		r1, 58				#5
	st		r1, 58				#5
	st		r1, 58				#5
	st		r1, 58				#5
	st		r1, 58				#5
	st		r1, 58				#5
	st		r1, 58				#5
	st		r1, 58				#5
	st		r1, 58				#5
	st		r1, 58				#5
	ld		%0, r16				#5

corelive:
	live	%985341				#10
	live	%985341				#10
	live	%985341				#10
	live	%985341				#10
	live	%985341				#10
	live	%985341				#10
	live	%985341				#10
	live	%985341				#10
	live	%985341				#10
	live	%985341				#10
	zjmp	%:corelive			#20

#generateur def av
t1gi:
	st 		r1, 6		  		#5

t1g:
	live 	%213904		  		#10
	fork 	%:t1g 		  		#800

#torps
t1i:
	ld		%0, r2				#5	7	#offset
	ld		%4, r3				#5	7	#increment
	ld		%96, r5				#5	7	#limit
	sti		r1, %:t1c, %1		#25 7
	st		r1, 6				#5  5

t1w:
t1l:
	live	%8008135			#10 5
	ldi		%:t1i, r2, r4		#25 6
	sti		r4, %400, r2		#25 6
	add		r2, r3, r2			#10 5
	ldi		%:t1i, r2, r4		#25 6
	sti		r4, %383, r2		#25 6
	add		r2, r3, r2			#10 5
t1c:
	live	%89523				#10 5
	xor		r2, r5, r15			#6	5	#if we're done
	zjmp	%362				#20	3	#jump ahead
t1lp:
	ld		%0, r15				#5	7	#else
	zjmp	%:t1w				#20	3	#loop

#generateur torps
t2gi:
	st		r1, 6				#5

t2g:
	live	%96824				#10
	fork	%:t2g				#800

#torps
t2i:
	ld		%0, r2				#5	7	#offset
	ld		%4, r3				#5	7	#increment
	ld		%96, r5				#5	7	#limit
	sti		r1, %:t2c, %1		#25 7
	st		r1, 6				#5  5

t2w:
t2l:
	live	%8008135			#10 5
	ldi		%:t2i, r2, r4		#25 6
	sti		r4, %400, r2		#25 6
	add		r2, r3, r2			#10 5
	ldi		%:t2i, r2, r4		#25 6
	sti		r4, %383, r2		#25 6
	add		r2, r3, r2			#10 5
t2c:
	live	%89523				#10 5
	xor		r2, r5, r15			#6	5	#if we're done
	zjmp	%362				#20	3	#jump ahead
t2lp:
	ld		%0, r15				#5	7	#else
	zjmp	%:t2w				#20	3	#loop

#generateur torps
t3gi:
	st		r1, 6				#5

t3g:
	live	%96824				#10
	fork	%:t3g				#800

#torps
t3i:
	ld		%0, r2				#5	7	#offset
	ld		%4, r3				#5	7	#increment
	ld		%96, r5				#5	7	#limit
	sti		r1, %:t3c, %1		#25 7
	st		r1, 6				#5  5

t3w:
t3l:
	live	%8008135			#10 5
	ldi		%:t3i, r2, r4		#25 6
	sti		r4, %400, r2		#25 6
	add		r2, r3, r2			#10 5
	ldi		%:t3i, r2, r4		#25 6
	sti		r4, %383, r2		#25 6
	add		r2, r3, r2			#10 5
t3c:
	live	%89523				#10 5
	xor		r2, r5, r15			#6	5	#if we're done
	zjmp	%362				#20	3	#jump ahead
t3lp:
	ld		%0, r15				#5	7	#else
	zjmp	%:t3w				#20	3	#loop
