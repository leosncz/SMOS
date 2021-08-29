;--- @author leosncz
;--- SmallModularOperatingSystem (SMOS) kernel launcher 
;--- Only purpose is to load kernel c part & provide basic routines

[bits 32]
extern start
global _start
global clock_irq
global default_irq
global keyboard_irq
global setup_pic
global enable_interrupt
global disable_interrupt
global test2
global test

_start:
jmp start

test:
int 0x30
jmp $

test2:
cli
mov   ax, 0x33 ; Ring 3 DS
mov   ds, eax
push  dword 0x3B ; Ring 3 SS
push  dword 0x0
pushfd
or dword [esp], 0x200
push  dword 0x2B
push  dword 0x0
iret

enable_interrupt:
sti
ret

disable_interrupt:
cli
ret

default_irq:
mov al, 0x20
out 0x20, al
iret

clock_irq:
mov al, 0x20
out 0x20, al
iret

keyboard_irq:
mov al, 0x20
out 0x20, al
iret

setup_pic:
mov al, 0x11
out 0x20, al
out 0xA0, al
jmp tempo_1
tempo_1:
mov al, 0x20
out 0x21, al
mov al, 0x70
out 0xA1, al
jmp tempo_2
tempo_2:
mov al, 0x04
out 0x21, al
mov al, 0x02
out 0xA1, al
jmp tempo_3
tempo_3:
mov al, 0x01
out 0x21, al
out 0xA1, al
jmp tempo_4
tempo_4:
in  al, 0x21
and al, 0xEF
out 0x21, al
ret
