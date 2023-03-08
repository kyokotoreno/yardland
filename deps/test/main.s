    org 0
    org $1000

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

;_entry:
    ldx #0
:   lda msg,x
    beq :+
    sta $c830,x
    inx
    bra :-
_entry:
:   lda #1
    sta $00200
    clc
    xce
    rep #$30
    a16
    x16
    lda #$ffff
    tax
    tay
    mvp 1,$0b
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

msg: asciiz "Hello World!, Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat."
qb = 10

    org $fffc
    dw _entry
    dw 0

    org $10000
img: incbin "reference.rgb565"
