bits 32

section .text
    align 4
    dd NlMagicNumber
    dd NlFlags
    dd NlChecksum

global NlStart
extern NlMain

NlStart:
    cli
    mov esp, NlStackSpace
    push eax
    push ebx
    call NlMain
    hlt

section .data
    NlMagicNumber equ 0x1badb002
    NlFlags equ 0x00
    NlChecksum equ -(NlMagicNumber - NlFlags)

section .bss
    resb 8192
    NlStackSpace: