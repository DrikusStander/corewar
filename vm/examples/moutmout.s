.name		"Le MoutMout de Corenouaille"
.comment	"PINAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAGE !!!!"

##########################################################
# Initialisation des lives

		sti	r1, %:chld_ar, %1
		sti	r1, %:chld_av, %1
		sti	r1, %:ar_def, %1
		and	r16, %0, r16
		zjmp	%:fork
########################################################
# defense arriere
before:		ld	%-5, r5
		ld	%-50, r4
		ld	%-5, r3
ar_def:		live 	%1337
		sti	r4, %:before, r3
		add	r3, r5, r3
		sti	r4, %:before, r3
		add	r3, r5, r3
		sti	r4, %:before, r3
		add	r3, r5, r3
		sti	r4, %:before, r3
		xor	r3,%-440,r15
		zjmp	%:before
		and	r6, %0, r6
		zjmp	%:ar_def
########################################################
# créateur des defenses arriere

chld_ar:live	%137
	fork	%:before
	and	r16, %0, r16
	zjmp	%:chld_ar
########################################################
# créateur de défense + des lives : processus principale

fork:	
	sti r1, %:livst2, %1
	sti r1, %:livst6, %1
livst2:	
	live	%1337
	fork	%:chld_av
livst6:
	live	%1337
	fork	%:chld_ar
	sti r1, %:livest, %1
livest:
	live	%1337
	and	r16, %0, r16
	fork	%:living
	sti r1, %:livst3, %1
livst3:
	live	%1337
	fork	%:chld_ar
	sti r1, %:livst4, %1
livst4:
	live	%1337
	fork	%:chld_av
	sti r1, %:livst5, %1
livst5:
	live	%1337
	and	r16, %0, r16
	zjmp	%:fork

######################################################
# processus chargé de faire les lives a la suite
# end game

living:
	sti r1, %:liv, %1
liv:	live	%1337
	fork	%:init
	fork	%:live

init:
	sti	r1, %:live1, %1
	sti	r1, %:live2, %1
	sti	r1, %:live3, %1
	sti	r1, %:live4, %1
	sti	r1, %:live5, %1
	sti	r1, %:live6, %1
	sti	r1, %:live7, %1
	sti	r1, %:live8, %1
	sti	r1, %:live9, %1
	sti	r1, %:live10, %1
	sti	r1, %:live11, %1
	sti	r1, %:live12, %1
	sti	r1, %:live13, %1
	sti	r1, %:live14, %1
	sti	r1, %:live15, %1
	sti	r1, %:live16, %1
	sti	r1, %:live17, %1
	sti	r1, %:live18, %1

live:	and	r16, %0, r16
live1:	live	%1337
live2:	live	%1337
live3:	live	%1337
live4:	live	%1337
live5:	live	%1337
live6:	live	%1337
live7:	live	%1337
live8:	live	%1337
live9:	live	%1337
live10:	live	%1337
live11:	live	%1337
live12:	live	%1337
live13:	live	%1337
live14: live	%1337
live15:	live	%1337
live16:	live	%1337
live17:	live	%1337
live18:	live	%1337
	zjmp	%:live1

##############################################
# Loop pour torpilles

chld_av:live	%96
	fork	%:chld_av

#############################################
# Torpilles

torps:
	sti r1, %:tlive1, %1 #330
	sti r1, %:tlive2, %1 #337
	ld	%100, r12 #347
	ld	%4, r6 #354
	ld	%0, r9 #361
tlive1:
	live	%1 #368

cp:
	ldi	%:torps, r9, r10 #373
	sti	r10, %400, r9
	add	r9, r6, r9
	sub	r9, r12, r13
tlive2:
	live	%1
	zjmp	%379
	ld	%0, r13
	zjmp	%:cp
