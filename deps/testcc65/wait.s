; ---------------------------------------------------------------------------
; wait.s
; ---------------------------------------------------------------------------
;
; Wait for interrupt and return

.export  _wait, _stop

; ---------------------------------------------------------------------------
; Wait for interrupt:  Forces the assembler to emit a WAI opcode ($CB)
; ---------------------------------------------------------------------------

.segment  "CODE"

.proc _wait: near

           CLI                    ; Enable interrupts
.byte      $CB                    ; Inserts a WAI opcode
           RTS                    ; Return to caller

.endproc

; ---------------------------------------------------------------------------
; Stop:  Forces the assembler to emit a WDM $FF opcode ($FF42)
; ---------------------------------------------------------------------------

.proc _stop: near

.word      $FF42                    ; Inserts a STP opcode

.endproc
