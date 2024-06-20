# File: hello.s
# Description: "Hello, World!" program in assembly for macOS (arm64)
#
# syscalls.master : Uses system calls defined in syscalls.master of the XNU kernel
# @see https://opensource.apple.com/source/xnu/xnu-1504.3.12/bsd/kern/syscalls.master
#
# source :
# @see https://stackoverflow.com/questions/78481684/zsh-invalid-system-call-hello-when-running-my-arm64-assembly-on-my-apple-s
#
# HTTP Server in arm64 assembly Apple silicon M1 :
# @see https://medium.com/@vincentcorbee/http-server-in-arm64-assembly-apple-silicon-m1-077a55bbe9ca
#
# ARM 64 Assembly Series— Basic definitions and registers :
# @see https://valsamaras.medium.com/arm-64-assembly-series-basic-definitions-and-registers-ec8cc1334e40
#
#                       ±----------------------+
#                       | General purpose      |
# +---------------------+----------------------+
# | Architectural names | R0, R1, R2, ..., X30 |
# | 64-bit views        | X0, X1, X2, ..., X30 |
# | 32-bit views        | W0, W1, W2, ..., W30 |
# +--------------------------------------------+
#
# - Registers R0 to R7 : are used to save arguments when calling a function (see below), while the R0 is used also to store the result which is returned by a function.
# - Registers R9 to R15: (known as scratch registers) can be used any time without any assumptions about their contents.
# - Registers R16, R17: (intra-procedure-call temporary registers) the linker may use these in PLT code. Can be used as temporary registers between calls.

.global _main

.data
    message: .ascii "Hello, World!\n"   ; Define the message with null terminator
    filename: .asciz "output.txt"       ; Define the message with null terminator

.text

    _main:

        ; int open(user_addr_t path, int flags, int mode);
        adrp x1, filename@page           ; Load address of filename into x1 (page address)
        add x1, x1, filename@pageoff     ; Add offset of filename (low 12 bits)
        mov x0, #0                       ; flags
        mov x2, #0                       ; mode
        mov x16, #5                      ; System call number for write (5 for ARM64)
        svc #0x80                        ; Invoke system call

        ; user_ssize_t write(int fd, user_addr_t cbuf, user_size_t nbyte)
        mov x0, #1                      ; Use file descriptor 1 (stdout)
        adrp x1, message@page           ; Load address of message into x1 (page address)
        add x1, x1, message@pageoff     ; Add offset of message (low 12 bits)
        mov x2, #14                     ; Load the length of the message into x2
        mov x16, #4                     ; System call number for write (4 for ARM64)
        svc #0x80                       ; Invoke system call

        ; void exit(int rval)
        mov x0, #0  ; Return code 0 (success)
        mov x16, #1 ; System call number for exit (1 for ARM64)
        svc #0x80   ; Invoke system call
