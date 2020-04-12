global gdt_load
extern main_gdt_descriptor
gdt_load:
    lgdt [main_gdt_descriptor]
    jmp 0x08:gdt_far_jump
    gdt_far_jump:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret