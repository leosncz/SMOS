#define DEBUG

#include "kernel.h"
#include "basic_graphics/basic_graphics.h"
#include "memory/memory.h"

void start()
{
	setupMemory(); // Setup GDT,IDT & System calls

	// Setup stack
	asm("   mov $0x90000, %eax \n \
                mov %eax, %esp \n");
	clearScreenWhite();
	kmain();

	printString("> SMOS Kernel is running", 0,25, BLACK_ON_WHITE);
	while(1); // Secuity loop - Should NEVER be executed
}

void kmain()
{
	// createProcessFromRAM(char* name, unsigned int memcpyStart, unsigned int size, unsigned int destination, unsigned int stackAddress, unsigned int kernelStackAddress)
	//int process = createProcessFromRAM("test app", &test, 500,0x100,0x500,0x900);
}
