segment .data
	LF 				equ	0xA ; Line Feed
	NULL			equ 0xD	; Final String
	SYS_CALL	equ	0x80;	Envia informação ao SO
	
	; eax rax
	SYS_EXIT  equ 0x1 ; Codigo para finalizar
	SYS_W			equ 0x4 ;	Operação de escrita 
	SYS_R			equ 0x3	; Operação de leitura

	; ebx rbx
	RET_EXIT 	equ 0x0 ; Operação finalizada com sucesso
	STD_OUT		equ 0x1
	STD_IN		equ 0x0

section .data
	msg 			db "Digite algo: ", LF, NULL
	tam 			equ $- msg
	
section .bss
	string		resb 1

section .text

global _start

_start:
	mov		rax, SYS_W
	mov		rbx, STD_OUT
	mov		rcx, msg
	mov		rdx, tam
	int 	SYS_CALL

	mov		rax, SYS_R
	mov		rbx, STD_IN
	mov		rcx, string
	mov		rdx, 0xF
	int 	SYS_CALL

	mov 	eax, SYS_EXIT
	mov 	ebx, RET_EXIT
	int		SYS_CALL
