; File: hello.s
; Description: Print the value of `identifier` in assembly for macOS (x86_64)
;
; If you haven't been prompted for any other app already, manually install Rosetta 2:
; softwareupdate --install-rosetta
; @see https://apple.stackexchange.com/questions/408375/zsh-bad-cpu-type-in-executable

bits 64

section .data
    identifier dq 12345          ; Exemple de nombre à afficher

section .bss
    buffer resb 6     ; Buffer pour la chaîne de caractères (au moins 6 caractères pour 12345)

section .text
    global start

start:

    ; Initialisation des registres
    mov rax, identifier         ; Charger l'adresse de identifier dans rax
    mov rax, [rax]              ; Charger la valeur à l'adresse pointée par rax dans rax
    mov rdi, buffer + 5         ; Pointez rdi vers la fin du buffer
    mov byte [rdi], 0xA         ; Null-terminate la chaîne de caractères

    ; Boucle pour convertir chaque chiffre en ASCII
convert_digit:
    dec rdi                      ; Déplacez-vous vers l'octet précédent
    xor rdx, rdx                 ; Effacez rdx
    mov rcx, 10                  ; Diviseur pour la division
    div rcx                      ; Diviser rax par 10 (rax = quotient, rdx = reste)
    add dl, '0'                  ; Convertir le reste en chiffre ASCII
    mov [rdi], dl                ; Stocker le caractère ASCII dans le buffer
    test rax, rax                ; Vérifiez si rax est nul
    jnz convert_digit            ; Si ce n'est pas le cas, continuez la conversion

    ; Calculer la longueur de la chaîne
    mov rdx, 6                   ; Longueur de la chaîne (au moins 6 caractères pour 12345)
    sub rdx, rdi                 ; rdi pointe vers le début de la chaîne

    ; Appel système pour écrire la chaîne de caractères
    mov rax, 0x2000004                  ; Appel système write = 4
    mov rdi, 1                          ; Descripteur de fichier (stdout)
    lea rsi, [rel buffer]               ; Adresse du buffer pour la chaîne à afficher
    mov rdx, 6                          ; Longueur de la chaîne
    syscall                             ; Appel au noyau pour effectuer l'écriture

    ; Sortie du programme
    mov rax, 0x2000001           ; Appel système exit = 1
    xor rdi, rdi                 ; Code de sortie (succès)
    syscall                      ; Appel au noyau pour effectuer la sortie
