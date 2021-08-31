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

void switchToProcess(int process)
{
	if(processes[process].ring == 0){
		//const int cs = 0x28;
		//set_cs(cs);
		//char testt[] = "ljmp $0x28, $0x0";
		//asm(testt);
		//asm("ljmp %0, $fake_label \n\t fake_label: \n\t" :: "i"(cs) );
	}
}

int createProcessFromRAM(int ring, char* name, unsigned int memcpyStart, unsigned int size, unsigned int destination, unsigned int stackAddress, unsigned int kernelStackAddress, unsigned int stackSize){
	int offset = 0;
	for(int i = 0;i<100;i++){
		if(processes[i].created == 1){offset = i;}
	}
	if(offset != 0){
		offset = offset + 1;
	}
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
	gdt[0].limit_0_15 = 0x0;
        gdt[0].base_0_15 = 0x0;
        gdt[0].base_16_23 = 0x0;
        gdt[0].access = 0x0;
        gdt[0].limit_16_19 = 0x0;
        gdt[0].misc = 0x0;
        gdt[0].base_24_31 = 0x0;
	//Code
	gdt[1].limit_0_15 = 0xFF;
	gdt[1].base_0_15 = 0x0;
	gdt[1].base_16_23 = 0x0;
	gdt[1].access = 0x9B;
	gdt[1].limit_16_19 = 0xF;
	gdt[1].misc = 0xD;
	gdt[1].base_24_31 = 0x0;

	//Data
	gdt[2].limit_0_15 = 0xFF;
	gdt[2].base_0_15 = 0x0;
	gdt[2].base_16_23 = 0x0;
	gdt[2].access = 0x93;
	gdt[2].limit_16_19 = 0xF;
	gdt[2].misc = 0xD;
	gdt[2].base_24_31 = 0x0;

	//Stack (not using data because growing downwards)
	gdt[3].limit_0_15 = 0xFF;
	gdt[3].base_0_15 = 0x0;
	gdt[3].base_16_23 = 0x0;
	gdt[3].access = 0x93;
	gdt[3].limit_16_19 = 0xF;
	gdt[3].misc = 0xD;
	gdt[3].base_24_31 = 0x0;

	//Kernel TSS
	kernelTask.debug_flag = 0x0;
	kernelTask.io_map = 0x0;
	kernelTask.esp0 = 0x90000;
	kernelTask.ss0 = 0x18;
	gdt[4].limit_0_15 = ((unsigned int)0x70 & 0xffff);
	gdt[4].base_0_15 = ((unsigned int)&kernelTask) & 0xffff;
	gdt[4].base_16_23 = (((unsigned int)&kernelTask) & 0xff0000) >> 16;
	gdt[4].access = 0xE9;
	gdt[4].limit_16_19 = ((unsigned int)0x70 & 0xf0000) >> 16;
	gdt[4].misc = 0x0;
	gdt[4].base_24_31 = ((unsigned int)&kernelTask & 0xff000000) >> 24;

	for(int i = 5;i<256;i++)
	{
		gdt[i].limit_0_15 = 0x0;
		gdt[i].base_0_15 = 0x0;
		gdt[i].base_16_23 = 0x0;
		gdt[i].access = 0x0;
		gdt[i].limit_16_19 = 0x0;
		gdt[i].misc = 0x0;
		gdt[i].base_24_31 = 0x0;
	}

	// Make changes
	gdtr.limit = 256*8; // Total size of gdt
	gdtr.base = &gdt;
        asm("lgdtl (gdtr)");

	asm("   movw $0x10, %ax \n \
            movw %ax, %ds       \n \
            movw %ax, %es       \n \
            movw %ax, %fs       \n \
            movw %ax, %gs       \n \
            ljmp $0x08, $next   \n \
            next:               \n");

	asm("   movw $0x18, %ax \n \
        	movw %ax, %ss \n"); 


	// IDT table
	for(int i = 0;i<255;i++){
		idt[i].offset_0_15 = ((int)default_irq) & 0xffff;
		idt[i].segment_selector = 0x8;
		idt[i].misc = 0x8E00;
		idt[i].offset_16_31 = ((int)default_irq & 0xffff0000) >> 16;
	}

	// Focus on created clock event
	idt[32].offset_0_15 = ((int)clock_irq) & 0xffff;
	idt[32].offset_16_31 = ((int)clock_irq & 0xffff0000) >> 16;

	// Focus on created keyboard event
	idt[33].offset_0_15 = ((int)keyboard_irq) & 0xffff;
	idt[33].offset_16_31 = ((int)keyboard_irq & 0xffff0000) >> 16;

	// System call accessible for every ring - only trap gates to keep interrupts
	// Debug sys call 0x30
	idt[48].offset_0_15 = ((int)printDebug) & 0xffff;
	idt[48].misc = 0xEF00;
	idt[48].offset_16_31 = ((int)printDebug & 0xffff0000) >> 16;

	idtr.limit = 256 * 8;
	idtr.base = &idt;
        asm("lidtl (idtr)");

	setup_pic();

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
	numberOfGDTDescriptor = 5;

}

unsigned short addGDTCodeEntry(char ring, unsigned int base, unsigned int limit)
{
	unsigned short gdtOffset = 0;

	gdt[numberOfGDTDescriptor].limit_0_15 = limit & 0xffff;
        gdt[numberOfGDTDescriptor].base_0_15 = base & 0xffff;
        gdt[numberOfGDTDescriptor].base_16_23 = (base & 0xff0000) >> 16;
	
	if(ring == 3){
        	gdt[numberOfGDTDescriptor].access = 0xF9; // UserSpace DPL=3 Not readable
		gdtOffset = numberOfGDTDescriptor * 8 + 3;
	}
	else{
		gdt[numberOfGDTDescriptor].access = 0x9B;
		gdtOffset = numberOfGDTDescriptor * 8;
	}
        
	gdt[numberOfGDTDescriptor].limit_16_19 = (limit & 0xf0000) >> 16;
        gdt[numberOfGDTDescriptor].misc = 0x5;
        gdt[numberOfGDTDescriptor].base_24_31 = (base & 0xff000000) >> 24;

	numberOfGDTDescriptor++;
	return gdtOffset;
}

unsigned short addGDTDataEntry(char ring, unsigned int base, unsigned int limit)
{
	unsigned short gdtOffset = 0;

	gdt[numberOfGDTDescriptor].limit_0_15 = limit & 0xffff;
        gdt[numberOfGDTDescriptor].base_0_15 = base & 0xffff;
        gdt[numberOfGDTDescriptor].base_16_23 = (base & 0xff0000) >> 16;

        if(ring == 3){
                gdt[numberOfGDTDescriptor].access = 0xF3; // UserSpace 
		gdtOffset = numberOfGDTDescriptor * 8 + 3;
        }
        else{
                gdt[numberOfGDTDescriptor].access = 0x93;
        	gdtOffset = numberOfGDTDescriptor * 8;
	}

        gdt[numberOfGDTDescriptor].limit_16_19 = (limit & 0xf0000) >> 16;
        gdt[numberOfGDTDescriptor].misc = 0x5;
        gdt[numberOfGDTDescriptor].base_24_31 = (base & 0xff000000) >> 24;

        numberOfGDTDescriptor++;
	return gdtOffset;
}

unsigned short addGDTStackEntry(char ring, unsigned int base, unsigned int limit)
{
	return  addGDTDataEntry(ring,base,limit);
}
