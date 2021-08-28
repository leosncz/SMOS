/*
   --- @author leosncz
   --- SmallModularOperatingSystem (SMOS) kernel memory functions header
   --- Usefull functions the kernel will use to handle memory
*/

#ifndef memory
#define memory
#include "../basic_graphics/basic_graphics.h"

extern void clock_irq();
extern void keyboard_irq();
extern void default_irq();
extern void setup_pic();
extern void enable_interrupt();
extern void disable_interrupt();

void setupMemory(); // Setup GDT & IDT
void *memcpy(char *dst, char *src, int n);

void addGDTCodeEntry(char ring, unsigned int base, unsigned int limit);
void addGDTDataEntry(char ring, unsigned int base, unsigned int limit);
void addGDTStackEntry(char ring, unsigned int base, unsigned int limit);

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

struct gdtDescriptor gdt[256];	/* GDT - code, data & stack*/
struct gdtr gdtr;
int numberOfGDTDescriptor;


struct idtDescriptor{
unsigned short offset_0_15;
unsigned short segment_selector;
unsigned short misc;
unsigned short offset_16_31;
} __attribute__ ((packed));

struct idtr{
unsigned short limit;
unsigned int base;
} __attribute__ ((packed));

struct idtDescriptor idt[256];
struct idtr idtr;

#endif
