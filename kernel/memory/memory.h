/*
   --- @author leosncz
   --- SmallModularOperatingSystem (SMOS) kernel memory functions header
   --- Usefull functions the kernel will use to handle memory
*/

#ifndef memory
#define memory

/*
   --- GDT
*/

struct gdtDescriptor{

unsigned short limit_0_15;
unsigned short base_0_15;
unsigned char base_16_23;
unsigned char access;
unsigned char limit_16_19 : 4;
unsigned char misc : 4;
unsigned char base_24_31;

} __attribute__ ((packed));

struct gdtr {
    unsigned short limit ;
    unsigned int base ;
} __attribute__ ((packed));

struct gdtDescriptor gdt[3];	/* GDT - code, data & stack*/
struct gdtr gdtr;		/* GDTR */

void setupMemory();
void *memcpy(char *dst, char *src, int n);

#endif
