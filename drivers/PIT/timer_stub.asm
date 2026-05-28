global TimerStub
extern TimerMain
TimerStub:
    pusha
    call TimerMain
    popa
    iretd