# Réalisé par Hengruy Cao et Jean Fauquenot
# sur le modèle d'octobre rouge
# stagiaire à 42 en 2013
# jean.fauquenot@gmail.com
.name "Phibonacci"
.comment "1 1 2 3 5 8 13 21 34 55"

# r3 = 1 for incrementation
# r4 = garbage for tests
# r5 = wall incrementation
# r7 = wall
# r2 = wait
ld	%0, r4
zjmp	%:main

#Wall
wall:
st	r7, -20
st	r5, -4			;5

wall_live:
live	%10			;5
sub	r5, r3, r5		;5
ld	%0, r4
zjmp	%:wall
#EndWall

#Main
main:
ld	%4294967295, r7
ld	%7, r3
sti	r1, %:wall_live, %1	;change live by the right value
ld	%1879310315, r5 	;70 03 ff EB | ff EB(16) = -20(10)
ld	%0, r4
#EndMain

october_fork:
	live %42
	fork %:fork1
	zjmp %:october_fork
	
#October
fork1:
live	%131232			;10
fork	%:fork3			;800 = 810
fork2:
live	%131312			;10
fork	%:init1			;800
zjmp	%:init4			;20 = 830
fork3:
live	%101313			;10
fork	%:init2			;800 = 810

init3:				;1620
ld	%50336001, r2		;03 00 11 01
ld	%50331649, r3		;03 00 00 01
ld	%0, r4
live	%123144
zjmp	%:october		;3*5 + 10 + 20 = 45
init2:				;1620
ld	%50335233, r2		;03 00 0E 01
ld	%117665795, r3		;07 03 70 03
ld	%0, r4
ld	%0, r4
zjmp	%:october		;4 * 5 + 20 = 40
init1:				;1620
ld	%50334209, r2		;03 00 0A 01
ld	%57672192, r3		;03 70 02 00
ld	%0, r4
zjmp	%:october		;3 * 5 + 20 = 35
init4:				;1640
ld	%50337025, r2		;03 00 15 01
st	r1, r3
ld	%0, r4
live	%1231413
ld	%0, r4			;3*5 + 5 + 10 + (20) = 50

october:
st	r2, 7
st	r3, 2342
live	%324434
#EndOctober
