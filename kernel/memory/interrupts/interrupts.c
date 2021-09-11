/*
   --- @author leosncz
   --- SmallModularOperatingSystem (SMOS) kernel memory interrupts functions code
   --- Usefull code the OS will use to handle interrupts
*/

#include "interrupts.h"
#include "../memory.h"
int last_ = 0;
void clockIRQHandler()
{
	if(last_ == 0){last_ = 1; char* test = 0xB809E; *test = '/';}
	else if(last_ == 1){last_ = 0; char* test = 0xB809E; *test = '\\';}
}
__attribute__((interrupt)) void printDebugTopRight(struct interrupt_frame* frame)
{
        int last = 0;
        char* characterAddress = (char*)0xB8012 + 80*2;
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
        //while(1){if(last == 0){last=1; char*test = (char*)0xB8012+80*2; *test = 'D';}else{last=0; char* test2 = (char*)0xB8012+80*2; *test2 = 'd';}}
	asm("mov $0x20, %al; \n\t outb %al, $0x20;");
}

__attribute__((interrupt)) void printDebugTopLeft(struct interrupt_frame* frame)
{
        int last = 0;
        char* characterAddress = (char*)0xB8000 + 80*2;
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
        //while(1){if(last == 0){last=1; char*test = (char*)0xB8000+80*2; *test = 'D';}else{last=0; char* test2 = (char*)0xB8000+80*2; *test2 = 'd';}}
	asm("mov $0x20, %al; \n\t outb %al, $0x20;");
}

__attribute__((interrupt)) void defaultIRQHandler(struct interrupt_frame* frame)
{
	asm("mov $0x20, %al; \n\t outb %al, $0x20;");
}
__attribute__((interrupt)) void keyboardIRQHandler(struct interrupt_frame* frame)
{ 
	asm("mov $0x20, %al; \n\t outb %al, $0x20;");
}

void setupIDT()
{
	// IDT table
        for(int i = 0;i<255;i++){
                idt[i].offset_0_15 = ((int)defaultIRQHandler) & 0xffff;
                idt[i].segment_selector = 0x8;
                idt[i].misc = 0x8E00;
                idt[i].offset_16_31 = ((int)defaultIRQHandler & 0xffff0000) >> 16;
        }

        // Focus on created clock event
        idt[32].offset_0_15 = ((int)clockIRQHandlerASM) & 0xffff;
        idt[32].offset_16_31 = ((int)clockIRQHandlerASM & 0xffff0000) >> 16;

        // Focus on created keyboard event
        idt[33].offset_0_15 = ((int)keyboardIRQHandler) & 0xffff;
        idt[33].offset_16_31 = ((int)keyboardIRQHandler & 0xffff0000) >> 16;

        // System call accessible for every ring - only trap gates to keep interrupts
        // Debug sys call 0x30
        idt[48].offset_0_15 = ((int)printDebugTopLeft) & 0xffff;
        idt[48].misc = 0xEF00;
        idt[48].offset_16_31 = ((int)printDebugTopLeft & 0xffff0000) >> 16;
        // Debug sys call 0x31
        idt[49].offset_0_15 = ((int)printDebugTopRight) & 0xffff;
        idt[49].misc = 0xEF00;
        idt[49].offset_16_31 = ((int)printDebugTopRight & 0xffff0000) >> 16;

        idtr.limit = 256 * 8;
        idtr.base = &idt;
        asm("lidtl (idtr)");

        setup_pic();
}
