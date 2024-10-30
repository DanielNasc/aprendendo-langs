%include "biblioteca.inc"

section .text

global _start

_start:
    lea esi, [BUFFER] ; Load Effective Address
    add esi, 0x9
    mov byte[esi], 0xA

    dec esi
    mov dl, 0x11
    add dl, '0'
    mov [esi], dl

    call saida

    mov eax, SYS_EXIT
    xor ebx, ebx
    int SYS_CALL