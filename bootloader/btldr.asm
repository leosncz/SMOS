;--- @author leosncz
;--- SmallModularOperatingSystem (SMOS) 1st-stage bootloader 
;--- Only purpose is to load kernel at 0x1000

[bits 16]
[org 0x0]

mov ax, 0x07c0
mov ds, ax

; Stack starts at 0x0:0x90000 (90 000)
mov ax, 0x9000
mov ss, ax
mov ax, 0d
mov sp, ax

; Load multiple (from 2nd sector) sectors off the binary file & load them right after this 1st-stage bootloader
; kernel will be loaded at 0x1000
mov ax, 0x0100
mov es, ax
xor ax, ax
mov bx, ax

mov ah, 0x2
mov al, 50d
mov ch, 0x0
mov dh, 0x0
mov cl, 2d
; We do not have to edit dl as it has not been modified
; mov dl, dl
int 0x13

; Ensure video mode is 03 for future kernel use (80x25 16 color text (CGA,EGA,MCGA,VGA))
mov ah, 0x0
mov al, 0x3
int 0x10

; Go into pmode
mov ax, gdtend    ; calcule la limite de GDT
mov bx, gdt
sub ax, bx
mov word [gdtptr], ax

xor eax, eax
xor ebx, ebx
mov ax, ds
mov ecx, eax
shl ecx, 4
mov bx, gdt
add ecx, ebx
mov dword [gdtptr+2], ecx
cli
lgdt [gdtptr]
mov eax, cr0
or  ax, 1
mov cr0, eax

; We are in pmode!
jmp reset
reset:

; data segment
mov ax, 0x10
mov ds, ax
mov fs, ax
mov gs, ax
mov es, ax

; stack segment
mov ss, ax
mov esp, 0x90000

; NOW JUMP TO kernel
jmp dword 0x8:0x1000

; GDT Stuff
gdt:
    db 0, 0, 0, 0, 0, 0, 0, 0
gdt_cs:
    db 0xFF, 0xFF, 0x0, 0x0, 0x0, 10011011b, 11011111b, 0x0
gdt_ds:
    db 0xFF, 0xFF, 0x0, 0x0, 0x0, 10010011b, 11011111b, 0x0
gdtend:
gdtptr:
    dw 0  ; limite
    dd 0  ; base


;--- NOP jusqu'a 510 ---
times 510-($-$$) db 144
dw 0xAA55
