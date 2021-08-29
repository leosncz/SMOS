#define DEBUG

#include "kernel.h"
#include "basic_graphics/basic_graphics.h"
#include "memory/memory.h"
extern void test();
extern void test2();
void start()
{
	setupMemory(); // Setup GDT,IDT & System calls

	// Setup stack
	asm("   mov $0x90000, %eax \n \
                mov %eax, %esp \n");
	clearScreenWhite();
	kmain();

	printString("> SMOS Kernel has ended execution", 80,34, BLACK_ON_WHITE);
	while(1); // Secuity loop - Should NEVER be executed
}

void kmain()
{
	addGDTCodeEntry(3, 0x100, 500);
	addGDTDataEntry(3,0x0,0xFFFF);
	addGDTStackEntry(3,0x500,500);
	memcpy(0x100, &test, 500);

	test2();

}
