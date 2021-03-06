; ---------------------------------------------------------------------------
;
; - Modified from http://www.cc65.org/doc/customizing-5.html
;
; interrupt.s - burin
; ---------------------------------------------------------------------------
;
; Interrupt handler.
;
; Checks for a BRK instruction and returns from all valid interrupts.

;TODO - take back out 6502 only code

.import   _stop
.export   _irq_int, _nmi_int

.segment  "CODE"

;.PC02                             ; Force 65C02 assembly mode

; ---------------------------------------------------------------------------
; Non-maskable interrupt (NMI) service routine

_nmi_int:  RTI                    ; Return from all NMI interrupts

; ---------------------------------------------------------------------------
; Maskable interrupt (IRQ) service routine

;_irq_int:  PHX                    ; Save X register contents to stack
;           TSX                    ; Transfer stack pointer to X
;           PHA                    ; Save accumulator contents to stack

;6502 only code
_irq_int:   PHA
            TXA
            PHA
            TSX
            
           INX                    ; Increment X so it points to the status
           INX                    ;   register value saved on the stack
           LDA $100,X             ; Load status register contents
           AND #$10               ; Isolate B status bit
           BNE break              ; If B = 1, BRK detected

; ---------------------------------------------------------------------------
; IRQ detected, return

;irq:       PLA                    ; Restore accumulator contents
;           PLX                    ; Restore X register contents

;6502 only

irq:        PLA
            TAX
            PLA
 
           RTI                    ; Return from all IRQ interrupts

; ---------------------------------------------------------------------------
; BRK detected, stop

break:     JMP _stop              ; If BRK is detected, something very bad
                                  ;   has happened, so stop running
