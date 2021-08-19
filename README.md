#SMOS
Small &amp; Modular x86 Operating System
## What is SMOS
It's an **unix-like** operating system, designed to be easily customizable by anyone to create its own OS.</br>
It supports pagination, is preemptive and small GUI system to create window(s) for your appplication(s).</br>
## How to modify & build this project
Memory organization: (can change over time)</br>
0x1000: Kernel</br>
0x7C00 bootloader</br>
0x90000 Stack beginning</br>
### Build
First, **use a cross-compiler for gcc**.</br>
Build bootloader with **nasm -f bin btldr.asm -o btldr.bin**</br>
Build kernel asm with **nasm -f elf kernel.asm -o kernelasm.o**.</br>
Build kernel c with **gcc -c kernel.c -o kernelc.o**.</br>
Link with **ld --oformat binary -Ttext 0x1000 kernelasm.o kernelc.o -o kernel.o**.</br>
Build binary image with **cat btldr.bin kernel.bin > final.bin**.</br>
You can then use this image with qemu-system-x86 or directly put it on a usb key using dd.</br>

Don't touch bootloaders & kernel files, you can edit :</br>
**Still in development, this rdme will be edited when time has come.**
