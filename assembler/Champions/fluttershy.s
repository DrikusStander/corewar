.name		"fluttershy"
.comment	"oh, my, what a scary project"

#init
entry:
	fork	%:coregeni
	st		r1, 6
	live	%42
	fork	%:torpgeni
	st		r1, 6
	live	%42
	fork	%:avdefgeni

ardeftgt:

#generateur def ar
ardefgeni:
	st 		r1, 6		  		#5

ardefgen:
	live 	%213904		  		#10
	fork 	%:ardefgen	  		#800

#def ar
ardefinit:
	sti		r1, %:ardefl1, %1	#25
	st		r1, 6				#5
	live	%43123				#10
	sti		r1, %:ardefchk, %1	#25
	ld		%-6, r2		  		#5		#write offset
	ld		%-6, r3		  		#5		#increment
	ld		%150994953, r4		#5		#payload, zjmp 00 00 zjmp
	ld		%-186, r5			#5		#xord to find out if we're done

ardefwrite:
ardefl1:
	live	%295423				#10
	sti		r4, %:ardeftgt, r2	#25
	add		r2, r3, r2			#10
	sti		r4, %:ardeftgt, r2	#25
	add		r2, r3, r2			#10
ardefchk:
	live	%3940641			#10
	xor		r2, r5, r15			#6		#if we wrote enough
	zjmp	%:ardefinit			#20		#we go back to init
ardefloop:	
	ld		%0, r16				#5		#else
	zjmp	%:ardefwrite		#20		#we loop


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
avdefgeni:
	st 		r1, 6		  		#5

avdefgen:
	live 	%213904		  		#10
	fork 	%:avdefgen	  		#800

#def av
avdefinit:
	sti		r1, %:avdefl1, %1	#25
	st		r1, 6				#5
	live	%43123				#10
	sti		r1, %:avdefchk, %1	#25
	ld		%0, r2		  		#5		#write offset
	ld		%6, r3		  		#5		#increment
	ld		%150994953, r4		#5		#payload, zjmp 00 00 zjmp
	ld		%180, r5			#5		#xord to find out if we're done

avdefwrite:
avdefl1:
	live	%295423				#10
	sti		r4, %:avdeftgt, r2	#25
	add		r2, r3, r2			#10
	sti		r4, %:avdeftgt, r2	#25
	add		r2, r3, r2			#10
avdefchk:
	live	%3940641			#10
	xor		r2, r5, r15			#6		#if we wrote enough
	zjmp	%:avdefinit			#20		#we go back to init
avdefloop:	
	ld		%0, r16				#5		#else
	zjmp	%:avdefwrite		#20		#we loop

#generateur torps
torpgeni:
	st		r1, 6				#5

torpgen:
	live	%96824				#10
	fork	%:torpgen			#800

#torps
torpinit:
	ld		%0, r2				#5	7	#offset
	ld		%4, r3				#5	7	#increment
	ld		%96, r5				#5	7	#limit
	sti		r1, %:torpchk, %1	#25 7
	st		r1, 6				#5  5

torpwrite:
torpl1:
	live	%8008135			#10 5
	ldi		%:torpinit, r2, r4	#25 6
	sti		r4, %400, r2		#25 6
	add		r2, r3, r2			#10 5
	ldi		%:torpinit, r2, r4	#25 6
	sti		r4, %383, r2		#25 6
	add		r2, r3, r2			#10 5
torpchk:
	live	%89523				#10 5
	xor		r2, r5, r15			#6	5	#if we're done
	zjmp	%362				#20	3	#jump ahead
torploop:
	ld		%0, r15				#5	7	#else
	zjmp	%:torpwrite			#20	3	#loop

#cible def av
avdeftgt:
