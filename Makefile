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
	i686-elf-ld -o bin/kernel.bin -Ttext 0x1000 bin/kernel_entry.o bin/main.o --oformat binary

bootcode:
	nasm -f bin Bootloader/bootsector.asm -o bin/bootloader.bin

clean:
	rm bin/*.bin 
	rm bin/*.o