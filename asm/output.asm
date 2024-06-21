bits 64

section .data
    helloWorld db "Hello, world!", 0xA
    identifier dq 12345

section .bss
    buffer_identifier resb 5

section .text
    global start

start:

    mov rax, identifier
    mov rax, [rax]
    mov rdi, buffer_identifier + 5
    mov byte [rdi], 0xA
convert_digit:
    dec rdi
    xor rdx, rdx
    mov rcx, 10
    div rcx
    add dl, '0'
    mov [rdi], dl
    test rax, rax
    jnz convert_digit
    mov rdx, 6
    sub rdx, rdi
    mov rax, 0x2000004
    mov rdi, 1
    lea rsi, [rel buffer_identifier]
    mov rdx, 6
    syscall 
    mov rax, 0x2000004
    mov rdi, 1
    mov rsi, helloWorld
    mov rdx, 14
    syscall 
    mov rax, 0x2000001
    xor rdi, rdi
    syscall
