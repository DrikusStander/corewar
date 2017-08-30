#
# ex.s for corewar
#
#
.name "s-ex"
.comment "ta mere en slip"



l2:     sti r1,%:live,%1
	and r1,%0,r1

live:	live %1
        zjmp %:live
