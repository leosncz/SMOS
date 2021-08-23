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
	gdt[3].access = 0x97;
	gdt[3].limit_16_19 = 0xF;
	gdt[3].misc = 0xD;
	gdt[3].base_24_31 = 0x0;

	// Make changes
	gdtr.limit = 4*8; // Total size of gdt
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

	for(int i = 0;i<255;i++){
		idt[i].offset_0_15 = ((int)default_irq) & 0xffff;
		idt[i].segment_selector = 0x8;
		idt[i].misc = 0x8E00;
		idt[i].offset_16_31 = ((int)default_irq & 0xffff0000) >> 16;
	}

	// Focus on created keyboard event
	idt[33].offset_0_15 = ((int)keyboard_irq) & 0xffff;
	idt[33].offset_16_31 = ((int)keyboard_irq & 0xffff0000) >> 16;

	idtr.limit = 256 * 8;
	idtr.base = &idt;
	asm("lidtl (idtr)");

	setup_pic();
	enable_interrupt();
}
