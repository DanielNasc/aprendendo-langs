section .data
    msg db "Hello, World!", 0xA
    size equ $- msg

section .text
    global _start

    _start:
        ; Imprimir "Hello World!"
        mov rax, 0x4
        mov rbx, 0x1
        mov rcx, msg
        mov rdx, size
        int 0x80

        mov rax, 0x1
        mov rbx, 0x0
        int 0x80 ; Finalizar programa