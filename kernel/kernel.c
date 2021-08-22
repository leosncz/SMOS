#include "basic_graphics/basic_graphics.h"
#include "memory/memory.h"

void kmain()
{
	setupMemory(); // Setup GDT again in case of bootloader is not ours.

	// Clear screen in case BIOS show something
	for(int i =0;i<2000;i++){
	 printCharacter(' ', i, BLACK_ON_WHITE);
	}

	char sentence[2] = {'H','i'};
	char sentence2[6] = {'/', 'H','e','l','l','o'};

	printString(sentence, 0, 2, BLACK_ON_WHITE);
	printString(sentence2, 3, 6, RED_ON_BLACK);
}
