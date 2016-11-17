; ---------------------------------------------------------------------------
;
; http://www.cc65.org/doc/customizing-6.html
;
; stop.s
; ---------------------------------------------------------------------------
;
; Defines what happens when BRK is vectored
.export _stop

_stop:  JMP _stop

    

