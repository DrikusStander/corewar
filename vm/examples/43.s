.name           "43"
.comment        "Just a basic Test Program"

test: 
#	sti r1, %:live, %1
live:
	live %37
	and r1, 42, r5
	ld  4, r3
	aff r3
	st r1, 65


jump:
	zjmp %4048
