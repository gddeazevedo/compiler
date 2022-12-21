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
