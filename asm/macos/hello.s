; -----------------------------------------------------------------------------------------------------------------------
;
; https://stackoverflow.com/questions/78481684/zsh-invalid-system-call-hello-when-running-my-arm64-assembly-on-my-apple-s
;
; https://stackoverflow.com/questions/48845697/macos-64-bit-system-call-table
;
; -----------------------------------------------------------------------------------------------------------------------

.global _main      
.align 4    

_main:
    ; Appel système pour écrire le message
    mov X0, #1                      ; Utiliser le descripteur de fichier 1 (stdout)
    adrp X1, message@page           ; Charger l'adresse du message dans x1
    add X1, X1, message@pageoff     ; ?
    mov X2, #15                     ; Charger la longueur du message dans x2
    mov X16, #4                     ; Numéro de l'appel système pour write (4 pour ARM64)
    svc #0x80                       ; Appel système

    ; Terminer le programme
    mov     X0, #0                  ; Code de retour 0 (succès)
    mov     X16, #1                 ; Numéro de l'appel système pour exit (1 pour ARM64)
    svc     #0x80                   ; Appel système

.data
message:      
    .ascii  "Hello, World !\n"
