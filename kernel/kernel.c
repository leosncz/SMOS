#define DEBUG

#include "basic_graphics/basic_graphics.h"
#include "memory/memory.h"

#ifdef DEBUG
extern void test(); // Used for testing purpose - Only in DEBUG
#endif

void kmain()
{
	setupMemory(); // Setup GDT & IDT

	clearScreenWhite();

	printString("> Hi user :)", 0, 10, BLACK_ON_WHITE);
	printString("> Kernel has ended execution", 400,29, BLACK_ON_WHITE);
}
