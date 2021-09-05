/*
   --- @author leosncz
   --- SmallModularOperatingSystem (SMOS) kernel memory functions code
   --- Usefull functions the kernel will use to handle memory
*/

#include "memory.h"

void *memcpy(char *dst, char *src, int n)
{
	char *p = dst;
	while (n--)
		*dst++ = *src++;
	return p;
}

void startProcesses(){
	// TODO
	return;
}

void switchToProcessSameRing0(int process)
{
	processes[getActualProcess()].active = 0;
	processes[process].active = 1;
	asm("push %0; push %1; retf;" :: "m"(processes[process].cs), "m"(processes[process].eip));
}

int getActualProcess()
{
	for(int i = 0;i<100;i++)
	{
		if(processes[i].active == 1){return i;}
	}
	return -1; // There is no active process, means we still do not have executed any process
}

int createProcessFromRAM(int ring, char* name, unsigned int memcpyStart, unsigned int size, unsigned int destination, unsigned int stackAddress, unsigned int kernelStackAddress, unsigned int stackSize){
	int offset = 0;
	for(int i = 0;i<99;i++){if(processes[i].created == 1){offset = i + 1;}}

	processes[offset].ring = ring;
	processes[offset].name = name;
	processes[offset].eax = 0x0;
        processes[offset].ebx = 0x0;
        processes[offset].ecx = 0x0;
        processes[offset].edx = 0x0;
	processes[offset].esp = stackSize;
	processes[offset].cs = addGDTCodeEntry(ring, destination, size);
	processes[offset].ds = addGDTDataEntry(ring,destination,size);
	processes[offset].ss = addGDTStackEntry(ring, stackAddress, stackSize);
	processes[offset].ss0 = addGDTStackEntry(ring, kernelStackAddress, stackSize);
	processes[offset].esp0 = stackSize;
	processes[offset].eip = 0x0;

	if(memcpyStart != destination){
		memcpy((unsigned char*)destination, (unsigned char*)memcpyStart, size);
	}

	processes[offset].created = 1;
	return offset;
}

void setupMemory(){

	setupGDT();
	setupIDT();

	asm("movw $0x21, %ax \n \
       		ltr %ax");
	asm("  	movw %%ss, %0 \n \
       		movl %%esp, %1" : "=m" (kernelTask.ss0), "=m" (kernelTask.esp0) : );

	// Processes
	for(int i = 0;i<100;i++){
		processes[i].name = "Undefined SMOS app";
		processes[i].active = 0;
		processes[i].created = 0;
	}

	enable_interrupt();
}
