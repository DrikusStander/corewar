#
# ex.s for corewar
#
#
.name "s-ex"

.comment "this is s-ex"


l2:     sti r1,%:live,%1
	and r1,%0,r1

xxx:	live %1
        zjmp %:live
