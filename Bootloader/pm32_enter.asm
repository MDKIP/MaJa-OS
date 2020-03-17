GDT_enter32pm:
    gdt_start: ; wymagany null
    dd 0x0
    dd 0x0
    gdt_code:
    dw 0xffff; długość segmentu
    dw 0x0; wskaźnik początku
    db 0x0; wskaźnik początku
    db 10011010b; flagi dostępu (1, poziom 2b, nie-systemowe, wykonywalny, kierunek w góre, writeable)
    db 11001111b; długość segmentu 4b + flagi (granularność - strona, tryb - pm32, 0, 0)
    db 0x0; wskaźnik początku
    gdt_data:
    dw 0xffff; długość segmentu
    dw 0x0; wskaźnik początku
    db 0x0; wskaźnik początku
    db 10010010b; flagi dostępu (1, poziom 2b, nie-systemowe, wykonywalny, kierunek w góre, writeable)
    db 11001111b; długość segmentu 4b + flagi (granularność - strona, tryb - pm32, 0, 0)
    db 0x0; wskaźnik początku
    gdt_end:
    gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; rozmiar 16b, -1
    dd gdt_start ; wskaźnik 32bit
GDT_CODE_SEG equ gdt_code - gdt_start
GDT_DATA_SEG equ gdt_data - gdt_start

[bits 16]
; void enter_32pm()
enter_32pm:
    cli ; wyłączamy przerwania
    lgdt [gdt_descriptor] ; ładujemy gdt
    mov eax, cr0
    or eax, 0x1 ; włączamy tryb 32bitowy chroniony
    mov cr0, eax
    jmp GDT_CODE_SEG:pm32_init

[bits 32]
; void pm32_init
pm32_init:
    mov ax, GDT_DATA_SEG ; ładujemy do rejetrów segmentowych
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; aktualizujemy stos i tworzymy nową ramkę
    mov ebp, 0x90000
    mov esp, ebp

    call bootloader_begin_32pm ; powrót do programu rozruchowego
