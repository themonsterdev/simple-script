extern GetStdHandle   ; Déclare l'utilisation de la fonction externe GetStdHandle
extern WriteFile      ; Déclare l'utilisation de la fonction externe WriteFile
extern ExitProcess    ; Déclare l'utilisation de la fonction externe ExitProcess

section .rodata                  ; Section pour les données en lecture seule
    message db "7", 0x0d, 0x0a   ; Chaîne de caractères "7" suivie de retour chariot et nouvelle ligne
    message_length equ $-message ; Longueur de la chaîne
    STD_OUTPUT_HANDLE equ -11    ; Valeur pour obtenir le handle de la sortie standard (STD_OUTPUT_HANDLE)

section .data                  ; Section pour les données variables
    stdout_handle dq 0         ; Réserve de l'espace pour le handle de la sortie standard (8 octets pour 64 bits)

section .text                  ; Section pour le code exécutable
    global start               ; Déclare le point d'entrée global du programme

start:
    ; Obtenir le handle de la sortie standard
    mov rcx, STD_OUTPUT_HANDLE        ; Place la valeur (STD_OUTPUT_HANDLE) dans le registre rcx
    call GetStdHandle                 ; Appelle la fonction GetStdHandle pour obtenir le handle de la sortie standard
    mov [rel stdout_handle], rax      ; Stocke le handle de la sortie standard dans la variable (stdout_handle)

    ; Écrire la chaîne de caractères sur la sortie standard
    mov  rcx, [rel stdout_handle] ; Place le handle de la sortie standard dans le registre rcx
    mov  rdx, message             ; Place l'adresse de la chaîne de caractères dans le registre rdx
    mov  r8, message_length       ; Place la longueur de la chaîne de caractères dans le registre r8
    xor  r9, r9                   ; Réinitialise r9 à 0 pour indiquer que bytesWritten n'est pas utilisé
    call WriteFile                ; Appelle la fonction WriteFile pour écrire la chaîne sur la sortie standard

    ; Terminer le programme
    xor  rcx, rcx              ; Place le code de sortie (0) dans le registre rcx
    call ExitProcess           ; Appelle la fonction ExitProcess pour terminer le programme
