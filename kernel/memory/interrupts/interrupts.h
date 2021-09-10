/*
   --- @author leosncz
   --- SmallModularOperatingSystem (SMOS) kernel memory interrupts functions header
   --- Usefull interrupts the OS will use
*/

#ifndef memory_int
#define memory_int
#include "../../basic_graphics/basic_graphics.h"
extern void setup_pic();
extern void enable_interrupt();
extern void disable_interrupt();
extern void clockIRQHandlerASM();

struct interrupt_frame* frame;

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

void setupIDT();

void clockIRQHandler();
__attribute__((interrupt)) void defaultIRQHandler(struct interrupt_frame* frame);
__attribute__((interrupt)) void keyboardIRQHandler(struct interrupt_frame* frame);
__attribute__((interrupt)) void printDebugTopLeft(struct interrupt_frame* frame); // Used for debugging
__attribute__((interrupt)) void printDebugTopRight(struct interrupt_frame* frame); // Used for debugging

#endif
