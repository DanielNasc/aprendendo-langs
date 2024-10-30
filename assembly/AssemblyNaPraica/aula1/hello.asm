section .data
	msg db "Hello, World!", 0xA
	msgC db "oxe kkkkkkkk", 0xA
	tam equ $- msg 
	msgD db "Agora sim", 0xA
	tamD equ $- msgD

section .text

global _start

_start: 
	mov rax, 0x4
	mov rbx, 0x1
	mov rcx, msg
	mov rdx, tam 
	int 0x80

	mov rax, 0x4
	mov rbx, 0x1
	mov rcx, msgD
	mov rdx, tamD
	int 0x80

	mov rax, 0x1 ; Diz ao SO que o programa está terminando
	mov rbx, 0x0 ; Diz ao SO que o valor de retorno é 0
	int 0x80
	
