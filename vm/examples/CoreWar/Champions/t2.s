#
# ex.s for corewar
#
#
.name "s-ex"

.comment "this is s-ex"


l2:     sti r42,%:live,%1
	and r1,%0,r18

live:	live %1
        zjmp %:live
