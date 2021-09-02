/*
   --- @author leosncz
   --- SmallModularOperatingSystem (SMOS) kernel memory interrupts functions code
   --- Usefull code the OS will use to handle interrupts
*/

#include "interrupts.h"
int last_ = 0;
__attribute__((interrupt)) void clockIRQHandler(struct interrupt_frame* frame)
{
	if(last_ == 0){last_ = 1; char* test = 0xB8090; *test = '/';}
	else if(last_ == 1){last_ = 0; char* test = 0xB8090; *test = '\\';} 
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
