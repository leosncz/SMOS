/*
   --- @author leosncz
   --- SmallModularOperatingSystem (SMOS) kernel basic graphics c file 
   --- Only purpose is to define basic graphics functions the kernel will use
*/
#include "basic_graphics.h"

void printCharacter(char character, int offset, int colorCode)
{
	char* characterAddress = (char*)0xB8000;
	characterAddress += offset*2;
	*characterAddress = character;

	characterAddress += 1;
	*characterAddress = colorCode;
}

void printString(char* string, int offset, int size, int colorCode)
{
	int offset_ = offset;
	for(int i = 0;i<size;i++)
	{
		printCharacter(string[i], offset_, colorCode);
		offset_ += 1;
	}
}
