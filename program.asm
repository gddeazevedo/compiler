section .data
	format: db "%d", 0
section .bss
	r: resd 32
section .text
	extern printf
	extern scanf
	global main

main:
	mov ebx, r
	pusha
	push ebx
	push format
	call scanf
	popa
	add esp, 8
	mov ebx, r
	pusha
	push ebx
	push format
	call printf
	popa
	add esp, 8
	IF:
	mov esi, 0
	mov eax, 3
	mov edx, r
	mov dword [edx + 4 * esi], eax
	ELSE:
	mov esi, 0
	mov eax, 10
	mov edx, r
	mov dword [edx + 4 * esi], eax
	ENDIF:
	WHILE:
	mov esi, 0
	mov eax, 1
	mov edx, r
	mov dword [edx + 4 * esi], eax
	mov esi, 0
	mov eax, 1
	mov edx, r
	mov dword [edx + 4 * esi], eax
	jmp WHILE
	ENDWHILE:
