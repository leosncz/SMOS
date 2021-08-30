/*
   --- @author leosncz
   --- SmallModularOperatingSystem (SMOS) kernel basic graphics c file 
   --- Only purpose is to define basic graphics functions the kernel will use
*/
#include "basic_graphics.h"
void clearScreenWhite()
{
	for(int i =0;i<2000;i++){
         	printCharacter(' ', i, BLACK_ON_WHITE);
        }
}

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

void printDebug(){
	char* characterAddress = (char*)0xB8000;
        *characterAddress = 'D';
        characterAddress += 1;
        *characterAddress = 0x52;

	characterAddress += 1;
	*characterAddress = 'E';
	characterAddress += 1;
	*characterAddress = 0x52;

	characterAddress += 1;
	*characterAddress = 'B';
	characterAddress += 1;
        *characterAddress = 0x52;

	characterAddress += 1;
        *characterAddress = 'U';
        characterAddress += 1;
        *characterAddress = 0x52;

	characterAddress += 1;
        *characterAddress = 'G';
        characterAddress += 1;
        *characterAddress = 0x52;
}
