/*
   --- @author leosncz
   --- SmallModularOperatingSystem (SMOS) kernel memory functions code
   --- Usefull functions the kernel will use to handle memory
*/

#include "gdt.h"

void setupGDT(){
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
;
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
