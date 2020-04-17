bc:
	make code
	make run

run:
	qemu-system-i386 -fda bin/os-image.bin

code:
	make bootcode
	make kernelcode
	cat bin/bootloader.bin bin/kernel.bin > bin/os-image.bin

kernelcode:
	nasm -f elf Kernel/kernel_entry.asm -o bin/kernel_entry.o
	i686-elf-gcc -ffreestanding -c Kernel/main.c -o bin/main.o
	nasm -f elf Drivers/isr.asm -o bin/isr_asm.o
	i686-elf-gcc -ffreestanding -c Drivers/isr.c -o bin/isr.o
	i686-elf-gcc -ffreestanding -c Drivers/screen.c -o bin/drivers_screen.o
	i686-elf-gcc -ffreestanding -c Drivers/ports.c -o bin/drivers_ports.o
	nasm -f elf Memory/gdt.asm -o bin/gdt_asm.o 
	i686-elf-gcc -ffreestanding -c Memory/gdt.c -o bin/gdt.o
	i686-elf-ld -o bin/kernel.bin -Ttext 0x1000 bin/kernel_entry.o bin/main.o bin/drivers_screen.o bin/drivers_ports.o bin/isr_asm.o bin/isr.o bin/gdt_asm.o bin/gdt.o --oformat binary

bootcode:
	nasm -f bin Bootloader/bootsector.asm -o bin/bootloader.bin

clean:
	rm bin/*.bin 
	rm bin/*.o