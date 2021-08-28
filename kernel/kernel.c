#define DEBUG

#include "basic_graphics/basic_graphics.h"
#include "memory/memory.h"

void kmain()
{
	setupMemory(); // Setup GDT & IDT

	clearScreenWhite();

	printString("> Hi user :)", 0, 10, BLACK_ON_WHITE);
	printString("> Kernel has ended execution", 80,29, BLACK_ON_WHITE);
}
