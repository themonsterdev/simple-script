; File: hello.s
; Description: "Hello, World!" program in assembly for macOS (x86_64)
;
; If you haven't been prompted for any other app already, manually install Rosetta 2:
; softwareupdate --install-rosetta
; @see https://apple.stackexchange.com/questions/408375/zsh-bad-cpu-type-in-executable

bits 64

section .data
    msg db "Hello World!", 0x0A ; Define the message with a newline character
    len equ $ - msg             ; Calculate the length of the message

section .text
    global start

    start:

        ; System call to write the message
        mov rax, 0x2000004  ; System call write = 4
        mov rdi, 1          ; File descriptor (stdout)
        mov rsi, msg        ; Address of the message
        mov rdx, len        ; Length of the message
        syscall             ; Invoke the kernel

        ; Exit the program
        mov rax, 0x2000001  ; System call close = 1
        mov rdi, 0          ; Exit code (success)
        syscall             ; Invoke the kernel
