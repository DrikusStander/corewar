.name           "43"
.comment        "Just a basic Test Program"

test: 
	#st r1, 43
	#and r1, 42, r5
	ld %52, r3
	aff r3
	#st r5, 1999

jump:
	#zjmp %4048
