#
# ex.s for corewar
#
#
.name "my test.s"

.comment "this is my test.s"

start:  
add	r4, r2, r3
sti r1, r2, %7
live %42
zjmp %-5
#l2:     sti r1,%:live,%1
#	and r1,%0,r1

#live:	live %42
#        zjmp %:live
