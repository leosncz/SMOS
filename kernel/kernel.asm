;--- @author leosncz
;--- SmallModularOperatingSystem (SMOS) kernel launcher 
;--- Only purpose is to load kernel c part & provide basic routines

[bits 32]
extern kmain
global start

start:
call kmain
jmp $ ; Security loop in case kmain ends execution - Should NEVER happen /!\
