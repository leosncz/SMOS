# SMOS
Small &amp; Modular x86 Operating System
## What is SMOS
It's an **unix-like** operating system, designed to be easily customizable by anyone to create its own OS.</br>
It supports pagination, is preemptive and small GUI system to create window(s) for your appplication(s).</br>
## What is working today ?
- Full protected mode GDT support, ring & dynamic gdt entries are working.
- Full interrupts (example clock & keyboard) support.

![image](actualState.png)

## How to modify & build this project
Memory organization: (can change over time)</br>
0x1000: Kernel code</br>
0x7C00 Bootloader code</br>
0x90000 Kernel stack beginning</br>

### Build
**Linux distro** (arm, x86, whatever architecture you want) is almost mandatory.</br>
Just run the auto-build script, you may need to give it execute right.</br>
Don't touch bootloaders & kernel files, you can edit :</br>
**Still in development, this rdme will be edited when time has come.**
