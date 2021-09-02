/*
   --- @author leosncz
   --- SmallModularOperatingSystem (SMOS) kernel memory GDT functions header
   --- Usefull functions the kernel will use to handle GDT
*/

#ifndef memory_gdt
#define memory_gdt

void setupGDT();

unsigned short addGDTCodeEntry(char ring, unsigned int base, unsigned int limit);
unsigned short addGDTDataEntry(char ring, unsigned int base, unsigned int limit);
unsigned short addGDTStackEntry(char ring, unsigned int base, unsigned int limit);

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

#endif
