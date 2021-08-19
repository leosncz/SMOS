/*
   --- @author leosncz
   --- SmallModularOperatingSystem (SMOS) kernel basic graphics header file 
   --- Only purpose is to define basic graphics functions the kernel will use
*/
#ifndef basic_graphics
#define basic_graphics

#define black_3bit 0x0
#define blue_3bit 0x1
#define green_3bit 0x2
#define cyan_3bit 0x3
#define red_3bit 0x4
#define magenta_3bit 0x5
#define yellow_3bit 0x6
#define white_3bit 0x7

void printCharacter(char character, int offset, int bgColor, int textColor);

#endif
