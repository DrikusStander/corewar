#
# ex.s for corewar
#
#
.name "s-ex"

.comment "this is s-ex"


l2:     sti r1,%:live,%1
	and r1,r1,%42

live:	live %1
        zjmp %:live
