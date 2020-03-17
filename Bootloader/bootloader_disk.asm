; ładuje z dysk od sektoru start_sec dokłanie num_sec sektorów i wrzuca do pamięci operacyjnej na ptr_load
; void real_disk_load(bx ptr_load, dh num_sec)
real_disk_load:
    pusha
    push dx
    ; wywołanie funkcji BIOSu
    mov ah, 0x02 ; - read
    mov al, dh ; liczba sektorów do przeczytania
    mov cl, 2 ; sektor startowy
    mov ch, 0 ; cylinder
    mov dh, 0 ; głowica
    ; es:bx - miejsce w pamięci do załadowania dysku
    int 0x13 ; wywołanie
    jc real_disk_load_error_disk ; carry trzyma informacje o błędzie dysku
    pop dx
    cmp al, dh ; al - przeczytana liczba sektorów
    jne real_disk_load_error_segments
    popa
    ret
    real_disk_load_error_disk:
    mov bx, MSG_DISKLOAD_ERROR_DISK
    call real_printl
    jmp $
    real_disk_load_error_segments:
    mov bx, MSG_DISKLOAD_ERROR_DISKSEGMENTS
    call real_printl
    jmp $