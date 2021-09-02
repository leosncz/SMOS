rm -rf build/
mkdir build
nasm -f bin bootloader/btldr.asm -o build/btldr.bin
nasm -f elf kernel/kernel.asm -o build/kernelasm.o

i686-elf-gcc -c kernel/kernel.c -o build/kernelc.o
i686-elf-gcc -c kernel/basic_graphics/basic_graphics.c -o build/basic_graphics.o
i686-elf-gcc -c kernel/memory/memory.c -o build/memory.o
i686-elf-gcc -c kernel/memory/interrupts/interrupts.c -mgeneral-regs-only -o build/interrupts.o 

i686-elf-ld --oformat binary -Ttext 0x1000 build/kernelasm.o build/kernelc.o build/basic_graphics.o build/memory.o build/interrupts.o -o build/kernel.bin

rm build/*.o

cat build/btldr.bin build/kernel.bin > build/final.bin
