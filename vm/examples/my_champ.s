.name       "Celebration Funebre v0.99pl42"
.comment    "Jour J"

	ld   %0,r3
label:
    zjmp %:avantdebt
	zjmp %0             # pour eviter ecrasement
# de l'instruction suivante
code:
    live %42            # 5
	sti  r15,%0,r14         # 6
	zjmp %-200          # 3
	live %42            # 5
	sti  r15,%0,r14         # 6
	zjmp %-200          # 3
	live %42            # 5
	sti  r15,%0,r14         # 6
	zjmp %-200          # 3
	live %42            # 5
	sti  r15,%0,r14         # 6
	zjmp %-200          # 3
	sti  r15,%0,r14         # 6
	zjmp %-200          # 3
	sti  r15,%0,r14         # 6
	zjmp %-200

avantdebt:  
	sti   r1,%:code,%1  #       # mets a jour le live
	sti   r1,%:code,%15 #       # mets a jour le live
	sti   r1,%:code,%29 #       # mets a jour le live
	sti   r1,%:code,%43 #       # mets a jour le live
	sti   r1,%:code,%57 #       # mets a jour le live
	sti   r1,%:code,%71 #       # mets a jour le live

#.name "Not that bad"
#.comment "What a piece of shit"

#start:
#	ld 1, r2
#	add r1, r3, r3

#next:
#	sub r3, r4, r4
#	and %1, %1, r5
#or r1 , r5, r5

#fork:
#	fork %200
#	lldi -15, %1, r6
#	st r6, 182
#then:
#	live %42
#	sti r3 :then, %1
#	zjmp %:then


