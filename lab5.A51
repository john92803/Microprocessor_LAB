nonorder:db 10H, 30H, 40H, 20H, 60H, 50H
_value:
	mov dptr, #nonorder
	mov a, #0
	movc a, @a+dptr
	mov 30h, a
	mov a, #1
	movc a, @a+dptr
	mov 31h, a
	mov a, #2
	movc a, @a+dptr
	mov 32h, a
	mov a, #3
	movc a, @a+dptr
	mov 33h, a
	mov a, #4
	movc a, @a+dptr
	mov 34h, a
	mov a, #5
	movc a, @a+dptr
	mov 35h, a
	mov r4, #05h
	jmp start

start:
	mov a, r4
	mov r3, a
	mov r0, #30h
	mov r1, #30h
	
restart:
	inc r1
	mov a, @r0
	subb a, @r1
	jc noswap
	mov a, @r0
	mov b, @r1
	mov @r0, b
	mov @r1, a
noswap:
	inc r0
	djnz r3, restart
	djnz r4, start
END
