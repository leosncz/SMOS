/*
   --- @author leosncz
   --- SmallModularOperatingSystem (SMOS) kernel memory functions header
   --- Usefull functions the kernel will use to handle memory
*/

#ifndef memory
#define memory
#include "interrupts/interrupts.h"
#include "gdt/gdt.h"

void setupMemory(); // Setup GDT & IDT
 
void *memcpy(char *dst, char *src, int n);

int createProcessFromRAM(int ring, char* name, unsigned int memcpyStart, unsigned int size, unsigned int destination, unsigned int stackAddress, unsigned int kernelStackAddress, unsigned int stackSize);

int getActualProcess();

struct process
{
char* name;
int ring;
int active; // 0 = inactive 1 = active
int created; // 0 = not created 1 = created
unsigned int eip, eflags;
unsigned int eax, ebx, ecx, edx;
unsigned int esp, ebp, esi, edi;
unsigned int cs:16,ds:16,ss:16,fs:16,gs:16;
unsigned int ss0:16;
unsigned int esp0;
};

struct process processes[100]; // All processes - Max 100 !
#endif
