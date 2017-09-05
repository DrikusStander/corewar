.name           "43"
.comment        "Just a basic Test Program"

test: 
	sti r1, %:live, %1
live:
	live %37
	and r1, 42, r5
	lldi -15, %4, r3
	aff r3
	st r3, 1999

jump:
	zjmp %4048
