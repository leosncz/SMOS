;--- @author leosncz
;--- SmallModularOperatingSystem (SMOS) kernel launcher 
;--- Only purpose is to load kernel c part & provide basic routines

[bits 32]
extern start
extern clockIRQHandler
global _start
global setup_pic
global enable_interrupt
global disable_interrupt
global clockIRQHandlerASM

_start:
jmp start

clockIRQHandlerASM:


call clockIRQHandler

mov al, 0x20
out 0x20, al
iret

enable_interrupt:
sti
ret

disable_interrupt:
cli
ret

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
