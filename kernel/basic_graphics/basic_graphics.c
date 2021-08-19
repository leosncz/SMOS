/*
   --- @author leosncz
   --- SmallModularOperatingSystem (SMOS) kernel basic graphics c file 
   --- Only purpose is to define basic graphics functions the kernel will use
*/
#include "basic_graphics.h"

void printCharacter(char character, int offset, int bgColor, int textColor)
{
	char* characterAddress = (char*)0xB8000;
	characterAddress += offset*2;
	*characterAddress = character;

	characterAddress += 1;
	*characterAddress = 0x52;

	// TODO TAKE bgColor and textColor into account
}
