section .data
	format: db "%d", 0
section .bss
	r: resd 32
section .text
	extern printf
	extern scanf
	global main

main:
