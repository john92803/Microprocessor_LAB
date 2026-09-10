start:
	mov P0, #0

scan:
	mov a, p2
	cpl a
	
chk1:
	cjne A, #00h, chk2
	mov 30h, #00h
	mov 31h, #00h
	mov 32h, #00h
	mov 33h, #00h
	mov 34h, #00h
	mov 35h, #00h
	mov 36h, #00h
	mov 37h, #00h
	jmp chk_end
chk2:
	cjne A, #40h, chk3
	call lab3
	jmp chk_end

chk3:
	cjne A, #80h, chk4
	call lab4
	jmp chk_end

chk4:
	cjne A, #0C0h, chk_end
	lab5:
		call _value1
		jmp new

	new:
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
		djnz r4, new
	aaa:
		mov a, p2
		cpl a
		cjne A, #0C0h, scan
			jmp aaa

	jmp chk_end
chk_end:
	jmp scan
	
lab3:
	init:
		mov dptr, #table1
		mov a, #0
		movc a, @a+dptr
		mov 30h, a
		mov P0, a 
		call delay100ms
		mov a, #1
		movc a, @a+dptr
		mov 31h, a
		mov P0, a 
		call delay100ms
		mov a, #2
		movc a, @a+dptr
		mov 32h, a
		mov P0, a 
		call delay100ms
		mov a, #3
		movc a, @a+dptr
		mov 33h, a
		mov P0, a 
		call delay100ms
		mov a, #4
		movc a, @a+dptr
		mov 34h, a
		mov P0, a 
		call delay100ms
		mov a, #5
		movc a, @a+dptr
		mov 35h, a
		mov P0, a 
		call delay100ms
		mov a, #6
		movc a, @a+dptr
		mov 36h, a
		mov P0, a 
		call delay100ms
		mov a, #7
		movc a, @a+dptr
		mov 37h, a
		mov P0, a 
		call delay100ms
		mov p0, #00h
		jmp scan
		delay100ms:
			mov r6,#10
		D1:
			mov r5,#10
			djnz r5,$
			djnz r6,D1
		ret
	ret
	
lab4:
	_value:
		mov dptr, #text
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
		jmp cal	
	cal:
		mov A, 30h
		add A, 32h
		mov 41h, A
		mov A, 31h
		addc A, 33h
		mov 40h, A

		clr A
		mov A, 30h
		subb A, 32h
		mov 43h, A
		mov A, 31h
		subb A, 33h
		mov 42h, A

		mov A, 30h
		mov B, 32h
		mul AB
		mov 44h, A
		mov 34h, B
		mov A, 31h
		mov B, 32h
		mul AB
		add A, 34h
		mov 45h,A
		mov A, B
		addc A, #00h
		mov 46h,A

		clr A
		mov A, 35h
		mov B, 36h
		div AB
		mov 48h, A
		mov 47h, B
		mov r5, #50
		djnz r5, $
		
ret
	

_value1:
		mov dptr, #Table1
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
		mov a, #6
		movc a, @a+dptr
		mov 36h, a
		mov a, #7
		movc a, @a+dptr
		mov 37h, a
		mov r4, #08h
		ret
Table1:
	DB 00H, 81H, 0C3H, 0E7H, 0FFH,07EH, 3CH, 18H
text: 
	db 90H, 34H, 86H, 23H, 57H,12H
end
	