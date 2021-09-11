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

void app1(){asm("int $0x30;"); while(1);}
void app2(){while(1);}

void kmain()
{
// int createProcessFromRAM(int ring, char* name, unsigned int memcpyStart, unsigned int size, unsigned int destination, unsigned int stackAddress, unsigned int kernelStackAddress, unsigned int stackSize);
	int process = createProcessFromRAM(3, "test app", (unsigned int)&app1, 30,0x100,0x500,0x900, 100);
	int process2 = createProcessFromRAM(3, "test app2", (unsigned int)&app2, 30, 0x91000, 0x92000, 0x93000,100); 
	// Clock interrupt will take its reponsability from now on

	if(processes[process].cs ==  0x28){char* test = 0xB8000 + 2*80*2; *test = 'T';}

	asm("cli \n \
            push $0x3B \n \
            push $0x550 \n \
            pushfl \n \
            push $0x2B \n \
            push $0x0 \n \
            iret");

}
