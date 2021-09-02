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
extern void _iret();

void setupMemory(); // Setup GDT & IDT
 
void *memcpy(char *dst, char *src, int n);

int createProcessFromRAM(int ring, char* name, unsigned int memcpyStart, unsigned int size, unsigned int destination, unsigned int stackAddress, unsigned int kernelStackAddress, unsigned int stackSize);

unsigned short addGDTCodeEntry(char ring, unsigned int base, unsigned int limit);
unsigned short addGDTDataEntry(char ring, unsigned int base, unsigned int limit);
unsigned short addGDTStackEntry(char ring, unsigned int base, unsigned int limit);

void switchToProcess(int process);
int getActualProcess();
void  clockHandler();
void startProcesses();

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

struct task
{
unsigned short previous_task, previous_task_ununsed;
unsigned int esp0;
unsigned short ss0, ss0_unused;
unsigned int esp1;
unsigned short ss1, ss1_unused;
unsigned int esp2;
unsigned short ss2, ss2_unused;
unsigned int cr3;
unsigned int eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
unsigned short es, es_unused;
unsigned short cs, cs_unused;
unsigned short ss, ss_unused;
unsigned short ds, ds_unused;
unsigned short fs, fs_unused;
unsigned short gs, gs_unused;
unsigned short ldt_selector, ldt_sel_unused;
unsigned short debug_flag, io_map;
} __attribute__ ((packed));

struct task kernelTask; // Default kernel task

struct process
{
char* name;
int ring;
int active; // 0 = inactive 1 = active
int created; // 0 = not created 1 = created
unsigned int eip;
unsigned int eax, ebx, ecx, edx;
unsigned int esp;
unsigned short cs,ds,ss;
unsigned short ss0;
unsigned int esp0;
};

struct process processes[100]; // All processes - Max 100 !
#endif
