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
    x           dd 100
    y           dd 1000
    msg1        db "X maior que Y", LF, NULL
    len1        equ $ - msg1
    msg2        db "Y maior que X", LF, NULL
    len2        equ $ - msg2

section .text

global _start

_start:
    mov eax, DWORD[x]
    mov ebx, DWORD[y]
    ; if
    cmp eax, ebx
    ; Salto condicional
    ; je -> Igual jg -> Maior jl -> Menor jle -> Menor ou igual jge -> Maior ou igual jne -> Diferente
    jg maior
    ; else
    mov ecx, msg2
    mov edx, len2

    jmp final

maior: 
    mov ecx, msg1
    mov edx, len1

final:
    mov eax, SYS_W
    mov ebx, STD_OUT
    int SYS_CALL

    mov eax, SYS_EXIT
    xor ebx, ebx
    int SYS_CALL