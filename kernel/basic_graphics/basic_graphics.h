/*
   --- @author leosncz
   --- SmallModularOperatingSystem (SMOS) kernel basic graphics header file 
   --- Only purpose is to define basic graphics functions the kernel will use
*/
#ifndef basic_graphics
#define basic_graphics

#define WHITE_ON_BLACK 0x87
#define RED_ON_BLACK 0x84
#define GREEN_ON_BLACK 0x82

#define BLACK_ON_WHITE 0xF0 

#define WHITE_ON_BLUE 0x97
#define BLACK_ON_BLUE 0x90

void printDebug(); // Used for debugging
void printCharacter(char character, int offset, int colorCode);
void printString(char* string, int offset, int size, int colorCode);
void clearScreenWhite();
#endif
