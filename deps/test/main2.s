    org 0
    org $d000

msg:
    asciiz "Hello World!, Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat."

;! Not working
; Function strcpy(char *src, char *dst)
; sizeof(char*) = 2
;
; stack = *dst
; stack+1 = *src
;_strcpy:
;    ldx #0
;    pla
;    sta $00,x
;    inx
;    rts

_entry:
    ldx #0   
:   
    lda msg,x
    beq :+
    sta $a000,x
    inx
    bra :-
:
    ;lda #1
    ;sta $a3e9
:   
    lda #0
:   
    sta $a7d0
    ina
    jsr _wait
    cmp #4
    beq :--
    bra :-
    wdm
    db $ff

_wait:
    ldx #1
:   ldy #$e0
:   dey
    bne :-
    dex
    bne :--
    rts

    org $fffc
    dw _entry
    dw 0
