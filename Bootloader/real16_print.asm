
; wyświetla dany string na ekranie używając wywołań BIOSu
; void real_print_str(bx strptr)
real_print_str:
    pusha
    mov ah, 0x0e ; tryb tty
    real_print_str_loopstart:
    mov al, [bx] ; transfer znaku
    cmp al, 0 ; koniec str?
    jz real_print_str_loopend
    int 0x10 ; wyświetlanie znaku (BIOS)
    inc bx ; następny znak
    jmp real_print_str_loopstart
    real_print_str_loopend:
    popa
    ret

; rozpoczyna nową lini
; void real_print_nl()
real_print_nl:
    pusha
    mov ah, 0x0e
    mov al, 0x0a ; znak nowej lini
    int 0x10
    mov al, 0x0d ; cr
    int 0x10
    popa
    ret

; void real_printl(bx strptr)
real_printl:
    call real_print_str
    call real_print_nl
    ret