.name "*"
.comment "blowjob tits fuck bitch deepthroat ass"

home:
	live	%42
	and	r10,%0,r10

goto:	
	zjmp	%:entry
	zjmp	%:home
	zjmp	%:home
	zjmp	%:home
	zjmp	%:home
	zjmp	%:home
	zjmp	%:home
	zjmp	%:home
	zjmp	%:home
	zjmp	%:home
	zjmp	%:home
	zjmp	%:home
	zjmp	%:home
	zjmp	%:home
	zjmp	%:home
	zjmp	%:home
	zjmp	%:home
	zjmp	%:home
	zjmp	%:home
	zjmp	%:home
	
entry:
	sti	r1, %:home, %1
	sti	r1, %:liver, %1
	sti	r1, %:zork, %1
	sti	r1, %:liver2, %1
	ld	%-42, r2
	ld	%0, r4
	sti	r2, %:goto, %1

liver:	
	live	%42
	fork	%:liver
	fork	%:zork
liver2:
	live	%42
	fork	%:liver
	zjmp	%:attack

zork:
	live	%42
	zjmp	%:zork

attack:
	ld	%0, r1
	ld	%14, r3

torp:
	sti	r1, %16, r4
	add	r4, r3, r4
	zjmp	%:torp
		
end:
