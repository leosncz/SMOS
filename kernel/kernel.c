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
// int createProcessFromRAM(int ring, char* name, unsigned int memcpyStart, unsigned int size, unsigned int destination, unsigned int stackAddress, unsigned int kernelStackAddress, unsigned int stackSize);
	int process = createProcessFromRAM(0, "test app", (unsigned int)&printDebugTopRight, 300,0x100,0x500,0x900, 100);
	int process2 = createProcessFromRAM(0, "test app2", (unsigned int)&printDebugTopLeft, 300, 0x50000, 0x60000, 0x65000,100); 

	// Clock interrupt will take its reponsability from now on
}
