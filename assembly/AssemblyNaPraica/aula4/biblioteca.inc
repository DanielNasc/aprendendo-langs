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

    TAM_BUFFER  equ 0xA

segment .bss
    BUFFER resb 0x1

section .text

saida: 
    mov eax, SYS_W
    mov ebx, STD_OUT
    mov ecx, BUFFER
    mov edx, TAM_BUFFER
	int SYS_CALL

    ret