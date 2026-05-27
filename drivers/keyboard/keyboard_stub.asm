[bits 32]
global KeyboardStub
extern KeyboardMain
KeyboardStub:
    pusha
    call KeyboardMain
    popa
    iretd