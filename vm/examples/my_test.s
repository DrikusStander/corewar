.name        "ToT"
.comment	"Just a basic winner program"

test:
	ld 42, r2

entree:	
  	fork %:test2

test2:
	fork %1

final:
	fork %:test2

# these are 
# test
# comments
     
