[org 0x7c00]
KERNEL equ 0x1000

; ustawianie stosu i głównej ramki stosu
mov bp, 0x8000
mov sp, bp

mov bx, MSG_STARTED16
call real_printl

; ładowanie systemu operacyjnego z dysku
mov bx, MSG_DISKLOAD
call real_printl
mov bx, KERNEL
mov dh, 10
call real_disk_load
mov bx, MSG_DISKLOAD_SUCCESS
call real_printl

; wchodzenie w tryb 32 bitowy
mov bx, MSG_PM32_ENTER
call real_printl
call enter_32pm
mov bx, MSG_PM32_ENTER_ERROR ; w razie niepowodzenia
call real_printl
jmp $

; biblioteki i pliki z danymi
%include "Bootloader/bootloader_messages.asm"
%include "Bootloader/real16_print.asm"
%include "Bootloader/bootloader_disk.asm"
%include "Bootloader/pm32_enter.asm"
%include "Bootloader/pm32_print.asm"

[bits 32]
bootloader_begin_32pm:
call pm32_clear_vm
mov esi, MSG_TEST
call KERNEL
jmp $

times 510-($-$$) db 0
dw 0xaa55
