[bits 32]

VIDEO_MEMORY equ 0xb8000
VIDEO_MEMORY_END equ 0xb8000 + 0x6d60
VM_WHITEonBLACK equ 0x0f

; void pm32_clear_vm()
pm32_clear_vm:
    pusha
    mov edi, VIDEO_MEMORY
    mov ah, VM_WHITEonBLACK
    mov al, 0
    pm32_clear_vm_loopstart:
    cmp edi, VIDEO_MEMORY_END
    jz pm32_clear_vm_loopend
    mov [edi], ax
    add edi, 2
    jmp pm32_clear_vm_loopstart
    pm32_clear_vm_loopend:
    popa
    ret


; void pm32_print_str(esi strptr)
pm32_print_str:
    pusha
    mov edi, VIDEO_MEMORY
    mov ah, VM_WHITEonBLACK
    pm32_print_str_loopstart:
    mov al, [esi]
    cmp al, 0
    jz pm32_print_str_loopend
    mov [edi], ax
    add esi, 1
    add edi, 2
    jmp pm32_print_str_loopstart
    pm32_print_str_loopend:
    mov al, 'e'
    mov [edi], ax
    popa
    ret