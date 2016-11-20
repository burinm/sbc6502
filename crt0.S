; ---------------------------------------------------------------------------
;
; - Modified from http://www.cc65.org/doc/customizing-3.html
;
; crt0.s
; ---------------------------------------------------------------------------
;
; Startup code for cc65 (Single Board Computer version)

.export   _init, _exit
.import   _main

.export   __STARTUP__ : absolute = 1        ; Mark as startup
.import   __RAM_START__, __RAM_SIZE__       ; Linker generated
;.import   __STACK_START__, __STACK_SIZE__       ; Linker generated

.import    copydata, zerobss, initlib, donelib

.include  "zeropage.inc"

; ---------------------------------------------------------------------------
; Place the startup code in a special segment

.segment  "STARTUP"

.PC02                             ; Force 65C02 assembly mode

; ---------------------------------------------------------------------------
; A little light 6502 housekeeping

_init:    LDX     #$FF                 ; Initialize stack pointer to $01FF
          TXS
          CLD                          ; Clear decimal mode
;          SEI                          ; Turn off interrupts

; ---------------------------------------------------------------------------
; Set cc65 argument stack pointer

;          LDA     #<(__RAM_START__ + __RAM_SIZE__)
;          LDA     #<(__STACK_START__ + __STACK_SIZE__)
;          STA     sp
;          LDA     #>(__RAM_START__ + __RAM_SIZE__)
;          LDA     #>(__STACK_START__ + __STACK_SIZE__)
;          STA     sp+1

; ---------------------------------------------------------------------------
; Initialize memory storage

          JSR     zerobss              ; Clear BSS segment
          JSR     copydata             ; Initialize DATA segment
          JSR     initlib              ; Run constructors

; ---------------------------------------------------------------------------
; Call main()

          JSR     _main

; ---------------------------------------------------------------------------
; Back from main (this is also the _exit entry):  force a software break

_exit:    JSR     donelib              ; Run destructors
          BRK

