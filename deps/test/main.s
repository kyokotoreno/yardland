	org $0000
	org $a000
string: asciiz "Hello, World! From inside this thing"

	org $b000 ; text

; Function strcpy(char* src, char* dst)
;
; in x receives a ptr to src (null terminated)
; in y receives a ptr to dst (should have enough space to fit src)

_strcpy:
	lda 0,x
	sta 0,y
	bne _strcpy
	rts

; Function entry()

_entry:
	lda #<string
	pha
	lda #>string
	pha
	jsr _strcpy

	org $fff0
	dw $0000
	dw $0000
	dw $0000
	dw $0000
	dw $0000
	dw $0000
	dw _entry
