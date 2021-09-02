/*
   --- @author leosncz
   --- SmallModularOperatingSystem (SMOS) kernel memory interrupts functions header
   --- Usefull interrupts the OS will use
*/

#ifndef memory_int
#define memory_int
extern void setup_pic();
extern void enable_interrupt();
extern void disable_interrupt();

struct interrupt_frame {
    unsigned short ip;
    unsigned short cs;
    unsigned short flags;
    unsigned short sp;
    unsigned short ss;
} __attribute__((packed));

__attribute__((interrupt)) void clockIRQHandler(struct interrupt_frame* frame);
__attribute__((interrupt)) void defaultIRQHandler(struct interrupt_frame* frame);
__attribute__((interrupt)) void keyboardIRQHandler(struct interrupt_frame* frame);

#endif
