text: db 89H, 45H, 93H, 27H, 67H, 15H
_value:
	mov dptr, #text
	mov a, #0
	movc a, @a+dptr
	mov 31h, a
	mov a, #1
	movc a, @a+dptr
	mov 30h, a
	mov a, #2
	movc a, @a+dptr
	mov 33h, a
	mov a, #3
	movc a, @a+dptr
	mov 32h, a
	mov a, #4
	movc a, @a+dptr
	mov 36h, a
	mov a, #5
	movc a, @a+dptr
	mov 35h, a
	jmp cal	
cal:
	mov A, 31h
	add A, 33h
	mov 41h, A
	mov A, 30h
	addc A, 32h
	mov 40h, A

	clr A
	mov A, 31h
	subb A, 33h
	mov 43h, A
	mov A, 30h
	subb A, 32h
	mov 42h, A

	mov A, 31h
	mov B, 33h
	mul AB
	mov 44h, A
	mov 34h, B
	mov A, 30h
	mov B, 33h
	mul AB
	add A, 34h
	mov 45h,A
	mov A, B
	addc A, #00h
	mov 46h,A

	clr A
	mov A, 36h
	mov B, 35h
	div AB
	mov 48h, A
	mov 47h, B

END

